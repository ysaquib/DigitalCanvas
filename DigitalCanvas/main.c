
#include <stdint.h>
#include <stdbool.h>
#include <tm4c123gh6pm.h>
#include <sysctl.h>
#include "timer.h"
#include "Serial.h"


#define PORTB GPIO_PORTB_DATA_R
#define PORTE GPIO_PORTE_DATA_R
#define PORTF GPIO_PORTF_DATA_R

void PLLInit()
{
    SYSCTL_RCC2_R |= 0x80000000;
    SYSCTL_RCC2_R |= 0x00000800;
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) + 0x00000540;
    SYSCTL_RCC2_R &= ~0x00000070;
    SYSCTL_RCC2_R &= ~0x00002000;
    SYSCTL_RCC2_R |= 0x40000000;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (4 << 22);
    while ((SYSCTL_RIS_R &0x00000040)==0){};
    SYSCTL_RCC2_R &= ~0x00000800;
}

void setServoX (uint32_t high)
{
    uint32_t bigBoy = TIMER1_TAPR_R << 16 + TIMER1_TAILR_R;
    bigBoy = bigBoy - high * 80 - 1;
    TIMER1_TAMATCHR_R = bigBoy & 0xFFFF;
    TIMER1_TAPMR_R = bigBoy >> 16;
}

void setServoY (uint32_t high)
{
    uint32_t bigBoy = TIMER2_TAPR_R << 16 + TIMER2_TAILR_R;
    bigBoy = bigBoy - high * 80 - 1;
    TIMER2_TAMATCHR_R = bigBoy & 0xFFFF;
    TIMER2_TAPMR_R = bigBoy >> 16;
}

void Timer1A_Init()
{
    SYSCTL_RCGCTIMER_R |= 0x02;     // activate TIMER1
    GPIO_PORTF_AFSEL_R |= 0x04;                // enable alternative functions for PF2
    GPIO_PORTF_DEN_R |= 0x04;                   // enable digital port for PF2
    GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFF0FF) + 0x0000700; // GPIO
    TIMER1_CTL_R = 0x00000000;      // disable TIMER1A during setup
    TIMER1_CFG_R = 0x00000004;      // set to 32-bit mode
    TIMER1_TAMR_R = 0x0000000A;     // set to pwm mode
    TIMER1_TAILR_R = 0x6A00; // set reset value
    TIMER1_TAPR_R = 0x18; // Activate pre-scale
    setServoX(1500);
    TIMER1_CTL_R |= 0x00000001;      // enable TIMER1A
}

void Timer2A_Init()
{
    SYSCTL_RCGCTIMER_R |= 0x04;     // activate TIMER1
    GPIO_PORTF_AFSEL_R |= 0x10;                // enable alternative functions for PF4
    GPIO_PORTF_DEN_R |= 0x10;                   // enable digital port for PF4
    GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFF0FFFF) + 0x00070000; // GPIO
    TIMER2_CTL_R = 0x00000000;      // disable TIMER2A during setup
    TIMER2_CFG_R = 0x00000004;      // set to 32-bit mode
    TIMER2_TAMR_R = 0x0000000A;     // set to pwm mode
    TIMER2_TAILR_R = 0x6A00; // set reset value
    TIMER2_TAPR_R = 0x18; // Activate pre-scale
    setServoY(1500);
    TIMER2_CTL_R |= 0x00000001;      // enable TIMER1A
}
void TimerInit(void)
{
    // ENABLE TIMER
    SYSCTL_RCGCTIMER_R |= 0x01;//|= 0x01;                 //  Activate Timer 0
    TIMER0_CTL_R &= ~0x00000001; // Disable timer 0 for configuration
    TIMER0_CFG_R = 0x00000004; // Configure for 16-bit capture mode
    TIMER0_TAMR_R = 0x00000007;
    TIMER0_CTL_R |= 0x0000000C; // configure for rising and falling edge
    TIMER0_TAILR_R = 0x0000FFFF; // Start value for count down
    TIMER0_TAPR_R = 0xFF; // Activate pre-scale
    TIMER0_IMR_R |= 0x00000004; // Enable Input capture interrupts
    TIMER0_CTL_R |= 0x00000001; // Timer 0A 24-bit, rising edge
    NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF) | 0x40000000;
    NVIC_EN0_R = 1<<19;




}

void Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x32;              // enable clock for PORT B & E & D

    PLLInit();
    SystickInit();
    SetupSerial();
    TimerInit();

    GPIO_PORTB_LOCK_R = 0x4C4F434B;         // this value unlocks the GPIOCR register.
    GPIO_PORTB_CR_R = 0xFF;
    GPIO_PORTB_AMSEL_R = 0x00;              // disable analog functionality
    GPIO_PORTB_PUR_R = 0x11;                // enable pullup resistors on PF0 and PF4
    GPIO_PORTB_DIR_R |= 0x40;               // Make PB6 an output
    GPIO_PORTB_AFSEL_R = 0x00;
    GPIO_PORTB_DEN_R |= 0x40;               // Enable Digital Functionality
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xF0FFFFFF) + 0x07000000;

    GPIO_PORTE_LOCK_R = 0x4C4F434B; // this value unlocks the GPIOCR register.
    GPIO_PORTE_CR_R = 0xFF;
    GPIO_PORTE_AMSEL_R = 0x00; // disable analog functionality
    GPIO_PORTE_PCTL_R = 0x00000000; // Select GPIO mode in PCTL
    GPIO_PORTE_DIR_R = 0xFF; // Set port E1 to input and everything else as output
    GPIO_PORTE_AFSEL_R = 0x00; // Disable alternate functionality
    GPIO_PORTE_DEN_R = 0xFF; //Enable digital ports

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // this value unlocks the GPIOCR register.
    GPIO_PORTF_CR_R = 0xFF;
    Timer1A_Init();
    Timer2A_Init();


}




bool done = true;
uint32_t first = 0;
uint32_t pulseWidth = 0;
uint32_t pulse = 0;
int ind = 0;
bool fullPulse = false;

uint32_t senderCounter = 0;
uint32_t delayCounter = 0;
uint32_t periodCounter = 0;
bool startSend = false;
bool startDelay = false;

int distance0X = 0;
int distance1X = 0;
int distance0Y = 0;
int distance1Y = 0;
int errorX = 0;
int position = 1400;
int moveCounter = 0;
int sender = -1;

int posMotorX = 1500;
int posMotorY = 1500;

int move = 0;
void Timer0A_Handler(void)
{

    TIMER0_ICR_R = 0x00000004; // acknowledge the interrupt
    // calculate the period
    pulseWidth = (first - TIMER0_TAR_R) & 0x00FFFFFF;
    // remember the timer for next time
    first = TIMER0_TAR_R;
    // set flag to say that period has a new value and set port to sending mode when a full high pulse is received
    if(fullPulse)
    {
        GPIO_PORTB_DIR_R = 0x40; // Set to Output Mode
        GPIO_PORTB_AFSEL_R = 0x00; // disable alternate functionality =
        done = true;
    }
    // to make sure that we send again only when we've received a full high pulse
    fullPulse = !fullPulse;

}


char* getSensor (int i)
{
    if (i < 10) return      "ZERO  ";
    else if (i < 20) return "ONE   ";
    else if (i < 30) return "TWO   ";
    else return "THREE   ";
}

int getSensorAngle (int i)
{
    if (i < 10)      return posMotorX;
    else if (i < 20) return posMotorX;
    else if (i < 30) return posMotorY;
    else             return posMotorY;
}

void sendPulse(int delay)
{
    PORTB = 0x40;
    SysTick_Wait1microsec(delay);
    PORTB = 0x00;
    //SysTick_Wait1microsec(delay);
    GPIO_PORTB_DIR_R &= ~0x40; //Set to Input Mode
    GPIO_PORTB_AFSEL_R  |= 0x40;
    senderCounter = 0;
    delayCounter = 0;
    done = 0;
}

int oldDistX = 0;
int oldDistY = 0;

int min(x,y)
{
    if(x < y) return x;
    else return y;
}
int lastChangeX = 0;
int lastChangeY = 0;
int limit = 35;
void getPositionX()
{
    int upLimit = 1600;
    int loLimit = 1000;
    int speed = 3;
    int current = min(distance0Y, distance1Y);
    int delta = current - oldDistY;
    if(delta < -1 && posMotorX < upLimit)
    {
        lastChangeX = 1;
        oldDistY = current;
        if ((distance1X > limit) || (distance0X > limit)) posMotorX += speed;

    }
    else if(delta > 1 && posMotorX > loLimit)
    {
        lastChangeX = -1;
        oldDistY = current;
        if ((distance1X > limit) || (distance0X > limit)) posMotorX -= speed;

    }
    else if(distance1X > limit || distance0X > limit)
    {
        if(lastChangeX > 0 && posMotorX < upLimit)
            {
                posMotorX += speed;

            }
            else if(lastChangeX < 0 && posMotorX > loLimit)
            {
                posMotorX -= speed;

            }

    }
}

void getPositionY()
{
    int upLimit = 2000;
    int loLimit = 1600;
    int speed = 3;
    int current = min(distance0X, distance1X);
    int delta = current - oldDistX;
    if(delta > 1 && posMotorY < upLimit)
        {
            lastChangeY = 1;
            oldDistX = current;
            if ((distance1Y > limit) || (distance0Y > limit)) posMotorY += speed;

        }
        else if(delta < -1 && posMotorY > loLimit)
        {
            lastChangeY = -1;
            oldDistX = current;
            if ((distance1Y > limit) || (distance0Y > limit)) posMotorY -= speed;

        }
        else if(distance1Y > limit || distance0Y > limit)
        {
            if(lastChangeY > 0 && posMotorY < upLimit)
                {
                    posMotorY += speed;

                }
                else if(lastChangeY < 0 && posMotorY > loLimit)
                {
                    posMotorY -= speed;

                }

        }


}




char* itoa(int value, char* result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int sendBoi = 0;

int main(void)
{
    Init();

    int data;
    int pw;
    bool send = done;

   // int posDelay = 1;
    char snum[12];
    while (1)
    {

        send = done;
        pw = pulseWidth/340/20;
        data = pw;

        if(send)
        {

            SerialWrite("Sensor  -  ");
            SerialWrite(getSensor(sender));
            SerialWrite("  -  ");
            SerialWrite(itoa(getSensorAngle(sender),snum,10));
            SerialWrite("  -  ");
            SerialWriteInt(data);
            sendBoi = (sendBoi + 1) % 100;
            sender = (sender + 1) % 40;
            if (sender < 10)
            {
                distance0X = data;
                PORTE = ~0x01;
            }
            else if (sender < 20)
            {
                distance1X = data;
                PORTE = ~0x02;
            }
            else if (sender < 30)
            {
                distance1Y = data;
                PORTE = ~0x08;

            }
            else
            {
                distance0Y = data;
                PORTE = ~0x04;

            }

            SysTick_Wait1ms(2);
            sendPulse(10);

        }

        //if ((distance1X > limit) || (distance0X > limit))
        getPositionX();

       // if (distance1Y > limit || distance0Y > limit)
        getPositionY();



        setServoY(posMotorY);
        setServoX(posMotorX);

        SysTick_Wait1ms(7);
    }
}

