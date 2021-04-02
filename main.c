#define _POSIX_C_SOURCE 200112L // POSIX.1-2001

#include <stdio.h> /* IO */
#include <stdlib.h> /* rand */
#include <sys/types.h> /* ssize_t */
#include <stdint.h> /* other int types */
#include <ctype.h> /* tolower */
#include <string.h> /* memcpy */

#ifndef VERSION
#define VERSION "Something went wrong with VERSION"
#endif

#define BUFFER_SIZE BUFSIZ
/* This controls how often emojis are displayed. */
#define EMOJI_BALANCE 1
#define STUTTER_BALANCE 2
/* This is the max len of the emoji strings. */
#define EMOJI_MAX_LEN 20
static uint8_t emojis[][EMOJI_MAX_LEN] = {
	"(ʘωʘ) ",
	"( °꒳° ) ",
	"(„ᵕᴗᵕ„) ",
	"(U ﹏ U) "
};
static size_t emojis_len = (sizeof(emojis)/sizeof(emojis[0]));

/* Custom faster isalpha. */
static inline int fast_isalpha(int c) {
    return ((unsigned int)(c | 32) - 97) < 26U;
}

int cnv_ascii(FILE *in, FILE *out);

int main(int argc, char *argv[]){
	// FILE *in = fopen("./tests/test_10k.txt", "r");
	FILE *in = stdin;
	FILE *out = stdout;

	fprintf(stderr, "Version: %s\n", VERSION);

	return cnv_ascii(in, out);
}

#define WBUFFER_WRITE(_ADDED_CHAR) { \
	if (write_buffer_free >= buffer_size) { \
		fwrite(write_buffer, buffer_size, 1, out); \
		write_buffer_free = 0; \
	} \
	write_buffer[write_buffer_free++] = _ADDED_CHAR; \
}

int cnv_ascii(FILE *in, FILE *out) {
	/* Buffers */
	const size_t buffer_size = BUFFER_SIZE;
	uint8_t read_buffer[BUFFER_SIZE];
	uint8_t write_buffer[BUFFER_SIZE];
	size_t write_buffer_free = 0;
	/* Generic variables */
	ssize_t bytes_read = 0;
	size_t n = 0, m = 0;
	uint8_t cc = 0, lc = 0; /* Current char, last char. */
	/* State counters */
	int sentence_state = 1; /* 0 - at start of sentence, 1 - normal */
	int stutter_state = 1; /* 0 - stutter, 0+ - don't */
	int emoji_state = 1; /* 0 - draw random emoji, 0+ - don't */

	/* Master loop, loop through buffers. */
	while ((bytes_read = fread(read_buffer, 1, buffer_size, in)) > 0) {
		/* Loop through charectors. */
		for (n = 0; n < bytes_read; ++n) {
			cc = read_buffer[n];
			/* Is char from alphabet */
			if (fast_isalpha(cc)) {
				/* Everything must be lowercase. */
				cc = tolower(cc);
				/* Remove double 'l','r' and convert into 'w'. */
				if (cc == 'l') {
					if (lc == 'l') {
						cc = '\0';
					} else {
						cc = 'w';
					}
				} else if (cc == 'r') {
					if (lc == 'r') {
						cc = '\0';
					} else {
						cc = 'w';
					}
				}
				/* Add 'y' in between 'n' and 'a'. */
				if (lc == 'n' && cc == 'a') {
					WBUFFER_WRITE('y');
				}
			}
			/* Sentence state. */
			if (sentence_state == 1) {
				if (cc == ' ') {
					if (lc == '.' || lc == '!') {
						sentence_state = 0;
					}
				}
			} else {
				/* Draw emoji if state says so. */
				if (emoji_state == 0) {
					/* Get random emoji. */
					const int rand_i = rand() % emojis_len;
					const uint8_t *s = emojis[rand_i];
					/* Write and flush write buffer. */
					while (*s != 0) {
						WBUFFER_WRITE(*(s++));
					}
					emoji_state = 1;
				} else {
					if (emoji_state++ >= EMOJI_BALANCE) {
						emoji_state = 0;
					}
				}
				if (fast_isalpha(cc)) {
					/* Stutter logic. */
					if (stutter_state == 0) {
						WBUFFER_WRITE(cc);
						WBUFFER_WRITE('-');
						stutter_state = 1;
					} else {
						if (stutter_state++ >= STUTTER_BALANCE) {
							stutter_state = 0;
						}
					}
				}
				sentence_state = 1;
			}
			/* Write current char if it isn't `NULL`. */
			lc = read_buffer[n];
			if (cc != '\0') {
				WBUFFER_WRITE(cc);
			}
		}
	}
	if (write_buffer_free > 0) {
		fwrite(write_buffer, write_buffer_free, 1, out);
		write_buffer_free = 0;
	}

	return 0;
}
