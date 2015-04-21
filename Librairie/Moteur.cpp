/********************************************************************
Fichier: Moteur.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation des méthodes pour les moteur
********************************************************************/

#include "Moteur.h"

Moteur::Moteur()
{
	TCCR2A = 0xA1;
	OCR2A = 0;
	OCR2B = 0;
	TCCR2B = 2;
	changerDirection(true,true);
}

void Moteur::ajustementPWM(uint8_t pwmMoteurGauche, uint8_t pwmMoteurDroit, bool directionMoteurGauche, bool directionMoteurDroit)
{
	OCR2A = pwmMoteurDroit;
	OCR2B = pwmMoteurGauche;
	changerDirection(directionMoteurGauche, directionMoteurDroit);
}

void Moteur::ajustementPWM(uint8_t pwmMoteurGauche, uint8_t pwmMoteurDroit){
	OCR2A = pwmMoteurDroit;
	OCR2B = pwmMoteurGauche;
}

void Moteur::changerDirection(bool directionMoteurGauche, bool directionMoteurDroit)
{
	if (directionMoteurGauche && directionMoteurDroit){
		PORTD = PORTD | 0b00110000;
	} else if (!directionMoteurGauche && directionMoteurDroit){
		PORTD |= 0b00100000;
		PORTD &= 0b11101111;
	} else if (directionMoteurGauche && !directionMoteurDroit){
		PORTD |= 0b00010000;
		PORTD &= 0b11011111;
	} else if (!directionMoteurGauche && !directionMoteurDroit){
		PORTD = PORTD & 0b11001111;
	}
}

void Moteur::booster()
{
	changerDirection(true,true);
	ajustementPWM(255, 255);
	_delay_ms(60);
}

void Moteur::tournerDroite()
{
	ajustementPWM(160,151);
    changerDirection(true,false);
}

void Moteur::tournerGauche()
{
	ajustementPWM(160,151);
	changerDirection(false,true);
}

void Moteur::rotationDroite()
{
	changerDirection(true,false);
}

void Moteur::rotationGauche()
{
	changerDirection(false,true);
}