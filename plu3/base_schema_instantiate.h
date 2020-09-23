/*  base_schema_instantiate.h
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#ifndef BASE_SCHEMA_INSTANTIATE_H
#define BASE_SCHEMA_INSTANTIATE_H

#include "src/pluH.h"
#include <time.h>
#include <bsoncxx/oid.hpp>

using namespace std;
using namespace plu;
using bsoncxx::oid;

base__IdentifierPropertyType *init_base_Identifier(soap *soap, string sid, oid lid, string ns);

#endif // BASE_SCHEMA_INSTANTIATE_H
