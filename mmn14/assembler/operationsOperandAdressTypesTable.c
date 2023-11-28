/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that dealing the macro table.
 */

/* Includes header files. */
#include "libraries.h"
#include "errors.h"
#include "operationName.h"
#include "adressType.h"
#include "boolean.h"
#include "helpMethodsFirstPass.h"

/* Finals */
#define AMOUNT_OF_OPERATIONS 16
#define AMOUNT_OF_OPERANDS_FIRST_INSTRUCTION_GROUP 2
#define AMOUNT_OF_OPERANDS_SECOND_INSTRUCTION_GROUP 1
#define AMOUNT_OF_OPERANDS_THIRD_INSTRUCTION_GROUP 0
#define ON_BIT 1
#define OFF_BIT 0
#define AMOUNT_OF_BITS_FOR_OPERAND 2
#define FIRST_ENCODE_TYPE 0
#define SECOND_ENCODE_TYPE 1
#define THIRD_ENCODE_TYPE 2
#define FOURTH_ENCODE_TYPE 3

/* Define data structure */
struct operationOperandAdressType
{
    char destinationOperandAdressTypes;
    char sourceOperandAdressTypes;
};
typedef struct operationOperandAdressType operationOperandAdressTypes;

/* Prototypes - there is an explanation of each function below (where the function appears in this file). */
void initDestinationOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName name, int firstType, int secondType, int thirdType, int fourthType);
void initSourceOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName name, int firstType, int secondType, int thirdType, int fourthType);
void setBitsToZero(operationOperandAdressTypes operationsOperandAdressTypesTable[], int operationNumber);
errors checkOperandsTypesInFirstInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType);
errors checkOperandsTypesInSecondInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType);
errors checkOperandsTypesInThirdInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType);
boolean isLegalSourceOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType);
boolean isLegalDestinationOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType destOperandAdressType);

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation. The method inits the adress types of operands for each operation in the operations table. The method returns nothing. */
void initOperationsOperandAdressTypesTable(operationOperandAdressTypes operationsOperandAdressTypesTable[])
{
    int i;
    /* Sets all bits in the array to zero. */
    for (i = 0; i < AMOUNT_OF_OPERATIONS; i++) {
        setBitsToZero(operationsOperandAdressTypesTable, i);
    }
    /* Init adress type of source operand and dest operand for all operations in operationsOperandAdressTypesTable(operations that have not dest operands so we not will init them(they will stay 0), and also thing with source operands). */
    initSourceOperandAdressType(operationsOperandAdressTypesTable, mov, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, mov, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initSourceOperandAdressType(operationsOperandAdressTypesTable, cmp, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, cmp, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initSourceOperandAdressType(operationsOperandAdressTypesTable, add, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, add, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initSourceOperandAdressType(operationsOperandAdressTypesTable, sub, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, sub, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, not, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, clr, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initSourceOperandAdressType(operationsOperandAdressTypesTable, lea, OFF_BIT, ON_BIT, OFF_BIT, OFF_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, lea, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, inc, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, dec, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, jmp, OFF_BIT, ON_BIT, ON_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, bne, OFF_BIT, ON_BIT, ON_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, red, OFF_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, prn, ON_BIT, ON_BIT, OFF_BIT, ON_BIT);
    initDestinationOperandAdressType(operationsOperandAdressTypesTable, jsr, OFF_BIT, ON_BIT, ON_BIT, ON_BIT);
}

/* This is a method that receives operationsOperandAdressTypesTable array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation
 * and four int parameters that represents the four possibly adress types. The method init adress types of dest operand for opName operation in operationsOperandAdressTypesTable. The method returns nothing.
 */
void initDestinationOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, int firstType, int secondType, int thirdType, int fourthType)
{
    /* For each type there is two bits in destinationOperandAdressTypes field of opName cell in operationsOperandAdressTypesTable. For each type if this is legal type of dest operand for opName operation, so
     * will be 01(that mean this is legal type of dest operand for opName operation) in the appropriate two bits(the two rightmost bits are for the first type and the two leftmost bits are for the fourth type)
     * and else will be 00(that mean this is not legal type of dest operand for opName operation) in the appropriate two bits.
     */
    operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes |= (firstType << (FIRST_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes |= (secondType << (SECOND_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes |= (thirdType << (THIRD_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes |= (fourthType << (FOURTH_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
}

/* This is a method that receives operationsOperandAdressTypesTable array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation
 * and four int parameters that represents the four possibly adress types. The method init adress types of source operand for opName operation in operationsOperandAdressTypesTable. The method returns nothing.
 */
void initSourceOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, int firstType, int secondType, int thirdType, int fourthType)
{
    /* For each type there is two bits in sourceOperandAdressTypes field of opName cell in operationsOperandAdressTypesTable. For each type if this is legal type of source operand for opName operation, so
     * will be 01(that mean this is legal type of source operand for opName operation) in the appropriate two bits(the two rightmost bits are for the first type and the two leftmost bits are for the fourth type)
     * and else will be 00(that mean this is not legal type of source operand for opName operation) in the appropriate two bits.
     */
    operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes |= (firstType << (FIRST_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes |= (secondType << (SECOND_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes |= (thirdType << (THIRD_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
    operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes |= (fourthType << (FOURTH_ENCODE_TYPE*AMOUNT_OF_BITS_FOR_OPERAND));
}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation and int parameter that represents number of operation(0-15).
 * The method sets the bits of destinationOperandAdressTypes and sourceOperandAdressTypes fields in operationsOperandAdressTypesTable[operationNumber] to zero. The method returns nothing.
 */
void setBitsToZero(operationOperandAdressTypes operationsOperandAdressTypesTable[], int operationNumber)
{
    operationsOperandAdressTypesTable[operationNumber].destinationOperandAdressTypes = OFF_BIT;
    operationsOperandAdressTypesTable[operationNumber].sourceOperandAdressTypes = OFF_BIT;
}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation
 * and adressType parameter that represents adress type of source operand.
 * The method checks if the type for source operand we receives as parameter is legal. If yes the method will return true, and else will return false.
 */
boolean isLegalSourceOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType)
{
    boolean result = true;
    if(sourceOperandAdressType != nothingType)
        /* Checks if in the two bits of the type that we receives as parameter in sourceOperandAdressTypes field of opName cell in operationsOperandAdressTypesTable there is 00.
         * If Yes so the result of operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes & (1 << ((sourceOperandAdressType)*AMOUNT_OF_BITS_FOR_OPERAND)) will be 0 because 00 & 01 is 0,
         * and that mean sourceOperandAdressType is illegal type of source operand for opName operation. Thus we will set result to false.
         */
        if(!(operationsOperandAdressTypesTable[opName].sourceOperandAdressTypes & (1 << ((sourceOperandAdressType)*AMOUNT_OF_BITS_FOR_OPERAND))))
            result = false;
    return result;
}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation
 * and adressType parameter that represents adress type of dest operand.
 * The method checks if the type for dest operand we receives as parameter is legal. If yes the method will return true, and else will return false.
 */
boolean isLegalDestinationOperandAdressType(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType destOperandAdressType)
{
    boolean result = true;
    if(destOperandAdressType != nothingType)
        /* Checks if in the two bits of the type that we receives as parameter in destinationOperandAdressTypes field of opName cell in operationsOperandAdressTypesTable there is 00.
         * If Yes so the result of operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes & (1 << ((destOperandAdressType)*AMOUNT_OF_BITS_FOR_OPERAND)) will be 0 because 00 & 01 is 0,
         * and that mean destOperandAdressType is illegal type of dest operand for opName operation. Thus we will set result to false.
         */
        if(!(operationsOperandAdressTypesTable[opName].destinationOperandAdressTypes & (1 << ((destOperandAdressType)*AMOUNT_OF_BITS_FOR_OPERAND))))
            result = false;
    return result;
}

/* This is a method that receives operationName parameter that represents name of operation, adressType parameter that represents adress type of source operand and adressType parameter that represents adress type of dest operand.
 * The method checks if the types we receives as parameters are legal. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkOperandsTypes(operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType)
{
    errors result;
    operationOperandAdressTypes operationsOperandAdressTypesTable[AMOUNT_OF_OPERATIONS];
    initOperationsOperandAdressTypesTable(operationsOperandAdressTypesTable);
    /* Checks to which group opName belongs and calls to the appropriate method. */
    if(isFirstInstructionGroup(opName) == true)
        result = checkOperandsTypesInFirstInstructionGroup(operationsOperandAdressTypesTable, opName, sourceOperandAdressType, destOperandAdressType);
    else if(isSecondInstructionGroup(opName) == true)
        result = checkOperandsTypesInSecondInstructionGroup(operationsOperandAdressTypesTable, opName, sourceOperandAdressType, destOperandAdressType);
    else
        result = checkOperandsTypesInThirdInstructionGroup(operationsOperandAdressTypesTable, opName, sourceOperandAdressType, destOperandAdressType);
    return result;

}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation,
 * adressType parameter that represents adress type of source operand and adressType parameter that represents adress type of dest operand. The method checks if the types we receives as parameters are legal for operations that belongs to first instruction group.
 * If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkOperandsTypesInFirstInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case mov:
            if (!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_MOV;
            break;
        case cmp:
            if (!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_CMP;
            break;
        case add:
            if (!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_ADD;
            break;
        case sub:
            if (!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_SUB;
            break;
        case lea:
            if (!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_LEA;
            break;
        default:
            break;
    }
    return result;
}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation,
 * adressType parameter that represents adress type of source operand and adressType parameter that represents adress type of dest operand. The method checks if the types we receives as parameters are legal for operations that belongs to second instruction group.
 * If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkOperandsTypesInSecondInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case not:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_NOT;
            break;
        case clr:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_CLR;
            break;
        case inc:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_INC;
            break;
        case dec:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_DEC;
            break;
        case jmp:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_JMP;
            break;
        case bne:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_BNE;
            break;
        case red:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_RED;
            break;
        case prn:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_PRN;
            break;
        case jsr:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_JSR;
            break;
        default:
            break;
    }
    return result;
}

/* This is a method that receives operationOperandAdressTypes array parameter that represents array of the legal adress types for operands in each operation, operationName parameter that represents name of operation,
 * adressType parameter that represents adress type of source operand and adressType parameter that represents adress type of dest operand. The method checks if the types we receives as parameters are legal for operations that belongs to third instruction group.
 * If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkOperandsTypesInThirdInstructionGroup(operationOperandAdressTypes operationsOperandAdressTypesTable[], operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType)
{
    errors result = THERE_IS_NO_ERROR;
    switch (opName) {
        case rts:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_RTS;
            break;
        case stop:
            if(!isLegalSourceOperandAdressType(operationsOperandAdressTypesTable, opName, sourceOperandAdressType) || !isLegalDestinationOperandAdressType(operationsOperandAdressTypesTable, opName, destOperandAdressType))
                result = ILLEGAL_ADRESS_TYPE_STOP;
            break;
        default:
            break;
    }
    return result;
}