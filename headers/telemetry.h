// #ifndef TELEMETRY_H
// #define TELEMETRY_H
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  uint64_t timestamp_ms;
  uint32_t packet_id;
  float latitude;
  float longitude;
  float altitude_m;
  float pitch;
  float roll;
  float yaw;
  uint8_t system_status;
} TelemetryPacket;
#pragma pack(pop)

void generate_random_packet(TelemetryPacket *packet, uint32_t current_id);

// #endif