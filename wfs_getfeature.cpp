/*  wfs_getfeature.cpp
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#include <ctime>
#include "wfs_getfeature.h"
#include "plu3/plu_schema_instantiate.h"
#include <ogr_spatialref.h>

/* 
    fgetfeature : prepare WFS download after a get call 
    This function initializes a wfs__GetFeatureClass according to query arguments 
    received from a dynamic HTTP GET application/x-www-form-urlencoded request
*/
int fgetfeature(struct soap *soap, string inputId, string srs, string typeNames, string BBox)
{
    wfs__GetFeatureType *getFeature;

    getFeature = soap_new_wfs__GetFeatureType(soap);
    
    try {
        stringstream e;
        int i = 0;        

        // Stored query GetFeatureById query in ?id=input
        if (!inputId.empty())
        {
            wfs__StoredQueryType *storedQuery = soap_new_wfs__StoredQueryType(soap);

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

                paramStoredQuery->name.assign("spatialplanid");
                paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.size()+1);
                strcpy(paramStoredQuery->__any, doc_urba.c_str());

                storedQuery->Parameter.insert( storedQuery->Parameter.begin(), paramStoredQuery);
            }
            else if (inputId.find("getfeaturebyid") != string::npos)
            {
                storedQuery->id = (char*)soap_malloc(soap, 15);
                strcpy(storedQuery->id, "getfeaturebyid");

                inputId = inputId.substr(inputId.find_first_of(",")+1);
                string doc_urba = inputId.substr(0,14);
                string gid = inputId.substr(doc_urba.size());
                //gid = gid.substr(0, gid.length()-16);
            
                if( (gid.empty() || gid.find("doc")!=std::string::npos) && !doc_urba.empty() ) 
                {
                    wfs__ParameterType* paramStoredQuery = soap_new_wfs__ParameterType(soap);

                    paramStoredQuery->name.assign("gid");
                    paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.size()+1);
                    strcpy(paramStoredQuery->__any, doc_urba.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.begin(), paramStoredQuery);
                }
                else if(!gid.empty() && !doc_urba.empty())
                {
                    wfs__ParameterType* paramStoredQuery = soap_new_wfs__ParameterType(soap, 2);

                    paramStoredQuery->name.assign("gid_urba");
                    paramStoredQuery->__any = (char*)soap_malloc(soap, doc_urba.size()+1);
                    strcpy(paramStoredQuery->__any, doc_urba.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.end(), paramStoredQuery);

                    (paramStoredQuery+1)->name.assign("gid");
                    (paramStoredQuery+1)->__any = (char*)soap_malloc(soap, gid.size()+1);
                    strcpy((paramStoredQuery+1)->__any, gid.c_str());

                    storedQuery->Parameter.insert( storedQuery->Parameter.end(), paramStoredQuery+1);
                }
            } // else getfeaturebyid
            else {
                e << "The requested stored query is not supported by this server";
                return http_fget_error(soap, "InvalidParameterValue", e.str(), "StoredQuery_Id", 400);
            }

            getFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery = storedQuery;
        }
        else
        {
            wfs__QueryType *pQuery = soap_new_wfs__QueryType(soap);

            //Parse inputid to retrieve information needed to query the DB
            cout << "Adhoc query request received" << endl;
            getFeature->version.assign("2.0.0");
            getFeature->__union_GetFeatureType = soap_new___wfs__union_GetFeatureType(soap);
            //Use SOAP_UNION__wfs__union_GetFeatureType_Query_ to indicate a KVP query
            getFeature->__union_GetFeatureType->__unionAbstractQueryExpression = SOAP_UNION__wfs__union_GetFeatureType_Query_;

            pQuery->srsName = (char**)soap_malloc(soap, sizeof(char**));
            *pQuery->srsName = (char*)soap_malloc(soap, srs.size()+1);
            strcpy(*pQuery->srsName, srs.c_str());

            pQuery->typeNames.append(typeNames);
            pQuery->union_AbstractAdhocQueryExpressionType_.Filter = soap_new_fes__FilterType(soap);            
            pQuery->union_AbstractAdhocQueryExpressionType_.Filter->union_FilterType.BBOX = soap_new_fes__BBOXType(soap);
            
            __fes__union_BBOXType bbox;
            fes__LiteralType* literal = soap_new_fes__LiteralType(soap);
            literal->__any = (char*)soap_malloc(soap, BBox.size()+1);
            strcpy(literal->__any, BBox.c_str());
            bbox.union_BBOXType.Literal = literal;

            pQuery->union_AbstractAdhocQueryExpressionType_.Filter->union_FilterType.BBOX->__union_BBOXType.insert(
                pQuery->union_AbstractAdhocQueryExpressionType_.Filter->union_FilterType.BBOX->__union_BBOXType.begin(), bbox);
            
            getFeature->__union_GetFeatureType->union_GetFeatureType.Query = pQuery;    
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


/** Server operation __f2i_plu__wfs_x002egetFeature */
int __f2i_plu__wfs_x002egetFeature(struct soap *soap, wfs__GetFeatureType *wfs__GetFeature, wfs__FeatureCollectionType &wfs__FeatureCollection)
{
    
    double bbox[4];
    double minLat = 0.0, minLon = 0.0, maxLat = 0.0, maxLon = 0.0;

    int i = 0;
    int outcrs = 0; 

    try {        
        stringstream e;
        string doc_urba, gid;
        bool adhocquery = true;
        int outcrs = 0;
        double bbox[4];
        double minLat = 0.0, minLon = 0.0, maxLat = 0.0, maxLon = 0.0;
        OGRSpatialReference oSourceSRS, oTargetSRS;
        OGRCoordinateTransformation *poCT;


        mongocxx::uri mongo("mongodb://localhost:27017");
        mongocxx::client client{mongo};

        mongocxx::database db = client["plu"];
        mongocxx::collection collsp = db["demosp"];        
        
        auto query_ze = bsoncxx::builder::stream::document{};
        auto query_sp = bsoncxx::builder::stream::document{};
        auto query_sr = bsoncxx::builder::stream::document{};
        
        // TODO : make an index with a unique key constraint

        // TODO : make an geospatial index for each queryable collections

        // Stored query GetFeatureById query in ?id=input
        if (wfs__GetFeature->__union_GetFeatureType->__unionAbstractQueryExpression == SOAP_UNION__wfs__union_GetFeatureType_StoredQuery)
        {
            adhocquery = false;

            //Features are returned using server default projection
            outcrs = 4326;

            //Parse inputid to retrieve information needed to query the DB
            boost::to_lower(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->id);
            if(strstr(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->id, "getspatialplanbyid") != NULL)
            {
                wfs__ParameterType* parameter = wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter.at(0);

                doc_urba.append(parameter->__any);
                query_sp << "gid" << doc_urba;
                query_ze << "gid_urba" << doc_urba;
            }
            else if (strstr(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->id, "getfeaturebyid") != NULL)
            {
                if (wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter.size() == 1) {
                    doc_urba.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[0]->__any);
                    query_sp << "gid" 
                             << doc_urba;
                }
                
                if (wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter.size() == 2) {
                    doc_urba.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[0]->__any);                
                    gid.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->Parameter[1]->__any);                
                    query_ze << "gid_urba" 
                             << doc_urba
                             << "gid" 
                             << gid;
                }                
            }// else getfeaturebyid
            else {
                e << "The requested stored query is not supported by this server";
                return http_fget_error(soap, "InvalidParameterValue", e.str(), "StoredQuery_Id", 400);
            }
        }
        else
        {
            adhocquery = true;
            // Ad hoc query
            string srs, typeNames;
            char bbox_srs[15];
            int epsgbbox = 0;

            //Parse srsName parameter (should be of type http://www.opengis.net/def/crs/[epsg|ogc]/0/{code})
            srs.append(*wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.Query->srsName);
            size_t pos = srs.find_last_of("/");
            if( pos == string::npos) {
                e << "The server failed in parsing srsName parameter";
                return http_fget_error(soap, "InvalidParameterValue", e.str().c_str(), "srsName", 500);
            }

            if( !sscanf(srs.substr(pos+1).c_str(),"%d", &outcrs) )
                return http_fget_ParseError(soap, "GetFeature", "srsName");

            //Test if the requested SRS is supported by the server
            //TODO : hardcoded for the demo. Parse capabilities document for dynamic testing
            if( !(outcrs == 4326 || outcrs == 2154 || outcrs == 4171) ){
                e << "The requested output projection is not currently supported by this server.";
                return http_fget_error(soap,"OptionNotSupported", e.str(), "srsName", 501);
            }

            cout << "Valid input EPSG : " << outcrs << endl;
            //query_sp->srsName = (char**)soap_malloc(soap, sizeof(char**));
            //*query_sp->srsName = (char*)soap_malloc(soap, sizeof("http://www.opengis.net/def/crs/epsg/0/")+sizeof(outcrs)+1);

            fes__BBOXType *BBox = wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.Query->union_AbstractAdhocQueryExpressionType_.Filter->union_FilterType.BBOX;
            //cout << "bbox received : " << BBox->__union_BBOXType.at(0).union_BBOXType.Literal->__any;
            
            if (wfs__GetFeature->__union_GetFeatureType->__unionAbstractQueryExpression == SOAP_UNION__wfs__union_GetFeatureType_Query )
            {
                // SOAP RPC XML query
                //struct soap *soap1 = soap_new1(SOAP_XML_INDENT);
                std::stringstream ss; //("<gml:Envelope><gml:lowerCorner>5.15 45.58</gml:lowerCorner><gml:upperCorner>5.21 45.68</gml:upperCorner></gml:Envelope>");
                ss << BBox->__union_BBOXType.at(0).union_BBOXType.Literal->__any;
                soap->is = &ss;
                gml__EnvelopeType *envl = soap_new_gml__EnvelopeType(soap, -1);
                if (soap_read_gml__EnvelopeType(soap, envl) != SOAP_OK)
                {
                    e << "The server failed in parsing bbox parameter";
                    soap_print_fault(soap, stderr);
                    cout << "parsing error :" << endl;
                    soap_print_fault_location(soap, stderr);
                    return http_fget_error(soap, "OperationParsingFailed", e.str().c_str(), "GetFeature", 500);
                }

                bbox[0] = envl->lowerCorner->__item.at(0);
                bbox[1] = envl->lowerCorner->__item.at(1);
                bbox[2] = envl->upperCorner->__item.at(0);
                bbox[3] = envl->upperCorner->__item.at(1);
            }
            else if (wfs__GetFeature->__union_GetFeatureType->__unionAbstractQueryExpression == SOAP_UNION__wfs__union_GetFeatureType_Query_ )
            {
                // GET KVP query

                //Parse WGS84BoundingBox of type "LatLC,LonLC,LatUC,LonUC"
                if( !sscanf(BBox->__union_BBOXType.at(0).union_BBOXType.Literal->__any, "%lf,%lf,%lf,%lf,urn:ogc:def:crs:%s", &minLon, &minLat, &maxLon, &maxLat, bbox_srs) ) {
                    e << "The server failed in parsing bbox parameter";
                    return http_fget_error(soap, "OperationParsingFailed", e.str().c_str(), "GetFeature", 500);
                }
            }
            
            sscanf(bbox_srs, "epsg::%d", &epsgbbox);

            //Test of the bbox srsid parameter, and transformation in WGS84 coordinates if relevant
            if ( epsgbbox == 4326 || epsgbbox == 4171 ) {
                // Données stockées dans le système de coordonnées géographiques LatLon, inversion des coordonnées
                double ftmp;
                ftmp = minLon;
                minLon = minLat;
                minLat = ftmp;
                ftmp = maxLon;
                maxLon = maxLat;
                maxLat = ftmp;
            }
            else if (epsgbbox != 0) {
                // different input projection, process transformation of BBOX parameter using GDAL in WGS84 geographic coordinates              
                oSourceSRS.importFromEPSGA(epsgbbox);
                oTargetSRS.importFromEPSG(4326);
                poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
                if(oSourceSRS.EPSGTreatsAsLatLong()) {
                    double ftmp;
                    ftmp = minLon;
                    minLon = minLat;
                    minLat = ftmp;
                    ftmp = maxLon;
                    maxLon = maxLat;
                    maxLat = ftmp;
                }
                if( poCT == NULL || !poCT->Transform( 1, &minLon, &minLat ) || !poCT->Transform( 1, &maxLon, &maxLat ) )
                {
                    e << "The server failed to reproject the BBOX parameter ";
                    poCT->~OGRCoordinateTransformation();
                    return http_fget_error(soap, "OperationProcessingFailed", e.str().c_str(), "GetFeature", 500);
                }
            } // end transformation bbox
            else
                return http_fget_ParseError(soap, "GetFeature", "BBox");

            bbox[0] = minLon;
            bbox[1] = minLat;
            bbox[2] = maxLon;
            bbox[3] = maxLat;

            cout << "Input bbox_ : minLon = " << bbox[0]
                 << ", minLat = " << bbox[1]
                 << ", maxLon = " << bbox[2]
                 << ", maxLat = " << bbox[3]
                 << ", with input srs = " << epsgbbox
                 << endl;

            //Check if bbox is not wrong or too small
            if ( (maxLon == 0.0 && minLon == 0.0 && maxLat == 0.0 && minLat == 0.0) ||
                 ( ((maxLon - minLon) < 0.000000001) || ((maxLat - minLat) < 0.000000001) ) )
                return http_fget_ParseError(soap, "getFeature", "BBox");

            //Implementation of the query for the geo-intersection
            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::document::value query = builder 
                << "$geoWithin" << bsoncxx::builder::stream::open_document
                << "$polygon" << bsoncxx::builder::stream::open_array
                << bsoncxx::builder::stream::open_array << minLon << minLat << bsoncxx::builder::stream::close_array
                << bsoncxx::builder::stream::open_array << minLon << maxLat << bsoncxx::builder::stream::close_array
                << bsoncxx::builder::stream::open_array << maxLon << maxLat << bsoncxx::builder::stream::close_array
                << bsoncxx::builder::stream::open_array << maxLon << minLat << bsoncxx::builder::stream::close_array
                << bsoncxx::builder::stream::close_array  
            << bsoncxx::builder::stream::close_document
            << bsoncxx::builder::stream::finalize;
            
            
            //Parse typeNames which could contain multiple comma-separated values
            typeNames.append(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.Query_->typeNames);
            std::vector<std::string> features;
            boost::split(features, typeNames, boost::is_any_of(","), boost::token_compress_on);

            while(!features.empty())
            {
                string feature = features.back();
                cout << "feature found :" << feature << endl;

                //Selection of the 'feature' objets that interects the BBox (one point must be entirely within the bbox)
                //To select multi-surface geometry, the request is limited to the outter ring of the first geometry
                if(0 == feature.compare("plu:spatialplan"))
                    query_sp << "extent.coordinates0.0.0" << query ;
                else if (0 == feature.compare("plu:zoningelement"))
                    query_ze << "geometry.coordinates0.0.0" << query ;
                else if (0 == feature.compare("plu:supplementaryregulation"))
                    query_sr << "geometry.coordinates0.0.0" << query ;
                else
                    return http_fget_ParseError(soap, "GetFeature","typeNames");

                features.pop_back();
            }//end while
            
        }

        /* Init of a pointer used to answer the request */
        vector<wfs__MemberPropertyType *> *pwfsm;
        if (!(pwfsm = soap_new_std__vectorTemplateOfPointerTowfs__MemberPropertyType(soap)))
        {
            e << "Error nb " << soap->error;            
            return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing MemberProperty object", 400);
        }

        i = 0;

        wfs__MemberPropertyType *member = NULL;
        wfs__MemberPropertyType *document = NULL;

        bsoncxx::document::value sp_value = query_sp << bsoncxx::builder::stream::finalize;

        if(!sp_value.view().empty()) 
        {
            std::cout << "sp_value : "<< bsoncxx::to_json(sp_value) << std::endl;
            auto cursor_sp = collsp.find(sp_value.view());
            
            for (auto plu : cursor_sp)
            {
                //binding plu sequence to wfs member type
                if (gid.empty())
                {
                    member = (wfs__MemberPropertyType *)init_plu_SpatialPlan(soap, plu, outcrs, bbox);
                    if (!member)
                    {
                        e << "Error nb " << soap->error;
                        //return soap_receiver_fault(soap, "Internal server error initializing SpatialPlan Object", e.str().c_str());
                        return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing SpatialPlan object", 400);
                    }

                    pwfsm->insert(pwfsm->end(), member);
                    i++;
                }

                /* Let include in the response the associated OfficialDocumentation
                   case 1 : it's an ad hoc query (all official documents are included by default)
                   case 2 : it's an GetFeatureById query with an ID of an official document as parameter
                   case 3 : it's an GetSpatialPlanById query (all official documents are included by default)
                */
                if ((plu["officialdocument"] && adhocquery) ||
                    (plu["officialdocument"] && !gid.empty()) ||
                    (plu["officialdocument"] && !strcmp(wfs__GetFeature->__union_GetFeatureType->union_GetFeatureType.StoredQuery->id, "getspatialplanbyid")))
                {
                    if (plu["officialdocument"].type() == bsoncxx::type::k_array)
                    {
                        // get all documents associated to this Spatial Plan
                        auto docArray = plu["officialdocument"].get_array().value;

                        int j = 0;
                        int maxDoc = std::distance(docArray.begin(), docArray.end());
                        while (j < maxDoc)
                        {
                            // get each official document associated to this SpatialPlan
                            stringstream identifier;
                            char n[8];
                            oid lid;
                            lid = plu["_id"].get_oid().value;

                            if (plu["gid"])
                            {
                                mongocxx::stdx::string_view strview = plu["gid"].get_utf8().value;
                                identifier << strview.to_string();
                                identifier << "_";
                            }
                            identifier << "doc" << j;

                            if (gid.empty() || gid.find(n) != std::string::npos)
                            {
                                auto doc = docArray[j].get_document();
                                document = (wfs__MemberPropertyType *)init_plu_OfficialDocumentation(soap, lid, doc.view(), identifier.str());
                                pwfsm->insert(pwfsm->end(), document);
                            }
                            j++;

                        } //while
                    }
                }
            } // for cursor
            cout << i << " spatial plan found" << endl;
        }


        mongocxx::collection collze = db["demoze"];
        bsoncxx::document::value ze_value = query_ze << bsoncxx::builder::stream::finalize;

        if(!ze_value.view().empty()) 
        {
            std::cout << "ze_value : "<< bsoncxx::to_json(ze_value) << std::endl;
            auto cursor_ze = collze.find( ze_value.view() );

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
        }

        mongocxx::collection collsr = db["demosr"];
        bsoncxx::document::value sr_value = query_sr << bsoncxx::builder::stream::finalize;

        if(!sr_value.view().empty()) 
        {
            auto cursor_sr = collsr.find( sr_value.view() );

            for (auto sr : cursor_sr) {

                std::cout << "sr_value : "<< bsoncxx::to_json(ze_value) << std::endl;

                //binding SupplementaryRegulation sequence to wfs member type
                member = (wfs__MemberPropertyType *)init_plu_SupplementaryRegulation(soap, sr, outcrs, bbox);
                if(!member)
                {
                    e << "Error nb " << soap->error;
                    return http_fget_error(soap, "OperationProcessingFailed", e.str(), "Internal server error initializing SupplementaryRegulation object" , 400);
                }

                pwfsm->insert(pwfsm->end(),member);
                i++;
            } //end for cursor_sr
        }

        //adding attributes to FeatureCollection
        wfs__FeatureCollection.numberReturned = i;
        e.flush();
        e << i;
        wfs__FeatureCollection.numberMatched = e.str();
        wfs__FeatureCollection.timeStamp = time(0);
        

        /* wfs:boundedBy for the entire collection */
        if ( !(bbox[0] < 0.0000001 && bbox[1] < 0.0000001 && bbox[2] < 0.0000001 && bbox[3] < 0.0000001) && i > 0 ){
            wfs__FeatureCollection.boundedBy = soap_new_wfs__EnvelopePropertyType(soap);
            gml__EnvelopeType* envelop = soap_new_gml__EnvelopeType(soap);
            if(envelop != NULL)
            {
                string strbbox;
                char sxy[30];
                strbbox.append("urn:ogc:def:crs:EPSG::");
                sprintf(sxy, "%d", outcrs);
                strbbox.append(sxy);

                envelop->srsName = (char **) soap_malloc(soap, sizeof(char*));
                *envelop->srsName = (char *) soap_malloc(soap, strbbox.size() ),
                strcpy(*envelop->srsName, strbbox.c_str());

                oTargetSRS.importFromEPSGA(outcrs);
                if(outcrs != 4326) {
                    if (outcrs != 4171) {
                        oSourceSRS.importFromEPSGA(4326);
                        poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
                        if( poCT == NULL || !poCT->Transform( 1, &bbox[0], &bbox[1] ) || !poCT->Transform( 1, &bbox[2], &bbox[3] ) )
                        {
                            e << "The server failed to reproject the BoundedBy coordinates";
                            return http_fget_error(soap, "OperationProcessingFailed", e.str().c_str(), "GetFeature", 500);
                        }
                    }
                }
                
                if(oTargetSRS.EPSGTreatsAsLatLong())
                    //Lat Lon order
                    sprintf(sxy, "%.6f %.6f", bbox[1], bbox[0]);                                    
                else
                    sprintf(sxy, "%.6f %.6f", bbox[0], bbox[1]);
                gml__DirectPositionType* lcorner = soap_new_gml__DirectPositionType(soap);
                lcorner->__item.assign(sxy);
                envelop->lowerCorner = lcorner;                
                
                if(oTargetSRS.EPSGTreatsAsLatLong())
                    //Lat Lon order
                    sprintf(sxy, "%.6f %.6f", bbox[3], bbox[2]);
                else
                    sprintf(sxy, "%.6f %.6f", bbox[2], bbox[3]);
                gml__DirectPositionType* ucorner = soap_new_gml__DirectPositionType(soap);
                ucorner->__item.assign(sxy);
                envelop->upperCorner = ucorner;
                
                wfs__FeatureCollection.boundedBy = (wfs__EnvelopePropertyType*) envelop;
            }
        }

        //binding wfs member type to wfs return type
        wfs__FeatureCollection.member = *pwfsm;
        
    }//try
    catch( exception e ) {
        return http_fget_error(soap, "OperationProcessingFailed", e.what(), "DBException" , 400);
    }

	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}

