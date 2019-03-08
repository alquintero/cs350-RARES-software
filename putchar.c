#define  WROTE_CS356_IO 1
#include <HERA.h>

//Two parameters for putchar function: character and terminal
//R1: holds the terminal (0 = terminal 1, 1 = terminal 2)
//R2: holds the character (loaded from R3 memory address)

void HERA_main()
{
  DLABEL(char_output)
    INTEGER('a')

  // putchar_ord with 1 character
  SET(R3, char_output)
  SET(R1, 0) // R1 has the terminal (proxy: terminal 1)
  CALL(FP_alt, putchar_ord)
  HALT()

  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    LOAD(R2, 0, R3) // load the current character at location R3 into R2
    OPCODE(9234) //0010010000010010
    RETURN(FP_alt, PC_ret)
}
