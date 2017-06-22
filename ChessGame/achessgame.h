#ifndef ACHESSGAME_H
#define ACHESSGAME_H

#include <set>
#include <vector>
#include "types.h"

class IChessObserver;

using std::set;
using std::vector;

class AChessGame
{
public:
    virtual void attachObserver(IChessObserver* observer);
    virtual void detachObserver(IChessObserver* observer);

    virtual void doCommand(Command *command)=0;
    virtual vector<TiledPiece> getConvertionPieces(Player player)=0;
    virtual vector<Tile> getMoveTiles(TiledPiece piece)=0;
    virtual vector<Tile> getAttackTiles(TiledPiece piece)=0;
    virtual Piece getPieceAtTile(Tile tile)=0;
    virtual Player getOrderPlayer()=0;
    virtual GameState getState()=0;

protected:
    set<IChessObserver*> observers;
private:
    AChessGame();
};

#endif // ACHESSGAME_H
