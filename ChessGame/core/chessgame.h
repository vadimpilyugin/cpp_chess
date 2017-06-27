#pragma once

#include "dark.h"
#include "stdio.h"
#include "adarkchessgame.h"
#include "player.h"

class ChessGame:public ADarkChessGame{
    protected:
		Tile_content** board;
		Piece_dark* pieces;
		ChessColor turn;
        Move lastmove;
	public:
		ChessGame();
        ~ChessGame();
		ChessColor getOrderPlayer();
        Piece getPieceAtTile(Tile tile);
        Move getLastMove();
};


