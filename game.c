/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : 
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"
#include <stdio.h>

/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two, 
    struct result * outcome)
{
    enum cell_contents gameboard[BOARDWIDTH][BOARDHEIGHT];
    
    //Copy the masterboard onto the current gameboard
    init_gameboard(gameboard);

    int i;
    struct player p1;
    for(i = 0; i < MAX_NAME_LEN; i++)
    {
        p1.name[i] = player_one[i];
    }
    struct player p2;
    for(i = 0; i < MAX_NAME_LEN; i++)
    {
        p2.name[i] = player_two[i];
    }

    int side = 0;  //Number deciding what colour each player will be

    //INSERT RANDOM NO. GEN 0-1

    if(side == 0)
    {
        p1.col = P_RED;
        p2.col = P_WHITE;
    }
    else if(side ==1)
    {
        p1.col = P_WHITE;
        p2.col = P_RED;
    }

    printf("%s %d\n", p1.name, p1.col);
    printf("%s %d\n", p2.name, p2.col);

}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current, 
    enum cell_contents board[][BOARDWIDTH])
{
    /* Delete this comment and write your own comments and code here*/
}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{
    /* Delete this comment and write your own comments and code here*/
    
    return INVALID;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
    enum cell_contents board[][BOARDWIDTH])
{
    BOOLEAN has_moves = TRUE;

    return has_moves;
}
