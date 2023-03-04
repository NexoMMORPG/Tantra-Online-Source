#pragma once

#define OTHERCHARMOVE_STAND				0
#define OTHERCHARMOVE_GO				1
#define OTHERCHARMOVE_CORRECTION		2


class HTOtherObjectMove
{
public:
	HTOtherObjectMove(void);
	~HTOtherObjectMove(void);

	//	MoveSystem
	//	MoveSystem Recive Action Msg
	HTvoid						HT_vOtherObjectMove_MoveSystemReciveActionMsg( MSG_Action* info );
	//	MoveSystem Go
	HTvoid 						HT_vOtherObjectMove_MoveSystemGo( HTfloat fElapsedTime );
	//	MoveSystem StopCheck
	HRESULT						HT_hrOtherObjectMove_MoveSystemStopCheck();
	//	MoveSystem Stop
	HTvoid						HT_vOtherObjectMove_MoveSystemStop();
	//	Move Up/Down Control
	HTvoid						HT_vOtherObjectMove_UpDownControl();

	//	Setting
	//	Setting Cur CoodPos;
	HTvoid						HT_vOtherObjectMove_SetCurCoodPos( HTvector3 );
	//	Setting Cur CellPos
	HTRESULT					HT_hrOtherObjectMove_SetTargetCellPos( HTint, HTint );
	//	Setting Cur Direct
	HTvoid						HT_vOtherObjectMove_SetCurDirect( HTfloat );
	//	Setting Up/Down
	HTvoid						HT_vOtherObjectMove_SetUpDown( HTfloat fHight, HTfloat fSpeedHight, HTfloat fLimitHight, HTbool bAccelerationHightSw );

	//	Returns
	//	Returns Cur Pos
    HTvector3					HT_vecOtherObjectMove_GetCurCoodPos();
	//	Returns Cur Grid
	HTPoint						HT_pOtherObjectMove_GetGrid();
	//	Returns Cur Cell
	HTPoint						HT_pOtherObjectMove_GetCellPos();
	//	Returns Cur Speed
	HTfloat						HT_fOtherObjectMove_GetCurSpeed();
	//	Returns Cur Direct
	HTfloat						HT_fOtherObjectMove_GetDirect();
	//	Returns Cur Direct
	HTfloat						HT_fOtherObjectMove_GetDirectCal();
	//	Returns Cur TargetToResentTerm
    HTfloat						HT_fOtherObjectMove_GetOtherCharTargetToResentDis();

public:

	HTbyte						m_byMoveState;
	HTfloat						m_fApplySpeedValue;

	HTint						m_iPhysical_CellX;
	HTint						m_iPhysical_CellZ;
	HTint						m_iLogical_CellX;
	HTint						m_iLogical_CellZ;

	HTvector3					m_vecTargetPos;
	HTvector3					m_vecResentPos;
	HTvector3					m_vecStartPos;

	//	상대적인 변화량
	HTfloat						m_fEOTransValue;
	//	시간 변화량
	HTfloat						m_fTimeTransValue;
	//	전체 시간
	HTfloat						m_fTotalTime;
	//	방향
	HTfloat						m_fResentDirect;
	//	Move Effect
	short						m_snEffect;
	//	Move Up/Down Control
	HTfloat						m_fHight;
	HTfloat						m_fSpeedHight;
	HTfloat						m_fLimitHight;
	HTbool						m_bAccelerationHightSw;
};

