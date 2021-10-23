CXX = g++
CXXFLAGS = -Wall -Werror -pedantic-errors -Weffc++ -Wextra -Wsign-conversion -std=c++20


all:
	${CXX} ${CXXFLAGS} main.cpp

run:
	./a.out
