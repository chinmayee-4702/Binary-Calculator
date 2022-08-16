#include "mybclist.h"

/*******************************stack.h**********************************/
#define MAX 1024
typedef struct stack{
	int i;
	list *l[MAX];
	
}stack;
void push(stack *s, list *l);
list *pop(stack *s);
int empty(stack *s);
int full(stack *s);
void sinit(stack *s);


/*******************************stack1.h**********************************/
#define MAX 1024
typedef struct stack1{
	int i;
	list *l[MAX];
	
}stack1;
void push1(stack1 *s, list *l);
list *pop1(stack1 *s);
int empty1(stack1 *s);
int full1(stack1 *s);
void sinit1(stack1 *s);


/****************************cstack.h***************************************/
#define MAX 1024
typedef struct cstack{
	char a[MAX];
	int i;
}cstack;
void cpush(cstack *s, char num);
char cpop(cstack *s);
int cempty(cstack *s);
int cfull(cstack *s);
void cinit(cstack *s);



