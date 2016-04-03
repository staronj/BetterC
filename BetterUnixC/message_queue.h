/**
 * Copyright Jakub Staroń 2015
 */

#ifndef BETTERC_MESSAGE_QUEUE_H
#define BETTERC_MESSAGE_QUEUE_H

#include "system_headers.h"
#include "better_string.h"

/**
 * Wrapper for system V message queue.
 */
struct MessageQueue;

typedef struct MessageQueue * MessageQueue_pointer;

/** Maximum size of message. */
#define MESSAGE_MAX_SIZE (100)

/**
 * Creates or opens new message queue with key_t \p key.
 */
MessageQueue_pointer MessageQueue_openOrCreate(key_t key);

/**
 * Opens new message queue with key_t \p key.
 * In case of failure calls syserr.
 */
MessageQueue_pointer MessageQueue_open(key_t key);

/**
 * Sends \p message to queue \p this with message type \p type.
 */
void MessageQueue_send(MessageQueue_pointer this, long type, String_pointer message);

/**
 * Receives and returns message of type \p type from queue \p this.
 */
String_pointer MessageQueue_receive(MessageQueue_pointer this, long type);

/**
 * Closes and frees queue \p this.
 * In case of failure calls syserr.
 */
void MessageQueue_closeAndFree(MessageQueue_pointer this);

/**
 * Frees queue \p this without closing it.
 */
void MessageQueue_free(MessageQueue_pointer this);

#endif /* BETTERC_MESSAGE_QUEUE_H */
