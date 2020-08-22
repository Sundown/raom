#include "raom.h"

char* rl(const char* prompt) {
  char ret[256];
  printf("%s", prompt);
  fgets(ret, sizeof(ret), stdin);

  if (feof(stdin)) { return NULL; }

  return (char*)strdup(ret);
}

int main(int argc, char** argv) {
	char* input;

	if (argc != 2) {
		printf("USAGE:\n    raom [OUTFILE]\n");
		return 1;
	}

	outfile = fopen(argv[1], "w");

	if (outfile == NULL) {
		printf("Couldn't open file '%s' for writing\n", argv[1]);
		return 1;
	}

	while ((input = rl("| ")) != NULL) {
		const char* p = input;
		Err err;
		Noun expr;

		fprintf(outfile, ".intel_syntax noprefix\n");
		fprintf(outfile, ".globl _main\n");
		fprintf(outfile, "_main:\n");

		err = read(p, &p, &expr);

		if (!err) {
			err = gen(expr);
		}

		switch (err) {
			case done_e:
				fprintf(outfile, "  pop rax\n");
				fprintf(outfile, "  ret\n");
				fprintf(outfile, "\n");
				printf("Doned and didded, check ./%s\n", argv[1]);
				exit(0);
				break;
			case fail_e:
				puts("Syntax error");
				break;
		}

		free(input);
	}

	return 0;
}
