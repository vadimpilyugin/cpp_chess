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
    protected:
        GameState state;  // FIXME(1): это явно лишнее, так как в AChessGame уже есть gameState
	public:
		ChessGame();
		~ChessGame();
        GameState getState(); // FIXME(2): то же самое, в AChessGame уже есть getState
		ChessColor getOrderPlayer();
        Piece getPieceAtTile(Tile tile);
        Move getLastMove();
        virtual void doCommand(Command* command) = 0; // FIXME(3): в AChessGame он уже объявлен
        virtual std::vector<Tile> getMoveTiles(TiledPiece piece)=0; // FIXME(4)
        virtual std::vector<Tile> getAttackTiles(TiledPiece piece)=0; // FIXME(5)
        virtual std::vector<Tile> getHiddenTiles(Player player)=0; // FIXME(6)
        virtual std::vector<TiledPiece> getConvertionPieces(Player player)=0; // FIXME(7)

};


