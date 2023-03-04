
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTNPC.h"


HTNPC::HTNPC()
{
	m_cNPCMove = NULL;
	m_iNpcModelID = -1;
	m_vNPCMapCellX = 0;
	m_vNPCMapCellZ = 0;
}

HTNPC::~HTNPC()
{
	HT_DELETE( m_cNPCMove );
	if ( m_iNpcModelID > 0 )
		g_pEngineHandler->HT_vDestroyNPC( m_iNpcModelID, 11 );
}

HTRESULT HTNPC::HT_vNpc_Input( HTint iNPCIndex, short snX, short snZ )
{
	m_iNPCActive					= HT_FALSE;
	m_dwNpcIndex					= iNPCIndex;
	HT_CELL_COORD crdCell;
	m_vNPCMapCellX = crdCell.x = snX;
	m_vNPCMapCellZ = crdCell.y = snZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vNPCPosition, crdCell );
	m_vNPCPosition.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vNPCPosition.x, m_vNPCPosition.z );

	CHTString szName;
	//if( g_pEngineHandler->HT_hrGetNPCName( m_dwNpcIndex, &szName ) == HT_OK )
	if( g_pParamMgr->HT_bGetNPCName( m_dwNpcIndex, &szName ) == true )
		m_strNPCName = szName;
	else
		m_strNPCName.HT_hrCleanUp();

	m_iNpcModelID = g_pEngineHandler->HT_iCreateNPC( m_dwNpcIndex, m_vNPCPosition );
	if( m_iNpcModelID == -1 )
		m_iNpcModelID = 0;
	g_pEngineHandler->HT_hrRotateObject( m_iNpcModelID, HTvector3(0, HT_PIX2, 0) );
	g_pEngineHandler->HT_hrStartAnimation( m_iNpcModelID, m_dwNpcIndex, HT_ANISTATE_STD, -1 );

	m_bBeforAoi = 0;

	//	NPC 정보 표시 여부
	m_bNPC_Info_Sw					= HT_FALSE;

	//	NPC 이동 클래스 셋팅
	m_cNPCMove						= HT_NULL;
	m_cNPCMove						= new CHTNPCMove;

	if( m_dwNpcIndex == 1104 )
		m_cNPCMove->HT_vNPCMoveInit( snX, snZ, 0.35f );
	else 
		m_cNPCMove->HT_vNPCMoveInit( snX, snZ, 1.0f );

	// NPC의 모델 위치를 업데이트 함
	g_pEngineHandler->HT_hrMoveObject( m_iNpcModelID, m_cNPCMove->HT_vecNPCMove_GetPos() );

	//	NPC 애니매이션 컨트롤을 위해 1:서기,2:걷기,3:아이들
	m_nNPCAnm_Type					= 1;

	//	Chat Msg
	m_strNPCChatMsg.HT_hrCleanUp();
	m_dwNPCChatMsgStartTime	= 0;
	
	return HT_OK;
}

HTRESULT HTNPC::HT_vNpcDistroy()
{
	return HT_OK;
}

HTRESULT HTNPC::HT_vNpcControl()
{
	return HT_OK;
}

HTPoint HTNPC::HT_vNpcGetCell()
{
	HTPoint ptCell;

	ptCell.x = m_vNPCMapCellX;
	ptCell.y = m_vNPCMapCellZ;

	return ptCell;
}

//---------정보 디스플레이 셋팅----------//
HTvoid HTNPC::HT_vNPC_SetInfoDisplay()
{
	m_bNPC_Info_Sw = HT_TRUE;

	if( m_nNPCTargettingEffectID == -1 )
        g_pEngineHandler->HT_hrStartSFX( &m_nNPCTargettingEffectID, HT_FX_NPCTARGETING, m_iNpcModelID, HT_TRUE );
}

//---------정보 디스플레이 셋팅취소----------//
HTvoid HTNPC::HT_vNPC_SetInfoCancel()
{
	m_bNPC_Info_Sw = HT_FALSE;
	if( m_nNPCTargettingEffectID != -1 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_nNPCTargettingEffectID );
		m_nNPCTargettingEffectID = -1;
	}
}

//----------NPC 그려주는 부분----------//
HTRESULT HTNPC::HT_vNpcRender()
{
	return HT_OK;
}

HTvoid HTNPC::HT_vNPC_Click()
{
	// NPC와의 거리 체크
	HTPoint pCharCellPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTPoint pDifference;
	pDifference.x = pCharCellPos.x - m_vNPCMapCellX;
	pDifference.y = pCharCellPos.y - m_vNPCMapCellZ;
	
	// NPC와의 거리가 제한 내인 경우에는 NPC를 바라보게 설정함
	if( pDifference.x*pDifference.x + pDifference.y*pDifference.x <= NPC_DISTANCE_LIMIT*NPC_DISTANCE_LIMIT )
	{
		m_cNPCMove->HT_vNPCMove_Click();
		g_pEngineHandler->HT_hrRotateObject( m_iNpcModelID, m_cNPCMove->HT_fNPCMove_GetDirect() );
	}
	else
	{
		HT_CELL_COORD cellPos;
		// NPC가 있는(약간 떨어진) 위치로 이동
		cellPos.x = ( pDifference.x < 0 )?(m_vNPCMapCellX - 2):(m_vNPCMapCellX + 2);
		cellPos.y = ( pDifference.y < 0 )?(m_vNPCMapCellZ - 2):(m_vNPCMapCellZ + 2);
		g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_TRUE );
	}
}

HTvoid HTNPC::HT_vNPC_OtherInput()
{
	m_cNPCMove->HT_vNPCMove_OtherInput();
}



