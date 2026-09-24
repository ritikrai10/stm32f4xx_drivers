/*
 * stm32f407xx.h
 *
 *  Created on: Jul 17, 2026
 *      Author: ritikrai
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>

#define __vo volatile




// nvic ISER REGISTERS ADDRESSE

#define NVIC_ISER0                  ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1                  ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2                  ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3                  ((__vo uint32_t*)0xE000E10c)



// nvic ICER REGISTERS ADDRESSE



#define NVIC_ICER0                  ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1                  ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2                  ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3                  ((__vo uint32_t*)0xE000E18C)


//priority registers address calculation ipr

#define NVIC_PR_BASE_ADDR           ((__vo uint32_t*)0xE000E400)


// no of priority bits implemented in priority register
#define NO_PR_BITS_IMPLEMENTED              4




#define FLASH_BASEADDR         0x08000000U
#define SRAM1_BASEADDR         0x20000000U
#define SRAM2_BASEADDR         0x20001C00U
#define ROM_BASEADDR           0x1FFF0000U
#define SRAM                   SRAM1_BASEADDR




#define PERIPH_BASEADDR                0x40000000U
#define APB1PERIPH_BASEADDR        PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR        0x40010000U
#define AHB1PERIPH_BASEADDR        0x40020000U
#define AHB2PERIPH_BASEADDR        0x50000000U



#define GPIOA_BASEADDR         (AHB1PERIPH_BASEADDR + 0X0000)
#define GPIOB_BASEADDR         (AHB1PERIPH_BASEADDR + 0X0400)
#define GPIOC_BASEADDR         (AHB1PERIPH_BASEADDR + 0X0800)
#define GPIOD_BASEADDR         (AHB1PERIPH_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR         (AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR         (AHB1PERIPH_BASEADDR + 0X1400)
#define GPIOG_BASEADDR         (AHB1PERIPH_BASEADDR + 0X1800)
#define GPIOH_BASEADDR         (AHB1PERIPH_BASEADDR + 0X1C00)
#define GPIOI_BASEADDR         (AHB1PERIPH_BASEADDR + 0X2000)
#define RCC_BASEADDR           (AHB1PERIPH_BASEADDR + 0X3800)




#define I2C1_BASEADDR           (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR           (APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR           (APB1PERIPH_BASEADDR + 0x5C00)


// SPI PERIPHERAL BASE ADDR
#define SPI2_BASEADDR           (APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR           (APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR         (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR         (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR          (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR          (APB1PERIPH_BASEADDR + 0x5000)



#define EXTI_BASEADDR               (APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR               (APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR             (APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR             (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR             (APB2PERIPH_BASEADDR + 0x1400)




typedef struct
{
	__vo uint32_t MODER ;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;






typedef struct
{
    __vo uint32_t CR;
    __vo uint32_t PLLCFGR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;
    __vo uint32_t AHB1RSTR;
    __vo uint32_t AHB2RSTR;
    __vo uint32_t AHB3RSTR;
    uint32_t      RESERVED0;
    __vo uint32_t APB1RSTR;
    __vo uint32_t APB2RSTR;
    uint32_t      RESERVED1[2];
    __vo uint32_t AHB1ENR;
    __vo uint32_t AHB2ENR;
    __vo uint32_t AHB3ENR;
    uint32_t      RESERVED2;
    __vo uint32_t APB1ENR;
    __vo uint32_t APB2ENR;
    uint32_t      RESERVED3[2];
    __vo uint32_t AHB1LPENR;
    __vo uint32_t AHB2LPENR;
    __vo uint32_t AHB3LPENR;
    uint32_t      RESERVED4;
    __vo uint32_t APB1LPENR;
    __vo uint32_t APB2LPENR;
    uint32_t      RESERVED5[2];
    __vo uint32_t BDCR;
    __vo uint32_t CSR;
    uint32_t      RESERVED6[2];
    __vo uint32_t SSCGR;
    __vo uint32_t PLLI2SCFGR;
} RCC_RegDef_t;










typedef struct
{
	__vo uint32_t IMR ;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;

}EXTI_RegDef_t;




// peripheral register defination
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
}SPI_RegDef_t;






typedef struct
{
	__vo uint32_t MEMRMP ;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED0[2];
	__vo uint32_t CMPCR;
	uint32_t RESERVED1[2];
	__vo uint32_t CFGR;

}SYSCFG_RegDef_t;









#define GPIOA                  ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                  ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                  ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                  ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                  ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                  ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                  ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH                  ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI                  ((GPIO_RegDef_t*)GPIOI_BASEADDR)


#define RCC                    ((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI                   ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG                 ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)



#define SPI1                   ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2                   ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3                   ((SPI_RegDef_t*)SPI3_BASEADDR)



#define GPIOA_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 0) )
#define GPIOB_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 1) )
#define GPIOC_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 2) )
#define GPIOD_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 3) )
#define GPIOE_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 4) )
#define GPIOF_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 5) )
#define GPIOG_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 6) )
#define GPIOH_PCLK_EN()    ( RCC ->AHB1ENR |= ( 1 << 7) )
#define GPIOI_PCLK_EN()     ( RCC ->AHB1ENR |= ( 1 << 8) )







#define I2C1_PCLK_EN()    ( RCC ->APB1ENR |= ( 1 << 21) )
#define I2C2_PCLK_EN()    ( RCC ->APB1ENR |= ( 1 << 22) )
#define I2C3_PCLK_EN()    ( RCC ->APB1ENR |= ( 1 << 23) )




// spi clock enable macrps
#define SPI1_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 12) )
#define SPI2_PCLK_EN()    ( RCC ->APB1ENR |= ( 1 << 14) )
#define SPI3_PCLK_EN()    ( RCC ->APB1ENR |= ( 1 << 15) )
#define SPI4_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 13) )

//DISABLE
#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~(1 << 13))




#define USART1_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 4) )
#define USART2_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 17) )
#define USART3_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 18) )
#define UART4_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 19) )
#define UART5_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 20) )
#define UART6_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 5) )




#define SYSCFG_PCLK_EN()    ( RCC ->APB2ENR |= ( 1 << 14) )




#define GPIOA_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 0) )
#define GPIOB_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 1) )
#define GPIOC_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 2) )
#define GPIOD_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 3) )
#define GPIOE_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 4) )
#define GPIOF_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 5) )
#define GPIOG_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 6) )
#define GPIOH_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 7) )
#define GPIOI_PCLK_DI()    ( RCC ->AHB1ENR &= ~( 1 << 8) )


#define GPIOA_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 0)); (( RCC ->AHB1RSTR |= ( 1 << 0)); }while(0)
#define GPIOB_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 1)); (( RCC ->AHB1RSTR |= ( 1 << 1)); }while(0)
#define GPIOC_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 2)); (( RCC ->AHB1RSTR |= ( 1 << 2)); }while(0)
#define GPIOD_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 3)); (( RCC ->AHB1RSTR |= ( 1 << 3)); }while(0)
#define GPIOE_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 4)); (( RCC ->AHB1RSTR |= ( 1 << 4)); }while(0)
#define GPIOF_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 5)); (( RCC ->AHB1RSTR |= ( 1 << 5)); }while(0)
#define GPIOG_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 6)); (( RCC ->AHB1RSTR |= ( 1 << 6)); }while(0)
#define GPIOH_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 7)); (( RCC ->AHB1RSTR |= ( 1 << 7)); }while(0)
#define GPIOI_REG_RESET()      do{( RCC ->AHB1RSTR |= ( 1 << 8)); (( RCC ->AHB1RSTR |= ( 1 << 8)); }while(0)


#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA)?0:\
                                        (x == GPIOB)?1:\
                                        (x == GPIOC)?2:\
                                        (x == GPIOD)?3:\
                                        (x == GPIOE)?4:\
                                        (x == GPIOF)?5:\
                                        (x == GPIOG)?6:\
                                        (x == GPIOH)?7:\
                                        (x == GPIOI)?8:0 )

// IRQ(INTERRUPT REQUEST NUMBER OF STM32 .


#define IRQ_NO_EXTI0            6
#define IRQ_NO_EXTI1            7
#define IRQ_NO_EXTI2            8
#define IRQ_NO_EXTI3            9
#define IRQ_NO_EXTI4            10
#define IRQ_NO_EXTI9_5          23
#define IRQ_NO_EXTI5_10         40





// macros for all possible priority

#define NVIC_IRQ_PRI0           0
#define NVIC_IRQ_PRI15          15






#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE
#define GPIO_PIN_SET            SET
#define GPIO_PIN_RESET          RESET
#define FLAG_RESET              RESET
#define FLAG_SET                SET









// bitposition definition of spi peripherals FOR CR1
#define SPI_CR1_CPHA                   0
#define SPI_CR1_CPOL                   1
#define SPI_CR1_BR                     3
#define SPI_CR1_SPE                    6
#define SPI_CR1_LSBFIRST               7
#define SPI_CR1_SSI                    8
#define SPI_CR1_SSM                    9
#define SPI_CR1_RXONLY                 10
#define SPI_CR1_DFF                    11
#define SPI_CR1_CRCNEXT                12
#define SPI_CR1_CRCEN                  13
#define SPI_CR1_BIDIOE                 14
#define SPI_CR1_BIDIMODE               15



// bitposition definition of spi peripherals CR2
#define SPI_CR2_RXDMAEN                   0
#define SPI_CR2_TXDMAEN                   1
#define SPI_CR2_SSOE                      2
#define SPI_CR2_FRF                       4
#define SPI_CR2_ERRIE                     5
#define SPI_CR2_RXNEIE                    6
#define SPI_CR2_TXEIE                     7

// FOR SR SPI PERIPHERALS
#define SPI_SR_RXNE                       0
#define SPI_SR_TXE                        1
#define SPI_SR_CHSIDE                     2
#define SPI_SR_UDR                        3
#define SPI_SR_CRCERR                     4
#define SPI_SR_MODF                       5
#define SPI_SR_OVR                        6
#define SPI_SR_BSY                        7
#define SPI_SR_FRE                        8






#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"




#endif /* INC_STM32F407XX_H_ */



















































