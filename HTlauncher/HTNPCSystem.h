
#ifndef __HTNPCSYSTEM_H__
#define __HTNPCSYSTEM_H__

#include "HTNPC.h"

#define NPC_DISTANCE_LIMIT		6	// NPC 반응 거리 제한
#define MAX_SELECT_COUNT		10	// 선택문 최대 개수

#define DIALOG_WIN_POSX			10
#define DIALOG_WIN_POSY			140 

//----------NPC LL 구현을 위한 구조체----------//
typedef struct _HT_NPC_NODE
{
	HTNPC							sNPC;
	struct _HT_NPC_NODE				*next;

} HT_NPC_NODE;

//class HTNPCScriptMgr;
//----------NPC 전체 시스템과 LL을 실제 구현----------//
class HTNPCSystem
{
public:
	HTNPCSystem();
	~HTNPCSystem();
	HTvoid					HT_vNPCSystem_CleanUp();

	HTRESULT				HT_hNPCSystemInit();
	HTvoid					HT_vNPCSystemControl();

	//-------현재 Zone에 있는 NPC 생성--------//
	HTvoid					HT_vNPCSystem_CreateNPC();

	HTint					HT_vNPCSystemCheckMapCell( HTint, HTint );	//지정한 맵셀위에 NPC가 있는가?

	//----------NPC를 픽 했을 때---------//
	HTint					HT_vNPCSystemComIDCheck( HTint iID );
	//----------NPC 정보창 초기화---------//
	HTvoid					HT_vNPCSystem_HPWindowInit();
	//----------NPC 전부 클리어---------//
	HTvoid					HT_vNPCSystem_TotalNPCDelete();

	//---------- 특정 NPC 지우기 -------------//
	HTbool					HT_bNPCSystem_DeleteNPC( DWORD dwNPCKeyID );
	// 특정 NPC 만들기
	HTbool					HT_bNPCSystem_CreateNPC(HTint iNPCIndex);

	//----------반환 / 셋팅값 들----------//
	HTvoid					HT_vNPCSystem_AntiActiveNPC();
	DWORD					HT_pNPCSystem_GetIndexFromModelID( HTint );
	HTPoint					HT_pNPCSystem_GetCellPosFromIndex( DWORD );
	HTvector3				HT_vNPCSystem_GetCoordFromModelID( DWORD dwID );

	HTvoid					HT_vNPCSystem_GetName(DWORD dwIndex, CHTString& szName);	// 이름
	HTvoid					HT_vNPCSystem_GetNameForModelID(DWORD dwModelID, CHTString& szName);
	//HTint					HT_nNPCSystem_GetGroupbyFamily(DWORD dwKeyID);				// NPC 계통 획득
	DWORD					HT_dwNPCSystem_GetActiveNPCIndex() { return m_dwActiveNPCID; };// 현재 활성화 되어있는 NPC KeyID
	//---------현재 타겟창에 정보가 보여지고 있는 NPC 모델 ID 반환-------------//
	DWORD					HT_vNPCSystem_GetTargetModelID();
	//	Returns Get	bCheck2ObjCollide
	HTint					HT_iNPCSystem_GetCheck2ObjCollide( HTint iKeyID, HTvector3 vecMainCharPos, HTfloat ColidSize );

	//------------친밀도 계산 - NPC 계통별 친밀도+브라만 포인트-------------//
	HTvoid					HT_vNPCSystem_CalNPCRelative(/*HTint nGroupbyFamily,*/ HTint& nTotalPoint, HTint& nSection);
	//----------픽된 NPC를 기능별로 연결----------//
	HTvoid					HT_pNPCSystem_PickConnect( HTint );

	//	Set
	//	Set Chat Msg
	HTvoid					HT_vNPCSystem_SetChatMsg( HTint iID, CHTString strMessage );

	//----------랜더----------//
	HTvoid					HT_vNPCSystemRender();
	//----------랜더_이름----------//
	HTvoid					HT_vNPCSystem_RenderName( HT_NPC_NODE* t );
	//	Render MiniMap Point
	HTvoid					HT_vNPCSystem_MiniMapPoint();

	//----------------------------------------------------//
	//---------------------서버 관련----------------------//
	//----------------------------------------------------//
	//----------NPC 친밀도 상승을 요청한다----------//
	//HTvoid					HT_CSP_REQ_NPC_POINT_UP( DWORD );
	//----------NPC 친밀도 상승을 요청한다_결과----------//
	//HTvoid					HT_SCP_REQ_NPC_POINT_UP_Result( PS_SCP_RESP_NPC_POINT_UP info );

	//-----------퀘스트 진행 상태를 알려준다-----------//
	HTvoid		HT_vNetWork_CSP_Req_Quest_Notify_Level( );
	HTvoid		HT_vNetWork_SCP_RESP_Quest_Notify_Level(PS_SCP_QUEST_NOTIFY_LEVEL info);
	
	//-----------현재 활성화된 NPC를 기준으로 퀘스트 진행 상태 설정-----------//
	HTvoid		HT_vNPCSystem_SetLastQuestStatus(BYTE byQuestIndex, BYTE byLevel, BYTE byLevelTime = 1);
	//-----------시나리오 퀘스트의 다음 진행 상태 설정-----------//
	HTvoid		HT_vNPCSystem_SetNextQuestStatus();

	//-----------현재 진행되고 있는 퀘스트 번호를 얻어온다--------//
	BYTE		HT_byNPCSystem_GetLastQuestIndex() 	{	return m_byQuestIndex; 	}
	//-------현재 활성화된 NPC를 기준으로 퀘스트 진행 상태를 얻어온다--------//
	BYTE		HT_byNPCSystem_GetLastQuestLevel() 	{	return m_byLevel; 	}
	BYTE		HT_byNPCSystem_GetLastQuestLevelTime() 	{	return m_byLevel_Time; 	}

private:
	HTvoid					HT_LL_vInitList();
	HTbool					HT_LL_bDeleteNode( int );
	HTvoid					HT_LL_hrDeleteAll();
	HTRESULT				HT_LL_hrInsertAfter( HTint iNPCIndex, short snX, short snZ );

public:
	HTint					m_iNPC_Count;
	//CHTString				m_RelativeStr[11];	// 친밀도에 따른 문장

	//----------OtherChar 정보 표시위해----------//
	HTbool					m_bNPC_Info_Sw;


	HT_NPC_NODE*			m_sNPCHead;
	HT_NPC_NODE*			m_sNPCTail;
	DWORD					m_dwActiveNPCID;	// 현재 선택한 NPC의 KeyID. 포인트 상승 요구후 결과를 처리하기 위해..

	//-----Quest--------//
	BYTE					m_byQuestIndex;
	BYTE					m_byLevel;
	BYTE					m_byLevel_Time;	// 시나리오퀘스트용. Level의 조건. 예)1차 or 2차 진행
};

#endif

