#include "Stack.h"

void push(char* stack, int* top, char value) {
	(*top)++;
	stack[*top] = value;
}

char pop(char* stack, int* top) {
	(*top)--;
	return stack[*(top)+1];
}

int is_empty(int top) {
	if (top < 0) {
		return 1;
	}
	return 0;
}

int is_full(int top) {
	if (top > 8) {
		return 1;
	}
	return 0;
}

char peek(char* stack, int top) {
	return stack[top];
}

void clear(int* top) {
	*top = -1;
}

int size(char* stack, int top) {
	return (top + 1);
}