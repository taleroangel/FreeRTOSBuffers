#include "pin_mux.h"
#include "fsl_common.h"
#include "fsl_port.h"

#include <pinout.h>

void BOARD_InitPins(void) {

  /* Enable CLOCK ports */
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);
  CLOCK_EnableClock(kCLOCK_PortE);

  /* Enable external UART */
  PORT_SetPinMux(UART_TX_PORT, UART_TX_PIN, kPORT_MuxAlt3);
  PORT_SetPinMux(UART_RX_PORT, UART_RX_PIN, kPORT_MuxAlt3);

  /* LED Builtin */
  PORT_SetPinMux(BUILTIN_LED_PORT, BUILTIN_LED_PIN, kPORT_MuxAsGpio);

  /* Display */
  PORT_SetPinMux(DISPLAY_SEGMENT_A_PORT, DISPLAY_SEGMENT_A_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_B_PORT, DISPLAY_SEGMENT_B_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_C_PORT, DISPLAY_SEGMENT_C_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_D_PORT, DISPLAY_SEGMENT_D_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_E_PORT, DISPLAY_SEGMENT_E_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_F_PORT, DISPLAY_SEGMENT_F_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SEGMENT_G_PORT, DISPLAY_SEGMENT_G_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SECTION_1_PORT, DISPLAY_SECTION_1_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SECTION_2_PORT, DISPLAY_SECTION_2_PIN,
                 kPORT_MuxAsGpio);
  PORT_SetPinMux(DISPLAY_SECTION_3_PORT, DISPLAY_SECTION_3_PIN,
                 kPORT_MuxAsGpio);

  SIM->SOPT5 = ((SIM->SOPT5 &
                 /* Mask bits to zero which are setting */
                 (~(SIM_SOPT5_UART1TXSRC_MASK | SIM_SOPT5_UART1RXSRC_MASK)))

                /* UART1 Transmit Data Source Select: UART1_TX pin. */
                | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX)

                /* UART1 Receive Data Source Select: UART1_RX pin. */
                | SIM_SOPT5_UART1RXSRC(SOPT5_UART1RXSRC_UART_RX));
}