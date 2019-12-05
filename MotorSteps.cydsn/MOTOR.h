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
#ifndef _MOTOR_H_
#define _MOTOR_H_
    
#define MOTOR_OFF		Pines_Write(0b0000);
    
extern unsigned char direction;
extern unsigned int velocidad;

void MOTOR(void);    
void ControlMotor(void);

#endif

/* [] END OF FILE */
