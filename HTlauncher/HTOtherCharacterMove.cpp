
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
		// New Param - ����
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
		m_fSpeedItem = (HTfloat)iSpeedRate;	// �������� �ϴ� ������ �������� �ϴ� ������ ���� �ʿ�
		//------------------------------------------------------------------
	}

	HT_vOtherCharSetSpeed();
}

HTvoid CHTOtherCharMove::HT_vOtherCharSetSpeedItemUp( HTfloat fItemSpeedUp )
{
	m_fSpeedItemUp = fItemSpeedUp/3.0f;
	HT_vOtherCharSetSpeed();
}

// �������� �����´�? - ����
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

//----------�κ��͸� �̿��Ͽ� ���� ���� ���´�.----------//
HTfloat CHTOtherCharMove::HT_fOtherCharMoveGetAngle( HTvector3 A, HTvector3 B )
{
	float sp= A.x*B.x + A.z*B.z;					//	�������ϱ� -> ������ ����(����)�� �˱� ����
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A ������ ���밪(����) ���ϱ� 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B ������ ���밪(����) ���ϱ� 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  ������ �̿��ؼ� ���� ���ϱ�

	float acos = acosf( cos );						//	�ڻ��ΰ��� ���Ȱ� �ٲٱ�
	float direction = A.z*B.x - B.z*A.x;			//	���� ������ ��
	if(direction < 0)								//	dirction ���̸� ���� , ���̸� ������
		acos *= -1;
	return acos;
}

//	��ǥ�� ���_�ٲ� ����
HTvoid CHTOtherCharMove::HT_vOtherCharMoveCheckTargetCell( MSG_Action* info )
{
	if( info->TargetX == m_iOtherCharphysical_CellX && info->TargetY == m_iOtherCharphysical_CellZ )
		return;

	//	�ӵ� ����
	if( info->Speed != 0 )
		m_fOtherCharSpeedValue = (HTfloat)info->Speed;

	//	��ǥ�� ���
	HT_CELL_COORD crdCell;
	crdCell.x = m_iOtherCharlogical_CellX = info->TargetX;
	crdCell.y = m_iOtherCharlogical_CellZ = info->TargetY;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecOtherCharTargetPos, crdCell );

	HTfloat fDistance = this->HT_fGetOtherCharTargetToResentDis();

	//	OtherChar ���� ���
	m_fOtherCharResentDirect = this->HT_fGetOtherCharMoveDirectCal();

	//	ù���� ��ġ ����
	m_vecOtherCharStartPos = m_vecOtherCharResentPos;
	//	�ð����� �̵��� üũ
	//	������� ��ȭ��
	m_fOtherCharMove_EOTransValue = 1;
	//	�ð� ��ȭ��
	m_fOtherCharMove_TimeTransValue = 0;
	//	��ü �ð�
	m_fOtherCharMove_TotalTime = fDistance * MAP_CELL_SIZE;

    m_iOtherCharMove_State = OTHERCHARMOVE_GO;
}

//----------��----------//
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

//----------������ ���� �������� ���� ������ ���� ����----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMovephysicalCellMoveCheck()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecOtherCharResentPos, crdCell );
	m_iOtherCharphysical_CellX = crdCell.x;
	m_iOtherCharphysical_CellZ = crdCell.y;
}

//----------��ǥ������ �����ϸ� ����----------//
HTbool CHTOtherCharMove::HT_vOtherCharMoveStopCheck()
{
	if( m_fOtherCharMove_EOTransValue == 0 )
	{
        HT_vOtherCharMoveStop();
        return HT_TRUE;
	}

	return HT_FALSE;
}

//----------�������ֱ�----------//
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

//----------���߱�----------//
HTvoid CHTOtherCharMove::HT_vOtherCharMoveStop()
{
	m_fOtherCharSpeedValue			= 0.0f;
	m_iOtherCharMove_State			= OTHERCHARMOVE_STAND;
	m_fOtherCharMove_EOTransValue	= 0;
}

//----------��ȯ����----------//
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

//	OtherChar ����
HTfloat CHTOtherCharMove::HT_fGetOtherCharMoveDirect()
{
	return m_fOtherCharResentDirect;
}

//	OtherChar ����
HTvoid CHTOtherCharMove::HT_vSetOtherCharMoveDirect( HTfloat fDir )
{
	m_fOtherCharResentDirect = fDir;
}

//	OtherChar ���� �ǽð� ���
HTfloat CHTOtherCharMove::HT_fGetOtherCharMoveDirectCal()
{
	//HTfloat fDistance = HT_fGetOtherCharTargetToResentDis();
	//if( fDistance < 5.0f )
	//	return m_fOtherCharResentDirect;
	//	���ⱸ�ϱ�
	HTvector3 vecVector = m_vecOtherCharTargetPos - m_vecOtherCharResentPos;
	return HT_fOtherCharMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;
}

//	��ǥ���� �������� ���̸� ���
HTfloat CHTOtherCharMove::HT_fGetOtherCharTargetToResentDis()
{
	return (float)sqrt( double( (m_vecOtherCharTargetPos.x - m_vecOtherCharResentPos.x) * (m_vecOtherCharTargetPos.x - m_vecOtherCharResentPos.x) ) 
					  + double( (m_vecOtherCharTargetPos.z - m_vecOtherCharResentPos.z) * (m_vecOtherCharTargetPos.z - m_vecOtherCharResentPos.z) ) );
}
