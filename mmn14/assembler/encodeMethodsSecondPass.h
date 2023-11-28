#ifndef encodeMethodsSecondPass_H /* #include guards */
#define encodeMethodsSecondPass_H

/* This is a method that receives char [][] parameter that represents instruction array(stores machine code), int parameter that represents counter of instruction words that encoded, unsigned int parameter that represents the adress of the label and labelType parameter that represents the type of the label.
 * The method encodes word memory of label. The method returns nothing.
 */
void encodeLabelInInstructionLine(char instructionArr[][SIZE_OF_INSTRUCTION_ARRAY_COLUMNS], int IC, unsigned int adress, labelType type);

#endif