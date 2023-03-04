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

#include "stdAfx.h"
#include "HTIDDef.h"
#include "HTObjResMgr.h"

#include "..\..\engine\HTUtilLib\HTFile.h"
#include "..\..\engine\HTUtilLib\HTXMLParser.h"

#define HT_OBJS_TABLENAME	_T("Objs")

//--------------------------------------------------------------------------------
// Map & Objects 리소스 관리
//--------------------------------------------------------------------------------
CHTObjResMgr::CHTObjResMgr(){}

CHTObjResMgr::~CHTObjResMgr()
{
	std::map<HTdword,HT_ResTableObjs*>::iterator it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}


HTbool
CHTObjResMgr::HT_bGetFileName( HTdword dwID, CHTString& strFile )
{
	std::map<HTdword,HT_ResTableObjs*>::iterator it = m_mapTable.find( dwID );
	if ( it != m_mapTable.end() )
	{
		if ( it->second )
		{
			strFile = (it->second)->szFileName;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTObjResMgr::HT_bGetCamCollision( HTdword dwID, HTbool& bCamCollision )
{
	std::map<HTdword,HT_ResTableObjs*>::iterator it = m_mapTable.find( dwID );
	if ( it != m_mapTable.end() )
	{
		if ( it->second )
		{
			bCamCollision = (it->second)->bCamCollision;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTRESULT	
CHTObjResMgr::HT_hrLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) )
	{
		HTbyte bVersion;
		oLoadFile.HT_bRead( &bVersion );
		if ( bVersion != 1 ) return HT_FAIL;

		HTint iRecordCount;
		oLoadFile.HT_bRead( &iRecordCount );

		HT_ResTableObjs* pRecord = HT_NULL;
		HTint iID;
		for ( HTint i = 0; i < iRecordCount; ++i )
		{
			pRecord = new HT_ResTableObjs;

			oLoadFile.HT_bRead( &iID );
			oLoadFile.HT_bRead( pRecord, sizeof(HT_ResTableObjs) );

			m_mapTable.insert( std::map<HTdword,HT_ResTableObjs*>::value_type( (HTdword)iID, pRecord ) );
		}

		oLoadFile.HT_vClose();

		return HT_OK;
	}
	else return HT_FAIL;
}

HTRESULT
CHTObjResMgr::HT_hrSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	if ( oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
	{
		HTbyte bVersion;
		bVersion = 1;
		oSaveFile.HT_bWrite( bVersion );

		HTint iRecordCount = (HTint)m_mapTable.size();
		oSaveFile.HT_bWrite( iRecordCount );

		HTint iID;
		std::map<HTdword,HT_ResTableObjs*>::iterator it;

		it = m_mapTable.begin();
		while ( it != m_mapTable.end() )
		{
			iID = it->first;

			oSaveFile.HT_bWrite( iID );
			oSaveFile.HT_bWrite( it->second, sizeof(HT_ResTableObjs) );

			it++;
		}

		oSaveFile.HT_vClose();
		return HT_OK;
	}
	else return HT_FAIL;
}

HTRESULT
CHTObjResMgr::HT_hrInit( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s 파일을 열지 못했습니다.", strXMLFile.HT_szGetString());
		MessageBox( NULL, str, "HTObjResMgr", MB_OK );
		return ( HT_FAIL );
	}

	HT_ResTableObjs* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;
	CHTString strTable( HT_OBJS_TABLENAME );

	HTuint nItems = oXML.HT_nGetTableRowCount( strTable );
	--nItems;

	if ( nItems > 0 )
	{
		for ( HTuint i = 0; i < nItems; ++i )
		{
			pRecord = new HT_ResTableObjs;

			strCell = _T("ID");				oXML.HT_hrGetTableValue( strTable, strCell, i, &iID );
			strCell = _T("File");			oXML.HT_hrGetTableValue( strTable, strCell, i, pRecord->szFileName );
			strCell = _T("CamCollision");	oXML.HT_hrGetTableValue( strTable, strCell, i, &iTemp ); pRecord->bCamCollision = ( iTemp > 0 ) ? HT_TRUE : HT_FALSE;

			m_mapTable.insert( std::map<HTdword,HT_ResTableObjs*>::value_type( (HTdword)iID, pRecord ) );
		}

		return HT_OK;
	}
	else return HT_FAIL;
}