#include <stdio.h>
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
	uart_init();
	u8 data[] = "Hello World";


	XUartLite_Send(&uart, &data[0], 11);
	while(XUartLite_IsSending(&uart));
	XUartLite_ResetFifos(&uart);


    return 0;
}
