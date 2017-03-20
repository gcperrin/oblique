/**
 * buffer.c
 *
 * See header for usage
 */

#include "buffer.h"

void buffer_init(buffer_t *buffer) {
  buffer->tail_idx = 0;
  buffer->head_idx = 0;
}

void buffer_queue(buffer_t *buffer, char data) {
  if (buffer_is_full(buffer)) {
    // Is going to overwrite the oldest byte
    buffer->tail_idx = ((buffer->tail_idx + 1) & BUFFER_MASK);
  }

  // Place data in buffer
  buffer->data[buffer->head_idx] = data;
  buffer->head_idx = ((buffer->head_idx + 1) & BUFFER_MASK);
}

buffer_size_t buffer_dequeue(buffer_t *buffer, char *data) {
  if(buffer_is_empty(buffer)) {
    // No items
    return 0;
  }

  *data = buffer->data[buffer->tail_idx];
  buffer->tail_idx = ((buffer->tail_idx + 1) & BUFFER_MASK);
  return 1;
}

void buffer_push(buffer_t *buffer, const char *data, buffer_size_t size) {
  // Add bytes; one by one
  buffer_size_t i;
  for(i = 0; i < size; i++) {
    buffer_queue(buffer, data[i]);
  }
}

buffer_size_t buffer_pop(buffer_t *buffer, char *data, buffer_size_t len) {
  if(buffer_is_empty(buffer)) {
    // No items
    return 0;
  }

  char *data_ptr = data;
  buffer_size_t cnt = 0;
  while((cnt < len) && buffer_dequeue(buffer, data_ptr)) {
    cnt++;
    data_ptr++;
  }
  return cnt;
}

buffer_size_t buffer_peek(buffer_t *buffer, char *data, buffer_size_t index) {
  if(index >= buffer_num_items(buffer)) {
    // No items at index
    return 0;
  }

  // Add index
 buffer_size_t data_index = ((buffer->tail_idx + index) & BUFFER_MASK);
  *data = buffer->data[data_index];
  return 1;
}

uint8_t buffer_is_empty(buffer_t *buffer) {
  return (buffer->head_idx == buffer->tail_idx);
}

uint8_t buffer_is_full(buffer_t *buffer) {
  return ((buffer->head_idx - buffer->tail_idx) & BUFFER_MASK) == BUFFER_MASK;
}

buffer_size_t buffer_size(buffer_t *buffer) {
  return ((buffer->head_idx - buffer->tail_idx) & BUFFER_MASK);
}
