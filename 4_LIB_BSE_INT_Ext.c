#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>

void Config_INT1(void)
{	
	//IE1 est un Flag de dection. 
	IT1=1; //Active INT1 sur front montant
	EX1 = 1; // Active Interrupt 1
}

void ISR_INT1(void) interrupt 1 //Signal d'interruption sur le port Port3.4
{
	Tst4=1;
	_nop_();_nop_();_nop_();_nop_();
	Tst4=0;
}