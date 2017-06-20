//
// Created by stardami on 5/16/17.
//

#include <fstream>
#include <iomanip>
#include "pbrt.h"
#include "paramset.h"
#include "pathoutput.h"
#include "extractor.h"
#include "fileutil.h"

namespace pbrt {

void PathOutputTile::AddSample(const Point2f &pFilm, std::shared_ptr<Container> container) {
  VLOG(2) << "New path sample";
  ProfilePhase p(Prof::AddPathSample);
  std::vector<path_entry> entries = container->GetPaths();
  tilepaths.insert(tilepaths.end(), entries.begin(), entries.end());
}


std::unique_ptr<PathOutputTile> PathOutput::GetPathTile() {
  return std::unique_ptr<PathOutputTile>(new PathOutputTile());
}

void PathOutput::MergePathTile(std::unique_ptr<PathOutputTile> tile) {
  VLOG(1) << "Merging path tile " << tile->pixelBounds;
  ProfilePhase _(Prof::MergePathTile);
  std::lock_guard<std::mutex> lock(mutex);

  // Path addition during rendering disabled (currently: slowing down rendering in text mode due to formatting)
  AppendPaths(tile->tilepaths, !HasExtension(filename, ".txtdump"));
}

void PathOutput::AppendPaths(const std::vector<path_entry> &entries, bool binarymode) {
  ProfilePhase _(Prof::MergePathTile);
  for(const path_entry &entry: entries) {
    if(!binarymode) {
      f << "Path:";
      std::ostringstream str;
      str << entry;
      f << str.str() << "\n";
    } else {
      f << entry;
    }
  }
  npaths += entries.size();
}



void PathOutput::WriteFile() {
  ProfilePhase p(Prof::PathWriteOutput);
  // Seek to beginning and write header
  f.seekp(std::ios::beg);
  f << "Path file; n = " << npaths;
  f.close();
}


PathOutput *CreatePathOutput(const ParamSet &params) {
  // Intentionally use FindOneString() rather than FindOneFilename() here
  // so that the rendered image is left in the working directory, rather
  // than the directory the scene file lives in.
  std::string filename = params.FindOneString("filename", "");
  if (filename == "") filename = "pbrt_pathextract.txt";

  return new PathOutput(filename);
}
}