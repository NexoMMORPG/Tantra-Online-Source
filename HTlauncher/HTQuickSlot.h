#pragma once

#define QUICKSLOT_MODE

//#define QUICKSLOT_STARTHIGHTTERM	1
#define QUICKSLOT_SIDECOUNT			5
#define QUICKSLOT_HIGHT				10

typedef struct HTQuickSlotInfo
{
	HTint				iIndex;
	HTint				iKeyID;
	HTint				iInvenIndex;
} HTQuickSlotInfo;

class HTQuickSlot
{
public:
	HTQuickSlot(void);
	~HTQuickSlot(void);

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vInit()
	// D : 퀵슬롯 메모리 초기화
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vInit();	

	//	Create Window
    HTvoid			HT_vQuick_CreateWindow();

	//	명령_입력함수 처리
	static void		HT_vQuick_InputCheckHQuickSlot(int iAction, int iTarget, int iTargetID);

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vIconSave()
	// D : 퀵슬롯에 등록되어 있는 아이콘을 저장하여 다음 로그인 때 사용할 수 있도록 한다.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vIconSave();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vIconLoad()
	// D : 저장된 아이콘 정보를 로드한다.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vIconLoad();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vDeleteIconByIndex( HTdword dwIndex, HTint iKeyID )
	// D : 퀵슬롯에 아이콘 삭제
	// I : dwIndex - 인덱스, iKeyID - 키 아이디
	//-------------------------------------------------------------------------------------------
	HTbool			HT_vDeleteIconInResentSlotByIndex( HTdword dwIndex, HTint iKeyID );
	HTvoid			HT_vDeleteIconInAllSlotByIndex( HTdword dwIndex, HTint iKeyID );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
	// D : 아이콘 삭제
	// I : iSideNo - 퀵바번호, iCellNo - 셀 번호
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vTotalDeleteIcon()
	// D : 아이콘 전부삭제
	// I : 
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vTotalDeleteIcon( HTint iType );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vTotalCoolTimeinit()
	// D : 현재 돌아가고 있는 쿨타임들 전부 초기화
	// I : 
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vTotalCoolTimeInit();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vSetSide( HTint iType )
	// D : 몇번째 퀵슬롯을 보여줄 것인가 결정한다.
	// I : iType - 보여줄 퀵슬롯 ( 100:--, 101:++, 기타:퀵슬롯 번호 )
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vSetSide( HTint iType );	
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_OnRButtonUp( HTPoint pPt, HTint iDlgNo )
	// D : 퀵바 안의 내용 지우기
	// I : pPt - 마우스 좌표, iDlgNo - 다이알로그 번호
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_OnRButtonUp( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
	// D : 쿨다임 설정
	//-------------------------------------------------------------------------------------------
	HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vActionItem( HTint iSlotNo)
	// D : 슬롯에 있는 아이템 사용
	// I : iSlotNo - 슬롯 번호
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vActionItem( HTint iSlotNo);
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vAction( HTint iSlotNo )
	// D : 슬롯에 설정된 기능을 사용
	// I : iSlotNo - 슬롯 번호
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vAction( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID )
	// D : 등록되어 있는 키아이디 변경
	// I : dwOldKeyID - 이전 키 아이디, dwNewKeyID - 새로운 키 아이디
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID );

	//===========================================================================================
	// Action에 따른 결과
	//===========================================================================================
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vResultActionItem( HTdword dwKeyID )
	// D : 아이템 사용의 결과
	// I : dwKeyID - 키아이디
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vResultActionItem( HTdword dwKeyID );
	//===========================================================================================
	
    //	퀵 슬롯 창 체크_마우스 왼쪽 버튼
	HTvoid			HT_vQuickSlot_DlgCheck_LButton( HTPoint pPt, HTbool bVer = HT_TRUE );

	// 슬롯에 등록되어있는 아이템의 KeyID 정보를 갱신한다.
	HTvoid			HT_vQuickSlot_RenewalSlotItemKeyID();
	//-------------------------------------------------------
	//		네트워크 함수
	//-------------------------------------------------------
	//	서버에서 퀵스롯에 등록 요청
	HTvoid			HT_vQuickSlot_ReqRegisterQuickSlot();
	//	서버에서 퀵스롯에 등록 요청_결과
	HTvoid			HT_vQuickSlot_ReqRegisterQuickSlot_Result();

	//------------------------------------------------------
	//		반환값들
	//------------------------------------------------------
	//	슬롯에 정보를 셋팅
	HTvoid			HT_bQuickSlot_SetSlot( HTint iType, HTint iIndexID, HTint iSlotNo );
	//	슬롯에 등록된 스킬/아이템이 있는지 
	//HTbool			HT_bQuickSlot_GetSlot( HTint );
	
	
	//	해당 슬롯에 위치한 아이템의 KeyID나 스킬의 Index를 넘겨준다
	HTvoid			HT_vQuickSlot_GetKeyIDInSlot( HTint iSlotNo, HTint *piKeyID, HTbyte *pbyType );

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
	// D : 키아이디가 사용되고 있는지 체크
	// I : dwIndex - 인덱스, dwKeyID - 키아이디
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID );

	//-------------------------------------------------------------------------------------------
	// HTvoid		HT_hrContinueTimeCheck()
	// D : 지속시간이 설정된 아이템들 체크
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vContinueTimeCheck();

private:
	//-------------------------------------------------------------------------
	// HTbool			HT_bBeUsedSlot( HTint iSlotNo )
	// D : 슬롯이 사용되고 있는지 
	//-------------------------------------------------------------------------
	HTbool			HT_bBeUsedSlot( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vSetAllIcon()
	// D : 모든 아이콘을 정보에 따라 재설정한다.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vSetAllIcon();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID )
	// D : 퀵슬롯에 아이콘 붙이기
	// I : iDlgNo - 다이알로그 번호, iType - 타입(-2 : 명령, 0 : 스킬, ELSE : UI ITEM), 
	//		iCellNo - 퀵슬롯 번호, iIndexID - 아이콘의 인덱스
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID );
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vActionskill( HTint iSlotNo)
	// D : 슬롯에 있는 스킬사용
	// I : iSlotNo - 슬롯 번호
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vActionskill( HTint iSlotNo);

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bBeUsedKey( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
	// D : 현재 등록되어 있는 키인지 체크하고, 등록되어 있는 Side와 슬롯 번호를 얻음
	// I : dwKeyID - 키아이디
	// R : piSlotSide - 퀵바의 번호, piSlotNo - 슬롯 번호
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo );

	//-------------------------------------------------------------------------------------------
	//	HTRESULT		HT_hrIsCoolTimeOver()
	// D : 현재 실행하려는 퀵스킬 등록 아이콘의 쿨타임체크
	// R : HT_OK - 쿨타임 초과 ( 사용할 수 있음 )
	//		HT_FAIL - 쿨타임 미초과 ( 사용할 수 없음 )
	//-------------------------------------------------------------------------------------------
	HTRESULT		HT_hrIsCoolTimeOver();

public:
	HTbool			m_bVerSlot;
	HTint			m_iSide;

private:
	HTint			m_iPrevSide;
	
	HTfloat			m_fQuickSlot_CoolTime[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];
	HTdword			m_dwQuickSlot_StartTimeCoolTime[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];
	HTQuickSlotInfo m_sQuickSlotInfo[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT]; // 퀵슬롯에 등록된 스킬/아이템 정보
	HTbool			m_bQuickSlot_ContinueSw[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];		//	지속아이템의 사용 유무

	HTint			m_iType;
	HTint			m_iSlotNo;
	HTint			m_iIndexID;
	//	다른 슬롯에서 넘어오는 텍스쳐 아이디
	int				m_iSlot_TextureID;
	HTint			m_iQuickSlot_ActionSlotNo;
	HTbool			m_bQuickSlot_Loaded;

	//	아이템 사용후 남은 겟수
	HTint			m_iUsedItemCount;

	//	For Continue Item
	HTint			m_iContinueItemKeyID[10];
	DWORD			m_dwContinueItemUseDelay;
};