#include "chess_log.h"

class ChessLog: IChessLog {
public:
	ChessLog (std::string log_string_): log_string (log_string_) {}
	virtual std::string getLogText () {
		return log_string;
	}

private:
	std::string log_string;
};