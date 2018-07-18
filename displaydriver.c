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
    gD.mux_timer_reload_val = (uint16_t)(65536L - (100000L/hz));
}

void initialise_display(void)
{
    gD.active_mux_digit = 0;
    gD.mux_ready_flag = 1;
    gD.num = 0;
    
//    gD.mux_timer_reload_val = 30000;
    set_mux_frequency(40);
    
    uint8_t initData[10] = {'9','8','7','6','5','4','3','2','1','0'}; //{0,0,0,0,0,0,0,0,0,0};//

    load_frame_buffer(initData);
}


void muxInterrupt(void)
{
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
        D2off;
        D3off;
        D4off;
        D5off;
        return;
    }
    case(1):
    {
        D1off;
        D2on;
        D3off;
        D4off;
        D5off;
        return;
    }
    case(2):
    {
        D1off;
        D2off;
        D3on;
        D4off;
        D5off;
        return;
    }
    case(3):
    {
        D1off;
        D2off;
        D3off;
        D4on;
        D5off;
        return;
    }
    case(4):
    {
        D1off;
        D2off;
        D3off;
        D4off;
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
        S1A = 1;
    }
    else
    {
        S1A = 0;
    }
    if((d1 & 0x40) > 0)
    {
        S1B = 1;
    }
    else
    {
        S1B = 0;
    }
    if((d1 & 0x20) > 0)
    {
        S1C = 1;
    }
    else
    {
        S1C = 0;
    }
    if((d1 & 0x10) > 0)
    {
        S1D = 1;
    }
    else
    {
        S1D = 0;
    }
    if((d1 & 0x08) > 0)
    {
        S1E = 1;
    }
    else
    {
        S1E = 0;
    }
    if((d1 & 0x04) > 0)
    {
        S1F = 1;
    }
    else
    {
        S1F = 0;
    }
    if((d1 & 0x02) > 0)
    {
        S1G = 1;
    }
    else
    {
        S1G = 0;
    }
    if((d1 & 0x01) > 0)
    {
        S1DP = 1;
    }
    else
    {
        S1DP = 0;
    }
    
    if((d2 & 0x80) > 0)
    {
        S2A = 1;
    }
    else
    {
        S2A = 0;
    }
    if((d2 & 0x40) > 0)
    {
        S2B = 1;
    }
    else
    {
        S2B = 0;
    }
    if((d2 & 0x20) > 0)
    {
        S2C = 1;
    }
    else
    {
        S2C = 0;
    }
    if((d2 & 0x10) > 0)
    {
        S2D = 1;
    }
    else
    {
        S2D = 0;
    }
    if((d2 & 0x08) > 0)
    {
        S2E = 1;
    }
    else
    {
        S2E = 0;
    }
    if((d2 & 0x04) > 0)
    {
        S2F = 1;
    }
    else
    {
        S2F = 0;
    }
    if((d2 & 0x02) > 0)
    {
        S2G = 1;
    }
    else
    {
        S2G = 0;
    }
    if((d2 & 0x01) > 0)
    {
        S2DP = 1;
    }
    else
    {
        S2DP = 0;
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
        enable_digit(gD.active_mux_digit);
        enable_segments_for_digits(gD.frame_buffer_7seg[gD.active_mux_digit], gD.frame_buffer_7seg[9-gD.active_mux_digit]);
    }
}





