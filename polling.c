#define  WROTE_CS356_IO 1
#include <HERA.h>

//Two parameters for putchar function: character and terminal
//R1: holds the terminal (0 = terminal 1, 1 = terminal 2)
//R2: holds the character (loaded from R4)
//R3: holds the keyboard (0 = keyboard 1, 1 = keyboard 2)
//---> we will be checking keyboard 1 first based on rough algorithm provided by JD
//R4: holds address of where ASCII from keyboard N is stored
//---> provides more versatility, we don't need to put it in R4 every time
//R5: does keyboard 1 have a character? (0 = no, 1 = yes)
//R6: does keyboard 2 have a character? (0 = no, 1 = yes)
//R7: holds the next address to load characters into
//R8: holds the current character from the buffer
//R9: register that holds thing to check against (for example, 1 for if register is ready, 10 for newline, and 0 for empty memory)

void HERA_main()
{
  SET(R7, 0) // always put characters in buffer from location 0

  LABEL(infinite_loop)  // while(true)
    SET(R10, 50)
    LABEL(simulate_os)  // for (a fixed number of times); // simulate OS
      DEC(R10, 1)
      BNZ(simulate_os)

    //CHECKING IF KEYBOARD1
    OPCODE(9733) //0010 0110 0000 0101 for loading into R5, if keyboard1 is ready
    SET(R9, 1) //for checking for character
    CMP(R5, R9) //returns 0 if equal
    BNZ(check_keyboard2) // if keyboard1 does not have a character, branch
      //keyboard1 has a character
      CALL(FP_alt, getchar_ord) // Display that character onto TTY0
      MOVE(R1, R5) // set which terminal to R1 for putchar
      CALL(FP_alt, putchar_ord) // Display that character onto TTY0

    //CHECKING IF KEYBOARD2
/*    LABEL(check_keyboard2)
    OPCODE(9989) //0010 0111 0000 0101 for loading into R6, if keyboard2 is ready
      SET(R9, 1) //for checking for character
      CMP(R6, R9) // returns 0 if equal
      BNZ(done_checking) // if keyboard2 does not have a character, branch
        //keyboard2 has a character
        CALL(FP_alt, getchar_ord)
        SET(R9, 10) // for checking newline
        CMP(R2, R9) // comparing character to new line (ascii)
        BNZ(not_newline) // if that character is not a newline, branch
          //it's a newline
          // put the newline into memory
          STORE(R7, 0, R2) // put that character in memory
          INC(R7, 1) // go to the next place in memory

          //loop through characters in memory and output each one
          LABEL(buffer_loop)
            SET(R9, 0)
            LOAD(R8, 0, R9) // load the character at location 0 in memory
            SET(R9, 10) // for checking for newline
            CMP(R8, R9) // is the character we just loaded a newline?
            BNZ(done_checking) // yes, so we're done
            // no...
            CALL(FP_alt, getchar_ord)
            MOVE(R1, R6) // set which terminal to R1 for putchar
            CALL(FP_alt, putchar_ord)

          //erase memory i.e. set what we used all back to 0 for next check ?

        LABEL(not_newline) // else
          //it's not a newline
          CALL(FP_alt, getchar_ord) // load from buffer
          //store character from buffer in memory (need to keep track) ?
          //store address of starting point in memory in R7 but this only needs to happen once ?
          STORE(R7, 0, R2) // then put that character in memory
          INC(R7, 1) // go to the next place in memory */


    LABEL(done_checking)
      BR(infinite_loop) // unconditional branch

  HALT()


  // RETURNS THE ASCII CHARACTER IN R2
  LABEL(getchar_ord)
    MOVE(R2, R4) // put the ascii character into R2 for putchar
    OPCODE(9524) //0010 0101 0011 0100
    RETURN(FP_alt, PC_ret)


  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    OPCODE(9234) //0010 0100 0001 0010
    RETURN(FP_alt, PC_ret)

}
