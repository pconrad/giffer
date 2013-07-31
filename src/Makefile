CFLAGS= -I../giflib/include -L../giflib/lib -lgif

BINARIES= giffer1 giffer2 gifferLoop1
GIFS=giffer1.gif giffer2.gif gifferLoop1.gif

WEBDEST=~/public_html/giffer

all:	${BINARIES} ${GIFS}


giffer1.gif:	giffer1
	LD_LIBRARY_PATH=../giflib/lib ./giffer1 < ../gifs/leds3.gif > giffer1.gif
	mkdir -p -m 755 ${WEBDEST}
	cp giffer1.gif ${WEBDEST}
	chmod a+rx ${WEBDEST}/giffer1.gif

giffer1: giffer1.o  qprintf.o 
	gcc ${CFLAGS} giffer1.o  qprintf.o -o giffer1 

giffer2.gif:	giffer2
	LD_LIBRARY_PATH=../giflib/lib ./giffer2 < ../gifs/leds3.gif > giffer2.gif
	mkdir -p -m 755 ${WEBDEST}
	cp giffer2.gif ${WEBDEST}
	chmod a+rx ${WEBDEST}/giffer2.gif

giffer2: giffer2.o  qprintf.o 
	gcc ${CFLAGS} giffer2.o  qprintf.o -o giffer2 


gifferLoop1.gif:	gifferLoop1
	LD_LIBRARY_PATH=../giflib/lib ./gifferLoop1 < ../gifs/leds3.gif > gifferLoop1.gif
	mkdir -p -m 755 ${WEBDEST}
	cp gifferLoop1.gif ${WEBDEST}
	chmod a+rx ${WEBDEST}/gifferLoop1.gif

gifferLoop1: gifferLoop1.o  qprintf.o 
	gcc ${CFLAGS} gifferLoop1.o  qprintf.o -o gifferLoop1 



depend:
	makedepend -I../giflib/include -I/usr/include *.c

clean:
	/bin/rm -f *.o ${BINARIES} ${GIFS}


# DO NOT DELETE

colorMapMerge1.o: /usr/include/stdio.h /usr/include/_types.h
colorMapMerge1.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
colorMapMerge1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
colorMapMerge1.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
colorMapMerge1.o: /usr/include/stdlib.h /usr/include/Availability.h
colorMapMerge1.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
colorMapMerge1.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
colorMapMerge1.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
colorMapMerge1.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
colorMapMerge1.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
colorMapMerge1.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
colorMapMerge1.o: /usr/include/sys/_endian.h
colorMapMerge1.o: /usr/include/libkern/_OSByteOrder.h
colorMapMerge1.o: /usr/include/libkern/i386/_OSByteOrder.h
colorMapMerge1.o: /usr/include/alloca.h /usr/include/machine/types.h
colorMapMerge1.o: /usr/include/i386/types.h /usr/include/string.h
colorMapMerge1.o: /usr/include/secure/_string.h /usr/include/fcntl.h
colorMapMerge1.o: /usr/include/sys/fcntl.h getarg.h /usr/include/stdbool.h
colorMapMerge1.o: ../giflib/include/gif_lib.h
getarg.o: /usr/include/stdlib.h /usr/include/Availability.h
getarg.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
getarg.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
getarg.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
getarg.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
getarg.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
getarg.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
getarg.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
getarg.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
getarg.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
getarg.o: /usr/include/libkern/_OSByteOrder.h
getarg.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
getarg.o: /usr/include/machine/types.h /usr/include/i386/types.h
getarg.o: /usr/include/stdio.h /usr/include/secure/_stdio.h
getarg.o: /usr/include/secure/_common.h /usr/include/string.h
getarg.o: /usr/include/secure/_string.h /usr/include/stdbool.h
getarg.o: /usr/include/stdarg.h /usr/include/stdarg.h getarg.h
makeColorMap.o: makeColorMap.h /usr/include/stdio.h /usr/include/_types.h
makeColorMap.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
makeColorMap.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
makeColorMap.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
makeColorMap.o: /usr/include/stdlib.h /usr/include/Availability.h
makeColorMap.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
makeColorMap.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
makeColorMap.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
makeColorMap.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
makeColorMap.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
makeColorMap.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
makeColorMap.o: /usr/include/sys/_endian.h
makeColorMap.o: /usr/include/libkern/_OSByteOrder.h
makeColorMap.o: /usr/include/libkern/i386/_OSByteOrder.h
makeColorMap.o: /usr/include/alloca.h /usr/include/machine/types.h
makeColorMap.o: /usr/include/i386/types.h /usr/include/string.h
makeColorMap.o: /usr/include/secure/_string.h /usr/include/fcntl.h
makeColorMap.o: /usr/include/sys/fcntl.h getarg.h /usr/include/stdbool.h
makeColorMap.o: ../giflib/include/gif_lib.h
mysponge1.o: /usr/include/stdio.h /usr/include/_types.h
mysponge1.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
mysponge1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
mysponge1.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
mysponge1.o: /usr/include/stdlib.h /usr/include/Availability.h
mysponge1.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
mysponge1.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mysponge1.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mysponge1.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
mysponge1.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
mysponge1.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mysponge1.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mysponge1.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mysponge1.o: /usr/include/machine/types.h /usr/include/i386/types.h
mysponge1.o: /usr/include/string.h /usr/include/secure/_string.h
mysponge1.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h getarg.h
mysponge1.o: /usr/include/stdbool.h ../giflib/include/gif_lib.h
mysponge2.o: /usr/include/stdio.h /usr/include/_types.h
mysponge2.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
mysponge2.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
mysponge2.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
mysponge2.o: /usr/include/stdlib.h /usr/include/Availability.h
mysponge2.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
mysponge2.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mysponge2.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mysponge2.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
mysponge2.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
mysponge2.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mysponge2.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mysponge2.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mysponge2.o: /usr/include/machine/types.h /usr/include/i386/types.h
mysponge2.o: /usr/include/string.h /usr/include/secure/_string.h
mysponge2.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h getarg.h
mysponge2.o: /usr/include/stdbool.h ../giflib/include/gif_lib.h
mysponge3.o: /usr/include/stdio.h /usr/include/_types.h
mysponge3.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
mysponge3.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
mysponge3.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
mysponge3.o: /usr/include/stdlib.h /usr/include/Availability.h
mysponge3.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
mysponge3.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mysponge3.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mysponge3.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
mysponge3.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
mysponge3.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mysponge3.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mysponge3.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mysponge3.o: /usr/include/machine/types.h /usr/include/i386/types.h
mysponge3.o: /usr/include/string.h /usr/include/secure/_string.h
mysponge3.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h getarg.h
mysponge3.o: /usr/include/stdbool.h ../giflib/include/gif_lib.h
mysponge3.o: makeColorMap.h
mysponge4.o: /usr/include/stdio.h /usr/include/_types.h
mysponge4.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
mysponge4.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
mysponge4.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
mysponge4.o: /usr/include/stdlib.h /usr/include/Availability.h
mysponge4.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
mysponge4.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
mysponge4.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
mysponge4.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
mysponge4.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
mysponge4.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
mysponge4.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
mysponge4.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
mysponge4.o: /usr/include/machine/types.h /usr/include/i386/types.h
mysponge4.o: /usr/include/string.h /usr/include/secure/_string.h
mysponge4.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h getarg.h
mysponge4.o: /usr/include/stdbool.h ../giflib/include/gif_lib.h
mysponge4.o: makeColorMap.h
qprintf.o: /usr/include/stdio.h /usr/include/_types.h
qprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
qprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
qprintf.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
qprintf.o: /usr/include/stdbool.h /usr/include/stdarg.h /usr/include/stdarg.h
qprintf.o: ../giflib/include/gif_lib.h
