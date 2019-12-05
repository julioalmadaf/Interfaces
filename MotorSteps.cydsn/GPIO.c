/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <project.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MOTOR.h"
#include "BTUART.h"
#include "POT.h"
#include "GPIO.h"
#include "LCD.h"

unsigned char FLED;
unsigned char FMOTOR;
unsigned char FINTTIMER;
unsigned char FINTLCD;
unsigned int CounterLed;

unsigned char interruption_flag;

CY_ISR(Timer_Int_Handler) //interrupcion del timer para el motor y led de 1 seg
{
    FINTTIMER=1;
}    


void INTTIMER(void) //timer para controlar motor y led de 1 seg
{
    counter++;
	CounterLed++;
    FINTTIMER=0;
    Timer_int_ClearPending();
}

void InitAll(void)
{
 CyBle_Start(GeneralEventHandler);
//Inicializacion del timer
    Timer_Start();
    Timer_int_StartEx(Timer_Int_Handler);
  

 //Inicializacion de variables
    FLED=1;
    TEMP_LIMIT=999;
    velocidad=1350;
    FMON=1;
    FCAMBIO=1;
}
