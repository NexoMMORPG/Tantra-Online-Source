
#ifndef _HTMAINCHARACTERMOVE_H_
#define _HTMAINCHARACTERMOVE_H_


#define	RETURN_AFTERCELL_NONE					0
#define	RETURN_AFTERCELL_MONSTER				1
#define	RETURN_AFTERCELL_NPC					2
#define	RETURN_AFTERCELL_OTHERCHAR				3
#define	RETURN_AFTERCELL_STRUCT					4


class CHTMainCharMove
{
public:
	CHTMainCharMove();
	~CHTMainCharMove();
	
	HTvoid						HT_vMainCharMove_Init();

	//----------이동가능 지역 체크----------//
	HTRESULT					HT_hrMainCharMove_CanPos( HTvector3 vecPos );
	HTRESULT					HT_hrMainCharMove_CanMove();
	HTvoid						HT_vMainCharMove_CheckTargetCell( HTvector3, HTint );	//	목표셀 계산
	HTvoid 						HT_vMainCharMove_Moving( HTfloat fElapsedTime );						//	고
	HTvoid 						HT_vMainCharMove_Forward( HTbool, HTfloat fElapsedTime );				//	앞으로 전진
	HTbool 						HT_bMainCharMove_CheckMove();					//	목표 도달 체크
	HTvoid						HT_vMainCharMove_StopMvoe();					//	멈추기
	HTvoid						HT_vMainCharMove_CellPositionCheck();			//	캐릭터의 셀 위치 계산
	HTbool						HT_bMainCharMove_ServerMoveCheck();				//	이동하는 셀의 정보 서버에 올려주기 위해

	HTvoid						HT_vMainCharMove_NetWorkMoveFaild( HTint iX, HTint iZ );		//	서버에서 이동 불가 내려받기
	

	//----------셋팅하고 반환값----------//
	HTvoid						HT_vSetInitSpeed( HTint );
	HTvoid						HT_vMainCharMove_SetSpeed( HTint );
	HTint						HT_iMainCharMove_GetSpeed( BYTE );		//	0x00:현재속도,0x01:걷기속도,0x02:달리기속도
	HTvoid					 	HT_vSetPosition( HTvector3 );
	HTvector3					HT_vecGetPosition();
	HTvector3				 	HT_vecGetTargetPosition();
	HTvoid					 	HT_vSetCellPosition( HTint, HTint );
	HTPoint					 	HT_ptGetCellPosition();
	HTPoint						HT_ptGetGridPosition();
	HTfloat					 	HT_fGetDirect();
	HTvoid					 	HT_fSetDirect( HTfloat );
	HTvoid					 	HT_fSetLeftRotate();
	HTvoid					 	HT_fSetRightRotate();
	HTvoid					 	HT_vSetAttackDirct( HTvector3 vecEnemyPos );
	BYTE						HT_vGetDirectDirect();
	HTvoid						HT_vSetDirectRadin();
	WORD						HT_vGetMoveSequenceNumber();
	HTPoint						HT_pGetAttackTargetCell()		{ return m_pTargetCell; };
    	
	WORD						m_wSeqNum;
protected:
	short						m_sMemoryCellX;
	short						m_sMemoryCellZ;
	short						m_sResentCellX;
	short						m_sResentCellZ;
	short						m_sAfterCellX;
	short						m_sAfterCellZ;
	BYTE						m_byMoveInfoDir;
	short						m_fResRadin;
	HTfloat						m_fResDirect;
	HTvector3					m_vecResentPos;
	HTvector3					m_vecTargetPos;
	HTvector3					m_vecStartPos;
	HTvector3					m_vecCollidePos;

	HTint						m_iSpeedResentWalk;
	HTint						m_iSpeedResentRun;
	BYTE						m_byMoveType;

	HTint						m_iForMoveEffect;

	HTPoint						m_pTargetCell;

	HTfloat						m_fAddDistance;

	HTfloat						m_fCharMove_Distance;			//	이동 해 갈 거리

	HTint						m_nCharMove_ForwardCount;		//	키보드 이동시에 스피드 셋업을 위한 카운트

	HTfloat						m_fCharMove_EOTransValue;		//	상대적인 변화량
	HTfloat						m_fCharMove_TimeTransValue;		//	시간 변화량
	HTfloat						m_fCharMove_TotalTime;			//	전체 시간

public:
	HTbool						m_eMainChrMove_State;
	HTbool						m_byCharMove_ForwardSw;			//	키보드 이동인지 파악

};

#endif