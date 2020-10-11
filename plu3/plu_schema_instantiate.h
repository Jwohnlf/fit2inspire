/*  plu_schema_instantiate.h
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#ifndef PLU_SCHEMA_INSTANTIATE_H
#define PLU_SCHEMA_INSTANTIATE_H

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

plu__SpatialPlanPropertyType * init_plu_SpatialPlan(struct soap *soap, view_or_value p, int outcrs, double bbox[]);

plu__ZoningElementPropertyType * init_plu_ZoningElement(struct soap *soap, view_or_value o, int outcrs, double bbox[]);

plu__OfficialDocumentationPropertyType * init_plu_OfficialDocumentation(soap *soap, oid lid, view_or_value d, string identifier);

plu__SupplementaryRegulationPropertyType * init_plu_SupplementaryRegulation(soap *soap, view_or_value o, int outcrs, double bbox[]);

#endif // PLU_SCHEMA_INSTANTIATE_H
