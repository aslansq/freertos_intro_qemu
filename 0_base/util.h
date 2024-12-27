#ifndef BASE_UTIL_H
#define BASE_UTIL_H

#include "uart.h"

#define util_ledSet(st) ((st) != 0) ? (uart1_print("ledSt: 1\n")) : (uart1_print("ledSt: 0\n"))

#endif //BASE_UTIL_H