/*
 * LCD8bits.c
 *
 * Created: 18/07/2024 06:26:23 p. m.
 *  Author: josei
 */ 

#include "LCD.h"
//#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void initLCD8bits(void){
	
	DDRB |= (1<<DDB4)|(1<<DDB5);												//ESTABLECER v COMO SALIDAS PARA E Y PARA RS
	DDRD |= ((1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7));		//ESTABLECER PD2 AL PD7 COMO SALIDAS PARA D0 AL D5
	DDRB |= (1<<DDB0)|(1<<DDB1);												//ESTABLECER PB0 Y PB1 COMO SALIDAS PARA D6 Y PARA D7
	PORTD = 0;
	PORTB = 0;																	//LIMPIAMOS LOS PUERTOS
	//PORTB |= (1<<PORTB4);	//E = 1;
	// Inicialización en 8 bits
	_delay_ms(20);
	LCD_CMD(0x38);
	_delay_ms(5);
	LCD_CMD(0x38);
	_delay_ms(1);
	LCD_CMD(0x38);
	_delay_ms(1);

	// Configuración del LCD
	LCD_CMD(0x38); // Función set
	LCD_CMD(0x0C); // Display on, cursor off
	LCD_CMD(0x01); // Clear display
	_delay_ms(2);  // Esperar para el clear display
	LCD_CMD(0x06); // Entry mode set
}

void LCD_CMD(char a){
	PORTB &= ~(1<<PORTB5);	//RS = 0;
	LCD_Port(a);
	//TRANSICIÓN
	PORTB |= (1<<PORTB4);	//E = 1;
	_delay_us(1);
	PORTB &= ~(1<<PORTB4);	//E = 0;
	_delay_ms(2);
}

void LCD_Port(char a){
	if (a & 1){
		//D0 = 1;
		PORTD |= (1<<PORTD2);
	}
	else {
		//D0 = 0;
		PORTD &= ~(1<<PORTD2);
	}
	if (a & 2){
		//D1 = 1;
		PORTD |= (1<<PORTD3);
	}
	else{
		//D1 = 0;
		PORTD &= ~(1<<PORTD3);
	}
	if (a & 4){
		//D2 = 1;
		PORTD |= (1<<PORTD4);
	}
	else{
		//D2 = 0;
		PORTD &= ~(1<<PORTD4);
	}
	if (a & 8){
		//D3 = 1;
		PORTD |= (1<<PORTD5);
	}
	else{
		//D3 = 0;
		PORTD &= ~(1<<PORTD5);
	}
	if (a & 16){
		//D4 = 1;
		PORTD |= (1<<PORTD6);
	}
	else{
		//D4 = 0;
		PORTD &= ~(1<<PORTD6);
	}
	if (a & 32){
		//D5 = 1;
		PORTD |= (1<<PORTD7);
	}
	else{
		//D5 = 0;
		PORTD &= ~(1<<PORTD7);
	}
	if (a & 64){
		//D6 = 1;
		PORTB |= (1<<PORTB0);
	}
	else{
		//D6 = 0;
		PORTB &= ~(1<<PORTB0);
	}
	if (a & 128){
		//D0 = 1;
		PORTB |= (1<<PORTB1);
	}
	else{
		//D0 = 0;
		PORTB &= ~(1<<PORTB1);
	}
}

void LCD_Write_Char(char c){
	//TOMAR DATO EN EL PUERTO COMO CARACTER
	PORTB |= (1<<PORTB5);	//RS = 1;
	LCD_Port(c);
	//TRANSICIÓN
	PORTB |= (1<<PORTB4);	//E = 1;
	_delay_us(1);
	PORTB &= ~(1<<PORTB4);	//E = 0;
	_delay_ms(2);
}

void LCD_Write_String(char *a){
	int i;
	for (i=0; a[i] != '\0'; i++)
	LCD_Write_Char(a[i]);
}

void LCD_Shift_Right(void){
	LCD_CMD(0x1C);
}

void LCD_Shift_Left(void){
	LCD_CMD(0x18);
}

void LCD_Set_Cursor(char c, char f){	
	char temp;
	if (f == 1){
		temp = 0x80 + c - 1;
		//z = temp >> 4;	PARA 4 BITS
		//y = temp & 0x0F;	PARA 4 BITS
		LCD_CMD(temp);
	}	else if (f == 2){
		temp = 0xC0 + c - 1;
		//z = temp >> 4;	PARA 4 BITS
		//y = temp & 0x
		LCD_CMD(temp);
	}
	LCD_CMD(temp);
}