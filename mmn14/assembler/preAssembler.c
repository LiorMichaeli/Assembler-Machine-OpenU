/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The file contains methods that handles of pre assembler pass.
 * In the pre assembler pass we create .am file that in this file will be the content that was in the assembly file but after we lay out the macros that were in the file.
 * If there is an error in the macros in the file we will print the error(we need to check that are no two macros with the same name and that not exist macro with save word) and not continue to the next passes.
 * We assume that each macro definition has endmcr line, that represents end of macro definition. Additionally, we assume that there are no nested macro settings in the system
 * and that macro definition always will be before calling to the macro.
 */

/* Finals */
#define MAX_LENGTH_OF_LINE_IN_FILE 82
#define LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE 3
#define LENGTH_OF_FILE_EXTENSION_FOR_ASSEMBLY_FILE 3
#define SIZE_OF_DELIM 7
#define FIRST_LINE 1
/* Includes header files. */
#include "libraries.h"
#include "boolean.h"
#include "errors.h"
#include "macrosTable.h"
#include "helpMethodsPreAssembler.h"
#include "printMessage.h"
#include "helpMethods.h"

/* Prototypes - There is an explanation of each function below (where the function appears in this file). */
void handleStartMacroDefinition(boolean *ptrFlagThereIsMcrDefinition, int numberOfLine, errors *ptrResult, nodeInMacrosTable **ptrHead, const char *nameOfAssemblyFile, const char *fileName, boolean *ptrFlagThereIsAllocationErrorInMacrosTable);
void handleContentOfMacro(char lineInTheFile[], char *wordInLine, const char *fileName, boolean *ptrFlagThereIsMcrDefinition, boolean *ptrFlagThereIsAllocationErrorInMacrosTable, nodeInMacrosTable **ptrHead);

/* This is a method that receives char* parameter that represents name of file(without extension). The method handles of pre assembler pass. The method creates .am file that in this file will be the content that was in the assembly file but after we lay out the macros that were in the file.
 * If there is an error in the macros in the file we will print the error and not continue to the next passes. If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors analyzeMacros(char *fileName)
{
    char *currentWordInLine = NULL, *nameOfFileAfterPreAssembler = NULL, *nameOfAssemblyFile = NULL, *infoOfMacro = NULL, currentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE], tempOfCurrentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE];
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r";
    errors result = THERE_IS_NO_ERROR;
    int lengthNeedForFileName, numberOfLine = FIRST_LINE;
    nodeInMacrosTable *ptrHead = NULL;
    FILE *ptrToReadFile, *ptrToWriteFile;
    boolean flagThereIsMcrDefinition = false, flagThereIsAllocationErrorInMacrosTable = false;
    lengthNeedForFileName = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_ASSEMBLY_FILE);
    nameOfAssemblyFile = (char *)malloc(lengthNeedForFileName*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of assembly file(with extension). */
    result = checkAllocationOfCharsPointers(nameOfAssemblyFile, fileName); /* Checks if the allocation succeed. If yes we will continue. */
    if(result == THERE_IS_NO_ERROR)
    {
        setNameOfFile(&nameOfAssemblyFile, fileName, ".as"); /* Sets the value of nameOfAssemblyFile. */
        ptrToReadFile = fopen(nameOfAssemblyFile, "r");
        /* Checks if there was no problems in the opening of the file. */
        if(checkOpenFile(ptrToReadFile, fileName) == THERE_IS_NO_ERROR){
            lengthNeedForFileName = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE);
            nameOfFileAfterPreAssembler = (char *)malloc(lengthNeedForFileName*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of after pre assembler file(.am)(with extension). */
            result = checkAllocationOfCharsPointers(nameOfFileAfterPreAssembler, fileName); /* Checks if the allocation succeed. If yes we will continue.*/
            if(result == THERE_IS_NO_ERROR)
            {
                setNameOfFile(&nameOfFileAfterPreAssembler, fileName, ".am"); /* Sets the value of nameOfFileAfterPreAssembler. */
                ptrToWriteFile = fopen(nameOfFileAfterPreAssembler, "w");
                /* If there was error allocation in macros table we will not continue in order not cause undefined behavior. */
                while(fgets(currentLineInTheFile, MAX_LENGTH_OF_LINE_IN_FILE, ptrToReadFile) != NULL && flagThereIsAllocationErrorInMacrosTable == false){
                    strcpy(tempOfCurrentLineInTheFile, currentLineInTheFile); /* Copy the content in currentLineInTheFile to tempOfCurrentLineInTheFile. */
                    currentWordInLine = getCurrentWord(tempOfCurrentLineInTheFile, delim);
                    /* Checks if the current line is not empty line. */
                    if(currentWordInLine != NULL){
                        /* Checks if we in macro definition(in the content of the macro definition). */
                        if(flagThereIsMcrDefinition == true)
                            handleContentOfMacro(currentLineInTheFile, currentWordInLine, fileName, &flagThereIsMcrDefinition, &flagThereIsAllocationErrorInMacrosTable, &ptrHead);
                        /* Checks if the current word is macro. If the macro is empty nothing will be printed. */
                        else if(isWordMacroInTheTable(currentWordInLine, ptrHead) == true)
                        {
                            if((infoOfMacro = getInfoByMacroName(currentWordInLine, ptrHead)) != NULL)
                                fprintf(ptrToWriteFile, "%s", infoOfMacro);
                        }
                        /* Checks if the current word is mcr. */
                        else if(isStartMacroDefinition(currentWordInLine) == true)
                            handleStartMacroDefinition(&flagThereIsMcrDefinition, numberOfLine, &result, &ptrHead, nameOfAssemblyFile, fileName, &flagThereIsAllocationErrorInMacrosTable);
                        else
                            fprintf(ptrToWriteFile, "%s", currentLineInTheFile);
                    }
                    else
                        fprintf(ptrToWriteFile, "%s", currentLineInTheFile);
                    numberOfLine++;
                }
                /* Close files and free the memory we allocated. */
                fclose(ptrToWriteFile);
                free(nameOfFileAfterPreAssembler);
            }
            fclose(ptrToReadFile); /* Close file. */
        }
        else
            result = THERE_IS_AN_ERROR;
        /* Free the memory we allocated. */
        free(nameOfAssemblyFile);
    }
    freeMemoryMacrosTable(&ptrHead);/* Free the memory in macros table. */
    if(result == THERE_IS_NO_ERROR && flagThereIsAllocationErrorInMacrosTable == true)
        result = THERE_IS_AN_ERROR; /* There is no errors except from allocation errors. */
    return result;
}

/* This is a method that receives boolean* parameter that represents pointer that points to flag that says if we in macro definition, int parameter that represents the number of the line(according the lines in the assembly file), errors* parameter that represents a pointer to the result of the pre assembler pass
 * ,nodeInMacrosTable** parameter that represents a pointer to the head of macros table, const char* parameter that represents the name of the assembly file(with extension), const char* parameter that represents the name of the file that we handle now without extension
 * and boolean* parameter that represents pointer that points to flag that says if there is an error allocation in macros table. The method handles of start macro definition for pre assembler pass. The method returns nothing.
 */
void handleStartMacroDefinition(boolean *ptrFlagThereIsMcrDefinition, int numberOfLine, errors *ptrResult, nodeInMacrosTable **ptrHead, const char *nameOfAssemblyFile, const char *fileName, boolean *ptrFlagThereIsAllocationErrorInMacrosTable)
{
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r";
    char *macroName;
    nodeInMacrosTable *ptrHeadTemp = *ptrHead; /* Need ptrHeadTemp in order we can activate addMacroToMacrosTable method. */
    macroName = getCurrentWord(NULL, delim);
    if(isNotSaveWord(macroName) == true)
    {
        if(isWordMacroInTheTable(macroName, ptrHeadTemp) == false)
        {
            addMacroToMacrosTable(macroName, fileName, &ptrHeadTemp, &ptrFlagThereIsAllocationErrorInMacrosTable);
            *ptrHead = ptrHeadTemp; /* Set *ptrHead to ptrHeadTemp because the macros table updated. */
            *ptrFlagThereIsMcrDefinition = true; /* We found start macro definition and thus we in macro definition. In other cases in this method we consider this line as not macro definition line. */
        }
        else
        {
            printMessage(numberOfLine ,TWO_MACROS_WITH_THE_SAME_NAME, nameOfAssemblyFile);
            *ptrResult = THERE_IS_AN_ERROR;
        }
    }
    else
    {
        printMessage(numberOfLine ,MACRO_WITH_SAVE_WORD, nameOfAssemblyFile);
        *ptrResult = THERE_IS_AN_ERROR;
    }
}

/* This is a method that receives char array that represents line in the file, char* that represents word in the line, const char* parameter that represents the name of the file that we handle now without extension, boolean* parameter that represents pointer that points to flag that says if we in macro definition,
 * , boolean* parameter that represents pointer that points to flag that says if there is an error allocation in macros table and nodeInMacrosTable** parameter that represents a pointer to the head of macros table.
 * The method handles of content of macro definition for pre assembler pass. The method returns nothing.
 */
void handleContentOfMacro(char lineInTheFile[], char *wordInLine, const char *fileName, boolean *ptrFlagThereIsMcrDefinition, boolean *ptrFlagThereIsAllocationErrorInMacrosTable, nodeInMacrosTable **ptrHead)
{
    nodeInMacrosTable *ptrHeadTemp = *ptrHead; /* Need ptrHeadTemp in order we can activate addInfoToLastMacro method. */
    if(isEndMacroDefinition(wordInLine) == false)
        addInfoToLastMacro(lineInTheFile, fileName, &ptrHeadTemp, &ptrFlagThereIsAllocationErrorInMacrosTable); /* We add info to the last macro in the macros table, that is to the macro in this macro definition. */
    else
        *ptrFlagThereIsMcrDefinition = false; /* We reach to the end of macro definition. */
}