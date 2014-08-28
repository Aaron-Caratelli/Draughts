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
    /* Delete this comment and write your own comments and code here*/
}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH])
{
	    
	int row = 0;
	int column = 0;

	for(row; row < BOARDHEIGHT; row++) 
    {
	    for(column = 0; column < BOARDWIDTH; column++) 
	    {
	    	if(master_board[row][column] == 0)
	        printf("%d ", master_board[row][column]);
	    	
	    	if(master_board[row][column] == 0)
	        printf("%d ", master_board[row][column]);
	    	
	    	if(master_board[row][column] == 0)
	        printf("%d ", master_board[row][column]);
	    }

	    printf("\n");
	}

	return;
}
