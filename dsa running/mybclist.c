#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mybclist.h"
#include "mybcstacks.h"

//list has two ptr : head pointing to first element ,tail pointing to last element of list
void init(list *l){
	l->head = l->tail = NULL;
	l->len = 0;
	l->dec = 0;
	l->sign = 1;
}
//inserting element 
void insert(list *l, int pos, int num){
	node *tmp, *p;
	int i;
	/* handle errors on position */	
	if(pos < 0 || pos > l->len)
		return;	
	/* create a new node */
	tmp = (node *)malloc(sizeof(node));	
	tmp->num = num;
	/* handle first node case separately */
	if(l->head == NULL) {
		tmp->next = NULL; 
		tmp->prev = NULL;
		l->head = l->tail = tmp;
		l->len++;
		return;		
	}
	/* link the new node on the list at appropriate position*/
	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	//appending at beginning	
	if(pos == 0) {
		tmp->next = l->head;
		l->head->prev = tmp;
		l->head = tmp;
		l->head->prev = NULL;
		l->len++;
		return;
	}
	//appending at ith position
	if(pos != l->len) {
		tmp->next = p->next;
		tmp->prev = p;
		p->next->prev = tmp;
		p->next = tmp;
		l->len++;
		return;
	}
	//appending at end
	if(pos == l->len) {
		p->next = tmp;
		l->tail = tmp;
		tmp->prev = p;	
		tmp->next = NULL;
		l->len++;
		return;
	}
}
//deleting element from the list
int remov(list *l, int pos){
	int i;
	int num;
	node *p, *tmp;
	/* handle errors on position */	
	if(pos < 0 || pos >= l->len)
		return 0;	
	
	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	//list is empty
	if(l->head == NULL) {
		return 0;
	}
	//deleting only element of list
	if(l->len == 1) {	
		num = p->num;
		l->head = l->tail = p = NULL;
		l->len--;
		return num;
	}
	//deleting first element
	if(pos == 0) {	
		num = p->num;
		p->next->prev = NULL;
		l->head = p->next;
		free(p);
		l->len--;
		return num;
	}
	//deleting last element
	if(pos == l->len - 1) {	
		num = p->next->num;
		tmp = p->next;
		p->next = NULL;
		l->tail = p;
		free(tmp);
		l->len--;
		return num;
	}
	
	tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;	
	num = tmp->num;
	free(tmp);
	l->len--;
	return num;
}
void traverse(list *l){
	node *p = l->head;
	int i = 0;
	int flag = 0, print = 0;
	int flag1 = 0;
	if(!p) {
		return;
	}
	do {
		if(l->sign == -1) {
			printf("-");
			l->sign = 1;
			flag = 1;
		}
		if(i == l->len - l->dec) {
			if(print != 1) {
				printf("0.");
			
				print = 1;
			}
		}
		i++;
		if(p->num != 0 || i > l->len - l->dec - 2) {
			flag1 = 1;
		}
		if(flag1 == 1)
			printf("%d", p->num);
		if( i == l->len - l->dec) {
			if(print != 1) {
				printf(".");
				print = 1;
			}
		}
		p = p->next;
	} while(p != NULL) ;
	if(flag == 1) {
		l->sign = -1;
		flag = 0;
	}
}
void append(list *l, int num) {
	insert(l, l->len, num);
}
int length(list *l) {
	return l->len;
}
int dec(list *l) {
	return l->dec;
}
//displaying element at particular position
int show(list *l, int pos) {
	node *p;
	if(pos <0 || pos > l->len) //position error
		return 0;
	p = l->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	return p->num;
}

