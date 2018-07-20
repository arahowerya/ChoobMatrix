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
#include <xc.h>


#define D1off do{PORTBbits.RB7 = 0;} while(PORTBbits.RB7 == 1)
#define D2off do{PORTBbits.RB6 = 0;} while(PORTBbits.RB6 == 1)
#define D3off do{PORTAbits.RA0 = 0;} while(PORTAbits.RA0 == 1)
#define D4off do{PORTAbits.RA1 = 0;} while(PORTAbits.RA1 == 1)
#define D5off do{PORTAbits.RA2 = 0;} while(PORTAbits.RA2 == 1)

#define D1on do{PORTBbits.RB7 = 1;} while(PORTBbits.RB7 == 0)
#define D2on PORTBbits.RB6 = 1 //do{PORTBbits.RB6 = 1;} while(PORTBbits.RB6 == 0)
#define D3on do{PORTAbits.RA0 = 1;} while(PORTAbits.RA0 == 0)
#define D4on do{PORTAbits.RA1 = 1;} while(PORTAbits.RA1 == 0)
#define D5on do{PORTAbits.RA2 = 1;} while(PORTAbits.RA2 == 0)
    
#define S1Aon do{PORTCbits.RC2 = 1;} while(PORTCbits.RC2 == 0)
#define S1Bon do{PORTCbits.RC0 = 1;} while(PORTCbits.RC0 == 0)
#define S1Con do{PORTAbits.RA4 = 1;} while(PORTAbits.RA4 == 0)
#define S1Don do{PORTAbits.RA3 = 1;} while(PORTAbits.RA3 == 0)
#define S1Eon do{PORTAbits.RA5 = 1;} while(PORTAbits.RA5 == 0)
#define S1Fon do{PORTAbits.RA6 = 1;} while(PORTAbits.RA6 == 0)
#define S1Gon do{PORTCbits.RC1 = 1;} while(PORTCbits.RC1 == 0)
#define S1DPon do{PORTAbits.RA7 = 1;} while(PORTAbits.RA7 == 0)
    
#define S2Aon do{PORTCbits.RC5 = 1;} while(PORTCbits.RC5 == 0)
#define S2Bon do{PORTCbits.RC4 = 1;} while(PORTCbits.RC4 == 0)
#define S2Con do{PORTBbits.RB4 = 1;} while(PORTBbits.RB4 == 0)
#define S2Don do{PORTBbits.RB5 = 1;} while(PORTBbits.RB5 == 0)
#define S2Eon do{PORTBbits.RB3 = 1;} while(PORTBbits.RB3 == 0)
#define S2Fon do{PORTBbits.RB1 = 1;} while(PORTBbits.RB1 == 0)
#define S2Gon do{PORTBbits.RB0 = 1;} while(PORTBbits.RB0 == 0)
#define S2DPon do{PORTBbits.RB2 = 1;} while(PORTBbits.RB2 == 0)


#define S1Aoff do{PORTCbits.RC2 = 0;} while(PORTCbits.RC2 == 1)
#define S1Boff do{PORTCbits.RC0 = 0;} while(PORTCbits.RC0 == 1)
#define S1Coff do{PORTAbits.RA4 = 0;} while(PORTAbits.RA4 == 1)
#define S1Doff do{PORTAbits.RA3 = 0;} while(PORTAbits.RA3 == 1)
#define S1Eoff do{PORTAbits.RA5 = 0;} while(PORTAbits.RA5 == 1)
#define S1Foff do{PORTAbits.RA6 = 0;} while(PORTAbits.RA6 == 1)
#define S1Goff do{PORTCbits.RC1 = 0;} while(PORTCbits.RC1 == 1)
#define S1DPoff do{PORTAbits.RA7 = 0;} while(PORTAbits.RA7 == 1)
    
#define S2Aoff do{PORTCbits.RC5 = 0;} while(PORTCbits.RC5 == 1)
#define S2Boff do{PORTCbits.RC4 = 0;} while(PORTCbits.RC4 == 1)
#define S2Coff do{PORTBbits.RB4 = 0;} while(PORTBbits.RB4 == 1)
#define S2Doff do{PORTBbits.RB5 = 0;} while(PORTBbits.RB5 == 1)
#define S2Eoff do{PORTBbits.RB3 = 0;} while(PORTBbits.RB3 == 1)
#define S2Foff do{PORTBbits.RB1 = 0;} while(PORTBbits.RB1 == 1)
#define S2Goff do{PORTBbits.RB0 = 0;} while(PORTBbits.RB0 == 1)
#define S2DPoff do{PORTBbits.RB2 = 0;} while(PORTBbits.RB2 == 1)


#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */

