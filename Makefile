CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = textviewer.o graphicviewer.o whitepawn.o blackpawn.o pawn.o knight.o bishop.o rook.o queen.o king.o empty.o piece.o board.o chess.o test.o viewer.o window.o player.o human.o computer.o easy.o medium.o hard.o ultra.o controller.o
PROGRAM = test

${PROGRAM}: ${OBJECTS}
	${CXX} -o ${PROGRAM} ${OBJECTS} -lX11



.PHONY: clean
clean:
	rm ${PROGRAM} ${OBJECTS}

