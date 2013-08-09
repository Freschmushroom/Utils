 
INCLUDES = -lglut -lsockets -lFreschGLushroom -lGL -lboost_thread
OUT_FOLDER = ./build
LIB_PATH = -L./build

all: Field.o GameField.o Go.o KeyboardListener.o Go

Field.o:
	g++ -c -o "$(OUT_FOLDER)/Field.o" Field.cpp -std=c++11

GameField.o:
	g++ -c -o "$(OUT_FOLDER)/GameField.o" GameField.cpp -std=c++11
	
Go.o:
	g++ -c -o "$(OUT_FOLDER)/Go.o" Go.cpp -std=c++11
	
KeyboardListener.o:
	g++ -c -o "$(OUT_FOLDER)/KeyboardListener.o" KeyboardListener.cpp -std=c++11
	
Go:
	g++ -o "Go" "$(OUT_FOLDER)/Field.o" "$(OUT_FOLDER)/GameField.o" "$(OUT_FOLDER)/Go.o" "$(OUT_FOLDER)/KeyboardListener.o" $(INCLUDES) $(LIB_PATH) -std=c++11