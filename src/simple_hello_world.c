#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"

int main(void)
{
	char ch;

	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	PRINTF("Hello world!, from my Meson project\r\n");

	while (1)
	{
		ch = GETCHAR();
		PUTCHAR(ch);
	}
}
