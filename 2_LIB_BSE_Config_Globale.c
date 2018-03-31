#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"

#include "LIB_BSE_Timers.h"
#include "LIB_BSE_GPIO.h"
#include "LIB_BSE_UART.h"
#include "LIB_BSE_ADC.h"
#include "LIB_BSE_INT_Ext.h"
#include "LIB_PWM.h"

void Reset_Sources_init(void) // desactivation du watchdog
{
	WDTCN = 0xDE;
	WDTCN = 0xAD;
}

void oscillator_init(void) //Configure L'oscillateur
{ 
	int i=0;
	OSCXCN = 0x67; // Crystal oscillator mode
	for (i = 0; i < 3000; i++)  // Wait for 1ms
	while ((OSCXCN & 0x80) == 0x00);  // Crystal oscillator valid flag check
	OSCICN = 0x08;  // Swicth from oscillator
	
}
void CrossBar_init(void){
	XBR0 = 0x08;// Rien d'activé
	XBR1 = 0x00;// Rien d'activé
	XBR2 = 0x40;// Active le Crossbar
}
void Init_Device(void) //Appel d'une fonction unique de configuration
{ 
	EA =0;
	oscillator_init(); //Appel la fonction qui configure l'oscillateur à la fréquence 22.1184MHz
	Reset_Sources_init(); //Déactive le watchdog, le reset automatique
	CrossBar_init();
	Config_GPIO();  //Configure les ports et du crossbar
	Config_INT1();	//Configure l'interruption 1
	CFG_Clock_UART0(); // Configure la clock de UART0, qui permettra l'écriture 
	CFG_UART0();
	CFG_ADC0();
	PCA0_Init ();
	Config_Timer2();
	EA =1;
}