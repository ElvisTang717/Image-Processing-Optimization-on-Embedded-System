## compiler and linker options
CC = g++
OUT= Unoptimzed_DIP

## default build target
all: default

default:
	${CC} Unoptimized_DIP.cpp -o ${OUT} `pkg-config opencv4 --cflags --libs`
	./${OUT}
	
clean: 
	rm  -f ${OUT}
