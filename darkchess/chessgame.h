#include "dark.h"
#include "stdio.h"

class ChessGame/*:public IDarkChessGame */{
	private:
		Tile_content** board;
		Piece_dark* pieces;
		GameState state;
		Color turn;
	public:
		ChessGame();
		~ChessGame();
		GameState getState();
		Color getOrderPlayer();
		Piece getPieceAtTile(Tile tile);
		bool doMove(Move move);
		std::vector<Tile> getMoveTiles(Piece piece);
		std::vector<Tile> getAttackTiles(Piece piece);
		std::vector<Tile> getHiddenTiles(Player player);
		std::vector<Piece> getConvertionPieces(Player player);
//METHODS BELOW WILL BE PRIVATE CAUSE NOBODY ELSE WILL NEED THEM
   		void forcedMove(Tile from, Tile to);
   		void doCastling(Piece king,bool isShort);
		void checkVictory(Color color);
		void updateVision();
		void rawOutput(Color color);
		void initialize();
		bool checkSingle(Tile start,int dx,int dy,Color color);
		std::vector<Tile> checkLine(Tile start,int dx,int dy,Color color);
		bool checkCastling(int kingnum,bool isShort);
		void prepareCastling(Tile* rookfrom, Tile * rookto,Tile* kingfrom,Tile* kingto,Color color, bool isShort);
		void updatePieceVision(int num);
};
//READ ABOUT VIRTUAL FUNCTIONS


