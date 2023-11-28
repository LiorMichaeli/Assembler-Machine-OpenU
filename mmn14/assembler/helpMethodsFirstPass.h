#ifndef helpMethodsFirstPass_H /* #include guards */
#define helpMethodsFirstPass_H

/* Includes header files. */
#include "parameterType.h"
#include "adressType.h"

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation is jump operation, ie whether the operation is jmp, bne or jsr.
 * If yes the method returns true and else false.
 */
boolean isJumpOperation(operationName operation);

/* This is a method that receives const char * parameter that represents name of register. The method returns the number of the register.*/
int getRegisterNumber(const char *registerName);

/* This is a  method that receives const char * parameter that represents pointer word. The method returns the type of the parameter.*/
parameterType getParameterType(const char *word);

/* This is a method that receives const char * parameter that represents pointer to word. The method returns the type of the parameter.*/
adressType getAdressType(const char *word);

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation belongs to first instruction group. If yes the method will return true and else false. */
boolean isFirstInstructionGroup(operationName operation);

/* This is a method that receives operationName parameter that represents operation. The method checks if the operation belongs to second instruction group. If yes the method will return true and else false. */
boolean isSecondInstructionGroup(operationName operation);

/* This is a help method that receives char parameter that represents current char. The method checks if the char is + or - sign. If yes the method will return true and else false. */
boolean isPlusOrMinusSign(char currentChar);

/* This is a method that receives char parameter that represents current char. The method checks if the char is a begin of guidance, ie whether the char is '.'. If yes the method will return true and else false. */
boolean isBeginOfGuidance(char currentChar);

/* This is a help method that receives const char array parameter that represents line in the file. The method returns the amount of the operands in operation line for operations that are not third adress type. */
int getAmountOfOperandsInOperationLineForNotThirdAdressTypeOperations(const char currentLineInTheFile[]);

/* This is a method that receives char parameter that represents current char. The method checks if the char is a end of label definition, ie whether the char is ':'. If yes the method will return true and else false. */
boolean isEndOfLabelDefinition(char currentChar);

/* This is a method that receives const char array that represents line in the file. The method returns the index after the end of operation name in the line. */
int getIndexAfterOperationName(const char currentLineInTheFile[]);

/* This is a method that receives char parameter that represents current char. The method checks if the char is a beginning of register, ie whether the char is 'r'. If yes the method will return true and else false. */
boolean isBeginningOfRegister(char currentChar);

/* This is a method that receives char parameter that represents current char. The method checks if the char is a beginning of label, ie whether the char is alphabetical letter. If yes the method will return true and else false. */
boolean isBeginningOfLabel(char currentChar);

/* This is a method that receives const char* parameter that represents label(without : in the end). The method checks if the length of the label(not include : in the end) is legal, that is means not grater than 30.
 * If the length of the label is legal we will return true, and else false.
 */
boolean isLabelLengthLegal(const char *label);

/* This is a method that receives const char array that represents line in the file, adressType * that represents pointer to the type of adress of source operand and adressType * that represents pointer to the type of adress of dest operand.
 * The method sets the adress types of operands in the line. The method returns nothing.
 */
void setOperandsAdressType(const char currentLineInTheFile[], adressType *ptrSourceOperandAdressType, adressType *ptrDestOperandAdressType);

/* This is a method that receives const char array parameter that represents line in the file. The method checks if in the line there is begin of third adress type for jump operations, ie whether after operation name
 * there is graphic letters with no space and '(' next to them without space. If yes the method will return true and else false.
 */
boolean isBeginOfThirdAdressTypeForJumpOperations(const char currentLineInTheFile[]);

/* This is a method that receives const char array that represents line in the file. The method returns the index after the end of guidance name in the line. */
int getIndexAfterGuidanceName(const char currentLineInTheFile[]);

/* This is a method that receives const char array that represents line in the file. The method returns the index after the begin parenthesis in the line. */
int getIndexAfterBeginParenthesisForThirdAdressTypeOperations(const char lineInTheFile[]);

#endif



