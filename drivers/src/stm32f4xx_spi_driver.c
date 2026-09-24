/*
 * stm32f4xx_spi_driver.c
 *
 *  Created on: Sep 17, 2026
 *      Author: ritikrai
 */


#include "stm32f407xx_spi_driver.h"







void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		    {
		        if(pSPIx == SPI1)
		        {
		        	SPI1_PCLK_EN();
		        }else if (pSPIx == SPI2)
		        {
		        	SPI2_PCLK_EN();
		        }else if (pSPIx == SPI3)
		        {
		        	SPI3_PCLK_EN();
		        }
		    }
		    else
		    {
		        if(pSPIx == SPI1)
		        {
		        	SPI1_PCLK_DI();
		        }else if (pSPIx == SPI2)
		        {
		        	SPI2_PCLK_DI();
		        }else if (pSPIx == SPI3)
		        {
		        	SPI3_PCLK_DI();
		        }

		    }
}




void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//FIRST LETS CONFIGURE THE SPI_CR1 FREGISTER
	uint32_t tempreg = 0;

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	// device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2 ;
	// configure bus
	if(pSPIHandle->SPIConfig.SPI_busConfig == SPI_BUS_CONFIG_FD )
	{
		//BIDI CLEAR
		tempreg &= ~( 1 << 15 );
	}else if (pSPIHandle->SPIConfig.SPI_busConfig == SPI_BUS_CONFIG_HD)
	{
		tempreg |= ( 1 << 15 );

	}else if (pSPIHandle->SPIConfig.SPI_busConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY )
	{
		tempreg &= ~( 1 << 15);
		tempreg |= ( 1<< 10);
	}
	//spi serial clk speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	// dff
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;
	// configure the cpol
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	pSPIHandle->pSPIx->CR1 = tempreg;
}






// DEINIT
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}


// function definition
uint8_t SPI_GetflagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}






// SEND DATA this is blocking call
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{ while(Len>0)
   {
	 while (SPI_GetflagStatus(pSPIx,SPI_TXE_FLAG )  == FLAG_RESET );

	 // CHECK DFF BIT IN CR1
	 if(pSPIx->CR1 & ( 1 << SPI_CR1_DFF))
	 {
		 pSPIx->DR = *((uint16_t*)pTxBuffer);
		 Len--;
		 Len--;
		 (uint16_t*)pTxBuffer++;

	 }else{
		         pSPIx->DR = *pTxBuffer;
		 		 Len--;
		 		pTxBuffer++;
	 }
	}

}




void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}




void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	  if(EnorDi == ENABLE)
	    {
	        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	    }
	    else
	    {
	        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	    }

}




void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	  if(EnorDi == ENABLE)
	    {
	        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	    }
	    else
	    {
	        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	    }

}



uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
    if(pSPIx->SR & FlagName)
    {
        return FLAG_SET; // Make sure FLAG_SET is defined in your main header as 1
    }
    return FLAG_RESET;   // Make sure FLAG_RESET is defined in your main header as 0
}


































































































