#include "color.h"
#include "tile.h"
#include "piece.h"
#include "my_exception.h"
#include <map>
namespace Command {
	
	class WrongCommandException: public Exception::Exception {
		using Exception::Exception;
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
		Color::Color color;
		static const std::string CLASS_NAME;
		Command (Color::Color color_ = Color::None): color (color_) {}
		virtual std::string serialize () const;
		virtual void deserialize (std::string command) throw (
			Color::NoSuchColorException, 
			WrongCommandException,
			Piece::NoSuchPieceException
		);
		virtual Command* clone() const { return new Command(*this); }
	};

	struct Move: public Command {
		Tile from;
		Tile to;
		bool isConvertion;
		Piece::PieceType convertPiece;
		static const std::string CLASS_NAME;
		Move (Tile from_ = Tile (), Tile to_ = Tile (), bool isConvertion_ = false, Piece::PieceType convertPiece_ = Piece::PieceType::None): 
			from (from_), to (to_), isConvertion (isConvertion_), convertPiece (convertPiece_) {}
		virtual std::string serialize () const;
		virtual void deserialize (std::string command) throw (Piece::NoSuchPieceException, WrongCommandException);
		virtual Move* clone() const { return new Move(*this); }
	};
	struct GiveUpCommand: public Command {
		static const std::string CLASS_NAME;
		static const std::string GIVE_UP_COMMAND;
		virtual std::string serialize () const;
		virtual void deserialize (std::string command) throw (WrongCommandException);
		virtual GiveUpCommand* clone() const { return new GiveUpCommand(*this); }
	};
	struct OfferDrawCommand: public Command {
		static const std::string CLASS_NAME;
		static const std::string OFFER_DRAW_COMMAND;
		virtual std::string serialize () const;
		virtual void deserialize (std::string command) throw (WrongCommandException);
		virtual OfferDrawCommand* clone() const { return new OfferDrawCommand(*this); }
	};
	struct TerminationCommand: public Command {
		static const std::string CLASS_NAME;
		static const std::string TERMINATION_COMMAND;
		virtual std::string serialize () const;
		virtual void deserialize (std::string command) throw (WrongCommandException);
		virtual TerminationCommand* clone() const { return new TerminationCommand(*this); }
	};
	// Фабрика
	class Factory
	{
	public:
		Factory ():
			ex1 (nullptr),
			ex2 (nullptr),
			ex3 (nullptr),
			ex4 (nullptr),
			ex5 (nullptr)
		{
			ex1 = new Command ();
			ex2 = new Move ();
			ex3 = new GiveUpCommand ();
			ex4 = new OfferDrawCommand ();
			ex5 = new TerminationCommand ();
			set (Command::CLASS_NAME, ex1);
			set (Move::CLASS_NAME, ex2);
			set (GiveUpCommand::CLASS_NAME, ex3);
			set (OfferDrawCommand::CLASS_NAME, ex4);
			set (TerminationCommand::CLASS_NAME, ex5);
		}
		Command* get(std::string const& class_name) const throw (std::out_of_range);
		~Factory () {
			delete ex1;
			delete ex2;
			delete ex3;
			delete ex4;
			delete ex5;
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
		TerminationCommand *ex5;
	};
}
