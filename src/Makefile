CFLAGS=  -g -Wall
LDFLAGS= -g

# Put a GIF into gifsOut for every .c file in sketches.

#SKETCHES=../sketchesIn
#GIFSOUT=../gifsOut
#BASEGIFS=../baseGifs

#GIFS= $(addprefix ${GIFSOUT}/,$(addsuffix .gif,$(basename $(notdir $(wildcard ${SKETCHES}/*.c)))))



# The object files that we wrote to support creating gifs from Arduino sketches
OUR_OBJS=main.o arduino.o 

# The following OBJ files are taken directly from giflib-5.0.4
# It would be better to link directly against the library if we could make
#   that work on Cygwin, but we were not successful so far.
GIFLIB_OBJS=qprintf.o gifalloc.o egif_lib.o dgif_lib.o gif_hash.o gif_font.o gif_err.o

all:  ${OUR_OBJS} ${GIFLIB_OBJS}

depend:
	- makedepend *.c

clean:
	/bin/rm -f *.o *.exe ${GIFS}


