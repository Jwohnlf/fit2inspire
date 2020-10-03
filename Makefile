test : wfsTester
	./wfsTester < wfs2/src/wfs.getCapabilities.req.xml 

plu3 : plu3WfsMongo
	./plu3WfsMongo 8090 &

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

plu3WfsMongo : soapC.o pluC.o soapServer.o logging.o get.o smdevp.o md5evp.o httpda.o threads.o options.o ows_si.o base_si.o gml_si.o plu_si.o wfs_getcapabilities.o wfs_getfeature.o webserver.c
	$(CPP) webserver.c $(CFLAGS) logging.o get.o smdevp.o httpda.o md5evp.o threads.o options.o soapC.o pluC.o soapServer.o ows_si.o base_si.o gml_si.o plu_si.o wfs_getcapabilities.o wfs_getfeature.o $(SOAPCPP) $(LIBW) $(LIBS) -o plu3WfsMongo

debug_plu3WfsMongo : soapC.o pluC.o soapServer.o logging.o get.o smdevp.o md5evp.o httpda.o threads.o options.o ows_si.o dgml_si.o dplu_si.o dwfs_getcapabilities.o dwfs_getfeature.o webserver.c
	$(CPP) webserver.c -DDEBUG -DSOAP_MEM_DEBUG $(CFLAGS) logging.o get.o smdevp.o httpda.o md5evp.o threads.o options.o soapC.o pluC.o soapServer.o ows_si.o gml_si.o dplu_si.o dwfs_getcapabilities.o dwfs_getfeature.o $(SOAPCPP) $(LIBW) $(LIBS) -o debug_plu3WfsMongo

wfsTester : soapC.o soapServer.o wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) wfs2/src/soapTester.cpp soapC.o soapServer.o $(LIBS) -o wfsTester

options.o:	webserver/opt.h webserver/options.h webserver/options.c
	$(GSOAP) -cnpopt -d webserver webserver/opt.h
	$(CPP) $(CFLAGS) -c webserver/options.c -o .obj/options.o

logging.o:	/usr/local/share/gsoap/plugin/logging.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/logging.c -o .obj/logging.o

httpda.o:	/usr/local/share/gsoap/plugin/httpda.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/httpda.c -o .obj/httpda.o
	
smdevp.o:	/usr/local/share/gsoap/plugin/smdevp.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/smdevp.c -o .obj/smdevp.o

md5evp.o:	/usr/local/share/gsoap/plugin/md5evp.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/md5evp.c -o .obj/md5evp.o
	
threads.o:	/usr/local/share/gsoap/plugin/threads.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/threads.c -o .obj/threads.o

get.o : /usr/local/share/gsoap/plugin/httpget.c
	$(CPP) $(CFLAGS) -c /usr/local/share/gsoap/plugin/httpget.c -o .obj/get.o

dwfs_getcapabilities.o : wfs_getcapabilities.cpp
	$(CPP) -g $(CFLAGS) -c wfs_getcapabilities.cpp -o .obj/dwfs_getcapabilities.o

wfs_getcapabilities.o : wfs_getcapabilities.cpp
	$(CPP) $(CFLAGS) -c wfs_getcapabilities.cpp -o .obj/wfs_getcapabilities.o

dwfs_getfeature.o : wfs_getfeature.cpp
	$(CPP) -g $(CFLAGS) -c wfs_getfeature.cpp -o .obj/dwfs_getfeature.o

wfs_getfeature.o : wfs_getfeature.cpp
	$(CPP) $(CFLAGS) -c wfs_getfeature.cpp -o .obj/wfs_getfeature.o

ows_si.o : wfs2/ows_schema_instantiate.cpp
	$(CPP) $(CFLAGS) -c wfs2/ows_schema_instantiate.cpp -o .obj/ows_si.o

plu_si.o : plu3/plu_schema_instantiate.cpp
	$(CPP) $(CFLAGS) -c plu3/plu_schema_instantiate.cpp -o .obj/plu_si.o

base_si.o : plu3/base_schema_instantiate.cpp
	$(CPP) -c $(CFLAGS) plu3/base_schema_instantiate.cpp -o .obj/base_si.o

dgml_si.o : plu3/gml_schema_instantiate.cpp
	$(CPP) -c -g $(CFLAGS) plu3/gml_schema_instantiate.cpp -o .obj/dgml_si.o

gml_si.o : plu3/gml_schema_instantiate.cpp
	$(CPP) -c $(CFLAGS) plu3/gml_schema_instantiate.cpp -o .obj/gml_si.o

soapTester.o : wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapTester.cpp -o .obj/soapTester.o

soapServer.o : wfs2/src/soapServer.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapServer.cpp -o .obj/soapServer.o

soapC.o : wfs2/src/soapC.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapC.cpp -o .obj/soapC.o

pluC.o : plu3/src/pluC.cpp
	$(CPP) $(CFLAGS) -c plu3/src/pluC.cpp -o .obj/pluC.o