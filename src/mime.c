#include <stdio.h>
#include <string.h>
#include "lib/MegaMimes.h"

bool is_matching_mime_type(char* file_name, char* tested_mime_type, bool has_subtype) {
    // on récupère le mime type du fichier
    const char* file_mimetype  = getMegaMimeType(file_name); // format: "type/subtype"
    // on compare le mime type du fichier avec celui passé en paramètre
    if(file_mimetype == NULL) {
        //printf("Error: mimetype is NULL : %s\n", file_name);
        return false;
    }

    // printf("mimetype: %s\n", file_mimetype);
    bool res = false;
    if (has_subtype) {
        // format : "type/subtype"
        res = strcmp(file_mimetype, tested_mime_type) == 0;

    } else { // format : "type"
        char *copy = malloc((strlen(file_mimetype) + 1) * sizeof(char));
        strcpy(copy, file_mimetype);
        char* mimetype_without_subtype = strtok(copy, "/");
        res = strcmp(mimetype_without_subtype, tested_mime_type) == 0;
        free(copy);
    }
    //free(file_mimetype);
    return res;
}
