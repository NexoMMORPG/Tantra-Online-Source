
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

	//=====		�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����
	HTfloat						HT_fOtherCharMoveGetAngle( HTvector3 A, HTvector3 B );
	//	��ǥ�� ���_�ٲ� ����
	HTvoid						HT_vOtherCharMoveCheckTargetCell( MSG_Action* info );
	HTvoid 						HT_vOtherCharMoveGo( HTfloat fElapsedTime );
	HTbool						HT_vOtherCharMoveStopCheck();
	HTvoid						HT_vOtherCharMoveCorrection();
	HTvoid						HT_vOtherCharMoveStop();					//	���߱�
	HTvoid						HT_vOtherCharMovephysicalCellMoveCheck();	//	�������� ���� �̵� ����
	
	//----------���� �� ��ȯ����----------//
    HTvector3					HT_fGetOtherCharMovePos();
	HTvoid						HT_fSetOtherCharMovePos( HTvector3 );
	HTPoint						HT_pGeOtherCharMoveGrid();
	HTvoid						HT_fSetOtherCharMovelogical_CellPos( HTint, HTint );
	HTvoid						HT_fSetOtherCharMovephysical_CellPos( HTint, HTint );
	HTvoid						HT_vGetOtherCharMove_physicalCellPos( HTPoint* );
	HTfloat						HT_fGetOtherCharMoveSpeed();
	HTfloat						HT_fGetOtherCharMoveDirect();				//	OtherChar ����
	HTvoid						HT_vSetOtherCharMoveDirect( HTfloat );		//	OtherChar ����
	HTfloat						HT_fGetOtherCharMoveDirectCal();			//	OtherChar ���� �ǽð� ���
	HTfloat						HT_fGetOtherCharTargetToResentDis();		//	��ǥ���� �������� ���̸� ���

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
	HTint						m_iOtherCharMove_State;			//	0:����,1:�̵�,2:����
	HTint						m_iOtherCharphysical_CellX;
	HTint						m_iOtherCharphysical_CellZ;
	HTint						m_iOtherCharlogical_CellX;
	HTint						m_iOtherCharlogical_CellZ;

	HTfloat						m_fOtherCharMove_EOTransValue;		//	������� ��ȭ��
	HTfloat						m_fOtherCharMove_TimeTransValue;	//	�ð� ��ȭ��
	HTfloat						m_fOtherCharMove_TotalTime;			//	��ü �ð�
};

#endif
