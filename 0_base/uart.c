#include "uart.h"
#include <stdio.h>

#define UART0_RX_WAIT()  while ((UART0_STATE & UART_STATE_RX_BF) == 0)

int uart0_read(char *ptrBuffer, int bufferLen)
{
    int i;

    for (i = 0; i < bufferLen; i++)
    {
        UART0_RX_WAIT();
        *ptrBuffer = UART0_DATA;
        ptrBuffer++;
    }

    return i;
}

int uart0_readLine(char *ptrBuffer, int bufferLen)
{
    char c = '\0';
    int i;

    for (i = 0; i < bufferLen; i++)
    {
        UART0_RX_WAIT();
        c = UART0_DATA;
        if(c == '\r') {
            *ptrBuffer = '\0';
            break;
        } else {
            *ptrBuffer = c;
            ptrBuffer++;
        }
    }

    return i;
}


uint8_t uart0_readU32(uint32_t *num) {
    static char buf[100];
    uart0_readLine(buf, 100);
    uint8_t i;
    *num = 0;
    for(i = 0; buf[i] != '\0'; i++) {
        *num = (*num * 10) + (buf[i] - '0');
    }
    return 1;
}
