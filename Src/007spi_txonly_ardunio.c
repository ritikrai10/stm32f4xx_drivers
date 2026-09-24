/*
 * 007spi_txonly_ardunio.c
 *
 *  Created on: Sep 24, 2026
 *      Author: ritikrai
 */


/*
 * 006spi_tx_testing.c
 *
 *  Created on: Sep 21, 2026
 *      Author: ritikrai
 */
#include <string.h>
#include "stm32f407xx.h"


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i++);
}





void SPI2_GPIOInits(void)
{

	GPIO_handle_t SPIPins = {0};


	GPIO_PeriClockControl(GPIOB, ENABLE);

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType  = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	// MISO (Not used for TX only test, but uncomment if needed)
	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	// GPIO_Init(&SPIPins);

	// NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	 GPIO_Init(&SPIPins);
}


void SPI2_Inits(void)
{
	// FIX 3: Initialize structure to zero
	SPI_Handle_t SPI2handle = {0};


	SPI_PeriClockControl(SPI2, ENABLE);

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_busConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2handle);
}



int main(void)
{
	GPIO_handle_t Gpioled , GPIOBtn ;

	Gpioled.pGPIOx = GPIOD;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST ;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP ;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;




	GPIO_Init(&GPIOBtn);

}

int main(void)
{
	char user_data[] = "Hello world";

	// Initialize GPIO pins for SPI2
	SPI2_GPIOInits();

	// Initialize SPI2 peripheral
	SPI2_Inits();

    SPI_SSOEConfig(SPI2,ENABLE);
  while(1){
    while( ! GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0) );

    delay();

	// Enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2, ENABLE);

	// Send the data
	SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));



	SPI_PeripheralControl(SPI2, DISABLE);
  }


	return 0;
}
