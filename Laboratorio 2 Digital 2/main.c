/*
 * Laboratorio 2 Digital 2.c
 *
 * Created: 18/07/2024 05:34:18 p. m.
 * Author : josei
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "SETUPS/ADC/ADC.h"
#include "SETUPS/LCD/LCD.h"
#include "SETUPS/UART/UART.h"


//VARIABLES
uint8_t contador = 0;
uint16_t ADC1 = 0;
uint16_t ADC2 = 0;

char lista[] = {'0','1','2','3','4','5','6','7','8','9'}; //Lista de numeros a mostrar

int centenas1 = 0;
int decenas1 = 0;
int unidades1 = 0;
int centenas2 = 0;
int decenas2 = 0;
int unidades2 = 0;
int centenas3 = 0;
int decenas3 = 0;
int unidades3 = 0;
int millares1 = 0;
int millares2 = 0;
uint8_t valorUART = 0;

void UART_COUNTER(char valorUART);
void UART_SEPARAR_COUNTER(void);
float map0(float duty, float Imin, float Imax, float Omin, float Omax);

int main(void){
	cli();
	
	initADC();
	initLCD8bits();
	initUART9600();
	LCD_Set_Cursor(1,1);
	LCD_Write_String("V1");
	LCD_Set_Cursor(6,1);
	LCD_Write_String("V2");
	LCD_Set_Cursor(11,1);
	LCD_Write_String("C");
	sei();
	
    while (1) 
    {
		ADC1 = ADC_CHANEL_SELECT(0);				//SELECCIONAR CANAL DE ADC
 		ADC1 = map0(ADC1, 0, 255, 0, 500);
		int centenas1 = ADC1/100;
 		int decenas1 = (ADC1/10)% 10;
 		int unidades1 = ADC1% 10;
		LCD_Set_Cursor(1,2);						//SELECCIONAR DONDE SE ESCRIBIRÁ EN LA LCD
		LCD_Write_Char(lista[centenas1]);				//ESCRIBIR
 		LCD_Write_String(".");
 		LCD_Write_Char(lista[decenas1]);					//ESCRIBIR
 		LCD_Write_Char(lista[unidades1]);				//ESCRIBIR
		_delay_ms(10);								//DELAY
		
		
		ADC2 = ADC_CHANEL_SELECT(1);	//SELECCIONAR CANAL DE ADC
		ADC2 = map0(ADC2, 0, 255, 0, 500);
		int centenas2 = ADC2/100;
		int decenas2 = (ADC2/10)% 10;
		int unidades2 = ADC2% 10;
		LCD_Set_Cursor(6,2);			//SELECCIONAR DONDE SE ESCRIBIRÁ EN LA LCD
		LCD_Write_Char(lista[centenas2]);				//ESCRIBIR
		LCD_Write_String(".");
		LCD_Write_Char(lista[decenas2]);					//ESCRIBIR
		LCD_Write_Char(lista[unidades2]);				//ESCRIBIR
		_delay_ms(10);					//DELAY
		
		LCD_Set_Cursor(11,2);			//SELECCIONAR DONDE SE ESCRIBIRÁ EN LA LCD
		LCD_Write_Char(lista[centenas3]);				//ESCRIBIR
		LCD_Write_Char(lista[decenas3]);				//ESCRIBIR
		LCD_Write_Char(lista[unidades3]);				//ESCRIBIR
		_delay_ms(10);					//DELAY
		
    }
}

void UART_COUNTER(char valorUART){
	switch(valorUART){
		case '+':
		unidades3++;
		writeTextUART("mas");
		break;
		case '-':
		unidades3--;
		writeTextUART("menos");
		break;
	}
}

void UART_SEPARAR_COUNTER(void){
	if (unidades3 == 10){
		unidades3 = 0;
		decenas3++;
		if(decenas3 == 10){
			decenas3 = 0;
			centenas3++;
			if (centenas3 == 10){
				centenas3 = 0;
				decenas3 = 0;
				unidades3 = 0;
			}
		}
	}
	else if (unidades3 == -1){
		if(decenas3 == 0 && centenas3 == 0){
			unidades3 = 9;
			decenas3 = 9;
			centenas3 = 9;
		}
		else if (decenas3 != 0){
			decenas3--;
			unidades3 = 9;
 		}
		 else if (decenas3 == 0 && centenas3 != 0){
			 centenas3--;
			 decenas3 = 9;
			 unidades3 = 9;
		 }
	}

	
}

float map0(float duty, float Imin, float Imax, float Omin, float Omax){
	return ((duty - Imin)*(Omax - Omin)/(Imax - Imin)) + Omin;
}

ISR(USART_RX_vect){
	valorUART = UDR0;
	UART_COUNTER(valorUART);
	UART_SEPARAR_COUNTER();
	while(!(UCSR0A & (1<<UDRE0)));		//HASTA QUE NO HAYAN CARACTERES
}