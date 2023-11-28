cmake_minimum_required(VERSION 3.24)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler.c preAssembler.c preAssembler.h helpMethodsPreAssembler.c helpMethodsPreAssembler.h macrosTable.c assembler.c firstPass.c firstPass.h helpMethodsFirstPass.c helpMethodsFirstPass.h helpMethods.c helpMethods.h labelsTable.c labelsTable.h encodeMethodsFirstPass.c encodeMethodsFirstPass.h checkErrorsForFirstPass.c checkErrorsForFirstPass.h operationsOperandAdressTypesTable.c operationsOperandAdressTypesTable.h errors.h printMessage.c printMessage.h boolean.h guidance.h label.h encodingType.h adressType.h operationName.h parameterType.h operandType.h libraries.h createFilesForAssembler.c createFilesForAssembler.h secondPass.c encodeMethodsSecondPass.c encodeMethodsSecondPass.h helpMethodsMacrosTable.c helpMethodsMacrosTable.h helpMethodsEncodeFirstPass.c helpMethodsEncodeFirstPass.h)
