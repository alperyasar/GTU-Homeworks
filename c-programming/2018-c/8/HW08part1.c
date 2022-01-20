#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>
		/*p = penalty, s = snake, m = stairs, b = boost, t = trap*/
typedef enum {P = 1,S,M,B,T,start,finish } block;

struct block
{
	int data;
	block type;	
	char text[12];
	int pos_x,pos_y;
	int jump_x,jump_y;
	int zar_x,zar_y;				
};



int randomNumber(){							/*zar icin random sayi uretiyor*/
	return (rand() % 6) +1;
}

void init_game(struct block board[10][10]){				/*oyun ozelliklerini structure'a atıyor*/
	int i,j,konum,i1,j1;

	for(i = 0; i < 10; ++i){
		for(j = 0; j < 10; ++j){
			board[i][j].type = 0;
		}
	}

	for (i = 0; i < 10; ++i)
	{
		if(i%2==0){
			konum = 101 - ((i+1)*10);
			for (j = 0; j < 10; ++j)
			{	
				board[i][j].data = konum+j;
			}
		}	
		else{
			konum = 100 - (i*10);
			for (j = 0; j < 10; ++j)
			{	
				board[i][j].data = konum-j;
			}	
		}
	}
	for (i = 0; i < 10; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			if(board[i][j].data == 100){
				board[i][j].type = finish;
				strcpy(board[i][j].text,"100{Finish}");
			}

			else if(board[i][j].data == 1)
				board[i][j].type = start;						/*ozellikli kutulari belirliyor*/

			else if(board[i][j].data == 85 || board[i][j].data == 48 || board[i][j].data == 13){
				board[i][j].type = P;
				
			}

			else if (board[i][j].data == 99 || board[i][j].data == 98 || board[i][j].data == 73 || board[i][j].data == 63 ||
					 board[i][j].data == 60 || board[i][j].data == 45 || board[i][j].data == 25 || board[i][j].data == 6){	
				board[i][j].type = S;
			
			}

			else if(board[i][j].data == 89 || board[i][j].data == 76 || board[i][j].data == 69 || board[i][j].data == 57 ||
					board[i][j].data == 32 || board[i][j].data == 17 || board[i][j].data == 7){	
				board[i][j].type = M;
			}

			else if(board[i][j].data == 82 || board[i][j].data == 66 || board[i][j].data == 50 || board[i][j].data == 36 || board[i][j].data == 29)
			{	board[i][j].type = B;
			
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == board[i][j].data + 5){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;

						}
					}
				}

			}
			else if(board[i][j].data == 93 || board[i][j].data == 79 || board[i][j].data == 54 || board[i][j].data == 40)
			{	board[i][j].type = T;	
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == board[i][j].data - 5){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
			}
		}
	}
	for (i = 0; i <= 9; ++i)								/*ozellikli kutularda gidilmesi gereken degerleri atama yapıyor*/
	{
		for (j = 0; j <= 9; ++j)
		{
			if(board[i][j].data == 6){
				strcpy(board[i][j].text,"S{1}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 1){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 25){
				strcpy(board[i][j].text,"S{12}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 12){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 45){
				strcpy(board[i][j].text,"S{22}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 22){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 60){
				strcpy(board[i][j].text,"S{44}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 44){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 63){
				strcpy(board[i][j].text,"S{52}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 52){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			
			else if(board[i][j].data == 73){
				strcpy(board[i][j].text,"S{68}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 68){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 98){
				strcpy(board[i][j].text,"S{72}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 72){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 99){
				strcpy(board[i][j].text,"S{56}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 56){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 7){
				strcpy(board[i][j].text,"M{11}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 11){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 17){
				strcpy(board[i][j].text,"M{28}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 28){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 32){
				strcpy(board[i][j].text,"M{52}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 52){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 57){
				strcpy(board[i][j].text,"M{77}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 77){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 71){
				strcpy(board[i][j].text,"M{77}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 77){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 76){
				strcpy(board[i][j].text,"M{83}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 83){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
			else if(board[i][j].data == 89){
				strcpy(board[i][j].text,"M{94}");
				for (i1 = 0; i1 <= 9; ++i1)
				{
					for (j1 = 0; j1 <= 9; ++j1)
					{
						if(board[i1][j1].data == 94){
							board[i][j].jump_x = i1;
							board[i][j].jump_y = j1;
						}
					}
				}
					
			}
		}
	}


}

void display_game(struct block board[10][10]){
	int i,j;

	printf("\n");
	for (i = 0; i < 10; ++i)
	{
		printf("\n");
		for (j = 0; j < 10; ++j)
		{
			if(board[i][j].type == finish)			/*finish degerini yazdırıyor*/
				printf("%7d",board[i][j].data);

			else if(board[i][j].type == start)		/*start degerini yazdiriiyor*/	
				printf("%6d", board[i][j].data);

			else if(board[i][j].type == S){			/*S noktalarini bastıriyor*/
				printf("    S ");

			}

			else if(board[i][j].type == P)			/*P noktalarini bastıriyor*/
				printf("    P ");
			
			else if(board[i][j].type == M){			/*M noktalarini bastıriyor*/
				printf("    M ");
			}

			else if(board[i][j].type == B)			/*B noktalarini bastıriyor*/
				printf("    B ");
			
			else if(board[i][j].type == T)			/*T noktalarini bastıriyor*/
				printf("    T ");
			else 
				printf("%6d", board[i][j].data);	/*degerleri bastıriyor*/
		}
		printf("\n");
		if(i==0)
			printf("\t\t\t\t\t     {72}  {56} (finish)\n");			/*S ve M degerlerinin gonderdigi noktayı yazıyor*/
		else if(i == 1)
			printf("         {94}\n");
		else if(i == 2)
			printf("	       {68}              {83}\n");
		else if(i == 3)
			printf("         {77}\t\t\t\t     {52}\n");
		else if(i == 4)
			printf("\t\t\t\t       {77}\t         {44}\n");
		else if(i == 5)
			printf("\t\t\t         {22}\n");
		else if(i == 6)
			printf("         {52}\n");
		else if(i == 7)
			printf("\t\t\t         {12}\n");
		else if(i == 8)
			printf("\t\t\t\t       {28}\n");
		else if(i == 9)
			printf("\t\t     {11}  {1}\t\t\t\t(start)\n");
		
			
	}

}


int single_player(int x,int y,int count,struct block board[10][10]){
	int zar,i,j,x1,y1,k,l,tempcount,tempzar, tempdata1, tempdata2;
	zar = randomNumber();
	tempcount = count;
	if(board[x][y].data + zar > 100)				/*oyun 100blogunu asıyorsa hareket sayisini arttırıp tekrar aynı yerden oynuyor*/
	{
		count++;
		count = single_player(x,y,count,board);
	}
	else{
		for (i = 0; i <= 9; ++i)
		{

		 	for (j = 0; j <= 9; ++j)
		 	{													/*zar atıldıktan sonra hangi noktada olacaigini yaziyor*/
		 		
		 		if(board[i][j].data == board[x][y].data + zar){
		 			x1 = i;
		 			y1 = j;
		 			/*board[k][l].pos_x = i;
		 			board[k][l].pos_y = j;*/
		 		}											
			}												
		}

		tempzar = zar;
		tempdata1 = board[x][y].data;						/*bulundugu noktayi ve gidecegi noktayi belirlemek icin atama yapiyor*/
		tempdata2 = board[x1][y1].data;
		

	/*	x1 = board[k][l].pos_x;													
		y1 = board[k][l].pos_y;*/


		if(board[x1][y1].data == 100){						/*100 degerinde hareketi return ediyor*/
			printf("c =%3d z =%2d, konum =%2d   gidecegi yer :%3d\n",tempcount,tempzar,tempdata1, tempdata2);
			return count;
		}
		else if(board[x1][y1].type == P && board[x1][y1].data < 100){					/*p degerinde is hareketi arttiriyor ve tekrar ayni noktadan oynuyor*/
			count++;

			count = single_player(x,y,count,board);
		}
		else{
			if(board[x1][y1].type == S || board[x1][y1].type == M || board[x1][y1].type == B || board[x1][y1].type == T){
				x = board[x1][y1].jump_x;					/*Belirli noktalarda gidecegi degeri alıyor ve ona gore gidilmesi gereken bloga gidiyor*/
				y = board[x1][y1].jump_y;

			}
			else{											/*ozellikli blokta degilse gitmesi gereken bloga gidiyor*/
				x = x1;
				y = y1;
			} 

			count ++;
			count = single_player(x,y,count,board);							/*count'u arttırıp tekrar ediyor*/
		}
		printf("c =%3d z =%2d, konum =%2d   gidecegi yer :%3d\n",tempcount,tempzar,tempdata1, tempdata2);		/*sondan basa yazdiriyor*/
	}
	return count;
}

void multiplayer(int x,int y,int count,struct block board[10][10]){
	int player1,player2;
													/*Multiplayer oyuncu single player'daki islemleri yapiyor ve daha az hamlede */
	player1 = single_player(x,y,count,board);		/*oyunu bitiren oyunu kazaniyor*/
	printf("\nPlayer 1 :%d\n\n", player1);
	count = 0;
	player2 = single_player(x,y,count,board);
	printf("\nPlayer 2 :%d\n\n", player2);
	if (player1 < player2)
	{
		printf("Player 1 is win!!!\n");
	}
	else if (player2 < player1)
	{
		printf("Player 2 is win!!!\n");
	}
	else{
		printf("The game is equal!!!\n");
	}
}

int main()
{
	struct block board[10][10]; 
	int move,count;
	init_game(board);
	display_game(board);
	count = 0;
	srand(time(NULL));
	count = single_player(9,9,count,board);
	printf("\n%d\n\n", count);
	count = 0;
	multiplayer(9,9,count,board);

	return 0;
}