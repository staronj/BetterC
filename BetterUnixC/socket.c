/**
 * Copyright Jakub Staroń 2016
 */

#include "socket.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "safe_memory_operations.h"
#include "err.h"


uint16_t host_to_network_short(uint16_t s) {
  return htons(s);
}

uint16_t network_to_host_short(uint16_t s) {
  return ntohs(s);
}

uint32_t host_to_network_long(uint32_t l) {
  return htonl(l);
}

uint32_t network_to_host_long(uint32_t l) {
  return ntohl(l);
}

struct UDPSocket {
  int socket;
};

UDPSocket_pointer UDPSocket_create(short port) {
  UDPSocket_pointer this = new(struct UDPSocket);
  this->socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->socket == -1)
    syserr("UDPListener_create - failed to create socket.");

  return this;
}

void UDPSocket_destroy(UDPSocket_pointer this) {
  if (close(this->socket) == -1)
    syserr("UDPSocket_destroy - close");

  free(this);
}

struct TCPListener {
  int socket;
};

struct TCPConnection {
  int socket;
};

TCPListener_pointer TCP_listen(short port) {
  TCPListener_pointer this = new(struct TCPListener);
  this->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->socket == -1)
    syserr("TCPListener_create - failed to create socket.");

  struct sockaddr_in address;
  safe_zero_memory(&address, 1, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = host_to_network_short(port);

  if (bind(this->socket, (struct sockaddr*)&address, sizeof(address)) != 0)
    syserr("TCPListener_create - failed to bind socket");

  if (listen(this->socket, 5) != 0)
    syserr("TCPListener_create - failed to start listening");

  return this;
}

TCPConnection_pointer TCP_accept(TCPListener_pointer listener) {
  struct sockaddr_in address;
  socklen_t address_length = sizeof(address);
  int new_socket = accept(listener->socket, (struct sockaddr*)&address, &address_length);
  if (new_socket < 0)
    syserr("TCPListener_accept - accept failure");

  TCPConnection_pointer connection = new(struct TCPConnection);
  connection->socket = new_socket;
  return connection;
}

TCPConnection_pointer TCP_connect(const char* service, const char* hostname) {
  struct addrinfo* address;
  struct addrinfo hints;
  safe_zero_memory(&hints, 1, sizeof(hints));
  //hints.ai_family = AF_INET | AF_INET6;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(hostname, service, &hints, &address);
  if (status != 0) {
    syserr("TCP_connect - getaddrinfo failure: %s", gai_strerror(status));
  }

  TCPConnection_pointer connection = new(struct TCPConnection);
  connection->socket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
  if (connection->socket < 0) {
    syserr("TCP_connect - creating socket failure");
  }

  if (connect(connection->socket, address->ai_addr, address->ai_addrlen) < 0)
    syserr("TCP_connect - connection failure");

  freeaddrinfo(address);
  return connection;
}

size_t TCP_receiveToBuffer(TCPConnection_pointer connection, void* buffer, size_t count) {
  char* buffer_ptr = (char*)buffer;
  size_t cumulatively_received = 0;

  while (count > cumulatively_received) {
    ssize_t received = recv(connection->socket, buffer_ptr, count, 0);
    if (received < 0) {
      syserr("TCPReceive - recv failure");
    }
    else if (received == 0) {
      /* Connection aborted. */
      break;
    }

    cumulatively_received += received;
    buffer_ptr += received;
  }

  return cumulatively_received;
}

String_pointer TCP_receive(TCPConnection_pointer connection, size_t count) {
  char* const buffer = new_table(char, count);
  size_t received = TCP_receiveToBuffer(connection, buffer, count);
  String_pointer result = String_fromData(buffer, received);
  free(buffer);
  return result;
}

void TCP_sendData(TCPConnection_pointer connection, const void* data, size_t size) {
  while (size > 0) {
    ssize_t sent = send(connection->socket, data, size, 0);
    if (sent < 0)
      syserr("TCPSend - send failure");

    data = safe_raw_offset((void*)data, sent, sizeof(char));
    size -= sent;
  }
}

void TCP_sendString(TCPConnection_pointer connection, String_pointer data) {
  TCP_sendData(connection, String_data(data), String_size(data));
}

void TCP_sendMessage(TCPConnection_pointer connection, String_pointer message) {
  uint32_t size = String_size(message);
  TCP_sendData(connection, &size, sizeof(uint32_t));
  TCP_sendString(connection, message);
}

String_pointer TCP_receiveMessage(TCPConnection_pointer connection) {
  uint32_t count;
  if (TCP_receiveToBuffer(connection, &count, sizeof(uint32_t)) != sizeof(uint32_t)) {
    fatal("TCP_receiveMessage - invalid message header");
  }
  String_pointer message = TCP_receive(connection, count);
  if (String_size(message) < count) {
    fatal("TCP_receiveMessage - received incomplete message (connection aborted?)");
  }
  return message;
}

void TCP_closeAndDestroyConnection(TCPConnection_pointer connection) {
  if (close(connection->socket) == -1)
    syserr("TCP_closeAndDestroyConnection - close failure");
  connection->socket = 0;
  free(connection);
}

void TCP_closeAndDestroyListener(TCPListener_pointer listener) {
  if (close(listener->socket) == -1)
    syserr("TCP_closeAndDestroyListener - close failure");
  listener->socket = 0;
  free(listener);
}
