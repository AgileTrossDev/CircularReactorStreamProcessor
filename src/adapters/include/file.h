#ifndef ADAPTER_FILE_H
#define ADAPTER_FILE_H

#include "adapter_interface.h"

// This class inherits from Base and implements fun()
class FileAdapter : public AdapterInterface {
    // private member variable
    int y;
 
public:
    // implementation of the pure virtual function
    // Reads the next block of data from a file
    virtual void read();          

    // Writes a block of data to a file
    virtual void write();         
};


class FileAdapterRegister : public AdapterBuilder {
  public:
    FileAdapterRegister() : AdapterBuilder("FileAdapter") {};
};

#endif