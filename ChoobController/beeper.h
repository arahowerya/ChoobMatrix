/* 
 * File:   beeper.h
 * Author: kilian
 *
 * Created on July 31, 2018, 3:11 PM
 */

#ifndef BEEPER_H
#define	BEEPER_H

#ifdef	__cplusplus
extern "C" {
#endif

void beeper_init(void);
void beeper_inc1ms(void);
void beeper_process(void);



void beeper_play_error_tone(void);
void beeper_play_charging_tone(void);
void beeper_play_connected_tone(void);
void beeper_button_tone(void);
void beeper_unplug_tone(void);
void beeper_has_unplugged_tone(void);

#define G4 40816
#define A4 36364
#define Bb4 34334
#define B4 32454
#define C5 30592
#define Cs5 28880
#define D5 27257
#define Ds5 25723
#define E5 24279
#define F5 22922
#define Fs5 21650
#define G5 20408
#define Gs5 19277
#define A5 18182
#define Bb5 17167
#define B5 16194
#define C6 15296
#define Cs6 14440
#define D6 13628
#define Ds6 12861
#define E6 12139
#define F6 11461
#define Fs6 10818
#define G6 10210
#define Gs6 9632
#define A6 9091
#define REST 1
#define NOTE_END 2

#ifdef	__cplusplus
}
#endif

#endif	/* BEEPER_H */





