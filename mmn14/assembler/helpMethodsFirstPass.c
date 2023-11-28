/*
 * @author Lior Michaeli
 * @version 17.03.23
 * The program contains help methods for the first pass in the program.
 */

/* Includes header files. */
#include "libraries.h"
#include "boolean.h"
#include "adressType.h"
#include "operationName.h"
#include "parameterType.h"
#include "register.h"
#include "helpMethods.h"

/* Prototype */
void setAdressType(adressType type, adressType **ptrSourceOperandAdressType, adressType **ptrDestOperandAdressType);
int getIndexAfterOperationName(const char currentLineInTheFile[]);

/* Finals */
#define ZERO_OPERANDS 0
#define INDEX_OF_REGISTER_NUMBER 1
#define FIRST_LETTER 0
#define MAX_LENGTH_FOR_LABEL 30

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation is jump operation, ie whether the operation is jmp, bne or jsr.
 * If yes the method returns true and else false.
 */
boolean isJumpOperation(operationName op)
{
    boolean result = false;
    if(op == jmp || op == bne || op == jsr)
        result = true;
    return result;
}

/* This is a method that receives const char * parameter that represents name of register. The method returns the number of the register.*/
int getRegisterNumber(const char *registerName)
{
    return (registerName[INDEX_OF_REGISTER_NUMBER] - '0');
}

/* This is a  method that receives const char * parameter that represents pointer word. The method returns the type of the parameter.*/
parameterType getParameterType(const char *ptrWord)
{
    parameterType result;
    if(ptrWord[FIRST_LETTER] == '#')
        result = num;
    else if(getRegister(ptrWord) != illegalRegister)
        result = reg;
    else
        result = label;
    return result;
}

/* This is a method that receives const char * parameter that represents pointer to word. The method returns the type of the parameter.*/
adressType getAdressType(const char *ptrWord)
{
    adressType result;
    if(ptrWord[FIRST_LETTER] == '#')
        result = firstAdressType;
    else if(getRegister(ptrWord) != illegalRegister)
        result = fourthAdressType;
    else
        result = secondAdressType;
    return result;
}

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation belongs to first instruction group. If yes the method will return true and else false. */
boolean isFirstInstructionGroup(operationName op)
{
    boolean result = false;
    if(op == mov || op == cmp || op == add || op == sub || op == lea)
        result = true;
    return result;
}

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation belongs to second instruction group. If yes the method will return true and else false. */
boolean isSecondInstructionGroup(operationName op)
{
    boolean result = false;
    if(op == not || op == clr || op == inc || op == dec || op == jmp)
        result = true;
    if(op == bne || op == red || op == prn || op == jsr)
        result = true;
    return result;
}

/* This is a help method that receives char parameter that represents current char. The method checks if the char is + or - sign. If yes the method will return true and else false. */
boolean isPlusOrMinusSign(char currentChar)
{
    boolean result = false;
    if(currentChar == '+' || currentChar == '-')
        result = true;
    return result;
}

/* This is a method that receives char parameter that represents current char. The method checks if the char is a begin of guidance, ie whether the char is '.'. If yes the method will return true and else false. */
boolean isBeginOfGuidance(char currentChar)
{
    boolean result = false;
    if(currentChar == '.')
        result = true;
    return result;
}

/* This is a method that receives char parameter that represents current char. The method checks if the char is a end of label definition, ie whether the char is ':'. If yes the method will return true and else false. */
boolean isEndOfLabelDefinition(char currentChar)
{
    boolean result = false;
    if(currentChar == ':')
        result = true;
    return result;
}

/* This is a method that receives char parameter that represents current char. The method checks if the char is a beginning of register, ie whether the char is 'r'. If yes the method will return true and else false. */
boolean isBeginningOfRegister(char currentChar)
{
    boolean result = false;
    if(currentChar == 'r')
        result = true;
    return result;
}

/* This is a method that receives char parameter that represents current char. The method checks if the char is a beginning of label, ie whether the char is alphabetical letter. If yes the method will return true and else false. */
boolean isBeginningOfLabel(char currentChar)
{
    boolean result = false;
    if(isalpha(currentChar))
        result = true;
    return result;
}

/* This is a method that receives const char* parameter that represents label(without : in the end). The method checks if the length of the label(not include : in the end) is legal, that is means not grater than 30.
 * If the length of the label is legal we will return true, and else false.
 */
boolean isLabelLengthLegal(const char *label)
{
    boolean result = true;
    if(strlen(label) > MAX_LENGTH_FOR_LABEL)
        result = false;
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if in the line there is begin of third adress type for jump operations, ie whether after operation name
 * there is graphic letters with no space and '(' next to them without space. If yes the method will return true and else false.
 */
boolean isBeginOfThirdAdressTypeForJumpOperations(const char lineInTheFile[])
{
    int i = getIndexAfterOperationName(lineInTheFile); /* Get the index after operation name in the line. */
    boolean result = false, flagThereIsBeginOfThirdAdress = true , flagThereIsLetter = false;
    while((lineInTheFile[i]) && (result == false) && (flagThereIsBeginOfThirdAdress == true))
    {
        /* This if checks if flagThereIsLetter is false, ie whether there was not a letter until now. If yes we check if the current char in the line is graphic letter, and if yes if the char is a comma this is mean
         * that this not beginning of third adress type and thus we set flagThereIsBeginOfThirdAdress to false. Else(If the char is not a comma) we set flagThereIsLetter to true.
         */
        if(flagThereIsLetter == false)
        {
            if(isgraph(lineInTheFile[i])){
                if(lineInTheFile[i] != ',')
                    flagThereIsLetter = true;
                else
                    flagThereIsBeginOfThirdAdress= false;
            }
        }
        else
        {
            /* Checks if the current char in the line is '('. If yes that means that in the line there is begin of third adress type for jump operations, and thus we set result to true.
             * Else if the current char in the line is white space or a comma this is mean that this not beginning of third adress type and thus we set flagThereIsBeginOfThirdAdress to false.
             */
            if(lineInTheFile[i] == '(')
                result = true;
            else if((isspace(lineInTheFile[i])) || (lineInTheFile[i] == ','))
                flagThereIsBeginOfThirdAdress = false;
        }
        i++;
    }
    return result;
}

/* This is a method that receives adressType parameter that represents type of adress, adressType ** that represents pointer to the type of adress of source operand and adressType ** that represents pointer to the type of adress of dest operand.
 * The method sets the variables ptrSourceOperandAdressType or ptrDestOperandAdressType(dependent the value of ptrSourceOperandAdressType) to type. The method returns nothing.
 */
void setAdressType(adressType type, adressType **ptrSourceOperandAdressType, adressType **ptrDestOperandAdressType)
{
    if(**ptrSourceOperandAdressType == nothingType)
        **ptrSourceOperandAdressType = type;
    else
        **ptrDestOperandAdressType = type;
}

/* This is a method that receives const char array that represents line in the file, adressType * that represents pointer to the type of adress of source operand and adressType * that represents pointer to the type of adress of dest operand.
 * The method sets the adress types of operands in the line. The method returns nothing.
 */
void setOperandsAdressType(const char lineInTheFile[], adressType *ptrSourceOperandAdressType, adressType *ptrDestOperandAdressType)
{
    int i;
    boolean flagThereIsLetter = false;
    i = getIndexAfterOperationName(lineInTheFile); /* Get the index after operation name in the line. */
    while(lineInTheFile[i])
    {
        /* This if checks if flagThereIsLetter is false, ie whether there was not a letter until now. If yes we check if the current char in the line is graphic letter and is not a comma.
         * If yes we check which operand this word(checks the beginning of the operand and according this we know which operand this word, because we was check that this line is legal and thus the operand(current word)
         * must be number,register or label). When we know which operand this word we call to setAdressType method that sets the adress type of ptrSourceOperandAdressType or ptrDestOperandAdressType
         * (In the beginning the source operand will be set and after dest operand will be set) to the appropriate type and in end will set flagThereIsLetter to true.
         */
        if(flagThereIsLetter == false)
        {
            if((isgraph(lineInTheFile[i])) && (lineInTheFile[i] != ','))
            {
                if(isBeginningOfNumberDefinition(lineInTheFile[i]))
                    setAdressType(firstAdressType, &ptrSourceOperandAdressType, &ptrDestOperandAdressType);
                else if(isBeginningOfRegister(lineInTheFile[i]) && (lineInTheFile[i+1] != 0 && isdigit(lineInTheFile[i+1]) && lineInTheFile[i+1]<'8') && (lineInTheFile[i+2] == 0 || isspace(lineInTheFile[i+2]) || lineInTheFile[i+2] == ','))
                    setAdressType(fourthAdressType, &ptrSourceOperandAdressType, &ptrDestOperandAdressType);
                else if(isBeginningOfLabel(lineInTheFile[i]))
                    setAdressType(secondAdressType, &ptrSourceOperandAdressType, &ptrDestOperandAdressType);
                flagThereIsLetter = true;
            }
        }
        else if((isspace(lineInTheFile[i])) || (lineInTheFile[i] == ',')) /* If current char is white space or a comma so the word we found end and thus we will set flagThereIsLetter to false.*/
            flagThereIsLetter = false;
        i++;
    }
    /* Checks if we set ptrSourceOperandAdressType but not set ptrDestOperandAdressType, ie there was only one operand after operation name. If yes so we will set ptrDestOperandAdressType to ptrSourceOperandAdressType
     * and ptrSourceOperandAdressType to nothingType.
     */
    if((*ptrSourceOperandAdressType != nothingType) && (*ptrDestOperandAdressType == nothingType))
    {
        *ptrDestOperandAdressType = *ptrSourceOperandAdressType;
        *ptrSourceOperandAdressType = nothingType;
    }
}

/* This is a help method that receives const char array parameter that represents line in the file. The method returns the amount of the operands in operation line for operations that are not third adress type. */
int getAmountOfOperandsInOperationLineForNotThirdAdressTypeOperations(const char lineInTheFile[])
{
    int i, result = ZERO_OPERANDS;
    boolean flagThereIsWord = false;
    i = getIndexAfterOperationName(lineInTheFile); /* Get the index after operation name in the line. */
    while(lineInTheFile[i])
    {
        /* Checks if the current char is graphic letter and not a comma. If yes that mean there is a operand and therefore we will set flagThereIsWord to true. Else the current char is white space or comma and
         * if flagThereIsWord is true so that mean the operand end and therefore we will increase result by one(because we found more operand) and will set flagThereIsWord to false.
         */
        if(isgraph(lineInTheFile[i]) && lineInTheFile[i] != ',')
                flagThereIsWord = true;
        else if(flagThereIsWord == true)
        {
            result++;
            flagThereIsWord = false;
        }
        i++;
    }
    return result;
}

/* This is a method that receives const char array that represents line in the file. The method returns the index after the end of operation name in the line. */
int getIndexAfterOperationName(const char lineInTheFile[])
{
    int i=0;
    boolean flagThereIsOperationName = false, flagThereIsLetter = false;
    while (lineInTheFile[i] && flagThereIsOperationName == false)
    {
        /* Checks if flagThereIsLetter is false and the current char is graphic letter. If yes that mean we found word in the line and thus we will set flagThereIsLetter to true.
         * Else if flagThereIsLetter is true and the current char is white space char, so that mean the word that we found end. If the the previous char is end of label definition, so
         * the word we found was label, and thus we will set flagThereIsLetter to false. Else we know that the word we found is not label and therefore we found operation name, and thus we will
         * set flagThereIsOperationName to true.
         */
        if(flagThereIsLetter == false && isgraph(lineInTheFile[i]))
            flagThereIsLetter = true;
        else if(flagThereIsLetter == true && isspace(lineInTheFile[i]))
        {
            if(isEndOfLabelDefinition(lineInTheFile[i-1]))
                flagThereIsLetter = false;
            else
                flagThereIsOperationName = true;
        }
        i++;
    }
    return i;
}

/* This is a method that receives const char array that represents line in the file. The method returns the index after the end of guidance name in the line. */
int getIndexAfterGuidanceName(const char lineInTheFile[])
{
    int i = 0;
    boolean flagThereIsEndOfGuidance = false, flagThereIsBeginOfGuidance = false;
    while (lineInTheFile[i] && flagThereIsEndOfGuidance == false)
    {
        /* Checks if the current char is begin of guidance. If yes that mean we found start of guidance name and thus we will set flagThereIsBeginOfGuidance to true.
         * Else if the current char is white space char and flagThereIsBeginOfGuidance is true, that mean we reach after the end of guidance and thus we will set flagThereIsEndOfGuidance to true.
         */
        if (isBeginOfGuidance(lineInTheFile[i]) == true)
            flagThereIsBeginOfGuidance = true;
        else if ((isspace(lineInTheFile[i])) && (flagThereIsBeginOfGuidance == true))
            flagThereIsEndOfGuidance = true;
        i++;
    }
    return i;
}

/* This is a method that receives const char array that represents line in the file. The method returns the index after the begin parenthesis in the line. */
int getIndexAfterBeginParenthesisForThirdAdressTypeOperations(const char lineInTheFile[])
{
    int i = 0;
    boolean flagThereIsBeginParenthesis = false;
    while (lineInTheFile[i] && flagThereIsBeginParenthesis == false)
    {
        if(lineInTheFile[i] == '(')
            flagThereIsBeginParenthesis = true;
        i++;
    }
    return i;
}

