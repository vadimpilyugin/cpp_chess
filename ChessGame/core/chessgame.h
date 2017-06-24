#pragma once

#include "dark.h"
#include "stdio.h"
#include "chesscolor.h"
#include "adarkchessgame.h"
#include "player.h"

class ChessGame:public ADarkChessGame{
	private:
		Tile_content** board;
		Piece_dark* pieces;
		GameState state;
        ChessColor turn;
	public:
		ChessGame();
		~ChessGame();
		GameState getState();
        ChessColor getOrderPlayer();
		Piece getPieceAtTile(Tile tile);
		bool doMove(Move move);
        std::vector<Tile> getMoveTiles(TiledPiece piece);
        std::vector<Tile> getAttackTiles(TiledPiece piece);
		std::vector<Tile> getHiddenTiles(Player player);
        std::vector<TiledPiece> getConvertionPieces(Player player);
//METHODS BELOW WILL BE PRIVATE CAUSE NOBODY ELSE WILL NEED THEM
   		void forcedMove(Tile from, Tile to);
   		void doCastling(Piece king,bool isShort);
        void checkVictory(ChessColor color);
		void updateVision();
        void rawOutput(ChessColor color);
		void initialize();
        bool checkSingle(Tile start,int dx,int dy,ChessColor color);
        std::vector<Tile> checkLine(Tile start,int dx,int dy,ChessColor color);
		bool checkCastling(int kingnum,bool isShort);
        void prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,ChessColor color, bool isShort);
		void updatePieceVision(int num);
};
//READ ABOUT VIRTUAL FUNCTIONS


