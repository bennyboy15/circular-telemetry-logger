// src/udp_receiver_main.c
#include "telemetry.h"
#include "udp_receiver.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 5000

int main() {
  TelemetryPacket rx_packet;
  struct sockaddr_in sender_info;

  int rx_socket = init_udp_receiver(PORT);
  if (rx_socket < 0) {
    return 1;
  }

  printf("Receiver online! Waiting for incoming telemetry on port %d...\n",
         PORT);

  while (1) {
    int status = receive_telemetry_packet(rx_socket, &rx_packet, &sender_info);

    if (status > 0) {

      printf("----------------------------------------\n");
      printf("CAPTURED PACKET #%u from %s:%d\n", rx_packet.packet_id,
             inet_ntoa(sender_info.sin_addr), ntohs(sender_info.sin_port));
      printf("  Timestamp: %lu ms\n", rx_packet.timestamp_ms);
      printf("  Altitude : %.2f m\n", rx_packet.altitude_m);
      printf("  GPS Coord: Lat %.4f, Lon %.4f\n", rx_packet.latitude,
             rx_packet.longitude);
      printf("  Attitude : Pitch %.1f, Roll %.1f, Yaw %.1f\n", rx_packet.pitch,
             rx_packet.roll, rx_packet.yaw);
      printf("  Sys State: 0x%02X\n", rx_packet.system_status);
    }
  }

  close(rx_socket);
  return 0;
}