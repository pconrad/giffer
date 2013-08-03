CFLAGS= -I../giflib/include -g
LDFLAGS=-L../giflib/lib -lgif -g

# Put a GIF into gifsOut for every .c file in sketches.

GIFS= $(addprefix gifsOut/,$(addsuffix .gif,$(basename $(notdir $(wildcard sketches/*.c)))))

WEBDEST=~/public_html/giffer

all:	${GIFS}

gifsOut/sketch%.gif : sketch%.exe
	LD_LIBRARY_PATH=../giflib/lib ./$< ../gifs/leds3.gif $@
	mkdir -p -m 755 ${WEBDEST}
	cp $@ ${WEBDEST}
	chmod a+rx ${WEBDEST}/$(notdir $@)

sketch%.o: sketches/sketch%.c
	gcc -c ${CFLAGS} -I. $< -o $@

sketch%.exe: sketch%.o main.o qprintf.o arduino.o 
	gcc ${LDFLAGS} main.o qprintf.o arduino.o $< -o $@ 

depend:
	makedepend -I../giflib/include -I/usr/include *.c

clean:
	/bin/rm -f *.o *.exe ${GIFS}


# DO NOT DELETE

arduino.o: arduino.h /usr/include/stdlib.h /usr/include/Availability.h
arduino.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
arduino.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
arduino.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
arduino.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
arduino.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
arduino.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
arduino.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
arduino.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
arduino.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
arduino.o: /usr/include/libkern/_OSByteOrder.h
arduino.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
arduino.o: /usr/include/machine/types.h /usr/include/i386/types.h
arduino.o: /usr/include/string.h /usr/include/secure/_string.h
arduino.o: /usr/include/secure/_common.h /usr/include/math.h
arduino.o: /usr/include/architecture/i386/math.h /usr/include/stdio.h
arduino.o: /usr/include/secure/_stdio.h arduinoState.h
main.o: /usr/include/stdio.h /usr/include/_types.h /usr/include/sys/_types.h
main.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
main.o: /usr/include/secure/_common.h /usr/include/stdlib.h
main.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
main.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
main.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
main.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
main.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
main.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
main.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
main.o: /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/string.h /usr/include/secure/_string.h
main.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
main.o: ../giflib/include/gif_lib.h /usr/include/stdbool.h arduinoState.h
main.o: arduino.h /usr/include/math.h /usr/include/architecture/i386/math.h
qprintf.o: /usr/include/stdio.h /usr/include/_types.h
qprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
qprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
qprintf.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
qprintf.o: /usr/include/stdbool.h /usr/include/stdarg.h /usr/include/stdarg.h
qprintf.o: ../giflib/include/gif_lib.h
