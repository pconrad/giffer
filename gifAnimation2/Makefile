CPPFLAGS= -I../giflib/include -L../giflib/lib -lgif

all:	main3 main4
	LD_LIBRARY_PATH=../giflib/lib ./main3
	LD_LIBRARY_PATH=../giflib/lib ./main4
	cp 0123.gif ~/public_html
	cp main4.gif ~/public_html


main4: main4.o AnimatedGifSaver2.o
	g++ ${CPPFLAGS} main4.o AnimatedGifSaver2.o -o main4


main3: main3.o AnimatedGifSaver2.o
	g++ ${CPPFLAGS} main3.o AnimatedGifSaver2.o -o main3



clean:
	/bin/rm -f *.o main3 main4

