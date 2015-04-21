/********************************************************************
Fichier: Son.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour le Piézoélectrique
********************************************************************/

#ifndef SON_H
#define SON_H

#include <util/delay.h>
#include <avr/io.h>
#include "Minuterie.h"

class Son
{
public:
	/* Constructeur de son qui initialise le registre pour faire du son */
	Son();
	/* Permet d'arrêter le son produit par le piézoélectrique */
	void arreter();
	/* Permet de jouer un son
	 * @param int Prend en paramètre la fréquence de la note à jouer
	 */
	void jouer(int frequence);
	/* Permet de jouer un son durant une période déterminée
	 * @param int, int Prend en paramètre la fréquence de la note à jouer et la durée de la note
	 */
	void jouer(int frequence, int temps);
	/* Permet de jouer un son selon la détection d'une ligne
	 * @param uint8_t* Prend en paramètre un tableau de uint8_t qui contient l'états des 5 capteurs
	 */
	void capteurSon(uint8_t* capteurs);

private:
	/* Composition pour avoir accès au grandDelai et Minuterie */
	Minuterie minuterie_;
};

#endif