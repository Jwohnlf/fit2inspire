test : wfsTester


GSOAP=soapcpp2
CPP=g++
LIBS=-lgsoap++

COFLAGS=-O2
CWFLAGS=-std=c++11 -Wno-deprecated-declarations
CFLAGS= $(CWFLAGS) $(COFLAGS) 

wfsTester : soapC.o soapServer.o wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) wfs2/src/soapTester.cpp soapC.o soapServer.o $(LIBS) -o wfsTester


soapTester.o : wfs2/src/soapTester.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapTester.cpp -o soapTester.o

soapServer.o : wfs2/src/soapServer.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapServer.cpp -o soapServer.o

soapC.o : wfs2/src/soapC.cpp
	$(CPP) $(CFLAGS) -c wfs2/src/soapC.cpp -o soapC.o

