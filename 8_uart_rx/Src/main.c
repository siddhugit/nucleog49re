#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "led.h"


int main()
{
	led_usr_init();
	uart2_rx_tx_init();
	while(1){
		char ch = uart2_read();
		if(ch == '1'){
			do_led_usr_on();
		}
		else{
			do_led_usr_off();
		}
		printf("%c\r\n",ch);
	}
}
