#include <stdio.h>
#include <stdlib.h>
#include <main.h>
const uint16_t sseg[10] = { 0b01011111, 0b000000110, 0b10011011, 0b10001111, 0b11000110,0b11001101, 0b11011101, 0b00000111, 0b110111111, 0b10000111};
const uint16_t sseg_err = 0x1AC;
void put_on_sseg(uint8_t dec_nbr)
{
	GPIOC->ODR = sseg[dec_nbr];

	if(dec_nbr > 6)
	{
		GPIOC->ODR = sseg_err;
	}

}


