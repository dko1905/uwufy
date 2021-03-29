#define _POSIX_C_SOURCE 200112L // POSIX.1-2001

#include <stdio.h> /* IO */
#include <sys/types.h> /* ssize_t */
#include <stdint.h> /* other int types */
#include <ctype.h> /* isalpha */

#include "stack.h"

#ifndef VERSION
#define VERSION "Something went wrong with VERSION"
#endif

#define BUFFER_SIZE BUFSIZ
#define EMOJI "<_-_> "
#define EMOJI_LEN (sizeof(EMOJI)/sizeof(EMOJI[0]))

int cnv_ascii(FILE *in, FILE *out);

int main(int argc, char *argv[]){
	FILE *in = stdin;
	FILE *out = stdout;

	snew((1 << 4));
	return cnv_ascii(in, out);
}

int cnv_ascii(FILE *in, FILE *out) {
	ssize_t ret = 0;
	size_t n = 0, i = 0;
	uint8_t buffer[BUFFER_SIZE];
	const size_t buffer_size = BUFFER_SIZE;
	int word_state = 0; /* 0 - start sentence, 1 - normal */
	int strtr_state = 1; /* 0 - strtr, 0+ - no strtr */
	int emoji_state = 1; /* 0 - add, 0+ - don't add */

	while ((ret = fread(buffer, 1, buffer_size, in)) > 0) {
		sclear();
		for (n = 0; n < ret; ++n) {
			/* Is char from alphabet */
			if (isalpha(buffer[n])) {
				/* Everything must be lowercase. */
				buffer[n] = tolower(buffer[n]);
				/* Replace some chars. */
				if (buffer[n] == 'l' || buffer[n] == 'r') {
					if (buffer[n] == 'l' && sptr()[sptr_size() - 1] == 'w') {
						buffer[n] = '\0';
					} else {
						buffer[n] = 'w';
					}
				} else if (buffer[n] == 'a' && sptr()[sptr_size() - 1] == 'n') {
					spush('y');
				}
				/* If we are at the start of a sentence. */
				if (word_state == 0) {
					/* Draw emoji after punctuation. */
					if (emoji_state == 0) {
						/* Draw it. */
						for (i = 0; i < EMOJI_LEN - 1; ++i) {
							spush(EMOJI[i]);
						}
						++emoji_state;
					} else {
						/* This controls how often emojis are displayed. */
						if (emoji_state++ >= 3) {
							emoji_state = 0;
						}
					}
					/* Stuttering control. */
					if (strtr_state == 0) {
						spush(buffer[n]);
						spush('-');
						++strtr_state;
					} else {
						/* This controls how often we stutter. */
						if (++strtr_state == 3) {
							strtr_state = 0;
						}
					}
					/* We are no longer at the start of a sentence. */
					word_state = 1;
				}
			} else if (word_state == 1) {
				/* If punctuation set state to start of sentence. */
				if (buffer[n] == (uint8_t)'.') {
					word_state = 0;
				}
			}
			if (buffer[n] != '\0')
				spush(buffer[n]);
		}
		fwrite(sptr(), sptr_size(), 1, out);
	}

	return ret;
}
