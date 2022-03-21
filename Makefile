CXX = g++
CXXLAGS = -Wall -Werror -pedantic --std=c++14

all: prog

prog: CelestialBody.o
	$(CXX) $(CXXFLAGS) -o NBody CelestialBody.o -lsfml-graphics -lsfml-window -lsfml-system

CelestialBody.o: CelestialBody.cpp CelestialBody.h Universe.h
	$(CXX) $(CXXFLAGS) -c CelestialBody.cpp

clean:
	rm -f NBody *.o
