#define  WROTE_CS356_IO 1
#include <HERA.h>

void HERA_main() {
/*  DLABEL(char_output)
    LP_STRING("Hi?there$*what's up?") */

  DLABEL(char_output)
    INTEGER('~')

  // putchar_ord with string...
  SET(R1, char_output)
  LOAD(R1, 0, R1) // R1 has the character to replace w underscore

  CALL(FP_alt, replace_underscore)

  HALT()

  // RETURNS THE CHARACTER FOR HARDWARE IN R1
  LABEL(replace_underscore) // R1 has the character to replace
    SET(Rt, 0x41)
    CMP(R1, Rt) // R1 >= 'A'?
    BL(check_if_number) // R1 < 'A' indicates R1 is not a letter. so is it a number?
    SET(Rt, 0x5A)
    CMP(R1, Rt) // R1 <= 'Z'?
    BLE(found_valid_char) // R1 >= 'A' && R1 <= 'Z' -- so R1 is a letter
    SET(Rt, 0x61)
    CMP(R1, Rt) // R1 >= 'a'?
    BL(found_invalid_char) // R1 < 'a' indicates R1 is not a letter
    SET(Rt, 0x7A)
    CMP(R1, Rt) // R1 <= 'z'?
    BLE(found_valid_char) // R1 <= 'a' && R1 <= 'z' -- so R1 is a letter
    BG(found_invalid_char) // R1 > 'z' indicates R1 is not a letter, nor a number. so skip to invalid
    LABEL(check_if_number)
      SET(Rt, 0x30)
      CMP(R1, Rt) // R1 >= '0'
      BL(found_invalid_char) // R1 < '0' indicates R1 is not a number
      SET(Rt, 0x39)
      CMP(R1, Rt) // R1 <= '9'?
      BLE(found_valid_char) // R1 >= '0' && R1 <= '9' -- so R1 is a number
    LABEL(found_invalid_char) // R1 is invalid, so replace with '_'
      SET(R1, '_')
      RETURN(FP_alt, PC_ret)
    LABEL(found_valid_char) // R1 is a valid letter, so leave the function
      RETURN(FP_alt, PC_ret)


}
