/**
  * =============================================================================
	Dans ce modul on a défini une structure de données pour les opérations
	de chargement en mémoire « LW » et de rangement en mémoire « SW ».
	Cette structure sera utilisée dans l’étage de décodage au sein de l’ordonnanceur,
	
 * =============================================================================
 */
 
 
/**

 * =============================================================================
	
	Procedure init_tabreg():

	• Utilisation : Cette procédure permet d'initialiser le tableau de registres 
	et celui de la mémoire.	
 * =============================================================================
 */
void init_tabreg();

 
/**

 * =============================================================================
	
	Fonction charger_instruction():

	• Paramètres : le chemin du fichier contenant le code qui est de type char*.
	• Utilisation : cette fonction lit l’instruction du code en faisant appel à la
	fonction de lecture du module gestionnaire d’entrée sortie et elle sera également
	appelée par les deux fonctions globales de l’ordonnanceur à savoir la fonction
	”séquentiel” et la fonction ”pipeline”.
	• Type de retour : cette fonction renvoie un char* qui est l’instruction lue.
 * =============================================================================
 */
 
char* charger_instruction(char* chemin_fichier);

/**
 * =============================================================================
	
	Fonction decodage :
	
	• Paramètres : l’instruction du code qui a été déjà lue et est de type char*.
	• Utilisation : cette fonction vérifie quelle opération sera faite par l’instruction
	à savoir une addition, branchement, accès mémoire. . . et suivant l’opération elle
	renvoie la structure adéquate pour le décodage autrement dit pour
	la sauvegarde des différentes parties de l’instruction dans la structure correspondante. 
	Cette fonction sera également appelée par les deux fonctions
	globales de l’ordonnanceur à savoir la fonction ”sequentiel” et la fonction
	”pipeline”
	• Type de retour : cette
 * =============================================================================
 */
 void* decodage(char* instruction);
 
 /**
 * =============================================================================
	
	Fontction execution:

	• Paramètres : la structure utilisée à l'étage de décodage .
	• Utilisation : cette fonction fait appel à la fonction de l’unité de calcul qui
	est « calcul arithmitique logique » pour avoir le résultat du calcul pour les
	différentes opérations selon l’opcode qui lui sera fourni par l’ordonnanceur.
	Cette fonction sera également appelée par les deux fonctions globales de
	l’ordonnanceur à savoir la fonction ”séequentiel” et la fonction ”pipeline”.
	• Type de retour : cette fonction renvoie un entier qui sera le résultat de calcul
	effectuée au niveau de l’unité de calcul.
 * =============================================================================
 */
 int execution(void* structure);
 
  /**
 * =============================================================================

	
	 Procédure Store : 

	• Paramètres : Un « int adresse » : qui représente l’adresse à laquelle nous
	voulons écrire et cette dernière sera calculée par le module ”unité de calcul”
	• « int val » : qui représente la valeur que nous voulons mettre dans l’adresse

	• Utilisation : cette procédure nous permet d’écrire une adresse dans un tableau
	elle sera également appelée par les deux fonctions globales de l’ordonnanceur
	à savoir la fonction ”séquentiel” et la fonction ”pipeline”


 * =============================================================================
 */
 void procedure_store(int adresse, int val);
 
  /**
 * =============================================================================

	Fonction load :

	Paramètres : « int adresse » : qui représente l’adresse ou nous voulons lire
	et celle ci sera calculée au niveau du module unité de calcul. .
	• Utilisation : lire une adresse qui se trouve dans un tableau.
	• Type de retour : cette fonction renvoie un entier qui correspond à la valeur
	lue dans l’adresse passée en paramètre.

 * ============================================================================= 
 */
 
 int fonction_load(int adresse);
 
   /**
 * =============================================================================

	Au niveau du cinquième et dernier étage qui est celui de l’écriture dans un
	registre (WB) nous aurons besoin de cette procédure :
	• Paramètres : Un registre de type registre dans lequel nous aurons un entier
	qui représente le résultat qui sera lui aussi passé en paramètre .
	• Utilisation : cette fonction nous permet d’écrire un résultat dans un registe
	elle sera également appelée par les deux fonctions globales de l’ordonnanceur
	à savoir la fonction ”séquentiel” et la fonction ”pipeline”

 * ============================================================================= 
 */
 
 void procedure_wb(int resultat,REGISTRE Reg);
 
    /**
 * =============================================================================

	Fonction sequentiel :
	elle est appelée par la procedure ”choix execution” qui se trouve dans le
	module ”interface graphique” dans le cas ou il a choisi le mode séquentiel.
	• Paramètres : chemin du fichier contenant le code qui est de type char*.
	
	• Utilisation : Cette fonction effectue l’ordonnancement séquentiel de l’instruction
	lue du code. Elle fait appel à la fonction lecture instruction(char* chemin fichier)
	de l’étage lecture (IF), la fonction decodage(char* instruction) de
	l’étage décodage (ID), execution(void* structure) de l’étage exécution (EX),
	procedure store (char* chemin, int adresse, int val) ou procedure load (char*
	chemin, int adresse ) de l’étage accès mémoire (MEM) et procedure WB (int
	resultat, Registre Reg) de l’étage écriture en registre (WB).
	
	• Type de retour :Un entier qui représente le nombre de cycles lié à un ordonnancement
	séquentiel des instructions du code.

 * ============================================================================= 
 */
 int sequentiel( char* chemin_fichier);
 
     /**
 * =============================================================================

	Fonction nb_cycl_sequentiel :
	
	• Paramètres : elle prend un char* qui représente l’opcode .
	• Utilisation : cette fonction nous sert à calculer le nombre de cycle en mode
	séquentiel à chaque exéecution d’une nouvelle instruction et nous permet ainsi
	de modifier la variable globale ”nb cycle” elle sera appelée par la fonction
	”sequentiel” qui est dans le module ordonnanceur.
	• Type de retour :cette fonction renvoie un entier

 * ============================================================================= 
 */
 
 int nb_cycle_sequentiel(char* opcode);
 
 
      /**
 * =============================================================================

	Fonction pipeline :
	
	• Paramètres : le chemin du fichier contenant le code qui est de type char*.
	
	• Utilisation : Dans cette fonction nous avons besoin de manipuler des processus
	qui représenteront les instructions du code . 
	La première étape que fait cette fonction est la lecture d’une
	instruction et c’est pour cela que nous faisons appel à la fonction charger_instruction
	(char* chemin fichier). Après avoir chargé l'instruction, nous créons un processus
	et c’est pour cela que nous faisons appel à la fonction :”creation processus”.
	
	Cette fonction fait appel à la fonction ”verification”, si nous ne trouvons pas
	des dépendances de données entre les registres nous faisons appel ”decodage (char* instruction)”
	définie précédemment, elle appelle aussi la fonction
	”load” s’il s’agit d’une lecture en mémoire, et la procédure ”store” s’il s’agit
	d’une écriture, et à la fin elle appelle la fonction ”write back”. elle nous permet
	également de calculer le nombre de cycles, tout en modifiant la variable
	globale ”NB Cycle”.
	
	• Type de retour : cette fonction renvoie le resultat d’exécution.


 * ============================================================================= 
 */
 
 int pipeline(char* chemin_fichier);
 
       /**
  * =============================================================================

	Fonction creation_processus :
	
	C’est la fonction qui permet de créer les processus necessaire à l’execution
	en mode pipeline :
	• prend en paramètre le chemin du fichier contenant le code qui est de type char*.
	• Utilisation : Cette fonction permettra de créer à chaque fois un processus
	pour chaque instruction lue du code à partir du fichier.
	• Type de retour :renvoie un processus qui représente une instruction du code
	et qui est de type Pidt
.


 * ============================================================================= 
 */
 
 pid_t creation_processus(char* chemin_fichier);
 
        /**
  * =============================================================================

		paramètres: deux registres de type char* et la structure utilisée à l'étage de décodage
	utilisation: cette fonction permet de vérifier s'il ya des pénalités lors de l'éxecution en mode pipline
                 et si c'est le cas nous retourne le nombre de ces pénalité  trouvé suite à un conflit
	
	

 * ============================================================================= 
 */
 
 int verification (char* nomreg1, char* nomreg2,void* structure,char* chemin_fichier);
 
        /**
  * =============================================================================

	Fonction suspendre_processus :
	
	• Paramètres : chemin du fichier contenant les instructions du code.
	• Utilisation : Cette fonction se charge de suspendre un processus.

 * ============================================================================= 
 */
 
 void suspendre_processus(char* chemin_fichier);
 /**
 * =============================================================================

	Fonction pipeline1 :
	
	• Paramètres : le chemin du fichier contenant le code qui est de type char*.
	
	• Utilisation : Dans cette fonction nous avons besoin de manipuler des processus
	qui représenteront les instructions du code . 
	La première étape que fait cette fonction est la lecture d’une
	instruction et c’est pour cela que nous faisons appel à la fonction charger_instruction
	(char* chemin fichier). 
	Cette fonction fait appel à la fonction ”verification”, si nous ne trouvons pas
	des dépendances de données entre les registres nous faisons appel ”decodage (char* instruction)”
	définie précédemment, elle appelle aussi la fonction
	”load” s’il s’agit d’une lecture en mémoire, et la procédure ”store” s’il s’agit
	d’une écriture, et à la fin elle appelle la fonction ”write back”. elle nous permet
	également de calculer le nombre de cycles, tout en modifiant la variable
	globale ”NB Cycle”.
	
	• Type de retour : cette fonction renvoie le resultat d’exécution.

 * ============================================================================= 
 */
 
int pipeline1(char* chemin_fichier);
