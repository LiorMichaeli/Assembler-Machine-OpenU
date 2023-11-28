#ifndef encodeMethodsFirstPass_H /* #include guards */
#define encodeMethodsFirstPass_H

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code) and int**** parameter that represents pointer that points to counter of data words that encoded.
 * The method encodes data guidance line to machine code. Each number in the line will encode to word in the the memory. The method returns nothing.
 */
void encodeDataGuidance(const char currentLineInTheFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrDC);

/* This is a method that receives const char array parameter that represents line in the file, char [][] parameter that represents data array(stores machine code) and int**** parameter that represents pointer that points to counter of data words that encoded.
 * The method encodes string guidance line to machine code. Each letter in the string in the line will encode to word in the the memory by his ascii code and in the end we will insert 0 to one more word(represents end of string). The method returns nothing.
 */
void encodeStringGuidance(const char currentLineInTheFile[], char dataArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ****ptrDC);

/* This is a method that receives char array parameter that represents line in the file, char [][] parameter that represents instruction array(stores machine code), int*** parameter that represents pointer that points to counter of instruction words that encoded and
 * boolean parameter that represents flag that says if the current line is third adress type. The method handles of encodes instruction line to machine code. The method returns nothing.
 */
void encodeInstructionLine(char lineInTheFile[], char instructionArr[][SIZE_OF_INSTRUCTION_AND_DATA_ARRAYS_COLUMNS], int ***ptrIC, boolean isThirdAdressType);

#endif