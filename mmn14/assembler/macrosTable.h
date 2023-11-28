#ifndef macrosTable_H /* #include guards */
#define macrosTable_H

typedef struct nodeInMacrosTable nodeInMacrosTable;

/* This is a method that receives char array parameter that represents line in the file, const char* parameter that represents the name of the file that we handle now without extension, nodeInMacrosTable ** parameter that represents pointer to the head of macros table
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in macros table.
 * The method add info to last macro in the macros table(that is the head of macros table because this is a stack). The method returns nothing.
 */
void addInfoToLastMacro(const char lineInTheFile[], const char *fileName, nodeInMacrosTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInMacrosTable);

/* This is a method that receives const char * parameter that represents word in line and nodeInMacrosTable * parameter that represents pointer to the head of macros table.
 * The method checks if the word that we receives as parameter is macro in the table. If yes the method will return true, and else false.
 */
boolean isWordMacroInTheTable(const char *wordInLine, nodeInMacrosTable *ptrHead);

/* This is a method that receives const char * parameter that represents macro name and nodeInMacrosTable * parameter that represents pointer to the head of macros table.
 * The method returns the info of macroName that we get as parameter. The method assume that there is macro in macrosTable that his name is macroName.
 */
char* getInfoByMacroName(const char *macroName, nodeInMacrosTable *ptrHead);

/* This is a method that receives const char * parameter that represents a pointer to macro name, const char* parameter that represents the name of the file that we handle now without extension, nodeInMacrosTable ** parameter that represents pointer to the head of macros table.
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in macros table.
 * The method add the macro(with name macroName) to the macros table. The method returns nothing.
 */
void addMacroToMacrosTable(const char *macroName, const char *fileName, nodeInMacrosTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInMacrosTable);

/* This is a method that receives nodeInMacrosTable ** parameter that represents pointer to the head of macros table.
 * The method free all the memory that has been allocated in macros table. The method returns nothing.
 */
void freeMemoryMacrosTable(nodeInMacrosTable **ptrStart);

#endif
