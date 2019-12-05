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
unsigned char cmt = 48;
unsigned char lulis[48]; //+CMT
unsigned char msj[160];
unsigned char m=0;
unsigned char c=0;
unsigned char l=0x0;
unsigned char READY_TO_RECEIVE=0;
CY_ISR(RX_ISR){
    RX_ISR_ClearPending();
    l= UART_GetByte();
    if (READY_TO_RECEIVE){
        if(c==cmt) {
            if( l == 13 ){
                c=0;
                m=0;
                Pin_Red_Write(~Pin_Red_Read());
                CyDelay(500);
                Pin_Red_Write(~Pin_Red_Read());
                 CyDelay(500);
                Pin_Red_Write(~Pin_Red_Read());
                 CyDelay(500);
                Pin_Red_Write(~Pin_Red_Read());
                 CyDelay(500);
                Pin_Red_Write(~Pin_Red_Read());
                 CyDelay(500);
                Pin_Red_Write(~Pin_Red_Read());
            }else{
                msj[m++]=l;
            }
        }
        else{
            if(l>0x0){
                lulis[c++]=l;
                l=0x0;
            }
        }
        l=0x0;
    }
}


int main(void)
{
    
    RX_ISR_StartEx(RX_ISR);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    
    UART_PutString("AT+CMGF=1\n");
    CyDelay(1000);
    UART_PutString("AT+CMGS=");
    UART_PutChar(0x22);
    UART_PutString("6441081756");
    UART_PutChar(0x22);
    UART_PutString("\n");
    CyDelay(1000);
    UART_PutString("SENDING MSG\n");
    UART_PutChar(0x1A);
    CyDelay(1000);
    /*UART_PutString("AT+CMGF=1\n");
    CyDelay(1000);
    UART_PutString("AT+CNMI=2,2,0,0,0\n");
    CyDelay(1000);
    READY_TO_RECEIVE=1;*/
    for(;;)
    
    
    {
        
    }
        /* Place your application code here. */
}


/* [] END OF FILE */
