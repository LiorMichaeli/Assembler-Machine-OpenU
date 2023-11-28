/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that dealing the macro table.
 */

/* Includes header files. */
#include "libraries.h"
#include "errors.h"
#include "boolean.h"
#include "helpMethods.h"
#include "printMessage.h"
#include "helpMethodsMacrosTable.h"
/* Finals */
#define LENGTH_OF_END_CHARACTER 1
#define EQUAL 0
#define NO_LINE 0

/* Define data structure - stack */
typedef struct nodeInMacrosTable
{
    char *info;
    char *macroName;
    struct nodeInMacrosTable *link;
}nodeInMacrosTable;

/* Prototype - there is an explanation of each function below (where the function appears in this file)*/
errors checkAllocationOfMacroTablePointers(nodeInMacrosTable *ptr, const char *fileName);

/* This is a method that receives char array parameter that represents line in the file, const char* parameter that represents the name of the file that we handle now without extension, nodeInMacrosTable ** parameter that represents pointer to the head of macros table
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in macros table.
 * The method add info to last macro in the macros table(that is the head of macros table because this is a stack). The method returns nothing.
 */
void addInfoToLastMacro(const char lineInTheFile[], const char *fileName, nodeInMacrosTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInMacrosTable)
{
    int lengthNeedForInfoAfterAdd;
    nodeInMacrosTable *ptrToNodeInMacrosTable = *ptrHead;
    lengthNeedForInfoAfterAdd = getLengthNeedForInfoOfMacroAfterAdd(ptrToNodeInMacrosTable->info, lineInTheFile); /* Get the length that we need for the new info after we add more info. */
    /* Checks if the info in ptrToNodeInMacrosTable is NULL that mean there is no info in the macro. If yes we use malloc to allocate memory for the info, checks if the allocation succeed and finally copy the line in the file
     * to info of ptrToNodeInMacrosTable. Else we use realloc to allocate memory for the info, check if the allocation succeed and finally add the line in the file to the info of ptrToNodeInMacrosTable.
     */
    if(ptrToNodeInMacrosTable->info == NULL)
    {
        ptrToNodeInMacrosTable->info = (char *)malloc(lengthNeedForInfoAfterAdd);
        /* Checks allocation errors. */
        if(checkAllocationOfCharsPointers(ptrToNodeInMacrosTable->info, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInMacrosTable = true;
        else
            strcpy(ptrToNodeInMacrosTable->info, lineInTheFile);
    }
    else
    {
        ptrToNodeInMacrosTable->info = (char *)realloc(ptrToNodeInMacrosTable->info, lengthNeedForInfoAfterAdd);
        /* Checks allocation errors. */
        if(checkAllocationOfCharsPointers(ptrToNodeInMacrosTable->info, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInMacrosTable = true;
        else
            strcat(ptrToNodeInMacrosTable->info, lineInTheFile);
    }
}

/* This is a method that receives const char * parameter that represents word in line and nodeInMacrosTable * parameter that represents pointer to the head of macros table.
 * The method checks if the word that we receives as parameter is macro in the table. If yes the method will return true, and else false.
 */
boolean isWordMacroInTheTable(const char *wordInLine, nodeInMacrosTable *ptrHead)
{
    boolean result = false;
    nodeInMacrosTable *ptrToNodeInMacrosTable = ptrHead;
    /* Go over all the nodes in macros table(or as long as result is false, that mean we not found wordInLine in the macros table). */
    while(ptrToNodeInMacrosTable != NULL && result == false)
    {
        if(!strcmp(ptrToNodeInMacrosTable->macroName, wordInLine)) /* Checks if the name of the current macro is wordInLine. If yes that mean we found wordInLine in the macros table and thus we will set result to true. */
            result = true;
        ptrToNodeInMacrosTable = ptrToNodeInMacrosTable->link;
    }
    return result;
}

/* This is a method that receives const char * parameter that represents macro name and nodeInMacrosTable * parameter that represents pointer to the head of macros table.
 * The method returns the info of macroName that we get as parameter. The method assume that there is macro in macrosTable that his name is macroName.
 */
char* getInfoByMacroName(const char *macroName, nodeInMacrosTable *ptrHead)
{
    nodeInMacrosTable *ptrToNodeInMacrosTable = ptrHead;
    /* Goes over all the nodes in macros table as long as we dont found macroName in macros table. */
    while(strcmp(ptrToNodeInMacrosTable->macroName, macroName) != EQUAL)
    {
        ptrToNodeInMacrosTable = ptrToNodeInMacrosTable->link;
    }
    return ptrToNodeInMacrosTable->info;
}

/* This is a method that receives const char * parameter that represents a pointer to macro name, const char* parameter that represents the name of the file that we handle now without extension, nodeInMacrosTable ** parameter that represents pointer to the head of macros table.
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in macros table.
 * The method add the macro(with name macroName) to the macros table. The method returns nothing.
 */
void addMacroToMacrosTable(const char *macroName, const char *fileName, nodeInMacrosTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInMacrosTable)
{
    nodeInMacrosTable *ptrToAddedNodeInMacrosTable = NULL;
    /* Checks if macros table is empty. */
    if(*ptrHead == NULL)
    {
        *ptrHead = (nodeInMacrosTable *)malloc(sizeof(nodeInMacrosTable)); /* Use malloc to allocates memory for the pointer that points to node in macros table. */
        /* Checks allocation errors. */
        if(checkAllocationOfMacroTablePointers(*ptrHead, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInMacrosTable = true;
        else
        {
            (*ptrHead)->info = NULL;
            (*ptrHead)->macroName = (char *)malloc(strlen(macroName)+LENGTH_OF_END_CHARACTER); /* Use malloc to allocates memory for the pointer that points to name of macro. */
            /* Checks allocation errors. */
            if(checkAllocationOfCharsPointers((*ptrHead)->macroName, fileName) == THERE_IS_AN_ERROR)
                **ptrFlagThereIsAllocationErrorInMacrosTable = true;
            else
                strcpy((*ptrHead)->macroName, macroName); /* Copy macroName to the name of the macro of this node. */
            (*ptrHead)->link = NULL;
        }
    }
    else
    {
        ptrToAddedNodeInMacrosTable = (nodeInMacrosTable *)malloc(sizeof(nodeInMacrosTable)); /* Use malloc to allocates memory for the pointer that points to node in macros Table. */
        /* Checks allocation errors. */
        if(checkAllocationOfMacroTablePointers(ptrToAddedNodeInMacrosTable, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInMacrosTable = true;
        else
        {
            ptrToAddedNodeInMacrosTable->info = NULL;
            ptrToAddedNodeInMacrosTable->macroName = (char *)malloc(strlen(macroName)+LENGTH_OF_END_CHARACTER); /* Use malloc to allocates memory for the pointer that points to name of macro. */
            /* Checks allocation errors. */
            if(checkAllocationOfCharsPointers(ptrToAddedNodeInMacrosTable->macroName, fileName) == THERE_IS_AN_ERROR)
                **ptrFlagThereIsAllocationErrorInMacrosTable = true;
            else
                strcpy(ptrToAddedNodeInMacrosTable->macroName, macroName); /* Copy macroName to the name of the macro of this node. */
            /* Sets link of ptrToAddedNodeInMacrosTable to *ptrHead and sets *ptrHead to ptrToAddedNodeInMacrosTable because macros table is stack. */
            ptrToAddedNodeInMacrosTable->link = *ptrHead;
            *ptrHead = ptrToAddedNodeInMacrosTable;
        }
    }
}

/* This is a method that receives nodeInMacrosTable ** parameter that represents pointer to the head of macros table.
 * The method free all the memory that has been allocated in macros table. The method returns nothing.
 */
void freeMemoryMacrosTable(nodeInMacrosTable **ptrHead)
{
    nodeInMacrosTable *ptrToNodeInMacrosTable = *ptrHead, *ptrToFreeNodeInMacrosTable;
    /* Goes over all the nodes in macros table. */
    while(ptrToNodeInMacrosTable != NULL)
    {
        ptrToFreeNodeInMacrosTable = ptrToNodeInMacrosTable;
        ptrToNodeInMacrosTable = ptrToNodeInMacrosTable->link;/* Goes to the next node in macros table. */
        /* Free info in macro, macro name and pointer to this macro. */
        free(ptrToFreeNodeInMacrosTable->info);
        free(ptrToFreeNodeInMacrosTable->macroName);
        free(ptrToFreeNodeInMacrosTable);
    }
    *ptrHead = NULL;
}

/* This is a method that receives nodeInMacrosTable * parameter that represents a pointer that we need to check and const char* parameter that represents the name of the file that we handle now without extension.
 * The method checks if the memory allocation we did was successful. If the memory allocation we did was not successful the method calls to printMessage method,
 * that will print error to the user and we will return that there is an error. Else we will return that there is no error.
 */
errors checkAllocationOfMacroTablePointers(nodeInMacrosTable *ptr, const char *fileName)
{
    errors result = THERE_IS_NO_ERROR;
    if(ptr == NULL)
    {
        /* Prints error to the user. */
        printMessage(NO_LINE, ALLOCATION_NOT_SUCCEEDED, fileName);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}