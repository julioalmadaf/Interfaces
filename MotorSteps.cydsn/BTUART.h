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

#ifndef _BTUART_H_
#define _BTUART_H_
    
extern unsigned char FRPS;
extern unsigned char FMON;
extern unsigned char FDONE;
extern unsigned char FMOFF;
extern unsigned char FGRAD;
extern unsigned int counter;
extern unsigned int valor;
extern unsigned int steps;
extern unsigned char rps1;
extern unsigned char rps2;
extern unsigned char rps3;
extern unsigned char frps;
extern unsigned char FCAMBIO;

extern unsigned char CounterTemp;
extern unsigned char F5SEGS;
extern unsigned char FOVTEMP;
extern unsigned char FOVREADY;
extern unsigned int temp;
extern unsigned int TEMP_LIMIT;
extern unsigned char temperature[7];
 
    
void GeneralEventHandler(uint32 event, void *eventParam);
void Eval(void);

#endif
/* [] END OF FILE */
