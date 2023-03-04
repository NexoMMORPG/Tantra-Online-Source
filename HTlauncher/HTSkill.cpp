
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSkill.h"


//-----0:종족스킬,1:주신스킬2:자유스킬
HTfloat g_fInventory_SkillX[3]	= {   6,   6,   6 };
HTfloat g_fInventory_SkillY[3]	= {  87, 218, 309 };
HTfloat g_fInventory_Skill_Count[3]	= {  10,  5,  10 };

CHTSkill::CHTSkill()
{
	m_dwSkill_Index = -1;
	m_iSkill_BitmapNo = -1;
	m_bySkill_Level = 0;
	m_bySkill_PlusLevel = 0;
}

CHTSkill::~CHTSkill()
{	
}

HTvoid CHTSkill::HT_hrSkill_Insert( HT_SKILLINSERT_FLAG sInsertData )
{
	//	스킬 인덱스/레벨
	m_bSkill_Type		= sInsertData.bySkill_Type;
	m_dwSkill_Index		= sInsertData.dwSkill_Index;
	m_bySkill_Level		= sInsertData.bySkill_Level;

	//	스킬 타입별 카운트
	if( sInsertData.bySkill_Type == 0x00 )
		m_bySkill_TribeCount = sInsertData.bySkill_Count;
	else if( sInsertData.bySkill_Type == 0x01 )
		m_bySkill_TrimuritiCount = sInsertData.bySkill_Count;
	else if( sInsertData.bySkill_Type == 0x02 )
		m_bySkill_FreeCount = sInsertData.bySkill_Count;

	//	스킬 UI아이콘 ID
	m_dwSkill_UIICONID	= g_pEngineHandler->HT_dwGetSkillUIID( m_dwSkill_Index );
}

//----------초기화----------//
HTRESULT CHTSkill::HT_hrSkillCreate( HT_SKILLCREATE_FLAG info, HTvector3 vecPos )
{
	info.iSkill_KeyID;
    m_bSkill_Type			= info.bSkill_Type;
	m_dwSkill_Index			= info.iSkill_Index;

	//	스킬 UI아이콘 ID
	m_dwSkill_UIICONID		= g_pEngineHandler->HT_dwGetSkillUIID( m_dwSkill_Index );

	//	서버에서 내려오는 값 셋팅
	m_snSkill_MovingSpeed	= info.snMovingSpeed;// 아이템의 이동속도
	m_snSkill_AttackSpeed	= info.snAttackSpeed;// 아이템의 공격속도
	m_snSkill_CastingSpeed	= info.snCastingSpeed;// 아이템의 케스팅속도
	m_bySkill_ShootRange	= info.byShootRange; // 발사체의 사정거리
	
	if( info.bSkill_Level < 1 )
		m_bySkill_Level = 1;
	else
		m_bySkill_Level = info.bSkill_Level;

	m_bSkill_Location		= info.bSkill_Location;

	return HT_OK;
}

//----------컨트롤 부분----------//
HTRESULT CHTSkill::HT_hrSkillControl()
{
	return HT_OK;
}

//----------스킬의 아이디를 얻어오기----------//
DWORD CHTSkill::HT_dwSkill_GetID( HTPoint pPt )
{
	if( pPt.x > m_pSkill_ScreenPos.x && pPt.x < m_pSkill_ScreenPos.x+32 &&
		pPt.y > m_pSkill_ScreenPos.y && pPt.y < m_pSkill_ScreenPos.y+32 )
		return m_dwSkill_Index;

	return -1;
}

