#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htotherobjectmove.h"

HTOtherObjectMove::HTOtherObjectMove(void)
{
	//	Move Up/Down Control
	m_fHight		= 0;
	m_fSpeedHight	= 0;
	m_fLimitHight	= 0;
	m_bAccelerationHightSw = HT_FALSE;
	m_fApplySpeedValue = 0.0f;
}

HTOtherObjectMove::~HTOtherObjectMove(void)
{
}

//	MoveSystem
//	MoveSystem Recive Action Msg
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_MoveSystemReciveActionMsg( MSG_Action* info )
{
	if( info->TargetX == m_iPhysical_CellX && info->TargetY == m_iPhysical_CellZ )
		return;

	//	목표셀 계산
	HT_CELL_COORD crdCell;
	crdCell.x = m_iLogical_CellX = info->TargetX;
	crdCell.y = m_iLogical_CellZ = info->TargetY;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecTargetPos, crdCell );
	//	방향 계산
	m_fResentDirect = this->HT_fOtherObjectMove_GetDirectCal();
	//	첫시작 위치 저장
	m_vecStartPos = m_vecResentPos;
	//	시간으로 이동량 체크
	//	상대적인 변화량
	m_fEOTransValue = 1;
	//	시간 변화량
	m_fTimeTransValue = 0;
	//	전체 시간
	HTfloat fDistance = this->HT_fOtherObjectMove_GetOtherCharTargetToResentDis();
	m_fTotalTime = fDistance * MAP_CELL_SIZE;
	//	상태
    m_byMoveState = OTHERCHARMOVE_GO;
	//	속도 셋팅
	m_fApplySpeedValue = (HTfloat)info->Speed;
	//if( m_fApplySpeedValue > 1 )
	//	m_fApplySpeedValue -= 0.5f;
	//	Move Effect
	m_snEffect = info->Effect;
}
//	MoveSystem Go
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_MoveSystemGo( HTfloat fElapsedTime )
{
	if( fElapsedTime < HT_EPSILON )
		return;

	m_fTimeTransValue += ( fElapsedTime * m_fApplySpeedValue * MAP_CELL_SIZE * CHARACTER_SPEED_OTHERCHARCORRECT );

	m_fEOTransValue = 1 - ( m_fTimeTransValue/m_fTotalTime );
	if( m_fEOTransValue < 0 )
		m_fEOTransValue = 0;
	else if( m_fEOTransValue > 1 )
		m_fEOTransValue = 1;

	//	Cood Pos Move
	m_vecResentPos = ( m_vecStartPos*m_fEOTransValue ) + ( m_vecTargetPos * (1-m_fEOTransValue) );
	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );

	//	Cell Pos Move
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, crdCell );
	m_iPhysical_CellX = crdCell.x;
	m_iPhysical_CellZ = crdCell.y;
}
//	MoveSystem StopCheck
HRESULT HTOtherObjectMove::HT_hrOtherObjectMove_MoveSystemStopCheck()
{
	if( m_fEOTransValue == 0 )
	{
        this->HT_vOtherObjectMove_MoveSystemStop();
		return HT_OK;
	}
	return HT_FAIL;
}
//	MoveSystem Stop
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_MoveSystemStop()
{
	m_fApplySpeedValue			= 0.0f;
	m_byMoveState				= OTHERCHARMOVE_STAND;
	m_fEOTransValue	= 0;
}
//	Move Up/Down Control
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_UpDownControl()
{
	//	오브젝트 높낮이 조정
	if( m_fSpeedHight != 0 )
	{
		//	가속 스위치가 켜져 있으면
		if( m_bAccelerationHightSw == HT_TRUE )
		{
			m_fSpeedHight *= 1.1f;
		}

		if( m_fLimitHight != 0 )
		{
			m_fHight += m_fSpeedHight;
			if( (HTfloat)sqrt(m_fHight) > m_fLimitHight )
			{
				m_fHight = m_fLimitHight;
				m_fLimitHight = 0;
				m_fSpeedHight = 0;
			}
		}
		else
		{
			if( m_fHight != 0 )
			{
				m_fHight += m_fSpeedHight;
				if( m_fSpeedHight > 0 )
				{
					if( m_fHight >= 0 )
					{
						m_fHight = 0;
						m_fLimitHight = 0;
						m_fSpeedHight = 0;
					}
				}
				else if( m_fSpeedHight < 0 )
				{
					if( m_fHight <= 0 )
					{
						m_fHight = 0;
						m_fLimitHight = 0;
						m_fSpeedHight = 0;
					}
				}
			}
			else
			{
				m_fHight = 0;
				m_fLimitHight = 0;
				m_fSpeedHight = 0;
			}
		}
	}
}

//	Setting
//	Setting Cur CoodPos;
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_SetCurCoodPos( HTvector3 vecPos )
{
	m_vecResentPos = vecPos;
	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, crdCell );
	m_iPhysical_CellX = crdCell.x;
	m_iPhysical_CellZ = crdCell.y;
}
//	Setting Cur CellPos
HTRESULT HTOtherObjectMove::HT_hrOtherObjectMove_SetTargetCellPos( HTint iX, HTint iZ )
{
	if( iX == m_iPhysical_CellX && iZ == m_iPhysical_CellZ )
		return HT_FAIL;

	MSG_Action* info = NULL;
	info = new MSG_Action;
	info->TargetX = iX;
	info->TargetY = iZ;
	info->Speed = 8;
	this->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	HT_DELETE( info );

	return HT_OK;
}
//	Setting Cur Direct
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_SetCurDirect( HTfloat fAngle )
{
	m_fResentDirect = fAngle;
}
//	Setting Up/Down
HTvoid HTOtherObjectMove::HT_vOtherObjectMove_SetUpDown( HTfloat fHight, HTfloat fSpeedHight, HTfloat fLimitHight, HTbool bAccelerationHightSw )
{
	m_fHight				= fHight;
	m_fSpeedHight			= fSpeedHight;
	m_fLimitHight			= fLimitHight;
	m_bAccelerationHightSw	= bAccelerationHightSw;
}

//	Returns
//	Returns Cur Pos
HTvector3 HTOtherObjectMove::HT_vecOtherObjectMove_GetCurCoodPos()
{
	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z ) + m_fHight;
    return m_vecResentPos;
}
//	Returns Cur Grid
HTPoint HTOtherObjectMove::HT_pOtherObjectMove_GetGrid()
{
	HTPoint pGrid;

	pGrid.x = m_iPhysical_CellX / 4;
	pGrid.y = m_iPhysical_CellZ / 4;

	return pGrid;
}
//	Returns Cur Cell
HTPoint HTOtherObjectMove::HT_pOtherObjectMove_GetCellPos()
{
	HTPoint pCellPos;
	pCellPos.x = m_iPhysical_CellX;
	pCellPos.y = m_iPhysical_CellZ;

	return pCellPos;
}
//	Returns Cur Speed
HTfloat HTOtherObjectMove::HT_fOtherObjectMove_GetCurSpeed()
{
	return m_fApplySpeedValue;
}
//	Returns Cur Direct
HTfloat HTOtherObjectMove::HT_fOtherObjectMove_GetDirect()
{
	return m_fResentDirect;
}
//	Returns Cur Direct
HTfloat HTOtherObjectMove::HT_fOtherObjectMove_GetDirectCal()
{
	HTvector3 vecVector = m_vecTargetPos - m_vecResentPos;
	return HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;
}
//	Returns Cur TargetToResentTerm
HTfloat HTOtherObjectMove::HT_fOtherObjectMove_GetOtherCharTargetToResentDis()
{
	return (float)sqrt( double( (m_vecTargetPos.x - m_vecResentPos.x) * (m_vecTargetPos.x - m_vecResentPos.x) ) 
					  + double( (m_vecTargetPos.z - m_vecResentPos.z) * (m_vecTargetPos.z - m_vecResentPos.z) ) );
}

