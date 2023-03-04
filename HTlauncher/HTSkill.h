

#ifndef __HTSKILL_H__
#define __HTSKILL_H__

//#include "TNEditorsData.h"

//-----0:고정스킬,1:자유스킬,2:주신스킬,3:주신자유스킬,3:직업스킬
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
	DWORD						m_dwSkill_UIICONID;				//	스킬 아이콘 ID
	BYTE						m_bSkill_Type;
	HTint						m_iSkill_BitmapNo;
	//-----0:왼손, 1:오른손, 2:단축스킬창, 3:인벤토리1
	BYTE						m_bSkill_Location;
	HTvector3					m_pSkill_ScreenPos;

	BYTE						m_bySkill_Level;
	HTbyte						m_bySkill_PlusLevel;

	short		                m_snSkill_MovingSpeed;			// 아이템의 이동속도
	short				        m_snSkill_AttackSpeed;			// 아이템의 공격속도
	short						m_snSkill_CastingSpeed;			// 아이템의 케스팅속도
	BYTE						m_bySkill_ShootRange;			// 발사체의 사정거리

	//	새 기획에 따른 멤버 변수
	BYTE						m_bySkill_TribeCount;
	BYTE						m_bySkill_TrimuritiCount;
	BYTE						m_bySkill_FreeCount;
};

#endif

