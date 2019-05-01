/* TEAM NAME: RED TEAM (Amanda Quintero, Sophia Trump, Rohan Shukla, Emily Lobel, Russell Gerhard)
*/

#define  WROTE_CS356_IO 1
#include <HERA.h>

// the hardware will signal RTI???? and we need a fixed counter that when
// fixed counter == some number, hardware signals RTI

void HERA_main()
{
  SET(R1, 0) // the counter for each thread, used to keep track of state

  LABEL(operating_system)  // while(true)

    // thread 1
    CALL(FP_alt, busy_function)
    SET(R2, 1000)
    CALL(interrupt handler w/ thread 1)
    SWI(opcode thread 1???)

    // thread 2
    CALL(FP_alt, busy_function)
    SET(R2, 2000)
    CALL(interrupt handler w/ thread 2)
    SWI(opcode thread 2???)

    // thread 2
    CALL(FP_alt, busy_function)
    SET(R2, 3000)
    CALL(interrupt handler w/ thread 3)
    SWI(opcode thread 3???)

  BR(operating_system)     // infinite loop. simulate os

  HALT()

  // SAVES THE STATE IN RAM
  // ASSUMES THE CURRENT THREAD NUMBER IS IN R2
  LABEL(interrupt_handler)
    // put all the registers into RAM, starting at location R2
    STORE(R1, R2)
    INC(R2, 1)
    STORE(R2, R2)
    INC(R2, 1)
    STORE(R3, R2)
    INC(R2, 1)
    STORE(R4, R2)
    INC(R2, 1)
    STORE(R5, R2)
    INC(R2, 1)
    STORE(R6, R2)
    INC(R2, 1)
    STORE(R7, R2)
    INC(R2, 1)
    STORE(R8, R2)
    INC(R2, 1)
    STORE(R9, R2)
    INC(R2, 1)
    STORE(R10, R2)
    INC(R2, 1)
  RETURN(FP_alt, PC_ret)



  // BUSY HELPER FUNCTION TO CHANGE STATE
  LABEL(busy_function)

    SET(R2, 5)
    LABEL(increment_by_five) // increment shared register by 5
      INC(R1, 1)
      DEC(R2, 1)
    BNZ(increment_by_five)

    MOVE(R2, R1) // output the value of R1 to terminal 1
    SET(R1, 0)
    CALL(FP_alt, putchar_ord)



  RETURN(FP_alt, PC_ret)


  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    //moves must happen after OPCODE call to actually move data from correct registers
    OPCODE(9234) //0010 0100 0001 0010
    RETURN(FP_alt, PC_ret)
}
