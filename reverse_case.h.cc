/* Author: Sophia Trump
   File: reverse_case.h.cc

   Reverses the case of 1 (assumed valid) ASCII character.
   (i.e., if it gets 'X' it will return 'x', and if it gets 'x' it will return 'X').
*/

#include <HERA.h>
#include <HERA-print.h>

void HERA_main()
{
  // Store our 3 numbers where we can find them
  DLABEL(letter_to_switch)
    INTEGER('a')

  CBON()             // disable addition-carrying
                     // Programs that use values only less than 2^15 will
		                 // do this to make ADD easier to work with

  SET(R1, letter_to_switch)   // Store the location of "letter_to_switch" in R1
  LOAD(R1, 0, R1)             // Store the value to be switched in R2

  CALL(FP_alt, reverse_case) // call the function to reverse the case

  HALT()             // End program

  LABEL(reverse_case) // the reverse case function
    SET(Rt, 0x20) // set R3 to bit mask 0010 0000
    XOR(R1, R1, Rt) // XOR with R3 bit mask reverses the case
    RETURN(FP_alt, PC_ret)


}
