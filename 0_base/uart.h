#ifndef BASE_UART_H
#define BASE_UART_H

#include <stdint.h>

#define UART0_ADDRESS    ( 0x40004000UL )
#define UART0_DATA       ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE      ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART_STATE_TX_BF ((uint32_t)1 << 0)
#define UART_STATE_RX_BF ((uint32_t)1 << 1)
#define UART0_CTRL       ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_CTRL_TX_EN ((uint32_t)1 << 0)
#define UART0_CTRL_RX_EN ((uint32_t)1 << 1)
#define UART0_INT        ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 12UL ) ) ) )
#define UART0_INT_TX     ((uint32_t)1 << 0)
#define UART0_INT_RX     ((uint32_t)1 << 1)
#define UART0_BAUDDIV    ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK   ( 1UL )

int uart0_read(char *ptrBuffer, int bufferLen);
/**
 * @retval -1 : if does not fit into buffer
 * @retval 0 to n : number of character read
 */
int uart0_readLine(char *ptrBuffer, int bufferLen);
/**
 * this has internal buffer of 100. not all the checks implemented since this is just demo code
 */
uint8_t uart0_readU32(uint32_t *num);
#endif // BASE_UART_H