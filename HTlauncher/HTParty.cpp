
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTParty.h"

//	�ֽ�, ����, ���, ID
HTint	g_nTrimurity_IconIndex[3]	= {	439, 438, 440 };
//	0:����,1:�Ƽ���,2:���,3:����,4:Ŵ����,5:������,6:���ٸ���,7:����� -> ���� �ε����� +1�� ����
HTint	g_nTribe_IconIndex[8]		= {	442, 443, 444, 445, 446, 447, 448, 449};
//	�����1,���̻�1,ũ��Ʈ����1,���1,�ƹ�Ʈ��1
HTint	g_nGradeIcon_Index[5]		= {	454, 455, 453, 452, 451 };
//	������ ���� ��
HTint	g_nIconCellNo[6][3]		= { 15,16,17,  18,19,20, 21,22,23, 24,25,26, 27,28,29, 30,31,32 };
//	HP Bar Bitmap Image
HTint	g_HPBarBitmapNo[6] = { 33, 34, 35, 36, 37, 38 };

HTint	g_iMiniParty_HPBarImageNumber[7] = { 1, 2, 3, 4, 5, 6, 7 };
//	��Ƽ�̴�â_TP Bar
HTint	g_iMiniParty_TPBarImageNumber[7] = { 8, 9, 10, 11, 12, 13, 14 };

HTParty::HTParty(void)
{
	m_bLoaded = HT_FALSE;
}

HTParty::~HTParty(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_PARTYWND );
	//---------��Ƽ��/�ּҷ� �׸�---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; ++i )
	{
		ZeroMemory(&m_Party_Factor[i], sizeof(S_PARTY));
		m_Party_Factor[i].byLevel= 0xff;
		//	UI ��Ʈ���� �����߳� ���޳�?
		m_byUIControlSet[i] = 0;
	}
}

HTvoid HTParty::HT_vParty_CleanUp()
{
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
}

HTvoid HTParty::HT_vParty_Init()
{
	//	Create Window
	this->HT_vParty_CreateWindow();

	m_nParty_Send_Process			= PARTY_PROCESS_ERRORMESSAGE;
	m_nParty_WindowActiveSw			= HT_FALSE;
	m_nParty_DialogBoxActiveSw		= HT_FALSE;
	m_nParty_ReDialogBoxActiveSw	= HT_FALSE;
	//---------���� ��Ƽ���̳�?---------//
	m_Party_Jang = HT_FALSE;
	m_dwParty_JangKeyID = 0;
	m_bParty_Exist = HT_FALSE;
	//---------��Ƽ��/�ּҷ� �׸�---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; ++i )
	{
		ZeroMemory(&m_Party_Factor[i], sizeof(S_PARTY));
		m_Party_Factor[i].byLevel= 0xff;
		//	UI ��Ʈ���� �����߳� ���޳�?
		m_byUIControlSet[i] = 0;
	}
	m_Party_MemberCount = 0;
	m_party_DeleteMember = 0;

	//----------�� ��Ƽ������ �ֽ�, ����, ��� ������ �̹���----------//
	//	���̻�3 -> �����3 -> ũ��Ʈ����3 -> ���3 -> �ƹ�Ÿ��1
	//for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	//{
	//	// HP Bar
	//	m_nParty_MemberHPBar[i] = -1;
	//}
	m_bLoaded = HT_TRUE;

	//	�̴���Ƽâ ����ġ
	m_bMiniParty_WndSw = HT_FALSE;

	//	��Ƽâ �����
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );

	// �ڵ��й� ���
	m_bParty_RootingMode = HT_FALSE;
}

//	Create Window
HTvoid HTParty::HT_vParty_CreateWindow()
{
	HTint i;
	CHTString strMessage;
	//	[_DIALOG_PARTYWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_PARTYWND, _T(""), 200, 300, g_cParty->HT_vParty_InputCheckForParty, 0 );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_PARTYWND, true );
	g_cUIManager->HT_MoveWindow( _DIALOG_PARTYWND, g_pEngineHandler->HT_iGetScreenWidth()-200, 32 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 1, 159, 0, 0, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 1, eMsgPartyAutoRootingMode, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 0, 79, 19 );//�ڵ��й�
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PARTYWND, 1 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 2, 159, 82, 0, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 2, eMsgCommonSecede, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 82, 0, 79, 19 );//	Ż  ��
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PARTYWND, 2 );
	for( i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_PARTYWND, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 20+(i*28), 180, 13 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_PARTYWND, 10+i, 7 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_PARTYWND, 10+i, 101, 0, 34+(i*28), 1400, 0, 5 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		g_cUIManager->HT_AddTextureControl( _DIALOG_PARTYWND, 20+i, 102, 0, 40+(i*28), 1400, 0, 5 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
	}
}
//	�Է� �޼��� ó��
//	AshramInfo
void HTParty::HT_vParty_InputCheckForParty(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == 1 )
		{
			if( g_cParty->HT_bParty_IsPartyJang( g_cMainCharacter->HT_iMainChar_GetKeyID() ) )
			{
				if( g_cParty->m_bParty_RootingMode )	g_cParty->m_bParty_RootingMode = HT_FALSE;
				else									g_cParty->m_bParty_RootingMode = HT_TRUE;
				g_cParty->HT_vNetWork_CSP_Req_Set_Party( g_cParty->m_bParty_RootingMode );
			}
		}
		else if( iTargetID == 2 )
		{
			g_cParty->HT_bParty_Command_PartyWithDraw();
		}
		else if( iTargetID>=10 && iTargetID<=((PARTY_MAX_PERSON-1)+10) )
		{
			//	��Ƽ ������� Ŭ���ߴ°�?
            g_cParty->HT_bParty_MemberClick(iTargetID);
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	Ȯ�� ��ư
		if( iTargetID == 2 )
		{
			//	���� �޽������� ó��
			if( g_cParty->m_nParty_Receive_Process == PARTY_PROCESS_RECIVEDJOINPARTY )
			{
				//----------���� ��Ƽ----------//
				g_cParty->HT_vNetWork_CSP_CNF_PARTY();
				g_cParty->m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
				return;
			}

			switch(g_cParty->m_nParty_Send_Process)
			{
				case PARTY_PROCESS_PARTYLEAVE:
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
					break;
				case PARTY_PROCESS_PARTYMEMBERDELETE:
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x01 );
					break;
				case PARTY_PROCESS_PARTYDELETE :
					g_cParty->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
					break;
				default :
					break;
			}
			g_cParty->m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		}
		//	��� ��ư
		else if( iTargetID == 3 )
		{
			//	���� �޽����� �׳� ó��
			g_cParty->m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		}
	}
}

//	ESC Key ������ ��Ƽâ �ݱ�
HTvoid HTParty::HT_vParty_ESC_CloseWindow()
{
	//----------Ȱ��ȭ / ��Ȱ��ȭ----------//
	this->HT_vParty_MiniPartyWndSetSw();
}

//----------��Ƽ Ż��----------//
HTvoid HTParty::HT_vParty_PartyLeave()
{
	//--------- ��Ƽ�� ����� ������?---------//
	if( m_bParty_Exist == HT_FALSE )
		return;

	HTint iInductNo = -1;
	//---------���� ��Ƽ���̳�?---------//
	if( m_Party_Jang == HT_TRUE )
	{
		if( m_party_DeleteMember >= 0 && m_party_DeleteMember < 7 )
		{
			// �̺��� ��Ƽ���� �����Ű�ڽ��ϱ�?
			HT_vParty_SetMessage( eMsgPartySecessionMemberQuestion, &m_strDialogBoxMessage );
			m_nParty_Send_Process = PARTY_PROCESS_PARTYMEMBERDELETE;
			iInductNo = RECONFIRM_PARTY_DELETE_MEMBER;
		}
		else 
		{
			// ��Ƽ�� ��ü �Ͻðڽ��ϱ�?
			//HT_vParty_SetMessage( eMsgPartyDissolutionQuestion, &m_strDialogBoxMessage );
			// ��Ƽ���� Ż�� �Ϸƴϱ�?
			HT_vParty_SetMessage( eMsgPartySecessionQuestion, &m_strDialogBoxMessage );
			//m_nParty_Send_Process = PARTY_PROCESS_PARTYDELETE;
			m_nParty_Send_Process = PARTY_PROCESS_PARTYLEAVE;
			iInductNo = RECONFIRM_PARTY_SECESSION;
			//iInductNo = RECONFIRM_PARTY_DISSOLUTION;
		}
	}
	else
	{
		// ��Ƽ���� Ż�� �Ϸƴϱ�?
		HT_vParty_SetMessage( eMsgPartySecessionQuestion, &m_strDialogBoxMessage );
		m_nParty_Send_Process = PARTY_PROCESS_PARTYLEAVE;
		iInductNo = RECONFIRM_PARTY_SECESSION;
	}
	
	g_cUIManager->HT_MessageBox( _DIALOG_PARTYWND, m_strDialogBoxMessage.HT_szGetString(), 1 );
}


HTbool HTParty::HT_bParty_IsClickJoinBn()
{
	if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY || m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//----------���� ĳ���Ϳ��� ��Ƽ ���� ��û----------//
HTRESULT HTParty::HT_vParty_JoinParty( HTint nObject )
{
	DWORD tKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nObject );
	m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( tKeyID );

	m_party_DeleteMember = 255;
	for (int i=0; i<7; ++i)	// �ٸ� ����� �ȵɶ����� ��� ������ �����ؾ� �Ѵ�.
		if (m_Party_Factor[i].nID == tKeyID) { m_party_DeleteMember = i; break;}
	if (m_party_DeleteMember == 255) m_szCharacterName = "";	// ��Ƽ�� �ƴ� ����� Ŭ���ߴٸ� ��������

	if( m_nParty_Send_Process != PARTY_PROCESS_REQJOINPARTY &&
		m_nParty_Send_Process != PARTY_PROCESS_PARTYCREATE )
		return HT_FAIL;

	// ��Ƽ���� �ƴϰų� ���� ��Ƽ�� ��û�� ĳ�����κ��� ���� �ȿ԰ų�
	// NPC�� ��ȭ���̰ų� �ٸ� ����� Ʈ���̵带 �ϰ� �ִ� ���̸� ó�� ���� ����
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) || g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) == HT_TRUE)
		return HT_FAIL;

	m_dwParty_JoinPartyKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( nObject );
	if( m_dwParty_JoinPartyKeyID == 0 )
	   return HT_FAIL;

	if( m_Party_MemberCount >= (PARTY_MAX_PERSON-1) )
		return HT_FAIL;

	// Ŀ�� ����
	if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
	{
		if( g_cExchangeSystem->HT_vExchange_GetClickTradeButton() == HT_TRUE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_TRADE_ANI);
		else
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_ARROW_1);
	}

	//	��Ƽ ���� ��û
	if( m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
		this->HT_vNetWork_CSP_CREATEJOIN_PARTY();
	//	��Ƽ ���� ��û
	else if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY )
	{
		CHTString strName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_dwParty_JoinPartyKeyID);
		if( HT_bParty_IsPartyMember( strName ) ) // ��Ƽ���� ���
		{
			CHTString str;
			// �̹� ���ԵǾ��ִ� ĳ�����Դϴ�.
			HT_vParty_SetMessage( eMsgPartyJoinAlreadyMember, &str );
			if( str.HT_bIsEmpty() == HT_FALSE )
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, str );
		}
		else
			this->HT_vNetWork_CSP_CREATEJOIN_PARTY();
	}

	//	��Ƽ���μ��� �ʱ�ȭ
	m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;

	return HT_OK;
}

//----------��Ʈ��ũ ���� �Լ�----------//
//			0x16 Group(Party/Guild/�ּҷ�)	101
//----------��Ƽ ����----------//
HTvoid HTParty::HT_vNetWork_CSP_CREATEJOIN_PARTY()
{
	MSG_REQParty* info = HT_NULL;
	info = new MSG_REQParty;
	info->TargetID = m_dwParty_JoinPartyKeyID;
	g_pNetWorkMgr->RequestReqCreateJoinParty( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_REQ_CREATE_PARTY" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//----------- ��Ƽ ���� ��û ���� --------------//
HTvoid HTParty::HT_vNetWork_SCP_CREATEJOIN_PARTY( MSG_REQParty* info )
{
	//	�̹� ��Ƽ�� ������� �ְų� NPC�� �۾����̰ų� 
	if( m_bParty_Exist == HT_TRUE || g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW )
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) 
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) 
								 ||	g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
	{
		CHTString str;
		// %s���� ��Ƽ ���� ��û�� �����߽��ϴ�.
		m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->Leader.nID );
		HT_vParty_SetMessage( eMsgPartyJoinReqReceiveRejection, &str);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ERROR, str );

		return;
	}

	//----------��Ƽ���� Ű���̵� ����----------//
	m_dwParty_JangKeyID = info->Leader.nID;
	m_strParty_JangName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_dwParty_JangKeyID );
	// %s���� ��Ƽ�α⸦ ��û�Ͽ����ϴ�
	m_szCharacterName = m_strParty_JangName;
	HT_vParty_SetMessage( eMsgPartyJoinReqReceive, &m_strDialogBoxMessage );
	m_nParty_Receive_Process = PARTY_PROCESS_RECIVEDJOINPARTY;
	g_cUIManager->HT_MessageBox( _DIALOG_PARTYWND, m_strDialogBoxMessage.HT_szGetString(), 1 );
}

//----------���� ��Ƽ----------//
HTvoid HTParty::HT_vNetWork_CSP_CNF_PARTY()
{
	MSG_CNFParty* info = HT_NULL;
	info = new MSG_CNFParty;
	info->TargetID = m_dwParty_JangKeyID;
	g_pNetWorkMgr->RequestReqCNFParty( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_CFN_PARTY : %d",  info->TargetID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//----------��Ƽ�� �߰�----------//
HTvoid HTParty::HT_vNetWork_SCP_MSG_AddParty( MSG_AddParty* info )
{

	//	����� ��� á����
	if( m_Party_MemberCount >= (PARTY_MAX_PERSON-1) )
		return;

	//	��Ƽ�� �������� ������
	if( !m_bParty_Exist )
	{
		//----------��Ƽ ������ �ʱ�ȭ----------//
		this->HT_vParty_InitMember();
		m_bParty_Exist = HT_TRUE;

		//----------�ý��� â�� �޽��� �ٿ��----------//
		CHTString strMessage;
		HT_vParty_SetMessage( eMsgPartyCreateOK, &strMessage ); // ��Ƽ�� �����Ǿ����ϴ�.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, strMessage );

		//	��Ƽâ �ٿ��
		m_bMiniParty_WndSw = HT_FALSE;
		this->HT_vParty_MiniPartyWndSetSw();

		// ���� ��Ƽ�� ó�� �������� �� ������ ���� ��� ǥ��
		if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			HT_bParty_SetRootingMode( m_bParty_RootingMode );
	}

	//	��Ƽ���� ���� ����
	m_dwParty_JangKeyID			= info->nLeaderID;
	if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() ) // ���� ��Ƽ���� ���
	{
		m_Party_Jang				= HT_TRUE;
		m_strParty_JangName			= g_oMainCharacterInfo.szCharName;
	}
	else // �ٸ� ����� ��Ƽ���� ���
	{
		m_Party_Jang				= HT_FALSE;
		m_strParty_JangName			= g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( info->nLeaderID );
	}

	S_PARTY oData;
	memcpy( &oData, &info->Party, sizeof( S_PARTY ) );
	//----------���ο� ��� �߰��ϱ�----------//
	this->HT_vParty_InsertMember( oData );

	// �ڵ��й� ���
	if( info->Party.nID == m_dwParty_JangKeyID )
	{
		HT_bParty_SetRootingMode( (HTbool)info->Party.byRootingMode );
	}

	//	��Ƽ ��� �����ֱ�
	this->HT_vParty_PartyMemberDiplay();
}

//----------���� ����Ÿ �����ϱ�----------//
HTvoid HTParty::HT_vNetWork_SCP_MSG_UpdateParty( PS_SCP_RESP_UPDATE_PARTY info )
{
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == info->Party.nID )
		{
			m_Party_Factor[i].byLevel = info->Party.byLevel;
			m_Party_Factor[i].nAffections = info->Party.nAffections;
			m_Party_Factor[i].nCurHP = info->Party.nCurHP;
			m_Party_Factor[i].nCurTP = info->Party.nCurTP;
			m_Party_Factor[i].nMaxHP = info->Party.nMaxHP;
			m_Party_Factor[i].nMaxTP = info->Party.nMaxTP;

			//	Member HP
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
			//	Member TP
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );

			//	HP
			HTfloat xPos;
			if( m_Party_Factor[i].nCurHP==0 && m_Party_Factor[i].nMaxHP==0 )
				xPos = 1.0f;
			else
				xPos = (HTfloat)m_Party_Factor[i].nCurHP/(HTfloat)m_Party_Factor[i].nMaxHP;
			if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 10+i, (HTint)(xPos*150), 5 );
			if( m_Party_Factor[i].nCurHP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
			else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
			//	TP
			if( m_Party_Factor[i].nCurTP==0 && m_Party_Factor[i].nMaxTP==0 )
				xPos = 1.0f;
			else
				xPos = (HTfloat)m_Party_Factor[i].nCurTP/(HTfloat)m_Party_Factor[i].nMaxTP;
			if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 20+i, (HTint)(xPos*150), 5 );
			if( m_Party_Factor[i].nCurTP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
			else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );
			return;
		}
	}
}

//----------��Ƽ Ż��/��ü----------//
HTvoid HTParty::HT_vNetWork_CSP_MSG_RemoveParty( HTint iTarget )
{
    MSG_RemoveParty* info = HT_NULL;
	info = new MSG_RemoveParty;
	if( iTarget == 0 )
		info->nTargetID = g_cMainCharacter->HT_iMainChar_GetKeyID();
	else if( iTarget == 1 )
		info->nTargetID = m_Party_Factor[m_party_DeleteMember].nID;
	else if( iTarget == 2 )
		info->nTargetID = MAX_USER;
	g_pNetWorkMgr-> RequestReqRemoveParty( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MSG_RemoveParty : %d",  info->nTargetID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid HTParty::HT_vNetWork_SCP_MSG_RemoveParty( MSG_RemoveParty* info )
{
	CHTString	strTargetName;
	CHTString	strMyName;
	strMyName = g_oMainCharacterInfo.szCharName;
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( info->nTargetID == m_Party_Factor[i].nID )
		{
            strTargetName = m_Party_Factor[i].Name;
			break;
		}
	}

	// ��Ƽ�� ���� ����
	if( info->nLeaderID != m_dwParty_JangKeyID )
	{
		m_dwParty_JangKeyID = info->nLeaderID;
		if( info->nLeaderID == g_cMainCharacter->HT_iMainChar_GetKeyID() ) // ���� ��Ƽ���� ���
		{
			m_Party_Jang				= HT_TRUE;
			m_strParty_JangName			= g_oMainCharacterInfo.szCharName;
		}
		else // �ٸ� ����� ��Ƽ���� ���
		{
			for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
			{
				if( info->nLeaderID == m_Party_Factor[i].nID )
				{
					m_strParty_JangName = m_Party_Factor[i].Name;
					break;
				}
			}
		}

		//----------�ý��� â�� �޽��� �ٿ��----------//
		CHTString strMessage;
		HT_vParty_SetMessage( eMsgPartyLeaderNotify, &strMessage ); // %s���� ��Ƽ���Դϴ�.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, strMessage );
	}

	if( strMyName.HT_iStringCompare( strTargetName ) == 0 || info->nTargetID == 0 )
	{
		m_bParty_Exist = HT_FALSE;
		//----------��Ƽ ����----------//
		this->HT_vParty_DISBAND();
		// ��Ƽ���� Ż��Ǿ����ϴ�.
		CHTString szMessage;
		HT_vParty_SetMessage( eMsgPartySecessionOK, &szMessage );
		m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );

		//	��Ƽâ �����
		g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
	}
	else
	{
		HT_vParty_DeleteMember( strTargetName );
		// %s��(��) ��Ƽ�� Ż���Ͽ����ϴ�.
		m_szCharacterName = strTargetName;
		CHTString szMessage;
		HT_vParty_SetMessage( eMsgPartySecessionMemberOK, &szMessage );
		m_nParty_Receive_Process = PARTY_PROCESS_ERRORMESSAGE;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );
		
		// �ڱ� �ڽŸ� ������ ��� ��Ƽâ ���� �����
		if( m_Party_MemberCount == 0 ) 
		{
			this->HT_vParty_DISBAND();

			//	��Ƽâ �����
			g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
		}
	}

	//	��Ƽ ��� �����ֱ�
	this->HT_vParty_PartyMemberDiplay();
}

// �ڵ��й� ���
HTvoid HTParty::HT_vNetWork_CSP_Req_Set_Party( HTbool bRootingMode )
{
	MSG_SetParty* info = HT_NULL;
	info = new MSG_SetParty;

	info->byRootingMode = bRootingMode;
	g_pNetWorkMgr->RequestSetParty( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Set_Party : %d",  info->byRootingMode );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid HTParty::HT_vNetWork_SCP_Resp_Set_Party( MSG_SetParty* info )
{
	if( info->byResult == 0x00 )
	{
		HT_bParty_SetRootingMode( (HTbool)info->byRootingMode );
	}
}

//----------��Ƽ ������ �ʱ�ȭ----------//
HTvoid HTParty::HT_vParty_InitMember()
{
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		m_Party_Factor[i].byLevel = 0xff;
	}
}

//----------���ο� ��� �߰��ϱ�----------//
HTvoid HTParty::HT_vParty_InsertMember( S_PARTY info )
{
	CHTString	strCompare;
	HTint		nIndex = 0;

	//	�� ������ ã�Ƴ�
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	������ �ִ� ĳ�������� ����
		strCompare = m_Party_Factor[i].Name;
		if( strCompare.HT_iStringCompare( info.Name ) == 0 )
			return;

		if( m_Party_Factor[i].byLevel == 0xff )
		{
			nIndex = i;
			break;
		}
	}

	//	��Ƽ��� ������ OtherCharSystem�� �ѱ�
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoineDisband( info.Name, 0x02 );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();

	memcpy( &m_Party_Factor[nIndex], &info, sizeof(S_PARTY) );
	++m_Party_MemberCount;
}

//----------���� ��� �����ϱ�----------//
HTvoid HTParty::HT_vParty_DeleteMember( CHTString strTemp )
{
	//	��Ƽ��� ������ OtherCharSystem�� �ѱ�
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoineDisband( strTemp, 0x01 );
	CHTString	strCompare;
	HTvector3	vecTempPos;

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		strCompare = m_Party_Factor[i].Name;
		if( strCompare.HT_iStringCompare( strTemp ) == 0 )
		{
			//	��Ƽ Ż�� ����
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoin( m_Party_Factor[i].Name, 0x01 );
			//	��� ����
			--m_Party_MemberCount;
			
			// �� ���� �κк��� ���� ����.
			for( HTint j=i ; j<m_Party_MemberCount ; j++ )
			{
				m_Party_Factor[j] = m_Party_Factor[j+1];
				memset( &m_Party_Factor[j+1], 0, sizeof(S_PARTY) );
				m_Party_Factor[j+1].byLevel = 0xff;
			}

			for( j=m_Party_MemberCount ; j<(PARTY_MAX_PERSON-1) ; j++ )
			{
				memset( &m_Party_Factor[j], 0, sizeof(S_PARTY) );
				m_Party_Factor[j].byLevel = 0xff;
			}
			break;
		}
	}
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//----------��Ƽ ����----------//
HTvoid HTParty::HT_vParty_DISBAND()
{
	//---------���� ��Ƽ���̳�?---------//
	m_Party_Jang = HT_FALSE;
	m_dwParty_JangKeyID = 0;
	m_strParty_JangName.HT_hrCleanUp();
	m_bParty_Exist = HT_FALSE;
	m_Party_MemberCount = 0;

	// �ڵ��й� ���
	m_bParty_RootingMode = HT_FALSE;

	//---------��Ƽ��/�ּҷ� �׸�---------//
	for( HTint i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	��Ƽ Ż�� ����
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetPartyJoin( m_Party_Factor[i].Name, 0x01 );
		memset( &m_Party_Factor[i], 0, sizeof(S_PARTY) );
		m_Party_Factor[i].byLevel = 0xff;
	}
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//----------�ܺο��� ��Ƽ ��ü �� Ż��----------//
HTvoid HTParty::HT_vParty_OutSideRequest_LogOut()
{
	if( m_bParty_Exist == HT_FALSE )
		return;

	//---------���� ��Ƽ���̳�?---------//
	if( m_Party_Jang == HT_TRUE )
	{
		//----------��Ƽ Ż��(��Ƽ�� �Ǵ� ��Ƽ���� ���� �����)�� ��û�Ѵ�----------//
		this->HT_vNetWork_CSP_MSG_RemoveParty( 0x02 );
	}
	else
	{
		//----------��Ƽ Ż��(��Ƽ�� �Ǵ� ��Ƽ���� ���� �����)�� ��û�Ѵ�----------//
		this->HT_vNetWork_CSP_MSG_RemoveParty( 0x00 );
	}
}

//----------��Ƽ ������� �Ǵ�----------//
HTbool HTParty::HT_bParty_IsPartyMember( CHTString strName )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	HTint nCompare;
	for( HTint i=0 ; i<m_Party_MemberCount ; i++ )
	{
		nCompare = strName.HT_iStringCompare( m_Party_Factor[i].Name );
		if( nCompare == 0 )
			return HT_TRUE;
	}

	return HT_FALSE;
}

HTbool HTParty::HT_bPArty_IsPartyMember( DWORD dwCharKeyID )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == dwCharKeyID )
			return HT_TRUE;
	}

	return HT_FALSE;
}

// ��Ƽ������ �˻�
HTbool HTParty::HT_bParty_IsPartyJang( DWORD dwCharKeyID )
{
	if( !m_bParty_Exist )
		return HT_FALSE;

	if( m_dwParty_JangKeyID == dwCharKeyID )
		return HT_TRUE;
	else
		return HT_FALSE;
}
// ��Ƽ�� �̸� ��ȯ
CHTString HTParty::HT_szParty_GetPartyMemberName( HTdword dwCharKeyID )
{
	if( !m_bParty_Exist )
		return " ";

	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		if( m_Party_Factor[i].nID == dwCharKeyID )
			return m_Party_Factor[i].Name;
	}

	return " ";
}

//	��Ƽ�� ���̵� ��ȯ
HTvoid HTParty::HT_vParty_GetPartyMemberKeyID( HTint* iMember, HTfloat fRange )
{
	HTfloat	fDis;
	HTvector3 vecPos;
	HTvector3 vecMainPos = g_cMainCharacter->HT_vecGetPosition();
	iMember[0] = g_cMainCharacter->HT_iMainChar_GetKeyID();
	for( HTint i=0 ; i<m_Party_MemberCount ; ++i )
	{
		//	�Ÿ��� ���س���
		vecPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( m_Party_Factor[i].nID );
		fDis = (float)sqrt( double( ( (vecMainPos.x - vecPos.x) * (vecMainPos.x - vecPos.x) ) + ( (vecMainPos.z - vecPos.z) * (vecMainPos.z - vecPos.z) ) ) );
		if( fDis < fRange )
		{
			iMember[i+1] = m_Party_Factor[i].nID;
		}
	}
}

// �ڵ��й� ���
HTvoid HTParty::HT_bParty_SetRootingMode( HTbool bMode )
{
	if( !m_bParty_Exist )
		return;

	m_bParty_RootingMode = bMode;

	CHTString szMessage;
	// �ڵ� �й� ���
	if( m_bParty_RootingMode == HT_TRUE )
	{
		HT_vParty_SetMessage( eMsgPartyAutoRootingMode, &szMessage );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 1, szMessage );
	}
	// �Ϲ� �й� ���
	else
	{ 
		HT_vParty_SetMessage( eMsgPartyUsualRootingMode, &szMessage );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 1, szMessage );
	}
	if( szMessage.HT_bIsEmpty() == HT_FALSE )
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_PARTY, szMessage );
}

//----------��Ƽ ��� �����ֱ�----------//
HTvoid HTParty::HT_vParty_PartyMemberDiplay()
{
	CHTString strName;
	HTint i=0;

	//	���� ��Ƽ ��Ʈ�ѵ��� ���� �����ϰ�
	for( i=0 ; i<(PARTY_MAX_PERSON-1) ; i++ )
	{
		//	Button
		g_cUIManager->HT_DelButtonControl( _DIALOG_PARTYWND, 10+i );
		//	Member Name
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 10+i, _T("") );
		//	Member HP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		//	Member TP
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
	}

	for( i=0 ; i < m_Party_MemberCount; ++i )
	{
		strName = m_Party_Factor[i].Name;
		if( m_strParty_JangName.HT_iStringCompare( strName ) == 0 )
		{
			CHTString szMessage;
			HT_vParty_SetMessage( eMsgCommonPartyMaster, &szMessage );
			strName += szMessage;
		}

		//	UI Set
		m_byUIControlSet[i] = 1;
		//	Button
		g_cUIManager->HT_AddButtonControl( _DIALOG_PARTYWND, 10+i, 0, 0, 20+(i*28), 9, 0, 1500, 150, 13 );
		//	�̸� ����ֱ�
      	g_cUIManager->HT_SetTextLabelControl( _DIALOG_PARTYWND, 10+i, strName.HT_szGetString() );
		//	HP
		HTfloat xPos;
		if( m_Party_Factor[i].nCurHP==0 && m_Party_Factor[i].nMaxHP==0 )
			xPos = 1.0f;
		else
			xPos = (HTfloat)m_Party_Factor[i].nCurHP/(HTfloat)m_Party_Factor[i].nMaxHP;
		if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 10+i, (HTint)(xPos*150), 5 );
		if( m_Party_Factor[i].nCurHP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_FALSE );
		else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 10+i, HT_TRUE );
		//	TP
		if( m_Party_Factor[i].nCurTP==0 && m_Party_Factor[i].nMaxTP==0 )
			xPos = 1.0f;
		else
			xPos = (HTfloat)m_Party_Factor[i].nCurTP/(HTfloat)m_Party_Factor[i].nMaxTP;
		if( xPos <= 0.0f || xPos > 1.0f )	xPos = 1.0f;
		g_cUIManager->HT_SetTextureControlScale( _DIALOG_PARTYWND, 20+i, (HTint)(xPos*150), 5 );
		if( m_Party_Factor[i].nCurTP == 0 )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_FALSE );
		else									g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_PARTYWND, 20+i, HT_TRUE );
	}
	//	���� �缳��
	g_cUIManager->HT_SetMovingRegion( _DIALOG_PARTYWND, TRUE, 0,0, 190, 40+(m_Party_MemberCount*28) );
}

//--------------------------------------//
//			�̴���Ƽâ					//
//--------------------------------------//
//	��Ƽ �̴�â_����ġ
HTvoid HTParty::HT_vParty_SetWnd()
{
	if (!m_bParty_Exist) return;
	m_bMiniParty_WndSw = HT_TRUE;

	//	��Ƽâ �����
	g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );

	//	��Ƽ ��� �����ֱ�
	this->HT_vParty_PartyMemberDiplay();
    
}
HTvoid HTParty::HT_vParty_MiniPartyWndSetSw()
{
	if (!m_bParty_Exist) return;
	//	�̴���Ƽâ ����ġ
	if( m_bMiniParty_WndSw == HT_FALSE )
	{
		m_bMiniParty_WndSw = HT_TRUE;
		g_cUIManager->HT_ShowWindow( _DIALOG_PARTYWND );
		//	��Ƽ ��� �����ֱ�
		this->HT_vParty_PartyMemberDiplay();

		// �ڵ� �й� ���
		this->HT_bParty_SetRootingMode( m_bParty_RootingMode );
	}
	else
	{
		m_bMiniParty_WndSw = HT_FALSE;
		g_cUIManager->HT_HideWindow( _DIALOG_PARTYWND );
	}
}

//	Command Check_Party
HTvoid HTParty::HT_bParty_Command_Party()
{
	//	���� ���μ��� �������̾��ٸ� ��Ƽ���μ��� �ʱ�ȭ
	if( m_nParty_Send_Process == PARTY_PROCESS_REQJOINPARTY ||
		m_nParty_Send_Process == PARTY_PROCESS_PARTYCREATE )
	{
        m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
		return;
	}

	if( m_bParty_Exist )
	{
		//	�׳� ���� ��û
		m_nParty_Send_Process = PARTY_PROCESS_REQJOINPARTY;
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_PARTY_ANI);
	}
	else
	{
		//	��Ƽ â���ϸ鼭 ��û
		m_nParty_Send_Process = PARTY_PROCESS_PARTYCREATE;
		if( g_cInterfaceCheck->m_bUseWindowsCursor == HT_FALSE )
			g_cInterfaceCheck->HT_vSetCursor(CURSOR_PARTY_ANI);
	}
}
//	Command Check_PartyWithDraw
HTvoid HTParty::HT_bParty_Command_PartyWithDraw()
{
	this->HT_vParty_PartyLeave();
}

//----------��Ƽ ������� Ŭ���ߴ°�?----------//
HTbool HTParty::HT_bParty_MemberClick( HTint iBtnNo )
{
	HTbool bMemClick = HT_TRUE;
	m_nParty_Send_Process = PARTY_PROCESS_ERRORMESSAGE;
	m_party_DeleteMember = iBtnNo - 10;

	///	�ӼӸ� ���·� ����� �ְ�..
	//CHTString strMyName = g_oMainCharacterInfo.szCharName;
	//if( strMyName.HT_iStringCompare( m_Party_Factor[m_party_DeleteMember].Name ) != 0 )
 //       g_cChatting->HT_vChatting_SetWisper( m_Party_Factor[m_party_DeleteMember].Name );

	if (!strcmp(m_Party_Factor[m_party_DeleteMember].Name, _T(""))) bMemClick = HT_FALSE;

	//	��ü ����Ī �̴� ó��
	g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
	//	��ó��
	m_szCharacterName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( m_Party_Factor[m_party_DeleteMember].nID );
	HTint iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_Party_Factor[m_party_DeleteMember].nID );
	g_cOtherObjectSystem->HT_iOtherObjectSystem_SRPickIDCheck( iObjectID );
	g_cMainCharacter->HT_vMainChar_SetAttackStatus( m_Party_Factor[m_party_DeleteMember].nID, iObjectID, HT_FALSE );
	bMemClick = HT_FALSE;
	return bMemClick;
}

HTvoid HTParty::HT_vParty_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vParty_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vParty_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vParty_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vParty_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid HTParty::HT_vParty_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// �ٸ� ĳ���� �̸�
		case eMsgParamOthercharName	:
			*pszParam = m_szCharacterName; break;
		// ��Ƽ�� �̸�
		case eMsgParamPartyLeaderName :
			*pszParam = m_strParty_JangName; break;

		default:
			break;
	}
}

