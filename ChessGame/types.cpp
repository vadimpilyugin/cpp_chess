#include "types.h"

String pieceTypeToString(PieceType pt){
    switch(pt){
    case PieceType::Queen:
        return "Queen";
    case PieceType::Rook:
        return "Rook";
    case PieceType::Bishop:
        return "Bishop";
    case PieceType::Knight:
        return "Knight";
    case PieceType::Pawn:
        return "Pawn";
    case PieceType::King:
        return "King";
    default:
        return "None";
    }
}

PieceType stringToPieceType(String str){
    if(str=="Queen") return PieceType::Queen;
    else if(str=="Rook") return PieceType::Rook;
    else if(str=="Bishop") return PieceType::Bishop;
    else if(str=="Knight") return PieceType::Knight;
    else if(str=="Pawn") return PieceType::Pawn;
    else if(str=="King") return PieceType::King;
    else return PieceType::None;
}

String playerColorToString(PlayerColor pc){
    if(pc==PlayerColor::Black)return "Black";
    else return "White";
}

PlayerColor stringToPlayerColor(String str){
    if(str=="Black")return PlayerColor::Black;
    else return PlayerColor::White;
}

String Move::serialize()
{
    return "blaa";
}
