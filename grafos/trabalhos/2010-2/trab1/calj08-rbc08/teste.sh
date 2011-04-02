#!/bin/bash

if [ ! -e /tmp/grafos ]
then
	mkdir /tmp/grafos
fi

for i in $(ls grafos/*.txt)
do
	./bfs < $i > /tmp/${i%.*}.bfs
	./dfs < $i > /tmp/${i%.*}.dfs
done

cont=1
while [ true ]
do
	for i in $(ls grafos/*.txt)
	do
		./bfs < $i > /tmp/${i%.*}.bfs.new
		./dfs < $i > /tmp/${i%.*}.dfs.new
		
		diff /tmp/${i%.*}.bfs.new /tmp/${i%.*}.bfs > /tmp/${i%.*}.bfs.diff
		diff /tmp/${i%.*}.dfs.new /tmp/${i%.*}.dfs > /tmp/${i%.*}.dfs.diff
		
		linhas=$(cat /tmp/${i%.*}.bfs.diff | wc -l)
		if (( linhas != 0 ))
		then
			echo -e "\nERRO: /tmp/"${i%.*}".bfs.diff não está vazio. Número de linhas: " $linhas
			cat "/tmp/"${i%.*}".bfs.diff"
			exit
		fi
		
		linhas=$(cat /tmp/${i%.*}.dfs.diff | wc -l)
		if (( linhas  != 0 ))
		then
			echo -e "\nERRO: /tmp/"${i%.*}".dfs.diff não está vazio. Número de linhas: " $linhas
			cat "/tmp/"${i%.*}".dfs.diff"
			exit
		fi
		
		mv /tmp/${i%.*}.bfs.new /tmp/${i%.*}.bfs
		mv /tmp/${i%.*}.dfs.new /tmp/${i%.*}.dfs
	done
	
	echo -n $cont " "
	((cont++))
done
