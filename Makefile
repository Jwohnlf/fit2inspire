test : wfsTester
	./wfsTester < wfs2/src/wfs.getCapabilities.req.xml

mongo : mongoTester
	./mongoTester

capa : capaWfsMongo
	./capaWfsMongo 8090 &

debug : debug_capaWfsMongo

GSOAP=soapcpp2
CPP=g++
SOAPCPP=/home/jeanloup/appli/gsoap-2.8/gsoap/stdsoap2.cpp
LIBS=-lgsoap++ -lpthread -lz -lssl -lcrypto
LIBW=-lmongocxx -lbsoncxx

COFLAGS=-O2
CWFLAGS=-std=c++11 -Wno-deprecated-declarations
MONGO = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi -I/home/jeanloup/appli/boost_1_58_0
CIFLAGS=-I/usr/local/share/gsoap -I/usr/local/share/gsoap/plugin $(MONGO)
CMFLAGS=-DWITH_COOKIES -DWITH_GZIP -DWITH_OPENSSL
CFLAGS= $(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)

capaWfsMongo : soapC.o soapServer.o logging.o get.o smdevp.o md5evp.o httpda.o threads.o options.o ows_schema_instantiate.o wfs_getcapabilities.o webserver.c
	$(CPP) webserver.c $(CFLAGS) logging.o get.o smdevp.o httpda.o md5evp.o threads.o options.o soapServer.o soapC.o ows_schema_instantiate.o wfs_getcapabilities.o $(SOAPCPP) $(LIBW) $(LIBS) -o capaWfsMongo

debug_capaWfsMongo : soapC.o soapServer.o logging.o get.o smdevp.o md5evp.o httpda.o threads.o options.o ows_schema_instantiate.o dwfs_getcapabilities.o webserver.c
	$(CPP) webserver.c -DDEBUG -DSOAP_MEM_DEBUG $(CFLAGS) logging.o get.o smdevp.o httpda.o md5evp.o threads.o options.o soapServer.o soapC.o ows_schema_instantiate.o dwfs_getcapabilities.o $(SOAPCPP) $(LIBW) $(LIBS) -o debug_capaWfsMongo

mongoTester : mongo-cxx-test.cpp
	$(CPP) $(CFLAGS) mongo-cxx-test.cpp \
	-I/usr/local/include/mongocxx/v_noabi \
	-I/usr/local/include/bsoncxx/v_noabi \
	-L/usr/local/lib -lmongocxx -lbsoncxx \
	-o mongoTester 

wfsTester : soapC.o soapServer.o wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) wfs2/src/soapTester.cpp soapC.o soapServer.o \
	$(LIBS) -o wfsTester

options.o:	webserver/opt.h webserver/options.h webserver/options.c
	$(GSOAP) -cnpopt -d webserver webserver/opt.h
	$(CPP) $(CFLAGS) -c webserver/options.c

logging.o:	/usr/local/share/gsoap/plugin/logging.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/logging.c

httpda.o:	/usr/local/share/gsoap/plugin/httpda.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/httpda.c
	
smdevp.o:	/usr/local/share/gsoap/plugin/smdevp.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/smdevp.c

md5evp.o:	/usr/local/share/gsoap/plugin/md5evp.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/md5evp.c
	
threads.o:	/usr/local/share/gsoap/plugin/threads.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/threads.c

get.o : /usr/local/share/gsoap/plugin/httpget.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/httpget.c -o get.o

dwfs_getcapabilities.o : wfs_getcapabilities.cpp
	$(CPP) -g $(CFLAGS) -c wfs_getcapabilities.cpp -o dwfs_getcapabilities.o

wfs_getcapabilities.o : wfs_getcapabilities.cpp
	$(CPP) $(CFLAGS) -c wfs_getcapabilities.cpp -o wfs_getcapabilities.o

ows_schema_instantiate.o : wfs2/ows_schema_instantiate.cpp
	$(CPP) $(CFLAGS) -c wfs2/ows_schema_instantiate.cpp -o ows_schema_instantiate.o

soapTester.o : wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapTester.cpp -o soapTester.o

soapServer.o : wfs2/src/soapServer.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapServer.cpp -o soapServer.o

soapC.o : wfs2/src/soapC.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapC.cpp -o soapC.o