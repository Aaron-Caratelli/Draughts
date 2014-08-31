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
    struct player current;
    
    //Copy the masterboard onto the current gameboard
    init_gameboard(gameboard);
    init_scoreboard(outcome);

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

    srand(time(NULL));
    //Number deciding what colour each player will be
    int side = rand() %2;
    printf("%d\n", side);

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
    printf("%d\n", p1.col);

    printf("%s %d\n", p1.name, p1.col);
    printf("%s %d\n", p2.name, p2.col);

    printf("%s is %d\n", p1.name, p1.col);

    printf("%s is %d\n", p2.name, p2.col);
    struct player * cp = &current;
    current.col = P_WHITE;
    while(test_for_winner(cp, gameboard) != 0)
    {
        if(current.col == p1.col)
        {
            current = p2;
            printf("Setting to player 2's turn.\n");
        }
        else if(current.col == p2.col)
        {
            current = p1;
            printf("Setting to player 1's turn.\n");
        }

        player_turn(cp, gameboard);
    }

    if(current.col == p1.col)
        printf("%s wins\n", p2.name); // Then pass name data into result.
    if(current.col == p2.col)
        printf("%s wins\n", p1.name);


}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current, 
    enum cell_contents board[][BOARDWIDTH])
{
    struct move next_move;
    struct player Player = *current;

    display_gameboard(board);

    if(Player.col == P_RED)
    {
        printf("%s", RED_SET);
        printf("%s's ", Player.name);
        printf("%s", WHITE_RESET);
        printf("turn: \n");
    }
    else
    {
        printf("%s's turn: \n", Player.name);
    }
    
    while(1)//(is_valid_move != INVALID)
    {
        printf("Select piece to move: \n");
        printf("Column: \n");  
        next_move.start.x = read_input()-48;
        printf("Row: \n");
        next_move.start.y = read_input()-48;

        printf("%d\n", next_move.start.x);
        printf("%d\n", next_move.start.y);
    }
}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{
    //if cell contains nothing (cellColour == EMPTY)
    //return INVALID;
    //if cell contains non-player colour (cellColour != current.col)
    //return INVALID;
    //if cell contains player colour (cellColour == current.col)
    //LOGIC
        //if KING  (K_RED || K_WHITE)
        //LOGIC
    //RETURN VALID/NOT
    
    return INVALID;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
    enum cell_contents board[][BOARDWIDTH])
{
    //LOGIC

    //if(is_valid_move == TURE)
    BOOLEAN has_moves = TRUE;
    //else
    //BOOLEAN has_moves = FALSE;

    return has_moves;
}

void quit_early(struct result * scoreboard, 
    struct result * latest_game)
{
    init_scoreboard(latest_game);
    add_to_scoreboard(latest_game);
}
