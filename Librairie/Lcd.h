/********************************************************************
Fichier: Lcd.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode public et privée pour le Lcd
********************************************************************/

#ifndef LCD_H
#define LCD_H

// Data Direction Register' AVR occupé par l'aff.
#define DEMO_DDR	DDRC 
// Port AVR occupé par l'afficheur
#define DEMO_PORT	PORTC 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "customprocs.h"
#include "lcm_so1602dtr_m.h"
#include "lcm_so1602dtr_m_fw.h"
#include <util/delay.h>

class Lcd
{
public:
	/* Permet d'afficher un message sur l'écran du Lcd en effaçant le message précédant 
	 * @param const char* Prend en paramètre un tableau de char représentant le message à afficher
	 */
	void affichage(const char* msg);
	/* Permet à l'utilisateur de choisir entre trois tâches en lui indiquant les instructions sur un Lcd 
	 * @return uint8_t Retourne la tâche choisi par l'utilisateur
	 */
	uint8_t getTache();

private:
	/* Permet de faire un delai au Lcd
	 */
	void inline w(void);

};

#endif