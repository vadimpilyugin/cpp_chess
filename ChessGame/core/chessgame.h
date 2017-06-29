#pragma once

#include "dark.h"
#include "stdio.h"
#include "adarkchessgame.h"
#include "player.h"

class ChessGame:public ADarkChessGame{
    // FIXME(2): перенести в ADarkChessGame
    protected:
		Tile_content** board;
		Piece_dark* pieces;
		ChessColor turn;
        Move lastmove;
	public:
        ChessGame(); // FIXME(3): сделать конструктором ADarkChessGame
        ~ChessGame();// FIXME(4): сделать деструктором ADarkChessGame
        virtual ChessColor getOrderPlayer(); // FIXME(5): перенести в ADarkChessGame
        virtual Piece getPieceAtTile(Tile tile);// FIXME(6): перенести в ADarkChessGame
        virtual Move getLastMove();// FIXME(7): перенести в ADarkChessGame
};
