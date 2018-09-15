/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2017-2018 Gauthier Briere
  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

//#include "grbl.h"
#include <string.h>
#include "main.h"
#include "Config.h"
#include "System.h"
#include "Serial.h"
#include "MotionControl.h"

#define RX_RING_BUFFER (RX_BUFFER_SIZE+1)
#define TX_RING_BUFFER (TX_BUFFER_SIZE+1)

uint8_t serial_rx_buffer[RX_RING_BUFFER];
uint8_t serial_rx_buffer_head = 0;
volatile uint8_t serial_rx_buffer_tail = 0;

uint8_t serial_tx_buffer[TX_RING_BUFFER];
uint8_t serial_tx_buffer_head = 0;
volatile uint8_t serial_tx_buffer_tail = 0;


// Returns the number of bytes available in the RX serial buffer.
uint8_t Serial_GetRxBufferAvailable()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(RX_BUFFER_SIZE - (serial_rx_buffer_head-rtail)); }
  return((rtail-serial_rx_buffer_head-1));
}


// Returns the number of bytes used in the RX serial buffer.
// NOTE: Deprecated. Not used unless classic status reports are enabled in config.h.
uint8_t Serial_GetRxBufferCount()
{
  uint8_t rtail = serial_rx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_rx_buffer_head >= rtail) { return(serial_rx_buffer_head-rtail); }
  return (RX_BUFFER_SIZE - (rtail-serial_rx_buffer_head));
}


// Returns the number of bytes used in the TX serial buffer.
// NOTE: Not used except for debugging and ensuring no TX bottlenecks.
uint8_t Serial_GetTxBufferCount()
{
  uint8_t ttail = serial_tx_buffer_tail; // Copy to limit multiple calls to volatile
  if (serial_tx_buffer_head >= ttail) { return(serial_tx_buffer_head-ttail); }
  return (TX_RING_BUFFER - (ttail-serial_tx_buffer_head));
}


void Serial_Init()
{
  LL_USART_EnableIT_RXNE(USART1);
}


// Writes one byte to the TX serial buffer. Called by main program.
void Serial_Write(uint8_t data) {
  // Calculate next head
  uint8_t next_head = serial_tx_buffer_head + 1;
  if (next_head == TX_RING_BUFFER) { next_head = 0; }

  // Wait until there is space in the buffer
  while (next_head == serial_tx_buffer_tail) {
    // TODO: Restructure st_prep_buffer() calls to be executed here during a long print.
    if (sys_rt_exec_state & EXEC_RESET) { return; } // Only check for abort to avoid an endless loop.
  }

  // Store data and advance head
  serial_tx_buffer[serial_tx_buffer_head] = data;
  serial_tx_buffer_head = next_head;

  // Enable Data Register Empty Interrupt to make sure tx-streaming is running
  if(! LL_USART_IsEnabledIT_TXE(USART1))
  {
    LL_USART_EnableIT_TXE(USART1);
  }
}


// Data Register Empty Interrupt handler
void Serial_ISR_TXE()
{
  uint8_t tail = serial_tx_buffer_tail; // Temporary serial_tx_buffer_tail (to optimize for volatile)

  if (tail == serial_tx_buffer_head) {
    LL_USART_DisableIT_TXE(USART1);
  }
  else {
    // Send a byte from the buffer
    LL_USART_TransmitData8(USART1, serial_tx_buffer[tail]);

    // Update tail position
    tail++;
    if (tail == TX_RING_BUFFER) { tail = 0; }

    serial_tx_buffer_tail = tail;
  }

}


// Fetches the first byte in the serial read buffer. Called by main program.
uint8_t Serial_Read(char *c)
{
  uint8_t tail = serial_rx_buffer_tail; // Temporary serial_rx_buffer_tail (to optimize for volatile)
  if (serial_rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  } else {
    *c = serial_rx_buffer[tail];

    tail++;
    if (tail == RX_RING_BUFFER) { tail = 0; }
    serial_rx_buffer_tail = tail;

    return SERIAL_GOT_DATA;
  }
}


void Serial_ISR_RXNE()
{
  uint8_t data;
  uint8_t next_head;

  data = LL_USART_ReceiveData8(USART1);

  // Pick off realtime command characters directly from the serial stream. These characters are
  // not passed into the main buffer, but these set system state flag bits for realtime execution.
  switch (data) {
    case CMD_RESET:         MC_Reset(); break; // Call motion control reset routine.
    case CMD_STATUS_REPORT: System_SetExecStateFlag(EXEC_STATUS_REPORT); break; // Set as true
    case CMD_CYCLE_START:   System_SetExecStateFlag(EXEC_CYCLE_START); break; // Set as true
    case CMD_FEED_HOLD:     System_SetExecStateFlag(EXEC_FEED_HOLD); break; // Set as true
    default :
      if (data > 0x7F) { // Real-time control characters are extended ACSII only.
        switch(data) {
          case CMD_SAFETY_DOOR:   System_SetExecStateFlag(EXEC_SAFETY_DOOR); break; // Set as true
          case CMD_JOG_CANCEL:
            if (sys.state & STATE_JOG) { // Block all other states from invoking motion cancel.
              System_SetExecStateFlag(EXEC_MOTION_CANCEL);
              Serial_ResetRxBuffer(); // Vide un reste éventuel de données dans le buffer
            }
            break;
          #ifdef DEBUG
            case CMD_DEBUG_REPORT: {uint8_t sreg = SREG; cli(); bit_true(sys_rt_exec_debug,EXEC_DEBUG_REPORT); SREG = sreg;} break;
          #endif
          case CMD_FEED_OVR_RESET: System_SetExecMotionOverrideFlag(EXEC_FEED_OVR_RESET); break;
          case CMD_FEED_OVR_COARSE_PLUS: System_SetExecMotionOverrideFlag(EXEC_FEED_OVR_COARSE_PLUS); break;
          case CMD_FEED_OVR_COARSE_MINUS: System_SetExecMotionOverrideFlag(EXEC_FEED_OVR_COARSE_MINUS); break;
          case CMD_FEED_OVR_FINE_PLUS: System_SetExecMotionOverrideFlag(EXEC_FEED_OVR_FINE_PLUS); break;
          case CMD_FEED_OVR_FINE_MINUS: System_SetExecMotionOverrideFlag(EXEC_FEED_OVR_FINE_MINUS); break;
          case CMD_RAPID_OVR_RESET: System_SetExecMotionOverrideFlag(EXEC_RAPID_OVR_RESET); break;
          case CMD_RAPID_OVR_MEDIUM: System_SetExecMotionOverrideFlag(EXEC_RAPID_OVR_MEDIUM); break;
          case CMD_RAPID_OVR_LOW: System_SetExecMotionOverrideFlag(EXEC_RAPID_OVR_LOW); break;
          case CMD_SPINDLE_OVR_RESET: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_RESET); break;
          case CMD_SPINDLE_OVR_COARSE_PLUS: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_COARSE_PLUS); break;
          case CMD_SPINDLE_OVR_COARSE_MINUS: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_COARSE_MINUS); break;
          case CMD_SPINDLE_OVR_FINE_PLUS: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_FINE_PLUS); break;
          case CMD_SPINDLE_OVR_FINE_MINUS: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_FINE_MINUS); break;
          case CMD_SPINDLE_OVR_STOP: System_SetExecAccessoryOverrideFlag(EXEC_SPINDLE_OVR_STOP); break;
          case CMD_COOLANT_FLOOD_OVR_TOGGLE: System_SetExecAccessoryOverrideFlag(EXEC_COOLANT_FLOOD_OVR_TOGGLE); break;
          case CMD_COOLANT_MIST_OVR_TOGGLE: System_SetExecAccessoryOverrideFlag(EXEC_COOLANT_MIST_OVR_TOGGLE); break;
        }
        // Throw away any unfound extended-ASCII character by not passing it to the serial buffer.
      } else { // Write character to buffer
        next_head = serial_rx_buffer_head + 1;
        if (next_head == RX_RING_BUFFER) { next_head = 0; }

        // Write data to buffer unless it is full.
        if (next_head != serial_rx_buffer_tail) {
          serial_rx_buffer[serial_rx_buffer_head] = data;
          serial_rx_buffer_head = next_head;
        }
      }
  }
}


void Serial_ResetRxBuffer()
{
  serial_rx_buffer_tail = serial_rx_buffer_head;
}


void Serial_PutString(const char* str)
{
  int i;
  int len = strlen(str);
  for(i=0; i<len; i++)
  {
    Serial_Write(str[i]);
  }
}
