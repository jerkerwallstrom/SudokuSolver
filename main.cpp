/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//#include <stdio.h>
#include <iostream>
#include <string>
#include "Soduko.cpp"
#include "readfile.cpp"
using namespace mySodukoLib;

int main()
{
    printf("Hello soduko cheater");
    printf("\n");
    Soduko* soduko = new Soduko();

    //readfile* rf = new readfile("C:\\Dev\\cPlusPlus\\Soduko\\SudokuFiles\\SudokuEasy.txt");
    //readfile* rf = new readfile("C:\\Dev\\cPlusPlus\\Soduko\\SudokuFiles\\SudokuMedium.txt");
    //readfile* rf = new readfile("C:\\Dev\\cPlusPlus\\Soduko\\SudokuFiles\\Sudoku.txt");
    readfile* rf = new readfile("Sudoku.txt");
    for (int y = 1; y <= 9; y++) {
      soduko->setupRow(y, (rf->getRow(y)));
    }

    //EMPTY template
    // soduko->setupRow(1, "000 000 000");
    // soduko->setupRow(2, "000 000 000");
    // soduko->setupRow(3, "000 000 000");
    // soduko->setupRow(4, "000 000 000");
    // soduko->setupRow(5, "000 000 000");
    // soduko->setupRow(6, "000 000 000");
    // soduko->setupRow(7, "000 000 000");
    // soduko->setupRow(8, "000 000 000");
    // soduko->setupRow(9, "000 000 000");
    //Lätt
    // soduko->setupRow(1, "107064309");
    // soduko->setupRow(2, "090702015");
    // soduko->setupRow(3, "602030008");
    // soduko->setupRow(4, "530240007");
    // soduko->setupRow(5, "060010050");
    // soduko->setupRow(6, "708090460");
    // soduko->setupRow(7, "006153800");
    // soduko->setupRow(8, "045000231");
    // soduko->setupRow(9, "300008000");
    
    //Medium
    // soduko->setupRow(1, "205093010");
    // soduko->setupRow(2, "001600000");
    // soduko->setupRow(3, "000100583");
    // soduko->setupRow(4, "030910000");
    // soduko->setupRow(5, "600038004");
    // soduko->setupRow(6, "010005208");
    // soduko->setupRow(7, "120006040");
    // soduko->setupRow(8, "000040050");
    // soduko->setupRow(9, "060000020");
    
    //Svårt
    // soduko->setupRow(1, "650021000");
    // soduko->setupRow(2, "000000000");
    // soduko->setupRow(3, "000500249");
    // soduko->setupRow(4, "301000002");
    // soduko->setupRow(5, "000000034");
    // soduko->setupRow(6, "000100000");
    // soduko->setupRow(7, "060750901");
    // soduko->setupRow(8, "000904500");
    // soduko->setupRow(9, "000610027");

    //Supersvår 27 mar DN
    // soduko->setupRow(1, "007400000");
    // soduko->setupRow(2, "000000000");
    // soduko->setupRow(3, "080000002");
    // soduko->setupRow(4, "006000038");
    // soduko->setupRow(5, "000900000");
    // soduko->setupRow(6, "050280046");
    // soduko->setupRow(7, "000620070");
    // soduko->setupRow(8, "062053084");
    // soduko->setupRow(9, "000804205");

    //Supersvår 30 mar DN
    // soduko->setupRow(1, "000906000");
    // soduko->setupRow(2, "605020000");
    // soduko->setupRow(3, "000000004");
    // soduko->setupRow(4, "510000960");
    // soduko->setupRow(5, "000600002");
    // soduko->setupRow(6, "090040058");
    // soduko->setupRow(7, "009000000");
    // soduko->setupRow(8, "002405006");
    // soduko->setupRow(9, "000080300");

    //Jättesvår 30 mar DN
    // soduko->setupRow(1, "503007000");
    // soduko->setupRow(2, "000046000");
    // soduko->setupRow(3, "040000000");
    // soduko->setupRow(4, "000000068");
    // soduko->setupRow(5, "620000030");
    // soduko->setupRow(6, "010603207");
    // soduko->setupRow(7, "008010003");
    // soduko->setupRow(8, "000000500");
    // soduko->setupRow(9, "204800001");
    soduko->testValuesInItems();
    soduko->printfunction();
    soduko->Solution();
    

    return 0;
}
