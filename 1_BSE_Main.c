#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include "LIB_BSE_Timers.h"
#include "LIB_BSE_Config_Globale.h"
#include "LIB_BSE_GPIO.h"
#include "LIB_BSE_INT_Ext.h"
#include "LIB_BSE_UART.h"
#include "LIB_BSE_ADC.h"


void main()
{
	char* s = "Salut";
	Init_Device(); // Regroupe toutes les fonctions de configuration
	/*
	send_String(s);// Envoie la chaine de caratère Via l'UART0.
	Getchar(); 		 // Recupère le caractère de l'UART0.
	*/
	while(1){
		ACQ_ADC();
		
	}  
	
}
