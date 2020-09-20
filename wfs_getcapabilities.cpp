/* wfs_getcapabilities.cpp
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/


#include <ctime>
#include "wfs_getcapabilities.h"

int fgetcapabilities(struct soap *soap)
{
    wfs__WFS_x005fCapabilitiesType *wfs__WFS_x005fCapabilities;
    wfs__WFS_x005fCapabilities = soap_new_wfs__WFS_x005fCapabilitiesType(soap);

    cout << "getCapabilities request received" << endl;
    __f2i_plu__wfs_x002egetCapabilities(soap, NULL,  *wfs__WFS_x005fCapabilities);

    soap->http_content = "text/xml";
    soap_response(soap, SOAP_FILE);
    wfs__WFS_x005fCapabilities->soap_put(soap, "wfs:WFS_Capabilities", "");
    soap_end_send(soap);

    return SOAP_OK;

} // end function fgetcapabilities

/** Server operation __f2i_plu__wfs_x002egetCapabilities */
int __f2i_plu__wfs_x002egetCapabilities(struct soap *soap, ows__GetCapabilitiesType *ows__GetCapabilities, wfs__WFS_x005fCapabilitiesType &wfs__WFS_x005fCapabilities)
{	
    /* Return incomplete response with default data values */
    string *pstr;

    /************** WSDL ***************/
    /***************/
    //wfs__WFS_x005fCapabilities->WSDL =


    /*************** Service Identification ***************/
    /***************/

    /* Connection à la base de données Mongo */
    try {

        mongocxx::client conn{mongocxx::uri{}};

        bsoncxx::builder::stream::document document{};        

        mongocxx::database db = conn["plu"];
        mongocxx::collection coll = conn["plu"]["server"];

        mongocxx::cursor cursor = coll.find( document << "identifier" << "plu-v0" << bsoncxx::builder::stream::finalize );


        for (auto&& wsd : cursor) {
                string stmp;

                bsoncxx::document::element el = {wsd["_id"]};
                char *uri;

                /*************** Service UpdateSequence ***************/

                oid lid;
                lid = el.get_oid().value;
                time_t t;
                stringstream sDate ;
                
                t = lid.get_time_t();
                sDate << put_time( gmtime(&t), "%F");
                wfs__WFS_x005fCapabilities.updateSequence = ::soap_new_std__string(soap);
                wfs__WFS_x005fCapabilities.updateSequence->append( sDate.str() );

                stmp.assign("2.0.0");
                wfs__WFS_x005fCapabilities.version = stmp;

                /*************** Service Identification ***************/

                _ows__ServiceIdentification* pservId = soap_new__ows__ServiceIdentification(soap);

                /*Title of WFS*/
                el = {wsd["title"]};
                if(el) {
                    auto titles = el.get_document().view();

                    for (auto title : titles) {
                        pservId->Title.insert(pservId->Title.end(),
                                              init_ows_LangString(soap, (string) title.key(), (string) title.get_utf8().value)
                                              );
                    }
                } //if title

                /*Abstract of WFS*/
                el = {wsd["abstract"]};
                if(el) {
                    auto abstracts = el.get_document().view();

                    for (auto abstract : abstracts) {
                        pservId->Abstract.insert(pservId->Abstract.end(), init_ows_LangString(soap, (string) abstract.key(), (string) abstract.get_utf8().value) );
                    }
                } //if abstract

                /* Service ows:Keywords */
                ows__KeywordsType *kw = soap_new_ows__KeywordsType(soap);

                el = {wsd["keywords"]};
                if(el) {
                    auto keysLang = el.get_document().view();

                    for (auto keys: keysLang) {
                        if (keys.type() == bsoncxx::type::k_array) {
                            auto kw_array = keys.get_array().value;
                                for(auto it : kw_array) {
                            //for(unsigned int i=0; i< vbe.size();i++)
                                    kw->Keyword.insert(kw->Keyword.end(), init_ows_LangString(soap, (string) keys.key(), (string) it.get_utf8().value) );
                                }
                        }
                    }//for
                } // if kw

                pservId->Keywords.insert(pservId->Keywords.end(), kw);

                /*Type of service*/
                pservId->ServiceType = soap_new_ows__CodeType(soap);
                pservId->ServiceType->__item.append("urn:ogc:service:wfs");

                pstr = soap_new_std__string(soap);
                pstr->assign("2.0.0");
                pservId->ServiceTypeVersion.insert(pservId->ServiceTypeVersion.end(), *pstr);

                /*Fees*/
                pservId->Fees = soap_new_std__string(soap);
                pservId->Fees->append("None");

                /*Access constraints*/
                pstr = soap_new_std__string(soap);
                pstr->assign("None");
                pservId->AccessConstraints.insert(pservId->AccessConstraints.end(), *pstr);

                wfs__WFS_x005fCapabilities.ServiceIdentification = pservId;


                /*************** Service Provider ***************/
                /***************/
                _ows__ServiceProvider* pservPro = soap_new__ows__ServiceProvider(soap);

                el = {wsd["provider"]["name"]};
                if (el)
                    pservPro->ProviderName.assign((string) el.get_utf8().value);

                el = {wsd["provider"]["url"]};
                if (el) {
                    pservPro->ProviderSite = soap_new_ows__OnlineResourceType(soap);
                    pservPro->ProviderSite->xlink__type = ::xlink__typeType__simple;
                    pservPro->ProviderSite->xlink__href =  (char**)soap_malloc(soap, sizeof(char**));
                    stmp.assign( (string) el.get_utf8().value );
                    soap ? uri = (char*)soap_malloc(soap, stmp.size()+1) : uri = (char*)malloc(stmp.size()+1);
                    strcpy(uri, stmp.c_str());
                    *(pservPro->ProviderSite->xlink__href) = uri;
                }

                ows__ResponsiblePartySubsetType * presp = soap_new_ows__ResponsiblePartySubsetType(soap);

                presp->ContactInfo = soap_new_ows__ContactType(soap);
                presp->ContactInfo->Address = soap_new_ows__AddressType(soap);

                el = {wsd["provider"]["city"]};
                if (el) {
                    presp->ContactInfo->Address->City = ::soap_new_std__string(soap);
                    presp->ContactInfo->Address->City->append( (string) el.get_utf8().value );
                }

                el = {wsd["provider"]["zipcode"]};
                if (el) {
                    presp->ContactInfo->Address->PostalCode = ::soap_new_std__string(soap);
                    presp->ContactInfo->Address->PostalCode->append( (string) el.get_utf8().value );
                }

                el = {wsd["provider"]["country"]};
                if (el) {
                    presp->ContactInfo->Address->Country = ::soap_new_std__string(soap);
                    presp->ContactInfo->Address->Country->append( (string) el.get_utf8().value );
                }

                el = {wsd["provider"]["mail"]};
                if (el) {
                    presp->ContactInfo->Address->ElectronicMailAddress.insert(presp->ContactInfo->Address->ElectronicMailAddress.begin(), (string) el.get_utf8().value );
                }

                el = {wsd["provider"]["phone"]};
                if (el) {
                    presp->ContactInfo->Phone = soap_new_ows__TelephoneType(soap);
                    presp->ContactInfo->Phone->Voice.insert(presp->ContactInfo->Phone->Voice.begin(), (string) el.get_utf8().value );
                }

                el = {wsd["provider"]["website"]};
                if (el) {
                    presp->ContactInfo->OnlineResource = soap_new_ows__OnlineResourceType(soap);
                    presp->ContactInfo->OnlineResource->xlink__type = ::xlink__typeType__simple;
                    presp->ContactInfo->OnlineResource->xlink__href =  (char**)soap_malloc(soap, sizeof(char**));
                    stmp.assign( (string) el.get_utf8().value );
                    soap ? uri = (char*)soap_malloc(soap, stmp.size()+1) : uri = (char*)malloc(stmp.size()+1);
                    strcpy(uri, stmp.c_str());
                    presp->ContactInfo->OnlineResource->xlink__href = (char**)soap_malloc(soap,sizeof(char**));
                    *(presp->ContactInfo->OnlineResource->xlink__href) = uri;
                }

                el = {wsd["provider"]["individual"]};
                if (el) {
                    pstr = ::soap_new_std__string(soap);
                    pstr->append( (string) el.get_utf8().value );
                    presp->IndividualName = pstr;
                }

                el = {wsd["provider"]["position"]};
                if (el) {
                    pstr = ::soap_new_std__string(soap);
                    pstr->append( (string) el.get_utf8().value );
                    presp->PositionName = pstr;
                }

                el = {wsd["provider"]["role"]};
                if (el) {
                    presp->Role = soap_new_ows__CodeType(soap);
                    presp->Role->__item.append( (string) el.get_utf8().value );
                }

                pservPro->ServiceContact = presp;

                wfs__WFS_x005fCapabilities.ServiceProvider = pservPro ;


                /*************** OperationsMetadata ***************/
                /***************/
                el = wsd["operationlist"];
                if(el) {
                    if(el.type() == bsoncxx::type::k_array) {
                        auto operations = el.get_array().value;

                        _ows__OperationsMetadata * pmeta = soap_new__ows__OperationsMetadata(soap, operations.length());
                        _ows__Operation * poper = soap_new__ows__Operation(soap, operations.length());
                        ows__DomainType *pdom;

                        for( auto ope : operations) {

                            /* ows:Operation attribute Name  */
                            if (ope["name"])
                                poper->name.assign( (string) ope["name"].get_utf8().value );

                            /* ows:DCP attribute Dcp */
                            if (ope["dcp"]) {
                                stmp.assign( (string) ope["dcp"].get_utf8().value  );
                                _ows__DCP *DCP = soap_new__ows__DCP(soap);
                                DCP->__union_DCP = 1;
                                DCP->union_DCP.HTTP = soap_new__ows__HTTP(soap);

                                ows__RequestMethodType *preq = soap_new_ows__RequestMethodType(soap);
                                preq->xlink__href = (char **)soap_malloc(soap, sizeof(char **));
                                (*preq->xlink__href) = (char *)soap_malloc(soap, stmp.size()+1);
                                strcpy((*preq->xlink__href), stmp.c_str());
                                
                                __ows__union_HTTP union_HTTP;
                                union_HTTP.__union_HTTP = 1;
                                union_HTTP.union_HTTP.Get = preq;
                                DCP->union_DCP.HTTP->__union_HTTP.insert(
                                    DCP->union_DCP.HTTP->__union_HTTP.begin(),
                                    union_HTTP);
                                poper->DCP.insert(poper->DCP.end(), DCP);
                            }

                            /* ows:Parameter */
                            if (ope["parameter"]) {
                                auto parameters = ope["parameter"].get_document().view();

                                for( auto it : parameters) {
                                    pdom = init_ows_Domain(soap, it);
                                    poper->Parameter.insert(poper->Parameter.end(), pdom);
                                }//for it
                            }
                            pmeta->Operation.insert(pmeta->Operation.begin(), poper);
                            poper++;
                        } //end for

                        /* ows_Parameter of all operations */
                        const auto versions = {"2.0.0"};
                        auto btmp = bsoncxx::builder::basic::document{};
                        btmp.append(kvp("Version", [&versions](sub_array child) {
                            for (const auto& vers : versions) {
                                child.append(vers);
                            }
                        }));
                        //auto in_array = builder << "Version" << builder::stream::open_array;
                        //bsoncxx::builder::stream otmp {} << "Version" << BSON_ARRAY("2.0.0"));
                        auto elem = btmp.view();
                        for( auto it : elem) {
                             pdom = init_ows_Domain(soap, it);
                        }
                        pmeta->Parameter.insert(pmeta->Parameter.end(), pdom);

                        /*************** INSPIRE ExtendedCapabilities ***************/
                        /***************/
                        //pmeta->ExtendedCapabilities = soap_new_idls__ExtendedCapabilitiesType(soap);
                        idls__ExtendedCapabilitiesType *pextcapa = soap_new_idls__ExtendedCapabilitiesType(soap);

                        /* inspire_x005fcommon:RessourceLocator */
                        icommon__resourceLocatorType * pres = soap_new_icommon__resourceLocatorType(soap);
                        stmp.assign(soap->endpoint);
                        pres->URL = (char*) soap_malloc(soap, stmp.size()+1);
                        strcpy(pres->URL, stmp.c_str());
                        pres->MediaType.insert(pres->MediaType.end(), icommon__mediaType__application_x002fvnd_x002eogc_x002ewfs_x005fxml);
                        pextcapa->ResourceLocator.insert(pextcapa->ResourceLocator.end(), pres);

                        /* inspire_x005fcommon:MetadarUrl : inapplicable TG 51 * /
                        /*
INSPIRE Metadata for the Download Service shall EITHER be linked to via an <inspire_x005fcommon:MetadataURL> in an extended capabilities section, OR the extended capabilities section shall contain all the INSPIRE Metadata for
the Download Service in accordance with Table 4 and the idls:ExtendedCapabilities schema.
                          */

                        /* inspire_x005fcommon:RessourceType */
                        pextcapa->ResourceType = (icommon__serviceSpatialDataResourceType*)soap_malloc(soap, sizeof(int*));
                        *(pextcapa->ResourceType) = icommon__serviceSpatialDataResourceType__service; //service

                        /* inspire_x005fcommon:SpatialDataServiceType */
                        pextcapa->SpatialDataServiceType = (icommon__spatialDataServiceType*)soap_malloc(soap, sizeof(int*));
                        *(pextcapa->SpatialDataServiceType) = icommon__spatialDataServiceType__download; //download service

                        /* inspire_x005fcommon:MandatoryKeyword */
                        icommon__classificationOfSpatialDataService *pclass = soap_new_icommon__classificationOfSpatialDataService(soap);
                        pclass->KeywordValue = _icommon__classificationOfSpatialDataService_KeywordValue__infoFeatureAccessService;
                        icommon__originatingControlledVocabulary *pvoc = soap_new_icommon__originatingControlledVocabulary(soap);
                        pvoc->Title.assign("Règlement (CE) n o 1205/2008");
                        //stmp.assign("http://eur-lex.europa.eu/legal-content/FR/ALL/?uri=CELEX:32008R1205");
                        //pvoc->URI.insert(pvoc->URI.end(), stmp.c_str());
                        pvoc->__union_originatingControlledVocabulary = 1;
                        pvoc->union_originatingControlledVocabulary.DateOfPublication = ::soap_new_std__string(soap);
                        pvoc->union_originatingControlledVocabulary.DateOfPublication->assign("2008-12_03");
                        pclass->OriginatingControlledVocabulary.insert(pclass->OriginatingControlledVocabulary.end(), pvoc);
                        pextcapa->MandatoryKeyword.insert(pextcapa->MandatoryKeyword.end(), pclass);

                        /* inspire_common:Conformity */
                        icommon__conformity* pcfm = soap_new_icommon__conformity(soap);
                        pcfm->Degree = icommon__degreeOfConformity__conformant;
                        pcfm->Specification = soap_new_icommon__citationConformity(soap);
                        pcfm->Specification->__union_citationConformity = 1;
                        pcfm->Specification->union_citationConformity.DateOfPublication = ::soap_new_std__string(soap);
                        pcfm->Specification->union_citationConformity.DateOfPublication->append("2013-12-10");
                        pcfm->Specification->Title.append("D2.8.III.4 INSPIRE Data Specification on Land Use");
                        pres = soap_new_icommon__resourceLocatorType(soap);
                        stmp.assign("http://inspire.ec.europa.eu/documents/Data_Specifications/INSPIRE_DataSpecification_LU_v3.0.pdf");
                        pres->URL = (char*) soap_malloc(soap, stmp.size()+1);
                        strcpy(pres->URL, stmp.c_str());
                        pres->MediaType.insert(pres->MediaType.end(), icommon__mediaType__application_x002fpdf);
                        pcfm->Specification->ResourceLocator.insert(pcfm->Specification->ResourceLocator.end(), pres);

                        pextcapa->Conformity.insert(pextcapa->Conformity.end(), pcfm);

                        /* inspire_common:TemporalReference*/
                        icommon__temporalReference *ptemp = soap_new_icommon__temporalReference(soap);
                        ptemp->DateOfPublication.insert(ptemp->DateOfPublication.end(), "2014-11-03");

                        pextcapa->TemporalReference.insert(pextcapa->TemporalReference.end(), ptemp);

                        /* inspire_common:MetadataDate (Metadata Date) */
                        pextcapa->MetadataDate = ::soap_new_std__string(soap);
                        pextcapa->MetadataDate->append( sDate.str() );

                        /* inspire_common:SupportedLangages (Metadata Language) */
                        pextcapa->SupportedLanguages = soap_new_icommon__supportedLanguagesType(soap);
                        pextcapa->SupportedLanguages->DefaultLanguage = soap_new_icommon__languageElementISO6392B(soap);
                        pextcapa->SupportedLanguages->DefaultLanguage->Language= icommon__euLanguageISO6392B__fre; //fre

                        icommon__languageElementISO6392B *plang = soap_new_icommon__languageElementISO6392B(soap, 1);
                        plang->Language = icommon__euLanguageISO6392B__eng; // eng
                        pextcapa->SupportedLanguages->SupportedLanguage.insert(pextcapa->SupportedLanguages->SupportedLanguage.end(),plang);

                        // Bind
                        pmeta->ExtendedCapabilities = pextcapa;
                        wfs__WFS_x005fCapabilities.OperationsMetadata = pmeta;
                    }
                }

                /*************** FeatureType List ***************/
                /***************/
                el = {wsd["featurelist"]};
                if(el) {
                    if( el.type() == bsoncxx::type::k_array ) {
                        auto features = el.get_array().value;

                        wfs__FeatureTypeListType *pflist = soap_new_wfs__FeatureTypeListType(soap);
                        wfs__FeatureTypeType *pfeat = soap_new_wfs__FeatureTypeType(soap, features.length());

                        for( auto feature : features )
                        {
                            auto efeat = feature.get_document().view();

                            /* wfs:Name */
                            if ( efeat["name"] ) {
                                stmp.assign( (string) efeat["name"].get_utf8().value );
                                pfeat->Name = (char*)soap_malloc(soap, stmp.size()+1);
                                strcpy(pfeat->Name, stmp.c_str());
                            }


                            /* wfs:Title xml:lang="en", xml:lang="fr"... */
                            if( efeat["title"] ) {
                                auto titles = efeat["title"].get_document().view();

                                _wfs__Title *wtitle = soap_new__wfs__Title(soap, titles.length());

                                for (auto title : titles) {
                                    wtitle->__item.append( (string) title.get_utf8().value );
                                    stmp.assign( (string) title.key() );
                                    wtitle->xml__lang = (char*)soap_malloc(soap, stmp.size()+1 );
                                    strcpy(wtitle->xml__lang, stmp.c_str());
                                    pfeat->Title.insert(pfeat->Title.end(), wtitle);
                                    wtitle++;
                                }
                            } //if title


                            /* wfs:Abstract xml:lang="en", xml:lang="fr"... */
                            if( efeat["abstract"] ) {
                                auto abstracts = efeat["abstract"].get_document().view();

                                _wfs__Abstract *wabst = soap_new__wfs__Abstract(soap, abstracts.length());

                                for (auto abs : abstracts) {
                                    wabst->__item.assign( (string) abs.get_utf8().value );
                                    stmp.assign( (string) abs.key() );
                                    wabst->xml__lang = (char*)soap_malloc(soap, stmp.size()+1);
                                    strcpy(wabst->xml__lang, stmp.c_str());
                                    pfeat->Abstract.insert(pfeat->Abstract.end(), wabst);
                                    wabst++;
                            }

                            /* ows:Keywords */
                            if( efeat["keywords"] ) {
                                if ( efeat["keywords"].type() == bsoncxx::type::k_document ) {
                                    auto keysLang = efeat["keywords"].get_document().view();
                                    ows__KeywordsType *wkw = soap_new_ows__KeywordsType(soap);

                                    for (auto keys: keysLang) {
                                        if (keys.type() == bsoncxx::type::k_array) {
                                            auto kw_array = keys.get_array().value;
                                                for(auto it : kw_array) {
                                                    wkw->Keyword.insert(wkw->Keyword.end(), init_ows_LangString(soap, (string) keys.key(), (string) it.get_utf8().value) );
                                                }
                                        }
                                    }//for
                                    pfeat->ows__Keywords.insert(pfeat->ows__Keywords.end(), wkw);
                                }
                            } // if kw

                            /* wfs:DefaultCRS */
                            if( efeat["defaultcrs"] ) {
                                stmp.assign( (string) efeat["defaultcrs"].get_utf8().value );
                                pfeat->DefaultCRS = (char**) soap_malloc(soap,sizeof(char **));
                                *(pfeat->DefaultCRS) = (char*) soap_malloc(soap, stmp.size()+1);
                                strcpy(*(pfeat->DefaultCRS), stmp.c_str());


                                /* wfs:OtherCRS */
                                if( efeat["othercrs"] ) {
                                    if( efeat["othercrs"].type() == bsoncxx::type::k_array ) {

                                        auto ocrs = efeat["othercrs"].get_array().value;
                                        for (auto crs : ocrs) {
                                            stmp.assign( (string) crs.get_utf8().value );
                                            char *srs = (char*) soap_malloc(soap, stmp.size()+1);
                                            strcpy(srs, stmp.c_str() );
                                            pfeat->OtherCRS.insert(pfeat->OtherCRS.end(), srs);
                                        } // for
                                    }
                                }
                            } //end if defaultcrs
                            else if ( efeat["nocrs"] ){
                                pfeat->NoCRS = soap_new__wfs__FeatureTypeType_NoCRS(soap);
                            }

                            /* wfs:OutputFormats */
                            wfs__OutputFormatListType *wof = soap_new_wfs__OutputFormatListType(soap);
                            __wfs__OutputFormatListType_sequence *format = soap_new___wfs__OutputFormatListType_sequence(soap);
                            format->Format.assign("application/gml+xml;version=3.2");
                            wof->__OutputFormatListType_sequence.insert(wof->__OutputFormatListType_sequence.begin(), *format);
                            pfeat->OutputFormats = wof;

                            /* ows:WGSBoundingBox */
                            if ( efeat["bbox"] ) {
                                /*Solution par défaut : utilisation du champ bbox de la collection server en BD
                                  Sinon oblige à parser toute la collection ? */

                                if( efeat["bbox"].type() == bsoncxx::type::k_array )
                                {
                                    ows__WGS84BoundingBoxType *pbbox = soap_new_ows__WGS84BoundingBoxType(soap);

                                    auto coord = efeat["bbox"].get_array().value;
                                    //if ( efeat["bbox"].size() == 4 ) {
                                        char corner[30];
                                        sprintf(corner, "%lf %lf", coord[0].get_double().value, coord[1].get_double().value );
                                        pbbox->LowerCorner.assign(corner);

                                        sprintf(corner, "%lf %lf", coord[2].get_double().value, coord[3].get_double().value );
                                        pbbox->UpperCorner.assign(corner);
                                        pfeat->ows__WGS84BoundingBox.insert(pfeat->ows__WGS84BoundingBox.end(), pbbox);
                                    //}
                                }
                            }

                            /* wfs:MetadataURL */
                            /* No metadata are available per feature type of the INSPIRE shema */
                            /* Choice : add metadata url to source datasets only at Spatial Plan feature type level */

                            if(strcmp(pfeat->Name, "plu:SpatialPlan") == 0) {
                                mongocxx::pipeline pipe ;
                                pipe.group(make_document(kvp("_id", "$metadata.view_meta")));

                                auto cursor = db["demosp"].aggregate(pipe);

                                for (auto&& doc : cursor) {

                                    if (doc["_id"].type() == bsoncxx::type::k_utf8 )
                                    {
                                        wfs__MetadataURLType* purl = soap_new_wfs__MetadataURLType(soap);
                                        purl->xlink__href = (char**) soap_malloc(soap, sizeof(char**));

                                        mongocxx::stdx::string_view strview = doc["_id"].get_utf8().value;

                                        stmp = strview.to_string();
                                        *(purl->xlink__href) = (char*) soap_malloc(soap, stmp.size()+1 );
                                        strcpy(*(purl->xlink__href), stmp.c_str());

                                        pfeat->MetadataURL.insert(pfeat->MetadataURL.end(), purl);
                                    }
                                } // for
                            } //if sp


                            pflist->FeatureType.insert(pflist->FeatureType.end(), pfeat);
                            pfeat++;
                        } // end for

                        /* wfs:MetadataURL */
                        wfs__WFS_x005fCapabilities.FeatureTypeList = pflist;

                        }
                    }
                } // featurelist



                /*************** FilterCapabilities ***************/
                /***************/
                _fes__Filter_x005fCapabilities *pfilter = soap_new__fes__Filter_x005fCapabilities(soap);
                fes__ConformanceType *pconf = soap_new_fes__ConformanceType(soap);

                el = {wsd["conformance"]};
                if(el) {
                    auto oconfs = el.get_document().view();
                    for(auto o : oconfs) {
                        ows__DomainType *pdom = soap_new_ows__DomainType(soap);
                        mongocxx::stdx::string_view strview = o.key();
                        pdom->name = strview.to_string();

                        pdom->DefaultValue = soap_new_ows__ValueType(soap);
                        o.get_bool().value ? pdom->DefaultValue->__item.append("true") : pdom->DefaultValue->__item.append("false");
                        pconf->Constraint.insert(pconf->Constraint.end(), pdom);
                    }//for
                }

                el = {wsd["capacity"]};
                if(el) {
                    auto ocapa = el.get_document().view();
                    for(auto o : ocapa) {
                        ows__DomainType *pdom = soap_new_ows__DomainType(soap);
                        mongocxx::stdx::string_view strview = o.key();
                        pdom->name = strview.to_string();

                        pdom->DefaultValue = soap_new_ows__ValueType(soap);
                        o.get_bool().value ? pdom->DefaultValue->__item.append("true") : pdom->DefaultValue->__item.append("false");
                        pconf->Constraint.insert(pconf->Constraint.end(), pdom);
                    }//for
                }

                pfilter->Conformance = pconf;
                wfs__WFS_x005fCapabilities.fes__Filter_x005fCapabilities = pfilter;

        }//for cursor

    } //try
    catch( exception e )
    {
        return http_fget_error(soap, "OperationProcessingFailed", e.what() , "DB query error" , 400);
    }
    return SOAP_OK;
}


int http_fget_error(struct soap *soap, const char* exceptionCode, string exceptionText, string locator, int status)
{
    ows__ExceptionType *exc;
    _ows__ExceptionReport *report;

    exc = soap_new_ows__ExceptionType(soap);
    exc->exceptionCode.assign(exceptionCode);
    if(!exceptionText.empty())
        exc->ExceptionText.insert(exc->ExceptionText.begin(), exceptionText);
    if(!locator.empty())
    {
        exc->locator = ::soap_new_std__string(soap);
        exc->locator->assign(locator);
    }
    report = soap_new__ows__ExceptionReport(soap);
    report->version = "2.0.0";
    report->Exception.insert(report->Exception.end(), exc);
    report->xml__lang = (char **)soap_malloc(soap, sizeof(char**));
    *(report->xml__lang) = (char *)soap_malloc(soap, sizeof("en")+1);
    strcpy(*(report->xml__lang), "en");

    soap->http_content = "text/xml";
    soap_response(soap, SOAP_FILE);
    report->soap_put(soap, "ows:ExceptionReport", "");
    soap_end_send(soap);

    return status;

} // end http_fget_error


int http_fget_ParseError(struct soap *soap, string function, string param)
{
    ows__ExceptionType *exc;
    _ows__ExceptionReport *report;

    exc = soap_new_ows__ExceptionType(soap, 2);
    exc->exceptionCode.assign("OperationParsingFailed");
    exc->ExceptionText.insert(exc->ExceptionText.begin(), "The request can't be parsed by the server");
    exc->locator = ::soap_new_std__string(soap);
    exc->locator->assign(function);

    (exc+1)->exceptionCode.assign("InvalidParameterValue");
    (exc+1)->ExceptionText.insert((exc+1)->ExceptionText.begin(), "This request parameter has invalid values");
    (exc+1)->locator = ::soap_new_std__string(soap);
    (exc+1)->locator->assign(param);

    report = soap_new__ows__ExceptionReport(soap);
    report->version = "2.0.0";
    report->xml__lang = (char **)soap_malloc(soap, sizeof(char**));
    *(report->xml__lang) = (char *)soap_malloc(soap, sizeof("en")+1);
    strcpy(*(report->xml__lang), "en");
    report->Exception.insert(report->Exception.end(), exc);
    report->Exception.insert(report->Exception.end(), exc+1);

    soap->http_content = "text/xml";
    soap_response(soap, SOAP_FILE);
    report->soap_put(soap, "ows:ExceptionReport", "");
    soap_end_send(soap);
    return 400;

} // http_fget_ParseError

/** Auto-test server operation __f2i_plu__wfs_x002ecreateStoredQuery */
int __f2i_plu__wfs_x002ecreateStoredQuery(struct soap *soap, wfs__CreateStoredQueryType *wfs__CreateStoredQuery, wfs__CreateStoredQueryResponseType &wfs__CreateStoredQueryResponse)
{
	(void)soap; /* appease -Wall -Werror */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002edescribeFeatureType */
int __f2i_plu__wfs_x002edescribeFeatureType(struct soap *soap, wfs__DescribeFeatureTypeType *wfs__DescribeFeatureType, util__DescribeFeatureTypeResponseType &util__DescribeFeatureTypeResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002egetFeature */
int __f2i_plu__wfs_x002egetFeature(struct soap *soap, wfs__GetFeatureType *wfs__GetFeature, wfs__FeatureCollectionType &wfs__FeatureCollection)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002edescribeStoredQueries */
int __f2i_plu__wfs_x002edescribeStoredQueries(struct soap *soap, wfs__DescribeStoredQueriesType *wfs__DescribeStoredQueries, wfs__DescribeStoredQueriesResponseType &wfs__DescribeStoredQueriesResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002elistStoredQueries */
int __f2i_plu__wfs_x002elistStoredQueries(struct soap *soap, wfs__ListStoredQueriesType *wfs__ListStoredQueries, wfs__ListStoredQueriesResponseType &wfs__ListStoredQueriesResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002edropStoredQuery */
int __f2i_plu__wfs_x002edropStoredQuery(struct soap *soap, _wfs__DropStoredQuery *wfs__DropStoredQuery, wfs__ExecutionStatusType &wfs__DropStoredQueryResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002egetFeatureWithLock */
int __f2i_plu__wfs_x002egetFeatureWithLock(struct soap *soap, wfs__GetFeatureWithLockType *wfs__GetFeatureWithLock, wfs__FeatureCollectionType &wfs__FeatureCollection)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002egetPropertyValue */
int __f2i_plu__wfs_x002egetPropertyValue(struct soap *soap, wfs__GetPropertyValueType *wfs__GetPropertyValue, wfs__ValueCollectionType &wfs__ValueCollection)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002elockFeature */
int __f2i_plu__wfs_x002elockFeature(struct soap *soap, wfs__LockFeatureType *wfs__LockFeature, wfs__LockFeatureResponseType &wfs__LockFeatureResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}


/** Auto-test server operation __f2i_plu__wfs_x002etransaction */
int __f2i_plu__wfs_x002etransaction(struct soap *soap, wfs__TransactionType *wfs__Transaction, wfs__TransactionResponseType &wfs__TransactionResponse)
{
	(void)soap; /* appease -Wall -Werror */
	/* Returns incomplete response containing some default data values */
	return SOAP_OK;
}
