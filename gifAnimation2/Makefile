CPPFLAGS= -I../giflib/include -L../giflib/lib -lgif

all:	main3
	LD_LIBRARY_PATH=../giflib/lib ./main3
	cp 0123.gif ~/public_html


main3: main3.o AnimatedGifSaver2.o
	g++ ${CPPFLAGS} main3.o AnimatedGifSaver2.o -o main3




clean:
	/bin/rm -f *.o main3

