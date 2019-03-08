# cs350-RARES-software
This is for our software team.

## DESIGN DOC: 

*For 3/3/18 Due Date.*
Our team began with writing a HERA program that converted uppercase to lowercase characters and vice versa, reverse_case.h.cc. We did this using arithmetic via a bit mask, 0010 0000, and the XOR function. This piece of code was very useful when writing putchar.c (our function that takes a character from a terminal and puts it into a register).

After useful discussion with our hardware team and the assignment specifications, we decided to store the terminal in R1 and the character in R2. Moreover, we decided to create an new opcode to represent putchar using HERA's OPCODE which takes in a decimal input where Hassem converts it to hex for our ROM to process.
