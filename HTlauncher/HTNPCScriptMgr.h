//////////////////////////////////////////////////////////////////////////////////////////
// ���� : ������, ��ų ����â ����
// 
// �ۼ��� : �輱��
// 2003.02.06
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTNPCSCRIPTMGR_H_
#define _HTNPCSCRIPTMGR_H_

#define HT_SCRIPT_QUE_MAXSIZE		1000	// ���ǹ� �ִ� ũ��
#define HT_SCRIPT_SEL_MAXSIZE		10		// ���ù� �ִ� ����
//------------------------------ ���� �����͸� �����ص� ����----------------------------//
// ���ǹ�
typedef struct _HT_QuestionTableLS
{
	HTbyte			byteParameter;
	HTtchar			szText[HT_SCRIPT_QUE_MAXSIZE];
} HT_QuestionTableLS;

typedef struct _HT_QuestionTable
{
	HTbyte			byteParameter;
	CHT_DATA_STR	strText;	
} HT_QuestionTable;

// ���ù�
typedef struct _HT_SelectTable
{
//	HTint		nIndex;
	CHTString	szText;
} HT_SelectTable;

// �� �ܰ��� ���ǹ��� ���ù��� ����
typedef struct _HT_ScriptTable
{
//	DWORD		dwSeq;				// ���������� �����ϴ� ��ȣ. szStep�� ���� ��� �����ϱ� ���� �뵵
	CHTString	szStep;				// �ܰ�
	HTint		iQuestionIndex;		// ���� �ܰ迡 ��µ� ����

	HTshort		sQuest;				// ����Ʈ ����
	HTshort		sCondition;			// ���� �ܰ踦 ���� �����ؾ� �� ����
	HTshort		sCondition2;
	HTshort		sClientEvent;		// ���� �ܰ踦 ���� �����ؾ��� Ŭ���̾�Ʈ �̺�Ʈ
	HTshort		sServerEvent;		// ���� �ܰ踦 ���� �����ؾ��� �������� ��û

	// ���ù��� ���������� ���ù��� �ƴ� �ٸ� �Է¿� ���� ���� �ܰ�� �Ѿ�� ����ϱ� ���� �������.
	HTint		nSelect[HT_SCRIPT_SEL_MAXSIZE];			// ���ù��� index
	CHTString	szNextSeq[HT_SCRIPT_SEL_MAXSIZE];		// �� ���ù��� ���� ���� �ܰ�
} HT_ScriptTable;

// �ó����� ����Ʈ ����
typedef struct _HT_QuestStepTable
{
	HTint		nSeq;				// ���� �ܰ��� ����Ʈ ������
	BYTE		byQuestIndex;
	HTint		nNPCIndex;
	BYTE		byServerLvl;		
	BYTE		byClientLvl;		// �ź�/����/����/�Ϸ�
	BYTE		byClientLvlTime;	// 1��/2��/3��
	HTint		nNexSeq;			// ���� �ܰ��� ����Ʈ ������
} HT_QuestStepTable;

typedef std::map<DWORD,HT_QuestionTable*>::value_type	HT_QuestionTable_Val;
typedef std::map<DWORD,HT_QuestionTable*>::iterator		HT_QuestionTable_It;
typedef std::map<DWORD,HT_SelectTable*>::value_type		HT_SelectTable_Val;
typedef std::map<DWORD,HT_SelectTable*>::iterator		HT_SelectTable_It;
typedef std::map<DWORD,HT_ScriptTable*>::value_type		HT_ScriptTable_Val;
typedef std::map<DWORD,HT_ScriptTable*>::iterator		HT_ScriptTable_It;

typedef std::map<DWORD,HT_QuestStepTable*>::value_type	HT_QuestStepTable_Val;
typedef std::map<DWORD,HT_QuestStepTable*>::iterator	HT_QuestStepTable_It;
//------------------------------------------------------------------------------------//
class CHTXMLParser;

class CHTBaseNPCScriptTable
{
public:
	CHTBaseNPCScriptTable() 
	{
		//m_strTable = _T("");
		m_nRows = 0;
	}
	virtual ~CHTBaseNPCScriptTable() {}

	virtual HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) = 0;

	virtual HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable ) = 0;
	virtual HTRESULT	HT_hrSave( CHTFile* pFile ) = 0;

	//virtual HTbool		HT_bGetStringByIndex(HTuint nIndex, HTtchar* strText) { return( HT_FALSE ); }
	virtual HTtchar*	HT_szGetStringByIndex( HTuint nIndex ) { return HT_NULL; };
	virtual HTbool		HT_bGetStringByIndex(HTuint nIndex, CHTString& strText) { return( HT_FALSE ); }

	// for question only
	virtual HTbool		HT_bGetPrameterByIndex( HTuint nIndex, HTbyte* pbyteParam ) { return( HT_FALSE ); }

	// for scripttable only
	//------- Ư�� step�� ��ȯ�Ѵ�:�������˻��ϱ����� ���� Ȱ��ȭ�� NPCType�� �ѱ�� --------//
	virtual HT_ScriptTable*		HT_bGetStep(CHTString szStep, BYTE byNPCType) { return HT_NULL; }

	// �Ϲ� ���� �ε��� ���� �˻�
	virtual 				HTbool HT_bIsCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsRelativeCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsJobCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsTribeCondition( const HTint id ) { return( HT_FALSE ); }
	virtual					HTbool HT_bIsLevelCondition( const HTint id ) { return( HT_FALSE ); }
	// ����Ʈ ���� �ε��� ���� �˻�
	virtual 				HTbool HT_bIsQuestCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsQuestProcessCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsQuestKindCondition( const HTint id ) { return( HT_FALSE ); }

	// ���� �˻�
	virtual HTbool			HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType) { return( HT_FALSE ); }
	// ����Ʈ ������� ����
	virtual HTbool			HT_bCheckCondition_QuestLevel(HTshort sQuest) { return( HT_FALSE ); }
	// ����Ʈ ��ȣ ����
	virtual HTbool			HT_bCheckCondition_QuestIndex(HTshort sCondition) { return( HT_FALSE ); }
	// ģ�е� ����
	virtual HTbool			HT_bCheckCondition_NPCRelative(HTshort sCondition) { return( HT_FALSE ); }
	// ��ų �̸� ���� 
	//virtual HTbool			HT_bCheckCondition_SkillName(HTshort sCondition, BYTE byNPCType) { return( HT_FALSE ); }
	// ��/�� ���� 
	virtual HTbool			HT_bCheckCondition_CurTime( HTshort sCondition ) { return( HT_FALSE ); }
	// ����Ʈ ����(1��/2��/3��) ���� 
	virtual HTbool			HT_bCheckCondition_LevelTime( HTshort sCondition ) { return( HT_FALSE ); }
	// ���� ��û�� ���� ��� ���� 
	virtual HTbool			HT_bCheckCondition_RequestResult( HTshort sCondition, BYTE byNPCType ) { return( HT_FALSE ); }
	// ���� ���� 
	virtual	HTbool			HT_bCheckCondition_Tribe( HTshort sCondition ) { return( HT_FALSE ); }
	// �ֽ� ���� �˻�
	virtual HTbool			HT_bCheckCondition_Trimuriti( HTshort sCondition ) { return( HT_FALSE ); }
	// ���� ������ �´��� �˻�
	virtual HTbool			HT_bCheckCondition_CharacterLevel( HTshort sCondition ) { return( HT_FALSE ); }
	// 1/2�� ���� �˻�
	virtual	HTbool			HT_bCheckCondition_JobLevelResult( HTshort sCondition ) { return( HT_FALSE ); }
	// ���� �˻�
	virtual	HTbool			HT_bCheckCondition_JobResult( HTshort sCondition ) { return( HT_FALSE ); }

	// for QuestStep only
//	virtual HTbool			HT_bGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& ClientLvlTime) { return( HT_FALSE ); }
	virtual HT_QuestStepTable*	HT_pGetQuestLevel(BYTE byServerLvl) { return HT_NULL; }
	virtual HT_QuestStepTable*	HT_pGetCurQuestLevel() { return HT_NULL; }
	virtual HT_QuestStepTable*	HT_pGetNextQuestLevel(HTint nNextSeq) { return HT_NULL; }

protected:
	//CHTString			m_strTable;	// �������� �� �̸�
	HTuint				m_nRows;	// ������ �� ��
};


class CHT_QuestionTable : public CHTBaseNPCScriptTable
{
public:
	CHT_QuestionTable() {}; 
	~CHT_QuestionTable();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );

	HTbool		HT_bGetPrameterByIndex( HTuint nIndex, HTbyte* pbyteParam );
	HTtchar*	HT_szGetStringByIndex( HTuint nIndex );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<DWORD,HT_QuestionTable*>	m_mapTable;
};

class CHT_SelectTable : public CHTBaseNPCScriptTable
{
public:
	CHT_SelectTable() {}; 
	~CHT_SelectTable();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );
	HTbool		HT_bGetStringByIndex(HTuint nIndex, CHTString& strText);

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<DWORD,HT_SelectTable*>	m_mapTable;
};

class CHT_ScriptTable : public CHTBaseNPCScriptTable
{
public:
	CHT_ScriptTable() {};
	~CHT_ScriptTable();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	//------- Ư�� step�� ��ȯ�Ѵ�:�������˻��ϱ����� ���� Ȱ��ȭ�� NPCType�� �ѱ�� --------//
	HT_ScriptTable*		HT_bGetStep(CHTString szStep, BYTE byNPCType);

	// �Ϲ� ���� �ε��� ���� �˻�
	HTbool 			HT_bIsCondition( const HTint id );
	HTbool 			HT_bIsRelativeCondition( const HTint id );
	HTbool 			HT_bIsJobCondition( const HTint id );
	HTbool 			HT_bIsTribeCondition( const HTint id );
	HTbool 			HT_bIsLevelCondition( const HTint id );

	// ����Ʈ ���� �ε��� ���� �˻�
	HTbool 			HT_bIsQuestCondition( const HTint id );
	HTbool 			HT_bIsQuestProcessCondition( const HTint id );
	HTbool 			HT_bIsQuestKindCondition( const HTint id );

	// ���� �˻�
	HTbool			HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType);
	// ����Ʈ ������� ����
	HTbool			HT_bCheckCondition_QuestLevel(HTshort sQuest);
	// ����Ʈ ��ȣ ����
	HTbool			HT_bCheckCondition_QuestIndex(HTshort sCondition);
	// ģ�е� ����
	HTbool			HT_bCheckCondition_NPCRelative(HTshort sCondition);
	// ��/�� ���� 
	HTbool			HT_bCheckCondition_CurTime(HTshort sCondition);
	// ����Ʈ ����(1��/2��/3��) ���� 
	HTbool			HT_bCheckCondition_LevelTime(HTshort sCondition);
	// ���� ��û�� ���� ��� ���� 
	HTbool			HT_bCheckCondition_RequestResult(HTshort sCondition, BYTE byNPCType);
	// ���� ���� 
	HTbool			HT_bCheckCondition_Tribe(HTshort sCondition);
	// �ֽ� ���� �˻�
	HTbool			HT_bCheckCondition_Trimuriti( HTshort sCondition );
	// ���� ������ �´��� �˻�
	HTbool			HT_bCheckCondition_CharacterLevel( HTshort sCondition );
	// 1/2�� ���� �˻�
	HTbool			HT_bCheckCondition_JobLevelResult( HTshort sCondition );
	// ���� �˻�
	HTbool			HT_bCheckCondition_JobResult( HTshort sCondition );

private:
	std::map<DWORD,HT_ScriptTable*>	m_mapTable;
};

class CHTQuestStepTable : public CHTBaseNPCScriptTable
{
public:
	CHTQuestStepTable() {}; 
	~CHTQuestStepTable();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

//	HTbool		HT_bGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& ClientLvlTime);
	HT_QuestStepTable* HT_pGetQuestLevel(HTbyte byServerLvl);
	// ���� ����Ʈ�� ������ ���´�
	HT_QuestStepTable* HT_pGetCurQuestLevel();
	// ���� ����Ʈ�� ���� ������ ���´�
	HT_QuestStepTable*	HT_pGetNextQuestLevel(HTint nNextSeq);
private:
	std::map<DWORD,HT_QuestStepTable*>	m_mapTable;
};

//-------------------------------------------------------------------------------------
// �̸� : ������ �񱳿������� ����
// ���� : STL�� map�� ù��°�� Ű���� ��Ʈ���������̱⶧���� ������ ����Ǿ��
// ����� ������ ���ĵǾ� ����, ã�� �� �ִ�. �׷��� ������ �����Ͱ�����
// �񱳸� �ϰԵǴ� ��Ȳ�� ��������. 
struct HTDerefLessStr
{
	template<typename PtrType>
		HTbool operator()( PtrType pStr1, PtrType pStr2 ) const
	{
		HTint i = stricmp( pStr1, pStr2 );
		if ( i < 0 )
			return ( HT_TRUE );
		else
			return ( HT_FALSE );
	}
};

typedef std::map<HTtchar*,CHTBaseNPCScriptTable*,HTDerefLessStr>::value_type HT_NPCScriptMgr_Value;
typedef std::map<HTtchar*,CHTBaseNPCScriptTable*,HTDerefLessStr>::iterator HT_NPCScriptMgr_It;

class HTNPCScriptMgr
{
public:
	HTNPCScriptMgr(void);
	~HTNPCScriptMgr(void);

	HTRESULT		HT_hrInit( CHTString& strFullXMLFile, CHTString strXMLFile  );
	
	HTRESULT		HT_hrInit_Mandara( CHTString& strXMLFile );
	HTRESULT		HT_hrInit_ShambalaAnu( CHTString& strXMLFile );
	HTRESULT		HT_hrInit_Jina1st( CHTString& strXMLFile );
	HTRESULT		HT_hrInit_Jina3rd( CHTString& strXMLFile );
	HTRESULT		HT_hrInit_Jina4th( CHTString& strXMLFile );
	HTRESULT		HT_hrInit_Chaturanga( CHTString& strXMLFile );

	HTvoid			HT_vCleanUp( );

	HTRESULT		HT_hrLoad( CHTString& strFile );
	HTRESULT		HT_hrSave( CHTString& strFile );
	
	HTtchar*				HT_pGetTableName( HTdword dwID );
	CHTBaseNPCScriptTable*	HT_pGetTable( HTdword dwID );

	HTint			HT_nSetActiveNPC(BYTE byNPCType);
	//-------ó�� �ܰ�� �����Ѵ�---------//
	HTint			HT_nSetFirstStep();
	//-------���� �ܰ�� ����-------------//
	HTint			HT_nNextStep(HTint nSelNum);

	//HTvoid			HT_vGetQuestion(HTtchar* szText, CHTString& szParam);
	HTvoid			HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam);

	HTvoid			HT_vGetSelectText(HTint nIndex, CHTString& szText);

	HTshort			HT_sGetClientEvent();
	HTshort			HT_sGetServerEvent();

	//CHTString		HT_szGetQuestStatus()	{ return m_pCurStep->szQuest;	}
	
	//-------- ���� ����Ʈ ������ ã�´� ----------//
	HTvoid			HT_vGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& byClientLvlTime);
	// ���� ����Ʈ�� ���� ������ ���´�
	HTvoid			HT_vGetNextQuestLevel(BYTE& byNextLvl, BYTE& byNextLvlTime);

	// ��� ����
	HTvoid			HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }

	HTint			m_iQuestion;	// ���� ���õ� ���ǹ��� Index

private:
	BYTE					m_byNPCType;	// ���� ���õ� NPC
	HT_NPCScriptMgr_It		m_ActiveNPC_It;	
	HT_ScriptTable*			m_pCurStep;
	//	HT_QuestStepTable*		m_pCurQuest;

	CHTString				m_szLanguage;
	std::map<HTtchar*,CHTBaseNPCScriptTable*,HTDerefLessStr>	m_mapTables;
};

#endif