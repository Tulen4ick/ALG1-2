#include "Stack1.h"

void push1(float* stack, int* top, float value) {
	(*top)++;
	stack[*top] = value;
}

float pop1(float* stack, int* top) {
	(*top)--;
	return stack[*(top)+1];
}

float peek1(float* stack, int top) {
	return stack[top];
}


int size1(float* stack, int top) {
	return (top + 1);
}