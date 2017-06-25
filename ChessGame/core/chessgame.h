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
        Move lastmove;
    protected:
        GameState state;
	public:
		ChessGame();
		~ChessGame();
		GameState getState();
		ChessColor getOrderPlayer();
		Piece getPieceAtTile(Tile tile);
        virtual std::vector<Tile> ChessGame::getMoveTiles(TiledPiece piece);
        virtual std::vector<Tile> ChessGame::getAttackTiles(TiledPiece piece);
        virtual std::vector<Tile> ChessGame::getHiddenTiles(Player player);
        virtual std::vector<TiledPiece> ChessGame::getConvertionPieces(Player player);
        virtual void ChessGame::doCommand(Command* command);
};


