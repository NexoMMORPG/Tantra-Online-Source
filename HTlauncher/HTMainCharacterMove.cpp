
#include "stdAfx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTMainCharacterMove.h"


CHTMainCharMove::CHTMainCharMove()
{
	m_eMainChrMove_State		= HT_FALSE;
	m_fResDirect				= 0.0f;
	m_wSeqNum					= 0;
	m_nCharMove_ForwardCount	= 0;		//	Ű���� �̵��ÿ� ���ǵ� �¾��� ���� ī��Ʈ

	m_iSpeedResentWalk			= 0;
	m_iSpeedResentRun			= 0;
	m_byMoveType				= CHARACTER_SPEEDLEVEL_STOP;

	//	�̵��ӵ�
	g_byteSpeed1 = 0;
	g_byteSpeed2 = 0;
	g_byteSpeed3 = 0;
	g_byteSpeedCorrection = 0;
	g_byteSpeedParity = 0;
}


CHTMainCharMove::~CHTMainCharMove()
{
}

HTvoid CHTMainCharMove::HT_vSetInitSpeed( HTint nMoveSpeed )
{
}

void CHTMainCharMove::HT_vMainCharMove_Init()
{
}

HTRESULT CHTMainCharMove::HT_hrMainCharMove_CanPos( HTvector3 vecPos )
{
	//	�̵� �Ұ� �������� üũ
	if( g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecPos, 0 ) == HT_FALSE )
	{
		return HT_FAIL;
	}

	//	OtherObject(Ư�� "��" �̵���)�� ���������� �浹üũ
	if( g_cOtherObjectSystem->HT_iOtherObjectSystem_GetCheck2ObjCollide( 0, vecPos, 4.0f ) )
	{
		return HT_FAIL;
	}

	//	NPC�� �浹 üũ
	if( g_sNPCSystem->HT_iNPCSystem_GetCheck2ObjCollide( 0, vecPos, 4.0f ) )
	{
		return HT_FAIL;
	}

	return HT_OK;
}

//----------�̵����� ���� üũ----------//
HTRESULT CHTMainCharMove::HT_hrMainCharMove_CanMove()
{
	//	�ٷ� �ռ��� �̵��Ұ� �����̳�?
	HTvector3 vecTempPos;
	HTfloat fBeforeDis, fAfterDis;
	HTbool bCanMove = HT_TRUE;
	
	//	32�������� �ľ��Ѵ�. �ֳİ�,,, ��ȣȣȣȣ����������.. �����̴�.
	for( HTint i=0 ; i<32 ; i++ )
	{
		//	�Ÿ�üũ1
		fBeforeDis = HT_extern_fGetDisForTwoPoint( m_vecCollidePos, m_vecResentPos );

		//	������ ������ ���� �����صΰ�
		m_vecCollidePos.x += sinf( m_fResDirect ) * ( 7.0f );
		m_vecCollidePos.z += cosf( m_fResDirect ) * ( 7.0f );

		if( HT_FAILED( this->HT_hrMainCharMove_CanPos( m_vecCollidePos ) ) )
		{
			bCanMove = HT_FALSE;
			break;
		}

		//	�Ÿ�üũ2
		fAfterDis = HT_extern_fGetDisForTwoPoint( m_vecCollidePos, m_vecResentPos );

		//	�־����� ��ŵ
		if( fBeforeDis < fAfterDis )
			break;
	}

	//	�̵��Ҽ� ���� �����̸�
	if( !bCanMove )
	{
		//	üũ�� ���⿡�� �ѽ��� �����Ͽ� ��ġ�� �����ϰ�
		m_vecCollidePos.x -= sinf( m_fResDirect ) * ( 7.0f );
		m_vecCollidePos.z -= cosf( m_fResDirect ) * ( 7.0f );
		m_vecResentPos = m_vecCollidePos;

		//----------�̵��ϴ� ���� ���� ������ �÷��ֱ� ����----------//
		HT_CELL_COORD codCell2;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, codCell2 );
		m_sResentCellX = codCell2.x;
		m_sResentCellZ = codCell2.y;
		return HT_FAIL;
	}

	return HT_OK;
}

//----------��ǥ�� ���----------//
void CHTMainCharMove::HT_vMainCharMove_CheckTargetCell( HTvector3 pos, HTint iSpeedGrade )
{
	//	�̵� ����
	m_eMainChrMove_State = HT_TRUE;
	// iSpeedGrade�� ���� �ٸ� �ӵ��� �����Ѵ�.
	m_byMoveType = iSpeedGrade;

	m_vecTargetPos = pos;
	m_vecTargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecTargetPos.x, m_vecTargetPos.z );

	//	Ű���� & ���콺 �̵����� üũ
	m_byCharMove_ForwardSw = HT_FALSE;
	//	�� ��ġ
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecTargetPos, crdCell );
	m_pTargetCell.x = crdCell.x;
	m_pTargetCell.y = crdCell.y;

	//	���� ����
	HTvector3 vecTemp = m_vecTargetPos - m_vecResentPos;
	m_fResDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecTemp ) + HT_PIX2;
	this->HT_vSetDirectRadin();

	//	�̵��ذ� �Ÿ�
	float fx = (float)sqrt( double( (m_vecResentPos.x - m_vecTargetPos.x) * (m_vecResentPos.x - m_vecTargetPos.x) ) );
	float fz = (float)sqrt( double( (m_vecResentPos.z - m_vecTargetPos.z) * (m_vecResentPos.z - m_vecTargetPos.z) ) );
	m_fCharMove_Distance = fx + fz;
	//	ù���� ��ġ ����
	m_vecStartPos = m_vecResentPos;
	//	�ð����� �̵��� üũ
	//	������� ��ȭ��
	m_fCharMove_EOTransValue = 1;
	//	�ð� ��ȭ��
	m_fCharMove_TimeTransValue = 0;
	//	��ü �ð�
	m_fCharMove_TotalTime = m_fCharMove_Distance * MAP_CELL_SIZE;
}

//----------�̵��ϴ� ���� ���� ������ �÷��ֱ� ����----------//
HTbool CHTMainCharMove::HT_bMainCharMove_ServerMoveCheck()
{
	HTbool bNotMoveSw = HT_FALSE;
	short sTempCellX = 0;
	short sTempCellZ = 0;
	if( m_sResentCellX != m_sMemoryCellX || m_sResentCellZ != m_sMemoryCellZ )
	{
        m_sMemoryCellX = m_sResentCellX;
		m_sMemoryCellZ = m_sResentCellZ;
		return HT_TRUE;
	}
	else
        return HT_FALSE;
}

//----------��----------//
HTvoid CHTMainCharMove::HT_vMainCharMove_Moving( HTfloat fElapsedTime )
{
	if( fElapsedTime <= HT_EPSILON )
		return;

	//	�̵� �ӵ� üũ
	signed char byteSpeed;
	byteSpeed = (g_byteSpeed1 - 104) + (g_byteSpeed2 - 15) + (g_byteSpeed3 - 74);
	byteSpeed += (g_byteSpeedCorrection ^ 0xFF);

	signed char byteSpeedParityTest = 0;
	for ( signed char i = 0; i < 7; ++i )	// �̼��� 25�� ���� �ʴ´ٰ� ����
		byteSpeedParityTest += (( byteSpeed & (1<<i) ) != 0);

	if ( byteSpeedParityTest == g_byteSpeedParity )
	{
		// ������ üũ�� ���⿡ �ٽ� �ִ´�.

		switch( m_byMoveType )
		{
			case CHARACTER_SPEEDLEVEL_STOP:
				byteSpeed = 0;
				break;
			case CHARACTER_SPEEDLEVEL_WALK:
				byteSpeed = byteSpeed/2;
				break;
			case CHARACTER_SPEEDLEVEL_KNOCKBACK :
				byteSpeed = 10;
				break;
			case CHARACTER_SPEEDLEVEL_ZUBAS :
				byteSpeed = 40;
				break;
		}

		m_fCharMove_TimeTransValue += ( fElapsedTime * byteSpeed * MAP_CELL_SIZE * CHARACTER_SPEED_MAINCHARCORRECT );

		m_fCharMove_EOTransValue = 1 - ( m_fCharMove_TimeTransValue/m_fCharMove_TotalTime );
		if( m_fCharMove_EOTransValue < 0 )
			m_fCharMove_EOTransValue = 0;

		//	�浹üũ�� ���Ͽ� 
		m_vecCollidePos = m_vecResentPos;

		m_vecResentPos = ( m_vecStartPos*m_fCharMove_EOTransValue ) + ( m_vecTargetPos * (1-m_fCharMove_EOTransValue) );
		m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );

		//----------�̵��ϴ� ���� ���� ������ �÷��ֱ� ����----------//
		HT_CELL_COORD codCell2;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, codCell2 );
		m_sResentCellX = codCell2.x;
		m_sResentCellZ = codCell2.y;
	}
}

//----------������ ����----------//
HTvoid CHTMainCharMove::HT_vMainCharMove_Forward( HTbool bWalkRun_Sw, HTfloat fElapsedTime )
{
	if( m_eMainChrMove_State == HT_TRUE || fElapsedTime <= HT_EPSILON )
	{
		HT_vMainCharMove_StopMvoe();
		return;
	}

	//	�̵� �ӵ� üũ
	signed char byteSpeed;
	byteSpeed = (g_byteSpeed1 - 104) + (g_byteSpeed2 - 15) + (g_byteSpeed3 - 74);
	byteSpeed += (g_byteSpeedCorrection ^ 0xFF);

	signed char byteSpeedParityTest = 0;
	for ( signed char i = 0; i < 7; ++i )	// �̼��� 25�� ���� �ʴ´ٰ� ����
		byteSpeedParityTest += (( byteSpeed & (1<<i) ) != 0);

	if ( byteSpeedParityTest == g_byteSpeedParity )
	{
		// ������ üũ�� ���⿡ �ٽ� �ִ´�.

		//	�̵� ����
		if( bWalkRun_Sw == HT_FALSE )
		{
			m_byMoveType = CHARACTER_SPEEDLEVEL_WALK;
			byteSpeed = byteSpeed/2;
		}
		else
		{
			m_byMoveType = CHARACTER_SPEEDLEVEL_RUN;
		}

		//----------��----------//
		float fx, fz;
		fx = sinf( m_fResDirect ) * ( byteSpeed * fElapsedTime * (CHARACTER_SPEED_MAINCHARCORRECT*0.8f) );
		fz = cosf( m_fResDirect ) * ( byteSpeed * fElapsedTime * (CHARACTER_SPEED_MAINCHARCORRECT*0.8f) );

		//	�浹üũ�� ���Ͽ� 
		m_vecCollidePos = m_vecResentPos;

		m_vecResentPos.x += fx;
		m_vecResentPos.z += fz;
		m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );

		//	Ű���� �̵��ÿ� ���ǵ� �¾��� ���� ī��Ʈ
		m_nCharMove_ForwardCount = 0;
		//	Ű���� & ���콺 �̵����� üũ
		m_byCharMove_ForwardSw = HT_TRUE;

		//----------�̵��ϴ� ���� ���� ������ �÷��ֱ� ����----------//
		HT_CELL_COORD codCell2;
		g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, codCell2 );
		m_sResentCellX = codCell2.x;
		m_sResentCellZ = codCell2.y;
	}
}

//----------ĳ������ �� ��ġ ���----------//
HTvoid CHTMainCharMove::HT_vMainCharMove_CellPositionCheck()
{
	//	Ű���� �̵��ÿ� ���ǵ� �¾��� ���� ī��Ʈ
	if( m_nCharMove_ForwardCount < 2)
        m_nCharMove_ForwardCount++;
	else
	{
		if( m_byCharMove_ForwardSw == HT_TRUE )
		{
			m_byMoveType = CHARACTER_SPEEDLEVEL_STOP;
			m_byCharMove_ForwardSw = HT_FALSE;
		}
	}
}

//----------��ǥ������ �����ϸ� ����----------//
HTbool CHTMainCharMove::HT_bMainCharMove_CheckMove()
{
	if( m_fCharMove_EOTransValue == 0 )
	{
		this->HT_vMainCharMove_StopMvoe();
		return HT_TRUE;
	}
	return HT_FALSE;
}


//-----------------------------------//
//----------�����ϰ� ��ȯ��----------//
//-----------------------------------//
HTvoid CHTMainCharMove::HT_vMainCharMove_SetSpeed( HTint iSpeedGrade )
{
	m_byMoveType = iSpeedGrade;
}

//	0x00:����ӵ�,0x01:�ȱ�ӵ�,0x02:�޸���ӵ�
HTint CHTMainCharMove::HT_iMainCharMove_GetSpeed( BYTE byType )
{
	//	�̵� �ӵ� üũ
	signed char byteSpeed;
	byteSpeed = (g_byteSpeed1 - 104) + (g_byteSpeed2 - 15) + (g_byteSpeed3 - 74);
	byteSpeed += (g_byteSpeedCorrection ^ 0xFF);

	signed char byteSpeedParityTest = 0;
	for ( signed char i = 0; i < 7; ++i )	// �̼��� 25�� ���� �ʴ´ٰ� ����
		byteSpeedParityTest += (( byteSpeed & (1<<i) ) != 0);

	if ( byteSpeedParityTest == g_byteSpeedParity )
	{
		// ������ üũ�� ���⿡ �ٽ� �ִ´�.
		if( byType == 0x00 )
		{
			if( m_byMoveType == CHARACTER_SPEEDLEVEL_STOP )
				return byteSpeed/2;
			else
				return byteSpeed;
		}
		else if( byType == 0x01 )
			return byteSpeed/2;
		else if( byType == 0x02 )
			return byteSpeed;
	}

	return byteSpeed;
}

HTvoid CHTMainCharMove::HT_vMainCharMove_StopMvoe()
{
	m_byMoveType = CHARACTER_SPEEDLEVEL_STOP;
	m_eMainChrMove_State = HT_FALSE;
}

HTvoid CHTMainCharMove::HT_vSetPosition( HTvector3 pos )
{
	m_vecResentPos = pos;
	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );
	m_vecCollidePos = m_vecResentPos;
}

HTvoid CHTMainCharMove::HT_vSetCellPosition( HTint x, HTint z )
{
	m_sResentCellX = x;
	m_sResentCellZ = z;

	//----------�̵��ϴ� ���� ���� ������ �÷��ֱ� ����----------//
	m_sMemoryCellX = m_sResentCellX;
	m_sMemoryCellZ = m_sResentCellZ;
}

HTPoint	CHTMainCharMove::HT_ptGetCellPosition()
{
	HTPoint pCellPos;
	pCellPos.x = m_sResentCellX;
	pCellPos.y = m_sResentCellZ;

	return pCellPos;
}

HTPoint CHTMainCharMove::HT_ptGetGridPosition()
{
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_vecResentPos, crdCell );

	HTPoint pGridPos;
	pGridPos.x = crdCell.x / 4;
	pGridPos.y = crdCell.y / 4;

	return pGridPos;
}

HTvector3 CHTMainCharMove::HT_vecGetPosition()
{
	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );
	return m_vecResentPos;
}

HTvector3 CHTMainCharMove::HT_vecGetTargetPosition()
{
	return m_vecTargetPos;
}

HTvoid CHTMainCharMove::HT_fSetDirect( HTfloat fDirect )
{
	m_fResDirect = fDirect;
}

HTvoid CHTMainCharMove::HT_fSetLeftRotate()
{
	m_fResDirect -= 0.1f;
	if( m_fResDirect <= HT_PI )
		m_fResDirect = HT_PIX2+HT_PI;

	HT_vSetDirectRadin();
}

HTvoid CHTMainCharMove::HT_fSetRightRotate()
{
	m_fResDirect +=0.1f;
	if( m_fResDirect >= HT_PIX2+HT_PI )
		m_fResDirect = HT_PI;

	HT_vSetDirectRadin();
}

HTvoid CHTMainCharMove::HT_vSetAttackDirct( HTvector3 vecEnemyPos )
{
	HTvector3 vecTemp = vecEnemyPos - m_vecResentPos;
	HTfloat fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecTemp ) + HT_PIX2;
	if( fDirect < 0.0f || fDirect > HT_PI*4 )
		return;
	else
	{
        m_fResDirect = fDirect;
	}
	
	HT_vSetDirectRadin();
}

BYTE CHTMainCharMove::HT_vGetDirectDirect()
{
	return m_byMoveInfoDir;
}

HTfloat CHTMainCharMove::HT_fGetDirect()
{
	return m_fResDirect;
}

HTvoid CHTMainCharMove::HT_vSetDirectRadin()
{
	m_fResRadin = (short)(360*( (m_fResDirect-HT_PI)/HT_PIX2 ));
}

WORD CHTMainCharMove::HT_vGetMoveSequenceNumber()
{
	return m_wSeqNum;
}


//-------------------------------------//
//----------��Ʈ���� �����Ͽ�----------//
//-------------------------------------//
//----------�������� ���� ���� ���� ������ ���� ������ ����� ��ġ�� ����----------//
HTvoid CHTMainCharMove::HT_vMainCharMove_NetWorkMoveFaild( HTint iX, HTint iZ )
{
	HT_CELL_COORD crdCell;
	crdCell.x = iX;
	crdCell.y = iZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecResentPos, crdCell );

	m_vecResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecResentPos.x, m_vecResentPos.z );

	m_wSeqNum = 0;
	HT_vMainCharMove_StopMvoe();

	this->HT_vSetCellPosition( iX, iZ );
}

