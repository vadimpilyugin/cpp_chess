#ifndef TYPES_H
#define TYPES_H

#include <string>

typedef std::string String;

enum class PlayerColor {White,Black};
enum class PieceType {Queen, Rook,Bishop,Knight,Pawn,King,None};
enum class GameState{Going,WhiteVictory,BlackVictory,Draw};
enum class BoardDirection{TopRight,BottomRight,TopLeft,BottomLeft};

String pieceTypeToString(PieceType pt);
PieceType stringToPieceType(String str);
String playerColorToString(PlayerColor pc);
PlayerColor stringToPlayerColor(String str);

struct Tile{
    int x,y;
    Tile(int x,int y){
        this->x=x;
        this->y=y;
    }
    Tile():x(0),y(0){}
};

struct Player{
    PlayerColor color;
    String name;
};

class Piece{
public:
    PieceType type;
    PlayerColor color;
    bool hasMoved;
    Piece():type(PieceType::None),color(PlayerColor::White),hasMoved(false){}
};

class TiledPiece:public Piece{
public:
    Tile place;
};

class Command{
public:
    PlayerColor player;
    virtual String serialize()=0;
};

class Move:public Command{
public:
    Tile from;
    Tile to;
    bool isConvertion;
    PieceType convertPiece;
    Move():isConvertion(false){};
    virtual String serialize();
};

#endif // TYPES_H
