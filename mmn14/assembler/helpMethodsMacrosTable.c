/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains help methods for macros table in the program.
 */

/* Includes header files. */
#include "libraries.h"

/* Finals */
#define LENGTH_OF_END_CHARACTER 1

/* This is a method that receives const char* parameter that represents pointer to the info in the macro and const char* parameter that represents pointer to the info that we want to add to the macro.
 * The method return int that represents the length needed for the info after the add.
 */
int getLengthNeedForInfoOfMacroAfterAdd(const char *info, const char *infoToAdd)
{
    int result;
    if(info == NULL)
        result = (int)strlen(infoToAdd) + LENGTH_OF_END_CHARACTER;
    else
        result = (int)strlen(info) + (int)strlen(infoToAdd) + LENGTH_OF_END_CHARACTER;
    return result;
}