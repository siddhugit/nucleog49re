#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"


int timestamp = 0;
int main()
{
	uart2_rx_tx_init();
	tim2_output_compare(2000u); //5 seconds
	void tim3_intput_capture();
	while(1)
	{
		//wait for UIF
		while(!(TIM3->SR & SR_CCIF)){}
		//clear UIF
		timestamp = TIM3->CCR1;
	}
}
