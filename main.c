/* 
 * File:   main.c
 * Author: kilian
 *
 * Created on July 8, 2018, 12:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f722a.h>
//Trying to bash the ide into believing these files exist and that it should read them...

#include "displaydriver.h"

/*
 * 
 */



void gpio_init(void)
{
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
}




int main(int argc, char** argv) {

    TXSTAbits.TXEN = 1;
    
    gpio_init();
    while(1)
    {
        processDisplay();
    }
    return (EXIT_SUCCESS);
}

