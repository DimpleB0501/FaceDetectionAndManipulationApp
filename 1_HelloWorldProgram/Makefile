CC = g++ -std=c++0x
CFLAGS = -c -v -Wall


SOURCES_TEST = src/main.cpp
OBJECTS_TEST = $(SOURCES_TEST:.cpp = .o)
EXECUTABLE_TEST = mainExample
$(EXECUTABLE_TEST):
	$(CC) $(OBJECTS_TEST) -o build/$@
