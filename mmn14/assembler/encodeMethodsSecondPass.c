/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains methods that encodes the text in the file to machine code for second pass(encode only labels).
 */

/* Finals */
#define SIZE_OF_INSTRUCTION_ARRAY_COLUMNS 2
#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define START_OF_LABEL_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_SECOND_ADRESS_TYPE  2
#define AMOUNT_OF_BITS_OF_LABEL_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_SECOND_ADRESS_TYPE 6

/* Includes header files. */
#include "libraries.h"
#include "label.h"
#include "encodingType.h"

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), int parameter that represents counter of instruction words that encoded, unsigned int parameter that represents the adress of the label and labelType parameter that represents the type of the label.
 * The method encodes word memory of label. The method returns nothing.
 */
void encodeLabelInInstructionLine(char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], int IC, unsigned int adress, labelType type)
{
    /* Encodes word memory of label. */
    /* ARE field. */
    if(type == external)
        instructionArr[IC][SECOND_COLUMN] |= (char)E;
    else
        instructionArr[IC][SECOND_COLUMN] |= (char)R;
    /* There is 12 bits in label field. The 6 rightmost bits will encoded in the second column of instruction array and the 6 leftmost bits will encoded in the first column of instruction array. */
    instructionArr[IC][SECOND_COLUMN] |= (char)(adress<<START_OF_LABEL_FIELD_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_SECOND_ADRESS_TYPE);
    instructionArr[IC][FIRST_COLUMN] |= (char)(adress>>AMOUNT_OF_BITS_OF_LABEL_FIELD_THAT_ENCODED_IN_SECOND_COLUMN_OF_INSTRUCTION_ARRAY_FOR_SECOND_ADRESS_TYPE);
}