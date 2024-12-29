#include "demo_hw.h"
#include "mps2_an385_uart.h"

//! is there a char to be read in uart0 rx buf
#define UART0_RX_AVAIL() ((UART0_STATE & UART_STATE_RX_BF) != 0)
//! wait until there is something to read in uart0 rx
#define UART0_RX_WAIT()  while ((UART0_STATE & UART_STATE_RX_BF) == 0)
// wait until it is available to put a char to uart1 tx buffer
#define UART0_TX_WAIT() while( ( UART0_STATE & UART_STATE_TX_BF ) != 0 )
// wait until it is available to put a char to uart1 tx buffer
#define UART1_TX_WAIT() while( ( UART1_STATE & UART_STATE_TX_BF ) != 0 )

static void _uart1_update(void);

static uint8_t _led_st = 0;
static uint8_t _adc_val = 0;

// PUBLIC

void demo_hw_term_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buf[100];
    vsprintf(buf, format, args);
    demo_hw_term_write(buf);
    va_end(args);
}

void demo_hw_term_writeChar(char c) {
    c = (c == '\r') ? '\n' : c;
    UART0_TX_WAIT();
    UART0_DATA = c;
    if(c == '\n') {
        UART0_TX_WAIT();
        UART0_DATA = '\r';
    }
}

void demo_hw_term_write(const char *const buf) {
    uint8_t idx  = 0;
    while(buf[idx] != '\0') {
        demo_hw_term_writeChar(buf[idx]);
        idx++;
    }
}

void demo_hw_term_writeLine(const char *const buf) {
    demo_hw_term_write(buf);
    demo_hw_term_writeChar('\n');
    demo_hw_term_writeChar('\r');
}

uint8_t demo_hw_term_readCharNonBlock(char *c) {
    uint8_t read = 0;
    if(UART0_RX_AVAIL()) {
        read = 1;
        *c = (char)UART0_DATA;
    }
    return read;
}

uint8_t demo_hw_term_readNonBlock(char *buf, uint8_t len) {
    uint8_t idx;
    for(idx = 0; idx < len; ++idx) {
        // if nothing is read just break
        if(!demo_hw_term_readCharNonBlock(&buf[idx])) {
            break;
        }
    }
    return idx; // returns number of bytes read
}


void demo_hw_term_read(char *buf, uint8_t len) {
    uint8_t idx;
    for(idx = 0; idx < len; ++idx) {
        UART0_RX_WAIT();
        buf[idx] = (char)UART0_DATA;
    }
}

int16_t demo_hw_term_readLine(char *buf, uint8_t len) {
    int16_t ret = 0;
    uint8_t idx;
    char c;

    for(idx = 0; idx < len; idx++) {
        UART0_RX_WAIT();
        c = (char)UART0_DATA;
        if(idx == (len-1) && c != '\r') {
            ret = -1;
            break;
        } else if(c == '\r') {
            buf[idx] = '\0';
            break;
        } else {
            buf[idx] = c;
        }
    }

    if(ret != -1) {
        ret = idx;
    }

    return ret;
}

uint8_t demo_hw_led_get(void) {
    return _led_st;
}

void demo_hw_led_set(uint8_t st) {
    _led_st = (st == 0) ? 0 : 1;
    _uart1_update();
}

void demo_hw_led_toggle(void) {
    demo_hw_led_set(!_led_st);
}

uint8_t demo_hw_adc_read(void) {
    static uint8_t adcBuf[] = {160, 170, 200, 180, 150, 121}; // :) behave like adc reading fluctuate like in real life
    static uint8_t adcBufIdx = 0;
    ++adcBufIdx;
    if(adcBufIdx == sizeof(adcBuf))
        adcBufIdx = 0;
    _adc_val = adcBuf[adcBufIdx];
    _uart1_update();
    return adcBuf[adcBufIdx];
}

// PROTECTED :)
void demo_hw_init(void) {
    UART0_BAUDDIV = 16;
    UART0_CTRL = ( UART0_CTRL_TX_EN | UART0_CTRL_RX_EN );
    UART1_BAUDDIV = 16;
    UART1_CTRL = UART0_CTRL_TX_EN;
    _uart1_update();
}

// PRIVATE

/**
 * @brief rewrites everything
 */
static void _uart1_update(void) {
    static char uart1_buf[] =
"\
\x1b[H\
led : 0\n\r\
adc : 000\n\r\
";
    static char *ledStPtr = &uart1_buf[9];
    static char *adcValPtr = &uart1_buf[18];
    *ledStPtr = (_led_st) ? '1' : '0';
    adcValPtr[0] = ' ';
    adcValPtr[1] = ' ';
    adcValPtr[2] = ' ';
    sprintf(adcValPtr, "%d", (int)_adc_val);
    uint8_t idx = 0;
    while(uart1_buf[idx] != '\0') {
        UART1_TX_WAIT();
        UART1_DATA = uart1_buf[idx];
        idx++;
    }
}
