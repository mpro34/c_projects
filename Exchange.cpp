/* Exchange.cpp : Defines the entry point for the console application.
    Takes two arrays of integers as parameters and exchanges their values.
*/

#include "stdafx.h"
#include "conio.h"
void print_vector(int * vector, int size);
void exchange_vector(int * array1, int * array2, int * temp, int num);
int _tmain(int argc, _TCHAR* argv[])
{
int vector1 [] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};  //Vector 1 to exchange
int vector2 [] = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};  //Vector 2 to exchange
int temp [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

printf("\nvector1_old: ");
print_vector(vector1, 10);
printf("\nvector2_old: ");
print_vector(vector2, 10);

exchange_vector(vector1, vector2, temp, 10);
printf("\nvector1_new: ");
print_vector(vector1, 10);
printf("\nvector2_new: ");
print_vector(vector2, 10);
_getche();
return 0;
}
void exchange_vector(int * array1, int * array2, int * tempa, int num)
{

_asm
{
push es				//save registers
push edi
push esi
push ds				//Copy Data Segment into Stack Segment
pop es

mov esi, array1		//Array1 into temp
mov edi, tempa
mov ecx, num
rep movsd

mov esi, array2		//Array2 into Array1
mov edi, array1
mov ecx, num
rep movsd			//Copies data from DS:SI and pastes into ES:DI

mov esi, tempa		//temp into Array2
mov edi, array2
mov ecx, num
rep movsd			//Copies data from DS:SI and pastes into ES:DI

pop edi
pop esi
pop es				//restore registers


}
return;
}

//Prints the vector once its data has been set.
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

