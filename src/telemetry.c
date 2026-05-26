#include "telemetry.h"
#include "udp_sender.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

float get_random_float(float min, float max) {
  float scale =
      (float)rand() / (float)RAND_MAX; // Generates a number between 0.0 and 1.0
  return min + scale * (max - min);
}

// Fills a TelemetryPacket with random values
void generate_random_packet(TelemetryPacket *packet, uint32_t current_id) {

  // TIMESTAMP
  struct timespec ts;
  if (timespec_get(&ts, TIME_UTC)) {
    packet->timestamp_ms =
        (uint64_t)(ts.tv_sec * 1000) + (uint64_t)(ts.tv_nsec / 1000000);
  };

  // ID
  packet->packet_id = current_id;

  // DATA
  packet->latitude = get_random_float(-90.0f, 90.0f);
  packet->longitude = get_random_float(-180.0f, 180.0f);
  packet->altitude_m = get_random_float(100.0f, 5000.0f);
  packet->pitch = get_random_float(-45.0f, 45.0f);
  packet->roll = get_random_float(-45.0f, 45.0f);
  packet->yaw = get_random_float(0.0f, 360.0f);
  packet->system_status = (uint8_t)(rand() % 256);
}

int main() {

  uint32_t current_id = 1;
  TelemetryPacket tp;

  // UDP SETUP
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in peer_adr = {
      .sin_family = AF_INET, // Socket Internet Family AF_INET = IPv4 address
                             // family, can use AF_INET6 for IPv6
      .sin_port =
          htons(5000) // Socket Internet Port htons = Host to Network Short
  };
  inet_pton(AF_INET, "127.0.0.1", &(peer_adr.sin_addr));

  while (1) {
    // FILL PACKET WITH RANDOM DATA
    generate_random_packet(&tp, current_id);

    printf("SENDING PACKET: #%u | Alt: %.2fm | Lat: %.4f\n", tp.packet_id,
           tp.altitude_m, tp.latitude);

    // SEND UDP PACKET
    send_telemetry_packet(udp_socket, &peer_adr, &tp);
    current_id++;

    // PAUSE FOR 100 MILLISECONDS
    usleep(100000);
  }
  // CLOSE UDP SOCKET ONCE DONE WITH IT
  close(udp_socket);
  return 0;
}