/* soapServer.cpp
   Generated by gSOAP 2.8.92 for ws-inspire-wfs2.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapServer.cpp ver 2.8.92 2020-04-17 08:58:41 GMT")
extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	soap->keep_alive = soap->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (soap->keep_alive > 0 && soap->max_keep_alive > 0)
			soap->keep_alive--;
#endif
		if (soap_begin_serve(soap))
		{	if (soap->error >= SOAP_STOP)
				continue;
			return soap->error;
		}
		if ((soap_serve_request(soap) || (soap->fserveloop && soap->fserveloop(soap))) && soap->error && soap->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:CreateStoredQuery"))
		return soap_serve___f2i_plu__wfs_x002ecreateStoredQuery(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:DescribeFeatureType"))
		return soap_serve___f2i_plu__wfs_x002edescribeFeatureType(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:GetFeature"))
		return soap_serve___f2i_plu__wfs_x002egetFeature(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:DescribeStoredQueries"))
		return soap_serve___f2i_plu__wfs_x002edescribeStoredQueries(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:ListStoredQueries"))
		return soap_serve___f2i_plu__wfs_x002elistStoredQueries(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:DropStoredQuery"))
		return soap_serve___f2i_plu__wfs_x002edropStoredQuery(soap);
	if (!soap_match_tag(soap, soap->tag, "ows:GetCapabilities"))
		return soap_serve___f2i_plu__wfs_x002egetCapabilities(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:GetFeatureWithLock"))
		return soap_serve___f2i_plu__wfs_x002egetFeatureWithLock(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:GetPropertyValue"))
		return soap_serve___f2i_plu__wfs_x002egetPropertyValue(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:LockFeature"))
		return soap_serve___f2i_plu__wfs_x002elockFeature(soap);
	if (!soap_match_tag(soap, soap->tag, "wfs:Transaction"))
		return soap_serve___f2i_plu__wfs_x002etransaction(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002ecreateStoredQuery(struct soap *soap)
{	struct __f2i_plu__wfs_x002ecreateStoredQuery soap_tmp___f2i_plu__wfs_x002ecreateStoredQuery;
	struct __f2i_plu__wfs_x002ecreateStoredQueryResponse soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse;
	soap_default___f2i_plu__wfs_x002ecreateStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse);
	soap_default___f2i_plu__wfs_x002ecreateStoredQuery(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQuery);
	if (!soap_get___f2i_plu__wfs_x002ecreateStoredQuery(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQuery, "-f2i-plu:wfs.createStoredQuery", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002ecreateStoredQuery(soap, soap_tmp___f2i_plu__wfs_x002ecreateStoredQuery.wfs__CreateStoredQuery, soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse.wfs__CreateStoredQueryResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	soap_serialize___f2i_plu__wfs_x002ecreateStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___f2i_plu__wfs_x002ecreateStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse, "-f2i-plu:wfs.createStoredQueryResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___f2i_plu__wfs_x002ecreateStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002ecreateStoredQueryResponse, "-f2i-plu:wfs.createStoredQueryResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002edescribeFeatureType(struct soap *soap)
{	struct __f2i_plu__wfs_x002edescribeFeatureType soap_tmp___f2i_plu__wfs_x002edescribeFeatureType;
	util__DescribeFeatureTypeResponseType util__DescribeFeatureTypeResponse;
	util__DescribeFeatureTypeResponse.soap_default(soap);
	soap_default___f2i_plu__wfs_x002edescribeFeatureType(soap, &soap_tmp___f2i_plu__wfs_x002edescribeFeatureType);
	if (!soap_get___f2i_plu__wfs_x002edescribeFeatureType(soap, &soap_tmp___f2i_plu__wfs_x002edescribeFeatureType, "-f2i-plu:wfs.describeFeatureType", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002edescribeFeatureType(soap, soap_tmp___f2i_plu__wfs_x002edescribeFeatureType.wfs__DescribeFeatureType, util__DescribeFeatureTypeResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	util__DescribeFeatureTypeResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || util__DescribeFeatureTypeResponse.soap_put(soap, "util:DescribeFeatureTypeResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || util__DescribeFeatureTypeResponse.soap_put(soap, "util:DescribeFeatureTypeResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002egetFeature(struct soap *soap)
{	struct __f2i_plu__wfs_x002egetFeature soap_tmp___f2i_plu__wfs_x002egetFeature;
	wfs__FeatureCollectionType wfs__FeatureCollection;
	wfs__FeatureCollection.soap_default(soap);
	soap_default___f2i_plu__wfs_x002egetFeature(soap, &soap_tmp___f2i_plu__wfs_x002egetFeature);
	if (!soap_get___f2i_plu__wfs_x002egetFeature(soap, &soap_tmp___f2i_plu__wfs_x002egetFeature, "-f2i-plu:wfs.getFeature", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002egetFeature(soap, soap_tmp___f2i_plu__wfs_x002egetFeature.wfs__GetFeature, wfs__FeatureCollection);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__FeatureCollection.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__FeatureCollection.soap_put(soap, "wfs:FeatureCollection", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__FeatureCollection.soap_put(soap, "wfs:FeatureCollection", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002edescribeStoredQueries(struct soap *soap)
{	struct __f2i_plu__wfs_x002edescribeStoredQueries soap_tmp___f2i_plu__wfs_x002edescribeStoredQueries;
	wfs__DescribeStoredQueriesResponseType wfs__DescribeStoredQueriesResponse;
	wfs__DescribeStoredQueriesResponse.soap_default(soap);
	soap_default___f2i_plu__wfs_x002edescribeStoredQueries(soap, &soap_tmp___f2i_plu__wfs_x002edescribeStoredQueries);
	if (!soap_get___f2i_plu__wfs_x002edescribeStoredQueries(soap, &soap_tmp___f2i_plu__wfs_x002edescribeStoredQueries, "-f2i-plu:wfs.describeStoredQueries", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002edescribeStoredQueries(soap, soap_tmp___f2i_plu__wfs_x002edescribeStoredQueries.wfs__DescribeStoredQueries, wfs__DescribeStoredQueriesResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__DescribeStoredQueriesResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__DescribeStoredQueriesResponse.soap_put(soap, "wfs:DescribeStoredQueriesResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__DescribeStoredQueriesResponse.soap_put(soap, "wfs:DescribeStoredQueriesResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002elistStoredQueries(struct soap *soap)
{	struct __f2i_plu__wfs_x002elistStoredQueries soap_tmp___f2i_plu__wfs_x002elistStoredQueries;
	wfs__ListStoredQueriesResponseType wfs__ListStoredQueriesResponse;
	wfs__ListStoredQueriesResponse.soap_default(soap);
	soap_default___f2i_plu__wfs_x002elistStoredQueries(soap, &soap_tmp___f2i_plu__wfs_x002elistStoredQueries);
	if (!soap_get___f2i_plu__wfs_x002elistStoredQueries(soap, &soap_tmp___f2i_plu__wfs_x002elistStoredQueries, "-f2i-plu:wfs.listStoredQueries", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002elistStoredQueries(soap, soap_tmp___f2i_plu__wfs_x002elistStoredQueries.wfs__ListStoredQueries, wfs__ListStoredQueriesResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__ListStoredQueriesResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__ListStoredQueriesResponse.soap_put(soap, "wfs:ListStoredQueriesResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__ListStoredQueriesResponse.soap_put(soap, "wfs:ListStoredQueriesResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002edropStoredQuery(struct soap *soap)
{	struct __f2i_plu__wfs_x002edropStoredQuery soap_tmp___f2i_plu__wfs_x002edropStoredQuery;
	struct __f2i_plu__wfs_x002edropStoredQueryResponse soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse;
	soap_default___f2i_plu__wfs_x002edropStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse);
	soap_default___f2i_plu__wfs_x002edropStoredQuery(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQuery);
	if (!soap_get___f2i_plu__wfs_x002edropStoredQuery(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQuery, "-f2i-plu:wfs.dropStoredQuery", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002edropStoredQuery(soap, soap_tmp___f2i_plu__wfs_x002edropStoredQuery.wfs__DropStoredQuery, soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse.wfs__DropStoredQueryResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	soap_serialize___f2i_plu__wfs_x002edropStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___f2i_plu__wfs_x002edropStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse, "-f2i-plu:wfs.dropStoredQueryResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___f2i_plu__wfs_x002edropStoredQueryResponse(soap, &soap_tmp___f2i_plu__wfs_x002edropStoredQueryResponse, "-f2i-plu:wfs.dropStoredQueryResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002egetCapabilities(struct soap *soap)
{	struct __f2i_plu__wfs_x002egetCapabilities soap_tmp___f2i_plu__wfs_x002egetCapabilities;
	wfs__WFS_x005fCapabilitiesType wfs__WFS_x005fCapabilities;
	wfs__WFS_x005fCapabilities.soap_default(soap);
	soap_default___f2i_plu__wfs_x002egetCapabilities(soap, &soap_tmp___f2i_plu__wfs_x002egetCapabilities);
	if (!soap_get___f2i_plu__wfs_x002egetCapabilities(soap, &soap_tmp___f2i_plu__wfs_x002egetCapabilities, "-f2i-plu:wfs.getCapabilities", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002egetCapabilities(soap, soap_tmp___f2i_plu__wfs_x002egetCapabilities.ows__GetCapabilities, wfs__WFS_x005fCapabilities);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__WFS_x005fCapabilities.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__WFS_x005fCapabilities.soap_put(soap, "wfs:WFS_Capabilities", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__WFS_x005fCapabilities.soap_put(soap, "wfs:WFS_Capabilities", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002egetFeatureWithLock(struct soap *soap)
{	struct __f2i_plu__wfs_x002egetFeatureWithLock soap_tmp___f2i_plu__wfs_x002egetFeatureWithLock;
	wfs__FeatureCollectionType wfs__FeatureCollection;
	wfs__FeatureCollection.soap_default(soap);
	soap_default___f2i_plu__wfs_x002egetFeatureWithLock(soap, &soap_tmp___f2i_plu__wfs_x002egetFeatureWithLock);
	if (!soap_get___f2i_plu__wfs_x002egetFeatureWithLock(soap, &soap_tmp___f2i_plu__wfs_x002egetFeatureWithLock, "-f2i-plu:wfs.getFeatureWithLock", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002egetFeatureWithLock(soap, soap_tmp___f2i_plu__wfs_x002egetFeatureWithLock.wfs__GetFeatureWithLock, wfs__FeatureCollection);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__FeatureCollection.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__FeatureCollection.soap_put(soap, "wfs:FeatureCollection", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__FeatureCollection.soap_put(soap, "wfs:FeatureCollection", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002egetPropertyValue(struct soap *soap)
{	struct __f2i_plu__wfs_x002egetPropertyValue soap_tmp___f2i_plu__wfs_x002egetPropertyValue;
	wfs__ValueCollectionType wfs__ValueCollection;
	wfs__ValueCollection.soap_default(soap);
	soap_default___f2i_plu__wfs_x002egetPropertyValue(soap, &soap_tmp___f2i_plu__wfs_x002egetPropertyValue);
	if (!soap_get___f2i_plu__wfs_x002egetPropertyValue(soap, &soap_tmp___f2i_plu__wfs_x002egetPropertyValue, "-f2i-plu:wfs.getPropertyValue", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002egetPropertyValue(soap, soap_tmp___f2i_plu__wfs_x002egetPropertyValue.wfs__GetPropertyValue, wfs__ValueCollection);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__ValueCollection.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__ValueCollection.soap_put(soap, "wfs:ValueCollection", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__ValueCollection.soap_put(soap, "wfs:ValueCollection", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002elockFeature(struct soap *soap)
{	struct __f2i_plu__wfs_x002elockFeature soap_tmp___f2i_plu__wfs_x002elockFeature;
	wfs__LockFeatureResponseType wfs__LockFeatureResponse;
	wfs__LockFeatureResponse.soap_default(soap);
	soap_default___f2i_plu__wfs_x002elockFeature(soap, &soap_tmp___f2i_plu__wfs_x002elockFeature);
	if (!soap_get___f2i_plu__wfs_x002elockFeature(soap, &soap_tmp___f2i_plu__wfs_x002elockFeature, "-f2i-plu:wfs.lockFeature", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002elockFeature(soap, soap_tmp___f2i_plu__wfs_x002elockFeature.wfs__LockFeature, wfs__LockFeatureResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__LockFeatureResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__LockFeatureResponse.soap_put(soap, "wfs:LockFeatureResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__LockFeatureResponse.soap_put(soap, "wfs:LockFeatureResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___f2i_plu__wfs_x002etransaction(struct soap *soap)
{	struct __f2i_plu__wfs_x002etransaction soap_tmp___f2i_plu__wfs_x002etransaction;
	wfs__TransactionResponseType wfs__TransactionResponse;
	wfs__TransactionResponse.soap_default(soap);
	soap_default___f2i_plu__wfs_x002etransaction(soap, &soap_tmp___f2i_plu__wfs_x002etransaction);
	if (!soap_get___f2i_plu__wfs_x002etransaction(soap, &soap_tmp___f2i_plu__wfs_x002etransaction, "-f2i-plu:wfs.transaction", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __f2i_plu__wfs_x002etransaction(soap, soap_tmp___f2i_plu__wfs_x002etransaction.wfs__Transaction, wfs__TransactionResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	wfs__TransactionResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || wfs__TransactionResponse.soap_put(soap, "wfs:TransactionResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || wfs__TransactionResponse.soap_put(soap, "wfs:TransactionResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapServer.cpp */
