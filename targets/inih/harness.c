#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

//handler, inih calls it, when it finds a key/value pair in the ini file.
//It passes the user pointer, section name, key name, and value string. It returns 1 on success, 0 on error.

static int fuzz_handler(void* user, const char* section, const char* name, const char* value){
    (void)user;
    (void)section;
    (void)name;
    (void)value;
    return 1; // continue parsing
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size){
    // 1. ini_parse_string needs \0, so we add it in the end
    char *conf = (char *)malloc(size+1);  //create new data
    if (conf==NULL) return 0;  //in case  created incorrectly  
    memcpy(conf,data,size);  //copy data
    conf[size] = '\0';

    ini_parse_string(conf, fuzz_handler, NULL);

    free(conf);

    return 0;
}
