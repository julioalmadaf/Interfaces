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


unsigned char secuencia[]={0b0001,0b0011,0b0010,0b0110,0b0100,0b1100,0b1000,0b1001}; 
unsigned char i;
unsigned char FLED;
unsigned char FMOTOR;

CY_ISR(Timer_Int_Handler)
{
    FLED=1;
    FMOTOR=1;
    
    Timer_int_ClearPending();
}    

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FLED=1;
    FMOTOR=1;
    Timer_Start();
    Timer_int_StartEx(Timer_Int_Handler);
    
    for(;;)
    {
        if(FMOTOR==1)    
        {
            Pines_Write(secuencia[(i++)%8]);
            FMOTOR=0;
        }
        if(FLED==1) 
        {
            Pin_Red_Write( ~ Pin_Red_Read());
            FLED=0;
        }
        
            //CyDelay(1000);
    }
}

/* [] END OF FILE */
