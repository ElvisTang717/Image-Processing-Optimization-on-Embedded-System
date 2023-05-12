## compiler and linker options
CC = g++
OUT= Sobel

## default build target
all: default

default:
	${CC} Sobel.cpp -o ${OUT} `pkg-config opencv4 --cflags --libs`
	./${OUT}
	
clean: 
	rm  -f ${OUT}
