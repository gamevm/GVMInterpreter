/*
 * main.cpp
 *
 *  Created on: Mar 28, 2011
 *      Author: hw
 */

#include "memory.hpp"
#include <cstdio>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

struct Instruction {
	u16 opCode;
	u16 argument;
};

gvm::StackMemory<1024> memory;
gvm::Stack<int, 256> intRegisters;

void* variables[256];

const u16 OP_ILOAD = 0;
const u16 OP_ISTORE = 1;
const u16 OP_IADD = 2;

void printOpStack() {
	for (int i = 0; i < intRegisters.size(); i++) {
		printf("%d ", intRegisters.get(i));
	}
	printf("\n");
}

void executeCommand(Instruction pc) {
	printf("Executing op=%d, arg=%d\n", pc.opCode, pc.argument);

	register int* addr;

	switch (pc.opCode) {
	case OP_ILOAD:
		addr = reinterpret_cast<int*>(variables[pc.argument]);
		intRegisters.push(*addr);
		break;
	case OP_ISTORE:
		addr = reinterpret_cast<int*>(variables[pc.argument]);
		*addr = intRegisters.pop();
		break;
	case OP_IADD:
		intRegisters.push(intRegisters.pop() + intRegisters.pop());
		break;
	}
	printOpStack();

}

int main(int argc, char** argv) {

	int x = 5;
	int y = 10;
	int z = 0;

	variables[0] = &x;
	variables[1] = &y;
	variables[2] = &z;

	Instruction i1; // load x on the stack
	i1.opCode = OP_ILOAD;
	i1.argument = 0;


	Instruction i2; // load y on the stack
	i2.opCode = OP_ILOAD;
	i2.argument = 1;

	Instruction i3; // push x + y on the stack
	i3.opCode = OP_IADD;

	Instruction i4; // load y on the stack
	i4.opCode = OP_ISTORE;
	i4.argument = 2;

	executeCommand(i1);
	executeCommand(i2);
	executeCommand(i3);
	executeCommand(i4);

//	Instruction program[4];
//	program[0] = i1;
//	program[1] = i2;
//	program[2] = i3;
//	program[3] = i4;
//
//	for (int i = 0; i < 4; i++) {
//		executeCommand(program[i]);
//	}

	printf("%d\n", z);

	return 0;
}
