#include "command.h"

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
	virtual std::string serialize () {
		return std::string("TODO: implement serialization for Move class");
	}
};

class GiveUpCommand: public Command {
public:
	virtual std::string serialize () {
		return std::string("TODO: implement serialization for GiveUpCommand class");
	}
};
class OfferDrawCommand: public Command {
public:
	virtual std::string serialize () {
		return std::string("TODO: implement serialization for OfferDrawCommand class");
	}
};
class TerminationCommand: public Command {
public:
	virtual std::string serialize () {
		return std::string("TODO: implement serialization for TerminationCommand class");
	}
};