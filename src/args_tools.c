#include <stdbool.h>
#include "args_tools.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

long date_arg_seconds = 0;
regex_t *name_regex;
regex_t *ctc_regex;

long get_date_arg_seconds() {
    return date_arg_seconds;
}

regex_t *get_name_regex() {
    return name_regex;
}

regex_t *get_ctc_regex() {
    return ctc_regex;
}


void init_arg_value(int arg_num, char *argValue) {
    if (argValue == NULL) {
        return;
    }
    arguments.is_def[arg_num] = true;
    char *copy = malloc((strlen(argValue) + 1) * sizeof(char));
    strcpy(copy, argValue);
    arguments.values[arg_num] = copy;
}

void init_arg(int argc, char *argv[]) {
    int i = 1;
    while (i < argc - 1) { //Parcours des arguments
        i++;
        // @formatter:off
        // arguments sans valeurs
        if(strcmp(argv[i], "-link") == 0)       {arguments.is_def[LINK]     = true; continue;}
        if(strcmp(argv[i], "-ou") == 0)         {arguments.is_def[OU]       = true; continue;}
        if(strcmp(argv[i], "-color") == 0)      {arguments.is_def[COLOR]    = true; continue;}
        if(strcmp(argv[i], "-test") == 0)       {arguments.is_def[TEST]     = true; continue;}

        // arguments avec valeurs
        if(strcmp(argv[i], "-dir") == 0)        {i++; init_arg_value(DIR_ARG,  argv[i]); continue;}
        if(strcmp(argv[i], "-size") == 0)       {i++; init_arg_value(SIZE,  argv[i]); continue;}
        if(strcmp(argv[i], "-name") == 0)       {i++; init_arg_value(NAME,  argv[i]); continue;}
        if(strcmp(argv[i], "-mime") == 0)       {i++; init_arg_value(MIME,  argv[i]); continue;}
        if(strcmp(argv[i], "-type") == 0)       {i++; init_arg_value(TYPE,  argv[i]); continue;}
        if(strcmp(argv[i], "-perm") == 0)       {i++; init_arg_value(PERM,  argv[i]); continue;}
        if(strcmp(argv[i], "-threads") == 0)    {i++; init_arg_value(THREAD,argv[i]); continue;}
        if(strcmp(argv[i], "-date") == 0)       {i++; init_arg_value(DATE,  argv[i]); continue;}
        if(strcmp(argv[i], "-w") == 0)          {i++; init_arg_value(W,     argv[i]); continue;}
        // @formatter:on
        if (strcmp(argv[i], "-ctc") == 0) {
            i++;
            char *tmp = malloc(200 * sizeof(char));
            strcpy(tmp, argv[i]);
            // Tant que l'argument suivant ne commence pas par "-", on ajoute un espace et on concatène
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                i++;
                strcat(tmp, " ");
                strcat(tmp, argv[i]);
            }
            arguments.values[CTC] = tmp;
            arguments.is_def[CTC] = true;
            continue;
        }
    }
    // On compte le nombre d'arguments
    int nb_arg = 0;
    for (int j = 0; j <= NB_ARGS; j++) {
        if (arguments.is_def[j]) {
            nb_arg++;
        }
    }
    arguments.nb_args = nb_arg;

    // DATE
    if (arguments.is_def[DATE]) {
        date_arg_seconds = parseDateArgToInt(arguments.values[DATE]);
    }

    // NAME
    if (arguments.is_def[NAME]) {
        name_regex = malloc(sizeof(regex_t));
        /* Compile regular expression */
        int reti = regcomp(name_regex, arguments.values[NAME], 0);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
    }
    // CTC
    if (arguments.is_def[CTC]) {
        ctc_regex = malloc(sizeof(regex_t));
        /* Compile regular expression */
        int reti = regcomp(ctc_regex, arguments.values[CTC], 0);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
    }
}

void destroy_args() {
    // Supprime la regex
    if (arguments.is_def[NAME]) {
        regfree(name_regex);
        free(name_regex);
    }
    // Supprime les valeurs des arguments
    for (int i = 0; i < NB_ARGS; i++) {
        if (arguments.values[i] != NULL) {
            free(arguments.values[i]);
        }
    }
}

long parseDateArgToInt(char *date_arg_val) {
    // get prefix if '+'
    bool is_plus = false;
    if (date_arg_val[0] == '+') {
        is_plus = true;
        date_arg_val++;
    }
    char suffix = date_arg_val[strlen(date_arg_val) - 1];
    char *value = malloc(sizeof(char) * strlen(date_arg_val));
    strncpy(value, date_arg_val, strlen(date_arg_val) - 1);
    int value_int = atoi(value);
    switch (suffix) {
        case 'm' :
            value_int *= 60;
            break;
        case 'h' :
            value_int *= 3600;
            break;
        case 'd' :
            value_int *= 86400;
            break;
    }
    free(value);
    return (is_plus ? -value_int : value_int);
}

/**
 * Retourne un char* contenant le contenu du fichier sans traitement supp
 * ! Ne pas oublier de libérer la mémoire !
 * @param path
 * @return
 */
char *get_file_content(char const *path) {
    char *buffer = NULL;
    long length;
    FILE *f = fopen(path, "rb"); //was "rb"

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *) malloc((length + 1) * sizeof(char));
        if (buffer) {
            fread(buffer, sizeof(char), length, f);
        }
        fclose(f);
    }
    if (buffer == NULL) {
        return NULL;
    }
    buffer[length] = '\0';
    return buffer;
}
