all: clean compile link run

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	
	
	
link:
	g++  -o bin/main bin/Settlement.o bin/main.o
clean:
	rm -f bin/*

run:
	rm -f bin/*.o
	./bin/main
