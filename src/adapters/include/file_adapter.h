#ifndef ADAPTER_FILE_H
#define ADAPTER_FILE_H

#include <fstream>

#include "adapter_interface.h"
#include "adapter_builder.h"

// This class inherits from Base and implements the Adapter Interface
class FileAdapter : public AdapterInterface {
 
public: 

  // Builder Functions
  static AdapterInterface& build(VariantMap_T &job_request);  

  // Constructor
  FileAdapter(std::string ingest_path);

  // implementation of the pure virtual function
  // Reads the next block of data from a file
  virtual void read();          

  // Writes a block of data to a file
  virtual void write();      



  private:

    // Writes a block of data to a file
    void open();    

    std::string file_path;
    std::ifstream file_stream;

   
};


// Class that is loaded staticly to register this class with the builder before main executes
class FileAdapterRegister : public AdapterBuilder {
  public:
    FileAdapterRegister() : AdapterBuilder("FileAdapter", FileAdapter::build){};
};

#endif