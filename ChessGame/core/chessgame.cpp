#include "chessgame.h"

const int BOARDSIZE=8;
const int TOTALPIECES=32;

ChessGame::ChessGame(){ // FIXME(8): изменить на ADarkChessGame::ADarkChessGame, перенести в ADCG.cpp
    state=GameState::Going;
    board=new Tile_content* [BOARDSIZE];
    for (int i=0;i<BOARDSIZE;i++)
        board[i]=new Tile_content[BOARDSIZE];
	pieces=new Piece_dark[TOTALPIECES];
    Move nullmove;
    lastmove=nullmove;
}
ChessGame::~ChessGame(){// FIXME(9): изменить на ADarkChessGame::~ADarkChessGame, перенести в ADCG.cpp
    for(int i=0;i<BOARDSIZE;i++)
		delete[] board[i];
	delete[] board;
	delete[] pieces;
}
Move ChessGame::getLastMove(){ // FIXME(8): изменить на ADarkChessGame::getLastMove, перенести в ADCG.cpp
    return lastmove;
}

ChessColor ChessGame::getOrderPlayer(){ // FIXME(8): изменить на ADarkChessGame::getOrderPlayer, перенести в ADCG.cpp
	return turn;
}
Piece ChessGame::getPieceAtTile(Tile tile){ // FIXME(8): изменить на ADarkChessGame::getPieceAtTile, перенести в ADCG.cpp
    if (board[tile.x-1][tile.y-1].type==PieceType::None){
		Piece default_piece;
		return default_piece;
	}
	else
        return pieces[board[tile.x-1][tile.y-1].piecenum];
}

			


		
		
