#include <stdio.h>
#include <stdint.h>
#include "stm32g491xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"



int main()
{
	uart2_rx_tx_init();
	tim2_output_compare(2000u); //5 seconds
}
