#include "adarkchessgame.h"
#include "stdlib.h"
#include <vector>
#include "stdio.h"

const int BOARDSIZE=8;
const int TOTALPIECES=32;

ADarkChessGame::ADarkChessGame(){
    state=GameState::Going;
    board=new Tile_content* [BOARDSIZE];
    for (int i=0;i<BOARDSIZE;i++)
        board[i]=new Tile_content[BOARDSIZE];
    pieces=new Piece_dark[TOTALPIECES];
    Move nullmove;
    lastmove=nullmove;
}
ADarkChessGame::~ADarkChessGame(){
    for(int i=0;i<BOARDSIZE;i++)
        delete[] board[i];
    delete[] board;
    delete[] pieces;
}
Move ADarkChessGame::getLastMove(){
    return lastmove;
}

ChessColor ADarkChessGame::getOrderPlayer(){
    return turn;
}
Piece ADarkChessGame::getPieceAtTile(Tile tile){
    if (board[tile.x-1][tile.y-1].type==PieceType::None){
        Piece default_piece;
        return default_piece;
    }
    else
        return pieces[board[tile.x-1][tile.y-1].piecenum];
}

// простая проверка того, что клетка лежит в векторе из клеток
bool isInVector(std::vector<Tile> range,Tile tile){
    bool result=false;
    for (auto tileInRange: range) {
        if (tileInRange.x == tile.x && tileInRange.y == tile.y){
            result = true;
            break;
        }
    }
    return result;
}
// Победа определяется как отсутствие в массиве pieces короля определенного цвета
void ADarkChessGame::checkVictory(ChessColor color){
    int i;
    bool victory=true;
    for(i=0;i<TOTALPIECES;i++)
        if ((pieces[i].color!=color)&&(pieces[i].type==PieceType::King))
            victory=false;
    if (victory)
        if (color==ChessColor::White)
            state=GameState::WhiteVictory;
        else
            state=GameState::BlackVictory;
    else;
}
std::vector<Tile> ADarkChessGame::getMoveTiles(TiledPiece piece){
    std::vector<Tile> result;
    int x=piece.place.x;
    int y=piece.place.y;
    int pieceIndex = board[x-1][y-1].piecenum;
    PieceType thisPieceType = pieces[pieceIndex].type;
    //клетки, куда фигура может сходить -- это пустые клетки из её поля видимости, за исключением клеток по диагонали для пешек
    for(auto visionTile: pieces[pieceIndex].vision) {
        if (board[visionTile.x-1][visionTile.y-1].type==PieceType::None &&
            (thisPieceType!=PieceType::Pawn || visionTile.x == x))
            result.push_back(visionTile);
    }
    return result;
}
std::vector<Tile> ADarkChessGame::getAttackTiles(TiledPiece piece){
    std::vector<Tile> result;
    int i;
    int x=piece.place.x;
    int y=piece.place.y;
    int pieceIndex = board[x-1][y-1].piecenum;
    PieceType thisPieceType = pieces[pieceIndex].type;
    //клетки, которые фигура может атаковать -- это непустые клетки из её поля видимости, за исключением клеток спереди для пешек
    for(auto visionTile: pieces[pieceIndex].vision) {
        if (board[visionTile.x-1][visionTile.y-1].type!=PieceType::None &&
            (thisPieceType != PieceType::Pawn || visionTile.x != x))
            result.push_back(visionTile);
    }
    return result;
}

//обновляем поле видимости для всех фигур
void ADarkChessGame::updateVision(){
    int i,j;
    //сначала сделаем все поле невидимым для всех, потом будем отмечать видимые клетки
    for(i=0;i<BOARDSIZE;i++)
        for(j=0;j<BOARDSIZE;j++){
            board[i][j].seenByWhite=false;
            board[i][j].seenByBlack=false;
        }
    int x,y;
    //здесь dc -- это 0 для белых и 16 для чёрных, поскольку их номера в массиве фигур соответственно 0-15 и 16-31
    for(int dc=0;dc<TOTALPIECES/2+1;dc+=TOTALPIECES/2)
        for(i=0;i<TOTALPIECES/2;i++){
            //обновим поле видимости каждой фигуры
            updatePieceVision(i+dc);
            x=pieces[i+dc].place.x;
            y=pieces[i+dc].place.y;
            //поскольку фигура не видит сама себя, эту клетку нужно показать видимыми отдельно
            if (pieces[i+dc].type!=PieceType::None){
                if (dc!=0)
                    board[x-1][y-1].seenByBlack=true;
                else
                    board[x-1][y-1].seenByWhite=true;
            }
            //проходим по полю видимости каждой фигуры и отмечаем соответствующие клетки доски
            for(auto visionTile: pieces[i+dc].vision) {
                if (dc)
                    board[visionTile.x-1][visionTile.y-1].seenByBlack=true;
                else
                    board[visionTile.x-1][visionTile.y-1].seenByWhite=true;
            }
        }
}
//Возвращает клетки, не видимые данным игроком
std::vector<Tile> ADarkChessGame::getHiddenTiles(Player player){
    ChessColor color=player.color;
    std::vector<Tile> result;
    for (int i=0;i<BOARDSIZE;i++)
        for (int j=0;j<BOARDSIZE;j++)
            //пробежим по доске и проверим, видима ли каждая конкретная клетка
            if (color==ChessColor::White)
                if (!board[i][j].seenByWhite)
                    result.push_back(board[i][j]);
                else;
            else
                if (!board[i][j].seenByBlack)
                    result.push_back(board[i][j]);
                else;
    return result;
}
// возвращает фигуры на клетках, которые будут превращаться
std::vector<TiledPiece> ADarkChessGame::getConvertionPieces(Player player){
    // нужно проверить первую либо последнюю линию на наличие пешек
    std::vector<TiledPiece> result;
    // белые должны дойти до 8 линии, черные - до 1
    int line = player.color == ChessColor::White ? BOARDSIZE-1 : 0;
    for (int i = 0; i < BOARDSIZE; i++) {
        Tile_content tile_with_piece = board[i][line];
        // проверяем клетки на наличие пешек
        if (tile_with_piece.type == PieceType::Pawn && pieces[tile_with_piece.piecenum].color == player.color)
            result.push_back(pieces[board[i][line].piecenum]);
    }
    return result;
}
//Передает ход другому игроку
void ADarkChessGame::changeTurn(){
    if (turn==ChessColor::White){
        turn=ChessColor::Black;
    }
    else{
        turn=ChessColor::White;
    }
}

//Просто переставляет фигуру с поля from на поле to, игнорируя возможные разногласия с правилами
void ADarkChessGame::forcedMove(Tile from, Tile to){
    if (board[to.x-1][to.y-1].type!=PieceType::None)
        pieces[board[to.x-1][to.y-1].piecenum].type=PieceType::None;
    board[to.x-1][to.y-1].piecenum=board[from.x-1][from.y-1].piecenum;
    board[to.x-1][to.y-1].type=board[from.x-1][from.y-1].type;
    pieces[board[from.x-1][from.y-1].piecenum].place.x=to.x;
    pieces[board[from.x-1][from.y-1].piecenum].place.y=to.y;
    pieces[board[from.x-1][from.y-1].piecenum].hasMoved=true;
    board[from.x-1][from.y-1].type=PieceType::None;
    updateVision();
}

// Осуществляет рокировку
void ADarkChessGame::doCastling(TiledPiece king,bool isShort){
    Tile rookfrom, rookto,kingfrom,kingto;
    prepareCastling(&rookfrom,&rookto,&kingfrom,&kingto,king.color,isShort);
    forcedMove(rookfrom,rookto);
    forcedMove(kingfrom,kingto);
}

// Проверяет, возможен ли ход, и если да, осуществляет его
bool ADarkChessGame::doMove(Move move){
    // Проверяем, есть ли фигура на данной клетке
    if (board[move.from.x-1][move.from.y-1].type==PieceType::None)
        return false;
    Piece_dark moving=pieces[board[move.from.x-1][move.from.y-1].piecenum];
    //Проверяем, является ли ход превращением пешки, проверяем его корректность и осуществляем превращение
    if ((move.isConvertion) && (moving.type==PieceType::Pawn) &&
    ((moving.color==ChessColor::Black) && (move.from.y==1) ||
    (moving.color==ChessColor::White) && (move.from.y==8))){
        pieces[board[move.from.x-1][move.from.y-1].piecenum].type=move.convertPiece;
        board[move.from.x-1][move.from.y-1].type=move.convertPiece;
        updateVision();
        return true;
    }
    //В отличие от остальных фигур, у пешки поле видимости не всегда совпадает с полем возможных ходов,
    //поэтому здесь необходима дополнительная проверка
    if (moving.type==PieceType::Pawn){
        if (((move.from.x!=move.to.x)&&(board[move.to.x-1][move.to.y-1].type==PieceType::None))||
        ((move.from.x==move.to.x)&&(board[move.to.x-1][move.to.y-1].type!=PieceType::None)))
            return false;
    }
    //Проверим, лежит ли поле, куда мы хотим попасть, в поле видимости фигуры
    if ((turn==moving.color)&&(isInVector(moving.vision,move.to))){
        //Проверим, является ли ход рокировкой, короткой или длинной
        if ((moving.type==PieceType::King) && ((move.to.x-move.from.x)==2)){
            doCastling(moving,true);
        }
        else if ((moving.type==PieceType::King) && ((move.to.x-move.from.x)==-2)){
            doCastling(moving,false);
        }
        //Если ход корректен, но не рокировка, значит, это просто перестановка фигуры на другое место
        else
            forcedMove(move.from,move.to);
    }
    //Если проверка на корректность не пройдена, возвратим false
    else
        return false;
    //Проверим, не выиграл ли ходящий в результате этого хода
    if (turn==ChessColor::White){
        checkVictory(ChessColor::White);
        turn=ChessColor::Black;
    }
    else{
        checkVictory(ChessColor::Black);
        turn=ChessColor::White;
    }
    //Сохраним ход
    lastmove=move;
    return true;
}

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
    return ((x>0)&&(x<BOARDSIZE+1)&&(y>0)&&(y<BOARDSIZE+1));
}

//расставить фигуры и приготовиться к игре
void ADarkChessGame::initialize(){
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
bool ADarkChessGame::checkSingle(Tile start,int dx,int dy,ChessColor color){
    //проверим, на доске ли поле, на которое мы собираемся сходить
    if (isOnBoard(start.x+dx,start.y+dy))
        //на поле можно сходить, если оно пустое или если там стоит вражеская фигура
        return ((board[start.x+dx-1][start.y+dy-1].type==PieceType::None)||(pieces[board[start.x+dx-1][start.y+dy-1].piecenum].color!=color));
    else
        return false;
}
//проверим, осуществима ли рокировка, зная номер короля в массиве pieces и то, хотим ли мы короткую или длинную рокировку
bool ADarkChessGame::checkCastling(int kingnum,bool isShort){
    ChessColor color=pieces[kingnum].color;
    //нельзя делать рокировку, если король ходил до этого
    if (pieces[kingnum].hasMoved==true)
        return false;
    // row и d выбираются исходя из цвета короля и длины рокировки и потом помогают нам найти ладью и места для рокировки
    int row=0;
    if (color==ChessColor::Black)
        row+=BOARDSIZE-1;
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
void ADarkChessGame::prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,ChessColor color, bool isShort){
    if (color==ChessColor::White){
        rookfrom->y=1;
        rookto->y=1;
        kingfrom->y=1;
        kingto->y=1;
    }
    else{
        rookfrom->y=BOARDSIZE;
        rookto->y=BOARDSIZE;
        kingfrom->y=BOARDSIZE;
        kingto->y=BOARDSIZE;
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
std::vector<Tile> ADarkChessGame::checkLine(Tile start,int dx,int dy,ChessColor color){
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
void ADarkChessGame::updatePieceVision(int num){
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
                    row=BOARDSIZE-1;
                result.push_back(board[xCastlingPlaces[3]-1][row]);
            }
            if (checkCastling(num,false)){
                row=0;
                if (color==ChessColor::Black)
                    row=BOARDSIZE-1;
                result.push_back(board[xCastlingPlaces[7]-1][row]);
            }
            break;
    }
    //готовый результат помещается в поле видимости
    pieces[num].vision=result;
}
