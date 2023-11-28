/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that check errors for the first pass.
 */

/* Finals */
#define AMOUNT_OF_OPERATIONS 16
#define ZERO_LENGTH 0
#define ONE_LENGTH 1
#define FIRST_PARAMETER 1
#define FIRST_OPERAND 1
#define SECOND_OPERAND 2
#define THIRD_OPERAND 3
#define MAX_OPERANDS_IN_LINE 3
#define AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP 2
#define AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP 1
#define AMOUNT_OF_OPERANDS_THIRD_INSTRUCTION_GROUP 0
#define AMOUNT_OF_LABELS_NEED_IN_EXTERN_OR_ENTRY_GUIDANCE 1
#define SIZE_OF_DELIM 10
#define MAX_LENGTH_FOR_LABEL 30

/* Includes header files. */
#include "libraries.h"
#include "errors.h"
#include "operationName.h"
#include "boolean.h"
#include "adressType.h"
#include "helpMethodsFirstPass.h"
#include "helpMethods.h"
#include "operationsOperandAdressTypesTable.h"
#include "printMessage.h"

/* Prototypes - there is an explanation of each function below (where the function appears in this file). */
errors checkLettersInStringGuidance(const char currentLineInTheFile[]);
errors checkNumbersInDataGuidance(const char currentLineInTheFile[]);
errors checkAmountOfOperandsInExternOrEntryGuidance(const char lineInTheFile[]);
errors checkContentOfLabelInExternAndEntryGuidance(const char lineInTheFile[]);
errors checkCommasInGuidance(const char currentLineInTheFile[]);
errors checkCommasInInstructionLine(const char lineInTheFile[]);
errors checkCommas(const char currentLineInTheFile[], int i);
errors checkErrorsForNotThirdAdressTypeOperations(operationName opName, char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine);
errors checkValidityOfContentNumberOperand(char currentChar, int lengthOfWord, boolean *ptrFlagThereIsPlusOrMinusSign);
errors checkValidityOfContentLabelOperand(char currentChar);
errors checkLengthOfNumberOperand(int lengthOfWord, boolean flagThereIsPlusOrMinusSign);
errors checkLengthOfLabelOperand(int lengthOfWord);
errors checkValidityOfOperandsInOperationLineForNotThirdAdressTypeOperations(const char currentLineInTheFile[]);
errors checkAmountOfOperandsInOperationLine(operationName opName, int amountOfOperandsInOperationLine);
errors checkAmountOfOperandsInFirstInstructionGroup(operationName opName, int amountOfOperandsInOperationLine);
errors checkAmountOfOperandsInSecondInstructionGroup(operationName opName, int amountOfOperandsInOperationLine);
errors checkAmountOfOperandsInThirdInstructionGroup(operationName opName, int amountOfOperandsInOperationLine);
errors checkValidityOfOperandInOperationLineForThirdAdressTypeOperations(const char currentLineInTheFile[]);
errors checkValidityOfParametersInOperationLine(const char currentLineInTheFile[], boolean *flagIsFirstParameterIsLabel, boolean *flagIsSecondParameterIsLabel);
errors checkErrorsForThirdAdressTypeOperations(char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine);
errors checkIfThisLegalThirdAdressType(const char currentLineInTheFile[]);
errors checksThatLabelsOperandsAreNotSaveWord(char lineInTheFile[], boolean flagIsFirstOperandIsLabel, boolean flagIsSecondOperandIsLabel, boolean flagIsThirdOperandIsLabel);

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is data guidance line(.data). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInDataGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine)
{
    errors result = THERE_IS_NO_ERROR, error;
    /* Checks if there is an error in numbers or commas in the line with the help of the methods checkNumbersInDataGuidance and checkCommasInGuidance. If there is an error we will call the method
     * printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR.
     */
    if((error = checkNumbersInDataGuidance(lineInTheFile)) != THERE_IS_NO_ERROR || (error = checkCommasInGuidance(lineInTheFile)) != THERE_IS_NO_ERROR)
    {
        printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is string guidance line(.string). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInStringGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine)
{
    errors result = THERE_IS_NO_ERROR, error;
    /* Checks if there is an error in letters(content of the line) in the line with the help of the methods checkLettersInStringGuidance. If there is an error we will call the method printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR. */
    if((error = checkLettersInStringGuidance(lineInTheFile)) != THERE_IS_NO_ERROR)
    {
        printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is extern or entry guidance line(.extern or .entry). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInExternAndEntryGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine)
{
    errors result = THERE_IS_NO_ERROR, error;
    /* Checks if there is an error in the amount of operands in the line or in the content of label in the line with the help of the methods checkAmountOfOperandsInExternOrEntryGuidance and checkContentOfLabelInExternAndEntryGuidance.
     * If there is an error we will call the method printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR.
     */
    if((error = checkAmountOfOperandsInExternOrEntryGuidance(lineInTheFile)) != THERE_IS_NO_ERROR || (error = checkContentOfLabelInExternAndEntryGuidance(lineInTheFile)) != THERE_IS_NO_ERROR)
    {
        printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives const char* parameter that represents pointer to the name of operation in the line, const char array parameter that represents line in the file, char array parameter that represents the same line in the file that we use this for check if labels are not save word
 * (We will use strtok and the first token will be the first operand), const char* parameter that represents name of the file after pre assembler(.am file)(with extension), int parameter that represents the number of the line that we receives as parameter and boolean* parameter that represents pointer to flag that says if the current line is third adress type.
 * The method checks if there is an error in the line, when the line is instruction line. If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInInstructionLine(const char *ptrOpName, char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine, boolean *ptrFlagIsThirdAdressType)
{
    errors result;
    operationName opName = getOperation(ptrOpName);
    if(isJumpOperation(opName) == true)
    {
        /* Checks if there is begin of third adress type for jump operations in this line, that mean there is label after operation name and adjacent to it without space there is '('. */
        if(isBeginOfThirdAdressTypeForJumpOperations(lineInTheFile) == true)
        {
            result = checkIfThisLegalThirdAdressType(lineInTheFile);
            /* Checks if the line is legal third adress type that means result is THERE_IS_NO_ERROR. If not so we will print the appropriate error with the help of the method printMessage. */
            if(result == THERE_IS_NO_ERROR)
            {
                *ptrFlagIsThirdAdressType = true;
                result = checkErrorsForThirdAdressTypeOperations(lineInTheFile, lineInTheFileForCheckLabelsNotSaveWords, nameOfFileAfterPreAssembler, numberOfLine);
            }
            else
                printMessage(numberOfLine, result, nameOfFileAfterPreAssembler);
        }
        else
            result = checkErrorsForNotThirdAdressTypeOperations(opName, lineInTheFile, lineInTheFileForCheckLabelsNotSaveWords, nameOfFileAfterPreAssembler, numberOfLine);
    }
    else
        result = checkErrorsForNotThirdAdressTypeOperations(opName, lineInTheFile, lineInTheFileForCheckLabelsNotSaveWords, nameOfFileAfterPreAssembler, numberOfLine);
    return result;
}

/* This is a method that receives operationName parameter that represents the name of the operation, char array parameter that represents line in the file, char array parameter that represents the same line in the file that we use this for check if labels are not save word(We will use strtok and the first token will be the first operand),
 * const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter. The method checks if there is an error in the line for not third adress type operations. If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsForNotThirdAdressTypeOperations(operationName opName, char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine)
{
    int amountOfOperandsInOperationLine;
    adressType sourceOperandAdressType = nothingType, destOperandAdressType = nothingType;
    boolean flagIsFirstOperandIsLabel = false, flagIsSecondOperandIsLabel = false;
    errors result = THERE_IS_NO_ERROR, error;
    amountOfOperandsInOperationLine = getAmountOfOperandsInOperationLineForNotThirdAdressTypeOperations(lineInTheFile);
    /* Checks if there is an error in the amount of operands in the line or in the commas in the line or in the content of the operands in the line with the help of the methods checkAmountOfOperandsInOperationLine, checkCommasInOperationLine
     * and checkValidityOfOperandsInOperationLineForNotThirdAdressTypeOperations. If there is an error we will call the method printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR.
     */
    if((error = checkAmountOfOperandsInOperationLine(opName, amountOfOperandsInOperationLine)) != THERE_IS_NO_ERROR || (error = checkCommasInInstructionLine(lineInTheFile)) != THERE_IS_NO_ERROR || (error = checkValidityOfOperandsInOperationLineForNotThirdAdressTypeOperations(lineInTheFile)) != THERE_IS_NO_ERROR)
    {
        printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
        result = THERE_IS_AN_ERROR;
    }
    if(result == THERE_IS_NO_ERROR)/* If we found an error we not try to find more errors in the current line.*/
    {
        setOperandsAdressType(lineInTheFile, &sourceOperandAdressType, &destOperandAdressType);
        if(sourceOperandAdressType == secondAdressType)
            flagIsFirstOperandIsLabel = true;
        if(destOperandAdressType == secondAdressType)
            flagIsSecondOperandIsLabel = true;
        /* Checks if there is an error in the content of operands(labels are not save word) or in the adress type of the operands in the line with the help of the methods checksThatOperandsAreNotSaveWord and checkOperandsTypes.
         * If there is an error we will call the method printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR.
         */
        if((error = checksThatLabelsOperandsAreNotSaveWord(lineInTheFileForCheckLabelsNotSaveWords, flagIsFirstOperandIsLabel, flagIsSecondOperandIsLabel, false)) != THERE_IS_NO_ERROR || (error = checkOperandsTypes(opName, sourceOperandAdressType, destOperandAdressType)) != THERE_IS_NO_ERROR)
        {
            printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
            result = THERE_IS_AN_ERROR;
        }
    }
    return result;
}

/* This is a method that receives char array parameter that represents line in the file, char array parameter that represents the same line in the file that we use this for check if labels are not save word(We will use strtok and the first token will be the first operand),
 * const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter. The method checks if there is an error in the line for third adress type operations. If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsForThirdAdressTypeOperations(char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine)
{
    errors result = THERE_IS_NO_ERROR, error;
    boolean flagIsFirstParameterIsLabel = false, flagIsSecondParameterIsLabel = false;
    /* Checks if there is an error in the content of the parameters in the line or if the operands are save words with the help of the methods checkValidityOfParametersInOperationLine and checksThatOperandsAreNotSaveWord. If there is an error we will call the method printMessage that will print the appropriate error and we will set result to THERE_IS_AN_ERROR. */
    if((error = checkValidityOfParametersInOperationLine(lineInTheFile, &flagIsFirstParameterIsLabel, &flagIsSecondParameterIsLabel)) != THERE_IS_NO_ERROR || (error = checksThatLabelsOperandsAreNotSaveWord(lineInTheFileForCheckLabelsNotSaveWords, true, flagIsFirstParameterIsLabel, flagIsSecondParameterIsLabel)) != THERE_IS_NO_ERROR)
    {
        printMessage(numberOfLine, error, nameOfFileAfterPreAssembler);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in letters(content of the line) in the line
 * when the line is string guidance line(.string). If yes the method will return the appropriate error and else will return that there is no error. Strings with inside quotes are illegal.
 */
int checkLettersInStringGuidance(const char lineInTheFile[])
{
    errors result = THERE_IS_NO_ERROR;
    boolean flagThereIsAParameter = false;
    int i = getIndexAfterGuidanceName(lineInTheFile);
    boolean flagThereIsBeginApostrophes = false, flagThereIsEndApostrophes = false;
    while (lineInTheFile[i] && result == THERE_IS_NO_ERROR)
    {
        if(flagThereIsBeginApostrophes == false)
        {
            if(lineInTheFile[i] == '"')
                flagThereIsBeginApostrophes = true;
            else if(isgraph(lineInTheFile[i])) /* Checks if the current char is a graphic letter.If yes that mean there is letters before begin apostrophes, that is an error. */
                result = ILLEGAL_STRING;
        }
        else if(flagThereIsEndApostrophes == false)
        {
            /* Checks if the current char is '"' that mean there is end apostrophes(and was begin apostrophes). If no we will set flagThereIsAParameter to true that mean there is content after begin apostrophes. */
            if(lineInTheFile[i] == '"')
                flagThereIsEndApostrophes = true;
            else
                flagThereIsAParameter = true;
        }
        /* Checks if the current char is graphic letter.If yes that mean there is letters after end apostrophes, that is an error. */
        else if(isgraph(lineInTheFile[i]))
            result = LETTER_AFTER_END_DOUBLE_QUOTES;
        i++;
    }
    if(result == THERE_IS_NO_ERROR)
    {
        /* Checks if there is begin apostrophes and no end apostrophes that there is an error. */
        if(flagThereIsBeginApostrophes == true && flagThereIsEndApostrophes == false)
            result = NO_END_APOSTROPHES_IN_STRING_GUIDANCE;
        /* Checks if there is end apostrophes and no parameter between apostrophes(no content) that there is an error. */
        if(flagThereIsEndApostrophes == true && flagThereIsAParameter == false)
            result = EMPTY_STRING;
        /* Checks if there was not error and no parameter that mean no content(we know this case not empty string, illegal string,
         * letters after end apostrophes or no end apostrophes after begin apostrophes, and thus this is the case of no content after .string), that there is an error.
         */
        if(result == THERE_IS_NO_ERROR && flagThereIsAParameter == false)
            result = NO_PARAMETER_IN_STRING_GUIDANCE;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in numbers in the line
 * when the line is data guidance line(.data). If yes the method will return the appropriate error and else will return that there is no error.
 */
int checkNumbersInDataGuidance(const char lineInTheFile[])
{
    errors result = THERE_IS_NO_ERROR;
    boolean flagThereIsAParameter = false, flagThereIsPlusOrMinusSign = false;
    int i = getIndexAfterGuidanceName(lineInTheFile), lengthOfWord = ZERO_LENGTH;
    while (lineInTheFile[i] && result == THERE_IS_NO_ERROR)
    {
        /* If the current char is a graphic letter that not a comma so we will check the validity of the content in the current number,
         * will set flagThereIsAParameter to true because we found number and increase length of word by one because we found one more letter in the current number.
         */
        if(isgraph(lineInTheFile[i]) && lineInTheFile[i] != ',')
        {
            result = checkValidityOfContentNumberOperand(lineInTheFile[i], lengthOfWord, &flagThereIsPlusOrMinusSign);
            flagThereIsAParameter = true;
            lengthOfWord++;
        }
        /* If the current char is a white space char or comma and lengthOfWord is bigger than 0 that mean there was number so we will check the length of the number(if there is an error in the length). */
        else if(lengthOfWord > ZERO_LENGTH && ((isspace(lineInTheFile[i])) || (lineInTheFile[i] == ',')))
        {
            result = checkLengthOfNumberOperand(lengthOfWord, flagThereIsPlusOrMinusSign);
            flagThereIsPlusOrMinusSign = false;
            lengthOfWord = ZERO_LENGTH;
        }
        i++;
    }
    /* Checks if there was not error and was not parameter(no content (that is not commas) after .data). If yes that is an error. */
    if(result == THERE_IS_NO_ERROR && flagThereIsAParameter == false)
        result = NO_PARAMETER_IN_DATA_GUIDANCE;
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in the amount of operands in the line
 * when the line is extern or entry guidance line(.extern or .entry). If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkAmountOfOperandsInExternOrEntryGuidance(const char lineInTheFile[])
{
    errors result = THERE_IS_NO_ERROR;
    boolean flagThereIsAnLetter = false;
    int i = getIndexAfterGuidanceName(lineInTheFile), counterOfWordsAfterGuidanceName = 0;
    while(lineInTheFile[i])
    {
        if (flagThereIsAnLetter == false)
        {
            /* If the current char is graphic letter that mean there is new word(flagThereIsAnLetter was false) and thus we will increase counterOfWordsAfterGuidanceName by one. */
            if (isgraph(lineInTheFile[i]))
            {
                flagThereIsAnLetter = true;
                counterOfWordsAfterGuidanceName++;
            }
        }
        else if(isspace(lineInTheFile[i]))
            flagThereIsAnLetter = false;
        i++;
    }
    /* Checks if counterOfWordsAfterGuidanceName is not AMOUNT_OF_LABELS_NEED_IN_EXTERN_OR_ENTRY_GUIDANCE(that is 1). If yes that is an error. */
    if(counterOfWordsAfterGuidanceName != AMOUNT_OF_LABELS_NEED_IN_EXTERN_OR_ENTRY_GUIDANCE)
        result = ILLEGAL_AMOUNT_OF_LABELS_IN_EXTERN_OR_ENTRY_GUIDANCE;
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in the content of label in the line
 * when the line is extern or entry guidance line(.extern or .entry). If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkContentOfLabelInExternAndEntryGuidance(const char lineInTheFile[])
{
    errors result = THERE_IS_NO_ERROR;
    boolean flagThereIsAnLetter = false, flagThereIsOperand = false;
    int i = getIndexAfterGuidanceName(lineInTheFile), lengthOfWord = ZERO_LENGTH;
    while(lineInTheFile[i] && result == THERE_IS_NO_ERROR && flagThereIsOperand == false)
    {
        if (flagThereIsAnLetter == false)
        {
            if (isgraph(lineInTheFile[i]))
            {
                /* Checks if the first letter in the new word that we found is not beginning of label. */
                if (isBeginningOfLabel(lineInTheFile[i]) == false)
                    result = ILLEGAL_LABEL;
                flagThereIsAnLetter = true;
                lengthOfWord++;
            }
        }
        else if(isgraph(lineInTheFile[i]))
        {
            if(checkValidityOfContentLabelOperand(lineInTheFile[i]) != THERE_IS_NO_ERROR)
                result = ILLEGAL_LABEL;
            lengthOfWord++;
        }
        else
        {
            result = checkLengthOfLabelOperand(lengthOfWord);
            flagThereIsOperand = false; /* The operand we found ended. */
        }
        i++;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in the commas in the line
 * when the line is guidance line. If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkCommasInGuidance(const char lineInTheFile[])
{
    errors result;
    int i = getIndexAfterGuidanceName(lineInTheFile);
    result = checkCommas(lineInTheFile, i);
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in the commas in the line
 * when the line is instruction line. If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkCommasInInstructionLine(const char lineInTheFile[])
{
    errors result;
    int i = getIndexAfterOperationName(lineInTheFile);
    result = checkCommas(lineInTheFile, i);
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file and int parameter that represents index that from him we will start to check. The method checks if there is an error in the commas in the line.
 * If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkCommas(const char lineInTheFile[], int i)
{
    errors result = THERE_IS_NO_ERROR;
    boolean  flagThereIsComma = false, flagThereIsWord = false, flagThereIsLetter = false;
    while (lineInTheFile[i] && result == THERE_IS_NO_ERROR)
    {
        if(isgraph(lineInTheFile[i]) && (lineInTheFile[i] != ','))
        {
            /* Checks if we found a word and found a comma. If yes so because the current char is graphic letter that not a comma so this legal(after a comma there is new word) and we will set flagThereIsComma and flagThereIsWord to false. */
            if( (flagThereIsComma == true) && (flagThereIsWord == true) )
            {
                flagThereIsComma = false;
                flagThereIsWord = false;
            }
            else if( (flagThereIsComma == false) && (flagThereIsWord == true) )
                result = MISSING_COMMA; /* We found a word and now new word but there is no comma between them and this is illegal. */
            else
                flagThereIsLetter = true;
        }
        else if(lineInTheFile[i] == ',')
        {
            if((flagThereIsLetter == false) && (flagThereIsWord == false) )
                result = ILLEGAL_COMMA; /* We not found a word or letter and the current char is comma that mean there is illegal comma. */
            else if(flagThereIsComma == true)
                result = MULTIPLE_COMMAS; /* We found two commas one after the other and this is illegal. */
            else if( (flagThereIsLetter == true) && (flagThereIsWord == false) )
            {
                flagThereIsWord = true; /* We found a letter and now a comma, that mean we found a word. */
                flagThereIsComma = true;
            }
            else
                flagThereIsComma = true;
        }
        else if(flagThereIsLetter == true)
            flagThereIsWord = true; /* We found a letter and the current char is white space, that mean we found a word. */
        i++;
    }
    /* Checks if we found a comma and not found error. If yes that mean there is a comma after the last word, that is an error. */
    if (flagThereIsComma == true && result == THERE_IS_NO_ERROR)
        result = COMMA_IN_THE_END;
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if the line is legal third adress type. If yes the method will return that there is no error and else will return the appropriate error.
 * The method assume that there is begin of third adress type for jump operations in this line, that mean there is graphic letters after operation name and adjacent to it without space there is '('.
 */
errors checkIfThisLegalThirdAdressType(const char currentLineInTheFile[])
{
    errors result;
    int i = getIndexAfterBeginParenthesisForThirdAdressTypeOperations(currentLineInTheFile);
    boolean flagThereIsEndParenthesis = false, flagThereIsParameter = false, flagThereIsCommaBetweenParameters = false;
    result = checkValidityOfOperandInOperationLineForThirdAdressTypeOperations(currentLineInTheFile); /* For label */
    while((currentLineInTheFile[i]) && (result == THERE_IS_NO_ERROR)){
        if(flagThereIsEndParenthesis == false){
            if(flagThereIsParameter == false){
                if((isgraph(currentLineInTheFile[i])) && (currentLineInTheFile[i] != ','))
                    flagThereIsParameter = true;
                else
                    result = ILLEGAL_THIRD_ADRESS_TYPE; /* There is space or comma after begin parenthesis that is illegal. */
            }
            else if(flagThereIsCommaBetweenParameters == false){
                if(currentLineInTheFile[i] == ','){
                    flagThereIsCommaBetweenParameters = true;
                    flagThereIsParameter = false;/* We found the first parameter and now we will found the second parameter after the comma. */
                }
                else if(isspace(currentLineInTheFile[i]))
                    result = ILLEGAL_THIRD_ADRESS_TYPE; /* We found a space after begin parenthesis and before end parenthesis that is illegal. */
            }
            else if(currentLineInTheFile[i] == ')')
                flagThereIsEndParenthesis = true;
            else if(isspace(currentLineInTheFile[i]) || currentLineInTheFile[i] == ',')
                result = ILLEGAL_THIRD_ADRESS_TYPE; /* We found a space after begin parenthesis and before end parenthesis or another comma besides the one that between parameters, that is illegal. */
        }
        else if(!isspace(currentLineInTheFile[i]))
            result = LETTERS_AFTER_END_PARENTHESIS; /* We found a letter after end parenthesis, that is illegal. */
        i++;
    }
    if(result == THERE_IS_NO_ERROR && flagThereIsEndParenthesis == false)
        result = ILLEGAL_THIRD_ADRESS_TYPE; /* We not found end parenthesis after begin parenthesis(if the label is legal), that is illegal. */
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if the operand in the line is legal label. If yes the method will return that there is no error and else will return the appropriate error. */
errors checkValidityOfOperandInOperationLineForThirdAdressTypeOperations(const char currentLineInTheFile[])
{
    int i = getIndexAfterOperationName(currentLineInTheFile), lengthOfLabelOperand = ZERO_LENGTH;
    errors result = THERE_IS_NO_ERROR;
    boolean flagThereIsLabel = false, flagThereIsBeginParenthesis = false;
    /* The while will end when we will reach to begin parenthesis. */
    while((currentLineInTheFile[i]) && (result == THERE_IS_NO_ERROR) && (flagThereIsBeginParenthesis == false))
    {
        if (flagThereIsLabel == false)
        {
            if (isgraph(currentLineInTheFile[i])) {
                if (isBeginningOfLabel(currentLineInTheFile[i]))
                {
                    flagThereIsLabel = true;
                    lengthOfLabelOperand++;
                }
                else
                    result = OPERAND_MUST_BE_LABEL_IN_THIRD_ADRESS_TYPE; /* We found a graphic letter that is not beginning of label(and before we do not found graphic letters), that is an error. */
            }
        }
        else
        {
            if (currentLineInTheFile[i] == '(')
            {
                result = checkLengthOfLabelOperand(lengthOfLabelOperand);
                flagThereIsBeginParenthesis = true;
            }
            else
            {
                result = checkValidityOfContentLabelOperand(currentLineInTheFile[i]);
                lengthOfLabelOperand++;
            }
        }
        i++;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file and two boolean* parameters that represents flags that says if the appropriate parameter is label.
 * The method checks if there is an error in the content of the parameters in the line and sets the appropriate flag to true if the appropriate parameter is label. If there is an error the method will return the appropriate error and else will return that there is no error.
 */
errors checkValidityOfParametersInOperationLine(const char lineInTheFile[], boolean *ptrFlagIsFirstParameterIsLabel, boolean *ptrFlagIsSecondParameterIsLabel)
{
    int lengthOfWord = ZERO_LENGTH, numberOfParameter = FIRST_PARAMETER, i = getIndexAfterBeginParenthesisForThirdAdressTypeOperations(lineInTheFile);
    boolean flagThereIsLabel = false, flagThereIsNumber = false, flagThereIsPlusOrMinusSign = false, flagThereIsEndParenthesis = false, flagThereIsParameter = false;
    errors result = THERE_IS_NO_ERROR;
    while((lineInTheFile[i]) && (result == THERE_IS_NO_ERROR) && (flagThereIsEndParenthesis == false)){
        if(flagThereIsParameter == false){
            if(isBeginningOfNumberDefinition(lineInTheFile[i]))
                flagThereIsNumber = true;
            /* Checks if the current parameter is legal register that mean he r0-r7 register. */
            else if(isBeginningOfRegister(lineInTheFile[i]) && (lineInTheFile[i+1] != 0 && isdigit(lineInTheFile[i+1]) && lineInTheFile[i+1]<'8') && (lineInTheFile[i+2] == 0 || isspace(lineInTheFile[i+2]) || lineInTheFile[i+2] == ',' || lineInTheFile[i+2] == ')'));
            else if(isBeginningOfLabel(lineInTheFile[i])){
                flagThereIsLabel = true;
                if(numberOfParameter == FIRST_PARAMETER)
                    *ptrFlagIsFirstParameterIsLabel = true;
                else
                    *ptrFlagIsSecondParameterIsLabel = true;
                lengthOfWord++; /* Increase only the length of beginning label parameter because the beginning of number is # and is not part of the number, and we are not check errors about registers. */
            }
            else
                result = ILLEGAL_BEGINNING_OF_PARAMETER;
            flagThereIsParameter = true;
        }
        else{
            /* Checks if the parameter that we found ended. */
            if(lineInTheFile[i] == ',' || lineInTheFile[i] == ')'){
                if(flagThereIsNumber == true){
                    result = checkLengthOfNumberOperand(lengthOfWord, flagThereIsPlusOrMinusSign);
                    flagThereIsNumber = false;
                    flagThereIsPlusOrMinusSign = false;
                }
                else if(flagThereIsLabel == true)
                {
                    result = checkLengthOfLabelOperand(lengthOfWord);
                    flagThereIsLabel = false;
                }
                lengthOfWord = ZERO_LENGTH;
                flagThereIsParameter = false;
                numberOfParameter++; /* We found parameter. */
                if(lineInTheFile[i] == ')')
                    flagThereIsEndParenthesis = true;
            }
            else{
                /* Checks the content of number and label parameters(we are not check errors about registers). */
                if(flagThereIsNumber == true)
                    result = checkValidityOfContentNumberOperand(lineInTheFile[i], lengthOfWord, &flagThereIsPlusOrMinusSign);
                else if(flagThereIsLabel == true)
                    result = checkValidityOfContentLabelOperand(lineInTheFile[i]);
                lengthOfWord++;
            }
        }
        i++;
    }
    return result;
}

/* This is a method that receives const char array parameter that represents line in the file. The method checks if there is an error in the content of the operands in the line. If there is an error the method will return the appropriate error and else will return that there is no error. */
errors checkValidityOfOperandsInOperationLineForNotThirdAdressTypeOperations(const char currentLineInTheFile[])
{
    int lengthOfWord = ZERO_LENGTH, i;
    boolean flagThereIsLetter = false, flagThereIsNumber = false, flagThereIsPlusOrMinusSign = false;
    errors result = THERE_IS_NO_ERROR;
    i = getIndexAfterOperationName(currentLineInTheFile);
    while(currentLineInTheFile[i] && result == THERE_IS_NO_ERROR)
    {
        if(flagThereIsLetter == false){
            if((isgraph(currentLineInTheFile[i])) && (currentLineInTheFile[i] != ',')){
                if(isBeginningOfNumberDefinition(currentLineInTheFile[i]))
                    flagThereIsNumber = true;
                /* No checks errors about registers and thus registers will be in this case(and will no be error). */
                else if(isBeginningOfLabel(currentLineInTheFile[i]))
                    lengthOfWord++; /* Increase only the length of beginning label operand because the beginning of number is # and is not part of the number, and we are not check errors about registers. */
                else
                    result = ILLEGAL_BEGINNING_OF_OPERAND;
                flagThereIsLetter = true;
            }
        }
        else{
            /* Checks if the operand that we found not end. */
            if((isgraph(currentLineInTheFile[i])) && (currentLineInTheFile[i] != ',')){
                /* Checks the content of number and label operands(we are not check errors about registers). */
                if(flagThereIsNumber == true)
                    result = checkValidityOfContentNumberOperand(currentLineInTheFile[i], lengthOfWord, &flagThereIsPlusOrMinusSign);
                else
                    result = checkValidityOfContentLabelOperand(currentLineInTheFile[i]);
                lengthOfWord++;
            }
            else{
                if(flagThereIsNumber == true){
                    result = checkLengthOfNumberOperand(lengthOfWord, flagThereIsPlusOrMinusSign);
                    flagThereIsNumber = false;
                    flagThereIsPlusOrMinusSign = false;
                }
                else
                    result = checkLengthOfLabelOperand(lengthOfWord);
                lengthOfWord = ZERO_LENGTH;
                flagThereIsLetter = false;
            }
        }
        i++;
    }
    return result;
}

/* This is a method that receives char parameter that represents current char, int parameter that represents length of word and boolean parameter that represents pointer to flag that says if there is plus or minus sign. The method checks if there are errors in the content of the number operand.
 * If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkValidityOfContentNumberOperand(char currentChar, int lengthOfWord, boolean *ptrFlagThereIsPlusOrMinusSign)
{
    errors result = THERE_IS_NO_ERROR;
    if(isPlusOrMinusSign(currentChar) == true)
    {
        /* Checks if there is two plus or minus sign or plus or minus sign after number. If yes we will set result to the appropriate error.*/
        if(*ptrFlagThereIsPlusOrMinusSign == true)
            result = MULTIPLE_PLUS_OR_MINUS_SIGN;
        else if(lengthOfWord >= ONE_LENGTH)
            result = PLUS_OR_MINUS_SIGN_AFTER_NUMBER;
        else
            *ptrFlagThereIsPlusOrMinusSign = true;
    }
    else if(!isdigit(currentChar)) /* Checks if the current char is not digit, that mean the number is illegal. */
        result = ILLEGAL_NUMBER;
    return result;
}

/* This is a method that receives char parameter that represents current char. The method checks if there are errors in the content of label operand.
 * If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkValidityOfContentLabelOperand(char currentChar)
{
    errors result = THERE_IS_NO_ERROR;
    /* Checks if the current char is not alphabetic letter and not digit, that mean there is an error, because in label the content(after first letter) must be alphabetic letters or digits. */
    if(!isalnum(currentChar))
        result = ILLEGAL_LABEL;
    return result;
}

/* This is a method that receives int parameter that represents length of word and boolean parameter that represents if there is plus or minus sign. The method checks if there are errors in the length of the number operand.
 * If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkLengthOfNumberOperand(int lengthOfWord, boolean flagThereIsPlusOrMinusSign)
{
    errors result = THERE_IS_NO_ERROR;
    if(flagThereIsPlusOrMinusSign == true)
    {
        /* Checks if there is sign but there are no digits after the sign. */
        if(lengthOfWord == ONE_LENGTH)
            result = THERE_IS_NO_NUMBER_AFTER_SIGN;
    }
    else if(lengthOfWord == ZERO_LENGTH) /* If length of word is 0 that mean there is no number after #, ie there is an error. */
        result = THERE_IS_NO_NUMBER_AFTER_BEGINNING_OF_NUMBER_OPERAND;
    return result;
}

/* This is a method that receives int parameter that represents length of word. The method checks if there are errors in the length of the label operand.
 * If yes the method will return the appropriate error and else will return that there is no error.
 */
errors checkLengthOfLabelOperand(int lengthOfWord)
{
    errors result = THERE_IS_NO_ERROR;
    if(lengthOfWord > MAX_LENGTH_FOR_LABEL)
        result = ILLEGAL_LABEL_LENGTH;
    return result;
}

/* This is a method that receives operationName parameter that represents name of operation and int parameter that represents the amount of operands in operation line.
 * The method checks if amountOfOperandsInOperationLine is equal to the amount that should be to opName. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkAmountOfOperandsInOperationLine(operationName opName, int amountOfOperandsInOperationLine)
{
    errors result;
    /* Checks to which group opName belongs and calls to the appropriate method. */
    if(isFirstInstructionGroup(opName) == true)
        result = checkAmountOfOperandsInFirstInstructionGroup(opName, amountOfOperandsInOperationLine);
    else if(isSecondInstructionGroup(opName) == true)
        result = checkAmountOfOperandsInSecondInstructionGroup(opName, amountOfOperandsInOperationLine);
    else
        result = checkAmountOfOperandsInThirdInstructionGroup(opName, amountOfOperandsInOperationLine);
    return result;
}

/* This is a method that receives operationName parameter that represents name of operation and int parameter that represents the amount of operands in operation line.
 * The method checks if amountOfOperandsInOperationLine is equal to the amount that should be to opName for operations that belongs to first instruction group. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkAmountOfOperandsInFirstInstructionGroup(operationName opName, int amountOfOperandsInOperationLine)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case mov:
            if (amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_MOV;
            break;
        case cmp:
            if (amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_CMP;
            break;
        case add:
            if (amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_ADD;
            break;
        case sub:
            if (amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_SUB;
            break;
        case lea:
            if (amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_LEA;
            break;
        default:
            break;
    }
    return result;
}

/* This is a method that receives operationName parameter that represents name of operation and int parameter that represents the amount of operands in operation line.
 * The method checks if amountOfOperandsInOperationLine is equal to the amount that should be to opName for operations that belongs to second instruction group. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkAmountOfOperandsInSecondInstructionGroup(operationName opName, int amountOfOperandsInOperationLine)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case not:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_NOT;
            break;
        case clr:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_CLR;
            break;
        case inc:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_INC;
            break;
        case dec:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_DEC;
            break;
        case jmp:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_JMP;
            break;
        case bne:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_BNE;
            break;
        case red:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_RED;
            break;
        case prn:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_PRN;
            break;
        case jsr:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_JSR;
            break;
        default:
            break;
    }
    return result;
}

/* This is a method that receives operationName parameter that represents name of operation and int parameter that represents the amount of operands in operation line.
 * The method checks if amountOfOperandsInOperationLine is equal to the amount that should be to opName for operations that belongs to third instruction group. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkAmountOfOperandsInThirdInstructionGroup(operationName opName, int amountOfOperandsInOperationLine)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case rts:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_THIRD_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_RTS;
            break;
        case stop:
            if(amountOfOperandsInOperationLine != AMOUNT_OF_OPERANDS_THIRD_INSTRUCTION_GROUP)
                result = ERROR_IN_AMOUNT_OF_OPERANDS_STOP;
            break;
        default:
            break;
    }
    return result;
}

/* This is a method that receives char array parameter that represents line in the file and three boolean parameters that represents flags that says if the appropriate operand in the line is label(if the amount of operands in the line less than three so the other flags will be false).
 * The method will checks if the labels in the line are not save word. If the labels in the line are not save word so the method will return that there is no error and else will return the appropriate error.
 * The method assume that the line we get as parameter was used in strtok and if we activates strtok on this line now we will get the first operand in the line after operation name(if there is at least one operand in the line).
 */
errors checksThatLabelsOperandsAreNotSaveWord(char lineInTheFile[], boolean flagIsFirstOperandIsLabel, boolean flagIsSecondOperandIsLabel, boolean flagIsThirdOperandIsLabel)
{
    errors result = THERE_IS_NO_ERROR;
    const char delim[SIZE_OF_DELIM] = " \n\t\v\f\r(),";
    char *operand;
    int numberOfOperand = FIRST_OPERAND;
    operand = strtok(NULL, delim); /* Get the first operand. */
    while(operand != NULL && numberOfOperand <= MAX_OPERANDS_IN_LINE)
    {
        /* If the current operand in the line is label, so we will check if the label is save word. */
        if((numberOfOperand == FIRST_OPERAND && flagIsFirstOperandIsLabel == true) || (numberOfOperand == SECOND_OPERAND && flagIsSecondOperandIsLabel == true) || (numberOfOperand == THIRD_OPERAND && flagIsThirdOperandIsLabel == true))
        {
            if(isNotSaveWord(operand) == false)
                result = LABEL_WITH_SAVE_WORD;
        }
        operand = strtok(NULL, delim); /* Get the next operand. */
        numberOfOperand++;
    }
    return result;
}