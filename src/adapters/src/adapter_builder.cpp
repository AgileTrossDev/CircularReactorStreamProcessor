#include <iostream>

#include "types.h"
#include "adapter_builder.h"

using std::map;
using std::string;
using std::cout;
using std::endl;

map<string, AdapterBuilder::builder_function_type> AdapterBuilder::builders = {}; 

void AdapterBuilder::register_builder(string adapter_name, builder_function_type builder) {
  cout <<"Registering: " << adapter_name << endl;
  AdapterBuilder::builders[adapter_name] = builder;  
}

AdapterInterface& AdapterBuilder::build(string adapter_name, VariantMap_T &job_request) {
   return builders[adapter_name](job_request);
}