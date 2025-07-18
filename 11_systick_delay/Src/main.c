#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "systick.h"


#define APP_DELAY_MS 5000U

int main()
{
	uart2_rx_tx_init();
	while(1)
	{
		printf("Wait for %u milliseconds...\r\n",APP_DELAY_MS);
		systick_ms_delay(5000);
	}
}
