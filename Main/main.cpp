/********************************************************************
Fichier: main.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Fichier qui contient l'exécution des trois tâches pour l'épreuve finale.
********************************************************************/

#include "Robot.h"

int main(void) 
{	
	Robot robot;
	robot.initialiser();

	robot.epreuveFinale();

	return 0;
}

