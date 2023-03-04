//----------------------------------------------------------------------------//
//																			  //
//	Project : Tantra game resource manager      							  //
//	Purpose : resource manager impls.                              			  //
//	File	: HTMapObjResMgr.h      										  //
//	Author	: salsaly														  //
//	History : 2003/10/07, Initiated by Assrada 								  //
//				- init                                         				  //
//																			  //
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.			  //
//----------------------------------------------------------------------------//
#ifndef _HTMAPOBJRESMGR_H
#define _HTMAPOBJRESMGR_H

//#include "HTResMgr.h"
#define HT_MAX_XML_STR 40

class CHTObjResMgr
{
public:
	CHTObjResMgr();
	~CHTObjResMgr();

	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetCamCollision( HTdword dwID, HTbool& bCamCollision );

	HTRESULT	HT_hrLoad( CHTString& strFile );
	HTRESULT	HT_hrSave( CHTString& strFile );
	HTRESULT	HT_hrInit( CHTString& strXMLFile );

private:

	struct HT_ResTableObjs
	{
		HTtchar   	szFileName[HT_MAX_XML_STR];
		HTbool		bCamCollision;
	};

	std::map<HTdword,HT_ResTableObjs*> m_mapTable;
};

#endif