/********************************************************************
Fichier: Del.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour la Del
********************************************************************/

#ifndef DEL_H
#define DEL_H

#include <avr/io.h>

class Del
{
public:
	/* Allume la Del de la couleur rouge en changeant uniquement la pin 2 */
	void rouge();
	/* Allume la Del de la couleur vert en changeant uniquement la pin 1 */
	void vert();
	/* Ferme la Del en changeant uniquement la pin 1 et la pin 2*/
	void eteinte();

};

#endif