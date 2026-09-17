#include <stdio.h>
#include <stdlib.h>
#include <main.h>


// everytime B1 is clicked it should return a value
int number = 0;
int roll_dice()
{
	number = (number % 6) + 1;

	return number;
}
