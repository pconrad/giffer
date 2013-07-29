

all:	main3
	./main3
	cp 0123.gif ~/public_html


main3: main3.o AnimatedGifSaver2.o
	g++ -lgif main3.o AnimatedGifSaver2.o -o main3




clean:
	/bin/rm -f *.o main3

