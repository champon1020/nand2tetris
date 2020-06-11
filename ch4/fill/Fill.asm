// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
(LOOP)
@KBD
D=M
@SET_BLACK
D;JGT
@SET_WHITE
D;JLT

(SET_BLACK)
@color
M=1
@DRAW
0;JMP

(SET_WHITE)
@color
M=0
@DRAW
0;JMP

(DRAW)
@8192
D=A
@cnt
M=D
@SCREEN
D=A
@pos
M=D

(DRAWING)
@cnt
D=M
@1
D=D-A
@END
D;JLT

@cnt
M=D
@color
D=M
@pos
A=M
M=D

@pos
M=M+1
@DRAWING
0;JMP

(END)
@LOOP
0;JMP
