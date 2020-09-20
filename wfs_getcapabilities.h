/*  wfs_getcapabilities.h
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

*/

#ifndef WFS_GETCAPABILITIES_H
#define WFS_GETCAPABILITIES_H

#include "wfs2/src/soapH.h"
#include "wfs2/ows_schema_instantiate.h"
#include <mongocxx/client.hpp> // the mongo c++ driver
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/cursor.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/oid.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

using namespace std;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::oid;

int fgetcapabilities(struct soap *soap);

int http_fget_error(struct soap *soap, const char* exceptionCode, string exceptionText, string locator, int status);

int http_fget_ParseError(struct soap *soap, string function, string param);

#endif // WFS_GETCAPABILITIES_H
