#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/mes_types.h"
#include "../inc/gestionnaire_entree_sortie.h"
#include "../inc/unite_calcul.h"
#include "../inc/ordonnanceur.h"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

	/*
La fonction init() permet d'initiliser le tableau 
des registres et celui de la mémoire

*/
	void init(){
		nbCycle=0;// nombre de cycle 
		tabReg=malloc(NB_REGISTRE*sizeof(REGISTRE));//allocation memoire du tableau des registres
tailleAdresse=0;
		for (int i = 0; i < NB_REGISTRE; ++i)
		{
			tabReg[i].nomRegistre=malloc(3*sizeof(char));
			sprintf(tabReg[i].nomRegistre, "%s%d","R",i); 
			tabReg[i].valeur=0;
			tabReg[i].etat=0;
		}
		memoire=malloc((taille_memoire*32)*sizeof(int));
		for (int i = 0; i < (32*taille_memoire); ++i)
		{ 
			memoire[i]=0;}
	}

 /*la fonction charger (char* chemin_fichier) permet de charger une instruction 
    à la fois a partir du fichier qu'on a passé son chemin en paramètre
	*/

	char* charger_instruction(char *chemin_fichier){
		char *instruction;
		instruction=lire_instruction(chemin_fichier); 
	return instruction;}


/**********************************************LA FONCTION DECODAGE*********************/


	void *decodage(char* instruction){
		const char *s = ", " " \n ( )";
		char chaine[10][10],*token1;
		int *tab=malloc(20*sizeof(int)),k=0;
		char* str1=malloc(strlen(instruction)*sizeof(char));
		strcpy(str1,instruction);
		int j=0;
		token1=strtok(str1,s);//prendre le premier token de l'instruction
		while(token1!=NULL){//on le teste s'il n'est pas nul 

			strcpy(chaine[k],token1);// on le copie dans une chaine de char
			token1 = strtok(NULL,s);
			k++;
		}

		strcpy(op,chaine[0]);
		/************************************STRUCTURE ADD/MULT/SLT********************************************/	
		    // Tester si c'est une instruction de type MULT, ADD ou SLT

printf("bbbbbbbbbbbbbbbbbbb %c\n",chaine[0][0] );
		if ((!strcmp(chaine[0], "add")) || (!strcmp(chaine[0], "mult"))||
		 (!strcmp(chaine[0], "slt") ) ||(!strcmp(chaine[0], "ADD")) ||
		 (!strcmp(chaine[0], "MULT") )|| (!strcmp(chaine[0], "SLT") )){
		RD *rd;// Déclaration d'un pointeur de type stract  RD.
	rd=malloc(sizeof (RD));
		rd->opcode=malloc(strlen(chaine[0])*sizeof(char));
		strcpy(rd->opcode,chaine[0]);//copier la valeur de la chinee[0] qui correspnd a l'opecode dans l'opecode de la structure rd.


		/*LE PREMIER REGISTRE */
		rd->r1.nomRegistre=malloc(strlen(chaine[1])*sizeof(char));// Allocation mémoire du premier nom du registre qui est de type char
		rd->r2.nomRegistre=malloc(strlen(chaine[2])*sizeof(char));// Allocation mémoire du deuxième nom du registre qui est de type char
		rd->r3.nomRegistre=malloc(strlen(chaine[3])*sizeof(char)); // Allocation mémoire du troisième nom du registre qui est de type char
		strcpy(rd->r1.nomRegistre,chaine[1]);//copier la valeur de la chinee[1] qui correspnd au nom du premier registre dans le nom de registre 1 de la structure rd.
		strcpy(rd->r2.nomRegistre,chaine[2]);//copier la valeur de la chinee[2] qui correspnd au nom du premier registre dans le nom de registre 2 de la structure rd.
		strcpy(rd->r3.nomRegistre,chaine[3]);//copier la valeur de la chinee[3] qui correspnd au nom du premier registre dans le nom de registre 3 de la structure rd.
		for (int i = 0; i < NB_REGISTRE; ++i){
			if (!strcmp(tabReg[i].nomRegistre,rd->r1.nomRegistre)){//Si le nom du registre de la structure n'est pas equivalent
                                    
				rd->r1.valeur=tabReg[i].valeur;   //On affecte la valeur du registre i à la valeur du registre1 de la structure rd
				rd->r1.etat=tabReg[i].etat;       //On affecte l'état du registre i à l'état du registre1 de la structure rd
				tabReg[i].etat=1;                 //On met l'etat du registre à 1
			                           		//	à l'un des noms du registre dans le tableau des registres 
			}
			if (!strcmp(tabReg[i].nomRegistre,rd->r2.nomRegistre)){//Si le nom du registre de la structure n'est pas equivalent
                                                             		//	à l'un des noms du registre dans le tableau des registres
				rd->r2.valeur=tabReg[i].valeur;        // On affecte la valeur du registre i à la valeur du registre2 de la structure rd
				rd->r2.etat=tabReg[i].etat;             //On met l'etat du registre à 1
							
				
			}
			if ((!strcmp(tabReg[i].nomRegistre,rd->r3.nomRegistre))){//Si le nom du registre de la structure n'est pas equivalent
                                                             		// à l'un des noms du registre dans le tableau des registres
							
				rd->r3.valeur=tabReg[i].valeur;          // On affecte la valeur du registre i à la valeur du registre3 de la structure rd
				rd->r3.etat=tabReg[i].etat;              //On met l'etat du registre à 1
				
		}}
		return  (void *) rd;// caster la structure rd en void*
		}

		/************************************STRUCTURE BNEZ********************************************/			

		if ((!strcmp(chaine[0],"bnez")) || (!strcmp(chaine[0], "BNEZ"))
		||(!strcmp(chaine[0], "li")) || (!strcmp(chaine[0], "LI"))){
			RDB *rdb;rdb=malloc(sizeof (RDB));
			rdb->opcode=malloc(strlen(chaine[0])*sizeof(char));
			strcpy(rdb->opcode,chaine[0]);	

			/*PREMIER REGISTRE*/
			rdb->r.nomRegistre=malloc(strlen(chaine[1])*sizeof(char));
			strcpy(rdb->r.nomRegistre,chaine[1]);
			for (int i = 0; i < NB_REGISTRE; ++i){
					if (!(strcmp(tabReg[i].nomRegistre,rdb->r.nomRegistre))){	
						if ((!strcmp(rdb->opcode, "li")) || (!strcmp(rdb->opcode, "LI"))){
							rdb->r.etat=tabReg[i].etat;
							tabReg[i].etat=1;
						}
						else{
							rdb->r.valeur=tabReg[i].valeur;
							rdb->r.etat=tabReg[i].etat;
							}
					}}

			/*L'ENITIER DU SAUT*/
			rdb->entier=atoi(chaine[2]);
			return  (void *) rdb;}
		/************************************STRUCTURE SW/LW*******************************************/	 
		if ((!strcmp(chaine[0], "sw")) || (!strcmp(chaine[0], "lw"))
		|| (!strcmp(chaine[0], "SW")) || (!strcmp(chaine[0], "LW"))){
			RDLS *rdls;rdls=malloc(sizeof (RDLS));
			rdls->opcode=malloc(strlen(chaine[0])*sizeof(char));
			strcpy(rdls->opcode,chaine[0]);
				if (  (!strcmp(rdls->opcode, "lw"))||(!strcmp(rdls->opcode, "LW"))){
				rdls->r1.nomRegistre=malloc(strlen(chaine[1])*sizeof(char));
				strcpy(rdls->r1.nomRegistre,chaine[1]);
				rdls->r2.nomRegistre=malloc(strlen(chaine[3])*sizeof(char));
				strcpy(rdls->r2.nomRegistre,chaine[3]);
				for (int i = 0; i < tailleAdresse; ++i)
				 {
				 	if (!(strcmp(tabAdresse[i].adr,chaine[2]))){
				 	rdls->entier=tabAdresse[i].entier;	
				 	}
				 }
				}
			if ((!strcmp(rdls->opcode, "sw"))|| (!strcmp(rdls->opcode, "SW"))){
					rdls->r1.nomRegistre=malloc(strlen(chaine[2])*sizeof(char));
					strcpy(rdls->r1.nomRegistre,chaine[2]);
					rdls->r2.nomRegistre=malloc(strlen(chaine[3])*sizeof(char));
					strcpy(rdls->r2.nomRegistre,chaine[3]);

					for (int i = 0; i < tailleAdresse; ++i)
					 {
					 	if (!(strcmp(tabAdresse[i].adr,chaine[1]))){
					  rdls->entier=tabAdresse[i].entier;
					}}
				}
			for (int i = 0; i < NB_REGISTRE; ++i){
				if ((!strcmp(rdls->opcode, "lw"))|| (!strcmp(rdls->opcode, "LW"))){
						if (!(strcmp(tabReg[i].nomRegistre,rdls->r2.nomRegistre))){				
						rdls->r2.etat=tabReg[i].etat;
						rdls->r2.valeur=tabReg[i].valeur;
						tabReg[i].etat=1;
						}}
				else if((!strcmp(rdls->opcode, "SW"))||(!strcmp(rdls->opcode, "sw")))	{
					if (!(strcmp(tabReg[i].nomRegistre,rdls->r1.nomRegistre))){
						rdls->r1.etat=tabReg[i].etat;
						rdls->r1.valeur=tabReg[i].valeur;} 
					if (!(strcmp(tabReg[i].nomRegistre,rdls->r2.nomRegistre))){ 			
						rdls->r2.etat=tabReg[i].etat;
						rdls->r2.valeur=tabReg[i].valeur;
						tabReg[i].etat=1;	}
				}}
			return  (void *) rdls;			
		}

		if (chaine[0][0],'@')//Si la chaine[0][0] est une '@'
		{
		strcpy(op,"adress");//alors on la copie dans l'op adresse pour savoir qu'il s'agit d'une déclaration
	
tabAdresse[tailleAdresse].adr=malloc(strlen(chaine[0])*sizeof(char));
strcpy(tabAdresse[tailleAdresse].adr,chaine[0]);
tabAdresse[tailleAdresse].entier=atoi(chaine[2]);
tailleAdresse++;
		return NULL;
		}}


/*
La focntion execution(void* structure) prend la structure retournée dans le décodage
et regarde par rapport à l'opcode de l'instruction ; elle effectue le calcul en appelant 
les fonctions de l'unité de calcul
*/
	int execution(void* structure){  
			if ((!strcmp(op,"add"))||(!strcmp(op,"ADD"))||(!strcmp(op,"mult"))
			||(!strcmp(op,"MULT"))||(!strcmp(op,"slt"))||(!strcmp(op,"SLT"))){
				    //caster sur la structure correspondante pour pouvoir effectuer le bon traitement (RD)
				RD cast_RD = *(RD*)structure;
						//affecter à "resultat" le résultat retourner par la fonction du module unité de calcul puis le retourner
	// en tant que resultat de la fonction "execution"
				int resultat = calcule_arithmetique_logique (cast_RD.opcode,cast_RD.r2.valeur,cast_RD.r3.valeur);
				return resultat; }

	// Quand il s'agit d'un "lx" ou un "sw" on fait un cast sur la structure RDLS puis retourner l'adresse à laquelle on doit
	// charger ou stocker un variable
			if ((!strcmp(op,"LW"))||(!strcmp(op,"lw"))){
				RDLS cast_RDLS = *(RDLS*)structure;
	
				int adress = calcule_arithmetique_logique (cast_RDLS.opcode,cast_RDLS.r2.valeur,cast_RDLS.entier);
				return adress;}
			if ((!strcmp(op,"SW"))||(!strcmp(op,"sw"))){	
				RDLS cast_RDLS = *(RDLS*)structure;
				int adress=calcule_arithmetique_logique (cast_RDLS.opcode,cast_RDLS.r1.valeur,cast_RDLS.entier);
				return adress;}
					// Quand l'opcode est est "BNEZ" on fait un cast sur la structure RDB et on renvoi le saut à effectuer
	
			if (!(strcmp(op,"BNEZ"))||(!strcmp(op,"bnez"))){
				RDB cast_RDB = *(RDB*)structure;
				int saut = calcule_arithmetique_logique (cast_RDB.opcode,cast_RDB.r.valeur,cast_RDB.entier);
				return saut;}
				return 0;} 



//fonction qui renvoie le nombre de cycles lors d'une éxecution séquentielle
	//selon le type de l'opcode on incrémente le nombre de cycle soit de 5 de 6 ou de 8
	int nb_cycle_sequentiel(char* opcode){
		if ((!strcmp(opcode,"ADD") ) ||(!strcmp(opcode,"SLT"))
		||( !strcmp(opcode,"BNEZ")) || (!strcmp(opcode,"LI") )
		||(!strcmp(opcode,"add")  ) ||(!strcmp(opcode,"slt") )
		||(!strcmp(opcode,"bnez"))|| (!strcmp(opcode,"li") ))
		{ nbCycle= nbCycle +5;}
		if ((!strcmp(opcode,"LW") ) || (!strcmp(opcode,"SW"))
		||(!strcmp(opcode,"lw")) || ( !strcmp(opcode,"sw"))) { nbCycle= nbCycle + 6 ;}
		if ((!strcmp(opcode,"MULT"))||(!strcmp(opcode,"mult"))) { 
		nbCycle= nbCycle + 8;}
		return nbCycle;}
/*
Cette fonction retourne la valeur mémoire qui correspond à l'adresse passée en paramètre
*/
	int fonction_load(int adresse) {return memoire[adresse];}
	
// une procedure qui permet de stocker une valeur passée en parametre dans
// un tableau de mémoire au niveau d'une adresse précise
	void procedure_store (int adresse , int val) {

		memoire[adresse] = val;
	}
	/*
Cette fonction permet de faire l'écriture du resultat dans un registre qui existe dans le tableau des registres
On regarde si le registre n'existe pas dans le tableau des regitres en verifiant son nom et que son etat = 0
*/
	void procedure_WB(int resultat, REGISTRE Reg){
		int i=0;
		while (strcmp(Reg.nomRegistre,tabReg[i].nomRegistre)){i++;}
		if ((!strcmp(Reg.nomRegistre,tabReg[i].nomRegistre))){
			tabReg[i].valeur = resultat;
		}
	}
/*
Cette fonction illustre l'exécution séquentielle d'une instruction en retournant 
à la fin le nombre de cycles nécessaires pour l'exécution de chaque instruction
*/
	int sequentiel(char* chemin_fichier){
	char *instruction=NULL;
	int result;    
	int resultat=0; // le résultat de l'exécution
	void *structure; // Variable (type void*) qu'on va lui affecter la structure retournée dans le décodage
	PC=0;  
	printf("ghhhhhhhhhhhhhhhhhhggggggggggggggg\n");
		init();//Initialiser le tableau des registres
				tabAdresse = malloc(30 * sizeof(ADRESSE));

		do{
			PC++; //incrémenter le PC à chaque fois qu'on charge une instruction du code
			instruction=charger_instruction(chemin_fichier);//on charge l'instruction
if (instruction[0]!='a' && instruction[0]!='A' && instruction[0]!='b' && instruction[0]!='B' && instruction[0]!='m' && instruction[0]!='M' && instruction[0]!='s' && 
	instruction[0]!='S' && instruction[0]!='l' && instruction[0]!='L' && instruction[0]!='@' && strcmp(instruction,"NULL") && strcmp(instruction,"\n"))
{
		strcpy(instruction,"NULL");
}
		else if (strcmp(instruction,"NULL") && strcmp(instruction,"\n")){
				structure=decodage(instruction);//on affecte la structure retournée dans le décodage à structure
printf("moi moi moi moi moi moi moi moi %s \n",instruction);
				if ( !strcmp(op,"li")|| !strcmp(op,"LI")){

					RDB cast_RDB = *(RDB*)structure; //cast de structure en RDB 
					nb_cycle_sequentiel(cast_RDB.opcode);// calcul du nombre de cycles en mode sequentiel
					resultat=cast_RDB.entier;// resulat est l'entier retournée par la structure
	
					procedure_WB(cast_RDB.entier,cast_RDB.r);// ecriture du résultat sur le registre

				}
				if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
				|| (!strcmp(op,"add")) || (!strcmp(op,"slt"))
				|| (!strcmp(op,"MULT")) || (!strcmp(op,"mult"))
				|| (!strcmp(op,"bnez")) || (!strcmp(op,"BNEZ"))
				|| (!strcmp(op,"sw")) || (!strcmp(op,"SW"))
				|| (!strcmp(op,"LW")) || (!strcmp(op,"lw"))){

					result=execution(structure);

					//strcmp : si c est un add ou mul ou slt ===> faire appel fonction nbcycleseq
					//caster la structure : void * 
					if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) || (!strcmp(op,"add")) || (!strcmp(op,"slt"))){
						RD cast_RD = *(RD*)structure;
						resultat=result;
						int t=nb_cycle_sequentiel(cast_RD.opcode);
						procedure_WB(result,cast_RD.r1);}
					// si bnez on va faire une condition : si resultat =0 on va rien faire sinon j'augmente le pc et on fait appel a la fonction calculnbcycle (pour bnez)
					if((!strcmp(op,"bnez"))||(!strcmp(op,"BNEZ"))){//il faut d'abord caster 
						RDB cast_RDB = *(RDB*)structure;
					//On vérifie si le résultat est différent de 0
						if (result != 0){		// On augmente le PC de la valeur du resultat d'execution-1
							PC += result-1; }
						nb_cycle_sequentiel(cast_RDB.opcode);
						procedure_WB(result,cast_RDB.r);}// si cest un sw : appel store ( prend 2 param : val et adresse)
					if ((!strcmp(op,"sw"))||(!strcmp(op,"SW"))){//il faut d'abord caster
						RDLS cast_RDLS = *(RDLS*)structure;
						procedure_store(result,cast_RDLS.r2.valeur);// si cest un SW : pon fait appel à store ( prend 2 paramètres : val et adresse)
						resultat=cast_RDLS.r2.valeur;
						nb_cycle_sequentiel(cast_RDLS.opcode);
					}
					if ((!strcmp(op,"lw"))||(!strcmp(op,"LW"))){//il faut d'abord caster
						RDLS cast_RDLS = *(RDLS*)structure;
						resultat= fonction_load(result);
						nb_cycle_sequentiel(cast_RDLS.opcode);
						procedure_WB(resultat,cast_RDLS.r1);}
					if ((!strcmp(op, "MULT"))|| (!strcmp(op, "mult"))){
						RD cast_RD = *(RD*)structure;

						resultat=result;
						int nb5 = nb_cycle_sequentiel(cast_RD.opcode);
						procedure_WB(result,cast_RD.r1);}
					}
				}
		}while(strcmp(instruction,"NULL")!=0);

		if (tabAdresse!=NULL)
{
for (int i = 0; i < tailleAdresse; ++i)
{
	printf("0000000000000........... %s\n",tabAdresse[i].adr );
}
}
//*******************LES LIBERATION MÉMOIRE *********************
		for (int i = 0; i < NB_REGISTRE; ++i){free(tabReg[i].nomRegistre);}
		free(tabReg); //libérer le tableau de registres
	if (tabAdresse!=NULL)
	{
	

		for (int i = 0; i < tailleAdresse; ++i){free(tabAdresse[i].adr) ;//libérer l'adresse)	 
	}
		free(tabAdresse);}//libérer tableau d'adresses
	
	return resultat;}

/*
Cette fonction calcule le nombre de cycle suite à une exécution en mode pipeline
*/
	int nb_cycle_pipline(char* opcode,int verif ){
	if ((!strcmp(opcode,"ADD") ) ||(!strcmp(opcode,"SLT"))//On regarde si on a des instructions de type ADD, BNEZ,SLT ou LI
	||( !strcmp(opcode,"BNEZ")) || (!strcmp(opcode,"LI") )
	||(!strcmp(opcode,"add")  ) ||(!strcmp(opcode,"slt") )
	||(!strcmp(opcode,"bnez"))||(!strcmp(opcode,"li") )) { // on calcule le nombre de cycle en ajoutant la valeur de verif, 1 qui correspond à la pénalité
nbCycle= nbCycle +verif+1;// on calcule le nombre de cycle en ajoutant la valeur de verif, 2 qui correspond à la pénalité}
	}
	if ((!strcmp(opcode,"LW") ) || (!strcmp(opcode,"SW"))||(!strcmp(opcode,"lw")) || ( !strcmp(opcode,"sw"))) { nbCycle= nbCycle + 2 + verif ;}
	if ((!strcmp(opcode,"MULT"))||(!strcmp(opcode,"mult"))) { 
	 // on calcule le nombre de cycle en ajoutant la valeur de verif, 4 qui correspond à la pénalité
nbCycle= nbCycle + verif+4;
}
	return nbCycle;}



    int verification (char* nomreg1, char* nomreg2,void* structure,char* chemin_fichier){
 	char *a,*b;
 	int i=0,k=0,j=0;
 	a=malloc(3*sizeof(char));
 	b=malloc(3*sizeof(char));
if(!strcmp(op,"bnez")  ||!strcmp(op,"BNEZ") ){
	return 3;
}
 		while(nomreg2[i]!='\0' || nomreg1[i]!='\0'){
 		if((isdigit(nomreg2[i]))){
 			b[j]=nomreg2[i];
 			j++;
 	}
 		if((isdigit(nomreg1[i]))){
 			a[k]=nomreg1[i];
 			k++;
 	}
 		i++;
 	}
char *instruction;
int pc=PC;
char chaine[10][10];
int t=0;
char* str1;
const char *s = ", " " \n ( )";
   char *token1;
if(tabReg[atoi(a)].etat==1 || tabReg[atoi(b)].etat==1){
	while(t<=3){
		PC--;
		if (PC<=0){break;}
		t++;
		instruction=lire_instruction(chemin_fichier);
		k=0;
		str1=malloc(strlen(instruction)*sizeof(char));
		strcpy(str1,instruction);
		//create(instruction,token);
		token1=strtok(str1,s);
		while(token1!=NULL){
			strcpy(chaine[k],token1);
			token1 = strtok(NULL,s);
			k++;}

		free(str1);
		if (!strcmp(op,"lw")||!strcmp(op,"LW") )
		{
		if ((chaine[0][0]=='@')){break;}
		if(!strcmp(chaine[1],nomreg2)  ){break;}}
		else{
		if ((chaine[0][0]=='@')){break;}
		if(!strcmp(chaine[1],nomreg1) ||!strcmp(chaine[1],nomreg2) )
		{break;
		}}



		}
	}
PC=pc;
free(a);
free(b);
if(t==1)return 3;
if(t==2)return 2;
if(t==3)return 1;
return 0;
 }

/*
Cette fonction illustre l'exécution d'une instruction en mode pipeline en prenant le chmein de l'instruction en paramètre 
et renvoyant le nombre de cycles nécessaires pour une exécution pipelinée de chaque instruction du code.
*/
	int pipeline(char* chemin_fichier){
		char *instruction=NULL;
		int result;
		void *structure;
		PC=0;
		int resultat=0;       //Resultat d'exécution 
		int nb;
		init();           //Initilaiser le tableau des registres
						tabAdresse = malloc(30 * sizeof(ADRESSE));

	nbCycle=4;        //Nombre de cycles
		int v;
		do{
			PC++;
			instruction=charger_instruction(chemin_fichier);

			if (instruction[0]!='a' && instruction[0]!='A' && instruction[0]!='b' && instruction[0]!='B' && instruction[0]!='m' && instruction[0]!='M' && instruction[0]!='s' && 
	instruction[0]!='S' && instruction[0]!='l' && instruction[0]!='L' && instruction[0]!='@' && strcmp(instruction,"NULL") && strcmp(instruction,"\n"))
{
		strcpy(instruction,"NULL");


}
			if (strcmp(instruction,"NULL") && strcmp(instruction,"\n")){
				structure=decodage(instruction);
				if ( !strcmp(op,"li")|| !strcmp(op,"LI")){
					RDB cast_RDB = *(RDB*)structure;//cast de la variable Structure en la structure utilisée pour les instructions ADD/SLT/ qui est RD
					nb_cycle_pipline(cast_RDB.opcode,0 );
					resultat=cast_RDB.entier;
					procedure_WB(cast_RDB.entier,cast_RDB.r);}
				if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
				|| (!strcmp(op,"add")) || (!strcmp(op,"slt"))
				|| (!strcmp(op,"MULT")) || (!strcmp(op,"mult"))
				|| (!strcmp(op,"bnez")) || (!strcmp(op,"BNEZ"))
				|| (!strcmp(op,"sw")) || (!strcmp(op,"SW"))
				|| (!strcmp(op,"LW")) || (!strcmp(op,"lw"))){
					result=execution(structure);
					//strcmp : si c est un add ou mul ou slt ===> faire appel fonction nbcycleseq
					//caster la structure : void * 
					if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) || (!strcmp(op,"add")) || (!strcmp(op,"slt"))){
						RD cast_RD = *(RD*)structure;
						resultat=result;
						v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier); //la valeur retournée par la fonction verification 
                                                                             //qui prend en paramètre le nom du registre2 et registre3 de la structure RD  
	nb_cycle_pipline(cast_RD.opcode,v);  //le calcul du nombre de cycles qui prend en paramètre l'opcode et la valeur de pénalité 
	                                     //retournée par la fonction vérification
	procedure_WB(result,cast_RD.r1);     //Ecriture du résultat dans le registre 
}
					// si bnez on va faire une condition : si resultat =0 on va rien faire sinon j'augmente le pc et on fait appel a la fonction calculnbcycle (pour bnez)
					if((!strcmp(op,"bnez"))||(!strcmp(op,"BNEZ"))){//il faut d'abord caster 
						RDB cast_RDB = *(RDB*)structure;
					if (result != 0){		PC += result-1; }
						v=verification (cast_RDB.r.nomRegistre, cast_RDB.opcode,structure,chemin_fichier);
						nb_cycle_pipline(cast_RDB.opcode,v );
						procedure_WB(result,cast_RDB.r);}// si cest un sw : appel store ( prend 2 param : val et adresse)
					if ((!strcmp(op,"sw"))||(!strcmp(op,"SW"))){//il faut d'abord caster
						RDLS cast_RDLS = *(RDLS*)structure;
						procedure_store(result,cast_RDLS.r2.valeur);
						resultat=cast_RDLS.r2.valeur;
						v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
						nb_cycle_pipline(cast_RDLS.opcode,v );}
					if ((!strcmp(op,"lw"))||(!strcmp(op,"LW"))){//il faut d'abord caster
						RDLS cast_RDLS = *(RDLS*)structure;
						resultat= fonction_load(result);
						v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
						nb_cycle_pipline(cast_RDLS.opcode,v );
						procedure_WB(resultat,cast_RDLS.r1);}
					if ((!strcmp(op, "MULT"))|| (!strcmp(op, "mult"))){
						RD cast_RD = *(RD*)structure;
						resultat=result;
						v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier);
						nb_cycle_pipline(cast_RD.opcode,v );//le calcul du nombre de cycles qui prend en paramètre l'opcode et la valeur de pénalité 
						procedure_WB(result,cast_RD.r1);        //Ecriture du résultat dans le registre 
					}
					}
			}
	}while(strcmp(instruction,"NULL")!=0);// L'instruction n'est pas nulle
	for (int i = 0; i < NB_REGISTRE; ++i){free(tabReg[i].nomRegistre);}
	free(tabReg);//libérer le tableau de registres
	for (int i = 0; i < tailleAdresse; ++i){ free(tabAdresse[i].adr);	 }
	free(tabAdresse); //libérer le tableau d'adressses
return resultat;   // retourner le resultat d'exécution
	}

/***********************************************************************************************
							DANS LA PARTIE EN BAS ON AS ESSEYER DE FAIRE
							  AVEC LES PROCESSUS LE CALCUL DE NOMBRE DE 
							    CYCLE FONCTION MAIS PAS LE RÉSULTAT
************************************************************************************************/


/*
/*la fonction suspendre_processus(har* chemin) permet de suspendre un processus, 
	prends le chemin du fichier qui contient les intructions, et a chaque fois qu'on charge
	une instruction non nulle, on lui crée un processus et on le suspend d'une durée de temps
	*//*
      void suspendre_processus(char* chemin_fichier  ){
 		temps_suspension = 2;
 		char* in = charger_instruction(chemin_fichier);
 		pid_t p = creation_processus(in);
		pid_t pid_fils;
		p = getpid();
        srand (getpid());
         sleep(temps_suspension);}

/*la fonction suspendre_processus(har* chemin) permet de créer un processus, 
	prends le chemin du fichier qui contient les intructions, et a chaque fois qu'on charge
	une instruction non nulle, on lui crée un processus
	*//*
pid_t creation_processus(char* chemin_fichier){
pid_t pid;
	pid=fork();
  if (pid){
		 moi(chemin_fichier);
	     sleep(0.5);
	    }
	else{
		pid_t pid_fils = getpid();
        srand (getpid());
         sleep(0.07);
         exit (0);
			}
				wait(NULL);
   return pid;}

int moi(char* chemin_fichier)
{
char *instruction=NULL;
int result=0,v=0;
void *structure;
instruction=charger_instruction(chemin_fichier);
if(strcmp(instruction,"NULL")!=0){

printf("%d et %d\n", nbCycle,PC);
PC++;
instruction=charger_instruction(chemin_fichier);
if (strcmp(instruction,"NULL") && strcmp(instruction,"\n")){
	printf("opopopopop %s\n",op );
structure=decodage(instruction);
if ( !strcmp(op,"li")|| !strcmp(op,"LI"))
{
RDB cast_RDB = *(RDB*)structure;
		  nb_cycle_pipline(cast_RDB.opcode,0 );
		resultat=cast_RDB.entier;
		procedure_WB(cast_RDB.entier,cast_RDB.r);}


if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
	|| (!strcmp(op,"add")) || (!strcmp(op,"slt"))
	|| (!strcmp(op,"MULT")) || (!strcmp(op,"mult"))
	|| (!strcmp(op,"bnez")) || (!strcmp(op,"BNEZ"))
	|| (!strcmp(op,"sw")) || (!strcmp(op,"SW"))
	|| (!strcmp(op,"LW")) || (!strcmp(op,"lw"))){

result=execution(structure);
//strcmp : si c est un add ou mul ou slt ===> faire appel fonction nbcycleseq
//caster la structure : void * 
if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
	|| (!strcmp(op,"add")) || (!strcmp(op,"slt")))
{   RD cast_RD = *(RD*)structure;
	resultat=result;
 v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RD.opcode,v );
	procedure_WB(result,cast_RD.r1);}





// si bnez on va faire une condition : si resultat =0 on va rien faire sinon j'augmente le pc et on fait appel a la fonction calculnbcycle (pour bnez)
if((!strcmp(op,"bnez"))||(!strcmp(op,"BNEZ")))
{//il faut d'abord caster 
	RDB cast_RDB = *(RDB*)structure;
	
		  int v=verification (cast_RDB.r.nomRegistre, cast_RDB.opcode,structure,chemin_fichier);
		  nb_cycle_pipline(cast_RDB.opcode,v );
		procedure_WB(result,cast_RDB.r);}// si cest un sw : appel store ( prend 2 param : val et adresse)



if ((!strcmp(op,"sw"))||(!strcmp(op,"SW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
	procedure_store(result,cast_RDLS.r2.valeur);
	resultat=cast_RDLS.r2.valeur;
	v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RDLS.opcode,v );}



if ((!strcmp(op,"lw"))||(!strcmp(op,"LW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
		resultat= fonction_load(result);
		v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
		nb_cycle_pipline(cast_RDLS.opcode,v );
	procedure_WB(resultat,cast_RDLS.r1);}



if ((!strcmp(op, "MULT"))|| (!strcmp(op, "mult")))
{RD cast_RD = *(RD*)structure;
	resultat=result;
	printf("resultat %d\n",result );
     	 v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RD.opcode,v );
	procedure_WB(result,cast_RD.r1);}

}}
}
return nbCycle;

}




int pipeline1(char* chemin_fichier){
char *instruction=NULL;
int result;
void *structure;
PC=0;

int nb;
init();
nbCycle=4;int v;
do{
PC++;
instruction=charger_instruction(chemin_fichier);
if (strcmp(instruction,"NULL") && strcmp(instruction,"\n")){
	pid_t p1=creation_processus( chemin_fichier);
structure=decodage(instruction);
if ( !strcmp(op,"li")|| !strcmp(op,"LI"))
{
RDB cast_RDB = *(RDB*)structure;
		  nb_cycle_pipline(cast_RDB.opcode,0 );
		resultat=cast_RDB.entier;
		pid_t p2=creation_processus( chemin_fichier);
		pid_t p3=creation_processus( chemin_fichier);
		pid_t p4=creation_processus( chemin_fichier);
		procedure_WB(cast_RDB.entier,cast_RDB.r);}


if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
	|| (!strcmp(op,"add")) || (!strcmp(op,"slt"))
	|| (!strcmp(op,"MULT")) || (!strcmp(op,"mult"))
	|| (!strcmp(op,"bnez")) || (!strcmp(op,"BNEZ"))
	|| (!strcmp(op,"sw")) || (!strcmp(op,"SW"))
	|| (!strcmp(op,"LW")) || (!strcmp(op,"lw"))){
pid_t p2=creation_processus( chemin_fichier);
result=execution(structure);
//strcmp : si c est un add ou mul ou slt ===> faire appel fonction nbcycleseq
//caster la structure : void * 
if((!strcmp(op,"ADD")) || (!strcmp(op,"SLT")) 
	|| (!strcmp(op,"add")) || (!strcmp(op,"slt")))
{   RD cast_RD = *(RD*)structure;
	resultat=result;
 v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RD.opcode,v );
pid_t p3=creation_processus( chemin_fichier);
pid_t p4=creation_processus( chemin_fichier);
	procedure_WB(result,cast_RD.r1);}





// si bnez on va faire une condition : si resultat =0 on va rien faire sinon j'augmente le pc et on fait appel a la fonction calculnbcycle (pour bnez)
if((!strcmp(op,"bnez"))||(!strcmp(op,"BNEZ")))
{//il faut d'abord caster 
	RDB cast_RDB = *(RDB*)structure;
	
		  int v=verification (cast_RDB.r.nomRegistre, cast_RDB.opcode,structure,chemin_fichier);
		  nb_cycle_pipline(cast_RDB.opcode,v );
		  pid_t p3=creation_processus( chemin_fichier);
		  pid_t p4=creation_processus( chemin_fichier);
		procedure_WB(result,cast_RDB.r);}// si cest un sw : appel store ( prend 2 param : val et adresse)



if ((!strcmp(op,"sw"))||(!strcmp(op,"SW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
	pid_t p3=creation_processus( chemin_fichier);
	procedure_store(result,cast_RDLS.r2.valeur);
	pid_t p4=creation_processus( chemin_fichier);
	resultat=cast_RDLS.r2.valeur;
	v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RDLS.opcode,v );}



if ((!strcmp(op,"lw"))||(!strcmp(op,"LW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
	pid_t p3=creation_processus( chemin_fichier);
		resultat= fonction_load(result);
		v=verification (cast_RDLS.r1.nomRegistre, cast_RDLS.r2.nomRegistre,NULL,chemin_fichier);
		nb_cycle_pipline(cast_RDLS.opcode,v );
		pid_t p4=creation_processus( chemin_fichier);
	procedure_WB(resultat,cast_RDLS.r1);}



if ((!strcmp(op, "MULT"))|| (!strcmp(op, "mult")))
{RD cast_RD = *(RD*)structure;
	resultat=result;
	printf("resultat %d\n",result );
     	 v=verification (cast_RD.r2.nomRegistre, cast_RD.r3.nomRegistre,NULL,chemin_fichier);
nb_cycle_pipline(cast_RD.opcode,v );
pid_t p3=creation_processus( chemin_fichier);
pid_t p4=creation_processus( chemin_fichier);
	procedure_WB(result,cast_RD.r1);}

}}
}while(strcmp(instruction,"NULL")!=0);
	 for (int i = 0; i < NB_REGISTRE; ++i)
	 {
	
			free(tabReg[i].nomRegistre);
			
	 }
	 free(tabReg);
	 for (int i = 0; i < tailleAdresse; ++i)
	 {
free(tabAdresse[i].adr);	 }
free(tabAdresse);
return resultat;
}*/



/***********************************************************************************************
							DANS LA PARTIE EN BAS ON AS ESSEYER DE FAIRE
							   AVEC LES THREAD CA MARCHE PAS AU NIVEAU
							  	  DE L'EXECUTION,CA IDENTIFIE PAS 
							  	   	  TOUJOURS L'OPCODE ET 
							  		      IL Y'A PAS LES 
							  			    SUSPEENSION
************************************************************************************************/

/*
char* chemin;
int bool_cycle=0;
int nb_cycle=0;
int fin=0;
int max= -1;
int final=0;
int etat_unit=0;
int suspendu=-1;

void *thread_pipeline(void *arg)
{	
	void* structure;
	int result;
    //printf("Nous sommes dans le thread.\n");
    int prec = bool_cycle;
    int val=bool_cycle;
//IF
	//~ while(suspendu!=-1 && val<suspendu){}
    char *instruction = lire_instruction(chemin);
    if(strcmp(instruction,"NULL")==0) {
        fin=1;
        pthread_exit(NULL);
    }
    
    while(strcmp(instruction,"\n")==0) {
		PC++;
		instruction=lire_instruction(chemin);
		
	}
	 if(strcmp(instruction,"NULL")==0) {
        fin=1;
        pthread_exit(NULL);
    }
    PC = PC + 1;
    printf("1er etage %s\n",instruction);
    while(bool_cycle==prec){}
//DE
	//~ while(suspendu!=-1 && val<suspendu){}
    structure=decodage(instruction);
    printf("2eme etage %s \n",instruction);
    prec=bool_cycle;
    
    while(bool_cycle==prec){}
//EX
	while(suspendu!=-1 && val<suspendu){}
	int attente=0;
	while(etat_unit!=0){ 
		attente=1;
		//~ suspendu=val;
		}
	etat_unit=1;
	if(attente==1) {
		attente=0;
		prec=bool_cycle;
		while(bool_cycle!=(prec+1)){ }
		prec=bool_cycle;
		
	}
	
	
	   if( strcmp(op,"ADD") == 0|| strcmp(op,"SLT") == 0 
	|| strcmp(op,"add") == 0 || strcmp(op,"slt") == 0  || strcmp(op,"bnez")==0 ||strcmp(op,"BNEZ")==0 )
{   
	
	result=execution(structure);
}

if ((strcmp(op,"lw"))==0||(strcmp(op,"LW"))==0 || (strcmp(op,"sw"))==0||(strcmp(op,"SW"))==0)
{

	result=execution(structure);
	while(bool_cycle!=(prec+2)){}
	prec=bool_cycle;
}

if ((strcmp(op, "MULT"))==0|| (strcmp(op, "mult"))==0)
{
	printf(" ");
	result=execution(structure);
	while(bool_cycle!=(prec+4)){}
	prec=bool_cycle;
	
}
	result=execution(structure);
    printf("3eme etage %s\n",instruction);
	
    prec=bool_cycle;
    etat_unit=0;
    while(bool_cycle==prec){}
//MEM  
	//~ while(suspendu!=-1 && val<suspendu){}
    // si cest un sw : appel store ( prend 2 param : val et adresse)
if ((!strcmp(op,"sw"))||(!strcmp(op,"SW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
	procedure_store(result, result);
	
}
    printf("4eme etage %s\n",instruction);prec=bool_cycle;

    prec=bool_cycle;
    while(bool_cycle==prec){}
    
//WB
	//~ while(suspendu!=-1 && val<suspendu){}
    if((!strcmp(op,"ADD")) == 0|| (!strcmp(op,"SLT") == 0) 
	|| (!strcmp(op,"add")) == 0 || (!strcmp(op,"slt")) == 0)
{   RD cast_RD = *(RD*)structure;
 
	procedure_WB(result,cast_RD.r1);
}
// si bnez on va faire une condition : si resultat =0 on va rien faire sinon j'augmente le pc et on fait appel a la fonction calculnbcycle (pour bnez)
if((!strcmp(op,"bnez"))||(!strcmp(op,"BNEZ")))
{//il faut d'abord caster 
	RDB cast_RDB = *(RDB*)structure;
	if (result != 0)
	{
		PC += result; 
		
		procedure_WB(result,cast_RDB.r);
	}
}

if ((!strcmp(op,"lw"))||(!strcmp(op,"LW")))
{//il faut d'abord caster
	RDLS cast_RDLS = *(RDLS*)structure;
	int valeur = fonction_load(result);
    
	procedure_WB(valeur,cast_RDLS.r2);
}
if ((!strcmp(op, "MULT"))|| (!strcmp(op, "mult")))
{
   RD cast_RD = *(RD*)structure;
    
	procedure_WB(result,cast_RD.r1);}

//
    printf("5eme etage %s\n",instruction);



    if(max==val) {
        final=1;

    }

    (void) arg;
    pthread_exit(NULL);
}

 int pipeline1(char* chemin_fichier)
{
	init();
	chemin=chemin_fichier;
	PC=1;
	int duree = 0.5*CLOCKS_PER_SEC; //Durée d'un cycle, si c'est égale a CLOCKS_PER_SEC le cycle dure 1 seconde
    //~ int nb_cycle = 0;
    int x=0;
    int y=0;

    pthread_t *tab = calloc(1, sizeof(pthread_t));

    while (fin!=1)    //Tant que le programme n'est pas fini
    {
        printf("\n---tour %d---\n",nb_cycle);
        //~ bool_cycle = 0;
        x = clock();
        if(x == -1)    //On vérifie qu'il n'y a pas d'erreur
        {
            printf("erreur\n");
            exit(0);
        }
        y = x;
        //Ici on doit créer un processus et effectué une instruction
         tab = realloc(tab,(nb_cycle + 1) * sizeof(pthread_t));
             if (pthread_create(&tab[nb_cycle], NULL, thread_pipeline, NULL)) {
            perror("pthread_create");
            return EXIT_FAILURE;
            }



        while((y-x) < duree)
        {
            y = clock();
        }
        //~ printf("x= %d, y= %d, y-x = %d\n",x,y,y-x);
        bool_cycle = bool_cycle + 1;
        nb_cycle = nb_cycle + 1;
    }
    max=nb_cycle - 2;
    while (final!=1)    //Tant que le programme n'est pas fini
    {
        printf("\n---tour %d---\n",nb_cycle);

        x = clock();
        if(x == -1)    //On vérifie qu'il n'y a pas d'erreur
        {
            printf("erreur\n");
            exit(0);
        }
        y = x;


        while((y-x) < duree)
        {
            y = clock();
        }
        //~ printf("x= %d, y= %d, y-x = %d\n",x,y,y-x);
        bool_cycle = bool_cycle + 1;
        nb_cycle = nb_cycle + 1;
    }


    printf("nombre de cycles = %d\nPC=%d\n", nb_cycle, PC);

    free(tab);

return 0;
}
*/