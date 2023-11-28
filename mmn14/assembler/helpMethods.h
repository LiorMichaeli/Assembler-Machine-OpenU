#ifndef helpMethods_H /* #include guards */
#define helpMethods_H

/* Includes header files. */
#include "boolean.h"
#include "guidance.h"
#include "operationName.h"
#include "register.h"
#include "errors.h"

/* Finals */
#define SIZE_OF_DATA_ARRAY_COLUMNS 2
#define SIZE_OF_INSTRUCTION_ARRAY_COLUMNS 2

/* This is a method that receives const char * parameter that represents a pointer that we need to check and const char* parameter that represents the name of the file that we handle now without extension.
 * The method checks if the memory allocation we did was successful. If the memory allocation we did was not successful the method calls to printMessage method,
 * that will print error to the user and we will return that there is an error. Else we will return that there is no error.
 */
errors checkAllocationOfCharsPointers(const char *ptr, const char *fileName);

/* This is a method that receives FILE * parameter that represents a pointer to a file that we need to check and const char* parameter that represents the name of the file that we handle now without extension.
 * The method checks if the open of the file we did was successful. If not the method calls to printMessage method that will print error to the user and (this method) return that there is an error.
 * Else the method will return that there is no error. The method returns if there is an error in the opening of the file.
 */
errors checkOpenFile(FILE *ptrToFile, const char *fileName);

/* This is a method that receives char[] parameter that represents line in the file and const char[] parameter that represents delimiter.
 * The method gets the current word according to delimiter and the line in the file with the help of the method strtok from string library. The method returns pointer to the current word.
 */
char* getCurrentWord(char *currentLineInTheFile, const char delim[]);

/* This is a method that receives char * parameter that represents pointer to word.
 * The method checks if the word is a save word. If yes the method will return false and else true. The method returns if the word is not a save word.
 */
boolean isNotSaveWord(char *word);

/* This is a method that receives char ** parameter that represents pointer to the name of the file(with extension), const char * parameter that represents pointer to the name of the file without extension and
 * const char * parameter that represents pointer to the extension of the file. The method set the name of the file with the appropriate name and extension. The method returns nothing.
 */
void setNameOfFile(char **ptrNameOfFile, const char *fileName, const char *fileExtension);

/* This is a method that receives const char * parameter that represents pointer to the name of the file without extension and int parameter that represents the length of the extension of the file.
 * The method return int that represents the length needed for file name.
 */
int getLengthNeedForFileName(const char *fileName, int lengthOfFileExtension);

/* This is a method that receives two dimensional char arrays parameters that represents data array and instruction array. The method initializes all cells of the arrays to zero. The method returns nothing*/
void initializeDataAndInstructionArrayToZero(char dataArr[][SIZE_OF_DATA_ARRAY_COLUMNS], char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS]);

/* This is a method that receives dimensional char array parameter that represents array that has machine code(data array or instruction array), char ** parameter that represents pointer to
 * word that store the machine code in unique base 2 code and int parameter that represents adress of machine code that we want to convert to unique base 2 code in MachineCodeArray array.
 * The method convert the machine code that found in adress in MachineCodeArray array to unique base 2 code and store this in ptrWordInUniqueBase2Code. The method return nothing.
 */
void convertMachineCodeToUniqueBase2Code(char MachineCodeArray[][SIZE_OF_DATA_ARRAY_COLUMNS], char **currentWordInUniqueBase2Code, int adress); /* Put SIZE_OF_DATA_ARRAY_COLUMNS because it doesn't matter. */

/* This is a method that receives const char array parameter that represents pointer to line in the file. The method checks if there is label definition in the beginning of the line that means there is word that her first letter is alphabetical letter, others letters must be
 * alphabetical letters or digits and the last letter is ':'. If there is label definition in the beginning of the line, so the method will return true and else false.
 */
boolean thereIsLabelDefinition(const char lineInTheFile[]);

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which guidance is word(If word is guidance). If word is guidance so the method will return the appropriate
 * guidance and else return that the word is illegal guidance.
 */
guidance getGuidance(const char *currentWordInLine);

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which operation is word(If word is operation). If word is operation so the method will return the appropriate
 * operation and else return that the word is illegal operation.
 */
operationName getOperation(const char *word);

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which register is word(If word is register). If word is register so the method will return the appropriate
 * register and else return that the word is illegal register.
 */
registerName getRegister(const char *word);

/* This is method that receives char parameter that represents the first char in word. If the char is # so this is beginning of number definition and the method will return true. Else the method will return false. */
boolean isBeginningOfNumberDefinition(char currentChar);

/* This is a method that receives int* parameter that represents pointer that points to number. The method set the number that we get as parameter to the appropriate negative number with 2's complement. The method returns nothing. */
void setNumberToNegative(int *ptrNumber);

#endif

