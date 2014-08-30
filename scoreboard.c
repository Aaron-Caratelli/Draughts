  /***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"

/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
  struct result Hscoreboard = *scoreboard;
  int i;
  for(i = 0; i < MAX_NAME_LEN; ++i)
  {
    Hscoreboard.won[i] = '\0';
    Hscoreboard.lost[i] = '\0';
  }
  *scoreboard = Hscoreboard;

  FILE *fr = fopen("scoreboard.txt", "r");
  if(!fr)
  {
    printf("Error: Could not find scoreboard file\n");
  }

  //Initialise char array for storing previous 9 games
  char temp_score[PREV_NINE_SIZE] = {'\0'};
  //Read from file character by character into the temp array
  i = 0;
  while (!feof(fr))
  {
    fgets(temp_score,PREV_NINE_SIZE,fr);
    ++i;
  }

  fclose(fr);

  //Open file with "write" to clear it
  FILE *fc = fopen("scoreboard.txt", "w");
  fclose(fc);


  FILE *fw = fopen("scoreboard_temp.txt", "w");
  if(!fw)
  {
    printf("Error: Could not find temp scoreboard file\n");
    return;
  }

  fwrite(temp_score, sizeof(char), PREV_NINE_SIZE, fw);
  fclose(fw);
  printf("Files.....initiailsed.\n");
  return;
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * latest_game)
{
  int i;
  char temp_score_array[PREV_NINE_SIZE] = {'\0'};
  char * temp_score = &temp_score_array[0];
  struct result outcome = *latest_game;

  FILE *fr = fopen("scoreboard_temp.txt", "r");
  if(!fr)
  {
    printf("Error: Could not find temp scoreboard file\n");
    return;
  }
  for(i = 0; i < PREV_NINE_SIZE; ++i)
  {
    while (!feof(fr))
    {
      fgets(temp_score,PREV_NINE_SIZE,fr);
      ++i;
    }
  }
  fclose(fr);

  FILE *fw = fopen("scoreboard.txt", "w");
  if(!fw)
  {
    printf("Error: Could not find scoreboard file\n");
    return;
  }

  char line[PREV_NINE_SIZE/9] = 
  "| \0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0     | \0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0      |\n";

  for(i = 2; i < MAX_NAME_LEN; ++i)
  {
    line[i] = outcome.won[i];
  }
  for(i = 30; i < MAX_NAME_LEN; ++i)
  {
    line[i] = outcome.lost[i];
  }

  fwrite(line, sizeof(char), (PREV_NINE_SIZE/9), fw);
  fwrite(temp_score, sizeof(char), PREV_NINE_SIZE, fw) != PREV_NINE_SIZE;
  fclose(fw);

  return;
}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
    /* Delete this comment and write your own comments and code here*/
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
      
}

