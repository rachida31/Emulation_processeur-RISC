

/*==================================================================================
* La fonction principale qui permet de faire l'analyse du code instruction par 
* instruction, il prend un char* en paramètre et retourne le chemin du fichier 
* où nous allons écrire les erreurs pour l'interface grafique.
*====================================================================================*/
char* analyse_code(char* chemin_fichier_code );



/*==================================================================================
* la fonction analyse lexical prend une l'instruction en paramètre, un pointeur sur 
* un tableau de token pour pouvoir le modifier au besoin, et un chemin de fichier
* ou écrire les erreurs s'il y en a. Elle retourne "1" s'il y a une erreur lexical 
* et "0" sinon.
*====================================================================================*/
int analyse_lexical(char* instruction,TOKEN** tab_token,char* chemin_fichier_erreur);






/*==================================================================================
* Cette procédure prend l'instruction et la devise en token et le met dans le tableau
* de token passé en paramètre.
*====================================================================================*/
void creer_tab_token(char* instruction,TOKEN** tab_token);
	




/*==================================================================================
* cette fonction analyse la syntaxe de chaque instruction, elle prend un pointeur 
* sur un tableau de token et un chemin de fichier pour pouvoir écrire les erreurs.
* Elle retourne "1" s'il y a une erreur syntaxe et "0" sinon.
*====================================================================================*/
int analyse_syntaxique(TOKEN** tab_token,char* chemin_fichier_erreur);





/*==================================================================================
** cette fonction analyse la sémentique de chaque instruction, elle prend un pointeur 
* sur un tableau de token et un chemin de fichier pour pouvoir écrire les erreurs.
* Elle retourne "1" s'il y a une erreur sémentique et "0" sinon.
*====================================================================================*/	
int analyse_semantique(TOKEN** tab_token,char* chemin_fichier_erreur);



/*==================================================================================
* cette fonction analyse la syntaxe de la déclaration d'adresse (exemple @x=1000). elle 
* Prends un pointeur sur un élément du tableau de token.
* Elle retourne "1" s'il y a une erreur dans la syntaxe de l'adresse et "0" sinon.
*====================================================================================*/
int analyse_adress(TOKEN** tab_token);
	



/*==================================================================================
* cette fonction analyse la syntaxe de l'instruction SW. elle 
* Prends un pointeur sur un élément du tableau de token.
* Elle retourne "1" s'il y a une erreur dans la syntaxe de l'instruction et "0" sinon.
*====================================================================================*/
int analyse_SW(TOKEN** tab_token);
	



/*==================================================================================
** cette fonction analyse la syntaxe de l'instruction LW. elle 
* Prends un pointeur sur un élément du tableau de token.
* Elle retourne "1" s'il y a une erreur dans la syntaxe de l'instruction et "0" sinon.
*====================================================================================*/
int analyse_LW(TOKEN** tab_token);




/*==================================================================================
* cette fonction analyse la syntaxe des instructions LI et BNEZ. elle 
* Prends un pointeur sur un élément du tableau de token.
* Elle retourne "1" s'il y a une erreur dans la syntaxe de l'instruction et "0" sinon.
*====================================================================================*/
int analyse_LI_BNEZ(TOKEN** tab_token);





/*==================================================================================
* cette fonction analyse la syntaxe des instructions ADD,MUTL et SLT. elle 
* Prends un pointeur sur un élément du tableau de token.
* Elle retourne "1" s'il y a une erreur dans la syntaxe de l'instruction et "0" sinon.
*====================================================================================*/
int analyse_ADD_MULT_SLT(TOKEN** tab_token);



/*==================================================================================
* cette fonction vérifie si le contenu des registres ne dépasse pas 2^32-1, elle prend 
* un pointeur sur un élément du tableau de token et elle retourne "1" s'il cet 
* élément qui est un registre dépasse la valeur maximale autorisée et "0" sinon.
*====================================================================================*/
int Verifier_contenu_reg(TOKEN* elt_tab_reg);





/*==================================================================================
* cette fonction vérifie si le registre zéro n'est pas à modifier, elle prend un pointeur 
* Sur un élément du tableau de token et elle retourne "1" s'il cet élément est dans un 
* emplacement pour qu'il soit modier et "0" sinon.
*====================================================================================*/	
int Verifier_Reg_Zero(TOKEN* elt_tab_un);



/*==================================================================================
* cette fonction vérifie si l'adresse est un multiple de 4, elle prend un pointeur 
* Sur un élément du tableau de token et elle retourne "1" s'il cet élément n'est pas
* multiple de 4 et "0" sinon.
*====================================================================================*/
int Verifier_add_quatre(TOKEN* elt_tab_add);
	



/*==================================================================================
* cette fonction vérifie si le saut est un multiple de 4, elle prend un pointeur 
* Sur un élément du tableau de token et elle retourne "1" s'il cet élément n'est pas
* multiple de 4 et "0" sinon.
*====================================================================================*/
int Verifier_saut_quatre(TOKEN* elt_tab_deux);