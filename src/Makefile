CFLAGS=  -g -Wall
LDFLAGS= -g

# Put a GIF into gifsOut for every .c file in sketches.

GIFS= $(addprefix gifsOut/,$(addsuffix .gif,$(basename $(notdir $(wildcard sketches/*.c)))))

# The object files that we wrote to support creating gifs from Arduino sketches
OUR_OBJS=main.o arduino.o 

# The following OBJ files are taken directly from giflib-5.0.4
# It would be better to link directly against the library if we could make
#   that work on Cygwin, but we were not successful so far.
GIFLIB_OBJS=qprintf.o gifalloc.o egif_lib.o dgif_lib.o gif_hash.o gif_font.o gif_err.o

WEBDEST=~/public_html/giffer

all:	${GIFS}

gifsOut/sketch%.gif : sketch%.exe
	./$< ../gifs/leds3.gif $@
	mkdir -p -m 755 ${WEBDEST}
	cp $@ ${WEBDEST}
	chmod a+rx ${WEBDEST}/$(notdir $@)

sketch%.o: sketches/sketch%.c
	gcc -c ${CFLAGS} -I. $< -o $@

sketch%.exe: sketch%.o ${OUR_OBJS} ${GIFLIB_OBJS}
	gcc ${LDFLAGS} ${OUR_OBJS} ${GIFLIB_OBJS} $< -o $@ 

depend:
	makedepend *.c

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
dgif_lib.o: /usr/include/stdlib.h /usr/include/Availability.h
dgif_lib.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
dgif_lib.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
dgif_lib.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
dgif_lib.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
dgif_lib.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
dgif_lib.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
dgif_lib.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
dgif_lib.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
dgif_lib.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
dgif_lib.o: /usr/include/libkern/_OSByteOrder.h
dgif_lib.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
dgif_lib.o: /usr/include/machine/types.h /usr/include/i386/types.h
dgif_lib.o: /usr/include/limits.h /usr/include/machine/limits.h
dgif_lib.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
dgif_lib.o: /usr/include/sys/syslimits.h /usr/include/stdint.h
dgif_lib.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
dgif_lib.o: /usr/include/unistd.h /usr/include/sys/unistd.h
dgif_lib.o: /usr/include/sys/select.h /usr/include/sys/_select.h
dgif_lib.o: /usr/include/stdio.h /usr/include/secure/_stdio.h
dgif_lib.o: /usr/include/secure/_common.h /usr/include/string.h
dgif_lib.o: /usr/include/secure/_string.h gif_lib.h /usr/include/stdbool.h
dgif_lib.o: gif_lib_private.h gif_hash.h
egif_lib.o: /usr/include/unistd.h /usr/include/_types.h
egif_lib.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
egif_lib.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
egif_lib.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
egif_lib.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_structs.h
egif_lib.o: /usr/include/machine/_structs.h /usr/include/i386/_structs.h
egif_lib.o: /usr/include/sys/_select.h /usr/include/stdint.h
egif_lib.o: /usr/include/stdlib.h /usr/include/Availability.h
egif_lib.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
egif_lib.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
egif_lib.o: /usr/include/i386/signal.h /usr/include/sys/resource.h
egif_lib.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
egif_lib.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
egif_lib.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
egif_lib.o: /usr/include/machine/types.h /usr/include/i386/types.h
egif_lib.o: /usr/include/stdio.h /usr/include/secure/_stdio.h
egif_lib.o: /usr/include/secure/_common.h /usr/include/string.h
egif_lib.o: /usr/include/secure/_string.h /usr/include/fcntl.h
egif_lib.o: /usr/include/sys/fcntl.h /usr/include/sys/types.h
egif_lib.o: /usr/include/sys/stat.h gif_lib.h /usr/include/stdbool.h
egif_lib.o: gif_lib_private.h gif_hash.h
gif_err.o: /usr/include/stdio.h /usr/include/_types.h
gif_err.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
gif_err.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
gif_err.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
gif_err.o: gif_lib.h /usr/include/stdbool.h gif_lib_private.h gif_hash.h
gif_err.o: /usr/include/unistd.h /usr/include/sys/unistd.h
gif_err.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
gif_err.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
gif_err.o: /usr/include/i386/_structs.h /usr/include/sys/_select.h
gif_err.o: /usr/include/stdint.h
gif_font.o: /usr/include/string.h /usr/include/_types.h
gif_font.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
gif_font.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
gif_font.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
gif_font.o: gif_lib.h /usr/include/stdbool.h
gif_hash.o: /usr/include/unistd.h /usr/include/_types.h
gif_hash.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
gif_hash.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
gif_hash.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
gif_hash.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_structs.h
gif_hash.o: /usr/include/machine/_structs.h /usr/include/i386/_structs.h
gif_hash.o: /usr/include/sys/_select.h /usr/include/stdint.h
gif_hash.o: /usr/include/stdlib.h /usr/include/Availability.h
gif_hash.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
gif_hash.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
gif_hash.o: /usr/include/i386/signal.h /usr/include/sys/resource.h
gif_hash.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
gif_hash.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
gif_hash.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
gif_hash.o: /usr/include/machine/types.h /usr/include/i386/types.h
gif_hash.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
gif_hash.o: /usr/include/stdio.h /usr/include/secure/_stdio.h
gif_hash.o: /usr/include/secure/_common.h /usr/include/string.h
gif_hash.o: /usr/include/secure/_string.h gif_lib.h /usr/include/stdbool.h
gif_hash.o: gif_hash.h gif_lib_private.h
gifalloc.o: /usr/include/stdlib.h /usr/include/Availability.h
gifalloc.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
gifalloc.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
gifalloc.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
gifalloc.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
gifalloc.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
gifalloc.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
gifalloc.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
gifalloc.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
gifalloc.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
gifalloc.o: /usr/include/libkern/_OSByteOrder.h
gifalloc.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
gifalloc.o: /usr/include/machine/types.h /usr/include/i386/types.h
gifalloc.o: /usr/include/stdio.h /usr/include/secure/_stdio.h
gifalloc.o: /usr/include/secure/_common.h /usr/include/string.h
gifalloc.o: /usr/include/secure/_string.h gif_lib.h /usr/include/stdbool.h
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
main.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h gif_lib.h
main.o: /usr/include/stdbool.h arduinoState.h arduino.h /usr/include/math.h
main.o: /usr/include/architecture/i386/math.h
qprintf.o: /usr/include/stdio.h /usr/include/_types.h
qprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
qprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
qprintf.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
qprintf.o: /usr/include/stdbool.h /usr/include/stdarg.h gif_lib.h
