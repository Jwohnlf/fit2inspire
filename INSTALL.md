# INSTALLATION GUIDE

## Prerequesites

-- Linux platform (tested on Ubuntu Xenial 16.04)
-- A compiler that supports C++11 (tested with gcc 5.4.0)
-- CMake 3.18.1 or later

## Install dependencies before building gSOAP

### Flex

```bash
wget <http://ftp.gnu.org/gnu/bison/bison-2.3.tar.gz>
tar -xvzf bison-2.3.tar.gz
cd  bison-2.3/
./configure --with-libiconv-prefix=/usr/local/libiconv/
make
sudo make install
```

### Bison

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
-- Build files have been written to: /home/jeanloup/setup/mongo-cxx-driver-r3.6.0/build

```bash
sudo cmake --build . --target EP_mnmlstc_core
sudo cmake --build . --target install
```

Log copied in Mongo-CXX-INSTALL.log

### Check Mongo connection

make mongo

./mongoTester
{ "_id" : { "$oid" : "5f3a363dcc7eca47d43fd5f2" }, "hello" : "world" }
