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



int main(void)
{   
    CyGlobalIntEnable; /* Enable global interrupts. */
     
    /* PlacLCD_Write('C');e your initialization/startup code here (e.g. MyInst_Start()) */
    
    InitAll(); //inicializacion de todo
    
    for(;;)
    {
        CyBle_ProcessEvents(); //Checa lo del BT
        
        if(FINTTIMER==1) INTTIMER(); //checa si ya hubo una interrupcion
        
        MOTOR(); //Controla todas las acciones del motor

    }
}
  

/* [] END OF FILE */
