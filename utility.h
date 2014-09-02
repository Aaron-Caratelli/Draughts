/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Aaron Caratelli
 * Student Number   : s3352594
 * Course Code      : COSC10176
 * Program Code     : BP094
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20
#define SELECTION_SIZE 1
 #define TEST_CODE 9


typedef enum
{
    FALSE, TRUE
}BOOLEAN;

/*Reads user input from keyboard*/
//void read_input();
/*Clears residual data from stdin*/
void read_rest_of_line(void);
int read_input();
void clear_screen(void);

#endif