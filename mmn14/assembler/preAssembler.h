#ifndef preAssembler_H /* #include guards */
#define preAssembler_H


/* This is a method that receives char* parameter that represents name of file(without extension). The method handles of pre assembler pass. The method creates .am file that in this file will be the content that was in the assembly file but after we lay out the macros that were in the file.
 * If there is an error in the macros in the file we will print the error and not continue to the next passes. If there is an error the method will return that there is an error and else will return that there is no error.
 */
int analyzeMacros(char *fileName);

#endif