
The binaries in the bin folder were compiled against kernel version 3.7.10-1.16-desktop on openSUSE 12.3

If you are using a different system or a different kernel version please recompile using

./make_linux.sh

The script compiles all libraries creates the Game and links everything. You eventually have to add the librarys libsockets.so and libFreschGLushroom.so to your dynamic library path.

Either by copying them to the path in:

	>echo $LD_LIBRARY_PATH

Or by modifying the library path

	>export LD_LIBRARY_PATH=<path to the libraries>:$LD_LIBRARY_PATH
