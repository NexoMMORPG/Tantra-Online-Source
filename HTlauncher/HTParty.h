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
	//	입력 메세지 처리
	//	Party
	static void			HT_vParty_InputCheckForParty(int iAction, int iTarget, int iTargetID);

	HTbool				HT_bParty_GetActiveSw()	{ return m_nParty_WindowActiveSw; };
	
	// 파티 멤버들을 클릭했는가?
	HTbool				HT_bParty_MemberClick( HTint iBtnNo );
	//------------------------------------------------
	// 창 체크
	//------------------------------------------------
	// 재확인창
	HTRESULT 			HT_vParty_ReDialogBoxCheck( HTint iProp, HTint iInductNo, HTint iButtonNo );
	
	//	ESC Key 누르면 파티창 닫기
	HTvoid				HT_vParty_ESC_CloseWindow();

	//------------------------------------------------
	// 파티 관리
	//------------------------------------------------
	// 파티 탈퇴
	HTvoid				HT_vParty_PartyLeave();
	// 파티 참여 요청
	HTRESULT			HT_vParty_JoinParty( HTint );
	// 파티 구성원 초기화 
	HTvoid				HT_vParty_InitMember();
	// 새로운 멤버 추가하기 
	HTvoid				HT_vParty_InsertMember( S_PARTY info );
	// 기존 멤버 삭제하기 
	HTvoid				HT_vParty_DeleteMember( CHTString strTemp );
	// 파티 해제 
	HTvoid				HT_vParty_DISBAND();
	// 외부에서 파티 해체 및 탈퇴 
	HTvoid				HT_vParty_OutSideRequest_LogOut();

	// 파티 멤버 보여주기
	HTvoid				HT_vParty_PartyMemberDiplay();

	HTbool				HT_bParty_IsClickJoinBn();

	//------------------------------------------------
	// 파티 관련 정보
	//------------------------------------------------
	// 파티원인지 검사
	HTbool				HT_bParty_IsPartyMember( CHTString strName );
	HTbool				HT_bPArty_IsPartyMember( DWORD dwCharKeyID );
	// 파티장인지 검사
	HTbool				HT_bParty_IsPartyJang( DWORD dwCharKeyID );

	// 자동분배 모드
	HTvoid				HT_bParty_SetRootingMode( HTbool bMode );
	HTbool				HT_bParty_GetRootingMode() { return m_bParty_RootingMode; }

	//	파티원 수
	HTint				HT_iParty_GetPartyMemberCount() { return m_Party_MemberCount; }
	//	파티원 이름 반환
	CHTString			HT_szParty_GetPartyMemberName( HTdword dwCharKeyID );
	//	파티원 아이디 반환
	HTvoid				HT_vParty_GetPartyMemberKeyID( HTint* iMember, HTfloat fRange );

	//-----------------------------------------------
	// 미니파티창
	//-----------------------------------------------
	//	파티 미니창_스위치
	HTvoid				HT_vParty_SetWnd();
    HTvoid				HT_vParty_MiniPartyWndSetSw();

	//	Command Check_Party
    HTvoid				HT_bParty_Command_Party();
	//	Command Check_PartyWithDraw
    HTvoid				HT_bParty_Command_PartyWithDraw();

	//------------------------------------------------
	// 네트워크 관련 함수
	//------------------------------------------------
	//			0x16 Group(Party/Guild/주소록)	101
	// 파티 생성
	HTvoid				HT_vNetWork_CSP_CREATEJOIN_PARTY();
	HTvoid				HT_vNetWork_SCP_CREATEJOIN_PARTY( MSG_REQParty* );
	// 컨펌 파티
	HTvoid				HT_vNetWork_CSP_CNF_PARTY();
	// 파티원 추가
	HTvoid				HT_vNetWork_SCP_MSG_AddParty( MSG_AddParty* );
	// 기존 데이타 변경하기
	HTvoid				HT_vNetWork_SCP_MSG_UpdateParty( PS_SCP_RESP_UPDATE_PARTY );
	// 파티 탈퇴/해체
	HTvoid				HT_vNetWork_CSP_MSG_RemoveParty( HTint iTarget );
	HTvoid				HT_vNetWork_SCP_MSG_RemoveParty( MSG_RemoveParty* );
	// 자동분배 모드
	HTvoid				HT_vNetWork_CSP_Req_Set_Party( HTbool bRootingMode );
	HTvoid				HT_vNetWork_SCP_Resp_Set_Party( MSG_SetParty* info );
private:
	// 메세지 출력
	HTvoid				HT_vParty_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid				HT_vParty_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:

	HTint						m_Party_MemberCount; // 자신을 제외한 나머지 파티원의 수

	//---------파티가 생성되어 있거나 가입했는가?---------//
	HTbool						m_bParty_Exist;
	BYTE						m_party_DeleteMember;

	//---------파티원/주소록 항목---------//
	S_PARTY						m_Party_Factor[PARTY_MAX_PERSON-1];	//	0:파티장,1:파티원...
																	// 자신을 제외하고 저장하기 때문에 -1을 한다
	
	// 자동분배 모드
	HTbool						m_bParty_RootingMode;

	//---------내가 파티장이냐?---------//
	HTbool						m_Party_Jang;
	DWORD						m_dwParty_JangKeyID;
	CHTString					m_strParty_JangName;

	//---------파티 윈도우 활성화---------//
	HTbool						m_nParty_WindowActiveSw;
	//---------대화상자 활성화---------//
	HTbool						m_nParty_DialogBoxActiveSw;
	HTbool						m_nParty_ReDialogBoxActiveSw;

	//---------대화상자에 뿌려줄 내용---------//
	CHTString					m_strDialogBoxMessage;

	//----------파티 절차----------//
	HTint						m_nParty_Send_Process;
	HTint						m_nParty_Receive_Process;

	//----------파티 전체 인원----------//
	HTint						m_nParty_TotalCount;

	//----------파티 참여 요청----------//
	HTbool						m_bParty_JoinParty;
	DWORD						m_dwParty_JoinPartyKeyID;

	HTbool						m_bLoaded;

	//--------------------------------------//
	//			미니파티창					//
	//--------------------------------------//
	HTbool						m_bMiniParty_WndSw;

	//	UI 컨트롤을 생셩했냐 안햇냐?
	HTbyte						m_byUIControlSet[PARTY_MAX_PERSON-1];
	
	// 메세지에 출력할 내용
	CHTString					m_szCharacterName;
};



