/* 
 * File:   displaydriver.h
 * Author: kilian
 *
 * Created on July 8, 2018, 2:16 PM
 */

#ifndef DISPLAYDRIVER_H
#define	DISPLAYDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

void displayInit(void);
void loadDisplay(uint8_t *data);
void processDisplay(void);
void muxInterrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAYDRIVER_H */

