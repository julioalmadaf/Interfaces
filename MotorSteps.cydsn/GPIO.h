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
#ifndef _GPIO_H_
#define _GPIO_H_

extern unsigned char FLED;
extern unsigned char FMOTOR;
extern unsigned char FINTTIMER;
extern unsigned char FINTLCD;
extern unsigned int CounterLed;

    void INTTIMER(void);
     
    void INTLCD(void);
    
    void InitAll(void);
    
    void ControlLED(void);
    
    void LED1SEC(void);
    
    void CountLed(void);
    
    void CheckTEMP_LIMIT(void);
    
#endif
/* [] END OF FILE */
