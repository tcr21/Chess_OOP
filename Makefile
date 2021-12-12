chess: ChessMain.o ChessBoard.o Piece.o Pawn.o King.o Knight.o Queen.o Bishop.o Rook.o
	g++ -Wall -g ChessMain.o ChessBoard.o Piece.o Pawn.o King.o Knight.o Queen.o Bishop.o Rook.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp -o ChessMain.o

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp -o ChessBoard.o

Piece.o: Piece.cpp Piece.h
	g++ -Wall -g -c Piece.cpp -o Piece.o

Pawn.o: Pawn.cpp Pawn.h
	g++ -Wall -g -c Pawn.cpp -o Pawn.o

King.o: King.cpp King.h
	g++ -Wall -g -c King.cpp -o King.o

Knight.o: Knight.cpp Knight.h Piece.h
	g++ -Wall -g -c Knight.cpp -o Knight.o

Queen.o: Queen.cpp Queen.h
	g++ -Wall -g -c Queen.cpp -o Queen.o

Bishop.o: Bishop.cpp Bishop.h
	g++ -Wall -g -c Bishop.cpp -o Bishop.o

Rook.o: Rook.cpp Rook.h
	g++ -Wall -g -c Rook.cpp -o Rook.o

clean:
	rm -f *.o chess

