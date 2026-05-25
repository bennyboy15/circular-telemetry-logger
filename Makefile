# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

# Rules
all:
	mkdir -p apps
	$(CC) $(CFLAGS) src/telemetry.c -o apps/telemetry

clean:
	rm -rf apps