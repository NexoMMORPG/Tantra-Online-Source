#pragma once

#define PARTY_MAX_PERSON					8
#define PARTY_MAX_PERSON_HPBAR				8

#define PARTY_PROCESS_PARTYCREATE			0
#define PARTY_PROCESS_PARTYLEAVE			1
#define PARTY_PROCESS_PARTYDELETE			2
#define PARTY_PROCESS_PARTYMEMBERDELETE		3
#define PARTY_PROCESS_REQJOINPARTY			4
#define PARTY_PROCESS_RECIVEDJOINPARTY		5
#define PARTY_PROCESS_ERRORMESSAGE			6

class HTParty
{
public:
	HTParty(void);
	~HTParty(void);
	HTvoid				HT_vParty_CleanUp();

	HTvoid				HT_vParty_Init();
	//	Create Window
	HTvoid				HT_vParty_CreateWindow();
	//	�Է� �޼��� ó��
	//	Party
	static void			HT_vParty_InputCheckForParty(int iAction, int iTarget, int iTargetID);

	HTbool				HT_bParty_GetActiveSw()	{ return m_nParty_WindowActiveSw; };
	
	// ��Ƽ ������� Ŭ���ߴ°�?
	HTbool				HT_bParty_MemberClick( HTint iBtnNo );
	//------------------------------------------------
	// â üũ
	//------------------------------------------------
	// ��Ȯ��â
	HTRESULT 			HT_vParty_ReDialogBoxCheck( HTint iProp, HTint iInductNo, HTint iButtonNo );
	
	//	ESC Key ������ ��Ƽâ �ݱ�
	HTvoid				HT_vParty_ESC_CloseWindow();

	//------------------------------------------------
	// ��Ƽ ����
	//------------------------------------------------
	// ��Ƽ Ż��
	HTvoid				HT_vParty_PartyLeave();
	// ��Ƽ ���� ��û
	HTRESULT			HT_vParty_JoinParty( HTint );
	// ��Ƽ ������ �ʱ�ȭ 
	HTvoid				HT_vParty_InitMember();
	// ���ο� ��� �߰��ϱ� 
	HTvoid				HT_vParty_InsertMember( S_PARTY info );
	// ���� ��� �����ϱ� 
	HTvoid				HT_vParty_DeleteMember( CHTString strTemp );
	// ��Ƽ ���� 
	HTvoid				HT_vParty_DISBAND();
	// �ܺο��� ��Ƽ ��ü �� Ż�� 
	HTvoid				HT_vParty_OutSideRequest_LogOut();

	// ��Ƽ ��� �����ֱ�
	HTvoid				HT_vParty_PartyMemberDiplay();

	HTbool				HT_bParty_IsClickJoinBn();

	//------------------------------------------------
	// ��Ƽ ���� ����
	//------------------------------------------------
	// ��Ƽ������ �˻�
	HTbool				HT_bParty_IsPartyMember( CHTString strName );
	HTbool				HT_bPArty_IsPartyMember( DWORD dwCharKeyID );
	// ��Ƽ������ �˻�
	HTbool				HT_bParty_IsPartyJang( DWORD dwCharKeyID );

	// �ڵ��й� ���
	HTvoid				HT_bParty_SetRootingMode( HTbool bMode );
	HTbool				HT_bParty_GetRootingMode() { return m_bParty_RootingMode; }

	//	��Ƽ�� ��
	HTint				HT_iParty_GetPartyMemberCount() { return m_Party_MemberCount; }
	//	��Ƽ�� �̸� ��ȯ
	CHTString			HT_szParty_GetPartyMemberName( HTdword dwCharKeyID );
	//	��Ƽ�� ���̵� ��ȯ
	HTvoid				HT_vParty_GetPartyMemberKeyID( HTint* iMember, HTfloat fRange );

	//-----------------------------------------------
	// �̴���Ƽâ
	//-----------------------------------------------
	//	��Ƽ �̴�â_����ġ
	HTvoid				HT_vParty_SetWnd();
    HTvoid				HT_vParty_MiniPartyWndSetSw();

	//	Command Check_Party
    HTvoid				HT_bParty_Command_Party();
	//	Command Check_PartyWithDraw
    HTvoid				HT_bParty_Command_PartyWithDraw();

	//------------------------------------------------
	// ��Ʈ��ũ ���� �Լ�
	//------------------------------------------------
	//			0x16 Group(Party/Guild/�ּҷ�)	101
	// ��Ƽ ����
	HTvoid				HT_vNetWork_CSP_CREATEJOIN_PARTY();
	HTvoid				HT_vNetWork_SCP_CREATEJOIN_PARTY( MSG_REQParty* );
	// ���� ��Ƽ
	HTvoid				HT_vNetWork_CSP_CNF_PARTY();
	// ��Ƽ�� �߰�
	HTvoid				HT_vNetWork_SCP_MSG_AddParty( MSG_AddParty* );
	// ���� ����Ÿ �����ϱ�
	HTvoid				HT_vNetWork_SCP_MSG_UpdateParty( PS_SCP_RESP_UPDATE_PARTY );
	// ��Ƽ Ż��/��ü
	HTvoid				HT_vNetWork_CSP_MSG_RemoveParty( HTint iTarget );
	HTvoid				HT_vNetWork_SCP_MSG_RemoveParty( MSG_RemoveParty* );
	// �ڵ��й� ���
	HTvoid				HT_vNetWork_CSP_Req_Set_Party( HTbool bRootingMode );
	HTvoid				HT_vNetWork_SCP_Resp_Set_Party( MSG_SetParty* info );
private:
	// �޼��� ���
	HTvoid				HT_vParty_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid				HT_vParty_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:

	HTint						m_Party_MemberCount; // �ڽ��� ������ ������ ��Ƽ���� ��

	//---------��Ƽ�� �����Ǿ� �ְų� �����ߴ°�?---------//
	HTbool						m_bParty_Exist;
	BYTE						m_party_DeleteMember;

	//---------��Ƽ��/�ּҷ� �׸�---------//
	S_PARTY						m_Party_Factor[PARTY_MAX_PERSON-1];	//	0:��Ƽ��,1:��Ƽ��...
																	// �ڽ��� �����ϰ� �����ϱ� ������ -1�� �Ѵ�
	
	// �ڵ��й� ���
	HTbool						m_bParty_RootingMode;

	//---------���� ��Ƽ���̳�?---------//
	HTbool						m_Party_Jang;
	DWORD						m_dwParty_JangKeyID;
	CHTString					m_strParty_JangName;

	//---------��Ƽ ������ Ȱ��ȭ---------//
	HTbool						m_nParty_WindowActiveSw;
	//---------��ȭ���� Ȱ��ȭ---------//
	HTbool						m_nParty_DialogBoxActiveSw;
	HTbool						m_nParty_ReDialogBoxActiveSw;

	//---------��ȭ���ڿ� �ѷ��� ����---------//
	CHTString					m_strDialogBoxMessage;

	//----------��Ƽ ����----------//
	HTint						m_nParty_Send_Process;
	HTint						m_nParty_Receive_Process;

	//----------��Ƽ ��ü �ο�----------//
	HTint						m_nParty_TotalCount;

	//----------��Ƽ ���� ��û----------//
	HTbool						m_bParty_JoinParty;
	DWORD						m_dwParty_JoinPartyKeyID;

	HTbool						m_bLoaded;

	//--------------------------------------//
	//			�̴���Ƽâ					//
	//--------------------------------------//
	HTbool						m_bMiniParty_WndSw;

	//	UI ��Ʈ���� �����߳� ���޳�?
	HTbyte						m_byUIControlSet[PARTY_MAX_PERSON-1];
	
	// �޼����� ����� ����
	CHTString					m_szCharacterName;
};



