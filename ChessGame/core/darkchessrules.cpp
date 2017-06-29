#include "darkchessgame.h"
#include "darkchessrules.h"
#include "stdio.h"
//количество возможных направлений движения по диагонали, прямо, и по-конски
const int DIAGNUM=4;
const int STRAIGHTNUM=4;
const int KNIGHTNUM=8;



//абсциссы и ординаты возможных направлений ходов
const int xDiagMoves[] = {1,1,-1,-1};
const int yDiagMoves[] = {1,-1,1,-1};
const int xStraightMoves[] = {1,-1,0,0};
const int yStraightMoves[] = {0,0,1,-1};
const int xKnightMoves[] = {1,1,2,2,-1,-1,-2,-2};
const int yKnightMoves[] = {2,-2,1,-1,2,-2,1,-1};
//абсциссы ладьи и короля при разных типах рокировки
const int xCastlingPlaces[] = {8,6,5,7,1,4,5,3};//rookfrom,rookto,kingfrom,kingto, first for the short, then for the long


bool isOnBoard(int x,int y){
	return ((x>0)&&(x<SIZE+1)&&(y>0)&&(y<SIZE+1));
}

//расставить фигуры и приготовиться к игре
void DarkChessGame::initialize(){
	int i,j;
    //присвоим нужный цвет
	for (i=0;i<16;i++){
        pieces[i].color=ChessColor::White;
        pieces[i+16].color=ChessColor::Black;
	}
    //расставим фигуры по местам, сделаем некоторые из них пешками -- те, что стоят на второй и седьмой горизонталях
	for (i=0;i<8;i++){
		pieces[i].place.x=i+1;
		pieces[i].place.y=1;
		pieces[i+8].place.x=i+1;
		pieces[i+8].place.y=2;
        pieces[i+8].type=PieceType::Pawn;
		pieces[i+16].place.x=i+1;
		pieces[i+16].place.y=8;
		pieces[i+24].place.x=i+1;
		pieces[i+24].place.y=7;
        pieces[i+24].type=PieceType::Pawn;
	}
    //Разберемся с остальными фигурами в массиве pieces
    pieces[0].type=pieces[7].type=pieces[16].type=pieces[23].type=PieceType::Rook;
    pieces[1].type=pieces[6].type=pieces[17].type=pieces[22].type=PieceType::Knight;
    pieces[2].type=pieces[5].type=pieces[18].type=pieces[21].type=PieceType::Bishop;
    pieces[3].type=pieces[19].type=PieceType::Queen;
    pieces[4].type=pieces[20].type=PieceType::King;
    //присвоим клеткам их координаты, они на единицу отличаются от номера в массиве
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			board[i][j].x=i+1;
			board[i][j].y=j+1;
	}
    //теперь перенесем на доску информацию из массива pieces
	for (i=0;i<32;i++){
		board[pieces[i].place.x-1][pieces[i].place.y-1].piecenum=i;
		board[pieces[i].place.x-1][pieces[i].place.y-1].type=pieces[i].type;
	}
    turn=ChessColor::White;
    updateVision();
}
// проверим, можно ли сходить из поля старт на поле, полученное из него сдвигом на (dx,dy) фигурой цвета color
bool DarkChessGame::checkSingle(Tile start,int dx,int dy,ChessColor color){
    //проверим, на доске ли поле, на которое мы собираемся сходить
	if (isOnBoard(start.x+dx,start.y+dy))
        //на поле можно сходить, если оно пустое или если там стоит вражеская фигура
        return ((board[start.x+dx-1][start.y+dy-1].type==PieceType::None)||(pieces[board[start.x+dx-1][start.y+dy-1].piecenum].color!=color));
	else
		return false;
}	
//проверим, осуществима ли рокировка, зная номер короля в массиве pieces и то, хотим ли мы короткую или длинную рокировку
bool DarkChessGame::checkCastling(int kingnum,bool isShort){
	ChessColor color=pieces[kingnum].color;
    //нельзя делать рокировку, если король ходил до этого
	if (pieces[kingnum].hasMoved==true)
		return false;
    // row и d выбираются исходя из цвета короля и длины рокировки и потом помогают нам найти ладью и места для рокировки
	int row=0;
    if (color==ChessColor::Black)
		row+=SIZE-1;
	int d=4;
	if (isShort)
		d=0;
    // expectedRook -- это та фигура, которая стоит в углу, и с которой мы хотим рокироваться
	Piece_dark expectedRook=pieces[board[xCastlingPlaces[d]-1][row].piecenum];
    // проверим, что это действительно Ладья, нужного цвета, не ходила, и между ней и королём все клетки пустые
    if (((expectedRook.type==PieceType::Rook) && (expectedRook.color==color) && (expectedRook.hasMoved==false)
     && (board[xCastlingPlaces[d+1]-1][row].type==PieceType::None) && (board[xCastlingPlaces[d+3]-1][row].type==PieceType::None)) &&
     ((isShort) || (board[xCastlingPlaces[d]][row].type==PieceType::None)))
		return true;
	else
		return false;
}
// по цвету и длине рокировки понимаем, на какие именно клетки после рокировки попадут ладья и король
void DarkChessGame::prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,ChessColor color, bool isShort){
    if (color==ChessColor::White){
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
// Пусть дано направление (dx,dy), место, где стоит фигура, и её цвет
// хотим сформировать вектор из возможных ходов этой фигуры в этом направлении
std::vector<Tile> DarkChessGame::checkLine(Tile start,int dx,int dy,ChessColor color){
	std::vector<Tile> result;
	int x=start.x;
	int y=start.y;
	bool stop=false;
    //будем двигаться в этом направлении
	while(!stop){
		x+=dx;
		y+=dy;
        //когда выйдем за пределы доски, надо остановиться
		if(!isOnBoard(x,y))
			stop=true;
		else
            //Если клетка пустая, то на неё можно сходить, и при этом есть смысл проверять следующую
            if(board[x-1][y-1].type==PieceType::None)
				result.push_back(board[x-1][y-1]);
			else
                //Если мы наткнулись на фигуру, то проверим её цвет, проверять клетки дальше смысла нет, остановимся
				if(pieces[board[x-1][y-1].piecenum].color==color)
					stop=true;
				else{
					result.push_back(board[x-1][y-1]);
					stop=true;
				}
	}
	return result;
}

//обновим поле видимости фигуры по её номеру в массиве pieces
void DarkChessGame::updatePieceVision(int num){
	std::vector<Tile> result;
	Tile place=pieces[num].place;
	ChessColor color=pieces[num].color;
	int i;
    //в этом векторе будем хранить промежуточные результаты проверки некоторого направления
	std::vector<Tile>line;
    //произведем разбор случаев по типу фигуры
	switch(pieces[num].type){
        case PieceType::Bishop:
        //для слона проверим диагональные ходы
			for(i=0;i<DIAGNUM;i++){
				line=checkLine(place,xDiagMoves[i],yDiagMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
        case PieceType::Rook:
        //для ладьи - прямые
			for(i=0;i<STRAIGHTNUM;i++){
				line=checkLine(place,xStraightMoves[i],yStraightMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
        case PieceType::Queen:
        //для ферзя - те и другие
			for(i=0;i<STRAIGHTNUM;i++){
				line=checkLine(place,xStraightMoves[i],yStraightMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			for(i=0;i<DIAGNUM;i++){
				line=checkLine(place,xDiagMoves[i],yDiagMoves[i],color);
				result.insert(result.end(),line.begin(),line.end());
			}
			break;
        case PieceType::Knight:
        // для коня - конские
			for(i=0;i<KNIGHTNUM;i++)
				if (checkSingle(place,xKnightMoves[i],yKnightMoves[i],color))
					result.push_back(board[place.x+xKnightMoves[i]-1][place.y+yKnightMoves[i]-1]);
			break;
        case PieceType::Pawn:
        // пешка не укладывается в общую концепцию, здесь придется несколько подробнее:
			int dy;
            // dy есть направление движения пешки
            if (color==ChessColor::White)
				dy=1;
			else
                dy=-1;
            //проверим, на доске ли клетка перед пешкой, если да, то она видна
			if (isOnBoard(place.x,place.y+dy)){
				result.push_back(board[place.x-1][place.y+dy-1]);
                // а если она при этом ещё и пустая, а доска позволяет ходить ещё на клетку вперед и пешка до этого не ходила
                // то можно пешка может сходить сразу на две клетки
                if (board[place.x-1][place.y+dy-1].type==PieceType::None){
					if ((!pieces[num].hasMoved)&&(isOnBoard(place.x,place.y+2*dy)))
						result.push_back(board[place.x-1][place.y+2*dy-1]);
					else;
				}
				else;
			}
			else;
            //теперь разберёмся с клетками по диагонали от пешки, их две, dx - это разность между абсциссами пешки и этих клеток
			for(int dx=-1;dx<2;dx+=2)
                //эта клетка видна, если она пустая, или там стоит чужая фигура
                if ((isOnBoard(place.x+dx,place.y+dy))&&
                                ((board[place.x+dx-1][place.y+dy-1].type==PieceType::None)||
                                (pieces[board[place.x+dx-1][place.y+dy-1].piecenum].color!=pieces[board[place.x-1][place.y-1].piecenum].color)))
					result.push_back(board[place.x+dx-1][place.y+dy-1]);
				else;
			break;
        case PieceType::King:
        //для короля проверяем все направления, но не как линии, а как единичные поля
			for(i=0;i<DIAGNUM;i++)
				if (checkSingle(place,xDiagMoves[i],yDiagMoves[i],color))
					result.push_back(board[place.x+xDiagMoves[i]-1][place.y+yDiagMoves[i]-1]);
			for(i=0;i<STRAIGHTNUM;i++)
				if (checkSingle(place,xStraightMoves[i],yStraightMoves[i],color))
					result.push_back(board[place.x+xStraightMoves[i]-1][place.y+yStraightMoves[i]-1]);
			int row;
            //а теперь проверим рокировки в обе стороны
			if (checkCastling(num,true)){
				row=0;
                if (color==ChessColor::Black)
					row=SIZE-1;
				result.push_back(board[xCastlingPlaces[3]-1][row]);
			}
			if (checkCastling(num,false)){
				row=0;
                if (color==ChessColor::Black)
					row=SIZE-1;
				result.push_back(board[xCastlingPlaces[7]-1][row]);
			}
			break;
	}
    //готовый результат помещается в поле видимости
	pieces[num].vision=result;
}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	
	

