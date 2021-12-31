CC=g++
all: sequentialObj threadingObj openmpobj

sequentialObj:
	$(CC) LUsequential.cpp -o sequential
	
threadingObj:
	$(CC) LUthreading.cpp -o pthread -pthread
	
openmpobj:
	$(CC) LUomp.cpp -o omp -fopenmp

splot:
	python3 sequentialplot.py
	
tplot:
	python3 pthreadplot.py
	
oplot:
	python3 ompplot.py

clear:
	rm *.txt
