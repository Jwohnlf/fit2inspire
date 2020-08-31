/*  ows_schema_instantiate.cpp
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu
*/

#include "ows_schema_instantiate.h"


ows__LanguageStringType * init_ows_LangString(struct soap *soap, string lang, string keyword)
{
    ows__LanguageStringType * pLangStr = NULL;

    pLangStr = soap_new_ows__LanguageStringType(soap,-1);
    pLangStr->__item.append(keyword);
    pLangStr->xml__lang = (char**)soap_malloc(soap, sizeof(char**));
    *(pLangStr->xml__lang) = (char*)soap_malloc(soap, lang.length()+1);
    strcpy(*(pLangStr->xml__lang), lang.c_str());

    return pLangStr;
}

//boost::optional<bsoncxx::document::view_or_value>
ows__DomainType * init_ows_Domain( struct soap *soap, element el )
{
    //el is formatted "name":["val1","val2"...]
    ows__DomainType* pdom = soap_new_ows__DomainType(soap);
    ows__ValueType *pval;

    pdom->name.append((string) el.key());
    pdom->__union_UnNamedDomainType = 1;

    if (el.type() == bsoncxx::type::k_array) {
        auto vbval = el.get_array().value;
        pdom->union_UnNamedDomainType.AllowedValues = soap_new__ows__AllowedValues(soap);
        //pdom->union_UnNamedDomainType.AllowedValues->__size_AllowedValues = el.length();
        //pdom->union_UnNamedDomainType.AllowedValues->__union_AllowedValues = soap_new___ows__union_AllowedValues(soap, el.length());

        for(auto element : vbval ) {
            pval = soap_new_ows__ValueType(soap);
            pval->__item.assign((string) element.get_utf8().value );
            //(pdom->union_UnNamedDomainType.AllowedValues->__union_AllowedValues+i)->__union_AllowedValues = 1;
            //(pdom->union_UnNamedDomainType.AllowedValues->__union_AllowedValues+i)->union_AllowedValues.Value = pval;

            __ows__union_AllowedValues AllowedValue = __ows__union_AllowedValues();
            AllowedValue.__union_AllowedValues = 1;
            AllowedValue.union_AllowedValues.Value = pval;            
            pdom->union_UnNamedDomainType.AllowedValues->__union_AllowedValues.insert(
                pdom->union_UnNamedDomainType.AllowedValues->__union_AllowedValues.begin(), 
                AllowedValue);
        }
    }

    return pdom;
}

/*
int ows_getWgs84Bbox(struct soap *soap, document o, double bbox[])
{
    element begeo;
    string coord;
    double x = 0.0, y = 0.0;
    int ngeom = 0;
    char s[15];

    if(o.hasField("ngeom") && o.hasField("gtype")) {
        ngeom = o.getIntField("ngeom");

        coord = o.getStringField("gtype");
        if(coord.find("Polygon") != string::npos)
        {
            for(int i=0; i<ngeom; i++)
            {
                sprintf(s,"coordinates%d",i);
                begeo = o.getField(s);
                if(begeo.eoo()) {
                    fprintf(stderr, "updateBbox : Missing or corrupted DB geomery element\n");
                    soap->error = SOAP_NULL;
                    return -1;
                }

                // Récupération des coordonnées de l'enveloppe extérieure dans un tableau
                if (begeo.type() != 4){
                    fprintf(stderr, "updateBbox : Missing or corrupted DB geometry element\n");
                    soap->error = SOAP_NULL;
                    return -1;
                }
                std::vector<BSONElement> vecbe, b1;
                vecbe = begeo.Array();

                //on prend le premier element correspondant à l'enveloppe extérieure
                b1 = vecbe[0].Array();

                for (unsigned int j = 0; j< b1.size(); j++)
                {
                    coord = b1[j].toString(false);
                    sscanf(coord.substr(2,coord.length()-9).c_str(),"%lf, %lf,", &x, &y);

                    if(x - bbox[2] > 0.000000001)
                        bbox[2] = x;
                    else if(x - bbox[0] < 0.000000001)
                        bbox[0] = x;

                    if(y - bbox[3] > 0.000000001)
                        bbox[3] = y;
                    else if(y - bbox[1] < 0.000000001)
                        bbox[1] = y;

                }//for j

            }//for i
        }// if
    }// if

    //cout << "test d'application soap.user : " << soap->user;

    return 0;
}
*/
