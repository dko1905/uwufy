#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdint.h>

void spush(uint8_t _c);
uint8_t spop();
uint8_t speek();
void sclear();
uint8_t *sptr();
size_t sptr_size();
void snew(size_t _initial_size);
void sfree();

#endif
