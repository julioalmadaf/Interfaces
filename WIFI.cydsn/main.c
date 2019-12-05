/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *a
 * ========================================
*/
#include "project.h"
unsigned char RECEIVE_MSG=0; 
unsigned char ip_r2r=0;
unsigned char staip_r2r=0;
unsigned char row=0;
unsigned char cont=0;
unsigned char staip[15];
unsigned char msj[100];
unsigned char m=0;
unsigned char s;
unsigned char msg=0;
CY_ISR(RX_ISR){
    RX_ISR_ClearPending();
    s= UART_GetByte();

    if(staip_r2r){
		if(s==34){
                staip_r2r=0;
                RECEIVE_MSG=1;
        }else{
            staip[cont++]=s; // se llena la ip address con puntos
        }
	}
	else if(ip_r2r){
		if(row==4){
			if(s==34){ //" fue recibida y a continuacion viene la ip
				staip_r2r=1;
				ip_r2r=0;
                UART_GetByte();
			}
		}else{
			if(s==13){
			row++; // para llegar al renglon 3 sin guardar los bytes
			}
		}
	}else if(RECEIVE_MSG){
        if(s==47){
            msg=1;
           }else if(msg){
            if(s!=0x20){
                msj[m++]=s;
            }else{
                RECEIVE_MSG=0;
            }
        }
        
    }
}



int main(void)
{
    
    RX_ISR_StartEx(RX_ISR);
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    CyDelay(3000);
    UART_PutString("AT\r\n");
    CyDelay(3000);
    UART_PutString("AT+CWMODE=3\r\n");
    CyDelay(3000);
    //*** para conectarse a la red ***
    UART_PutString("AT+CWJAP=");
    UART_PutChar(0x22);
    UART_PutString("AndroidAP");
    UART_PutChar(0x22);
    UART_PutString(",");
    UART_PutChar(0x22);
    UART_PutString("pendejos");
    UART_PutChar(0x22);
    UART_PutString("\r\n");
    CyDelay(5000);
    //********************************
    //*** configurar para multiples conexiones ***
    UART_PutString("AT+CIPMUX=1\r\n");
    CyDelay(3000);
    //********************************************
   // *** configurar como servidor en el puerto 80 **
    UART_PutString("AT+CIPSERVER=1,80\r\n");
    CyDelay(3000);
    //***********************************************
    //para recibir tu ip
    UART_PutString("AT+CIFSR\r\n");
    //CyDelay(3000);
	// 30 primeros ascii recibidos son de la APIP incluyendo el enter. Suponiendo que la ip es de 3 digitos por cada punto
	// 33 siguientes ascii recibidos son de la APMAC incluyendo el enter
	// para la staip>> 14 primeros ascii son +cifsr:staip, "     y posteriormente viene la ip add seguida de "\n
	ip_r2r=1;
    
    for(;;)
    {
    
    }
}
