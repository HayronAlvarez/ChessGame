#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#define BLACK_TEXT         "\x1b[30m"
#define WHITE_TEXT         "\x1b[37m"
#define BLACK_BACKGROUND   "\x1b[40m"
#define WHITE_BACKGROUND   "\x1b[47m"
#define ANSI_RESET         "\x1b[0m"

struct square{
	int color; //0=empty, 1=white, -1 = black
	int piece; 
} board[8][8];

void fillBoard()
{
	FILE * fPointer;
	fPointer = fopen("board.csv","r");
	char singleLine[50];
		
	
	char* token;
		
	for(int i = 0; i < 8; i++)//while(!feof(fPointer))
	{
		fgets(singleLine,50,fPointer);	
		token = strtok(singleLine,",");
		
		
		for(int j=0; j<8; j++)//while(token != NULL)
		{
			if(*token!= 10)
			{
				
				if( (((int)(*token) == 45) && ((int)*(token+1) == 49)) || ((int)(*token) == 45) && ((int)*(token+1) == 50)){
					board[i][j].color = -1;
					if(*(token+1)==49)
					board[i][j].piece = 1;
					else 
					board[i][j].piece = 2;	
					
				}
				else if ((int)(*token) == 49 || (int)(*token) == 50 )
				{
					board[i][j].color = 1;
					if(*(token)==49)
					board[i][j].piece = 1;
					else 
					board[i][j].piece = 2;	
				}
				else 
				{
					board[i][j].color = 0;
					board[i][j].piece = 0;	
				}
			}	
			token = strtok(NULL,",");
		}
	}
	
	
}

void displayBoard()
{
	FILE * fPointer;
	fPointer = fopen("board.csv","r");
	char singleLine[50];
		
	
		
	char* token;
		
	while(!feof(fPointer))
	{
		fgets(singleLine,50,fPointer);	
		
			
		token = strtok(singleLine,",");
			
		while(token != NULL)
		{
			if(*token!= 10)
			{
				//printf("%d",(int)(*token));
				if( (((int)(*token) == 45) && ((int)*(token+1) == 49)) || ((int)(*token) == 45) && ((int)*(token+1) == 50)){
					printf(BLACK_BACKGROUND WHITE_TEXT "%-5.5s" ANSI_RESET,token);
					printf("|");
				}
				else if ((int)(*token) == 49 || (int)(*token) == 50 )
				{
					printf(WHITE_BACKGROUND BLACK_TEXT "%-5.5s" ANSI_RESET,token);
					printf("|");
				}
				else 
					printf("%-5.5s|",token);
			}	
			token = strtok(NULL,",");
		}
		printf("\n");
		
	}
}

void updateFile()
{
	FILE * fPointerNew; 
	fPointerNew = fopen("board.csv","w");
	int j;
	for(int i =0; i<8; i++)
	{
		for( j =0; j<8; j++)
		{
			if(board[i][j].color == -1 && board[i][j].piece == 1 )
			{
				fprintf(fPointerNew,"-1,");	
			}
			else if(board[i][j].color == -1 && board[i][j].piece == 2)
			{
				fprintf(fPointerNew,"-2,");
			}
			else if(board[i][j].color == 1 && board[i][j].piece == 1)
			{
				fprintf(fPointerNew,"1,");
			}
			else if(board[i][j].color == 1 && board[i][j].piece == 2)
			{
				fprintf(fPointerNew,"2,");
			}
			else 
			{
				fprintf(fPointerNew, "0,")	;
			}
				
		}
		if(i!=7 && j!=7)
		fprintf(fPointerNew,"\n");
		
	}
	fclose(fPointerNew);
}

void movePiece(char input[])
{
	int oldPositionY  ;
	if(input[4]==56)
	{
		oldPositionY = 0;
	}
	else if(input[4]==55)
	{
		oldPositionY=1;
	}
	else if(input[4]==54)
	{
		oldPositionY=2;
	}
	else if(input[4]==53)
	{
		oldPositionY=3;
	}
	else if(input[4]==52)
	{
		oldPositionY=4;
	}
	else if(input[4]==51)
	{
		oldPositionY=5;
	}
	else if(input[4]==50)
	{
		oldPositionY=6;
	}else if(input[4]==49)
	{
		oldPositionY=7;
	}
	int oldPositionX  = (input[3]-97);//[oldPositionY][oldPositionX]
	
	int newPositionY ;
	
	int newPositionX  = (input[6]-97);
	if(input[7]==56)
	{
		newPositionY = 0;
	}
	else if(input[7]==55)
	{
		newPositionY=1;
	}
	else if(input[7]==54)
	{
		newPositionY=2;
	}
	else if(input[7]==53)
	{
		newPositionY=3;
	}
	else if(input[7]==52)
	{
		newPositionY=4;
	}
	else if(input[7]==51)
	{
		newPositionY=5;
	}
	else if(input[7]==50)
	{
		newPositionY=6;
	}else if(input[7]==49)
	{
		newPositionY=7;
	}
	
	
	
	
	
	if((board[oldPositionY][oldPositionX].color == -1 && board[oldPositionY][oldPositionX].piece == 1)&&(board[newPositionY][newPositionX].piece == 0))// its a black pawn
	{
		if(( (oldPositionY==1 && newPositionY <=3) || (oldPositionY+1 == newPositionY) )  && oldPositionX == newPositionX)
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = -1;
			board[newPositionY][newPositionX].piece = 1;
			updateFile();
		}
		else
		{
			printf("Invalid Move!\n");
		}
			
	}
	else if((board[oldPositionY][oldPositionX].color == -1) && (board[oldPositionY][oldPositionX].piece == 2) && (board[newPositionY][newPositionX].piece == 0))// its a black knight
	{
	 	if(  ((newPositionY == (oldPositionY-2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY-1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )) ||
		     ((newPositionY == (oldPositionY+2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY+1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )))
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = -1;
			board[newPositionY][newPositionX].piece = 2;
			updateFile();
		}
		else
		{
			printf("invalid move")	;
		}
	}
	else if ((board[oldPositionY][oldPositionX].color == 1) && (board[oldPositionY][oldPositionX].piece == 2) && (board[newPositionY][newPositionX].piece == 0))// white knight
	{
		if(  ((newPositionY == (oldPositionY-2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY-1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )) ||
		     ((newPositionY == (oldPositionY+2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY+1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )))
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = 1;
			board[newPositionY][newPositionX].piece = 2;
			updateFile();
		}
		else
		{
			printf("invalid move")	;
		}
	}
	else if((board[oldPositionY][oldPositionX].color == 1 && board[oldPositionY][oldPositionX].piece == 1)&& (board[newPositionY][newPositionX].piece == 0))// is a white pawn
	{
		if( ((oldPositionY==6 && newPositionY >=4)||(oldPositionY-1 == newPositionY) ) && oldPositionX == newPositionX)
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = 1;
			board[newPositionY][newPositionX].piece = 1;
			updateFile();
		}
		else 
		{
			printf("Invalid Move\n");	
		}
		
	}
	
	else 
	{
		printf("Invalid Move!\n");
	}
	
	
}

void capturePiece( char input[])
{
	int oldPositionY  ;
	if(input[4]==56)
	{
		oldPositionY = 0;
	}
	else if(input[4]==55)
	{
		oldPositionY=1;
	}
	else if(input[4]==54)
	{
		oldPositionY=2;
	}
	else if(input[4]==53)
	{
		oldPositionY=3;
	}
	else if(input[4]==52)
	{
		oldPositionY=4;
	}
	else if(input[4]==51)
	{
		oldPositionY=5;
	}
	else if(input[4]==50)
	{
		oldPositionY=6;
	}else if(input[4]==49)
	{
		oldPositionY=7;
	}
	int oldPositionX  = (input[3]-97);//[oldPositionY][oldPositionX]
	
	int newPositionY ;
	
	int newPositionX  = (input[6]-97);
	if(input[7]==56)
	{
		newPositionY = 0;
	}
	else if(input[7]==55)
	{
		newPositionY=1;
	}
	else if(input[7]==54)
	{
		newPositionY=2;
	}
	else if(input[7]==53)
	{
		newPositionY=3;
	}
	else if(input[7]==52)
	{
		newPositionY=4;
	}
	else if(input[7]==51)
	{
		newPositionY=5;
	}
	else if(input[7]==50)
	{
		newPositionY=6;
	}else if(input[7]==49)
	{
		newPositionY=7;
	}
	
	if((board[oldPositionY][oldPositionX].color == -1 && board[oldPositionY][oldPositionX].piece == 1)&&(board[newPositionY][newPositionX].color == 1 ))// its a black pawn
	{
		if(( (oldPositionY+1 == newPositionY) )  && oldPositionX != newPositionX)
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = -1;
			board[newPositionY][newPositionX].piece = 1;
			updateFile();
		}
		else
		{
			printf("Invalid Move!\n");
		}
			
	}
	else if((board[oldPositionY][oldPositionX].color == 1 && board[oldPositionY][oldPositionX].piece == 1)&&(board[newPositionY][newPositionX].color == -1 ))// white pawn trying to capture
	{
		if(( (oldPositionY-1 == newPositionY) )  && oldPositionX != newPositionX)
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = 1;
			board[newPositionY][newPositionX].piece = 1;
			updateFile();
		}
		else
		{
			printf("Invalid Move!\n");
		}
	}
	
	else if((board[oldPositionY][oldPositionX].color == -1) && (board[oldPositionY][oldPositionX].piece == 2) && (board[newPositionY][newPositionX].color == 1))// its a black knight
	{
	 	if(  ((newPositionY == (oldPositionY-2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY-1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )) ||
		     ((newPositionY == (oldPositionY+2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY+1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )))
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = -1;
			board[newPositionY][newPositionX].piece = 2;
			updateFile();
		}
		else
		{
			printf("invalid move")	;
		}
	}
	
	else if ((board[oldPositionY][oldPositionX].color == 1) && (board[oldPositionY][oldPositionX].piece == 2) && (board[newPositionY][newPositionX].color == -1))// white knight
	{
		if(  ((newPositionY == (oldPositionY-2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY-1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )) ||
		     ((newPositionY == (oldPositionY+2)) && (newPositionX == (oldPositionX-1)|| newPositionX ==(oldPositionX+1) )) || 
		     ((newPositionY == (oldPositionY+1)) && (newPositionX == (oldPositionX-2)|| newPositionX ==(oldPositionX+2) )))
		{
			board[oldPositionY][oldPositionX].color = 0;
			board[oldPositionY][oldPositionX].piece = 0;
			
			board[newPositionY][newPositionX].color = 1;
			board[newPositionY][newPositionX].piece = 2;
			updateFile();
		}
		else
		{
			printf("invalid move")	;
		}
	}
	
	else 
	{
		printf("Invalid Move\n");	
	}
	
}





int main()
{
	// fill the checker struct first with the csv file
	fillBoard();
	char userInput[100];
	printf("Please enter multiple string followed by enter\nWhen you with to finish type Control+D\n");
	
	while(scanf("%[^\n]%*c", userInput) != EOF )
	{
		if(userInput[0]=='m')
		{
			movePiece(userInput);
			
		}
		else if (userInput[0]=='c') 
		{
			capturePiece(userInput);
		}
		else if (userInput[0]=='s')
		{
		    displayBoard();
		}
		
	
	
	}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
}

