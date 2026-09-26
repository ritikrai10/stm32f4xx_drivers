/*
 * 006spi_tx_testing.c
 *
 *  Created on: Sep 17, 2026
 *      Author: ritikrai
 */

#include<stdio.h>
#include<string.h>
#include "stm32f407xx.h"

#define COMMAND_LED_CTRL      		0x50
#define COMMAND_SENSOR_READ      	0x51
#define COMMAND_LED_READ      		0x52
#define COMMAND_PRINT      			0x53
#define COMMAND_ID_READ      		0x54

#define LED_ON     1
#define LED_OFF    0

#define ANALOG_PIN0 	0
#define ANALOG_PIN1 	1
#define ANALOG_PIN2 	2
#define ANALOG_PIN3 	3
#define ANALOG_PIN4 	4

#define LED_PIN  9

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

void SPI2_GPIOInits(void)
{
	GPIO_handle_t SPIPins;

	GPIO_PeriClockControl(GPIOB, ENABLE);

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI2handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&GPIOBtn);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte == (uint8_t)0xF5)
	{
		return 1;
	}
	return 0;
}

int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	printf("Application is running\n");

	GPIO_ButtonInit();
	SPI2_GPIOInits();
	SPI2_Inits();

	printf("SPI Init. done\n");

	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		SPI_PeripheralControl(SPI2, ENABLE);

		uint8_t commandcode = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];

		SPI_SendData(SPI2, &commandcode, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if( SPI_VerifyResponse(ackbyte) )
		{
			args[0] = LED_PIN;
			args[1] = LED_ON;
			SPI_SendData(SPI2, args, 2);
			SPI_ReceiveData(SPI2, args, 2);
			printf("COMMAND_LED_CTRL Executed\n");
		}

		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		commandcode = COMMAND_SENSOR_READ;

		SPI_SendData(SPI2, &commandcode, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if( SPI_VerifyResponse(ackbyte) )
		{
			args[0] = ANALOG_PIN0;
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1);
			delay();
			SPI_SendData(SPI2, &dummy_write, 1);
			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
			printf("COMMAND_SENSOR_READ %d\n", analog_read);
		}

		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		commandcode = COMMAND_LED_READ;

		SPI_SendData(SPI2, &commandcode, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		if( SPI_VerifyResponse(ackbyte) )
		{
			args[0] = LED_PIN;
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1);
			delay();
			SPI_SendData(SPI2, &dummy_write, 1);
			uint8_t led_status;
			SPI_ReceiveData(SPI2, &led_status, 1);
			printf("COMMAND_READ_LED %d\n", led_status);
		}

		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		commandcode = COMMAND_PRINT;

		SPI_SendData(SPI2, &commandcode, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		uint8_t message[] = "Hello ! How are you ??";
		if( SPI_VerifyResponse(ackbyte) )
		{
			args[0] = strlen((char*)message);
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1);
			delay();

			for(int i = 0 ; i < args[0] ; i++){
				SPI_SendData(SPI2, &message[i], 1);
				SPI_ReceiveData(SPI2, &dummy_read, 1);
			}
			printf("COMMAND_PRINT Executed\n");
		}

		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		delay();

		commandcode = COMMAND_ID_READ;

		SPI_SendData(SPI2, &commandcode, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		SPI_SendData(SPI2, &dummy_write, 1);
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		uint8_t id[11];
		uint32_t i = 0;
		if( SPI_VerifyResponse(ackbyte) )
		{
			for( i = 0 ; i < 10 ; i++)
			{
				SPI_SendData(SPI2, &dummy_write, 1);
				SPI_ReceiveData(SPI2, &id[i], 1);
			}
			id[10] = '\0';
			printf("COMMAND_ID : %s \n", id);
		}

		while( SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG) );

		SPI_PeripheralControl(SPI2, DISABLE);

		printf("SPI Communication Closed\n");
	}

	return 0;
}
