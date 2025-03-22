# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17
LDFLAGS := -lraylib -lopengl32 -lgdi32 -lwinmm #-Wl,--subsystem,windows to disable debuggingconsole

# Target executable
TARGET := bin/game

# Source files (all .cpp files in the src directory)
SRCS := $(wildcard src/**/*.cpp) main.cpp

# Build rules
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET).exe $(LDFLAGS)

clean:
	rm -f $(TARGET).exe
