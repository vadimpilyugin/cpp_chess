#include "command.h"
#include "printer.h"
#include "serialize.h"

using namespace Command;
const std::string Command::Command::CLASS_NAME = std::string("Command");
const std::string Move::CLASS_NAME = std::string("Move");
const std::string GiveUpCommand::CLASS_NAME = std::string("GiveUpCommand");
const std::string OfferDrawCommand::CLASS_NAME = std::string("OfferDrawCommand");
const std::string TerminationCommand::CLASS_NAME = std::string("TerminationCommand");

const std::string GiveUpCommand::GIVE_UP_COMMAND = std::string("igiveup");
const std::string OfferDrawCommand::OFFER_DRAW_COMMAND = std::string ("draw_offer");
const std::string TerminationCommand::TERMINATION_COMMAND = std::string ("termination");

std::string Command::Command::serialize () const {
	SerializedObject result;
	// добавляем имя класса
	result.add (CLASS_NAME);
	// добавляем цвет к сериализованному объекту
	result.add (Color::toString (color));
	return result.toString ();
}
void Command::Command::deserialize (std::string command)
	throw (
		Color::NoSuchColorException, 
		WrongCommandException,
		Piece::NoSuchPieceException
	)
{
	try {
		SerializedObject result (command);
		color = Color::toColor (result.get ());
	}
	catch (Color::NoSuchColorException &exc) {
		Printer::error (exc.what(), "Command::deserialize");
		throw;
	}
}

std::string Move::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (std::to_string (from.x));
	result.add (std::to_string (from.y));
	result.add (std::to_string (to.x));
	result.add (std::to_string (to.y));
	result.add (std::to_string (isConvertion ? 1 : 0));
	result.add (Piece::toString (convertPiece));
	return result.toString();
}
void Move::deserialize (std::string command) throw (Piece::NoSuchPieceException, WrongCommandException) {
	SerializedObject result (command);
	try {
		from.x = std::stoi (result.get ());
		from.y = std::stoi (result.get ());
		to.x = std::stoi (result.get ());
		to.y = std::stoi (result.get ());
		isConvertion = std::stoi (result.get ()) ? true : false;
		convertPiece = Piece::toPiece (result.get ());
	}
	catch (std::invalid_argument &exc) {
		Printer::error (command, "Move::deserialize");
		throw WrongCommandException (command);
	}
	catch (Piece::NoSuchPieceException &exc) {
		Printer::error (command, "Move::deserialize");
		throw;
	}
}

std::string GiveUpCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (GIVE_UP_COMMAND);
	return result.toString();
}
void GiveUpCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != GIVE_UP_COMMAND) {
		Printer::error (command, "GiveUpCommand::deserialize");
		throw WrongCommandException (command);
	}
}

std::string OfferDrawCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (OFFER_DRAW_COMMAND);
	return result.toString();
}
void OfferDrawCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != OFFER_DRAW_COMMAND) {
		Printer::error (command, "OfferDrawCommand::deserialize");
		throw WrongCommandException (command);
	}
}

std::string TerminationCommand::serialize () const {
	SerializedObject result;
	result.add (CLASS_NAME);
	result.add (TERMINATION_COMMAND);
	return result.toString();
}
void TerminationCommand::deserialize (std::string command) throw (WrongCommandException) {
	SerializedObject result (command);
	if (result.get () != TERMINATION_COMMAND) {
		Printer::error (command, "TerminationCommand::deserialize");
		throw WrongCommandException (command);
	}
}

Command::Command* Factory::get(std::string const& class_name) const throw (std::out_of_range) {
	return mExemplars.at (class_name) -> clone ();
}
void Factory::set(std::string const& class_name, Command* exemplar) {
	mExemplars [class_name] = exemplar;
}