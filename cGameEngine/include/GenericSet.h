#include "defs.h"
#include <string.h>

/**
 * returns a void ** including all the passed variables
 * */
void GenericSetCreate(GenericSet* set, char* argumentorder, ...);

/**
 * deallocates and cleans up 
 * memory associated to the generic set
 * */
void GenericSetCleanup(GenericSet* set);

/**
 * returns an int from a generic set
 * */
int GenericSetGetInt(GenericSet* set, int index);

/**
 * returns an double from a generic set
 * */
double GenericSetGetDouble(GenericSet* set, int index);

/**
 * returns an float from a generic set
 * */
float GenericSetGetFloat(GenericSet* set, int index);

/**
 * returns an long from a generic set
 * */
long GenericSetGetLong(GenericSet* set, int index);

/**
 * returns an short from a generic set
 * */
short GenericSetGetShort(GenericSet* set, int index);

/**
 * returns an char from a generic set
 * */
char GenericSetGetChar(GenericSet* set, int index);

/**
 * returns an pointer from a generic set
 * */
void* GenericSetGetPointer(GenericSet* set, int index);

/**
 * returns a string retreived from a
 * generic set
 * */
const char* GenericSetGetString(GenericSet* set, int index);
