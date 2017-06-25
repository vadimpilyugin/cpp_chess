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
        GameState state;
	public:
		ChessGame();
		~ChessGame();
		GameState getState();
		ChessColor getOrderPlayer();
        Piece getPieceAtTile(Tile tile);
        virtual void doCommand(Command* command) = 0;
        std::vector<Tile> getMoveTiles(TiledPiece piece)=0;
        std::vector<Tile> getAttackTiles(TiledPiece piece)=0;
        std::vector<Tile> getHiddenTiles(Player player)=0;
        std::vector<TiledPiece> getConvertionPieces(Player player)=0;

};


