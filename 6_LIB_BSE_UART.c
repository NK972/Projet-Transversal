#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"

#include "LIB_BSE_UART.h"
#include "LIB_BSE_Config_Globale.h"

#include <string.h>
#include <intrins.h>
void CFG_Clock_UART0(void)
{
	CKCON |=0x10; //Timer 1 use SYSCLK divided by 12
	//CKCON = 0x10;
	
	TMOD |=0x20;  //Mode du timer 1 avec une ecriture de 8bit avec auto rechargement;
	TMOD &=0x2F;
	//TMOD = 0x20;
	
	TCON |=0x40; //Enable du timer 1
	TCON &=0x7F;
	//TCON = 
}
void CFG_UART0(void)
{
	SCON0 |=0x70; //mise à 1 du bit SM10
	SCON0 &=0x7C; //mise à 0 du bit SM00
	
	RCLK0=0;
	TCLK0=0;
	
	PCON |= 0x80; //mise à 1 du bit SMOD0
	PCON &= 0xBF; //mise à 0 du bit SSTAT0
	
	TL1=0x00; 
	TH1=0xF4; //le Baudrate vaut 115200Hz 
	TI0=1;
	
	
	
}

char Putchar(char c, char csg_tempo)
{
	while( csg_tempo !=0)
	{
		if (TI0!=0)
		{
			SBUF0 = c;
			TI0=0;		
			return c;
		}
		else
		{
			_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();
			csg_tempo--;
		}
	}
	return 1;
}


char Getchar(void){
	if (RI0!=0)
	{
		char lecture=SBUF0;
		RI0=0;
		return lecture;
	}
	else
	{
		return 0;
	}
}	

char send_String(char* char_ptr)
{
	int i;
	char nombre_de_caractere=0;
	for(i=0;i<strlen(char_ptr);i++)
	{
		Putchar(char_ptr[i],200);
		nombre_de_caractere++;
	}
	return nombre_de_caractere;
}
