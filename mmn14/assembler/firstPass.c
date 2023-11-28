/*
 * @author Lior Michaeli
 * @version 23.03.23
 * The file contains methods that handles of first pass.
 * In the first pass we checks errors, found labels in the file and add them to labels table and encodes the text in the file to machine code(we encode all the text except from labels that we will encode them in the second pass after we found all the labels in the file).
 */

/* Finals */
#define MAX_LENGTH_OF_LINE_IN_FILE 82
#define SIZE_OF_DELIM 7
#define SIZE_OF_DELIM_FOR_LABEL_DEFINITION 8
#define LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE 3
#define SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS 2
#define SIZE_OF_LABEL_NAME_IN_LINE 31
#define FIRST_LINE 1
#define FIRST_LETTER_IN_THE_LINE 0
#define ADRESS_OF_EXTERNAL_LABELS 0
/* Includes header files. */
#include "libraries.h"
#include "errors.h"
#include "boolean.h"
#include "guidance.h"
#include "operationName.h"
#include "label.h"
#include "helpMethods.h"
#include "encodeMethodsFirstPass.h"
#include "checkErrorsForFirstPass.h"
#include "printMessage.h"
#include "labelsTable.h"
#include "helpMethodsFirstPass.h"

/* Prototypes - There is an explanation of each function below (where the function appears in this file) */
void handleDataAndStringGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char *ptrLabelName, const char* nameOfFileAfterPreAssembler, const char *fileName, int **ptrDC, int numberOfLine, errors *ptrResult, boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, nodeInLabelsTable ***ptrHead, guidance guidanceType);
void handleExternAndEntryGuidanceForFirstPass(const char lineInFile[], const char* nameOfFileAfterPreAssembler, const char *fileName, boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, int numberOfLine, errors *ptrResult , nodeInLabelsTable ***ptrHead, guidance guidanceType);
void handleInstructionLineForFirstPass(const char *ptrOpName, char lineInFile[] , char tempOfLineInTheFile[], const char *ptrLabelName, char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, const char *fileName, int **ptrIC, errors *ptrResult, int numberOfLine , boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, nodeInLabelsTable ***ptrHead);
void handleLabelsForFirstPass(boolean *ptrFlagThereIsLabel, const char* nameOfFileAfterPreAssembler, char **ptrCurrentWordInLine,  char labelName[], errors *ptrResult, int numberOfLine, nodeInLabelsTable ***ptrHead);
void handleDataGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, int numberOfLine , int ***ptrDC, errors **ptrResult);
void handleStringGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, int numberOfLine , int ***ptrDC, errors **ptrResult);

/* This is a method that receives char* parameter that represents name of file(without extension), int* parameter that represents pointer that points to counter of instruction words that encoded,
 * int* parameter that represents pointer that points to counter of data words that encoded, two char [][] parameters that represents data array and instruction array(stores machine code) and nodeInLabelsTable** parameter that represents a pointer to the head of labels table.
 * The method handles of first pass in the program. The method checks errors in the file, founds labels in the file and adds them to labels table and encodes the text in the file to machine code(we encode all the text except from labels that we will encode them in the second pass after we found all the labels in the file).
 * If there is an error the method will return that there is an error and else will return that there is no error.
 * We assume that the size(in chars) of label name in the line is 31 chars(include null char in the end), assume that the size(in chars) of line in file is 82 chars(include null char in the end)
 */
errors firstPass(char *fileName, int *ptrIC, int *ptrDC, char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], nodeInLabelsTable **ptrHead)
{
    errors result = THERE_IS_NO_ERROR;
    const char delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:", delimForNotLabelDefinition[SIZE_OF_DELIM] = " \n\t\v\f\r"; /* Delimiter for label definition and delimiter for words there are not label definition. */
    char *nameOfFileAfterPreAssembler = NULL, *currentWordInLine = NULL, labelName[SIZE_OF_LABEL_NAME_IN_LINE] , currentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE], tempOfCurrentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE];
    int numberOfLine = FIRST_LINE, lengthNeedForFileAfterPreAssembler;
    FILE *ptrToReadFile;
    boolean flagThereIsLabel, flagThereIsAllocationErrorInLabelsTable = false;
    guidance guidanceType;
    lengthNeedForFileAfterPreAssembler = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE);
    nameOfFileAfterPreAssembler = (char *)malloc(lengthNeedForFileAfterPreAssembler*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of after pre assembler file(.am)(with extension). */
    result = checkAllocationOfCharsPointers(nameOfFileAfterPreAssembler, fileName); /* Checks if the allocation succeed. If yes we will continue. */
    if(result == THERE_IS_NO_ERROR)
    {
        setNameOfFile(&nameOfFileAfterPreAssembler, fileName, ".am"); /* Sets the value of nameOfFileAfterPreAssembler. */
        ptrToReadFile = fopen(nameOfFileAfterPreAssembler, "r");
        /* If there was error allocation in labels table we will not continue in order not cause undefined behavior. */
        while(fgets(currentLineInTheFile, MAX_LENGTH_OF_LINE_IN_FILE, ptrToReadFile) != NULL && flagThereIsAllocationErrorInLabelsTable == false){
            flagThereIsLabel = false;
            strcpy(tempOfCurrentLineInTheFile, currentLineInTheFile); /* Copy the content in currentLineInTheFile to tempOfCurrentLineInTheFile. */
            /* Checks if the current line is not comment line. */
            if(currentLineInTheFile[FIRST_LETTER_IN_THE_LINE] != ';'){
                /* Checks if there is label definition in the file. */
                if (thereIsLabelDefinition(currentLineInTheFile) == true){
                    currentWordInLine = getCurrentWord(currentLineInTheFile, delimForLabelDefinition); /* Gets label. */
                    handleLabelsForFirstPass(&flagThereIsLabel, nameOfFileAfterPreAssembler , &currentWordInLine, labelName, &result, numberOfLine, &ptrHead);
                }
                else
                    currentWordInLine = getCurrentWord(currentLineInTheFile, delimForNotLabelDefinition); /* Gets the first word in the line(if there is no word in the line we will get NULL). */
                /* Checks if the current line is not empty line. */
                if(currentWordInLine != NULL){
                    guidanceType = getGuidance(currentWordInLine);
                    if(guidanceType == dataGuidance || guidanceType == stringGuidance)
                        handleDataAndStringGuidanceForFirstPass(tempOfCurrentLineInTheFile, dataArr, labelName, nameOfFileAfterPreAssembler, fileName, &ptrDC, numberOfLine, &result, flagThereIsLabel, &flagThereIsAllocationErrorInLabelsTable, &ptrHead, guidanceType);
                    else if(guidanceType == externGuidance || guidanceType == entryGuidance)
                        handleExternAndEntryGuidanceForFirstPass(tempOfCurrentLineInTheFile, nameOfFileAfterPreAssembler, fileName, flagThereIsLabel, &flagThereIsAllocationErrorInLabelsTable, numberOfLine, &result , &ptrHead, guidanceType);
                    else{
                        /* Checks if the instruction name is legal operation. */
                        if(getOperation(currentWordInLine) != illegalOperation)
                            handleInstructionLineForFirstPass(currentWordInLine, currentLineInTheFile, tempOfCurrentLineInTheFile, labelName, instructionArr, nameOfFileAfterPreAssembler, fileName, &ptrIC, &result, numberOfLine, flagThereIsLabel, &flagThereIsAllocationErrorInLabelsTable, &ptrHead);
                        else{
                            printMessage(numberOfLine, ILLEGAL_INSTRUCTION_NAME, nameOfFileAfterPreAssembler); /* The instruction name we found not guidance and not legal operation, and that is an error. */
                            result = THERE_IS_AN_ERROR;
                        }
                    }
                }
            }
            numberOfLine++;
        }
        /* Close file and free the memory we allocated. */
        fclose(ptrToReadFile);
        free(nameOfFileAfterPreAssembler);
    }
    if(result == THERE_IS_NO_ERROR && flagThereIsAllocationErrorInLabelsTable == true)
        result = THERE_IS_AN_ERROR; /* There is no errors except from allocation errors. */
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code), const char* parameter that represents pointer that points to name of label(if there is label), const char* parameter that represents name of the file after pre assembler(.am file)(with extension),
 * const char* parameter that represents the name of the file that we handle now without extension, int** parameter that represents pointer that points to counter of data words that encoded, int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) , errors* parameter that represents a pointer to the result of the first pass,
 * boolean parameter that represents flag that says if there is a label in this line, boolean* parameter that represents pointer that points to flag that says if there is an error allocation in labels table, nodeInLabelsTable*** parameter that represents a pointer to the head of labels table and guidance parameter that represents the type of the guidance. The method handles of data and string guidance line for first pass. The method returns nothing.
 */
void handleDataAndStringGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char *ptrLabelName, const char* nameOfFileAfterPreAssembler, const char *fileName, int **ptrDC, int numberOfLine, errors *ptrResult, boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, nodeInLabelsTable ***ptrHead, guidance guidanceType)
{
    nodeInLabelsTable *ptrHeadTemp = **ptrHead; /* Need ptrHeadTemp in order we can activate addLabelToLabelsTable method. */
    if(flagThereIsLabel == true)
    {
        addLabelToLabelsTable(data, **ptrDC, ptrLabelName, fileName, &ptrHeadTemp, &ptrFlagThereIsAllocationErrorInLabelsTable);
        **ptrHead = ptrHeadTemp; /* Set **ptrHead to ptrHeadTemp because the labels table updated. */
    }
    /* If there was error allocation in labels table we will not continue in order not cause undefined behavior. */
    if(*ptrFlagThereIsAllocationErrorInLabelsTable == false)
    {
        if (guidanceType == dataGuidance)
            handleDataGuidanceForFirstPass(lineInFile, dataArr, nameOfFileAfterPreAssembler, numberOfLine, &ptrDC, &ptrResult);
        else
            handleStringGuidanceForFirstPass(lineInFile, dataArr, nameOfFileAfterPreAssembler, numberOfLine, &ptrDC, &ptrResult);
    }
}

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code), const char* parameter that represents name of the file after pre assembler(.am file)(with extension), int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)),
 * int** parameter that represents pointer that points to counter of data words that encoded and errors** parameter that represents a pointer to the result of the first pass. The method handles of data guidance line for first pass. The method returns nothing.
 */
void handleDataGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, int numberOfLine , int ***ptrDC, errors **ptrResult)
{
    if(checkErrorsInDataGuidance(lineInFile, nameOfFileAfterPreAssembler , numberOfLine) == THERE_IS_NO_ERROR)
    {
        /* Checks if *ptrResult is THERE_IS_NO_ERROR, because only if there was not errors in the file until now, we need to encode the current line(if there is an error the encoding process has no meaning(we will not go to second pass)). */
        if(**ptrResult == THERE_IS_NO_ERROR)
            encodeDataGuidance(lineInFile, dataArr, &ptrDC);
    }
    else
        **ptrResult = THERE_IS_AN_ERROR;
}

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code), const char* parameter that represents name of the file after pre assembler(.am file)(with extension), int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)),
 * int** parameter that represents pointer that points to counter of data words that encoded and errors** parameter that represents a pointer to the result of the first pass. The method handles of string guidance line for first pass. The method returns nothing.
 */
void handleStringGuidanceForFirstPass(char lineInFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, int numberOfLine , int ***ptrDC, errors **ptrResult)
{
    if(checkErrorsInStringGuidance(lineInFile, nameOfFileAfterPreAssembler, numberOfLine) == THERE_IS_NO_ERROR)
    {
        /* Checks if *ptrResult is THERE_IS_NO_ERROR, because only if there was not errors in the file until now, we need to encode the current line(if there is an error the encoding process has no meaning(we will not go to second pass)). */
        if(**ptrResult == THERE_IS_NO_ERROR)
            encodeStringGuidance(lineInFile, dataArr, &ptrDC);
    }
    else
        **ptrResult = THERE_IS_AN_ERROR;
}

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension), const char* parameter that represents the name of the file that we handle now without extension, boolean parameter that represents flag that says if there is a label in this line,
 * , boolean* parameter that represents pointer that points to flag that says if there is an error allocation in labels table, int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)), errors* parameter that represents a pointer to the result of the first pass, nodeInLabelsTable*** parameter that represents a pointer to the head of labels table and guidance parameter that represents the type of the guidance.
 * The method handles of extern and entry guidance line for first pass. The method returns nothing.
 */
void handleExternAndEntryGuidanceForFirstPass(const char lineInFile[], const char* nameOfFileAfterPreAssembler, const char *fileName, boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, int numberOfLine, errors *ptrResult , nodeInLabelsTable ***ptrHead, guidance guidanceType)
{
    nodeInLabelsTable *ptrHeadTemp = **ptrHead; /* Need ptrHeadTemp in order we can activate addLabelToLabelsTable method. */
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r";
    char *labelName;
    /* We ignore labels before .extern or .entry. */
    if(flagThereIsLabel == true)
        printMessage(numberOfLine, LABEL_BEFORE_EXTERN_OR_ENTRY_GUIDANCE, nameOfFileAfterPreAssembler); /* We found a label before extern or entry in the line, that is no meaning, and thus we will print warnings. */
    if(checkErrorsInExternAndEntryGuidance(lineInFile, nameOfFileAfterPreAssembler, numberOfLine) != THERE_IS_NO_ERROR)
        *ptrResult = THERE_IS_AN_ERROR;
    else
    {
        labelName = getCurrentWord(NULL, delim); /* Gets the label after the guidance name(extern or entry). */
        if(isNotSaveWord(labelName) == false)
        {
            printMessage(numberOfLine, LABEL_WITH_SAVE_WORD, nameOfFileAfterPreAssembler);
            *ptrResult = THERE_IS_AN_ERROR;
        }
    }
    /* Checks if *ptrResult is THERE_IS_NO_ERROR, because only if there was not errors in the file until now, we will add the current label to labels table. */
    if(*ptrResult == THERE_IS_NO_ERROR && guidanceType == externGuidance)
    {
        addLabelToLabelsTable(external, ADRESS_OF_EXTERNAL_LABELS, labelName, fileName, &ptrHeadTemp, &ptrFlagThereIsAllocationErrorInLabelsTable);
        **ptrHead = ptrHeadTemp; /* Set **ptrHead to ptrHeadTemp because the labels table updated. */
    }
}

/* This is a method that receives const char* parameter that represents pointer to the name of operation in the line, char array parameter that represents line in the file, char array parameter that represents temp of line in the file , const char* parameter that represents pointer that points to name of label(if there is label), char [][] parameter that represents instruction array(stores machine code), const char* parameter that represents name of the file after pre assembler(.am file)(with extension),
 * , const char* parameter that represents the name of the file that we handle now without extension, int** parameter that represents pointer that points to counter of instruction words that encoded, errors* parameter that represents a pointer that points to the result of the first pass, int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)),
 * boolean parameter that represents flag that says if there is a label in this line, boolean* parameter that represents pointer that points to flag that says if there is an error allocation in labels table and nodeInLabelsTable*** parameter that represents a pointer to the head of labels table. The method handles of instruction line for first pass. The method returns nothing.
 */
void handleInstructionLineForFirstPass(const char *ptrOpName, char lineInFile[] , char tempOfLineInTheFile[], const char *ptrLabelName, char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], const char* nameOfFileAfterPreAssembler, const char *fileName, int **ptrIC, errors *ptrResult, int numberOfLine , boolean flagThereIsLabel, boolean *ptrFlagThereIsAllocationErrorInLabelsTable, nodeInLabelsTable ***ptrHead)
{
    nodeInLabelsTable *ptrHeadTemp = **ptrHead; /* Need ptrHeadTemp in order we can activate addLabelToLabelsTable method. */
    boolean flagIsThirdAdressType = false;
    if(flagThereIsLabel == true)
    {
        addLabelToLabelsTable(code, **ptrIC, ptrLabelName, fileName, &ptrHeadTemp, &ptrFlagThereIsAllocationErrorInLabelsTable);
        **ptrHead = ptrHeadTemp; /* Set **ptrHead to ptrHeadTemp because the labels table updated. */
    }
    /* If there was error allocation in labels table we will not continue in order not cause undefined behavior. */
    if(*ptrFlagThereIsAllocationErrorInLabelsTable == false)
    {
        if (checkErrorsInInstructionLine(ptrOpName, tempOfLineInTheFile, lineInFile, nameOfFileAfterPreAssembler, numberOfLine, &flagIsThirdAdressType) == THERE_IS_NO_ERROR)
        {
            /* Checks if *ptrResult is THERE_IS_NO_ERROR, because only if there was not errors in the file until now, we need to encode the current line(if there is an error the encoding process has no meaning(we will not go to second pass)). */
            if (*ptrResult == THERE_IS_NO_ERROR)
                encodeInstructionLine(tempOfLineInTheFile, instructionArr, &ptrIC, flagIsThirdAdressType);
        }
        else
            *ptrResult = THERE_IS_AN_ERROR;
    }
}

/* This is a method that receives boolean* parameter that represents flag that says if there is a label in this line, const char* parameter that represents name of the file after pre assembler(.am file)(with extension), char** parameter that represents pointer that points to the current word in the line, char array parameter that represents name of label, errors* parameter that represents a pointer that points to the result of the first pass,
 * int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) and nodeInLabelsTable*** parameter that represents a pointer to the head of labels table.
 * The method handles of labels for first pass. We will check errors in the current word in the line that we get as parameter that should be a label. If the current word in the line that we get as parameter is a legal label so we will set labelName by ptrCurrentWordInLine, and else we will set ptrResult to the appropriate error. The method returns nothing.
 */
void handleLabelsForFirstPass(boolean *ptrFlagThereIsLabel, const char* nameOfFileAfterPreAssembler, char **ptrCurrentWordInLine,  char labelName[], errors *ptrResult, int numberOfLine, nodeInLabelsTable ***ptrHead)
{
    nodeInLabelsTable *ptrHeadTemp = **ptrHead; /* Need ptrHeadTemp in order we can activate isLabelInLabelsTable method. */
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r";
    /* Checks if the current word in the line that we get as parameter is not reserved word, because labels cannot be reserved words. */
    if(isNotSaveWord(*ptrCurrentWordInLine) == true)
    {
        /* Checks if the current word in the line that we got as parameter is not in the labels table.
         * If the current word in the line that we got as parameter is in the labels table that means she was already defined, and this is an error.
         */
        if(isLabelInLabelsTable(*ptrCurrentWordInLine, ptrHeadTemp) == true)
        {
            printMessage(numberOfLine, TWO_LABELS_WITH_THE_SAME_NAME, nameOfFileAfterPreAssembler);
            *ptrResult = THERE_IS_AN_ERROR;
        }
        /* Checks if the length of the current label is illegal that is mean the current word is illegal label(illegal length of label). */
        else if(isLabelLengthLegal(*ptrCurrentWordInLine) == false)
        {
            printMessage(numberOfLine, ILLEGAL_LABEL_LENGTH, nameOfFileAfterPreAssembler);
            *ptrResult = THERE_IS_AN_ERROR;
        }
        else
        {
            *ptrFlagThereIsLabel = true; /* Legal label */
            strcpy(labelName, *ptrCurrentWordInLine); /* Sets the value of labelName. */
        }
    }
    else
    {
        printMessage(numberOfLine, LABEL_WITH_SAVE_WORD, nameOfFileAfterPreAssembler);
        *ptrResult = THERE_IS_AN_ERROR;
    }
    *ptrCurrentWordInLine = getCurrentWord(NULL, delim); /* Get the next operand. */
    if(*ptrCurrentWordInLine == NULL)
    {
        printMessage(numberOfLine, ILLEGAL_INSTRUCTION_NAME, nameOfFileAfterPreAssembler); /* We not found instruction name after label definition, and that is an error. */
        *ptrResult = THERE_IS_AN_ERROR;
    }
}