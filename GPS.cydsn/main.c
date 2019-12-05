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
unsigned char s=0; //ascii symbol}
unsigned char d=0;
unsigned char e=0;
unsigned char f=0;
unsigned char g=0;
unsigned char buff_busy=0; 
unsigned char cont=0;
unsigned char date[8];
unsigned char time[10];
unsigned char lat[10];
unsigned char lon[11];
unsigned char fecha;

CY_ISR(RX_ISR){
    RX_ISR_ClearPending();
    s= UART_GetByte();
    if(!buff_busy)
    {
        if ( s >0x00)
        {
            buff_busy=1;
        }
        else
        {
            buff_busy=0;
            cont=0;
            UART_PutString("1 AT+CGNSINF\n");
        }
    }
    else
    {
        cont++;
        //*************date**********************
        if(cont>13 && cont<22){
            if(s>=0x30)
            {
                date[d++]=s;
            }
            else
            {
                //buff_busy=0;
                cont=0;
                UART_PutString("2 AT+CGNSINF\n");
            }
        }
        //*************time**********************
        else if(cont>21 && cont<32)
        {
            if(s>=0x00)
            {
                time[e++]=s;
            }
            else
            {
                //buff_busy=0;
                cont=0;
                UART_PutString("3 AT+CGNSINF\n");
            }
        }
        //*************latitud**********************
        else if(cont>32 && cont<42)
        {
            if(s>=0x00)
            {
                lat[f++]=s;
            }
            else
            {
                //buff_busy=0;
                cont=0;
                UART_PutString("4 AT+CGNSINF\n");
            }
        //***************************************
        }
        //*************longitud**********************
        else if(cont>42 && cont<53)
        {
            if(s>=0x00)
            {
                lon[g++]=s;
            }
            else
            {
                //buff_busy=0;
                cont=0;
                UART_PutString("4 AT+CGNSINF\n");
            }
        //***************************************
        } 
    }
}

void print_date()
{
    UART_PutChar(date[6]);   
    UART_PutChar(date[7]);
    UART_PutString("/");
    UART_PutChar(date[4]);
    UART_PutChar(date[5]);
    UART_PutString("/");
    UART_PutChar(date[0]);
    UART_PutChar(date[1]);
    UART_PutChar(date[2]);
    UART_PutChar(date[3]);  
}

void print_time()
{
    UART_PutChar(time[0]);   
    UART_PutChar(time[1]);
    UART_PutString(":");
    UART_PutChar(time[2]);
    UART_PutChar(date[3]);
    UART_PutString(":");
    UART_PutChar(time[4]);
    UART_PutChar(time[5]);  
}



int main(void)
{
    
    RX_ISR_StartEx(RX_ISR);
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_PutString("AT+CGNSPWR=1\n");
    CyDelay(1000);
    UART_PutString("AT+CGNSINF\n");
    for(;;)
    {
        if (cont==53){
        UART_PutString("\r\nDate : ");
        print_date();
        UART_PutString("\r\nTime : ");
        print_time();
        UART_PutString("\r\nLatitude : ");
        UART_PutArray(lat,10);
        UART_PutString("\r\nLongitud : ");
        UART_PutArray(lon,11);
        cont=0;
        d=e=f=g=0;
        buff_busy=0;
        /*AT+CGNSINF
+CGNSINF: 1,1,20180311193209.000,20.738190,-103.452480,1365.800,0.91,87.2,1,,1.4,1.7,1.0,,10,7,,,43,,
        */
        }
    }
        /* Place your application code here. */
}


/* [] END OF FILE */
