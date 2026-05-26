#pragma once

#include <netinet/in.h>
#include "telemetry.h"

int init_udp_receiver(int port);
int receive_telemetry_packet(int socket_fd, TelemetryPacket *packet, struct sockaddr_in *sender_addr);

