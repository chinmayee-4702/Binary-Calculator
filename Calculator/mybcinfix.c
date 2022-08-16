#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mybcstacks.h"
#include "mybclist.h"
#include "mybcbignum.h"
#include "mybcinfix.h"
#include "mybctoken.h"
/*Precedence function returns the precedence of operand given as argument*/
int precedence(char op) {
	if(op == '*' || op == '/' || op == '%')
		return 3;
	if(op == '+' || op == '-')
		return 2;
	if(op == '(')
		return 1;
	return 0;
}

/*Readline reads the string input from user and stores it in an array */
int readline(char *arr, int len) {
	int k = 0;
	int ch;
	while((ch = getchar()) != '\n' && k < len - 1) {
		arr[k] = ch;
		k++;
	}
	arr[k] = '\0';
	return k;
}
/*Infix function solves the infix equation.
*It takes Input in form of tokens from getnext
*and stores operators in cstack and operands in stack
* '(' and ')' are considered as operands.
* When a closing bracket comes it pops the operands out and do the calculations. At a time it pops two operators out.  
*/ 

list *infix(char *str) {
	list *x, *y, *z, *w;
	x = (list *)malloc(sizeof(list));
	y = (list *)malloc(sizeof(list));
	z = (list *)malloc(sizeof(list));
	w = (list *)malloc(sizeof(list));
		init(x);
	init(y);
	init(z);
	init(w);
	int reset = 1, c, b;
	char op1, op2, ch;
	token *t;
	t = (token *)malloc(sizeof(token));
	cstack cs;
	stack a;
	stack1 e;
	sinit(&a);
	cinit(&cs);
	sinit1(&e);
	int flag = 0, setpow = 0, comparison = 0, ip = 0;
	int i = 0, k, varflag = 0, m, prepos, postfix = 0, decimal = 0, decimal1 = 0;
	i = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND){
			if(setpow == 1) {
				x = pop(&a);
				if(dec(t->l) != 0)
					return NULL;
				y = power(x, t->l);
				setpow = 0;
				push(&a, y);
			}
			else {
				push(&a, t->l);
			}
		}
		else if(t->type == OPERATOR) {
			switch(t->op) {
				case '+': case '/': case '*': case '-': case '%':
					cpush(&cs, t->op);
					break;
				case '(':
					cpush(&cs, t->op);
					flag++; //counting no. of '('
					break;
				case '^':
					setpow = 1;
					break;
				
				case '!':
					x = pop(&a);
					append(w, 1);
					if(dec(x) != 0 || x->sign == -1)
						return NULL;
					else {	
						push(&a, factorial(x, w));
					}
					remov(w, 0);//emptyfying list w for further use
					break;
				
				
				case ')':
								 
					flag--;
					if(flag < 0)
						return NULL; //error in equation,unbalanced eqaution
					while(1) {
						if(!cempty(&cs)) {
							op1 = cpop(&cs);
							if(op1 == '(') {
								break;
							}						
						}
						else
							break;
						if(!cempty(&cs)) 
							op2 = cpop(&cs);
						c = precedence(op1);
						b = precedence(op2);
						if(c > b) {
							if(!empty(&a)) 
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							switch(op1) {
								case '+':
									push(&a, addnum(y, z));
									break;
								case '-':
									push(&a, subnum(y, z));
									break;
								case '/':
									push(&a, division(y, z));
									break;
								case '*':
									push(&a, mulnum(y, z));
									break;
								case '%':
									push(&a, modulus(y,z));
									break;
							}
							if(op2 != '(') {
								if(!empty(&a))
									z = pop(&a);
								else
									return NULL;
								if(!empty(&a))
									y = pop(&a);
								else
									return NULL;
								switch(op2) {
									case '+':
										push(&a, addnum(y, z));
										break;
									case '-':
										push(&a, subnum(y, z));
										break;
									case '/':
										push(&a, division(y, z));
										break;
									case '*':
										push(&a, mulnum(y, z));
										break;
									case '%':
										push(&a, modulus(y,z));
										break;
								}
							}
						}
						else if(c <= b) {
							if(!empty(&a))
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								x = pop(&a);
							else
								return NULL;
							switch(op2) {
								case '+':
									x = addnum(x, y);
									break;
								case '-':
									x = subnum(x, y);
									break;
								case '/':
									x = division(x, y);
									break;
								case '*':
									x = mulnum(x, y);
									break;
								case '%':
									x = modulus(x, y);
									break;	
							}
							switch(op1) {
								case '+':
									push(&a, addnum(x, z));
									break;
								case '-':
									push(&a, subnum(x, z));
									break;
								case '/':
									push(&a, division(x, z));
									break;
								case '*':
									push(&a, mulnum(x, z));
									break;
								case '%':
									push(&a, modulus(x,z));
									break;
							}
						}
					}
					break;	
				default:
					printf("default");
					return NULL;
					break;
			}
		}			
		else if(t->type == END) {
			while(!empty(&a)) {
				x = pop(&a);
				push1(&e, x);
				
			}
			char op[100];
			i = 0;
			while(!cempty(&cs)) {
				op[i] = cpop(&cs);
				i++;
			}
			int j = 0;
			while(j < i) {
				cpush(&cs, op[j]);
				j++;
			}
						
			while(1) { 
				if(flag != 0)//whether it is balanced or not
					return NULL;
				if(!cempty(&cs)) {
					op1 = cpop(&cs);
				}
				else {
					break;
				}
				if(!cempty(&cs))
					op2 = cpop(&cs);
				else {	
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push1(&e, addnum(z, y));
							break;
						case '-':
							push1(&e, subnum(z, y));
							break;
						case '/':
							push1(&e, division(z, y));
							break;
						case '*':
							push1(&e, mulnum(z, y));
							break;
						case '%':
							push1(&e, modulus(z,y));
							break;
					}
					break;
				}
				c = precedence(op1);
				b = precedence(op2);
				if(c >= b) {
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push1(&e, addnum(z, y));
							break;
						case '-':
							push1(&e, subnum(z, y));
							break;
						case '/':
							push1(&e, division(z, y));
							break;
						case '*':
							push1(&e, mulnum(z, y));
							break;
						case '%':
							push1(&e, modulus(z, y));
							break;
					}
					cpush(&cs, op2);
				}
				else if(c < b) {
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e))
						x = pop1(&e);
					else
						return NULL;
					switch(op2) {
						case '+':
							push1(&e, addnum(y, x));
							break;
						case '-':
							push1(&e, subnum(y, x));
							break;
						case '/':
							push1(&e, division(y, x));
							break;
						case '*':
							push1(&e, mulnum(y, x));
							break;
						case '%':
							push1(&e, modulus(y, x));
							break;		
					}
					push1(&e, z);
					cpush(&cs, op1);
				}		
			}
			
			
				
				
				if(empty1(&e) && cempty(&cs)) {
					x = NULL;
					z = NULL;
					w = NULL;
					free(x);
					free(z);
					free(w);
					return (y);
					
				}
				else if(setpow == 1) {
					if(!empty1(&e))
						x = pop1(&e);
					else
						return NULL;
					if(x->dec != 0)
						return NULL;
					z = power(y, x);
					setpow = 0;
					x = NULL;
					y = NULL;
					w = NULL;
					free(x);
					free(y);
					free(w);
					return z;
				}
				else {
					x = NULL;
					y = NULL;
					w = NULL;
					z = NULL;
					free(x);
					free(y);
					free(w);
					free(z);
					return NULL;	
				}	
			}
			else {
				
				x = NULL;
				y = NULL;
				w = NULL;
				z = NULL;
				free(x);
				free(y);
				free(w);
				free(z);
				return NULL;
			}
			
		}
		else if(t->type == ERROR) {
			printf("error");
			x = NULL;
			y = NULL;
			z = NULL;
			w = NULL;
			free(x);
			free(y);
			free(z);
			free(w);
			return NULL;
		}
		return NULL;	
		 	
	}
	
				

