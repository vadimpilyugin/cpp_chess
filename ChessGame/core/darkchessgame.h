#pragma once
#include "chessgame.h"

class DarkChessGame:public ChessGame{
    public:
        bool doMove(Move move);
        std::vector<Tile> getMoveTiles(TiledPiece piece);
        std::vector<Tile> getAttackTiles(TiledPiece piece);
        std::vector<Tile> getHiddenTiles(Player player);
        std::vector<TiledPiece> getConvertionPieces(Player player);
        void initialize();
//METHODS BELOW WILL BE PRIVATE CAUSE NOBODY ELSE WILL NEED THEM
    private:
        void forcedMove(Tile from, Tile to);
        void doCastling(TiledPiece king,bool isShort);
        void checkVictory(ChessColor color);
        void updateVision();
        void rawOutput(ChessColor color);
        bool checkSingle(Tile start,int dx,int dy,ChessColor color);
        std::vector<Tile> checkLine(Tile start,int dx,int dy,ChessColor color);
        bool checkCastling(int kingnum,bool isShort);
        void prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,ChessColor color, bool isShort);
        void updatePieceVision(int num);
};
