#ifndef ADARKCHESSGAME_H
#define ADARKCHESSGAME_H

#include "achessgame.h"
#include "vector"

#include "dark.h"
#include "stdio.h"
#include "player.h"

class ADarkChessGame:public AChessGame{
protected:
    Tile_content** board;
    Piece_dark* pieces;
    ChessColor turn;
    Move lastmove;
public:
    ADarkChessGame();
    ~ADarkChessGame();
    virtual ChessColor getOrderPlayer();
    virtual Piece getPieceAtTile(Tile tile);
    virtual Move getLastMove();
    virtual std::vector<Tile> getMoveTiles(TiledPiece piece);
    virtual std::vector<Tile> getAttackTiles(TiledPiece piece);
    virtual std::vector<Tile> getHiddenTiles(Player player);
    virtual std::vector<TiledPiece> getConvertionPieces(Player player);
protected:
    void initialize();
    bool doMove(Move move);
    void changeTurn();
private:
    void forcedMove(Tile from, Tile to);
    void doCastling(TiledPiece king,bool isShort);
    void checkVictory(ChessColor color);
    void updateVision();
    bool checkSingle(Tile start,int dx,int dy,ChessColor color);
    std::vector<Tile> checkLine(Tile start,int dx,int dy,ChessColor color);
    bool checkCastling(int kingnum,bool isShort);
    void prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,ChessColor color, bool isShort);
    void updatePieceVision(int num);
};

#endif // ADARKCHESSGAME_H
