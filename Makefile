
all: main.cpp
	g++ main.cpp -o main.exe -larmadillo -O3

.PHONY: clean
clean: 
	rm main.exe