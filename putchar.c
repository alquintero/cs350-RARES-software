#define  WROTE_CS356_IO 1
#include <HERA.h>

void HERA_main() {
  DLABEL(char_output)
    INTEGER('a')

  DLABEL(string_output)
    LP_STRING("Hello")

  SET(R2, 0) // Set R2 to first terminal

  // putchar_ord with 1 character
  SET(R1, char_output)
  CALL(FP_alt, putchar_ord)

/*  // putchar_ord with string...
  SET(R1, string_output)
  LOAD(R5, 0, R1) // R5 has the length of the string
  INC(R1, 1) // R1 has the first character of the string
  LABEL(get_string)
    CALL(FP_alt, putchar_ord)
    DEC(R5, 1) // decrement the number of characters left
    INC(R1, 1) // R1 goes to the next character
    BNZ(get_string) */

  HALT()

  LABEL(putchar_ord) // R1 has the character, R2 has which screen
    LOAD(R1, 0, R1) // R1 has the character
    RETURN(FP_alt, PC_ret)



}
