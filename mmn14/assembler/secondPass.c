/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that handles of second pass.
 * In the second pass we complete the encoding of the text in the file to machine code in that we complete the encoding of labels. Additionally we handle of some more errors.
 */
/* Finals */
#define MAX_LENGTH_OF_LINE_IN_FILE 82
#define SIZE_OF_DELIM 7
#define SIZE_OF_DELIM_FOR_LABEL_DEFINITION 8
#define SIZE_OF_DELIM_FOR_OPERANDS 10
#define FIRST_LINE 1
#define ZERO_OPERANDS 0
#define NO_ADRESS (-1)
#define ZERO_REGISTERS 0
#define TWO_REGISTERS 2
#define LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE 3
#define FIRST_CELL_IN_INSTRUCTION_ARRAY 0
#define SIZE_OF_INSTRUCTION_ARRAY_COLUMNS 2
#define FIRST_LETTER_IN_THE_LINE 0
#define FIRST_LETTER_IN_THE_WORD 0

/* Includes header files. */
#include "libraries.h"
#include "boolean.h"
#include "errors.h"
#include "register.h"
#include "label.h"
#include "operationName.h"
#include "guidance.h"
#include "labelsTable.h"
#include "secondPass.h"
#include "helpMethods.h"
#include "printMessage.h"
#include "encodeMethodsSecondPass.h"

/* Prototypes - There is an explanation of each function below (where the function appears in this file). */
void handleEntryGuidanceForSecondPass(nodeInLabelsTable ***ptrHead, errors *ptrResult, int numberOfLine, const char *nameOfFileAfterPreAssembler);
void handleInstructionLineForSecondPass(char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], const char *nameOfFileAfterPreAssembler , nodeInLabelsTable **ptrHead, int *ptrIC , int numberOfLine, errors *ptrResult);


/* This is a method that receives char* parameter that represents name of file(without extension), char [][] parameter that represents instruction array(stores machine code) and nodeInLabelsTable** parameter that represents a pointer to the head of labels table.
 * The method handles of second pass in the program. The method handles of some more errors(except from the errors we were check in the first pass) and completes the encoding of the text in the file to machine code in that we complete the encoding of labels.
 * If there is an error the method will return the appropriate error and else will return that there is no error.
 */
errors secondPass(char *fileName, char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], nodeInLabelsTable **ptrHead)
{
    errors result = THERE_IS_NO_ERROR;
    char *nameOfFileAfterPreAssembler = NULL, *currentWordInLine = NULL, currentLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE];
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r", delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:";
    int numberOfLine = FIRST_LINE, IC = FIRST_CELL_IN_INSTRUCTION_ARRAY, lengthNeedForFileAfterPreAssembler; /* Need IC variable in order to know to which cell I need to insert the encoding line(machine code). */
    guidance guidanceType; /* Variable that says in case that the current line is not comment line or empty line, what the guidance type of the current line. */
    FILE *ptrToReadFile;
    lengthNeedForFileAfterPreAssembler = getLengthNeedForFileName(fileName, LENGTH_OF_FILE_EXTENSION_FOR_AFTER_PRE_ASSEMBLER_FILE);
    nameOfFileAfterPreAssembler = (char *)malloc(lengthNeedForFileAfterPreAssembler*sizeof(char)); /* Use malloc to allocates memory for the pointer that points to the name of after pre assembler file(.am)(with extension). */
    result = checkAllocationOfCharsPointers(nameOfFileAfterPreAssembler, fileName); /* Checks if the allocation succeed. If yes we will continue. */
    if( result == THERE_IS_NO_ERROR )
    {
        setNameOfFile(&nameOfFileAfterPreAssembler, fileName, ".am"); /* Sets the value of nameOfFileAfterPreAssembler. */
        ptrToReadFile = fopen(nameOfFileAfterPreAssembler, "r");
        while(fgets(currentLineInTheFile, MAX_LENGTH_OF_LINE_IN_FILE, ptrToReadFile) != NULL)
        {
            /* Checks if the current line is not comment line. */
            if(currentLineInTheFile[FIRST_LETTER_IN_THE_LINE] != ';') {
                /* Skip to the instruction name in the line(if there is a label we will skip to the next operand). */
                if (thereIsLabelDefinition(currentLineInTheFile) == true)
                {
                    currentWordInLine = getCurrentWord(currentLineInTheFile, delimForLabelDefinition);
                    currentWordInLine = getCurrentWord(NULL, delim);
                }
                else
                    currentWordInLine = getCurrentWord(currentLineInTheFile, delim);
                /* Checks if the current line is not empty line. */
                if (currentWordInLine != NULL) {
                    guidanceType = getGuidance(currentWordInLine);
                    /* We check if the current line is entry guidance because in the first pass were not gave importance to entry guidance(because we were still dont know all the labels in the file). */
                    if (guidanceType == entryGuidance)
                        handleEntryGuidanceForSecondPass(&ptrHead, &result, numberOfLine, nameOfFileAfterPreAssembler);
                        /* Checks if the instruction name is legal operation. */
                    else if (getOperation(currentWordInLine) != illegalOperation)
                        handleInstructionLineForSecondPass(instructionArr, nameOfFileAfterPreAssembler , ptrHead, &IC, numberOfLine, &result);
                }
            }
            numberOfLine++;
        }
        /* Close file and free the memory we allocated. */
        fclose(ptrToReadFile);
        free(nameOfFileAfterPreAssembler);
    }
    return result;
}

/* This is a method that receives nodeInLabelsTable*** parameter that represents a pointer to the head of labels table, errors* parameter that represents a pointer to the result of second pass,
 * int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) and const char* parameter that represents name of the file after pre assembler(.am file)(with extension). The method handles of entry guidance for second pass. The method returns nothing.
 */
void handleEntryGuidanceForSecondPass(nodeInLabelsTable ***ptrHead, errors *ptrResult, int numberOfLine, const char *nameOfFileAfterPreAssembler)
{
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r";
    char *labelName = getCurrentWord(NULL, delim);
    nodeInLabelsTable *ptrHeadTemp = **ptrHead;
    labelType type = getTypeOfLabelInLabelsTableByName(labelName, ptrHeadTemp); /* Get the type of this label from labels table. */
    if(type == illegalLabelType)
    {
        /* Type is illegal label and that means that this label not exist in the file. */
        printMessage(numberOfLine, LABEL_THAT_NOT_EXIST_IN_ENTRY_GUIDANCE, nameOfFileAfterPreAssembler);
        *ptrResult = THERE_IS_AN_ERROR;
    }
    else if(type == external)
    {
        /* Type is external and that means that this label was defined in the file as entry and external both, and that is illegal. */
        printMessage(numberOfLine, LABEL_EXTERNAL_AND_ENTRY, nameOfFileAfterPreAssembler);
        *ptrResult = THERE_IS_AN_ERROR;
    }
    else
        setTypeOfLabelInLabelsTableByName(entry, labelName, &ptrHeadTemp); /* The label is legal and therefore we set the type of this label to entry. */
}

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), const char* parameter that represents name of the file after pre assembler(.am file)(with extension), nodeInLabelsTable** parameter that represents a pointer to the head of labels table,
 * int* parameter that represents pointer that points to counter of instruction words that encoded, int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) and errors* parameter that represents a pointer to the result of the second pass.
 * The method handles of instruction line for second pass. The method returns nothing.
 */
void handleInstructionLineForSecondPass(char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], const char *nameOfFileAfterPreAssembler , nodeInLabelsTable **ptrHead, int *ptrIC , int numberOfLine, errors *ptrResult)
{
    boolean flagThereIsAnErrorInCurrentLine = false;
    nodeInLabelsTable *ptrHeadTemp = *ptrHead;
    unsigned int adress;
    char *currentOperand = NULL;
    const char delim[SIZE_OF_DELIM_FOR_OPERANDS] = " \n\t\v\f\r,()";
    int counterOfRegisters = ZERO_REGISTERS;
    (*ptrIC)++;
    currentOperand = strtok(NULL, delim); /* Get the first operand in the line after operation name(if there is no operand after operation name so we will get NULL and nothing will be happen). */
    while(currentOperand != NULL && flagThereIsAnErrorInCurrentLine == false)
    {
        /* Checks if the current operand is label. */
        if(getRegister(currentOperand) == illegalRegister && isBeginningOfNumberDefinition(currentOperand[FIRST_LETTER_IN_THE_WORD]) == false)
        {
            adress = getAdressOfLabelInLabelsTableByName(currentOperand, ptrHeadTemp);
            if(adress == NO_ADRESS)
            {
                /* Adress is NO_ADRESS and that means that this label not defined in the file. */
                printMessage(numberOfLine, LABEL_THAT_NOT_DEFINED, nameOfFileAfterPreAssembler);
                *ptrResult = THERE_IS_AN_ERROR;
                flagThereIsAnErrorInCurrentLine = true;
            }
            else
                encodeLabelInInstructionLine(instructionArr, *ptrIC, adress, getTypeOfLabelInLabelsTableByName(currentOperand, ptrHeadTemp)); /* Complete the encoding of labels. */
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