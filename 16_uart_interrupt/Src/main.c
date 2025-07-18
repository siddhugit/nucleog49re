#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "led.h"

void my_usart2_handler()
{
	volatile char ch = (USART2->RDR & 0xFF);
	printf("%c\r\n",ch);
	if(ch == '1'){
		do_led_usr_on();
	}
	else{
		do_led_usr_off();
	}
}

void USART2_IRQHandler()
{
	//Make sure rx data register is ready to be read
	if(USART2->ISR & SR_RXE)
	{
		my_usart2_handler();
	}
}

int main()
{
	led_usr_init();
	uart2_rx_tx_interrupt_init();
	while(1){

	}
}
