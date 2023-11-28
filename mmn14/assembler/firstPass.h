
#ifndef firstPass_H /* #include guards */
#define firstPass_H

/* This is a method that receives char* parameter that represents name of file(without extension), int* parameter that represents pointer that points to counter of instruction words that encoded,
 * int* parameter that represents pointer that points to counter of data words that encoded, two char [][] parameters that represents data array and instruction array(stores machine code) and nodeInLabelsTable** parameter that represents a pointer to the head of labels table.
 * The method handles of first pass in the program. The method checks errors in the file, founds labels in the file and adds them to labels table and encodes the text in the file to machine code(we encode all the text except from labels that we will encode them in the second pass after we found all the labels in the file).
 * If there is an error the method will return that there is an error and else will return that there is no error.
 * We assume that the size(in chars) of label name in the line is 31 chars(include null char in the end), assume that the size(in chars) of line in file is 82 chars(include null char in the end)
 */
errors firstPass(char *fileName, int *ptrIC, int *ptrDC, char dataArr[][SIZE_OF_DATA_ARRAY_COLUMNS], char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], nodeInLabelsTable **ptrHead);

#endif

