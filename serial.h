/* 
 * File:   serial.h
 * Author: gokuhs
 *
 * Created on 3 de mayo de 2019, 16:59
 */

#ifndef SERIAL_H
#define	SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RXBUFFERSIZE 255
#define baud 9600 //UART baud rate

//Print string in Serial
void SerialPrint(unsigned char string[], int addEndLine);
//Read serial string
char * ReadSerial();
//Is serial Pending??
int SerialPending();


#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_H */

