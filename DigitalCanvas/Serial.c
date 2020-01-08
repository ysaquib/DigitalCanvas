/*
 * Serial.c
 *
 *  Created on: Feb 12, 2017
 *      Author: srazak
 */
#include <stdint.h>
#include <stdbool.h>
#include <tm4c123gh6pm.h>
#include <sysctl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <hw_i2c.h>
#include <hw_memmap.h>
#include <hw_types.h>
#include <hw_gpio.h>
#include <i2c.h>
#include <sysctl.h>
#include <gpio.h>
#include <pin_map.h>


void SetupSerial()
{
    SYSCTL_RCGCUART_R = 0x01;
    SYSCTL_RCGCGPIO_R |= 0x01;

    //GPIO_PORTA_CR_R = 0xFF;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_PCTL_R = 0x11;


    UART0_CTL_R &= ~UART_CTL_UARTEN;
    UART0_IBRD_R = 0x8;;
    UART0_FBRD_R = 0x2C;
    UART0_LCRH_R = 0x0070;
    UART0_CTL_R |= UART_CTL_UARTEN;
    UART0_IFLS_R = 0x12;
    UART0_CC_R = 0x05;

}
void SerialWrite(char * st)
{
    char* temp = st;
    while (*temp!=0)
    {
        while(UART0_FR_R & 0x20);
        UART0_DR_R = *temp;
        temp++;
        asm("    NOP");
        asm("    NOP");
    }

}
void SerialWriteLine(char * st)
{
    SerialWrite(st);
    while(UART0_FR_R & 0x20);
    UART0_DR_R = 13;
    asm("    NOP");
    asm("    NOP");
    while(UART0_FR_R & 0x20);
    UART0_DR_R = 10;
    asm("    NOP");
    asm("    NOP");

}
void SerialWriteInt(int n)
{
    // change n to String
    char str[] = {'0','0','0','0','0','0','0','0','0','0',0};
    int i = 9;
    while (n>0)
    {
        str[i] = '0'+n%10;
        n = n /10;
        i--;
    }
    char * ch = str;
    while (*ch!=0 && *ch=='0')
        ch++;
    SerialWriteLine(ch);
}
