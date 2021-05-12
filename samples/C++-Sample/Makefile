CXXFLAGS = -std=gnu++0x -Wall
LDLIBS = -lstdc++
.PHONY: all clean
all: ezesampleclient
clean:
	-rm  *.o
testserver: node_modules
	node example-server.js
node_modules:
	npm install
ezesampleclient: ezesampleclient.o ezewbsclient.o
ezesampleclient.o: ezesampleclient.cpp ezewbsclient.hpp
ezewbsclient.o: ezewbsclient.cpp ezewbsclient.hpp
