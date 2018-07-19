/* 
 * File:   main.c
 * Author: kilian
 *
 * Created on July 8, 2018, 12:45 PM
 */


#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xc.h>
#include <math.h>
//#include <pic16f722a.h>
//#include <pic16f722.h>

#include "pinout.h"
#include "ascii7seg.h"

#include "displaydriver.h"

static struct gD
{
    uint8_t frame_buffer_7seg[10U]; //7seg data
    uint8_t frame_buffer_ascii_input[10U]; //ASCII or other data

    uint8_t active_mux_digit;
    uint8_t mux_ready_flag;
    
    uint16_t mux_timer_reload_val;
    
    uint32_t num;
}gD;


void load_frame_buffer(uint8_t *data)
{
    memcpy(gD.frame_buffer_ascii_input, data, 10);
    for(int i = 0; i < 10; i++)
    {
        gD.frame_buffer_7seg[(uint8_t) i] = ASCII7SEG[gD.frame_buffer_ascii_input[(uint8_t) i]];
        if(gD.frame_buffer_ascii_input[(uint8_t) i+1U] == '.')
            gD.frame_buffer_7seg[(uint8_t) i] |= 0x01;
    }
}

uint16_t get_mux_timer_reload(void)
{
    return(gD.mux_timer_reload_val);
}

void set_mux_frequency(uint16_t hz)
{
    if(hz < 6)
        hz = 6;
    gD.mux_timer_reload_val = (uint16_t)(65536L - (100000L/hz));
}

void initialise_display(void)
{
    gD.active_mux_digit = 0;
    gD.mux_ready_flag = 1;
    gD.num = 0;
    
//    gD.mux_timer_reload_val = 30000;
    set_mux_frequency(59);
    
    uint8_t initData[10] = {'9','8','7','6','5','4','3','2','1','0'}; //
//    uint8_t initData[10] = {0,0,0,0,0,0,0,0,0,0};//
//    uint8_t initData[10] = {1,1,0,1,1,1,1,0,1,1};//

    load_frame_buffer(initData);
}


void muxInterrupt(void){

    //To be called from timer to set multiplex frequency
    gD.mux_ready_flag = 1;
}


// //Bullshit function to make a counter...
// const uint32_t div[10] = { 1000000000,10000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10};
// void incNum(void)
// {
//     gD.num++;
//     uint8_t data[10];
//     for(int i = 0; i < 10; i++)
//     {
//             uint32_t isolated = (gD.num % div[i])/(div[i]/10);
//             data[i] = isolated + '0';
//     }
//     load_frame_buffer(data);
// }

void disable_digits(void)
{    
        D1off;
        D2off;
        D3off;
        D4off;
        D5off;
}

void enable_digit(uint8_t pos)
{
    //Enables the digit to be multiplexed. Switches all others off.
    //
    switch(pos)
    {
    default:
    case(0):
    {
        D1on;
        return;
    }
    case(1):
    {
        D2on;
        return;
    }
    case(2):
    {
        D3on;
        return;
    }
    case(3):
    {
        D4on;
        return;
    }
    case(4):
    {
        D5on;
        return;
    }
    }
}


void enable_segments_for_digits(uint8_t d1, uint8_t d2)
{
    //Sets output latches depending on bitwise code in the input digits.
    //Sets the segments on or off for each digit.
    //
    if((d1 & 0x80) > 0)
    {
        S1Aon;
    }
    else
    {
        S1Aoff;
    }
    if((d1 & 0x40) > 0)
    {
        S1Bon;
    }
    else
    {
        S1Boff;
    }
    if((d1 & 0x20) > 0)
    {
        S1Con;
    }
    else
    {
        S1Coff;
    }
    if((d1 & 0x10) > 0)
    {
        S1Don;
    }
    else
    {
        S1Doff;
    }
    if((d1 & 0x08) > 0)
    {
        S1Eon;
    }
    else
    {
        S1Eoff;
    }
    if((d1 & 0x04) > 0)
    {
        S1Fon;
    }
    else
    {
        S1Foff;
    }
    if((d1 & 0x02) > 0)
    {
        S1Gon;
    }
    else
    {
        S1Goff;
    }
    if((d1 & 0x01) > 0)
    {
        S1DPon;
    }
    else
    {
        S1DPoff;
    }
    
    if((d2 & 0x80) > 0)
    {
        S2Aon;
    }
    else
    {
        S2Aoff;
    }
    if((d2 & 0x40) > 0)
    {
        S2Bon;
    }
    else
    {
        S2Boff;
    }
    if((d2 & 0x20) > 0)
    {
        S2Con;
    }
    else
    {
        S2Coff;
    }
    if((d2 & 0x10) > 0)
    {
        S2Don;
    }
    else
    {
        S2Doff;
    }
    if((d2 & 0x08) > 0)
    {
        S2Eon;
    }
    else
    {
        S2Eoff;
    }
    if((d2 & 0x04) > 0)
    {
        S2Fon;
    }
    else
    {
        S2Foff;
    }
    if((d2 & 0x02) > 0)
    {
        S2Gon;
    }
    else
    {
        S2Goff;
    }
    if((d2 & 0x01) > 0)
    {
        S2DPon;
    }
    else
    {
        S2DPoff;
    }
}

void processDisplay(void)
{
    // When flag is set via timer interrupt
    // increment the current digit to be multiplexed
    // And enable the appropriate segments on the output
    if(gD.mux_ready_flag >= 1)
    {
        gD.mux_ready_flag = 0;
        if(gD.active_mux_digit++ >= 4) //Set mux in cycles of 5 digits
        {
            gD.active_mux_digit = 0;
        }
        disable_digits();
        enable_segments_for_digits(gD.frame_buffer_7seg[gD.active_mux_digit], gD.frame_buffer_7seg[9-gD.active_mux_digit]);
        enable_digit(gD.active_mux_digit);
    }
}





