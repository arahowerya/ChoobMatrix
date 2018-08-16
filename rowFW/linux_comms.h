/* 
 * File:   lm75b.h
 * Author: kilian
 *
 * Created on March 28,  2018,  10:09 AM
 */

#include <stdint.h>
#ifndef LINUX_COMMS_H
#define	LINUX_COMMS_H

#ifdef	__cplusplus
extern "C" {
#endif

void comms_process(void);
void comms_inc1ms(void);
void init_comms(void);

enum ChargePointErrorCode {CONNECTORLOCKFAILURE, EVCOMMUNICATIONERROR, GROUNDFAILURE, HIGHTEMPERATURE,
 INTERNALERROR, LOCALLISTCONFLICT, OTHERERROR,
 OVERCURRENTFAILURE, OVERVOLTAGE, POWERMETERFAILURE,
 POWERSWITCHFAILURE, READERFAILURE, RESETFAILURE, UNDERVOLTAGE, WEAKSIGNAL, MAX_ERRORS};


uint8_t getAuthStatus(void);
void deauth_charger(void);

void add_error_code(uint8_t error_code);
void remove_error_code(uint8_t error_code);

#ifdef	__cplusplus
}
#endif

#endif	/* LINUX_COMMS_H */


