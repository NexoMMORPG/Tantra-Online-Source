//----------------------------------------------------------------------------//
//																			  //
//	Project : Tantra game resource manager      							  //
//	Purpose : resource manager impls.                              			  //
//	File	: HTResMgr.h      												  //
//	Author	: Assrada														  //
//	History : 2002/09/25, Initiated by Assrada 								  //
//				- init                                         				  //
//																			  //
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.			  //
//----------------------------------------------------------------------------//

#include "stdAfx.h"
#include "HTIDDef.h"
#include "HTResMgr.h"

#include "..\..\engine\HTUtilLib\HTFile.h"

#include "..\..\engine\HTUtilLib\HTXMLParser.h"

//-----------------------------------------------------------------------------
// Name		:	CHTResMgr()
// Desc		:	Constructor
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResMgr::CHTResMgr()
{
}

//-----------------------------------------------------------------------------
// Name		:	~CHTResMgr()
// Desc		:	Destructor
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResMgr::~CHTResMgr()
{
	HT_ResMgr_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		HT_DELETEARRAY( (HTtchar*)it->first );
		HT_DELETE( it->second );
		it = m_mapTables.erase( it );
	}
}

//-----------------------------------------------------------------------------
// Name		:	HT_hrInit()
// Desc		:	read xml files and load all resource table!
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
HTRESULT CHTResMgr::HT_hrInit( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
		return ( HT_FAIL );

	// load resource tables!
	CHTBaseResTable* pTable = HT_NULL;
	CHTString strTable;

	strTable = HT_RES_TABLENAME_PCTMD;
	pTable = new CHTResTableType21;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCMESH;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCTEX;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCANI;
	pTable = new CHTResTableType23;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCSTATEANI;
	pTable = new CHTResTableType08;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCATTACKANI;
	pTable = new CHTResTableType20;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MAP;
	pTable = new CHTResTableType02;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MATERIAL;
	pTable = new CHTResTableType03;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_CHARACTER;
	pTable = new CHTResTableType04;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_HEAD;
	pTable = new CHTResTableType05;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	//strTable = HT_RES_TABLENAME_WEAR;
	//pTable = new CHTResTableType06;
	//if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	//{
	//	HTtchar* szTableName = new HTtchar[HT_MAX_STR];
	//	CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
	//	m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	//}
	//else
	//	HT_DELETE( pTable );
	strTable = HT_RES_TABLENAME_UP_WEAR;
	pTable = new CHTResTableType061;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_DOWN_WEAR;
	pTable = new CHTResTableType062;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_HAND_WEAR;
	pTable = new CHTResTableType063;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_SHOES;
	pTable = new CHTResTableType07;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	//strTable = HT_RES_TABLENAME_WEARITEM;
	//pTable = new CHTResTableType08;
	//if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	//{
	//	HTtchar* szTableName = new HTtchar[HT_MAX_STR];
	//	CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
	//	m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	//}
	//else
	//	HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_UP_WEARITEM;
	pTable = new CHTResTableType081;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_DOWN_WEARITEM;
	pTable = new CHTResTableType081;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_HAND_WEARITEM;
	pTable = new CHTResTableType081;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_SHOESITEM;
	pTable = new CHTResTableType081;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ITEM;
	pTable = new CHTResTableType11;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ITEMTMD;
	pTable = new CHTResTableType21;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ITEMTEX;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_NPC;
	pTable = new CHTResTableType09;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_NPCTMD;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_NPCANI;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MONSTER;
	pTable = new CHTResTableType10;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MONTMD;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MONTEX;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MONANI;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_BGM;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_PCSOUND;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_NPCSOUND;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_MONSTERSOUND;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ITEMSOUND;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ETCSOUND;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	//strTable = HT_RES_TABLENAME_OBJTMD;
	//pTable = new CHTResTableType15;
	//if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	//{
	//	HTtchar* szTableName = new HTtchar[HT_MAX_STR];
	//	CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
	//	m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	//}
	//else
	//	HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_UIINTRO;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_UIMAIN;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_FXMON;
	pTable = new CHTResTableType13;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	//strTable = HT_RES_TABLENAME_FXFIELD;
	//pTable = new CHTResTableType14;
	//if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	//{
	//	HTtchar* szTableName = new HTtchar[HT_MAX_STR];
	//	CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
	//	m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	//}
	//else
	//	HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_3DSPR;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ETCTEX;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 길드
	strTable = HT_RES_TABLENAME_GUILDMARK_BACK;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_GUILDMARK_EMBLEM;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_GUILDMARK_TITLE;
	pTable = new CHTResTableType01;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_GUILDMARK_COLOR;
	pTable = new CHTResTableType24;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 지역표시
	strTable = HT_RES_TABLENAME_AREA_INDICATE;
	pTable = new CHTResTableType25;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_ITEMREFINING;
	pTable = new CHTResTableType26;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	strTable = HT_RES_TABLENAME_FOOTSOUND;
	pTable = new CHTResTableType27;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT	
CHTResMgr::HT_hrLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) )
		return ( HT_FAIL );

	HTbyte bVersion;
	oLoadFile.HT_bRead( &bVersion );
	// version check!
	if ( bVersion != 1 )
	{
		return ( HT_FAIL );
	}

	HTint iSheetCount;
	oLoadFile.HT_bRead( &iSheetCount );

	CHTBaseResTable* pTable = HT_NULL;
	CHTString strTable;
	HTbyte bType;

	for ( HTint i = 0; i < iSheetCount; i++ )
	{
		oLoadFile.HT_bRead( (HTtchar*)strTable, HT_MAX_STR );
		oLoadFile.HT_bRead( &bType );
		switch( bType ) 
		{
		case 1:
			pTable = new CHTResTableType01;
			break;
		case 2:
			pTable = new CHTResTableType02;
			break;
		case 3:
			pTable = new CHTResTableType03;
			break;
		case 4:
			pTable = new CHTResTableType04;
			break;
		case 5:
			pTable = new CHTResTableType05;
			break;
			//case 6:
			//	pTable = new CHTResTableType06;
			//	break;
		case 61:
			pTable = new CHTResTableType061;
			break;
		case 62:
			pTable = new CHTResTableType062;
			break;
		case 63:
			pTable = new CHTResTableType063;
			break;
		case 7:
			pTable = new CHTResTableType07;
			break;
		case 8:
			pTable = new CHTResTableType08;
			break;
		case 81:
			pTable = new CHTResTableType081;
			break;
		case 9:
			pTable = new CHTResTableType09;
			break;
		case 10:
			pTable = new CHTResTableType10;
			break;
		case 11:
			pTable = new CHTResTableType11;
			break;
		case 13:
			pTable = new CHTResTableType13;
			break;
			//case 15:
			//	pTable = new CHTResTableType15;
			//	break;
		case 20:
			pTable = new CHTResTableType20;
			break;
		case 21:
			pTable = new CHTResTableType21;
			break;
		case 23:
			pTable = new CHTResTableType23;
			break;
		case 24:
			pTable = new CHTResTableType24;
			break;
		case 25:
			pTable = new CHTResTableType25;
			break;
		case 26:
			pTable = new CHTResTableType26;
			break;
		case 27:
			pTable = new CHTResTableType27;
			break;

//fors_debug 249 is what?
		default:
			oLoadFile.HT_vClose();
			return ( HT_FAIL );
		}

		if ( HT_SUCCEED( pTable->HT_hrLoad( &oLoadFile, strTable ) ) )
		{
			HTtchar* szTableName = new HTtchar[HT_MAX_STR];
			CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
			m_mapTables.insert( HT_ResMgr_Value( szTableName, pTable ) );
		}
		else
			HT_DELETE( pTable );
	}

	oLoadFile.HT_vClose();

	return( HT_OK );
}

HTRESULT
CHTResMgr::HT_hrSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
		return ( HT_FAIL );

	HTbyte bVersion;
	bVersion = 1;
	oSaveFile.HT_bWrite( bVersion );

	HTint iSheetCount;
	iSheetCount = (HTint)m_mapTables.size();
	oSaveFile.HT_bWrite( iSheetCount );

	HT_ResMgr_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		oSaveFile.HT_bWrite( (HTtchar*)it->first, HT_MAX_STR );	// sheet name

		if ( HT_FAILED( (it->second)->HT_hrSave( &oSaveFile ) ) )
		{
		}

		it++;
	}

	oSaveFile.HT_vClose();

	return( HT_OK );
}

HTtchar* CHTResMgr::HT_pGetTableName( HTdword dwID )
{
	if ( HT_IS_CHARACTER( dwID ) )
		return ( HT_RES_TABLENAME_CHARACTER );
	else if ( HT_IS_NPC( dwID ) )
		return ( HT_RES_TABLENAME_NPC );
	else if ( HT_IS_MONSTER( dwID ) )
		return ( HT_RES_TABLENAME_MONSTER );
	else if ( HT_IS_HEAD( dwID ) )
		return ( HT_RES_TABLENAME_HEAD );
	else if ( HT_IS_UP_WEAR( dwID ) )
		return ( HT_RES_TABLENAME_UP_WEAR );
	else if ( HT_IS_DOWN_WEAR( dwID ) )
		return ( HT_RES_TABLENAME_DOWN_WEAR );
	else if ( HT_IS_HAND_WEAR( dwID ) )
		return ( HT_RES_TABLENAME_HAND_WEAR );
	else if ( HT_IS_SHOES( dwID ) )
		return ( HT_RES_TABLENAME_SHOES );
	else if ( HT_IS_CHARACTERSTATEANI( dwID ) )
		return ( HT_RES_TABLENAME_PCSTATEANI );
	else if ( HT_IS_CHARACTERANI( dwID ) )
		return ( HT_RES_TABLENAME_PCANI );
	else if ( HT_IS_CHARACTERTMD( dwID ) )
		return ( HT_RES_TABLENAME_PCTMD );
	else if ( HT_IS_CHARACTERMESHTMD( dwID ) )
		return ( HT_RES_TABLENAME_PCMESH );
	else if ( HT_IS_CHARACTERTEX( dwID ) )
		return ( HT_RES_TABLENAME_PCTEX );
	else if ( HT_IS_UPWEARITEM( dwID ) )
		return ( HT_RES_TABLENAME_UP_WEARITEM );
	else if ( HT_IS_DOWNWEARITEM( dwID ) )
		return ( HT_RES_TABLENAME_DOWN_WEARITEM );
	else if ( HT_IS_HANDWEARITEM( dwID ) )
		return ( HT_RES_TABLENAME_HAND_WEARITEM );
	else if ( HT_IS_SHOESITEM( dwID ) )
		return ( HT_RES_TABLENAME_SHOESITEM );
	else if ( HT_IS_ITEM( dwID ) )
		return ( HT_RES_TABLENAME_ITEM );
	else if ( HT_IS_ITEM_TMD( dwID ) )
		return ( HT_RES_TABLENAME_ITEMTMD );
	else if ( HT_IS_ITEM_TEX( dwID ) )
		return ( HT_RES_TABLENAME_ITEMTEX );
	else if ( HT_IS_MAP( dwID ) )
		return ( HT_RES_TABLENAME_MAP );
	else if ( HT_IS_MATERIAL( dwID ) )
		return ( HT_RES_TABLENAME_MATERIAL );
	else if ( HT_IS_NPC_TMD( dwID ) )
		return ( HT_RES_TABLENAME_NPCTMD );
	else if ( HT_IS_MONSTER_TMD( dwID ) )
		return ( HT_RES_TABLENAME_MONTMD );
	else if ( HT_IS_MONSTER_TEX( dwID ) )
		return ( HT_RES_TABLENAME_MONTEX );
	else if ( HT_IS_NPC_ANI( dwID ) )
		return ( HT_RES_TABLENAME_NPCANI );
	else if ( HT_IS_MONSTER_ANI( dwID ) )
		return ( HT_RES_TABLENAME_MONANI );
	else if ( HT_IS_BGM( dwID ) )
		return ( HT_RES_TABLENAME_BGM );
	//else if ( HT_IS_OBJS( dwID ) )
	//	return ( HT_RES_TABLENAME_OBJTMD );
	else if ( HT_IS_UIINTRO( dwID ) )
		return ( HT_RES_TABLENAME_UIINTRO );
	else if ( HT_IS_UIMAIN( dwID ) )
		return ( HT_RES_TABLENAME_UIMAIN );
	else if ( HT_IS_ETC( dwID ) )
		return ( HT_RES_TABLENAME_ETCTEX );
	else if ( HT_IS_FXMON( dwID ) )			// 20021101 HK : 기획변경 파기
		return ( HT_RES_TABLENAME_FXMON );
	//else if ( HT_IS_FX_FIELD( dwID ) )			// 20021204 HK : Objs에 통합
	//	return ( HT_RES_TABLENAME_FXFIELD );
	else if ( HT_IS_3DSPR( dwID ) )
		return ( HT_RES_TABLENAME_3DSPR );
	else if ( HT_IS_CHARACTERATTACKANI( dwID ) )
		return ( HT_RES_TABLENAME_PCATTACKANI );
	else if ( HT_IS_PCSOUND( dwID ) )
		return ( HT_RES_TABLENAME_PCSOUND );
	else if ( HT_IS_NPCSOUND( dwID ) )
		return ( HT_RES_TABLENAME_NPCSOUND );
	else if ( HT_IS_ITEMSOUND( dwID ) )
		return ( HT_RES_TABLENAME_ITEMSOUND );
	else if ( HT_IS_MONSTERSOUND( dwID ) )
		return ( HT_RES_TABLENAME_MONSTERSOUND );
	else if ( HT_IS_ETCSOUND( dwID ) )
		return ( HT_RES_TABLENAME_ETCSOUND );
	else if ( HT_IS_GUILDMARK_BACK( dwID ) )
		return ( HT_RES_TABLENAME_GUILDMARK_BACK );
	else if ( HT_IS_GUILDMARK_EMBLEM( dwID ) )
		return ( HT_RES_TABLENAME_GUILDMARK_EMBLEM );
	else if ( HT_IS_GUILDMARK_TITLE( dwID ) )
		return ( HT_RES_TABLENAME_GUILDMARK_TITLE );
	else if ( HT_IS_GUILDMARK_COLOR( dwID ) )
		return ( HT_RES_TABLENAME_GUILDMARK_COLOR );
	else if ( HT_IS_AREA_INDICATE( dwID ) )
		return ( HT_RES_TABLENAME_AREA_INDICATE );
	else if ( HT_IS_ITEM_RIFINING( dwID ) )
		return ( HT_RES_TABLENAME_ITEMREFINING );
	else if ( HT_IS_FOOT_SOUND( dwID ) )
		return ( HT_RES_TABLENAME_FOOTSOUND );
	else
		return ( HT_NULL );
}

CHTBaseResTable* CHTResMgr::HT_pGetTable( HTdword dwID )
{
	HTtchar* pTable = HT_pGetTableName( dwID );
	if ( !pTable )
		return ( HT_NULL );

	HT_ResMgr_It it = m_mapTables.find( pTable );
	if ( it != m_mapTables.end() )
	{
		return ( it->second );
	}

	return ( HT_NULL );
}

//-----------------------------------------------------------------------------
// Name		:	GetResFileName()
// Desc		:	Find resource file name from ID
// Params	:	id - search ID, fileName - found resource file name
// Returns	:	true / false
//-----------------------------------------------------------------------------
HTbool CHTResMgr::HT_bGetFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );

	if ( pTable )
		return ( pTable->HT_bGetFileName( dwID, strFile ) );

	return ( HT_FALSE );
}

HTdword CHTResMgr::HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow )
{
	HT_ResMgr_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second )
			return ( (it->second)->HT_dwGetIDByIndex( idxRow ) );
	}

	return ( 0 );
}

HTuint CHTResMgr::HT_nGetItemCount( CHTString& strTable )
{
	HT_ResMgr_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second )
			return ( (it->second)->HT_nGetItemCount() );
	}

	return ( 0 );
}

HTbool CHTResMgr::HT_bGetTHMFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetTHMFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetTMOFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetTMOFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetTMEFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetTMEFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetTCCFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetTCCFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetCFGFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetCFGFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

// 20021106 대호
HTbool CHTResMgr::HT_bGetBMPFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetBMPFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetOBJPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetOBJPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetOBJTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetOBJTEXPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMONPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMONPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMONANIPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMONANIPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMONTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMONTEXPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNPCPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNPCPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNPCANIPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNPCANIPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNPCTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNPCTEXPAKFileName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetFXFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFXFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNPCSoundFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNPCSoundFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMonSoundFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonSoundFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMinimapFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMinimapFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNPCScriptFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNPCScriptFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool CHTResMgr::HT_bGetObjResFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetObjResFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool		
CHTResMgr::HT_bGetPopObjPackFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetPopObjPackFilesName( dwID, strName ) );
	return ( HT_FALSE );

}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool		
CHTResMgr::HT_bGetPopTexPackFilesName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetPopTexPackFilesName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMonFXID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonFXID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMonScale( HTdword dwID, HTfloat& fScale )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonScale( dwID, fScale ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMonColor( HTdword dwID, HT_COLOR& clrMon )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonColor( dwID, clrMon ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDiffuseColor( HTdword dwID, HT_COLOR& clrWant )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDiffuseColor( dwID, clrWant ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetAmbientColor( HTdword dwID, HT_COLOR& clrWant )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetAmbientColor( dwID, clrWant ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSpecularColor( HTdword dwID, HT_COLOR& clrWant )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSpecularColor( dwID, clrWant ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetEmissiveColor( HTdword dwID, HT_COLOR& clrWant )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetEmissiveColor( dwID, clrWant ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetPower( HTdword dwID, HTfloat& fPower )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetPower( dwID, fPower ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMaterialID( dwID, dwMtrlID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetModelFileID( dwID, dwModelFileID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeAID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeAID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeBID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeBID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeCID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeCID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeDID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeDID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeEID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeEID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeFID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeFID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeGID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeGID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHeadTypeHID( HTdword dwID, HTdword& dwHeadID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHeadTypeHID( dwID, dwHeadID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDefaultUpWearID( HTdword dwID, HTdword& dwWearID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDefaultUpWearID( dwID, dwWearID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDefaultDownWearID( HTdword dwID, HTdword& dwWearID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDefaultDownWearID( dwID, dwWearID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDefaultHandWearID( HTdword dwID, HTdword& dwWearID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDefaultHandWearID( dwID, dwWearID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDefaultShoesID( HTdword dwID, HTdword& dwShoesID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDefaultShoesID( dwID, dwShoesID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetFaceMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFaceMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetFaceTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFaceTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHairModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHairModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHairTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHairTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHairType( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHairType( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetUpWearMeshes( HTdword dwID,
							   HTdword& dwChestMesh, HTdword& dwChestTexID,
							   HTdword& dwRUArmMesh, HTdword& dwLUArmMesh, HTdword& dwRUArmTexID, HTdword& dwLUArmTexID,
							   HTdword& dwSkirtMesh, HTdword& dwSkirtTexID,
							   HTdword& dwApronModelID, HTdword& dwApronTexID, HTdword& dwApronBackModelID, HTdword& dwApronBackTexID,
							   HTdword& dwShoulderLModelID, HTdword& dwShoulderLTexID, HTdword& dwShoulderRModelID, HTdword& dwShoulderRTexID,
							   HTbool& bSkirtType )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetUpWearMeshes( dwID,
		dwChestMesh, dwChestTexID,
		dwRUArmMesh, dwLUArmMesh, dwRUArmTexID, dwLUArmTexID,
		dwSkirtMesh, dwSkirtTexID,
		dwApronModelID, dwApronTexID, dwApronBackModelID, dwApronBackTexID,
		dwShoulderLModelID, dwShoulderLTexID, dwShoulderRModelID, dwShoulderRTexID,
		bSkirtType ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetDownWearMeshes( HTdword dwID,
								 HTdword& dwPantsMesh, HTdword& dw2ndPantsMesh, HTdword& dwPantsTexID,
								 HTdword& dwKneeLModelID, HTdword& dwKneeLTexID, HTdword& dwKneeRModelID, HTdword& dwKneeRTexID,
								 HTdword& dwThighLModelID, HTdword& dwThighLTexID, HTdword& dwThighRModelID, HTdword& dwThighRTexID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDownWearMeshes( dwID,
		dwPantsMesh, dw2ndPantsMesh, dwPantsTexID,
		dwKneeLModelID, dwKneeLTexID, dwKneeRModelID, dwKneeRTexID,
		dwThighLModelID, dwThighLTexID, dwThighRModelID, dwThighRTexID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetHandWearMeshes( HTdword dwID,
								 HTdword& dwRLArmMesh, HTdword& dwLLArmMesh, HTdword& dwRLArmTexID, HTdword& dwLLArmTexID,
								 HTdword& dwRHandMesh, HTdword& dwLHandMesh, HTdword& dwRHandTexID, HTdword& dwLHandTexID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHandWearMeshes( dwID,
		dwRLArmMesh, dwLLArmMesh, dwRLArmTexID, dwLLArmTexID,
		dwRHandMesh, dwLHandMesh, dwRHandTexID, dwLHandTexID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetChestMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetChestMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetChestTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetChestTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetPantsMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetPantsMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetPantsTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetPantsTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRUArmMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRUArmMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLUArmMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLUArmMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRUArmTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRUArmTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLUArmTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLUArmTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRLArmMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRLArmMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLLArmMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLLArmMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRLArmTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRLArmTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLLArmTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLLArmTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRHandMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRHandMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLHandMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLHandMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRHandTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRHandTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLHandTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLHandTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSkirtMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSkirtMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSkirtTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSkirtTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetApronBackModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetApronBackModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetApronBackTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetApronBackTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetApronModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetApronModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetApronTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetApronTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetShoulderLModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetShoulderLModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetShoulderLTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetShoulderLTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetShoulderRModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetShoulderRModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetShoulderRTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetShoulderRTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetKneeLModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKneeLModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetKneeLTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKneeLTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetKneeRModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKneeRModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetKneeRTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKneeRTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetThighLModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetThighLModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetThighLTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetThighLTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetThighRModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetThighRModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetThighRTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetThighRTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRBootsMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRBootsMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetLBootsMesh( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetLBootsMesh( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetBootsTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetBootsTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetImpactFX( dwID, dwImpactFX ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetNAGID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetYAKID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetASUID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDEVID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetKIMID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetGANID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRAKID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetGARID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSTDAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetMOVAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMOVAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetWLKAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWLKAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetRUNAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRUNAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetIDLAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool // 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
CHTResMgr::HT_bGetStateSoundID( HTdword dwID, HTdword& dwStateSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetStateSoundID( dwID, dwStateSoundID ) );
	return ( HT_FALSE );
}

HTbool // 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
CHTResMgr::HT_bGetClickSoundID( HTdword dwID, HTdword& dwClickSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetClickSoundID( dwID, dwClickSoundID ) );
	return ( HT_FALSE );
}

HTbool // 20021103 HK : Idle 애니메이션이 시작할 때 같이 시작하는 FX
CHTResMgr::HT_bGetIdleFX( HTdword dwID, HTdword& dwIdleFX )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetIdleFX( dwID, dwIdleFX ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetMovSoundID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMovSoundID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetATK1AniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetATK1AniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetATK2AniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetATK2AniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetHITAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHITAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetDIEAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDIEAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonFXIDFromMonID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonFXID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool	
CHTResMgr::HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSocketModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSocketModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSocketTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSocketTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetFallenModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFallenModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetFallenModelTexID( HTdword dwID, HTdword& dwFallenModelTexID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFallenModelTexID( dwID, dwFallenModelTexID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetInvenTexID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetInvenTexID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetSocketName( HTdword dwID, CHTString& strFile )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSocketName( dwID, strFile ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetWearItemID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWearItemID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool CHTResMgr::HT_bGetShoesItemID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetShoesItemID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetEquipSoundID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetEquipSoundID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetUnEquipSoundID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetUnEquipSoundID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetItemType( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemType( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifining012( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining012( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifining345( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining345( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifining678( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining678( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifining910( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining910( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifining1112( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining1112( dwID, dwOutID ) );
	return ( HT_FALSE );
}
HTbool
CHTResMgr::HT_bGetItemRifining13( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining13( dwID, dwOutID ) );
	return ( HT_FALSE );
}
HTbool
CHTResMgr::HT_bGetItemRifining14( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining14( dwID, dwOutID ) );
	return ( HT_FALSE );
}
HTbool
CHTResMgr::HT_bGetItemRifining15( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetItemRifining15( dwID, dwOutID ) );
	return ( HT_FALSE );
}

// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetImpactFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetImpactFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetCastFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetCastFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetActivateFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetActivateFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetStateFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetStateFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetSkillIconID( HTdword dwID, HTdword& dwOutID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetSkillIconID( dwID, dwOutID ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetMonNormalAtkFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonNormalAtkFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetMonSpecialAtkFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonSpecialAtkFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetMonStateFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonStateFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetMonIdleFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonIdleFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool CHTResMgr::HT_bGetMonDieFXName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonDieFXName( dwID, strName ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool	
//CHTResMgr::HT_bGetMonAttackSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonAttackSoundID( dwID, dwOutID ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool	
//CHTResMgr::HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonHitSoundID( dwID, dwOutID ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool	
//CHTResMgr::HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonIdleSoundID( dwID, dwOutID ) );
//	return ( HT_FALSE );
//}
// 20021101 HK : 폐기 By 기획변경
//HTbool	
//CHTResMgr::HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetMonDieSoundID( dwID, dwOutID ) );
//	return ( HT_FALSE );
//}

HTbool
CHTResMgr::HT_bGetMonAttackSoundID1( HTdword dwID, HTdword& dwAttackSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonAttackSoundID1( dwID, dwAttackSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonAttackSoundID2( HTdword dwID, HTdword& dwAttackSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonAttackSoundID2( dwID, dwAttackSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwHitSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonHitSoundID( dwID, dwHitSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonHit2SoundID( HTdword dwID, HTdword& dwHit2SoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonHit2SoundID( dwID, dwHit2SoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonWalkSoundID( HTdword dwID, HTdword& dwWalkSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonWalkSoundID( dwID, dwWalkSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonRunSoundID( HTdword dwID, HTdword& dwRunSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonRunSoundID( dwID, dwRunSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwIdleSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonIdleSoundID( dwID, dwIdleSoundID ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwDieSoundID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetMonDieSoundID( dwID, dwDieSoundID ) );
	return ( HT_FALSE );
}

//HTbool
//CHTResMgr::HT_bGetFieldWhenActive( HTdword dwID, HTdword& dwWhen )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetFieldWhenActive( dwID, dwWhen ) );
//	return ( HT_FALSE );
//}
//
//HTbool
//CHTResMgr::HT_bGetFieldFxName( HTdword dwID, CHTString& strName )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetFieldFxName( dwID, strName ) );
//	return ( HT_FALSE );
//}
//
//HTbool
//CHTResMgr::HT_bGetFieldWhereID( HTdword dwID, HTdword& dwWhereID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetFieldWhereID( dwID, dwWhereID ) );
//	return ( HT_FALSE );
//}
//

HTbool
CHTResMgr::HT_bGetName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetName( dwID, strName ) );
	return ( HT_FALSE );
}

//HTbool
//CHTResMgr::HT_bGetDayFXID( HTdword dwID, HTdword& dwFXID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetDayFXID( dwID, dwFXID ) );
//	return ( HT_FALSE );
//}
//
//HTbool
//CHTResMgr::HT_bGetNightFXID( HTdword dwID, HTdword& dwFXID )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetNightFXID( dwID, dwFXID ) );
//	return ( HT_FALSE );
//}
//
//HTbool		
//CHTResMgr::HT_bGetPickFlag( HTdword dwID, HTbool& bPick )
//{
//	CHTBaseResTable* pTable = HT_pGetTable( dwID );
//	if ( pTable )
//		return ( pTable->HT_bGetPickFlag( dwID, bPick ) );
//	return ( HT_FALSE );
//}

HTbool		
CHTResMgr::HT_bGetManAnim1ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManAnim1ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManAnim2ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManAnim2ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManAnim3ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManAnim3ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomAnim1ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomAnim1ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomAnim2ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomAnim2ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomAnim3ID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomAnim3ID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetNAGFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetNAGBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetYAKFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetYAKBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetASUFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetASUBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetDEVFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetDEVBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetKIMFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetKIMBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetGANFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetGANBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetRAKFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetRAKBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetGARFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARFApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetGARBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARBApronAnimID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManFApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManFApronAnimID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManBApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManBApronAnimID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomFApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomFApronAnimID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomBApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomBApronAnimID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManFApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManFApronAnimID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManBApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManBApronAnimID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomFApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomFApronAnimID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomBApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomBApronAnimID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManFApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManFApronAnimID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetManBApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetManBApronAnimID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomFApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomFApronAnimID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWomBApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWomBApronAnimID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

///////////////////////////////////////////////////////
HTbool		
CHTResMgr::HT_bGetAttackOKID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetAttackOKID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetAttackOKID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetAttackOKID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetAttackOKID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetAttackOKID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetSwingSoundID1( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSwingSoundID1( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetSwingSoundID2( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSwingSoundID2( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetSwingSoundID3( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSwingSoundID3( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWPNATKSTDAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWPNATKSTDAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWPNATKWLKAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWPNATKWLKAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWPNATKRUNAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWPNATKRUNAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetWPNHITAniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetWPNHITAniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetSecondSocketModelID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetSecondSocketModelID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetHideMeshName( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHideMeshName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetHair1AniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHair1AniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetHair2AniID( HTdword dwID, HTdword& dwOutID )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetHair2AniID( dwID, dwOutID ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetNAGScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetNAGScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetASUScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetASUScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetYAKScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetYAKScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetDEVScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDEVScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetKIMScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetKIMScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetRAKScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetRAKScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool		
CHTResMgr::HT_bGetGANScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGANScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetGARScale( HTdword dwID, HTfloat& fFactor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetGARScale( dwID, fFactor ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetGuildBackTex( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFileName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetGuildEmblemTex( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFileName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetGuildTitleTex( HTdword dwID, CHTString& strName )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetFileName( dwID, strName ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetGuildEmblemDWColor( HTdword dwID, HTdword& dwColor )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetDWColor( dwID, dwColor ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetAreaName(HTdword dwID, HTint iFromID, HTint iToID, CHTString& strAreaName)
{	
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )
		return ( pTable->HT_bGetAreaName( iFromID, iToID, strAreaName ) );
	return ( HT_FALSE );
}

HTbool
CHTResMgr::HT_bGetItemRifiningScaleStart( HTdword dwID, HTvector3& vecScaleStart )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetScaleStart( dwID, vecScaleStart );
	else return HT_FALSE;
}

HTbool
CHTResMgr::HT_bGetItemRifiningScaleEnd( HTdword dwID, HTvector3& vecScaleEnd )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetScaleEnd( dwID, vecScaleEnd );
	else return HT_FALSE;
}

HTbool
CHTResMgr::HT_bGetItemRifiningColorStart( HTdword dwID, HTdword& dwColorStart )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetColorStart( dwID, dwColorStart );
	else return HT_FALSE;
}

HTbool
CHTResMgr::HT_bGetItemRifiningColorEnd( HTdword dwID, HTdword& dwColorEnd )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetColorEnd( dwID, dwColorEnd );
	else return HT_FALSE;
}

HTbool
CHTResMgr::HT_bGetItemRifiningStart2EndTime( HTdword dwID, HTfloat& fStart2EndTime )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetStart2EndTime( dwID, fStart2EndTime );
	else return HT_FALSE;
}

HTbool
CHTResMgr::HT_bGetItemRifiningScaleColorTime( HTdword dwID, HTvector3& vecScaleStart, HTvector3& vecScaleEnd, HTdword& dwColorStart, HTdword& dwColorEnd, HTfloat& fStart2EndTime )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetItemRifiningScaleColorTime( dwID, vecScaleStart, vecScaleEnd, dwColorStart, dwColorEnd, fStart2EndTime );
	else return HT_FALSE;
}

HTdword
CHTResMgr::HT_dwGetFootSound( HTdword dwID, HTint iMapStatus, HTint iStatus )
{
	CHTBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_dwGetFootSound( dwID, iMapStatus, iStatus );
	else return 0;
}

HTbool
CHTResMgr::HT_bGetMonModelTexItem( HTdword dwID,
								  HTuint& nNumMesh, HTdword& dwBasicModel,
								  HTdword& dwMesh1, HTdword& dwMesh2, HTdword& dwMesh3, HTdword& dwMesh4, HTdword& dwMesh5,
								  HTdword& dwTex1, HTdword& dwTex2, HTdword& dwTex3, HTdword& dwTex4, HTdword& dwTex5,
								  HTdword& dwItemR, HTdword& dwItemRTex, HTdword& dwItemL, HTdword& dwItemLTex )
{
	CHTBaseResTable* pTable = this->HT_pGetTable( dwID );
	if ( pTable ) return pTable->HT_bGetMonModelTexItem( dwID, nNumMesh,
		dwBasicModel, dwMesh1, dwMesh2, dwMesh3, dwMesh4, dwMesh5,
		dwTex1, dwTex2, dwTex3, dwTex4, dwTex5,
		dwItemR, dwItemRTex, dwItemL, dwItemLTex );
	else return HT_FALSE;
}


//-----------------------------------------------------------------------------
// Name		:	CHTResTableType01()
// Desc		:	Constructor
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResTableType01::CHTResTableType01()
{
}

//-----------------------------------------------------------------------------
// Name		:	~CHTResTableType01()
// Desc		:	Destructor
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResTableType01::~CHTResTableType01()
{
	HT_ResTableType01_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

//-----------------------------------------------------------------------------
// Name		:	HT_hrLoad()
// Desc		:	Load resource table
// Params	:	filename string
// Returns	:	true / false
//-----------------------------------------------------------------------------
HTRESULT CHTResTableType01::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType01* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	// 제일 윗줄은 뺀다. 
	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType01;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("File");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFile );

		m_mapTable.insert( HT_ResTableType01_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType01::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType01* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType01;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType01) );

		m_mapTable.insert( HT_ResTableType01_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType01::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType01_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 1;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType01) );

		itTable++;
	}

	return ( HT_OK );
}

//-----------------------------------------------------------------------------
// Name		:	HT_bGetFileName()
// Desc		:	Get file name from resource table by ID
// Params	:	ID and resource filename
// Returns	:	true / false
//-----------------------------------------------------------------------------
HTbool CHTResTableType01::HT_bGetFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType01_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFile;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTdword CHTResTableType01::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType01_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

//-----------------------------------------------------------------------------
// Name		:	CHTResTableType02()
// Desc		:	Constructor
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResTableType02::CHTResTableType02()
{
}

//-----------------------------------------------------------------------------
// Name		:	~CHTResTableType02()
// Desc		:	Destructor
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
CHTResTableType02::~CHTResTableType02()
{
	HT_ResTableType02_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

//-----------------------------------------------------------------------------
// Name		:	HT_hrLoad()
// Desc		:	Load resource table
// Params	:	filename string
// Returns	:	true / false
//-----------------------------------------------------------------------------
HTRESULT CHTResTableType02::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType02* pRecord = HT_NULL;
	HTint iID, iMtrlID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	// 제일 윗줄은 뺀다. 
	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType02;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strMapName );
		strCell = _T("File");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileTHM );
		strCell = _T("ObjFile");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileTMO );
		strCell = _T("EnvFile");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileTME );
		strCell = _T("CellFile");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileTCC );
		strCell = _T("CFG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileCFG );
		strCell = _T("MiniMap");															// 20021106 대호
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileBMP );
		strCell = _T("Material_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iMtrlID );
		pRecord->dwMaterial = (HTdword)iMtrlID;
		strCell = _T("OBJ");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileOBJ );
		strCell = _T("OBJTEX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileTEX );
		strCell = _T("MON");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileMON );
		strCell = _T("MONANI");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileMONANI );
		strCell = _T("MONTEX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileMONTEX );
		strCell = _T("NPC");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileNPC );
		strCell = _T("NPCANI");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileNPCANI );
		strCell = _T("NPCTEX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileNPCTEX );
		strCell = _T("FX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFXFiles );
		strCell = _T("NPCSound");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strNPCSoundFiles );
		strCell = _T("MonSound");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strMonSoundFiles );
		strCell = _T("Minimap");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileMinimap );
		strCell = _T("NPCScript");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileNPCScript );
		strCell = _T("ObjResource");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileObjRes );
		strCell = _T("PopObj");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFilePopObjPack );
		strCell = _T("PopTex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFilePopTexPack );

		m_mapTable.insert( HT_ResTableType02_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType02::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType02* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType02;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType02) );

		m_mapTable.insert( HT_ResTableType02_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType02::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType02_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 2;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType02) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType02::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType02_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType02::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strMapName;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetTHMFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileTHM;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetTMOFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileTMO;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetTMEFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileTME;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetTCCFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileTCC;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetCFGFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileCFG;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

// 20021106 대호
HTbool CHTResTableType02::HT_bGetBMPFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileBMP;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetOBJPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileOBJ;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetOBJTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileTEX;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool CHTResTableType02::HT_bGetMONPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileMON;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
HTbool CHTResTableType02::HT_bGetMONANIPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileMONANI;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
HTbool CHTResTableType02::HT_bGetMONTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileMONTEX;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
HTbool CHTResTableType02::HT_bGetNPCPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileNPC;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
HTbool CHTResTableType02::HT_bGetNPCANIPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileNPCANI;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
HTbool CHTResTableType02::HT_bGetNPCTEXPAKFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFileNPCTEX;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool
CHTResTableType02::HT_bGetFXFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFXFiles;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );

}

HTbool		
CHTResTableType02::HT_bGetNPCSoundFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strNPCSoundFiles;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );

}

HTbool		
CHTResTableType02::HT_bGetMonSoundFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strMonSoundFiles;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );

}

HTbool		
CHTResTableType02::HT_bGetMinimapFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFileMinimap;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool		
CHTResTableType02::HT_bGetNPCScriptFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFileNPCScript;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool		
CHTResTableType02::HT_bGetObjResFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFileObjRes;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool		
CHTResTableType02::HT_bGetPopObjPackFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFilePopObjPack;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

// 오브젝트 리소스 분리 (20031008 DaeHo)
HTbool		
CHTResTableType02::HT_bGetPopTexPackFilesName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strFilePopTexPack;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}



HTbool CHTResTableType02::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	HT_ResTableType02_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwMtrlID = (itTable->second)->dwMaterial;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}
//-----------------------------------------------------------------------------------

CHTResTableType03::CHTResTableType03()
{
}

CHTResTableType03::~CHTResTableType03()
{
	HT_ResTableType03_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType03::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType03* pRecord = HT_NULL;
	HTint iID, iR, iG, iB;
	CHTString strCell;
	HTtchar szFloat[HT_MAX_STR];

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType03;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("DiffuseR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("DiffuseG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("DiffuseB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		pRecord->clrDiffuse = HT_COLOR( (HTfloat) iR/255.0f, (HTfloat) iG/255.0f, (HTfloat) iB/255.0f, 1.0f );
		strCell = _T("AmbientR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("AmbientG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("AmbientB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		pRecord->clrAmbient = HT_COLOR( (HTfloat) iR/255.0f, (HTfloat) iG/255.0f, (HTfloat) iB/255.0f, 1.0f );
		strCell = _T("SpecularR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("SpecularG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("SpecularB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		pRecord->clrSpecular = HT_COLOR( (HTfloat) iR/255.0f, (HTfloat) iG/255.0f, (HTfloat) iB/255.0f, 1.0f );
		strCell = _T("EmissiveR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("EmissiveG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("EmissiveB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		pRecord->clrEmissive = HT_COLOR( (HTfloat) iR/255.0f, (HTfloat) iG/255.0f, (HTfloat) iB/255.0f, 1.0f );
		strCell = _T("Power");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat );
		pRecord->fPower = (HTfloat)atof( szFloat );

		m_mapTable.insert( HT_ResTableType03_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType03::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType03* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType03;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType03) );

		m_mapTable.insert( HT_ResTableType03_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType03::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType03_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 3;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType03) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType03::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType03_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType03::HT_bGetDiffuseColor( HTdword dwID, HT_COLOR& clrWant )
{
	HT_ResTableType03_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			clrWant = (itTable->second)->clrDiffuse;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType03::HT_bGetAmbientColor( HTdword dwID, HT_COLOR& clrWant )
{
	HT_ResTableType03_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			clrWant = (itTable->second)->clrAmbient;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType03::HT_bGetSpecularColor( HTdword dwID, HT_COLOR& clrWant )
{
	HT_ResTableType03_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			clrWant = (itTable->second)->clrSpecular;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType03::HT_bGetEmissiveColor( HTdword dwID, HT_COLOR& clrWant )
{
	HT_ResTableType03_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			clrWant = (itTable->second)->clrEmissive;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType03::HT_bGetPower( HTdword dwID, HTfloat& fPower )
{
	HT_ResTableType03_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fPower = (itTable->second)->fPower;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

//-------------------------------------------------------------------------------

CHTResTableType04::CHTResTableType04()
{
}

CHTResTableType04::~CHTResTableType04()
{
	HT_ResTableType04_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType04::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType04* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType04;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Model_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwModelID = (HTdword)iTmp;

		strCell = _T("Default_UpWear_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwDefaultUpWearID = (HTdword)iTmp;
		strCell = _T("Default_DownWear_ID");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwDefaultDownWearID = (HTdword)iTmp;
		strCell = _T("Default_HandWear_ID");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwDefaultHandWearID = (HTdword)iTmp;

		strCell = _T("Default_Shoes_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDefaultShoesID = (HTdword)iTmp;
		strCell = _T("Head_TypeA_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeAID = (HTdword)iTmp;
		strCell = _T("Head_TypeB_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeBID = (HTdword)iTmp;
		strCell = _T("Head_TypeC_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeCID = (HTdword)iTmp;
		strCell = _T("Head_TypeD_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeDID = (HTdword)iTmp;
		strCell = _T("Head_TypeE_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeEID = (HTdword)iTmp;
		strCell = _T("Head_TypeF_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeFID = (HTdword)iTmp;
		strCell = _T("Head_TypeG_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeGID = (HTdword)iTmp;
		strCell = _T("Head_TypeH_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHeadTypeHID = (HTdword)iTmp;
		strCell = _T("Material_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMaterialID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType04_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType04::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType04* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType04;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType04) );

		m_mapTable.insert( HT_ResTableType04_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType04::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType04_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 4;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType04) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType04::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType04_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType04::HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwModelFileID = (itTable->second)->dwModelID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetDefaultUpWearID( HTdword dwID, HTdword& dwWearID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwWearID = (itTable->second)->dwDefaultUpWearID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetDefaultDownWearID( HTdword dwID, HTdword& dwWearID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwWearID = (itTable->second)->dwDefaultDownWearID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetDefaultHandWearID( HTdword dwID, HTdword& dwWearID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwWearID = (itTable->second)->dwDefaultHandWearID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetDefaultShoesID( HTdword dwID, HTdword& dwShoesID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwShoesID = (itTable->second)->dwDefaultShoesID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeAID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeAID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeBID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeBID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeCID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeCID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeDID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeDID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeEID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeEID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeFID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeFID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeGID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeGID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetHeadTypeHID( HTdword dwID, HTdword& dwHeadID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHeadID = (itTable->second)->dwHeadTypeHID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType04::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	HT_ResTableType04_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwMtrlID = (itTable->second)->dwMaterialID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType05::CHTResTableType05()
{
}

CHTResTableType05::~CHTResTableType05()
{
	HT_ResTableType05_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType05::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType05* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType05;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Face_Mesh");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwFaceMesh = (HTdword)iTmp;
		strCell = _T("Face_Tex_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwFaceTexID = (HTdword)iTmp;
		strCell = _T("HairModel_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHairModelID = (HTdword)iTmp;
		strCell = _T("Hair_Tex_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHairTexID = (HTdword)iTmp;
		strCell = _T("Hair_Type");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHairType = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType05_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType05::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType05* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType05;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType05) );

		m_mapTable.insert( HT_ResTableType05_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType05::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType05_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 5;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType05) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType05::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType05_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType05::HT_bGetFaceMesh( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType05_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwFaceMesh;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType05::HT_bGetFaceTexID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType05_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwFaceTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType05::HT_bGetHairModelID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType05_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHairModelID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType05::HT_bGetHairTexID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType05_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHairTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType05::HT_bGetHairType( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType05_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHairType;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

//CHTResTableType06::CHTResTableType06()
//{
//}
//
//CHTResTableType06::~CHTResTableType06()
//{
//	HT_ResTableType06_It it = m_mapTable.begin();
//	while ( it != m_mapTable.end() )
//	{
//		HT_DELETE( it->second );
//		it = m_mapTable.erase( it );
//	}
//}
//
//HTRESULT CHTResTableType06::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
//{
//	if ( !pXML )
//		return ( HT_FAIL );
//
//	if ( !pXML->HT_isThereTable( strTable ) )
//		return( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HT_ResTableType06* pRecord = HT_NULL;
//	HTint iID, iTmp;
//	CHTString strCell;
//
//	m_nItems = pXML->HT_nGetTableRowCount( strTable );
//
//	--m_nItems;	
//
//	if ( m_nItems <= 0 )
//		return ( HT_FAIL );
//
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType06;
//
//		strCell = _T("ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
//		strCell = _T("Chest_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwChestMesh = (HTdword)iTmp;
//		strCell = _T("Chest_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwChestTexID = (HTdword)iTmp;
//		strCell = _T("Pants_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwPantsMesh = (HTdword)iTmp;
//		strCell = _T("Pants_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwPantsTexID = (HTdword)iTmp;
//		strCell = _T("RUArm_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRUArmMesh = (HTdword)iTmp;
//		strCell = _T("LUArm_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLUArmMesh = (HTdword)iTmp;
//		strCell = _T("RUArm_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRUArmTexID = (HTdword)iTmp;
//		strCell = _T("LUArm_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLUArmTexID = (HTdword)iTmp;
//		strCell = _T("RLArm_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRLArmMesh = (HTdword)iTmp;
//		strCell = _T("LLArm_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLLArmMesh = (HTdword)iTmp;
//		strCell = _T("RLArm_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRLArmTexID = (HTdword)iTmp;
//		strCell = _T("LLArm_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLLArmTexID = (HTdword)iTmp;
//		strCell = _T("Rhand_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRHandMesh = (HTdword)iTmp;
//		strCell = _T("Lhand_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLHandMesh = (HTdword)iTmp;
//		strCell = _T("RHand_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwRHandTexID = (HTdword)iTmp;
//		strCell = _T("LHand_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwLHandTexID = (HTdword)iTmp;
//		strCell = _T("Skirt_Mesh");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwSkirtMesh = (HTdword)iTmp;
//		strCell = _T("Skirt_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwSkirtTexID = (HTdword)iTmp;
//		strCell = _T("Apron_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwApronModelID = (HTdword)iTmp;
//		strCell = _T("Apron_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwApronTexID = (HTdword)iTmp;
//		strCell = _T("ApronB_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwApronBackModelID = (HTdword)iTmp;
//		strCell = _T("ApronB_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwApronBackTexID = (HTdword)iTmp;
//		strCell = _T("ShoulderL_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwShoulderLModelID = (HTdword)iTmp;
//		strCell = _T("ShoulderL_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwShoulderLTexID = (HTdword)iTmp;
//		strCell = _T("ShoulderR_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwShoulderRModelID = (HTdword)iTmp;
//		strCell = _T("ShoulderR_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwShoulderRTexID = (HTdword)iTmp;
//
//		strCell = _T("KneeL_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwKneeLModelID = (HTdword)iTmp;
//		strCell = _T("KneeL_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwKneeLTexID = (HTdword)iTmp;
//		strCell = _T("KneeR_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwKneeRModelID = (HTdword)iTmp;
//		strCell = _T("KneeR_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwKneeRTexID = (HTdword)iTmp;
//
//		strCell = _T("ThighL_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwThighLModelID = (HTdword)iTmp;
//		strCell = _T("ThighL_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwThighLTexID = (HTdword)iTmp;
//		strCell = _T("ThighR_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwThighRModelID = (HTdword)iTmp;
//		strCell = _T("ThighR_Tex_ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwThighRTexID = (HTdword)iTmp;
//
//		m_mapTable.insert( HT_ResTableType06_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTRESULT	
//CHTResTableType06::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
//{
//	if ( !pFile )
//		return ( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HTint iRecordCount;
//	pFile->HT_bRead( &iRecordCount );
//	m_nItems = iRecordCount;
//
//	HT_ResTableType06* pRecord = HT_NULL;
//	HTint iID;
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType06;
//
//		pFile->HT_bRead( &iID );
//		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType06) );
//
//		m_mapTable.insert( HT_ResTableType06_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTRESULT	
//CHTResTableType06::HT_hrSave( CHTFile* pFile )
//{
//	if ( !pFile )
//		return ( HT_FAIL );
//
//	HT_ResTableType06_It itTable;
//	itTable = m_mapTable.begin();
//
//	HTbyte bType = 6;
//	pFile->HT_bWrite( bType );	// class type
//
//	HTint iRecordCount;
//	iRecordCount = (HTint)m_mapTable.size();
//	pFile->HT_bWrite( iRecordCount );	// 줄 수
//
//	HTint iID;
//	while ( itTable != m_mapTable.end() )
//	{
//		iID = itTable->first;
//		pFile->HT_bWrite( iID );
//
//		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType06) );
//
//		itTable++;
//	}
//
//	return ( HT_OK );
//}
//
//HTdword CHTResTableType06::HT_dwGetIDByIndex( HTuint idxRow )
//{
//	if ( idxRow > m_mapTable.size() )
//		return ( 0 );
//
//	HT_ResTableType06_It itTable = m_mapTable.begin();
//
//	HTuint i = 0;
//	while ( i < idxRow ) 
//	{
//		itTable++;
//		i++;
//	}
//
//	if ( itTable != m_mapTable.end() )
//		return ( itTable->first );
//
//	return ( 0 );
//}
//
//HTbool CHTResTableType06::HT_bGetChestMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwChestMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetChestTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwChestTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetPantsMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwPantsMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetPantsTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwPantsTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRUArmMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRUArmMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLUArmMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLUArmMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRUArmTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRUArmTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLUArmTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLUArmTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRLArmMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRLArmMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLLArmMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLLArmMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLLArmTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLLArmTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRLArmTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRLArmTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRHandMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRHandMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLHandMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLHandMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetRHandTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwRHandTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetLHandTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwLHandTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetSkirtMesh( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwSkirtMesh;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetSkirtTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwSkirtTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetApronBackModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwApronBackModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetApronBackTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwApronBackTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetApronModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwApronModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetApronTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwApronTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetShoulderLModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwShoulderLModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetShoulderLTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwShoulderLTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetShoulderRModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwShoulderRModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetShoulderRTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwShoulderRTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetKneeLModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwKneeLModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetKneeLTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwKneeLTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetKneeRModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwKneeRModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetKneeRTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwKneeRTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetThighLModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwThighLModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetThighLTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwThighLTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetThighRModelID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwThighRModelID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType06::HT_bGetThighRTexID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType06_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwThighRTexID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}

CHTResTableType061::CHTResTableType061(){}
CHTResTableType061::~CHTResTableType061()
{
	HT_ResTableType061_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType061::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML ) return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) ) return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType061* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems;	

	if ( m_nItems <= 0 ) return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType061;

		strCell = _T("ID");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Chest_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwChestMesh = (HTdword)iTmp;
		strCell = _T("Chest_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwChestTexID = (HTdword)iTmp;
		strCell = _T("RUArm_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRUArmMesh = (HTdword)iTmp;
		strCell = _T("LUArm_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLUArmMesh = (HTdword)iTmp;
		strCell = _T("RUArm_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRUArmTexID = (HTdword)iTmp;
		strCell = _T("LUArm_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLUArmTexID = (HTdword)iTmp;
		strCell = _T("Skirt_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwSkirtMesh = (HTdword)iTmp;
		strCell = _T("Skirt_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwSkirtTexID = (HTdword)iTmp;
		strCell = _T("Apron_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwApronModelID = (HTdword)iTmp;
		strCell = _T("Apron_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwApronTexID = (HTdword)iTmp;
		strCell = _T("ApronB_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwApronBackModelID = (HTdword)iTmp;
		strCell = _T("ApronB_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwApronBackTexID = (HTdword)iTmp;
		strCell = _T("ShoulderL_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwShoulderLModelID = (HTdword)iTmp;
		strCell = _T("ShoulderL_Tex_ID");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwShoulderLTexID = (HTdword)iTmp;
		strCell = _T("ShoulderR_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwShoulderRModelID = (HTdword)iTmp;
		strCell = _T("ShoulderR_Tex_ID");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwShoulderRTexID = (HTdword)iTmp;
		strCell = _T("Skirt_Type");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); iTmp == 0 ? (pRecord->bSkirtType = HT_FALSE) : (pRecord->bSkirtType = HT_TRUE);

		m_mapTable.insert( HT_ResTableType061_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT
CHTResTableType061::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType061* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType061;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType061) );

		m_mapTable.insert( HT_ResTableType061_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTdword
CHTResTableType061::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType061_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}



HTRESULT
CHTResTableType061::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return ( HT_FAIL );

	HT_ResTableType061_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 61;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType061) );

		itTable++;
	}

	return ( HT_OK );
}

HTbool
CHTResTableType061::HT_bGetUpWearMeshes( HTdword dwID,
										HTdword& dwChestMesh, HTdword& dwChestTexID,
										HTdword& dwRUArmMesh, HTdword& dwLUArmMesh, HTdword& dwRUArmTexID, HTdword& dwLUArmTexID,
										HTdword& dwSkirtMesh, HTdword& dwSkirtTexID,
										HTdword& dwApronModelID, HTdword& dwApronTexID, HTdword& dwApronBackModelID, HTdword& dwApronBackTexID,
										HTdword& dwShoulderLModelID, HTdword& dwShoulderLTexID, HTdword& dwShoulderRModelID, HTdword& dwShoulderRTexID,
										HTbool& bSkirtType )
{
	HT_ResTableType061_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwChestMesh = itTable->second->dwChestMesh;
			dwChestTexID = itTable->second->dwChestTexID;
			dwRUArmMesh = itTable->second->dwRUArmMesh;
			dwLUArmMesh = itTable->second->dwLUArmMesh;
			dwRUArmTexID = itTable->second->dwRUArmTexID;
			dwLUArmTexID = itTable->second->dwLUArmTexID;
			dwSkirtMesh = itTable->second->dwSkirtMesh;
			dwSkirtTexID = itTable->second->dwSkirtTexID;
			dwApronModelID = itTable->second->dwApronModelID;
			dwApronTexID = itTable->second->dwApronTexID;
			dwApronBackModelID = itTable->second->dwApronBackModelID;
			dwApronBackTexID = itTable->second->dwApronBackTexID;
			dwShoulderLModelID = itTable->second->dwShoulderLModelID;
			dwShoulderLTexID = itTable->second->dwShoulderLTexID;
			dwShoulderRModelID = itTable->second->dwShoulderRModelID;
			dwShoulderRTexID = itTable->second->dwShoulderRTexID;
			bSkirtType = itTable->second->bSkirtType;
			return HT_TRUE;
		}
	}
	return( HT_FALSE );
}

CHTResTableType062::CHTResTableType062(){}
CHTResTableType062::~CHTResTableType062()
{
	HT_ResTableType062_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType062::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML ) return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) ) return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType062* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems;	

	if ( m_nItems <= 0 ) return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType062;

		strCell = _T("ID");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Pants_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwPantsMesh = (HTdword)iTmp;
		strCell = _T("Pants_Mesh2nd");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwPantsMesh2nd = (HTdword)iTmp;
		strCell = _T("Pants_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwPantsTexID = (HTdword)iTmp;
		strCell = _T("KneeL_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwKneeLModelID = (HTdword)iTmp;
		strCell = _T("KneeL_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwKneeLTexID = (HTdword)iTmp;
		strCell = _T("KneeR_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwKneeRModelID = (HTdword)iTmp;
		strCell = _T("KneeR_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwKneeRTexID = (HTdword)iTmp;
		strCell = _T("ThighL_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwThighLModelID = (HTdword)iTmp;
		strCell = _T("ThighL_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwThighLTexID = (HTdword)iTmp;
		strCell = _T("ThighR_ID");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwThighRModelID = (HTdword)iTmp;
		strCell = _T("ThighR_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwThighRTexID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType062_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT
CHTResTableType062::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType062* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType062;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType062) );

		m_mapTable.insert( HT_ResTableType062_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTdword
CHTResTableType062::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType062_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}



HTRESULT
CHTResTableType062::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return ( HT_FAIL );

	HT_ResTableType062_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 62;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType062) );

		itTable++;
	}

	return ( HT_OK );
}

HTbool
CHTResTableType062::HT_bGetDownWearMeshes( HTdword dwID,
										  HTdword& dwPantsMesh, HTdword& dw2ndPantsMesh, HTdword& dwPantsTexID,
										  HTdword& dwKneeLModelID, HTdword& dwKneeLTexID, HTdword& dwKneeRModelID, HTdword& dwKneeRTexID,
										  HTdword& dwThighLModelID, HTdword& dwThighLTexID, HTdword& dwThighRModelID, HTdword& dwThighRTexID )
{
	HT_ResTableType062_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwPantsMesh = itTable->second->dwPantsMesh;
			dw2ndPantsMesh = itTable->second->dwPantsMesh2nd;
			dwPantsTexID = itTable->second->dwPantsTexID;
			dwKneeLModelID = itTable->second->dwKneeLModelID;
			dwKneeLTexID = itTable->second->dwKneeLTexID;
			dwKneeRModelID = itTable->second->dwKneeRModelID;
			dwKneeRTexID = itTable->second->dwKneeRTexID;
			dwThighLModelID = itTable->second->dwThighLModelID;
			dwThighLTexID = itTable->second->dwThighLTexID;
			dwThighRModelID = itTable->second->dwThighRModelID;
			dwThighRTexID = itTable->second->dwThighRTexID;
			return HT_TRUE;
		}
	}
	return( HT_FALSE );
}

CHTResTableType063::CHTResTableType063(){}
CHTResTableType063::~CHTResTableType063()
{
	HT_ResTableType063_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType063::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML ) return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) ) return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType063* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems;	

	if ( m_nItems <= 0 ) return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType063;

		strCell = _T("ID");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("RLArm_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRLArmMesh = (HTdword)iTmp;
		strCell = _T("LLArm_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLLArmMesh = (HTdword)iTmp;
		strCell = _T("RLArm_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRLArmTexID = (HTdword)iTmp;
		strCell = _T("LLArm_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLLArmTexID = (HTdword)iTmp;
		strCell = _T("Rhand_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRHandMesh = (HTdword)iTmp;
		strCell = _T("Lhand_Mesh");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLHandMesh = (HTdword)iTmp;
		strCell = _T("RHand_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwRHandTexID = (HTdword)iTmp;
		strCell = _T("LHand_Tex_ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp ); pRecord->dwLHandTexID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType063_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT
CHTResTableType063::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType063* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType063;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType063) );

		m_mapTable.insert( HT_ResTableType063_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTdword
CHTResTableType063::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType063_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}



HTRESULT
CHTResTableType063::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return ( HT_FAIL );

	HT_ResTableType063_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 63;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType063) );

		itTable++;
	}

	return ( HT_OK );
}

HTbool
CHTResTableType063::HT_bGetHandWearMeshes( HTdword dwID,
										  HTdword& dwRLArmMesh, HTdword& dwLLArmMesh, HTdword& dwRLArmTexID, HTdword& dwLLArmTexID,
										  HTdword& dwRHandMesh, HTdword& dwLHandMesh, HTdword& dwRHandTexID, HTdword& dwLHandTexID )
{
	HT_ResTableType063_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwRLArmMesh = itTable->second->dwRLArmMesh;
			dwLLArmMesh = itTable->second->dwLLArmMesh;
			dwRLArmTexID = itTable->second->dwRLArmTexID;
			dwLLArmTexID = itTable->second->dwLLArmTexID;
			dwRHandMesh = itTable->second->dwRHandMesh;
			dwLHandMesh = itTable->second->dwLHandMesh;
			dwRHandTexID = itTable->second->dwRHandTexID;
			dwLHandTexID = itTable->second->dwLHandTexID;
			return HT_TRUE;
		}
	}
	return( HT_FALSE );
}


CHTResTableType07::CHTResTableType07()
{
}

CHTResTableType07::~CHTResTableType07()
{
	HT_ResTableType07_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType07::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType07* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType07;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Rboots_Mesh");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRBootsMesh = (HTdword)iTmp;
		strCell = _T("Lboots_Mesh");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwLBootsMesh = (HTdword)iTmp;
		strCell = _T("Boots_Tex_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwBootsTexID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType07_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType07::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType07* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType07;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType07) );

		m_mapTable.insert( HT_ResTableType07_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType07::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType07_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 7;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType07) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType07::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType07_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType07::HT_bGetRBootsMesh( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType07_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRBootsMesh;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType07::HT_bGetLBootsMesh( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType07_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwLBootsMesh;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType07::HT_bGetBootsTexID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType07_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwBootsTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType08::CHTResTableType08()
{
}

CHTResTableType08::~CHTResTableType08()
{
	HT_ResTableType08_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType08::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType08* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType08;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("NAG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGID = (HTdword)iTmp;
		strCell = _T("YAK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKID = (HTdword)iTmp;
		strCell = _T("ASU");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUID = (HTdword)iTmp;
		strCell = _T("DEV");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVID = (HTdword)iTmp;
		strCell = _T("KIM");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMID = (HTdword)iTmp;
		strCell = _T("GAN");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANID = (HTdword)iTmp;
		strCell = _T("RAK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKID = (HTdword)iTmp;
		strCell = _T("GAR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARID = (HTdword)iTmp;

		strCell = _T("NAG_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID1 = (HTdword)iTmp;
		strCell = _T("NAG_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID2 = (HTdword)iTmp;
		strCell = _T("NAG_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID3 = (HTdword)iTmp;
		strCell = _T("YAK_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID1 = (HTdword)iTmp;
		strCell = _T("YAK_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID2 = (HTdword)iTmp;
		strCell = _T("YAK_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID3 = (HTdword)iTmp;
		strCell = _T("ASU_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID1 = (HTdword)iTmp;
		strCell = _T("ASU_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID2 = (HTdword)iTmp;
		strCell = _T("ASU_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID3 = (HTdword)iTmp;
		strCell = _T("DEV_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID1 = (HTdword)iTmp;
		strCell = _T("DEV_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID2 = (HTdword)iTmp;
		strCell = _T("DEV_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID3 = (HTdword)iTmp;
		strCell = _T("KIM_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID1 = (HTdword)iTmp;
		strCell = _T("KIM_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID2 = (HTdword)iTmp;
		strCell = _T("KIM_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID3 = (HTdword)iTmp;
		strCell = _T("GAN_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID1 = (HTdword)iTmp;
		strCell = _T("GAN_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID2 = (HTdword)iTmp;
		strCell = _T("GAN_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID3 = (HTdword)iTmp;
		strCell = _T("RAK_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID1 = (HTdword)iTmp;
		strCell = _T("RAK_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID2 = (HTdword)iTmp;
		strCell = _T("RAK_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID3 = (HTdword)iTmp;
		strCell = _T("GAR_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID1 = (HTdword)iTmp;
		strCell = _T("GAR_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID2 = (HTdword)iTmp;
		strCell = _T("GAR_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID3 = (HTdword)iTmp;

		strCell = _T("NAGFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGFApronAniID = (HTdword)iTmp;
		strCell = _T("NAGBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGBApronAniID = (HTdword)iTmp;
		strCell = _T("YAKFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKFApronAniID = (HTdword)iTmp;
		strCell = _T("YAKBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKBApronAniID = (HTdword)iTmp;
		strCell = _T("ASUFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUFApronAniID = (HTdword)iTmp;
		strCell = _T("ASUBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUBApronAniID = (HTdword)iTmp;
		strCell = _T("DEVFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVFApronAniID = (HTdword)iTmp;
		strCell = _T("DEVBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVBApronAniID = (HTdword)iTmp;
		strCell = _T("KIMFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMFApronAniID = (HTdword)iTmp;
		strCell = _T("KIMBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMBApronAniID = (HTdword)iTmp;
		strCell = _T("GANFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANFApronAniID = (HTdword)iTmp;
		strCell = _T("GANBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANBApronAniID = (HTdword)iTmp;
		strCell = _T("RAKFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKFApronAniID = (HTdword)iTmp;
		strCell = _T("RAKBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKBApronAniID = (HTdword)iTmp;
		strCell = _T("GARFApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARFApronAniID = (HTdword)iTmp;
		strCell = _T("GARBApronAniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARBApronAniID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType08_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType08::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType08* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType08;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType08) );

		m_mapTable.insert( HT_ResTableType08_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType08::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType08_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 8;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType08) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType08::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType08_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType08::HT_bGetNAGID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetYAKID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetASUID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetDEVID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetKIMID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetGANID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetRAKID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType08::HT_bGetGARID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetNAGFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetNAGBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetYAKFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetYAKBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetASUFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetASUBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetDEVFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetDEVBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetKIMFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetKIMBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGANFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGANBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetRAKFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetRAKBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGARFApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARFApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType08::HT_bGetGARBApronAnimID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType08_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARBApronAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType081::CHTResTableType081(){}
CHTResTableType081::~CHTResTableType081()
{
	HT_ResTableType081_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType081::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML ) return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) ) return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType081* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType081;

		strCell = _T("ID");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("NAG");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwNAGID = (HTdword)iTmp;
		strCell = _T("YAK");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwYAKID = (HTdword)iTmp;
		strCell = _T("ASU");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwASUID = (HTdword)iTmp;
		strCell = _T("DEV");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwDEVID = (HTdword)iTmp;
		strCell = _T("KIM");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwKIMID = (HTdword)iTmp;
		strCell = _T("GAN");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwGANID = (HTdword)iTmp;
		strCell = _T("RAK");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwRAKID = (HTdword)iTmp;
		strCell = _T("GAR");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwGARID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType081_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType081::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType081* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType081;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType081) );

		m_mapTable.insert( HT_ResTableType081_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType081::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return ( HT_FAIL );

	HT_ResTableType081_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 81;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType081) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType081::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType081_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType081::HT_bGetNAGID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetYAKID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetASUID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetDEVID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetKIMID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetGANID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetRAKID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType081::HT_bGetGARID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType081_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType09::CHTResTableType09(){}

CHTResTableType09::~CHTResTableType09()
{
	HT_ResTableType09_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType09::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType09* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType09;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strNPCName );
		strCell = _T("TMD");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTMD = (HTdword)iTmp;
		strCell = _T("STD");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_STD = (HTdword)iTmp;
		strCell = _T("MOV");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_WLK = (HTdword)iTmp;
		strCell = _T("IDLE");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_IDL = (HTdword)iTmp;
		strCell = _T("Material_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMaterialID = (HTdword)iTmp;
		strCell = _T("StateSoundID");	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwStateSoundID = (HTdword)iTmp;
		strCell = _T("ClickSoundID");	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwClickSoundID = (HTdword)iTmp;
		strCell = _T("IdleFX");			// 20021103 HK : NPC의 Idle 애니메이션이 시작할 때마다 발생하는 이펙트ID
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwIdleFX = (HTdword)iTmp;
		strCell = _T("MOVSound");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMovSoundID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType09_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType09::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType09* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType09;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType09) );

		m_mapTable.insert( HT_ResTableType09_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType09::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType09_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 9;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType09) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType09::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType09_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType09::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strNPCName;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType09::HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwModelFileID = (itTable->second)->dwTMD;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType09::HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_STD;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType09::HT_bGetMOVAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_WLK;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType09::HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_IDL;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType09::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwMtrlID = (itTable->second)->dwMaterialID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool // 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
CHTResTableType09::HT_bGetStateSoundID( HTdword dwID, HTdword& dwStateSoundID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwStateSoundID = (itTable->second)->dwStateSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool // 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
CHTResTableType09::HT_bGetClickSoundID( HTdword dwID, HTdword& dwClickSoundID )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwClickSoundID = (itTable->second)->dwClickSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool // 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
CHTResTableType09::HT_bGetIdleFX( HTdword dwID, HTdword& dwIdleFX )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwIdleFX = (itTable->second)->dwIdleFX;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType09::HT_bGetMovSoundID( HTdword dwID, HTdword& dwIdleFX )
{
	HT_ResTableType09_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwIdleFX = (itTable->second)->dwMovSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType10::CHTResTableType10()
{
}

CHTResTableType10::~CHTResTableType10()
{
	HT_ResTableType10_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType10::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType10* pRecord = HT_NULL;
	HTint iID, iTmp, iR, iG, iB;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType10;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strMonsterName );

		//strCell = _T("TMD");
		//pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		//pRecord->dwTMD = (HTdword)iTmp;

		strCell = _T("NumMesh");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->nNumMesh = (HTuint)iTmp;
		strCell = _T("BasicModel");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwBasicModel = (HTdword)iTmp;
		strCell = _T("Mesh1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMesh1 = (HTdword)iTmp;
		strCell = _T("Mesh2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMesh2 = (HTdword)iTmp;
		strCell = _T("Mesh3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMesh3 = (HTdword)iTmp;
		strCell = _T("Mesh4");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMesh4 = (HTdword)iTmp;
		strCell = _T("Mesh5");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMesh5 = (HTdword)iTmp;
		strCell = _T("Tex1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTex1 = (HTdword)iTmp;
		strCell = _T("Tex2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTex2 = (HTdword)iTmp;
		strCell = _T("Tex3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTex3 = (HTdword)iTmp;
		strCell = _T("Tex4");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTex4 = (HTdword)iTmp;
		strCell = _T("Tex5");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTex5 = (HTdword)iTmp;
		strCell = _T("ItemR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemR = (HTdword)iTmp;
		strCell = _T("ItemRTex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRTex = (HTdword)iTmp;
		strCell = _T("ItemL");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemL = (HTdword)iTmp;
		strCell = _T("ItemLTex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemLTex = (HTdword)iTmp;

		strCell = _T("STD");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_STD = (HTdword)iTmp;
		strCell = _T("IDL");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_IDL = (HTdword)iTmp;
		strCell = _T("WLK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_WLK = (HTdword)iTmp;
		strCell = _T("RUN");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_RUN = (HTdword)iTmp;
		strCell = _T("ATK1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_ATK1 = (HTdword)iTmp;
		strCell = _T("ATK2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_ATK2 = (HTdword)iTmp;
		strCell = _T("HIT");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_HIT = (HTdword)iTmp;
		strCell = _T("DIE");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwTAM_DIE = (HTdword)iTmp;
		strCell = _T("Material_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMaterialID = (HTdword)iTmp;
		strCell = _T("MonFXID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMonFXID = (HTdword)iTmp;

		strCell = _T("Scale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->fMonScale = (HTfloat)iTmp/100.0f;

		strCell = _T("R");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("G");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("B");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		pRecord->clrMon = HT_COLOR( (HTfloat) iR/255.0f, (HTfloat) iG/255.0f, (HTfloat) iB/255.0f, 1.0f );

		m_mapTable.insert( HT_ResTableType10_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType10::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType10* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType10;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType10) );

		m_mapTable.insert( HT_ResTableType10_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType10::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType10_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 10;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType10) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType10::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType10_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType10::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strMonsterName;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

//HTbool CHTResTableType10::HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID )
//{
//	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwModelFileID = (itTable->second)->dwTMD;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}

HTbool
CHTResTableType10::HT_bGetMonModelTexItem( HTdword dwID,
										  HTuint& nNumMesh, HTdword& dwBasicModel,
										  HTdword& dwMesh1, HTdword& dwMesh2, HTdword& dwMesh3, HTdword& dwMesh4, HTdword& dwMesh5,
										  HTdword& dwTex1, HTdword& dwTex2, HTdword& dwTex3, HTdword& dwTex4, HTdword& dwTex5,
										  HTdword& dwItemR, HTdword& dwItemRTex, HTdword& dwItemL, HTdword& dwItemLTex )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			nNumMesh		= itTable->second->nNumMesh;
			dwBasicModel	= itTable->second->dwBasicModel;
			dwMesh1			= itTable->second->dwMesh1;
			dwMesh2			= itTable->second->dwMesh2;
			dwMesh3			= itTable->second->dwMesh3;
			dwMesh4			= itTable->second->dwMesh4;
			dwMesh5			= itTable->second->dwMesh5;
			dwTex1			= itTable->second->dwTex1;
			dwTex2			= itTable->second->dwTex2;
			dwTex3			= itTable->second->dwTex3;
			dwTex4			= itTable->second->dwTex4;
			dwTex5			= itTable->second->dwTex5;
			dwItemR			= itTable->second->dwItemR;
			dwItemRTex		= itTable->second->dwItemRTex;
			dwItemL			= itTable->second->dwItemL;
			dwItemLTex		= itTable->second->dwItemLTex;

			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_STD;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetWLKAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_WLK;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetRUNAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_RUN;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_IDL;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetATK1AniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_ATK1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetATK2AniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_ATK2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetHITAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_HIT;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetDIEAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwTAM_DIE;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwMtrlID = (itTable->second)->dwMaterialID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetMonFXID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwMonFXID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetMonScale( HTdword dwID, HTfloat& fScale )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fScale = (itTable->second)->fMonScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType10::HT_bGetMonColor( HTdword dwID, HT_COLOR& clrMon )
{
	HT_ResTableType10_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			clrMon = (itTable->second)->clrMon;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}


CHTResTableType11::CHTResTableType11()
{
}

CHTResTableType11::~CHTResTableType11()
{
	HT_ResTableType11_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType11::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType11* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType11;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strItemName );
		strCell = _T("Model_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSocketModelID = (HTdword)iTmp;
		strCell = _T("ModelTexID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSocketTexID = (HTdword)iTmp;
		strCell = _T("SecondModelID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSecondSocketModelID = (HTdword)iTmp;
		strCell = _T("HideMesh");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strHideMeshName );
		strCell = _T("Fallen_Model_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwFallenModelID = (HTdword)iTmp;
		strCell = _T("Fallen_ModelTex_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwFallenModelTexID = (HTdword)iTmp;
		strCell = _T("Inventory_Tex_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwInvenTexID = (HTdword)iTmp;
		strCell = _T("SocketName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strSocketName );
		strCell = _T("WearItem_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWearItemID = (HTdword)iTmp;
		strCell = _T("ShoesItem_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwShoesItemID = (HTdword)iTmp;
		strCell = _T("Material_ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwMaterialID = (HTdword)iTmp;
		strCell = _T("Equip_SoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwEquipSoundID = (HTdword)iTmp;
		strCell = _T("Type");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemType = (HTdword)iTmp;
		strCell = _T("UnEquip_SoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwUnEquipSoundID = (HTdword)iTmp;
		strCell = _T("Refining012");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining012ID = (HTdword)iTmp;
		strCell = _T("Refining345");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining345ID = (HTdword)iTmp;
		strCell = _T("Refining678");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining678ID = (HTdword)iTmp;
		strCell = _T("Refining910");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining910ID = (HTdword)iTmp;
		strCell = _T("Refining1112");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining1112ID = (HTdword)iTmp;
     
		strCell = _T("Refining13");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining13ID = (HTdword)iTmp;

		strCell = _T("Refining14");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining14ID = (HTdword)iTmp;

		strCell = _T("Refining15");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwItemRefining15ID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType11_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType11::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType11* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType11;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType11) );

		m_mapTable.insert( HT_ResTableType11_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType11::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType11_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 11;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType11) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword CHTResTableType11::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType11_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool CHTResTableType11::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strItemName;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetSocketModelID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSocketModelID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType11::HT_bGetSecondSocketModelID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSecondSocketModelID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType11::HT_bGetHideMeshName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strHideMeshName;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetSocketTexID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSocketTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetFallenModelID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwFallenModelID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetFallenModelTexID( HTdword dwID, HTdword& dwFallenModelTexID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFallenModelTexID = (itTable->second)->dwFallenModelTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetInvenTexID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwInvenTexID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetSocketName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strSocketName;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetWearItemID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWearItemID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetShoesItemID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwShoesItemID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool CHTResTableType11::HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwMtrlID = (itTable->second)->dwMaterialID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType11::HT_bGetEquipSoundID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwEquipSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType11::HT_bGetUnEquipSoundID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwUnEquipSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType11::HT_bGetItemType( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemType;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetItemRifining012( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining012ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetItemRifining345( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining345ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetItemRifining678( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining678ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetItemRifining910( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining910ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType11::HT_bGetItemRifining1112( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining1112ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}
HTbool
CHTResTableType11::HT_bGetItemRifining13( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining13ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}
HTbool
CHTResTableType11::HT_bGetItemRifining14( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining14ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}
HTbool
CHTResTableType11::HT_bGetItemRifining15( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType11_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwItemRefining15ID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}
//CHTResTableType12::CHTResTableType12()
//{
//}
//
//CHTResTableType12::~CHTResTableType12()
//{
//	HT_ResTableType12_It it = m_mapTable.begin();
//	while ( it != m_mapTable.end() )
//	{
//		HT_DELETE( it->second );
//		it = m_mapTable.erase( it );
//	}
//}
//
//HTRESULT CHTResTableType12::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
//{
//	if ( !pXML )
//		return ( HT_FAIL );
//
//	if ( !pXML->HT_isThereTable( strTable ) )
//		return( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HT_ResTableType12* pRecord = HT_NULL;
//	HTint iID, iTmp;
//	CHTString strCell;
//
//	m_nItems = pXML->HT_nGetTableRowCount( strTable );
//
//	--m_nItems;	
//
//	if ( m_nItems <= 0 )
//		return ( HT_FAIL );
//
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType12;
//
//		strCell = _T("ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
//		strCell = _T("Name");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strName );
//		strCell = _T("Impact");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strImpactFX );
//		strCell = _T("Cast");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strCastFX );
//		strCell = _T("Activate");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strActivateFX );
//		strCell = _T("State");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strStateFX );
//		strCell = _T("UIID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwUIID = (HTdword)iTmp;
//
//		m_mapTable.insert( HT_ResTableType12_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTdword CHTResTableType12::HT_dwGetIDByIndex( HTuint idxRow )
//{
//	if ( idxRow > m_mapTable.size() )
//		return ( 0 );
//
//	HT_ResTableType12_It itTable = m_mapTable.begin();
//
//	HTuint i = 0;
//	while ( i < idxRow ) 
//	{
//		itTable++;
//		i++;
//	}
//
//	if ( itTable != m_mapTable.end() )
//		return ( itTable->first );
//
//	return ( 0 );
//}
//
//HTbool CHTResTableType12::HT_bGetName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strName;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType12::HT_bGetImpactFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strImpactFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType12::HT_bGetCastFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strCastFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType12::HT_bGetActivateFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strActivateFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType12::HT_bGetStateFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strStateFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType12::HT_bGetSkillIconID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType12_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwUIID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//CHTResTableType13::CHTResTableType13()
//{
//}
//
//CHTResTableType13::~CHTResTableType13()
//{
//	HT_ResTableType13_It it = m_mapTable.begin();
//	while ( it != m_mapTable.end() )
//	{
//		HT_DELETE( it->second );
//		it = m_mapTable.erase( it );
//	}
//}
//
//HTRESULT CHTResTableType13::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
//{
//	if ( !pXML )
//		return ( HT_FAIL );
//
//	if ( !pXML->HT_isThereTable( strTable ) )
//		return( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HT_ResTableType13* pRecord = HT_NULL;
//	HTint iID, iTmp;
//	CHTString strCell;
//
//	m_nItems = pXML->HT_nGetTableRowCount( strTable );
//
//	--m_nItems;	
//
//	if ( m_nItems <= 0 )
//		return ( HT_FAIL );
//
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType13;
//
//		strCell = _T("ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
//		strCell = _T("NormalAtk");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strNormalAttackFX );
//		strCell = _T("SpecialAtk");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strSpecialAttackFX );
//		strCell = _T("State");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strStateFX );
//		strCell = _T("Idle");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strIdleFX );
//		strCell = _T("Die");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strDieFX );
//		strCell = _T("AttackSoundID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwAttackSoundID = (HTdword)iTmp;
//		strCell = _T("HitSoundID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwHitSoundID = (HTdword)iTmp;
//		strCell = _T("IdleSoundID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwIdleSoundID = (HTdword)iTmp;
//		strCell = _T("DieSoundID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
//		pRecord->dwDieSoundID = (HTdword)iTmp;
//
//		m_mapTable.insert( HT_ResTableType13_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTdword CHTResTableType13::HT_dwGetIDByIndex( HTuint idxRow )
//{
//	if ( idxRow > m_mapTable.size() )
//		return ( 0 );
//
//	HT_ResTableType13_It itTable = m_mapTable.begin();
//
//	HTuint i = 0;
//	while ( i < idxRow ) 
//	{
//		itTable++;
//		i++;
//	}
//
//	if ( itTable != m_mapTable.end() )
//		return ( itTable->first );
//
//	return ( 0 );
//}
//
//HTbool CHTResTableType13::HT_bGetMonNormalAtkFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strNormalAttackFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType13::HT_bGetMonSpecialAtkFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strSpecialAttackFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType13::HT_bGetMonStateFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strStateFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType13::HT_bGetMonIdleFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strIdleFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool CHTResTableType13::HT_bGetMonDieFXName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strDieFX;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType13::HT_bGetMonAttackSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwAttackSoundID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType13::HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwHitSoundID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType13::HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwIdleSoundID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType13::HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwOutID )
//{
//	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwOutID = (itTable->second)->dwDieSoundID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}

CHTResTableType13::CHTResTableType13(){}
CHTResTableType13::~CHTResTableType13()
{
	HT_ResTableType13_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType13::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{	
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType13* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType13;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("AttackSoundID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAttackSoundID1 = (HTdword)iTemp;
		strCell = _T("AttackSoundID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAttackSoundID2 = (HTdword)iTemp;
		strCell = _T("HitSoundID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwHitSoundID = (HTdword)iTemp;
		strCell = _T("HitSoundID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwHit2SoundID = (HTdword)iTemp;
		strCell = _T("WalkSoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwWalkSoundID = (HTdword)iTemp;
		strCell = _T("RunSoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwRunSoundID = (HTdword)iTemp;
		strCell = _T("IdleSoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwIdleSoundID = (HTdword)iTemp;
		strCell = _T("DieSoundID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwDieSoundID = (HTdword)iTemp;

		m_mapTable.insert( HT_ResTableType13_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType13::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType13* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType13;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType13) );

		m_mapTable.insert( HT_ResTableType13_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType13::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType13_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 13;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType13) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTResTableType13::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType13_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}
HTbool
CHTResTableType13::HT_bGetMonAttackSoundID1( HTdword dwID, HTdword& dwAttackSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAttackSoundID = (itTable->second)->dwAttackSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonAttackSoundID2( HTdword dwID, HTdword& dwAttackSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAttackSoundID = (itTable->second)->dwAttackSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwHitSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHitSoundID = (itTable->second)->dwHitSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonHit2SoundID( HTdword dwID, HTdword& dwHit2SoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwHit2SoundID = (itTable->second)->dwHit2SoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonWalkSoundID( HTdword dwID, HTdword& dwWalkSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwWalkSoundID = (itTable->second)->dwWalkSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonRunSoundID( HTdword dwID, HTdword& dwRunSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwRunSoundID = (itTable->second)->dwRunSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwIdleSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwIdleSoundID = (itTable->second)->dwIdleSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType13::HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwDieSoundID )
{
	HT_ResTableType13_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwDieSoundID = (itTable->second)->dwDieSoundID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

//CHTResTableType14::CHTResTableType14(){}
//CHTResTableType14::~CHTResTableType14()
//{
//	HT_ResTableType14_It it = m_mapTable.begin();
//	while ( it != m_mapTable.end() )
//	{
//		HT_DELETE( it->second );
//		it = m_mapTable.erase( it );
//	}
//}
//
//HTRESULT
//CHTResTableType14::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
//{	
//	if ( !pXML )								return ( HT_FAIL );
//	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HT_ResTableType14* pRecord = HT_NULL;
//	HTint iID, iTemp;
//	CHTString strCell;
//
//	m_nItems = pXML->HT_nGetTableRowCount( strTable );
//
//	--m_nItems;	
//
//	if ( m_nItems <= 0 )
//	return ( HT_FAIL );
//
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType14;
//
//		strCell = _T("ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
//		strCell = _T("When");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwWhen = (HTdword)iTemp;
//		strCell = _T("Effect");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strEffectFx );
//		strCell = _T("Obj");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwObjID = (HTdword)iTemp;
//
//		m_mapTable.insert( HT_ResTableType14_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTdword
//CHTResTableType14::HT_dwGetIDByIndex( HTuint idxRow )
//{
//	if ( idxRow > m_mapTable.size() ) return ( 0 );
//
//	HT_ResTableType14_It itTable = m_mapTable.begin();
//
//	HTuint i = 0;
//	while ( i < idxRow ) 
//	{
//		itTable++;
//		i++;
//	}
//
//	if ( itTable != m_mapTable.end() )
//		return ( itTable->first );
//
//	return ( 0 );
//}
//
//HTbool
//CHTResTableType14::HT_bGetFieldWhenActive( HTdword dwID, HTdword& dwWhen )
//{
//	HT_ResTableType14_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwWhen = (itTable->second)->dwWhen;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool
//CHTResTableType14::HT_bGetFieldFxName( HTdword dwID, CHTString& strName )
//{
//	HT_ResTableType14_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strName = (itTable->second)->strEffectFx;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool
//CHTResTableType14::HT_bGetFieldWhereID( HTdword dwID, HTdword& dwWhen )
//{
//	HT_ResTableType14_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwWhen = (itTable->second)->dwObjID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}

//CHTResTableType15::CHTResTableType15(){}
//CHTResTableType15::~CHTResTableType15()
//{
//	HT_ResTableType15_It it = m_mapTable.begin();
//	while ( it != m_mapTable.end() )
//	{
//		HT_DELETE( it->second );
//		it = m_mapTable.erase( it );
//	}
//}
//
//HTRESULT
//CHTResTableType15::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
//{	
//	if ( !pXML )								return ( HT_FAIL );
//	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HT_ResTableType15* pRecord = HT_NULL;
//	HTint iID, iTemp;
//	CHTString strCell;
//
//	m_nItems = pXML->HT_nGetTableRowCount( strTable );
//
//	--m_nItems;	
//
//	if ( m_nItems <= 0 )
//		return ( HT_FAIL );
//
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType15;
//
//		strCell = _T("ID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
//		strCell = _T("File");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFileName );
//		strCell = _T("DayFXID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwDayFXID = (HTdword)iTemp;
//		strCell = _T("NightFXID");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwNightFXID = (HTdword)iTemp;
//		strCell = _T("Pick");
//		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	
//		if ( iTemp )	pRecord->bPick = HT_TRUE;
//		else			pRecord->bPick = HT_FALSE;
//
//		m_mapTable.insert( HT_ResTableType15_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTRESULT	
//CHTResTableType15::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
//{
//	if ( !pFile )
//		return ( HT_FAIL );
//
//	m_strTable = strTable;
//
//	HTint iRecordCount;
//	pFile->HT_bRead( &iRecordCount );
//	m_nItems = iRecordCount;
//
//	HT_ResTableType15* pRecord = HT_NULL;
//	HTint iID;
//	for ( HTuint i = 0; i < m_nItems; i++ )
//	{
//		pRecord = new HT_ResTableType15;
//
//		pFile->HT_bRead( &iID );
//		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType15) );
//
//		m_mapTable.insert( HT_ResTableType15_Value( (HTdword)iID, pRecord ) );
//	}
//
//	return ( HT_OK );
//}
//
//HTRESULT	
//CHTResTableType15::HT_hrSave( CHTFile* pFile )
//{
//	if ( !pFile )
//		return ( HT_FAIL );
//
//	HT_ResTableType15_It itTable;
//	itTable = m_mapTable.begin();
//
//	HTbyte bType = 15;
//	pFile->HT_bWrite( bType );	// class type
//
//	HTint iRecordCount;
//	iRecordCount = (HTint)m_mapTable.size();
//	pFile->HT_bWrite( iRecordCount );	// 줄 수
//
//	HTint iID;
//	while ( itTable != m_mapTable.end() )
//	{
//		iID = itTable->first;
//		pFile->HT_bWrite( iID );
//
//		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType15) );
//
//		itTable++;
//	}
//
//	return ( HT_OK );
//}
//
//HTdword
//CHTResTableType15::HT_dwGetIDByIndex( HTuint idxRow )
//{
//	if ( idxRow > m_mapTable.size() ) return ( 0 );
//
//	HT_ResTableType15_It itTable = m_mapTable.begin();
//
//	HTuint i = 0;
//	while ( i < idxRow ) 
//	{
//		itTable++;
//		i++;
//	}
//
//	if ( itTable != m_mapTable.end() )
//		return ( itTable->first );
//
//	return ( 0 );
//
//}
//
//HTbool		
//CHTResTableType15::HT_bGetFileName( HTdword dwID, CHTString& strFile )
//{
//	HT_ResTableType15_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strFile = (itTable->second)->strFileName;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType15::HT_bGetDayFXID( HTdword dwID, HTdword& dwFXID )
//{
//	HT_ResTableType15_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwFXID = (itTable->second)->dwDayFXID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType15::HT_bGetNightFXID( HTdword dwID, HTdword& dwFXID )
//{
//	HT_ResTableType15_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			dwFXID = (itTable->second)->dwNightFXID;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}
//
//HTbool		
//CHTResTableType15::HT_bGetPickFlag( HTdword dwID, HTbool& bPick )
//{
//	HT_ResTableType15_It itTable = m_mapTable.find( dwID );
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			bPick = (itTable->second)->bPick;
//			return( HT_TRUE );
//		}
//	}
//	return( HT_FALSE );
//}

CHTResTableType20::CHTResTableType20(){}
CHTResTableType20::~CHTResTableType20()
{
	HT_ResTableType20_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType20::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType20* pRecord = HT_NULL;
	HTint iID, iTmp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType20;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("ImpactFX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwImpactFX = (HTdword)iTmp;
		strCell = _T("Man01");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwMan01AnimID = (HTdword)iTmp;
		strCell = _T("Man02");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwMan02AnimID = (HTdword)iTmp;
		strCell = _T("Man03");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwMan03AnimID = (HTdword)iTmp;
		strCell = _T("Wom01");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwWom01AnimID = (HTdword)iTmp;
		strCell = _T("Wom02");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwWom02AnimID = (HTdword)iTmp;
		strCell = _T("Wom03");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );	pRecord->dwWom03AnimID = (HTdword)iTmp;

		strCell = _T("NAG_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID1 = (HTdword)iTmp;
		strCell = _T("NAG_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID2 = (HTdword)iTmp;
		strCell = _T("NAG_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwNAGSoundID3 = (HTdword)iTmp;
		strCell = _T("YAK_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID1 = (HTdword)iTmp;
		strCell = _T("YAK_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID2 = (HTdword)iTmp;
		strCell = _T("YAK_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwYAKSoundID3 = (HTdword)iTmp;
		strCell = _T("ASU_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID1 = (HTdword)iTmp;
		strCell = _T("ASU_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID2 = (HTdword)iTmp;
		strCell = _T("ASU_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwASUSoundID3 = (HTdword)iTmp;
		strCell = _T("DEV_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID1 = (HTdword)iTmp;
		strCell = _T("DEV_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID2 = (HTdword)iTmp;
		strCell = _T("DEV_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwDEVSoundID3 = (HTdword)iTmp;
		strCell = _T("KIM_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID1 = (HTdword)iTmp;
		strCell = _T("KIM_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID2 = (HTdword)iTmp;
		strCell = _T("KIM_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwKIMSoundID3 = (HTdword)iTmp;
		strCell = _T("GAN_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID1 = (HTdword)iTmp;
		strCell = _T("GAN_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID2 = (HTdword)iTmp;
		strCell = _T("GAN_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGANSoundID3 = (HTdword)iTmp;
		strCell = _T("RAK_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID1 = (HTdword)iTmp;
		strCell = _T("RAK_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID2 = (HTdword)iTmp;
		strCell = _T("RAK_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwRAKSoundID3 = (HTdword)iTmp;
		strCell = _T("GAR_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID1 = (HTdword)iTmp;
		strCell = _T("GAR_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID2 = (HTdword)iTmp;
		strCell = _T("GAR_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwGARSoundID3 = (HTdword)iTmp;

		strCell = _T("AttackOK_Sound1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwAttackOKSoundID1 = (HTdword)iTmp;
		strCell = _T("AttackOK_Sound2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwAttackOKSoundID2 = (HTdword)iTmp;
		strCell = _T("AttackOK_Sound3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwAttackOKSoundID3 = (HTdword)iTmp;

		strCell = _T("SwingSoundID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSwingSoundID1 = (HTdword)iTmp;
		strCell = _T("SwingSoundID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSwingSoundID2 = (HTdword)iTmp;
		strCell = _T("SwingSoundID3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwSwingSoundID3 = (HTdword)iTmp;

		strCell = _T("Man_FApron_AnimID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManFApronAnimID1 = (HTdword)iTmp;
		strCell = _T("Man_BApron_AnimID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManBApronAnimID1 = (HTdword)iTmp;
		strCell = _T("Wom_FApron_AnimID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomFApronAnimID1 = (HTdword)iTmp;
		strCell = _T("Wom_BApron_AnimID1");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomBApronAnimID1 = (HTdword)iTmp;
		strCell = _T("Man_FApron_AnimID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManFApronAnimID2 = (HTdword)iTmp;
		strCell = _T("Man_BApron_AnimID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManBApronAnimID2 = (HTdword)iTmp;
		strCell = _T("Wom_FApron_AnimID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomFApronAnimID2 = (HTdword)iTmp;
		strCell = _T("Wom_BApron_AnimID2");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomBApronAnimID2 = (HTdword)iTmp;
		strCell = _T("Man_FApron_AnimID3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManFApronAnimID3 = (HTdword)iTmp;
		strCell = _T("Man_BApron_AnimID3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwManBApronAnimID3 = (HTdword)iTmp;
		strCell = _T("Wom_FApron_AnimID3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomFApronAnimID3 = (HTdword)iTmp;
		strCell = _T("Wom_BApron_AnimID3");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwWomBApronAnimID3 = (HTdword)iTmp;
		strCell = _T("ATK_STD");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwATKSTDAniID = (HTdword)iTmp;
		strCell = _T("ATK_WLK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwATKWLKAniID = (HTdword)iTmp;
		strCell = _T("ATK_RUN");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwATKRUNAniID = (HTdword)iTmp;
		strCell = _T("HIT");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTmp );
		pRecord->dwHITAniID = (HTdword)iTmp;

		m_mapTable.insert( HT_ResTableType20_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType20::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType20* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType20;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType20) );

		m_mapTable.insert( HT_ResTableType20_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType20::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType20_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 20;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType20) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTResTableType20::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType20_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool
CHTResTableType20::HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwImpactFX = (itTable->second)->dwImpactFX;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetManAnim1ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwMan01AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetManAnim2ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwMan02AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetManAnim3ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwMan03AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetWomAnim1ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwWom01AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetWomAnim2ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwWom02AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool
CHTResTableType20::HT_bGetWomAnim3ID( HTdword dwID, HTdword& dwFXID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFXID = (itTable->second)->dwWom03AnimID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwNAGSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwYAKSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwASUSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwDEVSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwKIMSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGANSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwRAKSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwGARSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManFApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManFApronAnimID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManBApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManBApronAnimID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomFApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomFApronAnimID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomBApronAnimID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomBApronAnimID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManFApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManFApronAnimID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManBApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManBApronAnimID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomFApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomFApronAnimID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomBApronAnimID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomBApronAnimID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManFApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManFApronAnimID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetManBApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwManBApronAnimID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomFApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomFApronAnimID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWomBApronAnimID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwWomBApronAnimID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetAttackOKID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwAttackOKSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetAttackOKID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwAttackOKSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetAttackOKID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwAttackOKSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetSwingSoundID1( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSwingSoundID1;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetSwingSoundID2( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSwingSoundID2;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetSwingSoundID3( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwSwingSoundID3;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWPNATKSTDAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwATKSTDAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWPNATKWLKAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwATKWLKAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWPNATKRUNAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwATKRUNAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType20::HT_bGetWPNHITAniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType20_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHITAniID;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

CHTResTableType21::CHTResTableType21(){}
CHTResTableType21::~CHTResTableType21()
{
	HT_ResTableType21_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType21::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType21* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	HTint iReadVal;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType21;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("File");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFile );
		strCell = _T("NAGScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fNAGScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("ASUScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fASUScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("YAKScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fYAKScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("DEVScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fDEVScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("KIMScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fKIMScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("RAKScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fRAKScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("GANScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fGANScale = (HTfloat)iReadVal/100.0f;
		strCell = _T("GARScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->fGARScale = (HTfloat)iReadVal/100.0f;

		m_mapTable.insert( HT_ResTableType21_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType21::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType21* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType21;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType21) );

		m_mapTable.insert( HT_ResTableType21_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType21::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType21_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 21;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType21) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTResTableType21::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType21_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool		
CHTResTableType21::HT_bGetNAGScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fNAGScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetASUScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fASUScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetYAKScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fYAKScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetDEVScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fDEVScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetKIMScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fKIMScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetRAKScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fRAKScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetGANScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fGANScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool		
CHTResTableType21::HT_bGetGARScale( HTdword dwID, HTfloat& fFactor )
{
	HT_ResTableType21_It itTable = m_mapTable.find( dwID );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fFactor = (itTable->second)->fGARScale;
			return( HT_TRUE );
		}
	}
	return( HT_FALSE );
}

HTbool 
CHTResTableType21::HT_bGetFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType21_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFile;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

CHTResTableType23::CHTResTableType23(){}
CHTResTableType23::~CHTResTableType23()
{
	HT_ResTableType23_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType23::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType23* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	HTint iReadVal;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType23;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("File");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFile );
		strCell = _T("Hair1AniID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->dwHain1AniID = (HTdword)iReadVal;
		strCell = _T("NAGScale");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->dwHain2AniID = (HTdword)iReadVal;

		m_mapTable.insert( HT_ResTableType23_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType23::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType23* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType23;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType23) );

		m_mapTable.insert( HT_ResTableType23_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType23::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType23_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 23;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType23) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTResTableType23::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType23_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool 
CHTResTableType23::HT_bGetFileName( HTdword dwID, CHTString& strFile )
{
	HT_ResTableType23_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFile = (itTable->second)->strFile;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool		
CHTResTableType23::HT_bGetHair1AniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType23_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHain1AniID;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTbool		
CHTResTableType23::HT_bGetHair2AniID( HTdword dwID, HTdword& dwOutID )
{
	HT_ResTableType23_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwOutID = (itTable->second)->dwHain2AniID;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

CHTResTableType24::CHTResTableType24()
{
}

CHTResTableType24::~CHTResTableType24()
{
	HT_ResTableType24_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTResTableType24::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )
		return ( HT_FAIL );

	if ( !pXML->HT_isThereTable( strTable ) )
		return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType24* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	// 제일 윗줄은 뺀다. 
	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType24;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );

		HTint iR, iG, iB, iA;

		strCell = _T("ColorR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("ColorG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("ColorB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		strCell = _T("ColorA");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iA );

		pRecord->dwColor = (HTdword)(HT_COLOR( iR/255.0f, iG/255.0f, iB/255.0f, iA/255.0f ));

		m_mapTable.insert( HT_ResTableType24_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType24::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType24* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType24;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType24) );

		m_mapTable.insert( HT_ResTableType24_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType24::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType24_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 24;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType24) );

		itTable++;
	}

	return ( HT_OK );
}

HTbool
CHTResTableType24::HT_bGetDWColor( HTdword dwID, HTdword& dwColor )
{
	HT_ResTableType24_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwColor = (itTable->second)->dwColor;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

HTdword CHTResTableType24::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType24_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

// 지역표시
CHTResTableType25::CHTResTableType25()
{
}

CHTResTableType25::~CHTResTableType25()
{
	HT_ResTableType25_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTResTableType25::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType25* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	HTint iReadVal;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType25;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );		
		strCell = _T("From");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->dwFrom = (HTdword)iReadVal;
		strCell = _T("To");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iReadVal ); pRecord->dwTo = (HTdword)iReadVal;
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strName );

		m_mapTable.insert( HT_ResTableType25_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType25::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType25* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType25;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType25) );

		m_mapTable.insert( HT_ResTableType25_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT	
CHTResTableType25::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType25_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 25;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType25) );

		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTResTableType25::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType25_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTbool 
CHTResTableType25::HT_bGetAreaName( HTdword dwID, CHTString& strName )
{
	HT_ResTableType25_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (itTable->second)->strName;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType25::HT_bGetAreaName( HTdword dwFrom, HTdword dwTo, CHTString& strName )
{
	HT_ResTableType25_It it;
	it = m_mapTable.begin();

	while ( it!= m_mapTable.end() )
	{
		if ( it->second )
		{
			if ((it->second)->dwFrom==dwFrom &&	(it->second)->dwTo==dwTo)
			{
				strName = (it->second)->strName;
				return( HT_TRUE );
			}
		}
		it++;
	}
	return HT_FALSE;
}

HTbool		
CHTResTableType25::HT_bGetAreaFrom( HTdword dwID, HTdword& dwFromID )
{
	HT_ResTableType25_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFromID = (itTable->second)->dwFrom;
			return( HT_TRUE );
		}
		itTable++;
	}

	return( HT_FALSE );
}

HTbool
CHTResTableType25::HT_bGetAreaTo( HTdword dwID, HTdword& dwToID )
{
	HT_ResTableType25_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwToID = (itTable->second)->dwTo;
			return( HT_TRUE );
		}
		itTable++;
	}

	return( HT_FALSE );
}

CHTResTableType26::CHTResTableType26()
{
}

CHTResTableType26::~CHTResTableType26()
{
	HT_ResTableType26_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTdword
CHTResTableType26::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return ( 0 );

	HT_ResTableType26_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return ( 0 );
}

HTRESULT
CHTResTableType26::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType26* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	HTint iR, iG, iB, iA;
	HTtchar szFloat[HT_MAX_STR];
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType26;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("StartScaleX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleStart.x = (HTfloat)atof( szFloat );
		strCell = _T("StartScaleY");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleStart.y = (HTfloat)atof( szFloat );
		strCell = _T("StartScaleZ");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleStart.z = (HTfloat)atof( szFloat );
		strCell = _T("EndScaleX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleEnd.x = (HTfloat)atof( szFloat );
		strCell = _T("EndScaleY");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleEnd.y = (HTfloat)atof( szFloat );
		strCell = _T("EndScaleZ");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->vecScaleEnd.z = (HTfloat)atof( szFloat );
		strCell = _T("StartColorR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("StartColorG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("StartColorB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		strCell = _T("StartColorA");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iA ); pRecord->dwColorStart = (HTdword)(HT_COLOR( iR/255.0f, iG/255.0f, iB/255.0f, iA/255.0f ));
		strCell = _T("EndColorR");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iR );
		strCell = _T("EndColorG");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iG );
		strCell = _T("EndColorB");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iB );
		strCell = _T("EndColorA");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iA ); pRecord->dwColorEnd = (HTdword)(HT_COLOR( iR/255.0f, iG/255.0f, iB/255.0f, iA/255.0f ));
		strCell = _T("Start2EndTime");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->fStart2EndTime = (HTfloat)atof( szFloat );

		m_mapTable.insert( HT_ResTableType26_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT
CHTResTableType26::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType26* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType26;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType26) );

		m_mapTable.insert( HT_ResTableType26_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );

}

HTRESULT
CHTResTableType26::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return ( HT_FAIL );

	HT_ResTableType26_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 26;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType26) );

		itTable++;
	}

	return ( HT_OK );

}

HTbool
CHTResTableType26::HT_bGetScaleStart( HTdword dwID, HTvector3& vecScaleStart )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			vecScaleStart = (itTable->second)->vecScaleStart;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType26::HT_bGetScaleEnd( HTdword dwID, HTvector3& vecScaleEnd )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			vecScaleEnd = (itTable->second)->vecScaleEnd;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType26::HT_bGetColorStart( HTdword dwID, HTdword& dwColorStart )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwColorStart = (itTable->second)->dwColorStart;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType26::HT_bGetColorEnd( HTdword dwID, HTdword& dwColorEnd )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwColorEnd = (itTable->second)->dwColorEnd;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType26::HT_bGetStart2EndTime( HTdword dwID, HTfloat& fStart2EndTime )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			fStart2EndTime = (itTable->second)->fStart2EndTime;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

HTbool
CHTResTableType26::HT_bGetItemRifiningScaleColorTime( HTdword dwID, HTvector3& vecScaleStart, HTvector3& vecScaleEnd, HTdword& dwColorStart, HTdword& dwColorEnd, HTfloat& fStart2EndTime )
{
	HT_ResTableType26_It itTable;
	itTable = m_mapTable.find( dwID );

	while ( itTable != m_mapTable.end() )
	{
		if ( itTable->second ) //fors_debug 혤奈��
		{
			vecScaleStart = (itTable->second)->vecScaleStart;
			vecScaleEnd = (itTable->second)->vecScaleEnd;
			dwColorStart = (itTable->second)->dwColorStart;
			dwColorEnd = (itTable->second)->dwColorEnd;
			fStart2EndTime = (itTable->second)->fStart2EndTime;
			return( HT_TRUE );
		}
		itTable++;
	}
	return HT_FALSE;
}

//-------------------------------------------------------------
// CHTResTableType27
//-------------------------------------------------------------
CHTResTableType27::CHTResTableType27()
{
}

CHTResTableType27::~CHTResTableType27()
{
	HT_ResTableType27_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTdword
CHTResTableType27::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() )
		return ( 0 );

	HT_ResTableType27_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow ) 
	{
		itTable++;
		i++;
	}

	if ( itTable != m_mapTable.end() )
		return ( itTable->first );

	return 0;
}

HTRESULT
CHTResTableType27::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return ( HT_FAIL );

	m_strTable = strTable;

	HT_ResTableType27* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );

	--m_nItems;	

	if ( m_nItems <= 0 )
		return ( HT_FAIL );

	HTtchar szFloat[HT_MAX_STR];
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType27;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Status");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->dwStatus = (HTdword)atoi( szFloat );
		strCell = _T("NORMAL_WALK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->dwSound[0] = (HTdword)atoi( szFloat );
		strCell = _T("NORMAL_RUN");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->dwSound[1] = (HTdword)atoi( szFloat );
		strCell = _T("FIGHT_WALK");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->dwSound[2] = (HTdword)atoi( szFloat );
		strCell = _T("FIGHT_RUN");
		pXML->HT_hrGetTableValue( strTable, strCell, i, szFloat ); pRecord->dwSound[3] = (HTdword)atoi( szFloat );

		m_mapTable.insert( HT_ResTableType27_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTResTableType27::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return ( HT_FAIL );

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HT_ResTableType27* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HT_ResTableType27;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ResTableType27) );

		m_mapTable.insert( HT_ResTableType27_Value( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );

}

HTRESULT
CHTResTableType27::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_ResTableType27_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = 27;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ResTableType27) );

		itTable++;
	}

	return HT_OK;
}

HTdword
CHTResTableType27::HT_dwGetFootSound( HTdword dwID, HTint iMapStatus, HTint iStatus )
{
	HT_ResTableType27_It itTable;
	itTable = m_mapTable.find( dwID );


	while ( itTable != m_mapTable.end() )
	{
		if ((itTable->second)->dwStatus==iMapStatus)
		{
			return (itTable->second)->dwSound[iStatus];
		}
		itTable++;
	}
	return 0;
}
