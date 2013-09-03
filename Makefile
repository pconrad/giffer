CFLAGS=  -g -I./src -Wall
LDFLAGS= -g

# Put a GIF into gifsOut for every .c file in sketches.

SKETCHES=sketchesIn
GIFSOUT=gifsOut
BASEGIFS=baseGifs

GIFS_TO_MAKE= $(addprefix ${GIFSOUT}/,$(addsuffix .gif,$(basename $(notdir $(wildcard ${SKETCHES}/*.c)))))

ALL_OBJS=$(addprefix src/,$(addsuffix .o,$(basename $(notdir $(wildcard src/*.c)))))

all:	compileSrc ${GIFS_TO_MAKE}

compileSrc:	
	${MAKE} -C src

${GIFSOUT}/sketch%.gif : src/sketch%.exe
	./$< ${BASEGIFS}/leds3.gif $@

src/sketch%.o: ${SKETCHES}/sketch%.c
	gcc -c ${CFLAGS} -I. $< -o $@

src/sketch%.exe: src/sketch%.o ${ALL_OBJS}
	gcc ${LDFLAGS} ${ALL_OBJS} $< -o $@ 

clean:
	/bin/rm -f ${GIFS_TO_MAKE}
	${MAKE} -C src clean


