for i in `seq 1 10`;
do
	sed 's/replace_integer/'$((2**$i))'/g' ../pbrt-scenes/CornellBox/scenei.pbrt | ../pbrt
done
