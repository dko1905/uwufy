#include "stack.h"
#include "die.h"

#include <stdlib.h>
#include <stdio.h>

static uint8_t *stack_buffer = NULL;
static size_t stack_size = 0;
static size_t free_spot = 0;

void spush(uint8_t c) {
	if (stack_size < free_spot + 1) {
		stack_size *= 2;
		stack_buffer = realloc(stack_buffer, stack_size);
		if (stack_buffer == NULL) {
			die("Failed to reallocate stack");
		}
	}
	stack_buffer[free_spot++] = c;
}

uint8_t spop() {
	if (free_spot > 0) {
		return stack_buffer[--free_spot];
	} else {
		return '\0';
	}
}

uint8_t speek() {
	if (free_spot > 0) {
		return stack_buffer[free_spot - 1];
	} else {
		return '\0';
	}
}

uint8_t *sptr() {
	return stack_buffer;
}

size_t sptr_size() {
	return free_spot;
}

void sclear() {
	free_spot = 0;
}

void snew(size_t initial_size) {
	stack_size = initial_size;
	stack_buffer = malloc(initial_size);
	if (stack_buffer == NULL) {
		die("Failed to allocate stack buffer");
	}
}

void sfree() {
	if (stack_buffer != NULL) {
		free(stack_buffer);
		stack_buffer = NULL;
		stack_size = 0;
	}
}
