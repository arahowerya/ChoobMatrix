/* 
 * File:   main.c
 * Author: kilian
 *
 * Created on July 8, 2018, 12:45 PM
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <xc.h>
#include <pic16f722a.h>
#include <pic16f722.h>

#include "displaydriver.h"


/*
 * 
 */

// Defines
#define MAX_RX_BYTES 10

// Variables
uint8_t volatile updateDisplay;
uint8_t rcBuf[MAX_RX_BYTES];

// Function prototypes:
void delay(int d);

void variable_init(){
    updateDisplay = 0;
    memset(rcBuf, (int) 0, MAX_RX_BYTES);
}

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

void ausart_init(){

    // Setup the Transmit Status & Control Register (TXSTA)
    TXSTAbits.CSRC  = 0; // Slave mocde, clocked externally
    TXSTAbits.TX9   = 0; // 9-bit transmission
    TXSTAbits.TXEN  = 0; // Transmit enable bit
    TXSTAbits.SYNC  = 1; // Synchronous mode
    
    // Setup the Receive Status & Control Register (RCSTA)
    RCSTAbits.SPEN  = 1; // Serial Port Enabled
    RCSTAbits.RX9   = 0; // 9-bit Receive Enable bit
    RCSTAbits.SREN  = 1; // Single Receive Enable bit (1 = receive mode))
    RCSTAbits.CREN  = 1; // Enable Continuous Receive Enable bit (1 = receive mode))
    RCSTAbits.ADDEN = 0; //Address Detect Enable bit
//    RCSTAbits.FERR // Framing Error bit
//    RCSTAbits.OERR // Overrun Error bit
//    RCSTAbits.RX9D // Ninth bit of Received data
        
}

void ausart_isr_init(){
    // Activate ISR for receive mode
    PIE1bits.RCIE   = 1; // Receive Interrupt Enable
    INTCONbits.GIE  = 1; // Global Interrupts Enable
    INTCONbits.PEIE = 1; // PEripheral Interrupt Enable      
}

int main(int argc, char** argv) {
    
    variable_init();
    gpio_init();
    ausart_init();
    ausart_isr_init();
    
    displayInit();
    
    // Port is set to output in gpio_init() - set high here
    PORTAbits.RA1 = 1;
    
    while(1)
    {
        if(updateDisplay == 1U){
            updateDisplay = 0;
            loadDisplay(rcBuf);
        }
        processDisplay();
            
        /*Trying, and failing, to toggle an LED...*/
        PORTAbits.RA1 ^= 1;
        delay(1000);
    }
    return (EXIT_SUCCESS);
}


// Delay routine
void delay(int d)
{
    int i;  // Declare variable to be used in the loop

    while(d)    // While d > 0
    {
        i = 100;    // set i to 100 for inner loop
        while(i--);    // while i > 0

        d--;    // decrement d
    }
}

void interrupt isr_ausart(void){
    static uint8_t rcindex = 0;
    if(PIR1bits.RCIF){
        // Check for Framing or Overrun Error
        if(!RCSTAbits.FERR && !RCSTAbits.OERR){
            // Valid data received
            rcBuf[rcindex] = RCREG;

            if(++rcindex > MAX_RX_BYTES){ // increment string index
                rcindex = 0;
                updateDisplay = 1;
            }
        }
        PIR1bits.RCIF = 0; // Reset interrupt flag
    }
 
}