CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O2 -mwindows -municode -D_WIN32_WINNT=0x0A00
SOURCE = main.cpp
TARGET = ste

$(TARGET): $(SOURCE)
		$(CXX) $(SOURCE) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

all: $(TARGET)
.PHONY: clean
