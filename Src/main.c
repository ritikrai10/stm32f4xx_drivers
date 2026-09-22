/*
 * main.c
 *
 *  Created on: Sep 11, 2026
 *      Author: ritikrai
 */

#include "stm32f407xx.h"



int main(void)
{
	return 0;
}



void EXTI0_IRQHandle(void)
{
	// handle the interrupt
	GPIO_IRQHandling(0);
}
