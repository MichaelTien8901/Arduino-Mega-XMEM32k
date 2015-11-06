# Arduino-Mega-XMEM32k
Arduino Mega 2560 with external 32K memory

ATMEGA CPU for Arduino has one drawback in hardware specification.  That is, data memory(RAM) is not enough.  Due to CPU 
architecture, constant data array will use RAM memory if you want to directly acesss(unless you use some library the access 
program memory).  

## External Memory for ATMEGA 2560
For ATMEGA 2560, it has external memory bus to add more SRAM(data) up to 64K(overlapping internal memory).  In this project, we only add 32K memory from address 0x8000 to 0xFFF.  With internal 8K RAM(why so little), you 
will have total 40K RAM.

## Using External Memory at Heap(for memory allocation)
We can certainly configure program RAM(stack and healp) at this external memory.  But then we probably leave out the internal 
8k memory.  This project configure external memory as heap so that internal 8K memory is still used as before.  You have to 
allocate the memory before use.  The sample program demo the usage.

## Configuration in boards.txt
Add the content of file "platform\boards.txt" into the file "[ARDUINO INSTALL FOLDER]\hardware\arduino\avr\boards.txt".
Before you compile the project xmem32k, choose the board [Tools]->[board]->[Mega with heap 32K external RAM].  

## Circuit Diagram
ATMEGA 2560 datasheet has the information how to add external memory.
Sorry, UNO hardware doesn't has the external memory bus.

## PINs Used

| Signal | Port |
|------- | ----------|
| WR      | (PG0)    |
| RD      | (PG1)    |
|ALE      | (PG2)    |
|AD0-AD7 | (PA0-PA7) |
|A8-A15  | (PC0-PC7) |

