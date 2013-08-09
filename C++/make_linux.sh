
echo "Making GO Game for Linux"
echo "Make sure you are not running this script as root"

echo "Making Networking Library"

cd ./UnixSockets

make -B -s

cd ..

echo "Making GLLib"

echo "You need to have X11-devel, GL-devel, GLU-devel and freeglut-devel installed"

cd ./FreschGLushroom

make -B -s

cd ..

echo "Copying Files"

cp ./UnixSockets/sockets.h ./Game
cp ./UnixSockets/bin/sockets.so ./Game/build
cp ./FreschGLushroom/FreschGLushroom.h ./Game
cp ./FreschGLushroom/Events.h ./Game
cp ./FreschGLushroom/bin/libFreschGLushroom.so ./Game/build

echo "Making Game"

echo "You need to have X11-devel, GL-devel, GLU-devel and freeglut-devel installed"

cd ./Game

make -B -s

cd ..

echo "Finished"
