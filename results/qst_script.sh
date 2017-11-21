for i in `seq 0 10`;
do
	sed 's/replace_integer/'$((2**$i))'/g' ../pbrt-scenes/CornellBox/sceneivolpath.pbrt | ../pbrt
	sed 's/replace_integer/'$((2**$i))'/g' ../pbrt-scenes/CornellBox/sceneibdpt.pbrt | ../pbrt
done
