
CC=gcc
C_FLAGS=-Wall -o ccdoc


build:
	$(CC) $(C_FLAGS) src/*.c
