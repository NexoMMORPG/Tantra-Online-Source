
#ifndef _HTMOVEMONSTER_H_
#define _HTMOVEMONSTER_H_



class CHTMoveMonSter
{
public:
	CHTMoveMonSter();
	~CHTMoveMonSter();
	
	HTvoid						HT_vMoveMonSterInit();

	//=====		�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����
	HTfloat						HT_fMonsterGetAngle( HTvector3 A, HTvector3 B );
	HTvoid 						HT_vMonsterTransDirect();
	HTvoid						HT_vMonsterCalVelocity();
	HTvoid 						HT_vMonsterMoving( HTfloat );
	HTvoid 						HT_bMonsterCheckMove();
	HTvoid						HT_vecMonsterStopMove();
	HTvoid						HT_vMonsterCellPositionCheck(); //	������ �������� ����ġ�� ����Ѵ�
	HTvoid						HT_vMonsterMove_SetEnd( HTint, HTint, HTint );

	HTvoid						HT_vMonsterMove_Correction();				//	�������ֱ�

	//----------���� ȸ����Ű�� ���Ͽ�----------//
	HTvoid						HT_vMonsterMoveAngleCheck( HTfloat );
	HTvoid						HT_vMonsterMoveAngleTransing();

	//----------Ÿ�ݰ� ���� �зȴٰ� ���ƿ���_����----------//
	HTvoid						HT_vMonsterMove_HitPushMoveSetting( HTfloat );
	//----------Ÿ�ݰ� ���� �зȴٰ� ���ƿ���_��Ʈ��----------//
	HTvoid						HT_vMonsterMove_HitPushMove();

	//----------���� �Ҷ� �Ÿ� ���߾� �ֱ�----------//
	HTvoid						HT_vMonsterMove_AttackDistanceCheck( HTint, HTint, HTvector3 );

	//----------�̵� ����----------//
	HTvoid						HT_vMoveMonster_MoveSetting( HTint, HTint, HTfloat );

	//----------�����ϰ� ��ȯ��----------//
	HTvector3					HT_vecGetMonsterPos();
	HTPoint						HT_pGetMonsterCellPos();
	HTvoid						HT_fSetMonsterPos( HTvector3 );
	HTvoid						HT_fSetMonsterSize( BYTE );
	HTfloat						HT_fGetMonsterDirect();
	HTfloat						HT_fGetMonsterRotateDirect();
	HTvoid						HT_vSetMonsterDirect( HTfloat );
	HTvoid						HT_vSetMonsterlogical_Cell( short, short );
	HTvoid						HT_vSetMonsterphysical_Cell( short, short );
	HTPoint						HT_pGetMonsterGrid();
	HTbool						HT_pGetMonster_ResentMoveStatus();
	HTvoid						HT_vSetMonster_SetHitStop( HTbool );


public:
	HTfloat						m_fMonsterResentDirect;
	HTvector3					m_vecMonsterResentPos;
	HTvector3					m_vecMonsterTargetPos;
	HTvector3					m_vecMonsterVelocity;
	HTvector3					m_vecMonsterStartPos;

	HTfloat						m_fMonsterSpeedValue;

	short						m_iMonsterlogical_CellX;	//	������ ������ ��
	short						m_iMonsterlogical_CellZ;	//	������ ������ ��
	short						m_iMonsterphysical_CellX;	//	������ �������� ��
	short						m_iMonsterphysical_CellZ;	//	������ �������� ��
	BYTE						m_bMonsterSize;

	HTfloat						m_fMonster_Distance;			//	�̵� �� �� �Ÿ�
	HTfloat						m_fMonster_Distance_Trans;		//	�̵� �� �� �Ÿ� ��ȭ

	BYTE						m_bMonster_StepType;			//	0x00:OneStep, 0x01:NStep
	
	//----------���� ȸ����Ű�� ���Ͽ�----------//
	HTint						m_bAngleTrans_Sw;
	HTfloat						m_fTransDirect;
	HTfloat						m_fTargetAngle;
	HTfloat						m_fPlusAngle;
	HTfloat						m_fMinusAngle;

	//----------�¾����� �̵����� �����ϱ�� ����----------//
	HTfloat						m_fMonsterResentDirect_Temp;
	HTfloat						m_fMonsterSpeedValue_Temp;
	HTfloat						m_fMonster_Distance_Temp;
	HTfloat						m_fMonster_Distance_Trans_Temp;

	//----------Ÿ�ݹ޾����� �и��� ����----------//
	HTbool						m_bMonster_Push_Sw;
	//----------Ÿ�ݹ޾����� �и��� �պ� ����----------//
	HTbool						m_bMonster_PushReturn_Sw;
	//----------Ÿ�ݹ޾����� �и��� �Ÿ�----------//
	HTfloat						m_fMonster_PushDis;
	//----------Ÿ�ݹ޾����� �и��� �Ÿ��� ����ϱ� ����----------//
	HTfloat						m_fMonster_PushDis_Trans;
	//----------Ÿ�ݹ޾����� �и��� ����----------//
	HTfloat						m_fMonster_PushDirect;
	//----------Ÿ�ݹ޾����� ���� ��ġ ����----------//
	HTvector3					m_vecMonster_PushSavePos;


	HTfloat						m_fMonster_EOTransValue;		//	������� ��ȭ��
	HTfloat						m_fMonster_TimeTransValue;		//	�ð� ��ȭ��
	HTfloat						m_fMonster_TotalTime;			//	��ü �ð�
    	

public:
	HTbool						m_bMonsterMoveState;
	HTint						m_iMonsterSpeedGrade;

};

#endif