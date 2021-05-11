CXXFLAGS = -std=gnu++0x -Wall
LDLIBS = -lstdc++
.PHONY: all clean
all: example-client
clean:
	-rm  *.o
testserver: node_modules
	node example-server.js
node_modules:
	npm install
example-client: example-client.o easywsclient.o
example-client.o: example-client.cpp easywsclient.hpp
easywsclient.o: easywsclient.cpp easywsclient.hpp
