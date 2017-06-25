#include "chessgame.h"



ChessGame::ChessGame(){
    state=GameState::Going;
	board=new Tile_content* [SIZE];
	for (int i=0;i<SIZE;i++)
		board[i]=new Tile_content[SIZE];
	pieces=new Piece_dark[TOTALPIECES];
    Move nullmove;
    lastmove=nullmove;
}
ChessGame::~ChessGame(){
	for(int i=0;i<SIZE;i++)
		delete[] board[i];
	delete[] board;
	delete[] pieces;
}
GameState ChessGame::getState(){
	return state;
}

ChessColor ChessGame::getOrderPlayer(){
	return turn;
}
Piece ChessGame::getPieceAtTile(Tile tile){
    if (board[tile.x-1][tile.y-1].type==PieceType::None){
		Piece default_piece;
		return default_piece;
	}
	else
		return pieces[board[tile.x-1][tile.y-1].piecenum];
}

			
virtual void ChessGame::doCommand(Command* command)=0;
virtual std::vector<Tile> ChessGame::getMoveTiles(TiledPiece piece)=0;
virtual std::vector<Tile> ChessGame::getAttackTiles(TiledPiece piece)=0;
virtual std::vector<Tile> ChessGame::getHiddenTiles(Player player)=0;
virtual std::vector<TiledPiece> ChessGame::getConvertionPieces(Player player)=0;


		
		
