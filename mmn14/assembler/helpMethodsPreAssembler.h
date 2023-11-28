#ifndef helpMethodsPreAssembler_H /* #include guards */
#define helpMethodsPreAssembler_H

/* This is method that receives char * parameter that represents word. The method checks if the word is end macro definition, that is word equals to "endmcr" and if yes the method will returns true
 * and else the method will return false.
 */
boolean isEndMacroDefinition(char *word);

/* This is method that receives char * parameter that represents word. The method checks if the word is start macro definition, that is word equals to "mcr" and if yes the method will returns true
 * and else the method will return false.
 */
boolean isStartMacroDefinition(char *word);


#endif