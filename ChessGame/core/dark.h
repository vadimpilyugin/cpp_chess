#pragma once

#include "tile.h"
#include "piece.h"
#include <vector>

#define SIZE 8
#define TOTALPIECES 32


struct Tile_content: Tile{
	int piecenum;
	PieceType type;
	bool seenByWhite;
	bool seenByBlack;
	Tile_content(){
        type=PieceType::None;
		seenByBlack=false;
		seenByWhite=false;
	}
};

struct Piece_dark: TiledPiece{
	std::vector<Tile> vision;
};
	


