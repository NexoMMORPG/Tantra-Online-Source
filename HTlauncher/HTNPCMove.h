#pragma once

#ifndef _HTMOVENPC_H_
#define _HTMOVENPC_H_


class CHTNPCMove
{
public:
	CHTNPCMove(void);
	~CHTNPCMove(void);

/*
1. �ʱ�ȭ
2. �̵� -> ���� -> �̵� -> ���� 
3. Ŭ��
4. ĳ���͸� �ٶ󺻴�
5. �ٸ� ��ǲ�� ������ �ٽ� 2������
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

	HTPoint						m_pPatrol_Node[10];			//	��Ʈ�� ���
	HTint						m_nPatrol_Count;			//	��Ƽ�� ��� ī��Ʈ
	HTint						m_nPatrol_Limit;			//	��Ʈ�� ��� �Ѱ�
	HTvector3					m_vecNPC_ResentPos;			//	���� ��ġ
	HTvector3					m_vecNPC_TargetPos;			//	��ǥ ��ġ
	DWORD						m_dwMoveDelayTime;			//	�̵� �ϰ� ��� ������ Ÿ��
	DWORD						m_dwStopTime;				//	������ ������ �ð�
	DWORD						m_dwPassedTime;				//  �̹� ������ �ð�(�ʱ�ȭ�� �������� ����)
	HTbool						m_bMove_Sw;					//	�̵�:TRUE, ����:FALSE
	HTfloat						m_fNPC_Direct;				//	NPC�� ����
	HTfloat						m_fNPC_Speed;				//	���ǵ�

	HTfloat						m_fNPC_Distance;			//	�̵� �� �� �Ÿ�
	HTfloat						m_fNPC_Distance_Trans;		//	�̵� �� �� �Ÿ� ��ȭ

	HTbool						m_bNPC_Click_Sw;			//	ĳ���Ͱ� NPC�� Ŭ������ ��

};

#endif
