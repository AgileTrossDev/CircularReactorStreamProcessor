#include <iostream>
#include <variant>

#include "file_adapter.h"

using namespace std;

AdapterInterface& FileAdapter::FileAdapter::build(VariantMap_T &job_request) {

  string ingest_file = get<std::string>( job_request["ingest_file"] );
   

  cout << "Building File Adapter class: " << ingest_file  << endl;
  FileAdapter *instance = new FileAdapter(ingest_file);
  return *instance;

}

// Constructor
FileAdapter::FileAdapter(std::string ingest_path) {

  file_path = ingest_path;

  

  
  

}

void FileAdapter::open() {

  file_stream.open("ingest_path.txt");


}

// implementation of the pure virtual function
// Reads the next block of data from a file
void FileAdapter::read() {
  cout << "READING" << endl;
  //if (!file_stream.is_open()) {open();}

}         

// Writes a block of data to a file
void FileAdapter::write() {
}


// Staticly create class here so that adapter can be registered before main executes
static FileAdapterRegister file_adapter_register;



