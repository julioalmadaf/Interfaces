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

unsigned int TEMPER;
unsigned char FADC;//********************

void OBTTEMP(void)//metodo para obtener la temperatura del ADC
{		
				TEMPER=ADC_GetResult16(0);
			    
                TEMPER*=2;
                
                if(TEMPER>=999)
                {
                    TEMPER=999;
                }
   }
/* [] END OF FILE */
