#pragma once

#define _GOING_PORTAL_NUM	5
class HTPortal
{
public:
	HTPortal(void);
	~HTPortal(void);
    
	//	포탈 초기화
	HTvoid			HT_vPortal_Init();
	//	Create Window
	HTvoid			HT_vPortal_CreateWindow();
	//	입력함수 처리 포탈
	static void		HT_vPortal_InputCheckPortal(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 Jiva Pustica
	static void		HT_vPortal_InputCheckJivaPustica(int iAction, int iTarget, int iTargetID);
	//	입력함수 처리 Upgrade Jiva Pustica
	static void		HT_vPortal_InputCheckUpgradeJivaPustica(int iAction, int iTarget, int iTargetID);

	//	포탈 클릭
	HTRESULT		HT_vPortal_Click( HTint iPortalObj, HTvector3 vecPickPos );
	//	포탈 창 닫기
	HTvoid			HT_vPotal_AntiActive();
	//	ESC Key 누르면 창 닫기
	HTvoid			HT_vPotal_ESC_CloseWindow();
	//	캐릭터 위치체크_캐릭터 움직이면 다운시킨다
	HTvoid			HT_vPortal_CharPos_Check();
	//	향상된 이동의 지바 푸스티카 Dlg
	HTvoid			HT_vPortal_ImprovementMovePustica();
	// 차투랑가 입장권 사용시 패킷 전송 함수
	HTvoid			HT_vPortal_Chaturanga_Enter();
	
	//	테크워크
	//	서버에 포탈 요청하기
	HTvoid			HT_vPortal_Network_ReqPortal();
	//	서버에 포탈 요청에 대한 응답 받기 -> 전부 에러 메시지 일것임
	HTvoid			HT_vPortal_Network_SCP_Resp_Portal( PS_SCP_RESP_MOVE_PORTAL info );
	//	서버에 칼라코어 등록 요청하기
	HTvoid			HT_vPortal_RegisterKalaCore( HTint iObjNo );
	//	_MSG_Item
	HTvoid			HT_vPortal_NetWork_CSP_MSG_Item( HTint iIndex );
	//	_MSG_MoveOtherZone
	HTvoid			HT_vPortal_NetWork_SCP_MSG_MoveOtherZone( MSG_MoveOtherZone* info );
	//	MSG_Warp
	HTvoid			HT_vPortal_NetWork_SCP_Msg_Warp( MSG_Warp* info );


	//	동접체크해오기
	HTint			HT_iPortal_GetConnectNum( HTint iGroup, HTint iConnectZone );

	//	Data Setting for MSG_Item
	HTvoid			HT_vPortal_SetDataForMsgItem( HTbyte byPlace, HTbyte byIndex, HTint iItemID );

	//	Set Portress Pustica
	HTvoid			HT_vPortal_SetPortressPustica( HTbyte byPlace, HTbyte byIndex );
	//	Set Siege Pustica
	HTvoid			HT_vPortal_SetSiegePustica( HTbyte byPlace, HTbyte byIndex );
	
private:
	HTvoid			HT_vPortal_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid			HT_vPortal_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool			m_bPotal_Sw;

	//	1차지역으로 가려할때 나누어진 서버를 검색하기 위한장치
	HTbool			m_bPortal_FirstZoneSw;
	HTint			m_iPortal_FirstZoneIndex;

	//HTint			m_nPotal_Count;
	//HTint			m_nPotal_Connect;

	HTint			m_nPotal_SelectIndex;
	//	포탈 클릭했을때 캐릭터 위치 기억
	HTPoint			m_pCharpos_Memory;

	//	Data Setting for MSG_Item
	HTbyte			m_byPlace_ForMsgItem;
	HTbyte			m_byIndex_ForMsgItem;

private:
	HTint			m_iGoingPortal[_GOING_PORTAL_NUM];
	HTdword			m_dwFee[_GOING_PORTAL_NUM];
	HTdword			m_dwLevel[_GOING_PORTAL_NUM];
	//	포탈 ID
	HTint			m_iPortal_StartPortalID;
	HTint			m_iPortal_TargetPortalID;
	//	대화상자 스위칭 변수
	HTbool			m_bPortal_ReDialogBoxActiveSw;

	//	메세지 출력용
	HTdword			m_dwMessageVal;

	//	 향샹된 이동의 지바 푸스티카 대화상자의 페이지
	HTint			m_iPortal_ImprovmentPusticaPage;
	//	JivaPustica For Three Mandara vilige
	HTint			m_iPortal_JiPusticaForMantraIndex;
	//	for compare Portal item id
	HTint			m_iPotral_PortalMoveItemID;
	//	주신 던젼을 위한 셀렉트된던젼번호
	HTint			m_iTirmuritiCaveNo;
	//	만다라 마을이 여러개 떠있을경우에 저장
	HTint			m_iSaveSelectUpgradeJPNo;
};
