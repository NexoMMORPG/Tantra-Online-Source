
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTEngineHandler.h"
#include "HTextern.h"
#include "HTMoveMonster.h"


CHTMoveMonSter::CHTMoveMonSter()
{
	m_fMonsterSpeedValue = 0.0f;
	m_iMonsterSpeedGrade = 3;
	m_bMonsterMoveState = HT_FALSE;
	m_fMonsterResentDirect = 0.0f;
	m_fTransDirect		   = 0.0f;

	//----------타격받았을때 밀리는 동작----------//
	m_bMonster_Push_Sw = HT_FALSE;
	//----------타격받았을때 예전 위치 저장----------//
	m_vecMonster_PushSavePos = HTvector3( 0, 0 ,0 );
}

CHTMoveMonSter::~CHTMoveMonSter()
{
}

//----------몬스터 데이타 초기화----------//
HTvoid CHTMoveMonSter::HT_vMoveMonSterInit()
{
}


//----------두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터----------//
float CHTMoveMonSter::HT_fMonsterGetAngle(HTvector3 A, HTvector3 B)
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

//----------네트워크_N스텝 이동----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_SetEnd( HTint nX, HTint nZ, HTint iSpeed )
{
	m_bMonster_StepType = 0x00;

	m_iMonsterlogical_CellX = nX;
	m_iMonsterlogical_CellZ = nZ;

	//----------이동 셋팅----------//
	this->HT_vMoveMonster_MoveSetting( m_iMonsterlogical_CellX, m_iMonsterlogical_CellZ, (HTfloat)iSpeed );
}

void CHTMoveMonSter::HT_vMonsterMoving( HTfloat fElapsedTime )
{
	if( fElapsedTime < HT_EPSILON )
		return;

	m_fMonster_TimeTransValue += ( fElapsedTime * m_fMonsterSpeedValue * MAP_CELL_SIZE * (CHARACTER_SPEED_MONSTERCORRECT-3) );

	m_fMonster_EOTransValue = 1 - ( m_fMonster_TimeTransValue/m_fMonster_TotalTime );
	if( m_fMonster_EOTransValue < 0 )
		m_fMonster_EOTransValue = 0;

	m_vecMonsterResentPos = ( m_vecMonsterStartPos*m_fMonster_EOTransValue ) + ( m_vecMonsterTargetPos * (1-m_fMonster_EOTransValue) );
	m_vecMonsterResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecMonsterResentPos.x, m_vecMonsterResentPos.z );

	//---------몬스터의 물리적인 셀위치를 계산한다.----------//
	this->HT_vMonsterCellPositionCheck();
}

HTvoid CHTMoveMonSter::HT_bMonsterCheckMove()
{
	if( m_fMonster_EOTransValue == 0 )
	{
		HT_vecMonsterStopMove();
	}
}

HTvoid CHTMoveMonSter::HT_vecMonsterStopMove()
{
	m_fMonsterSpeedValue = 0.0f;
	m_bMonsterMoveState = HT_FALSE;

	//------------보정해주기---------------//
	//HT_vMonsterMove_Correction();
}

//------------보정해주기---------------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_Correction()
{
	//---------위치가 같으면 그냥 넘어가고 같지않으면 물리적인 셀을 보정해준다.----------//
	if( m_iMonsterphysical_CellX != m_iMonsterlogical_CellX || m_iMonsterphysical_CellZ != m_iMonsterlogical_CellZ )
	{
		//----------이동 셋팅----------//
		HT_vMoveMonster_MoveSetting( m_iMonsterlogical_CellX, m_iMonsterlogical_CellZ, 20.0f );
	}
}

//------------몬스터 각도 체크---------------//
HTvoid CHTMoveMonSter::HT_vMonsterMoveAngleCheck( HTfloat fAngle )
{
	if( fAngle == m_fTransDirect )
		return;

	m_fTargetAngle				= fAngle;
	m_fPlusAngle				= 0;
	m_fMinusAngle				= 0;
	
	//-----1. 현재각에서부터 타겥각까지의 음과 양의 카운트를 계산한다.-----//
	m_bAngleTrans_Sw = 0;
	if( HT_DIFF( m_fTargetAngle, m_fTransDirect ) < HT_PI )
	{
		if( m_fTargetAngle > m_fTransDirect )
			m_fPlusAngle = m_fTargetAngle - m_fTransDirect;
		else
			m_fMinusAngle = m_fTransDirect - m_fTargetAngle;
	}
	else
	{
		if( m_fTargetAngle > m_fTransDirect )
			m_fMinusAngle = ( m_fTransDirect-HT_PI ) + ( HT_PIX2+HT_PI - m_fTargetAngle );
		else
			m_fPlusAngle = ( m_fTargetAngle-HT_PI ) + ( HT_PIX2+HT_PI - m_fTransDirect );
	}

	if( m_fMinusAngle == 0 )
		m_bAngleTrans_Sw = 1;
	else
		m_bAngleTrans_Sw = -1;
}

//------------각도를 회전시키기---------------//
HTvoid CHTMoveMonSter::HT_vMonsterMoveAngleTransing()
{
	if( m_bAngleTrans_Sw == 0 )
		return;

	if( m_bAngleTrans_Sw == 1 )
	{
		m_fTransDirect += 0.3f;
		if( m_fTransDirect >= HT_PI+HT_PIX2 )
			m_fTransDirect = HT_PI;

		m_fPlusAngle -= 0.3f;
		if( m_fPlusAngle <= 0 )
		{
			m_fPlusAngle = 0;
			m_bAngleTrans_Sw = 0;
			m_fTransDirect = m_fTargetAngle;
		}
	}
	else
	{
		m_fTransDirect -= 0.3f;
		if( m_fTransDirect <= HT_PI )
			m_fTransDirect = HT_PI+HT_PIX2;

		m_fMinusAngle -= 0.3f;
		if( m_fMinusAngle <= 0 )
		{
			m_fMinusAngle = 0;
			m_bAngleTrans_Sw = 0;
			m_fTransDirect = m_fTargetAngle;
		}
	}
}

//---------몬스터의 물리적인 셀위치를 계산한다.----------//
HTvoid CHTMoveMonSter::HT_vMonsterCellPositionCheck()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMonsterResentPos, crdCell );
	m_iMonsterphysical_CellX = crdCell.x;
	m_iMonsterphysical_CellZ = crdCell.y;
}

//----------타격감 관련 밀렸다가 돌아오기_셋팅----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_HitPushMoveSetting( HTfloat fDirect )
{
	//----------타격받았을때 밀리는 동작----------//
	m_bMonster_Push_Sw = HT_TRUE;
	//----------타격받았을때 밀리는 왕복 동작----------//
	m_bMonster_PushReturn_Sw = HT_TRUE;
	//----------타격받았을때 밀리는 거리----------//
	m_fMonster_PushDis = 0.0f;
	//----------타격받았을때 밀리는 거리를 계산하기 위해----------//
	m_fMonster_PushDis_Trans = 3.0f;
	//----------타격받았을때 밀리갈 방향----------//
	m_fMonster_PushDirect = fDirect;
	//----------타격받았을때 예전 위치 저장----------//
	m_vecMonster_PushSavePos = HTvector3( 0, 0, 0 );
//	m_vecMonster_PushSavePos = m_vecMonsterResentPos;
}

//----------타격감 관련 밀렸다가 돌아오기_컨트롤----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_HitPushMove()
{
	float fx, fz;

	fx = sinf( m_fMonster_PushDirect ) * ( m_fMonster_PushDis );
	fz = cosf( m_fMonster_PushDirect ) * ( m_fMonster_PushDis );

	m_vecMonster_PushSavePos.x = fx;
	m_vecMonster_PushSavePos.z = fz;


	if( m_bMonster_PushReturn_Sw == HT_TRUE )
	{
		m_fMonster_PushDis += m_fMonster_PushDis_Trans;
		m_fMonster_PushDis_Trans /= 2;
		if( m_fMonster_PushDis_Trans < 1 )
			m_bMonster_PushReturn_Sw = HT_FALSE;
	}
	else
	{
		m_fMonster_PushDis -= m_fMonster_PushDis_Trans;
		m_fMonster_PushDis_Trans *= 2;
		if( m_fMonster_PushDis_Trans > 3 )
		{
			m_fMonster_PushDis = 0;
			m_bMonster_Push_Sw = HT_FALSE;
			m_vecMonster_PushSavePos = HTvector3( 0, 0, 0 );
		}
	}
}

//----------공격 할때 거리 맞추어 주기----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_AttackDistanceCheck( HTint nX, HTint nZ, HTvector3 vecCharPos )
{
	//if( m_iMonsterphysical_CellX == nX && m_iMonsterphysical_CellZ == nZ )
	//	return;

	//	2. 공격자의 좌표를 구하고, 이동도 멈추고,
	HT_CELL_COORD crdCell;
	crdCell.x = m_iMonsterlogical_CellX = nX;
	crdCell.y = m_iMonsterlogical_CellZ = nZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterResentPos, crdCell );

	//---------몬스터의 물리적인 셀위치를 계산한다.----------//
	HT_vMonsterCellPositionCheck();

	m_bMonsterMoveState = HT_FALSE;

	//	3. 밀려나야할 거리를 구하고
	HTfloat fTempDistance;
	if( m_bMonsterSize == 1 )
		fTempDistance = (HTfloat)( m_bMonsterSize * 10 );
	else
        fTempDistance = (HTfloat)( ( m_bMonsterSize * 10 ) - ( m_bMonsterSize * 2 ) );
	//	4. 밀려날 방향을 구하고
	HTvector3 vecPos = m_vecMonsterResentPos - vecCharPos;
	HTfloat fTempDirect = HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	//	5. 캐리터와의 현재 거리를 구하고
	HTfloat fCurDistance = (float)sqrt( double( ((m_vecMonsterResentPos.x - vecCharPos.x) * (m_vecMonsterResentPos.x - vecCharPos.x))+
		((m_vecMonsterResentPos.z - vecCharPos.z) * (m_vecMonsterResentPos.z - vecCharPos.z)) ) );
	//	6. 내가 이동해야 할 거리도 구하고
	HTfloat fMoveDistance = fTempDistance - fCurDistance;
	//	7. 조건에 합당하면 이동시켜주자
	if( fMoveDistance > 0 )
	{
		float fx, fz;

		fx = sinf( fTempDirect ) * ( fMoveDistance );
		fz = cosf( fTempDirect ) * ( fMoveDistance );

		m_vecMonsterResentPos.x += fx;
		m_vecMonsterResentPos.z += fz;
		m_vecMonsterResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecMonsterResentPos.x, m_vecMonsterResentPos.z );
	}
}

//----------이동 셋팅----------//
HTvoid CHTMoveMonSter::HT_vMoveMonster_MoveSetting( HTint nX, HTint nZ, HTfloat fSpeed )
{
	if( m_iMonsterphysical_CellX == nX && m_iMonsterphysical_CellZ == nZ )
		return;

	//	이동 셋팅
	m_bMonsterMoveState			= HT_TRUE;

	//	목적지 좌표 셋팅
	HT_CELL_COORD crdCell;
	crdCell.x = nX;
	crdCell.y = nZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterTargetPos, crdCell );
	//	시작위치 구하기
	m_vecMonsterStartPos = m_vecMonsterResentPos;

	//	방향구하기
	HTvector3 vecVector = m_vecMonsterTargetPos - m_vecMonsterResentPos;
	m_fMonsterResentDirect = HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;

	//	공격 갈 거리 변화
	m_fMonster_Distance = (float)sqrt( double( ((m_vecMonsterTargetPos.x - m_vecMonsterResentPos.x) * (m_vecMonsterTargetPos.x - m_vecMonsterResentPos.x))+
											   ((m_vecMonsterTargetPos.z - m_vecMonsterResentPos.z) * (m_vecMonsterTargetPos.z - m_vecMonsterResentPos.z)) ) );
	m_fMonster_Distance_Trans		= 0;

	//	스피드 셋팅
	m_fMonsterSpeedValue = fSpeed;

	//	상대적인 변화량
	m_fMonster_EOTransValue = 1;
	//	시간 변화량
	m_fMonster_TimeTransValue = 0;
	//	전체 시간
	m_fMonster_TotalTime = m_fMonster_Distance * MAP_CELL_SIZE;
}

//----------셋팅하고 반환값----------//
HTvector3 CHTMoveMonSter::HT_vecGetMonsterPos()
{
	m_vecMonsterResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecMonsterResentPos.x, m_vecMonsterResentPos.z );
	return m_vecMonsterResentPos;
}

HTvoid CHTMoveMonSter::HT_fSetMonsterPos( HTvector3 vecPos )
{
	m_vecMonsterResentPos = vecPos;
}

HTvoid CHTMoveMonSter::HT_vSetMonsterDirect( HTfloat fDirect )
{
	m_fMonsterResentDirect = fDirect;
}

HTvoid CHTMoveMonSter::HT_fSetMonsterSize( BYTE bSize )
{
	m_bMonsterSize = bSize;
}

HTfloat CHTMoveMonSter::HT_fGetMonsterDirect()
{
	return m_fMonsterResentDirect;
}

HTfloat CHTMoveMonSter::HT_fGetMonsterRotateDirect()
{
	return m_fTransDirect;//m_fMonsterResentDirect;//
}

HTvoid CHTMoveMonSter::HT_vSetMonsterlogical_Cell( short x, short z )
{
	m_iMonsterlogical_CellX = x;
	m_iMonsterlogical_CellZ = z;

	HT_CELL_COORD crdCell;
	crdCell.x = m_iMonsterlogical_CellX;
	crdCell.y = m_iMonsterlogical_CellZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterTargetPos, crdCell );
}

HTvoid CHTMoveMonSter::HT_vSetMonsterphysical_Cell( short x, short z )
{
	m_iMonsterphysical_CellX = x;
	m_iMonsterphysical_CellZ = z;

	HT_CELL_COORD crdCell;
	crdCell.x = m_iMonsterphysical_CellX;
	crdCell.y = m_iMonsterphysical_CellZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterResentPos, crdCell );
}

HTPoint CHTMoveMonSter::HT_pGetMonsterGrid()
{
	HTPoint MonsterGrid;

	MonsterGrid.x = m_iMonsterlogical_CellX / 4;
	MonsterGrid.y = m_iMonsterlogical_CellZ / 4;

	return MonsterGrid;
}

HTPoint CHTMoveMonSter::HT_pGetMonsterCellPos()
{
	HTPoint MonsterCell;

	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMonsterResentPos, crdCell );

	MonsterCell.x = crdCell.x;
	MonsterCell.y = crdCell.y;
	return MonsterCell;
}

HTbool CHTMoveMonSter::HT_pGetMonster_ResentMoveStatus()
{
	if( m_fMonsterSpeedValue == 0.0f )
		return HT_FALSE;

   	return HT_TRUE;
}

HTvoid CHTMoveMonSter::HT_vSetMonster_SetHitStop( HTbool bType )
{
	if( bType == HT_TRUE )
	{
		m_bMonsterMoveState				= HT_TRUE;
		m_fMonsterResentDirect			= m_fMonsterResentDirect_Temp;
		m_fMonsterSpeedValue			= m_fMonsterSpeedValue_Temp;
		m_fMonster_Distance				= m_fMonster_Distance_Temp;
		m_fMonster_Distance_Trans		= m_fMonster_Distance_Trans_Temp;
	}
	else
	{
		m_bMonsterMoveState				= HT_FALSE;
		m_fMonsterResentDirect_Temp		= m_fMonsterResentDirect;
		m_fMonsterSpeedValue_Temp		= m_fMonsterSpeedValue;
		m_fMonster_Distance_Temp		= m_fMonster_Distance;
		m_fMonster_Distance_Trans_Temp	= m_fMonster_Distance_Trans;
	}
}

/*
HT_CELL_COORD crdCell;
crdCell.x = m_iMonsterlogical_CellX;
crdCell.y = m_iMonsterlogical_CellZ;
g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterResentPos, crdCell );
m_vecMonsterResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecMonsterResentPos.x, m_vecMonsterResentPos.z );
*/