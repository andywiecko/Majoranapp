
GCC=g++
FLAGS=-larmadillo -O3 -std=c++17 
VERB=-Wall -Werror -Wpedantic
WEB=firefox

all: majoranapp.cpp
	${GCC} majoranapp.cpp -o majoranapp.exe ${FLAGS} ${VERB}

doxy:
	doxygen
	${WEB} Doxy/html/index.html &

.PHONY: clean
clean: 
	rm \
	    majoranapp.exe \
	    Doxy/html/search/*
	    Doxy/html/* \
	    Doxy/latex/*
