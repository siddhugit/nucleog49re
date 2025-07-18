#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"



int main()
{
	uart2_rx_tx_init();
	tim2_init(5000u); //5 seconds

	while(1)
	{
		//wait for UIF
		while(!(TIM2->SR & SR_UIF)){}
		//clear UIF
		TIM2->SR &= ~SR_UIF;
		printf("5 second elapsed...\r\n");
	}
}
