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
    virtual GameState getState();

    virtual void doCommand(Command *command)=0;
    virtual vector<TiledPiece> getConvertionPieces(Player player)=0;
    virtual vector<Tile> getMoveTiles(TiledPiece piece)=0;
    virtual vector<Tile> getAttackTiles(TiledPiece piece)=0;
    virtual Piece getPieceAtTile(Tile tile)=0;
    virtual ChessColor getOrderPlayer()=0;
    virtual Move getLastMove()=0;


protected:
    set<IChessObserver*> observers;
    GameState state;
};

#endif // ACHESSGAME_H
