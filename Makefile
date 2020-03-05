
GCC=g++
FLAGS=-larmadillo -O3 -std=c++17 
VERB=-Wall -Werror -Wpedantic

all: main.cpp
	${GCC} main.cpp -o main.exe ${FLAGS} ${VERB}

.PHONY: clean
clean: 
	rm main.exe
