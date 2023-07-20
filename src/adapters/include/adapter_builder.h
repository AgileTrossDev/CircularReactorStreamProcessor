#ifndef ADAPTER_BUILDER_H
#define ADAPTER_BUILDER_H

#include <map>
#include <string>

#include "types.h"
#include "adapter_interface.h"

// Class used at the builder for classes of Adpaters implementing the Adapter Interface
//
// NOTE: The intention here is that each derived class creates a static instance
// of the Adapter Builder. So that when the class is loaded at run time, it 
// registered with the builder.
class AdapterBuilder {
  public:

    typedef  AdapterInterface& (*builder_function_type)(VariantMap_T &job_request) ;

    // ------------------------------------------------------
    // Static Functions
    // ------------------------------------------------------
    static void register_builder(std::string adapter_name, builder_function_type);
    static AdapterInterface& build(std::string adapter_name, VariantMap_T &job_request);
    
    // ------------------------------------------------------
    // Constructor
    // ------------------------------------------------------
    AdapterBuilder(std::string adapter_name,builder_function_type builder) {AdapterBuilder::register_builder(adapter_name, builder);}    

    static std::map<std::string, builder_function_type> builders;

};


#endif
