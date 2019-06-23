png_stream: mtrx.o juliaset.o
	g++ -std=c++17 -O3 -fopenmp -Wall -pedantic png_stream.cpp -o png_stream `pkg-config --cflags --libs opencv` 

juliaset: mtrx.o
	g++ -std=c++17 juliaset.cpp -c  

mtrx: mtrx.h
	g++ -std=c++17 mtrx.cpp -c

clean:
	rm -f *.o png_stream
	
