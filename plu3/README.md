# Generation of serializers for INSPIRE Planned Land Use application schema

This section explains how to generate the C++ serializers classes for the XSD application schema defined by the Planned Land Use theme (link below).

## SETUP

1. Download the Inspire schema to implement : the official GML INSPIRE Planned Land Use application schema v3.0 is saved in the file PlannedLandUse_v3.0_origin.xsd.

2. Get the following imported schema.
    - base2.xsd
    - LandUseNomenclature.xsd

Some useless dependencies with other schema such as Addresses, Base, Gml, GmlCov have been removed.

Each modified XSD file is added to this repo. They are the inputs for code generation.

The gSoap configuration file typemap.dat must be completed of every namespaces your XSD are using.
By adding this section in the condig file, gSoap generates code using correct namespaces and prefixes.

plu = "http://inspire.ec.europa.eu/schemas/plu/3.0"

base = "http://inspire.ec.europa.eu/schemas/base/3.3"

base2 = "http://inspire.ec.europa.eu/schemas/base2/1.0"

lunom = "http://inspire.ec.europa.eu/schemas/lunom/3.0"

sc = "http://www.interactive-instruments.de/ShapeChange/AppInfo"

gml = "http://www.opengis.net/gml/3.2"

gmd = "http://www.isotc211.org/2005/gmd"

gco = "http://www.isotc211.org/2005/gco"

gss = "http://www.isotc211.org/2005/gss"

gts = "http://www.isotc211.org/2005/gts"

gsr = "http://www.isotc211.org/2005/gsr"

## CODE GENERATION

Create a directory for generated files

`$ mkdir src`

Parse the input XSD files

`$ wsdl2h -m -x -qplu -_ -t../typemap.dat PlannedLandUse-v3.0.xsd 2> xsd_plu2h.log`

Generate CPP source code

`$ soapcpp2 -d src -I /usr/local/share/gsoap:/usr/local/share/gsoap/import PlannedLandUse_v3.0.h 2> src/1compile.log`

Fix the PlannedLandUse_v3.0.h by removing redundant lines indicated in the generated  log file

`$ vi src/1compil.log`

Launch soapcpp2 command again

`$ soapcpp2 -d src -I /usr/local/share/gsoap:/usr/local/share/gsoap/import PlannedLandUse_v3.0.h 2> src/fcompile.log`

Check that every warnings have been solved in fcompile.log file
Done !

## FIRST TEST

Build and run the first instance of the webservice in the top directory.

`$ make test`
