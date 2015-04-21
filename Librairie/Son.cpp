#include "Son.h"

/* Constructeur de son qui initialise le registre pour faire du son */
Son::Son()
{
	TCCR0A |= (1<<WGM01)|(1<< COM0A0);
}

/* Met le registre à zéro pour empêcher d'émettre un son */
void Son::arreter()
{
	TCCR0B = 0;
}


/* Permet de jouer un son
* @param int Prend en paramètre la fréquence de la note à jouer
*/
void Son::jouer(int frequence)
{
	TCCR0B |= (1<<CS02);
	OCR0A = 15625/frequence;
}

/* Permet de jouer un son selon la détection d'une ligne
* @param uint8_t* Prend en paramètre un tableau de uint8_t qui contient l'états des 5 capteurs
*/
void Son::jouer(int frequence, int temps)
{
	jouer(frequence);
	minuterie_.grandDelai(temps);
	arreter();
}

/* Permet de jouer un son selon la détection d'une ligne
* @param uint8_t* Prend en paramètre un tableau de uint8_t qui contient l'états des 5 capteurs
*/
void Son::capteurSon(uint8_t* capteurs)
{
	 if(capteurs[0])
            {
                jouer(262);
            }
            else if(capteurs[1])
            { 
                jouer(294);
            }
            else if(capteurs[2])
            {
                jouer(330);
            }
            else if(capteurs[3])
            {
                jouer(349);
            }
            else if(capteurs[4])
            {
                jouer(392);
            }
            else
            {
                arreter();
            }
}
