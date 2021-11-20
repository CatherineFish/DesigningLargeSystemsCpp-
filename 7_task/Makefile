CXX = g++
CXXFLAGS += -std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
SOURCES = main.cpp factory.cpp
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = 7_task

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) generators.h $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)