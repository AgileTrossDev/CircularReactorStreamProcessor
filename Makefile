# the compiler: gcc for C program, define as g++ for C++
CC = g++ 
 
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall -std=c++17 

#INC=-Ilibs/csv_ingestion/include -Ilibs/coordinates/include
INC=-Isrc/adapters/include -Iinclude
#$(OBJS) = $(patsubst %.o,obj/%.o,file0.o file1.o)
 
# The build target 
TARGET = src/main
EXECUTABLE = bin/app
OBJ_DIR = obj/

all: clean adapters executable

# NOTE: -lpthread need to overcome the 'undefined reference to `pthread_create'' linker error.  This appears to be needed at the end of the object list
executable:
	g++  ${CFLAGS}  ${INC} -o ${EXECUTABLE} ${TARGET}.cpp -lpthread obj/adapter_interface.o obj/adapter_builder.o obj/file_adapter.o -lpthread

adapters:
	g++  ${CFLAGS} ${INC} -c -o ${OBJ_DIR}adapter_builder.o src/adapters/src/adapter_builder.cpp 
	g++  ${CFLAGS} ${INC} -c -o ${OBJ_DIR}adapter_interface.o src/adapters/src/adapter_interface.cpp
	g++ ${CFLAGS} ${INC} -c -o ${OBJ_DIR}file_adapter.o src/adapters/src/file_adapter.cpp

clean:
	$(RM) $(EXECUTABLE)
	$(RM) $(OBJ_DIR)*