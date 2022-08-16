#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mybcstacks.h"
#include "mybclist.h"
/*******************************stack.c**************************************/
void push(stack *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}
list *pop(stack *s) {
	list *t = (list *)malloc(sizeof(list)); 
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int empty(stack *s) {
	return s->i == 0;
}
int full(stack *s) {
	return s->i == MAX;
}
void sinit(stack *s) {
	s->i = 0;
}





/*******************************stack1.c**************************************/
void push1(stack1 *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}
list *pop1(stack1 *s) {
	list *t = (list *)malloc(sizeof(list)); 
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int empty1(stack1 *s) {
	return s->i == 0;
}
int full1(stack1 *s) {
	return s->i == MAX;
}
void sinit1(stack1 *s) {
	s->i = 0;
}




/**********************************cstack.c**************************************/
//this stack stores operators
void cpush(cstack *s, char num) {
	s->a[s->i]= num;
	(s->i)++;
}
char cpop(cstack *s) {
	char t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int cempty(cstack *s) {
	return s->i == 0;
}
int cfull(cstack *s) {
	return s->i == MAX;
}
void cinit(cstack *s) {
	s->i = 0;
}

