all: main.c
	avr-gcc -mmcu=atmega128 -Os -DF_CPU=16000000 main.c
	avr-objcopy -O ihex a.out a.hex

install: a.out
	avrdude -p m128 -c jtagmkI -P /dev/ttyUSB0 -b 9600 -U flash:w:a.hex

clean:
