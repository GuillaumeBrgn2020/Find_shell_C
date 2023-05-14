//
// Created by Nico on 09/12/2022.
//

#ifndef RS2022PROJ245_ARGS_TOOLS_H
#define RS2022PROJ245_ARGS_TOOLS_H

#include <regex.h>


#define W 0
#define TEST 1
#define NAME 2
#define SIZE 3
#define DATE 4
#define MIME 5
#define CTC 6
#define DIR_ARG 7
#define COLOR 8
#define PERM 9
#define LINK 10
#define THREAD 11
#define OU 12
#define TYPE 13

#define NB_ARGS 14

struct arguments_t {
    bool is_def[NB_ARGS];
    char *values[NB_ARGS];
    int nb_args;
} arguments_t;

struct arguments_t arguments;

/**
 * Initialise la structure contenant les arguments passés au programmes et leur valeurs
 * @param argc
 * @param argv
 */
void init_arg(int argc, char *argv[]);

/**
 * enregistre une copie de la valeur de l'arguments dans la case vide
 * @param arg_num
 * @param argValue
 */
void init_arg_value(int arg_num, char *argValue);

/**
 * Libère la mémoire des arguments
 */
void destroy_args();

long parseDateArgToInt(char *date_arg_val);
long get_date_arg_seconds();
regex_t * get_name_regex();
regex_t *get_ctc_regex();
char *get_file_content(char const *path);

#endif //RS2022PROJ245_ARGS_TOOLS_H
