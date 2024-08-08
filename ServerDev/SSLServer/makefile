# Makefile for SSLServer

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Include directories
INCLUDES = -I/usr/include

# Library directories
LIBDIRS = -L/usr/lib -L/usr/local/lib

# Libraries
LIBS = -lboost_system -lboost_thread -lssl -lcrypto -lpthread

# Source files
SRCS = SSLServer.cpp

# Header files
HEADERS = SSLServer.h

# Output executable
TARGET = SSLServer.elf

# Object files
OBJS = $(SRCS:.cpp=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBDIRS) $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
