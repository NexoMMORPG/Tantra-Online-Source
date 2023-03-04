#ifndef _HTWEBINFO_H
#define _HTWEBINFO_H
enum
{
	LOGIN_ENABLE,
	IDPASSWORD_TESTSEV,
	IDPASSWORD_MAINSEV,
	GM_CALL,
	GM_CALL_CANCEL,
	GM_CALL_CHECK,
};
//============================================================================================
// Web 관련 클래스가 다룰 기본 함수 ( 상위 클래스 )
//============================================================================================
class CHTWebInfo
{
	public:
		CHTWebInfo();
		~CHTWebInfo();

	public:
		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize )
		// D : HTTP에서 정보를 얻어오기
		// R : recvbuffer - 정보 내용
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize );
	
		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetLogInEnable()
		// D : 로그인 가능/불가능 얻기
		// R : 
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetLogInEnable(){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword)
		// D : ID와 PASSWORD로 로그인이 가능한지 웹에서 인증
		// I : strID-아이디, strPassword-패스워드
		// R : 0-가능, 1-ID ERROR, 2-PASSWORD ERROR, 3-블럭된 아이디, 4-알수없는 이유
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword, HTint iServerType){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerStatusCheck()
		// D : 서버가 로그인을 할 수 있는 상태인지와, 월드내의 존들의 동시접속자수를 설정
		// I : pcWebRecv-웹에서 읽어온 텍스트
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerStatusCheck(){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetWorldNum();
		// D : 월드의 갯수 얻기, 월드당 존의 수는 20개로 정해있다!!!
		// R : 월드의 갯수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetWorldNum(){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
		// D : 동시접속자수 얻기
		// I : iWorldNo - 월드번호, iZoneNo - 존번호
		// R : 동시접속자수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerDownCause(HTchar* pcCause)
		// D : 서버가 다운되어 있는 이유 얻기
		// I : 
		// R : pcCause - 이유
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerDownCause(HTchar* pcCause){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetAliveZoneNum(HTint iWorldNum)
		// D : 월드에서 살아있는 존 갯수 얻기
		// R : 월드에서 살아있는 존 갯수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetAliveZoneNum(HTint iWorldNum){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCall(CHTString sID, CHTString sName, CHTString sContents)
		// D : 진정내용을 접수시킨다.
		// I : sID - 아이디, sName - 캐릭터 이름, pcContents - 진정내용
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCall(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName, CHTString sContents){ return 0; };
		HTint	HT_iGMCallCheck(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCallCancel(CHTString sID, CHTString sName)
		// D : 접수시킨 진정내용 취소
		// I : sID - 아이디, sName - 캐릭터 이름, 
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCallCancel(HTint iWorldNo, CHTString sID, CHTString sName){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : 접수메세지 수 얻기
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCallCount(){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType)
		// D : URL설정
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType);

	protected:
		HTchar		m_cLogInEnableURL[HT_MAX_STR];
		HTchar		m_cCheckIDPASSWORD_TEST[HT_MAX_STR];
		HTchar		m_cCheckIDPASSWORD_MAIN[HT_MAX_STR];
		HTchar		m_cGMCallURL[HT_MAX_STR];
		HTchar		m_cGMCallCheckURL[HT_MAX_STR];
		HTchar		m_cGMCallCancelURL[HT_MAX_STR];
};

//============================================================================================
// Web LogIn인증 관련 
//============================================================================================
#define _ZONENUM_PER_WORLD		20

// 아이디와 패스워드로 로그인이 불가능한 이유
#define _LOGIN_ENABLE								0
#define _LOGIN_DISABLE_CAUSE_PASSWORDERROR			1
#define _LOGIN_DISABLE_CAUSE_IDERROR				2
#define _LOGIN_DISABLE_CAUSE_BLOCKUSER				3
#define _LOGIN_DISABLE_CAUSE_SERVERDOWN				4

#define _LOGIN_DISABLE_CAUSE_HOMEPAGE_WITHDRAW		5
#define _LOGIN_DISABLE_CAUSE_NEED_EXTRAINFO			6
#define _LOGIN_DISABLE_CAUSE_NEED_PARENTAGREE		7

#define _LOGIN_DISABLE_CAUSE_UNKNOWN				8

#define _LOGIN_DISABLE_CAUSE_NOTBILL				9
#define _LOGIN_DISABLE_CAUSE_NEEDBILL				10
#define _LOGIN_DISABLE_CAUSE_OPENWAIT				11

#define _LOGIN_DISABLE_CAUSE_TESTSERVER				12	// 이계정은 테스트 서버에 접속이 불가능합니다.
#define _LOGIN_DISABLE_CAUSE_AGELIMIT				13	// 탄트라는 만12세 이상만 게임을 이용하실수 있습니다.

typedef struct _HT_ZONEINFO
{
	HTint	iWorldNo;
	HTint	iZoneNo;
	HTint	iCCUserNum;
} _HT_ZONEINFO;

typedef struct _HT_WORLDINFO
{
	HTint			iZoneNum;
	_HT_ZONEINFO	oZoneInfo[MAX_SERVER];
} _HT_WORLDINFO;

class CHTWebLogIn : public CHTWebInfo
{
	public:
		CHTWebLogIn();
		~CHTWebLogIn();

	public:
		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetLogInEnable()
		// D : 로그인 가능/불가능 얻기
		// R : 
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetLogInEnable();

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword)
		// D : ID와 PASSWORD로 로그인이 가능한지 웹에서 인증
		// I : strID-아이디, strPassword-패스워드
		// R : 0-가능, 1-ID ERROR, 2-PASSWORD ERROR, 3-블럭된 아이디, 4-알수없는 이유
		//-----------------------------------------------------------------------------------
		HTint		HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword, HTint iServerType);
		CHTString	HT_strAttendanceCheck(CHTString strID, CHTString strPassword, HTint iType);

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerStatusCheck()
		// D : 서버가 로그인을 할 수 있는 상태인지와, 월드내의 존들의 동시접속자수를 설정
		// I : pcWebRecv-웹에서 읽어온 텍스트
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerStatusCheck();

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetWorldNum();
		// D : 월드의 갯수 얻기, 월드당 존의 수는 20개로 정해있다!!!
		// R : 월드의 갯수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetWorldNum();

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetWorldNum(HTint iWorldNum)
		// D : 월드의 수를 설정한다. 현재는 개발자 모드를 지원하기 위해 사용된다.
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetWorldNum(HTint iWorldNum);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
		// D : 동시접속자수 얻기
		// I : iWorldNo - 월드번호, iZoneNo - 존번호
		// R : 동시접속자수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo);
		HTint	HT_iGetCCUserNum(HTint iWorldNo);

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerDownCause(HTchar* pcCause)
		// D : 서버가 다운되어 있는 이유 얻기
		// I : 
		// R : pcCause - 이유
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerDownCause(HTchar* pcCause);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetAliveZoneNum(HTint iWorldNo)
		// D : 월드에서 살아있는 존 갯수 얻기
		// R : 월드에서 살아있는 존 갯수
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetAliveZoneNum(HTint iWorldNo);

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetZoneCCUserInit()
		// D : 존의 동시접속자수를 -1로 만든다.
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetZoneCCUserInit();

	private:
		HTbool			m_bLogInEnable;
		DWORD			m_dwLogInDiableCause;
		HTbool			m_bServerOn;

		// 월드 관련 정보
		HTint			m_iWorldNum;
		_HT_WORLDINFO*	m_poWorldInfo;

		// 월드의 동시접속자수
		HTint*			m_piCCUserNum;
		// 서버가 다운되어 있는 이유
		HTchar			m_cServerDownCause[1024];
};

class CHTGMCall : public CHTWebInfo
{
	public:
		CHTGMCall();
		~CHTGMCall();

	public:
		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCall(CHTString sID, CHTString sName, HTchar* pcContents)
		// D : 진정내용을 접수시킨다.
		// I : sID - 아이디, sName - 캐릭터 이름, pcContents - 진정내용
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCall(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName, CHTString sContents);
		HTint	HT_iGMCallCheck(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCallCancel(CHTString sID, CHTString sName)
		// D : 접수시킨 진정내용 취소
		// I : sID - 아이디, sName - 캐릭터 이름, 
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCallCancel(HTint iWorldNo, CHTString sID, CHTString sName);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : 접수메세지 수 얻기
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCallCount(){ return m_iCallCount; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : GM확인답변 내용 얻기
		//-----------------------------------------------------------------------------------
		HTchar*	HT_szGetCallReply(){ return m_strMsg; };

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSaveGMChat()
		// D : GM채팅 저장
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSaveGMChat(CHTString strCharName, CHTString str, HT_COLOR clr);

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetGMLogPath(HTchar* pcPath)
		// D : GM로그 경로 설정
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetGMLogPath(HTchar* pcPath);

	private:
		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vReArrangeCallMsg(CHTString strMsg)
		// D : 메
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vReArrangeCallMsg(CHTString strMsg);

	private:
		HTint		m_iCallAcept;
		HTint		m_iCallCount;
		CHTString	m_strMsg;
		HTchar		m_cGMLogPath[HT_MAX_STR];
};
#endif