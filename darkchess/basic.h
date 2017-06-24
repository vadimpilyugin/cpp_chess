#include "stdlib.h"
#include <string>

enum GameState {Going,WhiteVictory,BlackVictory,Draw};
enum PieceType {Queen,Rook,Bishop,Knight,Pawn,King,None};
enum ChessColor {White,Black};

struct Tile{
	int x;
	int y;
};

struct Player{
	std::string name;
	ChessColor color;
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
	ChessColor color;
	bool hasMoved;
	Piece(){
		hasMoved=false;
		type=None;
	}
};

struct TiledPiece: Piece{
	Tile place;
};

	
