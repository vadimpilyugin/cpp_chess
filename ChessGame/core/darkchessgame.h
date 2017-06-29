#pragma once
#include "chessgame.h"

class DarkChessGame:public ChessGame{
    public:
        bool doMove(Move move);
        // FIXME(10): они должны быть объявлены виртуальными
        std::vector<Tile> getMoveTiles(TiledPiece piece);
        std::vector<Tile> getAttackTiles(TiledPiece piece);
        std::vector<Tile> getHiddenTiles(Player player);
        std::vector<TiledPiece> getConvertionPieces(Player player);
        //
        void initialize();
    protected:
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
