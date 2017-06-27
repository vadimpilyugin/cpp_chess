#pragma once

#include "chesscolor.h"
#include "tile.h"
#include "piece.h"
#include "my_exception.h"
#include <map>

class WrongCommandException: public Exception::Exception {
public:
    WrongCommandException(const std::string _msg): Exception(_msg) {}
};
/*
* Нужно для паттерна Фабрика
*/
class Clonable
{
public:
	virtual Clonable* clone() const = 0;
};

struct Command: Clonable {
    ChessColor playerColor;
	static const std::string CLASS_NAME;
    Command (ChessColor color_ = ChessColor::None) { playerColor = color_; }
    virtual ~Command(){}
	virtual std::string serialize () const;
	virtual Command* deserialize (std::string command) throw (
		NoSuchColorException, 
		WrongCommandException,
		NoSuchPieceException
	);
	virtual Command* clone() const { return new Command(*this); }
	virtual std::string getClassName () const { return CLASS_NAME; }
};

struct Move: public Command {
	Tile from;
	Tile to;
	bool isConvertion;
	PieceType convertPiece;
	static const std::string CLASS_NAME;
	Move (Tile from_ = Tile (), Tile to_ = Tile (), bool isConvertion_ = false, PieceType convertPiece_ = PieceType::None): 
		from (from_), to (to_), isConvertion (isConvertion_) { convertPiece = convertPiece_; }
    bool operator==(const Move &m2) const;
	virtual std::string serialize () const;
	virtual Move* deserialize (std::string command) throw (NoSuchPieceException, WrongCommandException);
	virtual Move* clone() const { return new Move(*this); }
	virtual std::string getClassName () const { return CLASS_NAME; }
};

struct GiveUpCommand: public Command {
	static const std::string CLASS_NAME;
	static const std::string GIVE_UP_COMMAND;
	virtual std::string serialize () const;
	virtual GiveUpCommand* deserialize (std::string command) throw (WrongCommandException);
	virtual GiveUpCommand* clone() const { return new GiveUpCommand(*this); }
	virtual std::string getClassName () const { return CLASS_NAME; }
};

struct OfferDrawCommand: public Command {
	static const std::string CLASS_NAME;
	static const std::string OFFER_DRAW_COMMAND;
	virtual std::string serialize () const;
	virtual OfferDrawCommand* deserialize (std::string command) throw (WrongCommandException);
	virtual OfferDrawCommand* clone() const { return new OfferDrawCommand(*this); }
	virtual std::string getClassName () const { return CLASS_NAME; }
};

struct AcceptDrawCommand: public Command {
    static const std::string CLASS_NAME;
    static const std::string ACCEPT_DRAW_COMMAND;
    virtual std::string serialize () const;
    virtual AcceptDrawCommand* deserialize (std::string command) throw (WrongCommandException);
    virtual AcceptDrawCommand* clone() const { return new AcceptDrawCommand(*this); }
    virtual std::string getClassName () const { return CLASS_NAME; }
};

struct RefuseDrawCommand: public Command {
    static const std::string CLASS_NAME;
    static const std::string REFUSE_DRAW_COMMAND;
    virtual std::string serialize () const;
    virtual RefuseDrawCommand* deserialize (std::string command) throw (WrongCommandException);
    virtual RefuseDrawCommand* clone() const { return new RefuseDrawCommand(*this); }
    virtual std::string getClassName () const { return CLASS_NAME; }
};

struct TerminationCommand: public Command {
	static const std::string CLASS_NAME;
	static const std::string TERMINATION_COMMAND;
	virtual std::string serialize () const;
	virtual TerminationCommand* deserialize (std::string command) throw (WrongCommandException);
	virtual TerminationCommand* clone() const { return new TerminationCommand(*this); }
	virtual std::string getClassName () const { return CLASS_NAME; }
};

struct GreetingCommand: public Command {
    static const std::string CLASS_NAME;
    static const std::string GREETING_COMMAND;
    std::string playerName;
    virtual std::string serialize () const;
    virtual GreetingCommand* deserialize (std::string command) throw (WrongCommandException);
    virtual GreetingCommand* clone() const { return new GreetingCommand(*this); }
    virtual std::string getClassName () const { return CLASS_NAME; }
};

struct PassCommand: public Command {
    static const std::string CLASS_NAME;
    static const std::string PASS_COMMAND;
    virtual std::string serialize () const;
    virtual PassCommand* deserialize (std::string command) throw (WrongCommandException);
    virtual PassCommand* clone() const { return new PassCommand(*this); }
    virtual std::string getClassName () const { return CLASS_NAME; }
};

// Фабрика
class CommandFactory
{
public:
    CommandFactory ();
	Command* get(std::string const& class_name) const throw (std::out_of_range);
    ~CommandFactory () {
		delete ex1;
		delete ex2;
		delete ex3;
		delete ex4;
		delete ex5;
		delete ex6;
		delete ex7;
        delete ex8;
        delete ex9;
	}

private:
	void set(std::string const& class_name, Command* exemplar);
	typedef std::map < std::string, Command* > exemplars_type;
	exemplars_type mExemplars;
	// Типы производимых классов
	Command *ex1;
	Move *ex2;
	GiveUpCommand *ex3;
	OfferDrawCommand *ex4;
    AcceptDrawCommand *ex5;
    RefuseDrawCommand *ex6;
    TerminationCommand *ex7;
    GreetingCommand *ex8;
    PassCommand *ex9;
};
