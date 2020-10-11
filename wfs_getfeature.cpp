/*  wfs_getfeature.cpp
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#include <ctime>
#include "wfs_getfeature.h"
#include "plu3/plu_schema_instantiate.h"


/* 
    fgetfeature : prepare WFS download after a get call 
    This function initializes a wfs__FetFeatureClass according to query arguments 
    received from a dynamic HTTP GET application/x-www-form-urlencoded request
*/
int fgetfeature(struct soap *soap, string inputId, string srs, string typeNames, string BBox)
{
    wfs__GetFeatureType *getFeature;

    getFeature = soap_new_wfs__GetFeatureType(soap);
    
    try {
        stringstream e;

        // Stored query GetFeatureById query in ?id=input
        if (!inputId.empty())
        {
            wfs__StoredQueryType *storedQuery = storedQuery = soap_new_wfs__StoredQueryType(soap);

            //Parse inputid to retrieve information needed to query the DB
            cout << "Stored query request received" << endl;
            getFeature->version.assign("2.0.0");
            getFeature->__union_GetFeatureType = soap_new___wfs__union_GetFeatureType(soap);
            getFeature->__union_GetFeatureType->__unionAbstractQueryExpression = SOAP_UNION__wfs__union_GetFeatureType_StoredQuery;
            
            if(inputId.find("getspatialplanbyid") != string::npos)
            {
                wfs__ParameterType* paramStoredQuery = soap_new_wfs__ParameterType(soap);

                storedQuery->id = (char*)soap_malloc(soap, 20); 
                strcpy(storedQuery->id, "getspatialplanbyid");
                string doc_urba = inputId.substr(inputId.find_first_of(",")+1);
                doc_urba = doc_urba.substr(0,13);
                doc_urba.insert(5,"_");

                paramStoredQuery->name.assign("spatialplanid");
                paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.length()+1);
                strcpy(paramStoredQuery->__any, doc_urba.c_str());

                storedQuery->Parameter.insert( storedQuery->Parameter.begin(), paramStoredQuery);
            }
            else if (inputId.find("getfeaturebyid") != string::npos)
            {
                storedQuery->id = (char*)soap_malloc(soap, 15); 
                strcpy(storedQuery->id, "getfeaturebyid");
                inputId = inputId.substr(inputId.find_first_of(",")+1);
                string doc_urba = inputId.substr(0,13);
                string gid = inputId.substr(doc_urba.length());
                gid = gid.substr(0, gid.length()-16);
                doc_urba.insert(5,"_");
            
                if( (gid.empty() || gid.find("doc")!=std::string::npos) && !doc_urba.empty() ) 
                {
                    wfs__ParameterType* paramStoredQuery = soap_new_wfs__ParameterType(soap);

                    paramStoredQuery->name.assign("gid_urba");
                    paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.length()+1);
                    strcpy(paramStoredQuery->__any, doc_urba.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.begin(), paramStoredQuery);
                }
                else if(!gid.empty() && !doc_urba.empty())
                {
                    wfs__ParameterType* paramStoredQuery = soap_new_wfs__ParameterType(soap, 2);

                    paramStoredQuery->name.assign("gid_urba");
                    paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.length()+1);
                    strcpy(paramStoredQuery->__any, doc_urba.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.begin(), paramStoredQuery);

                    paramStoredQuery->name.assign("gid");
                    paramStoredQuery->__any = (char*)soap_malloc(soap, gid.length()+1);
                    strcpy(paramStoredQuery->__any, gid.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.end(), paramStoredQuery);
                }
            } // else getfeaturebyid
            else {
                e << "The requested stored query is not supported by this stored query";
                return http_fget_error(soap, "InvalidParameterValue", e.str(), "StoredQuery_Id", 400);
            }
            
        }

        wfs__FeatureCollectionType featureCollection;
        __f2i_plu__wfs_x002egetFeature(soap, getFeature, featureCollection);
    
        soap->http_content = "text/xml";
        soap_response(soap, SOAP_FILE);
        featureCollection.soap_put(soap, "wfs:FeatureCollection", "");
        soap_end_send(soap);

        return SOAP_OK;
    }//try
    catch( exception e ) {
        return http_fget_error(soap, "OperationProcessingFailed", e.what(), "DBException" , 400);
    }    

} // end fonction fgetfeature


/** Auto-test server operation __f2i_plu__wfs_x002egetFeature */
int __f2i_plu__wfs_x002egetFeature(struct soap *soap, wfs__GetFeatureType *wfs__GetFeature, wfs__FeatureCollectionType &wfs__FeatureCollection)
{
	//(void)soap; /* appease -Wall -Werror */

    //auto_ptr<DBClientCursor> cursor_sp, cursor_ze, cursor_sr;
    //wfs__FeatureCollectionType *wfs__FeatureCollection;
    double bbox[4];
    double minLat = 0.0, minLon = 0.0, maxLat = 0.0, maxLon = 0.0;

    int i = 0;
    int outcrs = 0; 

    try {        
        stringstream e;
        string doc_urba, gid;
        bool adhocquery = true;
        mongocxx::uri mongo("mongodb://localhost:27017");
        mongocxx::client client{mongo};

        //c.connect("localhost");
        mongocxx::database db = client["plu"];
        mongocxx::collection collsp = db["demosp"];        

        //auto_ptr<mongocxx::cursor> cursor_sp; //, cursor_ze, cursor_sr;
        bsoncxx::builder::stream::document query_sp {};
        bsoncxx::builder::stream::document query_ze {};
        
        // TODO : make an index with a unique key constraint

        // TODO : make an geospatial index for each queryable collections

        // Stored query GetFeatureById query in ?id=input
        if (wfs__GetFeature->__union_GetFeatureType->__unionAbstractQueryExpression == SOAP_UNION__wfs__union_GetFeatureType_StoredQuery)
        {
            adhocquery = false;
            //Parse inputid to retrieve information needed to query the DB
            if(!wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->handle->compare("getspatialplanbyid"))
            {
                doc_urba.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[0]->__any);                
                query_sp << "gid" << doc_urba << bsoncxx::builder::stream::finalize;
                query_ze << "gid_urba" << doc_urba << bsoncxx::builder::stream::finalize;
            }
            else if (!wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->handle->compare("getfeaturebyid"))
            {
                if (wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter.size() == 1) {
                    doc_urba.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[0]->__any);                
                    query_sp << "gid" << doc_urba << bsoncxx::builder::stream::finalize;
                }
                
                if (wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter.size() == 2) {
                    doc_urba.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[0]->__any);                
                    gid.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[1]->__any);                
                    query_ze << "gid_urba" << doc_urba << "gid" << gid << bsoncxx::builder::stream::finalize;
                }                
            }// else getfeaturebyid
            else {
                e << "The requested stored query is not supported by this stored query";
                return http_fget_error(soap, "InvalidParameterValue", e.str(), "StoredQuery_Id", 400);
            }
        }

        auto cursor_sp = collsp.find( query_sp.extract() );
        
        /* Init of a pointer used to answer the request */
        vector<wfs__MemberPropertyType*> *pwfsm;
        if(!(pwfsm = soap_new_std__vectorTemplateOfPointerTowfs__MemberPropertyType(soap, -1))){
            e << "Error nb " << soap->error;
            return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing MemberProperty object" , 400);
        }

        i = 0;

        wfs__MemberPropertyType *member = NULL;
        wfs__MemberPropertyType *document = NULL;
        for (auto plu : cursor_sp) {
            i++;
            cout << "A plu found : " << i << endl;

            //binding plu sequence to wfs member type
            if( gid.empty() ) {
                member = (wfs__MemberPropertyType *) init_plu_SpatialPlan(soap, plu, outcrs, bbox);
                if(!member)
                {
                    e << "Error nb " << soap->error;
                    //return soap_receiver_fault(soap, "Internal server error initializing SpatialPlan Object", e.str().c_str());
                    return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing SpatialPlan object" , 400);
                }

                pwfsm->insert(pwfsm->end(),member);
            }

            /* Let include in the response the associated OfficialDocumentation
                   case 1 : it's an ad hoc query (all official documents are included by default)
                   case 2 : it's an GetFeatureById query with an ID of an official document as parameter
                   case 3 : it's an GetSpatialPlanById query (all official documents are included by default)
            */
            if( ( plu["officialdocument"] && adhocquery ) ||
                ( plu["officialdocument"] && !gid.empty() ) ||
                ( plu["officialdocument"] && !wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->handle->compare("getfeaturebyid")) )
            {
                if(plu["officialdocument"].type() == bsoncxx::type::k_array) {
                    // get all documents associated to this Spatial Plan
                    auto docArray = plu["officialdocument"].get_array().value;

                    int j = 0;
                    int maxDoc = std::distance(docArray.begin(), docArray.end());
                    while ( j <  maxDoc)
                    {
                        // get each official document associated to this SpatialPlan
                        stringstream identifier;
                        char n[8];
                        //BSONElement elem;
                        //p.getObjectID(elem);
                        oid lid;
                        lid = plu["_id"].get_oid().value;

                        if(plu["gid"])
                        {
                            mongocxx::stdx::string_view strview = plu["gid"].get_utf8().value;
                            identifier <<  strview.to_string();
                            identifier << "_";
                        }
                        identifier << "doc" << j;

                        if(gid.empty() || gid.find(n)!=std::string::npos)
                        {
                            auto doc = docArray[j].get_document();
                            document = (wfs__MemberPropertyType *) init_plu_OfficialDocumentation(soap, lid, doc.view(), identifier.str());
                            pwfsm->insert(pwfsm->end(), document);
                        }
                        j++;

                    } //while
                }
            }
        }// for cursor


        mongocxx::collection collze = db["demoze"];
        auto cursor_ze = collze.find( query_ze.extract() );

        for (auto ze : cursor_ze) {            

            //binding zoningElement sequence to wfs member type
            member = (wfs__MemberPropertyType *) init_plu_ZoningElement(soap, ze, outcrs, bbox);
            if(!member)
            {
                e << "Error nb " << soap->error;
                return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing ZoningElement object" , 400);
            }

            pwfsm->insert(pwfsm->end(), member);
            i++;
        } //end for cursor_ze

        //adding attributes to FeatureCollection
        wfs__FeatureCollection.numberReturned = i;
        e.flush();
        e << i;
        wfs__FeatureCollection.numberMatched = e.str();
        wfs__FeatureCollection.timeStamp = time(0);
        
        //binding wfs member type to wfs return type
        wfs__FeatureCollection.member = *pwfsm;
        
    }//try
    catch( exception e ) {
        return http_fget_error(soap, "OperationProcessingFailed", e.what(), "DBException" , 400);
    }

	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}

