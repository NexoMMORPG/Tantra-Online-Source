#pragma once

#ifndef _HTMOVENPC_H_
#define _HTMOVENPC_H_


class CHTNPCMove
{
public:
	CHTNPCMove(void);
	~CHTNPCMove(void);

/*
1. 초기화
2. 이동 -> 정지 -> 이동 -> 정지 
3. 클릭
4. 캐릭터를 바라본다
5. 다른 인풋이 들어오면 다시 2번으로
*/

	HTvoid						HT_vNPCMoveInit( HTint nX, HTint nZ, HTfloat fSpeed );
	HTfloat						HT_fNPCMoveGetAngle( HTvector3 A, HTvector3 B );
	HTint						HT_vNPCMove_Control();
	HTRESULT					HT_vNPCMove_StopControl();
	HTvoid						HT_vNPCMove_SetTarget();
	HTvoid						HT_vNPCMove_MoveControl();
	HTvoid						HT_vNPCMove_StopCheck();

	HTvoid						HT_vNPCMove_Click();
	HTvoid						HT_vNPCMove_Unclick();
	HTvoid						HT_vNPCMove_OtherInput() { m_bNPC_Click_Sw = HT_FALSE; };
	
	HTvector3					HT_vecNPCMove_GetPos() { return m_vecNPC_ResentPos; };
	HTfloat						HT_fNPCMove_GetDirect() { return m_fNPC_Direct; };
	HTPoint						HT_pGetNPCGrid();

public:

	HTPoint						m_pPatrol_Node[10];			//	패트롤 노드
	HTint						m_nPatrol_Count;			//	패티롤 노드 카운트
	HTint						m_nPatrol_Limit;			//	패트롤 노드 한계
	HTvector3					m_vecNPC_ResentPos;			//	현재 위치
	HTvector3					m_vecNPC_TargetPos;			//	목표 위치
	DWORD						m_dwMoveDelayTime;			//	이동 하고 잠시 정지한 타임
	DWORD						m_dwStopTime;				//	정지한 시점의 시간
	DWORD						m_dwPassedTime;				//  이미 지나간 시간(초기화때 랜덤으로 설정)
	HTbool						m_bMove_Sw;					//	이동:TRUE, 정지:FALSE
	HTfloat						m_fNPC_Direct;				//	NPC의 방향
	HTfloat						m_fNPC_Speed;				//	스피드

	HTfloat						m_fNPC_Distance;			//	이동 해 갈 거리
	HTfloat						m_fNPC_Distance_Trans;		//	이동 해 갈 거리 변화

	HTbool						m_bNPC_Click_Sw;			//	캐릭터가 NPC를 클릭했을 때

};

#endif
