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
	char sel = '\0';

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

char read_input()
{
	char input[SIZE + 2];
	int done = 0;
	char choice = '0';

	do
	{
		printf("\nInput: ");
		fgets(input, SIZE + 2, stdin);
		if(input[strlen(input)-1] != '\n')
		{
			printf("Error: Input was too long. \n");
			read_rest_of_line();
		}
		else
		{
			input[strlen(input)-1] = '\0';
			done = 1;
		}
	}	while(done != 1);

    choice = input[0];
    return choice;
}

void do_option(char choice)
{
	int Exit = 0;
	int valid = 0;

	while(!Exit)
	{	
		if(choice == '1')
		{
			char player_one[MAX_NAME_LEN] = {'\0'};
			char player_two[MAX_NAME_LEN] = {'\0'};

			printf("Play Game selected\n");
			printf("Player 1, enter name: ");

			if (fgets(player_one, MAX_NAME_LEN, stdin) != NULL)
			{
				if(player_one[strlen(player_one)-1] != '\n')
				{
					printf("Error: Input was too long or invalid. \n");				//NOTE: Here's where I left off. Input validation not complete
					read_rest_of_line();
					do_option(choice);
				}
				else
				{
					player_one[strlen(player_one)-1] = '\0';printf("%s\n", player_one);
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
							player_two[strlen(player_two)-1] = '\0';printf("%s\n", player_two);
						}
						printf("DONE\n");

    					struct result scoreboard[SCOREBOARDSIZE];		//initialise scoreboard
						// play_game(*player_one, *player_two, scoreboard);
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
		else if(choice == '2')
		{
			printf("Leaderboard selected\n");
		}
		else if(choice == '3')
		{
			printf("Reset scores selected\n");
		}
		else if(choice == '4')
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