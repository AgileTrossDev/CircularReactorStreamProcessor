#include <iostream>
#include <pthread.h>

#include "types.h"
#include "adapter_builder.h"
#include "adapter_interface.h"
#include "circular_buffer.h"
#include "new_data_event.h"
#include "reactor_events.h"

using std::cout;
using std::endl;

int main(void) {
  cout <<"Application Starting" << endl;

  // TODO: Setup Job from CMD Line Parameters
  VariantMap_T job_request;
  job_request["ingest_file"] = "scott.tmp";

  AdapterInterface& file_ingester = AdapterBuilder::build("FileAdapter", job_request);
  file_ingester.read();

  CircularBuffer& buffer = CircularBuffer::get_instance();
  cout << "Good to go: " << buffer.able_to_write() << endl; 


  NewDataEvent<AdapterInterface&> event_handler(file_ingester);
  

  ReactorEvent event;
  event.id = 1;
  event.data ="SCOTT";

  event_handler.handle_event(event);


  cout << "Application exiting!" << endl;


}