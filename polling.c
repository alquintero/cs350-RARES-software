/* TEAM NAME: RED TEAM (Amanda Quintero, Sophia Trump, Rohan Shukla, Emily Lobel, Russell Gerhard)
*/

#define  WROTE_CS356_IO 1
#include <HERA.h>

//Two parameters for putchar function: character and terminal
//R1: holds the terminal (0 = terminal 1, 1 = terminal 2)
//R2: holds the character (loaded from R4)
//R3: holds the keyboard (0 = keyboard 1, 1 = keyboard 2)
//---> we will be checking keyboard 1 first based on rough algorithm provided by JD
//R4: holds the ASCII character from keyboard N, (for use in getchar_ord to return ASCII in R2. R2 is then used in putchar_ord)
//---> provides more versatility, we don't need to put it in R4 every time
//R5: does keyboard 1 have a character? (0 = no, 1 = yes)
//R6: does keyboard 2 have a character? (0 = no, 1 = yes)
//R7: holds the next address to load characters into from the buffer
//R8: placeholder reg for local operations
//R9: placeholder reg for local operations

void HERA_main()
{

  LABEL(infinite_loop)  // while(true)
    SET(R9, 3)
    LABEL(simulate_os)  // for (a fixed number of times); // simulate OS
      DEC(R9, 1)
      BNZ(simulate_os)

      //CHECKING IF KEYBOARD1 HAS CHARACTER
      OPCODE(9733) //0010 0110 0000 0101 for loading into R5, if keyboard1 is ready
      SET(R9, 1) //for checking for character
      CMP(R5, R9) //returns 0 if equal
      BNZ(check_keyboard2) // if keyboard1 does not have a character, branch
        //keyboard1 has a character
        SET(R3, 0) // set which terminal, to pass to getchar_ord
        CALL(FP_alt, getchar_ord) // Display that character onto TTY0
        CALL(FP_alt, putchar_ord) // Display that character onto TTY0

      //KEYBOARD1 IS EMPTY, CHECKING IF KEYBOARD2 HAS CHARACTER
      LABEL(check_keyboard2)
        OPCODE(9990) //0010 0111 0000 0110 for loading into R6, if keyboard2 is ready
        SET(R9, 1) //for checking for character
        CMP(R6, R9) // returns 0 if equal
        BNZ(done_checking) // if keyboard2 does not have a character, branch
          //keyboard2 has a character
          SET(R3, 1) // set which terminal, to pass to getchar_ord
          CALL(FP_alt, getchar_ord) // get the character
          SET(R9, 10) // for checking newline
          CMP(R2, R9) // comparing character to new line (ascii)

          //CHECKING IF CHARACTER IS A NEWLINE
          BNZ(not_newline) // if that character is not a newline, branch
            //it's a newline
            STORE(R2, 0, R7) // put that character in memory
            SET(R7, 0) // reset for next buffer string that needs to be stored
            SET(R8, 10) // for checking when we are finished looping (if newline is found)
            SET(R9, 0) // for looping from location 0 in memory
            
            //LOOPING THROUGH CHARACTERS (FROM BUFFER) THAT ARE STORED IN MEMORY
            LABEL(memory_loop)
              LOAD(R4, 0, R9) // load the character at location R9 in memory to R4 for putchar
              CALL(FP_alt, putchar_ord) //want to ouput both newline and other characters
              CMP(R4, R8) // is the character we just loaded a newline?
                BZ(done_checking) // yes, it's a new line
                  // no, it's a character
                  INC(R9, 1) // go to the next place in memory
                  BR(memory_loop) // always branch back because didn't encounter newline in memory

        //CHARACTER IS NOT A NEWLINE
        LABEL(not_newline) //else
          STORE(R2, 0, R7) // store current character (which is in R2) in memory
          INC(R7, 1) // go to the next place in memory

    LABEL(done_checking)
      BR(infinite_loop) // unconditional branch

  HALT()


  // RETURNS THE ASCII CHARACTER IN R2
  LABEL(getchar_ord)
    OPCODE(9524) //0010 0101 0011 0100
    RETURN(FP_alt, PC_ret)


  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    //moves must happen after OPCODE call to actually move data from correct registers
    MOVE(R1, R3) // put which terminal into R1 for putchar
    MOVE(R2, R4) // put the ascii character into R2 for putchar
    OPCODE(9234) //0010 0100 0001 0010
    RETURN(FP_alt, PC_ret)

}
