#include "uart.h"
#include <stdio.h>

#define UART0_RX_WAIT()  while ((UART0_STATE & UART_STATE_RX_BF) == 0)
// wait until it is available to put a char to uart1 tx buffer
#define UART1_TX_WAIT_AVAIL() while( ( UART1_STATE & UART_STATE_TX_BF ) != 0 )

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
    int retVal = 0;

    for (i = 0; i < bufferLen; i++)
    {
        UART0_RX_WAIT();
        c = UART0_DATA;
        if(c == '\r') {
            ptrBuffer[i] = '\0';
            break;
        } else {
            ptrBuffer[i] = c;
        }
    }

    if((i == (bufferLen-1)) && (ptrBuffer[i] != '\0')) {
        ptrBuffer[i] = '\0';
        retVal = -1;
    }

    return retVal;
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

void uart1_print(char *str) {
    for( ; (*str) != '\0' ; )
    {
        if(*str=='\n') {
            UART1_TX_WAIT_AVAIL();
            UART1_DATA = '\r';
        }
        UART1_TX_WAIT_AVAIL();
        UART1_DATA = *str;
        str++;
    }
}
