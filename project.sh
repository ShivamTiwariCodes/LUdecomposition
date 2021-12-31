#!/usr/bin/bash

make
> sequential.txt
> thread.txt
> omp.txt

str="Singular matrix error"
for (( i=100; i <= 800; i=$(( $i + 100 )) ))
do
    res=$(./sequential $i)
    if [[ "$res" == *Singular* ]]; 
	then
    		echo "Singular Matric found for matrix size = $i x $i in sequential implementation"
	else
  		echo "$res" >> sequential.txt
	fi
done

for (( i=100; i <= 800; i=$(( $i + 100 )) ))
do
	for (( j=1; j <= 8; j++))
	do
		res=$(./pthread $i $j)
		if [[ "$res" == *Singular* ]]; 
		then
    			echo "Singular Matrix found for matrix size = $i x $i and threads = $j in pthread implementation"
		else
  			echo "$res" >> thread.txt
		fi
    	done
done

for (( i=100; i <= 800; i=$(( $i + 100 )) ))
do
	for (( j=1; j <= 8; j++))
	do
		res=$(./omp $i $j)
		if [[ "$res" == *Singular* ]]; 
		then
    			echo "Singular Matric found for matrix size = $i x $i and threads = $j in openmp implementation"
		else
  			echo "$res" >> omp.txt
		fi
    	done
done

