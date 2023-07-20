#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

#include "circular_buffer.h"

using namespace std;

// Static function to get instance of the CircularBuffer Singleton.
//
// NOTE: the Size of the Buffer is only initialized on the first get_instance
CircularBuffer& CircularBuffer::get_instance(size_t buffer_size) {
  static CircularBuffer instance(buffer_size);  
  return instance;
}

// Writes Data to the Buffer
//
// NOTE: Will block until there is space enough for write
void CircularBuffer::write(const char* incoming_data, size_t length_of_incoming_data) {

  // Blocks until we have acess to buffer and there is enough space for the write
  unique_lock<mutex> lock(mtx);
  notFull.wait(lock, [this, length_of_incoming_data] { return size_of_buffer - used_space() >= length_of_incoming_data; });

  // Copy incoming_data to the start of available space at the end of the buffer vector
  size_t bytes_to_write = min(length_of_incoming_data, size_of_buffer - write_ptr);
  copy(incoming_data, incoming_data + bytes_to_write, buffer.begin() + write_ptr);

  // Handle wrap around of circular buffer if there is remaining data to write
  if (length_of_incoming_data != bytes_to_write) {
    copy(incoming_data + bytes_to_write, incoming_data + length_of_incoming_data, buffer.begin());
  }

  // Update the location of the write pointer, handling the circular buffer wrap around
  write_ptr = (write_ptr + length_of_incoming_data) % size_of_buffer;

  // We are done here, so unlock and notify
  lock.unlock();
  notEmpty.notify_one();
}

void CircularBuffer::read(char* outgoing_data, size_t length_of_outgoing_data) {
  cout << "READ!!!!" << endl;
  /*
  unique_lock<mutex> lock(mtx);
  notEmpty.wait(lock, [this, length_of_outgoing_data] { return used_space() >= length_of_outgoing_data; });

  size_t bytesToRead = min(length_of_outgoing_data, size_of_buffer - read_ptr);
  copy(buffer.begin() + read_ptr, buffer.begin() + read_ptr + bytesToRead, outgoing_data);

  size_t remaining_bytes = length_of_outgoing_data - bytesToRead;
  copy(buffer.begin(), buffer.begin() + remaining_bytes, outgoing_data + bytesToRead);

  
  read_ptr = (read_ptr + length_of_outgoing_data) % size_of_buffer;

  lock.unlock();
  notFull.notify_one();
  */
}


// Moves the read-ptr to position to read
void CircularBuffer::seek(size_t position) {
  unique_lock<mutex> lock(mtx);
  read_ptr = position % size_of_buffer;
  lock.unlock();
}

// Returns the size of the buffer that is actively in use/unprocessed
size_t CircularBuffer::used_space() const {
  return (write_ptr >= read_ptr) ? (write_ptr - read_ptr) : (size_of_buffer - read_ptr + write_ptr);
}


// Returns a boolean representing if the buffer has space to be written to
bool CircularBuffer::able_to_write() const {
  return write_ptr == read_ptr;
}
