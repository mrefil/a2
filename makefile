# FILE 			:	makefile
# PROJECT 		:	PROG2030 - Assignment #2
# PROGRAMMER 	:	Mustafa Efiloglu
# DATE 			:	02/02/2022
# DESCRIPTION 	:	This file compile functions and sources from encodeInput
#
# =======================================================
#                  		encodeInput
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/encodeInput.o ./obj/assembly.o ./obj/srec.o
	cc ./obj/encodeInput.o ./obj/assembly.o ./obj/srec.o -o ./bin/encodeInput

# =======================================================
#                     	Dependencies
# =======================================================                     
./obj/encodeInput.o : ./src/encodeInput.c ./inc/encodeInput.h
	cc -c ./src/encodeInput.c -o ./obj/encodeInput.o

./obj/assembly.o : ./src/assembly.c ./inc/encodeInput.h
	cc -c ./src/assembly.c -o ./obj/assembly.o

./obj/srec.o : ./src/srec.c ./inc/encodeInput.h
	cc -c ./src/srec.c -o ./obj/srec.o

#
# =======================================================	
# 						Other targets
# =======================================================                     
all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	


