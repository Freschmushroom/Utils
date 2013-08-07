INCLUDES=-lws2_32 -lboost_thread -lboost_system
OUT_FOLDER=C:\FreschMushroom\GitHub\Utils\C++\WinSockets\bin

all: WindowsClient.o WindowsServerSocket.o WindowsSocket.o WinSockets.dll


WindowsClient.o: WindowsClient.cpp Sockets.h
	g++ -Wall -c -o "$(OUT_FOLDER)\WindowsClient.o" WindowsClient.cpp $(INCLUDES) $(LIB_PATHS)
WindowsServerSocket.o: WindowsServerSocket.cpp Sockets.h
	g++ -Wall -c -o "$(OUT_FOLDER)\WindowsServerSocket.o" WindowsServerSocket.cpp $(INCLUDES) $(LIB_PATHS)
WindowsSocket.o: WindowsSocket.cpp Sockets.h
	g++ -Wall -c -o "$(OUT_FOLDER)\WindowsSocket.o" WindowsSocket.cpp $(INCLUDES) $(LIB_PATHS)

WinSockets.dll: WindowsClient.o WindowsServerSocket.o WindowsSocket.o
	g++ -shared -o "$(OUT_FOLDER)\sockets.dll" "$(OUT_FOLDER)\WindowsClient.o" "$(OUT_FOLDER)\WindowsServerSocket.o" "$(OUT_FOLDER)\WindowsSocket.o" $(INCLUDES) $(LIB_PATHS)
	

clean:
	-del *.o "$(OUT_FOLDER)\*.o" "$(OUT_FOLDER)\*.dll" 