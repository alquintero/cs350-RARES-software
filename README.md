# cs350-RARES-software
This is for our software team.

## DESIGN DOC: 

*For 3/3/18 Due Date: Output.*

Our team began with writing a HERA program that converted uppercase to lowercase characters and vice versa, reverse_case.h.cc. We did this using arithmetic via a bit mask, 0010 0000, and the XOR function. This piece of code was very useful when writing putchar.c (our function that takes a character from a terminal and puts it into a register).

After useful discussion with our hardware team and the assignment specifications, we decided to store the terminal (0 for terminal 1 and 1 for terminal 2) in R1 and the character in R2. Moreover, we decided to create an new opcode to represent putchar using HERA's OPCODE which takes in a decimal input where Hassem converts it to hex for our ROM to process.


*For 3/26/18 Due Date: Polling.*

In our discussion with the hardware team, for getchar, we decided to store the keyboard (0 for keyboard 1 and 1 for keyboard 2) in R3 and the character in R4.

We decided to follow the outline given to us in JD's lab since it followed the standard idea of polling: continuously check until things need to be updated. Our software consistently keeps track of keyboard 1 and keyboard 2 simultaneously. It adds any input from keyboard 1 directly into terminal 1, but adds any input from keyboard 2 into a buffer. This buffer doesn't go into terminal 2 until our polling function receives the input from keyboard 2 of a newline, which acts as a signal to print the buffer into terminal 2.

We used registers to help us keep track of everything. As listed in a comment:
- R1 holds the terminal (0 = terminal 1, 1 = terminal 2)
- R2 holds the character (loaded from R4)
- R3: holds the keyboard (0 = keyboard 1, 1 = keyboard 2)
- R4: holds address of where ASCII from keyboard N is stored (which provides more versatility, since the length of the message is only limited by the amount of free memory, rather than storing the characters directly in registers)
- R5 and R6 keep track of whether or not keyboard 1 or keyboard 2 respectively have a character (0 = no, 1 = yes)
- R7 holds the next address to load characters into from the buffer (i.e., memory location)
- R8 and R9 are placeholders for local operations in the software.


*For 4/28/18 Due Date: Interrupts.*

### Instructions for building:

Please note that the code in interrupts.c is not meant to be run via simulation. Rather, it is designed for our microprocessor found here: https://github.com/alquintero/cs350-RARES-hardware

To run using the microprocessor in the repository above, particular sections of code must be placed in specific locations in the microprocessor's ROM. It is necessary that the code is correctly placed in ROM because particular offsets (used in BRANCH instructions) and changes to the program counter (see the hardware README) rely on specific memory locations for flow of control.

In particular, compile the code in interrupts.c using Hassem. Then, place all code before HALT (up to the BRANCH instruction for infinite_loop) in the first memory locations in ROM. The compiled HALT instruction should be moved and placed in ROM after these. Then, the interrupt handler for keyboard 1 (the function k1_helper_function, which is handled under Hassem code ed14 - 100b) should be pasted starting at memory location 1000 in ROM. The interrupt handler for keyboard 2 (the function k2_helper_function, which is handled under Hassem code ed1d - 100b) should be pasted starting at memory location 2000 in ROM.

#### Conceptual description:

In implementation, our code is not very different from polling.c. HOWEVER, conceptually, as this code is meant to handle interrupts instead of polling, it is very different. The flow of control is handled by our microprocessor, rather than via an infinite loop that continually checks keyboard activity through software control. To implement this, we made our code more modular and pulled apart functionality for keyboards 1 and 2 from this infinite loop (to see how this flow of control is handled in execution, look at our hardware repository linked in the previous section). Also, our software accessed the software functionality for keyboards 1 and 2 via a CALL() and RETURN(). This allows us to save and restore the state of our microprocessor when an interrupt occurs. However, these CALLs are only accessed through a check to if an interrupt is not already occurring. This prevents an interrupt from interrupting and interrupt.



* For Lab 7 *

ASSUMES THAT R7 IS A SPECIAL REGISTER THAT IS NOT TO BE CHANGED DURING THREAD EXECUTION! *

Software calls SWI for the current thread (either SWI(1) or SWI(2) -- so both these SWI's need to be implemented in hardware). Then, in hardware, using the location in R7 (location 1000 or 2000, depending on thread), the hardware knows where to start saving the state in RAM. The hardware should jump in RAM to the interrupt_store function (we have decided this will be location 1000 in ROM). The hardware has to save the program counter for the thread! We can't do this in HERA. The interrupt_store function first saves the values of registers, then saves the flags (startiing at the respective location in RAM).

The interrupt_handler function has a function call to busy_function. The hardware should call busy_function a predetermined number of times (5 times) by having some sort of counter that loops over the function a certain number of times (this is arbitrary to make it so that threads do not execute forever). The busy_function outputs either 5 (for thread 1) or 10 (for thread 2), by calling the put_char function. Once this number of times is met, the hardware should jump to interrupt_load, which restores the state. It does this by using the unmodified value in R7, which goes to the respective location in RAM. Like the interrupt_store function, the interrupt_load function restores the registers, then the flags. Restoring the PC should be handled by the hardware. Once the hardware is done restoring the state, the hardware should jump back to the correct place in the operating system (the line following the current SWI) by using the restored PC + 1.

OUTPUT FOR THE PROGRAM (in terminal 1):

5
10
5
10
5
10
... (infinite)


OVERALL FLOW OF THE PROGRAM:

(1) store the values of the operating system (save the state that is being interrupted)
(2) load the values of the current thread (prep the current thread)
(3) run the thread
(4) stop running the thread
(5) store the values of the current thread (save the state of the thread after it has finished running)
(6) load the values of the operating system (restore the state that was interrupted)
