#include <stdio.h>

typedef enum {white_man, black_man, white_king, black_king, empty} piece;

typedef enum {white = 10, black = 20} player;

void init_board(piece board[][8]);
int control_capture(piece board[][8], int from_x, int from_y, player p);/*kendi tanımladığım otomatik yeme yeme fonksiyonu*/
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y,player p);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
void sample_game_2();

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

}/*
int control_capture(piece board[][8],player p){
	int i,j,k,c=0;	*/												/*if there is any capture user must be play it*/
	
/*	if(p==white){
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(board[i][j]==white_man){
					if((board[i-1][j]==black_man || board[i-1][j] == black_king) && board[i-2][j]==empty) 
						return 1;
					else if((board[i][j-1]==black_man || board[i][j-1] == black_king) && board[i][j-2]==empty)
						return 1;
					else if((board[i][j+1]==black_man || board[i][j+1] == black_king)&& board[i][j+2]==empty)
						return 1;					
				}
				else if(board[i][j]==white_king){
					for(k=j;k<8;k++){
						if(board[i][k] == black_man || board[i][k] == black_king)
							c++;
						if(c==1 && board[i][k+1] == empty)
							return 1;
						else if(c==1 && board[k+1][j] == empty)
							return 1;
					}	
					c=0;	
					for(k=j;k<8;k--){
						if(board[i][k] == black_man || board[i][k] == black_king)
							c++;

						if(c==1 && board[i][k-1] == empty)
							return 1;
						
						else if(c==1 && board[k-1][j] == empty)
							return 1;
					}
				}	
		
			}
		}
	}

	else if(p==black){	
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(board[i][j]==black_man){
					if((board[i+1][j]==white_man || board[i+1][j]==white_king) && board[i+2][j]==empty)
						return 1;
					else if((board[i][j-1]==white_man || board[i][j-1]==white_king) && board[i][j-2]==empty)
						return 1;
					else if((board[i][j+1]==white_man || board[i][j+1]==white_king) && board[i][j+2]==empty)
						return 1;					
				}
				else if(board[i][j]==black_king){
					for(k=j;k<8;k++){
						if(board[i][k] == black_man || board[i][k] == black_king)
							c++;
						if(c==1 && board[i][k+1] == empty)
							return 1;
						else if(c==1 && board[k+1][j] == empty)
							return 1;
					}	
					c=0;		
					for(k=j;k<8;k--){
						if(board[i][k] == black_man || board[i][k] == black_king)
							c++;
						if(c==1 && board[i][k-1] == empty)
							return 1;
						else if(c==1 && board[k-1][j] == empty)
							return 1;
					}
				}	
		
			}
		}
	}
	return 0;
}


int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){
	int i,b=0,c=0,king_control=0;
	
	control_capture(board,p);
	
	if(p == white){
		if(board[from_x][from_y] == black_man || board[from_x][from_y] == black_king)
			return -1;
	}
	else if(p == black){
		if(board[from_x][from_y] == white_man || board[from_x][from_y] == white_king){
			return -1;
		}
	}
	
	else if(control_capture(board,p)==1 && p == white){
		if(board[from_x][from_y] == white_man){
			if((board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king) && to_x == from_x-2 && to_y == from_y &&  					board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= white_man;
				board[from_x-1][from_y] = empty;
				board[from_x][from_y]   = empty;
			}
			else if((board[from_x][from_y -1] == black_man || board[from_x][from_y-1] == black_king) && to_x == from_x && to_y == from_y-2 					  && board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= white_man;
				board[from_x][from_y-1] = empty;
				board[from_x][from_y]   = empty;
			}
			else if((board[from_x][from_y +1] == black_man || board[from_x][from_y+1] == black_king) && to_x == from_x && to_y == from_y+2 					  && board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= white_man;
				board[from_x][from_y+1] = empty;
				board[from_x][from_y]   = empty;
			}
		}
		else if(board[from_x][from_y] == white_king){
			if(from_y == to_y){
				for(i=from_x;i<to_x;i++){
					if(board[i][from_y] == black_man || board[i][from_y] == black_king){				
						c++;
						b=i;
					}
				}
				for(i=from_x;i>to_x;i--){
					if(board[i][from_y] == black_man || board[i][from_y] == black_king){				
						c++;
						b=i;
					}
				}
				if(c==1){
					board[from_x][from_y] = empty;
					board[b][from_y]	  = empty;
					board[to_x][to_y] 	  = white_king;
				}
				
			}
			else if(from_x == to_x){
				for(i=from_y;i<to_y;i++){
					if(board[from_x][i] == black_man || board[from_x][i] == black_king){				
						c++;
						b=i;
					}
				}
				for(i=from_x;i>to_x;i--){
					if(board[from_x][i] == black_man || board[from_x][i] == black_king){				
						c++;
						b=i;
					}
				}
				if(c==1){
					board[from_x][from_y] = empty;
					board[from_x][b]	  = empty;
					board[to_x][to_y] 	  = white_king;
				}
			}
		}
	}
	else if(control_capture(board,p)==1 && p == black){
		if(board[from_x][from_y] == black_man){
			if((board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king) && to_x == from_x+2 && to_y == from_y &&    					board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= black_man;
				board[from_x+1][from_y] = empty;
				board[from_x][from_y]   = empty;
			}
			else if((board[from_x][from_y -1] == white_man || board[from_x][from_y-1] == white_king) && to_x == from_x && to_y == from_y-2 					  && board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= black_man;
				board[from_x][from_y-1] = empty;
				board[from_x][from_y]   = empty;
			}
			else if((board[from_x][from_y +1] == white_man || board[from_x][from_y+1] == white_king) && to_x == from_x && to_y == from_y+2 					  && board[to_x][to_y] == empty){
				
				board[to_x][to_y] 		= black_man;
				board[from_x][from_y+1] = empty;
				board[from_x][from_y]   = empty;
			}
		}
		else if(board[from_x][from_y] == black_king){
			if(from_y == to_y){
				for(i=from_x;i<to_x;i++){
					if(board[i][from_y] == white_man || board[i][from_y] == white_king){				
						c++;
						b=i;
					}
				}
				for(i=from_x;i>to_x;i--){
					if(board[i][from_y] == white_man || board[i][from_y] == white_king){				
						c++;
						b=i;
					}
				}
				if(c==1){
					board[from_x][from_y] = empty;
					board[b][from_y]	  = empty;
					board[to_x][to_y] 	  = black_king;
				}
				
			}
			else if(from_x == to_x){
				for(i=from_y;i<to_y;i++){
					if(board[from_x][i] == white_man || board[from_x][i] == white_man){				
						c++;
						b=i;
					}
				}
				for(i=from_x;i>to_x;i--){
					if(board[from_x][i] == white_man || board[from_x][i] == white_man){				
						c++;
						b=i;
					}
				}
				if(c==1){
					board[from_x][from_y] = empty;
					board[from_x][b]	  = empty;
					board[to_x][to_y] 	  = black_king;
				}
			}
		}		
	}
		if(p==white){
			if(board[from_x][from_y]==white_man){
				if(to_x == from_x -1 && to_y == from_y){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==white_man;
				}
				else if(to_x == from_x && to_y == from_y -1){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==white_man;
				}
				else if(to_x == from_x && to_y == from_y +1){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==white_man;
				}
			}
			else if(board[from_x][from_y]==white_king){
				if(from_x==to_x && from_y != to_y){
					for(i=from_y;i>to_y;i--){
						if(board[to_x][i]== black_man || board[to_x][i] == black_king)
							king_control++;
					}
					for(i=from_y;i<to_y;i++){
						if(board[to_x][i]== black_man || board[to_x][i] == black_king)
							king_control++;
					}
					if(king_control == 0){
						board[from_x][from_y]==empty;
						board[to_x][to_y]==white_king;
					}
				}
				else if(from_y==to_y && from_x != to_x){
					for(i=from_x;i>to_x;i--){
						if(board[i][to_y]== black_man || board[i][to_y] == black_king)
							king_control++;
					}

					for(i=from_y;i<to_y;i++){
						if(board[i][to_y]== black_man || board[i][to_y] == black_king)
							king_control++;
					}
					if(king_control == 0){
						board[from_x][from_y]==empty;
						board[to_x][to_y]==white_king;
					}
				}
			}
		}

		else if(p==black){
			if(board[from_x][from_y]==black_man){
				if(to_x == from_x +1 && to_y == from_y){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==black_man;
				}	
				else if(to_x == from_x && to_y == from_y -1){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==black_man;
				}
				else if(to_x == from_x && to_y == from_y +1){
					board[from_x][from_y]==empty;
					board[to_x][to_y]==black_man;
				}	
			}
			else if(board[from_x][from_y]==black_king){
				if(from_x==to_x && from_y != to_y){
					for(i=from_y;i>to_y;i--){
						if(board[to_x][i]== white_man || board[to_x][i] == white_king)
							king_control++;
					}
				
					for(i=from_y;i<to_y;i++){
						if(board[to_x][i]== white_man || board[to_x][i] == white_king)
							king_control++;
					}
					if(king_control == 0){
						board[from_x][from_y]==empty;
						board[to_x][to_y]==black_king;
					}
				}
				else if(from_y==to_y && from_x != to_x){
					for(i=from_x;i>to_x;i--){
						if(board[i][to_y]== white_man || board[i][to_y] == white_king)
							king_control++;
					}
					for(i=from_y;i<to_y;i++){
						if(board[i][to_y]== white_man || board[i][to_y] == white_king)
							king_control++;
					}
					if(king_control == 0){
						board[from_x][from_y]==empty;
						board[to_x][to_y]==black_king;
					}
				}
			}	
		}

	
	return 0;
}*/

int control_capture(piece board[][8], int from_x, int from_y ,player p)/*çağırıldığı noktadaki otomatik yemeleri yapar*/
{
	int i,king ,x ,y ,flag , count , flag_2 , count_2 = 0;
	king = 0;
	flag = 0;

	if (p == white)/*eğer beyaz taşlar için oynama yapılacaksa bu koşula girer*/
	{
		if (board[from_x][from_y] == white_king)/*white_king in otomatik yeme  ihtimalleri*/
		{
			if (board[from_x][from_y-1] != white_man && board[from_x][from_y-1] != white_king )/*sola taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x][from_y-2] == empty && (board[from_x][from_y-1] == black_man || board[from_x][from_y-1] == black_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y-1] = empty;
					board[from_x][from_y-2] = white_king;
					from_y = from_y - 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x][from_y-i] == empty && from_y > 1)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x][from_y-1-i] == empty && (board[from_x][from_y-i] == black_man || board[from_x][from_y-i] == black_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;/*atamaları gerçekleştirdim*/
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-2] = white_king;
						from_y = from_y - 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}
			if (board[from_x][from_y+1] != white_man && board[from_x][from_y+1] != white_king )/*sağa taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x][from_y+2] == empty && (board[from_x][from_y+1] == black_man || board[from_x][from_y+1] == black_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y+2] = white_king;
					from_y = from_y + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
		     	{
					while(board[from_x][from_y+i] == empty && from_y < 6)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x][from_y+1+i] == empty && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king))/*aralarında bosluk olsa dahi yer*/
					{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y+2] = white_king;
					from_y = from_y + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}
	
			if (board[from_x][from_y-1] != white_man && board[from_x][from_y-1] != white_king )/*yukarı taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x-2][from_y] == empty && (board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king))/*yanındaki taşı yer*//*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x-1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x-2][from_y] = white_king;
					from_x = from_x - 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			else
				{
					while(board[from_x-i][from_y] == empty && from_x > 1)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x-1-i][from_y] == empty && (board[from_x-i][from_y] == black_man || board[from_x-i][from_y] == black_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x-1][from_y] = empty;/*atamaları gerçekleştirdim*/
						board[from_x-2][from_y] = white_king;
						from_x = from_x - 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}											

			if (board[from_x][from_y+1] != white_man && board[from_x][from_y+1] != white_king )/*aşağı taraf atlayarak yeme*/
	    	{
				i = 1;
				if (board[from_x+2][from_y] == empty && (board[from_x+1][from_y] == black_man || board[from_x+1][from_y] == black_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x+1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x+2][from_y] = white_king;
					from_x = from_x + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x+i][from_y] == empty && from_x < 6)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x+1+i][from_y] == empty && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x+1][from_y] = empty;/*atamaları gerçekleştirdim*/
						board[from_x+2][from_y] = white_king;
						from_x = from_x + 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}
			return 0;
		
		}/*white_king bitimi*/


		else if (board[from_x][from_y] == white_man)/*white_man in otomatik yeme  ihtimalleri*/
		{
			if (from_y > 1 && board[from_x][from_y - 2] == empty)/*sola taraf atlayarak yeme*/
			{
				if (board[from_x][from_y-1] == black_man || board[from_x][from_y-1] == black_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y-1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y-2] = white_man;
					from_y = from_y - 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			}
			if (from_y < 6 && board[from_x][from_y + 2] == empty)/*sağa taraf atlayarak yeme*/
			{
				if (board[from_x][from_y+1] == black_man || board[from_x][from_y+1] == black_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y+2] = white_man;
					from_y = from_y + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			}				
			if (board[from_x-2][from_y] == empty && from_x > 1)/*ileriye doğru otomatik olarak yeme*/
			{
				if (board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x-1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x-2][from_y] = white_man;
					from_x = from_x - 2;
					if (from_x == 0)/*king olama durumu*/
					{
						board[from_x][from_y] = white_king;
						p = white_king;
					}
					return control_capture(board ,from_x ,from_y ,p);	/*recursion olarak fonksiyon yeniden çağırılır*/		
				}
			}
			return 0;

		}/*white_man kapama*/		


	}/*white kapama*/

	else if (p == black)
	{
		if (board[from_x][from_y] == black_king)/*black_king in otomatik yeme  ihtimalleri*/
		{
			if (board[from_x][from_y-1] != black_man && board[from_x][from_y-1] != black_king )/*sola taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x][from_y-2] == empty && (board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y-1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y-2] = black_king;
					from_y = from_y - 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x][from_y-i] == empty && from_y > 1)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x][from_y-1-i] == empty && (board[from_x][from_y-i] == white_man || board[from_x][from_y-i] == white_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;/*atamaları gerçekleştirdim*/
						board[from_x][from_y-2] = black_king;
						from_y = from_y - 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}
			if (board[from_x][from_y+1] != black_man && board[from_x][from_y+1] != black_king )/*sağa taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x][from_y+2] == empty && (board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y+2] = black_king;
					from_y = from_y + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x][from_y+i] == empty && from_y < 6)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x][from_y+1+i] == empty && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
						board[from_x][from_y+2] = black_king;
						from_y = from_y + 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}	
			if (board[from_x][from_y-1] != black_man && board[from_x][from_y-1] != black_king )/*yukarı taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x-2][from_y] == empty && (board[from_x-1][from_y] == white_man || board[from_x-1][from_y] == white_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x-1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x-2][from_y] = black_king;
					from_x = from_x - 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x-i][from_y] == empty && from_x > 1)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x-1-i][from_y] == empty && (board[from_x-i][from_y] == white_man || board[from_x-i][from_y] == white_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x-1][from_y] = empty;/*atamaları gerçekleştirdim*/
						board[from_x-2][from_y] = black_king;
						from_x = from_x - 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}											
			if (board[from_x][from_y+1] != black_man && board[from_x][from_y+1] != black_king )/*aşağı taraf atlayarak yeme*/
			{
				i = 1;
				if (board[from_x+2][from_y] == empty && (board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king))/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x+1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x+2][from_y] = black_king;
					from_x = from_x + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
				else
				{
					while(board[from_x+i][from_y] == empty && from_x < 6)/*aradaki boşlukları saymak için kullandım*/
					{
						i = i + 1;
					}
					if (board[from_x+1+i][from_y] == empty && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king))/*aralarında bosluk olsa dahi yer*/
					{
						display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
						board[from_x][from_y] = empty;
						board[from_x+1][from_y] = empty;/*atamaları gerçekleştirdim*/
						board[from_x+2][from_y] = black_king;
						from_x = from_x + 2;
						return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
					}
				}
			}
			return 0;											
		}/*black_king kapama*/

		else if (board[from_x][from_y] ==black_man)/*black_man in otomatik yeme  ihtimalleri*/
		{
			if (from_y > 1 && board[from_x][from_y - 2] == empty)/*sola taraf atlayarak yeme*/
			{
				if (board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y-1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y-2] = black_man;
					from_y = from_y - 2;
					return control_capture(board ,from_x ,from_y ,p);	/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			}
			if (from_y < 6 && board[from_x][from_y + 2] == empty)/*sağa taraf atlayarak yeme*/
			{
				if (board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = empty;/*atamaları gerçekleştirdim*/
					board[from_x][from_y+2] = black_man;
					from_y = from_y + 2;
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			}				
			if (board[from_x+2][from_y] == empty)/*ileriye doğru otomatik olarak yeme*/
			{
				if (board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king)/*yanındaki taşı yer*/
				{
					display_board(board);/*kendinden önceki yenmiş olan taşıda ekrana yazar*/
					board[from_x][from_y] = empty;
					board[from_x+1][from_y] = empty;/*atamaları gerçekleştirdim*/
					board[from_x+2][from_y] = black_man;
					from_x = from_x + 2;
					if (from_x == 7)/*king olama durumu*/
					{
						board[from_x][from_y] = black_king;
						p = black_man;
					}
					return control_capture(board ,from_x ,from_y ,p);/*recursion olarak fonksiyon yeniden çağırılır*/
				}
			}
			return 0;

		}/*black_man kapama*/
	}


}

/*hareket edilecek yerin gidip gidemeyeceği veya yiyip yiyemeyeceği burada gerçekleşir*/
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y,player p)
{
	int i ,king ,x ,y;
	int oto_rtrn;
	king = 0;

	if (p == white)/*seçilen karakter taşı beyaz ise bu döngüye girer*/
	{
		if (board[from_x][from_y] == white_king) /*white_king hareket ettirme*/
		{
			if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
				return -2;
			}
			else if (from_x < to_x && to_y == from_y)/*aşağı hareket*/
			{
				for (i = 1; i <= to_x - from_x; ++i)
				{
					if (board[from_x + i][from_y] == black_man || board[from_x + i][from_y] == black_king)
					{
						king = king + 1;
						x = from_x + i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[x][from_y] = empty;
					board[to_x][to_y] = white_king;/*atamaları yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else if (from_x > to_x && to_y == from_y)/*yukarıya hareket*/
			{
				for (i = 1; i <= from_x - to_x; ++i)
				{
					if (board[from_x - i][from_y] == black_man || board[from_x - i][from_y] == black_king)
					{
						king = king + 1;
						x = from_x - i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_king;/*atamaları yaptım*/
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[x][from_y] = empty;
					board[to_x][to_y] = white_king;/*atamaları yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;	
			}
			else if (from_x == to_x && to_y < from_y)/*sağa hareket*/
			{
				for (i = 1; i <= from_y - to_y; ++i)
				{
					if (board[from_x][from_y - i] == black_man || board[from_x][from_y - i] == black_king)
					{
						king = king + 1;
						x = from_y - i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[from_x][x] = empty;
					board[to_x][to_y] = white_king;/*atamaları yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else if (from_x == to_x && to_y > from_y)/*sola hareket*/
			{
				for (i = 1; i <= to_y - from_y ; ++i)
				{
					if (board[from_x][from_y + i] == black_man || board[from_x][from_y + i] == black_king)
					{
						king = king + 1;
						x = from_y + i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[from_x][x] = empty;
					board[to_x][to_y] = white_king;/*atamaları yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else/*oynanmak istenen yer boş değilse oynanamaz der*/
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
				return -2;
			}
		}	

		else if (board[from_x][from_y] == white_man)
		{
			if (from_x < to_x)/*geriye hareket etmeyi önlemek için kullandım*/
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
				return -2;
			} 


			



			/*tek hareket olarak white_man hareketi*/			
			else if (from_x == to_x + 1 && from_y == to_y)/*düz ilerleme*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yerin boş olmadığı durumlardır */
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");					
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa atamayı yapar*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_man;/*atamaları yaptım*/
					if (to_x == 0)
					{
						board[to_x][to_y] = white_king;
					}					
					return 0;
				}
			}
			else if (from_x == to_x && from_y == to_y - 1)/*sağa hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istene yer boş değilse buraya girer*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa atamayı yapar*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_man;/*atamaları yaptım*/
					
					return 0;
				}
			}
			else if (from_x == to_x && from_y == to_y + 1) /*sola hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa atamayı yapar*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = white_man;/*atamaları yaptım*/
					
					return 0;
				}
			}


			/*yemek için kullanılan white_man*/
			else if (from_x == to_x + 2 && from_y == to_y )/*düz ilerleme*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yerin boş olmadığı durumlardır */
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");					
					return -2;
				}

				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;
						from_x = from_x - 1;
						board[from_x][from_y] = empty;/*atamaları yaptım*/
						board[to_x][to_y] = white_man;
						oto_rtrn = control_capture(board ,to_x ,to_y ,p);
						if (to_x == 0)
						{
							board[to_x][to_y] = white_king;
						}
						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}
			else if (from_x == to_x && from_y == to_y - 2)/*sağa hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yerin boş olmadığı durumlardır */
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");					
					return -2;
				}

				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x][from_y + 1] == black_man || board[from_x][from_y + 1] == black_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;
						from_y = from_y + 1;						
						board[from_x][from_y] = empty;/*atamaları yaptım*/
						board[to_x][to_y] = white_man;
						oto_rtrn = control_capture(board ,to_x ,to_y ,p);
						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}
			else if (from_x == to_x && from_y == to_y + 2) /*sola hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x][from_y - 1] == black_man || board[from_x][from_y - 1] == black_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;
						from_y = from_y - 1;
						board[from_x][from_y] = empty;/*atamaları yaptım*/
						board[to_x][to_y] = white_man;
						oto_rtrn = control_capture(board ,to_x ,to_y ,p);
						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}	

			else
			{
				printf("\nkendi taşınızı oynayınız.\n");			
				return -1;
			}	
		}			
		
	}

	if (p == black)
	{
		if (board[from_x][from_y] == black_king)
		{
			if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
				return -2;
			}
			else if (from_x < to_x && to_y == from_y)/*aşağı hareket*/
			{
				for (i = 1; i <= to_x - from_x; ++i)
				{
					if (board[from_x + i][from_y] == white_man || board[from_x + i][from_y] == white_king)
					{
						king = king + 1;
						x = from_x + i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_king;/*atamayı yaptım*/
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;/*atamayı yaptım*/
					board[x][from_y] = empty;
					board[to_x][to_y] = black_king;
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else if (from_x > to_x && to_y == from_y)/*yukarıya hareket*/
			{
				for (i = 1; i <= from_x - to_x; ++i)
				{
					if (board[from_x - i][from_y] == white_man || board[from_x - i][from_y] == white_king)
					{
						king = king + 1;
						x = from_x - i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[x][from_y] = empty;
					board[to_x][to_y] = black_king;/*atamayı yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;	
			}
			else if (from_x == to_x && to_y < from_y)/*sağa hareket*/
			{
				for (i = 1; i <= from_y - to_y; ++i)
				{
					if (board[from_x][from_y - i] == white_man || board[from_x][from_y - i] == white_king)
					{
						king = king + 1;
						x = from_y - i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[from_x][x] = empty;
					board[to_x][to_y] = black_king;/*atamayı yaptım*/
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else if (from_x == to_x && to_y > from_y)/*sola hareket*/
			{
				for (i = 1; i <= to_y - from_y ; ++i)
				{
					if (board[from_x][from_y + i] == white_man || board[from_x][from_y + i] == white_king)
					{
						king = king + 1;/*atamayı yaptım*/
						x = from_y + i;
					}
				}
				if (king == 0)/*arada yenecek taş yoksa buraya girer*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_king;
					return 0;
				}
				else if (king == 1)/*arada yenecek taş varsa buraya girer*/
				{
					board[from_x][from_y] = empty;/*atamayı yaptım*/
					board[from_x][x] = empty;
					board[to_x][to_y] = black_king;
					oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/
					return 0;
				}	
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");							
				return -2;
			}
			else
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
				return -2;
			}
		}

		else if (board[from_x][from_y] == black_man)/*eğer seçilen yer black_man ise buraya girer*/
		{
			if (from_x > to_x)/*geriye hareket etmeyi önlemek için kullandım*/
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");				
				return -2;
			} 	



			/*düz ilerleme için black_man */
			else if (from_x == to_x - 1 && from_y == to_y)/*düz ilerleme*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_man;/*atamayı yaptım*/
					if (to_x == 7)
					{
						board[to_x][to_y] = black_king;/*atamayı yaptım*/
					}					
					return 0;
				}
			}
			else if (from_x == to_x && from_y == to_y - 1)/*sağa hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");		
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gidilecek yer boşsa atamaları yapar*/
				{
					board[from_x][from_y] = empty;
					board[to_x][to_y] = black_man;/*atamayı yaptım*/
					
					return 0;
				}
			}
			else if (from_x == to_x && from_y == to_y + 1) /*sola hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");					
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gidilecek yer boşsa atamaları yapar*/
				{
					board[from_x][from_y] = empty;/*atamayı yaptım*/
					board[to_x][to_y] = black_man;

					return 0;
				}
			}


			/*yeme için black_man*/
			else if (from_x == to_x - 2 && from_y == to_y)/*düz ilerleme*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yerin boş olmadığı durumlardır */
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");					
					return -2;
				}

				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;
						from_x = from_x + 1;						
						board[from_x][from_y] = empty;
						board[to_x][to_y] = black_man;/*atamayı yaptım*/

						oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/

						if (to_x == 7)/*king olma durumu*/
						{
							board[to_x][to_y] = black_king;
						}
						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}
			else if (from_x == to_x && from_y == to_y - 2) /*sağa hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x][from_y + 1] == white_man || board[from_x][from_y + 1] == white_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;
						from_y = from_y + 1;						
						board[from_x][from_y] = empty;/*atamayı yaptım*/
						board[to_x][to_y] = black_man;

						oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/

						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}
			else if (from_x == to_x && from_y == to_y + 2) /*sola hareket*/
			{
				if (board[to_x][to_y] != empty)/*oynanmak istenen yer boş değilse oynanamaz der*/
				{
					printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");
					return -2;
				}
				else if (board[to_x][to_y] == empty)/*gideceği yer boş olursa kontrollere girer*/
				{
					if (board[from_x][from_y - 1] == white_man || board[from_x][from_y - 1] == white_king)/*yeme olayı burada gerçekleşir*/
					{
						board[from_x][from_y] = empty;/*atamayı yaptım*/
						from_y = from_y - 1;						
						board[from_x][from_y] = empty;
						board[to_x][to_y] = black_man;/*atamayı yaptım*/

						oto_rtrn = control_capture(board ,to_x ,to_y ,p);/*geldiği yerde yiyebileceği taşlar varmı diye kontrol eder.varsa yer*/

						return 0;
					}
					else 				
					{
						return -2;
					}
				}
			}			


			else
			{
				printf("\ntaşınızın kordinata oynama ihtimali yoktur oynayamazsınız.Tekrar secim yapınız.\n");				
				return -2;
			}
		}

		else
		{
			printf("\nkendi taşınızı oynayınız.\n");			
			return -1;
		}
		
	}
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
		if(p%black==white)
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
	sample_game_2();
	return 0;
}
