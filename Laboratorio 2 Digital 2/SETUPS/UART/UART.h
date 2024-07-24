/*
 * UART.h
 *
 * Created: 19/05/2024 08:26:28 p. m.
 *  Author: josei
 */ 


#ifndef UART_H_
#define UART_H_

void initUART9600(void);

void writeUART(char Caracter);

void writeTextUART(char* Texto);

#endif /* UART_H_ */