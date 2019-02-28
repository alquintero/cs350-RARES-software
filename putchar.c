#define  WROTE_CS356_IO 1
#include <HERA.h>

void HERA_main() {
  DLABEL(char_output)
    INTEGER('a')

  DLABEL(string_output)
    LP_STRING("Hello")

  // putchar_ord with 1 character
  SET(R3, char_output)
  CALL(FP_alt, putchar_ord)

  // putchar_ord with string...
  SET(R3, string_output)
  LOAD(R5, 0, R3) // R5 has the length of the string
  INC(R3, 1) // R3 has the first character of the string
  LABEL(get_string)
    CALL(FP_alt, putchar_ord)
    INC(R3, 1) // R3 goes to the next character
    DEC(R5, 1) // decrement the number of characters left -- THIS WILL SET THE FLAG FOR THE BRANCH
    BNZR(get_string)

  HALT()

  // RETURNS THE CHARACTER FOR HARDWARE IN R1
  LABEL(putchar_ord) // R3 has the character, R2 has which screen
    LOAD(R1, 0, R3) // load the current character at location R3 into R1
    SET(R2, 0) // R2 has the screen (proxy: screen 1)
    RETURN(FP_alt, PC_ret)

}
