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

	// ������� ���ǹ�
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

	// �� ���� ���ǹ�
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

	// �׼����� ���� ���ǹ�
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

	// �·� ���ǹ�
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

	// ��ǰ ���� ���ǹ�
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

	// ������� ���ǹ�
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

	// ������ ���ǹ�
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

	// �ּ��� ���ǹ�
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

	// Etc ���ǹ�
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

	// ������ ���ǹ�
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

	// ��ġ���� ���ǹ�
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

	// ���ù�
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

	// ������� �ܰ躰 ����
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

	// �� ���� �ܰ躰 ����
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

	// ��Ÿ��ǰ ���� �ܰ躰 ����
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

	// �·� �ܰ躰 ����
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

	// ��ǰ���� �ܰ躰 ����
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

	// ������� �ܰ躰 ����
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

	// ������ �ܰ躰 ����
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

	// �ּ��� �ܰ躰 ����
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

	// Etc �ܰ躰 ����
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

	// �ó����� ����Ʈ ���� ����
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

	// ������ �ܰ躰 ����
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

	// ��ġ���� ���� ����
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

	// ������� ���ǹ�
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

	// �� ���� ���ǹ�
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

	// �׼����� ���� ���ǹ�
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

	// �·� ���ǹ�
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

	// ������� ���ǹ�
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

	// Etc ���ǹ�
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

	// ������ ���ǹ�
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

	// ��ġ���� ���ǹ�
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

	// ���ù�
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

	// ������� �ܰ躰 ����
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

	// �� ���� �ܰ躰 ����
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

	// ��Ÿ��ǰ ���� �ܰ躰 ����
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

	// �·� �ܰ躰 ����
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

	// ������� �ܰ躰 ����
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

	// Etc �ܰ躰 ����
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

	// ������ �ܰ躰 ����
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

	// ��ġ���� ���� ����
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

	// �ó����� ����Ʈ ���� ����
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

	// ������� ���ǹ�
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

	// �� ���� ���ǹ�
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

	// �׼����� ���� ���ǹ�
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

	// �·� ���ǹ�
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

	// ��ǰ ���� ���ǹ�
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

	// ������� ���ǹ�
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

	// ������ ���ǹ�
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

	// ��ġ���� ���ǹ�
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

	// ���ù�
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

	// ������� �ܰ躰 ����
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

	// �� ���� �ܰ躰 ����
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

	// ��Ÿ��ǰ ���� �ܰ躰 ����
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

	// �·� �ܰ躰 ����
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

	// ��ǰ���� �ܰ躰 ����
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

	// ������� �ܰ躰 ����
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

	// ������ �ܰ躰 ����
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

	// ��ġ���� ���� ����
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

	// �ó����� ����Ʈ ���� ����
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

	// �׼����� ���� ���ǹ�
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

	// �·� ���ǹ�
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

	// ��ǰ ���� ���ǹ�
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

	// Etc ���ǹ�
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

	// ������ ���ǹ�
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

	// ��ġ���� ���ǹ�
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

	// ���ù�
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

	// ��Ÿ��ǰ ���� �ܰ躰 ����
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

	// �·� �ܰ躰 ����
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

	// ��ǰ���� �ܰ躰 ����
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

	// Etc �ܰ躰 ����
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

	// ������ �ܰ躰 ����
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

	// ��ġ���� ���� ����
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

	// �ó����� ����Ʈ ���� ����
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

	// �׼����� ���� ���ǹ�
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

	// ��ǰ ���� ���ǹ�
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

	// ������ ���ǹ�
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

	// ��ġ���� ���ǹ�
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

	// ���ù�
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

	// ��Ÿ��ǰ ���� �ܰ躰 ����
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

	// ��ǰ���� �ܰ躰 ����
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

	// ������ �ܰ躰 ����
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

	// ��ġ���� ���� ����
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

	// �������� npc ���ǹ�
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

	// ������ ���ǹ�
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


	// ���ù�
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

	// ������ �ܰ躰 ����
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


	// �������� npc �ܰ躰 ����
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

	// ���ù�
	if ( HT_IS_SELECT(dwID) )	
		return ( HT_RES_TABLENAME_SELECT );
	// ���ǹ�
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
		// ������
	else if ( HT_IS_BATTLE_QUE(dwID) )
		return ( HT_RES_TABLENAME_BATTLE );
		// ��ġ����
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
		// ������
	else if ( HT_IS_BATTLE_STEP(dwID) )
		return ( HT_RES_TABLENAME_BATTLE_STEP );
		// ��ġ����
	else if ( HT_IS_SAVEPOINT_STEP(dwID) )
		return ( HT_RES_TABLENAME_SAVEPOINT_STEP );
		// �ó����� ����Ʈ ����
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

//--------------- ���� ���õ� NPC�� �����ϰ� �� NPC�� ó�� �ܰ踦 ���´� --------------------------------//
HTint HTNPCScriptMgr::HT_nSetActiveNPC(BYTE byNPCType)
{
//	if ((byNPCType != HT_NPC_TYPE_BATTLE) && g_cNPCControl->m_bPrimium_Button == HT_TRUE && byNPCType != 0)	// NPC �����찡 Ȱ��ȭ �Ǳ��� �̹� ũ������ ��ư���� ���� ���� â�� �ִٸ� �ݾ��ش�.
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
		// ��������
		case HT_NPC_TYPE_WEPON:	
			strTable = HT_RES_TABLENAME_WEAPON_STEP;
			szStep = _T("1");
			break;
		// ������
		case HT_NPC_TYPE_DEFENSE:
			strTable = HT_RES_TABLENAME_DEFENSE_STEP;
			szStep = _T("2");
			break;
		// �׼����� ����
		case HT_NPC_TYPE_ACCESSORY:
			strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
			szStep = _T("3");
			break;
		// �·�
		case HT_NPC_TYPE_TEMPLE:
			strTable = HT_RES_TABLENAME_TEMPLE_STEP;
			szStep = _T("4");
			break;
		// ��ǰ����
		case HT_NPC_TYPE_WAREHOUSE:
			strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
			szStep = _T("5");
			break;
		// �������
		case HT_NPC_TYPE_CHIEFGUARD:
			strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
			szStep = _T("6");
			break;
		// ������
		case HT_NPC_TYPE_POSTHORSE:
			strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
			szStep = _T("7");
			break;
		// �ּ���
		case HT_NPC_TYPE_ANIMALLEND:
			strTable = HT_RES_TABLENAME_ANIMALLEND_STEP;
			szStep = _T("8");
			break;
		// ����1
		case HT_NPC_TYPE_SOLDIER1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("9");
			break;
		// ����2
		case HT_NPC_TYPE_SOLDIER2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("10");
			break;
		// ���ھ���1
		case HT_NPC_TYPE_BOY1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("11");
			break;
		// ���ھ���1
		case HT_NPC_TYPE_GIRL1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("12");
			break;
		// ����Ʈ�� ���� ����ü ���� NPC
		case HT_NPC_TYPE_QUEST_SOLDIER:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("13");
			break;

		// ����Ʈ�� �������ٴ� ���� NPC
		case HT_NPC_TYPE_QUEST_SPORBADA:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("14");
			break;

		// ����Ʈ�� �������ٴ� ���ھ���
		case HT_NPC_TYPE_QUEST_BOY:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("15");
			break;
		// ������ NPC
		case HT_NPC_TYPE_BATTLE:
			strTable = HT_RES_TABLENAME_BATTLE_STEP;
			szStep = _T("16");
			break;
		// ��ġ���� NPC
		case HT_NPC_TYPE_SAVEPOINT:
			strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
			szStep = _T("17");
			break;
		// �̺�Ʈ�� NPC
		case HT_NPC_TYPE_EVENTNPC:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("18");
			break;
		// ���� NPC (����)
		case HT_NPC_TYPE_RESERVED:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("19");
			break;
		// ETC Ȯ�� NPC2
		case HT_NPC_TYPE_EXTRA_ETC2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("21");
			break;
		// ETC Ȯ�� NPC3
		case HT_NPC_TYPE_EXTRA_ETC3:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("22");
			break;
		// ETC Ȯ�� NPC4
		case HT_NPC_TYPE_EXTRA_ETC4:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("23");
			break;
		// ETC Ȯ�� NPC5
		case HT_NPC_TYPE_EXTRA_ETC5:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("24");
			break;
		// ETC Ȯ�� NPC6
		case HT_NPC_TYPE_EXTRA_ETC6:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("25");
			break;
		// ETC Ȯ�� NPC7
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
 
//-------ó�� �ܰ�� �����Ѵ�---------//
HTint HTNPCScriptMgr::HT_nSetFirstStep()
{
	CHTString strTable, szStep;

	switch( m_byNPCType ) 
	{
		// ��������
		case HT_NPC_TYPE_WEPON:	
			strTable = HT_RES_TABLENAME_WEAPON_STEP;
			szStep = _T("1");
			break;
		// ������
		case HT_NPC_TYPE_DEFENSE:
			strTable = HT_RES_TABLENAME_DEFENSE_STEP;
			szStep = _T("2");
			break;
		// �׼����� ����
		case HT_NPC_TYPE_ACCESSORY:
			strTable = HT_RES_TABLENAME_ACCESSORY_STEP;
			szStep = _T("3");
			break;
		// �·�
		case HT_NPC_TYPE_TEMPLE:
			strTable = HT_RES_TABLENAME_TEMPLE_STEP;
			szStep = _T("4");
			break;
		// ��ǰ����
		case HT_NPC_TYPE_WAREHOUSE:
			strTable = HT_RES_TABLENAME_WAREHOUSE_STEP;
			szStep = _T("5");
			break;
		// �������
		case HT_NPC_TYPE_CHIEFGUARD:
			strTable = HT_RES_TABLENAME_CHIEFGUARD_STEP;
			szStep = _T("6");
			break;

		// ������
		case HT_NPC_TYPE_POSTHORSE:
			strTable = HT_RES_TABLENAME_POSTHORSE_STEP;
			szStep = _T("7");
			break;
		// �ּ���
		case HT_NPC_TYPE_ANIMALLEND:
			strTable = HT_RES_TABLENAME_ANIMALLEND_STEP;
			szStep = _T("8");
			break;
		// ����1
		case HT_NPC_TYPE_SOLDIER1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("9");
			break;
		// ����2
		case HT_NPC_TYPE_SOLDIER2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("10");
			break;
		// ���ھ���1
		case HT_NPC_TYPE_BOY1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("11");
			break;
		// ���ھ���1
		case HT_NPC_TYPE_GIRL1:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("12");
			break;
		// ����Ʈ�� ���� ����ü ���� NPC
		case HT_NPC_TYPE_QUEST_SOLDIER:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("13");
			break;
		// ����Ʈ�� �������ٴ� ���� NPC
		case HT_NPC_TYPE_QUEST_SPORBADA:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("14");
			break;
		// ����Ʈ�� �������ٴ� ���ھ���
		case HT_NPC_TYPE_QUEST_BOY:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("15");
			break;
		// ������ NPC
		case HT_NPC_TYPE_BATTLE:
			strTable = HT_RES_TABLENAME_BATTLE_STEP;
			szStep = _T("16");
			break;
		// ��ġ���� NPC
		case HT_NPC_TYPE_SAVEPOINT:
			strTable = HT_RES_TABLENAME_SAVEPOINT_STEP;
			szStep = _T("17");
			break;
		// �̺�Ʈ�� NPC
		case HT_NPC_TYPE_EVENTNPC:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("18");
			break;
		// ���� NPC (����)
		case HT_NPC_TYPE_RESERVED:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("19");
			break;
		// ETC Ȯ�� NPC2
		case HT_NPC_TYPE_EXTRA_ETC2:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("21");
			break;
		// ETC Ȯ�� NPC3
		case HT_NPC_TYPE_EXTRA_ETC3:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("22");
			break;
		// ETC Ȯ�� NPC4
		case HT_NPC_TYPE_EXTRA_ETC4:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("23");
			break;
		// ETC Ȯ�� NPC5
		case HT_NPC_TYPE_EXTRA_ETC5:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("24");
			break;
		// ETC Ȯ�� NPC6
		case HT_NPC_TYPE_EXTRA_ETC6:
			strTable = HT_RES_TABLENAME_ETC_STEP;
			szStep = _T("25");
			break;
		// ETC Ȯ�� NPC7
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
				// ó�� �ܰ踦 ��ã�´ٸ� �ٸ� ������ �߻����� ���� �����Ƿ� Ȱ��ȭ NPC Type�� �ʱ�ȭ�Ѵ�.
				m_byNPCType = HT_NPC_TYPE_NONE;	
				return HT_SCRIPT_NEXTSTEP_FAIL;
			}
		}
	}
	else
		return HT_SCRIPT_NEXTSTEP_FAIL;

	return HT_SCRIPT_NEXTSTEP_SUCCESS;
}

//-----------------���� �ܰ�� ����-----------------------------------//
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

	if(szNextStep == _T("NULL") )	// ���� �ܰ谡 ���� ���
		return HT_SCRIPT_NEXTSTEP_FAIL;

	HT_ScriptTable* pNewStep = (m_ActiveNPC_It->second)->HT_bGetStep(szNextStep, m_byNPCType);
	 
	if(pNewStep != HT_NULL)
	{
		// ���� �ܰ�� ���� �ܰ谡 ���� ���
		if( (m_pCurStep->szStep == pNewStep->szStep) && (m_pCurStep->sQuest == pNewStep->sQuest)
				&& (m_pCurStep->sCondition == pNewStep->sCondition) && (m_pCurStep->sCondition2 == pNewStep->sCondition2) )
			return HT_SCRIPT_NEXTSTEP_EQUALSTEP;
		
		m_pCurStep = pNewStep;
		return HT_SCRIPT_NEXTSTEP_SUCCESS;
	}

	return HT_SCRIPT_NEXTSTEP_FAIL;
}

//--------- ���� �ܰ��� ���ǹ��� ���´� -------------//
HTvoid HTNPCScriptMgr::HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam)
{
	// � NPC�� ���ǹ����� �˾Ƴ���
	HTtchar* pTable = HT_pGetTableName( m_pCurStep->iQuestionIndex );	
	if ( !pTable )
		return;
	 
	HT_NPCScriptMgr_It it = m_mapTables.find(pTable );
	if ( it != m_mapTables.end() )
	{
		if(it->second)
		{
			// ����
			CHTString::HT_hrStringCopy( szText, 
						(it->second)->HT_szGetStringByIndex(m_pCurStep->iQuestionIndex), HT_SCRIPT_QUE_MAXSIZE );			
			// �Ķ����
			(it->second)->HT_bGetPrameterByIndex(m_pCurStep->iQuestionIndex, pbyteParam);
		}
	}
}
   
//--------- ���� �ܰ��� ���ù��� ���´� ------------//
HTvoid HTNPCScriptMgr::HT_vGetSelectText(HTint nIndex, CHTString& szText)
{
	HT_NPCScriptMgr_It it = m_mapTables.find(HT_RES_TABLENAME_SELECT);
	if ( it != m_mapTables.end() )
	{
		if(it->second)
			(it->second)->HT_bGetStringByIndex(m_pCurStep->nSelect[nIndex], szText);
	}
}
	
//--------- ���� �ܰ迡�� Ŭ���̾�Ʈ�� �ؾ��� ���� �˾Ƴ��� -------------//
HTshort HTNPCScriptMgr::HT_sGetClientEvent()
{
	if( m_pCurStep )
		return m_pCurStep->sClientEvent;
	else
		return eNpcCEventNone;
}

//--------- ���� �ܰ迡�� ������ �������� ��û�� �˾Ƴ��� ------------//
HTshort HTNPCScriptMgr::HT_sGetServerEvent()
{
	if( m_pCurStep )
		return m_pCurStep->sServerEvent;
	else
		return eNpcSEventReqNone;
}

//-------- ���� ����Ʈ ������ ã�´� ----------//
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

// ���� ����Ʈ�� ���� ������ ���´�
HTvoid HTNPCScriptMgr::HT_vGetNextQuestLevel(BYTE& byNextLvl, BYTE& byNextLvlTime)
{
	HT_QuestStepTable*	pCurQuest = HT_NULL;

	HT_NPCScriptMgr_It it = m_mapTables.find(HT_RES_TABLENAME_QUEST_STEP);
	// ���� ����Ʈ�� ã�´�
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
	// ���� ����Ʈ ������ ã�´�
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

		strCell = _T("Seq");			// ��ȣ
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nSeq );
//		pRecord->dwSeq = nSeq;

		strCell = _T("Step");			// �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->szStep );

		strCell = _T("Question");		// ���ǹ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, &pRecord->iQuestionIndex ); 

		strCell = _T("Quest");			//����Ʈ����
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sQuest = iOut;

		strCell = _T("Condition");		// ����
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sCondition = iOut;

		strCell = _T("Condition2");		// ����2
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sCondition2 = iOut;

		strCell = _T("Client_Event");	// Ŭ���̾�Ʈ �̺�Ʈ
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sClientEvent = iOut;

		strCell = _T("Server_Event");	// ���� �̺�Ʈ
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iOut );
		pRecord->sServerEvent = iOut;

		strCell = _T("Select1");		// ���ù� 1
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[0]) );	

		strCell = _T("NextSeq1");		// ���ù� 1�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[0]) );

		strCell = _T("Select2");		// ���ù� 2
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[1]) );	

		strCell = _T("NextSeq2");		// ���ù� 2�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[1]) );

		strCell = _T("Select3");		// ���ù� 3
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[2]) );	

		strCell = _T("NextSeq3");		// ���ù� 3�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[2]) );

		strCell = _T("Select4");		// ���ù� 4
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[3]) );	

		strCell = _T("NextSeq4");		// ���ù� 4�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[3]) );

		strCell = _T("Select5");		// ���ù� 5
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[4]) );	

		strCell = _T("NextSeq5");		// ���ù� 5�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[4]) );
		
		strCell = _T("Select6");		// ���ù� 6
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[5]) );	

		strCell = _T("NextSeq6");		// ���ù� 6�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[5]) );

		strCell = _T("Select7");		// ���ù� 7
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[6]) );	

		strCell = _T("NextSeq7");		// ���ù� 7�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[6]) );

		strCell = _T("Select8");		// ���ù� 8
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[7]) );	

		strCell = _T("NextSeq8");		// ���ù� 8�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[7]) );
		
		strCell = _T("Select9");		// ���ù� 9
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[8]) );	

		strCell = _T("NextSeq9");		// ���ù� 9�� ���� �ܰ�
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)(pRecord->szNextSeq[8]) );

		strCell = _T("Select10");		// ���ù� 10
		pXML->HT_hrGetTableValue( strTable, strCell, i, &(pRecord->nSelect[9]) );	

		strCell = _T("NextSeq10");		// ���ù� 10�� ���� �ܰ�
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
	pFile->HT_bWrite( iRecordCount );	// �� ��

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
 
//---------- Ư�� step�� ��ȯ�Ѵ�. ------------//
HT_ScriptTable*	CHT_ScriptTable::HT_bGetStep(CHTString szStep, BYTE byNPCType)
{
	HT_ScriptTable_It it = m_mapTable.begin();
	
	HTbool bRes = HT_FALSE;
	while( it != m_mapTable.end() )
	{
		if( (it->second)->szStep == szStep)
		{
			//if( (it->second)->szQuest != _T("NULL") || (it->second)->szCondition != _T("NULL") )	// ������ ������ �˻�
            //    bRes = HT_bCheckCondition( (it->second)->szQuest, (it->second)->szCondition, (it->second)->szCondition2, byNPCType );				
			// ������ ������ �˻�
			if( (it->second)->sQuest != eNpcQuestNone || (it->second)->sCondition != eNpcConditionNone )
                bRes = HT_bCheckCondition( (it->second)->sQuest, (it->second)->sCondition, (it->second)->sCondition2, byNPCType );	
			else
				bRes = HT_TRUE;

			if(bRes == HT_TRUE)	// ������ ������
			{
				return ( it->second );
			}
		}
		it++;
	}

	return HT_NULL;
}
// �Ϲ� ����
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

// ����Ʈ ����
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

//------------ ������ �´��� �˻� --------------------//
HTbool CHT_ScriptTable::HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType)
{
	HTbool bRes = HT_FALSE;

	// ����Ʈ ���� �˻�
	if( sQuest == eNpcQuestNone )	// ����Ʈ ������ ���� ���
		bRes = HT_TRUE;
	else
		bRes = HT_bCheckCondition_QuestLevel( sQuest );
	
	// 1��° ���� �˻�
	// ����Ʈ ���� ������ TRUE�� ���� �˻�
	if( bRes == HT_TRUE && ( sCondition != eNpcConditionNone ) )
	{
		// ����Ʈ ��ȣ �˻�
		if( HT_bIsQuestKindCondition( sCondition ) )
			bRes = HT_bCheckCondition_QuestIndex( sCondition );
		// ģ�е� �˻�
		else if( HT_bIsRelativeCondition( sCondition ) )
			bRes = HT_bCheckCondition_NPCRelative( sCondition );
		// ���� ���� �˻�
		else if( HT_bIsTribeCondition( sCondition ) )
			bRes = HT_bCheckCondition_Tribe( sCondition );
		// ĳ���� ���� �˻�
		else if( HT_bIsLevelCondition( sCondition ) )
			bRes = HT_bCheckCondition_CharacterLevel(sCondition);
		else
		{
			// �ֽ� �˻�
			if(HT_bCheckCondition_Trimuriti( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// 1/2�� ���� �˻�
			else if( HT_bCheckCondition_JobLevelResult( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// ���� �˻�
			else if(HT_bCheckCondition_JobResult( sCondition ) == HT_TRUE)
				bRes = HT_TRUE;
			// ���� ��û�� ���� ��� ���� �˻�
			else if( HT_bCheckCondition_RequestResult( sCondition, byNPCType ) == HT_TRUE )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
	}

	// 2��° ���� �˻�
	// ù��° ������ TRUE �� ���� �˻�
	if( bRes == HT_TRUE && ( sCondition2 != eNpcConditionNone ) )
	{
		// ����Ʈ ��ȣ �˻�
		if( HT_bIsQuestKindCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_QuestIndex( sCondition2 );
		// 1��/2��/3�� ���� �˻�
		else if( HT_bIsQuestProcessCondition( sCondition2 ) )
            bRes = HT_bCheckCondition_LevelTime( sCondition2 );
		// ģ�е� �˻�
		else if( HT_bIsRelativeCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_NPCRelative( sCondition2 );
		// ���� ���� �˻�
		else if( HT_bIsTribeCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_Tribe( sCondition2 );
		// ĳ���� ���� �˻�
		else if( HT_bIsLevelCondition( sCondition2 ) )
			bRes = HT_bCheckCondition_CharacterLevel( sCondition2 );
		else
		{
			// ��/�� ���� �˻�
			if( HT_bCheckCondition_CurTime( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			// ���� ��û�� ���� ��� ���� �˻� 
			else if( HT_bCheckCondition_RequestResult( sCondition2, byNPCType ) == HT_TRUE )
				bRes = HT_TRUE;
			// 1/2�� ���� �˻�
			else if( HT_bCheckCondition_JobLevelResult( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			// ���� �˻�
			else if( HT_bCheckCondition_JobResult( sCondition2 ) == HT_TRUE )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
		}
	}

	return bRes;
}

//---------����Ʈ ������ �´��� �˻�---------//
HTbool CHT_ScriptTable::HT_bCheckCondition_QuestLevel( HTshort sQuest )
{
	HTbool bRes = HT_FALSE;
	// ���� ����Ʈ ���� ���� ����
	BYTE byLevel = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevel();

	switch( sQuest )
	{
		case eNpcQuestStepNone		: // ����
			if( byLevel == QUEST_STATUS_NONE ) bRes = HT_TRUE;
			break;

		case eNpcQuestStepStart		: // ����
		{
			// ����Ʈ ��ȣ�� 0 �̰� ������°� 1�̸� Ʃ�丮�� ���� �ź� ����
			BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			if(byIndex != 0 && byLevel == QUEST_STATUS_START ) bRes = HT_TRUE;
		}
			break;
		
		case eNpcQuestStepProcess	: // ����
			if (byLevel == QUEST_STATUS_PROGRESS ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepFail		: // ����
			if( byLevel == QUEST_STATUS_FAIL ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepSuccess	: // �Ϸ�
			if( byLevel == QUEST_STATUS_SUCCESS ) bRes = HT_TRUE;
			break;
		
		case eNpcQuestStepRejection	: // �ź�
		{
			BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();
			
			// ����Ʈ ��ȣ�� 0 �̰� ������°� 1�̸� Ʃ�丮�� ���� �ź� ����
			if( byIndex == QUEST_TUTORIAL_0 && byLevel == QUEST_STATUS_START )
				bRes = HT_TRUE;
			// �ó����� ����Ʈ �źλ���
			else if( byIndex >=SCENARIO_QUEST_1_START && byLevel == QUEST_STATUS_REJECTION )
				bRes = HT_TRUE;
		}
			break;
		
		default:
			// ����Ʈ ��ȣ�� 0 �϶��� �ǹ̾���.
			if( g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex() == 0 )
				bRes = HT_TRUE;
			else
				bRes = HT_FALSE;
			break;
	}

	return bRes;
}

//-----------����Ʈ ��ȣ ������ �´��� �˻�-----------//
HTbool CHT_ScriptTable::HT_bCheckCondition_QuestIndex( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;
	// ����Ʈ ��ȣ
	BYTE byIndex = g_sNPCSystem->HT_byNPCSystem_GetLastQuestIndex();

	if( byIndex <= TUTORIAL_QUEST_END )	// �ʺ��� ����Ʈ
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
	else if( byIndex <= SCENARIO_QUEST_1_END )	// 1�� �ó����� ����Ʈ
	{
		switch( sCondition )
		{
			case eNpcQuestTutorial6:	// 1�� ���� 6��
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
	else	// 2�� �ó����� ����Ʈ
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
			case eNpcQuestScenario31: // ������1
				if(byIndex == QUEST_JINA2_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario32: // ������2
				if(byIndex == QUEST_JINA2_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario33: // ������3
				if(byIndex == QUEST_JINA2_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario34: // ������4
				if(byIndex == QUEST_JINA2_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario35: // ������5
				if(byIndex == QUEST_JINA2_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario36: // �ϵμ���1
				if(byIndex == QUEST_JINA3_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario37: // �ϵμ���2
				if(byIndex == QUEST_JINA3_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario38: // �ϵμ���3
				if(byIndex == QUEST_JINA3_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario39: // �ϵμ���4
				if(byIndex == QUEST_JINA3_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario40: // �ϵμ���5
				if(byIndex == QUEST_JINA3_5)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario41: // īŸ��1
				if(byIndex == QUEST_K3_1)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario42: // īŸ��2
				if(byIndex == QUEST_K3_2)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario43: // īŸ��3
				if(byIndex == QUEST_K3_3)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario44: // īŸ��4
				if(byIndex == QUEST_K3_4)			bRes = HT_TRUE;
				break;
			case eNpcQuestScenario45: // īŸ��5
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

//-----------ģ�е� ������ �´��� �˻�----------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_NPCRelative( HTshort sCondition )
{
	HTint nTotalPoint = 0, nSection = 0;
	HTbool bRes = HT_FALSE;

	// ģ�е� �˾ƿ´�
	g_sNPCSystem->HT_vNPCSystem_CalNPCRelative(/*nGroup, */nTotalPoint, nSection);

	switch( sCondition )
	{
		case eNpcConditionRelative1: // ģ�е�1
			if(nSection == 1)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative2: //ģ�е�2 
			if(nSection == 2)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative3: //ģ�е�3 
			if(nSection == 3)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative4: //ģ�е�4 
			if(nSection == 4)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative5: //ģ�е�5 
			if(nSection == 5)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative6: //ģ�е�6 
			if(nSection == 6)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative7: //ģ�е�7 
			if(nSection == 7)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative8: //ģ�е�8 
			if(nSection == 8)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative9: //ģ�е�9 
			if(nSection == 9)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative10: //ģ�е�10 
			if(nSection == 10)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative2Over: //ģ�е�2�̻� 
			if(nSection >= 2)		bRes = HT_TRUE;
				break;
		case eNpcConditionRelative3Over: //ģ�е�3�̻� 
			if(nSection >= 3)		bRes = HT_TRUE;
			break;
		case eNpcConditionRelative4Over: //ģ�е�4�̻� 
			if(nSection >= 4)		bRes = HT_TRUE;
			break;
		default:
			bRes = HT_FALSE; break;
	}

	return bRes;
}

//-----------���� ���� �˻�-------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_Tribe( HTshort sCondition )
{
	HTbool res = HT_FALSE;
	HTint iTribe = g_cMainCharacter->HT_iMainChar_GetTribeServerCode();

	switch( sCondition )
	{
		case eNpcConditionAsura:	// �Ƽ��� 
			if( TRIBE_ASURA == iTribe  )		res = HT_TRUE;
			break;
		case eNpcConditionRakshasa: // ��ũ���� 
			if( TRIBE_RAKSHASA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionNaga:		// ���� 
			if( TRIBE_NAGA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionKimnara:	// Ų���� 
			if( TRIBE_KINNARA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionYaksa:	// ��ũ�� 
			if( TRIBE_YAKSA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionGandharva: // ���ٸ��� 
			if( TRIBE_GANDHARVA == iTribe )		res = HT_TRUE;
			break;
		case eNpcConditionDeva:		// ���� 
			if( TRIBE_DEVA == iTribe )			res = HT_TRUE;
			break;
		case eNpcConditionGaruda:	// ����� 
			if( TRIBE_GARUDA == iTribe )		res = HT_TRUE;
			break;
		default:
			res = HT_FALSE; break;
	}

	return res;
}

//----------��/�� ���� �˻�---------//
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

//----------- ����Ʈ ����(1��/2��/3��) ���� �˻�-------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_LevelTime( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	BYTE byLvlTime = g_sNPCSystem->HT_byNPCSystem_GetLastQuestLevelTime();
	switch( sCondition )
	{
		case eNpcQuest1st: // 1��
			if( byLvlTime == QUEST_STATUS_1 )		bRes = HT_TRUE;
			break;
		case eNpcQuest2nd: // 2�� 
			if( byLvlTime == QUEST_STATUS_2 )		bRes = HT_TRUE;
			break;
		case eNpcQuest3rd: // 3�� 
			if( byLvlTime == QUEST_STATUS_3 )		bRes = HT_TRUE;
			break;
		case eNpcQuest4th: // 4�� 
			if( byLvlTime == QUEST_STATUS_4 )		bRes = HT_TRUE;
			break;
		case eNpcQuest5th: // 5�� 
			if( byLvlTime == QUEST_STATUS_5 )		bRes = HT_TRUE;
			break;		
		default :
			bRes = HT_FALSE; break;
	}

	return bRes;
}

//---------���� ��û�� ���� ��� ���� �˻�--------------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_RequestResult( HTshort sCondition, BYTE byNPCType )
{
	HTbool bReqResult = g_cNPCControl->HT_bNPCControl_RequestResult();

	if( sCondition == eNpcConditionSuccess && bReqResult == HT_FALSE ) // ����	
		return HT_TRUE;
	else if( sCondition == eNpcConditionFail && bReqResult == HT_TRUE ) // ����
		return HT_TRUE;
	else
		return HT_FALSE;
}

//-----------�ֽ� ���� �˻�-------------//
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

//-----------���� ������ �´��� �˻�----------------//
HTbool CHT_ScriptTable::HT_bCheckCondition_CharacterLevel( HTshort sCondition )
{
	HTbyte byLevel = g_cStatus->HT_byGetLevel();
	HTbool bRes = HT_FALSE;
	
	switch( sCondition ) 
	{
		case eNpcConditionLevel10Under : // 10�����̸�
			if( byLevel < 10 ) 		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel10Over : // 10�����̻�
			if( byLevel >= 10 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel30Under : // 30�����̸�
			if( byLevel < 30 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel30Over : // 30�����̻�
			if( byLevel >= 30)		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel45Under : // 45�����̸�
			if( byLevel < 45 )		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel45Over : // 45�����̻�
			if( byLevel >= 45)		bRes = HT_TRUE;
			break;
		case eNpcConditionLevel1000Under : // 1000�����̸�
			if( byLevel < 1000 )	bRes = HT_TRUE;
			break;
		default :
			bRes = HT_FALSE; break;
	}

	return bRes;
}

// 1/2�� ���� �˻�
HTbool CHT_ScriptTable::HT_bCheckCondition_JobLevelResult( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	if( sCondition == eNpcConditionChangeJob1 ) // 1������
	{
		if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL0 )
			bRes = HT_TRUE;
	}
	else if( sCondition == eNpcConditionChangeJob2) // 2������
	{
		if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL1 )
			bRes = HT_TRUE;
	}
	else
		bRes = HT_FALSE;

	return bRes;
}

// ���� �˻�
HTbool CHT_ScriptTable::HT_bCheckCondition_JobResult( HTshort sCondition )
{
	HTbool bRes = HT_FALSE;

	switch( sCondition )
	{
		//case eNpcConditionJobSatvan : // ����
		//	if( byClass2 == CLASS_SATVAN ) 	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobDhvanta : // �ϻ���
		//	if( byClass2 == CLASS_DHVANTA )	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobNirvana : // ������
		//	if( byClass2 == CLASS_NIRVANA )	bRes = HT_TRUE;
		//	break;
		//case eNpcConditionJobMantrika : // ����
		//	if( byClass2 == CLASS_MANTRIKA )	bRes = HT_TRUE;
		//	break;
		case eNpcConditionJobSatya : // ��Ʈ��
			if( g_oMainCharacterInfo.byClass2 == CLASS_SATVAN1 ) 	bRes = HT_TRUE;
			break;
		case eNpcConditionJobVanare	: // �ٳ���
			if( g_oMainCharacterInfo.byClass2 == CLASS_SATVAN2 ) 	bRes = HT_TRUE;
			break;
		case eNpcConditionJobDruta : // ���Ÿ
			if( g_oMainCharacterInfo.byClass2 == CLASS_DHVANTA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobKarya : // ī����
			if( g_oMainCharacterInfo.byClass2 == CLASS_DHVANTA2 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobNakayuda : // ��ī����
			if( g_oMainCharacterInfo.byClass2 == CLASS_NIRVANA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobVaidya	: // ���̵��
			if( g_oMainCharacterInfo.byClass2 == CLASS_NIRVANA2 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobAbicara : // �ƺ�ī��
			if( g_oMainCharacterInfo.byClass2 == CLASS_MANTRIKA1 )	bRes = HT_TRUE;
			break;
		case eNpcConditionJobSamavat : // �縶��Ʈ
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
	pFile->HT_bWrite( iRecordCount );	// �� ��

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

// ���ǹ� ��������
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
//	if(nIndex == 0)	// ���ǹ��� ������ ����ϴ� �ε���
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
// ���ǹ��� �Ķ���� ��������
//HTbool CHT_QuestionTable::HT_bGetPrameterByIndex( HTuint nIndex, CHTString& szParam )
HTbool CHT_QuestionTable::HT_bGetPrameterByIndex( HTuint nIndex, HTbyte* pbyteParam )
{
	if(nIndex == 0)	// ���ǹ��� ������ ����ϴ� �ε���
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
	pFile->HT_bWrite( iRecordCount );	// �� ��

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
	if(nIndex == 0)	// ���ù��� ���� �� ����ϴ� �ε���
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

	strText.HT_hrCleanUp();	// �� ��Ʈ���� �����.
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
		// ����Ʈ ��ȣ
		strCell = _T("QuestIndex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byQuestIndex = (BYTE)nVal;
		// NPC ��ȣ
		strCell = _T("NPCIndex");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &pRecord->nNPCIndex );
		// ������ ����Ʈ �ܰ�
		strCell = _T("ServerLevel");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byServerLvl = (BYTE)nVal;
		// Ŭ���̾�Ʈ�� ����Ʈ �ܰ� - �ź�/����/����/�Ϸ�
		strCell = _T("ClientLevel");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byClientLvl = (BYTE)nVal;
		// Ŭ���̾�Ʈ�� ����Ʈ �ܰ� - 1��/2��/3��
		strCell = _T("ClientLevelTime");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &nVal );
		pRecord->byClientLvlTime = (BYTE)nVal;
		// �źγ� 1���Ϸ���� ���� ����Ʈ�� ���� �ܰ��� seq
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
	pFile->HT_bWrite( iRecordCount );	// �� ��

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

// ����Ʈ�� ������ ���´�
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

// ����Ʈ�� ���� ������ ���´�
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

// ���� ����Ʈ�� ���� ������ ���´�
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

