CFLAGS= -I../giflib/include -L../giflib/lib -lgif -g

BINARIES= oldLoop1 main main2
GIFS= oldLoop1.gif main2.gif

WEBDEST=~/public_html/giffer

all:	${BINARIES} ${GIFS}


oldLoop1.gif:	oldLoop1
	LD_LIBRARY_PATH=../giflib/lib ./oldLoop1 < ../gifs/leds3.gif > oldLoop1.gif
	mkdir -p -m 755 ${WEBDEST}
	cp oldLoop1.gif ${WEBDEST}
	chmod a+rx ${WEBDEST}/oldLoop1.gif

main2.gif: main2
	LD_LIBRARY_PATH=../giflib/lib ./main2 ../gifs/leds3.gif main2.gif
	mkdir -p -m 755 ${WEBDEST}
	cp main2.gif ${WEBDEST}
	chmod a+rx ${WEBDEST}/main2.gif


oldLoop1: oldLoop1.o  qprintf.o 
	gcc ${CFLAGS} oldLoop1.o  qprintf.o -o oldLoop1 

main2: main2.o  qprintf.o arduino.o sketch.o
	gcc ${CFLAGS} main2.o arduino.o qprintf.o sketch.o -o main2 

main:	main.o arduino.o sketch.o
	${CC} ${CFLAGS} main.o arduino.o sketch.o -o main

depend:
	makedepend -I../giflib/include -I/usr/include *.c

clean:
	/bin/rm -f *.o ${BINARIES} ${GIFS}


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
arduino.o: /usr/include/architecture/i386/math.h
main.o: giffer.h Arduino.h /usr/include/stdlib.h /usr/include/Availability.h
main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
main.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
main.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
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
main.o: /usr/include/secure/_common.h /usr/include/math.h
main.o: /usr/include/architecture/i386/math.h /usr/include/stdio.h
main.o: /usr/include/secure/_stdio.h
oldLoop1.o: /usr/include/stdio.h /usr/include/_types.h
oldLoop1.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
oldLoop1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
oldLoop1.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
oldLoop1.o: /usr/include/stdlib.h /usr/include/Availability.h
oldLoop1.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
oldLoop1.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
oldLoop1.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
oldLoop1.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
oldLoop1.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
oldLoop1.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
oldLoop1.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
oldLoop1.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
oldLoop1.o: /usr/include/machine/types.h /usr/include/i386/types.h
oldLoop1.o: /usr/include/string.h /usr/include/secure/_string.h
oldLoop1.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
oldLoop1.o: ../giflib/include/gif_lib.h /usr/include/stdbool.h
qprintf.o: /usr/include/stdio.h /usr/include/_types.h
qprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
qprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
qprintf.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
qprintf.o: /usr/include/stdbool.h /usr/include/stdarg.h /usr/include/stdarg.h
qprintf.o: ../giflib/include/gif_lib.h
