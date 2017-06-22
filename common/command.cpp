#include "command.h"

class Command {
public:
	Color color;
	Command (std::string command_ = std::string()): command (command_) {}
	virtual std::string serialize () {
		return Color::toString (color);
	}
private:
	static const std::string command;
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