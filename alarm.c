// Alarm program
// Created by Caleb Perez
// Date: 3/25/21
// alarm.c

#include "msp.h"
#include "Clock.h"
#include "TExaS.h"

void main()
{
     //CONFIG

     Clock_Init48MHz();
     TExaS_Init(LOGICANALYZER_P2);

     //Set all of port 1 to GPIO.
     P1 -> SEL0 = 0x00;
     P1 -> SEL1 = 0x00;
     //Set port 1.1 and 1.4 as inputs, this actually sets all the ports as inputs.
     P1 -> DIR = 0x00;
     //Enable port 1.1 and 1.4 resistors
     P1 -> REN = 0x12;

     //Set all of port 2 to GPIO
     P2 -> SEL0 = 0x00;
     P2 -> SEL1 = 0x00;
     //Set ports 2.0 (red) and 2.1 (green) to output
     P2 -> DIR = 0x03;
     P2 -> OUT = 0x00;


    while(1)
    {
        //Button bounce/press delay
        Clock_Delay1ms(500);

        //First while loop sets the alarm system into inactive mode.
        while (1)
        {
            //Turn on green LED
            P2 -> OUT = 0x02;

            //Check status of activate button
            if ((P1 -> IN & 0x10) == 0x00)
            {
                //If button is pushed then break out of the while loop.
                break;
            }
        }

        //Button bounce/press delay
        Clock_Delay1ms(500);

        //This while loop keeps the alarm system in active mode.
        while (1)
        {
            //Turn on red LED
            P2 -> OUT = 0x01;

            //If window button is pressed.
            while((P1 -> IN & 0x02) == 0x00)
            {
                //Flash RED LED.
                P2 -> OUT = P2 -> OUT ^ 0x01;
                Clock_Delay1ms(100);
            }

            //Check status of activate button
            if ((P1 -> IN & 0x10) == 0x00)
            {
                //If button is pushed then break out of the while loop.
                break;
            }
        }

    }
}
