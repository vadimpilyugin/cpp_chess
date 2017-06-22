#include "color.h"
#include "tile.h"
#include "piece.h"

class Command {
public:
	Color color;
	virtual std::string serialize () = 0;
};

class Move: public Command {
public:
	Tile from;
	Tile to;
	bool isConvertion;
	PieceType convertPiece;
	virtual std::string serialize ();
};

class GiveUpCommand: public Command {
public:
	virtual std::string serialize ();
};
class OfferDrawCommand: public Command {
public:
	virtual std::string serialize ();
};
class TerminationCommand: public Command {
public:
	virtual std::string serialize ();
};