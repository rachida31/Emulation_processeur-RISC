#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include "../inc/mes_types.h"
#include "../inc/gestionnaire_entree_sortie.h"
#include "../inc/ordonnanceur.h"
#include "../inc/analyseur.h"
#include "../inc/interface_graphique.h"
gpointer *view1;
GtkWidget *p_window;
int actif=0;
GtkWindow *p_main_window;
gchar *chemin=NULL;
gboolean save;
static GtkWidget *view;
int   choix_mode;
void quitter(GtkWidget *p_widget, gpointer user_data)
{ 
  if (actif)
  {
  /* Avant de fermer, il faut verifier qu'un document a bien ete ouvert */
  if (actif)
  {
    if (!save)
    {
      GtkWidget *p_dialog = NULL;
      GtkWidget *p_label = NULL;

      p_dialog = gtk_dialog_new_with_buttons ("sauvegarder",
                                              p_main_window,
                                              GTK_DIALOG_MODAL,
                                              GTK_STOCK_YES, GTK_RESPONSE_YES,
                                              GTK_STOCK_NO, GTK_RESPONSE_NO,
                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

      
      p_label = gtk_label_new ("Voulez-vous sauvegarder les modifications ?");
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG (p_dialog)->vbox), p_label, TRUE, TRUE, 0);
      gtk_widget_show_all (GTK_DIALOG (p_dialog)->vbox);
      switch (gtk_dialog_run (GTK_DIALOG (p_dialog)))
      {
        case GTK_RESPONSE_YES:
          save1 (p_widget, user_data);
        break;
        case GTK_RESPONSE_NO:
        break;
        case GTK_RESPONSE_CANCEL:
          gtk_widget_destroy (p_dialog);
          return;
        break;
      }
      gtk_widget_destroy (p_dialog);
    }
    {
      GtkTextIter start;
      GtkTextIter end;
      GtkTextBuffer *p_text_buffer = NULL;

      p_text_buffer = gtk_text_view_get_buffer (view1);
      gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
      gtk_text_buffer_delete (p_text_buffer, &start, &end);
      gtk_widget_set_sensitive (GTK_WIDGET (view1), FALSE);
      g_free (chemin), chemin = NULL;
     view1 = NULL;
       actif = 0;
    }
  }
  (void)p_widget;
  (void)user_data;  }
  if (!actif)
  {
    gtk_main_quit();
  }
}
void verifier1(GtkWidget *p_widget, gpointer user_data) 
{
    /* Avant de verifier, il faut verifier qu'un document a bien ete ouvert et sauvgarder */

if (actif)
  {
    if (save)
    {
        char  *chemin_erreur=analyse_code(chemin);
  
       if (chemin_erreur!=NULL)
         {
          Affiche_Erreur(chemin_erreur);
         }
         else{
          choix_execution(chemin);
         }
  }}
  
  /* Avant de verifier, il faut verifier qu'un document a bien ete ouvert et sauvgarder */
  if (actif)
  {
    if (!save)
    {
      GtkWidget *p_dialog = NULL;
      GtkWidget *p_label = NULL;
     /*fenètre dialogue pour selectionner le repertoire ou sauvegarder le fichier*/

      p_dialog = gtk_dialog_new_with_buttons ("sauvegarder",
                                              p_main_window,
                                              GTK_DIALOG_MODAL,
                                              GTK_STOCK_YES, GTK_RESPONSE_YES,
                                                 GTK_STOCK_NO, GTK_RESPONSE_NO,
                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                               NULL);
      p_label = gtk_label_new ("Vous devez sauvegarder avant de vérifier !");
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG (p_dialog)->vbox), p_label, TRUE, TRUE, 0);
      gtk_widget_show_all (GTK_DIALOG (p_dialog)->vbox);
      switch (gtk_dialog_run (GTK_DIALOG (p_dialog)))
      {
        case GTK_RESPONSE_YES:
          save1 (p_widget, user_data);
        break;
         case GTK_RESPONSE_NO:
        break;
        case GTK_RESPONSE_CANCEL:
          gtk_widget_destroy (p_dialog);
          return;
        break;
      }
      gtk_widget_destroy (p_dialog);
    }}

  (void)p_widget;
  (void)user_data;  }
  



  
void modifie (GtkWidget *p_widget, gpointer user_data)
{ 
  if (actif)
  {
    save = FALSE;
  }

  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

static GtkWidget *text_view;
void Saisir_code(char *chemin_fichier)
{
    quitter(p_window,view1);

  GtkWidget *window;
  GtkWidget *main_box;
  GtkWidget *vbox;
  GtkWidget *fixed;
  GtkWidget *retour;
  GtkWidget *scrolled_window;
  GtkTextBuffer *buffer;
  GtkTextIter start, end;
  GtkTextIter iter;
  char* text;

  gtk_init(0, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1200, 640);
  gtk_window_set_title(GTK_WINDOW(window), "RISC-Emulator");
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (quitter), NULL);

  main_box=gtk_vbox_new(FALSE, 0);
  gtk_container_add( GTK_CONTAINER(window), main_box);

 

  scrolled_window = gtk_scrolled_window_new( NULL, NULL); //Ajout de la capacité a pouvoir faire défiler
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);

      if (actif)
  {
quitter(NULL,view);

  }
  

/* la nous allons initialiser les variables, par la suite on modifiera leurs valeurs*/
  actif =1;
  chemin = NULL;
  save = FALSE;

  view = gtk_text_view_new();
      view1=view;
  gtk_widget_set_sensitive (GTK_WIDGET (view1), TRUE);

  gtk_container_add( GTK_CONTAINER( scrolled_window), view);
  buffer = gtk_text_view_get_buffer(view);
  gtk_text_buffer_get_start_iter(buffer,&start);
  gtk_text_buffer_get_end_iter(buffer,&end);
  text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

  gtk_text_view_set_left_margin(view,10);
gtk_label_set_line_wrap_mode (view,PANGO_WRAP_WORD_CHAR);
  PangoFontDescription *font1 = pango_font_description_from_string("Sans, Bold, 12"); //Format de l'ecriture
    gtk_widget_modify_font(view, font1);

  vbox = gtk_hbutton_box_new();
  gtk_box_pack_start (GTK_BOX (main_box), vbox, FALSE, FALSE, 0);

 GtkTextBuffer *p_text_buffer = NULL;

  p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    g_signal_connect (G_OBJECT (p_text_buffer), "changed", G_CALLBACK (modifie), NULL);
  
 {  /* création du button pour lancer l'analyse du code*/

 
 GtkWidget *verifier;
  verifier = gtk_button_new_from_stock ("Vérifier");//création du buton pour lancer l'analyse du code
            g_signal_connect(G_OBJECT(verifier), "clicked",G_CALLBACK(verifier1), view);
  
     gtk_box_pack_start(GTK_BOX (vbox), verifier,FALSE, FALSE, 0); }
 {
 /*Creation du button "Enregitrer sous"*/
 
 GtkWidget *enregistrer;
 
    enregistrer = gtk_button_new_from_stock ("Enregistrer sous");
    g_signal_connect (G_OBJECT (enregistrer), "clicked", G_CALLBACK (save1), NULL);
    gtk_box_pack_start (GTK_BOX (vbox), enregistrer, FALSE, FALSE, 0);
  }

  {
     GtkWidget *retour;

   retour =gtk_button_new_from_stock ("_Retour");
           g_signal_connect(G_OBJECT(retour), "clicked",G_CALLBACK(Affichage_principale), NULL);

   gtk_box_pack_start(GTK_BOX(vbox),retour,FALSE, FALSE, 0);
 
 }

 {
       GtkWidget *quitter1;

  quitter1 =gtk_button_new_from_stock ("Quitter");//création du buton pour quitter le programme
      g_signal_connect(G_OBJECT(quitter1), "clicked",G_CALLBACK(quitter),NULL);
  
    gtk_box_pack_start(GTK_BOX (vbox), quitter1,FALSE, FALSE, 0);
  
    }
  gtk_widget_show_all(window);

  gtk_main();

}


/************************************************************************/



/********************************************/
void Affiche_code (GtkWidget *p_widget, gpointer user_data)
{
    quitter(p_window,view1);
  gtk_init(0,NULL);
  GtkWidget *main_box;
  GtkWidget *vbox;
  GtkWidget *window;
  GtkWidget *scrolled_window;
  GtkWidget *quitter1;
  GtkWidget *verifier;
    GtkWidget *enregistrer;

  GtkWidget *retour;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1200, 640);
  gtk_window_set_title(GTK_WINDOW(window), "RISC-Emulator"); //Création de la fenêtre 
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (quitter), NULL);
  p_main_window = GTK_WINDOW (window);

  main_box=gtk_vbox_new(FALSE, 0);
  gtk_container_add( GTK_CONTAINER(window), main_box);

  scrolled_window = gtk_scrolled_window_new( NULL, NULL); //Ajout de la capacité a pouvoir faire défiler
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);
  view = gtk_text_view_new();
    view1=view;

GtkTextBuffer *p_text_buffer = NULL;

  p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    g_signal_connect (G_OBJECT (p_text_buffer), "changed", G_CALLBACK (modifie), NULL);
  
  gtk_container_add( GTK_CONTAINER( scrolled_window), view);
  
  PangoFontDescription *font1 = pango_font_description_from_string("Sans, Bold, 12"); //Format de l'ecriture du code 
  gtk_widget_modify_font(view, font1);
 
  vbox = gtk_hbutton_box_new();
  gtk_box_pack_start (GTK_BOX (main_box), vbox, FALSE, FALSE, 0);

  
GtkWidget *p_dialog = NULL;
  p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    charger_code (file_name, GTK_TEXT_VIEW (view1));
    g_free (file_name), file_name = NULL;
  }
  gtk_widget_destroy (p_dialog);

   {
    verifier = gtk_button_new_from_stock ("Vérifier");//création du buton pour lancer l'analyse du code
            g_signal_connect(G_OBJECT(verifier), "clicked",G_CALLBACK(verifier1), view);
  
     gtk_box_pack_start(GTK_BOX (vbox), verifier,FALSE, FALSE, 0);}

      /* Creation du bouton "Sauvegarder" */
  {
    GtkWidget *p_button = NULL;

    p_button = gtk_button_new_from_stock ("Enregistrer sous");
    g_signal_connect (G_OBJECT (p_button), "clicked", G_CALLBACK (save1), NULL);
    gtk_box_pack_start (GTK_BOX (vbox), p_button, FALSE, FALSE, 0);
  }
   /*Creation du button "Retour"*/

{
   retour =gtk_button_new_from_stock ("_Retour");
           g_signal_connect(G_OBJECT(retour), "clicked",G_CALLBACK(Affichage_principale), NULL);

   gtk_box_pack_start(GTK_BOX(vbox),retour,FALSE, FALSE, 0);
 
 }

   /*Creation du button "Quitter"*/

  { quitter1 =gtk_button_new_from_stock ("Quitter");//création du buton pour quitter le programme
      g_signal_connect(G_OBJECT(quitter1), "clicked",G_CALLBACK(quitter),NULL);
  
    gtk_box_pack_start(GTK_BOX (vbox), quitter1,FALSE, FALSE, 0);
  
    }


  gtk_widget_show_all(window);  //Affichage

  gtk_main();
   /* Parametre inutilise */
  (void)p_widget;
}




void charger_code(const gchar *file_name, GtkTextView *p_text_view)
{   
    GtkTextBuffer *buffer;
    GtkTextIter start;
    GtkTextIter end;
    FILE *fichier;
  g_return_if_fail (file_name && p_text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      /* Copie de contents dans le GtkTextView */
      gchar *utf8 = NULL;
      GtkTextIter iter;
      GtkTextBuffer *p_text_buffer = NULL;
  
   if (actif)
  {
quitter(NULL,text_view);

  }
  
  actif =1;
  chemin = NULL;
  save = FALSE;
  gtk_widget_set_sensitive (GTK_WIDGET (view1), TRUE);


      chemin = g_strdup (file_name);
      gtk_widget_set_sensitive (GTK_WIDGET (view1), TRUE);
      p_text_buffer = gtk_text_view_get_buffer (view1);
      gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
      utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
      g_free (contents), contents = NULL;
      gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
      g_free (utf8), utf8 = NULL;
      /* Nous sommes obliges de remetre sauve a TRUE car l'insertion du contenu
         du fichier dans le GtkTextView a appele cb_modfie */
      save = TRUE;
    }
    else printf("pas ouvert\n");
  
}
}
void Affichage_principale (int argc, char **argv)

{
    quitter(p_window,view1);

  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *frame2;
  GtkWidget *frame3;
  GtkWidget *fixed1;
  GtkWidget *fixed2;
  GtkWidget *saisie;
  GtkWidget *box=NULL;
  GtkWidget *Qbox=NULL;
  GtkWidget *chargement;

  gtk_init(&argc, &argv);
  /* Creation de la fenètre*/
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "RISC-Emulator");
  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  frame = gtk_frame_new (NULL);
  frame2 = gtk_frame_new (NULL);
  frame3 = gtk_frame_new (NULL);

  box = gtk_hbutton_box_new ();
  gtk_box_set_spacing (box,10);
  Qbox = gtk_vbox_new(FALSE, 0);
  fixed1 = gtk_fixed_new();
  fixed2 = gtk_fixed_new();
  
  gtk_container_add (GTK_CONTAINER (frame), box);
  gtk_container_add (GTK_CONTAINER (frame), Qbox);
  gtk_container_add (GTK_CONTAINER (frame), frame3);
  gtk_container_add(GTK_CONTAINER(window),frame);
        p_window=window;

  gtk_box_pack_start (GTK_BOX (box), Qbox, FALSE, FALSE, 20);

  /*Creation des frames pour mettre a l'interieur les buttons*/


  gtk_frame_set_label (GTK_FRAME (frame), "Bienvenue sur l'emulateur RISC");//Creation du premier titre 
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.4);

  gtk_frame_set_label (GTK_FRAME (frame2), "Veuillez introduire votre programme");//Creation du deuxieme titre
  gtk_frame_set_label_align (GTK_FRAME (frame2), 0.5, 1.0);
  gtk_frame_set_shadow_type(GTK_FRAME (frame2),GTK_SHADOW_ETCHED_OUT);
  gtk_widget_set_size_request(frame, 800, 405);

  saisie = gtk_button_new_with_mnemonic("Saisir le code"); //création du bouton pour saisir le code  
  gtk_box_pack_start_defaults(GTK_BOX (box), saisie);
  g_signal_connect(saisie, "clicked", G_CALLBACK(Saisir_code),NULL);//affichage de l'editeur de text  pour saisir le code 
  
  chargement = gtk_button_new_with_label("charger le code"); //création du bouton pour le chargement du code 
  gtk_box_pack_start_defaults(GTK_BOX (box), chargement);
  g_signal_connect(G_OBJECT(chargement), "clicked", G_CALLBACK(Affiche_code), G_OBJECT(window));
  
 {
  GtkWidget *quitter;
  quitter = gtk_button_new_with_mnemonic("_Quitter");//création du bouton pour quitter 
  gtk_box_pack_start_defaults(GTK_BOX (Qbox), quitter);
  g_signal_connect(G_OBJECT(quitter), "clicked", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
 }

  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), window);

  gtk_widget_show_all(window);
  gtk_main();
}
void save1 (GtkWidget *p_widget, gpointer user_data)
{
 if (actif)
  {
    if (!save)
    {
      /* Le fichier n'a pas encore ete enregistre */
      if (!chemin)
      {
        GtkWidget *p_dialog = NULL;

        p_dialog = gtk_file_chooser_dialog_new ("savegarder le fichier", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);
        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
        {
          chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
        }
        gtk_widget_destroy (p_dialog);
      }
      /* Soit le fichier a deja ete enregistre, soit l'utilisateur vient de creer
         un nouveau  emplacement, dans le qu'elle on peut enregistrer */
      if (chemin)
      {
          gchar *contents = NULL;
          gchar *locale = NULL;
          GtkTextIter start;
          GtkTextIter end;
          GtkTextBuffer *p_text_buffer = NULL;
          p_text_buffer = gtk_text_view_get_buffer (view1);
          gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
          contents = gtk_text_buffer_get_text (p_text_buffer, &start, &end, FALSE);
          locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
          g_free (contents), contents = NULL;
          ecrire_instruction(chemin,locale);
          g_free (locale), locale = NULL;
          save = TRUE;
      
      }
    }
  }
  /* Parametres inutilises */
  (void)p_widget;
  (void)user_data;
}

quitter1(GtkWidget *p_widget, gpointer user_data){

    gtk_main_quit();
    (void)p_widget;
  (void)user_data;
}

void Affiche_Erreur (char* chemin_fichier)
{


  gtk_init(0, NULL);
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *text_view;
  GtkWidget *scrolled_window;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  gtk_window_set_title(GTK_WINDOW(window), "Emulateur de processeur RISC"); //Création de la fenêtre
 g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  
  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  
  scrolled_window = gtk_scrolled_window_new( NULL, NULL); //Ajout de la capacité a pouvoir faire défiler
  
  gtk_box_pack_start( GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
  
  text_view = gtk_text_view_new();
  PangoFontDescription *font1 = pango_font_description_from_string("Sans, Bold, 12"); //Format de l'ecriture
  gtk_widget_modify_font(text_view, font1);
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 5);
  gtk_container_add( GTK_CONTAINER( scrolled_window), text_view);
  
  char *buffer = NULL;  //Récuperation du texte dans un fichier
  GError *error = NULL;
  if (g_file_get_contents (chemin_fichier, &buffer, NULL, &error) == FALSE)
  {
    g_warning ("%s", error->message);
    g_clear_error (&error);
  }
  GtkTextBuffer *buff;
  buff = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));  //Insertion du texte
  gtk_text_buffer_set_text (buff, buffer, -1);

  gtk_widget_show_all(window);  //Affichage
  gtk_main();
  }

void sequentiel1(GtkWidget *p_widget, gpointer user_data) 
{      

  int resultat=0; 
choix_mode=1;
  resultat=sequentiel(chemin);
Affiche_Resultat(resultat);

  (void)p_widget;
  (void)user_data;  }
  
  void pipe1(GtkWidget *p_widget, gpointer user_data) 

{

  int resultat=0;
choix_mode=2;
  resultat=pipeline(chemin);

Affiche_Resultat(resultat);
  (void)p_widget;
  (void)user_data;  }
  

void choix_execution (char* chemin_fichier)
{
  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *frame2;
  GtkWidget *fixed;
  GtkWidget *quitter;
  GtkWidget *main_box;

  gtk_init(0, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "RISC");
  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  fixed = gtk_fixed_new();
  frame = gtk_frame_new (NULL);
  frame2 = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (fixed), frame2);
  gtk_container_add (GTK_CONTAINER (frame), fixed);
  gtk_container_add(GTK_CONTAINER(window),frame);

  main_box = gtk_hbutton_box_new();
  gtk_container_add( GTK_CONTAINER(frame2), main_box);
  gtk_widget_set_size_request(main_box,1290,580);
  gtk_frame_set_label (GTK_FRAME (frame), "Le programme est correct");
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.4);
  gtk_frame_set_label (GTK_FRAME (frame2), "Veuillez choisir le mode d'exécution");
  gtk_frame_set_label_align (GTK_FRAME (frame2), 1.0, 1.4);
  gtk_widget_set_size_request(frame, 350, 250);
  gtk_widget_set_size_request(frame2, 250, 150);
  gtk_widget_set_uposition(frame2,65,65);
  int b=0;
 {
  GtkWidget *normale;

  normale = gtk_button_new_with_label("Normale"); 
  gtk_box_pack_start_defaults(GTK_BOX (main_box), normale);
    g_signal_connect(normale, "clicked", G_CALLBACK(sequentiel1),window);
 }
 {
 
  GtkWidget *pipeline;
  pipeline = gtk_button_new_with_label("Pipeline"); 
  gtk_box_pack_start_defaults(GTK_BOX (main_box), pipeline);
  g_signal_connect(pipeline, "clicked", G_CALLBACK(pipe1),window);
 }

 { 
  quitter = gtk_button_new_with_label("Quitter"); //création du boutton pour quitter 
  g_signal_connect(G_OBJECT(quitter), "clicked", G_CALLBACK(gtk_main_quit), G_OBJECT(window));
 }
  gtk_widget_show_all(window);

  gtk_main();

}




void Affiche_Resultat(int resultat)
{     

  gtk_init(0, NULL);
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *text_view;
  GtkWidget *scrolled_window;


  //le resultat a recevoir par l'ordonnanceur
   //bool mode = true; une valeur booleén
   /* puis on fais deux message pipeline,normale ,tous deponds du button choisis avant ,
   puis apres true=normale donc il affiche normale sinn il affiche l'autre et je sais pas comment tu affiche le buffer , mais en gros l'idée c ça */

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1080, 720);
  gtk_window_set_title(GTK_WINDOW(window), "Emulateur de processeur RISC"); //Création de la fenêtre
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  scrolled_window = gtk_scrolled_window_new( NULL, NULL); //Ajout de la capacité a pouvoir faire défiler

  gtk_box_pack_start( GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

  text_view = gtk_text_view_new();
  PangoFontDescription *font1 = pango_font_description_from_string("Sans, Bold, 12"); //Format de l'ecriture
  

  gtk_widget_modify_font(text_view, font1);
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 5);
  gtk_container_add( GTK_CONTAINER( scrolled_window), text_view);
  char mode[40];
  if (choix_mode==1)
  {
 strcpy(mode,"Le mode choisi = sequentiel");
  }
  else if(choix_mode==2)
  {
   strcpy(mode,"Le mode choisi = pipeline");

  }
  char buffer2[30];
  char buffer[30];
  sprintf(buffer, "%d", resultat);  //Conversion des int en char
  sprintf(buffer2, "%d", nbCycle);
  char Buffer3[256];
  strcpy(Buffer3,mode);
  char Buffer[40] = "\nNombre de cycles = ";
  char Buff [40] = "\nResulat = ";
  strcat(Buffer3,Buffer);
  strcat(Buffer3, buffer2);
  strcat(Buffer3, Buff);
  strcat(Buffer3,buffer);
  GtkTextBuffer *buff;

  buff = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));  //Insertion du texte
  gtk_text_buffer_set_text (buff, Buffer3, -1);

   hbox = gtk_hbutton_box_new();
   gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

 

 {
  GtkWidget *retour;
  retour = gtk_button_new_with_label("Retour");//création du buton pour revenir et choisir un autre mode d'execution
  gtk_box_pack_start_defaults(GTK_BOX (hbox), retour);
  g_signal_connect (retour, "clicked", G_CALLBACK (choix_execution), window);
 }
{
  GtkWidget *retourp;
  retourp = gtk_button_new_with_label("Retour_principale");//création du buton pour revenir et choisir un autre mode d'execution
  gtk_box_pack_start_defaults(GTK_BOX (hbox), retourp);
  g_signal_connect (retourp, "clicked", G_CALLBACK (Affichage_principale), window);
 }
 {
  GtkWidget *quitter;
  quitter = gtk_button_new_with_label("Quitter");//création du buton pour quitter le programme
  gtk_box_pack_start_defaults(GTK_BOX (hbox), quitter);
  g_signal_connect(G_OBJECT(quitter), "clicked",G_CALLBACK(gtk_main_quit), window);
 }

  gtk_widget_show_all(window);  //Affichage
  gtk_main();

}
