#include <iostream>
#include <pthread.h>

#include "types.h"
#include "adapter_builder.h"
#include "adapter_interface.h"

using std::cout;
using std::endl;

int main(void) {
  cout <<"Application Starting" << endl;

  // TODO: Setup Job from CMD Line Parameters
  VariantMap_T job_request;
  job_request["ingest_file"] = "scott.tmp";

  AdapterBuilder::build("FileAdapter", job_request);

  cout << "Application exiting!" << endl;


}