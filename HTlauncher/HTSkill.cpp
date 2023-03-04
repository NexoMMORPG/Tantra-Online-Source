
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSkill.h"


//-----0:������ų,1:�ֽŽ�ų2:������ų
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
	//	��ų �ε���/����
	m_bSkill_Type		= sInsertData.bySkill_Type;
	m_dwSkill_Index		= sInsertData.dwSkill_Index;
	m_bySkill_Level		= sInsertData.bySkill_Level;

	//	��ų Ÿ�Ժ� ī��Ʈ
	if( sInsertData.bySkill_Type == 0x00 )
		m_bySkill_TribeCount = sInsertData.bySkill_Count;
	else if( sInsertData.bySkill_Type == 0x01 )
		m_bySkill_TrimuritiCount = sInsertData.bySkill_Count;
	else if( sInsertData.bySkill_Type == 0x02 )
		m_bySkill_FreeCount = sInsertData.bySkill_Count;

	//	��ų UI������ ID
	m_dwSkill_UIICONID	= g_pEngineHandler->HT_dwGetSkillUIID( m_dwSkill_Index );
}

//----------�ʱ�ȭ----------//
HTRESULT CHTSkill::HT_hrSkillCreate( HT_SKILLCREATE_FLAG info, HTvector3 vecPos )
{
	info.iSkill_KeyID;
    m_bSkill_Type			= info.bSkill_Type;
	m_dwSkill_Index			= info.iSkill_Index;

	//	��ų UI������ ID
	m_dwSkill_UIICONID		= g_pEngineHandler->HT_dwGetSkillUIID( m_dwSkill_Index );

	//	�������� �������� �� ����
	m_snSkill_MovingSpeed	= info.snMovingSpeed;// �������� �̵��ӵ�
	m_snSkill_AttackSpeed	= info.snAttackSpeed;// �������� ���ݼӵ�
	m_snSkill_CastingSpeed	= info.snCastingSpeed;// �������� �ɽ��üӵ�
	m_bySkill_ShootRange	= info.byShootRange; // �߻�ü�� �����Ÿ�
	
	if( info.bSkill_Level < 1 )
		m_bySkill_Level = 1;
	else
		m_bySkill_Level = info.bSkill_Level;

	m_bSkill_Location		= info.bSkill_Location;

	return HT_OK;
}

//----------��Ʈ�� �κ�----------//
HTRESULT CHTSkill::HT_hrSkillControl()
{
	return HT_OK;
}

//----------��ų�� ���̵� ������----------//
DWORD CHTSkill::HT_dwSkill_GetID( HTPoint pPt )
{
	if( pPt.x > m_pSkill_ScreenPos.x && pPt.x < m_pSkill_ScreenPos.x+32 &&
		pPt.y > m_pSkill_ScreenPos.y && pPt.y < m_pSkill_ScreenPos.y+32 )
		return m_dwSkill_Index;

	return -1;
}

