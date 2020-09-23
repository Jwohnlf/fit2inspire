/*  ows_schema_instantiate.h
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/

#ifndef OWS_SCHEMA_INSTANTIATE_H
#define OWS_SCHEMA_INSTANTIATE_H

#include <iomanip>
#include <sstream>

#include <bsoncxx/document/element.hpp>
#include <bsoncxx/types.hpp>

#include "src/soapH.h"

using namespace std;
using bsoncxx::document::element;

ows__LanguageStringType * init_ows_LangString(struct soap *soap, string lang, string keyword);

ows__DomainType * init_ows_Domain(struct soap *soap, element el);


#endif // OWS_SCHEMA_INSTANTIATE_H
