CFLAGS= -I../giflib/include -L../giflib/lib -lgif

all:	mysponge1 mysponge2
	LD_LIBRARY_PATH=../giflib/lib ./mysponge1 < ../gifs/leds.gif > ~/public_html/sponge1.gif
	chmod a+rx ~/public_html/sponge1.gif
	LD_LIBRARY_PATH=../giflib/lib ./mysponge2 < ../gifs/leds.gif > ~/public_html/sponge2.gif
	chmod a+rx ~/public_html/sponge2.gif

mysponge1: mysponge1.o getarg.o qprintf.o
	gcc ${CFLAGS} mysponge1.o getarg.o qprintf.o -o mysponge1

mysponge2: mysponge2.o getarg.o qprintf.o
	gcc ${CFLAGS} mysponge2.o getarg.o qprintf.o -o mysponge2

clean:
	/bin/rm -f *.o mysponge1 mysponge2

