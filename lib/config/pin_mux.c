/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#include <pinout.h>

void BOARD_InitPins(void)
{
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinMux(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, kPORT_MuxAlt2);
	PORT_SetPinMux(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, kPORT_MuxAlt2);

	/* LED Builtin */
	PORT_SetPinMux(BUILTIN_LED_PORT, BUILTIN_LED_PIN, kPORT_MuxAsGpio);

	/* Display */
	PORT_SetPinMux(DISPLAY_SEGMENT_A_PORT, DISPLAY_SEGMENT_A_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_B_PORT, DISPLAY_SEGMENT_B_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_C_PORT, DISPLAY_SEGMENT_C_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_D_PORT, DISPLAY_SEGMENT_D_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_E_PORT, DISPLAY_SEGMENT_E_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_F_PORT, DISPLAY_SEGMENT_F_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SEGMENT_G_PORT, DISPLAY_SEGMENT_G_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SECTION_1_PORT, DISPLAY_SECTION_1_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SECTION_2_PORT, DISPLAY_SECTION_2_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(DISPLAY_SECTION_3_PORT, DISPLAY_SECTION_3_PIN, kPORT_MuxAsGpio);

	SIM->SOPT5 = ((SIM->SOPT5 &
				   (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK))) |
				  SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX) | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX));
}