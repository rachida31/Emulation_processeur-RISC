/*==========================================================================
* La fonction principale la l'unité de calcul, elle prend un char* en 
* paramètre qui est l'opcode, et deux entiers elle reterne un entier 
* qui est le résultat du calcul.
============================================================================*/
int calcule_arithmetique_logique (char* opcode ,int  op1,int  op2);





/*===========================================================================
* cette fonction prend deux entiers en paramètre et fait une addition 
* entre les deux et nous envoie le résultat dans un entier.
=============================================================================*/
int  ADD(int  op1,int  op2);




/*===========================================================================
* cette fonction prend deux entiers en paramètre et fait une 
* multiplication entre les deux et nous envoie le résultat dans 
* un entier.
=============================================================================*/
int MULT(int  op1,int  op2);



/*============================================================================
* cette fonction prend deux entiers en paramètre et fait une comparaison 
* entre les deux et nous envoie "1" si op1<op2 et "0" sinon.
==============================================================================*/
int SLT(int  op1,int  op2);




/*============================================================================
* cette fonction prend deux entiers en paramètre.si res=0 elle return un 0
* sinon elle returne saut/4. 
==============================================================================*/
int BNEZ(int  res, int saut);

/*============================================================================ 
* cette fonction calcule sois l'adresse si c'est un SW,sois la somme d'un
* contenu de l'adresse avec l'offset. prend deux entiers en paramètre et fait 
* une addition entre les deux et nous envoie le résultat dans un entier.
==============================================================================*/
int LW_SW(int offset,int  ref );
