// this file abstracts hw needed by demos

#ifndef DEMO_HW
#define DEMO_HW

#include <stdint.h>

/**
 * @brief write a byte to terminal
 */
void demo_hw_term_writeChar(char u8);

/**
 * @brief writes null terminated buffer to stdout of your terminal
 */
void demo_hw_term_write(const char *const buf);

/**
 * @brief writes null terminated buffer with newline to stdout of your terminal
 */
void demo_hw_term_writeLine(const char *const buf);

/**
 * @brief read byte from stdin of your terminal
 * @retval 0: not read
 * @retval 1: read
 */
uint8_t demo_hw_term_readCharNonBlock(char *c);

/**
 * @brief read from stdin of your terminal
 * @retval 0: if no character has been read
 * @retval n: number of characters read
 */
uint8_t demo_hw_term_readNonBlock(char *buf, uint8_t len);

/**
 * @brief read from stdin of your terminal until buffer is full
 * @retval none
 */
void demo_hw_term_read(char *buf, uint8_t len);

/**
 * @brief reads stdin of your terminal until new line entered
 * @arg buf[out]: null terminated string
 * @arg len     : length of buf
 * @retval -1: it did not fit into buf
 * @retval  n: number of characters read
 */

int16_t demo_hw_term_readLine(char *buf, uint8_t len);

/**
 * @brief gets the state of the led
 * @retval 1: led is on
 * @retval 0: led is off
 */
uint8_t demo_hw_led_get(void);

/**
 * @brief sets the state of the led
 * @arg st == 0: off
 * @arg st != 0: on
 */
void demo_hw_led_set(uint8_t st);

/**
 * @brief toggle led
 */
void demo_hw_led_toggle(void);


#endif // DEMO_HW