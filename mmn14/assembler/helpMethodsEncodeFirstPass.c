/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains help methods for encoding process of first pass in the program.
 */

/* Finals */
#define SIZE_OF_DELIM 10
#define SIZE_OF_DELIM_FOR_LABEL_DEFINITION 8
/* Includes header files. */
#include "libraries.h"
#include "operationName.h"
#include "adressType.h"
#include "boolean.h"
#include "parameterType.h"
#include "helpMethods.h"
#include "helpMethodsFirstPass.h"


/* Prototypes - There is an explanation of each function below (where the function appears in this file). */
void setTypeOfParametersInThirdAdressType(parameterType **firstParameterForThirdAdressType, parameterType **secondParameterForThirdAdressType, const char *word);
void setAdressTypeOfOperandsInNotThirdAdressType(adressType **sourceOperandAdressType, adressType **destOperandAdressType, operationName operationName, const char *word);



/* This is a method that receives char array parameter that represents line in the file, operationName* parameter that represents name of the operation in this line, two adressType* parameters that represents pointer that points to the adress type of source and dest operands in the line
 * , two parameterType* parameters that represents pointer that points to the type of first and second parameters in the line(only in third adress type) and boolean parameter that represents flag that says if the current line is third adress type.
 * The method sets the attributes operation, sourceOperandAdressType, destOperandAdressType, firstParameterForThirdAdressType and secondParameterForThirdAdressType for we can encode instruction line to machine code. The method returns nothing.
 */
void setAttributesInInstructionLine(char lineInTheFile[], operationName *operation, adressType *sourceOperandAdressType, adressType *destOperandAdressType, parameterType *firstParameterForJumpOperands, parameterType *secondParameterForJumpOperands, boolean isThirdAdressType)
{
    const char delimForLabelDefinition[SIZE_OF_DELIM_FOR_LABEL_DEFINITION] = " \n\t\v\f\r:";
    const char delim[SIZE_OF_DELIM] = " \t\n\v\f\r,()";
    char *wordInLine;
    /* Skip to the instruction name in the line(if there is a label we will skip to the instruction name). */
    if (thereIsLabelDefinition(lineInTheFile) == true)
    {
        wordInLine = getCurrentWord(lineInTheFile, delimForLabelDefinition);
        wordInLine = getCurrentWord(NULL, delim);
    }
    else
        wordInLine = getCurrentWord(lineInTheFile, delim);
    *operation = getOperation(wordInLine);
    wordInLine = getCurrentWord(NULL, delim); /* Get first operand after operation name in the line(if there is no operand after operation name so wordInLine will be NULL). */
    /* Checks if there is at least one operand after operation name. */
    if(wordInLine != NULL)
    {
        if(isThirdAdressType == true)
        {
            *destOperandAdressType = thirdAdressType;
            wordInLine = getCurrentWord(NULL, delim); /* Get first parameter in the line. */
            while(wordInLine != NULL)
            {
                setTypeOfParametersInThirdAdressType(&firstParameterForJumpOperands, &secondParameterForJumpOperands, wordInLine);
                wordInLine = getCurrentWord(NULL, delim); /* Get next parameter in the line. */
            }
        }
        else
        {
            while(wordInLine != NULL)
            {
                setAdressTypeOfOperandsInNotThirdAdressType(&sourceOperandAdressType, &destOperandAdressType, *operation, wordInLine);
                wordInLine = getCurrentWord(NULL, delim); /* Get next operand in the line. */
            }
        }
    }
}


/* This is a method that receives two parameterType** parameters that represents pointer that points to the type of first and second parameters in the line(they appear only in third adress type) and const char* parameter that represents word.
 * The method sets the type of the parameters in the line(for third adress type). The method returns nothing.
 */
void setTypeOfParametersInThirdAdressType(parameterType **firstParameterForThirdAdressType, parameterType **secondParameterForThirdAdressType, const char *word)
{
    /* First we will set the first parameter and after it has been set we will set the second parameter. */
    if(**firstParameterForThirdAdressType == nothingParameter)
        **firstParameterForThirdAdressType = getParameterType(word);
    else
        **secondParameterForThirdAdressType = getParameterType(word);
}

/* This is a method that receives two adressType** parameters that represents pointer that points to the adress type of source and dest operands in the line, operationName parameter that represents the name of the operation and const char* parameter that represents word.
 * The method sets the type of the operands in the line(for not third adress type). The method returns nothing.
 */
void setAdressTypeOfOperandsInNotThirdAdressType(adressType **sourceOperandAdressType, adressType **destOperandAdressType, operationName operationName, const char *word)
{
    if(isSecondInstructionGroup(operationName) == true)
        **destOperandAdressType = getAdressType(word); /* In second instruction group there is only dest operand. */
    else
    {
        /* First we will set the source operand and after it has been set we will set the dest operand. */
        if(**sourceOperandAdressType == nothingType)
            **sourceOperandAdressType = getAdressType(word);
        else
            **destOperandAdressType = getAdressType(word);
    }
}
