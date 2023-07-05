# the compiler: gcc for C program, define as g++ for C++
CC = g++
 
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall -std=c++11

#INC=-Ilibs/csv_ingestion/include -Ilibs/coordinates/include
INC=-Isrc/adapters/include
#$(OBJS) = $(patsubst %.o,obj/%.o,file0.o file1.o)
 
# The build target 
TARGET = src/main
EXECUTABLE = bin/app
OBJ_DIR = obj/



all: clean adapters executable


executable:
	g++ ${CFLAGS}  ${INC} -o ${EXECUTABLE} ${TARGET}.cpp obj/adapter_interface.o obj/adapter_file.o


adapters:
	g++ ${CFLAGS} ${INC} -c -o ${OBJ_DIR}adapter_interface.o src/adapters/src/adapter_interface.cpp 
	g++ ${CFLAGS} ${INC} -c -o ${OBJ_DIR}adapter_file.o src/adapters/src/file.cpp

 


clean:
	$(RM) $(EXECUTABLE)
	$(RM) $(OBJ_DIR)*