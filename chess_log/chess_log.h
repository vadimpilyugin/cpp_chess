#include <string>

#include "chess_observer.h"

class IChessLog: IChessObserver {
public:
	virtual std::string getLogText () = 0;
};