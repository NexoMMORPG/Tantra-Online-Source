
#ifndef _HTOTHERCHARACTERMOVE_H_
#define _HTOTHERCHARACTERMOVE_H_

#define OTHERCHARMOVE_STAND				0
#define OTHERCHARMOVE_GO				1
#define OTHERCHARMOVE_CORRECTION		2



class CHTOtherCharMove
{
public:
	CHTOtherCharMove();
	~CHTOtherCharMove();
	
	HTvoid						HT_vOtherCharSetInitSpeed( BYTE byCharType );
	HTvoid						HT_vOtherCharSetSpeed();
	HTvoid						HT_vOtherCharSetSpeedItem( DWORD );
	HTvoid						HT_vOtherCharSetSpeedItemUp( HTfloat );
	HTvoid						HT_vOtherCharSetSpeedSkill( DWORD, BYTE );

	//=====		두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터
	HTfloat						HT_fOtherCharMoveGetAngle( HTvector3 A, HTvector3 B );
	//	목표셀 계산_바뀐 이후
	HTvoid						HT_vOtherCharMoveCheckTargetCell( MSG_Action* info );
	HTvoid 						HT_vOtherCharMoveGo( HTfloat fElapsedTime );
	HTbool						HT_vOtherCharMoveStopCheck();
	HTvoid						HT_vOtherCharMoveCorrection();
	HTvoid						HT_vOtherCharMoveStop();					//	멈추기
	HTvoid						HT_vOtherCharMovephysicalCellMoveCheck();	//	물리적인 셀의 이동 위해
	
	//----------셋팅 및 반환값들----------//
    HTvector3					HT_fGetOtherCharMovePos();
	HTvoid						HT_fSetOtherCharMovePos( HTvector3 );
	HTPoint						HT_pGeOtherCharMoveGrid();
	HTvoid						HT_fSetOtherCharMovelogical_CellPos( HTint, HTint );
	HTvoid						HT_fSetOtherCharMovephysical_CellPos( HTint, HTint );
	HTvoid						HT_vGetOtherCharMove_physicalCellPos( HTPoint* );
	HTfloat						HT_fGetOtherCharMoveSpeed();
	HTfloat						HT_fGetOtherCharMoveDirect();				//	OtherChar 방향
	HTvoid						HT_vSetOtherCharMoveDirect( HTfloat );		//	OtherChar 방향
	HTfloat						HT_fGetOtherCharMoveDirectCal();			//	OtherChar 방향 실시간 계산
	HTfloat						HT_fGetOtherCharTargetToResentDis();		//	목표점과 현재점의 차이를 계산

protected:
	HTfloat						m_fOtherCharResentDirect;
	HTvector3					m_vecOtherCharResentPos;
	HTvector3					m_vecOtherCharTargetPos;
	HTvector3					m_vecOtherCharStartPos;
	
	HTfloat						m_fBasicSpeedWalk;
	HTfloat						m_fBasicSpeedRun;
	HTfloat						m_fSpeedItem;
	HTfloat						m_fSpeedItemUp;
	HTfloat						m_fSpeedSkill;
	HTfloat						m_fSpeedWalk;
	HTfloat						m_fSpeedRun;
	HTfloat						m_fOtherCharSpeedValue;
	BYTE						m_byOtherCharMoveState;

public:
	HTint						m_iOtherCharMove_State;			//	0:정지,1:이동,2:보정
	HTint						m_iOtherCharphysical_CellX;
	HTint						m_iOtherCharphysical_CellZ;
	HTint						m_iOtherCharlogical_CellX;
	HTint						m_iOtherCharlogical_CellZ;

	HTfloat						m_fOtherCharMove_EOTransValue;		//	상대적인 변화량
	HTfloat						m_fOtherCharMove_TimeTransValue;	//	시간 변화량
	HTfloat						m_fOtherCharMove_TotalTime;			//	전체 시간
};

#endif
