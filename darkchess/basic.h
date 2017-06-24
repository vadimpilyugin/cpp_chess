#include "stdlib.h"
#include <string>

enum GameState {Going,WhiteVictory,BlackVictory,Draw};
enum PieceType {Queen,Rook,Bishop,Knight,Pawn,King,None};
enum Color {White,Black};

struct Tile{
	int x;
	int y;
};

struct Player{
	std::string name;
	Color color;
};

struct Move{
	Tile from;
	Tile to;
	bool isConvertion;
	PieceType convertPiece;
	Move(){
		isConvertion=false;
	}
};

struct Piece{
	PieceType type;
	Color color;
	Tile place;
	bool hasMoved;
	Piece(){
		hasMoved=false;
		type=None;
	}
};



	
