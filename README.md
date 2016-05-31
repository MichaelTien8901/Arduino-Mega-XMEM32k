# Arduino-Mega-XMEM32k

Arduino Mega 2560 adding external 32K memory

##Overview

ATMEGA CPU for Arduino has one drawback in hardware specification.  That is, data memory(RAM) is not enough.  Due to CPU 
architecture, constant data array will consume RAM memory if you want to direct acesss.

## External Memory for ATMEGA 2560

For ATMEGA 2560, it has external memory bus to add more SRAM(data) up to 64K(overlapping internal memory).  In this project, we only add 32K memory from address 0x8000 to 0xFFFF.  With internal 8K RAM, you will have total 40K RAM.

## Using External Memory at Heap(for memory allocation)

We can certainly configure program RAM(stack and heap) at this external memory.  But then we probably leave out the internal 8k memory. This project configure external memory as heap so that internal 8K memory is still used as before.  You have to 
allocate the external memory before use.  The sample program demo the usage.

## How to Install to Arduino IDE

Add the content of file **platform\boards.txt** into the file **[ARDUINO INSTALL FOLDER]\hardware\arduino\avr\boards.txt**.
Before you compile the project xmem32k, choose the board **Tools->board->Mega with heap 32K external RAM**.  

## Circuit Diagram

ATMEGA 2560 datasheet has the information how to add external memory.
Arduino UNO hardware doesn't has the external memory bus.

## PINs Used

| Signal | Port | Arduino Defined Pin Number |
|------- | ----------|-----------------------|
| WR      | (PG0)    | 41 |
| RD      | (PG1)    | 40 |
|ALE      | (PG2)    | 39 |
|AD0-AD7 | (PA0-PA7) |22, 23, ..., 29 |
|A8-A15  | (PC0-PC7) |37, 36, ..., 30 |

