all: plot

plot: main.o plot.o
	g++ main.o plot.o -o plot 

plot.o: plot.cpp
	g++ -c plot.cpp 

main.o: main.cpp 
	g++ -c main.cpp 

clean: 
	rm -rf *.o plot