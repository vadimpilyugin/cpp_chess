#include "dark.h"

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
		void checkVictory(Color color);
		void updateVision();
		void rawOutput(Color color);
		void initialize();
		bool checkSingle(Tile start,int dx,int dy,Color color);
		std::vector<Tile> checkLine(Tile start,int dx,int dy,Color color);
		void updatePieceVision(int num);
};
//READ ABOUT VIRTUAL FUNCTIONS


