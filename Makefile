# Ulysses Butler
# Madison Miller
# Final Project

install-game: game.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:game.hex:i

button.o: button.c led.h common.h
	avr-gcc -mmcu=atmega328p -c button.c -o button.o

common.o: common.c common.h
	avr-gcc -mmcu=atmega328p -c common.c -o common.o

rng.o: rng.c rng.h common.h
	avr-gcc -mmcu=atmega328p -c rng.c -o rng.o

led.o: led.c led.h sound.h common.h
	avr-gcc -mmcu=atmega328p -c led.c -o led.o

sound.o: sound.c sound.h common.h
	avr-gcc -mmcu=atmega328p -c sound.c -o sound.o

#sleepy.o: sleepy.S
#	avr-gcc -mmcu=atmega328p -c sleepy.S -o sleepy.o

game.o: game.c led.h common.h button.h rng.h sleepy.h
	avr-gcc -mmcu=atmega328p -c game.c -o game.o

game.elf: game.o sound.o led.o rng.o common.o button.o
	avr-gcc -mmcu=atmega328p game.o sound.o led.o button.o common.o rng.o -o game.elf
	avr-strip game.elf

game.hex: game.elf
	avr-objcopy -j .text -j .data -O ihex game.elf game.hex

clean:
	rm -f *.o *.elf *.hex *.lst
