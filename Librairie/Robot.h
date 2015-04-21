/********************************************************************
Fichier: Robot.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour le robot
********************************************************************/

#ifndef ROBOT_H
#define ROBOT_H

#include <avr/io.h>
#include "Lcd.h"
#include "Minuterie.h"
#include "Son.h"
#include "Sonar.h"
#include "TraceurDeLigne.h"




class Robot
{
public:
	/* Méthode servant à initialiser les ports et les registres servant aux interruptions*/
	void initialiser();

	/* Méthode servant à gérer la tâche un, c'est-à-dire, ce que le robot doit faire rendu à un bout de ligne ou lorsqu'une des photo-résistances est illuminées*/
	void tacheUn();
	
	/* Méthode servant à gérer la tâche deux, c'est-à-dire, toutes la "chorégraphie" du robot*/
	void tacheDeux();
	
	/* Méthode servant à gérer la tâche trois, c'est-à-dire, la gestion du sonar, du son pour chaque capteur du traceur de ligne et le temps de l'épreuve*/
	void tacheTrois();

	/* Méthode contenant le menu du LCD et faisant le lien entre les trois tâches*/
	void epreuveFinale();

	

private:
	Lcd lcd_;
	Moteur moteur_;
	Son son_;
	TraceurDeLigne traceur_;
	Del del_;
	Sonar sonar_;
	Minuterie minuterie_;
};

#endif