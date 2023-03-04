//////////////////////////////////////////////////////////////////////////////////////////
// 설명 : 아이템, 스킬 정보창 관련
// 
// 작성자 : 김선미
//
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTOBJECTINFO_H__
#define __HTOBJECTINFO_H__

#include "HTControlDef.h"

typedef enum 
{ 
	eInfo_Character = 1, 
	eInfo_Monster,
	eInfo_NPC,
	eInfo_Item,
	eInfo_Item_Economy,
	eInfo_Item_Work,
	eInfo_Item_Fix,
	eInfo_Item_Disjoint,
	eInfo_Item_Store_Sell,
	eInfo_Item_Store_Buy,
	eInfo_Skill,
	eInfo_MainCheck,
	eInfo_ART,			// 메인바의 Address, Run, Trade
	eInfo_QuickSlotCommand,	// 퀵슬롯창의 명령어
	eInfo_QuickSlot,
	eInfo_None,
	eInfo_Item_RentalStore
} eInfoType;

#define INFODATA_POSX 10
#define INFODATA_POSY 10

class HTObjectInfo
{
public:
	HTObjectInfo(void); 
	~HTObjectInfo(void);
	
	//	변수 초기화, 그림 로딩
	HTvoid		HT_vObjectInfo_Init();

	//	마우스 포인트를 체크
	HTvoid		HT_vObjectInfo_MousePtCheck( HTPoint pPt);
	HTvoid		HT_vObjectInfo_InfoCheck(unsigned int iIndex, unsigned int iCIndex );

	//	정보창을 활성화 시켜줌
	HTvoid		HT_vObjectInfo_Active( HTPoint pPt);
	//	정보창을 비활성화 시켜줌
	HTvoid		HT_vObjectInfo_AntiActive();

	//	전체 텍스트 랜더 컨트롤
	HTvoid		HT_vObjectInfo_SetInfoText();

	// 데이터 모두 지우기
	HTvoid		HT_vObjectInfo_DeleteAll();

	HTbool		HT_bObjectInfo_IsActive()	{ return m_bInfoWinImageSw; }
	HTvoid		HT_vObjectInfo_Active_NPC(int iObjID);

	unsigned int		nWindowIndex;
	unsigned int		nControlIndex;
private:
	HTvector3			m_pInfoPos;			// 정보창 시작 위치
	HTbool				m_bInfoWinImageSw;	// 정보창이 활성화 되었는지
	HTint				m_iInfoWinImageID;	// 정보창 이미지 아이디
	HTint				m_iRenderType;		
	DWORD				m_dwObjectKeyID;	// 인벤토리에 있는 아이템 정보를 위해
	DWORD				m_dwObjectModelID;	// 몬스터나 캐릭터의 정보를 위해
	HTint				m_iEconomy_ItemIndex;//제조창의 아이템 정보를 위해

	HT_ITEMINFO				m_stItemInfo;			// 정보창에 나타낼 데이터
	vector<HT_ITEM_DATA*>	m_vFixDisjointInfo;	// 수리/해체
	HTbool					m_bFixDisjointPossible;	// 수리/해체 가능한지(커서 변경을 위해서)
	vector<HT_ITEM_DATA*>	m_vSkillNextInfo;
	HT_ITEMINFO				m_stSkillInfo;
	CHTString			m_szName;			// 캐릭터/몬스터의 이름
	CHTString			m_szNeedPrana;		// 차크라포인트/브라만포인트를 올리기위해 필요한 프라나양
	HTint				m_nLocation;		// 아이템 위치. trade창으로 언패킹된 아이템 때문에..
											// (언패킹 전상태라 KeyID는 기존의 것을 사용한다.) 

	HTPoint				m_ptWinSize;		// 정보창 크기
};

#endif