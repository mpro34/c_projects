/*  Signal.cpp : Defines the entry point for the console application.
    Adds two signals, determines the period of a signal, and prints
    the corresponding data.
*/

#include "stdafx.h"
#include "conio.h"
#define LEN 13
//Function Prototypes
void print_vector(int *, int);
int find_period(int *, int);
void add_signals(int *, int *, int *, int);

int _tmain(int argc, _TCHAR* argv[])
{
int signal1 [] = {1, 2, 3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1};  //User defined signal1
int signal2 [] = {1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1};    //User defined signal2
int signal3 [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};       //Temporary empty signal array

//Adds signal 1 and signal 2.
add_signals(signal1, signal2, signal3, LEN);

//Finds the periods of all 3 signals.
int p1 = find_period(signal1, LEN);
int p2 = find_period(signal2, LEN);
int p3 = find_period(signal3, LEN);

printf("\nChris Whiting\n");
printf("\nSignal 1: ");
print_vector(signal1, LEN);
printf("\nSingal 1's period: %d samples", p1);
printf("\nSignal 2: ");
print_vector(signal2, LEN);
printf("\nSingal 2's period: %d samples", p2);
printf("\nSignal 1 + Signal 2: ");
print_vector(signal3, LEN);
printf("\nSingal 1+2's period: %d samples", p3);
_getche();
return 0;
}
void print_vector(int * vector, int size)
{
printf("[");
for(int i = 0; i < size; i++)
{
printf(" %d", vector[i]);
}
printf(" ]");
return;
}

//Iterates through the s1 and s2 while placing the sum into s3.
void add_signals(int * s1, int * s2, int * s3, int len)
{
int temp1;
int temp2;
_asm
{
	push es
	push edi
	push esi
	push ds
	pop es

		mov ecx, 0				//Initializes the count
		mov eax, s1				//Moves s1 array into eax
		mov ebx, s3				//Moves s3 array into ebx
top:	lea esi, [eax+ecx*4]	//loads esi with value of s1[ecx]
		lea edi, [ebx+ecx*4]   //loads edi with value of s3[ecx]
		mov edx, [esi]
		add [edi], edx			//Adds each element
		inc ecx
		cmp ecx, len			//Checks to see if count is 13
		jle top					//loops to top if less than or equal to 13 (LEN)

		mov ecx, 0				//A repeat of the above instructions, instead s2 and s3 are added.
		mov eax, s2				//This was to preserve the original values of s1 and s2
		mov ebx, s3
bot:	lea esi, [eax+ecx*4]  //s2
		lea edi, [ebx+ecx*4]  //s3
		mov edx, [esi]
		add [edi], edx
		inc ecx
		cmp ecx, len
		jle bot

	pop edi
	pop esi
	pop es
}
return;
}

//Determines the period of s, which is the amount of samples it takes to repeat.
int find_period(int * s, int len)
{
int period;
int compare;
_asm
{
		mov eax, 0				//Clears eax
		mov eax, s				//Moves s array into eax
		mov ebx, 0				//Initializes the count for the period
		mov ecx, 0				//Initializes the count for the array


		lea edx, [eax+ecx*4]	//loads edx with value of s[ecx]
		mov edi, [edx]			//loads di with the compare value
		mov compare, edi
here:	inc ecx
		lea edx, [eax+ecx*4]
		inc ebx
		mov esi, [edx]
		cmp compare, esi			//Compares the first value in the array with each subsequenct value to determine when it repeats.
		jne here
		mov period, ebx				//The period is determined by the number of time the here loop iterated.
}
return period;
}
