#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

#define ATOMIC_BUFFER_SIZE 8

// ATOMIC RING BUFFER
typedef struct {
  char arr[ATOMIC_BUFFER_SIZE];
  atomic_size_t head;
  atomic_size_t tail;
} AtomicRingBuff;

AtomicRingBuff *initARB();
void resetARB(AtomicRingBuff *rb);
void freeARB(AtomicRingBuff *rb);
int spaceLeftARB(AtomicRingBuff *rb);
void writeARB(AtomicRingBuff *rb, char newChar);
char readARB(AtomicRingBuff *rb);