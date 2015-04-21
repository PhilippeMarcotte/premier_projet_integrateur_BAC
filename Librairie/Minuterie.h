/********************************************************************
Fichier: Minuterie.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour une minuterie et méthode de délai
********************************************************************/

#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <util/delay.h>
#include <avr/interrupt.h>

class Minuterie
{
public:
	/* Permet de partir une minuterie sur le robot
	 * @param uint16_t  Prend en paramètre la durée de la minuterie
	 */
	void partirMinuterie ( uint16_t duree );
	/* Permet de savoir si la minuterie est expiree ou non
	 * @return bool Retourne un bool true si la minuterie est expiree. Sinon false
	 */
	bool getMinuterie();
	/* Cette fonctionne effectue une boucle de N fois 1ms. Permet d'être plus précis dans 
	 * nos delay et simplifie le code puisqu'on peut insérer des variables 
	 * @param uint16_t Prend en paramètre le delai en ms
	 */
	void grandDelai(uint16_t milisecondes);

	void setEtatMinuterie(uint8_t etat);
};

#endif