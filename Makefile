CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: a.out

a.out: main.o rsdl.o Camera.o Mario.o Clay.o Hole.o Brick.o Block.o Question.o Pipe.o Flag.o Goomba.o Koopa.o Coin.o Mushroom.o
	$(CC) main.o rsdl.o Camera.o Mario.o Clay.o Hole.o Brick.o Block.o Question.o Pipe.o Flag.o Goomba.o Koopa.o Coin.o Mushroom.o $(CCFLAGS) -o a.out

main.o: main.cpp src/rsdl.hpp
	$(CC) -c main.cpp $(CCFLAGS) -o main.o

rsdl.o: src/rsdl.cpp src/rsdl.hpp
	$(CC) -c src/rsdl.cpp $(CCFLAGS) -o rsdl.o

Camera.o: Camera.cpp Camera.hpp
	$(CC) -c Camera.cpp $(CCFLAGS) -o Camera.o

Mario.o: Mario.cpp Mario.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Mario.cpp $(CCFLAGS) -o Mario.o

Clay.o: Clay.cpp Clay.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Clay.cpp $(CCFLAGS) -o Clay.o

Hole.o: Hole.cpp Hole.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Hole.cpp $(CCFLAGS) -o Hole.o

Brick.o: Brick.cpp Brick.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Brick.cpp $(CCFLAGS) -o Brick.o

Block.o: Block.cpp Block.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Block.cpp $(CCFLAGS) -o Block.o

Question.o: Question.cpp Question.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Question.cpp $(CCFLAGS) -o Question.o

Pipe.o: Pipe.cpp Pipe.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Pipe.cpp $(CCFLAGS) -o Pipe.o

Flag.o: Flag.cpp Flag.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Flag.cpp $(CCFLAGS) -o Flag.o

Goomba.o: Goomba.cpp Goomba.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Goomba.cpp $(CCFLAGS) -o Goomba.o

Koopa.o: Koopa.cpp Koopa.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Koopa.cpp $(CCFLAGS) -o Koopa.o

Coin.o: Coin.cpp Coin.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Coin.cpp $(CCFLAGS) -o Coin.o

Mushroom.o: Mushroom.cpp Mushroom.hpp src/rsdl.hpp Camera.hpp
	$(CC) -c Mushroom.cpp $(CCFLAGS) -o Mushroom.o

.PHONY: clean
clean:
	rm -r *.o