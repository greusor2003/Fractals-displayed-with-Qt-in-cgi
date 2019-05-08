main: mtrx.o juliaset.o
	g++ -std=c++17 -O3 -fopenmp -Wall -pedantic main.cpp -o main `pkg-config --cflags --libs opencv` 

juliaset: mtrx.o
	g++ -std=c++17 juliaset.cpp -c  

mtrx: mtrx.h
	g++ -std=c++17 mtrx.cpp -c

clean:
	rm -f *.o main
	
