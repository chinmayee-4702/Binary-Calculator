#include "mybcstacks.h"
#include "mybclist.h"
#include "mybcinfix.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define COUNT 2048
int main() {
	printf("Chinmayee Kulkarni\n");
	printf("112003074\n");
	
	char str[COUNT];	
	int x;
	list *ans;
	ans = (list *)malloc(sizeof(list));
	init(ans);
	while((x = readline(str, COUNT))) {
		ans = infix(str);
		if(ans == NULL) {
			printf("Erorr in expression\n");
		}  
		else {
			traverse(ans);
			printf("\n");
		}
	}
	return 0;
}

