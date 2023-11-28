
#ifndef checkErrorsForFirstPass_H /* #include guards */
#define checkErrorsForFirstPass_H

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is data guidance line(.data). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInDataGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine);

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is string guidance line(.string). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInStringGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine);

/* This is a method that receives const char* parameter that represents pointer to the name of operation in the line, const char array parameter that represents line in the file, char array parameter that represents the same line in the file that we use this for check if labels are not save word
 * (We will use strtok and the first token will be the first operand), const char* parameter that represents name of the file after pre assembler(.am file)(with extension), int parameter that represents the number of the line that we receives as parameter and boolean* parameter that represents pointer to flag that says if the current line is third adress type.
 * The method checks if there is an error in the line, when the line is instruction line. If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInInstructionLine(const char *ptrOpName, char lineInTheFile[], char lineInTheFileForCheckLabelsNotSaveWords[], const char *nameOfFileAfterPreAssembler, int numberOfLine, boolean *ptrFlagIsThirdAdressType);

/* This is a method that receives const char array parameter that represents line in the file, const char* parameter that represents name of the file after pre assembler(.am file)(with extension) and int parameter that represents the number of the line that we receives as parameter.
 * The method checks if there is an error in the line, when the line is extern or entry guidance line(.extern or .entry). If there is an error the method will return that there is an error and else will return that there is no error.
 */
errors checkErrorsInExternAndEntryGuidance(const char lineInTheFile[], const char *nameOfFileAfterPreAssembler, int numberOfLine);

#endif