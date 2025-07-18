#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "adc.h"

volatile uint32_t sensor_val;

void my_delay()
{
	for(int i = 0;i<500000;++i){
		}
}
int main()
{
	uart2_rx_tx_init();
	pa1_adc_init();

	while(1)
	{
		adc1_start_conversion();
		sensor_val = adc1_read_data();
		printf("sensor_val = %lu...\r\n",sensor_val);
		//my_delay();
	}
}
