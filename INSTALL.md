Tohil
=====

This file explains how to build and install Tohil from source.

Installing
----------

* Install the dependencies.
  * SDL 2.0
    * http://libsdl.org
  * OpenGL 1.1 or later
    * (OpenGL headers are handled via SDL)
    * (OpenGL is loaded dynamically)
  * MXE (optional; needed for cross-compiling Windows binaries)
    * http://mxe.cc/

* Download the source code.
  * GitHub/SSH
    * git clone git@github.com:olofson/tohil.git
  * *Alternatively:* GitHub/HTTPS
    * git clone https://github.com/olofson/tohil.git

* Configure the source tree.
  * Option 1 (Un*x with bash or similar shell)
    * ./configure [*target*]
      * Currently available targets:
        * release
        * release32
        * maintainer
        * debug
        * mingw-release
        * mingw-debug
        * mingw-static
        * all *(all of the above)*
        * (Default if not specified: release)
  * Option 2 (Using CMake directly)
    * mkdir build
    * cd build
    * cmake ..

* Build and install.
  * ./make-all
    * (The resulting executables are found in "build/<target>/src/")
  * *Alternatively:* Enter the desired build target directory.
    * make
    * *Optional:* sudo make install
