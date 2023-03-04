
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
	float sp= A.x*B.x + A.z*B.z;					//	내적구하기 -> 벡터의 관계(각도)를 알기 위해
	float sqrt_A = (float)sqrt( (float)(A.x*A.x + A.z*A.z) );	//  A 벡터의 절대값(길이) 구하기 
	float sqrt_B = (float)sqrt( (float)(B.x*B.x + B.z*B.z) );	//  B 벡터의 절대값(길이) 구하기 

	// By HK : 내적 공식을 이용해서 두 사잇각을 구하고자 할 경우에
	// 나누기 연산이 포함되어야 하는데, 분모가 0이거나 또는 매우 근접하는 값이 되는 경우에
	// 나누기 연산에서 devide by zero와 같은 문제가 발생할 수 있다.
	// 그렇기 때문에 이 경우에는 그냥 사잇각을 0으로 리턴한다.
	// 이와 같은 문제를 피하기 위해 본래 특정 object를 회전시키고자 할 경우에
	// parameter로 각을 사용하는 것이 아니라 방향 vector를 사용하는 것이 보통이다.
	// 현 탄트라 엔진에서 이와 같은 구조로 변경하는 것은 많은 시간과 테스트가 필요할 것으로 예상되므로
	// 이와 같이 임시로 처리한다.
	if ( sqrt_A < HT_EPSILON || sqrt_B < HT_EPSILON )
	{
		return 0.0f;
	}

	float cos = sp / (sqrt_A * sqrt_B);				//  세값을 이용해서 각도 구하기

	float acos = acosf( cos );						//	코사인값을 라디안값 바꾸기
	float direction = A.z*B.x - B.z*A.x;			//	왼쪽 오른쪽 비교
	if(direction < 0)								//	dirction 음이면 왼쪽 , 양이면 오른쪽
		acos *= -1;
	return acos;
}

//	NPC 무빙 이니트
HTvoid CHTNPCMove::HT_vNPCMoveInit( HTint nX, HTint nZ, HTfloat fSpeed )
{
	//	패트롤 노드 Setting
	m_pPatrol_Node[0].x			= nX;
	m_pPatrol_Node[0].y			= nZ;

	// 약간의 변화를 줌 20030222Tenma
	m_pPatrol_Node[1].x			= m_pPatrol_Node[0].x + (rand()%10 -5);
	m_pPatrol_Node[1].y			= m_pPatrol_Node[0].y + (rand()%10 -5);

	m_nPatrol_Count				= 0;				//	패티롤 노드 카운트
	m_nPatrol_Limit				= 2;				//	패트롤 노드 한계			

	//	현재 위치
	HT_CELL_COORD crdCell;
	crdCell.x					= nX;
	crdCell.y					= nZ;
    g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecNPC_ResentPos, crdCell );

	//	건물에 의한 높이 조절
	m_vecNPC_ResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecNPC_ResentPos.x, m_vecNPC_ResentPos.z );
	
	m_dwMoveDelayTime			= 5000 + (rand()%10000);	//	이동 하고 잠시 정지한 타임
	m_dwStopTime				= GetTickCount();	//	정지한 시점의 시간
	m_bMove_Sw					= HT_FALSE;			//	이동:HT_TRUE, 정지:HT_FALSE
	m_fNPC_Direct				= HT_PIX2;			//	NPC의 방향

	m_bNPC_Click_Sw				= HT_FALSE;//	캐릭터가 NPC를 클릭했을 때

	m_dwPassedTime = rand()%m_dwMoveDelayTime;

	//	스피드 셋팅
	m_fNPC_Speed = fSpeed;

	HT_vNPCMove_SetTarget();
}

//	NPC 무빙 컨트롤
HTint CHTNPCMove::HT_vNPCMove_Control()
{
	//	캐릭터가 NPC를 클릭했을 때
	if( m_bNPC_Click_Sw	== HT_TRUE )
		return 1;

	//	NPC 무빙 정지컨트롤
	if( HT_SUCCEED( HT_vNPCMove_StopControl() ) )
		return 1;

	if( m_bMove_Sw == HT_TRUE )
	{
		//	NPC 무빙 이동컨트롤
		HT_vNPCMove_MoveControl();
		//	NPC 정지 체크
		HT_vNPCMove_StopCheck();
	}

	return 2;
}

//	NPC 무빙 정지컨트롤
HTRESULT CHTNPCMove::HT_vNPCMove_StopControl()
{
	if( m_bMove_Sw == HT_TRUE )
		return HT_FAIL;

	DWORD dwPassTime = m_dwPassedTime + GetTickCount();

    if( dwPassTime >= m_dwStopTime + m_dwMoveDelayTime )
	{
		//	NPC 이동 타겥 지정
		HT_vNPCMove_SetTarget();
	}
    
	return HT_OK;
}

//	NPC 이동 타겥 지정
HTvoid CHTNPCMove::HT_vNPCMove_SetTarget()
{
	m_bMove_Sw					= HT_TRUE;			//	이동:HT_TRUE, 정지:HT_FALSE

	//	패트롤 노드 증가
	m_nPatrol_Count++;
	if( m_nPatrol_Count == m_nPatrol_Limit )
		m_nPatrol_Count = 0;

	//	목적지 좌표 셋팅
	HT_CELL_COORD crdCell;
	crdCell.x = m_pPatrol_Node[m_nPatrol_Count].x;
	crdCell.y = m_pPatrol_Node[m_nPatrol_Count].y;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( m_vecNPC_TargetPos, crdCell );

	//	방향구하기
	HTvector3 vecVector = m_vecNPC_TargetPos - m_vecNPC_ResentPos;
	m_fNPC_Direct = HT_fNPCMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;

	//	공격 갈 거리 변화
	m_fNPC_Distance = (float)sqrt( double( ((m_vecNPC_TargetPos.x - m_vecNPC_ResentPos.x) * (m_vecNPC_TargetPos.x - m_vecNPC_ResentPos.x))+
										   ((m_vecNPC_TargetPos.z - m_vecNPC_ResentPos.z) * (m_vecNPC_TargetPos.z - m_vecNPC_ResentPos.z)) ) );
	m_fNPC_Distance_Trans		= 0;
}

//	NPC 무빙 이동컨트롤
HTvoid CHTNPCMove::HT_vNPCMove_MoveControl()
{
	//	이동해가기
	float fx, fz;

	fx = sinf( m_fNPC_Direct ) * ( m_fNPC_Speed );
	fz = cosf( m_fNPC_Direct ) * ( m_fNPC_Speed );

	m_vecNPC_ResentPos.x += fx;
	m_vecNPC_ResentPos.z += fz;
	m_vecNPC_ResentPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecNPC_ResentPos.x, m_vecNPC_ResentPos.z );

	m_fNPC_Distance_Trans += HT_ABS(fx) + HT_ABS(fz);
}

//	NPC 정지 체크
HTvoid CHTNPCMove::HT_vNPCMove_StopCheck()
{
	if( m_fNPC_Distance_Trans > m_fNPC_Distance )
	{
		m_dwStopTime				= GetTickCount();	//	정지한 시점의 시간
		m_bMove_Sw					= HT_FALSE;			//	이동:HT_TRUE, 정지:HT_FALSE

		// 약간의 변화를 줌 20030222Tenma
		m_dwMoveDelayTime			= 5000 + (rand()%10000);	//	이동 하고 잠시 정지한 타임
		m_pPatrol_Node[1].x			= m_pPatrol_Node[0].x + (rand()%10 -5);
		m_pPatrol_Node[1].y			= m_pPatrol_Node[0].y + (rand()%10 -5);
	}
}

HTvoid CHTNPCMove::HT_vNPCMove_Click()
{
	//	캐릭터가 NPC를 클릭했을 때
	m_bNPC_Click_Sw	= HT_TRUE;

	HTvector3 vecCharPos = g_cMainCharacter->HT_vecGetPosition();

	//	방향구하기
	HTvector3 vecVector = vecCharPos - m_vecNPC_ResentPos;
	m_fNPC_Direct = HT_fNPCMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector ) + HT_PIX2;
}

HTvoid CHTNPCMove::HT_vNPCMove_Unclick()
{
	//	캐릭터가 NPC와 대화를 끝냈을 때
	m_bNPC_Click_Sw	= HT_FALSE;
}

HTPoint CHTNPCMove::HT_pGetNPCGrid()
{
	HTPoint NPCGrid;

	NPCGrid.x = m_pPatrol_Node[0].x / 4;
	NPCGrid.y = m_pPatrol_Node[0].y / 4;

	return NPCGrid;
}

