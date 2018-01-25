CC=g++
CFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
TARGET=fmq-game

all: $(TARGET)

fmq-game: 
	$(CC) main.cpp -o fmq-game $(CFLAGS)

clean:
	rm fmq-game 
