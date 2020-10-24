/*  gml_schema_instantiate.cpp
    Generated for fit2inspire.eu service implementation

    Copyright(C) 2014-2020, Jean-Loup Delaveau, Fit2Inspire.eu

    This code is released under the following license:
    1) GPL
*/

#include "gml_schema_instantiate.h"


char* init_gml_id(struct soap *soap, string strval, oid lid)
{
    char *id;

    std::size_t found = strval.find_first_of("_");
    while (found!=std::string::npos)
    {
        strval.erase(found,1);
        found=strval.find_first_of("_",found+1);
    }

    std::time_t tstamp = lid.get_time_t();
    strval.append(std::ctime(&tstamp));
    //strval.append(timeToISOString(lid.asDateT().toTimeT()));
    found = strval.find_first_of("-:.");
    while (found!=std::string::npos)
    {
        strval.erase(found,1);
        found=strval.find_first_of("-:.",found+1);
    }
    soap ? id = (char*)soap_malloc(soap, strval.length()+1) : id = (char*)malloc(strval.length()+1);
    strcpy(id, strval.c_str());

    return id;
}

/* nom : init_gml_ReferenceType
   description : construction of gml__Reference object to build a link or a reference
   towards an object or an external URI
   return : gml__ReferenceType pointer
*/
gml__ReferenceType * init_gml_ReferenceType(struct soap *soap, mongocxx::stdx::string_view val, string uri)
{
    gml__ReferenceType * pgref = NULL;
    char *test = NULL;

    pgref = soap_new_gml__ReferenceType(soap,-1);

    if(!val.empty()) {
        // when the referenced value is registered in a codeList
        // Example : xlink:title="5_2_ResidentialUseWithOtherCompatibleUses" xlink:href="http://inspire.ec.europa.eu/codelist/HILUCSValue/5_2_ResidentialUseWithOtherCompatibleUses"

        pgref->xlink__title = plu::soap_new_std__string(soap);
        pgref->xlink__title->append( val.to_string() );
    } // endif val empty

    if(!uri.empty()){
        soap ? test = (char*)soap_malloc(soap, uri.length()+1) : test = (char*)malloc(uri.length()+1);
        if(!test)
        {
            fprintf(stderr, "SP : Allocation of char test pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
        strcpy(test, uri.c_str());

        pgref->xlink__href = (char**)soap_malloc(soap,sizeof(char**));
        if (pgref->xlink__href)
            *(pgref->xlink__href) = test;
        else
        {
            fprintf(stderr, "SP : Allocation of xlink__href pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
    } //endif uri empty

    return pgref;
}

gml__MultiSurfacePropertyType * init_gml_MultiSurfacePropertyType(struct soap *soap, view_or_value bgeom, int outcrs, double bbox[])
{

    gml__MultiSurfacePropertyType *pret;
    
    if(!(pret = soap_new_gml__MultiSurfacePropertyType(soap,-1)))
    {
        fprintf(stderr, "Allocation of MultiSurfacePropertyType pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    __gml__MultiSurfacePropertyType_sequence *msfseq = soap_new___gml__MultiSurfacePropertyType_sequence(soap);

    msfseq->MultiSurface = init_gml_MultiSurfaceType(soap, bgeom, outcrs, bbox);

    pret->__MultiSurfacePropertyType_sequence = msfseq;

    return pret;
}

gml__MultiSurfaceType * init_gml_MultiSurfaceType(struct soap *soap, view_or_value bgeom, int outcrs, double bbox[])
{
    gml__MultiSurfaceType *pmsf = NULL;
    bsoncxx::array::view be_ring;
    int i=0;
    int ngeom = 0;
    //char s[15];
    stringstream s;
    string strepsg;

    pmsf = soap_new_gml__MultiSurfaceType(soap,-1);
    if(!pmsf){
        fprintf(stderr, "Allocation of MultiSurfaceType pointer failed\n");
        soap->error = SOAP_NULL;
        return NULL;
    }

    //Initialisation de l'attribut srsName correspondant à la projection de la géométrie
    strepsg.assign("urn:ogc:def:crs:EPSG::");
    //sprintf(s, "%d", outcrs);
    s << outcrs;
    strepsg.append(s.str());
    pmsf->srsName = (char**)soap_malloc(soap, sizeof(char**));
    *pmsf->srsName = (char*)soap_malloc(soap, strepsg.length()+1);
    strcpy(*pmsf->srsName, strepsg.c_str());

    if(bgeom.view()["nring"] && bgeom.view()["ngeom"])
    {
        be_ring = bgeom.view()["nring"].get_array();
        ngeom = bgeom.view()["ngeom"].get_int32();        
    }


    //for nGeom
    for(i=0; i<ngeom; i++)
    {
        int nring = 0;
        gml__SurfacePropertyType *psf = soap_new_gml__SurfacePropertyType(soap,-1);
        if(!psf){
            fprintf(stderr, "Allocation of SurfacePropertyType pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }

        __gml__SurfacePropertyType_sequence *sfseq = soap_new___gml__SurfacePropertyType_sequence(soap);
        if(!sfseq){
            fprintf(stderr, "Allocation of SurfacePropertyType_sequence pointer failed\n");
            soap->error = SOAP_NULL;
            return NULL;
        }

        sfseq->__unionAbstractSurface = 7;

        char coord[20];
        //s.clear();
        sprintf(coord,"coordinates%d",i);
        //s << "coordinates" << i; 
        auto begeo = bgeom.view()[coord];
        if(!begeo) {
            fprintf(stderr, "Missing or corrupted DB geometry element\n");
            soap->error = SOAP_NULL;
            return NULL;
        }

        nring = be_ring[i].length();
        if(0 == nring)
        {
            fprintf(stderr, "Missing or corrupted number of ring value (nring)\n");
            soap->error = SOAP_NULL;
            return NULL;
        }
         
        sfseq->union_SurfacePropertyType.Polygon = init_gml_PolygonType(soap, begeo, bbox, nring, outcrs);

        psf->__SurfacePropertyType_sequence = sfseq;
        pmsf->surfaceMember.insert(pmsf->surfaceMember.begin(), psf);
    }//end for nGeom

    return pmsf;
}

gml__PolygonType * init_gml_PolygonType(struct soap *soap, element belem,  double bbox[], int nbRing=1, int outcrs=4326)
{
    gml__PolygonType *ppoly = soap_new_gml__PolygonType(soap);   
    char sxy[50] = "";

    string coord;
    double x, y;

    // Récupération des coordonnées de l'enveloppe extérieure dans un tableau
    if (belem.type() != bsoncxx::type::k_array){
        fprintf(stderr, "Missing or corrupted DB geometry element\n");
        soap->error = SOAP_NULL;
        return NULL;
    }
    bsoncxx::array::view vecbe = belem.get_array();

    //Initialisation de l'attribut srsName correspondant à la projection de la géométrie
    ppoly->srsName = (char**)soap_malloc(soap, sizeof(char**));
    coord.assign("urn:ogc:def:crs:EPSG::");

    // Init of coordinates transformation parameters
    OGRSpatialReference oSourceSRS, oTargetSRS;
    OGRCoordinateTransformation *poCT = NULL;
    oTargetSRS.importFromEPSGA(outcrs); // Système demandé par le client

    if(outcrs != 4326) {
        oSourceSRS.importFromEPSGA(4326);   // Données stockées en DB en coordonnées géographiques
        poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
    }

    sprintf(sxy,"%d",outcrs);
    coord.append(sxy);

    *ppoly->srsName = (char*)soap_malloc(soap, coord.length()+1);
    strcpy(*ppoly->srsName, coord.c_str());

    coord.clear();

    gml__AbstractRingPropertyType *pabring;
    gml__LinearRingType * pring;
    gml__DirectPositionListType *posList;
    ULONG64 *npos;

    //Initialisation de l'attribut srsDimension correspondant au nombre de dimension du polygone
    //A revoir pour tenir compte du cas 3D !!!
    ULONG64 *nsrs = (ULONG64 *)soap_malloc(soap, sizeof(ULONG64));
    *nsrs = 2;

    for(int j=0; j < nbRing; j++)
    {
        pabring = soap_new_gml__AbstractRingPropertyType(soap);
        pring = soap_new_gml__LinearRingType(soap);
        posList = soap_new_gml__DirectPositionListType(soap);
        npos =  (ULONG64 *)soap_malloc(soap, sizeof(ULONG64));

        auto b1 = vecbe[j];
        *npos = vecbe[j].length();
        posList->count = npos;
        posList->srsDimension = nsrs;

        for (unsigned int i = 0; i<*npos; i++)
        {            
            /* This works only with simple polygon without holes */
            /*sprintf(sxy, "%.10f %.10f ",
                 be[i].Array()[0].number(),
                 be[i].Array()[1].number() );
            posList->__item.append(sxy);*/

            /* Add the 3D case */
            coord = b1[i].get_utf8().value.to_string();
            sscanf(coord.substr(2,coord.length()-9).c_str(),"%lf, %lf,", &x, &y);

            if ( (bbox[0] < 0.0000001 && bbox[1] < 0.0000001) )
            {
                //initialisation of a bbox with first coordinates
                bbox[0] = x;
                bbox[1] = y;
            } else {
                if(x - bbox[2] > 0.000001)
                    bbox[2] = x;
                else if(x - bbox[0] < 0.000001)
                    bbox[0] = x;

                if(y - bbox[3] > 0.000001)
                    bbox[3] = y;
                else if(y - bbox[1] < 0.000001)
                    bbox[1] = y;
            }

            /* This code enables coordinates reprojection using OGR */
            if( poCT != NULL ) {
                if(!poCT->Transform( 1, &x, &y ) )
                    printf( "Transformation failed.\n" );
            }
            if(oTargetSRS.EPSGTreatsAsLatLong())
                sprintf(sxy, "%.8f %.8f ", y, x);
            else
                sprintf(sxy, "%.4f %.4f ", x, y);
            posList->__item.append(sxy);

        } //end for

        //if (nbRing>1)
            //b1.empty();

        pring->__union_LinearRingType = 2;
        pring->union_LinearRingType.posList = posList;
        pabring->__unionAbstractRing = 2;
        pabring->union_AbstractRingPropertyType.LinearRing = pring;

        if (j == 0) {
            ppoly->exterior = pabring;
        }
        else
        {
            ppoly->interior.insert(ppoly->interior.end(), pabring);
        }

    }//end for j
    return ppoly;
}

//init_gml_MultiCurvePropertyType

gml__LineStringType * init_gml_LineStringType(struct soap *soap, element belem, int outcrs,  double bbox[])
{
    string stmp;
    char sName[30];
    gml__LineStringType *plstring = soap_new_gml__LineStringType(soap,-1);

    //choice of DirectListPositionType
    plstring->__union_LineStringType = 2;

    //Initialisation de l'attribut srsName correspondant à la projection de la géométrie
    plstring->srsName = (char**)soap_malloc(soap, sizeof(char**));
    stmp.assign("urn:ogc:def:crs:EPSG::");
    sprintf(sName,"%d",outcrs);
    stmp.append(sName);
    *plstring->srsName = (char*)soap_malloc(soap, stmp.length()+1);
    strcpy(*plstring->srsName, stmp.c_str());

    plstring->union_LineStringType.posList = init_gml__DirectPositionListType(soap, belem, outcrs, bbox);

    return plstring;
}

gml__PointType * init_gml_PointType(struct soap *soap, element belem, int outcrs, double bbox[])
{
    string stmp;
    char sName[30];
    gml__PointType *ppt = soap_new_gml__PointType(soap,-1);

    //choice of DirectPositionType
    ppt->__union_PointType = 1;

    //Initialisation de l'attribut srsName correspondant à la projection de la géométrie
    ppt->srsName = (char**)soap_malloc(soap, sizeof(char**));
    stmp.assign("urn:ogc:def:crs:EPSG::");
    sprintf(sName,"%d",outcrs);
    stmp.append(sName);
    *ppt->srsName = (char*)soap_malloc(soap, stmp.length()+1);
    strcpy(*ppt->srsName, stmp.c_str());

    ppt->union_PointType.pos = init_gml__DirectPositionType(soap, belem, outcrs, bbox);

    return ppt;
}

gml__DirectPositionListType * init_gml__DirectPositionListType(struct soap *soap, element belem, int outcrs, double bbox[])
{
    ULONG64 *npos;
    char sxy[50] = "";
    string coord;
    double x, y;

    if(belem.type() == bsoncxx::type::k_array) {
        // Set coordinates list in an array
        //std::vector<BSONElement> vecbe = belem.Array();
        bsoncxx::array::view vecbe = belem.get_array();
        
        // Init of coordinates transformation parameters
        OGRSpatialReference oSourceSRS, oTargetSRS;
        OGRCoordinateTransformation *poCT = NULL;

        oTargetSRS.importFromEPSGA(outcrs); // Système demandé par le client

        if(outcrs != 4326)
        {
            oSourceSRS.importFromEPSGA(4326);   // Données stockées en DB en coordonnées géographiques
            poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
        }

        gml__DirectPositionListType *posList = soap_new_gml__DirectPositionListType(soap,-1);
        if(!posList)
        {
            fprintf(stderr, "LineString : Allocation of DirectPositionListType pointer failed\n");
            return NULL;
        }

        //Initialisation de l'attribut srsDimension correspondant au nombre de dimension du polygone
        //A revoir pour tenir compte du cas 3D !!!
        ULONG64 *nsrs = (ULONG64 *)soap_malloc(soap, sizeof(ULONG64));
        *nsrs = 2;

        if(!vecbe.empty())
        {
            auto b1 = vecbe[0];

            if (b1)
            {
                npos = (ULONG64 *)soap_malloc(soap, sizeof(ULONG64));
                if (npos)
                    *npos = b1.length();
                posList->count = npos;
                posList->srsDimension = nsrs;

                for (unsigned int i = 0; i<*npos; i++)
                {
                    /* Add the 3D case */
                    coord = b1[i].get_utf8().value.to_string();
                    sscanf(coord.substr(2,coord.length()-9).c_str(),"%lf, %lf,", &x, &y);

                    if ( (bbox[0] < 0.0000001 && bbox[1] < 0.0000001 && bbox[2] < 0.0000001 && bbox[3] < 0.0000001) )
                    {
                        //initialisation of a bbox with first coordinates
                        bbox[0] = x;
                        bbox[1] = y;
                        bbox[2] = x;
                        bbox[3] = y;
                    } else {
                        if(x - bbox[2] > 0.000001)
                            bbox[2] = x;
                        else if(x - bbox[0] < 0.000001)
                            bbox[0] = x;

                        if(y - bbox[3] > 0.000001)
                            bbox[3] = y;
                        else if(y - bbox[1] < 0.000001)
                            bbox[1] = y;
                    }

                    /* This code enables coordinates reprojection using OGR */
                    if( poCT != NULL ) {
                        if(!poCT->Transform( 1, &x, &y ) )
                            printf( "Transformation failed.\n" );
                    }
                    if(oTargetSRS.EPSGTreatsAsLatLong())
                        sprintf(sxy, "%.8f %.8f ", y, x);
                    else
                        sprintf(sxy, "%.4f %.4f ", x, y);

                    posList->__item.append(sxy);
                }//end for
            }
        }
        return posList;
    }

    return NULL;
}

gml__DirectPositionType * init_gml__DirectPositionType(struct soap *soap, element belem, int outcrs, double bbox[])
{
    char sxy[50] = "";
    string coord;
    double x, y;

    bsoncxx::array::view vecbe = belem.get_array();
    
    gml__DirectPositionType *pos = soap_new_gml__DirectPositionType(soap,-1);
    if(!pos)
    {
        fprintf(stderr, "LineString : Allocation of DirectPositionType pointer failed\n");
        return NULL;
    }
    if(!vecbe.empty())
    {
        auto b1 = vecbe[0];

        if (b1)
        {
            // Init of coordinates transformation parameters
            OGRSpatialReference oSourceSRS, oTargetSRS;
            OGRCoordinateTransformation *poCT = NULL;

            oTargetSRS.importFromEPSGA(outcrs); // Système demandé par le client
            if(outcrs != 4326)
            {
                oSourceSRS.importFromEPSGA(4326);   // Données stockées en DB en coordonnées géographiques
                poCT = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );
            }

            coord = b1[0].get_utf8().value.to_string();
            sscanf(coord.substr(2,coord.length()-9).c_str(),"%lf, %lf,", &x, &y);

            // we encountered a point
            //We chek the case if the bbox is still 0,0,0,0
            if ( (bbox[0] < 0.0000001 && bbox[1] < 0.0000001 && bbox[2] < 0.0000001 && bbox[3] < 0.0000001) )
            {
                //creation of a bbox avoiding null surface area
                bbox[0] = x - 0.001;
                bbox[2] = x + 0.001;
                bbox[1] = y - 0,001;
                bbox[3] = y + 0.001;
            } else {
                if(x - bbox[2] > 0.000001)
                    bbox[2] = x;
                else if(x - bbox[0] < 0.000001)
                    bbox[0] = x;

                if(y - bbox[3] > 0.000001)
                    bbox[3] = y;
                else if(y - bbox[1] < 0.000001)
                    bbox[1] = y;
            }

            if( poCT != NULL ) {
                if(!poCT->Transform( 1, &x, &y ) )
                    printf( "Transformation failed.\n" );
            }
            if(oTargetSRS.EPSGTreatsAsLatLong())
                sprintf(sxy, "%.8f %.8f ", y, x);
            else
                sprintf(sxy, "%.4f %.4f ", x, y);
            pos->__item.append(sxy);
        }
    }//vecbe

    return pos;
}
