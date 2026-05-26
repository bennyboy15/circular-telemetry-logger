#include "udp_receiver.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// INITIALISES A SOCKET TO LISTEN @ SPECIFIED PORT
int init_udp_receiver(int port) {

  int new_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (new_socket < 0) {
    perror("ERROR: Could not create receiver socket");
    return -1;
  }

  struct sockaddr_in my_addr = {.sin_family = AF_INET,
                                .sin_addr.s_addr = INADDR_ANY,
                                .sin_port = htons(port)};

  if (bind(new_socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
    perror("ERROR: Could not bind socket to port");
    close(new_socket);
    return -1;
  }

  return new_socket;
}

//
int receive_telemetry_packet(int socket_fd, TelemetryPacket *packet,
                             struct sockaddr_in *sender_addr) {

  socklen_t addr_len = sizeof(struct sockaddr_in);

  ssize_t bytes_received =
      recvfrom(socket_fd, packet, sizeof(TelemetryPacket), 0,
               (struct sockaddr *)sender_addr, &addr_len);

  if (bytes_received < 0) {
    perror("ERROR: Network read failure");
    return -1;
  }

  if (bytes_received != sizeof(TelemetryPacket)) {
    printf("WARNING: Fragmented packet dropped! Received %zd bytes, expected "
           "%zd.\n",
           bytes_received, sizeof(TelemetryPacket));
    return 0;
  }

  return 1;
}