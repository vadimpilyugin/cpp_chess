#include "darkchessgame.h"
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
void DarkChessGame::checkVictory(ChessColor color){
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
std::vector<Tile> DarkChessGame::getMoveTiles(TiledPiece piece){
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
std::vector<Tile> DarkChessGame::getAttackTiles(TiledPiece piece){
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
void DarkChessGame::updateVision(){
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
std::vector<Tile> DarkChessGame::getHiddenTiles(Player player){
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
std::vector<TiledPiece> DarkChessGame::getConvertionPieces(Player player){
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
void DarkChessGame::changeTurn(){
    if (turn==ChessColor::White){
        turn=ChessColor::Black;
    }
    else{
        turn=ChessColor::White;
    }
}

//Просто переставляет фигуру с поля from на поле to, игнорируя возможные разногласия с правилами
void DarkChessGame::forcedMove(Tile from, Tile to){
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
void DarkChessGame::doCastling(TiledPiece king,bool isShort){
    Tile rookfrom, rookto,kingfrom,kingto;
    prepareCastling(&rookfrom,&rookto,&kingfrom,&kingto,king.color,isShort);
    forcedMove(rookfrom,rookto);
    forcedMove(kingfrom,kingto);
}

// Проверяет, возможен ли ход, и если да, осуществляет его
bool DarkChessGame::doMove(Move move){
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


