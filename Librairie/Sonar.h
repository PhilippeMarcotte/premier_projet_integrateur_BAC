/********************************************************************
Fichier: Sonar.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour le sonar
********************************************************************/

#ifndef SONAR_H
#define SONAR_H

#include <util/delay.h>
#include <avr/io.h>

class Sonar
{
public:
	/* Permet d'avoir la distance d'un objet par rapport un sonar d'au plus 24pouces.
	 * @return unsigned int Retourne la distance de l'objet
	 */
	unsigned int getDistance(void);

};

#endif