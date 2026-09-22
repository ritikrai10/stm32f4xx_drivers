/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Aug 15, 2026
 *      Author: ritikrai
 */


#include "stm32f407xx_gpio_driver.h"


/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 *
 * @return            - none
 *
 * @Note              - none
 */



void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx , uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	    {
	        if(pGPIOx == GPIOA)
	        {
	            GPIOA_PCLK_EN();
	        }else if (pGPIOx == GPIOB)
	        {
	            GPIOB_PCLK_EN();
	        }else if (pGPIOx == GPIOC)
	        {
	            GPIOC_PCLK_EN();
	        }else if (pGPIOx == GPIOD)
	        {
	            GPIOD_PCLK_EN();
	        }else if (pGPIOx == GPIOE)
	        {
	            GPIOE_PCLK_EN();
	        }else if (pGPIOx == GPIOF)
	        {
	            GPIOF_PCLK_EN();
	        }else if (pGPIOx == GPIOG)
	        {
	            GPIOG_PCLK_EN();
	        }else if (pGPIOx == GPIOH)
	        {
	            GPIOH_PCLK_EN();
	        }else if (pGPIOx == GPIOI)
	        {
	            GPIOI_PCLK_EN();
	        }
	    }
	    else
	    {
	        if(pGPIOx == GPIOA)
	        {
	            GPIOA_PCLK_DI();
	        }else if (pGPIOx == GPIOB)
	        {
	            GPIOB_PCLK_DI();
	        }else if (pGPIOx == GPIOC)
	        {
	            GPIOC_PCLK_DI();
	        }else if (pGPIOx == GPIOD)
	        {
	            GPIOD_PCLK_DI();
	        }else if (pGPIOx == GPIOE)
	        {
	            GPIOE_PCLK_DI();
	        }else if (pGPIOx == GPIOF)
	        {
	            GPIOF_PCLK_DI();
	        }else if (pGPIOx == GPIOG)
	        {
	            GPIOG_PCLK_DI();
	        }else if (pGPIOx == GPIOH)
	        {
	            GPIOH_PCLK_DI();
	        }else if (pGPIOx == GPIOI)
	        {
	            GPIOI_PCLK_DI();
	        }
	    }
}


/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initializes the GPIO port and pin according to the specified parameters in the handle
 *
 * @param[in]         - pointer to the GPIO handle structure
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_Init(GPIO_handle_t *pGPIOHandle){
   uint32_t temp=0;

   //enavble peripheral clock
   GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE );

   if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
   {
	   temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
	   pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			   pGPIOHandle->pGPIOx->MODER |= temp ;

   }else
   {
	   //later
	   if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT )
	   {
		   // CONFIGURE FALLING TRIGGER SELECTION RESISTOR FTSR

		   EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		   EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );


	   }else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
	   {
		   // CONFIGURE RISE TRIGGER SELECTION RESISTOR RTSR


		   EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		   EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );



	   }else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
	   {
		   // CONFIGURE FTSR AND RTSR

		   EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		   EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	   }
	   // GPIO PORT SELECTION IN SYSCFG_EXITCR
	   uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
	   uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
	   uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
	   SYSCFG_PCLK_EN();
	   SYSCFG->EXTICR[ temp1 ] = portcode << (temp2 * 4);



	   // ENABLE EXIT INTERRUPT DELIVERY USING IMR
	   EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
   }
   temp = 0;

       //2. configure the speed
       temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
       pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
       pGPIOHandle->pGPIOx->OSPEEDR |= temp;

       temp = 0;

       //3. configure the pupd settings
       temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
       pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
       pGPIOHandle->pGPIOx->PUPDR |= temp;

       temp = 0;

       //4. configure the optype
       temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
       pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
       pGPIOHandle->pGPIOx->OTYPER |= temp;

       //5. configure the alt functionality
       if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
       {
           //configure the alt function registers.
    	   uint8_t temp1, temp2;

    	   temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
    	   temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber  % 8;
    	   pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << ( 4 * temp2));
    	   pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * temp2));
       }

}


/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function de-initializes the GPIO port, resetting its registers to their default values
 *
 * @param[in]         - pointer to the GPIO handle structure
 *
 * @return            - none
 *
 * @Note              - none
 */


void GPIO_DeInit(GPIO_handle_t *pGPIOHandle){

}
/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This function reads the value from a specific GPIO pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number to read from
 * @param[in]         - value variable (Note: this parameter might be a typo in your code)
 *
 * @return            - 0 or 1 depending on the pin state
 *
 * @Note              - none
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}


/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This function reads the value of the entire GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 *
 * @return            - 16-bit value containing the state of the entire port
 *
 * @Note              - none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{



	uint16_t value;
		value = (uint16_t)pGPIOx->IDR;
		return value;

}


/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - This function writes a specific value (1 or 0) to a specific GPIO pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number to write to
 * @param[in]         - value to write (GPIO_PIN_SET or GPIO_PIN_RESET)
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber, uint8_t Value)
{

	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= ~( 1 << PinNumber);
	}else
	{
		pGPIOx->ODR &= ~( 1 << PinNumber);


	}



}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - This function writes a 16-bit value to the entire GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - 16-bit value to write to the port
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value)
{
	pGPIOx->ODR = Value ;

}




/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This function toggles the state of a specific GPIO pin
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - pin number to toggle
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber )
{
	pGPIOx->ODR ^= ( 1 << PinNumber );

}



/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - This function configures the IRQ number, priority, and enables/disables it
 *
 * @param[in]         - IRQ number to configure
 * @param[in]         - Priority for the IRQ
 * @param[in]         - ENABLE or DISABLE macros
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if ( EnorDi == ENABLE )
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) // 32 to 64
		{
			// program ISER1 register
			*NVIC_ISER1 |= ( 1 << IRQNumber % 32 );

		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			// program ISER2 register  // 64 to 96
			*NVIC_ISER3 |= ( 1 << IRQNumber % 64 );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
					// program ISER0 register
					*NVIC_ICER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) // 32 to 64
		{
					// program ISER1 register
					*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );

		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
					// program ISER2 register  // 64 to 96
					*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
}
}







void GPIO_IRQPriorityConfig(uint8_t IRQNumber , uint8_t IRQPriority)
{
	// lets find out ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;
	*(NVIC_PR_BASE_ADDR + iprx * 4) |= ( IRQPriority << shift_amount );
}














/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             - This function handles the interrupt for a specific GPIO pin
 *
 * @param[in]         - pin number where the interrupt occurred
 *
 * @return            - none
 *
 * @Note              - none
 */
void GPIO_IRQHandling(uint8_t PinNumber){
	// clear the exti pr register correspond
	if(EXTI ->PR & ( 1 << PinNumber ))
	{
		(EXTI ->PR |=  ( 1 << PinNumber ));
	}

}































