CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = straights
OBJECTS = card.o deck.o player.o pile.o game.o main.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
