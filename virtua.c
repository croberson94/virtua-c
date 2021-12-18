// Filename: virtua.c
// Description: Virtual machine in C
// Date: 12/17/21
// Author: Charles Roberson
//
//

// PRE-PROCESSOR DIRECTIVES
#include <stdio.h>
#include <stdbool.h>

// DECLARATIONS
bool running = true;
int ip = 0; // instruction pointer
int sp = -1; // stack pointer
int stack[256];

// DATA
typedef enum{
	PSH,
	ADD,
	POP,
	SET,
	HLT
} InstructionSet;

const int program[] = {
	PSH, 5,
	PSH, 6,
	ADD,
	POP,
HLT};

typedef enum{
	A, B, C, D, E, F,
	NUM_OF_REGISTERS
} Registers;

// FUNCTIONS
int fetch(){
	return program[ip];
}

void eval (int instr){
	switch (instr){
		case HLT: {
			running = false;
			break;
		}
		case PSH: {
			sp++;
			stack[sp] = program[++ip];
			break;
		}
		case POP: {
			int val_popped = stack[sp--];
			printf("popped %d\n", val_popped);
			break;
		}
		case ADD: {
			int a = stack[sp--];
			int b = stack[sp--];
			int result = b + a;
			sp++;
			stack[sp] = result;
			break;
		}
	}
}

// MAIN
int main(){
	while(running){
		eval(fetch());
		ip++; // increment the ip 
	}
}
