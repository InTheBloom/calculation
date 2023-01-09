#include <stdio.h>
#include <stdlib.h>

typedef struct number {
	char *a; // 数字
	int sign; // 符号
	int len; // 長さ
} number;

number *getnumber(long long int x) {
	number *num = (number *)malloc(sizeof(number));
	char *aa = (char *)malloc(20 * sizeof(char));
	for(int i = 0; 20 > i; aa[i++] = 0) {}

	for(int i = 0; x != 0; i++) {
		aa[i] = x % 10;
		x /= 10;
	}

	num->len = 1;
	for(int i = 19; i >= 0; i--) {
		if(aa[i] != 0) {
			num->len = i + 1;
			break;
		}
	}

	char *b = (char *)malloc(num->len * sizeof(char));
	for(int i = 0; num->len > i; i++) {
		b[i] = aa[i];
	}
	free(aa);
	aa = NULL;
	num->a = b;
	if(x < 0) {
		num->sign = 0;
	} else {
		num->sign = 1;
	}

	return num;
}

number *add(number *a, number *b) {
	int max, min;
	int flag = 0;
	if(a->len > b->len) {
		max = a->len;
		min = b->len;
		flag = 0;
	} else {
		max = b->len;
		min = a->len;
		flag = 1;
	}

	number *c = malloc(sizeof(number));
	char *e = (char *)malloc((max + 1) * sizeof(char));
	for(int i = 0; max + 1 > i; e[i++] = 0) {}

	int carry = 0; // 繰り上げ
	for(int i = 0; min > i; i++) {
		int temp = a->a[i] + b->a[i] + carry;
		if(temp > 9) {
			carry = temp / 10;
		} else {
			carry = 0;
		}
		temp %= 10;
		e[i] = temp;
	}

	if(flag == 0) {
		for(int i = min; max > i; i++) {
			int temp = a->a[i] + carry;
			if(temp > 9) {
				carry = temp / 10;
			} else {
				carry = 0;
			}
			temp %= 10;
			e[i] = temp;
		}
	} else {
		for(int i = min; max > i; i++) {
			int temp = b->a[i] + carry;
			if(temp > 9) {
				carry = temp / 10;
			} else {
				carry = 0;
			}
			temp %= 10;
			e[i] = temp;
		}
		e[max] = carry;
	}

	if(e[max] == 0) {
		char *aa = (char *)malloc(max * sizeof(char));
		for(int i = 0; max > i; i++) {
			aa[i] = e[i];
		}
		free(e);
		e = NULL;
		c->a = aa;
		c->len = max;
	} else {
		c->a = e;
		c->len = max + 1;
	}

	return c;
}

void freenum(number *a) {
	free(a->a);
	free(a);
}

void printnum(number *a) {
	for(int i = a->len - 1; i >= 0; i--) {
		printf("%i", a->a[i]);
	}
}

#define facto 5000

int main(void) {
	number *zero = getnumber(0);
	number *temp = NULL;
	number *a1 = getnumber(1);
	number *a2 = getnumber(1);

	for(int i = 1; facto > i; i++) {
		for(int j = 0; i > j; j++) {
			temp = add(a1, a2);
			freenum(a1);
			a1 = temp;
		}
		freenum(a2);
		a2 = add(a1, zero);
	}

	printnum(a1);
	printf("\n");

	return 0;
}
