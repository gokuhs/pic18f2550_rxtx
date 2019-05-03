/* 
 * File:   main.c
 * Author: gokuhs
 *
 * Created on May 22, 2013, 8:31 AM
 * 
 * THANKS to this sources:
 * 
 * https://www.makerelectronico.com/comunicacion-serial-uart-usart-rs232-pic18f4550/ 
 * https://stackoverflow.com/questions/33212059/rcreg-data-pic-18f4550-not-displaying-value
 * 
 */

#include <xc.h>
#include <plib/usart.h>
#include "configure.h"
#include "utils.h"
#include "serial.h"

void Setup(){
    //Config Fosc = 8Mhz internal
    OSCCONbits.IRCF = 0b111; //Configuration intearnal crystal to 8Mhz (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; //Internel Fosc font
 
    //Config UART to 9600 baudios
    TRISCbits.RC6 = 0; //  Pin RC6 digital outpit to TX.
    TXSTAbits.TX9 = 0; //  Modo-8bits.
    TXSTAbits.TXEN = 1; //  Transmission on.
    TXSTAbits.SYNC = 0; //  Asinc mode.
    TXSTAbits.BRGH = 0; //  Low rate bauds.
    BAUDCONbits.BRG16 = 0; //  Bauds mode to 8bits.
    RCSTAbits.SPEN = 1; //  Set modle SSP as UART.
    TRISBbits.RB4 = 0; //RX pin set as output led
    //  Calculate the SPBRG value
    SPBRG = (unsigned char) (((_XTAL_FREQ / baud) / 64) - 1);
    
    //Interrupt Configuration
    RCSTAbits.CREN=1; // To enable continuous reception
    PIE1bits.RCIE=1; // To enable the Reception (Rx) Interrupt
    INTCONbits.PEIE = 1; //enable peripheral interrupts
    INTCONbits.GIE = 1; //enable global interrupts
}

void main(int argc, char** argv) {
    Setup();
    SerialPrint("\n\0",1);
    SerialPrint("----------------------------------\0",1);
    SerialPrint("---- 2019 Gokuhs - TX/RX TEST ----\0",1);
    SerialPrint("----------------------------------\0",1);
    SerialPrint("\n\0",1);
    SerialPrint("Hi! I repeat all do you say!\0", 1);
    SerialPrint("(Endline char: '}') -> \0", 0);
    Delay1Second();
    while (1) {
        if (SerialPending() == 1){
            SerialPrint("Received: \0", 0);
            SerialPrint(ReadSerial(),1);
            SerialPrint("\n\0", 0);
            SerialPrint("(Endline char: '}') -> \0", 0);
        }
    }
}

