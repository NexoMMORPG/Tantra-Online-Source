#include "stdafx.h"
#include "HTextern.h"
#include "HTWebInfo.h"
#include <wininet.h>
#include <time.h>

#define _SERVERTYPE_TEST									0
#define _SERVERTYPE_MAIN									1
#define _ZONE_NUM											20

//#define _GM_COPYPATH	_T("//Navy//GmLog//Data//")
//#define _GM_COPYPATH	_T("//salsaly//��ü����//GM_CHAT//Data//")

struct _GM_MSG
{	
	BYTE		clrR;
	BYTE		clrG;
	BYTE		clrB;
	HTchar		strMsg[256];
};

CHTWebInfo::CHTWebInfo()
{
	ZeroMemory(&m_cLogInEnableURL, sizeof(HTchar)*HT_MAX_STR);
	ZeroMemory(&m_cCheckIDPASSWORD_TEST, sizeof(HTchar)*HT_MAX_STR);
	ZeroMemory(&m_cCheckIDPASSWORD_MAIN, sizeof(HTchar)*HT_MAX_STR);
	ZeroMemory(&m_cGMCallURL, sizeof(HTchar)*HT_MAX_STR);
	ZeroMemory(&m_cGMCallCheckURL, sizeof(HTchar)*HT_MAX_STR);
	ZeroMemory(&m_cGMCallCancelURL, sizeof(HTchar)*HT_MAX_STR);
}

CHTWebInfo::~CHTWebInfo()
{
}

//===================================================================================
// CHTWebInfo
//===================================================================================
//-----------------------------------------------------------------------------------
// HTbool	HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize )
// D : HTTP���� ������ ������
// R : recvbuffer - ���� ����
//-----------------------------------------------------------------------------------
HTbool
CHTWebInfo::HT_bGetHttpRequest( LPSTR url, LPSTR recvbuffer,HTint iBuffersize )
{
	HTdword dwBytesRead;
	HINTERNET hSession = InternetOpen("MS",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL,0) ;
	if (!hSession) return HT_FALSE;

	HINTERNET hHttpFile	= InternetOpenUrl(hSession, (const char *) url, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE , 0);
	if ( !hHttpFile ) return HT_FALSE;
	
	InternetReadFile( hHttpFile, recvbuffer, iBuffersize, &dwBytesRead );

	InternetCloseHandle( hHttpFile );
	InternetCloseHandle( hSession );		// ���ǵ� ������� �Ѵ�. 2004. 7. 27. ���׼��� ������
	
	return HT_TRUE;
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vSetURL(HTchar* pcURL, HTint iURLType)
// D : URL����
//-----------------------------------------------------------------------------------
HTvoid
CHTWebInfo::HT_vSetURL(HTchar* pcURL, HTint iURLType)
{
	switch(iURLType)
	{
		case LOGIN_ENABLE:
			//sprintf(m_cLogInEnableURL, pcURL);				break;
			CopyMemory(m_cLogInEnableURL, pcURL, sizeof(HTchar)*HT_MAX_STR);		break;
		case IDPASSWORD_TESTSEV:
			//sprintf(m_cCheckIDPASSWORD_TEST, pcURL);		break;
			CopyMemory(m_cCheckIDPASSWORD_TEST, pcURL, sizeof(HTchar)*HT_MAX_STR);	break;
		case IDPASSWORD_MAINSEV:
			CopyMemory(m_cCheckIDPASSWORD_MAIN, pcURL, sizeof(HTchar)*HT_MAX_STR);	break;
		case GM_CALL:
			CopyMemory(m_cGMCallURL, pcURL, sizeof(HTchar)*HT_MAX_STR);				break;
			//sprintf(m_cGMCallURL, pcURL);					break;
		case GM_CALL_CANCEL:
			CopyMemory(m_cGMCallCancelURL, pcURL, sizeof(HTchar)*HT_MAX_STR);		break;
			//sprintf(m_cGMCallCancelURL, pcURL);				break;
		case GM_CALL_CHECK:
			CopyMemory(m_cGMCallCheckURL, pcURL, sizeof(HTchar)*HT_MAX_STR);		break;
	}
}


//===================================================================================
// CHTWebLogIn
//===================================================================================
CHTWebLogIn::CHTWebLogIn()
{
	m_dwLogInDiableCause = 0;
	m_bLogInEnable		= HT_FALSE;
	m_bServerOn			= HT_FALSE;
	
	m_iWorldNum			= 0;								// ���� ����
	m_poWorldInfo		= HT_NULL;							// ���� ����
	
	m_piCCUserNum		= HT_NULL;							// ������ ���������ڼ�
	ZeroMemory(m_cServerDownCause, sizeof(HTchar)*1024);	// ������ �ٿ�Ǿ� �ִ� ����
}

CHTWebLogIn::~CHTWebLogIn()
{
	HT_DELETEARRAY(m_piCCUserNum);
	HT_DELETEARRAY(m_poWorldInfo);
}

//-----------------------------------------------------------------------------------
// HTbool	HT_bGetLogInEnable()
// D : �α��� ����/�Ұ��� ���
// R : 
//-----------------------------------------------------------------------------------
HTbool
CHTWebLogIn::HT_bGetLogInEnable()
{
	return m_bLogInEnable;
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword)
// D : ID�� PASSWORD�� �α����� �������� ������ ����
// I : strID-���̵�, strPassword-�н�����
// R : 0-����, 1-ID ERROR, 2-PASSWORD ERROR
//-----------------------------------------------------------------------------------
HTint
CHTWebLogIn::HT_iGetLogInIDCheck(CHTString strID, CHTString strPassword, HTint iServerType)
{
	HTchar cURL[_MAX_PATH];
	//HTchar cLogInURL[_MAX_PATH];
	HTchar cID[_MAX_FNAME];
	HTchar cPassword[_MAX_FNAME];
	HTchar pcRecv[10]; 

	ZeroMemory(pcRecv, sizeof(HTchar)*10);

	sprintf(cID, strID);
	sprintf(cPassword, strPassword);

	if (iServerType==_SERVERTYPE_MAIN)
	{
		sprintf(cURL, m_cCheckIDPASSWORD_MAIN, cID, cPassword);
	}
	else if (iServerType==_SERVERTYPE_TEST)
	{
		sprintf(cURL, m_cCheckIDPASSWORD_TEST, cID, cPassword);
	}
	else{}
	//sprintf(_LOGIN_IDPASS_CHECK_URL, strID, strPassword);
	HTbool bHttpAlive = CHTWebInfo::HT_bGetHttpRequest(cURL, pcRecv, 10);

	if (!bHttpAlive)
	{
		return -1;	// HTTP�� �������� ���ϴ� ����
	}

	// atoi�� �ߴ� �� �˼� ���� ������ ���� ����
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//DWORD dwEvent;
		int iReciveNumber[10];
		for( HTint i=0 ; i<10 ; i++ )
			iReciveNumber[i] = 0;

		//	�����϶�
		if( pcRecv[0] == '0' )
		{
			if( pcRecv[5] == '1' )			m_dwLogInDiableCause = 1;
			else if( pcRecv[5] == '2' )		m_dwLogInDiableCause = 2;
			else if( pcRecv[5] == '3' )		m_dwLogInDiableCause = 3;
			else if( pcRecv[5] == '4' )		m_dwLogInDiableCause = 4;
			else if( pcRecv[5] == '5' )		m_dwLogInDiableCause = 5;
			else if( pcRecv[5] == '6' )		m_dwLogInDiableCause = 6;
			else if( pcRecv[5] == '7' )		m_dwLogInDiableCause = 7;
			else if( pcRecv[5] == '8' )		m_dwLogInDiableCause = 8;
			else if( pcRecv[5] == '9' )		m_dwLogInDiableCause = 9;
			m_dwLogInDiableCause += 1000;
			m_bLogInEnable = HT_FALSE;
			return (HTint)m_dwLogInDiableCause;
		}
		//	�����϶�
		else
		{
			for( HTint i=2 ; i<10 ; i++ )
			{
				if( pcRecv[i] == '0' )		iReciveNumber[i] = 0;
				else						iReciveNumber[i] = 1;
			}

			m_dwLogInDiableCause = (iReciveNumber[2]*128)+(iReciveNumber[3]*64)+(iReciveNumber[4]*32)+(iReciveNumber[5]*16)+
									(iReciveNumber[6]*8)+(iReciveNumber[7]*4)+(iReciveNumber[8]*2)+(iReciveNumber[9]*1);
			m_bLogInEnable = HT_TRUE;
			return (HTint)m_dwLogInDiableCause;
		}
	}
	else
	{
		//	Success
		if( !strcmp(pcRecv, "0") )
		{
			m_dwLogInDiableCause = 0;
			m_bLogInEnable = HT_TRUE;
		}
		//	Success For Japan
		else if( !strcmp(pcRecv, "100") )
		{
			m_dwLogInDiableCause = 100;
			m_bLogInEnable = HT_TRUE;
		}
		//	Password Error
		else if( !strcmp(pcRecv, "1") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_PASSWORDERROR;
			m_bLogInEnable = HT_FALSE;
		}
		//	ID Error
		else if( !strcmp(pcRecv, "2") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_IDERROR;
			m_bLogInEnable = HT_FALSE;
		}
		//	ID Error
		else if( !strcmp(pcRecv, "107") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_IDERROR;
			m_bLogInEnable = HT_FALSE;
		}
		//	ID Block User
		else if(!strcmp(pcRecv, "3") )
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_BLOCKUSER;
			m_bLogInEnable = HT_FALSE;
		}
		//	ID Block User
		else if( !strcmp(pcRecv, "102") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_BLOCKUSER;
			m_bLogInEnable = HT_FALSE;
		}
		//	Server Down
		else if(!strcmp(pcRecv, "4") )
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_SERVERDOWN;
			m_bLogInEnable = HT_FALSE;
		}
		//	Delete ID
		else if(!strcmp(pcRecv, "5") )
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_HOMEPAGE_WITHDRAW;
			m_bLogInEnable = HT_FALSE;
		}
		//	Delete ID Company
		else if( !strcmp(pcRecv, "103") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_HOMEPAGE_WITHDRAW;
			m_bLogInEnable = HT_FALSE;
		}
		//	Delete ID Game
		else if( !strcmp(pcRecv, "104") )
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_HOMEPAGE_WITHDRAW;
			m_bLogInEnable = HT_FALSE;
		}
		//	Input HomePage Extra Infomation
		else if (!strcmp(pcRecv, "6"))
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_NEED_EXTRAINFO;
			m_bLogInEnable = HT_FALSE;
		}
		//	Not Teenage
		else if (!strcmp(pcRecv, "7"))
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_NEED_PARENTAGREE;
			m_bLogInEnable = HT_FALSE;
		}
		// Test Server Connect Failed.
		else if (!strcmp(pcRecv, "8"))
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_TESTSERVER;
			m_bLogInEnable = HT_FALSE;
		}
		else if (!strcmp(pcRecv, "9"))	// 12�� �̸��� ������ �� �� �����ϴ�.
		{
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_AGELIMIT;
			m_bLogInEnable = HT_FALSE;
		}
		//	Not Bill
		else if (!strcmp(pcRecv, "101"))
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_NOTBILL;
			m_bLogInEnable = HT_FALSE;
		}
		else if (!strcmp(pcRecv, "105"))
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_NEEDBILL;
			m_bLogInEnable = HT_FALSE;
		}
		else if (!strcmp(pcRecv, "106"))
		{	
			m_dwLogInDiableCause = _LOGIN_DISABLE_CAUSE_OPENWAIT;
			m_bLogInEnable = HT_FALSE;
		}
		else
		{
			m_bLogInEnable = HT_FALSE;
			m_dwLogInDiableCause = 8;
		}
		return (HTint)m_dwLogInDiableCause;
	}
	return 0;
}

CHTString
CHTWebLogIn::HT_strAttendanceCheck(CHTString strID, CHTString strPassword, HTint iType)
{
	HTchar cURL[_MAX_PATH];
	HTchar cID[_MAX_FNAME];
	HTchar cPassword[_MAX_FNAME];
	HTchar pcRecv[28]; 
	ZeroMemory(pcRecv, sizeof(HTchar)*28);

	sprintf(cID, strID);
	sprintf(cPassword, strPassword);

	//	�⼮ üũ
	if( iType == 0 )        sprintf(cURL, "http://tantra.hanbiton.com/s_game/handstamp/stamp.asp?user_id=%s&user_pass=%s", cID, cPassword);
	//	��ȸ
	else if( iType == 1 )	sprintf(cURL, "http://tantra.hanbiton.com/s_game/handstamp/stamplist.asp?user_id=%s&user_pass=%s", cID, cPassword);

	HTbool bHttpAlive = CHTWebInfo::HT_bGetHttpRequest(cURL, pcRecv, 28);

	// HTTP�� �������� ���ϴ� ����
	if (!bHttpAlive)
	{
		return _T("");
	}

	return pcRecv;
}

//-----------------------------------------------------------------------------------
// HTbool	HT_bGetServerStatusCheck(HTchar* pcWebRecv)
// D : ������ �α����� �� �� �ִ� ����������, ���峻�� ������ ���������ڼ��� ����
// I : pcWebRecv-������ �о�� �ؽ�Ʈ
//-----------------------------------------------------------------------------------
HTbool
CHTWebLogIn::HT_bGetServerStatusCheck(/*HTchar* pcWebRecv*/)
{
	HTchar				sepq[] = " ";
	HTchar				seps[] = "<br>";
	HTchar				sepp[] = ":";
	HTint				iTempInt = -1;
	
	//HTint				nZoneNum;
	HTchar*				pcToken;

	HT_g_vLogFile("Connecting URL No 301 \n");
	
	HTchar pcRecv[8192*5]; 
	ZeroMemory(pcRecv, sizeof(HTchar)*8192*5);

	if (HT_FALSE==CHTWebInfo::HT_bGetHttpRequest( m_cLogInEnableURL, pcRecv, 8192*5 ))
	{
		return HT_FALSE;
	}

	pcToken = strtok(pcRecv, sepq);

	if (strcmp(pcToken, "LOGIN_RESULT:"))
	{
		return FALSE;	// ��Ʈ��Ȯ��
	}
	pcToken = strtok(HT_NULL, seps);

	if (!strcmp(pcToken, "SUCCESS"))	m_bServerOn = HT_TRUE;
	else								m_bServerOn = HT_FALSE;

	if (!m_bServerOn)	this->HT_vSetZoneCCUserInit();

	if (m_bServerOn)
	{

		HTint	i, j;		
		HTint	iWorldUserNum;
		pcToken = strtok(HT_NULL, sepq);
		pcToken = strtok(HT_NULL, seps);
		
		m_iWorldNum = atoi(pcToken);

		if (m_poWorldInfo)	HT_DELETEARRAY(m_poWorldInfo);
		m_poWorldInfo = new _HT_WORLDINFO[m_iWorldNum];

		if (m_piCCUserNum)	HT_DELETEARRAY(m_piCCUserNum);		
		m_piCCUserNum = new HTint[m_iWorldNum];

		for(i=0; i<m_iWorldNum; i++)
		{
			pcToken = strtok(HT_NULL, sepq);
			pcToken = strtok(HT_NULL, seps);

			//m_poWorldInfo[i].iZoneNum = atoi(pcToken);
			m_poWorldInfo[i].iZoneNum = MAX_SERVER;

			iWorldUserNum = 0;
			for(j=0; j<m_poWorldInfo[i].iZoneNum; j++)
			{
				pcToken = strtok(HT_NULL, sepq);
				pcToken = strtok(HT_NULL, sepq);
				m_poWorldInfo[i].oZoneInfo[j].iWorldNo = i;				// �����ȣ

				pcToken = strtok(HT_NULL, sepq);
				//m_poWorldInfo[i].oZoneInfo[j].iZoneNo = atoi(pcToken);	// ����ȣ
				m_poWorldInfo[i].oZoneInfo[j].iZoneNo = j+1;	// ����ȣ

				pcToken = strtok(HT_NULL, seps);
				if (!pcToken)
				{
					m_poWorldInfo[i].oZoneInfo[j].iCCUserNum = 0;
				}
				else
				{	
					iTempInt = atoi(pcToken);
					if (-1 != iTempInt)
						m_poWorldInfo[i].oZoneInfo[j].iCCUserNum = atoi(pcToken)*300 + rand()/300;
					else
						m_poWorldInfo[i].oZoneInfo[j].iCCUserNum = -1;
				}
				iWorldUserNum += m_poWorldInfo[i].oZoneInfo[j].iCCUserNum;

			}
			m_piCCUserNum[i] = iWorldUserNum;
		}
	}
	else
	{
		HTbool bFirst = HT_TRUE;
		pcToken = strtok(HT_NULL, seps);
		while(pcToken)
		{	
			if (bFirst) 
			{
				sprintf(m_cServerDownCause, "%s", pcToken);
				bFirst = HT_FALSE;
			}
			else
			{
				strcat(m_cServerDownCause, ">> ");
				strcat(m_cServerDownCause, pcToken);
			}
			pcToken = strtok(HT_NULL, seps);
		}
	}
	return m_bServerOn;
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGetWorldNum();
// D : ������ ���� ���, ����� ���� ���� 20���� �����ִ�!!!
// R : ������ ����
//-----------------------------------------------------------------------------------
HTint	
CHTWebLogIn::HT_iGetWorldNum()
{
	return m_iWorldNum;
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vSetWorldNum(HTint iWorldNum)
// D : ������ ���� �����Ѵ�. ����� ������ ��带 �����ϱ� ���� ���ȴ�.
//-----------------------------------------------------------------------------------
HTvoid
CHTWebLogIn::HT_vSetWorldNum(HTint iWorldNum)
{
	HT_DELETEARRAY(m_poWorldInfo);
	if (m_piCCUserNum)	HT_DELETEARRAY(m_piCCUserNum);

	m_iWorldNum = iWorldNum;

	m_poWorldInfo = new _HT_WORLDINFO[m_iWorldNum];
	m_piCCUserNum = new HTint[m_iWorldNum];

	for (HTint i=0; i<m_iWorldNum; i++)
	{
		ZeroMemory( &m_poWorldInfo[i], sizeof(_HT_WORLDINFO));
		ZeroMemory( &m_piCCUserNum[i], sizeof(HTint));
	}
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
// D : ���������ڼ� ���
// I : iWorldNo - �����ȣ, iZoneNo - ����ȣ
// R : ���������ڼ�
//-----------------------------------------------------------------------------------
HTint
CHTWebLogIn::HT_iGetCCUserNum(HTint iWorldNo, HTint iZoneNo)
{
	return m_poWorldInfo[iWorldNo].oZoneInfo[iZoneNo].iCCUserNum;
}

HTint
CHTWebLogIn::HT_iGetCCUserNum(HTint iWorldNo)
{
	HTint iWorldCCUserNum = 0;
	for (HTint i=0; i<_ZONENUM_PER_WORLD; i++)
	{
		if (m_poWorldInfo[iWorldNo].oZoneInfo[i].iCCUserNum!=-1)
			iWorldCCUserNum += m_poWorldInfo[iWorldNo].oZoneInfo[i].iCCUserNum;
	}
	return iWorldCCUserNum;
}

//-----------------------------------------------------------------------------------
// HTbool	HT_bGetServerDownCause(HTchar* pcCause)
// D : ������ �ٿ�Ǿ� �ִ� ���� ���
// I : 
// R : pcCause - ����
//-----------------------------------------------------------------------------------
HTbool
CHTWebLogIn::HT_bGetServerDownCause(HTchar* pcCause)
{
	if (m_bServerOn) return HT_FALSE;
	sprintf(pcCause, m_cServerDownCause);
	return HT_TRUE;
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGetAliveZoneNum(HTint iWorldNum)
// D : ���忡�� ����ִ� �� ���� ���
// R : ���忡�� ����ִ� �� ����
//-----------------------------------------------------------------------------------
HTint
CHTWebLogIn::HT_iGetAliveZoneNum(HTint iWorldNo)
{
	HTint iAliveZoneNum = 0;
	for (HTint i=0; i<_ZONENUM_PER_WORLD; i++)
	{
		if (m_poWorldInfo[iWorldNo].oZoneInfo[i].iCCUserNum!=-1)
		{
			iAliveZoneNum++;
		}
	}
	return iAliveZoneNum;
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vSetZoneCCUserInit()
// D : ���� ���������ڼ��� -1�� �����.
//-----------------------------------------------------------------------------------
HTvoid
CHTWebLogIn::HT_vSetZoneCCUserInit()
{
	HTint i, j;
	for(i=0; i<m_iWorldNum; i++)
	{	
		for(j=0; j<m_poWorldInfo[i].iZoneNum; j++)
		{	
			m_poWorldInfo[i].oZoneInfo[j].iWorldNo = i;				// �����ȣ
			m_poWorldInfo[i].oZoneInfo[j].iZoneNo = j;	// ����ȣ
			m_poWorldInfo[i].oZoneInfo[j].iCCUserNum = -1;
		}
		m_piCCUserNum[i] = 0;
	}
}
//===================================================================================

CHTGMCall::CHTGMCall()
{
	m_iCallAcept = 0;
	m_iCallCount = 0;
	m_strMsg = _T("");
	ZeroMemory(&m_cGMLogPath, sizeof(HTchar)*HT_MAX_STR);
}

CHTGMCall::~CHTGMCall()
{
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGMCall(CHTString sID, CHTString sName, HTchar* pcContents)
// D : ���������� ������Ų��.
// I : sID - ���̵�, sName - ĳ���� �̸�, pcContents - ��������
//-----------------------------------------------------------------------------------
HTint
CHTGMCall::HT_iGMCall(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName, CHTString sContents)
{ 
	m_iCallAcept = -1;

	HTchar		cURL[1024];
	HTchar		pcRecv[20];
	HTchar		seps[] = "<br>";
	HTchar		sepp[] = "%s";
	HTchar*		pcToken;
	HTchar		strWorld[4];
	HTchar		strCharName[24];
	HTchar		strID[24];
	HTchar		strText[512];
	ZeroMemory(strText, sizeof(HTchar)*256);

	sprintf(strWorld, "0%1d", iWorldNo);
	sprintf(strCharName, sName);;
	sprintf(strID, sID);

	this->HT_vReArrangeCallMsg(sContents);

	HTint iNum = m_strMsg.HT_nGetSize();
	for (HTint i=0; i<iNum; i++)
	{
		strText[i] = m_strMsg[i];
	}

	sprintf(cURL, sURL, strWorld, strID, strCharName, strText);

	HTbool bHttpAlive = CHTWebInfo::HT_bGetHttpRequest(cURL, pcRecv, 20);

	if (bHttpAlive)
	{
		pcToken = strtok(pcRecv, seps);		m_iCallAcept = atoi(pcToken);
		pcToken = strtok(HT_NULL, seps);	m_iCallCount = atoi(pcToken);
	}
	return m_iCallAcept;
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGMCallCheck(HTint iWorldNo, CHTString sID, CHTString sName)
// D : ���������� ������Ų��.
// I : sID - ���̵�, sName - ĳ���� �̸�, pcContents - ��������
//-----------------------------------------------------------------------------------
HTint
CHTGMCall::HT_iGMCallCheck(CHTString sURL, HTint iWorldNo, CHTString sID, CHTString sName)
{
	m_iCallAcept = -1;

	HTchar		cURL[1024];
	HTchar		pcRecv[512];
	HTchar		seps[] = "<br>";
	HTchar		sepp[] = "<";
	HTchar*		pcToken;
	HTchar		strWorld[5];
	HTchar		strCharName[25];
//	HTchar		strID[25];
	HTchar		strText[512];
	
	//ZeroMemory(strText, sizeof(HTchar)*512);
	//ZeroMemory(pcRecv, sizeof(HTchar)*512);

	sprintf(strWorld, "0%1d", iWorldNo);
	sprintf(strCharName, sName);;
	//sprintf(strID, sID);

	sprintf(cURL, sURL, strWorld, strCharName);

	HTbool bHttpAlive = CHTWebInfo::HT_bGetHttpRequest(cURL, pcRecv, 512);
//	m_strMsg = "";

	if (bHttpAlive)
	{
		pcToken = strtok(pcRecv, seps);		m_iCallAcept = atoi(pcToken);

		if (m_iCallAcept == 0)
		{
			pcToken = strtok(NULL, sepp);	m_strMsg = pcToken;
			strcpy(strText, m_strMsg);
			strText[0] = '>';
			strText[1] = '>';
			strText[2] = 32;
			strcpy(m_strMsg, strText);
		}
	}
	return m_iCallAcept;
}

//-----------------------------------------------------------------------------------
// HTint	HT_iGMCallCancel(CHTString sID, CHTString sName)
// D : ������Ų �������� ���
// I : sID - ���̵�, sName - ĳ���� �̸�, 
//-----------------------------------------------------------------------------------
HTint
CHTGMCall::HT_iGMCallCancel(HTint iWorldNo, CHTString sID, CHTString sName)
{
	m_iCallAcept = -1;
	HTchar		cURL[500];
	HTchar		pcRecv[20];
	HTchar		seps[] = "<br>";
	HTchar		sepp[] = "%s";
	HTchar*		pcToken;
	HTchar		strWorld[2];
	HTchar		strCharName[20];
	HTchar		strID[20];
	HTchar		strText[256];
	ZeroMemory(strText, sizeof(HTchar)*256);

	sprintf(strWorld, "0%1d", iWorldNo);
	sprintf(strCharName, sName);;
	sprintf(strID, sID);

	sprintf(cURL, m_cGMCallCancelURL, strWorld, strID, strCharName);

	HTbool bHttpAlive = CHTWebInfo::HT_bGetHttpRequest(cURL, pcRecv, 20);

	if (bHttpAlive)
	{
		pcToken = strtok(pcRecv, seps);		m_iCallAcept = atoi(pcToken);
	}
	return m_iCallAcept;
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vReArrangeCallMsg(CHTString strMsg)
// D : ��
//-----------------------------------------------------------------------------------
HTvoid
CHTGMCall::HT_vReArrangeCallMsg(CHTString strMsg)
{
	CHTString str;
	m_strMsg = strMsg;
	//m_strMsg.HT_hrStringCopy(m_strMsg, strMsg, 255);

	HTchar		seps1[] = "%", seps2[] = "&", seps3[] = "<",  seps4[] = "=", seps5[] = ">", seps6[] = " ";
	HTchar*		pcToken;
	
	pcToken = strtok(m_strMsg, seps1);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%25");
		pcToken = strtok(HT_NULL, seps1);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
	
	pcToken = strtok(m_strMsg, seps2);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%26");
		pcToken = strtok(HT_NULL, seps2);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
	
	pcToken = strtok(m_strMsg, seps3);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%3C");
		pcToken = strtok(HT_NULL, seps3);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
	
	pcToken = strtok(m_strMsg, seps4);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%3D");
		pcToken = strtok(HT_NULL, seps4);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
	
	pcToken = strtok(m_strMsg, seps5);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%3E");
		pcToken = strtok(HT_NULL, seps5);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
	
	pcToken = strtok(m_strMsg, seps6);
	while (pcToken)
	{
		strcat(str, pcToken);
		strcat(str, "%20");
		pcToken = strtok(HT_NULL, seps6);
		if (!pcToken) 
		{
			str--;str--;str--;
		}
	}
	m_strMsg = str;//m_strMsg.HT_hrStringCopy(m_strMsg, str, 255); 
	str = _T("");
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vSaveGMChat()
// D : GMä�� ����
//-----------------------------------------------------------------------------------
HTvoid
CHTGMCall::HT_vSaveGMChat(CHTString strCharName, CHTString str, HT_COLOR clr)
{
	HTchar cFileName[HT_MAX_STR];
	HTchar cCharName[HT_MAX_STR];
	
	sprintf(cCharName, strCharName);
	struct tm when;
	__time64_t now;
	_time64( &now );
	when = *_localtime64( &now );
  
	sprintf( cFileName, "%s%s%.4d%.2d%.2d.txt", 
	   cCharName, "_", when.tm_year+1900,  when.tm_mon+1, when.tm_mday);
	
	FILE*	fp;
	
	//HTint iSize = str.HT_nGetSize();
	//if (iSize<=0) return;
	HTchar strR[256];
	sprintf(strR, str);
	for (HTint i=0; i<256; i++)		strR[i] += 0x01;
	
	
	_GM_MSG		oGMMsg;
	ZeroMemory(&oGMMsg, sizeof(_GM_MSG));
	sprintf(oGMMsg.strMsg, strR);
	
	oGMMsg.clrR = (BYTE)(clr.r*255.0f);
	oGMMsg.clrG = (BYTE)(clr.g*255.0f);
	oGMMsg.clrB = (BYTE)(clr.b*255.0f);
	
	// �ڱ� �Ŀ� ����
	//fp = fopen(cFileName, "a");
	//if (!fp) return;
	//fwrite( &oGMMsg, sizeof(_GM_MSG), 1, fp);
	//fclose(fp);		

	// ��Ʈ��ũ ���� ���丮�� ����
	HTchar cCopyPath[HT_MAX_STR];
	sprintf(cCopyPath, "%s%s", m_cGMLogPath, cFileName);

	//MessageBox(NULL, cCopyPath, cCopyPath, MB_OK);
	fp = fopen(cCopyPath, "a");
	if (!fp) return;
	fprintf(fp, str);	fprintf(fp, "\n");
	fclose(fp);	
}

//-----------------------------------------------------------------------------------
// HTvoid	HT_vSetGMLogPath(HTchar* pcPath)
// D : GM�α� ��� ����
//-----------------------------------------------------------------------------------
HTvoid	
CHTGMCall::HT_vSetGMLogPath(HTchar* pcPath)
{
	sprintf(m_cGMLogPath, pcPath);
}