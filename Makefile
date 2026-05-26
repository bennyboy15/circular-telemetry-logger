CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

all:
	mkdir -p apps
	$(CC) $(CFLAGS) src/telemetry.c src/udp_sender.c -o apps/telemetry

clean:
	rm -rf apps