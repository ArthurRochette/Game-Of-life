all: main.o
	g++ main.o -o gameoflife -lsfml-graphics -lsfml-window -lsfml-system -lpthread
	rm *.o
main.o: main.cpp
	g++ -c main.cpp -g
clean:
	rm -f *.o
	rm gameoflife
