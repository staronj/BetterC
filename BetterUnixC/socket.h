/**
 * Copyright Jakub Staroń 2016
 */

#ifndef BETTERC_SOCKET_H
#define BETTERC_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include "better_string.h"

uint16_t host_to_network_short(uint16_t s);

uint16_t network_to_host_short(uint16_t s);

uint32_t host_to_network_long(uint32_t l);

uint32_t network_to_host_long(uint32_t l);

struct UDPSocket;

typedef struct UDPSocket* UDPSocket_pointer;

struct TCPListener;

typedef struct TCPListener* TCPListener_pointer;

struct TCPConnection;

typedef struct TCPConnection* TCPConnection_pointer;

/**
 * Creates new TCP listener which will be listening on given \p port.
 */
TCPListener_pointer TCP_listen(short port);

/**
 * Waits for client to connect to \p listener.
 *
 * Returns TCP connection to client.
 */
TCPConnection_pointer TCP_accept(TCPListener_pointer listener);

/**
 * Connects to specific \p service and \p hostname.
 */
TCPConnection_pointer TCP_connect(const char* service, const char* hostname);

/**
 * Receives \p count bytes from TCP \p connection and stores them in \p buffer.
 *
 * Returns number of received bytes. It can be smaller than \p count if connection
 * was closed by sender.
 */
size_t TCP_receiveToBuffer(TCPConnection_pointer connection, void* buffer, size_t count);

/**
 * Receives \p count bytes from TCP \p connection.
 *
 * Returns string with received data.
 * If sender closes the connection returned string can be shorter than
 * \p count bytes.
 */
String_pointer TCP_receive(TCPConnection_pointer connection, size_t count);

/**
 * Sends \p data or \p string to TCP \p connection.
 */
void TCP_sendData(TCPConnection_pointer connection, const void* data, size_t size);
void TCP_sendString(TCPConnection_pointer connection, String_pointer data);

/**
 * Sends message to \p connection.
 *
 * Sends size of \p message string and then message string.
 * Should be received via TCP_receiveMessage function.
 */
void TCP_sendMessage(TCPConnection_pointer connection, String_pointer message);

/**
 * Receives message sent by TCP_sendMessage function.
 */
String_pointer TCP_receiveMessage(TCPConnection_pointer connection);

/**
 * Closes \p connection and frees memory.
 */
void TCP_closeAndFreeConnection(TCPConnection_pointer connection);

/**
 * Stops listening, closes the socket and frees memory.
 */
void TCP_closeAndFreeListener(TCPListener_pointer listener);

#endif /* BETTERC_SOCKET_H */
