/* 
 * File:   utils.c
 * Author: gokuhs
 *
 * Created on 3 de mayo de 2019, 16:54
 */
#include <xc.h>
#include "utils.h"
#include "configure.h"

#define LED LATBbits.LB4

void LEDON(){
    LED =1;
}

void LEDOFF(){
    LED =0;
}

void Delay1Second()
{
    int i=0;
    LED =1;
    for(i=0;i<20;i++)
    {
         __delay_ms(10);
    }
    LED =0;
    for(i=0;i<20;i++)
    {
         __delay_ms(10);
    }
    LED=1;
    for(i=0;i<20;i++)
    {
         __delay_ms(10);
    }
    LED =0;
    for(i=0;i<20;i++)
    {
         __delay_ms(10);
    }
    LED =1;
    for(i=0;i<20;i++)
    {
         __delay_ms(10);
    }
    LED =0;
}