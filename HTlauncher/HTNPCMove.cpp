
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htnpcmove.h"


CHTNPCMove::CHTNPCMove(void)
{
	srand(time(NULL));
}

CHTNPCMove::~CHTNPCMove(void)
{
}

HTfloat CHTNPCMove::HT_fNPCMoveGetAngle( HTvector3 A, HTvector3 B )
{
	float sp= A.x*B.x + A.z*B.z;					//	�������ϱ� -> ������ ����(����)�� �˱� ����
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A ������ ���밪(����) ���ϱ� 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B ������ ���밪(����) ���ϱ� 

	// By HK : ���� ������ �̿��ؼ� �� ���հ��� ���ϰ��� �� ��쿡
	// ������ ������ ���ԵǾ�� �ϴµ�, �и� 0�̰ų� �Ǵ� �ſ� �����ϴ� ���� �Ǵ� ��쿡
	// ������ ���꿡�� devide by zero�� ���� ������ �߻��� �� �ִ�.
	// �׷��� ������ �� ��쿡�� �׳� ���հ��� 0���� �����Ѵ�.
	// �̿� ���� ������ ���ϱ� ���� ���� Ư�� object�� ȸ����Ű���� �� ��쿡
	// parameter�� ���� ����ϴ� ���� �ƴ϶� ���� vector�� ����ϴ� ���� �����̴�.
	// �� źƮ�� �������� �̿� ���� ������ �����ϴ� ���� ���� �ð��� �׽�Ʈ�� �ʿ��� ������ ����ǹǷ�
	// �̿� ���� �ӽ÷� ó���Ѵ�.
	if ( sqrt_A < HT_EPSILON || sqrt_B < HT_EPSILON )
	{
		return 0.0f;
	}

	float cos = sp / (sqrt_A * sqrt_B);				//  ������ �̿��ؼ� ���� ���ϱ�

	float acos = acosf( cos );						//	�ڻ��ΰ��� ���Ȱ� �ٲٱ�
	float direction = A.z*B.x - B.z*A.x;			//	���� ������ ��
	if(direction < 0)								//	dirction ���̸� ���� , ���̸� ������
		acos *= -1;
	return acos;
}

//	NPC ���� �̴�Ʈ
HTvoid CHTNPCMove::HT_vNPCMoveInit( HTint nX, HTint nZ, HTfloat fSpeed )
{
	//	��Ʈ�� ��� Setting
	m_pPatrol_Node[0].x			= nX;
	m_pPatrol_Node[0].y			= nZ;

	// �ణ�� ��ȭ�� �� 20030222Tenma
	m_pPatrol_Node[1].x			= m_pPatrol_Node[0].x + (rand()%10 -5);
	m_pPatrol_Node[1].y			= m_pPatrol_Node[0].y + (rand()%10 -5);

	m_nPatrol_Count				= 0;				//	��Ƽ�� ��� ī��Ʈ
	m_nPatrol_Limit				= 2;				//	��Ʈ�� ��� �Ѱ�			

	//	���� ��ġ
	HT_CELL_COORD crdCell;
	crdCell.x					= nX;
	crdCell.y					= nZ;
    g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecNPC_ResentPos, crdCell );

	//	�ǹ��� ���� ���� ����
	m_vecNPC_ResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecNPC_ResentPos.x, m_vecNPC_ResentPos.z );
	
	m_dwMoveDelayTime			= 5000 + (rand()%10000);	//	�̵� �ϰ� ��� ������ Ÿ��
	m_dwStopTime				= GetTickCount();	//	������ ������ �ð�
	m_bMove_Sw					= HT_FALSE;			//	�̵�:HT_TRUE, ����:HT_FALSE
	m_fNPC_Direct				= HT_PIX2;			//	NPC�� ����

	m_bNPC_Click_Sw				= HT_FALSE;//	ĳ���Ͱ� NPC�� Ŭ������ ��

	m_dwPassedTime = rand()%m_dwMoveDelayTime;

	//	���ǵ� ����
	m_fNPC_Speed = fSpeed;

	HT_vNPCMove_SetTarget();
}

//	NPC ���� ��Ʈ��
HTint CHTNPCMove::HT_vNPCMove_Control()
{
	//	ĳ���Ͱ� NPC�� Ŭ������ ��
	if( m_bNPC_Click_Sw	== HT_TRUE )
		return 1;

	//	NPC ���� ������Ʈ��
	if( HT_SUCCEED( HT_vNPCMove_StopControl() ) )
		return 1;

	if( m_bMove_Sw == HT_TRUE )
	{
		//	NPC ���� �̵���Ʈ��
		HT_vNPCMove_MoveControl();
		//	NPC ���� üũ
		HT_vNPCMove_StopCheck();
	}

	return 2;
}

//	NPC ���� ������Ʈ��
HTRESULT CHTNPCMove::HT_vNPCMove_StopControl()
{
	if( m_bMove_Sw == HT_TRUE )
		return HT_FAIL;

	DWORD dwPassTime = m_dwPassedTime + GetTickCount();

    if( dwPassTime >= m_dwStopTime + m_dwMoveDelayTime )
	{
		//	NPC �̵� Ÿ�� ����
		HT_vNPCMove_SetTarget();
	}
    
	return HT_OK;
}

//	NPC �̵� Ÿ�� ����
HTvoid CHTNPCMove::HT_vNPCMove_SetTarget()
{
	m_bMove_Sw					= HT_TRUE;			//	�̵�:HT_TRUE, ����:HT_FALSE

	//	��Ʈ�� ��� ����
	m_nPatrol_Count++;
	if( m_nPatrol_Count == m_nPatrol_Limit )
		m_nPatrol_Count = 0;

	//	������ ��ǥ ����
	HT_CELL_COORD crdCell;
	crdCell.x = m_pPatrol_Node[m_nPatrol_Count].x;
	crdCell.y = m_pPatrol_Node[m_nPatrol_Count].y;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecNPC_TargetPos, crdCell );

	//	���ⱸ�ϱ�
	HTvector3 vecVector = m_vecNPC_TargetPos - m_vecNPC_ResentPos;
	m_fNPC_Direct = HT_fNPCMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;

	//	���� �� �Ÿ� ��ȭ
	m_fNPC_Distance = (float)sqrt( double( ((m_vecNPC_TargetPos.x - m_vecNPC_ResentPos.x) * (m_vecNPC_TargetPos.x - m_vecNPC_ResentPos.x))+
										   ((m_vecNPC_TargetPos.z - m_vecNPC_ResentPos.z) * (m_vecNPC_TargetPos.z - m_vecNPC_ResentPos.z)) ) );
	m_fNPC_Distance_Trans		= 0;
}

//	NPC ���� �̵���Ʈ��
HTvoid CHTNPCMove::HT_vNPCMove_MoveControl()
{
	//	�̵��ذ���
	float fx, fz;

	fx = sinf( m_fNPC_Direct ) * ( m_fNPC_Speed );
	fz = cosf( m_fNPC_Direct ) * ( m_fNPC_Speed );

	m_vecNPC_ResentPos.x += fx;
	m_vecNPC_ResentPos.z += fz;
	m_vecNPC_ResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecNPC_ResentPos.x, m_vecNPC_ResentPos.z );

	m_fNPC_Distance_Trans += HT_ABS(fx) + HT_ABS(fz);
}

//	NPC ���� üũ
HTvoid CHTNPCMove::HT_vNPCMove_StopCheck()
{
	if( m_fNPC_Distance_Trans > m_fNPC_Distance )
	{
		m_dwStopTime				= GetTickCount();	//	������ ������ �ð�
		m_bMove_Sw					= HT_FALSE;			//	�̵�:HT_TRUE, ����:HT_FALSE

		// �ణ�� ��ȭ�� �� 20030222Tenma
		m_dwMoveDelayTime			= 5000 + (rand()%10000);	//	�̵� �ϰ� ��� ������ Ÿ��
		m_pPatrol_Node[1].x			= m_pPatrol_Node[0].x + (rand()%10 -5);
		m_pPatrol_Node[1].y			= m_pPatrol_Node[0].y + (rand()%10 -5);
	}
}

HTvoid CHTNPCMove::HT_vNPCMove_Click()
{
	//	ĳ���Ͱ� NPC�� Ŭ������ ��
	m_bNPC_Click_Sw	= HT_TRUE;

	HTvector3 vecCharPos = g_cMainCharacter->HT_vecGetPosition();

	//	���ⱸ�ϱ�
	HTvector3 vecVector = vecCharPos - m_vecNPC_ResentPos;
	m_fNPC_Direct = HT_fNPCMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;
}

HTvoid CHTNPCMove::HT_vNPCMove_Unclick()
{
	//	ĳ���Ͱ� NPC�� ��ȭ�� ������ ��
	m_bNPC_Click_Sw	= HT_FALSE;
}

HTPoint CHTNPCMove::HT_pGetNPCGrid()
{
	HTPoint NPCGrid;

	NPCGrid.x = m_pPatrol_Node[0].x / 4;
	NPCGrid.y = m_pPatrol_Node[0].y / 4;

	return NPCGrid;
}

