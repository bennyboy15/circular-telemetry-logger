// #ifndef UDP_SENDER_H
// #define UDP_SENDER_H
#pragma once

#include "telemetry.h"
#include <netinet/in.h>

int send_telemetry_packet(int socket_fd, const struct sockaddr_in *dest_addr,
                          const TelemetryPacket *packet);

// #endif