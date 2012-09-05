/*
 * memory
 *
 *  Created on: Mar 28, 2011
 *      Author: hw
 */

#ifndef MEMORY_
#define MEMORY_

#include <string>

using std::string;

namespace gvm {

template <int SIZE>
class StackMemory {

public:

	StackMemory() {
		pos = &memory[0];
	}

	template <class T>
	T* push(int number = 1) {
		return reinterpret_cast<T*>(pos);
		pos += sizeof(T)*number;
	}

	template <class T>
	void pop(int number = 1) {
		pos -= sizeof(T)*number;
	}

private:

	unsigned char* pos;

	unsigned char memory[SIZE];

};

template <class T, int SIZE>
class Stack {

public:

	Stack() {
		pos = -1;
	}

	void push(T element) {
		array[++pos] = element;
	}

	T pop() {
		return array[pos--];
	}

	int size() {
		return pos+1;
	}

	const T& get(int index) {
		return array[index];
	}

private:

	int pos;

	T array[SIZE];

};

}


#endif /* MEMORY_ */
