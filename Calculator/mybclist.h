#define PLUS 1
#define MINUS -1 
#include<math.h>
typedef struct node {
	int num;
	int flag;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len, dec, sign;
}list;
void init(list *l);
void insert(list *l, int pos, int num);
int remov(list *l, int pos);
void traverse(list *l);
void append(list *l, int num);
int length(list *l);
int dec(list *l);
int show(list *l, int pos);




