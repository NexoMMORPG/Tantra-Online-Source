#pragma once

class HTSystem
{
public:
	HTSystem(void);
	~HTSystem(void);

	int					m_iOption0;		// ���İ�
	bool				m_bOption1;		// ���̵�ǥ��
	bool				m_bOption2;		// ����Ʈ
	bool				m_bOption3;		// ��������ȭ
	int					m_iOption4;		// ����
	int					m_iOption5;		// ����
	bool				m_bOption6;		// ���Լ���
	bool				m_bOption7;		// ĳ���� ����� ������� ����

	
	HTvoid				HT_vSystem_CleanUp();

	HTvoid				HT_vSystem_Init();
	//	Create Window
	HTvoid				HT_vSystem_CreateWindow();
	//	�Է��Լ� ó��
	static void			HT_vSystem_InputCheckSystem(int iAction, int iTarget, int iTargetID);

	HTbool				HT_bSystem_GetActiveSw()	{ return m_bSystem_WindowActiveSw; };
	//----------Ȱ��ȭ / ��Ȱ��ȭ----------//
	HTvoid				HT_vSystem_ActiveSw();
	//	ESC Key ������ �ý���â �ݱ�
	HTvoid				HT_vSystem_ESC_CloseWindow();

	// ���� â ��ư Ȱ��ȭ / �� Ȱ��ȭ

	HTbool				HT_bSystem_GetActiveSkillEffectSw()	{ return m_bSystem_ActiveSkillEffectSw; };

	HTbool				HT_bSystem_GetMyNameShow() { return m_bMyNameShow; }
	HTbool				HT_bSystem_GetNPCNameShow() { return m_bNPCNameShow; }
	HTbool				HT_bSystem_GetOtherCharNameShow() { return m_bOtherCharNameShow; }
	HTbool				HT_bSystem_GetShopModelMode() { return m_bShopModelMode; }
	HTbool				HT_bSystem_GetF1ToF10Mode() { return m_bF1ToF10SlotMode; }

public:

	HTbool						m_bSystem_ExitSw;
	HTbool						m_bSystem_WindowActiveSw;
	HTvector3					m_vSystem_WindowPos;
	HTbool						m_bSystem_ActiveSkillEffectSw;

	HTfloat						m_fBright;
	HTfloat						m_fStreamVolume;
	HTfloat						m_fSampleVolume;


private:
	HTint						m_iSelectSlideNo;	//20030521,DAEHO

	HTbool						m_bMyNameShow;	// ���� �̸� ǥ��
	HTbool						m_bNPCNameShow; // ����, NPC �̸� ǥ��
	HTbool						m_bOtherCharNameShow; // �ٸ� �÷��̾� �̸� ǥ��
	HTbool						m_bInitUI;
	HTbool						m_bRootingMode;	// ������ �ڵ��й� ���
	HTbool						m_bChattingMode; // ä�ø��
	HTbool						m_bMinimapMode; // ä�ø��
	HTbool						m_bShopModelMode;	//	���λ��� Model ���
	HTbool						m_bF1ToF10SlotMode;		//	F1-F10���� ����/��ų ��� ��ȯ
};
