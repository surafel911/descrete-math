#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct set {
	int* elements;
	size_t len;
};

static int
strcount(const char* expr, const char* tok)
{
	int count = 0;
	size_t len = strlen(tok);

	while (*expr != '\0') {
		for (int i = 0; i < len; i++) {
			if (*expr == tok[i]) {
				count++;
				break;
			}
		}

		expr++;
	}

	return count;
}

static void
set_setup(struct set* set, const char* expr)
{
	const char* tok;

	set->len = strcount(expr, ", ") + 1;
	set->elements = malloc(sizeof(*set->elements) * set->len);

	tok = strtok((char*)expr, ", ");
	for (int i = 0; i < set->len && tok != NULL; i++) {
		sscanf(tok, "%d", set->elements + i);
		tok = strtok(NULL, ", ");
	}
}

static void
set_cleanup(struct set* set)
{
	free(set->elements);
}

static void
set_powerset(struct set* set, const char* id)
{
	printf("P(%s)\t={{}", id);

	for (int i = 0, count = pow(2, set->len); i < count; i++) {
		printf(",{");
		for (int j = 0; j < set->len; j++) {
			if (i & (1 << j)) {
				printf("%d", set->elements[j]);
			}
		}
		printf("}");
	}

	puts("");
}

static void
set_cartesian(struct set* a, struct set* b)
{
	printf("(AXB)\t= = {");

	for (int i = 0; i < a->len; i++) {
		for (int j = 0; j < b->len; j++) {
			printf("(%d,%d),", a->elements[i], b->elements[j]);
		}
	}

	puts("}");
}

static void
set_intersection(struct set* a, struct set* b)
{
	printf("AnB\t={");

	for (int i = 0; i < a->len; i++) {
		for (int j = 0; j < b->len; j++) {
			if (a->elements[i] == b->elements[j]) {
				printf("%d,", a->elements[i]);
			}
		}
	}

	puts("}");
}

static void
set_union(struct set* a, struct set* b)
{
	bool print;

	printf("AuB\t={");

	for (int i = 0; i < a->len; i++) {
		print = true;
		for (int j = 0; j < b->len; j++) {
			if (a->elements[i] == b->elements[j]) {
				print = false;
			}
		}

		if (print) {
			printf("%d,", a->elements[i]);
		}
	}
	
	for (int i = 0; i < b->len; i++) {
		printf("%d,", b->elements[i]);
	}

	puts("}");
}

static void
set_difference(struct set* a, struct set* b)
{
	bool print;

	printf("A-B\t={");

	for (int i = 0; i < a->len; i++) {
		print = true;
		for (int j = 0; j < b->len; j++) {
			if (a->elements[i] == b->elements[j]) {
				print = false;
			}
		}

		if (print) {
			printf("%d,", a->elements[i]);
		}
	}

	puts("}");

	printf("B-A\t={");

	for (int i = 0; i < b->len; i++) {
		print = true;
		for (int j = 0; j < a->len; j++) {
			if (b->elements[i] == a->elements[j]) {
				print = false;
			}
		}

		if (print) {
			printf("%d,", b->elements[i]);
		}
	}

	puts("}");

}

int
main(void)
{
	char s[512];
	struct set a, b;

	printf("Enter elements of A: ");
	fgets(s, sizeof(s), stdin);
	set_setup(&a, s);	

	printf("Enter elements of B: ");
	fgets(s, sizeof(s), stdin);
	set_setup(&b, s);	

	set_powerset(&a, "A");
	set_powerset(&b, "B");

	set_cartesian(&a, &b);

	set_intersection(&a, &b);

	set_union(&a, &b);

	set_difference(&a, &b);

	set_cleanup(&a);
	set_cleanup(&b);
}
