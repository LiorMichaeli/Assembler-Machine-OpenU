
#ifndef secondPass_H /* #include guards */
#define secondPass_H


/* This is a method that receives char* parameter that represents name of file(without extension), char [][] parameter that represents instruction array(stores machine code) and nodeInLabelsTable** parameter that represents a pointer to the head of labels table.
 * The method handles of second pass in the program. The method handles of some more errors(except from the errors we were check in the first pass) and completes the encoding of the text in the file to machine code in that we complete the encoding of labels.
 * If there is an error the method will return the appropriate error and else will return that there is no error.
 */
errors secondPass(char *fileName, char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], nodeInLabelsTable **ptrHead);

#endif