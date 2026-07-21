CXX = g++
STD = -std=c++17
INC = -I/opt/homebrew/include
LIB = -L/opt/homebrew/lib
LIBS = -lraylib -framework Cocoa -framework IOKit -framework OpenGL -framework CoreVideo

TARGET = drone
SRC = drone.cpp

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(STD) $(INC) $(LIB) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean