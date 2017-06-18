//////////////////////////////////////////////////////////////////////
// **************************************************************** //
//	OctoZapperPocket 				- 		Version: 1.0 			//
//	Programme pour zapper clark - 3 frequences differences			//
//	Code libre.											OctoJulo	//
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Bibliothèque ************************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
#include <Timer.h>													// Inclusion de la Bibliothèque d'horloge. 
#include <Tone.h>
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ********** Constantes, Variables, Fonctions Internes *********** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
// 	---		---			Variables Comm-Serie			---		--- //
	int BaudCOM1				= 9600;								// Vitesse de communication serie : 9600, etc, 19200, 57600, 19200, 115200.
// 	---		---				Variables Timer				---		--- //
	Timer horloge;													// Initialisation d'un timer. 
	#define Tmax				11									// Valeur max du compteur de durée de validation reception.
// 	---		---				Variables Tone				---		--- //	
	Tone tone1;
	int freqMAX  				= 65535;
	int freq  					= 3000;

// 	---		---					Brochage				---		--- //
	int PIN_tone = 3;
	int PIN_LEDRouge = 2;
	int PIN_LEDVerte = 4;
	int PIN_BP = A1;

// 	---		---					Prog					---		--- //
	int dureeprogram = 600; 										//avec l'appel du compteur donne environ 10minutes
	int freq_1  = 3300;
	int freq_2 = 12000;	
	int freq_3 = freqMAX;
	int numeroprogramme = 0;
	int timeout = 0;
	boolean ActiveOUT = false;

//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// *********************** Progamme Principal ********************* //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void setup() 
{
	pinMode(PIN_BP, INPUT);
	pinMode(PIN_LEDRouge, OUTPUT);
	pinMode(PIN_LEDVerte, OUTPUT);
// --- 		Initialisation  Serie.				---	//	
	Serial.begin(BaudCOM1);											// Initialise la vitesse de connexion série.	
	Serial.println(" Octo-TEST Zapper"); 								// Support : affichage serie	
	Serial.println("debut du programme.");									// Support : affichage serie.
// --- 			Initialisation du Timer. 		---// 
	horloge.every (940, compteur);

// --- 		Initialisation  tone.				---//	
	tone1.begin(PIN_tone);
	tone1.play(freq);
}
//////////////////////////////////////////////////////////////////////
// **************************************************************** //
// ************************* Progamme Boucle ********************** //
// **************************************************************** //
//////////////////////////////////////////////////////////////////////
void loop() 
{
	horloge.update();
	programme();
}
//////////////////////////////////////////////////////////////////////
void compteur()														// pas de paramètres.
{
	if (ActiveOUT == true)
	{
		if(timeout >= dureeprogram)
		{
		    ActiveOUT = false;
			timeout = 0;
			numeroprogramme = 0;
			tone1.stop();
			Serial.println("compteur stop.");	
		}
		else
		{
			timeout = timeout +1;
		}	
	}	
}
//////////////////////////////////////////////////////////////////////
void programme()
{

	if(digitalRead(PIN_BP)== HIGH)
	{
	    Serial.println("toto");
	}


	if (digitalRead(PIN_BP) == HIGH && numeroprogramme == 0)								// Met a 1 si le bit 1 est détecté. ou pas.
	{ 	
		ActiveOUT = true;
		timeout = 0;
		numeroprogramme = 1;
		delay(1);
		//active le premier programme et initialise le compteur	
	}
	else if (digitalRead(PIN_BP) == HIGH && numeroprogramme == 1)
	{ 	
		ActiveOUT = true;
		timeout = 0;
		numeroprogramme = 2;
		delay(1);
		//active le second programme et initialise le compteur	
	}
	else if (digitalRead(PIN_BP) == HIGH && numeroprogramme == 2)
	{ 	
		ActiveOUT = true;
		timeout = 0;
		numeroprogramme = 3;
		delay(1);
		//active le troisieme programme et initialise le compteur	
	}
	else if (digitalRead(PIN_BP) == HIGH && numeroprogramme == 3)
	{ 	ActiveOUT = false;
		timeout = 0;
		numeroprogramme = 0;
		delay(1);		
		//	STOP
	}
	if(numeroprogramme == 0 && ActiveOUT == false)
	{
		digitalWrite(PIN_LEDVerte, LOW);
		digitalWrite(PIN_LEDRouge, LOW);
		ActiveOUT = false;
		timeout = 0;
		numeroprogramme = 0;
		tone1.stop() ; 
		//STOP 
	}
	else if(numeroprogramme == 1 && ActiveOUT == true)
	{
		Serial.println("prog1");
		digitalWrite(PIN_LEDVerte, HIGH);
		digitalWrite(PIN_LEDRouge, LOW);
	  	tone1.play(freq_1);
	  	//Prog 1
	}
	else if(numeroprogramme == 2 && ActiveOUT == true)
	{
		Serial.println("prog2");
		digitalWrite(PIN_LEDVerte, LOW);
		digitalWrite(PIN_LEDRouge, HIGH);
	  	tone1.play(freq_2);
		// Prog 2
	}
	else if(numeroprogramme == 3 && ActiveOUT == true)
	{
		Serial.println("prog3");
		digitalWrite(PIN_LEDVerte, HIGH);
		digitalWrite(PIN_LEDRouge, HIGH);
	   	tone1.play(freq_3);
		// Prog 3
	}

}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////