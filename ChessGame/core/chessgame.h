#pragma once

#include "dark.h"
#include "stdio.h"
#include "adarkchessgame.h"
#include "player.h"

class ChessGame:public ADarkChessGame{
	private:
		Tile_content** board;
		Piece_dark* pieces;
		ChessColor turn;
    protected:
        GameState state;
	public:
		ChessGame();
		~ChessGame();
		GameState getState();
		ChessColor getOrderPlayer();
		Piece getPieceAtTile(Tile tile);
};


