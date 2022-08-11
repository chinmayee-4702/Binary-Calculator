#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mybclist.h"
#include "mybcbignum.h"
#include "mybcstacks.h"
#include<math.h>
//copying elements of list 1 to list2 
void copy(list *l1, list *l2) {
	int dec, i, num, sign;
	init(l2);
	for(i = 0; i < l1->len; i++) {
		//fetching element of l1
		num = show(l1, i);
		append(l2, num);//appending at end
	}
	dec = l1->dec;
	l2->dec = dec;
	sign = l1->sign;
	l2->sign = sign; //assigning it sign same as l1
	return;
}

int checkzero(list *l) {
	int e, flag = 0;
	for(e = 0; e < l->len; e++) {
		if(show(l, e) != 0)
			flag = 1;
	}
	return flag;	
}
/*
int compare(list *l1, list *l2);
list *subnum(list *l1, list *l2);
int *division(list *temp, list *l1);
*/

list *addnum(list *l1, list *l2) {
	list *result;
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	result = (list *)malloc(sizeof(list));
	init(result);
	//eqaulizing length after decimal
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	//handling sign
	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subnum(l2, l1);
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subnum(l1, l2);
		}
	}
	
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = length(l1);
		j = length(l2);
		int carry = 0;
		while(i != 0 || j != 0) {
			if(i == 0) { //if len(l1) == 0
				num = show(l2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else if(j == 0) { //if len(l2) == 0
				num = show(l1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else {
				num = show(l1, i - 1) + show(l2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0 , num);
			}
		}
		result->dec = dec(l1);
		if(carry != 0)
			insert(result, 0, carry);
	}
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}

list *subnum(list *l1, list *l2) {
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	/*Make no of digits after decimal equal*/
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int num;
	static int flag = 0;
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	//handling the signs
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			//if numbers are a,-b
			result = addnum(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			///if numbers are -a,b
			result = addnum(l1, l2);
			result->sign = -1;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			//numbers are -a,-b
			result = subnum(l2, l1);
		}
		if(l1->sign == 1) {
		        //numbers are a,b
			if(compare(l1, l2) >= 0) {
				if(flag != 1)
					//a > b
					result->sign = 1;
				else
					//b > a
					result->sign = -1;
				int b = 0;
				int m,n;
				m = length(l1) - 1;
				n = length(l2) - 1; 
				while(m != -1 || n != -1) {
						if(n == -1) {
						num = show(l1, m);m--;
						insert(result, 0, num);
						}
						else {
						int a = show(l1, m);m--;
						int c = show(l2, n);n--;
						if(a >= c) {
							num = a - c;
							insert(result, 0, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert(l1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert(l1, m, 9);
							}
							num = 10 + a - c;
							insert(result, 0, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				flag = 1;
				result = subnum(l2, l1);
				result->sign = -1;
			}
		}
	}
	result->dec = l1->dec;
	flag = 0;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}   



list *mulnum(list *l1, list *l2) {
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	int tempsign, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(checkzero(l1) == 0)
		return l1;
	if(checkzero(l2) == 0)
		return l2;
	//handling signs	
	if(l1->sign == l2->sign) {
		tempsign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		tempsign = -1;
		l1->sign = l2->sign = 1;
	}
	int x = length(l1) - length(l2);
	//abc*abcd
	if(x < 0) {
		result = mulnum(l2, l1);
		return result;
	}
	//abcd*abc
	else {
		int n = length(l2) - 1, j, i;
		int a = length(l2), b = length(l1);
		int arr[2 * b];
		for( i = 0; i < 2 * b; i++)
			arr[i] = 0;
		int num1 = 0, num2 = 0;
		int k = 2 * b - 1;
		for( i = 0; i < a; i++) {
			int m = length(l1) - 1;
			int carry1 = 0, carry2 = 0;
			for( j = k - i; j > b - 2; j--) {
				if(m != -1 && n != -1) {
					num1 = show(l1, m) * show(l2, n) + carry1;
					m--;
					carry1 = num1 / 10;
					num1 = num1 % 10;
					num2 = arr[j] + num1 + carry2;
					carry2 = num2 / 10;
					num2 = num2 % 10;
					arr[j] = num2;
				}
				else {
					break;
				}
			}
			arr[j] = carry1 + carry2 + arr[j];
			b--; n--;
		}
		j = 0;
		for( i = 2 * length(l1) - 1; i > b - 1 && i >= 0; i--) {
			insert(result, 0, arr[i]); j++;
		}
		result->dec = l1->dec + l2->dec;
		result->sign = tempsign;
		l1->sign = sign1;
		l2->sign = sign2;
		return result;
	}
}




list *division(list *l1, list *l2) {
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:dividing by zero");
		return NULL;
	}
	list *result;
	result = (list *)malloc(sizeof(list));
	list *temp;
	temp = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	//handling signs
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}
	
	int a, b;
	m = l1->dec - l2->dec;
	int i, j, k, num;
	//let the numbers be x ,y
	a = l1->dec; //storing no. of digits after decimal
	b = l2->dec;
	l1->dec = l2->dec = 0; //removing decimal points
	for(i = 0; i < length(l1); i++) { 
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l2) < 0) {//checks whether x < y
			append(result, 0);//if x < y append 0 at end in x and then divide
		}
		else {
			int d = 0;
			while(1) { //result before decimal point
				temp = subnum(temp, l2);
				d++; //d maintains the count of no. of times l2 is added to get l1 or number just less than l1
				if(compare(temp, l2) < 0)
					break;
					
			}
			append(result, d);
		}
	}
	j = 0; k = 0; //appending after decimal point
	while(j < 10) {
		append(temp, 0);
		int d = 0;
		while(compare(temp, l2) >= 0) {
			temp = subnum(temp, l2);
			d++;
		}
		append(result, d);
		k++;j++;
	}//answer upto 10 decimals
	result->dec = 10 + m;
	l1->dec = a;
	l2->dec = b;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}


list *modulus(list *l1, list *l2) {
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:modulo by zero");
		return NULL;
	}
	list *result;
	result = (list *)malloc(sizeof(list));
	list *temp;
	temp = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	list *l3;
	l3 = (list *)malloc(sizeof(list));
	init(l3);
	copy(l2, l3);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	//sign handling
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}
	
	int a, b;
	m = length(l1);
	int i, j, num;
	
	a = dec(l1);
	b = dec(l2);
	if(dec(l1) != 0) {
		l1->len = l1->len - dec(l1);
	}
	if(l3->dec != 0) {
		i = dec(l3);
		for(j = 0; j < i; j++) {
			remov(l3, l3->len);
		}
	}
	for(i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l3) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subnum(temp, l3);
				d++;
				if(compare(temp, l3) < 0)
					break;
					
			}
			append(result, d);
		}
	}
	l1->len = m;
	l1->sign = sign1;
	l2->sign = sign2;
	l1->dec = a;
	l2->dec = b;
	return temp;
}

	
	
int compare(list *l1, list *l2) {
	if(l1->sign == 1 && l2->sign == -1)
		return 1; //l1 is greater
	if(l2->sign == 1 && l1->sign == -1)
		return -1; // l2 is greater
	/*Make no. of digits after decimal equal*/
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	//making length equal
	int a = (length(l1) - length(l2));
	if(a > 0) {
		int i = 0;
		while(i < a) {
			insert(l2, 0, 0);
			i++;
		}
	}
	else if(a < 0) {
		int i = 0;
		a = -a;
		while(i < a) {
			insert(l1, 0, 0);
			i++;
		}
	}	
	
		int i;
		for(i = 1; i <= length(l1); i++) {
			if(show(l1, i - 1) > show(l2, i - 1))
				return 1;
			else if(show(l1, i - 1) < show(l2, i - 1))
				return -1;
		}
		return 0;
}

list *power(list *l1, list *l2) {
	list *result = (list *)malloc(sizeof(list));
	init(result);
	append(result, 1);
	list *c1 = (list *)malloc(sizeof(list));
	init(c1);
	append(c1, 1);
	list *l3 = (list *)malloc(sizeof(list));
	init(l3);
	list *c2 = (list *)malloc(sizeof(list));
	init(c2);
	list *c0 = (list *)malloc(sizeof(list));
	init(c0);
	int sign = l1->sign;
	append(c2, 2);
	append(c0, 0);
	copy(l2, l3);
	if(l2->sign == 1) {
		while(checkzero(l3) != 0) {
			result = mulnum(result, l1);
			l3 = subnum(l3, c1);//reducing power by 1
		}
	}
	else if(l2->sign == -1) {
		while(checkzero(l3) != 0) {
			result = division(result, l1);
			l3 = addnum(l3, c1);//reducing power by 1
		}
	}
	l1->sign = sign;
	if(l1->sign == -1) {
		if(compare(modulus(l2, c2), c0) == 0) //checking whether l2 is even or odd
			result->sign = 1; //if even
		else{
			result->sign = -1; //if odd 
	}
	return result; 
	
} 

list *factorial(list *l1, list *l2) {
	list *result = (list *)malloc(sizeof(list));
	init(result);
	append(result, 1);
	while(compare(l1, l2) > 0) {
		result = mulnum(l1, result);
		l1 = subnum(l1, l2);
	}
	return result;		 
	
}


