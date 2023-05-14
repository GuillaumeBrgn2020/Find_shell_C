#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <regex.h>
#include "args_tools.h"
#include "size.h"
#include "mime.c"

#define UNUSED(x) (void)(x)

/**
 * Ecrire le code permettant de parcourir l’arborescence de fichier (de mani`ere r ́ecursive). Pour v ́erifier
 * le bon fonctionnement de cette  ́etape, le programme devra afficher le chemin de tous les dossiers et
 * fichiers pr ́esents depuis la racine. Il se comportera donc comme un ‘ls‘ r ́ecursif
 */
void parcourir(const char *name, int indent) {
    DIR *dir;
    struct dirent *current;
    if (!(dir = opendir(name)))
        return;
    // Dossier initial
    if (indent == 0 && (arguments.nb_args == 0)) {
        printf("%s :\n", name);
    }

    while ((current = readdir(dir)) != NULL) {
        // Construction du chemin du repertoire actuel par concaténation
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", name, current->d_name);

        if (current->d_type == DT_DIR) {
            // ------------- DIRECTORY ---------

            if (strcmp(current->d_name, ".") == 0 || strcmp(current->d_name, "..") == 0) {
                continue;
            }

            if (arguments.nb_args == 0) {
                printf("%s :\n", path);
            } else if (arguments.is_def[DIR_ARG] && strcmp(current->d_name, arguments.values[DIR_ARG]) == 0) {
                // Avec l'argument -dir
                printf("%s\n", path);
            }
            parcourir(path, ++indent);

        } else {
            // ----------------  FILE --------------

            // Si on recherche un repertoire, on skip cette étape
            if (arguments.is_def[DIR_ARG]) {
                continue;
            }

            struct stat *buf_stat;
            buf_stat = malloc(sizeof(struct stat));
            stat(path, buf_stat);
            bool affiche = true;

            // NAME
            if (affiche && arguments.is_def[NAME]) {
                /* Execute regular expression */
                int reti = regexec(get_name_regex(), current->d_name, 0, NULL, 0);
                if (!reti) {
                    affiche = true;
                } else if (reti == REG_NOMATCH) {
                    affiche = false;
                } else {
                    printf("Regex match failed\n");
                    exit(1);
                }
            }

            // CTC
            if (affiche && arguments.is_def[CTC]) {
                /* Execute regular expression */
                char *file_content = get_file_content(path);
                int reti = regexec(get_ctc_regex(), file_content, 0, NULL, 0);
                free(file_content);
                if (!reti) {
                    affiche = true;
                } else if (reti == REG_NOMATCH) {
                    affiche = false;
                } else {
                    printf("Regex match failed\n");
                    exit(1);
                }
            }

            // SIZE
            if (affiche && arguments.is_def[SIZE]) {
                // on récupère la taille du fichier courant avec stat

                int size_file = buf_stat->st_size;
                int size_args = get_size(arguments.values[SIZE]);
                affiche = (arguments.values[SIZE][0] == '-' && size_file < size_args) //taille <
                          || (arguments.values[SIZE][0] == '+' && size_file > size_args) //taille >
                          || ((arguments.values[SIZE][0] >= '0' && arguments.values[SIZE][0] <= '9') &&
                              (size_file == size_args)); //taille =
            }

            // DATE
            if (affiche && arguments.is_def[DATE]) {
                // on récupère la date de modification du fichier courant
                time_t t = time(NULL);
                long seconds_since_access = difftime(t, buf_stat->st_atime);
                int date_args = get_date_arg_seconds();
                affiche = (date_args >= 0 && seconds_since_access <= date_args) //date "-"
                          || (date_args < 0 && seconds_since_access > -date_args); //date +
            }

            // MIME
            if (affiche && arguments.is_def[MIME]) {
                bool contains_subtype = strchr(arguments.values[MIME], '/') != NULL;
                affiche = is_matching_mime_type(current->d_name, arguments.values[MIME], contains_subtype);
            }

            if (affiche) {
                printf("%s\n", path);
            }
            free(buf_stat);
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[]) {
    if (argv[1][strlen(argv[1]) - 1] == '/') {
        argv[1][strlen(argv[1]) - 1] = '\0';
    }

    // Parsing des arguments
    init_arg(argc, argv);

    //Question 1
    if (arguments.is_def[TEST]) {  //On vérifie si la 1ere option est -test
        if (arguments.nb_args >= 2) {
            printf("La valeur du flag %s est %s\n", argv[3], argv[4]);
        } else {
            printf("Le flag %s n'est pas correct\n", argv[3]);
        }
    } else {
        parcourir(argv[1], 0);
    }

    // Free
    destroy_args();
}
