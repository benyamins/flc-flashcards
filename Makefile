CXX = clang++
CXXFLAGS = -Wall -Werror -pedantic-errors -Weffc++ -Wextra -Wsign-conversion -std=c++20
BUILD_DIR = build


all:
	${CXX} ${CXXFLAGS} main.cpp -o ${BUILD_DIR}/flc
