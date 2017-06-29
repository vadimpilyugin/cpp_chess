#pragma once
#include "chessgame.h"

class DarkChessGame:public ChessGame{
    public:

        virtual std::vector<Tile> getMoveTiles(TiledPiece piece); // FIXME: перенести в ADCG.h
        virtual std::vector<Tile> getAttackTiles(TiledPiece piece); // FIXME: перенести в ADCG.h
        virtual std::vector<Tile> getHiddenTiles(Player player); // FIXME: перенести в ADCG.h
        virtual std::vector<TiledPiece> getConvertionPieces(Player player); // FIXME: перенести в ADCG.h

    protected:
    void initialize(); // FIXME: перенести в ADCG.h
        bool doMove(Move move); // FIXME: перенести в ADCG.h
        void changeTurn(); // FIXME: перенести в ADCG.h

    private:  // FIXME: перенести в ADCG.h
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
