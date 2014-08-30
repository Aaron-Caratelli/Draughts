/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "gameboard.h"

/* Copies the master board to a local copy for each game */
void init_gameboard(enum cell_contents board[][BOARDWIDTH])
{
	int i, j;
    for(i = 0; i < BOARDWIDTH; i++)
    {
    	for(j = 0; j < BOARDHEIGHT; j++)
    	{
    		board[i][j] = master_board[i][j];
    	}

    }

}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH])
{
	int count = 0;    
	int row = 0;
	int column = 0;

	clear_screen();

	printf("   |");
	for(count = 0; count < 8; ++count)
	{
		printf(" %d |", count);
	}
	printf("\n");
	printf("------------------------------------\n");

	for(row; row < BOARDHEIGHT; row++) 
    {
    	printf(" %d ", row);
	    for(column = 0; column < BOARDWIDTH; column++) 
	    {
	    	if(master_board[row][column] == 0)
	        printf("|  %s ", WHITE_RESET);
	    	
	    	if(master_board[row][column] == 1)
	        printf("| %s ", RED_DISPLAY);
	    	
	    	if(master_board[row][column] == 2)
	        printf("| %s ", WHITE_DISPLAY);
	    	
	    	if(master_board[row][column] == 3)
	        printf("| %s ", RED_KING_DISPLAY);

	    	if(master_board[row][column] == 4)
	        printf("| %s ", WHITE_KING_DISPLAY);

	    	printf("%s", WHITE_RESET);
	    }

	    printf("%s|\n", WHITE_RESET);
	    printf("------------------------------------\n");
	}

	return;
}
