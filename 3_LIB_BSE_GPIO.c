
#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"


void Config_GPIO(){
	XBR0 = 0x08; //Active la CEX0 (PWM du servo moteur Horizontale)
	XBR1 = 0x00;
	XBR2 = 0x40; //Active le crossbar
}