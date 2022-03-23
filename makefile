.PHONY: all clear build docs

all: clear build

clear:
	@clear

build:
	g++ -o a.exe test.cpp -std=c++11

docs:
	doxygen Doxyfile