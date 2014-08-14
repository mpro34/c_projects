/*  Subtraction.cpp : Defines the entry point for the console application.
    Prompts user for two inputs and subtracts those values if correct inputs.
*/

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

//Prompts user for input.
char *buffer = "Welcome to the Subtraction Program!";
char *buffer1 = "Enter the first number: ";
char *buffer2 = "Enter the second number: ";

//Declares & Initializes temporary variables.
int a, b, c, d  = 0;

//Calls the subtraction function on arg1 and arg2.
int sub(int arg1, int arg2);

int _tmain(int argc, _TCHAR* argv[]) {
_cputs(buffer);
_putch('\r');
_putch('\n');
_cputs(buffer1);			//Displays buffer1 message
a = _getche();			    //Puts first input in variable a

//Accounts for multiple numbered inputs
while(a>='0' && a <= '9') {
	_asm sub a, 30h;//
	b = b * 10 + a;
	a = _getche();
}
_putch('\r');
_putch('\n');
_cputs(buffer2);			//Displays buffer2 message
c = _getche();			//Puts second input in c

//Accounts for multiple numbered inputs
while(c>='0' && c <= '9') {
	_asm sub c, 30h;//
	d = d * 10 + c;
	c = _getche();
}
_putch('\r');
_putch('\n');

//Calls the subtraction function
sub(b,d);

_putch('\r');
_putch('\n');
getche();
return 0;
}

//Subtracts two integers given as parameters.
int sub(int arg1, int arg2) {
	int result;
_asm {
	mov eax, arg1
	mov ebx, arg2
	sub eax,ebx
	mov result,eax
}
_cprintf("The Subtraction Yields: %d",result);				//Outputs the result
}


