# INSTALLATION GUIDE

## Prerequesites

-- Linux platform
        tested on Ubuntu Xenial 16.04 LTS
        Update on Ubuntu Jammy 22.04 LTS
-- A compiler that supports C++11 (tested with gcc 5.4.0)
-- CMake 3.18.1 or later

## Install dependencies before building gSOAP

### Bison

```bash
wget <http://ftp.gnu.org/gnu/bison/bison-2.3.tar.gz>
tar -xvzf bison-2.3.tar.gz
cd  bison-2.3/
./configure --with-libiconv-prefix=/usr/local/libiconv/
make
sudo make install
```

### Flex

```bash
wget <https://github.com/westes/flex/files/981163/flex-2.6.4.tar.gz>
tar xvzf flex-2.6.4.tar.gz
cd flex-2.6.4/
./configure
make
sudo make install
```

## Build and install gSOAP

```bash
wget <https://netix.dl.sourceforge.net/project/gsoap2/gsoap-2.8/gsoap_2.8.92.zip>
tar xvzf gsoap_2.8.92.zip
cd gsoap-2.8
./configure 
make
sudo make install
which wsdl2h
```

! update for Ubuntu Jammy 22.04 :

```bash
wget <https://netix.dl.sourceforge.net/project/gsoap2/gsoap-2.8/gsoap_2.8.122.zip>
unzip gsoap_2.8.124.zip
cd gsoap-2.8
./configure
make
sudo make install
which wsdl2h
```

Note : default configuration file generates a non-SSL-enabled wsdl2h tool that is not working with HTTPS website.

## Install Mongo CXX driver

### Mongo C Driver

Mongo CXX driver needs previously the Mongo C driver as explained here :
<http://mongocxx.org/mongocxx-v3/installation/#step-1-install-the-latest-version-of-the-mongodb-c-driver>

```bash
tar xzf mongo-c-driver-1.17.0.tar.gz
cd mongo-c-driver-1.17.0/
mkdir cmake-build
cd cmake-build/
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
sudo make install
```

This last command installs the following files :

* in /usr/local/lib :

libbson-1.0.*
libbson-static-1.0.a
libmongoc-1.0.*
libmongoc-static-1.0.a

* in /usr/local/bin :

mongoc-stat

! update for Ubuntu Jammy 22.04 :
Mongo CXX driver r3.7.0-beta1 needs previously the Mongo C driver version 1.19

```bash
unzip mongo-c-driver-r1.19.zip
cd mongo-c-driver-r1.19/
mkdir cmake-build
cd cmake-build/
cmake -DBUILD_VERSION=1.19.0 -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
sudo make install
```

### Build Mongo CXX driver

```bash
curl -OL <https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.0/mongo-cxx-driver-r3.6.0.tar.gz>

tar -xzf mongo-cxx-driver-r3.6.0.tar.gz
cd mongo-cxx-driver-r3.6.0/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DBSONCXX_POLY_USE_MNMLSTC=1
```

-- Auto-configuring bsoncxx to use MNMLSTC for polyfills since C++17 is inactive
bsoncxx version: 3.6.0
found libbson version 1.17.0
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
-- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
mongocxx version: 3.6.0
found libmongoc version 1.17.0
-- Looking for C++ include pthread.h
-- Looking for C++ include pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Check if compiler accepts -pthread
-- Check if compiler accepts -pthread - yes
-- Found Threads: TRUE  
-- Build files generated for:
-- build system: Unix Makefiles
-- Configuring done
-- Generating done
-- Build files have been written to: /home/jeanloup/appli/mongo-cxx-driver-r3.6.0/build

```bash
cmake --build . --target EP_mnmlstc_core
sudo cmake --build . --target install
```

Log copied in Mongo-CXX-INSTALL.log

! update for Ubuntu Jammy 22.04:
Mongo CXX driver r3.7.0-beta1 needed for Jammy (bug fix wih the good version of lib Catch)
See <https://jira.mongodb.org/browse/CXX-2358>

```bash
curl -OL <https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.7.0-beta1/mongo-cxx-driver-r3.7.0-beta1.tar.gz>
tar -xvzf mongo-cxx-driver-r3.7.0-beta1.tar.gz
cd mongo-cxx-driver-r3.7.0-beta1/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBSONCXX_POLY_USE_BOOST=1 -Dlibmongoc-1.0_DIR:PATH=/usr/local/lib/
```

Command 'cmake .. -L' outputs :

bsoncxx version: 3.7.0-pre
found libbson version 1.19.0
mongocxx version: 3.7.0-pre
found libmongoc version 1.19.0
-- Build files generated for:
-- build system: Unix Makefiles
-- Configuring done
-- Generating done
-- Build files have been written to: /home/jeanloup/appli/mongo-cxx-driver-r3.7.0-beta1/build
-- Cache values
BSONCXX_OUTPUT_BASENAME:STRING=bsoncxx
BSONCXX_POLY_USE_BOOST:BOOL=1
BSONCXX_POLY_USE_MNMLSTC:BOOL=OFF
BSONCXX_POLY_USE_STD:BOOL=OFF
BSONCXX_POLY_USE_STD_EXPERIMENTAL:BOOL=OFF
BSONCXX_POLY_USE_SYSTEM_MNMLSTC:BOOL=OFF
BUILD_SHARED_AND_STATIC_LIBS:BOOL=OFF
BUILD_SHARED_LIBS:BOOL=ON
BUILD_SHARED_LIBS_WITH_STATIC_MONGOC:BOOL=OFF
BUILD_VERSION:STRING=0.0.0
Boost_INCLUDE_DIR:PATH=/usr/local/include
CMAKE_BUILD_TYPE:STRING=Release
CMAKE_INSTALL_PREFIX:PATH=/usr/local
ENABLE_CODE_COVERAGE:BOOL=OFF
ENABLE_TESTS:BOOL=ON
ENABLE_UNINSTALL:BOOL=ON
MONGOCXX_ENABLE_SLOW_TESTS:BOOL=OFF
MONGOCXX_ENABLE_SSL:BOOL=ON
MONGOCXX_OUTPUT_BASENAME:STRING=mongocxx
bson-1.0_DIR:PATH=/usr/local/lib/cmake/bson-1.0
mongoc-1.0_DIR:PATH=/usr/local/lib/cmake/mongoc-1.0

```bash
sudo cmake --build . --target install
```

### Check Mongo connection

make mongo

./mongoTester
{ "_id" : { "$oid" : "5f3a363dcc7eca47d43fd5f2" }, "hello" : "world" }

## Install dependencies for build and runtime

### Zlib

This library is necessary for message compression.

```bash
sudo apt install libzip-dev
```

### Boost

```bash
curl -OL https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz
tar -xzf boost_1_74_0.tar.gz
cd boost_1_74_0
./bootstrap.sh # this will generate ./b2
# get the no of cpucores to make faster
cpuCores=`cat /proc/cpuinfo | grep "cpu cores" | uniq | awk '{print $NF}'`
echo "Available CPU cores: "$cpuCores
sudo ./b2 --with=atomic,date_time,exception,filesystem,iostreams,locale,program_options,regex,signals,system,test,thread,timer,log -j $cpuCores install
# check the version number of your installed lib
cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
```

### SQLite3

```bash
unzip tar xvf proj-9.3.0.tar.gz
cd sqlite-src-3390000
./configure
cmake -DSQLITE3_INCLUDE_DIR=/usr/local/include -DSQLITE3_LIBRARY=/usr/local/lib/libsqlite3.so ..
cmake --build .
sudo cmake --build . --target install

```

### Proj.4

On Ubuntu Xenial 18.04

```bash
sudo apt-get install libproj-dev
```

Update Jammy 22.04

Build from source

Dependency with TIFF library :

```bash
sudo apt install libtiff-dev:i386
sudo apt install libtiff-dev
```

```bash
wget https://download.osgeo.org/proj/proj-9.3.0.tar.gz
tar xvf proj-9.3.0.tar.gz
cd proj-9.3.0/
mkdir build && cd build
cmake -DSQLITE3_INCLUDE_DIR=/usr/local/include -DSQLITE3_LIBRARY=/usr/local/lib/libsqlite3.so ..
cmake --build .
sudo cmake --build . --target install
```

### GDAL

Build from source (dependency with SQLite3 & Proj.4)

```bash
cd master-gdal/
mkdir build && cd build
cmake -DSQLITE3_INCLUDE_DIR=/usr/local/include -DSQLITE3_LIBRARY=/usr/local/lib/libsqlite3.so ..
cmake --build .
sudo cmake --build . --target install
sudo ldconfig
```
