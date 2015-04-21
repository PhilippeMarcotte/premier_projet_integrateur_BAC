/********************************************************************
Fichier: TraceurDeLigne.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour suivre une ligne noire
********************************************************************/
#ifndef TRACEURDELIGNE_H
#define TRACEURDELIGNE_H

#include <avr/io.h>
#include "can.h"
#include <util/delay.h>
#include "Moteur.h"
#include "Minuterie.h"
#include "Del.h"

//États utilisé pour l'épreuve 1
enum resultat {FIN_LIGNE,LUMIERE_DROITE,LUMIERE_GAUCHE};

//Constante représentant le seuil auquel le robot va tourner vers la lumière
int const SEUIL_LUMIERE = 235;

class TraceurDeLigne
{
public:
	/* Fonction servant à vérifier quel capteur du traceur de ligne sont allumés
	 * @return uint8_t* Adresse d'un tableau représentant les 5 capteurs
	 */
	uint8_t* getPosition();

	/* Méthode servant permettant au robot de suivre une ligne noire et s'arrêter lorsqu'il ne la voit plus*/
	void suivreLigne();

	/* Méthode permettant au robot de suivre une ligne noire, continuer tout droit lorsqu'il ne voit et s'arrêter lorsque la distance passé en paramètre est parcourue complètement
	 * @param uint8_t Représente la distance à parcourir
	 */
	void suivreLigne(uint8_t distance);

	/* Méthode permettant au robot de suivre une ligne noire, continuer tout droit lorsqu'il ne voit et s'arrêter lorsque la durée s'est écoulée
	 * @param uint8_t Représente la temps durant lequel le robotdoit avancer en suivant une ligne
	 */
	void suivreLigneTemps(uint16_t miliseconde);

	/* Fonction utilisée pour parcourir la ligne pointillé de l'épreuve 2
	 * @return int8_t* Adresse du tableau contenant les corrections appliqués sur les moteurs
	 */
	int8_t* suivreLignePointille();

	/* Fonction pour gérer la lumière en plus de suivre les lignes pour l'épreuve 1
	 * @return uint8_t État représentant s'il est à la fin du ligne ou s'il a détecté de la lumière à gauche ou à droite
	 */
	uint8_t suivreLigneEpreuve1();

	/* Méthode servant à suivre la ligne noire du parcours de l'épreuve 2*/
	void suivreLigneEpreuve2();

	/* Méthode servant à faire un déplacement dans le «vide» jusqu'à ce qu'il trouve une ligne*/
	void attendreLigne();
	
private:
	/* Méthode servant à démarrer un compteur utiliser pour les suivreLigne basé sur une distance ou le temps (suivreLigne(uint16_t distance) et suivreLigneTemps(uint16_t miliseconde))
	 * @param uint16_t Integer représentant jusqu'à combien le compteur doit incrémenter
	 */
	void partirMinuterie ( uint16_t duree );

	/* Fonction servant à corriger la force des moteurs pour que le robot reste le plus centré possible sur la ligne noire
	 * @param uint8_t* Tableau représentant l'état des capteurs du traceur de ligne
	 * @param int8_t& Référence à la variable servant à corriger le moteur gauche
	 * @param int8_t* Référence à la variable servant à corriger le moteur droit
	 * @return bool Vrai si à la fin de correction le robot est toujours sur la ligne et faux dans le cas contraire
	 */
	bool ajustementPosition(uint8_t* position, int8_t& correctionMoteurGauche, int8_t& correctionMoteurDroit);

	/* Méthode permettant au robot de faire un balayage de gauche à droite lorsqu'il ne trouve plus de ligne pour s'assurer qu'il ne s'est pas juste perdu*/
	void balayage();

	Moteur moteur_;
	Del del_;
	Minuterie minuterie_;
};

#endif