CC = avr-gcc
ARGS = -mmcu=atmega2560 -Os -Wall -std=gnu99

all:
	$(CC) $(ARGS) -o ledrc.hex *.c fx/*.c

