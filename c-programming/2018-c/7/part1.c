#include <stdio.h>

typedef enum {white_man, black_man, white_king, black_king, empty} piece;

typedef enum {white = 10, black = 20} player;

void init_board(piece board[][8]){
	int i,j;
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){					/*assign 2. and 3. row black men*/
			if(i==1 || i==2)
				board[i][j]=black_man;		/*assign 2. and 3. row white men*/
			else if(i==5 || i==6)
				board[i][j]=white_man;
		
			else
				board[i][j]=empty;
		}
	}

}

int capture_control(piece board[][8], int from_x, int from_y, int to_x, int to_y){


}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){
	
	return 0;
}


int check_end_of_game(piece board[][8]){
	int i,j,w=0,b=0;

	for(i=0;i<8;i++){							
		for(j=0;j<8;j++){
			if(board[i][j]==black_man || board[i][j]==black_king)
				w++;
		}
	}
	if(w==0)
		return white;	
	for(i=0;i<8;i++){							
		for(j=0;j<8;j++){
			if(board[i][j]==white_man || board[i][j]==white_king)
				b++;
		}
	}
	if(b==0)
		return black;
	return -1;
}

void display_board(piece board[][8]){
	int	i,j;										/*‘-‘: Empty squares.			*/
													/*‘b’: The regular black pieces.*/
													/*‘B’: The black kings.			*/
													/*‘w’: The regular white pieces.*/
	for(i=0;i<8;i++){								/*‘W’: The white kings.			*/
		for(j=0;j<8;j++){
			if(board[i][j]==black_man)
				printf("b");
			else if(board[i][j]==black_king)
				printf("B");		
			else if(board[i][j]==white_man)
				printf("w");
			else if(board[i][j]==white_king)
				printf("W");						
			else
				printf("-");
		
		}
		printf("\n");
	}

}

void sample_game_1(){
	piece board[8][8];
	
	int from_x,from_y,to_x,to_y;
	player p=white;
	
	init_board(board);
	display_board(board);
	
	while(check_end_of_game(board) == -1){
		printf("enter x : ");
		scanf("%d",&from_x);
		printf("enter y : ");
		scanf("%d",&from_y);
		printf("enter to x : ");
		scanf("%d",&to_x);
		printf("enter to y : ");
		scanf("%d",&to_y);
		
		move(board, from_x, from_y, to_x, to_y, p);
		if(move(board, from_x, from_y, to_x, to_y, p) == -1)
			printf("It's not your move!!\n");
		else if(move(board, from_x, from_y, to_x, to_y, p) == -2)
			printf("you can not this move!!\n");	
		else if(move(board, from_x, from_y, to_x, to_y, p) == 0){
			display_board(board);
			p += white;
		}
		if(white == p%black)
			p=white;
		else
			p=black;
			
	}
	
	if(check_end_of_game(board) == white)
		printf("White wins the game");
	
	else if(check_end_of_game(board) == black)
		printf("Black wins the game");
}

void sample_game_2(){
	piece board[8][8];
	int i,j;
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(i=1 && j >= 2 && j <= 6)
				board[i][j] = black_man;
			else if(i=2 && j != 0 && j != 5)
				board[i][j] = black_man;
			else if(i=3 && j != 3 && j != 6 && j != 4)
				board[i][j] = black_man;
			else if(i=4 && j == 5)
				board[i][j] = black_man;
			else if(i=4 && ((j >= 2 && j <= 4) || (j >= 6 && j <= 7)))
				board[i][j] = white_man;
			else if(i=5 && j != 5)
				board[i][j] = white_man;
			else if(i=6 && j >= 2 && j <= 5)
				board[i][j] = white_man;				
		}
	}
	display_board(board);
	
	move(board,5,1,4,1,white);
	display_board(board);
	move(board,3,1,5,1,black);
	display_board(board);
	move(board,4,3,3,3,white);
	display_board(board);
	move(board,4,5,4,3,black);
	display_board(board);
	move(board,4,3,4,1,black);
	display_board(board);
	move(board,3,3,3,1,white);
	display_board(board);
	move(board,3,1,1,1,white);
	display_board(board);
	move(board,1,2,1,0,black);
	display_board(board);
	move(board,5,3,4,3,white);
	display_board(board);
	move(board,5,1,5,3,black);
	display_board(board);
	move(board,5,3,5,5,black);
	display_board(board);
	move(board,5,5,5,7,black);
	display_board(board);
	move(board,4,3,3,3,white);
	display_board(board);
	move(board,2,3,4,3,black);
	display_board(board);
	move(board,5,6,5,5,white);
	display_board(board);
	move(board,7,5,4,5,black);
	display_board(board);
	move(board,4,6,4,4,white);
	display_board(board);
	move(board,4,4,4,2,white);
	display_board(board);
	move(board,4,2,0,2,white);
	display_board(board);
	move(board,4,0,2,0,white);
	display_board(board);
	move(board,2,0,0,0,white);
	display_board(board);
	
	
}
int main(){
	
	sample_game_1();
//	sample_game_2();
	return 0;
}
