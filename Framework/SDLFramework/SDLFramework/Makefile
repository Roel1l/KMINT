SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
CXXFLAGS=-ggdb -Wall -Wextra -std=c++11
CXX=g++

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS := $(SDL_CFLAGS)
LDFLAGS := $(SDL_LDFLAGS) -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) -iquote./ $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $?

all: main

clean:
	rm -f *.o main
