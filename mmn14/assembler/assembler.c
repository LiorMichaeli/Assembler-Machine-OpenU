/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The file contains the main method of the project-assembler.
 * If there was error allocation in macros table or labels table we will not continue in the current file in order not cause undefined behavior, and go to the next file.
 * In the program we assume that the maximal length of line in the file is 81(include \n char), the maximal length of data array(stores machine code) is 50, the maximal length of instruction array(stores machine code) is 106
 * and that the first word memory will be in adress 100.
 */

/* Finals */
#define MAX_LENGTH_OF_DATA 50
#define MAX_LENGTH_OF_INSTRUCTION 106
#define NO_LINE 0
#define START_ADRESS 100
#define START_VALUE_OF_DC_AND_IC 0
#define SIZE_OF_DATA_ARRAY_COLUMNS 2
#define SIZE_OF_INSTRUCTION_ARRAY_COLUMNS 2
#define THERE_ARE_NO_NAMES_OF_FILES_IN_COMMAND_LINE 1

/* Prototype */
#include "libraries.h"
#include "errors.h"
#include "preAssembler.h"
#include "helpMethods.h"
#include "labelsTable.h"
#include "firstPass.h"
#include "secondPass.h"
#include "createFilesForAssembler.h"
#include "printMessage.h"

/* This is the main method of the program that receives int parameter that represents the amount of the arguments that the user entered in the command line and char *[] that represents array of pointers that points to the arguments that the user entered.
 * The arguments after the name of the program are names of assembly files for the assembler(in the command line they without extension).
 * The main method calls to methods that do the preAssembler pass, first pass, second pass and finally creates the files of the assembler. If there is an error in some pass so we will not continue to the other passes
 * and of course we will print the appropriate error. The errors will be print according the line in .am file and only in pre assembler pass the errors will be print according the line in .as file.
 * If there are no errors the program will create ob file and externals and entries files, if there was entries and externals labels in the file. The method return only 0.
 */
int main(int argc, char *argv[])
{
    int i, IC, DC; /* Counter of instruction words that encoded and counter of data words that encoded. */
    /* Two char [][] that represents data array and instruction array(stores machine code). */
    char dataArr[MAX_LENGTH_OF_DATA][SIZE_OF_DATA_ARRAY_COLUMNS], instructionArr[MAX_LENGTH_OF_INSTRUCTION][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS];
    nodeInLabelsTable *ptrHead; /* Pointer to the head of labels table. */
    if(argc == THERE_ARE_NO_NAMES_OF_FILES_IN_COMMAND_LINE)
        printMessage(NO_LINE, NO_NAMES_OF_FILES_IN_COMMAND_LINE, NULL);
    for (i = 1; i < argc; i++) {
        IC = START_VALUE_OF_DC_AND_IC;
        DC = START_VALUE_OF_DC_AND_IC;
        ptrHead = NULL;
        initializeDataAndInstructionArrayToZero(dataArr, instructionArr);
        /* Checks that there was no errors in pre assembler pass. */
        if(analyzeMacros(argv[i]) == THERE_IS_NO_ERROR)
        {
            /* Checks that there was no errors in first pass. */
            if(firstPass(argv[i], &IC, &DC, dataArr, instructionArr, &ptrHead) == THERE_IS_NO_ERROR)
            {
                addAdressToDataAndInstructionLabels(&ptrHead, START_ADRESS+IC, START_ADRESS);/* The start adress in the memory for the assembler is 100. */
                /* Checks that there was no errors in second pass. */
                if(secondPass(argv[i], instructionArr, &ptrHead) == THERE_IS_NO_ERROR)
                {
                    /* Creates ob file and externals and entries files(if there was entries and externals labels in the file). If there are no errors(allocation errors) we will print successful message. */
                    if((createObjectFile(argv[i], dataArr, instructionArr, IC, DC) == THERE_IS_NO_ERROR) && (createEntriesFile(argv[i], ptrHead) == THERE_IS_NO_ERROR) && (createExternalsFile(argv[i], ptrHead) == THERE_IS_NO_ERROR))
                        printMessage(NO_LINE, THERE_IS_NO_ERROR, argv[i]);
                }
            }
        }
        /* Free the memory we allocated. */
        freeMemoryLabelsTable(&ptrHead);
    }
    return 0;
}
