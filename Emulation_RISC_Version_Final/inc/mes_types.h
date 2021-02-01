
/** ** * Ce fichier contient les defirent type de variable et structure déclarie .******* */

#include <gtk/gtk.h>

	
#define OPCODE_CHAINE 1
#define RED 2
#define SEPARATEUR 3
#define IMMEDIAT 4
#define ADRESS 5
#define AFFECTE 6
#define ERREUR 7
#define NB_REGISTRE 64		//nombre de registre 
#define taille_memoire 128

int PC ;
int resExc;
int nbCycle;
int taille_token ;
int *memoire;
char op[5];
int temps_suspension;

/**typedef struct registre REGISTRE;

 * =============================================================================
 * 
 * =============================================================================
 */

struct Registre {
		char *nomRegistre;
		int valeur;
		int etat;
};
typedef struct Registre REGISTRE;
REGISTRE *tabReg;


/*
 * =============================================================================
 *
 * =============================================================================
 */
struct Token {
		char *id_token;  
		int  type; 	     
		int  erreur ;  	
};
typedef struct Token TOKEN;


/**

 * =============================================================================
	Nous avons défini une structure de données pour les trois types d’opérations 
	à savoir l’addition « ADD », la multiplication « MULT » et la comparaison « SLT ».
	Cette structure sera utilisée dans l’étage de décodage au sein
	de l’ordonnanceur, elle est nommée « Res Decodage ADD MULT SLT », de
	type « struct » et définie par :
	• char* :le nom de l’opération effectuée.
	• Registre r1 : le premier registre utilisé dans l’instruction.
	• Registre r2 : le deuxième registre utilisé dans l’instruction.
	• Registre r3 : le troisième registre utilisé dans l’instruction qui contiendra le
	résultat du calcul suite à l’opération effectuée.

 * =============================================================================
 */
 struct Res_Decodage_ADD_MULT_SLT{
	 char* opcode;
	 REGISTRE r1;
	 REGISTRE r2;
	 REGISTRE r3;
 };
 typedef struct Res_Decodage_ADD_MULT_SLT RD;

/**
  * =============================================================================
	Nous avons défini ègalement une structure de donnèes pour l’opération de
	branchement « BNEZ ». Cette structure sera utilisèe dans l’ètage de 
	décodage au sein de l’ordonnanceur, elle est nommée « Res Decodage BNEZ »,
	de type « struct » et dèfinie par :
	• char* : le nom de l’opération effectuée qui est le BNEZ.
	• Registre r1 : le registre à èvaluer pour faire le branchement.
	• int entier : la valeur du saut pour le branchement


 * =============================================================================
 */
  struct Res_Decodage_BNEZ{
	 char* opcode;
	 REGISTRE r;
     int entier;
 };
 typedef struct Res_Decodage_BNEZ RDB;


 /**
  * =============================================================================
	De la meme façon, on a défini une structure de données pour les opérations
	de chargement en mémoire « LW » et de rangement en mémoire « SW ».
	Cette structure sera utilisée dans l’étage de décodage au sein de l’ordonnanceur,
	elle est nommée « Res Decodage RDLS », de type « struct » et définie
	par :
	• char* : le nom de l’opération effectuée qui peut ˆetre un LW ou SW .
	• registre r1 : le registre dans lequel nous allons écrire la valeur chargée en
	mémoire, ou il peut etre le registre dans lequel nous prenons la valeur à
	ecrire en mémoire.
	• registre r2 : le registre qui contient la valeur à utiliser pour calculer
	l’adresse
	de chargement ou rangement.
	• int entier : qui représente l’offset à utiliser pour calculer l’adresse
	de chargement rangement.


 * =============================================================================
 */
 
   struct Res_Decodage_LW_SW{
	 char* opcode;
	 REGISTRE r1;
	 REGISTRE r2;
     int entier;
 };
 typedef struct Res_Decodage_LW_SW RDLS;

 
 

/**typedef struct Adresse ADRESSE;

 * =============================================================================
 *
 * =============================================================================
 */
   struct adresse{
	 char* adr;
	 int entier;
 };
 typedef struct adresse ADRESSE;

ADRESSE *tabAdresse;
int tailleAdresse;
