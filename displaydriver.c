/* 
 * File:   main.c
 * Author: kilian
 *
 * Created on July 8, 2018, 12:45 PM
 */

#include <stdint.h>
#include <stdio.h>

#include </Applications/microchip/xc8/v2.00/pic/include/xc.h>
#include </Applications/microchip/xc8/v2.00/pic/include/pic16f722a.h>

#include "pinout.h"
#include "ascii7seg.h"

static struct gD
{
    uint8_t out[10]; //7seg data
    uint8_t raw[10]; //ASCII or other data

    uint8_t muxPos = 0;
    uint8_t muxFlag = 0;
}gD;


void muxInterrupt(void)
{
    gD.muxFlag = 1;
}

void loadDisplay(uint8_t *data)
{
    memcpy(gD.raw, data, 10);
    for(int i = 0; i < 10; i++)
    {
        gD.out[i] = ASCII7SEG[gD.raw[i]];
        if(gD.raw[i+1] == '.')
            gD.out[i] |= 0x01;
    }
}

void enableDigit(uint8_t pos)
{
    D3 = 0;
    D4 = 0;
    D5 = 0;
    D2 = 0;
    D1 = 0;
    switch(pos)
    {
    default:
    case(0):
        D1 = 1;
    case(1):
        D2 = 1;
    case(2):
        D3 = 1;
    case(3):
        D4 = 1;
    case(4):
        D5 = 1;
    }
}


void muxDigit(uint8_t d1, uint8_t d2)
{
    if(d1 && 0x80 > 0)
        S1A = 1;
    if(d1 && 0x40 > 0)
        S1B = 1;
    if(d1 && 0x20 > 0)
        S1C = 1;
    if(d1 && 0x10 > 0)
        S1D = 1;
    if(d1 && 0x08 > 0)
        S1E = 1;
    if(d1 && 0x04 > 0)
        S1F = 1;
    if(d1 && 0x02 > 0)
        S1G = 1;
    if(d1 && 0x01 > 0)
        S1DP = 1;
    
    if(d2 && 0x80 > 0)
        S2A = 1;
    if(d2 && 0x40 > 0)
        S2B = 1;
    if(d2 && 0x20 > 0)
        S2C = 1;
    if(d2 && 0x10 > 0)
        S2D = 1;
    if(d2 && 0x08 > 0)
        S2E = 1;
    if(d2 && 0x04 > 0)
        S2F = 1;
    if(d2 && 0x02 > 0)
        S2G = 1;
    if(d2 && 0x01 > 0)
        S2DP = 1;
}

void processDisplay(void)
{
    if(gD.muxFlag == 1)
    {
        gD.muxFlag = 0;
        if(gD.muxPos++ == 6) //Set mux in cycles of 5 digits
            gD.muxPos = 0;
        enableDigit(gD.muxPos);
        muxDigit(gD.out[gD.muxPos], gD.out[gD.muxPos+5]);
    }
}






