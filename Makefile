CXX := g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: thegame

%.o: %.cpp 
	$(CXX) -c $< -o $@

%.o: %.hpp 
	$(CXX) -c $< -o $@

thegame: main.o game.o graph_handler.o
	@echo "** Building the game" 
	$(CXX) -o thegame main.o game.o graph_handler.o $(LIBS)

clean:
	rm -f thegame *.o

install: 
	@echo '** Installing...' 
	cp thegame /usr/bin/
