


/** ** * Ce fichier contient les differents prototypes de l'interface graphique ******* */

/**

 * =============================================================================
 * cette fonction affiche la première fenetre qui permet à l'utilisateur de choisir
 * entre saisir le code ou ouvrir un fichier deja existant en memoire; elle prend 
 * comme parametres un entier qui represente le nombre d'arguments de la ligne de 
 * commande et un tableau de chaine de caracteres qui correspond aux arguments
 * de la ligne de commande, et elle renvoie rien.
 * =============================================================================
 */



void Affichage_principale (int argc, char **argv);

/**
 * =============================================================================
 * cette fonction permet d'afficher l'editeur de texte et permettra a l'utilisateur
 * d'écrire son programme.
 * =============================================================================
 */
void Saisir_code(char *chemin_fichier);




/**
* =============================================================================
 * cette fonction permet la recherche du fichier, elle renvoie le chemin du fichier. 
 * =============================================================================
*/
//void charger_code(GtkWidget* button, GtkWidget *file_selection);
void charger_code(const gchar *file_name, GtkTextView *p_text_view);


 /** 
 * =============================================================================
 * cette fonction permet d'afficher le code dans l'editeur, elle prend en parametre
 * une chaine de caractere qui correspond au chemin du fichier, et renvoie un void. 
 * =============================================================================
 *///void Affiche_code (char* chemin_fichier);
void Affiche_code (GtkWidget *p_widget, gpointer user_data);



/**
 * =============================================================================
 * cette fonction va afficher les différentes erreurs qui se trouvent dans le code 
 * elle renvoie un void et prend en parametre une liste d'erreurs.
 * =============================================================================
 */void Affiche_Erreur (char* chemin_fichier);




/**
 * =============================================================================
 * cette fonction permet de choisir le mode d'exécution qui prend le chemin du
 * fichier contenant le code et le renvoie à l'ordonnanceur, elle retourne un void 
 * =============================================================================
 */
void choix_execution (char* chemin_fichier);





/**
 * =============================================================================
 * cette fonction permet d'afficher le nombre de cycles et le résultat d'exécution,
 * elle prend en paramètre une structure de données qui correspond aux résultats 
 * à affichés, elle renvoie un void.
 * =============================================================================
 */
void Affiche_Resultat(int resultat);



/**
 * =============================================================================
 * cette fonction vérifie si le code est sauvegardé avant de quitter 
 * =============================================================================
 */
void quitter(GtkWidget *p_widget, gpointer user_data);

/**
 * =============================================================================
 * cette fonction vérifie si le code est sauvegardé avant l'analyse 
 * =============================================================================
 */
void verifier1(GtkWidget *p_widget, gpointer user_data);


/**
 * =============================================================================
 * cette fonction permet la modification du code dans le cas d'erreur dans le 
 * programme
 * =============================================================================
 */
void modifie (GtkWidget *p_widget, gpointer user_data);

/**
 * =============================================================================
 * cette fonction ouvre une fenêtre dialoguée pour choisir le nom du fichier et 
 * choisir le répertoire ou sauvegarder ce fichier
 * =============================================================================
 */
void save1 (GtkWidget *p_widget, gpointer user_data);