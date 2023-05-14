# definition du compilateur
CC = clang
# definition des options de compilation pour obtenir un fichier .o
PRODUCTFLAGS = -Wall -Wextra -pedantic -O3 -g3 -fno-omit-frame-pointer #-fsanitize=address
COMPIL = $(CC) $(PRODUCTFLAGS)

# Deplacement des fichiers dans le bon dossier
MOV = mv *.o obj/


ftc: main.o args_tools.o size.o MegaMimes.o
	$(COMPIL) -o ftc main.o args_tools.o size.o MegaMimes.o && $(MOV)
main.o: src/main.c src/args_tools.h src/size.h src/lib/MegaMimes.h
	$(COMPIL) -c src/main.c
args_tools.o:
	$(COMPIL) -c src/args_tools.c
size.o:
	$(COMPIL) -c src/size.c
MegaMimes.o:
	$(COMPIL) -c src/lib/MegaMimes.c



# Pour nettoyer les fichiers sources
clean:
	rm -f ./bin/*
	rm -rf ./*.o
	rm -rf ./obj/*.o