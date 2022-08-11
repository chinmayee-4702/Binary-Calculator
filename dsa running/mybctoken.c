#include "mybclist.h"
#include "mybctoken.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//enum states { SPC, DIG, OPR, VAR, STOP, ERR };
token *getnext(char *arr, int *reset) {
	static int currstate;
	int nextstate;
	static int i;
	static list *l;
	static int dec = 0;
	static int flag = 0;
	static int m = 0, num = 0, sign = 1;
	l = (list *)malloc(sizeof(list));
	init(l);
	
	if(m == 1) {
		append(l, num);
		m = 0;
	}	
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) { //this switch case determines the nextstate of arr[i]
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
			case '!': case '<': case '>': case '=':
			
				nextstate = OPR;
				break;
			
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {//this switch case determines the currentstate of arr[i]
			case SPC:
				if(nextstate == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(l,(arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}			
				break;
			case DIG:
				if(nextstate == DIG) {
					if(arr[i] == '.') { 
						flag = 1;
					}
					else {
						append(l, (arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}
				else  { 
					t->type = OPERAND;
					t->l = l;
					t->l->dec = dec;
					t->l->sign = sign; //storing values
					//setting values of sign , dec and flag to default.
					sign = 1; 
					dec = 0;
					flag = 0;
					currstate = nextstate;
					i++;
					return t; //returning the token
				}
				break;
			case OPR:
				if(arr[i - 2] == '(') {
					if(arr[i - 1] == '-') //checking whether number is negative or positive
						sign = -1;
					else
						sign = 1;
				}
					 
				if(sign != -1) {
					t->type = OPERATOR;
					t->op = arr[i - 1];
				}
				currstate = nextstate;
						
				if(nextstate == DIG) { 
					if(arr[i] == '.') {
						flag = 1; //marks presence od decimal
						dec = 0;
					}
					else {	
						m = 1;
						num = arr[i] - '0';
						if(flag == 1)
							dec++;
					}
				}
				i++;
				return t; //returning the token
			
			case STOP:
				t->type = END;
				currstate = nextstate;
				i++;
				return t; //returning the token
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				i++;
				return t; //returning the token
				break;
		}
		currstate = nextstate;
		i++;
	}
}



