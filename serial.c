/* 
 * File:   serial.c
 * Author: gokuhs
 *
 * Created on 3 de mayo de 2019, 16:58
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "configure.h"
#include "serial.h"

unsigned char rxBuffer[RXBUFFERSIZE];
unsigned char rxExit[RXBUFFERSIZE];
unsigned int rxBufferLevel = 0;
unsigned int pending=0;

int SerialPending(){
    return pending;
}

char *ReadSerial(){
    if (pending){
        pending = 0;
        return rxExit;
    }
    return "\0\0";
}

void permutAndResetsBuffers(){
    for (unsigned i = 0; i < rxBufferLevel; i++){
        rxExit[i] = rxBuffer[i];
    }
    pending = 1;
    rxBuffer[0] = '\0';
    rxBufferLevel = 0;
}

// High priority interrupts
void interrupt ISR(void)
{
	// USART Receive interrupt?
	if (RCIF)
	{
        LEDON();
		// Check for overrun error condition
		if (OERR == 1)
		{
			// Clear the overrun error condition
			CREN = 0;
			CREN = 1;
		}
		else
		{
			if (rxBufferLevel != RXBUFFERSIZE)
			{
				// Buffer is not full, write the byte and update
				// the end pointer
				rxBuffer[rxBufferLevel] = RCREG;

                if (rxBuffer[rxBufferLevel] == '\0' || rxBuffer[rxBufferLevel] == '\n'|| rxBuffer[rxBufferLevel] == '}'){
                    permutAndResetsBuffers();
                    LEDOFF();
                }
                else{
                    // Increment the buffer level indicator
                    rxBufferLevel++;	
                }
			}
            else{
                rxBuffer[rxBufferLevel-1] = '\0';
                permutAndResetsBuffers();
                LEDOFF();
            }
		}	
 
		// RCIF is cleared when RCREG is read
	}	
}

void SerialPrint(unsigned char string[], int addEndLine){
    //  espera a que el registro de transmisión este disponible o vacio.
    unsigned int position = 0;
    do{
        while (!TXSTAbits.TRMT) {
        }
        //  escribe el dato que se enviará a través de TX.
        TXREG = string[position];
        LATCbits.LATC0 = !PORTCbits.RC0;
        position++;
    }
    while (string[position] != '\0' && string[position] != '\n' && position < RXBUFFERSIZE);
    if (string[position] != '\n'){
        TXREG = string[position];
        LATCbits.LATC0 = !PORTCbits.RC0;
    }
    if (addEndLine > 0) { //  0,1,2,3,4.......
       while (!TXSTAbits.TRMT) {
       }
       TXREG = 10;
    }
    while (!TXSTAbits.TRMT) {
    }
    TXREG = 13;
}
