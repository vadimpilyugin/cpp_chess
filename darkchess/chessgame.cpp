#include "chessgame.h"

bool isInVector(std::vector<Tile> range,Tile tile){
	bool result=false;
	for (int i=0;i<range.size();i++)
		if ((tile.x==range[i].x)&&(tile.y==range[i].y)){
			result=true;
			break;
		}
	return result;
}

ChessGame::ChessGame(){
	state=Going;
	board=new Tile_content* [SIZE];
	for (int i=0;i<SIZE;i++)
		board[i]=new Tile_content[SIZE];
	pieces=new Piece_dark[TOTALPIECES];
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
void ChessGame::checkVictory(ChessColor color){
	int i;
	bool victory=true;
	for(i=0;i<TOTALPIECES;i++)
		if ((pieces[i].color!=color)&&(pieces[i].type==King))
			victory=false;
	if (victory)
		if (color==White)
			state=WhiteVictory;
		else
			state=BlackVictory;
	else;
}
ChessColor ChessGame::getOrderPlayer(){
	return turn;
}
Piece ChessGame::getPieceAtTile(Tile tile){
	if (board[tile.x-1][tile.y-1].type==None){
		Piece default_piece;
		return default_piece;
	}
	else
		return pieces[board[tile.x-1][tile.y-1].piecenum];
}
std::vector<Tile> ChessGame::getMoveTiles(TiledPiece piece){
	std::vector<Tile> result;
	int i;
	int x=piece.place.x;
	int y=piece.place.y;
	for (i=0;i<pieces[board[x-1][y-1].piecenum].vision.size();i++)
		if (board[pieces[board[x-1][y-1].piecenum].vision[i].x-1]
			[pieces[board[x-1][y-1].piecenum].vision[i].x-1].type==None)
		result.push_back(pieces[board[x-1][y-1].piecenum].place);
	return result;
}
std::vector<Tile> ChessGame::getAttackTiles(TiledPiece piece){
	std::vector<Tile> result;
	int i;
	int x=piece.place.x;
	int y=piece.place.y;
	for (i=0;i<pieces[board[x-1][y-1].piecenum].vision.size();i++)
		if (board[pieces[board[x-1][y-1].piecenum].vision[i].x-1]
			[pieces[board[x-1][y-1].piecenum].vision[i].x-1].type!=None)
		result.push_back(pieces[board[x-1][y-1].piecenum].place);
	return result;
}
void ChessGame::updateVision(){
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			board[i][j].seenByWhite=false;
			board[i][j].seenByBlack=false;
		}	 
	int x,y;
	for(int dc=0;dc<TOTALPIECES/2+1;dc+=TOTALPIECES/2)
		for(i=0;i<TOTALPIECES/2;i++){
			updatePieceVision(i+dc);
			int x=pieces[i+dc].place.x;
			int y=pieces[i+dc].place.y;
			if (pieces[i+dc].type!=None){
				if (dc!=0)
					board[x-1][y-1].seenByBlack=true;
				else
					board[x-1][y-1].seenByWhite=true;
			}
			for (j=0;j<pieces[i+dc].vision.size();j++)
				if (dc)
					board[pieces[i+dc].vision[j].x-1][pieces[i+dc].vision[j].y-1].seenByBlack=true;
				else 
					board[pieces[i+dc].vision[j].x-1][pieces[i+dc].vision[j].y-1].seenByWhite=true;
		}
}

std::vector<Tile> ChessGame::getHiddenTiles(Player player){
	ChessColor color=player.color;
	std::vector<Tile> result;
	for (int i=0;i<SIZE;i++)
		for (int j=0;j<SIZE;j++)
			if (color==White)
				if (!board[i][j].seenByWhite)
					result.push_back(board[i][j]);
				else;
			else
				if (!board[i][j].seenByBlack)
					result.push_back(board[i][j]);
				else;
	return result;
}

std::vector<Piece> ChessGame::getConvertionPieces(Player player){
	ChessColor color=player.color;
	std::vector<Piece> result;
	int dy;
	if (color==White)
		dy=SIZE-1;
	else
		dy=0;
	for (int i=0;i<SIZE;i++)
		if ((board[i][0+dy].type==Pawn)&&(pieces[board[i][0+dy].piecenum].color==color))
			result.push_back(pieces[board[i][0+dy].piecenum]);
	return result;
}


void ChessGame::forcedMove(Tile from, Tile to){
	if (board[to.x-1][to.y-1].type!=None)
		pieces[board[to.x-1][to.y-1].piecenum].type=None;
	board[to.x-1][to.y-1].piecenum=board[from.x-1][from.y-1].piecenum;
	board[to.x-1][to.y-1].type=board[from.x-1][from.y-1].type;
	pieces[board[from.x-1][from.y-1].piecenum].place.x=to.x;
	pieces[board[from.x-1][from.y-1].piecenum].place.y=to.y;
	pieces[board[from.x-1][from.y-1].piecenum].hasMoved=true;
	board[from.x-1][from.y-1].type=None;
}


void ChessGame::doCastling(TiledPiece king,bool isShort){
	Tile rookfrom, rookto,kingfrom,kingto;
	prepareCastling(&rookfrom,&rookto,&kingfrom,&kingto,king.color,isShort);
	forcedMove(rookfrom,rookto);
	forcedMove(kingfrom,kingto);
}
		

bool ChessGame::doMove(Move move){
	if (board[move.from.x-1][move.from.y-1].type==None)
		return false;
	Piece_dark moving=pieces[board[move.from.x-1][move.from.y-1].piecenum];
	if ((move.isConvertion) && (moving.type==Pawn) && 
	((moving.color==Black) && (move.from.y==1) ||
	(moving.color==White) && (move.from.y==8)))
		pieces[board[move.from.x-1][move.from.y-1].piecenum].type=move.convertPiece;
	if (moving.type==Pawn){
		if (((move.from.x!=move.to.x)&&(board[move.to.x-1][move.to.y-1].type==None))||
		((move.from.x==move.to.x)&&(board[move.to.x-1][move.to.y-1].type!=None)))
			return false;
	}
	if ((turn==moving.color)&&(isInVector(moving.vision,move.to))){
		if ((moving.type==King) && ((move.to.x-move.from.x)==2)){
			doCastling(moving,true);
		}
		else if ((moving.type==King) && ((move.to.x-move.from.x)==-2)){
			doCastling(moving,false);
		}
		else
			forcedMove(move.from,move.to);
	}
	else
		return false;
	if (turn==White){
		checkVictory(White);
		turn=Black;
	}
	else{
		checkVictory(Black);
		turn=White;
	}
	return true;
}
			
		
void ChessGame::rawOutput(ChessColor color){
	char icon;
	for (int j=SIZE-1;j>-1;j--){
		for(int i=0;i<SIZE;i++){
			switch(board[i][j].type){
				case None:
					icon='*';
					break;
				case King:
					icon='K';
					break;
				case Pawn:
					icon='1';
					break;
				case Knight:
					icon='?';
					break;
				case Bishop:
					icon='A';
					break;
				case Rook:
					icon='H';
					break;
				case Queen:
					icon='Q';
					break;
			}
			if ((color==White) && (board[i][j].seenByWhite==false))
				icon='#';
			if ((color==Black) && (board[i][j].seenByBlack==false))
				icon='#';
			printf("%c",icon);
		}
		printf("\n");
	}
}
		
		
