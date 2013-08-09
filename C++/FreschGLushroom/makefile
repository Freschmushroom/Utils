 
all: GL_Main.o Input.o libFreschGLushroom.so

GL_Main.o:
	g++ -fPIC -c -o "./bin/GL_Main.o" GL_Main.cpp -lglut
	
Input.o:
	g++ -fPIC -c -o "./bin/Input.o" Input.cpp -lglut
	
libFreschGLushroom.so:
	g++ -shared -o "./bin/libFreschGLushroom.so" "./bin/GL_Main.o" "./bin/Input.o" -lglut