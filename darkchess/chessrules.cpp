#include "chessgame.h"
#include "stdio.h"

#define DIAGNUM 4
#define STRAIGHTNUM 4
#define KNIGHTNUM 8




const int xDiagMoves[] = {1,1,-1,-1};
const int yDiagMoves[] = {1,-1,1,-1};
const int xStraightMoves[] = {1,-1,0,0};
const int yStraightMoves[] = {0,0,1,-1};
const int xKnightMoves[] = {1,1,2,2,-1,-1,-2,-2};
const int yKnightMoves[] = {2,-2,1,-1,2,-2,1,-1};
const int xCastlingPlaces[] = {8,6,5,7,1,4,5,3};//rookfrom,rookto,kingfrom,kingto, first for the short, then for the long


bool isOnBoard(int x,int y){
	return ((x>0)&&(x<SIZE+1)&&(y>0)&&(y<SIZE+1));
}


void ChessGame::initialize(){
	int i,j;
	for (i=0;i<16;i++){
		pieces[i].color=White;
		pieces[i+16].color=Black;
	}
	for (i=0;i<8;i++){
		pieces[i].place.x=i+1;
		pieces[i].place.y=1;
		pieces[i+8].place.x=i+1;
		pieces[i+8].place.y=2;
		pieces[i+8].type=Pawn;
		pieces[i+16].place.x=i+1;
		pieces[i+16].place.y=8;
		pieces[i+24].place.x=i+1;
		pieces[i+24].place.y=7;
		pieces[i+24].type=Pawn;
	}
	pieces[0].type=pieces[7].type=pieces[16].type=pieces[23].type=Rook;
	pieces[1].type=pieces[6].type=pieces[17].type=pieces[22].type=Knight;
	pieces[2].type=pieces[5].type=pieces[18].type=pieces[21].type=Bishop;
	pieces[3].type=pieces[19].type=Queen;
	pieces[4].type=pieces[20].type=King;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			board[i][j].x=i+1;
			board[i][j].y=j+1;
	}
	for (i=0;i<32;i++){
		board[pieces[i].place.x-1][pieces[i].place.y-1].piecenum=i;
		board[pieces[i].place.x-1][pieces[i].place.y-1].type=pieces[i].type;
	}
	turn=White;	
}

bool ChessGame::checkSingle(Tile start,int dx,int dy,Color color){
	if (isOnBoard(start.x+dx,start.y+dy))
		return ((board[start.x+dx-1][start.y+dy-1].type==None)||(pieces[board[start.x+dx-1][start.y+dy-1].piecenum].color!=color));
	else
		return false;
}	

bool ChessGame::checkCastling(int kingnum,bool isShort){
	Color color=pieces[kingnum].color;
	if (pieces[kingnum].hasMoved==true)
		return false;
	int row=0;
	if (color==Black)
		row+=SIZE-1;
	int d=4;
	if (isShort)
		d=0;
	Piece_dark expectedRook=pieces[board[xCastlingPlaces[d]-1][row].piecenum];
	if (((expectedRook.type==Rook) && (expectedRook.color==color) && (expectedRook.hasMoved==false)
	 && (board[xCastlingPlaces[d+1]-1][row].type==None) && (board[xCastlingPlaces[d+3]-1][row].type==None)) &&
	 ((isShort) || (board[xCastlingPlaces[d]][row].type==None)))
		return true;
	else
		return false;
}

void ChessGame::prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,Color color, bool isShort){
	if (color==White){
		rookfrom->y=1;
		rookto->y=1;
		kingfrom->y=1;
		kingto->y=1;
	}
	else{
		rookfrom->y=SIZE;
		rookto->y=SIZE;
		kingfrom->y=SIZE;
		kingto->y=SIZE;
	}
	if (isShort){
		kingfrom->x=xCastlingPlaces[2];
		kingto->x=xCastlingPlaces[3];
		rookto->x=xCastlingPlaces[1];
		rookfrom->x=xCastlingPlaces[0];
	}
	else{
		kingfrom->x=xCastlingPlaces[6];
		kingto->x=xCastlingPlaces[7];
		rookto->x=xCastlingPlaces[5];
		rookfrom->x=xCastlingPlaces[4];
	}
}

std::vector<Tile> ChessGame::checkLine(Tile start,int dx,int dy,Color color){
	std::vector<Tile> result;
	int x=start.x;
	int y=start.y;
	bool stop=false;
	while(!stop){
		x+=dx;
		y+=dy;
		if(!isOnBoard(x,y))
			stop=true;
		else
			if(board[x-1][y-1].type==None)
				result.push_back(board[x-1][y-1]);
			else
				if(pieces[board[x-1][y-1].piecenum].color==color)
					stop=true;
				else{
					result.push_back(board[x-1][y-1]);
					stop=true;
				}
	}
	return result;
}

			
void ChessGame::updatePieceVision(int num){
	std::vector<Tile> result;
	Tile place=pieces[num].place;
	Color color=pieces[num].color;
	int i;
	std::vector<Tile>line;
	switch(pieces[num].type){
		case Bishop:
			for(i=0;i<DIAGNUM;i++){
				line=checkLine(place,xDiagMoves[i],yDiagMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
		case Rook:
			for(i=0;i<STRAIGHTNUM;i++){
				line=checkLine(place,xStraightMoves[i],yStraightMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
		case Queen:
			for(i=0;i<STRAIGHTNUM;i++){
				line=checkLine(place,xStraightMoves[i],yStraightMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			for(i=0;i<DIAGNUM;i++){
				line=checkLine(place,xDiagMoves[i],yDiagMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
		case Knight:
			for(i=0;i<KNIGHTNUM;i++)
				if (checkSingle(place,xKnightMoves[i],yKnightMoves[i],color))
					result.push_back(board[place.x+xKnightMoves[i]-1][place.y+yKnightMoves[i]-1]);
			break;
		case Pawn:
			int dy;
			if (color==White)
				dy=1;
			else
				dy=-1;
			if (isOnBoard(place.x,place.y+dy)){
				result.push_back(board[place.x-1][place.y+dy-1]);
				if (board[place.x-1][place.y+dy-1].type==None){
					if ((!pieces[num].hasMoved)&&(isOnBoard(place.x,place.y+2*dy)))
						result.push_back(board[place.x-1][place.y+2*dy-1]);
					else;
				}
				else;
			}
			else;
			for(int dx=-1;dx<2;dx+=2)
				if (isOnBoard(place.x+dx,place.y+dy))
					result.push_back(board[place.x+dx-1][place.y+dy-1]);
				else;
			break;
		case King:
			for(i=0;i<DIAGNUM;i++)
				if (checkSingle(place,xDiagMoves[i],yDiagMoves[i],color))
					result.push_back(board[place.x+xDiagMoves[i]-1][place.y+yDiagMoves[i]-1]);
			for(i=0;i<STRAIGHTNUM;i++)
				if (checkSingle(place,xStraightMoves[i],yStraightMoves[i],color))
					result.push_back(board[place.x+xStraightMoves[i]-1][place.y+yStraightMoves[i]-1]);
			int row;
			if (checkCastling(num,true)){
				row=0;
				if (color==Black)
					row=SIZE-1;
				result.push_back(board[xCastlingPlaces[3]-1][row]);
			}
			if (checkCastling(num,false)){
				row=0;
				if (color==Black)
					row=SIZE-1;
				result.push_back(board[xCastlingPlaces[7]-1][row]);
			}
			break;
	}
	pieces[num].vision=result;
}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	
	
