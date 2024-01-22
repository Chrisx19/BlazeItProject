#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartlite.h"
#include "xparameters.h"

XUartLite_Config *uart_config;
XUartLite uart;

void uart_init(){

	uart_config = XUartLite_LookupConfig(XPAR_AXI_UARTLITE_0_DEVICE_ID);
	int status = XUartLite_CfgInitialize(&uart, uart_config, uart_config->RegBaseAddr);
	if(status == XST_SUCCESS)
		xil_printf("UART INIT SUCCESSFUL\n");
	else
		xil_printf("UART INIT FAILED\n");

	while(XUartLite_IsSending(&uart));
	XUartLite_ResetFifos(&uart);

	status = XUartLite_SelfTest(&uart);
	if(status == XST_SUCCESS)
		xil_printf("UART SELF TEST SUCCESSFUL\n");
	else
		xil_printf("UART SELF TEST  FAILED\n");

	while(XUartLite_IsSending(&uart));
	XUartLite_ResetFifos(&uart);

}

int main()
{
	int count = 0;
	u8 dataReceived[11];
	uart_init();

	while (count != 11) {
		count += XUartLite_Recv(&uart, &dataReceived[count], 11);
	}

	xil_printf("Transmission Complete\n");

	while(XUartLite_IsSending(&uart));
	XUartLite_ResetFifos(&uart);

	for(int i=0; i < 11; i++) {
		xil_printf("%0c", dataReceived[i]);
	}


    return 0;
}
