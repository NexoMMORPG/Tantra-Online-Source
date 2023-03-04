
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTOtherCharacterMove.h"

CHTOtherCharMove::CHTOtherCharMove()
{
	m_fBasicSpeedWalk				= 0.0f;
	m_fBasicSpeedRun				= 0.0f;
	m_fSpeedItem					= 0.0f;
	m_fSpeedItemUp					= 0.0f;
	m_fSpeedSkill					= 0.0f;
    m_fSpeedWalk					= 0.0f;
	m_fSpeedRun						= 0.0f;
	m_fOtherCharSpeedValue			= 0.0f;
	m_byOtherCharMoveState			= 0x20;
	m_fOtherCharResentDirect		= HT_PI;
	m_iOtherCharMove_State			= OTHERCHARMOVE_STAND;
}

CHTOtherCharMove::~CHTOtherCharMove()
{
}

HTshort g_sMovingSpeed[] = { 350, 300, 320, 340 };

HTvoid CHTOtherCharMove::HT_vOtherCharSetInitSpeed( BYTE byCharType )
{
	HTfloat fMoveSpeed;
	if( byCharType == 0x09 )
	{
		fMoveSpeed = 200;
	}
	else
	{
		int nTribeIndex = (byCharType - 1) % 4;
		fMoveSpeed = (HTfloat)g_sMovingSpeed[ nTribeIndex ];
	}
	
	m_fBasicSpeedRun = (HTfloat)fMoveSpeed;
	m_fBasicSpeedWalk = (HTfloat)fMoveSpeed*2;

	HT_vOtherCharSetSpeed();
}

HTvoid CHTOtherCharMove::HT_vOtherCharSetSpeedItem( DWORD dwItemIndex )
{
	if( dwItemIndex == 0 )
	{
		m_fSpeedItem = 0;
		m_fSpeedItemUp = 0;
	}
	else
	{
		//------------------------------------------------------------------
		// New Param - 선미
		//------------------------------------------------------------------
		HTint iSpeedRate = 0, iOut = 0;
		//g_pParamMgr->HT_bGetItemPlusMovingSpeed(dwItemIndex, &sMovingSpeed);
		//m_fSpeedItem = (HTfloat)iMovingSpeed/3.0f;
		if(g_pParamMgr->HT_bLockID(dwItemIndex) == true )
		{
			if( g_pParamMgr->HT_bGetItemEffect1ID( &iOut ) == true && 
										( iOut == _EFFECT_FASTER_MOVE || iOut == _EFFECT_SLOWER_MOVE ) )
				g_pParamMgr->HT_bGetItemEffect1Param1( &iSpeedRate );

			else if( g_pParamMgr->HT_bGetItemEffect2ID( &iOut ) == true &&  
										( iOut == _EFFECT_FASTER_MOVE || iOut == _EFFECT_SLOWER_MOVE ) )
				g_pParamMgr->HT_bGetItemEffect2Param1( &iSpeedRate );

			else if( g_pParamMgr->HT_bGetItemEffect3ID( &iOut ) == true &&  
										( iOut == _EFFECT_FASTER_MOVE || iOut == _EFFECT_SLOWER_MOVE ) )
				g_pParamMgr->HT_bGetItemEffect3Param1( &iSpeedRate );

			else if( g_pParamMgr->HT_bGetItemEffect4ID( &iOut ) == true &&  
										( iOut == _EFFECT_FASTER_MOVE || iOut == _EFFECT_SLOWER_MOVE ) )
				g_pParamMgr->HT_bGetItemEffect4Param1( &iSpeedRate );

			else if( g_pParamMgr->HT_bGetItemEffect5ID( &iOut ) == true &&  
										( iOut == _EFFECT_FASTER_MOVE || iOut == _EFFECT_SLOWER_MOVE ) )
				g_pParamMgr->HT_bGetItemEffect5Param1( &iSpeedRate );

			g_pParamMgr->HT_bUnLockID(dwItemIndex);
		}
		m_fSpeedItem = (HTfloat)iSpeedRate;	// 빨라지게 하는 값인지 느려지게 하는 값인지 구분 필요
		//------------------------------------------------------------------
	}

	HT_vOtherCharSetSpeed();
}

HTvoid CHTOtherCharMove::HT_vOtherCharSetSpeedItemUp( HTfloat fItemSpeedUp )
{
	m_fSpeedItemUp = fItemSpeedUp/3.0f;
	HT_vOtherCharSetSpeed();
}

// 서버에서 내려온다? - 선미
HTvoid CHTOtherCharMove::HT_vOtherCharSetSpeedSkill( DWORD dwSkillIndex, BYTE byLevel )
{
	//if( dwSkillIndex != 0 && dwSkillIndex < 10000 )
	//{
	//	SKILL_BASIC_PARAMS* sSkill_Param = g_pclsEditorsData->SearchSkillParam( dwSkillIndex, byLevel );
	//	m_fSpeedSkill = -(sSkill_Param->byMovingSpeedVariation);
	//}
	//else
	//{
	//	m_fSpeedSkill = 0;
	//}
	//HT_vOtherCharSetSpeed();
}

HTvoid CHTOtherCharMove::HT_vOtherCharSetSpeed()
{
	m_fSpeedWalk = 12.0f / ((m_fBasicSpeedWalk + m_fSpeedItem + m_fSpeedItemUp + m_fSpeedSkill)/1000.0f);
	m_fSpeedRun = 12.0f / ((m_fBasicSpeedRun + m_fSpeedItem + m_fSpeedItemUp + m_fSpeedSkill)/1000.0f);

	if( m_byOtherCharMoveState == 0x20 )
		m_fOtherCharSpeedValue = m_fSpeedWalk;
	else if( m_byOtherCharMoveState == 0x30 )
		m_fOtherCharSpeedValue = m_fSpeedRun;
	else
		m_fOtherCharSpeedValue = m_fSpeedRun;
}

//----------두벡터를 이용하여 라디안 값을 얻어온다.----------//
HTfloat CHTOtherCharMove::HT_fOtherCharMoveGetAngle( HTvector3 A, HTvector3 B )
{
	float sp= A.x*B.x + A.z*B.z;					//	내적구하기 -> 벡터의 관계(각도)를 알기 위해
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A 벡터의 절대값(길이) 구하기 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B 벡터의 절대값(길이) 구하기 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  세값을 이용해서 각도 구하기

	float acos = acosf( cos );						//	코사인값을 라디안값 바꾸기
	float direction = A.z*B.x - B.z*A.x;			//	왼쪽 오른쪽 비교
	if(direction < 0)								//	dirction 음이면 왼쪽 , 양이면 오른쪽
		acos *= -1;
	return acos;
}

//	목표셀 계산_바뀐 이후
HTvoid CHTOtherCharMove::HT_vOtherCharMoveCheckTargetCell( MSG_Action* info )
{
	if( info->TargetX == m_iOtherCharphysical_CellX && info->TargetY == m_iOtherCharphysical_CellZ )
		return;

	//	속도 셋팅
	if( info->Speed != 0 )
		m_fOtherCharSpeedValue = (HTfloat)info->Speed;

	//	목표셀 계산
	HT_CELL_COORD crdCell;
	crdCell.x = m_iOtherCharlogical_CellX = info->TargetX;
	crdCell.y = m_iOtherCharlogical_CellZ = info->TargetY;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecOtherCharTargetPos, crdCell );

	HTfloat fDistance = this->HT_fGetOtherCharTargetToResentDis();

	//	OtherChar 방향 계산
	m_fOtherCharResentDirect = this->HT_fGetOtherCharMoveDirectCal();

	//	첫시작 위치 저장
	m_vecOtherCharStartPos = m_vecOtherCharResentPos;
	//	시간으로 이동량 체크
	//	상대적인 변화량
	m_fOtherCharMove_EOTransValue = 1;
	//	시간 변화량
	m_fOtherCharMove_TimeTransValue = 0;
	//	전체 시간
	m_fOtherCharMove_TotalTime = fDistance * MAP_CELL_SIZE;

    m_iOtherCharMove_State = OTHERCHARMOVE_GO;
}

//----------고----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMoveGo( HTfloat fElapsedTime )
{
	if( fElapsedTime < HT_EPSILON )
		return;

	m_fOtherCharMove_TimeTransValue += ( fElapsedTime * m_fOtherCharSpeedValue * MAP_CELL_SIZE * CHARACTER_SPEED_OTHERCHARCORRECT );

	m_fOtherCharMove_EOTransValue = 1 - ( m_fOtherCharMove_TimeTransValue/m_fOtherCharMove_TotalTime );
	if( m_fOtherCharMove_EOTransValue < 0 )
		m_fOtherCharMove_EOTransValue = 0;
	else if( m_fOtherCharMove_EOTransValue > 1 )
		m_fOtherCharMove_EOTransValue = 1;

	m_vecOtherCharResentPos = ( m_vecOtherCharStartPos*m_fOtherCharMove_EOTransValue ) + ( m_vecOtherCharTargetPos * (1-m_fOtherCharMove_EOTransValue) );
	m_vecOtherCharResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOtherCharResentPos.x, m_vecOtherCharResentPos.z );
}

//----------논리적인 셀과 물리적인 셀이 같은지 비교후 보정----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMovephysicalCellMoveCheck()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecOtherCharResentPos, crdCell );
	m_iOtherCharphysical_CellX = crdCell.x;
	m_iOtherCharphysical_CellZ = crdCell.y;
}

//----------목표점까지 도착하면 스톱----------//
HTbool CHTOtherCharMove::HT_vOtherCharMoveStopCheck()
{
	if( m_fOtherCharMove_EOTransValue == 0 )
	{
        HT_vOtherCharMoveStop();
        return HT_TRUE;
	}

	return HT_FALSE;
}

//----------보정해주기----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMoveCorrection()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecOtherCharResentPos, crdCell );

	if( crdCell.x != m_iOtherCharlogical_CellX || crdCell.y != m_iOtherCharlogical_CellZ )
	{
		m_iOtherCharphysical_CellX = m_iOtherCharlogical_CellX;
		m_iOtherCharphysical_CellZ = m_iOtherCharlogical_CellZ;
		HT_CELL_COORD crdCell;
		crdCell.x = m_iOtherCharlogical_CellX;
		crdCell.y = m_iOtherCharlogical_CellZ;
		g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecOtherCharResentPos, crdCell );
	}
}

//----------멈추기----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMoveStop()
{
	m_fOtherCharSpeedValue			= 0.0f;
	m_iOtherCharMove_State			= OTHERCHARMOVE_STAND;
	m_fOtherCharMove_EOTransValue	= 0;
}

//----------반환값들----------//
HTPoint CHTOtherCharMove::HT_pGeOtherCharMoveGrid()
{
	HTPoint OtherCharGrid;

	OtherCharGrid.x = m_iOtherCharphysical_CellX / 4;
	OtherCharGrid.y = m_iOtherCharphysical_CellZ / 4;

	return OtherCharGrid;
}

HTvector3 CHTOtherCharMove::HT_fGetOtherCharMovePos()
{
	m_vecOtherCharResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOtherCharResentPos.x, m_vecOtherCharResentPos.z );
    return m_vecOtherCharResentPos;
}

HTvoid CHTOtherCharMove::HT_fSetOtherCharMovePos( HTvector3 vPos )
{
	m_vecOtherCharResentPos = vPos;
}

HTvoid CHTOtherCharMove::HT_fSetOtherCharMovelogical_CellPos( HTint x, HTint z )
{
	m_iOtherCharlogical_CellX = x;
	m_iOtherCharlogical_CellZ = z;
}

HTvoid CHTOtherCharMove::HT_fSetOtherCharMovephysical_CellPos( HTint x, HTint z )
{
	if( x == m_iOtherCharphysical_CellX && z == m_iOtherCharphysical_CellZ )
		return;

	m_iOtherCharphysical_CellX = x;
	m_iOtherCharphysical_CellZ = z;

	HT_CELL_COORD crdCell;
	crdCell.x = m_iOtherCharphysical_CellX;
	crdCell.y = m_iOtherCharphysical_CellZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecOtherCharResentPos, crdCell );
	m_vecOtherCharResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOtherCharResentPos.x, m_vecOtherCharResentPos.z );
}

HTvoid CHTOtherCharMove::HT_vGetOtherCharMove_physicalCellPos( HTPoint* pPhysicalCellPos )
{
	pPhysicalCellPos->x = m_iOtherCharphysical_CellX;
	pPhysicalCellPos->y = m_iOtherCharphysical_CellZ;
}

HTfloat CHTOtherCharMove::HT_fGetOtherCharMoveSpeed()
{
	return m_fOtherCharSpeedValue;
}

//	OtherChar 방향
HTfloat CHTOtherCharMove::HT_fGetOtherCharMoveDirect()
{
	return m_fOtherCharResentDirect;
}

//	OtherChar 방향
HTvoid CHTOtherCharMove::HT_vSetOtherCharMoveDirect( HTfloat fDir )
{
	m_fOtherCharResentDirect = fDir;
}

//	OtherChar 방향 실시간 계산
HTfloat CHTOtherCharMove::HT_fGetOtherCharMoveDirectCal()
{
	//HTfloat fDistance = HT_fGetOtherCharTargetToResentDis();
	//if( fDistance < 5.0f )
	//	return m_fOtherCharResentDirect;
	//	방향구하기
	HTvector3 vecVector = m_vecOtherCharTargetPos - m_vecOtherCharResentPos;
	return HT_fOtherCharMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;
}

//	목표점과 현재점의 차이를 계산
HTfloat CHTOtherCharMove::HT_fGetOtherCharTargetToResentDis()
{
	return (float)sqrt( double( (m_vecOtherCharTargetPos.x - m_vecOtherCharResentPos.x) * (m_vecOtherCharTargetPos.x - m_vecOtherCharResentPos.x) ) 
					  + double( (m_vecOtherCharTargetPos.z - m_vecOtherCharResentPos.z) * (m_vecOtherCharTargetPos.z - m_vecOtherCharResentPos.z) ) );
}
