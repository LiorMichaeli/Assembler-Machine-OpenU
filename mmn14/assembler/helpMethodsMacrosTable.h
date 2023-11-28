#ifndef helpMethodsMacrosTable_H /* #include guards */
#define helpMethodsMacrosTable_H

/* This is a method that receives const char* parameter that represents pointer to the info in the macro and const char* parameter that represents pointer to the info that we want to add to the macro.
 * The method return int that represents the length needed for the info after the add.
 */
int getLengthNeedForInfoOfMacroAfterAdd(const char *info, const char *infoToAdd);

#endif