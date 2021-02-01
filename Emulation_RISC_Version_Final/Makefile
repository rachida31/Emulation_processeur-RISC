#variables..............................................................

NOM=ABDERRAHMANI_Ghouzali_CARRE_Clement_KHAMARI_Nor_el_khitem_LOUALIA_Kamilia_OUCHENE_Rachida_REKIK_Ines_REYNAUD_Julien_TOUAZI_Lylia 
cc=gcc
EXEC=RISC
#CFLAGS=-Wall -W -O2 -ansi -pedantic 
#LDFLAGS=`pkg-config --cflags --libs gtk+-2.0`
############################################################
#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic
 
 
#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0)
 
CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)
 
 
#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)
 
LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)
 
############################################################
#structure..............................................................
SRC_CHEMIN=src/
INC_CHEMIN=inc/
OBJ_CHEMIN=obj/
SRC=$(shell find $(SRC_CHEMIN)*.c)
OBJ=$(SRC:$(SRC_CHEMIN)%.c=$(OBJ_CHEMIN)%.o)

NIV_CHEMIN=code/
REPORT_PATH = report/


#cible
.PHONY:clean
.SUFFIXES:

#lancement execution....................................................

test: compil
	$(info lancement de $(EXEC):)
	./$(EXEC)  
# Edition de liens 

compil:$(EXEC)

$(EXEC): $(OBJ)
	$(info edition des liens dans $(EXEC):)
	$(cc) $^ -o $(EXEC) $(LDFLAGS)  

# Compilation
$(OBJ_CHEMIN)RISC.o: $(SRC_CHEMIN)RISC.c $(INC_CHEMIN)mes_types.h $(INC_CHEMIN)ordonnanceur.h $(INC_CHEMIN)interface_graphique.h $(INC_CHEMIN)analyseur.h $(INC_CHEMIN)unite_calcul.h 
	$(cc) -c $< -o  $@  $(CFLAGS)
$(OBJ_CHEMIN)%.o: $(SRC_CHEMIN)%.c $(INC_CHEMIN)%.h $(INC_CHEMIN)mes_types.h $(INC_CHEMIN)ordonnanceur.h $(INC_CHEMIN)interface_graphique.h $(INC_CHEMIN)analyseur.h $(INC_CHEMIN)unite_calcul.h 
	$(info compilation de $(EXEC):)
	$(cc) -c $< -o $@ $(CFLAGS)





# Dépendances supplémentaires ................................................:

editeur:
	#geany Makefile  $(INC_CHEMIN)mes_types.h $(SRC_CHEMIN)blackjack.c $(INC_CHEMIN)Menu.h $(INC_CHEMIN)create_processus.h
# $(SRC_CHEMIN)afficher.c $(INC_CHEMIN)afficher.h &


#aligner le code 
aligner:
	indent -linux  $(SRC_CHEMIN)*.c $(INC_CHEMIN)*.h
# Pour creer le zip a deposer sur e-campus
zip:
	rm -fr $(NOM)
	rm -f $(NOM).zip
	mkdir $(NOM)
	cp -r inc $(NOM)
	cp -r obj $(NOM)
	cp -r  code $(NOM)
	cp -r src $(NOM)
	cp -r report $(NOM)
	cp Makefile $(NOM)
	zip -r $(NOM).zip $(NOM)/*



clean:
	rm -rf $(EXEC)
	rm -f $(NOM).zip
	rm -f $(OBJ)

## Rapport ....................................................................:

report :
	make --directory="$(REPORT_PATH)"
