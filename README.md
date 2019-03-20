# cs350-RARES-software
This is for our software team.

## DESIGN DOC: 

*For 3/3/18 Due Date: Output.*
Our team began with writing a HERA program that converted uppercase to lowercase characters and vice versa, reverse_case.h.cc. We did this using arithmetic via a bit mask, 0010 0000, and the XOR function. This piece of code was very useful when writing putchar.c (our function that takes a character from a terminal and puts it into a register).

After useful discussion with our hardware team and the assignment specifications, we decided to store the terminal (0 for terminal 1 and 1 for terminal 2) in R1 and the character in R2. Moreover, we decided to create an new opcode to represent putchar using HERA's OPCODE which takes in a decimal input where Hassem converts it to hex for our ROM to process.


*For 3/26/18 Due Date: Polling.*
In our discussion with the hardware team, we decided to store the keyboard (0 for keyboard 1 and 1 for keyboard 2) in R6 and the character in R7 (not sure if we should use R3 and R4 since we used them for putchar and may not want to overwrite these values).
