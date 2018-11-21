all: main.c
	avr-gcc -mmcu=atmega128p -Os -DF_CPU=16000000 main.c
	avr-objcopy a.out

install: a.out
	avrdude -p m128p -c jtagmkI -P /dev/ttyUSB0 -b 38400 -P COM5 -U flash:w:a.out

clean:
