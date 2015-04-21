/********************************************************************
Fichier: Minuterie.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation des méthodes pour la minuterie sur le robot et delai
********************************************************************/

#include "Minuterie.h"


volatile uint8_t minuterieExpiree = 0;
ISR ( TIMER1_COMPA_vect ) 
{
minuterieExpiree=1;
}

void Minuterie::setEtatMinuterie(uint8_t etat){
	minuterieExpiree = etat;
}

/* Dure = 8 000 000/1024 = 1 secondes */
void Minuterie::partirMinuterie ( uint16_t duree ) 
{
// mode CTC du timer 1 avec horloge divisee par 1024
// interruption apres la duree specifiee
TCNT1 = 0;
OCR1A = duree;
TCCR1A = 0;
TCCR1B = 5;
TIMSK1 = 2;
}

/* Permet d'avoir la valeur de la minuterieExpiree selon un bool et remet la valeur 
de minuterieExpiree à 0 */
bool Minuterie::getMinuterie()
{
	bool expiree = false;
	if (minuterieExpiree == 1)
	{
		expiree = true;
		minuterieExpiree = 0;
	}
	return expiree;
}

/* Cette fonctionne effectue une boucle de N fois 1ms. Permet d'être plus précis dans 
nos delay et simplifie le code puisqu'on peut insérer des variables.*/
void Minuterie::grandDelai(uint16_t milisecondes)
{
	for(uint16_t j=0;j<milisecondes;j++)
	{
		_delay_ms(1);
	}
}