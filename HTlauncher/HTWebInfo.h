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
// Web ���� Ŭ������ �ٷ� �⺻ �Լ� ( ���� Ŭ���� )
//============================================================================================
class CHTWebInfo
{
	public:
		CHTWebInfo();
		~CHTWebInfo();

	public:
		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize )
		// D : HTTP���� ������ ������
		// R : recvbuffer - ���� ����
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize );
	
		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetLogInEnable()
		// D : �α��� ����/�Ұ��� ���
		// R : 
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetLogInEnable(){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword)
		// D : ID�� PASSWORD�� �α����� �������� ������ ����
		// I : strID-���̵�, strPassword-�н�����
		// R : 0-����, 1-ID ERROR, 2-PASSWORD ERROR, 3-���� ���̵�, 4-�˼����� ����
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword, HTint iServerType){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerStatusCheck()
		// D : ������ �α����� �� �� �ִ� ����������, ���峻�� ������ ���������ڼ��� ����
		// I : pcWebRecv-������ �о�� �ؽ�Ʈ
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerStatusCheck(){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetWorldNum();
		// D : ������ ���� ���, ����� ���� ���� 20���� �����ִ�!!!
		// R : ������ ����
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetWorldNum(){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
		// D : ���������ڼ� ���
		// I : iWorldNo - �����ȣ, iZoneNo - ����ȣ
		// R : ���������ڼ�
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerDownCause(HTchar* pcCause)
		// D : ������ �ٿ�Ǿ� �ִ� ���� ���
		// I : 
		// R : pcCause - ����
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerDownCause(HTchar* pcCause){ return HT_FALSE; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetAliveZoneNum(HTint iWorldNum)
		// D : ���忡�� ����ִ� �� ���� ���
		// R : ���忡�� ����ִ� �� ����
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetAliveZoneNum(HTint iWorldNum){ return -1; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCall(CHTString sID, CHTString sName, CHTString sContents)
		// D : ���������� ������Ų��.
		// I : sID - ���̵�, sName - ĳ���� �̸�, pcContents - ��������
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCall(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName, CHTString sContents){ return 0; };
		HTint	HT_iGMCallCheck(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCallCancel(CHTString sID, CHTString sName)
		// D : ������Ų �������� ���
		// I : sID - ���̵�, sName - ĳ���� �̸�, 
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCallCancel(HTint iWorldNo, CHTString sID, CHTString sName){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : �����޼��� �� ���
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCallCount(){ return 0; };

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType)
		// D : URL����
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
// Web LogIn���� ���� 
//============================================================================================
#define _ZONENUM_PER_WORLD		20

// ���̵�� �н������ �α����� �Ұ����� ����
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

#define _LOGIN_DISABLE_CAUSE_TESTSERVER				12	// �̰����� �׽�Ʈ ������ ������ �Ұ����մϴ�.
#define _LOGIN_DISABLE_CAUSE_AGELIMIT				13	// źƮ��� ��12�� �̻� ������ �̿��ϽǼ� �ֽ��ϴ�.

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
		// D : �α��� ����/�Ұ��� ���
		// R : 
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetLogInEnable();

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword)
		// D : ID�� PASSWORD�� �α����� �������� ������ ����
		// I : strID-���̵�, strPassword-�н�����
		// R : 0-����, 1-ID ERROR, 2-PASSWORD ERROR, 3-���� ���̵�, 4-�˼����� ����
		//-----------------------------------------------------------------------------------
		HTint		HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword, HTint iServerType);
		CHTString	HT_strAttendanceCheck(CHTString strID, CHTString strPassword, HTint iType);

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerStatusCheck()
		// D : ������ �α����� �� �� �ִ� ����������, ���峻�� ������ ���������ڼ��� ����
		// I : pcWebRecv-������ �о�� �ؽ�Ʈ
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerStatusCheck();

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetWorldNum();
		// D : ������ ���� ���, ����� ���� ���� 20���� �����ִ�!!!
		// R : ������ ����
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetWorldNum();

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetWorldNum(HTint iWorldNum)
		// D : ������ ���� �����Ѵ�. ����� ������ ��带 �����ϱ� ���� ���ȴ�.
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetWorldNum(HTint iWorldNum);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
		// D : ���������ڼ� ���
		// I : iWorldNo - �����ȣ, iZoneNo - ����ȣ
		// R : ���������ڼ�
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo);
		HTint	HT_iGetCCUserNum(HTint iWorldNo);

		//-----------------------------------------------------------------------------------
		// HTbool	HT_bGetServerDownCause(HTchar* pcCause)
		// D : ������ �ٿ�Ǿ� �ִ� ���� ���
		// I : 
		// R : pcCause - ����
		//-----------------------------------------------------------------------------------
		HTbool	HT_bGetServerDownCause(HTchar* pcCause);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetAliveZoneNum(HTint iWorldNo)
		// D : ���忡�� ����ִ� �� ���� ���
		// R : ���忡�� ����ִ� �� ����
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetAliveZoneNum(HTint iWorldNo);

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetZoneCCUserInit()
		// D : ���� ���������ڼ��� -1�� �����.
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetZoneCCUserInit();

	private:
		HTbool			m_bLogInEnable;
		DWORD			m_dwLogInDiableCause;
		HTbool			m_bServerOn;

		// ���� ���� ����
		HTint			m_iWorldNum;
		_HT_WORLDINFO*	m_poWorldInfo;

		// ������ ���������ڼ�
		HTint*			m_piCCUserNum;
		// ������ �ٿ�Ǿ� �ִ� ����
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
		// D : ���������� ������Ų��.
		// I : sID - ���̵�, sName - ĳ���� �̸�, pcContents - ��������
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCall(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName, CHTString sContents);
		HTint	HT_iGMCallCheck(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGMCallCancel(CHTString sID, CHTString sName)
		// D : ������Ų �������� ���
		// I : sID - ���̵�, sName - ĳ���� �̸�, 
		//-----------------------------------------------------------------------------------
		HTint	HT_iGMCallCancel(HTint iWorldNo, CHTString sID, CHTString sName);

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : �����޼��� �� ���
		//-----------------------------------------------------------------------------------
		HTint	HT_iGetCallCount(){ return m_iCallCount; };

		//-----------------------------------------------------------------------------------
		// HTint	HT_iGetCallCount()
		// D : GMȮ�δ亯 ���� ���
		//-----------------------------------------------------------------------------------
		HTchar*	HT_szGetCallReply(){ return m_strMsg; };

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSaveGMChat()
		// D : GMä�� ����
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSaveGMChat(CHTString strCharName, CHTString str, HT_COLOR clr);

		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vSetGMLogPath(HTchar* pcPath)
		// D : GM�α� ��� ����
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vSetGMLogPath(HTchar* pcPath);

	private:
		//-----------------------------------------------------------------------------------
		// HTvoid	HT_vReArrangeCallMsg(CHTString strMsg)
		// D : ��
		//-----------------------------------------------------------------------------------
		HTvoid	HT_vReArrangeCallMsg(CHTString strMsg);

	private:
		HTint		m_iCallAcept;
		HTint		m_iCallCount;
		CHTString	m_strMsg;
		HTchar		m_cGMLogPath[HT_MAX_STR];
};
#endif