
   
#include <C8051F020.h>                 // SFR declarations   
#include "LIB_PWM.h"


void PCA0_Init (void)   
{   
	 PCA0MD = 0x00;   
   PCA0CN = 0x00;                      // compteur arrete; reset flag   
   PCA0MD = 0x00;                      // Utiliser SYSCLK/12 comme base de temps   
   
   PCA0CPM0 =0x83;                     // Module 0,   
                                       // active Module 0 Interruption flag,   
		
	 Commande_Servo_Horiz(0);					 // Initialise le Servomoteur à la "position" indiquée.
   
   PCA0L = 0x00;                       // met le compteur PCA à 0x0000   
   PCA0H = 0x00;   

   EIE1 |= 0x10;                       // Active les interruptions du PCA 
   
   CR = 1;                             // demarre PCA   
   
}   
void Commande_Servo_Horiz(int Angle){
	float ms;
	float pourcentage;
	int	Nbrepoints;
	unsigned int Consigne;

	ms = (Angle/90.0+0.5);// On traite les cas de manière séparée
	if(Angle>90){													
		ms= (Angle/180.0+1.5);
	}
	
	pourcentage= ms/36.0;									//Divisé par la période de 36ms
	Nbrepoints = 65535.0*pourcentage;
	Consigne = 65535 - (int)(Nbrepoints);

	PCA0CPL0 = Consigne;  //On récupère le premier octect de de consigne dans le registre PCA0CPL0.
	PCA0CPH0 = Consigne >> 8; //On récupère second octect de consigne dans le registre PCA0CPH0.

}
