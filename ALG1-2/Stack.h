#pragma once
void push(char* stack, int* top, char value);
char pop(char* stack, int* top);
char peek(char* stack, int top);
int is_empty(int top);
int is_full(int top);
void clear(int* top);
int size(char* stack, int top);