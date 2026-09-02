\
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = hotel_app
SOURCES = $(wildcard *.cpp)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
