
#ifndef HELP_METHODS_ENCODE_FIRST_PASS_H /* #include guards */
#define HELP_METHODS_ENCODE_FIRST_PASS_H

/* This is a method that receives char array parameter that represents line in the file, operationName* parameter that represents name of the operation in this line, two adressType* parameters that represents pointer that points to the adress type of source and dest operands in the line
 * , two parameterType* parameters that represents pointer that points to the type of first and second parameters in the line(only in third adress type) and boolean parameter that represents flag that says if the current line is third adress type.
 * The method sets the attributes operation, sourceOperandAdressType, destOperandAdressType, firstParameterForThirdAdressType and secondParameterForThirdAdressType for we can encode instruction line to machine code. The method returns nothing.
 */
void setAttributesInInstructionLine(char lineInTheFile[], operationName *operation, adressType *sourceOperandAdressType, adressType *destOperandAdressType, parameterType *firstParameterForJumpOperands, parameterType *secondParameterForJumpOperands, boolean isThirdAdressType);


#endif
