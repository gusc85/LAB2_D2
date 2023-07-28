// ------------------------------------------------------------------------------
// DATOS Y ENCABEZADO
//-------------------------------------------------------------------------------
    
// Archivo:                 lab2.h
// Dispositivo:             PIC16F887
// Autor:                   GUSTABO CÓRDOVA 
// Programa:                LAB2_D2
// Creado:                  28 JUL, 2023 
// Última modificación:     28 JUL, 2023

#ifndef USART_HEADER_H
#define	USART_HEADER_H

#define RS_PIN   RE0 // Cambia RB0 al pin que estás utilizando para RS
#define EN_PIN    RE1 // Cambia RB1 al pin que estás utilizando para E

#ifndef D0
#define	D0 RD0
#endif


#ifndef D1
#define	D1 RD1
#endif

#ifndef D2
#define	D2 RD2
#endif

#ifndef D3
#define	D3 RD3
#endif

#ifndef D4
#define	D4 RD4
#endif

#ifndef D5
#define	D5 RD5
#endif

#ifndef D6
#define	D6 RD6
#endif

#ifndef D7
#define	D7 RD7
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

extern int Low_ADC;
extern int High_ADC;
extern int Resultado_ADC;

void InterruptADC(char* DisplayLow_ADC, char* DisplayHigh_ADC);
void delayADC(char n);
void Read_ADC(char channel);
void EnvioSerial(char value);
void InterruptReciboUSART (char *value2);
void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);


#endif