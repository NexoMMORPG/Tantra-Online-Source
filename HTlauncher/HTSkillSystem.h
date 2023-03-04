
#ifndef __HTSKILLSYSTEM_H__
#define __HTSKILLSYSTEM_H__

#include "HTSkill.h"

//----------스킬 구현을 위한 구조체----------//
typedef struct _HT_SKILL_NODE
{
	CHTSkill						sSkill;
	struct _HT_SKILL_NODE			*next;

} HT_SKILL_NODE;

//----------NPC 전체 시스템과 LL을 실제 구현----------//
class HTSkillSystem
{
public:
	HTSkillSystem();
	~HTSkillSystem();
	HTvoid					HT_vSkillSystem_CleanUp();

	HTRESULT				HT_hSkillSystemInit();

	//	스킬 리스트 북 초기화_서버에서 초기 스킬 리스트를 받는다.
	HTvoid					HT_vSkillSystem_Init_SkillBook( BYTE bySkill[MAX_SKILL] );

	//	서버로부터 스킬 Learn 정보를 받느다.
	HTvoid					HT_vSkillSystem_SetLearn( S_TNSKILL_DATA info );

	//	전체 스킬 지우기
	HTvoid					HT_vSkillSystem_TotalSkillDelete();
	//	전체 스킬위 레벨을 전부 초기화
	HTvoid					HT_vSkillSystem_TotalSkillLevelInit();

	//-----------------------------------------------------------------
	// 스킬 정보
	//-----------------------------------------------------------------
	// 스킬 정보를 얻어온다
	HTint					HT_iGetSkillInfo(DWORD dwIndex, HT_ITEMINFO& vInfo, vector<HT_ITEM_DATA*>& vNextInfo);
	// Effect 종류에 따른 메세지 얻어오기
	HTbool					HT_bSkillSystem_GetEffect( HTint iEffectID, CHTString* pString, HTint iParam1=0, 
											HTint iParam2=0, HTint iFunction=0, HTint iDecreaseVal = 0, HTint idSkill = 0 );
	// 데미지 Effect의 실제 데미지 수치 계산하기
	HTvoid					HT_bSkillSystem_SetDamageParam( HTint iEffectID, HTint iParam1, HTint iParam2 );

	//-----------------------------------------------------------------
	// 반환값들
	//-----------------------------------------------------------------
	HTint					HT_vSkillSystem_GetSkill_UIIconID( DWORD );		//	스킬의 이미지 아이디를 넘겨줌
	BYTE					HT_bySkillSystem_GetSkill_Level( DWORD );		//	스킬의 레벨
	HTvoid					HT_vSkillSystem_SetAttackSpeedVariation( DWORD,  short snSpeed );	//	레벨업으로 변경된 스킬의 공격속도를 셋팅
	HTvoid					HT_vSkillSystem_SetCastingSpeedVariation( DWORD dwSkillIndex, short snSpeed );	//	레벨업으로 변경된 스킬의 캐스팅속도를 셋팅
	HTvoid					HT_vSkillSystem_SetShootRange( DWORD dwSkillIndex, BYTE byShootRange );	//	레벨업으로 변경된 스킬의 사정거리
	HTvoid					HT_vSkillSystem_SetMovingSpeed( DWORD dwSkillIndex, short snSpeed );	//	레벨업으로 변경된 스킬의 이동속도를 셋팅
	HTvoid					HT_vSkillSystem_SetSkill_Level(DWORD dwIndex, BYTE byLevel);
	CHTString				HT_szSkillSystem_GetSkillName(DWORD);	// 스킬 이름 조사
	HTvoid					HT_vSkillSystem_GetSkillSequenceCount( HTint iType, HTint iIndex, HT_SKILL_INVENTORYCONNECT *sElement );	//	스킬의 종족,주신,자유스킬 차례를 넘겨줌
	HTint					HT_vSkillSystem_GetSkillEffect1Param1( DWORD dwSkillIndex );

	//	Get
	//	Return Get Plus Level
	HTbyte					HT_bySkillSystem_GetSkillPlusLevel( DWORD dwSkillIndex );

	//	Set
	//	Set Plus Level
	HTvoid					HT_vSkillSystem_SetSkillPlusLevel( DWORD dwSkillIndex, HTbyte byLevel, HTbyte byPlusLevel );


	// 스킬 Effect가 공격력 종류인지
	HTbool					HT_bSkillSystem_IsDamageEffect( HTint iEffectID );
	// 마우스 포인트를 넘겨받아 활성화된 스킬 중에 포인트 위치에 있는것의 KeyID를 반환
	DWORD					HT_dwSkillSystem_MousePtToSkillPosCheck( HTint iBitmapNo );
	// 등록되어있는 스킬인지 검사
	HTbool					HT_bSkillSystem_IsRegistedSkill(DWORD dwIndex);

private:
	HTvoid					HT_LL_vInitList();
	HTRESULT				HT_LL_hrDeleteNode( DWORD );
	HTRESULT				HT_LL_hrInsertAfter( HT_SKILLINSERT_FLAG info );
	HT_SKILL_NODE*			HT_LL_hrDeleteAll();

	//--------------------------------------------------------------------------
	// 메세지 출력
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