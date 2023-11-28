/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that encodes the text in the file to machine code for first pass.
 */

/* Finals */
#define MAX_LENGTH_OF_LINE_IN_FILE 82
#define SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS 2
#define ZERO_NUMBER 0
#define TEN_NUMBER 10
#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define AMOUNT_OF_BITS_IN_BYTE 8
#define SIZE_OF_DELIM 11
#define SIZE_OF_DELIM_FOR_LABEL_DEFINITION 8
#define START_OF_DEST_OPERAND_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 2
#define START_OF_SOURCE_OPERAND_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 4
#define START_OF_OPCODE_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 6
#define AMOUNT_OF_BITS_OF_OPCODE_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 2
#define START_OF_SECOND_PARAMETER_FIELD_IN_FIRST_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 2
#define START_OF_FIRST_PARAMETER_FIELD_IN_FIRST_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD 4
#define START_OF_NUMBER_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_ADRESS_TYPE 2
#define AMOUNT_OF_BITS_OF_NUMBER_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_ADRESS_TYPE 6
#define START_OF_DEST_REGISTER_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FOURTH_ADRESS_TYPE 2
#define ONE_MEMORY_WORD 1
#define TWO_MEMORY_WORDS 2
#define BASE_10 10

/* Includes header files. */
#include "libraries.h"
#include "operationName.h"
#include "adressType.h"
#include "parameterType.h"
#include "operandType.h"
#include "boolean.h"
#include "encodingType.h"
#include "helpMethodsFirstPass.h"
#include "helpMethods.h"
#include "helpMethodsEncodeFirstPass.h"
/* Prototypes - There is an explanation of each function below (where the function appears in this file). */
void encodeFirstWordInOperationLine(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, adressType sourceOperandAdressType, adressType destOperandAdressType, operationName operation, parameterType firstParameterForThirdAdressType, parameterType secondParameterForThirdAdressType);
void encodeFirstAdressType(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ptrIC, const char *word);
void encodeFourthAdressType(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ptrIC, const char *word, operandType type);
void encodeOtherWordsOfNotThirdAdressTypeInInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, adressType sourceOperandAdressType, adressType destOperandAdressType);
void encodeOtherWordsOfThirdAdressTypeInInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, parameterType firstParameterForThirdAdressType, parameterType secondParameterForThirdAdressType);

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code) and int**** parameter that represents pointer that points to counter of data words that encoded.
 * The method encodes data guidance line to machine code. Each number in the line will encode to word in the the memory. The method returns nothing.
 */
void encodeDataGuidance(const char lineInTheFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrDC)
{
    int number = ZERO_NUMBER , i = 0;
    boolean flagThereIsAnNumber = false, flagThereIsNegativeMark = false;
    while(lineInTheFile[i])
    {
        if(lineInTheFile[i] == '-')
            flagThereIsNegativeMark = true;
        else if(isdigit(lineInTheFile[i]))
        {
            number = (number*TEN_NUMBER) + (lineInTheFile[i]-'0'); /* Calc the current number after the digit we found. */
            flagThereIsAnNumber = true;
        }
        else if(flagThereIsAnNumber == true)
        {
            if(flagThereIsNegativeMark == true)
                setNumberToNegative(&number); /* Set the number to the appropriate negative number. */
            /* Encode the number to the machine code. Insert the machine code to data array. The first 8 bits (0-7 bits) will be in the second column and the other bits will be in first column. */
            dataArr[(****ptrDC)][FIRST_COLUMN] = (char)(number>>AMOUNT_OF_BITS_IN_BYTE);
            dataArr[(****ptrDC)++][SECOND_COLUMN] = (char)number;
            number = ZERO_NUMBER;
            flagThereIsAnNumber = false;
            flagThereIsNegativeMark = false;
        }
        i++;
    }
}

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code) and int**** parameter that represents pointer that points to counter of data words that encoded.
 * The method encodes string guidance line to machine code. Each letter in the string in the line will encode to word in the the memory by his ascii code and in the end we will insert 0 to one more word(represents end of string). The method returns nothing.
 */
void encodeStringGuidance(const char lineInTheFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrDC)
{
    int i = 0;
    unsigned int asciiCode;
    boolean flagThereIsBeginOfString = false, flagThereIsEndOfString = false;
    while(flagThereIsEndOfString == false)
    {
        if(flagThereIsBeginOfString == true && lineInTheFile[i] == '"')
            flagThereIsEndOfString = true;
        else if(flagThereIsBeginOfString == true)
        {
            /* Encode the current letter in the string to the machine code. Insert the machine code to data array. The first 8 bits (0-7 bits) will be in the second column and the other bits will be in first column. */
            asciiCode = (int)lineInTheFile[i];
            dataArr[(****ptrDC)][FIRST_COLUMN] = (char)(asciiCode>>AMOUNT_OF_BITS_IN_BYTE);
            dataArr[(****ptrDC)++][SECOND_COLUMN] = (char)asciiCode;
        }
        else if(lineInTheFile[i] == '"')
            flagThereIsBeginOfString = true;
        i++;
    }
    (****ptrDC)++; /* For end of string. */
}


/* This is a method that receives char array parameter that represents line in the file, char [][] parameter that represents instruction array(stores machine code), int*** parameter that represents pointer that points to counter of instruction words that encoded and
 * boolean parameter that represents flag that says if the current line is third adress type. The method handles of encodes instruction line to machine code. The method returns nothing.
 */
void encodeInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ***ptrIC, boolean isThirdAdressType)
{
    adressType sourceOperandAdressType = nothingType, destOperandAdressType = nothingType;
    parameterType firstParameterForThirdAdressType = nothingParameter, secondParameterForThirdAdressType = nothingParameter;
    operationName operation;
    char tempOfLineInTheFile[MAX_LENGTH_OF_LINE_IN_FILE];
    strcpy(tempOfLineInTheFile, lineInTheFile); /* Copy the content in lineInTheFile to tempOfLineInTheFile. */
    /* Sets the attributes operation, sourceOperandAdressType, destOperandAdressType, firstParameterForThirdAdressType and secondParameterForThirdAdressType. */
    setAttributesInInstructionLine(tempOfLineInTheFile, &operation, &sourceOperandAdressType, &destOperandAdressType, &firstParameterForThirdAdressType, &secondParameterForThirdAdressType, isThirdAdressType);
    encodeFirstWordInOperationLine(instructionArr, &ptrIC, sourceOperandAdressType, destOperandAdressType, operation, firstParameterForThirdAdressType, secondParameterForThirdAdressType);
    /* Checks if there is at least one operand after operation name. */
    if(!((sourceOperandAdressType == nothingType) && (destOperandAdressType == nothingType)))
    {
        if(isThirdAdressType == true)
            encodeOtherWordsOfThirdAdressTypeInInstructionLine(lineInTheFile, instructionArr, &ptrIC, firstParameterForThirdAdressType, secondParameterForThirdAdressType);
        else
            encodeOtherWordsOfNotThirdAdressTypeInInstructionLine(lineInTheFile, instructionArr, &ptrIC, sourceOperandAdressType, destOperandAdressType);
    }
}

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), int**** parameter that represents pointer that points to counter of instruction words that encoded, two adressType parameters that represents the adress type of source and dest operands in the line
 * , operationName parameter that represents name of the operation in this line and two parameterType parameters that represents the type of first and second parameters in the line(they appear only in third adress type). The method encodes the first memory word of the line. The method returns nothing.
 */
void encodeFirstWordInOperationLine(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, adressType sourceOperandAdressType, adressType destOperandAdressType, operationName operation, parameterType firstParameterForThirdAdressType, parameterType secondParameterForThirdAdressType)
{
    /* Encodes the first memory word of the line. */
    instructionArr[****ptrIC][SECOND_COLUMN] |= (char)A; /* ARE field. */
    /* Checks if there is dest operand in the line. */
    if(destOperandAdressType != nothingType)
        instructionArr[****ptrIC][SECOND_COLUMN] |= (char)((int)(destOperandAdressType<<START_OF_DEST_OPERAND_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    /* Checks if there is source operand in the line. */
    if(sourceOperandAdressType != nothingType)
        instructionArr[****ptrIC][SECOND_COLUMN] |= (char)((int)(sourceOperandAdressType<<START_OF_SOURCE_OPERAND_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    /* There is four bits in opcode field. The two rightmost bits will encoded in the second column of instruction array and the two leftmost bits will encoded in the first column of instruction array. */
    instructionArr[****ptrIC][SECOND_COLUMN] |= (char)((int)(operation<<START_OF_OPCODE_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    instructionArr[****ptrIC][FIRST_COLUMN] |= (char)((int)(operation>>AMOUNT_OF_BITS_OF_OPCODE_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    /* Checks if there is second parameter in the line(he appears only in third adress type). */
    if(secondParameterForThirdAdressType != nothingParameter)
        instructionArr[****ptrIC][FIRST_COLUMN] |= (char)((int)(secondParameterForThirdAdressType<<START_OF_SECOND_PARAMETER_FIELD_IN_FIRST_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    /* Checks if there is first parameter in the line(he appears only in third adress type). */
    if(firstParameterForThirdAdressType != nothingParameter)
        instructionArr[****ptrIC][FIRST_COLUMN] |= (char)((int)(firstParameterForThirdAdressType<<START_OF_FIRST_PARAMETER_FIELD_IN_FIRST_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_MEMORY_WORD));
    (****ptrIC)++; /* Continues to the next memory word. */
}

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), int parameter that represents counter of instruction words that encoded and const char* parameter that represents word.
 * The method encodes word memory of first adress type. The method returns nothing.
 */
void encodeFirstAdressType(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ptrIC, const char *word)
{
    unsigned int number = (int)strtol(word, NULL, BASE_10); /* Convert the word that is number to int that represents the number. */
    /* Encodes word memory of first adress type. */
    instructionArr[ptrIC][SECOND_COLUMN] |= (char)A; /* ARE field. */
    /* There is 12 bits in number field. The 6 rightmost bits will encoded in the second column of instruction array and the 6 leftmost bits will encoded in the first column of instruction array. */
    instructionArr[ptrIC][SECOND_COLUMN] |= (char)(number<<START_OF_NUMBER_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_ADRESS_TYPE);
    instructionArr[ptrIC][FIRST_COLUMN] |= (char)(number>>AMOUNT_OF_BITS_OF_NUMBER_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FIRST_ADRESS_TYPE);
}

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), int parameter that represents counter of instruction words that encoded, const char* parameter that represents word and operandType parameter that represents the type of the operand.
 * The method encodes word memory of first adress type. The method returns nothing.
 */
void encodeFourthAdressType(char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ptrIC, const char *word, operandType type)
{
    /* Encodes word memory of fourth adress type. */
    instructionArr[ptrIC][SECOND_COLUMN] |= (char)A; /* ARE field. */
    if(type == dest)
        instructionArr[ptrIC][SECOND_COLUMN] |= (char)(getRegisterNumber(word)<<START_OF_DEST_REGISTER_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_FOURTH_ADRESS_TYPE);
    else
        instructionArr[ptrIC][FIRST_COLUMN] |= (char)(getRegisterNumber(word));
}

/* This is a method that receives char array parameter that represents line in the file, char [][] parameter that represents instruction array(stores machine code), int**** parameter that represents pointer that points to counter of instruction words that encoded and two adressType parameters that represents the adress type of source and dest operands in the line.
 * The method encodes the other memory words of the line for not third adress type. The method returns nothing.
 */
void encodeOtherWordsOfNotThirdAdressTypeInInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, adressType sourceOperandAdressType, adressType destOperandAdressType)
{
    const char delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:";
    const char delim[SIZE_OF_DELIM] = " \t\n\v\f\r,()#";
    char *wordInLine;
    int counterOfWordsThatEncoded = ONE_MEMORY_WORD;
    /* Skip to the instruction name in the line(if there is a label we will skip to the instruction name). */
    if (thereIsLabelDefinition(lineInTheFile) == true)
    {
        wordInLine = getCurrentWord(lineInTheFile, delimForLabelDefinition);
        wordInLine = getCurrentWord(NULL, delim);
    }
    else
        wordInLine = getCurrentWord(lineInTheFile, delim);
    wordInLine = strtok(NULL, delim); /* Get first operand after operation name in the line(if there is no operand after operation name so wordInLine will be NULL). */
    while(wordInLine != NULL)
    {
        /* Checks if we encoded only the first word of this line and there is source operand in the line. */
        if(counterOfWordsThatEncoded == ONE_MEMORY_WORD && sourceOperandAdressType != nothingType)
        {
            /* Encodes the source operand(if the operand is a label we will not encode him because we will encode the labels in the second pass(if there are no errors) after we know all the labels in the file). */
            if(sourceOperandAdressType == firstAdressType)
                encodeFirstAdressType(instructionArr, ****ptrIC, wordInLine);
            else if(sourceOperandAdressType == fourthAdressType)
                encodeFourthAdressType(instructionArr, ****ptrIC, wordInLine, source);
            /* Checks that at least one operand in the line is no register, because if there are two registers in the line so they encoded in one word of memory and thus we will not continue to the next memory word. */
            if( (sourceOperandAdressType != fourthAdressType) || (destOperandAdressType != fourthAdressType) )
                (****ptrIC)++;
            counterOfWordsThatEncoded++;
        }
        else
        {
            /* Encodes the dest operand(if the operand is a label we will not encode him because we will encode the labels in the second pass(if there are no errors) after we know all the labels in the file). */
            if(destOperandAdressType == firstAdressType)
                encodeFirstAdressType(instructionArr, ****ptrIC, wordInLine);
            else if(destOperandAdressType == fourthAdressType)
                encodeFourthAdressType(instructionArr, ****ptrIC, wordInLine, dest);
            (****ptrIC)++;
        }
        wordInLine = strtok(NULL, delim); /* Get the next operand. */
    }
}

/* This is a method that receives char array parameter that represents line in the file, char [][] parameter that represents instruction array(stores machine code), int**** parameter that represents pointer that points to counter of instruction words that encoded and two parameterType parameters that represents the type of first and second parameters in the line(they appear only in third adress type).
 * The method encodes the other memory words of the line for third adress type. The method returns nothing.
 */
void encodeOtherWordsOfThirdAdressTypeInInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrIC, parameterType firstParameterForThirdAdressType, parameterType secondParameterForThirdAdressType)
{
    const char delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:";
    const char delim[SIZE_OF_DELIM] = " \t\n\v\f\r,()#";
    char *wordInLine;
    int counterOfWordsThatEncoded = TWO_MEMORY_WORDS;
    /* Skip to the instruction name in the line(if there is a label we will skip to the instruction name). */
    if (thereIsLabelDefinition(lineInTheFile) == true)
    {
        wordInLine = getCurrentWord(lineInTheFile, delimForLabelDefinition);
        wordInLine = getCurrentWord(NULL, delim);
    }
    else
        wordInLine = getCurrentWord(lineInTheFile, delim);
    wordInLine = strtok(NULL, delim); /* Label */
    (****ptrIC)++; /* For label(we will encode the labels in the second pass(if there are no errors) after we know all the labels in the file). */
    wordInLine = strtok(NULL, delim); /* Get first parameter after label operand in the line. */
    while(wordInLine != NULL)
    {
        /* Checks if we encoded only two memory words of this line and there is first parameter in the line. */
        if(counterOfWordsThatEncoded == TWO_MEMORY_WORDS && firstParameterForThirdAdressType != nothingParameter)
        {
            /* Encodes the first parameter(if the parameter is a label we will not encode him because we will encode the labels in the second pass(if there are no errors) after we know all the labels in the file). */
            if(firstParameterForThirdAdressType == num)
                encodeFirstAdressType(instructionArr, ****ptrIC, wordInLine);
            else if(firstParameterForThirdAdressType == reg)
                encodeFourthAdressType(instructionArr, ****ptrIC, wordInLine, source);
            /* Checks that at least one parameter in the line is no register, because if there are two registers in the line so they encoded in one word of memory and thus we will not continue to the next memory word. */
            if( (firstParameterForThirdAdressType != reg) || (secondParameterForThirdAdressType != reg) )
                (****ptrIC)++;
            counterOfWordsThatEncoded++;
        }
        else
        {
            /* Encodes the second parameter(if the parameter is a label we will not encode him because we will encode the labels in the second pass(if there are no errors) after we know all the labels in the file). */
            if(secondParameterForThirdAdressType == num)
                encodeFirstAdressType(instructionArr, ****ptrIC, wordInLine);
            else if(secondParameterForThirdAdressType == reg)
                encodeFourthAdressType(instructionArr, ****ptrIC, wordInLine, dest);
            (****ptrIC)++;
        }
        wordInLine = strtok(NULL, delim); /* Get the next operand. */
    }
}


