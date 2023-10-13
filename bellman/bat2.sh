for i in bat2/*.mtx
do
	echo -e "\e[33mInstância $i\e[0m";
	./bellman.bin -f $i -o output/$(basename $i)

done