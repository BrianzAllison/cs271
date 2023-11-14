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

(START)
    @SCREEN 
    D = A 
    @addr
    M = D

    @8192
    D = A 
    @pixels
    M = D 

(CHECK)
    @pixels
    D = M 
    @START
    D;JMP

    @KBD 
    D = M 

    @BLACKSC 
    D;JNE

    @BLANKSC
    D;JEQ

    (BLACKSC)
        @addr
        A = M 
        M = -1 

        @addr
        M = M + 1

        @pixels
        M = M - 1

        @CHECK 
        0;JMP

    (BLANKSC)
        @addr
        A = M 
        M = 0

        @addr 
        M = M + 1

        @pixels
        M = M - 1

        @CHECK
        0;JMP
