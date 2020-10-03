# Generation of serializers for WFS2 webservice

This section explains how to generate the C++ serializers classes for implementing webservice interfaces according the standard of Web Feature Service version 2.

The implementation starts with a generic webservice description WSDL downloaded from <http://schemas.opengis.net/wfs/2.0/wsdl/>.

## SETUP

1. Tune the default WSDL file with the specific requirement of INSPIRE directive

2. Get the following imported schema.
    - base2.xsd
    - LandUseNomenclature.xsd

Some useless dependencies with other schema such as Addresses, Base, Gml, GmlCov have been removed.

Each modified XSD file is added to this repo. They are the inputs for code generation.

The gSoap configuration file typemap.dat must be completed of every namespaces your XSD are using.
By adding this section in the condig file, gSoap generates code using correct namespaces and prefixes.

plu = "http://inspire.ec.europa.eu/schemas/plu/3.0"

...

## CODE GENERATION

Create a directory for generated files

`$ mkdir src`

Parse the input WSDL files

`$ wsdl2h -m -g -_ -t ../typemap.dat ws-inspire-wfs2.wsdl -o ws-inspire-wfs2.h 2> inspire-wfs2h.log`

Generate CPP source code

`$ soapcpp2 -T -d src -I /usr/local/share/gsoap/import/ ws-inspire-wfs2.h 2> src/1compile.log`

Fix the warnings issued in the log file by modifying the ws-inspire-wfs2.h

`$ vi src/1compil.log`

Launch soapcpp2 command again

`$ soapcpp2 -d src -I /usr/local/share/gsoap:/usr/local/share/gsoap/import PlannedLandUse_v3.0.h 2> src/fcompile.log`

Check that every warnings have been solved in fcompile.log file
Done !

# BUILD STANDALONE WFS SERVER

First load into Mongo 3.6 the document containing the server capaibilities

`$ mongoimport -d plu -c server data/plu__server_capabilities.json`

Build and run the server building using the available Makefile

`$ make capa`