#include "die.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void die(const char *msg) {
	fprintf(stderr, "die: %s: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}
