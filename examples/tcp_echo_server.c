/**
 * Copyright Jakub Staroń 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include "thread.h"
#include "socket.h"
#include "mutex_and_signal.h"
#include "err.h"


MutexAndSignal_pointer mutex_signal;
size_t pending_connections = 0;

void* HandleConnection(void* arg) {
  TCPConnection_pointer connection = (TCPConnection_pointer)arg;

  String_pointer message = TCP_receiveMessage(connection);
  TCP_sendMessage(connection, message);
  String_free(message);
  TCP_closeAndFreeConnection(connection);

  MutexAndSignal_lock(mutex_signal);
  pending_connections--;
  MutexAndSignal_signal(mutex_signal);
  MutexAndSignal_unlock(mutex_signal);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    fatal("Usage: %s port jobs simultaneous_connections \n", argv[0]);
  }

  mutex_signal = MutexAndSignal_create();
  short port = atoi(argv[1]);
  size_t jobs = atoi(argv[2]);
  size_t simultaneous_connections = atoi(argv[3]);

  TCPListener_pointer listener = TCP_listen(port);

  for (size_t i = 0 ; i < jobs ; i++) {
    /* Waits for finish of pending jobs. */
    MutexAndSignal_lock(mutex_signal);
    while (pending_connections > simultaneous_connections) {
      puts("Too many connections.. waiting...");
      MutexAndSignal_wait(mutex_signal);
    }
    MutexAndSignal_unlock(mutex_signal);

    TCPConnection_pointer connection = TCP_accept(listener);

    MutexAndSignal_lock(mutex_signal);
    pending_connections++;
    MutexAndSignal_unlock(mutex_signal);

    Thread_pointer thread = Thread_create(HandleConnection, connection, THREAD_DETACHED);
    Thread_free(thread);
  }

  /* Waits for all finish of all jobs. */
  MutexAndSignal_lock(mutex_signal);
  while (pending_connections > 0) {
    MutexAndSignal_wait(mutex_signal);
  }
  MutexAndSignal_unlock(mutex_signal);

  puts("Shutting down server...");

  TCP_closeAndFreeListener(listener);
  MutexAndSignal_free(mutex_signal);
  return 0;
}

