#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* outfile;

#define streq(a, b) ( !strcmp(a, b) )

typedef enum { done_e = 0, fail_e } Err;

typedef enum { null_t, int_t, tuple_t, symbolic_t } Type;

struct Noun {
	Type type;

	__extension__
	union {
		long int integer;
		const char* symbol;
		struct Tuple* tuple;
	};
};

struct Tuple { struct Noun n[2]; };

typedef struct Noun Noun;

#define head(p) ( (p).tuple->n[0] )
#define tail(p) ( (p).tuple->n[1] )
#define null(n) ( (n).type == null_t )

static const Noun null = { null_t };

Err gen(Noun expr);
Noun make_int(const long int x);
Noun make_symbolic(const char* s);
Noun make_tuple(Noun head, Noun tail);
Err read(const char* input, const char** end, Noun* result);
