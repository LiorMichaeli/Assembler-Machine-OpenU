#ifndef operationsOperandAdressTypesTable_H /* #include guards */
#define operationsOperandAdressTypesTable_H

/* This is a method that receives operationName parameter that represents name of operation, adressType parameter that represents adress type of source operand and adressType parameter that represents adress type of dest operand.
 * The method checks if the types we receives as parameters are legal. If yes the method will return that there is no error, and else will return the appropriate error.
 */
errors checkOperandsTypes(operationName opName, adressType sourceOperandAdressType, adressType destOperandAdressType);

#endif
