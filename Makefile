
GCC=g++
FLAGS=-larmadillo -O3 -std=c++17 
VERB=-Wall -Werror -Wpedantic
WEB=firefox

all: main.cpp
	${GCC} main.cpp -o main.exe ${FLAGS} ${VERB}

doxy:
	doxygen
	${WEB} Doxy/html/index.html &

.PHONY: clean
clean: 
	rm \
	    main.exe \
	    Doxy/html/search/*
	    Doxy/html/* \
	    Doxy/latex/*
