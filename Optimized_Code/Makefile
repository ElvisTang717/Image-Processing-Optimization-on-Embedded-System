## compiler and linker options
CC = g++
OUT = Optimized_DIP

## default build target
all: compile

compile:
	${CC} Optimized_DIP.cpp -o Optimized_DIP -O0 `pkg-config opencv4 --cflags --libs` -lpthread -mfpu=neon -mcpu=Cortex-A8 -flax-vector-conversions
	./${OUT}

debug:
	${CC} -g Optimized_DIP.cpp -O0 `pkg-config opencv4 --cflags --libs` -lpthread -mfpu=neon -mcpu=Cortex-A8	-flax-vector-conversions
	gdb ./Optimized_DIP.out
	
clean: 
	rm  -f ${OUT}
