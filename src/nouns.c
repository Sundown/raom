#include "raom.h"

Noun make_tuple(Noun head, Noun tail) {
	Noun n;

	n.type = tuple_t;
	n.tuple = malloc(sizeof(struct Tuple));

	head(n) = head;
	tail(n) = tail;

	return n;
}

Noun make_int(const long int x) {
	Noun n;
	n.type = int_t;
	n.integer = x;
	return n;
}

Noun make_symbolic(const char* s) {
	Noun n;

	n.type = symbolic_t;
	n.symbol = strdup(s);

	return n;
}

void print(Noun n) {
	switch (n.type) {
		case null_t: {
			printf("null");
			break;
		} case tuple_t: {
			putchar('(');
			print(head(n));

			n = tail(n);
			while (!null(n)) {
				if (n.type == tuple_t) {
					putchar(' ');
					print(head(n));
					n = tail(n);
				} else {
					printf(" . ");
					print(n);
					break;
				}
			}

			putchar(')');
			break;
		} case symbolic_t: {
			printf("%s", n.symbol);
			break;
		} case int_t: {
			printf("%ld", n.integer);
			break;
		}
	}
}
