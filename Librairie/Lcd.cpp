/********************************************************************
Fichier: Lcd.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation pour les méthode pour le Lcd
********************************************************************/

#include "Lcd.h"

volatile uint8_t effacer = 0;
volatile uint8_t debut = 0;
/* Interruption sur la broche PD3. La PIND 0x04 doit être en entrée */
ISR ( INT0_vect )
{ 	
	_delay_ms(50);
	if(PIND & 0x04)
	{
		effacer = 1;
		debut = 1;
	}
} 

volatile uint8_t confirmation = 0;
/* Interruption sur la broche PD4. La PIND 0x08 doit être en entrée */
ISR ( INT1_vect )
{ 	
	_delay_ms(50);
	if(PIND & 0x08)
	{
		confirmation = 1;
	}
} 

void Lcd::affichage(const char* msg)
{
	LCM disp(&DEMO_DDR, &DEMO_PORT);

	disp.clear();
	w();
	disp.write(msg);
}

uint8_t Lcd::getTache()
{	
	LCM disp(&DEMO_DDR, &DEMO_PORT);

	typedef enum {UN, DEUX, TROIS} Partie;
	Partie partie = UN;
	uint8_t partieEnCours = 1;

	disp.write(" Please press   to select task", 1); 
	w();

	do
	{

	}while(debut == 0);
	disp.clear();
	w();

	disp.write("Choix:", 5);
	disp.write("Partie 1", 20);
	do
	{	
		if(effacer == 1)
		{
			// Suppression des 1 caractère précédents
			disp -= 1;
			w();
			effacer = 0;

			switch(partie) 
			{ 	
				case UN:
				// Écriture d'un simple caractère au dernier caractère
				disp.put('1');
				w();
				partie = DEUX;
				partieEnCours = 1;
				break;

				case DEUX:
				// Écriture d'un simple caractère au dernier caractère
				disp.put('2');
				w();
				partie = TROIS;
				partieEnCours = 2;
				break;

				case TROIS:
				// Écriture d'un simple caractère au dernier caractère
				disp.put('3');
				w();
				partie = UN;
				partieEnCours = 3;
				break;

				default:
				disp.write("Erreur de code  Veuillez reset", 1);
				partie = UN;
				break;
			}
		}
		
		
	}while(confirmation==0);

	return partieEnCours;
}

/* Permet de faire un delai */
void inline Lcd::w(void) 
{
	cp_wait_ms(1);
}