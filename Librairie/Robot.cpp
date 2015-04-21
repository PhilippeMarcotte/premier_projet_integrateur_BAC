/********************************************************************
Fichier: Robot.cpp
Auteur: Frederic Gregoire, Philippe Marcotte, Gabriel Côté-Carrier, Thomas Forest
Description: Implémentation des méthodes pour le robot
********************************************************************/

#include "Robot.h"

void Robot::initialiser()
{
	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'etre interrompu alors que 
	// le microcontroleur n'est pas pret... 
	cli (); 
	// configurer et choisir les ports pour les entrees
	// et les sorties. DDRx... Initialisez bien vos variables
	DDRA = 0x80;
	DDRB = 0x2f;
	DDRD = 0xf0;
	// cette procédure ajuste le registre EIMSK 
	// de ATmega324PA pour permettre les interruptions externes 
	EIMSK |= _BV(INT0);
	EIMSK |= _BV(INT1);  
	// il faut sensibiliser les interruptions externes aux 
	// changements de niveau du bouton-poussoir 
	// en ajustant le registre EICRA 
	EICRA |= 3;

	// sei permet de recevoir a nouveau des interruptions. 
	sei (); 
}

void Robot::tacheUn()
{
    uint8_t posLigne = 3;
    uint8_t changementsLigne = 0;
    uint8_t* position;
    uint8_t reponse = FIN_LIGNE;
    bool fini = false;
    moteur_.changerDirection(true,true);
    del_.eteinte();
    moteur_.booster();
    while(!fini){       //Si le robot est sur la ligne du milieu et a fait un nombre pair de changement de lignes supérieur à 0
        //lumiere(1);
    
        reponse = traceur_.suivreLigneEpreuve1();

        position = traceur_.getPosition();
        switch (reponse){

            case FIN_LIGNE: 
    /*************************************************************************************************************/
            //Si le robot n'est plus sur une ligne
                del_.eteinte();
                fini = (posLigne==3)&&changementsLigne>0;         //trouver une solution pour remplacer 0
                if (!fini)
                    {
                    
                    if (posLigne<=3)
                    {
                        moteur_.ajustementPWM(PWM_M_G,0);
                        posLigne++;
                    }
                    else{
                        moteur_.ajustementPWM(0,PWM_M_D);
                        posLigne--;

                    }
                    while (!(position[0]||position[1]||position[2]||position[3]||position[4]))
                    {
                        position = traceur_.getPosition();
                    } 
                    changementsLigne++;
                }

                break;              
        /*************************************************************************************************************/
                //La résistance photo-sensible à droite a été activée
            case LUMIERE_DROITE:
                del_.vert();
                if (posLigne < 5)
                {
                    posLigne++;

                    moteur_.ajustementPWM(PWM_M_G,0);
                    traceur_.attendreLigne();
                    traceur_.suivreLigneTemps(750);
                    changementsLigne++;
                }
                break;


/*************************************************************************************************************/
                //la résistance photo-sensible à gauche a été activée
            case LUMIERE_GAUCHE:
                del_.vert();
                if (posLigne > 1)
                {
                    posLigne--;

                    moteur_.ajustementPWM(0,PWM_M_D);

                    traceur_.attendreLigne();

                    traceur_.suivreLigneTemps(750);
                    changementsLigne++;
                }
                break;

        }
    }
    son_.jouer(110, 1000);
    moteur_.ajustementPWM(0,0);
    minuterie_.grandDelai(1000);
    moteur_.booster();
    moteur_.tournerGauche();
    moteur_.ajustementPWM(PWM_M_G, PWM_M_D);
    position = traceur_.getPosition();
    while (!(position[0]||position[1]||position[2]||position[3]||position[4])){
        position = traceur_.getPosition();
    }

    moteur_.ajustementPWM(0,0);
    del_.eteinte();
}

void Robot::tacheDeux()
{
    const uint16_t CENTRE_ROBOT = 10;
    uint8_t* position;
        
    /********************************************************************************/
    //Trois courtes interruptions
    //moteur_.booster();
    int8_t* correction = traceur_.suivreLignePointille();
    for (int i = 0; i < 3; ++i)
    {
        moteur_.changerDirection(true, true);
     
        position = traceur_.getPosition();
        while(!(position[0]||position[1]||position[2]||position[3]||position[4])) //tant que le robot ne sent pas de ligne
        {
            moteur_.ajustementPWM(PWM_M_G+correction[0], PWM_M_D+correction[1]);
            //_delay_ms(4);
            if (correction[0] <=-1)
            {
                correction[0] += 1;
            }
            if (correction[1] <=-1)
            {
                correction[1] += 1;
            }
            position = traceur_.getPosition();                                               //Il avance

        }
        correction = traceur_.suivreLignePointille();   
    }

    /********************************************************************************/
    //Premier virage à angle droit
    traceur_.suivreLigne(CENTRE_ROBOT);

    moteur_.rotationGauche();                                           
    moteur_.ajustementPWM(PWM_M_G, PWM_M_D);
    traceur_.attendreLigne();
    moteur_.booster();
    /********************************************************************************/
    //Suivre la ligne jusqu'au virage à gauche arbitraire
    traceur_.suivreLigne(10 + CENTRE_ROBOT);


    /********************************************************************************/
    //virage à gauche arbitraire
    
    moteur_.booster();
    moteur_.ajustementPWM(0, PWM_M_D);
    traceur_.attendreLigne();
    del_.eteinte();
    moteur_.booster();
    traceur_.suivreLigneEpreuve2();
    /********************************************************************************/
    //virage à droite à angle perpendiculaire dans l'île
    traceur_.suivreLigne(CENTRE_ROBOT);            //BUG ÉTRANGE, SUIVRELIGNE N'EMBARQUE JAMAIS

    moteur_.rotationDroite();                                      
    moteur_.ajustementPWM(PWM_M_G, PWM_M_D);
    traceur_.attendreLigne();
    moteur_.booster();
    /********************************************************************************/
    //virage arbitraire à gauche
    traceur_.suivreLigneEpreuve2();
    traceur_.suivreLigne(2+CENTRE_ROBOT);    //CHANGEMENT DE VALEUR 6->2


    moteur_.rotationGauche();
    moteur_.ajustementPWM(PWM_M_G,PWM_M_D);
    traceur_.attendreLigne();
    moteur_.booster();
    del_.vert();

    /********************************************************************************/
    //  Dépassement de la légère croche
    traceur_.suivreLigne(42);        //On dépasse le léger virage à droite
    moteur_.booster();
    /********************************************************************************/
    //Dépasse premier embranchement
    traceur_.suivreLigneEpreuve2();      //On dépasse le premier embranchement

    traceur_.suivreLigne(CENTRE_ROBOT);

    /********************************************************************************/
    //Prend second embranchement
    traceur_.suivreLigneEpreuve2();

    traceur_.suivreLigne(CENTRE_ROBOT);        //Vire à droite dans le second embranchement

    moteur_.rotationDroite();                                              
    moteur_.ajustementPWM(PWM_M_G, PWM_M_D);
    traceur_.attendreLigne();
    
    moteur_.booster();
    /********************************************************************************/
    //Suit ligne et prend virage obtus
    traceur_.suivreLigneEpreuve2();
    traceur_.suivreLigne(1 + CENTRE_ROBOT);                        //vire à gauche dans le virage à angle obtus 
    moteur_.rotationGauche();
    moteur_.ajustementPWM(PWM_M_G,PWM_M_D);
    traceur_.attendreLigne();
    moteur_.booster();
    /********************************************************************************/
    //dépasse légère croche
    traceur_.suivreLigne(20);
    /********************************************************************************/
    //suis la ligne jusqu'à la croix
    traceur_.suivreLigneEpreuve2();
    /********************************************************************************/
    //Se positionne pour l'étape 3
    traceur_.suivreLigne(CENTRE_ROBOT+2);
    

    moteur_.ajustementPWM(0, 0);
    del_.eteinte();
    
}

void Robot::tacheTrois()
{
	int distance = 0;
	//JOUER SON PENDANT 2 SECONDES
    son_.jouer(880, 2000); //15000
    const uint16_t HUIT_SECONDES = 62500;
    
    //TOURNER DANS LE SENS HORRAIRE PENDANT 8 SECONDES
    moteur_.rotationDroite();
    minuterie_.partirMinuterie(HUIT_SECONDES);
    
    while(!minuterie_.getMinuterie())
    {
        distance = sonar_.getDistance();
        if(distance < 130)
        {
            moteur_.ajustementPWM (0, 0);
        }
        else
        {
            moteur_.ajustementPWM(distance, distance);
        }
        son_.capteurSon(traceur_.getPosition());
    }

    //TOURNER DANS LE SENS ANTI-HORRAIRE PENDANT 8 SECONDES
    distance = 0;
    minuterie_.partirMinuterie(HUIT_SECONDES);
    moteur_.rotationGauche();
    while(!minuterie_.getMinuterie())
    {
        distance = sonar_.getDistance();
        if(distance < 130)
        {
            moteur_.ajustementPWM (0, 0);
        }
        else
        {
            moteur_.ajustementPWM(distance, distance);
        }
        son_.capteurSon(traceur_.getPosition());
    }

    moteur_.ajustementPWM (0, 0);
    son_.arreter();
    del_.vert();
}

void Robot::epreuveFinale()
{
	uint8_t end =0;
	uint8_t partieEnCours = lcd_.getTache();
    minuterie_.grandDelai(1000);
	do
	{
		switch(partieEnCours) 
			{ 	
			case 1:
				lcd_.affichage("Tache 1 en cours de progression");

				tacheUn();

				partieEnCours = 2;
				break;

			case 2:
				lcd_.affichage("Tache 2 en cours de progression");

				tacheDeux();

				partieEnCours = 3;
				break;

			case 3:
				lcd_.affichage("Tache 3 en cours de progression");

				tacheTrois();

			    end = 1;
				break;
			}
	}while(end == 0);

	lcd_.affichage("   Succes de       Gertrudine");
}
