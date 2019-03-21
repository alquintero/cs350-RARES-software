#define  WROTE_CS356_IO 1
#include <HERA.h>

//Two parameters for putchar function: character and terminal
//R1: holds the terminal (0 = terminal 1, 1 = terminal 2)
//R2: holds the character (loaded from R4)
//R4: ASCII from keyboardN
//R5: keyboard 1 has a letter? (0 = no, 1 = yes)
//R6: keyboard 2 has a letter? (0 = no, 1 = yes)

void HERA_main()
{

  LABEL(infinite_loop)  // while(true)
    LOAD(R10, 50)
    LABEL(simulate_os)  // for (a fixed number of times); // simulate OS
      DEC(R10, 1)
      BNZ(simulate_os)

    // OPCODE() for loading into R5, if keyboard 1 is ready
    CMP(R5, 1)
    BNZ(check_keyboard2) // if keyboard0 has a character
      CALL(FP_alt, getchar_ord) // Display that character onto TTY0
      MOVE(R1, R5) // set which terminal to R1 for putchar
      CALL(FP_alt, putchar_ord) // Display that character onto TTY0

    LABLE(check_keyboard2)
    // OPCODE() for loading into R6, if keyboard 2 is ready
      CMP(R6, 1)
      BNZ(done_checking) // if keyboard2 has a character
        CALL(FP_alt, getchar_ord)
        CMP(R4, 0x0A)
        BNZ(not_newline) // if that character is a newline
          // load from buffer?
          MOVE(R1, R6) // set which terminal to R1 for putchar
          CALL(FP_alt, putchar_ord)

        LABEL(not_newline) // else
          // Add that character to the buffer?

    LABEL(done_checking)
      BR(infinite_loop) // unconditional branch

  HALT()


  // RETURNS THE ASCII CHARACTER IN R2
  // instructions say getchar takes parameter for "which keyboard"...
  // not sure how that applies here?
  LABEL(getchar_ord)
    MOVE(R2, R4) // put the ascii character into R2 for putchar
    OPCODE(???)
    RETURN(FP_alt, PC_ret)


  // RETURNS THE CHARACTER FOR HARDWARE IN R2
  LABEL(putchar_ord) // R1 has which screen, R2 has the character
    OPCODE(9234) //0010010000010010
    RETURN(FP_alt, PC_ret)

}
