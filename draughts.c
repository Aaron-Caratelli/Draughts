/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : COSC1076
 * Program Code     : 
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"
#include "utility.h"
#include "gameboard.h"

int main (int argc, char *argv[])
{
	int sel = 0;

    enum cell_contents master_board[BOARDWIDTH][BOARDHEIGHT];

    clear_screen();
    print_menu();

    sel = read_input();
    do_option(sel);

  	display_gameboard(master_board);
  	printf("-------------ENGLISH DRAUGHTS------------\n");

    printf("\x1b[39m" "THANKS FOR PLAYING! Program End\n");
    return EXIT_SUCCESS;
}

 void print_menu ()
 {
 	printf("\x1b[39m" "English Draughts - Main Menu\n");
 	printf("1) Play Game\n");
 	printf("2) Display Winners\n");
 	printf("3) Reset Scoreboard\n");
 	printf("4) Quit\n");

 	return;
 }

void do_option(int choice)
{
	int Exit = 0;
	int valid = 0;

	while(!Exit)
	{	
		if(choice == 1)
		{
			char player_one[MAX_NAME_LEN] = {'\0'};
			char player_two[MAX_NAME_LEN] = {'\0'};

			printf("Play Game selected\n");
			printf("Player 1, enter name: ");

			if (fgets(player_one, MAX_NAME_LEN, stdin) != NULL)
			{
				if(player_one[strlen(player_one)-1] != '\n')
				{
					printf("Error: Input was too long or invalid. \n");
					read_rest_of_line();
					do_option(choice);
				}
				else
				{
					player_one[strlen(player_one)-1] = '\0';
				}

				while(1)
				{
					printf("Player 2, enter name: ");
					if(fgets(player_two, MAX_NAME_LEN, stdin) != NULL)
					{
						if(player_two[strlen(player_two)-1] != '\n')
						{
							printf("Error: Input was too long or invalid. \n");
							read_rest_of_line();
						}
						else
						{
							player_two[strlen(player_two)-1] = '\0';;
						}

    					struct result scoreboard[SCOREBOARDSIZE];		//initialise scoreboard
						play_game(player_one, player_two, scoreboard);
					}
					else
					{
					printf("Error: Name may be too long or invalid.\n");
					read_rest_of_line();
					}
				}
			}
			else
			{
				printf("Error: Name may be too long or invalid.\n");
				read_rest_of_line();
			}
		}
		else if(choice == 2)
		{
			display_scoreboard();
			clear_screen();
			print_menu();
			choice = read_input();
		}
		else if(choice == 3)
		{
			struct result scoreboard[SCOREBOARDSIZE];
			reset_scoreboard(scoreboard);
		}
		else if(choice == 4)
		{
			printf("Quit selected\n");
			Exit = 1;
		}
		else
		{
			printf("Error: Please choose a valid input from 1-4.\n");
			choice = read_input();
		}
	}
}