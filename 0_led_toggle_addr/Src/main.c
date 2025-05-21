#include <stdio.h>
#include <stdint.h>

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

//set mode of PA5 to output
//|=(1U<<10)
//&=~(1U<<11)

int main()
{
	//(1) Enable clock access to GPIOA
	*RCC_AHB2EN_R |= GPIOAEN;
	//(2) Set PA5 as output mode
	*GPIOA_MODE_R |= (1U<<10);
	*GPIOA_MODE_R &= ~(1U<<11);
	//(3) forever loop
	for(;;){
		//(4) toggle output register
		*GPIOA_OD_R ^= (LED_USR);
		//(5) cause delay
		for(int i = 0;i<1000000;++i){

		}
	}
}
