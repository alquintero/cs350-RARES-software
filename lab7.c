/* TEAM NAME: RED TEAM (Amanda Quintero, Sophia Trump, Rohan Shukla, Emily Lobel, Russell Gerhard)
*/

#define  WROTE_CS356_IO 1
#include <HERA.h>

// the hardware will signal RTI???? and we need a fixed counter that when
// fixed counter == some number, hardware signals RTI

void HERA_main()
{

  // SET UP AND STORE PRESET VALUES FOR THREAD 1
  SET(R7, 1000)
  SET(R1, 1)
  SET(R2, 1)
  SET(R3, 1)
  SET(R4, 1)
  SET(R5, 1)
  SET(R6, 1)
  SET(R8, 1)
  SET(R9, 1)
  SET(R10,1)

  STORE(R1, R7)
  INC(R7, 1)
  STORE(R2, R7)
  INC(R7, 1)
  STORE(R3, R7)
  INC(R7, 1)
  STORE(R4, R7)
  INC(R7, 1)
  STORE(R5, R7)
  INC(R7, 1)
  STORE(R6, R7)
  INC(R7, 1)
  STORE(R7, R7)
  INC(R7, 1)
  STORE(R8, R7)
  INC(R7, 1)
  STORE(R9, R7)
  INC(R7, 1)
  STORE(R10, R7)
  INC(R7, 1)

  // save flags
  SAVEF(R3)
  STORE(R3, R7)
  INC(R7, 1)


  // SET UP AND STORE PRESET VALUES FOR THREAD 2
  SET(R7, 2000)
  SET(R1, 2)
  SET(R2, 2)
  SET(R3, 2)
  SET(R4, 2)
  SET(R5, 2)
  SET(R6, 2)
  SET(R8, 2)
  SET(R9, 2)
  SET(R10,2)

  STORE(R1, R7)
  INC(R7, 1)
  STORE(R2, R7)
  INC(R7, 1)
  STORE(R3, R7)
  INC(R7, 1)
  STORE(R4, R7)
  INC(R7, 1)
  STORE(R5, R7)
  INC(R7, 1)
  STORE(R6, R7)
  INC(R7, 1)
  STORE(R7, R7)
  INC(R7, 1)
  STORE(R8, R7)
  INC(R7, 1)
  STORE(R9, R7)
  INC(R7, 1)
  STORE(R10, R7)
  INC(R7, 1)

  // save flags
  SAVEF(R3)
  STORE(R3, R7)
  INC(R7, 1)

  // SET UP AND STORE PRESET VALUES FOR OPERATING SYSTEM
  SET(R7, 0)
  SET(R1, 3)
  SET(R2, 3)
  SET(R3, 3)
  SET(R4, 3)
  SET(R5, 3)
  SET(R6, 3)
  SET(R8, 3)
  SET(R9, 3)
  SET(R10,3)

  STORE(R1, R7)
  INC(R7, 1)
  STORE(R2, R7)
  INC(R7, 1)
  STORE(R3, R7)
  INC(R7, 1)
  STORE(R4, R7)
  INC(R7, 1)
  STORE(R5, R7)
  INC(R7, 1)
  STORE(R6, R7)
  INC(R7, 1)
  STORE(R7, R7)
  INC(R7, 1)
  STORE(R8, R7)
  INC(R7, 1)
  STORE(R9, R7)
  INC(R7, 1)
  STORE(R10, R7)
  INC(R7, 1)

  // save flags
  SAVEF(R3)
  STORE(R3, R7)
  INC(R7, 1)

  LABEL(operating_system)  // while(true)

    // general flow of control:
    // (1) store the values of the operating system (save the state that is being interrupted)
    // (2) load the values of the current thread (prep the current thread)
    // (3) run the thread
    // (4) stop running the thread
    // (5) store the values of the current thread (save the state of the thread after it has finished running)
    // (6) load the values of the operating system (restore the state that was interrupted)

    // thread 1
    // hardware should do: SET(R7, 0) and call interrupt_store
    // hardware should do: SET(R7, 1000) and call interrupt_load
    SWI(1)
    // hardware should do: SET(R7, 1000) and call interrupt_store
    // hardware should do: SET(R7, 0) and call interrupt_load

    // thread 2
    // hardware should do: SET(R7, 0) and call interrupt_store
    // hardware should do: SET(R7, 2000) and call interrupt_load
    SWI(2)
    // hardware should do: SET(R7, 2000) and call interrupt_store
    // hardware should do: SET(R7, 0) and call interrupt_load

  BR(operating_system)     // infinite loop. simulate os

  HALT()

  // SAVES THE STATE IN RAM
  // ASSUMES THE CURRENT THREAD NUMBER IS IN R2
  LABEL(interrupt_store)
    // put all the registers into RAM, starting at location R2
    STORE(R1, R7)
    INC(R7, 1)
    STORE(R2, R7)
    INC(R7, 1)
    STORE(R3, R7)
    INC(R7, 1)
    STORE(R4, R7)
    INC(R7, 1)
    STORE(R5, R7)
    INC(R7, 1)
    STORE(R6, R7)
    INC(R7, 1)
    STORE(R7, R7)
    INC(R7, 1)
    STORE(R8, R7)
    INC(R7, 1)
    STORE(R9, R7)
    INC(R7, 1)
    STORE(R10, R7)
    INC(R7, 1)

    // save flags
    SAVEF(R3)
    STORE(R3, R7)
    INC(R7, 1)

    // state is saved, so do stuff now
    // actual thread behavior
    CALL(FP_alt, busy_function)

  RETURN(FP_alt, PC_ret)


  // Puts the state back from RAM
  // ASSUMES THE CURRENT RELEVANT RAM LOCATION IS IN R2
  LABEL(interrupt_load)
    //set the pointer back to the beginning of the place in RAM
    DEC(R7, 11)

    // put all the registers back
    LOAD(R1, R7)
    INC(R7, 1)
    LOAD(R2, R7)
    INC(R7, 1)
    LOAD(R3, R7)
    INC(R7, 1)
    LOAD(R4, R7)
    INC(R7, 1)
    LOAD(R5, R7)
    INC(R7, 1)
    LOAD(R6, R7)
    INC(R7, 1)
    LOAD(R7, R7)
    INC(R7, 1)
    LOAD(R8, R7)
    INC(R7, 1)
    LOAD(R9, R7)
    INC(R7, 1)
    LOAD(R10, R7)
    INC(R7, 1)

    // put the flags back
    RSTRF(R7)

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
