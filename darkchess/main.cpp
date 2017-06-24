
#include "chessgame.h"
				
		
Move rawConstructMove(){
	Move res;
	printf("ENTER fromx fromy tox toy\n");
	scanf("%d %d %d %d",&res.from.x,&res.from.y,&res.to.x,&res.to.y);
	return res;
}			

int main(){
	ChessGame test;
	test.initialize();
	while(test.getState()==Going){
		test.updateVision();
		test.rawOutput(White);
		printf("\nWhitePOV\n\n\n");
		test.rawOutput(Black);
		printf("\nBlackPOV\n\n\n");
		if (test.getOrderPlayer()==White)
			printf("White's turn\n");
		else
			printf("Black's turn\n");
		Move newMove=rawConstructMove();
		test.doMove(newMove);
		test.updateVision();
	}
	return 0;
}


