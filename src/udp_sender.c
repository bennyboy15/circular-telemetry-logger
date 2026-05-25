#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Usage: %s <peer_ip> <peer_port> <message>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *peer_ip = argv[1];
  int peer_port = atoi(argv[2]); // stdlib/atois = converts string to integer
  const char *message = argv[3];

  struct sockaddr_in peer_adr = {
      .sin_family = AF_INET, // Socket Internet Family AF_INET = IPv4 address
                             // family, can use AF_INET6 for IPv6
      .sin_port =
          htons(peer_port) // Socket Internet Port htons = Host to Network Short
  };

  /*
    inet_pton (Internet Presentation to Network)
    standard C library function used to convert human-readable IP addresses
    (like "192.168.1.1" or "2001:db8::1") into their binary network byte-order
    representation
  */
  if (inet_pton(AF_INET, peer_ip, &(peer_adr.sin_addr)) <= 0) {
    perror("ERROR: Something wrong with IP address");
    return EXIT_FAILURE;
  }

  /* SOCK_DGRAM = fast & connectionless, just sending to an address & not
   * establishing a connection prior */
  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (udp_socket <= 0) {
    perror("ERROR: Failed to create socket");
    return EXIT_FAILURE;
  }

  if (sendto(udp_socket, message, strlen(message) + 1, 0,
             (struct sockaddr *)&peer_adr, sizeof(peer_adr)) <= 0) {
    perror("ERROR: Failed to send");
    close(udp_socket);
    return EXIT_FAILURE;
  }

  printf("Sent: \"%s\" to %s:%d\n", message, peer_ip, peer_port);
  close(udp_socket);

  return EXIT_SUCCESS;
}