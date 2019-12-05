#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "types.h"

#define TIME_BIT 105
#define TxD_ENABLE PTBDD_PTBDD0 = 1 
#define TxD_PIN PTBD_PTBD0 
#define VALUE_OC_TX TPMC0V 
#define MASTER_TIMER TPMCNT

#define RxD 		PTBD_PTBD5
#define VALUE_OC_RX	TPMC1V
#define MASTER_TIMER 	TPMCNT
#define CAPTURE_TIME	((3*TIME_BIT)/2)

//TX
unsigned char u8counterTxInterruption, THR;
unsigned char message[] = {"HOLA"};
unsigned char u8_messageSizeTx;
unsigned char u8characters_To_Transmit[10];



unsigned char u8_characterSentTx;
unsigned char u8_charactersCounterTx;
unsigned char u8Buffer_Tx_Index_Interruption;
unsigned char u8Buffer_Tx_Index;


//RX
unsigned int u8_timeRx;
unsigned char u8_conterRxInterruption; //para tener control de cuantos bits tengo que leer
unsigned char u8_dataInterruptionRx;
unsigned char u8_frame_error_Rx;
unsigned char u8_data_ready_Rx;
unsigned char u8_ic_Rx;

unsigned char bufferRx[100];
unsigned char bufferRx_counter;


void UART_init(void)
{
	TPMSC = 0b00001010; // configure tpm main timer as free run
						// w/busclock(4Mhz) and preescaler divide by 4
	TPMC0SC = 0b00010000; //Configuring as output compare
	TPMMOD = 0xfffe;

	//Pin de salida
	TxD_PIN = 1;
	TxD_ENABLE;
	
	u8_characterSentTx = 1;
	u8_charactersCounterTx = 0;
	u8Buffer_Tx_Index_Interruption = 0;
	
	
	//Rx
	//se habilitan las interrupciones del input capture
	TPMC1SC = 0b01001000;
		
	u8_ic_Rx = 1;
	//configure RxD Input Capture as falling edge
	
	bufferRx_counter = 0;
	
}

interrupt VectorNumber_Vtpmch1 void IC_OC(void)
{
	//CH1 flag off
	(void) TPMC1SC;
	TPMC1SC_CH1F = 0;
	
	if(u8_ic_Rx)
	{
		u8_timeRx = MASTER_TIMER;
		
		//configurar como OC para a partir de aqui muestrear
		TPMC1SC = 0b01010000; //Configuring as output compare
		
		VALUE_OC_RX = u8_timeRx + CAPTURE_TIME; //la operacion * y / la resuelve el compilador, es una constante
		u8_ic_Rx=0;
		u8_conterRxInterruption=0;
	
	}
	else
	{
		if(u8_conterRxInterruption<8)
		{
			u8_dataInterruptionRx>>=1;
			if(RxD==1)
			{
				u8_dataInterruptionRx|=0x80;
			}
			u8_conterRxInterruption++;
			VALUE_OC_RX+=TIME_BIT;

		}
		else
		{
			if(RxD==0)
			{
				u8_frame_error_Rx=1;

			}
			else
			{
				u8_frame_error_Rx=0;
				u8_data_ready_Rx=1;
				u8_ic_Rx = 1;
				//configurar nuevamente como IC
				TPMC1SC = 0b01001000;

				bufferRx[bufferRx_counter++] = u8_dataInterruptionRx;
				
				if(u8_dataInterruptionRx == 32){
					bufferRx_counter = 0;
				}
			}
		}
		
	}
	
}

interrupt VectorNumber_Vtpmch0 void Tx_interrupt(void)
{
	//CH0 flag off
	(void) TPMC0SC;
	TPMC0SC_CH0F = 0;
	
	//Modifying value oc
	VALUE_OC_TX+=TIME_BIT;
	
	u8counterTxInterruption--;
	if(u8counterTxInterruption<10 && u8counterTxInterruption>1)
	{
		if(THR & 0X01)
		{
			TxD_PIN = 1;
		}else
		{
			TxD_PIN = 0;
		}
		
		THR>>=1;
	}
	
	if(u8counterTxInterruption == 1)
	{
		TxD_PIN = 1;
	}
	if(u8counterTxInterruption == 0)
	{
		u8_characterSentTx = 1;
		
		u8_charactersCounterTx++;
		
		 //Disable interruption 
		TPMC0SC_CH0IE = 0;
	}
}

void UART_send(unsigned char dato)
{
	//CH0 flag off
	(void) TPMC0SC;
	TPMC0SC_CH0F = 0; 
	
	//Modifying value oc
	VALUE_OC_TX = MASTER_TIMER + TIME_BIT;
	
	TxD_PIN = 0;
	
	u8counterTxInterruption = 10;
	
	THR = dato;
	
	TPMC0SC_CH0IE = 1;
	
}

void UART_sendMessage(void)
{
	while(u8_charactersCounterTx < u8_messageSizeTx)
	{
		if(u8_characterSentTx)
		{
			u8_characterSentTx = 0;
			
			UART_send(u8characters_To_Transmit[u8Buffer_Tx_Index_Interruption++]);
		}
	}
	
	u8Buffer_Tx_Index_Interruption = 0;
	
	u8_charactersCounterTx = 0;
}

void UART_setCharactersToTransmit(unsigned char characters[], unsigned char size)
{
	for(u8Buffer_Tx_Index = 0; u8Buffer_Tx_Index < size; u8Buffer_Tx_Index++){
					
			u8characters_To_Transmit[u8Buffer_Tx_Index] = characters[u8Buffer_Tx_Index];
	}
	
	 u8_messageSizeTx = size;
}

void main(void) {
								EnableInterrupts;
  
 
  UART_init();
  UART_setCharactersToTransmit(message, 4);
  
  UART_sendMessage();
  
  for(;;) {
	  UART_sendMessage();
    __RESET_WATCHDOG(); 
  } 
}
