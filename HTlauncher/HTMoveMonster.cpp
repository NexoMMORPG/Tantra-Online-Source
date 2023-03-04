
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

	//----------Ÿ�ݹ޾����� �и��� ����----------//
	m_bMonster_Push_Sw = HT_FALSE;
	//----------Ÿ�ݹ޾����� ���� ��ġ ����----------//
	m_vecMonster_PushSavePos = HTvector3( 0, 0 ,0 );
}

CHTMoveMonSter::~CHTMoveMonSter()
{
}

//----------���� ����Ÿ �ʱ�ȭ----------//
HTvoid CHTMoveMonSter::HT_vMoveMonSterInit()
{
}


//----------�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����----------//
float CHTMoveMonSter::HT_fMonsterGetAngle(HTvector3 A, HTvector3 B)
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

//----------��Ʈ��ũ_N���� �̵�----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_SetEnd( HTint nX, HTint nZ, HTint iSpeed )
{
	m_bMonster_StepType = 0x00;

	m_iMonsterlogical_CellX = nX;
	m_iMonsterlogical_CellZ = nZ;

	//----------�̵� ����----------//
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

	//---------������ �������� ����ġ�� ����Ѵ�.----------//
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

	//------------�������ֱ�---------------//
	//HT_vMonsterMove_Correction();
}

//------------�������ֱ�---------------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_Correction()
{
	//---------��ġ�� ������ �׳� �Ѿ�� ���������� �������� ���� �������ش�.----------//
	if( m_iMonsterphysical_CellX != m_iMonsterlogical_CellX || m_iMonsterphysical_CellZ != m_iMonsterlogical_CellZ )
	{
		//----------�̵� ����----------//
		HT_vMoveMonster_MoveSetting( m_iMonsterlogical_CellX, m_iMonsterlogical_CellZ, 20.0f );
	}
}

//------------���� ���� üũ---------------//
HTvoid CHTMoveMonSter::HT_vMonsterMoveAngleCheck( HTfloat fAngle )
{
	if( fAngle == m_fTransDirect )
		return;

	m_fTargetAngle				= fAngle;
	m_fPlusAngle				= 0;
	m_fMinusAngle				= 0;
	
	//-----1. ���簢�������� Ÿ���������� ���� ���� ī��Ʈ�� ����Ѵ�.-----//
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

//------------������ ȸ����Ű��---------------//
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

//---------������ �������� ����ġ�� ����Ѵ�.----------//
HTvoid CHTMoveMonSter::HT_vMonsterCellPositionCheck()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecMonsterResentPos, crdCell );
	m_iMonsterphysical_CellX = crdCell.x;
	m_iMonsterphysical_CellZ = crdCell.y;
}

//----------Ÿ�ݰ� ���� �зȴٰ� ���ƿ���_����----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_HitPushMoveSetting( HTfloat fDirect )
{
	//----------Ÿ�ݹ޾����� �и��� ����----------//
	m_bMonster_Push_Sw = HT_TRUE;
	//----------Ÿ�ݹ޾����� �и��� �պ� ����----------//
	m_bMonster_PushReturn_Sw = HT_TRUE;
	//----------Ÿ�ݹ޾����� �и��� �Ÿ�----------//
	m_fMonster_PushDis = 0.0f;
	//----------Ÿ�ݹ޾����� �и��� �Ÿ��� ����ϱ� ����----------//
	m_fMonster_PushDis_Trans = 3.0f;
	//----------Ÿ�ݹ޾����� �и��� ����----------//
	m_fMonster_PushDirect = fDirect;
	//----------Ÿ�ݹ޾����� ���� ��ġ ����----------//
	m_vecMonster_PushSavePos = HTvector3( 0, 0, 0 );
//	m_vecMonster_PushSavePos = m_vecMonsterResentPos;
}

//----------Ÿ�ݰ� ���� �зȴٰ� ���ƿ���_��Ʈ��----------//
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

//----------���� �Ҷ� �Ÿ� ���߾� �ֱ�----------//
HTvoid CHTMoveMonSter::HT_vMonsterMove_AttackDistanceCheck( HTint nX, HTint nZ, HTvector3 vecCharPos )
{
	//if( m_iMonsterphysical_CellX == nX && m_iMonsterphysical_CellZ == nZ )
	//	return;

	//	2. �������� ��ǥ�� ���ϰ�, �̵��� ���߰�,
	HT_CELL_COORD crdCell;
	crdCell.x = m_iMonsterlogical_CellX = nX;
	crdCell.y = m_iMonsterlogical_CellZ = nZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterResentPos, crdCell );

	//---------������ �������� ����ġ�� ����Ѵ�.----------//
	HT_vMonsterCellPositionCheck();

	m_bMonsterMoveState = HT_FALSE;

	//	3. �з������� �Ÿ��� ���ϰ�
	HTfloat fTempDistance;
	if( m_bMonsterSize == 1 )
		fTempDistance = (HTfloat)( m_bMonsterSize * 10 );
	else
        fTempDistance = (HTfloat)( ( m_bMonsterSize * 10 ) - ( m_bMonsterSize * 2 ) );
	//	4. �з��� ������ ���ϰ�
	HTvector3 vecPos = m_vecMonsterResentPos - vecCharPos;
	HTfloat fTempDirect = HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	//	5. ĳ���Ϳ��� ���� �Ÿ��� ���ϰ�
	HTfloat fCurDistance = (float)sqrt( double( ((m_vecMonsterResentPos.x - vecCharPos.x) * (m_vecMonsterResentPos.x - vecCharPos.x))+
		((m_vecMonsterResentPos.z - vecCharPos.z) * (m_vecMonsterResentPos.z - vecCharPos.z)) ) );
	//	6. ���� �̵��ؾ� �� �Ÿ��� ���ϰ�
	HTfloat fMoveDistance = fTempDistance - fCurDistance;
	//	7. ���ǿ� �մ��ϸ� �̵���������
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

//----------�̵� ����----------//
HTvoid CHTMoveMonSter::HT_vMoveMonster_MoveSetting( HTint nX, HTint nZ, HTfloat fSpeed )
{
	if( m_iMonsterphysical_CellX == nX && m_iMonsterphysical_CellZ == nZ )
		return;

	//	�̵� ����
	m_bMonsterMoveState			= HT_TRUE;

	//	������ ��ǥ ����
	HT_CELL_COORD crdCell;
	crdCell.x = nX;
	crdCell.y = nZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecMonsterTargetPos, crdCell );
	//	������ġ ���ϱ�
	m_vecMonsterStartPos = m_vecMonsterResentPos;

	//	���ⱸ�ϱ�
	HTvector3 vecVector = m_vecMonsterTargetPos - m_vecMonsterResentPos;
	m_fMonsterResentDirect = HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;

	//	���� �� �Ÿ� ��ȭ
	m_fMonster_Distance = (float)sqrt( double( ((m_vecMonsterTargetPos.x - m_vecMonsterResentPos.x) * (m_vecMonsterTargetPos.x - m_vecMonsterResentPos.x))+
											   ((m_vecMonsterTargetPos.z - m_vecMonsterResentPos.z) * (m_vecMonsterTargetPos.z - m_vecMonsterResentPos.z)) ) );
	m_fMonster_Distance_Trans		= 0;

	//	���ǵ� ����
	m_fMonsterSpeedValue = fSpeed;

	//	������� ��ȭ��
	m_fMonster_EOTransValue = 1;
	//	�ð� ��ȭ��
	m_fMonster_TimeTransValue = 0;
	//	��ü �ð�
	m_fMonster_TotalTime = m_fMonster_Distance * MAP_CELL_SIZE;
}

//----------�����ϰ� ��ȯ��----------//
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