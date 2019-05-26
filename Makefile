# links suggested in gl tutorial:
#  -lX11 -lpthread -lXrandr -lXi -ldl

SRC = src/stbImage.cpp \
src/context.cpp \
src/textureLoader.cpp \
src/rectDrawing.cpp \
src/main.cpp

CFLAGS = -std=c++17

LFLAGS = -lGLEW -lGL -lglfw

EXECUTABLE = kuvasiirtyma

all:
	g++ $(SRC) $(CFLAGS) $(LFLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
