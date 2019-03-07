#define  WROTE_CS356_IO 1
#include <HERA.h>

//Two parameters for putchar function: character and terminal
//R1: holds the terminal (0 = terminal 1, 1 = terminal 2)
//R2: holds the character (loaded from R3 memory address)

void HERA_main() {
  DLABEL(char_output)
    INTEGER('a')

  DLABEL(string_output)
    LP_STRING("Hello")

  // putchar_ord with 1 character
  SET(R3, char_output)
  SET(R1, 0) // R1 has the terminal (proxy: terminal 1)
  CALL(FP_alt, putchar_ord)
/*
  // putchar_ord with string...
  SET(R3, string_output)
  LOAD(R4, 0, R3) // R4 has the length of the string
  INC(R3, 1) // R3 has the first character of the string
  LABEL(get_string)
    CALL(FP_alt, putchar_ord)
    INC(R3, 1) // R3 goes to the next character
    DEC(R4, 1) // decrement the number of characters left -- THIS WILL SET THE FLAG FOR THE BRANCH
    BNZR(get_string)
*/
  HALT()

  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    LOAD(R2, 0, R3) // load the current character at location R3 into R2
    OPCODE(9234) //0010010000010010
    RETURN(FP_alt, PC_ret)
