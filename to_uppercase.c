#define  WROTE_CS356_IO 1
#include <HERA.h>

void HERA_main() {
  DLABEL(char_output)
    INTEGER('G')

  // putchar_ord with string...
  SET(R1, char_output)
  LOAD(R1, 0, R1) // R1 has the character to make uppercase

  CALL(FP_alt, to_uppercase)

  HALT()

  // RETURNS THE CHARACTER FOR HARDWARE IN R1
  LABEL(to_uppercase) // R1 has the character
    SET(Rt, ~0x20) // set bit mask into temp register
    AND(R1, R1, Rt) // convert to uppercase
    RETURN(FP_alt, PC_ret)

}
