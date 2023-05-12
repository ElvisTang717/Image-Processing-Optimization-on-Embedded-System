## compiler and linker options
CC = g++
OUT = RTES_Optim

## default build target
all: compile

compile:
	${CC} RTES_Optim.cpp -o RTES_Optim -O0 `pkg-config opencv4 --cflags --libs` -lpthread -mfpu=neon -mcpu=Cortex-A8 -flax-vector-conversions
	./${OUT}

debug:
	${CC} -g RTES_Optim.cpp -O0 `pkg-config opencv4 --cflags --libs` -lpthread -mfpu=neon -mcpu=Cortex-A8	-flax-vector-conversions
	gdb ./a.out
	
clean: 
	rm  -f ${OUT}
