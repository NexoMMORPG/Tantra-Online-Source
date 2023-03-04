
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

	//----------�̵����� ���� üũ----------//
	HTRESULT					HT_hrMainCharMove_CanPos( HTvector3 vecPos );
	HTRESULT					HT_hrMainCharMove_CanMove();
	HTvoid						HT_vMainCharMove_CheckTargetCell( HTvector3, HTint );	//	��ǥ�� ���
	HTvoid 						HT_vMainCharMove_Moving( HTfloat fElapsedTime );						//	��
	HTvoid 						HT_vMainCharMove_Forward( HTbool, HTfloat fElapsedTime );				//	������ ����
	HTbool 						HT_bMainCharMove_CheckMove();					//	��ǥ ���� üũ
	HTvoid						HT_vMainCharMove_StopMvoe();					//	���߱�
	HTvoid						HT_vMainCharMove_CellPositionCheck();			//	ĳ������ �� ��ġ ���
	HTbool						HT_bMainCharMove_ServerMoveCheck();				//	�̵��ϴ� ���� ���� ������ �÷��ֱ� ����

	HTvoid						HT_vMainCharMove_NetWorkMoveFaild( HTint iX, HTint iZ );		//	�������� �̵� �Ұ� �����ޱ�
	

	//----------�����ϰ� ��ȯ��----------//
	HTvoid						HT_vSetInitSpeed( HTint );
	HTvoid						HT_vMainCharMove_SetSpeed( HTint );
	HTint						HT_iMainCharMove_GetSpeed( BYTE );		//	0x00:����ӵ�,0x01:�ȱ�ӵ�,0x02:�޸���ӵ�
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

	HTfloat						m_fCharMove_Distance;			//	�̵� �� �� �Ÿ�

	HTint						m_nCharMove_ForwardCount;		//	Ű���� �̵��ÿ� ���ǵ� �¾��� ���� ī��Ʈ

	HTfloat						m_fCharMove_EOTransValue;		//	������� ��ȭ��
	HTfloat						m_fCharMove_TimeTransValue;		//	�ð� ��ȭ��
	HTfloat						m_fCharMove_TotalTime;			//	��ü �ð�

public:
	HTbool						m_eMainChrMove_State;
	HTbool						m_byCharMove_ForwardSw;			//	Ű���� �̵����� �ľ�

};

#endif