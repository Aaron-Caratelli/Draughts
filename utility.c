/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : COSC1076
 * Program Code     : 
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

void clear_screen(void)
{
	int count = 0;
	
	for(count = 0; count < 100; count++)
	{
		printf("\n");
	}
}