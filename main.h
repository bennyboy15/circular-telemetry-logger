#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

// PACKET
#pragma pack(push, 1) // Forces compiler to not add padding and keep this struct to smallest size possible!
typedef struct {
    uint64_t timestamp_ms; // 8 bytes
    uint32_t packet_id;    // 4 bytes
    float latitude;        // 4 bytes
    float longitude;       // 4 bytes
    float altitude_m;      // 4 bytes
    float pitch;           // 4 bytes
    float roll;            // 4 bytes
    float yaw;             // 4 bytes
    uint8_t system_status; // 1 byte
} TelemetryPacket;
#pragma pack(pop)

// ATOMIC RING BUFFER
#define ATOMIC_BUFFER_SIZE 8
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