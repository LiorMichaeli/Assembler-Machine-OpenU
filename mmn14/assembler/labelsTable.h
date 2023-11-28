#ifndef labelsTable_H /* #include guards */
#define labelsTable_H

/* Includes header files. */
#include "label.h"

typedef struct nodeInLabelsTable nodeInLabelsTable;

/* This is a method that receives char * parameter that represents label name and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method checks if the word that we receives as parameter is label in the table. If yes the method will return true, and else false.
 */
boolean isLabelInLabelsTable(const char *labelName, nodeInLabelsTable *ptrHead);

/* This is a method that receives labelType parameter that represents type and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method checks if there is label in labels table with the type we receive as parameter. If yes the method will return true, and else false.
 */
boolean thereIsLabelWithThisTypeInLabelsTable(labelType type, nodeInLabelsTable *ptrHead);

/* This is a method that receives labelType parameter that represents the type of the label that we want to add, int parameter that represents the adress of the label that we want to add, const char * parameter
 * that represents the name of the label that we want to add, const char* parameter that represents the name of the file that we handle now without extension, nodeInLabelsTable** parameter that represents pointer to the head of labels table
 * and boolean** parameter that represents pointer that points to flag that says if there is an error allocation in labels table.
 * The method add new label(with the attributes that we receives as parameters) to the labels table. The method returns nothing.
 */
void addLabelToLabelsTable(labelType type, int labelAdress, const char *labelName, const char *fileName , nodeInLabelsTable **ptrHead, boolean **ptrFlagThereIsAllocationErrorInLabelsTable);

/* This is a method that receives nodeInLabelsTable** parameter that represents pointer to the head of labels table.
 * The method free all the memory that has been allocated in labels table. The method returns nothing.
 */
void freeMemoryLabelsTable(nodeInLabelsTable **ptrHead);

/* This is a method that receives nodeInLabelsTable** parameter that represents pointer to the head of labels table, int parameter that represents the amount that we need to add to adress of data labels
 * and int parameter that represents the amount that we need to add to adress of instruction labels. Thw method add to the adress of data and instruction labels the appropriate amount that we want to add. The method returns nothing.
 */
void addAdressToDataAndInstructionLabels(nodeInLabelsTable **ptrHead, int amountOfAddAdressToData, int amountOfAddAdressToInstruction);

/* This is a method that receives const char * parameter that represents the name of the label and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method returns the type of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName.
 */
labelType getTypeOfLabelInLabelsTableByName(const char *labelName, nodeInLabelsTable *ptrHead);

/* This is a method that receives const char * parameter that represents the name of the label and nodeInLabelsTable* parameter that represents pointer to the head of labels table.
 * The method returns the adress of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName.
 */
int getAdressOfLabelInLabelsTableByName(const char *labelName, nodeInLabelsTable *ptrHead);

/* This is a method that receives labelType parameter that represents type of label, const char * parameter that represents the name of the label and nodeInLabelsTable** parameter that represents pointer to the head of labels table.
 * The method sets the type of labelName that we get as parameter. The method assume that there is label in labels table that his name is labelName. The method returns nothing.
 */
void setTypeOfLabelInLabelsTableByName(labelType type, const char *labelName, nodeInLabelsTable **ptrHead);

/* This is a method that receives labelType parameter that represents type of label, nodeInLabelsTable* parameter that represents pointer to the head of labels table and FILE ** parameter that represents
 * pointer to file. The method writes all the labels in labels table with the type that we receives as parameter to the file.
 */
void writeAllLabelsWithThisTypeInLabelsTableToFile(labelType type, nodeInLabelsTable *ptrHead, FILE **ptrToFile);


#endif