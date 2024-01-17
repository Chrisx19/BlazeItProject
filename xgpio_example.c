#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"

#define SWITCH_CHANNEL 1
#define LED_CHANNEL    2
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

    // 0x0000 for all the LED output on A7 which are 16 bit
    XGpio_SetDataDirection(&gpio, LED_CHANNEL, 0x0000);
    // 0xFFFE for all the Switch input on A7 which are 16 bit
	XGpio_SetDataDirection(&gpio, SWITCH_CHANNEL, 0xFFFE);
	bool temp = false;
	while (1) {
    	dataRead = XGpio_DiscreteRead(&gpio, 1);

    	if (dataRead == 1) {
    		temp = true;
    	} else {
    		temp = false;
    	}

    	xil_printf("%d\n", temp);
    	if (temp) {
			for (int i=0; i<30; i++) {
				int count = (i < LED_COUNT) ? i: 30 - i;
				XGpio_DiscreteWrite(&gpio, LED_CHANNEL, (1 << count));
				usleep(1000 * 50);
				XGpio_DiscreteClear(&gpio, LED_CHANNEL, (1 << count));
				usleep(1000 * 50);
			}
    	}
	}

    cleanup_platform();
    return 0;
}
