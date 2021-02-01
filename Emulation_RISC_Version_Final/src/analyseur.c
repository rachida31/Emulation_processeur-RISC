#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "../inc/mes_types.h"
#include "../inc/analyseur.h"
#include "../inc/gestionnaire_entree_sortie.h"


char* analyse_code(char* chemin_fichier_code ){
char* chemin_fichier_erreur=NULL,* instruction=NULL,*message = NULL;
TOKEN *tab_token=NULL;
PC=0;
 tailleAdresse=0;
chemin_fichier_erreur= malloc(20*sizeof(char));
tabAdresse = malloc( 30 * sizeof(ADRESSE));
remove("code/erreur.txt");
do{
    PC++;
      instruction=lire_instruction(chemin_fichier_code);
  if(strcmp(instruction,"NULL")&&
   strcmp(instruction,"\n")&& strcmp(instruction," ")){
   
    int erreur=analyse_lexical(instruction,&tab_token,chemin_fichier_erreur);
          if (erreur==1|| erreur==0){
            if (erreur==1){
             strcpy(chemin_fichier_erreur,"code/erreur.txt");
             for (int i = 0; i < taille_token; i++){
              message = (char*)malloc(10*sizeof(tab_token[i].id_token) );
              if(tab_token[i].erreur==1){
                sprintf(message, "%s%d%s%s%s", "ligne ", PC ," : L'erreur est dans le mot ",tab_token[i].id_token
                  ,". Ce lexique n'appartient pas à notre langage");

                ecrire_erreur(chemin_fichier_erreur, message);
                tab_token[i].erreur=0;
                free(message);}}
              }
    erreur=analyse_syntaxique(&tab_token,chemin_fichier_erreur);
          if (erreur==1){
                     strcpy(chemin_fichier_erreur,"code/erreur.txt");

             for (int i = 0; i < taille_token; i++){
              message = (char*)malloc(100*sizeof(tab_token[i].id_token) );
              if(tab_token[i].erreur==1){
                  sprintf(message, "%s%d%s%s%s%s", "ligne ", PC ," : L'erreur est dans le mot ",tab_token[i].id_token
                    ,". il y'a une erreur dans la syntaxe de l'instruction ",tab_token[0].id_token);
                ecrire_erreur(chemin_fichier_erreur, message);
                tab_token[i].erreur=0;
                free(message);}
                if(tab_token[i].erreur==2){
                  sprintf(message, "%s%d%s%s%s", "ligne ", PC ," : L'erreur est dans taille de l'instruction ",tab_token[0].id_token
                  ," l'erreur est de  type syntaxique ");
                ecrire_erreur(chemin_fichier_erreur, message);
                tab_token[i].erreur=0;
                free(message);}
              }

            }
    erreur=analyse_semantique(&tab_token,chemin_fichier_erreur);
          if (erreur==1){
                  strcpy(chemin_fichier_erreur,"code/erreur.txt");

             for (int i = 0; i < taille_token; i++){
              message = (char*)malloc(100*sizeof(tab_token[i].id_token) );
              if(tab_token[i].erreur==1){
                sprintf(message, "%s%d%s%s%s", "ligne ", PC ," : L'erreur est dans le mot ",tab_token[i].id_token
                   ,". l'erreur est de type sémantique");
                ecrire_erreur(chemin_fichier_erreur, message);
                tab_token[i].erreur=0;
                free(message);
                }}

              }


              if (erreur==3){
     strcpy(chemin_fichier_erreur,"code/erreur.txt");

 for (int i = 0; i < taille_token; i++){
              message = (char*)malloc(100*sizeof(tab_token[i].id_token) );
              if(tab_token[i].erreur==1){
                printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% %s\n", tab_token[i].id_token);
                sprintf(message, "%s%d%s%s%s", "ligne ", PC ," : L'erreur est dans le mot ",tab_token[i].id_token
                    ," cette erreur est de type sémantique la variable utiliser n'est pas déclarer ");
               ecrire_erreur(chemin_fichier_erreur, message);
                  tab_token[i].erreur=0;
                free(message);}}

              }
            }
  if (erreur==2){
     strcpy(chemin_fichier_erreur,"code/erreur.txt");
 for (int i = 0; i < taille_token; i++){
              message = (char*)malloc(100*sizeof(tab_token[i].id_token) );
              if(tab_token[i].erreur==1){
                printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%s\n", tab_token[i].id_token);
                sprintf(message, "%s%d%s%s%s", "ligne ", PC ," : L'erreur est dans le mot ",tab_token[i].id_token
                    ,". Ce lexique n'appartient pas à notre langage");
               ecrire_erreur(chemin_fichier_erreur, message);
                  tab_token[i].erreur=0;
                free(message);}}

              }}
  } while(strcmp(instruction,"NULL"));
  /*------------------------------liberation---------------------------*/
  free(instruction);
  if (tab_token!=NULL)
  {
  
  for (int i = 0; i < taille_token; ++i) {free(tab_token[i].id_token);}
  free(tab_token);}
if (tabAdresse!=NULL)
{
free(tabAdresse);
}
if (strcmp(chemin_fichier_erreur,"code/erreur.txt"))
{
  free(chemin_fichier_erreur);
chemin_fichier_erreur=NULL;
}
  return chemin_fichier_erreur;}


int analyse_lexical(char* instruction,TOKEN** tab_token,char* chemin_fichier_erreur)
{
int erreur=0;
creer_tab_token(instruction,(tab_token));
for (int i = 0; i < taille_token; ++i){
if( (*tab_token)[0].type !=OPCODE_CHAINE && (*tab_token)[0].type !=ADRESS) erreur=2;
else if(i!=0 && (*tab_token)[i].erreur) erreur=1;
}
return erreur;}





void creer_tab_token(char* instruction,TOKEN** tab_token)

{
  const char *s = ", " " \n ( )";
  char chaine[100][100];
   char *token1;
   TOKEN tok1;
   int k=0,occu=0,j=0,z=0,lng=0,m=1,n=0;
  
   int *tab=malloc(20*sizeof(int));
   char* str1=malloc(strlen(instruction)*sizeof(char));
char* w=malloc(100*sizeof(char));
   strcpy(str1,instruction);
   //calcul nombre d'ocurence de ',' dans la instruction
for (int i = 0; i < strlen(instruction); ++i)
{if(instruction[i]!=' '&& instruction[i]!=',' && instruction[i]!='(' && instruction[i]!=')'){
    j++;}
if(instruction[i]==','){
  tab[occu]=j;
  occu++;}}
 token1=strtok(str1,s);
while(token1!=NULL){
  strcpy(chaine[k],token1);
  lng+=strlen(token1);
  //la au meme moment que on crée le tableau nous allons placer les ','dans le tableu aleus place exacte
        while(z<occu && lng==tab[z]){
          k++;
            strcpy(chaine[k],",");

          z++;
        }

            token1 = strtok(NULL,s);
  k++;
   }     
taille_token=k;
 *tab_token = malloc(taille_token* sizeof(**tab_token));
//la nous allons utiliser le tableau de chaine de caractere créer toute à l'heur 
 //pour fairele tableau de token et nous allons faire un teste pour chaqu'un d'eux pour
 //verifier si il sagit d'un token valide ou non

for (int i = 0; i < k; ++i)
{ m=1;
tok1.id_token=malloc(strlen(chaine[i])*sizeof(char));
    strcpy(tok1.id_token,chaine[i]);
  tok1.erreur=0;

if(!strcmp(chaine[i],"add")||!strcmp(chaine[i],"sub")||
      !strcmp(chaine[i],"mult")||!strcmp(chaine[i],"slt")||
      !strcmp(chaine[i],"bnez")||!strcmp(chaine[i],"li")||
      !strcmp(chaine[i],"ADD")||!strcmp(chaine[i],"SUB")||
      !strcmp(chaine[i],"MULT")||!strcmp(chaine[i],"SLT")||
      !strcmp(chaine[i],"LW")||!strcmp(chaine[i],"lw")||
      !strcmp(chaine[i],"SW")||!strcmp(chaine[i],"sw")||
      !strcmp(chaine[i],"BNEZ")||!strcmp(chaine[i],"LI"))
    {
          tok1.type= OPCODE_CHAINE;

    }
else if (chaine[i][0]=='R')
{
  n=0;

 while((isdigit(chaine[i][m]))&& chaine[i][m]!='\0'){ 
  w[n]=chaine[i][m];
  n++;
  m++;
}
w[n]='\0';
if(chaine[i][m]=='\0'&& (atoi(w)>=0 && atoi(w)<=64)){
  tok1.type=RED;}
else{
  tok1.type=ERREUR;
    tok1.erreur=1;
}
}
else if (!strcmp(chaine[i],","))
{
  tok1.type=SEPARATEUR;
}
else if (chaine[i][0]=='-'||isdigit(chaine[i][0]))
{

  if(chaine[i][0]=='-')
  {
   while(( isdigit(chaine[i][m]))&& chaine[i][m]!='\0'){
     m++;
  }

  if(chaine[i][m]=='\0'){
    tok1.type=IMMEDIAT;}
  else{
    tok1.type=ERREUR;
      tok1.erreur=1;
  }}
  else{
 while(( isdigit(chaine[i][m]))&& chaine[i][m]!='\0'){
     m++;
  }
  if(chaine[i][m]=='\0'){
    tok1.type=IMMEDIAT;}
  else{
    tok1.type=ERREUR;
      tok1.erreur=1;
  }

  }
}

else if (chaine[i][0]=='@')
{
n=0;
while(chaine[i][m]!='\0'&& (chaine[i][m]>=65 && chaine[i][m]<=89)
  ||(chaine[i][m]>=97 && chaine[i][m]<= 122)){
  m++;
}
if (chaine[i][m]=='\0')
{
  tok1.type=ADRESS;
  if(strcmp (chaine[0],"sw") && strcmp (chaine[0],"SW") 
    && strcmp (chaine[0],"lw") && strcmp (chaine[0],"LW")){
  
tabAdresse[tailleAdresse].adr=malloc(strlen(chaine[i])*sizeof(char));
strcpy(tabAdresse[tailleAdresse].adr,chaine[i]);
tabAdresse[tailleAdresse].entier=atoi(chaine[i+1]);
tailleAdresse++;
}}



else{
  tok1.type=ERREUR;
    tok1.erreur=1;
}


}
else if (!strcmp(chaine[i],"="))
{

  tok1.type=AFFECTE;
}
else{

    tok1.type=ERREUR;
    tok1.erreur=1;


}
(*tab_token)[i]=tok1;
}

free(str1);
free(w);
}



int analyse_syntaxique(TOKEN** tab_token,char* chemin_fichier_erreur)
{
int erreur=0;

if((*tab_token)[0].type== OPCODE_CHAINE && (!strcmp((*tab_token)[0].id_token,"add")||!strcmp((*tab_token)[0].id_token,"ADD")||
    !strcmp((*tab_token)[0].id_token,"mult")||!strcmp((*tab_token)[0].id_token,"MULT")||
    !strcmp((*tab_token)[0].id_token,"slt")
    ||!strcmp((*tab_token)[0].id_token,"SLT")))
  
      {
          erreur=analyse_ADD_MULT_SLT( tab_token);
           }

if((*tab_token)[0].type== OPCODE_CHAINE && (!strcmp((*tab_token)[0].id_token,"li")||!strcmp((*tab_token)[0].id_token,"LI")||
    !strcmp((*tab_token)[0].id_token,"bnez")
    ||!strcmp((*tab_token)[0].id_token,"BNEZ")))
{
erreur= analyse_LI_BNEZ( tab_token);
  }
  if((*tab_token)[0].type== OPCODE_CHAINE 
    &&(!strcmp((*tab_token)[0].id_token,"lw")
      ||!strcmp((*tab_token)[0].id_token,"LW")))
  {
        erreur=analyse_LW(tab_token);
  }
if ((*tab_token)[0].type== OPCODE_CHAINE && (!strcmp((*tab_token)[0].id_token,"sw")
    |!strcmp((*tab_token)[0].id_token,"SW")))
{

      erreur=analyse_SW(tab_token);
}
  if ((*tab_token)[0].type==ADRESS)
  {
    erreur=analyse_adress(tab_token);
  }


return erreur;}


int analyse_semantique(TOKEN** tab_token,char* chemin_fichier_erreur)
{
  int erreur=0;
  if(!strcmp((*tab_token)[0].id_token,"add")||!strcmp((*tab_token)[0].id_token,"ADD")||
    !strcmp((*tab_token)[0].id_token,"mult")||!strcmp((*tab_token)[0].id_token,"MULT")||
    !strcmp((*tab_token)[0].id_token,"slt")||!strcmp((*tab_token)[0].id_token,"SLT")||
    !strcmp((*tab_token)[0].id_token,"li")||!strcmp((*tab_token)[0].id_token,"LI")||
    !strcmp((*tab_token)[0].id_token,"lw")||!strcmp((*tab_token)[0].id_token,"LW")){

   if(Verifier_Reg_Zero(&(*tab_token)[1])==1) erreur=1;
  if(!strcmp((*tab_token)[0].id_token,"li")||!strcmp((*tab_token)[0].id_token,"LI")){
    if (Verifier_contenu_reg(&(*tab_token)[3])) erreur=1;
  }
  }


   if (((*tab_token)[0].type==ADRESS))
  {
   if(Verifier_add_quatre(&(*tab_token)[2]))erreur=1;
  }
 else  if(!strcmp((*tab_token)[0].id_token,"sw")||!strcmp((*tab_token)[0].id_token,"SW"))
  { erreur=Verifier_add_quatre(&(*tab_token)[1]);
  	printf("yyyyyyyyyyyyyyyyyyyyyy %d \n",erreur );
  }
  else  if(!strcmp((*tab_token)[0].id_token,"lw")||!strcmp((*tab_token)[0].id_token,"LW"))
  { erreur=Verifier_add_quatre(&(*tab_token)[3]);
}
  else if(!strcmp((*tab_token)[0].id_token,"bnez")||!strcmp((*tab_token)[0].id_token,"BNEZ"))
  {
    if(Verifier_saut_quatre(&(*tab_token)[3])==1) erreur=1;
  }

return erreur;}

int analyse_adress(TOKEN** tab_token){
  
  int i,erreur=0;
  if(taille_token ==3){
  
  if((*tab_token)[1].type!=AFFECTE) {
    (*tab_token)[1].erreur=1;
    erreur=1;
  }
  if((*tab_token)[2].type!=IMMEDIAT) {
    (*tab_token)[2].erreur=1;
    erreur=1;
  }}
  else
{
	erreur=1;(*tab_token)[0].erreur=2;
}
return erreur;
}
int analyse_SW(TOKEN** tab_token){
  int erreur=0;

  if(taille_token == 5) {

  if((*tab_token)[1].type!=ADRESS){ 
    erreur=1;
    (*tab_token)[1].erreur=1;
  }

  if((*tab_token)[2].type!=RED){    
    erreur=1;
    (*tab_token)[2].erreur=1;
  }

  if((*tab_token)[3].type!=SEPARATEUR){ 
    erreur=1;
    (*tab_token)[3].erreur=1;
  }

  if((*tab_token)[4].type!=RED){    
    erreur=1;
    (*tab_token)[4].erreur=1;
  }
  }
  else{
  	erreur=1;
    (*tab_token)[0].erreur=2;

  }
  return erreur;
}

int analyse_LW(TOKEN** tab_token){
  int erreur=0;
  if(taille_token ==5) {
    
 if((*tab_token)[1].type!=RED){
    erreur=1;
    (*tab_token)[1].erreur=1;
  }

  if((*tab_token)[2].type!=SEPARATEUR){
    erreur=1;
    (*tab_token)[2].erreur=1;
  }

  if((*tab_token)[3].type!=ADRESS){
    erreur=1;
    (*tab_token)[3].erreur=1;
  }

  if((*tab_token)[4].type!=RED){
    erreur=1;
    (*tab_token)[4].erreur=1;
  }}
  else{
  	erreur=1;
    (*tab_token)[0].erreur=2;
  }
  return erreur;
}

int analyse_LI_BNEZ(TOKEN** tab_token){
  int erreur=0;
  
  if(taille_token ==4) {
  if((*tab_token)[1].type!=RED){
    erreur=1;
    (*tab_token)[1].erreur=1;
  }
  
  if((*tab_token)[2].type!=SEPARATEUR){
    erreur=1;
    (*tab_token)[2].erreur=1;
  }
  
  if((*tab_token)[3].type!=IMMEDIAT){
    erreur=1;
    (*tab_token)[3].erreur=1;
  }}
  else{
  	erreur=1;
    (*tab_token)[0].erreur=2;
  }
  return erreur;
}

int analyse_ADD_MULT_SLT(TOKEN** tab_token)

{
  int erreur=0;
if(taille_token==6){
  for (int i =1; i < taille_token; ++i)
  { 
  if(i==1 && (*tab_token)[i].type!=RED )
  {
    (*tab_token)[i].erreur=1;
    erreur=1;
  }
if(i==2 && (*tab_token)[i].type!=SEPARATEUR )
  {
    (*tab_token)[i].erreur=1;
    erreur=1;
  }
  if(i==3 && (*tab_token)[i].type!=RED )
  {
    (*tab_token)[i].erreur=1;
    erreur=1;
  }
  if(i==4 && (*tab_token)[i].type!=SEPARATEUR )
  {
    (*tab_token)[i].erreur=1;
    erreur=1;
  }
  if(i==5 && (*tab_token)[i].type!=RED )
  {
    (*tab_token)[i].erreur=1;
    erreur=1;
  }
}
}
else {erreur=1;(*tab_token)[0].erreur=2;}

return erreur;}

int Verifier_contenu_reg(TOKEN* elt_tab_reg){
  if (elt_tab_reg->type==IMMEDIAT){
    if (atof(elt_tab_reg->id_token)>(pow(2,32)-1)){
      elt_tab_reg->erreur=1;
        return 1;
    }}
return 0;}




int Verifier_add_quatre(TOKEN* elt_tab_add){
  int erreur=0;
    if (elt_tab_add->type == IMMEDIAT ){
      if ((atoi(elt_tab_add->id_token)%4)){
        elt_tab_add->erreur=1;
        erreur=1;
      }
    }

    else if (elt_tab_add->type == ADRESS ){
    	erreur=3;
    	elt_tab_add->erreur=1;
    	for (int i = 0; i < tailleAdresse; ++i)
    	{
    		if (!strcmp(tabAdresse[i].adr,elt_tab_add->id_token))
    		{
    			erreur=0;
    			elt_tab_add->erreur=0;
    		}
    	}


    }
    return erreur;
}




int Verifier_Reg_Zero(TOKEN* elt_tab_un){

  if (elt_tab_un->type == RED){
       if (!strcmp(elt_tab_un->id_token,"R0")||!strcmp(elt_tab_un->id_token,"r0")){
        elt_tab_un->erreur=1;
        return 1;}}

return 0;
}

int Verifier_saut_quatre(TOKEN* elt_tab_deux){
  if (elt_tab_deux->type == IMMEDIAT ){
    if ((atoi(elt_tab_deux->id_token)%4)){
      elt_tab_deux->erreur=1;
        return 1;}}
return 0;}

