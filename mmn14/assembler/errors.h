#ifndef ERRORS_H  /* #include guards */
#define ERRORS_H

typedef enum{
    THERE_IS_AN_ERROR = -1, THERE_IS_NO_ERROR, ERROR_IN_AMOUNT_OF_OPERANDS_MOV, ERROR_IN_AMOUNT_OF_OPERANDS_CMP,ERROR_IN_AMOUNT_OF_OPERANDS_ADD, ERROR_IN_AMOUNT_OF_OPERANDS_SUB
    ,ERROR_IN_AMOUNT_OF_OPERANDS_LEA, ERROR_IN_AMOUNT_OF_OPERANDS_NOT, ERROR_IN_AMOUNT_OF_OPERANDS_CLR, ERROR_IN_AMOUNT_OF_OPERANDS_INC, ERROR_IN_AMOUNT_OF_OPERANDS_DEC
    ,ERROR_IN_AMOUNT_OF_OPERANDS_JMP, ERROR_IN_AMOUNT_OF_OPERANDS_BNE, ERROR_IN_AMOUNT_OF_OPERANDS_RED, ERROR_IN_AMOUNT_OF_OPERANDS_PRN, ERROR_IN_AMOUNT_OF_OPERANDS_JSR
    ,ERROR_IN_AMOUNT_OF_OPERANDS_RTS, ERROR_IN_AMOUNT_OF_OPERANDS_STOP, MISSING_COMMA, ILLEGAL_COMMA, MULTIPLE_COMMAS, COMMA_IN_THE_END, ILLEGAL_ADRESS_TYPE_MOV, ILLEGAL_ADRESS_TYPE_CMP
    ,ILLEGAL_ADRESS_TYPE_ADD, ILLEGAL_ADRESS_TYPE_SUB, ILLEGAL_ADRESS_TYPE_LEA, ILLEGAL_ADRESS_TYPE_NOT, ILLEGAL_ADRESS_TYPE_CLR, ILLEGAL_ADRESS_TYPE_INC, ILLEGAL_ADRESS_TYPE_DEC,
    ILLEGAL_ADRESS_TYPE_JMP, ILLEGAL_ADRESS_TYPE_BNE, ILLEGAL_ADRESS_TYPE_RED, ILLEGAL_ADRESS_TYPE_PRN, ILLEGAL_ADRESS_TYPE_JSR, ILLEGAL_ADRESS_TYPE_RTS, ILLEGAL_ADRESS_TYPE_STOP, ILLEGAL_BEGINNING_OF_OPERAND
    , MULTIPLE_PLUS_OR_MINUS_SIGN, PLUS_OR_MINUS_SIGN_AFTER_NUMBER, ILLEGAL_NUMBER, ILLEGAL_LABEL, THERE_IS_NO_NUMBER_AFTER_SIGN, THERE_IS_NO_NUMBER_AFTER_BEGINNING_OF_NUMBER_OPERAND,
    OPERAND_MUST_BE_LABEL_IN_THIRD_ADRESS_TYPE, ILLEGAL_BEGINNING_OF_PARAMETER, ILLEGAL_STRING, LETTER_AFTER_END_DOUBLE_QUOTES, TWO_LABELS_WITH_THE_SAME_NAME
    , LABEL_BEFORE_EXTERN_OR_ENTRY_GUIDANCE, LABEL_WITH_SAVE_WORD, ILLEGAL_INSTRUCTION_NAME, OPEN_FILE_ERROR, MACRO_WITH_SAVE_WORD, NO_PARAMETER_IN_DATA_GUIDANCE, NO_PARAMETER_IN_STRING_GUIDANCE
    , NO_END_APOSTROPHES_IN_STRING_GUIDANCE, EMPTY_STRING, ILLEGAL_THIRD_ADRESS_TYPE, LETTERS_AFTER_END_PARENTHESIS, LABEL_THAT_NOT_EXIST_IN_ENTRY_GUIDANCE, LABEL_EXTERNAL_AND_ENTRY, LABEL_THAT_NOT_DEFINED, ALLOCATION_NOT_SUCCEEDED
    , ILLEGAL_AMOUNT_OF_LABELS_IN_EXTERN_OR_ENTRY_GUIDANCE, NO_NAMES_OF_FILES_IN_COMMAND_LINE, TWO_MACROS_WITH_THE_SAME_NAME, ILLEGAL_LABEL_LENGTH
} errors;
#endif