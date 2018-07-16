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
    uint8_t out[10U]; //7seg data
    uint8_t raw[10U]; //ASCII or other data

    uint8_t muxPos;
    uint8_t muxFlag;
    
    uint32_t num;
}gD;


void loadDisplay(uint8_t *data)
{
    memcpy(gD.raw, data, 10);
    for(int i = 0; i < 10; i++)
    {
        gD.out[(uint8_t) i] = ASCII7SEG[gD.raw[(uint8_t) i]];
        if(gD.raw[(uint8_t) i+1U] == '.')
            gD.out[(uint8_t) i] |= 0x01;
    }
}

void displayInit(void)
{
    gD.muxPos = 0U;
    gD.muxFlag = 1U;
    gD.num = 0;
    
    uint8_t initData[10] = {'9','8','7','6','5','4','3','2','1','0'}; //{0,0,0,0,0,0,0,0,0,0};//

    loadDisplay(initData);
}


void muxInterrupt(void)
{
    gD.muxFlag = 1U;
}


//Bullshit function to make a counter...
const uint32_t div[10] = { 1000000000,10000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10};
void incNum(void)
{
    gD.num++;
    uint8_t data[10];
    for(int i = 0; i < 10; i++)
    {
            uint32_t isolated = (gD.num % div[i])/(div[i]/10);
            data[i] = isolated + '0';
    }
    loadDisplay(data);
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
        incNum();
        D1 = 1;
        break;
    case(1):
        D2 = 1;
        break;
    case(2):
        D3 = 1;
        break;
    case(3):
        D4 = 1;
        break;
    case(4):
        D5 = 1;
        break;
    }
}


void muxDigit(uint8_t d1, uint8_t d2)
{
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
    if(gD.muxFlag == 1U)
    {
        gD.muxFlag = 0U;
        if(gD.muxPos++ >= 4U) //Set mux in cycles of 5 digits
            gD.muxPos = 0U;
        enableDigit(gD.muxPos);
        muxDigit(gD.out[gD.muxPos], gD.out[9-gD.muxPos]);
    }
}






