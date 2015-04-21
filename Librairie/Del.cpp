/********************************************************************
Fichier: Del.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implementation des méthodes pour la Del
********************************************************************/

#include "Del.h"

void Del::rouge()
{
	PORTB |= 0b00000010;
}

void Del::vert()
{
	PORTB |= 0b00000001;
}

void Del::eteinte()
{
	PORTB &= 0b11111100;
}	