CXX = g++
CXXFLAGS = -std=c++0x

main: main.o utility.o city.o edge.o christofides.o twoOpt.o 
	${CXX} ${CXXFLAGS} main.o utility.o city.o edge.o christofides.o twoOpt.o -o main

main.o: main.cpp
	${CXX} -c main.cpp

utility.o: utility.hpp utility.cpp
	${CXX} -c utility.cpp

city.o: city.hpp city.cpp
	${CXX} -c city.cpp

edge.o: edge.hpp edge.cpp
	${CXX} -c edge.cpp

christofides.o: christofides.hpp christofides.cpp
	${CXX} -c christofides.cpp

twoOpt.o: twoOpt.hpp twoOpt.cpp
	${CXX} -c twoOpt.cpp

clean:
	rm *o main
