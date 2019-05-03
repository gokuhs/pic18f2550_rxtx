# PIC18F2550 RX/TX Test
Full example to configure an a PIC18F2550 to use RX/TX pins to send/receive data.

After a lot of searching online I got to communicate with the PIC through its UART/USART. Since I was unable to find a complete example on which to base myself, here I leave one fully functional.

# CONFIGURATION

The internal oscillator is used, so you do not have to use the soldering iron. ;)

In my example I use an LED on pin 25 (RB4)

I use MPLABX IDE V5.15 and XC8 V1.34) to compile it

# THANKS

Thanks to these two sources I was able to complete the project:
- https://www.makerelectronico.com/comunicacion-serial-uart-usart-rs232-pic18f4550/ 
- https://stackoverflow.com/questions/33212059/rcreg-data-pic-18f4550-not-displaying-value
