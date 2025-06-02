#include <stdio.h>
#include <stdint.h>
#include "uart.h"


int main()
{
	uart2_tx_init();
	while(1){
		printf("From modular uart_tx driver.....\n\r");
	}
}
