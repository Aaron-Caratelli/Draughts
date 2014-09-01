/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : COSC10176
 * Program Code     : BP094
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
    int second_turn = 0;

    enum move_type state = NORMAL;
    do 
    {
        display_gameboard(board);
        if(state == INVALID)
        {
            printf("%s", RED_SET);
            printf("INVLAID MOVE");
            printf("%s\n", WHITE_RESET);
        }

        if(state == ATTACK)
        {
            printf("%s", GREEN_SET);
            printf("ATTACK AVAILABLE");
            printf("%s\n", WHITE_RESET);

            second_turn = 1;
        }

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

        if(!second_turn)
        {
            printf("Select piece to move: \n");
            printf("Row");  
            next_move.start.y = read_input();
            printf("Column");
            next_move.start.x = read_input();

            printf("Select destination: \n");
            printf("Row");
            next_move.end.y = read_input();
            printf("Column");
            next_move.end.x = read_input();
            state = is_valid_move(next_move, current, board, second_turn);
        }
        else if(second_turn)
        {
            next_move.start.y = next_move.end.y;
            next_move.start.x = next_move.end.x;

            do{
                if(state == INVALID)
                {
                    display_gameboard(board);
                    printf("%s", RED_SET);
                    printf("INVLAID MOVE\n");
                    printf("%s", GREEN_SET);
                    printf("ATTACK AVAILABLE");
                    printf("%s\n", WHITE_RESET);
                }
                printf("Select next attack: \n");
                printf("Row");
                next_move.end.y = read_input();
                printf("Column");
                next_move.end.x = read_input();
                state = is_valid_move(next_move, current, board, second_turn);
            }while(state == INVALID);
            second_turn = 0;
        }
        if(state == ATTACK)
        {
            state = continue_attack(next_move, current, board);
            if(state == NORMAL)
                second_turn = 0;
        }

    }while(state != NORMAL);
}

/* Requirement 4 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
    struct player * current, enum cell_contents board[][BOARDWIDTH], int chain)
{
    struct player Player = *current;

    if(board[next_move.start.y][next_move.start.x] == EMPTY)
    {
        return INVALID;
    }

    if(Player.col == P_WHITE)
    {
        if(board[next_move.start.y][next_move.start.x] != WHITE 
            && board[next_move.start.y][next_move.start.x] != K_WHITE)
        {
            return INVALID;
        }

        if(board[next_move.end.y][next_move.end.x] == EMPTY)
        {
            if(next_move.start.x - next_move.end.x == -1 || next_move.start.x - next_move.end.x == 1)
            {
                if(next_move.start.y - next_move.end.y == 1)
                {
                    if(chain == 0)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        if(next_move.end.y == 0)
                            board[next_move.end.y][next_move.end.x] = K_WHITE;
                        return NORMAL;
                    }
                }
                if(next_move.start.y - next_move.end.y == -1 && board[next_move.start.y][next_move.start.x] == K_WHITE)
                {
                    board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                    board[next_move.start.y][next_move.start.x] = EMPTY;
                    if(next_move.end.y == 0)
                        board[next_move.end.y][next_move.end.x] = K_WHITE;
                    return NORMAL;
                }
                else
                    return INVALID;
            }

            else if(next_move.start.x - next_move.end.x == -2)
            {
                if(next_move.start.y - next_move.end.y == 2)
                {
                    if(board[next_move.start.y - 1][next_move.start.x + 1] == RED
                        || board[next_move.start.y - 1][next_move.start.x + 1] == K_RED)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        board[next_move.start.y - 1][next_move.start.x + 1] = EMPTY;
                        if(next_move.end.y == 0)
                            board[next_move.end.y][next_move.end.x] = K_WHITE;
                        return ATTACK;
                    }
                    return INVALID;
                }
                else if(next_move.start.y - next_move.end.y == -2)
                {
                    if(board[next_move.start.y][next_move.start.x] == K_WHITE)
                    {
                        if(board[next_move.start.y + 1][next_move.start.x + 1] == RED
                        || board[next_move.start.y + 1][next_move.start.x + 1] == K_RED)
                        {
                            board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                            board[next_move.start.y][next_move.start.x] = EMPTY;
                            board[next_move.start.y + 1][next_move.start.x + 1] = EMPTY;
                            if(next_move.end.y == 0)
                                board[next_move.end.y][next_move.end.x] = K_WHITE;
                            return ATTACK;
                        }
                        return INVALID;
                    }
                    return INVALID;
                }
            }
            else if(next_move.start.x - next_move.end.x == 2)
            {
                if(next_move.start.y - next_move.end.y == 2)
                {
                    if(board[next_move.start.y - 1][next_move.start.x - 1] == RED
                        || board[next_move.start.y - 1][next_move.start.x - 1] == K_RED)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        board[next_move.start.y - 1][next_move.start.x - 1] = EMPTY;
                        if(next_move.end.y == 0)
                            board[next_move.end.y][next_move.end.x] = K_WHITE;
                        return ATTACK;
                    }
                    return INVALID;
                }
                else if(next_move.start.y - next_move.end.y == -2)
                {
                    if(board[next_move.start.y][next_move.start.x] == K_WHITE)
                    {
                        if(board[next_move.start.y + 1][next_move.start.x - 1] == RED
                        || board[next_move.start.y + 1][next_move.start.x - 1] == K_RED)
                        {
                            board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                            board[next_move.start.y][next_move.start.x] = EMPTY;
                            board[next_move.start.y + 1][next_move.start.x - 1] = EMPTY;
                            if(next_move.end.y == 0)
                                board[next_move.end.y][next_move.end.x] = K_WHITE;
                            return ATTACK;
                        }
                        return INVALID;
                    }
                    return INVALID;
                }
                return INVALID;
            }
            return INVALID;
        }
        return INVALID;
    }
    else if(Player.col == P_RED)
    {
        if(board[next_move.start.y][next_move.start.x] != RED 
            && board[next_move.start.y][next_move.start.x] != K_RED)
        {
            return INVALID;
        }

        if(board[next_move.end.y][next_move.end.x] == EMPTY)
        {
            if(next_move.start.x - next_move.end.x == -1 || next_move.start.x - next_move.end.x == 1)
            {
                if(next_move.start.y - next_move.end.y == -1)
                {
                    if(chain == 0)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        if(next_move.end.y == 7)
                            board[next_move.end.y][next_move.end.x] = K_RED;
                        return NORMAL;
                    }
                }
                if(next_move.start.y - next_move.end.y == + 1 && board[next_move.start.y][next_move.start.x] == K_RED)
                {
                    board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                    board[next_move.start.y][next_move.start.x] = EMPTY;
                    if(next_move.end.y == 7)
                        board[next_move.end.y][next_move.end.x] = K_RED;
                    return NORMAL;
                } 
                else
                    return INVALID;
            }
            else if(next_move.start.x - next_move.end.x == -2)
            {
                if(next_move.start.y - next_move.end.y == -2)
                {
                    if(board[next_move.start.y + 1][next_move.start.x + 1] == WHITE 
                        || board[next_move.start.y + 1][next_move.start.x + 1] == K_WHITE)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        board[next_move.start.y + 1][next_move.start.x + 1] = EMPTY;
                        if(next_move.end.y == 7)
                            board[next_move.end.y][next_move.end.x] = K_RED;
                        return ATTACK;
                    }
                    return INVALID;
                }
                else if(next_move.start.y - next_move.end.y == 2)
                {
                    if(board[next_move.start.y][next_move.start.x] == K_RED)
                    {
                        if(board[next_move.start.y - 1][next_move.start.x + 1] == WHITE
                        || board[next_move.start.y - 1][next_move.start.x + 1] == K_WHITE)
                        {
                            board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                            board[next_move.start.y][next_move.start.x] = EMPTY;
                            board[next_move.start.y - 1][next_move.start.x + 1] = EMPTY;
                            if(next_move.end.y == 7)
                                board[next_move.end.y][next_move.end.x] = K_RED;
                            return ATTACK;
                        }
                        return INVALID;
                    }
                    return INVALID;
                }
            }
            else if(next_move.start.x - next_move.end.x == 2)
            {
                if(next_move.start.y - next_move.end.y == -2)
                {
                    if(board[next_move.start.y + 1][next_move.start.x - 1] == WHITE
                        || board[next_move.start.y + 1][next_move.start.x - 1] == K_WHITE)
                    {
                        board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                        board[next_move.start.y][next_move.start.x] = EMPTY;
                        board[next_move.start.y + 1][next_move.start.x - 1] = EMPTY;
                        if(next_move.end.y == 7)
                            board[next_move.end.y][next_move.end.x] = K_RED;
                        return ATTACK;
                    }
                    return INVALID;
                }
                else if(next_move.start.y - next_move.end.y == 2)
                {
                    if(board[next_move.start.y][next_move.start.x] == K_RED)
                    {
                        if(board[next_move.start.y - 1][next_move.start.x - 1] == WHITE
                        || board[next_move.start.y - 1][next_move.start.x - 1] == K_WHITE)
                        {
                            board[next_move.end.y][next_move.end.x] = board[next_move.start.y][next_move.start.x];
                            board[next_move.start.y][next_move.start.x] = EMPTY;
                            board[next_move.start.y - 1][next_move.start.x - 1] = EMPTY;
                            if(next_move.end.y == 7)
                                board[next_move.end.y][next_move.end.x] = K_RED;
                            return ATTACK;
                        }
                        return INVALID;
                    }
                    return INVALID;
                }
                return INVALID;
            }
            return INVALID;
        }
        return INVALID;
    }
    
    return INVALID;
}

enum move_type continue_attack(struct move next_move, 
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{
    struct player Player = *current;
    int checker;
    int counter = 0;
    int * count = &counter;
    enum move_type state = NORMAL;


    while(counter < 4)
    {
        if(Player.col == P_RED)
        {
            checker = data_check(next_move.end.y, next_move.end.x, count);
            
            switch(checker)
            {
                case 1: 
                    if(board[next_move.end.y][next_move.end.x] == K_RED)
                    { 
                        if(board[next_move.end.y - 1][next_move.end.x + 1] == WHITE 
                        || board[next_move.end.y - 1][next_move.end.x + 1] == K_WHITE)
                        {
                            if(board[next_move.end.y - 2][next_move.end.x + 2] == EMPTY)
                            {
                                state = ATTACK;
                            }
                        }
                    }
                    break;
                case 2:
                    if(board[next_move.end.y][next_move.end.x] == K_RED)
                    { 
                        if(board[next_move.end.y - 1][next_move.end.x - 1] == WHITE 
                        || board[next_move.end.y - 1][next_move.end.x - 1] == K_WHITE)
                        {
                            if(board[next_move.end.y - 2][next_move.end.x - 2] == EMPTY)
                            {
                                state = ATTACK;
                            }
                        }
                    }
                    break;
                case 3:
                    if(board[next_move.end.y + 1][next_move.end.x + 1] == WHITE
                    || board[next_move.end.y + 1][next_move.end.x + 1] == K_WHITE)
                    {
                        if(board[next_move.end.y + 2][next_move.end.x + 2] == EMPTY)
                        {
                            state = ATTACK;
                        }
                    }
                    break;
                case 4:
                    if(board[next_move.end.y + 1][next_move.end.x - 1] == WHITE
                    || board[next_move.end.y + 1][next_move.end.x - 1] == K_WHITE)
                    {
                        if(board[next_move.end.y + 2][next_move.end.x - 2] == EMPTY)
                            state = ATTACK;
                    }
                    break;
                default:
                    state = NORMAL;
            }
        }
        else if(Player.col == P_WHITE)
        {
            checker = data_check(next_move.end.y, next_move.end.x, count);

            switch(checker)
            {
                case 1: 
                    if(board[next_move.end.y - 1][next_move.end.x + 1] == RED 
                    || board[next_move.end.y - 1][next_move.end.x + 1] == K_RED)
                    {
                        if(board[next_move.end.y - 2][next_move.end.x + 2] == EMPTY)
                        {
                            state = ATTACK;
                        }
                    }
                    break;
                case 2:
                    if(board[next_move.end.y - 1][next_move.end.x - 1] == RED 
                    || board[next_move.end.y - 1][next_move.end.x - 1] == K_RED)
                    {
                        if(board[next_move.end.y - 2][next_move.end.x - 2] == EMPTY)
                        {
                            state = ATTACK;
                        }
                    }
                    break;
                case 3:
                    if(board[next_move.end.y][next_move.end.x] == K_WHITE)
                    { 
                        if(board[next_move.end.y + 1][next_move.end.x + 1] == RED
                        || board[next_move.end.y + 1][next_move.end.x + 1] == K_RED)
                        {
                            if(board[next_move.end.y + 2][next_move.end.x + 2] == EMPTY)
                            {
                                state = ATTACK;
                                printf("%d\n", state);
                            }
                        }
                    }
                    break;
                case 4:
                    if(board[next_move.end.y][next_move.end.x] == K_WHITE)
                    { 
                        if(board[next_move.end.y + 1][next_move.end.x - 1] == RED
                        || board[next_move.end.y + 1][next_move.end.x - 1] == K_RED)
                        {
                            if(board[next_move.end.y + 2][next_move.end.x - 2] == EMPTY)
                                state = ATTACK;
                        }
                    }
                    break;
            }
        }
    } //While loop end
    return state;
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

int data_check(int y, int x, int * count)
{
    printf("%d %d %d\n", y, x, *count);
    if(y < 6 && *count < 2)
    {
        if(x < 6 && *count < 1)
        {
            printf("++\n");
            *count = *count + 1;
            return 3;
        }
        if(x > 1)
        {

            printf("+-\n");
            *count = *count + 1;
            return 4;
        }

    }
    else if(y > 1 && *count < 4)
    {
        if(x < 6 && *count < 3)
        {

            printf("-+\n");
            *count = *count + 1;
            return 1;
        }
        if(x > 1)
        {

            printf("--\n");
            *count = *count + 1;
            return 2;
        }
    }
    *count = *count + 1;
    return 0;
}
