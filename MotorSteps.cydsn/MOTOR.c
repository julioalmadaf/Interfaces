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

unsigned char j; //contador del arreglo del motor
unsigned int count_step;
unsigned char direction;
unsigned int velocidad;


unsigned char secuencia[]={0b0001,0b0011,0b0010,0b0110,0b0100,0b1100,0b1000,0b1001}; 


void MOTOR(void){
       if(FRPS==1){
			velocidad=98000/valor;// CONVERSION
			FRPS=0;
		}

		if(counter >= velocidad){
			if(FMON==1)
			{
				ControlMotor();
			}else if(FMON==0 && FGRAD==1){
				ControlMotor();
			}

			counter=0;
		}
}

void ControlMotor(void) //PARA CONTROLAR EL MOTOR
{
	if(direction==1)		//CHECA LA DIRECCION EN LA QUE VA EL MOTOR
	{
		Pines_Write(secuencia[(j++)%8]);
		if(FGRAD==1)		//PARA QUE SE MUEVA POR GRADOS
		{
			count_step++;
			if(count_step>=steps)
			{
				FGRAD=0;
				count_step=0;				
			}
		}
	}
	else {			
		Pines_Write(secuencia[(j--)%8]);
		if(FGRAD==1)				//PARA QUE SE MUEVA POR GRADOS
		{
			count_step++;
			if(count_step>=steps)
			{
				FGRAD=0;
				count_step=0;				
			}
		}
	}
}




/* [] END OF FILE */
