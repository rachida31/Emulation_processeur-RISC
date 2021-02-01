#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/mes_types.h"
//lire le code instruction par instruction
char* lire_instruction(char *chemin_fichier) 
{
FILE *fichier=NULL;
fichier=fopen(chemin_fichier,"r");
  char inst[255];
  int i=0;
  if(fichier){
    
      
  	while (i<PC){
 		if(fgets(inst,255, fichier)!= NULL  ) 
    {
  			i++;
      

    }
 	 	else {strcpy(inst, "NULL");

  			i++;
			}
		}
	}
  else {
   		printf("\n le fichier n'est pas ouvere\n");
		exit(0);
		}
	fclose(fichier);
	char *chain = malloc(strlen(inst));
    strcpy(chain, inst);

return chain;}
//ecrire un une chaine dans un fichier passer en paramétre
void ecrire_instruction(char *chemin_fichier, char *instruction)
{
int i;

  FILE *fichier = NULL;
  
  fichier = fopen(chemin_fichier, "w");
  if (fichier == NULL) {
    printf("\n le fichier n'est pas ouvere\n");
    exit(0);
  } 
  else{
    printf("hhhhhhhhhh %s\n",instruction );
    fprintf(fichier, "%s \n", instruction);}
    fclose(fichier);
  

}
//lire dans le contenu de fichier d'erreur
char* lire_erreur(char *chemin_fichier)

{
FILE *fichier=NULL;
char chaine[1000];  
char *concat_chaine = NULL;         
int size = 0;
fichier = fopen(chemin_fichier, "r" );
  if (fichier){
        while(fgets(chaine, 1000, fichier) != NULL){  
            size =size+strlen(chaine);
            if (concat_chaine == NULL)
              concat_chaine = (char*)malloc( size );
            else
              concat_chaine = (char*)realloc(concat_chaine,size);
            strcat( concat_chaine  ,chaine);
          }
  }

  else {printf("erreur le fichier %s n'a pas pu etre ouvert \n",chemin_fichier );
        exit(0);}

  fclose(fichier);
  char *text_erreur = malloc(strlen(concat_chaine));
  strcpy(text_erreur, concat_chaine);
  return text_erreur;}
//ecrire dans le fichier d'erreurs 
void ecrire_erreur(char *chemin_fichier, char *erreur){
	FILE* f=NULL;
	f=fopen(chemin_fichier,"a");
	if(!f){
		printf("Erreur lecture fichier erreur.\n");
		exit(0);
	}
	
	fprintf(f,"%s \n",erreur);
	fclose(f);
		
}
