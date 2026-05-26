#include "telemetry.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int send_telemetry_packet(int socket_fd, const struct sockaddr_in *dest_addr,
                          const TelemetryPacket *packet) {

  size_t sent_bytes =
      sendto(socket_fd, packet, sizeof(TelemetryPacket), 0,
             (const struct sockaddr *)dest_addr, sizeof(struct sockaddr_in));

  if (sent_bytes <= 0) {
    perror("ERROR: Failed to send telemetry packet");
    return -1;
  }
  // printf("SUCCESS: Sent packet in UDP_SENDER!\n");
  return 1; // true (success!)
}