/* base_schema_instantiate.cpp
   Generated for fit2inspire.eu service implementation

   Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

   This code is released under the following license:
   1) GPL
*/

#include "base_schema_instantiate.h"


base__IdentifierPropertyType *init_base_Identifier(soap *soap, string sid, oid lid, string ns)
{
    base__IdentifierPropertyType * pinspireId = soap_new_base__IdentifierPropertyType(soap);
    if(!pinspireId){
        fprintf(stderr, "Allocation of base__IdentifierPropertyType pointer failed\n");
        soap->error = SOAP_FAULT;
        return NULL;
    }

    pinspireId->Identifier = soap_new_base__IdentifierType(soap);    
    pinspireId->Identifier->localId.append(sid);
    
    if(pinspireId->Identifier->versionId = soap_new__base__IdentifierType_versionId(soap))
    {
        pinspireId->Identifier->versionId->__item.append(/*dateToISOStringUTC(*/lid.to_string());
        pinspireId->Identifier->namespace_ = ns;
    } // endif
    
    return pinspireId;
}
