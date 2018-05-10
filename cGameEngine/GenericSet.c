#include "include/GenericSet.h"
#include "include/defs.h"

void GenericSetCreate(GenericSet* arguments, char* argorder, ...){
    int argCount = strlen(argorder);
    arguments->types = malloc(sizeof(char) * argCount);
    strcpy(arguments->types, argorder);

    //set so I can later get the types
    char* current = argorder;

    //handle the variable arguments
    va_list args;
    va_start(args, argorder);

    int totalBytes = 0;
    void** array = (void**)malloc(sizeof(void*) * argCount);

    for(int i = 0; i < argCount; i++){
        switch(*current){
            case GENERIC_SET_INT:
                {
                    totalBytes += sizeof(int);
                    int* value = (int*) malloc(sizeof(int));
                    value[0] = va_arg(args, int);
                    array[i] = (void*)value;
                    break;
                }
            case GENERIC_SET_DOUBLE:
                {
                    totalBytes += sizeof(double);
                    double* value = (double*) malloc(sizeof(double));
                    value[0] = va_arg(args, double);
                    array[i] = (void*)value;
                    break;
                }
            case GENERIC_SET_POINTER:
                {
                    totalBytes += sizeof(void*);
                    array[i] = va_arg(args, void*);
                    break;
                }
            case GENERIC_SET_STRING:
                {
                    char* s;
                    s = va_arg(args, char*);
                    int len = strlen((char*)s);
                    char* valuestring = (char*)malloc(sizeof(char) * len);
                    strcpy(valuestring, (char*)s);
                    array[i] = (void*) valuestring;
                    break;
                }
        }

        current++;
    }

    arguments->data = array;
    arguments->bytes = totalBytes;
    arguments->elements = argCount;
}

void GenericSetFree(GenericSet* set){
    for(int i = 0; i < set->elements; i++){
        if(set->types[i] != GENERIC_SET_POINTER){
            free(set->data[i]);
        }
    }

    free(set->data);
    free(set->types);
}

int GenericSetGetInt(GenericSet* set, int index){
    return *((int*)set->data[index]);
}

double GenericSetGetDouble(GenericSet* set, int index){
    return *((double*)set->data[index]);
}

float GenericSetGetFloat(GenericSet* set, int index){
    return *((float*)set->data[index]);
}

long GenericSetGetLong(GenericSet* set, int index){
    return *((long*)set->data[index]);
}

short GenericSetGetShort(GenericSet* set, int index){
    return *((short*)set->data[index]);
}

char GenericSetGetChar(GenericSet* set, int index){
    return *((char*)set->data[index]);
}

void* GenericSetGetPointer(GenericSet* set, int index){
    return set->data[index];
}

const char* GenericSetGetString(GenericSet* set, int index){
    return (const char*)set->data[index];
}



