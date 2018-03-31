#include <c8051F020.h>
#include "LIB_BSE_Timers.h"
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>

void Config_Timer2(void){
	
	T2CON = 0x04; // Active le timer 2 en Interrupteur et l'autorelaod 
	CKCON &= ~0x20; //CKCON Permet de choisir l'Horloge à utiliser 
	
	RCAP2L =0xFF; // Valeur d'auto reload du timer
	RCAP2H =0x15;
	
	TL2=0xFF; //Valeur Initial du timer
	TH2=0x15;
	
	ET2 = 1; // Active les requete interruption du time2 par le flag TF2
	
	PT2 = 1; //Priorité de L'interruption déclenché par timer 2
}