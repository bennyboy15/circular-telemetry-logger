#include <stdint.h>

// PACKET
#pragma pack(push, 1) // Forces compiler to not add padding and keep this struct
                      // to smallest size possible!
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

// FUNCTIONS DEFINITIONS
float get_random_float(float min, float max);
void generate_random_packet(TelemetryPacket *packet, uint32_t current_id);