/* 
 * File:   main.c
 * Author: the lads
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
#include "pinout.h"

/*
 * 
 */

// Defines
#define MAX_RX_BYTES 10U
#define MY_ADDRESS   0x00

// Variables
uint8_t volatile updateDisplay;
uint8_t rcBuf[MAX_RX_BYTES];


void variable_init(void){
    updateDisplay = 0;
    memset(rcBuf, (int) 0, MAX_RX_BYTES);
}

void gpio_init(void)
{
    TRISA = 0;  //PORTA = outputs
    ANSELA = 0; //No Analog on PORTA
    
    OPTION_REGbits.T0CS = 0; //Disable RA4 Timer0
    
    TRISB = 0; //PORTB = outputs
    ANSELB = 0; //No Analog on PORTB
    TRISC = 0; //PORTC = Outputs.... except:
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    
    
    ADCON0 = 0; //Disable all analog settings
    ADCON1 = 0;
    
}

void ausart_init_synchronous(){

    // Setup the Transmit Status & Control Register (TXSTA)
    TXSTAbits.CSRC  = 0; // Slave mode, clocked externally
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

void ausart_init_asynchronous(void){

    // Setup the Transmit Status & Control Register (TXSTA)
    TXSTAbits.SYNC  = 0; // Synchronous mode
    TXSTAbits.BRGH  = 1; // Baud Rate generator
    
    // Setup the Receive Status & Control Register (RCSTA)
    RCSTAbits.SPEN  = 1; // Serial Port Enable bit
    RCSTAbits.RX9   = 0; // 9-bit Receive Enable bit
    RCSTAbits.SREN  = 1; // Single Receive Enable bit (1 = receive mode))
    RCSTAbits.CREN  = 1; // Continuous Receive Enable bit (1 = receive mode))
    RCSTAbits.ADDEN = 0; // Address Detect Enable bit
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
    /* SBPRG = (Fosc)/(16x(Desired Baud Rate)) - 1
     * For a baud rate of 19200, Fosc=8MHz = 25.04 */
    SPBRG = 25;
     /* For a baud rate of 19200, Fosc=16MHz = 51 */
//    SPBRG = 51;
}

void ausart_isr_init(void){
    // Activate ISR for receive mode
    PIE1bits.RCIE   = 1; // Receive Interrupt Enable
    INTCONbits.GIE  = 1; // Global Interrupts Enable
    INTCONbits.PEIE = 1; // PEripheral Interrupt Enable      
}

void timer1_init(void)
{

    T1CONbits.TMR1CS = 0b00;  /* Source is FOSC/4 */
    T1CONbits.T1CKPS = 0b11;  /* 1:8 prescale */
    T1CONbits.T1OSCEN = 0;  /* Oscillator Disable */
    T1GCONbits.TMR1GE = 0;  /*Gate is disabled*/

    T1CONbits.TMR1ON = 1U;
    PIE1bits.TMR1IE = 1U;
    INTCONbits.PEIE = 1U;
    INTCONbits.GIE = 1U;
}

int main(int argc, char** argv) 
{
    
    ConfigureOscillator();
//    variable_init();
    gpio_init();
    
    
    /* UART setup */
//    ausart_init_asynchronous();
//    ausart_isr_init();
    
    /* Timer setup */
    timer1_init();
    initialise_display();
   
    
    while(1)
    {
        processDisplay();
    } 
   return (EXIT_SUCCESS);
}

void interrupt isr(void){
    static uint8_t rcindex = 0;
    if(PIR1bits.RCIF)
    {
        // Check for Framing or Overrun Error
        if(!RCSTAbits.FERR && !RCSTAbits.OERR){
            // Valid data received
            rcBuf[rcindex] = RCREG;

            if(rcBuf[rcindex] == MY_ADDRESS){
                /* Device has been addressed, listen for message data */
//                RCSTAbits.ADDEN = 0;
            }
            
            
            if(++rcindex >= MAX_RX_BYTES){ // increment string index
                rcindex = 0;
//                RCSTAbits.ADDEN = 1; /* message over - listen for address again*/
                updateDisplay = 1;
            }
        } else if(RCSTAbits.OERR){
            RCSTAbits.CREN  = 0;
        }
    }
    if(PIR1bits.TMR1IF){
//        PORTAbits.RA1 = 1;
        muxInterrupt();
        TMR1 = get_mux_timer_reload();
    }
    
    PIR1bits.RCIF = 0;
    PIR1bits.TMR1IF = 0;
}














