#include "raom.h"

Err gen(Noun expr) {
	Noun p = null;

	if (null(expr)) { return done_e; }

	if (expr.type == int_t) {
		fprintf(outfile, "  push %ld\n", expr.integer);
		return done_e;
	}

	p = tail(expr);

	while (!null(p)) {
		gen(head(p));
		p = tail(p);
	}

	if (head(expr).type == symbolic_t) {
		fprintf(outfile, "  pop rdi\n");
		fprintf(outfile, "  pop rax\n");

		if (streq(head(expr).symbol, "+")) {
			fprintf(outfile, "  add rax, rdi\n");
		} else if (streq(head(expr).symbol, "-")) {
			fprintf(outfile, "  sub rax, rdi\n");
		} else if (streq(head(expr).symbol, "*")) {
			fprintf(outfile, "  imul rax, rdi\n");
		} else if (streq(head(expr).symbol, "/")) {
			fprintf(outfile, "  cqo\n");
			fprintf(outfile, "  idiv rdi\n");
		}
	}

	fprintf(outfile, "  push rax\n");

	return done_e;
}
