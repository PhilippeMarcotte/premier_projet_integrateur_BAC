/********************************************************************
Fichier: Méthode.h
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Méthode pour les moteurs
********************************************************************/

#ifndef MOTEUR_H
#define MOTEUR_H

#include <avr/io.h>
#include <util/delay.h>

/* Constante pour que le robot puisse aller en ligne droite selon les moteurs */
const uint8_t PWM_M_G = 100;
const uint8_t PWM_M_D = 92;
const uint8_t VITESSE_MOTEUR = 6;

class Moteur
{
public:
	Moteur();
	/* Cette fonction est une variation de la fonction précédente. Plutôt d’émettre deux signaux 
	 * PWM égaux, celle-ci prend deux arguments et génère un signal PWM pour chaque argument 
	 * indépendamment de la valeur de l’autre argument. Ainsi, on peut faire fonctionner 
	 * les deux moteurs du robot à des puissances différentes, permettant, entre autres, 
	 * de faire tourner le robot sur son parcours.
	 * @param uint8_t, uint8_t, bool, bool Prend en paramètre la force des deux moteurs,
	 * ainsi que la valeur de la pin de direction.
	 */
	void ajustementPWM (uint8_t pwmMoteurGauche, uint8_t pwmMoteurDroit, bool directionMoteurGauche, bool directionMoteurDroit);
	/* Fonction émettant deux signaux PWM égaux. Partant à une valeur de pwm de 0,
	 * l’intensité de puissance dans les moteurs est alors nulle et s’approche de la 
	 * puissance maximale au fur et à mesure que la valeur de la variable pwm s’approche de 255.
	 * @param uint8_t, uint8_t Prend en paramètre la force des deux moteurs
	 */
	void ajustementPWM (uint8_t pwmMoteurGauche, uint8_t pwmMoteurDroit);
	/* Cette fonction permet de pallier à la difficulté que les moteurs ont de briser 
	 * leur immobilité. Elle fait avancer les deux moteurs à vitesse maximale pour une courte 
	 * durée afin de les mettre en mouvement. Toutefois, puisque la fonction ne ramène pas les 
	 * vitesses des signaux PWM à leurs valeurs initiale, il est recommandé d’appeler ajustementPWM 
	 * immédiatement après avoir appelé cette fonction si on ne désire pas que le robot avance à pleine puissance.
	 */
	void booster();
	/* Permet d'ajuster la pin de direction pour chaque roue du moteur
	 * @param bool, bool Prend en paramètre la valeur de la pin de direction pour chaque roue
	 */
	void changerDirection(bool directionMoteurGauche, bool directionMoteurDroit);
	/* Fait en sorte que le robot tourne de 90 degree vers la droite
	 */
	void tournerDroite();
	/* Fait en sorte que le robot tourne de 90 degree vers la gauche
	 */
	void tournerGauche();
	/* Ajuste tous les ports de telle sorte que le robot soit en mesure d'allé vers la droite
	 */
	void rotationDroite();
	/* Ajuste tous les ports de telle sorte que le robot soit en mesure d'allé vers la droite
	 */
	void rotationGauche();

};

#endif