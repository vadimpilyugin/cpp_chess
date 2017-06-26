#include "command.h"
#include "printer.h"
#include "serialize.h"

const std::string Command::CLASS_NAME = std::string("Command");
const std::string Move::CLASS_NAME = std::string("Move");
const std::string GiveUpCommand::CLASS_NAME = std::string("GiveUpCommand");
const std::string OfferDrawCommand::CLASS_NAME = std::string("OfferDrawCommand");
const std::string AcceptDrawCommand::CLASS_NAME = std::string("AcceptDrawCommand");
const std::string RefuseDrawCommand::CLASS_NAME = std::string("RefuseDrawCommand");
const std::string TerminationCommand::CLASS_NAME = std::string("TerminationCommand");
const std::string GreetingCommand::CLASS_NAME = std::string("GreetingCommand");
const std::string PassCommand::CLASS_NAME = std::string("PassCommand");

const std::string GiveUpCommand::GIVE_UP_COMMAND = std::string("igiveup");
const std::string OfferDrawCommand::OFFER_DRAW_COMMAND = std::string ("draw_offer");
const std::string AcceptDrawCommand::ACCEPT_DRAW_COMMAND = std::string ("draw_accept");
const std::string RefuseDrawCommand::REFUSE_DRAW_COMMAND = std::string ("draw_refuse");
const std::string TerminationCommand::TERMINATION_COMMAND = std::string ("termination");
const std::string GreetingCommand::GREETING_COMMAND = std::string ("greeting");
const std::string PassCommand::PASS_COMMAND = std::string ("pass");

std::string Command::serialize () const {
	SerializedObject result;
	// добавляем имя класса
	result.add (CLASS_NAME);
	// добавляем цвет к сериализованному объекту
    result.add (toString (playerColor));
	return result.toString ();
}
Command *Command::deserialize (std::string command)
	throw (
		NoSuchColorException, 
		WrongCommandException,
		NoSuchPieceException
	)
{
	try {
		SerializedObject result (command);
        playerColor = toColor (result.get ());
	}
	catch (NoSuchColorException &exc) {
		Printer::error (exc.what(), "Command::deserialize");
		throw;
	}
	return this;
}

std::string Move::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (std::to_string (from.x));
	result.add (std::to_string (from.y));
	result.add (std::to_string (to.x));
	result.add (std::to_string (to.y));
	result.add (std::to_string (isConvertion ? 1 : 0));
	result.add (toString (convertPiece));
	return result.toString();
}
Move *Move::deserialize (std::string command) throw (NoSuchPieceException, WrongCommandException) {
	SerializedObject result (command);
	try {
		from.x = std::stoi (result.get ());
		from.y = std::stoi (result.get ());
		to.x = std::stoi (result.get ());
		to.y = std::stoi (result.get ());
		isConvertion = std::stoi (result.get ()) ? true : false;
		convertPiece = toPiece (result.get ());
	}
	catch (std::invalid_argument &exc) {
		Printer::error (command, "Move::deserialize");
		throw WrongCommandException (command);
	}
	catch (NoSuchPieceException &exc) {
		Printer::error (command, "Move::deserialize");
		throw;
	}
	return this;
}

std::string GiveUpCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (GIVE_UP_COMMAND);
	return result.toString();
}
GiveUpCommand* GiveUpCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != GIVE_UP_COMMAND) {
		Printer::error (command, "GiveUpCommand::deserialize");
		throw WrongCommandException (command);
	}
	return this;
}

std::string OfferDrawCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (OFFER_DRAW_COMMAND);
	return result.toString();
}
OfferDrawCommand* OfferDrawCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != OFFER_DRAW_COMMAND) {
		Printer::error (command, "OfferDrawCommand::deserialize");
		throw WrongCommandException (command);
	}
	return this;
}

std::string AcceptDrawCommand::serialize () const {
    SerializedObject result;
    result.add (CLASS_NAME);
    result.add (ACCEPT_DRAW_COMMAND);
    return result.toString();
}
AcceptDrawCommand* AcceptDrawCommand::deserialize (std::string command) throw (WrongCommandException) {
    SerializedObject result (command);
    if (result.get () != ACCEPT_DRAW_COMMAND) {
        Printer::error (command, "AcceptDrawCommand::deserialize");
        throw WrongCommandException (command);
    }
    return this;
}

std::string RefuseDrawCommand::serialize () const {
    SerializedObject result;
    result.add (CLASS_NAME);
    result.add (REFUSE_DRAW_COMMAND);
    return result.toString();
}
RefuseDrawCommand* RefuseDrawCommand::deserialize (std::string command) throw (WrongCommandException) {
    SerializedObject result (command);
    if (result.get () != REFUSE_DRAW_COMMAND) {
        Printer::error (command, "RefuseDrawCommand::deserialize");
        throw WrongCommandException (command);
    }
    return this;
}

std::string TerminationCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (TERMINATION_COMMAND);
	return result.toString();
}
TerminationCommand* TerminationCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != TERMINATION_COMMAND) {
		Printer::error (command, "TerminationCommand::deserialize");
		throw WrongCommandException (command);
	}
	return this;
}

std::string GreetingCommand::serialize () const {
    SerializedObject result;
    result.add (CLASS_NAME);
    result.add (GREETING_COMMAND);
    result.add(playerName);
    return result.toString();
}
GreetingCommand* GreetingCommand::deserialize (std::string command) throw (WrongCommandException) {
    SerializedObject result (command);
    if (result.get () != GREETING_COMMAND) {
        Printer::error (command, "Greeting::deserialize");
        throw WrongCommandException (command);
    }
    playerName=result.get();
    return this;
}
std::string PassCommand::serialize () const {
    SerializedObject result;
    result.add (CLASS_NAME);
    result.add (PASS_COMMAND);
    return result.toString();
}
PassCommand* PassCommand::deserialize (std::string command) throw (WrongCommandException) {
    SerializedObject result (command);
    if (result.get () != PASS_COMMAND) {
        Printer::error (command, "Greeting::deserialize");
        throw WrongCommandException (command);
    }
    return this;
}

CommandFactory::CommandFactory ():
	ex1 (nullptr),
	ex2 (nullptr),
	ex3 (nullptr),
	ex4 (nullptr),
	ex5 (nullptr),
	ex6 (nullptr),
	ex7 (nullptr)
{
	ex1 = new Command ();
	ex2 = new Move ();
	ex3 = new GiveUpCommand ();
	ex4 = new OfferDrawCommand ();
	ex5 = new TerminationCommand ();
	ex6 = new GreetingCommand ();
	ex7 = new PassCommand ();
	set (Command::CLASS_NAME, ex1);
	set (Move::CLASS_NAME, ex2);
	set (GiveUpCommand::CLASS_NAME, ex3);
	set (OfferDrawCommand::CLASS_NAME, ex4);
	set (TerminationCommand::CLASS_NAME, ex5);
	set (GreetingCommand::CLASS_NAME, ex6);
	set (PassCommand::CLASS_NAME, ex7);
}

Command* CommandFactory::get(std::string const& class_name) const throw (std::out_of_range) {
	return mExemplars.at (class_name) -> clone ();
}
void CommandFactory::set(std::string const& class_name, Command* exemplar) {
	mExemplars [class_name] = exemplar;
}
