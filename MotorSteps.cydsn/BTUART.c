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

uint8 number_write = 0;
uint8 number_read= 0;
char flag_to_print=0;
unsigned char checar_arreglo =0;
//checar el de los otros checar_arreglo
unsigned char array[16];
unsigned char k; //contador del arreglo que guarda lo que recibe por BT

CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
CYBLE_GATT_ERR_CODE_T gattError;


//Validation
unsigned int grados;
unsigned char FRPS;
unsigned char FMON;
unsigned char FDONE;
unsigned char FMOFF;
unsigned char FGRAD;
unsigned int counter;
unsigned int valor;
unsigned int steps;
unsigned char rps1='5';
unsigned char rps2='0';
unsigned char rps3='0';
unsigned char frps=1;

//UART
unsigned char done[]={"\n\rDONE\n\r"};
unsigned char OverTemp[]={"OVERTEMPERATURE DETECTED\n\r"};
unsigned char CounterStr=0;
unsigned char k=0;
unsigned char j=0;
unsigned char l=0;


unsigned char CounterTemp;
unsigned char F5SEGS;
unsigned char FOVTEMP;
unsigned char FOVREADY;
unsigned int temp;
unsigned int TEMP_LIMIT;
unsigned char temperature[7];

unsigned char FCAMBIO;

void GeneralEventHandler(uint32 event, void *eventParam)
{
    
    switch (event)
    {
         
        case CYBLE_EVT_STACK_ON:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            // Start BLE advertisement for 30 seconds and update link
	        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST); 
            break; 
        
        case CYBLE_EVT_GAP_DEVICE_CONNECTED: /* BLE link is established */
            CyBle_GappStopAdvertisement(); 
            break; 
        
        case CYBLE_EVT_GATTS_WRITE_REQ: 
            //wReqparam = *(CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            //gattError = CyBle_GattsWriteAttributeValue(&wReqparam->handleValPair,0,&cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
           // palabra = *wReqparam->handleValPair.value.val;
            //CyBle_GattsWriteRsp(cyBle_connHandle);
            //printf("Palabra: %d\r\n",palabra);
            //break;
            
	    case CYBLE_EVT_GATTS_WRITE_CMD_REQ: 
        {
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;  
               
            if(wrReqParam->handleValPair.attrHandle == CYBLE_NUMBER_NUMBER_WRITE_CHAR_HANDLE)  
    	    {
                number_write = *wrReqParam->handleValPair.value.val; //Pull out the number_write value
                //word = number_write;
                if (number_write != 0) //If Client wrote anything other than 0, increment number_read++
                { 
                    number_read++; 
                    number_write = 0; 
                    if(number_read == 1){
                        int i=0;
                        for(i=0; i<16; i++){
                            array[k++] = wrReqParam->handleValPair.value.val[i];
                        }
                        k=0;
                        flag_to_print = 1;
                        number_read = 0;
                        checar_arreglo = 1;
                    }
                    /*update read characteristic*/ 
                    CYBLE_GATT_HANDLE_VALUE_PAIR_T Number_R;  
                    Number_R.attrHandle= CYBLE_NUMBER_NUMBER_READ_CHAR_HANDLE;  
                    Number_R.value.val = &number_read; 
                    Number_R.value.len = 1;
                    CyBle_GattsWriteAttributeValue(&Number_R, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED); 
                    Eval();
                } 
            }
                
            if(wrReqParam->handleValPair.attrHandle == CYBLE_NUMBER_NUMBER_NOTIFY_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                 
                    
            }   
                
             if(wrReqParam->handleValPair.attrHandle == CYBLE_NUMBER_NUMBER_INDICATE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                 
                    
            }   
            
            if (event == CYBLE_EVT_GATTS_WRITE_REQ)  
		    {
                CyBle_GattsWriteRsp(cyBle_connHandle);  
		    }             
           
            break; 
        }
        
        case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
            break; 
        
        default:
            break;
    }   
}



//Validation

void Eval(void){
	switch(array[0]) //CHECA LA PRIMER LETRA DEL STRING PARA HACER LO QUE ENTRE POR EL SERIAL
	{ 
	case 'R':  //CHECA COMANDO DE RPS
		if(array[1]=='P' && array[2]=='S' && array[3]==':' && array[6]=='.')
		{
			if((array[4] > '/') && (array[4] < ':'))
			{
				if((array[5] > '/') && (array[5] < ':'))
				{
					if((array[7] > '/') && (array[7] < ':') && array[8]==array[7])
					{
						FRPS=1;
						valor=((array[4]-'0')*100 + (array[5]-'0')*10 + (array[7]-'0')); //GUARDA EL VALOR
						rps1=array[4]; //PARA IMPRIMIR EN LA LCD
						rps2=array[5];
						rps3=array[7];
						FDONE=1;
						frps=0; //PARA DECIRLE AL LCD QUE YA SE USO EL COMANDO RPS
                        FCAMBIO=1;
					}
					else
					{
						FDONE=0;
						//SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					//SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				//SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			//SCIC2=0x2C;
		}
		break;

	case 'D':  //COMANDO DIR
		if(array[1]=='I' && array[2]=='R' && array[3]==':' && array[4]=='C')
		{
			if(array[5]=='W' && array[6]==array[5]) //CW
			{
				direction=0;
				FDONE=1;
                FCAMBIO=1;
			}
			else if(array[5]=='C' && array[6]=='W' && ((array[7]=='N') | (array[7]=='F')| (array[7]=='I') | ((array[7] > '/') && (array[7] < ':')))) //CCW
			{
				direction=1;
				FDONE=1;
                FCAMBIO=1;
			}
			else
			{
				FDONE=0;
				//SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			//SCIC2=0x2C;
		}
		break;

	case 'M':  //COMANDO DEL MOTOR
		if(array[1]=='O' && array[2]=='T' && array[3]=='O' && array[4]=='R' && array[5]==':' && array[6]=='O')
		{
			if(array[7]=='N' && array[8]==array[7]) 
			{
				FMON=1;
				FDONE=1;
				FMOFF=0;
				ControlMotor();
				counter = 0;
				frps=0;
                FCAMBIO=1;
			}
			else if(array[7]=='F' && array[8]=='F' && ((array[9]==':') |(array[9]=='u') | ((array[9] > '/') && (array[9] < ':')))) //MOTOR OFF
			{
				MOTOR_OFF;
				FMON=0;
				FDONE=1;
				FMOFF=1;
				frps=1;
                FCAMBIO=1;
			}
			else
			{
				FDONE=0;
				//SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			//SCIC2=0x2C;
		}
		break;

	case 'S':  //COMANDO DE GRADOS
		if(array[1]=='T' && array[2]=='E' && array[3]=='P' && array[4]=='C')
		{
			if( array[5]=='W' && array[6]==':')												//CW
			{
				if((array[7] > '/') && (array[7] < ':'))
				{
					if((array[8] > '/') && (array[8] < ':'))
					{
						if((array[9] > '/') && (array[9] < ':') && array[10]==array[9])
						{
							grados=((array[7]-'0')*100 + (array[8]-'0')*10 + (array[9]-'0'));
							steps=grados*12/45;
							FGRAD=1;
							direction=1; 
							FDONE=1;
						}
						else
						{
							FDONE=0;
							//SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						//SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					//SCIC2=0x2C;
				}
			}
			else if( array[5]=='C' && array[6]=='W'&& array[7]==':')					//CCW
			{
				if((array[8] > '/') && (array[8] < ':'))
				{
					if((array[9] > '/') && (array[9] < ':'))
					{
						if((array[10] > '/') && (array[10] < ':') && array[11]=='8')
						{
							grados=((array[8]-'0')*100 + (array[9]-'0')*10 + (array[10]-'0'));
							steps=grados*12/45;
							FGRAD=1;
							direction=0;
							FDONE=1;
						}
						else
						{
							FDONE=0;
							//SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						//SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					//SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				//SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			//SCIC2=0x2C;
		}

		break;

	case 'T': //COMANDO TEMPLIMIT
		if(array[1]=='E' && array[2]=='M' && array[3]=='P' && array[4]=='L' && array[5]=='I' && array[6]=='M' && array[7]=='I' && array[8]=='T' && array[9]==':' && array[13]=='.')
		{
			if((array[10] > '/') && (array[10] < ':'))
			{
				if((array[11] > '/') && (array[11] < ':'))
				{
					if((array[12] > '/') && (array[12] < ':'))
					{
						if((array[14] > '/') && (array[14] < ':') && ((array[15]=='Y')|(array[15]=='y')))
						{
							TEMP_LIMIT=(array[10]-'0')*100 + (array[11]-'0')*10 + (array[12]-'0') + (array[14]-'0');
                            //TEMP_LIMIT=(array[10]-'0')*1000 + (array[11]-'0')*100 + (array[12]-'0')*10 + (array[14]-'0');
							FDONE=1;
						}
						else
						{
							FDONE=0;
							//SCIC2=0x2C;
						}
					}
					else
					{
						FDONE=0;
						//SCIC2=0x2C;
					}
				}
				else
				{
					FDONE=0;
					//SCIC2=0x2C;
				}
			}
			else
			{
				FDONE=0;
				//SCIC2=0x2C;
			}
		}
		else
		{
			FDONE=0;
			//SCIC2=0x2C;
		}
		break;

	default:
		FDONE=0;
		//SCIC2=0x2C;
	}
}




/* [] END OF FILE */
