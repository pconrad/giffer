from Tkinter import *
from tkFileDialog import askopenfilename,asksaveasfilename
from subprocess import call
import ntpath
import os
from os.path import expanduser

dir = "~"
inoFile = ""
master = Tk()

def askForFilename():
    global dir
    global inoFile
    filename.delete(1.0, END)
    file = askopenfilename(initialdir=dir)
    temp, inoFile = ntpath.split(file)
    filename.insert(END, file)
    dir = os.path.dirname(os.path.realpath(file))

def askSaveWhere():
    global dir
    global inoFile
    inoFile = inoFile.replace(".ino",".gif")
    saveLocation.delete(1.0, END)
    file = asksaveasfilename(initialdir=dir, defaultextension=".gif",initialfile=inoFile)
    saveLocation.insert(END, file)
    dir = os.path.dirname(os.path.realpath(file))

def gifIt():
    file = filename.get(1.0, END)
    file = file.replace("\n","")
    location = saveLocation.get(1.0, END)
    location = location.replace("\n","")
    oldFile=open(file)
    contents = oldFile.read()
    oldFile.close()
    home = expanduser("~") + "\\temp.c"
    newFile=open(home,"w")
    newFile.write('#include "arduino.h"\n')
    newFile.write(contents)
    newFile.close()
    call(["gcc", "-c", "-g", "-I", "../src", "-Wall", "-I", ".", home, "-o", "../src/sketch1.o"]) #gcc -c -g -I ../src -Wall -I . ../sketchesIn/sketch1.c -o ../src/sketch1.o
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/main.o", "../src/main.c"]) #gcc -g -Wall   -c -o main.o main.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/arduino.o", "../src/arduino.c"]) #gcc -g -Wall   -c -o arduino.o arduino.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/qprintf.o", "../src/qprintf.c"]) #gcc -g -Wall   -c -o qprintf.o qprintf.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/gifalloc.o", "../src/gifalloc.c"]) #gcc -g -Wall   -c -o gifalloc.o gifalloc.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/egif_lib.o", "../src/egif_lib.c"]) #gcc -g -Wall   -c -o egif_lib.o egif_lib.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/dgif_lib.o", "../src/dgif_lib.c"]) #gcc -g -Wall   -c -o dgif_lib.o dgif_lib.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/gif_hash.o", "../src/gif_hash.c"]) #gcc -g -Wall   -c -o gif_hash.o gif_hash.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/gif_font.o", "../src/gif_font.c"]) #gcc -g -Wall   -c -o gif_font.o gif_font.c
    call(["gcc", "-g", "-Wall", "-c", "-o", "../src/gif_err.o", "../src/gif_err.c"]) #gcc -g -Wall   -c -o gif_err.o gif_err.c
    call(["gcc", "-g", "../src/egif_lib.o", "../src/main.o", "../src/gif_font.o", "../src/dgif_lib.o", "../src/gif_err.o", "../src/gifalloc.o", "../src/qprintf.o", "../src/gif_hash.o", "../src/arduino.o", "../src/sketch1.o", "-o", "../src/sketch1.exe"]) #gcc -g src/egif_lib.o src/main.o src/gif_font.o src/dgif_lib.o src/gif_err.o src/gifalloc.o src/qprintf.o src/gif_hash.o src/arduino.o src/sketch1.o -o src/sketch1.exe
    call(["rm", "../src/*.o"]) #rm ../src/sketch1.o
    call(["../src/sketch1.exe", "../baseGifs/leds3.gif", location]) # ./src/sketch1.exe baseGifs/leds3.gif gifsOut/sketch1.gif
    call(["rm", "../src/sketch1.exe"])
    call(["rm", home])

locate = Button(master, text="Step 1: Locate .ino", command=askForFilename)
filename = Text(master, height = 1)
save = Button(master, text="Step 2: Where to save .gif", command=askSaveWhere)
saveLocation = Text(master, height = 1)
gif = Button(master, text="Step 3: gif it", command=gifIt)

locate.pack()
filename.pack()
save.pack()
saveLocation.pack()
gif.pack()

mainloop()
