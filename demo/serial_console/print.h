/* Formats binary values into ascii strings using the standard c format syntax
E.g. to format the value stored in variable data as an integer at least three characters wide.
printformat("%3i" , data);
*/

#ifndef MSP430G2553
#define MSP430G2553
#include <msp430g2553.h>
#endif
#include "stdarg.h"

void printformat(char *format, ...);

#ifdef printf
# undef printf
# define printf			printformat
#endif	/* printf */

