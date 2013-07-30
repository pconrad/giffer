CPPFLAGS= -I../giflib/include -L../giflib/lib -lgif
CFLAGS= -I../giflib/include -L../giflib/lib -lgif

all:	main3 main4 main5 mysponge1 mysponge2
	LD_LIBRARY_PATH=../giflib/lib ./main3
	LD_LIBRARY_PATH=../giflib/lib ./main4
	LD_LIBRARY_PATH=../giflib/lib ./main5
	- cp 0123.gif ~/public_html
	- cp main4.gif ~/public_html
	- cp main5.gif ~/public_html
	LD_LIBRARY_PATH=../giflib/lib ./mysponge1 < ../gifs/leds.gif > ~/public_html/sponge1.gif
	chmod a+rx ~/public_html/sponge1.gif
	LD_LIBRARY_PATH=../giflib/lib ./mysponge2 < ../gifs/leds.gif > ~/public_html/sponge2.gif
	chmod a+rx ~/public_html/sponge2.gif

main4: main4.o AnimatedGifSaver.o
	g++ ${CPPFLAGS} main4.o AnimatedGifSaver.o -o main4

main5: main5.o GifAnimator.o
	g++ ${CPPFLAGS} main5.o GifAnimator.o -o main5

main3: main3.o AnimatedGifSaver.o
	g++ ${CPPFLAGS} main3.o AnimatedGifSaver.o -o main3

mysponge1: mysponge1.o getarg.o qprintf.o
	gcc ${CFLAGS} mysponge1.o getarg.o qprintf.o -o mysponge1

mysponge2: mysponge2.o getarg.o qprintf.o
	gcc ${CFLAGS} mysponge2.o getarg.o qprintf.o -o mysponge2


clean:
	/bin/rm -f *.o main3 main4 main5 mysponge1 mysponge2

