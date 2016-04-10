/**
 * Copyright Jakub Staroń 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include "socket.h"
#include "err.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fatal("Usage: %s hostname port message\n", argv[0]);
  }

  String_pointer message = String_fromCString(argv[3]);

  TCPConnection_pointer connection = TCP_connect(argv[2], argv[1]);
  TCP_sendMessage(connection, message);
  String_pointer received = TCP_receiveMessage(connection);
  puts(String_toCstring(received));
  String_destroy(received);
  String_destroy(message);
  TCP_closeAndDestroyConnection(connection);

  return 0;
}

