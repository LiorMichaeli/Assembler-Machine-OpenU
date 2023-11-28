#ifndef printMessage_H /* #include guards */
#define printMessage_H

/* This is a method that receives an int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) that had an error and errors type that represents the type of the error and const char* that represents the name of the file(with extension in all the cases except from the case of generically messages that with no line but with file) that had an error.
 * The method prints the appropriate message to the user and returns nothing.
 */
void printMessage(int numberOfLine, errors errorType, const char* filename);

#endif