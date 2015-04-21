/********************************************************************
Fichier: Sonar.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation pour les méthodes du sonar
********************************************************************/

#include "Sonar.h"

/* Permet d'avoir la distance d'un objet par rapport un sonar d'au plus 24pouces.
* @return unsigned int Retourne la distance de l'objet
*/
unsigned int Sonar::getDistance(void)
{
    int range=0;
    int distance = 0;
    PORTB |= 0x20;
    _delay_us(10);
    PORTB &= (0xDF);
    
    // Wait for echo pin to go high,  this indicates the start of the incoming pulse
    while(!(PINB & 0x10));        
    
    while((PINB&0x10))
    {
        range++;
        _delay_us(12);
    };
    distance = (500-range)*0.5;
    return(distance);
    //DISTANCE EN POUCE * 10!
}
