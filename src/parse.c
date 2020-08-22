#include "raom.h"

Err lex(const char* string, const char** start, const char** end) {
	string += strspn(string, " \t\n");

	if (string[0] == '\0') {
		*start = *end = NULL;
		return fail_e;
	}

	*start = string;

	if (strchr("()", string[0]) != NULL) {
		*end = string + 1;
	} else {
		*end = string + strcspn(string, "() \t\n");
	}

	return done_e;
}

Err parse(const char* start, const char* end, Noun* result) {
	char *buf, *p;

	long int val = strtol(start, &p, 10);
	if (p == end) {
		result->type = int_t;
		result->integer = val;
		return done_e;
	}

	buf = malloc(end - start + 1);
	p = buf;

	while (start != end) { *p++ = *start, ++start; }

	*p = '\0';

	if (streq(buf, "null")) {
		*result = null;
	} else {
		*result = make_symbolic(buf);
	}

	free(buf);
	return done_e;
}

Err list(const char* start, const char** end, Noun* result) {
	Noun p;

	*end = start;
	p = *result = null;

	for (;;) {
		const char* token;
		Noun item;
		Err err;

		err = lex(*end, &token, end);
		if (err) { return err; }

		if (token[0] == ')') { return done_e; }

		err = read(token, end, &item);

		if (err) { return err; }

		if (null(p)) {
			*result = make_tuple(item, null);
			p = *result;
		} else {
			tail(p) = make_tuple(item, null);
			p = tail(p);
		}
	}
}

Err read(const char* input, const char** end, Noun* result) {
	const char* token;
	Err err;

	err = lex(input, &token, end);
	if (err) { return err; }

	if (token[0] == '(') {
		return list(*end, end, result);
	} else if (token[0] == ')') {
		return fail_e;
	} else {
		return parse(token, *end, result);
	}
}
