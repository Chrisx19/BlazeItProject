#include <stdio.h>
#include <unistd.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

#define LED_CHANNEL 1
#define LED_COUNT 16

XGpio_Config *gpio_config;
XGpio gpio;

void gpio_init(void){

	gpio_config = XGpio_LookupConfig(XPAR_AXI_GPIO_0_DEVICE_ID);
	int status = XGpio_CfgInitialize(&gpio, gpio_config, gpio_config->BaseAddress);
   if(status == XST_SUCCESS)
	   xil_printf("GPIO INIT SUCCESSFUL\n");
   else
	   xil_printf("GPIO INIT FAILED\n");
}


int main()
{
	volatile uint32_t dataRead = 0;
    init_platform();
    gpio_init();
    // 0xFFFE for all the Switch input on A7 which are 16 bit
	XGpio_SetDataDirection(&gpio, LED_CHANNEL, 0xFFFE);

	while (1) {
		//reads input
		dataRead = XGpio_DiscreteRead(&gpio, LED_CHANNEL);
		//basically print() but lighter weight
		xil_printf("Value Read SW: %0d\n", dataRead);
		sleep(1);
	}

    cleanup_platform();
    return 0;
}
