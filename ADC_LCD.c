// ------------------------------------------------------------------------------
// DATOS Y ENCABEZADO
//-------------------------------------------------------------------------------
    
// Archivo:                 librerias2.c
// Dispositivo:             PIC16F887
// Autor:                   GUSTABO CÓRDOVA 
// Programa:                LAB2_D2
// Creado:                  28 JUL, 2023 
// Última modificación:     28 JUL, 2023

// ------------------------------------------------------------------------------
// CONFIGURACIÓN DEL PIC
//-------------------------------------------------------------------------------
#include <xc.h>
#include <stdint.h>
#include "ADC_LCD.h"
#define _XTAL_FREQ 8000000

int Low_ADC;
int High_ADC;
int Resultado_ADC;
char value;
char value2;

void InterruptADC(char* LowNibble_ADC, char* HighNibble_ADC){
    if (ADIF == 1){
        ADIF = 0;
        
        High_ADC = ADRESH;
        High_ADC = High_ADC << 6; //Se mueven los 2 del ADRESH 6 espacios en la parte de arriba
        
        Low_ADC = ADRESL;
        Low_ADC = (Low_ADC & 0b11111100) >> 2; // Se borran los 2 primeros bits de ADRESL y los movemos
        
        Resultado_ADC = High_ADC + Low_ADC; // Se suman ambos para obtener 8 espacios de bits significativos
        *LowNibble_ADC = Resultado_ADC & 0b00001111;
        *HighNibble_ADC = (Resultado_ADC & 0b11110000)>>4;
    }
}

void Read_ADC(char channel){
    ADCON0bits.CHS = channel;
    delayADC(10); //delay al hacer el cambio de canal
    GO = 1; //inicio de conversión ADC
    while(GO==1); //final de conversión
}
// ------------------------------------------------------------------------------
// DELAY LIBRERIA ADC
//-------------------------------------------------------------------------------
void delayADC(char n){         
    for (int i = 0; i < n; i++){
        for(int j = 0; j < 255; j++){    
        }
    }
}

void EnvioSerial(char value){
    TXREG = value; //carga el registro
    while (TXSTAbits.TRMT == 0){  
    }
}

void InterruptReciboUSART(char *value2){
    if(RCIF == 1){
        *value2 = RCREG; //lee el registro
        RCIF = 0; //limpia la bandera de recibo
    }
}

void Lcd_Port(char a){
    if (a & 1)
        D0 = 1;
    else 
        D0 = 0;
    if (a & 2)
        D1 = 1;
    else 
        D1 = 0;
    if (a & 4)
        D2 = 1;
    else 
        D2 = 0;
    if (a & 8)
        D3 = 1;
    else 
        D3 = 0;
    if (a & 16)
        D4 = 1;
    else 
        D4 = 0;
    if (a & 32)
        D5 = 1;
    else 
        D5 = 0;
    if (a & 64)
        D6 = 1;
    else 
        D6 = 0;
    if (a & 128)
        D7 = 1;
    else 
        D7 = 0;
}

void Lcd_Cmd(char a){
    RS_PIN = 0; // puerto lo va a identificar el dato como comando
    Lcd_Port(a);
    EN_PIN = 1;
    __delay_ms(5);
    EN_PIN = 0;
}

void Lcd_Clear(void){
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b){
    char c;
    if(a == 1){
        c = 0x80 + b - 1;
        Lcd_Cmd(c);
    }
    else if (a == 2){
        c = 0xC0 + b - 1;
        Lcd_Cmd(c);
    }
}
// ------------------------------------------------------------------------------
// SECUENCIA DE ENCENDIDO PARA LCD DE 8 BITS
//-------------------------------------------------------------------------------

void Lcd_Init(void){
    Lcd_Port(0x00); 
    __delay_ms(15);
    Lcd_Cmd(0x030);
    __delay_ms(4);
    Lcd_Cmd(0x030);
    __delay_ms(100);
    Lcd_Cmd(0x030);

    Lcd_Cmd(0x38);
    Lcd_Cmd(0x08); //se apaga el display
    Lcd_Cmd(0x01); // limpieza de displya
    __delay_ms(11);
    
    Lcd_Cmd(0x06);
    Lcd_Cmd(0x0C); //encendido de display
}
// ------------------------------------------------------------------------------
// VALORES NECESARIOS PARA LA ESCRITURA
//-------------------------------------------------------------------------------

void Lcd_Write_Char(char a){    // VALORES QUE DEFINIMOS DIRECTAMENTE
    RS_PIN = 1;
    Lcd_Port(a);
    EN_PIN = 1;
    __delay_ms(40);
    EN_PIN = 0;
}

void Lcd_Write_String(char *a){  // VALORES TIPO ASCCI
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void){
    Lcd_Cmd(0x1C);
}

void Lcd_Shift_left(void){
    Lcd_Cmd(0x18);
}