
#ifndef __HTSKILLSYSTEM_H__
#define __HTSKILLSYSTEM_H__

#include "HTSkill.h"

//----------��ų ������ ���� ����ü----------//
typedef struct _HT_SKILL_NODE
{
	CHTSkill						sSkill;
	struct _HT_SKILL_NODE			*next;

} HT_SKILL_NODE;

//----------NPC ��ü �ý��۰� LL�� ���� ����----------//
class HTSkillSystem
{
public:
	HTSkillSystem();
	~HTSkillSystem();
	HTvoid					HT_vSkillSystem_CleanUp();

	HTRESULT				HT_hSkillSystemInit();

	//	��ų ����Ʈ �� �ʱ�ȭ_�������� �ʱ� ��ų ����Ʈ�� �޴´�.
	HTvoid					HT_vSkillSystem_Init_SkillBook( BYTE bySkill[MAX_SKILL] );

	//	�����κ��� ��ų Learn ������ �޴���.
	HTvoid					HT_vSkillSystem_SetLearn( S_TNSKILL_DATA info );

	//	��ü ��ų �����
	HTvoid					HT_vSkillSystem_TotalSkillDelete();
	//	��ü ��ų�� ������ ���� �ʱ�ȭ
	HTvoid					HT_vSkillSystem_TotalSkillLevelInit();

	//-----------------------------------------------------------------
	// ��ų ����
	//-----------------------------------------------------------------
	// ��ų ������ ���´�
	HTint					HT_iGetSkillInfo(DWORD dwIndex, HT_ITEMINFO& vInfo, vector<HT_ITEM_DATA*>& vNextInfo);
	// Effect ������ ���� �޼��� ������
	HTbool					HT_bSkillSystem_GetEffect( HTint iEffectID, CHTString* pString, HTint iParam1=0, 
											HTint iParam2=0, HTint iFunction=0, HTint iDecreaseVal = 0, HTint idSkill = 0 );
	// ������ Effect�� ���� ������ ��ġ ����ϱ�
	HTvoid					HT_bSkillSystem_SetDamageParam( HTint iEffectID, HTint iParam1, HTint iParam2 );

	//-----------------------------------------------------------------
	// ��ȯ����
	//-----------------------------------------------------------------
	HTint					HT_vSkillSystem_GetSkill_UIIconID( DWORD );		//	��ų�� �̹��� ���̵� �Ѱ���
	BYTE					HT_bySkillSystem_GetSkill_Level( DWORD );		//	��ų�� ����
	HTvoid					HT_vSkillSystem_SetAttackSpeedVariation( DWORD,  short snSpeed );	//	���������� ����� ��ų�� ���ݼӵ��� ����
	HTvoid					HT_vSkillSystem_SetCastingSpeedVariation( DWORD dwSkillIndex, short snSpeed );	//	���������� ����� ��ų�� ĳ���üӵ��� ����
	HTvoid					HT_vSkillSystem_SetShootRange( DWORD dwSkillIndex, BYTE byShootRange );	//	���������� ����� ��ų�� �����Ÿ�
	HTvoid					HT_vSkillSystem_SetMovingSpeed( DWORD dwSkillIndex, short snSpeed );	//	���������� ����� ��ų�� �̵��ӵ��� ����
	HTvoid					HT_vSkillSystem_SetSkill_Level(DWORD dwIndex, BYTE byLevel);
	CHTString				HT_szSkillSystem_GetSkillName(DWORD);	// ��ų �̸� ����
	HTvoid					HT_vSkillSystem_GetSkillSequenceCount( HTint iType, HTint iIndex, HT_SKILL_INVENTORYCONNECT *sElement );	//	��ų�� ����,�ֽ�,������ų ���ʸ� �Ѱ���
	HTint					HT_vSkillSystem_GetSkillEffect1Param1( DWORD dwSkillIndex );

	//	Get
	//	Return Get Plus Level
	HTbyte					HT_bySkillSystem_GetSkillPlusLevel( DWORD dwSkillIndex );

	//	Set
	//	Set Plus Level
	HTvoid					HT_vSkillSystem_SetSkillPlusLevel( DWORD dwSkillIndex, HTbyte byLevel, HTbyte byPlusLevel );


	// ��ų Effect�� ���ݷ� ��������
	HTbool					HT_bSkillSystem_IsDamageEffect( HTint iEffectID );
	// ���콺 ����Ʈ�� �Ѱܹ޾� Ȱ��ȭ�� ��ų �߿� ����Ʈ ��ġ�� �ִ°��� KeyID�� ��ȯ
	DWORD					HT_dwSkillSystem_MousePtToSkillPosCheck( HTint iBitmapNo );
	// ��ϵǾ��ִ� ��ų���� �˻�
	HTbool					HT_bSkillSystem_IsRegistedSkill(DWORD dwIndex);

private:
	HTvoid					HT_LL_vInitList();
	HTRESULT				HT_LL_hrDeleteNode( DWORD );
	HTRESULT				HT_LL_hrInsertAfter( HT_SKILLINSERT_FLAG info );
	HT_SKILL_NODE*			HT_LL_hrDeleteAll();

	//--------------------------------------------------------------------------
	// �޼��� ���
	//--------------------------------------------------------------------------
	HTvoid					HT_vSkillSystem_SetMessage( HTint idMessage, CHTString* pstrMessage );
	HTvoid					HT_vSkillSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HT_SKILL_NODE*			m_sSkillHead;
	HT_SKILL_NODE*			m_sSkillTail;


	BYTE					m_bTribeAttack_Count;
	BYTE					m_bFreeAttack_Count;
	BYTE					m_bJusinAttack_Count;
	BYTE					m_bJusinFreeAttack_Count;
	BYTE					m_bJobSkill_Count;

	DWORD					m_dwKeyID_Count;
private:
	HTint					m_iParam1;
	HTint					m_iParam2;
	HTint					m_iDecreaseVal;
	CHTString				m_szParamString;
	HTint					m_iFunction;

	HTbool					m_bSkillDataCheck;
};


#endif