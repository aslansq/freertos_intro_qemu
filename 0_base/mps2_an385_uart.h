#ifndef MPS2_AN385_UART_H
#define MPS2_AN385_UART_H

#include <stdint.h>

// qemu repo https://github.com/qemu/qemu.git
// uart base addresses hw/arm/mps2.c
// bit mapping and register offsets hw/char/cmsdk-apb-uart.c
#define UART_DATA_OFFSET  (0UL)
#define UART_STATE_OFFSET (4UL)
#define UART_CTRL_OFFSET  (8UL)
#define UART_INT_OFFSET   (12UL)
#define UART_BAUD_OFFSET  (16UL)
// state register bit def
#define UART_STATE_TX_BF ((uint32_t)1 << 0)
#define UART_STATE_RX_BF ((uint32_t)1 << 1)
// ctrl register bit def
#define UART0_CTRL_TX_EN ((uint32_t)1 << 0)
#define UART0_CTRL_RX_EN ((uint32_t)1 << 1)
// int register bit def
#define UART0_INT_TX     ((uint32_t)1 << 0)
#define UART0_INT_RX     ((uint32_t)1 << 1)

#define UART0_ADDRESS    ( 0x40004000UL ) // uart0 base address
#define UART0_DATA       ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + UART_DATA_OFFSET ) ) ) )
#define UART0_STATE      ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + UART_STATE_OFFSET) ) ) )
#define UART0_CTRL       ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + UART_CTRL_OFFSET ) ) ) )
#define UART0_INT        ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + UART_INT_OFFSET  ) ) ) )
#define UART0_BAUDDIV    ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + UART_BAUD_OFFSET ) ) ) )

#define UART1_ADDRESS    ( 0x40005000UL ) // uart1 base address
#define UART1_DATA       ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + UART_DATA_OFFSET ) ) ) )
#define UART1_STATE      ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + UART_STATE_OFFSET) ) ) )
#define UART1_CTRL       ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + UART_CTRL_OFFSET ) ) ) )
#define UART1_INT        ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + UART_INT_OFFSET  ) ) ) )
#define UART1_BAUDDIV    ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + UART_BAUD_OFFSET ) ) ) )

#endif // MPS2_AN385_UART_H