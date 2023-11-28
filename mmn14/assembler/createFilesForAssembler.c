/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that creates files for assembler(not including .am file).
 */

/* Finals*/
#define MAX_LENGTH_OF_LINE_IN_FILE 82
#define SIZE_OF_DELIM 7
#define SIZE_OF_DELIM_FOR_OPERANDS 10
#define SIZE_OF_DELIM_FOR_LABEL_DEFINITION 8
#define START_ADRESS 100
#define LENGTH_OF_WORD 14
#define LENGTH_OF_END_CHARACTER_FOR_STRINGS 1
#define END_CHARACTER_FOR_STRINGS 0
#define LENGTH_OF_FILE_EXTENSION_FOR_OBJECT_AND_AFTER_PRE_ASSEMBLER_FILES 3
#define LENGTH_OF_FILE_EXTENSION_FOR_EXTERNALS_AND_ENTRIES_FILES 4
#define ZERO_REGISTERS 0
#define TWO_REGISTERS 2
#define SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS 2
#define FIRST_CELL_IN_INSTRUCTION_ARRAY 0
#define FIRST_LETTER_IN_THE_LINE 0
#define FIRST_LETTER_IN_THE_WORD 0

/* Includes header files. */
#include "boolean.h"
#include "label.h"
#include "operationName.h"
#include "register.h"
#include "libraries.h"
#include "labelsTable.h"
#include "helpMethods.h"

/* Prototype - There is an explanation of each function below (where the function appears in this file) */
void handleInstructionLineForCreateExternalsFile(FILE **ptrToExternalsFile, nodeInLabelsTable *ptrHead, int *ptrIC, boolean *ptrFlagThereIsExternalLabelInInstructionLine, char *nameOfExternalsFile);

/* This is a method that receives const char* parameter that represents the name of the file(without extension), two char [][] parameters that represents data array and instruction array(stores machine code), int parameter that represents counter of instruction words that encoded
 * and int parameter that represents counter of data words that encoded. The method creates object file. In the object file will be two numbers in the first line, the value of IC and DC(left to right) and the next lines will be machine code that
 * stored in data array and instruction array. In each line will be the number of the adress and first will be the machine code of instruction array and after will be the machine code of data array.
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createObjectFile(const char *fileName, char dataArr[][SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS], char instructionArr[][SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS], int IC, int DC)
{
    errors result = THERE_IS_NO_ERROR;
    int lengthNeedForNameOfObjectFile, i;
    char *nameOfObjectFile, *currentWordInUniqueBase2Code;
    FILE *ptrToObjectFile;
    currentWordInUniqueBase2Code = (char *)malloc(LENGTH_OF_WORD*sizeof(char)+LENGTH_OF_END_CHARACTER_FOR_STRINGS); /* Use malloc to allocates memory for the pointer that points to current memory word in unique base 2 code. */
    result = checkAllocationOfCharsPointers(currentWordInUniqueBase2Code, fileName); /* Checks if the allocation succeed. If yes we will continue. */
    if(result == THERE_IS_NO_ERROR)
    {
        currentWordInUniqueBase2Code[LENGTH_OF_WORD] = END_CHARACTER_FOR_STRINGS;
        lengthNeedForNameOfObjectFile = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_OBJECT_AND_AFTER_PRE_ASSEMBLER_FILES);
        nameOfObjectFile = (char *)malloc(lengthNeedForNameOfObjectFile*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of object file(with extension). */
        result = checkAllocationOfCharsPointers(nameOfObjectFile, fileName); /* Checks if the allocation succeed. If yes we will continue. */
        if(result == THERE_IS_NO_ERROR)
        {
            setNameOfFile(&nameOfObjectFile, fileName, ".ob"); /* Sets the value of nameOfObjectFile. */
            ptrToObjectFile = fopen(nameOfObjectFile, "w");
            fprintf(ptrToObjectFile, "          %d %d\n",IC, DC);
            /* Like I explained before, in each line will be the number of the adress and first will be the machine code of instruction array and after will be the machine code of data array. */
            for (i = 0; i < IC; i++) {
                fprintf(ptrToObjectFile, "%04d", i+START_ADRESS);
                fprintf(ptrToObjectFile,"                 ");
                convertMachineCodeToUniqueBase2Code(instructionArr, &currentWordInUniqueBase2Code, i);
                fprintf(ptrToObjectFile,"%s\n", currentWordInUniqueBase2Code);
            }
            for (i = 0; i < DC; i++) {
                fprintf(ptrToObjectFile, "%04d", i+START_ADRESS+IC);
                fprintf(ptrToObjectFile,"                 ");
                convertMachineCodeToUniqueBase2Code(dataArr, &currentWordInUniqueBase2Code, i);
                fprintf(ptrToObjectFile,"%s\n", currentWordInUniqueBase2Code);
            }
            /* Close file and free the memory we allocated. */
            fclose(ptrToObjectFile);
            free(nameOfObjectFile);
        }
        free(currentWordInUniqueBase2Code);
    }
    return result;
}

/* This is a method that receives const char* parameter that represents the name of the file(without extension) and nodeInLabelsTable* parameter that represents a pointer to the head of labels table.
 * The method creates entries file(if there is entry label in the file). In the entries file will be all the entries labels in the file. In each line will be label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createEntriesFile(const char *fileName, nodeInLabelsTable *ptrHead)
{
    errors result = THERE_IS_NO_ERROR;
    int lengthNeedForNameOfEntriesFile;
    char *nameOfEntriesFile;
    FILE *ptrToEntriesFile;
    /* Checks if there is entry label in the file in order to know if create entries file. */
    if(thereIsLabelWithThisTypeInLabelsTable(entry, ptrHead) == true)
    {
        lengthNeedForNameOfEntriesFile = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_EXTERNALS_AND_ENTRIES_FILES);
        nameOfEntriesFile = (char *)malloc(lengthNeedForNameOfEntriesFile*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of entries file(with extension). */
        result = checkAllocationOfCharsPointers(nameOfEntriesFile, fileName); /* Checks if the allocation succeed. If yes we will continue. */
        if(result == THERE_IS_NO_ERROR)
        {
            setNameOfFile(&nameOfEntriesFile, fileName, ".ent"); /* Sets the value of nameOfEntriesFile. */
            ptrToEntriesFile = fopen(nameOfEntriesFile, "w");
            /* Write all entry labels in the file to entries file like I explained before. */
            writeAllLabelsWithThisTypeInLabelsTableToFile(entry, ptrHead, &ptrToEntriesFile);
            /* Close file and free the memory we allocated. */
            fclose(ptrToEntriesFile);
            free(nameOfEntriesFile);
        }
    }
    return result;
}

/* This is a method that receives const char* parameter that represents the name of the file(without extension) and nodeInLabelsTable* parameter that represents a pointer to the head of labels table.
 * The method creates externals file(if there is appearance of external label in the file(in instruction line)). In the externals file will be all the appearances of externals labels in the file(in instruction lines). In each line will be appearance of label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createExternalsFile(const char *fileName, nodeInLabelsTable *ptrHead)
{
    errors result = THERE_IS_NO_ERROR;
    int IC = FIRST_CELL_IN_INSTRUCTION_ARRAY, lengthNeedForFileAfterPreAssembler, lengthNeedForNameOfExternalsFile;
    char *nameOfExternalsFile = NULL, *nameOfAfterPreAssemblerFile = NULL , *currentWordInLine = NULL, currentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE];
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r", delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:";
    boolean flagThereIsExternalLabelInInstructionLine = false;
    FILE *ptrToExternalsFile, *ptrToReadFile;
    /* Checks if there is external label in the file in order to know if there is chance to create entries file(in addition we need to check if there is appearance of external label in the file(in instruction line)). */
    if(thereIsLabelWithThisTypeInLabelsTable(external, ptrHead) == true)
    {
        lengthNeedForFileAfterPreAssembler = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_OBJECT_AND_AFTER_PRE_ASSEMBLER_FILES);
        lengthNeedForNameOfExternalsFile = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_EXTERNALS_AND_ENTRIES_FILES);
        nameOfAfterPreAssemblerFile = (char *)malloc(lengthNeedForFileAfterPreAssembler*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of after pre assembler file(.am)(with extension). */
        result = checkAllocationOfCharsPointers(nameOfAfterPreAssemblerFile, fileName); /* Checks if the allocation succeed. If yes we will continue. */
        if(result == THERE_IS_NO_ERROR)
        {
            nameOfExternalsFile = (char *)malloc(lengthNeedForNameOfExternalsFile*sizeof(char));/* Use malloc to allocates memory for the pointer that points to the name of externals file(with extension). */
            result = checkAllocationOfCharsPointers(nameOfExternalsFile, fileName);/* Checks if the allocation succeed. If yes we will continue. */
            if(result == THERE_IS_NO_ERROR)
            {
                setNameOfFile(&nameOfAfterPreAssemblerFile, fileName, ".am"); /* Sets the value of nameOfAfterPreAssemblerFile. */
                setNameOfFile(&nameOfExternalsFile, fileName, ".ext"); /* Sets the value of nameOfExternalsFile. */
                ptrToReadFile = fopen(nameOfAfterPreAssemblerFile, "r");
                while(fgets(currentLineInTheFile, MAX_LENGTH_OF_LINE_IN_FILE, ptrToReadFile) != NULL)
                {
                    if(currentLineInTheFile[FIRST_LETTER_IN_THE_LINE] != ';') {
                        /* Skip to the instruction name in the line(if there is a label we will skip to the next operand). */
                        if (thereIsLabelDefinition(currentLineInTheFile) == true)
                        {
                            currentWordInLine = getCurrentWord(currentLineInTheFile, delimForLabelDefinition);
                            currentWordInLine = getCurrentWord(NULL, delim);
                        }
                        else
                            currentWordInLine = getCurrentWord(currentLineInTheFile, delim);
                        if (currentWordInLine != NULL) {
                            /* Checks if the current line is instruction line(that mean the operand that we get is legal operation). */
                            if (getOperation(currentWordInLine) != illegalOperation)
                                handleInstructionLineForCreateExternalsFile(&ptrToExternalsFile, ptrHead, &IC, &flagThereIsExternalLabelInInstructionLine, nameOfExternalsFile);
                        }
                    }
                }
                /* Close files(we will close the externals file only if we found appearance of external label in the file(in instruction line), because if not so we do not create the external file) and free the memory we allocated. */
                if(flagThereIsExternalLabelInInstructionLine == true)
                    fclose(ptrToExternalsFile);
                fclose(ptrToReadFile);
                free(nameOfExternalsFile);
            }
            free(nameOfAfterPreAssemblerFile);
        }
    }
    return result;
}

/* This is a method that receives FILE** parameter that represents pointer to the externals file, nodeInLabelsTable* parameter that represents a pointer to the head of labels table, int* parameter that represents pointer that points to counter of instruction words that encoded , boolean* parameter that represents pointer that points to flag that says if there is external label in instruction line
 * and char* parameter that represents a pointer to the name of the externals file(with extension). The method handle of instruction lines and creates externals file(if there is appearance of external label in the file(in instruction line)).
 * In the externals file will be all the appearances of externals labels in the file(in instruction lines). In each line will be appearance of label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).
 * The method returns nothing.
 */
void handleInstructionLineForCreateExternalsFile(FILE **ptrToExternalsFile, nodeInLabelsTable *ptrHead, int *ptrIC, boolean *ptrFlagThereIsExternalLabelInInstructionLine, char *nameOfExternalsFile)
{
    char *currentOperand = NULL;
    const char delim[SIZE_OF_DELIM_FOR_OPERANDS] = " \n\t\v\f\r,()";
    int counterOfRegisters = ZERO_REGISTERS;
    /* Skip to the first operand after operation name(if there is no operand after operation name so we will get NULL and nothing will be happen) in the line. */
    currentOperand = strtok(NULL, delim);
    (*ptrIC)++;
    while(currentOperand != NULL)
    {
        /* Checks if the current operand is label. */
        if(getRegister(currentOperand) == illegalRegister && isBeginningOfNumberDefinition(currentOperand[FIRST_LETTER_IN_THE_WORD]) == false)
        {
            if(getTypeOfLabelInLabelsTableByName(currentOperand, ptrHead) == external)
            {
                if(*ptrFlagThereIsExternalLabelInInstructionLine == false)
                {
                    /* We found appearance of external label in instruction line in the file and thus we will create externals file. */
                    *ptrToExternalsFile = fopen(nameOfExternalsFile, "w");
                    *ptrFlagThereIsExternalLabelInInstructionLine = true;
                }
                /* Like I explained before in each line will be appearance of label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).*/
                fprintf(*ptrToExternalsFile,"%-15s%d\n", currentOperand, (*ptrIC + START_ADRESS));
            }

        }
        if(getRegister(currentOperand) != illegalRegister)
            counterOfRegisters++;
        (*ptrIC)++;
        currentOperand = strtok(NULL, delim); /* Get next operand. */
    }
    /* If we found two registers in the line so they encoded in one word of memory, and thus we will decrease the value of ptrIC by one. */
    if(counterOfRegisters == TWO_REGISTERS)
        (*ptrIC)--;
}
