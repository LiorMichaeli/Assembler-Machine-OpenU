
/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains help methods for pre assembler.
 */

/* Includes header files. */
#include "libraries.h"
#include "boolean.h"

/* Finals */
#define EQUAL 0

/* This is method that receives char * parameter that represents word. The method checks if the word is end macro definition, that is word equals to "endmcr" and if yes the method will returns true
 * and else the method will return false.
 */
boolean isEndMacroDefinition(char *word)
{
    boolean result = true;
    if(strcmp(word, "endmcr") != EQUAL)
        result = false;
    return result;
}

/* This is method that receives char * parameter that represents word. The method checks if the word is start macro definition, that is word equals to "mcr" and if yes the method will returns true
 * and else the method will return false.
 */
boolean isStartMacroDefinition(char *word)
{
    boolean result = true;
    if(strcmp(word, "mcr") != EQUAL)
        result = false;
    return result;
}