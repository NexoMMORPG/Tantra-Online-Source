

#ifndef __HTSKILL_H__
#define __HTSKILL_H__

//#include "TNEditorsData.h"

//-----0:������ų,1:������ų,2:�ֽŽ�ų,3:�ֽ�������ų,3:������ų
extern HTfloat g_fInventory_SkillX[3];
extern HTfloat g_fInventory_SkillY[3];
extern HTfloat g_fInventory_Skill_Count[3];

#define HT_SKILLINVENTORY_TERMX					56
#define HT_SKILLINVENTORY_TERMY					40

#define HT_SKILL_LOCATION_LEFTHAND				0
#define HT_SKILL_LOCATION_RIGHTHAND				1
#define HT_SKILL_LOCATION_QUICKWINDOW			2
#define HT_SKILL_LOCATION_INVENTORY				3
#define HT_SKILL_LOCATION_NONE					4


class CHTSkill
{
public:
	CHTSkill();
	~CHTSkill();

	HTvoid						HT_hrSkill_Insert( HT_SKILLINSERT_FLAG sInsertData );
	HTRESULT					HT_hrSkillCreate( HT_SKILLCREATE_FLAG info, HTvector3 vecPos );
	HTRESULT					HT_hrSkillControl();

	DWORD						HT_dwSkill_GetID( HTPoint );

public:

	DWORD						m_dwSkill_Index;				// index
	DWORD						m_dwSkill_UIICONID;				//	��ų ������ ID
	BYTE						m_bSkill_Type;
	HTint						m_iSkill_BitmapNo;
	//-----0:�޼�, 1:������, 2:���ེųâ, 3:�κ��丮1
	BYTE						m_bSkill_Location;
	HTvector3					m_pSkill_ScreenPos;

	BYTE						m_bySkill_Level;
	HTbyte						m_bySkill_PlusLevel;

	short		                m_snSkill_MovingSpeed;			// �������� �̵��ӵ�
	short				        m_snSkill_AttackSpeed;			// �������� ���ݼӵ�
	short						m_snSkill_CastingSpeed;			// �������� �ɽ��üӵ�
	BYTE						m_bySkill_ShootRange;			// �߻�ü�� �����Ÿ�

	//	�� ��ȹ�� ���� ��� ����
	BYTE						m_bySkill_TribeCount;
	BYTE						m_bySkill_TrimuritiCount;
	BYTE						m_bySkill_FreeCount;
};

#endif

