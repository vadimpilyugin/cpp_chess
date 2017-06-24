#include "basic.h"

class ChessGame{
	private:
		Tile_content board[8][8];
		Piece_dark pieces[32];
		GameState state;
	public:
		Chessgame(){
			state=Going;
			board=new Tile_content[8][8];
			pieces=new Piece_dark[32];
		}
		~Chessgame(){
			if (board)
				delete board;
			if (pieces)
				delete pieces;
		}
		void Initialize(){
			

}


