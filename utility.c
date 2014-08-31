/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : COSC10176
 * Program Code     : BP094
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
 #include <stdio.h>
 #include "utility.h"

 void read_rest_of_line()
{
    int ch;
    /* remove all characters from the buffer */
    while(ch = getc(stdin), ch!='\n' && ch!=EOF) 
        ;
    /* clear the error status of the input pointer */
    clearerr(stdin);
}

int read_input()
{
	char input[SELECTION_SIZE + 2];
	int done = 0;
	int choice = 0;
	int char_conversion = 48; //difference between char '1' and int 1

	do
	{
		printf("\nInput: ");
		fgets(input, SELECTION_SIZE + 2, stdin);
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

	//Converts numeric char to int
    choice = input[0]-char_conversion;
    return choice;
}

void clear_screen(void)
{
	int count = 0;
	
	for(count = 0; count < 100; count++)
	{
		printf("\n");
	}
}