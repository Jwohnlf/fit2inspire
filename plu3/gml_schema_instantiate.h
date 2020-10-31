/*  gml_schema_instantiate.h
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#ifndef GML_SCHEMA_INSTANTIATE_H
#define GML_SCHEMA_INSTANTIATE_H

#include <iomanip>
#include <sstream>
#include "src/pluH.h"
#include <mongocxx/client.hpp> // the mongo c++ driver
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/oid.hpp>
#include <bsoncxx/document/element.hpp>
#include <mongocxx/cursor.hpp>
#include <ogr_spatialref.h>

using namespace std;
using bsoncxx::builder::stream::document;
using bsoncxx::oid;
using bsoncxx::document::element;
using bsoncxx::document::view_or_value;
using bsoncxx::builder::basic::array;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::make_document;
using namespace plu;

int http_fget_error(struct soap *soap, const char* exceptionCode, string exceptionText, string locator, int status);

gml__ReferenceType * init_gml_ReferenceType(struct soap *soap, mongocxx::stdx::string_view val, string uri);

gml__PolygonType * init_gml_PolygonType(struct soap *soap, element belem, double bbox[], int outcrs);

gml__MultiSurfacePropertyType * init_gml_MultiSurfacePropertyType(struct soap *soap, view_or_value bgeom, int outcrs, double bbox[]);

gml__MultiSurfaceType * init_gml_MultiSurfaceType(struct soap *soap, view_or_value bgeom, int outcrs, double bbox[]);

gml__LineStringType * init_gml_LineStringType(struct soap *soap, element belem, int outcrs, double bbox[]);

gml__DirectPositionListType * init_gml__DirectPositionListType(struct soap *soap, element belem, int outcrs, double bbox[]);

gml__DirectPositionType * init_gml__DirectPositionType(struct soap *soap, element belem, int outcrs, double bbox[]);

gml__PointType * init_gml_PointType(struct soap *soap, element belem, int outcrs, double bbox[]);

char* init_gml_id(struct soap *soap, string strval, oid lid);

#endif // GML_SCHEMA_INSTANTIATE_H
