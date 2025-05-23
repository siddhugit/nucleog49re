#include <stdio.h>
#include <stdint.h>
//#include "stm32g491xx.h"

#define __IO  volatile

//Where is user led
//PA5 ( from user manual)
//port: A
//pin: 5
//Bus: AHB2

//To get to PA5 look into datasheet for memory map

#define PERIPH_BASE (0x40000000UL)
#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB2PERIPH_OFFSET (0x08000000UL)
#define APB1PERIPH_OFFSET (0x00000000UL)
#define APB2PERIPH_OFFSET (0x00010000UL)

#define AHB1_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define AHB2_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)
#define APB1_BASE (PERIPH_BASE + APB1PERIPH_OFFSET)
#define APB2_BASE (PERIPH_BASE + APB2PERIPH_OFFSET)


#define GPIOA_OFFSET (0x00000000UL)
#define GPIOA_BASE (AHB2_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x00001000UL)
#define RCC_BASE (AHB1_BASE + RCC_OFFSET)

#define AHB2EN_R_OFFSET (0x4CUL)
#define RCC_AHB2EN_R (volatile uint32_t*)(RCC_BASE + AHB2EN_R_OFFSET)

#define MODE_R_OFFSET (0x0UL)
#define GPIOA_MODE_R (volatile uint32_t*)(GPIOA_BASE + MODE_R_OFFSET)
#define GPIOB_MODE_R (volatile uint32_t*)(GPIOB_BASE + MODE_R_OFFSET)
#define GPIOC_MODE_R (volatile uint32_t*)(GPIOC_BASE + MODE_R_OFFSET)
#define GPIOD_MODE_R (volatile uint32_t*)(GPIOD_BASE + MODE_R_OFFSET)
#define GPIOE_MODE_R (volatile uint32_t*)(GPIOE_BASE + MODE_R_OFFSET)
#define GPIOF_MODE_R (volatile uint32_t*)(GPIOF_BASE + MODE_R_OFFSET)
#define GPIOG_MODE_R (volatile uint32_t*)(GPIOG_BASE + MODE_R_OFFSET)

#define OD_R_OFFSET (0x14UL)
#define GPIOA_OD_R (volatile uint32_t*)(GPIOA_BASE + OD_R_OFFSET)
#define GPIOB_OD_R (volatile uint32_t*)(GPIOB_BASE + OD_R_OFFSET)
#define GPIOC_OD_R (volatile uint32_t*)(GPIOC_BASE + OD_R_OFFSET)
#define GPIOD_OD_R (volatile uint32_t*)(GPIOD_BASE + OD_R_OFFSET)
#define GPIOE_OD_R (volatile uint32_t*)(GPIOE_BASE + OD_R_OFFSET)
#define GPIOF_OD_R (volatile uint32_t*)(GPIOF_BASE + OD_R_OFFSET)
#define GPIOG_OD_R (volatile uint32_t*)(GPIOG_BASE + OD_R_OFFSET)

#define GPIOAEN (1U<<0)
#define GPIOBEN (1U<<1)
#define GPIOCEN (1U<<2)
#define GPIODEN (1U<<3)
#define GPIOEEN (1U<<4)
#define GPIOFEN (1U<<5)
#define GPIOGEN (1U<<6)

#define PIN5 (1U<<5)
#define LED_USR PIN5

typedef struct
{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
}GPIO_Typedef;

typedef struct
{
  __IO uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
  __IO uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
  __IO uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
  __IO uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
  uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x10 */
  uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x14 */
  __IO uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
  __IO uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
  __IO uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x24 */
  __IO uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  __IO uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  __IO uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x34 */
  __IO uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
  __IO uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
  __IO uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
  uint32_t      RESERVED4;   /*!< Reserved,                                                                Address offset: 0x44 */
  __IO uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
  __IO uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
  __IO uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
  uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x54 */
  __IO uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
  __IO uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
  __IO uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
  uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x64 */
  __IO uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
  __IO uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
  __IO uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
  uint32_t      RESERVED7;   /*!< Reserved,                                                                Address offset: 0x74 */
  __IO uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
  __IO uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
  __IO uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
  uint32_t      RESERVED8;   /*!< Reserved,                                                                Address offset: 0x84 */
  __IO uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
  uint32_t      RESERVED9;   /*!< Reserved,                                                                Address offset: 0x8C */
  __IO uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
  __IO uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
  __IO uint32_t CRRCR;       /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
  __IO uint32_t CCIPR2;      /*!< RCC peripherals independent clock configuration register 2,              Address offset: 0x9C */
} RCC_TypeDef;


#define GPIOA ((GPIO_Typedef*)GPIOA_BASE)
#define RCC ((RCC_TypeDef*)RCC_BASE)

int main()
{
	//(1) Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//(2) Set PA5 as output mode
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);



	//(3) forever loop
	for(;;){
		//(4) toggle output register
		GPIOA->ODR ^= (LED_USR);
		//(5) cause delay
		for(int i = 0;i<500000;++i){

		}
	}
}
