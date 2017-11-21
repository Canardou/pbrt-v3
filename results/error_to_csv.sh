rm error.csv
for i in `seq 0 10`;
do
	x=$(identify -format "%[fx:mean.r ]\n" errorcornell-box-$((2**$i))spp.png)
	y=$(identify -format "%[fx:mean.r ]\n" errorbdpt_cornell-box-$((2**$i))spp.png)
	echo $((2**$i)) $x $y >> error.csv
done
