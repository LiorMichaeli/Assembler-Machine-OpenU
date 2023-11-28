/*
 * @author Lior Michaeli
 * @version 18.03.23
 * The program contains methods that dealing the labels table.
 */

/* Includes header files. */
#include "libraries.h"
#include "label.h"
#include "boolean.h"
#include "errors.h"
#include "helpMethods.h"
#include "printMessage.h"

/* Finals */
#define LENGTH_OF_END_CHARACTER 1
#define NO_ADRESS (-1)
#define NO_LINE 0

/* Define data structure - stack*/
typedef struct nodeInLabelsTable
{
    labelType type;
    int labelAdress;
    char *labelName;
    struct nodeInLabelsTable *link;
}nodeInLabelsTable;

/* Prototype - there is an explanation of each function below (where the function appears in this file). */
errors checkAllocationOfLabelsTablePointers(nodeInLabelsTable *ptr, const char *fileName);

/* This is a method that receives char * parameter that represents label name and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method checks if the word that we receives as parameter is label in the table. If yes the method will return true, and else false.
 */
boolean isLabelInLabelsTable(const char *labelName, nodeInLabelsTable *ptrHead)
{
    boolean result = false;
    nodeInLabelsTable *ptrToNodeInLabelsTable = ptrHead;
    /* Go over all the nodes in labels table and as long as result is false, that mean we not found labelName in the labels table. */
    while(ptrToNodeInLabelsTable != NULL && result == false)
    {
        /* Checks if the name of the current label is labelName. If yes that mean we found labelName in the labels table and thus we will set result to true. */
        if(!strcmp(ptrToNodeInLabelsTable->labelName, labelName))
            result = true;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
    return result;
}

/* This is a method that receives labelType parameter that represents type and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method checks if there is label in labels table with the type we receive as parameter. If yes the method will return true, and else false.
 */
boolean thereIsLabelWithThisTypeInLabelsTable(labelType type, nodeInLabelsTable *ptrHead)
{
    boolean result = false;
    nodeInLabelsTable *ptrToNodeInLabelsTable = ptrHead;
    /* Go over all the nodes in labels table and as long as result is false, that mean we not found label in the labels table with the type we receive as parameter. */
    while(ptrToNodeInLabelsTable != NULL && result == false)
    {
        /* Checks if the type of the current label is the type we receive as parameter. If yes that mean we found label in the labels table with the type we receive as parameter and thus we will set result to true. */
        if(ptrToNodeInLabelsTable->type == type)
            result = true;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
    return result;
}

/* This is a method that receives labelType parameter that represents the type of the label that we want to add, int parameter that represents the adress of the label that we want to add, const char * parameter
 * that represents the name of the label that we want to add, const char* parameter that represents the name of the file that we handle now without extension, nodeInLabelsTable** parameter that represents pointer to the head of labels table
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in labels table.
 * The method add new label(with the attributes that we receives as parameters) to the labels table. The method returns nothing.
 */
void addLabelToLabelsTable(labelType type, int labelAdress, const char *labelName, const char *fileName , nodeInLabelsTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInLabelsTable)
{
    nodeInLabelsTable *ptrToAddedNodeInLabelsTable = NULL;
    /* Checks if labels table is empty. */
    if(*ptrHead == NULL)
    {
        *ptrHead = (nodeInLabelsTable *)malloc(sizeof(nodeInLabelsTable));/* Use malloc to allocates memory for the pointer that points to node in labels table. */
        /* Checks allocation errors. */
        if(checkAllocationOfLabelsTablePointers(*ptrHead, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInLabelsTable = true;
        else
        {
            (*ptrHead)->type = type;
            (*ptrHead)->labelAdress = labelAdress;
            (*ptrHead)->labelName = (char *)malloc(strlen(labelName)+LENGTH_OF_END_CHARACTER);/* Use malloc to allocates memory for the pointer that points to the name of the label. */
            /* Checks allocation errors. */
            if(checkAllocationOfCharsPointers((*ptrHead)->labelName, fileName) == THERE_IS_AN_ERROR)
                **ptrFlagThereIsAllocationErrorInLabelsTable = true;
            else
                strcpy((*ptrHead)->labelName, labelName);/* Copy labelName to the name of the label of this node. */
            (*ptrHead)->link = NULL;
        }
    }
    else
    {
        ptrToAddedNodeInLabelsTable = (nodeInLabelsTable *)malloc(sizeof(nodeInLabelsTable)); /* Use malloc to allocates memory for the pointer that points to node in labels table. */
        /* Checks allocation errors. */
        if(checkAllocationOfLabelsTablePointers(ptrToAddedNodeInLabelsTable, fileName) == THERE_IS_AN_ERROR)
            **ptrFlagThereIsAllocationErrorInLabelsTable = true;
        else
        {
            ptrToAddedNodeInLabelsTable->type = type;
            ptrToAddedNodeInLabelsTable->labelAdress = labelAdress;
            ptrToAddedNodeInLabelsTable->labelName = (char *)malloc(strlen(labelName)+LENGTH_OF_END_CHARACTER); /* Use malloc to allocates memory for the pointer that points to the name of the label. */
            /* Checks allocation errors. */
            if(checkAllocationOfCharsPointers(ptrToAddedNodeInLabelsTable->labelName, fileName) == THERE_IS_AN_ERROR)
                **ptrFlagThereIsAllocationErrorInLabelsTable = true;
            else
                strcpy((ptrToAddedNodeInLabelsTable)->labelName, labelName); /* Copy labelName to the name of the label of this node. */
            /* Sets link of ptrToAddedNodeInLabelsTable to ***ptrHead and sets ***ptrHead to ptrToAddedNodeInLabelsTable because labels table is stack. */
            ptrToAddedNodeInLabelsTable->link = *ptrHead;
            *ptrHead = ptrToAddedNodeInLabelsTable;
        }
    }
}

/* This is a method that receives const char * parameter that represents the name of the label and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method returns the type of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName.
 */
labelType getTypeOfLabelInLabelsTableByName(const char *labelName, nodeInLabelsTable *ptrHead)
{
    labelType result = illegalLabelType;
    nodeInLabelsTable *ptrToNodeInLabelsTable = ptrHead;
    /* Goes over all the nodes in labels table as long as we dont found labelName in labels table. */
    while(ptrToNodeInLabelsTable != NULL && result == illegalLabelType)
    {
        if(!strcmp(ptrToNodeInLabelsTable->labelName, labelName))
            result = ptrToNodeInLabelsTable->type;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
    return result;
}

/* This is a method that receives const char * parameter that represents the name of the label and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method returns the adress of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName.
 */
int getAdressOfLabelInLabelsTableByName(const char *labelName, nodeInLabelsTable *ptrHead)
{
    int result = NO_ADRESS;
    nodeInLabelsTable *ptrToNodeInLabelsTable = ptrHead;
    /* Goes over all the nodes in labels table as long as we dont found labelName in labels table. */
    while(ptrToNodeInLabelsTable != NULL && result == NO_ADRESS)
    {
        if(!strcmp(ptrToNodeInLabelsTable->labelName, labelName))
            result = ptrToNodeInLabelsTable->labelAdress;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
    return result;
}

/* This is a method that receives labelType parameter that represents type of label, const char * parameter that represents the name of the label and nodeInLabelsTable** parameter that represents pointer to the head of labels table.
 * The method sets the type of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName. The method returns nothing.
 */
void setTypeOfLabelInLabelsTableByName(labelType type, const char *labelName, nodeInLabelsTable **ptrHead)
{
    boolean flagWeFindTheLabel = false;
    nodeInLabelsTable *ptrToNodeInLabelsTable = *ptrHead;
    /* Goes over all the nodes in labels table as long as we dont found labelName in labels table. */
    while(ptrToNodeInLabelsTable != NULL && flagWeFindTheLabel == false)
    {
        if(!strcmp(ptrToNodeInLabelsTable->labelName, labelName))
        {
            ptrToNodeInLabelsTable->type = type;
            flagWeFindTheLabel = true;
        }
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
}

/* This is a method that receives nodeInLabelsTable** parameter that represents pointer to the head of labels table, int parameter that represents the amount that we need to add to adress of data labels
 * and int parameter that represents the amount that we need to add to adress of instruction labels. Thw method add to the adress of data and instruction labels the appropriate amount that we want to add. The method returns nothing.
 */
void addAdressToDataAndInstructionLabels(nodeInLabelsTable **ptrHead, int amountOfAddAdressToData, int amountOfAddAdressToInstruction)
{
    nodeInLabelsTable *ptrToNodeInLabelsTable = *ptrHead;
    /* Goes over all the nodes in labels table */
    while(ptrToNodeInLabelsTable != NULL)
    {
        if(ptrToNodeInLabelsTable->type == data)
            ptrToNodeInLabelsTable->labelAdress += amountOfAddAdressToData;
        else if(ptrToNodeInLabelsTable->type == code)
            ptrToNodeInLabelsTable->labelAdress += amountOfAddAdressToInstruction;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
}

/* This is a method that receives labelType parameter that represents type of label, nodeInLabelsTable* parameter that represents pointer to the head of labels table and FILE ** parameter that represents
 * pointer to file. The method writes all the labels in labels table with the type that we receives as parameter to the file.
 */
void writeAllLabelsWithThisTypeInLabelsTableToFile(labelType type, nodeInLabelsTable *ptrHead, FILE **ptrToFile)
{
    nodeInLabelsTable *ptrToNodeInLabelsTable = ptrHead;
    /* Goes over all the nodes in labels table */
    while(ptrToNodeInLabelsTable != NULL)
    {
        /* If the type of current label is the type that we receives as parameter, so we will print to the file the name of the label and her adress. */
        if(ptrToNodeInLabelsTable->type == type)
            fprintf(*ptrToFile,"%-15s%d\n", ptrToNodeInLabelsTable->labelName, ptrToNodeInLabelsTable->labelAdress);
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link;
    }
}

/* This is a method that receives nodeInLabelsTable** parameter that represents pointer to the head of labels table.
 * The method free all the memory that has been allocated in labels table. The method returns nothing.
 */
void freeMemoryLabelsTable(nodeInLabelsTable **ptrHead)
{
    nodeInLabelsTable *ptrToNodeInLabelsTable = *ptrHead, *ptrToFreeNodeInLabelsTable;
    /* Goes over all the nodes in labels table. */
    while(ptrToNodeInLabelsTable != NULL)
    {
        ptrToFreeNodeInLabelsTable = ptrToNodeInLabelsTable;
        ptrToNodeInLabelsTable = ptrToNodeInLabelsTable->link; /* Goes to the next node in labels table. */
        /* Free name of label and pointer to this macro. */
        free(ptrToFreeNodeInLabelsTable->labelName);
        free(ptrToFreeNodeInLabelsTable);
    }
    *ptrHead = NULL;
}

/* This is a method that receives nodeInLabelsTable* parameter that represents a pointer that we need to check and const char* parameter that represents the name of the file that we handle now without extension
 * The method checks if the memory allocation we did was successful. If the memory allocation we did was not successful the method calls to printMessage method,
 * that will print error to the user and we will return that there is an error. Else we will return that there is no error.
 */
errors checkAllocationOfLabelsTablePointers(nodeInLabelsTable *ptr, const char *fileName)
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