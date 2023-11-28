
#ifndef createFilesForAssembler_H /* #include guards */
#define createFilesForAssembler_H

/* This is a method that receives const char* parameter that represents the name of the file(without extension), two char [][] parameters that represents data array and instruction array(stores machine code), int parameter that represents counter of instruction words that encoded
 * and int parameter that represents counter of data words that encoded. The method creates object file. In the object file will be two numbers in the first line, the value of IC and DC(left to right) and the next lines will be machine code that
 * stored in data array and instruction array. In each line will be the number of the adress and first will be the machine code of instruction array and after will be the machine code of data array.
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createObjectFile(const char *fileName, char dataArr[][SIZE_OF_DATA_ARRAY_COLUMNS], char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], int IC, int DC);

/* This is a method that receives const char* parameter that represents the name of the file(without extension) and nodeInLabelsTable* parameter that represents a pointer to the head of labels table.
 * The method creates entries file(if there is entry label in the file). In the entries file will be all the entries labels in the file. In each line will be label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createEntriesFile(const char *fileName, nodeInLabelsTable *ptrHead);

/* This is a method that receives const char* parameter that represents the name of the file(without extension) and nodeInLabelsTable* parameter that represents a pointer to the head of labels table.
 * The method creates externals file(if there is appearance of external label in the file(in instruction line)). In the externals file will be all the appearances of externals labels in the file(in instruction lines). In each line will be appearance of label that defined as entry and the address where it was set(the adress will be last in the file in the right side of the line).
 * If there are no errors(allocation errors) we will return that there is no error, and else will return that there is an error.
 */
errors createExternalsFile(const char *fileName, nodeInLabelsTable *ptrHead);

#endif