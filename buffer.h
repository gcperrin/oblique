/**
 * buffer.h
 * A circular buffer implementation
 */

#ifndef INCLUDE_BUFFER_H_
#define INCLUDE_BUFFER_H_

#define BUFFER_SIZE 16384

#if (BUFFER_SIZE & (BUFFER_SIZE - 1)) != 0
#error "BUFFER_SIZE must be a power of two"
#endif

// Modulus mask
#define BUFFER_MASK (BUFFER_SIZE-1)

#include "opcua_thread.h"

typedef uint32_t buffer_size_t;
typedef struct buffer_t buffer_t;

struct buffer_t {
    char data[BUFFER_SIZE];
    buffer_size_t tail_idx;
    buffer_size_t head_idx;
};

/**
 * Initializes the circular buffer pointed to by buffer
 * This function can also be used to empty and reset
 * @param buffer The buffer to initialize.
 */
void buffer_init(buffer_t *buffer);

/**
 * Adds a byte to the buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data The byte to place.
 */
void buffer_queue(buffer_t *buffer, char data);

/**
 * Returns the oldest byte in the buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
buffer_size_t buffer_dequeue(buffer_t *buffer, char *data);

/**
 * Adds an array of bytes to the buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void buffer_push(buffer_t *buffer, const char *data, buffer_size_t size);

/**
 * Returns the oldest bytes in the buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
buffer_size_t buffer_pop(buffer_t *buffer, char *data, buffer_size_t len);

/**
 * Returns an element without removing it.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
buffer_size_t buffer_peek(buffer_t *buffer, char *data, buffer_size_t index);

/**
 * Returns whether the buffer is empty.
 * @param buffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
uint8_t buffer_is_empty(buffer_t *buffer);

/**
 * Returns whether the buffer is full.
 * @param buffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
uint8_t buffer_is_full(buffer_t *buffer);

/**
 * Returns the number of items in the buffer.
 * @param buffer The buffer for which the number of items should be returned.
 * @return The number of items in the buffer.
 */
buffer_size_t buffer_size(buffer_t *buffer);


#endif /* INCLUDE_CIRCULAR_BUFFER_H_ */
