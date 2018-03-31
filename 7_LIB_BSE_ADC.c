
#include <c8051f020.h>
#include "LIB_BSE_Config_Globale.h"
#include "Declarations_GPIO_BSE.h"
#include "LIB_BSE_ADC.h"


float VRef;
float ADCTension = 0;
float Distance_obstacle_n = 0;

void CFG_VREF(void)
{
	/*
	Configuration de VRef avec VRef interne.
	VREF = 2.4V.
	D'après la datasheet les bits 0 et 1 DOIVENT être mis à 1.
	*/ 
	float VRef = 2.4;
	REF0CN = 0x03;
}
	
void CFG_ADC0(void)
{	
	
	CFG_VREF();
	//Analog/Digital Converter
	ADC0CN = 0xE1; //1110 0001 
	ADC0CF = 0xF8; //1111 1000
	AMX0SL = 0x04; //0000 0100
	AMX0CF = 0x00; //0000 0000
	ADC0H = 0x00; //0000 0000
	ADC0L = 0xAC; //1010 1100
	
	AD0EN = 1;
	AD0TM = 1;
	AD0INT = 1;
	
	//Programmable Window Dectector
	//ADC0GT = 0xFFFF;
	//ADC0LT = 0x0000;
	
	
	//AD0VRS = 0;
	//TEMPE = 0;
	//BIASE = 1;
	//REFBE = 1;
	
}
float ACQ_ADC(void)
{
	AD0BUSY=1;// déclenchement de la conversion
	while(AD0INT==0);
	AD0INT=0;// déclenchement de la conversion
	
	//conversion Hexa vers Tension. La tension de référence est de 3.3V et on utilise 12bits
	//Donc d'après la datasheet : 
	// Code = Vin* Gain/Vref * 2^12
	// Gain de 1
	
	ADCTension = ADC0H*VRef/(1*254);
	//Distance_obstacle_n = -3e-6*ADCval^3+0.003*ADCval^2-0.969*ADCval+3.9839; 
	
	Calcul_Distance();
	

	return Distance_obstacle_n;
}

void Calcul_Distance(void)
{
	if (ADCTension >=1,143 && ADCTension <=2.6){
		Distance_obstacle_n = (ADCTension-3.1945) / (-0.0428);
	}
	else if(ADCTension <1.143){
		Distance_obstacle_n = (ADCTension-1.5369) /(-0.0095);
	}
	else{
		Distance_obstacle_n = 0; 
	}
}

