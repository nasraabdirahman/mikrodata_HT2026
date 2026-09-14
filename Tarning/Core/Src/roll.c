#include <stdio.h>
#include <stdlib.h>
#include <main.h>


// everytime B1 is clicked it should return a value
int random_number = 99;
int roll_dice()
{
	int max_number = 6;
	int min_number = 1;
	random_number = rand() % (max_number - min_number + 1) + min_number;
	return random_number;
}
