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

#include "displaydriver.h"
#include "system.h"


/*
 * 
 */

// Defines
#define MAX_RX_BYTES 3
#define MY_ADDRESS   0xAB

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
    ANSELA = 0;
    ANSELB = 0;
    ADCON0 = 0;
    OPTION_REGbits.T0CS = 0;
    ADCON1 = 0;
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

void ausart_init_synchronous(){

    // Setup the Transmit Status & Control Register (TXSTA)
    TXSTAbits.CSRC  = 0; // Slave mocde, clocked externally
    TXSTAbits.TX9   = 0; // 9-bit transmission
    TXSTAbits.TXEN  = 0; // Transmit enable bit
    TXSTAbits.SYNC  = 1; // Synchronous mode
    
    // Setup the Receive Status & Control Register (RCSTA)
    RCSTAbits.SPEN  = 1; // Serial Port Enable bit
    RCSTAbits.RX9   = 0; // 9-bit Receive Enable bit
    RCSTAbits.SREN  = 1; // Single Receive Enable bit (1 = receive mode))
    RCSTAbits.CREN  = 1; // Continuous Receive Enable bit (1 = receive mode))
    RCSTAbits.ADDEN = 0; //Address Detect Enable bit
    /* Note: Setting CREN overrides SREN if enabled */
        
}

void ausart_init_asynchronous(){

    // Setup the Transmit Status & Control Register (TXSTA)
    TXSTAbits.SYNC  = 0; // Synchronous mode
    TXSTAbits.BRGH  = 1; // Baud Rate generator
    
    // Setup the Receive Status & Control Register (RCSTA)
    RCSTAbits.SPEN  = 1; // Serial Port Enable bit
    RCSTAbits.RX9   = 1; // 9-bit Receive Enable bit
    RCSTAbits.SREN  = 1; // Single Receive Enable bit (1 = receive mode))
    RCSTAbits.CREN  = 1; // Continuous Receive Enable bit (1 = receive mode))
    RCSTAbits.ADDEN = 1; // Address Detect Enable bit
    /* Note: Setting CREN overrides SREN if enabled */
    
    /*
     * Can set up address detection if we are able to send 9-bit data
     * RX9 and ADDEN must be set. Send 9bits with MSB high, check remaining 8bits
     * to see if byte contains device address. If so, disable ADDEN and listen for 
     * remainder of message. Once message complete, set ADDEN high once more to
     * start listening for next message.
     * 
     * When ADDEN=1, UART FIFO (and the RCIF interrupt) will only fill with data
     * if rx'ed 9th bit is high, thus mitigating it listening to data it doesn't need. 
     */
    
    // Set baud rate
    /* SBPRG = (Fosc)/(64x(Desired Baud Rate)) - 1
     * For a baud rate of 19200, Fosc=8MHz = 25.04 */
    SPBRG = 25;
}

void ausart_isr_init(){
    // Activate ISR for receive mode
    PIE1bits.RCIE   = 1; // Receive Interrupt Enable
    INTCONbits.GIE  = 1; // Global Interrupts Enable
    INTCONbits.PEIE = 1; // PEripheral Interrupt Enable      
}

#define _XTAL_FREQ 8000000

int main(int argc, char** argv) {
    
    ConfigureOscillator();
//    variable_init();
    gpio_init();
//    ausart_init_asynchronous();
//    ausart_isr_init();
    
    displayInit();
    
    // Port is set to output in gpio_init() - set high here
//    PORTAbits.RA1 = 0;
    
    while(1)
    {
//        if(updateDisplay){
//            updateDisplay = 0;
////            loadDisplay(rcBuf);
//            NOP();
//            PORTAbits.RA1 = 0;
//        }
        processDisplay();
        __delay_ms(2);
        muxInterrupt();
    }
    return (EXIT_SUCCESS);
}

//
//// Delay routine
//void delay(int d)
//{
//    int i;  // Declare variable to be used in the loop
//
//    while(d)    // While d > 0
//    {
//        i = 100;    // set i to 100 for inner loop
//        while(i--);    // while i > 0
//
//        d--;    // decrement d
//    }
//}
//
//void interrupt isr_ausart(void){
//    static uint8_t rcindex = 0;
//    if(PIR1bits.RCIF){
//        // Check for Framing or Overrun Error
//        if(!RCSTAbits.FERR && !RCSTAbits.OERR){
//            // Valid data received
//            rcBuf[rcindex] = RCREG;
//
//            if(rcBuf[rcindex] == MY_ADDRESS){
//                /* Device has been addressed, listen for message data */
//                RCSTAbits.ADDEN = 0;
//            }
//            
//            PORTAbits.RA1 = 1;
//            
//            if(++rcindex >= MAX_RX_BYTES){ // increment string index
//                rcindex = 0;
//                RCSTAbits.ADDEN = 1; /* message over - listen for address again*/
//                updateDisplay = 1;
//            }
//        } else if(RCSTAbits.OERR){
//            RCSTAbits.CREN  = 0;
//        }
//    }
// 
//}