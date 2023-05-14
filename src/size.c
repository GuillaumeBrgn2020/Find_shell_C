//
// Created by Nico on 09/12/2022.
//

#include <string.h>
#include <stdlib.h>
#include "size.h"

int get_size(char * size_c){

    int size = 0;
    char prefix = size_c[0];
    char suffixe = size_c[strlen(size_c)-1];
    if ((prefix=='+') || (prefix=='-')){
        size = atoi(size_c+1);
    }
    else {
        size = atoi(size_c);
    }
    if (suffixe=='k'){
        size *= 1024;
    }
    else if (suffixe=='M'){
        size *= 1024*1024;
    }
    else if (suffixe=='G'){
        size *= 1024*1024*1024;
    }

    return size;
}
