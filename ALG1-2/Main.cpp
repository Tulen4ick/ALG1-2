#define _CRT_SECURE_NO_WARNINGS
#define IN 1
#define OUT 0
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "stack1.h"


int Prior(char a)
{
	switch (a)
	{
	case '*':
	case '/':
		return 3;
	case '-':
	case '+':
		return 2;
	case '(':
		return 1;
	default: return 10;
	}

}


int main() {
	setlocale(LC_ALL, "Rus");
	FILE* fpi;
	FILE* fpo = fopen("1-2out.txt", "w");
	if ((fpi = fopen("1-2in.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл");
		getchar();
		return 0;
	}
	char stack[30];
	float stack1[30];
	char rez[60];
	int top = -1;
	int top_rez = -1;
	char str[30];
	for (int i = 0; i < 60; ++i) {
		rez[i] = '\0';
	}
	fgets(str, 30, fpi);
	fprintf(fpo, "%s", "Введенное выражение: ");
	fprintf(fpo, "%s", str);
	fprintf(fpo, "\n");
	int state = OUT;
	for (int i = 0; str[i] != '\0'; ++i) {
		if ((str[i] == '(') || (str[i] == ')') || (str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/')) {
			if (state == IN) {
				top_rez += 1;
				rez[top_rez] = ' ';
			}
			state = OUT;
			if (str[i] == '(') {
				push(stack, &top, str[i]);
			}
			if (str[i] == ')') {
				while (stack[top] != '(') {
						top_rez += 1;
						rez[top_rez] = pop(stack, &top);
						top_rez += 1;
						rez[top_rez] = ' ';
				}
				top -= 1;
			}
			if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/')) {
				if (top == -1)
					push(stack, &top, str[i]);
				else {
					if (Prior(str[i]) > Prior(stack[top])) {
						push(stack, &top, str[i]);
					}
					else {
						char t = peek(stack, top);
						while ((Prior(str[i]) <= Prior(t)) && (is_empty(top) == 0)) {
							top_rez += 1;
							rez[top_rez] = pop(stack, &top);
							t = peek(stack, top);
							top_rez += 1;
							rez[top_rez] = ' ';
						}
						push(stack, &top, str[i]);
					}
				}
			}
		}
		else {
			state = IN;
			top_rez += 1;
			rez[top_rez] = str[i];
		}
	}
	if (state == IN){
		top_rez += 1;
		rez[top_rez] = ' ';
	}
	while (top != -1) {
		top_rez += 1;
		rez[top_rez] = pop(stack, &top);
		top_rez += 1;
		rez[top_rez] = ' ';
	}
	clear(&top);
	clear(&top_rez);
	for (int i = 0; i < 60; ++i) {
		fprintf(fpo, "%c", rez[i]);
	}
	fprintf(fpo, "\n");
	float temp;
	int i = 0;
	while(rez[i] != '\0') {
		if ((rez[i] == '+') || (rez[i] == '-') || (rez[i] == '*') || (rez[i] == '/')) {
			switch (rez[i]){
			case '*':
				temp = stack1[top_rez-1] * stack1[top_rez];
				break;
			case '/':
				temp = stack1[top_rez - 1] / stack1[top_rez];
				break;
			case '-':
				temp = stack1[top_rez - 1] - stack1[top_rez];
				break;
			case '+':
				temp = stack1[top_rez - 1] + stack1[top_rez];
				break;
			default: 
				printf("Неправильный символ.\n");
			}
			pop1(stack1, &top_rez);
			pop1(stack1, &top_rez);
			push1(stack1, &top_rez, temp);
			i++;
		}
		else {
			while(rez[i] != ' ') {
				push(stack, &top, rez[i]);
				i++;
			}
			clear(&top);
			push1(stack1, &top_rez, atof(stack));
			for (int j = 0; j < 30; ++j) {
				stack[j] = '\0';
			}
		}
		i++;
	}
	temp = stack1[top_rez];
	fprintf(fpo, "%s", "Результат вычисления выражения в постфиксной записи : ");
	fprintf(fpo, "%4.1f", temp);
	clear(&top_rez);
}