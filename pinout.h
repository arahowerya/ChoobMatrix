/* 
 * File:   pinout.h
 * Author: kilian
 *
 * Created on July 8, 2018, 1:05 PM
 */

#ifndef PINOUT_H
#define	PINOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define D3 PORTAbits.RA0
#define D4 PORTAbits.RA1
#define D5 PORTAbits.RA2
#define D2 PORTBbits.RB6
#define D1 PORTBbits.RB7
    
#define S1A PORTCbits.RC2
#define S1B PORTCbits.RC0
#define S1C PORTAbits.RA4
#define S1D PORTAbits.RA3
#define S1E PORTAbits.RA5
#define S1F PORTAbits.RA6
#define S1G PORTCbits.RC1
#define S1DP PORTAbits.RA7
    
#define S2A PORTCbits.RC5
#define S2B PORTCbits.RC4
#define S2C PORTBbits.RB4
#define S2D PORTBbits.RB5
#define S2E PORTBbits.RB3
#define S2F PORTBbits.RB1
#define S2G PORTBbits.RB0
#define S2DP PORTBbits.RB2


#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */

