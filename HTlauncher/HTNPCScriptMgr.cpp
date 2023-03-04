#include "stdafx.h"
#include "HTNPCScriptMgr.h"
#include "HTNPCScriptDef.h"
#include "HTextern.h"

#include "..\..\engine\HTUtilLib\HTXMLParser.h"
#include "..\..\engine\HTUtilLib\HTFile.h"

HTNPCScriptMgr::HTNPCScriptMgr(void) 
{
	m_byNPCType = HT_NPC_TYPE_NONE;
	m_pCurStep = HT_NULL;
}

HTNPCScriptMgr::~HTNPCScriptMgr(void)
{
	HT_NPCScriptMgr_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		HT_DELETEARRAY( (HTtchar*)it->first );
		HT_DELETE( it->second );
		it = m_mapTables.erase( it );
	}
}

HTvoid HTNPCScriptMgr::HT_vCleanUp( )
{
	HT_NPCScriptMgr_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		HT_DELETEARRAY( (HTtchar*)it->first );
		HT_DELETE( it->second );
		it = m_mapTables.erase( it );
	}

	m_pCurStep = HT_NULL;
	m_byNPCType = HT_NPC_TYPE_NONE;
//	m_pCurQuest = HT_NULL; 
}

//-----------------------------------------------------------------------------
// Name		:	HT_hrInit()
// Desc		:	read xml files and load all resource table!
// Params	:	void
// Returns	:	void
//-----------------------------------------------------------------------------
HTRESULT HTNPCScriptMgr::HT_hrInit( CHTString& strFullXMLFile, CHTString strXMLFile )
{
	if( strcmp(strXMLFile.HT_szGetString(), "Mandara_NPC.xml") == 0 )
	{
		return HT_hrInit_Mandara( strFullXMLFile );
	}
	else if( strcmp(strXMLFile.HT_szGetString(), "ShambalaAnu_NPC.xml") == 0 )
	{
		return HT_hrInit_ShambalaAnu( strFullXMLFile );
	}
	else if( strcmp(strXMLFile.HT_szGetString(), "Jina1st_NPC.xml") == 0 )
	{
		return HT_hrInit_Jina1st( strFullXMLFile );
	}
	else if( strcmp(strXMLFile.HT_szGetString(), "Jina3rd_NPC.xml") == 0 )
	{
		return HT_hrInit_Jina3rd( strFullXMLFile );
	}
	else if( strcmp(strXMLFile.HT_szGetString(), "Jina4th_NPC.xml") == 0 )
	{
		return HT_hrInit_Jina4th( strFullXMLFile );
	}
	else if( strcmp(strXMLFile.HT_szGetString(), "Chaturanga_NPC.xml") == 0 )
	{
		return HT_hrInit_Chaturanga( strFullXMLFile );
	}
	else
	{
		CHTString str;
		str.HT_szFormat("Error - File Name!");
		MessageBox(NULL, str, "HTNPCScriptMgr::HT_hrInit", MB_OK);
		return ( HT_FAIL );
	}

	return( HT_FAIL );
}

HTRESULT HTNPCScriptMgr::HT_hrInit_Mandara( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 무기상점 질의문
	strTable = HT_RES_TABLENAME_WEAPON;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 질의문
	strTable = HT_RES_TABLENAME_DEFENSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 액세서리 상점 질의문
	strTable = HT_RES_TABLENAME_ACCESSORY;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 질의문
	strTable = HT_RES_TABLENAME_TEMPLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품 보관 질의문
	strTable = HT_RES_TABLENAME_WAREHOUSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 질의문
	strTable = HT_RES_TABLENAME_CHIEFGUARD;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 역마꾼 질의문
	strTable = HT_RES_TABLENAME_POSTHORSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 주술사 질의문
	strTable = HT_RES_TABLENAME_ANIMALLEND;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 질의문
	strTable = HT_RES_TABLENAME_ETC;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 질의문
	strTable = HT_RES_TABLENAME_SAVEPOINT;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 무기상점 단계별 조합
	strTable = HT_RES_TABLENAME_WEAPON_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 단계별 조합
	strTable = HT_RES_TABLENAME_DEFENSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 기타용품 상점 단계별 조합
	strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 단계별 조합
	strTable = HT_RES_TABLENAME_TEMPLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품보관 단계별 조합
	strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 단계별 조합
	strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 역마꾼 단계별 조합
	strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 주술사 단계별 조합
	strTable = HT_RES_TABLENAME_ANIMALLEND_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 단계별 조합
	strTable = HT_RES_TABLENAME_ETC_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 시나리오 퀘스트 스탭 조합
	strTable = HT_RES_TABLENAME_QUEST_STEP;
	pTable = new CHTQuestStepTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 스탭 조합
	strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}
 
HTRESULT HTNPCScriptMgr::HT_hrInit_ShambalaAnu( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 무기상점 질의문
	strTable = HT_RES_TABLENAME_WEAPON;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 질의문
	strTable = HT_RES_TABLENAME_DEFENSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 액세서리 상점 질의문
	strTable = HT_RES_TABLENAME_ACCESSORY;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 질의문
	strTable = HT_RES_TABLENAME_TEMPLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 질의문
	strTable = HT_RES_TABLENAME_CHIEFGUARD;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 질의문
	strTable = HT_RES_TABLENAME_ETC;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 질의문
	strTable = HT_RES_TABLENAME_SAVEPOINT;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 무기상점 단계별 조합
	strTable = HT_RES_TABLENAME_WEAPON_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 단계별 조합
	strTable = HT_RES_TABLENAME_DEFENSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 기타용품 상점 단계별 조합
	strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 단계별 조합
	strTable = HT_RES_TABLENAME_TEMPLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 단계별 조합
	strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 단계별 조합
	strTable = HT_RES_TABLENAME_ETC_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 스탭 조합
	strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 시나리오 퀘스트 스탭 조합
	strTable = HT_RES_TABLENAME_QUEST_STEP;
	pTable = new CHTQuestStepTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrInit_Jina1st( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 무기상점 질의문
	strTable = HT_RES_TABLENAME_WEAPON;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 질의문
	strTable = HT_RES_TABLENAME_DEFENSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 액세서리 상점 질의문
	strTable = HT_RES_TABLENAME_ACCESSORY;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 질의문
	strTable = HT_RES_TABLENAME_TEMPLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품 보관 질의문
	strTable = HT_RES_TABLENAME_WAREHOUSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 질의문
	strTable = HT_RES_TABLENAME_CHIEFGUARD;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 질의문
	strTable = HT_RES_TABLENAME_SAVEPOINT;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 무기상점 단계별 조합
	strTable = HT_RES_TABLENAME_WEAPON_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 방어구 상점 단계별 조합
	strTable = HT_RES_TABLENAME_DEFENSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 기타용품 상점 단계별 조합
	strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 단계별 조합
	strTable = HT_RES_TABLENAME_TEMPLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품보관 단계별 조합
	strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 수비대장 단계별 조합
	strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 스탭 조합
	strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 시나리오 퀘스트 스탭 조합
	strTable = HT_RES_TABLENAME_QUEST_STEP;
	pTable = new CHTQuestStepTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrInit_Jina3rd( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 액세서리 상점 질의문
	strTable = HT_RES_TABLENAME_ACCESSORY;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 질의문
	strTable = HT_RES_TABLENAME_TEMPLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품 보관 질의문
	strTable = HT_RES_TABLENAME_WAREHOUSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 질의문
	strTable = HT_RES_TABLENAME_ETC;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 질의문
	strTable = HT_RES_TABLENAME_SAVEPOINT;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 기타용품 상점 단계별 조합
	strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 승려 단계별 조합
	strTable = HT_RES_TABLENAME_TEMPLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품보관 단계별 조합
	strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// Etc 단계별 조합
	strTable = HT_RES_TABLENAME_ETC_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 스탭 조합
	strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 시나리오 퀘스트 스탭 조합
	strTable = HT_RES_TABLENAME_QUEST_STEP;
	pTable = new CHTQuestStepTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrInit_Jina4th( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 액세서리 상점 질의문
	strTable = HT_RES_TABLENAME_ACCESSORY;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품 보관 질의문
	strTable = HT_RES_TABLENAME_WAREHOUSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 질의문
	strTable = HT_RES_TABLENAME_SAVEPOINT;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 기타용품 상점 단계별 조합
	strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 물품보관 단계별 조합
	strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 위치저장 스탭 조합
	strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrInit_Chaturanga( CHTString& strXMLFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strXMLFile ) ) )
	{
		CHTString str;
		str.HT_szFormat("%s cannot open!", strXMLFile.HT_szGetString());
		MessageBox(NULL, str, "HTNPCScriptMgr", MB_OK);
		return ( HT_FAIL );
	}
 
	// load resource tables!
	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;

	// 차투랑가 npc 질의문
	strTable = HT_RES_TABLENAME_POSTHORSE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 질의문
	strTable = HT_RES_TABLENAME_BATTLE;
	pTable = new CHT_QuestionTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );


	// 선택문
	strTable = HT_RES_TABLENAME_SELECT;
	pTable = new CHT_SelectTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	// 격투장 단계별 조합
	strTable = HT_RES_TABLENAME_BATTLE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );


	// 차투랑가 npc 단계별 조합
	strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
	pTable = new CHT_ScriptTable;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable, m_szLanguage ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
	}
	else
		HT_DELETE( pTable );

	oXML.HT_hrClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrLoad( CHTString& strFile )
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

	CHTBaseNPCScriptTable* pTable = HT_NULL;
	CHTString strTable;
	HTbyte bType;

	for ( HTint i = 0; i < iSheetCount; i++ )
	{
		oLoadFile.HT_bRead( (HTtchar*)strTable, HT_MAX_STR );
		oLoadFile.HT_bRead( &bType );
		switch( bType ) 
		{
			case HT_TYPE_QUESTION:
				pTable = new CHT_QuestionTable;
				break;
			
			case HT_TYPE_SELECT:
				pTable = new CHT_SelectTable;
				break;
			
			case HT_TYPE_STEP:
				pTable = new CHT_ScriptTable;
				break;
			
			case HT_TYPE_QUEST_STEP:
				pTable = new CHTQuestStepTable;
				break;

			default:
				oLoadFile.HT_vClose();
				return ( HT_FAIL );
		}

		if ( HT_SUCCEED( pTable->HT_hrLoad( &oLoadFile, strTable ) ) )
		{
			HTtchar* szTableName = new HTtchar[HT_MAX_STR];
			CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
			m_mapTables.insert( HT_NPCScriptMgr_Value( szTableName, pTable ) );
		}
		else
			HT_DELETE( pTable );
	}

	oLoadFile.HT_vClose();

	return( HT_OK );
}

HTRESULT HTNPCScriptMgr::HT_hrSave( CHTString& strFile )
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

	HT_NPCScriptMgr_It it = m_mapTables.begin();
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

HTtchar* HTNPCScriptMgr::HT_pGetTableName( HTdword dwID )
{
	m_iQuestion = dwID;

	// 선택문
	if ( HT_IS_SELECT(dwID) )	
		return ( HT_RES_TABLENAME_SELECT );
	// 질의문
	else if ( HT_IS_WEPON_QUE(dwID) )
		return ( HT_RES_TABLENAME_WEAPON );
	
	else if ( HT_IS_DEFENSE_QUE(dwID) )
		return ( HT_RES_TABLENAME_DEFENSE );
	
	else if ( HT_IS_ACCESSORY_QUE(dwID) )
		return ( HT_RES_TABLENAME_ACCESSORY );
	
	else if ( HT_IS_TEMPLE_QUE(dwID) )
		return ( HT_RES_TABLENAME_TEMPLE );
	
	else if ( HT_IS_WAREHOUSE_QUE(dwID) )
		return ( HT_RES_TABLENAME_WAREHOUSE );

	else if ( HT_IS_CHIEFGUARD_QUE(dwID) )
		return ( HT_RES_TABLENAME_CHIEFGUARD );

	else if ( HT_IS_POSTHORSE_QUE(dwID) )
		return ( HT_RES_TABLENAME_POSTHORSE );
	
	else if ( HT_IS_ANIMALLEND_QUE(dwID) )
		return ( HT_RES_TABLENAME_ANIMALLEND );
	
	else if ( HT_IS_ETC_QUE(dwID) )
		return ( HT_RES_TABLENAME_ETC );
		// 격투장
	else if ( HT_IS_BATTLE_QUE(dwID) )
		return ( HT_RES_TABLENAME_BATTLE );
		// 위치저장
	else if ( HT_IS_SAVEPOINT_QUE(dwID) )
		return ( HT_RES_TABLENAME_SAVEPOINT );
	// step
	else if ( HT_IS_WEPON_STEP(dwID) )
		return ( HT_RES_TABLENAME_WEAPON_STEP );
	
	else if ( HT_IS_DEFENSE_STEP(dwID) )
		return ( HT_RES_TABLENAME_DEFENSE_STEP );
	
	else if ( HT_IS_ACCESSORY_STEP(dwID) )
		return ( HT_RES_TABLENAME_ACCESSORY_STEP );
	
	else if ( HT_IS_TEMPLE_STEP(dwID) )
		return ( HT_RES_TABLENAME_TEMPLE_STEP );
	
	else if ( HT_IS_WAREHOUSE_STEP(dwID) )
		return ( HT_RES_TABLENAME_WAREHOUSE_STEP );
	
	else if ( HT_IS_CHIEFGUARD_STEP(dwID) )
		return ( HT_RES_TABLENAME_CHIEFGUARD_STEP );

	else if ( HT_IS_POSTHORSE_STEP(dwID) )
		return ( HT_RES_TABLENAME_POSTHORSE_STEP );
	
	else if ( HT_IS_ANIMALLEND_STEP(dwID) )
		return ( HT_RES_TABLENAME_ANIMALLEND_STEP );
	
	else if ( HT_IS_ETC_STEP(dwID) )
		return ( HT_RES_TABLENAME_ETC_STEP );
		// 격투장
	else if ( HT_IS_BATTLE_STEP(dwID) )
		return ( HT_RES_TABLENAME_BATTLE_STEP );
		// 위치저장
	else if ( HT_IS_SAVEPOINT_STEP(dwID) )
		return ( HT_RES_TABLENAME_SAVEPOINT_STEP );
		// 시나리오 퀘스트 스텝
	else if ( HT_IS_QUEST_STEP(dwID) )
		return ( HT_RES_TABLENAME_QUEST_STEP );

	else
		return ( HT_NULL );
}

CHTBaseNPCScriptTable* HTNPCScriptMgr::HT_pGetTable( HTdword dwID )
{
	HTtchar* pTable = HT_pGetTableName( dwID );
	if ( !pTable )
		return ( HT_NULL );

	HT_NPCScriptMgr_It it = m_mapTables.find( pTable );
	if ( it != m_mapTables.end() )
	{
		return ( it->second );
	}

	return ( HT_NULL );
}

//--------------- 현재 선택된 NPC를 설정하고 그 NPC의 처음 단계를 얻어온다 --------------------------------//
HTint HTNPCScriptMgr::HT_nSetActiveNPC(BYTE byNPCType)
{
//	if ((byNPCType != HT_NPC_TYPE_BATTLE) && g_cNPCControl->m_bPrimium_Button == HT_TRUE && byNPCType != 0)	// NPC 윈도우가 활성화 되기전 이미 크리슈나 버튼으로 인해 열린 창이 있다면 닫아준다.
//	{
		if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ))
		{
			g_cUIManager->HT_HideWindow( _DIALOG_NPCWINDOW );
		}

//		g_cNPCControl->m_bPrimium_Button = HT_FALSE;
//	}
	//else if ((byNPCType != HT_NPC_TYPE_BATTLE) && g_cNPCControl->m_bPrimium_Button == HT_TRUE && byNPCType != 0)


	CHTString strTable, szStep;

	m_byNPCType = HT_NPC_TYPE_NONE;

	switch( byNPCType ) 
	{
		// 무기제조
		case HT_NPC_TYPE_WEPON:	
			strTable = HT_RES_TABLENAME_WEAPON_STEP;
			szStep = _T("1");
			break;
		// 방어구제조
		case HT_NPC_TYPE_DEFENSE:
			strTable = HT_RES_TABLENAME_DEFENSE_STEP;
			szStep = _T("2");
			break;
		// 액세서리 제조
		case HT_NPC_TYPE_ACCESSORY:
			strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
			szStep = _T("3");
			break;
		// 승려
		case HT_NPC_TYPE_TEMPLE:
			strTable = HT_RES_TABLENAME_TEMPLE_STEP;
			szStep = _T("4");
			break;
		// 물품보관
		case HT_NPC_TYPE_WAREHOUSE:
			strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
			szStep = _T("5");
			break;
		// 수비대장
		case HT_NPC_TYPE_CHIEFGUARD:
			strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
			szStep = _T("6");
			break;
		// 역마꾼
		case HT_NPC_TYPE_POSTHORSE:
			strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
			szStep = _T("7");
			break;
		// 주술사
		case HT_NPC_TYPE_ANIMALLEND:
			strTable = HT_RES_TABLENAME_ANIMALLEND_STEP;
			szStep = _T("8");
			break;
		// 병사1
		case HT_NPC_TYPE_SOLDIER1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("9");
			break;
		// 병사2
		case HT_NPC_TYPE_SOLDIER2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("10");
			break;
		// 남자아이1
		case HT_NPC_TYPE_BOY1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("11");
			break;
		// 여자아이1
		case HT_NPC_TYPE_GIRL1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("12");
			break;
		// 퀘스트용 공동 협의체 병사 NPC
		case HT_NPC_TYPE_QUEST_SOLDIER:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("13");
			break;

		// 퀘스트용 스포르바다 병사 NPC
		case HT_NPC_TYPE_QUEST_SPORBADA:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("14");
			break;

		// 퀘스트용 스포르바다 남자아이
		case HT_NPC_TYPE_QUEST_BOY:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("15");
			break;
		// 격투장 NPC
		case HT_NPC_TYPE_BATTLE:
			strTable = HT_RES_TABLENAME_BATTLE_STEP;
			szStep = _T("16");
			break;
		// 위치저장 NPC
		case HT_NPC_TYPE_SAVEPOINT:
			strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
			szStep = _T("17");
			break;
		// 이벤트용 NPC
		case HT_NPC_TYPE_EVENTNPC:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("18");
			break;
		// 예약 NPC (비상용)
		case HT_NPC_TYPE_RESERVED:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("19");
			break;
		// ETC 확장 NPC2
		case HT_NPC_TYPE_EXTRA_ETC2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("21");
			break;
		// ETC 확장 NPC3
		case HT_NPC_TYPE_EXTRA_ETC3:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("22");
			break;
		// ETC 확장 NPC4
		case HT_NPC_TYPE_EXTRA_ETC4:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("23");
			break;
		// ETC 확장 NPC5
		case HT_NPC_TYPE_EXTRA_ETC5:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("24");
			break;
		// ETC 확장 NPC6
		case HT_NPC_TYPE_EXTRA_ETC6:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("25");
			break;
		// ETC 확장 NPC7
		case HT_NPC_TYPE_EXTRA_ETC7:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("26");
			break;

		default:
			return HT_SCRIPT_NEXTSTEP_FAIL;
	}

	m_byNPCType = byNPCType;

	m_ActiveNPC_It = m_mapTables.find( (HTtchar*)strTable );
	if ( m_ActiveNPC_It != m_mapTables.end() )
	{
		if(m_ActiveNPC_It->second)
		{
			m_pCurStep = (m_ActiveNPC_It->second)->HT_bGetStep(szStep, m_byNPCType);
			if(m_pCurStep == HT_NULL)
				return HT_SCRIPT_NEXTSTEP_FAIL;
		}
	}
	else
		return HT_SCRIPT_NEXTSTEP_FAIL;

	return HT_SCRIPT_NEXTSTEP_SUCCESS;
}
 
//-------처음 단계로 셋팅한다---------//
HTint HTNPCScriptMgr::HT_nSetFirstStep()
{
	CHTString strTable, szStep;

	switch( m_byNPCType ) 
	{
		// 무기제조
		case HT_NPC_TYPE_WEPON:	
			strTable = HT_RES_TABLENAME_WEAPON_STEP;
			szStep = _T("1");
			break;
		// 방어구제조
		case HT_NPC_TYPE_DEFENSE:
			strTable = HT_RES_TABLENAME_DEFENSE_STEP;
			szStep = _T("2");
			break;
		// 액세서리 제조
		case HT_NPC_TYPE_ACCESSORY:
			strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
			szStep = _T("3");
			break;
		// 승려
		case HT_NPC_TYPE_TEMPLE:
			strTable = HT_RES_TABLENAME_TEMPLE_STEP;
			szStep = _T("4");
			break;
		// 물품보관
		case HT_NPC_TYPE_WAREHOUSE:
			strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
			szStep = _T("5");
			break;
		// 수비대장
		case HT_NPC_TYPE_CHIEFGUARD:
			strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
			szStep = _T("6");
			break;

		// 역마꾼
		case HT_NPC_TYPE_POSTHORSE:
			strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
			szStep = _T("7");
			break;
		// 주술사
		case HT_NPC_TYPE_ANIMALLEND:
			strTable = HT_RES_TABLENAME_ANIMALLEND_STEP;
			szStep = _T("8");
			break;
		// 병사1
		case HT_NPC_TYPE_SOLDIER1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("9");
			break;
		// 병사2
		case HT_NPC_TYPE_SOLDIER2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("10");
			break;
		// 남자아이1
		case HT_NPC_TYPE_BOY1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("11");
			break;
		// 여자아이1
		case HT_NPC_TYPE_GIRL1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("12");
			break;
		// 퀘스트용 공동 협의체 병사 NPC
		case HT_NPC_TYPE_QUEST_SOLDIER:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("13");
			break;
		// 퀘스트용 스포르바다 병사 NPC
		case HT_NPC_TYPE_QUEST_SPORBADA:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("14");
			break;
		// 퀘스트용 스포르바다 남자아이
		case HT_NPC_TYPE_QUEST_BOY:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("15");
			break;
		// 격투장 NPC
		case HT_NPC_TYPE_BATTLE:
			strTable = HT_RES_TABLENAME_BATTLE_STEP;
			szStep = _T("16");
			break;
		// 위치저장 NPC
		case HT_NPC_TYPE_SAVEPOINT:
			strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
			szStep = _T("17");
			break;
		// 이벤트용 NPC
		case HT_NPC_TYPE_EVENTNPC:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("18");
			break;
		// 예약 NPC (비상용)
		case HT_NPC_TYPE_RESERVED:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("19");
			break;
		// ETC 확장 NPC2
		case HT_NPC_TYPE_EXTRA_ETC2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("21");
			break;
		// ETC 확장 NPC3
		case HT_NPC_TYPE_EXTRA_ETC3:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("22");
			break;
		// ETC 확장 NPC4
		case HT_NPC_TYPE_EXTRA_ETC4:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("23");
			break;
		// ETC 확장 NPC5
		case HT_NPC_TYPE_EXTRA_ETC5:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("24");
			break;
		// ETC 확장 NPC6
		case HT_NPC_TYPE_EXTRA_ETC6:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("25");
			break;
		// ETC 확장 NPC7
		case HT_NPC_TYPE_EXTRA_ETC7:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("26");
			break;

		default:
			return HT_SCRIPT_NEXTSTEP_FAIL;
	}

	m_ActiveNPC_It = m_mapTables.find( (HTtchar*)strTable );
	if ( m_ActiveNPC_It != m_mapTables.end() )
	{
		if(m_ActiveNPC_It->second)
		{
			m_pCurStep = (m_ActiveNPC_It->second)->HT_bGetStep(szStep, m_byNPCType);
			if(m_pCurStep == HT_NULL)
			{
				// 처음 단계를 못찾는다면 다른 오류가 발생했을 수도 있으므로 활성화 NPC Type을 초기화한다.
				m_byNPCType = HT_NPC_TYPE_NONE;	
				return HT_SCRIPT_NEXTSTEP_FAIL;
			}
		}
	}
	else
		return HT_SCRIPT_NEXTSTEP_FAIL;

	return HT_SCRIPT_NEXTSTEP_SUCCESS;
}

//-----------------다음 단계로 간다-----------------------------------//
HTint HTNPCScriptMgr::HT_nNextStep(HTint nSelNum)
{
//	if (g_cNPCControl->m_bPrimium_Button != HT_TRUE)
//	{
		if( nSelNum < 0 || nSelNum > HT_SCRIPT_SEL_MAXSIZE || m_byNPCType == HT_NPC_TYPE_NONE )	
			return HT_SCRIPT_NEXTSTEP_FAIL;
//	}
//	else
//	{
//		m_byNPCType = HT_NPC_TYPE_BATTLE;
//	}
	
	if( m_pCurStep == HT_NULL )
		return HT_SCRIPT_NEXTSTEP_FAIL;
	CHTString szNextStep;
	szNextStep = m_pCurStep->szNextSeq[nSelNum];

	if(szNextStep == _T("NULL") )	// 다음 단계가 없을 경우
		return HT_SCRIPT_NEXTSTEP_FAIL;

	HT_ScriptTable* pNewStep = (m_ActiveNPC_It->second)->HT_bGetStep(szNextStep, m_byNPCType);
	 
	if(pNewStep != HT_NULL)
	{
		// 현재 단계와 다음 단계가 같은 경우
		if( (m_pCurStep->szStep == pNewStep->szStep) && (m_pCurStep->sQuest == pNewStep->sQuest)
				&& (m_pCurStep->sCondition == pNewStep->sCondition) && (m_pCurStep->sCondition2 == pNewStep->sCondition2) )
			return HT_SCRIPT_NEXTSTEP_EQUALSTEP;
		
		m_pCurStep = pNewStep;
		return HT_SCRIPT_NEXTSTEP_SUCCESS;
	}

	return HT_SCRIPT_NEXTSTEP_FAIL;
}

//--------- 현재 단계의 질의문을 얻어온다 -------------//
HTvoid HTNPCScriptMgr::HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam)
{
	// 어떤 NPC의 질의문인지 알아낸다
	HTtchar* pTable = HT_pGetTableName( m_pCurStep->iQuestionIndex );	
	if ( !pTable )
		return;
	 
	HT_NPCScriptMgr_It it = m_mapTables.find(pTable );
	if ( it != m_mapTables.end() )
	{
		if(it->second)
		{
			// 질문
			CHTString::HT_hrStringCopy( szText, 
						(it->second)->HT_szGetStringByIndex(m_pCurStep->iQuestionIndex), HT_SCRIPT_QUE_MAXSIZE );			
			// 파라미터
			(it->second)->HT_bGetPrameterByIndex(m_pCurStep->iQuestionIndex, pbyteParam);
		}
	}
}
   
//--------- 현재 단계의 선택문을 얻어온다 ------------//
HTvoid HTNPCScriptMgr::HT_vGetSelectText(HTint nIndex, CHTString& szText)
{
	HT_NPCScriptMgr_It it = m_mapTables.find(HT_RES_TABLENAME_SELECT);
	if ( it != m_mapTables.end() )
	{
		if(it->second)
			(it->second)->HT_bGetStringByIndex(m_pCurStep->nSelect[nIndex], szText);
	}
}
	
//--------- 현재 단계에서 클라이언트가 해야할 일을 알아낸다 -------------//
HTshort HTNPCScriptMgr::HT_sGetClientEvent()
{
	if( m_pCurStep )
		return m_pCurStep->sClientEvent;
	else
		return eNpcCEventNone;
}

//--------- 현재 단계에서 서버로 보내야할 요청을 알아낸다 ------------//
HTshort HTNPCScriptMgr::HT_sGetServerEvent()
{
	if( m_pCurStep )
		return m_pCurStep->sServerEvent;
	else
		return eNpcSEventReqNone;
}

//-------- 현재 퀘스트 레벨을 찾는다 ----------//
HTvoid HTNPCScriptMgr::HT_vGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& byClientLvlTime)
{
	HT_QuestStepTable*	pCurQuest = HT_NULL;

	HT_NPCScriptMgr_It it = m_mapTables.find(HT_RES_TABLENAME_QUEST_STEP);
	if ( it != m_mapTables.end() )
	{
		if(it->second)
			pCurQuest = (it->second)->HT_pGetQuestLevel(byServerLvl);
	}

	if( pCurQuest == HT_NULL )
	{
		byClientLvl = byClientLvlTime = 0;
	}
	else
	{
		byClientLvl = pCurQuest->byClientLvl;
		byClientLvlTime = pCurQuest->byClientLvlTime;
	}
}

// 현재 퀘스트의 다음 레벨을 얻어온다
HTvoid HTNPCScriptMgr::HT_vGetNextQuestLevel(BYTE& byNextLvl, BYTE& byNextLvlTime)
{
	HT_QuestStepTable*	pCurQuest = HT_NULL;

	HT_NPCScriptMgr_It it = m_mapTables.find(HT_RES_TABLENAME_QUEST_STEP);
	// 현제 퀘스트를 찾는다
	if ( it != m_mapTables.end() )
	{
		if(it->second)
		{
			pCurQuest = (it->second)->HT_pGetCurQuestLevel();
		}
	}

	if( pCurQuest == HT_NULL )
	{
		byNextLvl = byNextLvlTime = 0 ;
		return;
	}
	if( pCurQuest->nNexSeq == 0 )
	{
		byNextLvl = byNextLvlTime = 0 ;
		return;
	}
	// 다음 퀘스트 레벨을 찾는다
	else
	{
		pCurQuest = (it->second)->HT_pGetNextQuestLevel(pCurQuest->nNexSeq);
	}
	
	if( pCurQuest == HT_NULL )
	{
		byNextLvl = byNextLvlTime = 0 ;
	}
	else
	{
		byNextLvl = pCurQuest->byClientLvl;
		byNextLvlTime = pCurQuest->byClientLvlTime;
	}
}

//------------------------------------------------------------------------------------//
CHT_ScriptTable::~CHT_ScriptTable()
{
	HT_ScriptTable_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
} 

HTRESULT CHT_ScriptTable::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	//m_strTable = strTable;
	m_nRows = pXML->HT_nGetTableRowCount( strTable );

	--m_nRows;	

	if ( m_nRows <= 0 )
		return ( HT_FAIL );

	HT_ScriptTable* pRecord = HT_NULL;
	CHTString strCell;
	HTint nSeq, iOut;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_ScriptTable;
		ZeroMemory( pRecord, sizeof( HT_ScriptTable ) );

		strCell = _T("Seq");			// 번호
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nSeq );
//		pRecord->dwSeq = nSeq;

		strCell = _T("Step");			// 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->szStep );

		strCell = _T("Question");		// 질의문
		pXML->HT_hrGetTableValue( strTable, strCell, i, &pRecord->iQuestionIndex ); 

		strCell = _T("Quest");			//퀘스트상태
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sQuest = iOut;

		strCell = _T("Condition");		// 조건
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sCondition = iOut;

		strCell = _T("Condition2");		// 조건2
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sCondition2 = iOut;

		strCell = _T("Client_Event");	// 클라이언트 이벤트
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sClientEvent = iOut;

		strCell = _T("Server_Event");	// 서버 이벤트
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sServerEvent = iOut;

		strCell = _T("Select1");		// 선택문 1
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[0]) );	

		strCell = _T("NextSeq1");		// 선택문 1의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[0]) );

		strCell = _T("Select2");		// 선택문 2
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[1]) );	

		strCell = _T("NextSeq2");		// 선택문 2의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[1]) );

		strCell = _T("Select3");		// 선택문 3
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[2]) );	

		strCell = _T("NextSeq3");		// 선택문 3의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[2]) );

		strCell = _T("Select4");		// 선택문 4
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[3]) );	

		strCell = _T("NextSeq4");		// 선택문 4의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[3]) );

		strCell = _T("Select5");		// 선택문 5
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[4]) );	

		strCell = _T("NextSeq5");		// 선택문 5의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[4]) );
		
		strCell = _T("Select6");		// 선택문 6
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[5]) );	

		strCell = _T("NextSeq6");		// 선택문 6의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[5]) );

		strCell = _T("Select7");		// 선택문 7
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[6]) );	

		strCell = _T("NextSeq7");		// 선택문 7의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[6]) );

		strCell = _T("Select8");		// 선택문 8
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[7]) );	

		strCell = _T("NextSeq8");		// 선택문 8의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[7]) );
		
		strCell = _T("Select9");		// 선택문 9
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[8]) );	

		strCell = _T("NextSeq9");		// 선택문 9의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[8]) );

		strCell = _T("Select10");		// 선택문 10
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[9]) );	

		strCell = _T("NextSeq10");		// 선택문 10의 다음 단계
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[9]) );

		m_mapTable.insert( HT_ScriptTable_Val( (DWORD)nSeq, pRecord ) );
	}

	return ( HT_OK);
}

HTRESULT CHT_ScriptTable::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	//m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nRows = iRecordCount;

	HT_ScriptTable* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_ScriptTable;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_ScriptTable) );

		m_mapTable.insert( HT_ScriptTable_Val( (HTdword)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHT_ScriptTable::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
	return ( HT_FAIL );

	HT_ScriptTable_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_TYPE_STEP;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_ScriptTable) );

		itTable++;
	}

	return ( HT_OK );
}
 
//---------- 특정 step를 반환한다. ------------//
HT_ScriptTable*	CHT_ScriptTable::HT_bGetStep(CHTString szStep, BYTE byNPCType)
{
	HT_ScriptTable_It it = m_mapTable.begin();
	
	HTbool bRes = HT_FALSE;
	while( it != m_mapTable.end() )
	{
		if( (it->second)->szStep == szStep)
		{
			//if( (it->second)->szQuest != _T("NULL") || (it->second)->szCondition != _T("NULL") )	// 조건이 있으면 검사
            //    bRes = HT_bCheckCondition( (it->second)->szQuest, (it->second)->szCondition, (it->second)->szCondition2, byNPCType );				
			// 조건이 있으면 검사
			if( (it->second)->sQuest != eNpcQuestNone || (it->second)->sCondition != eNpcConditionNone )
                bRes = HT_bCheckCondition( (it->second)->sQuest, (it->second)->sCondition, (it->second)->sCondition2, byNPCType );	
			else
				bRes = HT_TRUE;

			if(bRes == HT_TRUE)	// 조건이 맞으면
			{
				return ( it->second );
			}
		}
		it++;
	}

	return HT_NULL;
}
// 일반 조건
HTbool CHT_ScriptTable::HT_bIsCondition( const HTint id )
{
	if ( ( id >= HT_NPC_CONDITION_START ) && ( id <= HT_NPC_CONDITION_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsRelativeCondition( const HTint id )
{
	if ( ( id >= HT_NPC_RELATIVE_CONDITION_START ) && ( id <= HT_NPC_RELATIVE_CONDITION_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsJobCondition( const HTint id )
{
	if ( ( id >= HT_NPC_JOB_CONDITION_START ) && ( id <= HT_NPC_JOB_CONDITION_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsTribeCondition( const HTint id )
{
	if ( ( id >= HT_NPC_TRIBE_CONDITION_START ) && ( id <= HT_NPC_TRIBE_CONDITION_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsLevelCondition( const HTint id )
{
	if ( ( id >= HT_NPC_LEVEL_CONDITION_START ) && ( id <= HT_NPC_LEVEL_CONDITION_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

// 퀘스트 조건
HTbool CHT_ScriptTable::HT_bIsQuestCondition( const HTint id )
{
	if ( ( id >= HT_NPC_QUEST_START ) && ( id <= HT_NPC_QUEST_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsQuestProcessCondition( const HTint id )
{
	if ( ( id >= HT_NPC_QUEST_PROCESS_START ) && ( id <= HT_NPC_QUEST_PROCESS_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

HTbool CHT_ScriptTable::HT_bIsQuestKindCondition( const HTint id )
{
	if ( ( id >= HT_NPC_QUEST_TUTORIAL_START ) && ( id <= HT_NPC_QUEST_SCENARIO4_END ) ) return HT_TRUE;
	else return HT_FALSE;
}

//------------ 조건이 맞는지 검사 --------------------//
HTbool CHT_ScriptTable::HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType)
{
	HTbool bRes = HT_FALSE;

	// 퀘스트 상태 검사
	if( sQuest == eNpcQuestNone )	// 퀘스트 조건이 없는 경우
		bRes = HT_TRUE;
	else
		bRes = HT_bCheckCondition_QuestLevel( sQuest );
	
	// 1번째 조건 검사
	// 퀘스트 상태 조건이 TRUE일 때만 검사
	if( bRes == HT_TRUE && ( sCondition != eNpcConditionNone ) )
	{
		// 퀘스트 번호 검사
		if( HT_bIsQuestKindCondition( sCondition ) )
			bRes = HT_bCheckCondition_QuestIndex( sCondition );
		// 친밀도 검사
		else if( HT_bIsRelativeCondition( sCondition ) )
			bRes = HT_bCheckCondition_NPCRelative( sCondition );
		// 종족 조건 검사
		else if( HT_bIsTribeCondition( sCondition ) )
			bRes = HT_bCheckCondition_Tribe( sCondition );
		// 캐릭터 레벨 검사
		else if( HT_bIsLevelCondition( sCondition ) )
			bRes = HT_bCheckCondition_CharacterLevel(sCondition);
		else
		{
			// 주신 검사
			if(HT_bCheckCondition_Trimuriti( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// 1/2차 전직 검사
			else if( HT_bCheckCondition_JobLevelResult( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// 직업 검사
			else if(HT_bCheckCondition_JobResult( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// 서버 요청에 대한 결과 조건 검사
			else if( HT_bCheckCondition_RequestResult( sCondition, byNPCType ) == HT_TRUE )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
	}

	// 2번째 조건 검사
	// 첫번째 조건이 TRUE 일 때만 검사
	if( bRes == HT_TRUE && ( sCondition2 != eNpcConditionNone ) )
	{
		// 퀘스트 번호 검사
		if( HT_bIsQuestKindCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_QuestIndex( sCondition2 );
		// 1차/2차/3차 조건 검사
		else if( HT_bIsQuestProcessCondition( sCondition2 ) )
            bRes = HT_bCheckCondition_LevelTime( sCondition2 );
		// 친밀도 검사
		else if( HT_bIsRelativeCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_NPCRelative( sCondition2 );
		// 종족 조건 검사
		else if( HT_bIsTribeCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_Tribe( sCondition2 );
		// 캐릭터 레벨 검사
		else if( HT_bIsLevelCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_CharacterLevel( sCondition2 );
		else
		{
			// 낮/밤 조건 검사
			if( HT_bCheckCondition_CurTime( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			// 서버 요청에 대한 결과 조건 검사 
			else if( HT_bCheckCondition_RequestResult( sCondition2, byNPCType ) == HT_TRUE )
				bRes = HT_TRUE;
			// 1/2차 전직 검사
			else if( HT_bCheckCondition_JobLevelResult( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			// 직업 검사
			else if( HT_bCheckCondition_JobResult( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
	}

	return bRes;
}

//---------퀘스트 조건이 맞는지 검사---------//
HTbool CHT_ScriptTable::HT_bCheckCondition_QuestLevel( HTshort sQuest )
{
	HTbool bRes = HT_FALSE;
	// 현재 퀘스트 진행 상태 조사
	BYTE byLevel = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevel();

	switch( sQuest )
	{
		case eNpcQuestStepNone		: // 없음
			if( byLevel == QUEST_STATUS_NONE ) bRes = HT_TRUE;
			break;

		case eNpcQuestStepStart		: // 시작
		{
			// 퀘스트 번호가 0 이고 진행상태가 1이면 튜토리얼 시작 거부 상태
			BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			if(byIndex != 0 && byLevel == QUEST_STATUS_START ) bRes = HT_TRUE;
		}
			break;
		
		case eNpcQuestStepProcess	: // 진행
			if (byLevel == QUEST_STATUS_PROGRESS ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepFail		: // 실패
			if( byLevel == QUEST_STATUS_FAIL ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepSuccess	: // 완료
			if( byLevel == QUEST_STATUS_SUCCESS ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepRejection	: // 거부
		{
			BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			
			// 퀘스트 번호가 0 이고 진행상태가 1이면 튜토리얼 시작 거부 상태
			if( byIndex == QUEST_TUTORIAL_0 && byLevel == QUEST_STATUS_START )
				bRes = HT_TRUE;
			// 시나리오 퀘스트 거부상태
			else if( byIndex >=SCENARIO_QUEST_1_START && byLevel == QUEST_STATUS_REJECTION )
				bRes = HT_TRUE;
		}
			break;
		
		default:
			// 퀘스트 번호가 0 일때는 의미없음.
			if( g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex() == 0 )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
			break;
	}

	return bRes;
}

//-----------퀘스트 번호 조건이 맞는지 검사-----------//
HTbool CHT_ScriptTable::HT_bCheckCondition_QuestIndex( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;
	// 퀘스트 번호
	BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();

	if( byIndex <= TUTORIAL_QUEST_END )	// 초보자 퀘스트
	{
		switch( sCondition )
		{
			case eNpcQuestTutorial0 : // Tutorial0
				if(byIndex == QUEST_TUTORIAL_0)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial1: // Tutorial1
				if(byIndex == QUEST_TUTORIAL_1)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial2: // Tutorial2 
				if(byIndex == QUEST_TUTORIAL_2)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial3: // Tutorial3 
				if(byIndex == QUEST_TUTORIAL_3)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial4: // Tutorial4 
				if(byIndex == QUEST_TUTORIAL_4)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial5: // Tutorial5 
				if(byIndex == QUEST_TUTORIAL_5)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial6: // Tutorial6 
				if(byIndex == QUEST_TUTORIAL_6)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial7: // Tutorial7 
				if(byIndex == QUEST_TUTORIAL_7)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial8: // Tutorial8 
				if(byIndex == QUEST_TUTORIAL_8)		bRes = HT_TRUE;
				break;
			case eNpcQuestTutorial9: // Tutorial9 
				if(byIndex == QUEST_TUTORIAL_9)		bRes = HT_TRUE;
				break;
			default:
				bRes = HT_FALSE; break;
		}
	}
	else if( byIndex <= SCENARIO_QUEST_1_END )	// 1차 시나리오 퀘스트
	{
		switch( sCondition )
		{
			case eNpcQuestTutorial6:	// 1차 전직 6번
				if(byIndex == QUEST_BASIC_GRADE) bRes = HT_TRUE;
				break;
			case eNpcQuestScenario1: // Mandara1 
				if(byIndex == QUEST_MANDARA_1) 		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario2: // Mandara2 
				if(byIndex == QUEST_MANDARA_2)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario3: // Mandara3 
				if(byIndex == QUEST_MANDARA_3)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario4: // Mandara4 
				if(byIndex == QUEST_MANDARA_4)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario5: // Mandara5 
				if(byIndex == QUEST_MANDARA_5)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario6: // Mandara6 
				if(byIndex == QUEST_MANDARA_6)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario7: // Mandara7 
				if(byIndex == QUEST_MANDARA_7)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario8: // Mandara8 
				if(byIndex == QUEST_MANDARA_8)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario9: // Mandara9 
				if(byIndex == QUEST_MANDARA_9)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario10: // Mandara10 
				if(byIndex == QUEST_MANDARA_10)		bRes = HT_TRUE;
				break;
			default :
				bRes = HT_FALSE; break;
		}
	}
	else	// 2차 시나리오 퀘스트
	{
		switch( sCondition )
		{
			case eNpcQuestScenario11: // Shambala1 
				if(byIndex == QUEST_SHAMBALA_1)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario12: // Shambala2
				if(byIndex == QUEST_SHAMBALA_2)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario13: // Shambala3
				if(byIndex == QUEST_SHAMBALA_3)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario14: // Shambala4
				if(byIndex == QUEST_SHAMBALA_4)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario15: // Shambala5
				if(byIndex == QUEST_SHAMBALA_5)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario16: // Shambala6
				if(byIndex == QUEST_SHAMBALA_6)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario17: // Shambala7
				if(byIndex == QUEST_SHAMBALA_7)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario18: // Shambala8
				if(byIndex == QUEST_SHAMBALA_8)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario19: // Shambala9
				if(byIndex == QUEST_SHAMBALA_9)		bRes = HT_TRUE;
				break;
			case eNpcQuestScenario20: // Shambala10
				if(byIndex == QUEST_SHAMBALA_10)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario21: // Shambala11
				if(byIndex == QUEST_SHAMBALA_11)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario22: // Shambala12 
				if(byIndex == QUEST_SHAMBALA_12)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario23: // Shambala13
				if(byIndex == QUEST_SHAMBALA_13)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario24: // Shambala14
				if(byIndex == QUEST_SHAMBALA_14)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario25: // Shambala15
				if(byIndex == QUEST_SHAMBALA_15)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario26: // Jina1
				if(byIndex == QUEST_JINA_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario27: // Jina2
				if(byIndex == QUEST_JINA_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario28: // Jina3
				if(byIndex == QUEST_JINA_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario29: // Jina4
				if(byIndex == QUEST_JINA_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario30: // Jina5
				if(byIndex == QUEST_JINA_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario31: // 유배지1
				if(byIndex == QUEST_JINA2_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario32: // 유배지2
				if(byIndex == QUEST_JINA2_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario33: // 유배지3
				if(byIndex == QUEST_JINA2_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario34: // 유배지4
				if(byIndex == QUEST_JINA2_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario35: // 유배지5
				if(byIndex == QUEST_JINA2_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario36: // 북두성군1
				if(byIndex == QUEST_JINA3_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario37: // 북두성군2
				if(byIndex == QUEST_JINA3_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario38: // 북두성군3
				if(byIndex == QUEST_JINA3_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario39: // 북두성군4
				if(byIndex == QUEST_JINA3_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario40: // 북두성군5
				if(byIndex == QUEST_JINA3_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario41: // 카타나1
				if(byIndex == QUEST_K3_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario42: // 카타나2
				if(byIndex == QUEST_K3_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario43: // 카타나3
				if(byIndex == QUEST_K3_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario44: // 카타나4
				if(byIndex == QUEST_K3_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario45: // 카타나5
				if(byIndex == QUEST_K3_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario81: // Shambala81
				if(byIndex == QUEST_INDEPENDENCE_1)	bRes = HT_TRUE;
				break;
			case eNpcQuestScenario82: // Shambala82
				if(byIndex == QUEST_INDEPENDENCE_2)	bRes = HT_TRUE;
				break;
			default :
				bRes = HT_FALSE; break;
		}
	}

	return bRes;
}

//-----------친밀도 조건이 맞는지 검사----------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_NPCRelative( HTshort sCondition )
{
	HTint nTotalPoint = 0, nSection = 0;
	HTbool bRes = HT_FALSE;

	// 친밀도 알아온다
	g_sNPCSystem->HT_vNPCSystem_CalNPCRelative(/*nGroup, */nTotalPoint, nSection);

	switch( sCondition )
	{
		case eNpcConditionRelative1: // 친밀도1
			if(nSection == 1)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative2: //친밀도2 
			if(nSection == 2)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative3: //친밀도3 
			if(nSection == 3)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative4: //친밀도4 
			if(nSection == 4)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative5: //친밀도5 
			if(nSection == 5)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative6: //친밀도6 
			if(nSection == 6)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative7: //친밀도7 
			if(nSection == 7)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative8: //친밀도8 
			if(nSection == 8)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative9: //친밀도9 
			if(nSection == 9)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative10: //친밀도10 
			if(nSection == 10)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative2Over: //친밀도2이상 
			if(nSection >= 2)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative3Over: //친밀도3이상 
			if(nSection >= 3)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative4Over: //친밀도4이상 
			if(nSection >= 4)		bRes = HT_TRUE;
			break;
		default:
			bRes = HT_FALSE; break;
	}

	return bRes;
}

//-----------종족 조건 검사-------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_Tribe( HTshort sCondition )
{
	HTbool res = HT_FALSE;
	HTint iTribe = g_cMainCharacter->HT_iMainChar_GetTribeServerCode();

	switch( sCondition )
	{
		case eNpcConditionAsura:	// 아수라 
			if( TRIBE_ASURA == iTribe  )		res = HT_TRUE;
			break;
		case eNpcConditionRakshasa: // 라크샤사 
			if( TRIBE_RAKSHASA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionNaga:		// 나가 
			if( TRIBE_NAGA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionKimnara:	// 킨나라 
			if( TRIBE_KINNARA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionYaksa:	// 야크샤 
			if( TRIBE_YAKSA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionGandharva: // 간다르바 
			if( TRIBE_GANDHARVA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionDeva:		// 데바 
			if( TRIBE_DEVA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionGaruda:	// 가루다 
			if( TRIBE_GARUDA == iTribe )		res = HT_TRUE;
			break;
		default:
			res = HT_FALSE; break;
	}

	return res;
}

//----------낮/밤 조건 검사---------//
HTbool CHT_ScriptTable::HT_bCheckCondition_CurTime( HTshort sCondition)
{
	HTbool bRes = HT_FALSE;

	HTfloat fCurTime = g_cNPCControl->HT_fNPCControl_GetCurTime();
	if( sCondition == eNpcConditionDay )
	{
		if( 0 <= fCurTime && fCurTime < 0.5 )
			bRes = HT_TRUE;
	}
	else if( sCondition == eNpcConditionNight )
	{
		if( 0.5 <= fCurTime && fCurTime <= 1 )
			bRes = HT_TRUE;
	}
	else
		bRes = HT_FALSE;
	
	return bRes;
}

//----------- 퀘스트 차수(1차/2차/3차) 조건 검사-------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_LevelTime( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	BYTE byLvlTime = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevelTime();
	switch( sCondition )
	{
		case eNpcQuest1st: // 1차
			if( byLvlTime == QUEST_STATUS_1 )		bRes = HT_TRUE;
			break;
		case eNpcQuest2nd: // 2차 
			if( byLvlTime == QUEST_STATUS_2 )		bRes = HT_TRUE;
			break;
		case eNpcQuest3rd: // 3차 
			if( byLvlTime == QUEST_STATUS_3 )		bRes = HT_TRUE;
			break;
		case eNpcQuest4th: // 4차 
			if( byLvlTime == QUEST_STATUS_4 )		bRes = HT_TRUE;
			break;
		case eNpcQuest5th: // 5차 
			if( byLvlTime == QUEST_STATUS_5 )		bRes = HT_TRUE;
			break;		
		default :
			bRes = HT_FALSE; break;
	}

	return bRes;
}

//---------서버 요청에 대한 결과 조건 검사--------------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_RequestResult( HTshort sCondition, BYTE byNPCType )
{
	HTbool bReqResult = g_cNPCControl->HT_bNPCControl_RequestResult();

	if( sCondition == eNpcConditionSuccess && bReqResult == HT_FALSE ) // 성공	
		return HT_TRUE;
	else if( sCondition == eNpcConditionFail && bReqResult == HT_TRUE ) // 실패
		return HT_TRUE;
	else
		return HT_FALSE;
}

//-----------주신 조건 검사-------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_Trimuriti( HTshort sCondition )
{
	HTbool res = HT_FALSE;

	switch( sCondition )
	{
		case eNpcConditionBrahma :
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA ) res = HT_TRUE;
			break;
		case eNpcConditionVishunu :
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU ) res = HT_TRUE;
			break;
		case eNpcConditionSiva	:
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA ) res = HT_TRUE;
			break;
		default :
			res = HT_FALSE;
	}

	return res;
}

//-----------레벨 조건이 맞는지 검사----------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_CharacterLevel( HTshort sCondition )
{
	HTbyte byLevel = g_cStatus->HT_byGetLevel();
	HTbool bRes = HT_FALSE;
	
	switch( sCondition ) 
	{
		case eNpcConditionLevel10Under : // 10레벨미만
			if( byLevel < 10 ) 		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel10Over : // 10레벨이상
			if( byLevel >= 10 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel30Under : // 30레벨미만
			if( byLevel < 30 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel30Over : // 30레벨이상
			if( byLevel >= 30)		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel45Under : // 45레벨미만
			if( byLevel < 45 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel45Over : // 45레벨이상
			if( byLevel >= 45)		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel1000Under : // 1000레벨미만
			if( byLevel < 1000 )	bRes = HT_TRUE;
			break;
		default :
			bRes = HT_FALSE; break;
	}

	return bRes;
}

// 1/2차 전직 검사
HTbool CHT_ScriptTable::HT_bCheckCondition_JobLevelResult( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	if( sCondition == eNpcConditionChangeJob1 ) // 1차전직
	{
		if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL0 )
			bRes = HT_TRUE;
	}
	else if( sCondition == eNpcConditionChangeJob2) // 2차전직
	{
		if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL1 )
			bRes = HT_TRUE;
	}
	else
		bRes = HT_FALSE;

	return bRes;
}

// 직업 검사
HTbool CHT_ScriptTable::HT_bCheckCondition_JobResult( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	switch( sCondition )
	{
		//case eNpcConditionJobSatvan : // 전사
		//	if( byClass2 == CLASS_SATVAN ) 	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobDhvanta : // 암살자
		//	if( byClass2 == CLASS_DHVANTA )	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobNirvana : // 격투사
		//	if( byClass2 == CLASS_NIRVANA )	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobMantrika : // 법사
		//	if( byClass2 == CLASS_MANTRIKA )	bRes = HT_TRUE;
		//	break;
		case eNpcConditionJobSatya : // 사트야
			if( g_oMainCharacterInfo.byClass2 == CLASS_SATVAN1 ) 	bRes = HT_TRUE;
			break;
		case eNpcConditionJobVanare	: // 바나르
			if( g_oMainCharacterInfo.byClass2 == CLASS_SATVAN2 ) 	bRes = HT_TRUE;
			break;
		case eNpcConditionJobDruta : // 드루타
			if( g_oMainCharacterInfo.byClass2 == CLASS_DHVANTA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobKarya : // 카르야
			if( g_oMainCharacterInfo.byClass2 == CLASS_DHVANTA2 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobNakayuda : // 나카유다
			if( g_oMainCharacterInfo.byClass2 == CLASS_NIRVANA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobVaidya	: // 바이드야
			if( g_oMainCharacterInfo.byClass2 == CLASS_NIRVANA2 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobAbicara : // 아비카라
			if( g_oMainCharacterInfo.byClass2 == CLASS_MANTRIKA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobSamavat : // 사마바트
			if( g_oMainCharacterInfo.byClass2 == CLASS_MANTRIKA2 )	bRes = HT_TRUE;
			break;
		default :
			bRes = HT_FALSE; break;
	}

	return bRes;
}

//---------------------------------------------------------------------------------------------------//
CHT_QuestionTable::~CHT_QuestionTable()
{
	HT_QuestionTable_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHT_QuestionTable::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	//m_strTable = strTable;
	m_nRows = pXML->HT_nGetTableRowCount( strTable );

	--m_nRows;	

	if ( m_nRows <= 0 )
		return ( HT_FAIL );

	HT_QuestionTable* pRecord = HT_NULL;
	CHTString strCell;
	HTint	nIndex, iParam = 0;
	for ( HTuint i = 0; i < m_nRows; ++i)
	{
		HT_QuestionTableLS QuestionTableLS;

		strCell = _T("iIndex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nIndex );

		strCell = _T("byteParameter");
		//pXML->HT_hrGetTableValue( strTable, strCell, i, QuestionTableLS.szParameter );
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iParam );
		QuestionTableLS.byteParameter = (HTbyte)iParam;

		//strCell = _T("szText");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_szText");
		else
			strCell = _T("kor_szText");
		pXML->HT_hrGetTableValue( strTable, strCell, i, QuestionTableLS.szText );

		pRecord = new HT_QuestionTable;

		//pRecord->strParameter = QuestionTableLS.szParameter;
		pRecord->byteParameter = QuestionTableLS.byteParameter;
		pRecord->strText = QuestionTableLS.szText;

		m_mapTable.insert( HT_QuestionTable_Val( (DWORD)nIndex, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHT_QuestionTable::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );
	//m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nRows = iRecordCount;

	HT_QuestionTable* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		HT_QuestionTableLS QuestionTableLS;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( &QuestionTableLS, sizeof(HT_QuestionTableLS) );

		pRecord = new HT_QuestionTable;
		//pRecord->strParameter = QuestionTableLS.szParameter;
		pRecord->byteParameter = QuestionTableLS.byteParameter;
		pRecord->strText = QuestionTableLS.szText;

		m_mapTable.insert( HT_QuestionTable_Val( (DWORD)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHT_QuestionTable::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_QuestionTable_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_TYPE_QUESTION;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	HT_QuestionTableLS QuestionTableLS;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;

		memset( &QuestionTableLS, 0, sizeof(HT_QuestionTableLS) );
		//CHTString::HT_hrStringCopy( QuestionTableLS.szParameter, (itTable->second)->strParameter, 20 );
		QuestionTableLS.byteParameter = (itTable->second)->byteParameter;
		CHTString::HT_hrStringCopy( QuestionTableLS.szText, (itTable->second)->strText, HT_SCRIPT_QUE_MAXSIZE );

		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( &QuestionTableLS, sizeof(HT_QuestionTableLS) );

		itTable++;
	}

	return ( HT_OK );
}

// 질의문 가져오기
HTtchar*
CHT_QuestionTable::HT_szGetStringByIndex( HTuint nIndex )
{
	if ( nIndex == 0 )
	{
		return HT_NULL;
	}
	else
	{
		HT_QuestionTable_It itTable;
		itTable = m_mapTable.find( nIndex );

		if ( itTable != m_mapTable.end() )
		{
			if ( itTable->second )
			{
				return (itTable->second)->strText; 
			}
		}

		return HT_NULL;
	}
}
//
//HTbool CHT_QuestionTable::HT_bGetStringByIndex(HTuint nIndex, HTtchar* strText)
//{
//	if(nIndex == 0)	// 질의문이 없을때 사용하는 인덱스
//	{
//		strText = NULL;
//		return HT_TRUE;
//	}
//
//	HT_QuestionTable_It itTable;
//	itTable = m_mapTable.find( nIndex );
//
//	if ( itTable != m_mapTable.end() )
//	{
//		if ( itTable->second )
//		{
//			strcpy(strText, (itTable->second)->szText ); 
//			return( HT_TRUE );
//		}
//	}
//
//	return( HT_FALSE );
//}
// 질의문의 파라미터 가져오기
//HTbool CHT_QuestionTable::HT_bGetPrameterByIndex( HTuint nIndex, CHTString& szParam )
HTbool CHT_QuestionTable::HT_bGetPrameterByIndex( HTuint nIndex, HTbyte* pbyteParam )
{
	if(nIndex == 0)	// 질의문이 없을때 사용하는 인덱스
	{
		//szParam.HT_hrCleanUp();
		*pbyteParam = eNpcParamNone;
		return HT_TRUE;
	}

	HT_QuestionTable_It itTable;
	itTable = m_mapTable.find( nIndex );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			//szParam = (itTable->second)->szParameter;
			//szParam = (itTable->second)->strParameter;
			*pbyteParam = (itTable->second)->byteParameter;
			return( HT_TRUE );
		}
	}

	return( HT_FALSE );
}

//-------------------------------------------------------------------------//
CHT_SelectTable::~CHT_SelectTable()
{
	HT_SelectTable_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHT_SelectTable::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	//m_strTable = strTable;
	m_nRows = pXML->HT_nGetTableRowCount( strTable );

	--m_nRows;	

	if ( m_nRows <= 0 )
		return ( HT_FAIL );

	HT_SelectTable* pRecord = HT_NULL;
	CHTString strCell;
	HTint	nIndex;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_SelectTable;

		strCell = _T("Index");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nIndex );

		//strCell = _T("Text");
		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("chi_Text");
		else
			strCell = _T("kor_Text");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->szText );
		
		m_mapTable.insert( HT_SelectTable_Val( (DWORD)nIndex, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHT_SelectTable::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	//m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nRows = iRecordCount;

	HT_SelectTable* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_SelectTable;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_SelectTable) );

		m_mapTable.insert( HT_SelectTable_Val( (DWORD)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHT_SelectTable::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_SelectTable_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_TYPE_SELECT;
	pFile->HT_bWrite( bType );	// class type

    HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_SelectTable) );

		itTable++;
	}

	return ( HT_OK );
}

HTbool CHT_SelectTable::HT_bGetStringByIndex(HTuint nIndex, CHTString& strText)
{
	if(nIndex == 0)	// 선택문이 없을 때 사용하는 인덱스
	{
		strText.HT_hrCleanUp();
		return HT_TRUE;
	}

	HT_SelectTable_It itTable;
	itTable = m_mapTable.find( nIndex );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strText = (itTable->second)->szText;
			return( HT_TRUE );
		}
	}

	strText.HT_hrCleanUp();	// 빈 스트링을 만든다.
	return( HT_FALSE );
}
//-----------------------------------------------------------------------------------
CHTQuestStepTable::~CHTQuestStepTable()
{
	HT_QuestStepTable_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT CHTQuestStepTable::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML )								return ( HT_FAIL );
	if ( !pXML->HT_isThereTable( strTable ) )	return( HT_FAIL );

	//m_strTable = strTable;
	m_nRows = pXML->HT_nGetTableRowCount( strTable );

	--m_nRows;	

	if ( m_nRows <= 0 )
		return ( HT_FAIL );

	HT_QuestStepTable* pRecord = HT_NULL;
	CHTString strCell;
	HTint	nIndex, nVal;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_QuestStepTable;

		// Seq
		strCell = _T("Seq");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nIndex );
		pRecord->nSeq = nIndex;
		// 퀘스트 번호
		strCell = _T("QuestIndex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byQuestIndex = (BYTE)nVal;
		// NPC 번호
		strCell = _T("NPCIndex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &pRecord->nNPCIndex );
		// 서버의 퀘스트 단계
		strCell = _T("ServerLevel");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byServerLvl = (BYTE)nVal;
		// 클라이언트의 퀘스트 단계 - 거부/시작/진행/완료
		strCell = _T("ClientLevel");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byClientLvl = (BYTE)nVal;
		// 클라이언트의 퀘스트 단계 - 1차/2차/3차
		strCell = _T("ClientLevelTime");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byClientLvlTime = (BYTE)nVal;
		// 거부나 1차완료등을 위한 퀘스트의 다음 단계의 seq
		strCell = _T("NextSeq");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &pRecord->nNexSeq );

		m_mapTable.insert( HT_QuestStepTable_Val( (DWORD)nIndex, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHTQuestStepTable::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile )
		return ( HT_FAIL );

	//m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nRows = iRecordCount;

	HT_QuestStepTable* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nRows; i++ )
	{
		pRecord = new HT_QuestStepTable;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HT_QuestStepTable) );

		m_mapTable.insert( HT_QuestStepTable_Val( (DWORD)iID, pRecord ) );
	}

	return ( HT_OK );
}

HTRESULT CHTQuestStepTable::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile )
		return ( HT_FAIL );

	HT_QuestStepTable_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_TYPE_QUEST_STEP;
	pFile->HT_bWrite( bType );	// class type

    HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// 줄 수

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		pFile->HT_bWrite( itTable->second, sizeof(HT_QuestStepTable) );

		itTable++;
	}

	return ( HT_OK );
}

// 퀘스트의 레벨을 얻어온다
HT_QuestStepTable* CHTQuestStepTable::HT_pGetQuestLevel(BYTE byServerLvl)
{
	BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
	HTint nNPCIndex = g_sNPCSystem->HT_dwNPCSystem_GetActiveNPCIndex();

	HT_QuestStepTable_It it = m_mapTable.begin();
	
	while( it != m_mapTable.end() )
	{
		if( (it->second)->byQuestIndex == byQuestIndex && (it->second)->nNPCIndex == nNPCIndex 
													&& (it->second)->byServerLvl == byServerLvl )
		{
			return ( it->second );
		}
		it++;
	}

	return HT_NULL;
}

// 퀘스트의 현재 레벨을 얻어온다
HT_QuestStepTable* CHTQuestStepTable::HT_pGetCurQuestLevel()
{
	BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
	HTint nNPCIndex = g_sNPCSystem->HT_dwNPCSystem_GetActiveNPCIndex();
	BYTE byLevel = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevel();
	BYTE byLvlTime = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevelTime();

	HT_QuestStepTable_It it = m_mapTable.begin();
	
	while( it != m_mapTable.end() )
	{
		if( (it->second)->byQuestIndex == byQuestIndex && (it->second)->nNPCIndex == nNPCIndex 
			&& (it->second)->byClientLvl == byLevel && (it->second)->byClientLvlTime == byLvlTime )
		{
			return ( it->second );
		}
		it++;
	}

	return HT_NULL;
}

// 현재 퀘스트의 다음 레벨을 얻어온다
HT_QuestStepTable* CHTQuestStepTable::HT_pGetNextQuestLevel(HTint nNextSeq)
{
	BYTE byQuestIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();

	HT_QuestStepTable_It it = m_mapTable.begin();
	
	while( it != m_mapTable.end() )
	{
		if( nNextSeq == (it->second)->nSeq )
		{
			return (it->second);
		}
		it++;
	}

	return HT_NULL;
}

