/********************************************************************
Fichier: TraceurDeLigne.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation des méthodes pour suivre une ligne noire
********************************************************************/
#include "TraceurDeLigne.h"

uint8_t* TraceurDeLigne::getPosition()
{
	uint8_t tmp[5];
	for(uint8_t i = 0; i < 5; i++){
		tmp[i] = PINA & 1<<(i+2);
	}
	return tmp;
}

void TraceurDeLigne::balayage(){
	moteur_.ajustementPWM(0, PWM_M_D);
	minuterie_.grandDelai(150);
	moteur_.ajustementPWM(PWM_M_G, 0);
	minuterie_.grandDelai(150);
}

void TraceurDeLigne::attendreLigne(){
	uint8_t* position = getPosition();
	while (position[0]||position[1]||position[2]||position[3]||position[4]){        //Vire jusqu'à ce qu'il sorte de la ligne actuelle
        position = getPosition();
    }
    while(!(position[0]||position[1]||position[2]||position[3]||position[4])){          //Au bout de la ligne, il vire à gauche  jusqu'à ce qu'il ne sente plus rien aux extrémités
        position = getPosition();
    }
}

bool TraceurDeLigne::ajustementPosition(uint8_t* position, int8_t& correctionMoteurGauche, int8_t& correctionMoteurDroit){

	bool ligneTrouvee = true;
//##################################################################################
	if(position[2] ){
		if (position[3]) //est trop à droite
		{
			correctionMoteurDroit += -15;
		}
		else if (position[1]) //est trop a`gauche
		{
			correctionMoteurGauche += -12;
		}
		else {
			if(correctionMoteurGauche + 30 < 0){
				correctionMoteurGauche += 30;
			}
			else{
				correctionMoteurGauche = 0;
			}

			if(correctionMoteurDroit + 30 < 0){
				correctionMoteurDroit += 30;
			}
			else {
				correctionMoteurDroit = 0;	
			}
		}
		
	}
//##################################################################################
	//si le robot va trop à droite
	else if(position [3]|| position[4])
	{ 
			//positio0n 3
			correctionMoteurDroit = -PWM_M_D;	//vérifier que c'est bien ajustementPWM (gauche, droite)
	}
//##################################################################################
	//si le robot va trop à gauche
	else if(position[0] || position [1])
	{ 
			//positio0n 1
			correctionMoteurGauche = -PWM_M_G;		//vérifier que c'est bien ajustementPWM (gauche, droite)
	}
	else {
		ligneTrouvee = false;
	}

	return ligneTrouvee;

}

void TraceurDeLigne::suivreLigne()
{
	uint8_t* position;
	int8_t correctionMoteurGauche = 0,correctionMoteurDroit = 0;
	moteur_.changerDirection(true,true);
	bool allume = true;

	while(allume){
		moteur_.ajustementPWM(PWM_M_G+correctionMoteurGauche,PWM_M_D+correctionMoteurDroit);

		bool ligneTrouvee = ajustementPosition(getPosition(),correctionMoteurGauche,correctionMoteurDroit);
		
		if(!ligneTrouvee){

			balayage();

			position = getPosition();
			if (!(position[0]||position[1]||position[2]||position[3]||position[4])){
				allume = false;
			}
		
		}
	}

}
int8_t* TraceurDeLigne::suivreLignePointille(){
	uint8_t* position;
	int8_t correction[2] = {0,0};
	moteur_.changerDirection(true,true);
	bool allume = true;

	while(allume){
		moteur_.ajustementPWM(PWM_M_G+correction[0],PWM_M_D+correction[1]);

		bool ligneTrouvee = ajustementPosition(getPosition(),correction[0],correction[1]);
		
		if(!ligneTrouvee){
			allume = false;		
		}
	}

	return correction;

}



void TraceurDeLigne::suivreLigne(uint8_t distance)
{
	int8_t correctionMoteurGauche = 0,correctionMoteurDroit = 0;
	moteur_.changerDirection(true,true);
	uint8_t duree = distance/VITESSE_MOTEUR;
	suivreLigneTemps(duree);
}

void TraceurDeLigne::suivreLigneTemps(uint16_t miliseconde)
{
	int8_t correctionMoteurGauche = 0,correctionMoteurDroit = 0;
	moteur_.changerDirection(true,true);
	minuterie_.partirMinuterie(miliseconde*7813);
	del_.rouge();
	while (!minuterie_.getMinuterie()){			
		moteur_.ajustementPWM(PWM_M_G+correctionMoteurGauche,PWM_M_D+correctionMoteurDroit);

		bool ligneTrouvee = ajustementPosition(getPosition(),correctionMoteurGauche,correctionMoteurDroit);

		if(!ligneTrouvee){
			correctionMoteurDroit = 0;
			correctionMoteurGauche = 0;
		}
	}
	moteur_.ajustementPWM(0, 0);
	del_.eteinte();
}

uint8_t TraceurDeLigne::suivreLigneEpreuve1()
{
	can convertisseur;

	uint16_t temporaire;

	uint8_t luminositeDroite, luminositeGauche;

	uint8_t retour;

	uint8_t* position = getPosition();

	int8_t correctionMoteurGauche = 0,correctionMoteurDroit = 0;

	moteur_.changerDirection(true,true);

	bool allume = true;

	while(allume){
		position = getPosition();

		temporaire = convertisseur.lecture(0);	//lecture et conversion en 8 bits
		luminositeGauche = temporaire >>2;

		temporaire = convertisseur.lecture(1);	//lecture et conversion en 8 bits
		luminositeDroite = temporaire >>2;

		moteur_.ajustementPWM(PWM_M_G+correctionMoteurGauche,PWM_M_D+correctionMoteurDroit);


//##################################################################################
		if (luminositeDroite > SEUIL_LUMIERE)
		{
			minuterie_.grandDelai(50);
			temporaire = convertisseur.lecture(1);	//lecture et conversion en 8 bits
			luminositeDroite = temporaire >>2;
			if (luminositeDroite > SEUIL_LUMIERE)
			{
				allume = false; //On arrête la boucle
				retour = LUMIERE_DROITE;
			}
		}

//##################################################################################
		else if (luminositeGauche > SEUIL_LUMIERE){

			minuterie_.grandDelai(50);
			temporaire = convertisseur.lecture(0);	//lecture et conversion en 8 bits
			luminositeGauche = temporaire >>2;
			if (luminositeGauche > SEUIL_LUMIERE)
			{
				allume = false; //On arrête la boucle
				retour = LUMIERE_GAUCHE;
			}

		}

//##################################################################################
		else {
			bool ligneTrouvee = ajustementPosition(getPosition(),correctionMoteurGauche,correctionMoteurDroit);
			if(!ligneTrouvee){

				balayage();

				position = getPosition();
				if (!(position[0]||position[1]||position[2]||position[3]||position[4])){
					allume = false;
					retour = FIN_LIGNE;
				}
			
			}
		}

	}
	return retour;
}

void TraceurDeLigne::suivreLigneEpreuve2()
{
	uint8_t* position = getPosition();
	int8_t correctionMoteurGauche = 0,correctionMoteurDroit = 0;
	moteur_.changerDirection(true, true);
	bool allume = true;

	while(allume){
		position = getPosition();

		moteur_.ajustementPWM(PWM_M_G+correctionMoteurGauche,PWM_M_D+correctionMoteurDroit);
/*************************************************************************************************************/
		if (position[0] && position[1] && position[2]){
			allume = false;
		}


/*************************************************************************************************************/
		else if ( position[2] && position[3] && position[4]){
			allume = false;
		}


/*************************************************************************************************************/
		else {
			bool ligneTrouvee = ajustementPosition(getPosition(),correctionMoteurGauche,correctionMoteurDroit);
			if(!ligneTrouvee){
				allume = false;
			}
		}
	}
}