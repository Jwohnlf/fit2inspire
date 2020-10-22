/* plu_schema_instantiate.cpp
   Generated for fit2inspire.eu service implementation

   Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

   This code is released under the following license:
   1) GPL
*/

#include <time.h>
#include "plu_schema_instantiate.h"
#include "base_schema_instantiate.h"
#include "gml_schema_instantiate.h"

#define E_CODELIST_REGISTER "http://inspire.ec.europa.eu/codelist/"


/* name : init_plu_SpatialPlan
   description : returns a pointer of SpatialPlanProperty class
                 using a BSON object given by a MongoDB query
   return : pointer on a plu_SpatialPlanPropertyType element
*/

plu__SpatialPlanPropertyType * init_plu_SpatialPlan(struct soap *soap, view_or_value p, int outcrs, double bbox[])
{
    mongocxx::stdx::string_view strview;
    string str, code;
    time_t ldate;
    auto elem = p.view();

    plu__SpatialPlanPropertyType *eplu;
    __plu__SpatialPlanPropertyType_sequence *splu;
    plu__SpatialPlanType *pplu;

    if(!(eplu = soap_new_plu__SpatialPlanPropertyType(soap, -1))){
        fprintf(stderr, "Allocation of SpatialPlanPropertyType pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    if(!(pplu = soap_new_plu__SpatialPlanType(soap, -1))){
        fprintf(stderr, "Allocation of SpatialPlanType pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    if(!(splu = soap_new___plu__SpatialPlanPropertyType_sequence(soap, -1))){
        fprintf(stderr, "Allocation of SpatialPlanPropertyType_sequence pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    //Get MongoDB id of the current document
    oid lid = elem["_id"].get_oid().value;

    // ********* inspireId
    str.append("http://dataproviderns/sp");
    if( elem["gid"] )
    {
        strview = elem["gid"].get_utf8().value;
        code.append(strview.to_string());
        pplu->inspireId = init_base_Identifier(soap, code, lid, str);
        pplu->gml__id = (char**) soap_malloc(soap, sizeof(char**));
        *pplu->gml__id = init_gml_id(soap, code, lid);
    }
    str.clear();
    code.clear();

    // ********* officialTitle
    // *****************
    if( elem["officialtitle"] )
    {
        strview = elem["officialtitle"].get_utf8().value;
        pplu->officialTitle = strview.to_string();
    }

    // ********* levelOfSpatialPlan
    // *****************
    if(elem["levelofspatialplan"] )
    {
        strview =  elem["levelofspatialplan"].get_utf8().value;
        code.append(E_CODELIST_REGISTER);
        code.append("LevelOfSpatialPlanValue/");
        code.append(strview.to_string());
        pplu->levelOfSpatialPlan = init_gml_ReferenceType(soap, strview, code);
    }

    // JLD : on considère par défaut que le plan est de niveau "local"
    // si le champ typeplan.niveau n'est pas renseigné

    str.clear();
    code.clear();

    // ********* planTypeName & alternativeTitle
    // *****************
    if( elem["plantypename"] )
    {
        if( elem["plantypename"]["valstd"] )
        {
            strview = elem["plantypename"]["valstd"].get_utf8().value;

            if( elem["plantypename"]["valin"] )
            {
                code.append(E_CODELIST_REGISTER);
                code.append("PlanTypeNameValue/");
                code.append( (string) elem["plantypename"]["valstd"].get_utf8().value );
            }

            // il faut passer la valeur standardisée en 1, son URI dans le registre INSPIRE en 2.
            pplu->planTypeName = init_gml_ReferenceType(soap, strview, code);

            if(!(pplu->alternativeTitle = soap_new__plu__SpatialPlanType_alternativeTitle(soap,-1)))
            {
                fprintf(stderr, "SP : Allocation of alternativeTitle pointer failed\n");
                soap->error = SOAP_NULL;
                return NULL;
            }
            else if( elem["authority"] )
            {
                str = strview.to_string() + " - ";
                str.append( (string) elem["authority"].get_utf8().value );
                pplu->alternativeTitle->__item.append( str );
            }
        }
    } // endif plantypename

    code.clear();


    // ********* processGeneralStep
    // *****************
    if( elem["processstepgeneral"] )
    {
        if( elem["processstepgeneral"]["valin"] )
        {
            strview = elem["processstepgeneral"]["valin"].get_utf8().value;

            if( elem["processstepgeneral"]["valstd"] ){
                code.append(E_CODELIST_REGISTER);
                code.append("ProcessStepGeneralValue/");
                code.append((string) elem["processstepgeneral"]["valstd"].get_utf8().value );
            }
            pplu->processStepGeneral = init_gml_ReferenceType(soap, strview, code);
        }
    }


    // ********* extent
    // *****************
    /*if( elem["extent"] )
    {
        auto bgeom = elem["extent"].get_document().value;

        if( !bgeom.empty() )
        {
            pplu->extent = init_gml_MultiSurfacePropertyType(soap, bgeom, outcrs, bbox);
            if(!pplu->extent) {
                fprintf(stderr, "SP : Contruction of extent MultiSurface geometry failed\n");
                soap->error = SOAP_NULL;
                return NULL;
            }
        }
    } // end extent
*/

    // ********* beginLifespanVersion
    // *****************

    if(!(pplu->beginLifespanVersion = soap_new__plu__SpatialPlanType_beginLifespanVersion(soap)) )
    {
        fprintf(stderr, "SP : Allocation of beginLifespanVersion pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }   
    if ( elem["beginlifespanversion"] )
    {
        if( elem["beginlifespanversion"].type() == bsoncxx::type::k_date )
        {
            auto bls = elem["beginlifespanversion"].get_date().value;
            time_t time = bls.count();
            pplu->beginLifespanVersion->__item = time;
        }
        else
        {
            //if the returned value is not a date
            pplu->beginLifespanVersion->nilReason = plu::soap_new_std__string(soap);
            pplu->beginLifespanVersion->nilReason->append("unknown");
        }
    } // endif beginlifespanversion
    else
    {
        pplu->beginLifespanVersion->nilReason = plu::soap_new_std__string(soap);
        pplu->beginLifespanVersion->nilReason->append("missing");
    } // endelse beginlifespanversion


    // ********* endLifespanVersion
    // *****************

    if(elem["endlifespanversion"] )
    {
        if(!(pplu->endLifespanVersion = soap_new__plu__SpatialPlanType_endLifespanVersion(soap)) )
        {
            fprintf(stderr, "SP : Allocation of endLifespanVersion pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        if( elem["endlifespanversion"].type() == bsoncxx::type::k_date )
        {
            auto els = elem["endlifespanversion"].get_date().value;
            time_t time = els.count();
            pplu->endLifespanVersion->__item = time;
        }
    } //endif endlifespanversion


    // ********* validFrom
    // *****************
    if( elem["validfrom"] )
    {
        if( !(pplu->validFrom = soap_new__plu__SpatialPlanType_validFrom(soap)) )
        {
            fprintf(stderr, "SP : Allocation of validFrom pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        //if(p.getField("validfrom").type() == 9)
        if( elem["validfrom"].type() == bsoncxx::type::k_date )
        {
            auto vfr = elem["validfrom"].get_date().value;
            soap ? pplu->validFrom->__item = (char*)soap_malloc(soap,10+1) : pplu->validFrom->__item = (char*)malloc(10+1);

            stringstream sDate ;
            time_t time = vfr.count();
            sDate << put_time( gmtime(&time), "F");
            strcpy(pplu->validFrom->__item, sDate.str().c_str());
        }
    } //endif validFrom


    // ********* validTo
    // *****************
    if( elem["validto"] )
    {
        if(!(pplu->validTo = soap_new__plu__SpatialPlanType_validTo(soap)))
        {
            fprintf(stderr, "SP : Allocation of validTo pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        if( elem["validto"].type() == bsoncxx::type::k_date )
        {
            auto vto = elem["validto"].get_date().value;
            soap ? pplu->validTo->__item = (char*)soap_malloc(soap,10+1) : pplu->validTo->__item = (char*)malloc(10+1);

            stringstream sDate ;
            time_t time = vto.count();
            sDate << put_time( gmtime(&time), "F");
            strcpy(pplu->validTo->__item, sDate.str().c_str());
        }
    } //endif validTo

        // ********* backGroundMap
        // *****************
        if( elem["backgroundmap_name"] )
        {
            strview = elem["backgroundmap_name"] .get_utf8().value;
            pplu->backgroundMap = soap_new__plu__SpatialPlanType_backgroundMap(soap);
            pplu->backgroundMap->BackgroundMapValue = soap_new_plu__BackgroundMapValueType(soap);
            pplu->backgroundMap->BackgroundMapValue->backgroundMapReference = strview.to_string();

            if ( elem["backgroundmap_date"] ){
                if(elem["backgroundmap_date"].type() == bsoncxx::type::k_date )
                {
                    auto bmd = elem["backgroundmap_date"].get_date().value;
                    time_t time = bmd.count();
                    pplu->backgroundMap->BackgroundMapValue->backgroundMapDate = time;
                }
            }
        } // end if backgroundMap

        // ********* ordinance
        // *****************

        // ********* officialDocument
        /*****************
        if( elem["officialdocument"] && lid.isSet() )
        {
            vector<BSONElement> vecdoc = p.getField("officialdocument").Array();
            for(unsigned int i=0; i<vecdoc.size(); i++)
            {
                gml__ReferenceType *pgref = NULL;
                char *gmlid;
                char n[4];

                sprintf(n,"%d", i);
                str.assign("#");
                //Ajout du code du SpatialPlan
                str.append(p.getStringField("gid"));
                str.append("doc");
                str.append(n);

                gmlid = init_gml_id(soap, str, lid);
                code.assign(gmlid);
                if(!(pgref = init_gml_ReferenceType(soap, "", code)))
                {
                    soap->error = SOAP_NULL;
                    return NULL;
                }
                pplu->officialDocument.insert(pplu->officialDocument.end(),pgref);
            }
        }

        // ********* member (reference vers les zones composant le plan)
        // *****************
        if( elem["members"] )
        {
            vector<BSONElement> vecbe = p.getField("members").Array();
            for(unsigned int i=0; i<vecbe.size(); i++)
            {
                gml__ReferenceType *pgref = NULL;
                char *gmlid;
                str.assign("#");
                //Ajout du code du SpatialPlan
                str.append(p.getStringField("gid"));
                //Ajout du code du ZoningElement
                str.append(vecbe[i].Obj().getStringField("gid"));
                //Creation de l'OID
                OID ze_oid;
                ze_oid.init(vecbe[i].Obj().getStringField("_id"));

                gmlid = init_gml_id(soap, str, ze_oid);
                code.assign(gmlid);
                if(!(pgref = init_gml_ReferenceType(soap, "", code)))
                {
                    soap->error = SOAP_NULL;
                    return NULL;
                }
                pplu->member.insert(pplu->member.end(),pgref);
            }
        }


        // restriction (reference vers les prescriptions composant le plan)
        // *****************
        if( elem["restrictions"] )
        {
            vector<BSONElement> vecbe = p.getField("restrictions").Array();
            for(unsigned int i=0; i<vecbe.size(); i++)
            {
                gml__ReferenceType *pgref = NULL;
                char *gmlid;

                str.assign("#");
                //Ajout du code du SpatialPlan
                str.append(p.getStringField("gid"));
                //Ajout du code du SupplementaryRegulation
                str.append(vecbe[i].Obj().getStringField("gid"));
                //Ajout du timestamp
                OID sr_oid;
                sr_oid.init(vecbe[i].Obj().getStringField("_id"));

                gmlid = init_gml_id(soap, str, sr_oid);
                code.assign(gmlid);
                if(!(pgref = init_gml_ReferenceType(soap, "", code)))
                {
                    soap->error = SOAP_NULL;
                    return NULL;
                }
                pplu->restriction.insert(pplu->restriction.end(),pgref);
            }
        }
*/
        // bind plu object to plu sequence type
        // *****************
        splu->SpatialPlan = pplu;
        eplu->__SpatialPlanPropertyType_sequence = splu ;

        return eplu;

    }//end of function


/************* init_plu_OfficialDocumentation ***************/

plu__OfficialDocumentationPropertyType * init_plu_OfficialDocumentation(soap *soap, oid lid, view_or_value d, string identifier)
{
    plu__OfficialDocumentationPropertyType *retdoc;
    __plu__OfficialDocumentationPropertyType_sequence *dseq;
    plu__OfficialDocumentationType *document;
    mongocxx::stdx::string_view url,name;
    string str;


    if(!(retdoc = soap_new_plu__OfficialDocumentationPropertyType(soap, -1))){
            fprintf(stderr, "Allocation of OfficialDocumentationPropertyType pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
    }

    if(!(document = soap_new_plu__OfficialDocumentationType(soap, -1))){
        fprintf(stderr, "Allocation of OfficialDocumentationType pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    if(!(dseq = soap_new___plu__OfficialDocumentationPropertyType_sequence(soap, -1))){
        fprintf(stderr, "Allocation of OfficialDocumentationPropertyType_sequence pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    // ********* OfficialDocumentation InspireId & gml:id
    // *****************    
    document->inspireId = init_base_Identifier(soap, identifier, lid, "http://dataproviderns/od");
    document->gml__id = (char**) soap_malloc(soap, sizeof(char**));
    *(document->gml__id) = init_gml_id(soap, identifier, lid);
    

    if(d.view()["regurl"] && d.view()["regname"])
    {
        url = d.view()["regurl"].get_utf8().value;
        name = d.view()["regname"].get_utf8().value;

        // Gestion des documents graphiques du spatial plan dans le type planDocument si le champ regurl contient "graphique"
        if(std::string::npos != url.to_string().find("graphique",6))
        {
            document->planDocument = soap_new__plu__OfficialDocumentationType_planDocument(soap,-1);
            __plu__OfficialDocumentationType_planDocument_sequence  *odseq = soap_new___plu__OfficialDocumentationType_planDocument_sequence(soap);
            odseq->__unionDocumentCitation = 1;
            odseq->union_OfficialDocumentationType_planDocument.base2__DocumentCitation = soap_new_base2__DocumentCitationType(soap,1);
            odseq->union_OfficialDocumentationType_planDocument.base2__DocumentCitation->name.append(name.to_string());
            odseq->union_OfficialDocumentationType_planDocument.base2__DocumentCitation->link = soap_new_std__vectorTemplateOf_base2__DocumentCitationType_link(soap,-1);
            _base2__DocumentCitationType_link *dlink = soap_new__base2__DocumentCitationType_link(soap,-1);

            soap ? dlink->__item = (char*)soap_malloc(soap, url.size()+1) : dlink->__item = (char*)malloc(url.size()+1);
            //url.copy(dlink->__item, url.length(), 0);
            strcpy(dlink->__item, url.to_string().c_str());
            odseq->union_OfficialDocumentationType_planDocument.base2__DocumentCitation->link->insert(odseq->union_OfficialDocumentationType_planDocument.base2__DocumentCitation->link->begin(), *dlink);

            document->planDocument->__OfficialDocumentationType_planDocument_sequence = odseq;
        }
        else
        {
            // Regulation documents of the spatial plan encoded as legislationCitation
            document->legislationCitation = soap_new__plu__OfficialDocumentationType_legislationCitation(soap,-1);
            base2__LegislationCitationType *legalcit = soap_new_base2__LegislationCitationType(soap,-1);
            _base2__DocumentCitationType_link *dlink = soap_new__base2__DocumentCitationType_link(soap,-1);

            //add document url
            soap ? dlink->__item = (char*)soap_malloc(soap, url.size()+1) : dlink->__item = (char*)malloc(url.size()+1);
            strcpy(dlink->__item, url.to_string().c_str());
            legalcit->link = soap_new_std__vectorTemplateOf_base2__DocumentCitationType_link(soap,-1);
            legalcit->link->insert(legalcit->link->begin(), *dlink);

            //add document name
            legalcit->name.append(name.to_string());

            //add document level
            str.append(E_CODELIST_REGISTER);
            str.append("LegislationLevelValue/sub-national");
            legalcit->level = init_gml_ReferenceType(soap, "sub-national", str);

            //add citation to legalCitation attribute
            __plu__OfficialDocumentationType_legislationCitation_sequence *legalseq = soap_new___plu__OfficialDocumentationType_legislationCitation_sequence(soap);
            legalseq->base2__LegislationCitation = legalcit;
            document->legislationCitation->__OfficialDocumentationType_legislationCitation_sequence = legalseq;

        }

    }

    dseq->OfficialDocumentation = document;
    retdoc->__OfficialDocumentationPropertyType_sequence = dseq;

    return retdoc;

}// end of function init_plu_OfficialDocumentation



/************* init_plu_ZoningElement ***************/

plu__ZoningElementPropertyType * init_plu_ZoningElement(soap *soap, view_or_value o, int outcrs, double bbox[])
{

    plu__ZoningElementPropertyType *zoning ;
    __plu__ZoningElementPropertyType_sequence *zseq ;
    plu__ZoningElementType *zone ;

    mongocxx::stdx::string_view strview;
    string str, strtmp, code;

    auto elem = o.view();

    if(!(zoning = soap_new_plu__ZoningElementPropertyType(soap, -1))){
            fprintf(stderr, "Allocation of ZoningElementPropertyType pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
    }

    if(!(zone = soap_new_plu__ZoningElementType(soap, -1))){
            fprintf(stderr, "Allocation of ZoningElementType pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
    }

    if(!(zseq = soap_new___plu__ZoningElementPropertyType_sequence(soap, -1))){
        fprintf(stderr, "Allocation of ZoningElementPropertyType_sequence pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    //Get MongoDB id of the current document
    oid lid = elem["_id"].get_oid().value;

    // Init ZoningElement inspireId et gml:id
    // *****************
    str.append("http://dataproviderns/ze");
    if( elem["gid"] && elem["gid_urba"] )
    {
        strview = elem["gid_urba"].get_utf8().value;
        code.append(strview.to_string());
        code.append("_");
        strview = elem["gid"].get_utf8().value;
        code.append(strview.to_string());

        zone->inspireId = init_base_Identifier(soap, code, lid, str);

        // ********* Init ZoningElement gml:id
        // *****************
        str.assign("sgo.");
        str.append(code);
        zone->gml__id = (char**) soap_malloc(soap, sizeof(char**));
        *zone->gml__id = init_gml_id(soap, str, lid);
    }
    /*else if(o.hasField("CodeINSEE")) {
        zone->inspireId = init_base_Identifier(soap, o.getStringField("CodeINSEE"), lid, str);
    }*/

    str.clear();
    code.clear();

    // ********* geometry
    // *****************
    /*if( elem["geometry"] )
    {
        auto bo = elem["geometry"].get_document().value;
        zone->geometry =  init_gml_MultiSurfacePropertyType(soap, bo, outcrs, bbox);
        if(!zone->geometry)
        {
            fprintf(stderr, "ZE : Construction of MultiSurface geometry failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
    }//end if geometry
*/

    // ********* validFrom
    // *****************

    if( elem["validfrom"] ){
        if(!(zone->validFrom = soap_new__plu__ZoningElementType_validFrom(soap,-1))){
            fprintf(stderr, "ZE : Allocation of validFrom pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        //soap ? zone->validFrom->__item = (char*)soap_malloc(soap,str.size()) : zone->validFrom->__item = (char*)malloc(str.size());        
        if( elem["validfrom"].type() == bsoncxx::type::k_date ){
            auto ldate = elem["validfrom"].get_date().value;
            stringstream sDate ;
            time_t t = ldate.count();
            sDate << put_time( gmtime(&t), "%F");
            soap ? zone->validFrom->__item = (char*)soap_malloc(soap, sDate.gcount()+1) : zone->validFrom->__item = (char*)malloc(sDate.gcount()+1);
            strcpy(zone->validFrom->__item, sDate.str().c_str());
        }
    } // end validfrom


    // ********* validTo
    // *****************
    if( elem["validto"] ){
        if(!(zone->validTo = soap_new__plu__ZoningElementType_validTo(soap,-1))) {
            fprintf(stderr, "ZE : Allocation of validTo pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        if( elem["validto"].type() == bsoncxx::type::k_date ){
            auto ldate = elem["validto"].get_date().value;
            stringstream sDate ;
            time_t t = ldate.count();
            sDate << put_time( gmtime(&t), "%F");
            soap ? zone->validTo->__item = (char*)soap_malloc(soap, sDate.gcount()+1) : zone->validFrom->__item = (char*)malloc(sDate.gcount()+1);
            strcpy(zone->validTo->__item, sDate.str().c_str());
        }
    } // validto
    str.clear();


    // ********* beginlifespanVersion
    // *****************
    if(!(zone->beginLifespanVersion = soap_new__plu__ZoningElementType_beginLifespanVersion(soap,-1))){
        fprintf(stderr, "ZE : Allocation of beginLifespanVersion pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }
    if( elem["beginlifespanversion"] ) {
        if( elem["beginlifespanversion"].type() == bsoncxx::type::k_date )
        {
            auto bls = elem["beginlifespanversion"].get_date().value;
            time_t time = bls.count();
            zone->beginLifespanVersion->__item = time;
        }
        else
        {
            //if the returned value is not a date
            zone->beginLifespanVersion->nilReason = plu::soap_new_std__string(soap);
            zone->beginLifespanVersion->nilReason->append("unknown");
        }
    }
    else
    {
        zone->beginLifespanVersion->nilReason = plu::soap_new_std__string(soap);
        zone->beginLifespanVersion->nilReason->append("missing");
    }


    // ********* endLifespanVersion
    // *****************
    if( elem["endlifespanversion"] ){
        if(!(zone->endLifespanVersion = soap_new__plu__ZoningElementType_endLifespanVersion(soap,-1))){
            fprintf(stderr, "ZE : Allocation of endLifespanVersion pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        if( elem["endlifespanversion"] ) {
            if( elem["endlifespanversion"].type() == bsoncxx::type::k_date )
            {
                auto els = elem["endlifespanversion"].get_date().value;
                time_t time = els.count();
                zone->endLifespanVersion->__item = time;
            }
            else
            {
                //if the returned value is not a date
                zone->endLifespanVersion->nilReason = plu::soap_new_std__string(soap);
                zone->endLifespanVersion->nilReason->append("unknown");
            }
        }
        else
        {
            zone->endLifespanVersion->nilReason = plu::soap_new_std__string(soap);
            zone->endLifespanVersion->nilReason->append("missing");
        }
    }

    // ********* hilucsLandUse
    // *****************
    if( elem["hilucslanduse"] ) {
        auto bo = elem["hilucslanduse"].get_document().value;
        if(bo["valstd"]) {
            strview = bo["valstd"].get_utf8().value;

            //check if valstd contains multiple comma-separated values
            str.assign(strview.to_string());
            while(!str.empty())
            {
                code.append(E_CODELIST_REGISTER);
                code.append("HILUCSValue/");
                strtmp = str.substr(0, str.find_first_of(","));
                code.append(strtmp);
                zone->hilucsLandUse.insert(zone->hilucsLandUse.begin(),
                                           init_gml_ReferenceType(soap, strtmp, code));

                str = str.substr(strtmp.length(), string::npos);
                // if str is not empty, we erase first caracter containing the comma
                if(!str.empty())
                    str = str.substr(1, string::npos);
                strtmp.clear();
                code.clear();
            }//end while
        }
   }

    // ********* regulationNature
    // *****************
    code.assign(E_CODELIST_REGISTER);
    code.append("RegulationNatureValue/");
    str.assign("generallyBinding");
    code.append(str);
    zone->regulationNature = init_gml_ReferenceType(soap, str, code);


    // ********* specificLandUse
    // *****************
    if( elem["specificlanduse"] )
    {
        //Ce champ contient une des valeurs de l'énumération ZoneUrbaType définie dans le géostandard COVADIS PLU 2.0
        strview = elem["specificlanduse"].get_utf8().value;
        str.assign(strview.to_string());
        if( !str.empty() ){
            code.assign(E_CODELIST_REGISTER);
            code.append("LandUseClassificationValue/");
            code.append(str);

            zone->specificLandUse.insert(zone->specificLandUse.begin(), init_gml_ReferenceType(soap, str, code));
        }
    }

    // ********* Init assocation to spatial plan
    // *****************
    if( elem["plan"] )
    {
        str = "#";
        oid *pluOid = new oid(elem["plan"].get_utf8().value);
        strview = elem["gid_urba"].get_utf8().value;
        strtmp.assign( strview.to_string() );
        str.append( init_gml_id(soap, strtmp, *pluOid) );
        zone->plan = init_gml_ReferenceType(soap, "", str);
    }

    //binding zoningelement object to zoning sequence type
    zseq->ZoningElement = zone;
    zoning->__ZoningElementPropertyType_sequence = zseq;

    return zoning;
}//end of init_plu_zoningelement

