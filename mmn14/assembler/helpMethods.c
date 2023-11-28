/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains help methods for all the steps in the program.
 */

/* Finals */
#define NO_LINE 0
#define LENGTH_OF_END_CHARACTER 1
#define START_ADRESS 100
#define LENGTH_OF_WORD 14
#define MAX_LENGTH_OF_DATA 50
#define MAX_LENGTH_OF_INSTRUCTION 107
#define SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS 2
#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define LAST_SIX_BITS_IN_WORD 6
#define FIRST_EIGHT_BITS_IN_WORD 8
#define FIVE_BITS 5
#define TWO_BITS 2
#define ONE_NUMBER 1
#define GO_ONE_BIT_LEFT 1
#define AMOUNT_OF_BITS_IN_WORD_MEMORY 14
#define ZERO 0
#define ONE 1
/* Includes header files. */
#include "libraries.h"
#include "errors.h"
#include "boolean.h"
#include "operationName.h"
#include "register.h"
#include "guidance.h"
#include "printMessage.h"
#include "helpMethodsFirstPass.h"



/* This is a method that receives const char * parameter that represents a pointer that we need to check and const char* parameter that represents the name of the file that we handle now without extension.
 * The method checks if the memory allocation we did was successful. If the memory allocation we did was not successful the method calls to printMessage method,
 * that will print error to the user and we will return that there is an error. Else we will return that there is no error.
 */
errors checkAllocationOfCharsPointers(const char *ptr, const char *fileName)
{
    errors result = THERE_IS_NO_ERROR;
    if(ptr == NULL)
    {
        /* Prints error to the user. */
        printMessage(NO_LINE, ALLOCATION_NOT_SUCCEEDED, fileName);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives FILE * parameter that represents a pointer to a file that we need to check and const char* parameter that represents the name of the file that we handle now without extension.
 * The method checks if the open of the file we did was successful. If not the method calls to printMessage method that will print error to the user and (this method) return that there is an error.
 * Else the method will return that there is no error. The method returns if there is an error in the opening of the file.
 */
errors checkOpenFile(FILE *ptrToFile, const char *fileName)
{
    errors result = THERE_IS_NO_ERROR;
    if(ptrToFile == NULL)
    {
        printMessage(NO_LINE, OPEN_FILE_ERROR, fileName);
        result = THERE_IS_AN_ERROR;
    }
    return result;
}

/* This is a method that receives char[] parameter that represents line in the file and const char[] parameter that represents delimiter.
 * The method gets the current word according to delimiter and the line in the file with the help of the method strtok from string library. The method returns pointer to the current word.
 */
char* getCurrentWord(char lineInTheFile[], const char delim[])
{
    return strtok(lineInTheFile, delim);
}

/* This is a method that receives char * parameter that represents pointer to word.
 * The method checks if the word is a save word. If yes the method will return false and else true. The method returns if the word is not a save word.
 */
boolean isNotSaveWord(char *ptrWord)
{
    boolean result = true;
    if(!strcmp(ptrWord, ".data") || !strcmp(ptrWord, ".string") || !strcmp(ptrWord, ".entry") || !strcmp(ptrWord, ".extern"))
        result = false;
    else if(!strcmp(ptrWord, "r0") || !strcmp(ptrWord, "r1") || !strcmp(ptrWord, "r2") || !strcmp(ptrWord, "r3") || !strcmp(ptrWord, "r4"))
        result = false;
    else if(!strcmp(ptrWord, "r5") || !strcmp(ptrWord, "r6") || !strcmp(ptrWord, "r7"))
        result = false;
    else if(!strcmp(ptrWord, "mov") || !strcmp(ptrWord, "cmp") || !strcmp(ptrWord, "add") || !strcmp(ptrWord, "sub") || !strcmp(ptrWord, "not"))
        result = false;
    else if(!strcmp(ptrWord, "clr") || !strcmp(ptrWord, "lea") || !strcmp(ptrWord, "inc") || !strcmp(ptrWord, "dec") || !strcmp(ptrWord, "jmp"))
        result = false;
    else if(!strcmp(ptrWord, "bne") || !strcmp(ptrWord, "red") || !strcmp(ptrWord, "prn") || !strcmp(ptrWord, "jsr") || !strcmp(ptrWord, "rts") || !strcmp(ptrWord, "stop"))
        result = false;
    return result;
}

/* This is a method that receives char ** parameter that represents pointer to the name of the file(with extension), const char * parameter that represents pointer to the name of the file without extension and
 * const char * parameter that represents pointer to the extension of the file. The method set the name of the file with the appropriate name and extension. The method returns nothing.
 */
void setNameOfFile(char **ptrNameOfFile, const char *fileName, const char *fileExtension)
{
    strcpy(*ptrNameOfFile, fileName);
    strcat(*ptrNameOfFile, fileExtension);
}

/* This is a method that receives const char * parameter that represents pointer to the name of the file without extension and int parameter that represents the length of the extension of the file.
 * The method return int that represents the length needed for file name.
 */
int getLengthNeedForFileName(const char *fileName, int lengthOfFileExtension)
{
    return (int)strlen(fileName)+lengthOfFileExtension+LENGTH_OF_END_CHARACTER;
}

/* This is a method that receives two dimensional char arrays parameters that represents data array and instruction array. The method initializes all cells of the arrays to zero. The method returns nothing*/
void initializeDataAndInstructionArrayToZero(char dataArr[][SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS], char instructionArr[][SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS])
{
    int i;
    for (i = 0; i < MAX_LENGTH_OF_DATA; i++) {
        dataArr[i][FIRST_COLUMN] = ZERO;
        dataArr[i][SECOND_COLUMN] = ZERO;
    }
    for (i = 0; i < MAX_LENGTH_OF_INSTRUCTION; i++) {
        instructionArr[i][FIRST_COLUMN] = ZERO;
        instructionArr[i][SECOND_COLUMN] = ZERO;
    }
}

/* This is a method that receives dimensional char array parameter that represents array that has machine code(data array or instruction array), char ** parameter that represents pointer to
 * word that store the machine code in unique base 2 code and int parameter that represents adress of machine code that we want to convert to unique base 2 code in MachineCodeArray array.
 * The method convert the machine code that found in adress in MachineCodeArray array to unique base 2 code and store this in ptrWordInUniqueBase2Code. The method return nothing.
 */
void convertMachineCodeToUniqueBase2Code(char MachineCodeArray[][SIZE_OF_DATA_AND_INSTRUCTION_ARRAY_COLUMNS], char **ptrWordInUniqueBase2Code, int adress)
{
    int i;
    unsigned int mask = (ONE<<FIVE_BITS); /* Set the mask that the on bit in 1 will be in the sixth bit(index 5). */
    /* Go over all six bits in the first column in adress in MachineCodeArray and convert the machine code to unique base 2 code.*/
    for (i = 0; i < LAST_SIX_BITS_IN_WORD; i++) {
        if(MachineCodeArray[adress][FIRST_COLUMN] & mask>>i)
            (*ptrWordInUniqueBase2Code)[i] = '/';
        else
            (*ptrWordInUniqueBase2Code)[i] = '.';
    }
    mask <<= TWO_BITS; /* Set the mask that the on bit in 1 will be in the eight bit(index 7). */
    /* Go over all eight bits in the second column in adress in MachineCodeArray and convert the machine code to unique base 2 code.*/
    for (i = 0; i < FIRST_EIGHT_BITS_IN_WORD; i++) {
        if(MachineCodeArray[adress][SECOND_COLUMN] & mask>>i)
            (*ptrWordInUniqueBase2Code)[i+LAST_SIX_BITS_IN_WORD] = '/';
        else
            (*ptrWordInUniqueBase2Code)[i+LAST_SIX_BITS_IN_WORD] = '.';
    }
}

/* This is a method that receives const char array parameter that represents pointer to line in the file. The method checks if there is label definition in the beginning of the line that means there is word that her first letter is alphabetical letter, others letters must be
 * alphabetical letters or digits and the last letter is ':'. If there is label definition in the beginning of the line, so the method will return true and else false.
 */
boolean thereIsLabelDefinition(const char lineInTheFile[])
{
    boolean result = false, flagThereIsLabel = true, flagThereIsLetter = false;
    int i = 0;
    /* Goes over all the line as long as result is true and flagThereIsLabel is false that mean we not found a label definition and not found a word that is not label definition. */
    while(lineInTheFile[i] && flagThereIsLabel == true && result == false)
    {
        if(flagThereIsLetter == false)
        {
            if(isgraph(lineInTheFile[i]))
            {
                /* Checks if the first letter in the word that we found is not beginning of label. If yes we will set flagThereIsLabel to false. */
                if(isBeginningOfLabel(lineInTheFile[i]) == false)
                    flagThereIsLabel = false;
                flagThereIsLetter = true;
            }
        }
        else
        {
            /* Checks if the current letter in the word that we found is end of label definition. If yes we will set result to true, because we found label definition. Else we checks if the current letter in the word that we found is
             * not alphabetical letter or digit. If yes that mean this word is not label definition and thus we will set flagThereIsLabel to false.
             */
            if(isEndOfLabelDefinition(lineInTheFile[i]) == true)
                result = true;
            else if(!isalnum(lineInTheFile[i]))
                flagThereIsLabel = false;
        }
        i++;
    }
    return result;
}

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which guidance is word(If word is guidance). If word is guidance so the method will return the appropriate
 * guidance and else return that the word is illegal guidance.
 */
guidance getGuidance(const char *ptrWord)
{
    guidance result = illegalGuidance;
    if(!strcmp(ptrWord, ".data"))
        result = dataGuidance;
    else if(!strcmp(ptrWord, ".string"))
        result = stringGuidance;
    else if(!strcmp(ptrWord, ".entry"))
        result = entryGuidance;
    else if(!strcmp(ptrWord, ".extern"))
        result = externGuidance;
    return result;
}

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which operation is word(If word is operation). If word is operation so the method will return the appropriate
 * operation and else return that the word is illegal operation.
 */
operationName getOperation(const char *ptrWord)
{
    operationName result = illegalOperation;
    if(!strcmp(ptrWord, "mov"))
        result = mov;
    else if(!strcmp(ptrWord, "cmp"))
        result = cmp;
    else if(!strcmp(ptrWord, "add"))
        result = add;
    else if(!strcmp(ptrWord, "sub"))
        result = sub;
    else if(!strcmp(ptrWord, "not"))
        result = not;
    else if(!strcmp(ptrWord, "clr"))
        result = clr;
    else if(!strcmp(ptrWord, "lea"))
        result = lea;
    else if(!strcmp(ptrWord, "inc"))
        result = inc;
    else if(!strcmp(ptrWord, "dec"))
        result = dec;
    else if(!strcmp(ptrWord, "jmp"))
        result = jmp;
    else if(!strcmp(ptrWord, "bne"))
        result = bne;
    else if(!strcmp(ptrWord, "red"))
        result = red;
    else if(!strcmp(ptrWord, "prn"))
        result = prn;
    else if(!strcmp(ptrWord, "jsr"))
        result = jsr;
    else if(!strcmp(ptrWord, "rts"))
        result = rts;
    else if(!strcmp(ptrWord, "stop"))
        result = stop;
    return result;
}

/* This is a method that receives const char * parameter that represents pointer to word. The method finds which register is word(If word is register). If word is register so the method will return the appropriate
 * register and else return that the word is illegal register.
 */
registerName getRegister(const char *ptrWord)
{
    registerName result = illegalRegister;
    if(!strcmp(ptrWord, "r0"))
        result = r0;
    else if(!strcmp(ptrWord, "r1"))
        result = r1;
    else if(!strcmp(ptrWord, "r2"))
        result = r2;
    else if(!strcmp(ptrWord, "r3"))
        result = r3;
    else if(!strcmp(ptrWord, "r4"))
        result = r4;
    else if(!strcmp(ptrWord, "r5"))
        result = r5;
    else if(!strcmp(ptrWord, "r6"))
        result = r6;
    else if(!strcmp(ptrWord, "r7"))
        result = r7;
    return result;
}

/* This is method that receives char parameter that represents the first char in word. If the char is # so this is beginning of number definition and the method will return true. Else the method will return false. */
boolean isBeginningOfNumberDefinition(char firstCharInWord)
{
    boolean result = false;
    if(firstCharInWord == '#')
        result = true;
    return result;
}

/* This is a method that receives int* parameter that represents pointer that points to number. The method set the number that we get as parameter to the appropriate negative number with 2's complement. The method returns nothing. */
void setNumberToNegative(int *ptrNumber)
{
    unsigned int mask = ONE_NUMBER, i = 0;
    boolean ThereIsOnBit = false;
    while(i < AMOUNT_OF_BITS_IN_WORD_MEMORY)
    {
        if(ThereIsOnBit == true)
            *ptrNumber = (int)(*ptrNumber ^ mask); /* Reverses the bits(0 will be 1 and 1 will be 0). */
            /* Checks if the current bit is 1, that is mean the current bit is on bit. */
        else if(*ptrNumber & mask)
            ThereIsOnBit = true;
        mask <<= GO_ONE_BIT_LEFT;
        i++;
    }
}