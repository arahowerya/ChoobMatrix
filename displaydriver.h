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

void initialise_display(void);
void loadDisplay(uint8_t *data);
void processDisplay(void);

void set_mux_frequency(uint16_t hz);
uint16_t get_mux_timer_reload(void);
void muxInterrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAYDRIVER_H */

