#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

class CircularBuffer {

public:

  // Singleton Constructor
  static CircularBuffer& get_instance(std::size_t buffer_size = 1048576);
     
  // Singletons should not be cloneable or assignable   
  CircularBuffer(CircularBuffer &other) = delete;    
  void operator=(const CircularBuffer &) = delete;

  // API tp work with the buffer
  void write(const char* incoming_data, std::size_t length_of_incoming_data);
  void read(char* outgoing_data, std::size_t length_of_outgoing_data);
  void seek(std::size_t position);
  std::size_t used_space() const;
  bool able_to_write() const;
  
  private:

    // Attributes
    std::vector<char> buffer;           // Vector of bytes in the buffer
    std::size_t size_of_buffer;        // 
    std::size_t read_ptr;
    std::size_t write_ptr;
    std::mutex mtx;
    std::condition_variable notFull;
    std::condition_variable notEmpty;

    // Private Constructor to make it a Singleton of class manageing a buffer
    CircularBuffer(std::size_t buffer_size)
        : buffer(buffer_size), size_of_buffer(buffer_size), read_ptr(0), write_ptr(0) {}
};

#endif