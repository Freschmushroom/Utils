 
INCLUDES = 
OUT_FOLDER = ./bin

all: UnixSocket.o UnixClient.o UnixServer.o UnixSockets.so


UnixClient.o:
	g++ -Wall -fPIC -c -o "$(OUT_FOLDER)/UnixClient.o" UnixClient.cpp $(INCLUDES) -std=c++11
	
UnixServer.o:
	g++ -Wall -fPIC -c -o "$(OUT_FOLDER)/UnixServer.o" UnixServer.cpp $(INCLUDES) -std=c++11
	
UnixSocket.o:
	g++ -Wall -fPIC -c -o "$(OUT_FOLDER)/UnixSocket.o" UnixSocket.cpp $(INCLUDES) -std=c++11
	
UnixSockets.so:
	g++ -shared -o "$(OUT_FOLDER)/libsockets.so" "$(OUT_FOLDER)/UnixClient.o" "$(OUT_FOLDER)/UnixServer.o" "$(OUT_FOLDER)/UnixSocket.o" $(INCLUDES) -std=c++11
	
clean:
	-del *.o "$(OUT_FOLDER)/*.o" "$(OUT_FOLDER)/*.so"