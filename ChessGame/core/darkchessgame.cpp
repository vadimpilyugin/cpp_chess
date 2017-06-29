#include "darkchessgame.h"

bool isInVector(std::vector<Tile> range,Tile tile){
    bool result=false;
    // FIXME(13)
    /*
    for (auto tileInRange: range) {
        if (tileInRange.x == tile.x && tileInRange.y == tile.y){
            result = true;
            break;
        }
    }
    */
    for (int i=0;i<range.size();i++)
        if ((tile.x==range[i].x)&&(tile.y==range[i].y)){
            result=true;
            break;
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
    int i;
    int x=piece.place.x;
    int y=piece.place.y;
    // FIXME(11): заменить цикл на более читабельный
    /*
    int pieceIndex = board[x-1][y-1].piecenum;
    PieceType thisPieceType = pieces[pieceIndex].type;

    for(auto visionTile: pieces[pieceIndex].vision) {
        if (board[visionTile.x-1][visionTile.y-1].type==PieceType::None &&
            (thisPieceType!=PieceType::Pawn || visionTile.x == x))
            result.push_back(visionTile);
    }*/
    for (i=0;i<pieces[board[x-1][y-1].piecenum].vision.size();i++)
        if ((board[pieces[board[x-1][y-1].piecenum].vision[i].x-1]
            [pieces[board[x-1][y-1].piecenum].vision[i].y-1].type==PieceType::None)&&
            ((pieces[board[x-1][y-1].piecenum].type!=PieceType::Pawn)||(pieces[board[x-1][y-1].piecenum].vision[i].x==x)))
        result.push_back(pieces[board[x-1][y-1].piecenum].vision[i]);
    return result;
}
std::vector<Tile> DarkChessGame::getAttackTiles(TiledPiece piece){
    std::vector<Tile> result;
    int i;
    int x=piece.place.x;
    int y=piece.place.y;
    // FIXME(12): то же самое
    /*
    int pieceIndex = board[x-1][y-1].piecenum;
    PieceType thisPieceType = pieces[pieceIndex].type;
    for(auto visionTile: pieces[pieceIndex].vision) {
        if (board[visionTile.x-1][visionTile.y-1].type!=PieceType::None &&
            (thisPieceType != PieceType::Pawn || visionTile.x != x)
            result.push_back(visionTile);
    }
    */
    for (i=0;i<pieces[board[x-1][y-1].piecenum].vision.size();i++)
        if ((board[pieces[board[x-1][y-1].piecenum].vision[i].x-1]
            [pieces[board[x-1][y-1].piecenum].vision[i].y-1].type!=PieceType::None)&&
            ((pieces[board[x-1][y-1].piecenum].type!=PieceType::Pawn)||(pieces[board[x-1][y-1].piecenum].vision[i].x!=x)))
        result.push_back(pieces[board[x-1][y-1].piecenum].vision[i]);
    return result;
}
void DarkChessGame::updateVision(){
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
            if (pieces[i+dc].type!=PieceType::None){
                if (dc!=0)
                    board[x-1][y-1].seenByBlack=true;
                else
                    board[x-1][y-1].seenByWhite=true;
            }
            // FIXME(13): читабельность++
            /*
            for(auto visionTile: pieces[i+dc].vision) {
                if (dc)
                    board[visionTile.x-1][visionTile.y-1].seenByBlack=true;
                else
                    board[visionTile.x-1][visionTile.y-1].seenByWhite=true;
            }
            */
            for (j=0;j<pieces[i+dc].vision.size();j++)
                if (dc)
                    board[pieces[i+dc].vision[j].x-1][pieces[i+dc].vision[j].y-1].seenByBlack=true;
                else
                    board[pieces[i+dc].vision[j].x-1][pieces[i+dc].vision[j].y-1].seenByWhite=true;
        }
}
//Возвращает клетки, не видимые данным игроком
std::vector<Tile> DarkChessGame::getHiddenTiles(Player player){
    ChessColor color=player.color;
    std::vector<Tile> result;
    for (int i=0;i<SIZE;i++)
        for (int j=0;j<SIZE;j++)
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
    int line = player.color == ChessColor::White ? SIZE-1 : 0;
    for (int i = 0; i < SIZE; i++) {
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


