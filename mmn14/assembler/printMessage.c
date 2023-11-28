/*
 * @author Lior Michaeli
 * @version 26.03.23
 * The program contains method that helps to prints the appropriate message to the user.
 */

/* Includes header files. */
#include "libraries.h"
#include "errors.h"

/* Finals */
#define NO_LINE 0

/* This is a method that receives an int parameter that represents the number of the line(according the lines in the file after pre assembler(.am)) that had an error and errors type that represents the type of the error and const char* that represents the name of the file(with extension in all the cases except from the case of generically messages that with no line but with file) that had an error.
 * The method prints the appropriate message to the user and returns nothing.
 */
void printMessage(int numberOfLine, errors errorType, const char* filename)
{
    char *messagesTable[] = {
            "Everything went successfully.", "There is an error in the amount of operands. In mov operation should be 2 operands.", "There is an error in the amount of operands. In cmp operation should be 2 operands."
            , "There is an error in the amount of operands. In add operation should be 2 operands.", "There is an error in the amount of operands. In sub operation should be 2 operands."
            , "There is an error in the amount of operands. In lea operation should be 2 operands.", "There is an error in the amount of operands. In not operation should be 1 operands."
            , "There is an error in the amount of operands. In clr operation should be 1 operands.", "There is an error in the amount of operands. In inc operation should be 1 operands.", "There is an error in the amount of operands. In dec operation should be 1 operands."
            , "There is an error in the amount of operands. In jmp operation should be 1 operands.", "There is an error in the amount of operands. In bne operation should be 1 operands.", "There is an error in the amount of operands. In red operation should be 1 operands."
            , "There is an error in the amount of operands. In prn operation should be 1 operands.", "There is an error in the amount of operands. In jsr operation should be 1 operands.", "There is an error in the amount of operands. In rts operation should be 0 operands."
            , "There is an error in the amount of operands. In stop operation should be 0 operands.", "There is an error. A comma is missing in the line. There should be a comma between every two operands.", "There is an error. A illegal comma is in the line. There should be a comma only between operands."
            , "There is an error. There are multiple commas between two operands in the line. There should be a only once comma between every two operands.", "There is an error. Extra comma in the line. There should not be a comma after the last operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for mov operation are first, second and fourth types for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for cmp operation are first, second and fourth types for source and destination operands."
            , "There is an error in the address types of operands in the line.\nThe legal address types for add operation are first, second and fourth types for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for sub operation are first, second and fourth types for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for lea operation are second type for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for not operation are nothing for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for clr operation are nothing for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for inc operation are nothing for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for dec operation are nothing for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for jmp operation are nothing for source operand, and second, third and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for bne operation are nothing for source operand, and second, third and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for red operation are nothing for source operand, and second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for prn operation are nothing for source operand, and first, second and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for jsr operation are nothing for source operand, and second, third and fourth types for destination operand."
            , "There is an error in the address types of operands in the line.\nThe legal address types for rts operation are nothing for source and destination operands."
            , "There is an error in the address types of operands in the line.\nThe legal address types for stop operation are nothing for source and destination operands."
            , "There is an error. Illegal operand. Operand must be register or label or number.", "There is an error in number. A + or - sign cannot appear twice in a number.", "There is an error in number. A + or - sign cannot appear after beginning of number."
            , "There is an error in number. In number should be only digits and optional sign in beginning.", "There is an error in label operand. In label should be only alphabetical letters or digits and the first letter in label must be alphabetical letter."
            , "There is an error in number. There is must be digits after + or - sign.", "There is an error in number operand. There is must be number after # that is beginning of number operand."
            , "There is an error. In third adress type in jmp, bne and jsr operations the operand must be label.", "There is an error. Illegal parameter. Parameter must be register or label or number.",
              "There is an error in string guidance. The string is illegal.\nA valid string is a series of printable ASCII characters enclosed in double quotes.", "There is an error in string guidance. There is should not be letters after end double quotes."
              ,"There is an error in labels. Cannot be two labels with the same name in the same file.", "There is warning. To label before extern or entry guidance has no meaning.", "There is an error in the label. A label cannot be a reserved word."
              , "There is an error. The instruction name is incorrect.", "There is an error in the open of the file that you entered.", "There is an error in the macro. A macro cannot be a reserved word.", "There is an error in data guidance. In data guidance must be at least one parameter."
              , "There is an error in string guidance. In string guidance must be one parameter.", "There is an error in string guidance. The parameter in string guidance must be enclosed in double quotes.", "There is an error in string guidance.\nIn string guidance empty string is illegal, that mean in string guidance must be at least one printable ASCII character enclosed in double quotes."
              , "There is an error. In third address type for jump operands must be two operands in double parenthesis,\nthat separated from each other by a one comma and there is no spaces between the parts of the operand.", "There is an error. In third address type for jump operands should not have be text(graphic letters) after end parenthesis."
              , "There is an error in entry guidance. In entry guidance the operand must be label that defined in the current file.", "There is an error in label. Label can not be both extern and entry.", "There is an error in label. In instruction line if there is labels they must be defined in the file or be externals.", "Error! Memory not allocated."
              , "There is an error. In extern and entry guidance the amount of labels in the line must be one.", "There is an error. There are no names of files in command line.", "There is an error in macros. Cannot be two macros with the same name in the same file.", "There is an error in label. Length of label can not be greater than 30 chars(not include : in the end)."

    };
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    /* Prints the line that had an error. If the error is not happened in specific line so, we are not will print any line. */
    if(numberOfLine != NO_LINE)
        printf("In file %s, In line %d:\n", filename , numberOfLine);
    /* For generically messages that with no line but with file. In this case numberOfLine equal to NO_LINE and filename is not NULL(he is the name of the file that we handle now without extension). */
    else if(filename != NULL)
        printf("For file %s.as:\n", filename);
    printf("%s\n",messagesTable[errorType]); /* Prints the appropriate message to the user from the array of the messages. */
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}