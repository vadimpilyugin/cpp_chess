#ifndef ACHESSGAME_H
#define ACHESSGAME_H

#include <set>
#include <vector>
#include "tile.h"
#include "command.h"
#include "player.h"

class IChessObserver;

using std::set;
using std::vector;

enum class GameState{Going,WhiteVictory,BlackVictory,Draw,WhiteOfferDraw,BlackOfferDraw,WhiteGiveUp,BlackGiveUp,Termination};

class AChessGame
{
public:
    AChessGame();
    virtual ~AChessGame();

    virtual void attachObserver(IChessObserver* observer);
    virtual void detachObserver(IChessObserver* observer);
    virtual void notifyObservers();
    virtual GameState getState()const;

    virtual void doCommand(Command *command)=0;
    virtual vector<TiledPiece> getConvertionPieces(Player player)const=0;
    virtual vector<Tile> getMoveTiles(TiledPiece piece)const=0;
    virtual vector<Tile> getAttackTiles(TiledPiece piece)const=0;
    virtual Piece getPieceAtTile(Tile tile)const=0;
    virtual ChessColor getOrderPlayer()const=0;
    virtual Move getLastMove()const=0;


protected:
    set<IChessObserver*> observers;
    GameState state;
};

#endif // ACHESSGAME_H
