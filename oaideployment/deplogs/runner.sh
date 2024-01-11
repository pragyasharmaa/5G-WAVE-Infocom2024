
mkdir alltables alltables/wave/ alltables/nowave/ alltables/wavemean alltables/nowavemean
for ((i=1; i<=20; i++))
do
	#python3 parse_logs.py wave-$i
	cp wave-$i/finaltable.csv alltables/wave/tables$i.csv
	#python3 parse_logs.py nowave-$i
	cp nowave-$i/finaltable.csv alltables/nowave/tables$i.csv
done

#python3 mean_finder.py 
