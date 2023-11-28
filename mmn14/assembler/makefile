assembler: assembler.o checkErrorsForFirstPass.o createFilesForAssembler.o encodeMethodsFirstPass.o firstPass.o helpMethods.o helpMethodsFirstPass.o helpMethodsEncodeFirstPass.o helpMethodsPreAssembler.o helpMethodsMacrosTable.o labelsTable.o macrosTable.o operationsOperandAdressTypesTable.o preAssembler.o printMessage.o secondPass.o encodeMethodsSecondPass.o 
	 gcc -g -Wall -ansi -pedantic assembler.o checkErrorsForFirstPass.o createFilesForAssembler.o encodeMethodsFirstPass.o firstPass.o helpMethods.o helpMethodsFirstPass.o helpMethodsEncodeFirstPass.o helpMethodsPreAssembler.o helpMethodsMacrosTable.o labelsTable.o macrosTable.o operationsOperandAdressTypesTable.o preAssembler.o printMessage.o secondPass.o encodeMethodsSecondPass.o  -o assembler
assembler.o: assembler.c libraries.h errors.h preAssembler.h helpMethods.h createFilesForAssembler.h labelsTable.h firstPass.h secondPass.h printMessage.h
	 gcc -c -Wall -ansi -pedantic assembler.c -o assembler.o
checkErrorsForFirstPass.o: checkErrorsForFirstPass.c libraries.h errors.h operationName.h boolean.h adressType.h helpMethodsFirstPass.h helpMethods.h operationsOperandAdressTypesTable.h printMessage.h
	 gcc -c -Wall -ansi -pedantic checkErrorsForFirstPass.c -o checkErrorsForFirstPass.o
createFilesForAssembler.o: createFilesForAssembler.c libraries.h boolean.h label.h operationName.h register.h labelsTable.h helpMethods.h
	 gcc -c -Wall -ansi -pedantic createFilesForAssembler.c -o createFilesForAssembler.o
encodeMethodsFirstPass.o: encodeMethodsFirstPass.c libraries.h operationName.h adressType.h parameterType.h operandType.h boolean.h encodingType.h helpMethodsFirstPass.h helpMethods.h helpMethodsEncodeFirstPass.h
	 gcc -c -Wall -ansi -pedantic encodeMethodsFirstPass.c -o encodeMethodsFirstPass.o
firstPass.o: firstPass.c libraries.h errors.h boolean.h guidance.h operationName.h label.h helpMethods.h encodeMethodsFirstPass.h checkErrorsForFirstPass.h printMessage.h labelsTable.h helpMethodsFirstPass.h
	 gcc -c -Wall -ansi -pedantic firstPass.c -o firstPass.o
helpMethods.o: helpMethods.c libraries.h errors.h boolean.h operationName.h register.h guidance.h printMessage.h helpMethodsFirstPass.h
	 gcc -c -Wall -ansi -pedantic helpMethods.c -o helpMethods.o
helpMethodsFirstPass.o: helpMethodsFirstPass.c libraries.h boolean.h adressType.h operationName.h parameterType.h register.h helpMethods.h
	 gcc -c -Wall -ansi -pedantic helpMethodsFirstPass.c -o helpMethodsFirstPass.o
helpMethodsEncodeFirstPass.o: helpMethodsEncodeFirstPass.c libraries.h boolean.h adressType.h operationName.h parameterType.h helpMethods.h helpMethodsFirstPass.h
	 gcc -c -Wall -ansi -pedantic helpMethodsEncodeFirstPass.c -o helpMethodsEncodeFirstPass.o	 
helpMethodsPreAssembler.o: helpMethodsPreAssembler.c libraries.h boolean.h 
	 gcc -c -Wall -ansi -pedantic helpMethodsPreAssembler.c -o helpMethodsPreAssembler.o
helpMethodsMacrosTable.o: helpMethodsMacrosTable.c libraries.h
	 gcc -c -Wall -ansi -pedantic helpMethodsMacrosTable.c -o helpMethodsMacrosTable.o	 
labelsTable.o: labelsTable.c libraries.h label.h boolean.h errors.h helpMethods.h printMessage.h
	 gcc -c -Wall -ansi -pedantic labelsTable.c -o labelsTable.o
macrosTable.o: macrosTable.c libraries.h errors.h boolean.h helpMethods.h printMessage.h helpMethodsMacrosTable.h
	 gcc -c -Wall -ansi -pedantic macrosTable.c -o macrosTable.o
operationsOperandAdressTypesTable.o: operationsOperandAdressTypesTable.c libraries.h errors.h operationName.h adressType.h boolean.h helpMethodsFirstPass.h 
	 gcc -c -Wall -ansi -pedantic operationsOperandAdressTypesTable.c -o operationsOperandAdressTypesTable.o
preAssembler.o: preAssembler.c libraries.h boolean.h errors.h macrosTable.h helpMethods.h helpMethodsPreAssembler.h printMessage.h 
	 gcc -c -Wall -ansi -pedantic preAssembler.c -o preAssembler.o
printMessage.o: printMessage.c libraries.h errors.h 
	 gcc -c -Wall -ansi -pedantic printMessage.c -o printMessage.o
secondPass.o: secondPass.c libraries.h boolean.h errors.h register.h label.h operationName.h guidance.h  labelsTable.h secondPass.h helpMethods.h printMessage.h encodeMethodsSecondPass.h 
	 gcc -c -Wall -ansi -pedantic secondPass.c -o secondPass.o
encodeMethodsSecondPass.o: encodeMethodsSecondPass.c libraries.h label.h encodingType.h
	 gcc -c -Wall -ansi -pedantic encodeMethodsSecondPass.c -o encodeMethodsSecondPass.o


