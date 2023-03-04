
#ifndef _HTMOVEMONSTER_H_
#define _HTMOVEMONSTER_H_



class CHTMoveMonSter
{
public:
	CHTMoveMonSter();
	~CHTMoveMonSter();
	
	HTvoid						HT_vMoveMonSterInit();

	//=====		두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터
	HTfloat						HT_fMonsterGetAngle( HTvector3 A, HTvector3 B );
	HTvoid 						HT_vMonsterTransDirect();
	HTvoid						HT_vMonsterCalVelocity();
	HTvoid 						HT_vMonsterMoving( HTfloat );
	HTvoid 						HT_bMonsterCheckMove();
	HTvoid						HT_vecMonsterStopMove();
	HTvoid						HT_vMonsterCellPositionCheck(); //	몬스터의 물리적인 셀위치를 계산한다
	HTvoid						HT_vMonsterMove_SetEnd( HTint, HTint, HTint );

	HTvoid						HT_vMonsterMove_Correction();				//	보정해주기

	//----------방향 회전시키기 위하여----------//
	HTvoid						HT_vMonsterMoveAngleCheck( HTfloat );
	HTvoid						HT_vMonsterMoveAngleTransing();

	//----------타격감 관련 밀렸다가 돌아오기_셋팅----------//
	HTvoid						HT_vMonsterMove_HitPushMoveSetting( HTfloat );
	//----------타격감 관련 밀렸다가 돌아오기_컨트롤----------//
	HTvoid						HT_vMonsterMove_HitPushMove();

	//----------공격 할때 거리 맞추어 주기----------//
	HTvoid						HT_vMonsterMove_AttackDistanceCheck( HTint, HTint, HTvector3 );

	//----------이동 셋팅----------//
	HTvoid						HT_vMoveMonster_MoveSetting( HTint, HTint, HTfloat );

	//----------셋팅하고 반환값----------//
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

	short						m_iMonsterlogical_CellX;	//	몬스터의 논리적인 셀
	short						m_iMonsterlogical_CellZ;	//	몬스터의 논리적인 셀
	short						m_iMonsterphysical_CellX;	//	몬스터의 물리적인 셀
	short						m_iMonsterphysical_CellZ;	//	몬스터의 물리적인 셀
	BYTE						m_bMonsterSize;

	HTfloat						m_fMonster_Distance;			//	이동 해 갈 거리
	HTfloat						m_fMonster_Distance_Trans;		//	이동 해 갈 거리 변화

	BYTE						m_bMonster_StepType;			//	0x00:OneStep, 0x01:NStep
	
	//----------방향 회전시키기 위하여----------//
	HTint						m_bAngleTrans_Sw;
	HTfloat						m_fTransDirect;
	HTfloat						m_fTargetAngle;
	HTfloat						m_fPlusAngle;
	HTfloat						m_fMinusAngle;

	//----------맞았을때 이동정보 저장하기기 위해----------//
	HTfloat						m_fMonsterResentDirect_Temp;
	HTfloat						m_fMonsterSpeedValue_Temp;
	HTfloat						m_fMonster_Distance_Temp;
	HTfloat						m_fMonster_Distance_Trans_Temp;

	//----------타격받았을때 밀리는 동작----------//
	HTbool						m_bMonster_Push_Sw;
	//----------타격받았을때 밀리는 왕복 동작----------//
	HTbool						m_bMonster_PushReturn_Sw;
	//----------타격받았을때 밀리는 거리----------//
	HTfloat						m_fMonster_PushDis;
	//----------타격받았을때 밀리는 거리를 계산하기 위해----------//
	HTfloat						m_fMonster_PushDis_Trans;
	//----------타격받았을때 밀리갈 방향----------//
	HTfloat						m_fMonster_PushDirect;
	//----------타격받았을때 예전 위치 저장----------//
	HTvector3					m_vecMonster_PushSavePos;


	HTfloat						m_fMonster_EOTransValue;		//	상대적인 변화량
	HTfloat						m_fMonster_TimeTransValue;		//	시간 변화량
	HTfloat						m_fMonster_TotalTime;			//	전체 시간
    	

public:
	HTbool						m_bMonsterMoveState;
	HTint						m_iMonsterSpeedGrade;

};

#endif