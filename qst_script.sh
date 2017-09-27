for i in `seq 0 10`;
do
	./pbrt | sed 's/replace_integer/i/g' ../pbrt-scenes/CornellBox/scenei.pbrt
done
