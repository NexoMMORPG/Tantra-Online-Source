//////////////////////////////////////////////////////////////////////////////////////////
// 설명 : 아이템, 스킬 정보창 관련
// 
// 작성자 : 김선미
// 2003.02.06
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTNPCSCRIPTMGR_H_
#define _HTNPCSCRIPTMGR_H_

#define HT_SCRIPT_QUE_MAXSIZE		1000	// 질의문 최대 크기
#define HT_SCRIPT_SEL_MAXSIZE		10		// 선택문 최대 개수
//------------------------------ 읽은 데이터를 저장해둘 형식----------------------------//
// 질의문
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

// 선택문
typedef struct _HT_SelectTable
{
//	HTint		nIndex;
	CHTString	szText;
} HT_SelectTable;

// 각 단계의 질의문과 선택문의 조합
typedef struct _HT_ScriptTable
{
//	DWORD		dwSeq;				// 순차적으로 증가하는 번호. szStep가 같은 경우 구별하기 위한 용도
	CHTString	szStep;				// 단계
	HTint		iQuestionIndex;		// 현재 단계에 출력될 윗말

	HTshort		sQuest;				// 퀘스트 상태
	HTshort		sCondition;			// 현재 단계를 위해 만족해야 할 조건
	HTshort		sCondition2;
	HTshort		sClientEvent;		// 현재 단계를 위해 실행해야할 클라이언트 이벤트
	HTshort		sServerEvent;		// 현재 단계를 위해 실행해야할 서버로의 요청

	// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈때 사용하기 위해 만들었다.
	HTint		nSelect[HT_SCRIPT_SEL_MAXSIZE];			// 선택문의 index
	CHTString	szNextSeq[HT_SCRIPT_SEL_MAXSIZE];		// 각 선택문의 다음 실행 단계
} HT_ScriptTable;

// 시나리오 퀘스트 스탭
typedef struct _HT_QuestStepTable
{
	HTint		nSeq;				// 현재 단계의 퀘스트 시퀀스
	BYTE		byQuestIndex;
	HTint		nNPCIndex;
	BYTE		byServerLvl;		
	BYTE		byClientLvl;		// 거부/시작/진행/완료
	BYTE		byClientLvlTime;	// 1차/2차/3차
	HTint		nNexSeq;			// 다음 단계의 퀘스트 시퀀스
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
	//------- 특정 step을 반환한다:조건을검사하기위해 현재 활성화된 NPCType을 넘긴다 --------//
	virtual HT_ScriptTable*		HT_bGetStep(CHTString szStep, BYTE byNPCType) { return HT_NULL; }

	// 일반 조건 인덱스 영역 검사
	virtual 				HTbool HT_bIsCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsRelativeCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsJobCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsTribeCondition( const HTint id ) { return( HT_FALSE ); }
	virtual					HTbool HT_bIsLevelCondition( const HTint id ) { return( HT_FALSE ); }
	// 퀘스트 조건 인덱스 영역 검사
	virtual 				HTbool HT_bIsQuestCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsQuestProcessCondition( const HTint id ) { return( HT_FALSE ); }
	virtual 				HTbool HT_bIsQuestKindCondition( const HTint id ) { return( HT_FALSE ); }

	// 조건 검사
	virtual HTbool			HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType) { return( HT_FALSE ); }
	// 퀘스트 진행상태 조건
	virtual HTbool			HT_bCheckCondition_QuestLevel(HTshort sQuest) { return( HT_FALSE ); }
	// 퀘스트 번호 조건
	virtual HTbool			HT_bCheckCondition_QuestIndex(HTshort sCondition) { return( HT_FALSE ); }
	// 친밀도 조건
	virtual HTbool			HT_bCheckCondition_NPCRelative(HTshort sCondition) { return( HT_FALSE ); }
	// 스킬 이름 조건 
	//virtual HTbool			HT_bCheckCondition_SkillName(HTshort sCondition, BYTE byNPCType) { return( HT_FALSE ); }
	// 낮/밤 조건 
	virtual HTbool			HT_bCheckCondition_CurTime( HTshort sCondition ) { return( HT_FALSE ); }
	// 퀘스트 차수(1차/2차/3차) 조건 
	virtual HTbool			HT_bCheckCondition_LevelTime( HTshort sCondition ) { return( HT_FALSE ); }
	// 서버 요청에 대한 결과 조건 
	virtual HTbool			HT_bCheckCondition_RequestResult( HTshort sCondition, BYTE byNPCType ) { return( HT_FALSE ); }
	// 종족 조건 
	virtual	HTbool			HT_bCheckCondition_Tribe( HTshort sCondition ) { return( HT_FALSE ); }
	// 주신 조건 검사
	virtual HTbool			HT_bCheckCondition_Trimuriti( HTshort sCondition ) { return( HT_FALSE ); }
	// 레벨 조건이 맞는지 검사
	virtual HTbool			HT_bCheckCondition_CharacterLevel( HTshort sCondition ) { return( HT_FALSE ); }
	// 1/2차 전직 검사
	virtual	HTbool			HT_bCheckCondition_JobLevelResult( HTshort sCondition ) { return( HT_FALSE ); }
	// 직업 검사
	virtual	HTbool			HT_bCheckCondition_JobResult( HTshort sCondition ) { return( HT_FALSE ); }

	// for QuestStep only
//	virtual HTbool			HT_bGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& ClientLvlTime) { return( HT_FALSE ); }
	virtual HT_QuestStepTable*	HT_pGetQuestLevel(BYTE byServerLvl) { return HT_NULL; }
	virtual HT_QuestStepTable*	HT_pGetCurQuestLevel() { return HT_NULL; }
	virtual HT_QuestStepTable*	HT_pGetNextQuestLevel(HTint nNextSeq) { return HT_NULL; }

protected:
	//CHTString			m_strTable;	// 문서안의 탭 이름
	HTuint				m_nRows;	// 데이터 줄 수
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

	//------- 특정 step을 반환한다:조건을검사하기위해 현재 활성화된 NPCType을 넘긴다 --------//
	HT_ScriptTable*		HT_bGetStep(CHTString szStep, BYTE byNPCType);

	// 일반 조건 인덱스 영역 검사
	HTbool 			HT_bIsCondition( const HTint id );
	HTbool 			HT_bIsRelativeCondition( const HTint id );
	HTbool 			HT_bIsJobCondition( const HTint id );
	HTbool 			HT_bIsTribeCondition( const HTint id );
	HTbool 			HT_bIsLevelCondition( const HTint id );

	// 퀘스트 조건 인덱스 영역 검사
	HTbool 			HT_bIsQuestCondition( const HTint id );
	HTbool 			HT_bIsQuestProcessCondition( const HTint id );
	HTbool 			HT_bIsQuestKindCondition( const HTint id );

	// 조건 검사
	HTbool			HT_bCheckCondition(HTshort sQuest, HTshort sCondition, HTshort sCondition2, HTbyte byNPCType);
	// 퀘스트 진행상태 조건
	HTbool			HT_bCheckCondition_QuestLevel(HTshort sQuest);
	// 퀘스트 번호 조건
	HTbool			HT_bCheckCondition_QuestIndex(HTshort sCondition);
	// 친밀도 조건
	HTbool			HT_bCheckCondition_NPCRelative(HTshort sCondition);
	// 낮/밤 조건 
	HTbool			HT_bCheckCondition_CurTime(HTshort sCondition);
	// 퀘스트 차수(1차/2차/3차) 조건 
	HTbool			HT_bCheckCondition_LevelTime(HTshort sCondition);
	// 서버 요청에 대한 결과 조건 
	HTbool			HT_bCheckCondition_RequestResult(HTshort sCondition, BYTE byNPCType);
	// 종족 조건 
	HTbool			HT_bCheckCondition_Tribe(HTshort sCondition);
	// 주신 조건 검사
	HTbool			HT_bCheckCondition_Trimuriti( HTshort sCondition );
	// 레벨 조건이 맞는지 검사
	HTbool			HT_bCheckCondition_CharacterLevel( HTshort sCondition );
	// 1/2차 전직 검사
	HTbool			HT_bCheckCondition_JobLevelResult( HTshort sCondition );
	// 직업 검사
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
	// 현재 퀘스트의 레벨을 얻어온다
	HT_QuestStepTable* HT_pGetCurQuestLevel();
	// 현재 퀘스트의 다음 레벨을 얻어온다
	HT_QuestStepTable*	HT_pGetNextQuestLevel(HTint nNextSeq);
private:
	std::map<DWORD,HT_QuestStepTable*>	m_mapTable;
};

//-------------------------------------------------------------------------------------
// 이름 : 역참조 비교연산자형 선언
// 설명 : STL의 map에 첫번째인 키값이 스트링포인터이기때문에 비교형이 선언되어야
// 제대로 값들이 정렬되어 들어가고, 찾을 수 있다. 그렇지 않으면 포인터값으로
// 비교를 하게되는 상황이 벌어진다. 
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
	//-------처음 단계로 셋팅한다---------//
	HTint			HT_nSetFirstStep();
	//-------다음 단계로 간다-------------//
	HTint			HT_nNextStep(HTint nSelNum);

	//HTvoid			HT_vGetQuestion(HTtchar* szText, CHTString& szParam);
	HTvoid			HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam);

	HTvoid			HT_vGetSelectText(HTint nIndex, CHTString& szText);

	HTshort			HT_sGetClientEvent();
	HTshort			HT_sGetServerEvent();

	//CHTString		HT_szGetQuestStatus()	{ return m_pCurStep->szQuest;	}
	
	//-------- 현재 퀘스트 레벨을 찾는다 ----------//
	HTvoid			HT_vGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& byClientLvlTime);
	// 현재 퀘스트의 다음 레벨을 얻어온다
	HTvoid			HT_vGetNextQuestLevel(BYTE& byNextLvl, BYTE& byNextLvlTime);

	// 언어 설정
	HTvoid			HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }

	HTint			m_iQuestion;	// 현재 선택된 질의문의 Index

private:
	BYTE					m_byNPCType;	// 현재 선택된 NPC
	HT_NPCScriptMgr_It		m_ActiveNPC_It;	
	HT_ScriptTable*			m_pCurStep;
	//	HT_QuestStepTable*		m_pCurQuest;

	CHTString				m_szLanguage;
	std::map<HTtchar*,CHTBaseNPCScriptTable*,HTDerefLessStr>	m_mapTables;
};

#endif