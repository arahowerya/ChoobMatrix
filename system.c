/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>            /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

//#include <pic16f722.h>

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */
    OSCCONbits.IRCF = 2U; // 2 = 10 = 8MHz (POR value)
//    OSCCONbits.IRCF = 3U; // 3 = 11 = 16MHz
    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}
