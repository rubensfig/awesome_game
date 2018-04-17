CC=g++
CFLAGS= -std=c++11
TARGET=fmq-game

all: $(TARGET)

fmq-game: 
	$(CC) main.cpp -o fmq-game $(CFLAGS)

clean:
	rm fmq-game 

format:
	find -regex '.*\.\(h\|cc\)$$' | xargs clang-format -style=file
