CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

all:
	mkdir -p apps
	$(CC) $(CFLAGS) src/telemetry.c src/udp_sender.c -o apps/transmitter
	$(CC) $(CFLAGS) src/main.c src/udp_receiver.c -o apps/receiver

clean:
	rm -rf apps