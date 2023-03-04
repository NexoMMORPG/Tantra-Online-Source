//======================================================================
// HTMainBar.h
// ȭ�� �ϴ��� ���� ��
// (��)�Ѻ�����Ʈ ���Ӱ����� ����		2003.03.07
//======================================================================
#pragma once

#define			MYSKILL_COUNT					10

class CHTMainBar
{
public:
	CHTMainBar();
	~CHTMainBar();

	HTvoid			HT_vLoad();
	HTvoid			HT_vMainBar_CreateWindow();

	//	�Է� �޼��� ó��
	//	Main Bar
	static void		HT_vMainBar_InputCheckForMainBar(int iAction, int iTarget, int iTargetID);
	//	Main Char HP
	static void		HT_vMainBar_InputCheckForMainCharHP(int iAction, int iTarget, int iTargetID);
	//	Prana Bar
	static void		HT_vMainBar_InputCheckForPranaBar(int iAction, int iTarget, int iTargetID);
	//	Buff Skill
	static void		HT_vMainBar_InputCheckForBuffSkill(int iAction, int iTarget, int iTargetID);

	//	Set PK Button
	HTvoid			HT_vMainBar_GameSystem_SetForPKButton();

	//	���ι�_�����췯
	HTvoid			HT_vMainBar_Control( HTfloat );
	//	������Ʈ ���ڿ� �ؽ�Ʈ�� ����.
    HTvoid			HT_vSetObjectTextDraw( CHTString );
	//	������Ʈ ���ڿ� HP�� �׸���.
	HTvoid			HT_vSetObjectHPDraw( HTint, HTint );
	//	������Ʈ ���ڿ� HP�� �׸��� �ʰ� �ϴ�
	HTvoid			HT_vSetObjectHPOut();
	//	������Ʈ ���ڿ� Name�� �׸��� �ʰ� �ϴ�
	HTvoid			HT_vSetObjectNameOut();

    // ������ ������Ʈ
	//----------------------------------------------------------------------------------
	// ���ο�UI����(20030728)
	//----------------------------------------------------------------------------------
	HTvoid			HT_vPranaUpdate( HTint iTotalPrana );
	HTvoid			HT_vHPUpdate(HTint iCurHP, HTint iMaxHP );				// HP ������ ������Ʈ �Ѵ�.
	HTvoid			HT_vMainBar_SetCurTransparent( HTint iCurHP, HTint iMaxHP );	// ���࿡ ���� HP ������ ������Ʈ �Ѵ�.
	//----------------------------------------------------------------------------------
	//--------------------------------------------------------------
	// D : Tapas
	//--------------------------------------------------------------
	HTvoid			HT_vMainBar_SetCurTP( HTint, HTint );					//	CUR TP ����
	HTint			HT_iMainBar_GetCurTP()	{ return m_iMainBar_CurTP; };	//	CUR TP ��������
	HTint			HT_iMainBar_GetMaxTP()	{ return m_iMainBar_MaxTP; };

	//==============================================================
	// ���ο�UI����(20030728)
	//==============================================================
	//--------------------------------------------------------------
	// HTint			HT_iGetCurChacra()
	// D : ���� �����ְ� �ִ� ��ũ�� �����ش�.
	//--------------------------------------------------------------
	HTint			HT_iGetCurChacra()	{ return m_iCurChacra; };
	HTbool			HT_bGetPKButton()	{ return m_bMainBar_PKButton;	};

	//	�������� �ʿ��� ���� ����
	HTvoid			HT_vMainBar_SetNeedPrana( HTint iNeedPrana )	{	m_dwNeedPrana = iNeedPrana;	};

	//	���ǽ�ų ����
	HTvoid			HT_vMainBar_SetMySkill( HTint iSkillID, BYTE byActor, HTshort snSkillLevel );
	//	���ǽ�ų ������ �ð� Check
	HTvoid			HT_vMainBar_MySkillEndTimeCheck();
	//	���ǽ�ų Init
	HTvoid			HT_vMainBar_MySkillInit();
	//	���ǽ�ų ���ϴ� �༮�� Delete
	HTvoid			HT_vMainBar_MySkillSetDelete( HTint iSkillID );

private:
	//	������ ����� �̸�
	CHTString		m_strPickObjectName;

	// HP�� ���� ����
	CHTString		m_strHP;
	CHTString		m_strPRANA;

	//	���� 
	HTint			m_iScreenWidth;
	HTint			m_iScreenHIGHT;

	// Sprite�� ID
	HTint			m_iActionSkillID;			// Action Skill
	HTint			m_iActiveSkillID;			// Active Skill

	//	��ų �� ī��Ʈ
	HTint			m_nSkillTotalCount;

	// �������� �ʿ��� ����
	DWORD			m_dwNeedPrana;

	//	íũ�� �ʿ䷮ ǥ��
	HTbool			m_bChacraBoxSw;

	// ���ο�UI����(20030728)
	HTint			m_iCurChacra;
	HTint			m_iTotalPrana;

	//	Ÿ�Ľ�
	HTint			m_iMainBar_MaxTP;
	HTint			m_iMainBar_CurTP;

	//	���� ��ų
	HTint			m_iMainBar_MySkillID[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillStartTime[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillDurationTime[MYSKILL_COUNT];
	HTbool			m_bMainBar_MySkillBufWaring[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillSaveBufWaringNo[MYSKILL_COUNT];

	//	PK Button
	HTbool			m_bMainBar_PKButton;

	//	������ �ǸŸ� ���� �ʴ� ���� ������
	HTint			m_iForDelPriminumIconX;
};
