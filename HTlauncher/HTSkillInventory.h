
#ifndef __HTSKILLINVENTORY_H__
#define __HTSKILLINVENTORY_H__
/*
typedef struct _SKILL_ICON
{
	HTint						m_iSkillIconNo1[6][4];
	HTint						m_iSkillIconNo2[6][4];
	HTint						m_iSkillIconNo3[6][4];
	HTint						m_iSkillIconNo4[6][4];
	
} _SKILL_ICON;

typedef struct _SKILL_ARROW
{
	HTint						m_iSkillArrow1[6][4];
	HTint						m_iSkillArrow2[6][4];
	HTint						m_iSkillArrow3[6][4];	
	HTint						m_iSkillArrow4[6][4];

} _SKILL_ARROW;

typedef struct _SKILL_INDEX
{
	HTint						m_iSkillIndex1[6][4];
	HTint						m_iSkillIndex2[6][4];
	HTint						m_iSkillIndex3[6][4];	
	HTint						m_iSkillIndex4[6][4];	

} _SKILL_INDEX;
*/
class CHTSkillInventory
{
public:
	CHTSkillInventory();
	~CHTSkillInventory();
	HTvoid						HT_vSkillInventory_CleanUp();

	HTRESULT					HT_hrSkillInventoryInit();
	HTRESULT					HT_hrSkillInventoryDestory();

	HTvoid						HT_vSkillInventoryActiveCheck( BYTE byType );
	HTvoid						HT_vSkillInventory_SetActive();
	HTvoid						HT_vSkillInventory_SetAntiActive();
	//	ESC Key 누르면 스킬창 닫기
	HTvoid						HT_vSkillInventory_ESC_CloseWindow();

	HTvoid						HT_vSkillInventory_SkillAnalysis( DWORD );

	//-------------------------------------------------------
	// 셋팅 및 반환값들
	//-------------------------------------------------------
	HTbool						HT_bSkillInventory_GetActive();
	HTvoid						HT_vSkillInventory_SetSkillPoint( HTshort snSkillPoint, HTshort snTrimuritiSkillPoint );
		
	HTRESULT					HT_hrSkillItemInit();

	//----------------네트워크 관련----------------//
	//-----스킬 레벨업------//	
	HTvoid						HT_vNetWork_CSP_Skill_LevekUp();
	HTvoid						HT_vNetWork_SCP_Skill_LevelUp(PS_SCP_RESP_SKILL_LEVEL_UP info);
	HTvoid						HT_vNetWork_CSP_Skill_LearnSkill( HTint iButton );
	HTvoid						HT_vNetWork_SCP_Skill_LearnSkill(PS_SCP_RESP_LEARN_SKILL info);
	//	Recive Server MSG_SKILL_UP_EFFECT
	HTvoid						HT_vNetWork_SCP_Skill_Up_Effect( MSG_SKILL_UP_EFFECT* info );

private:
	//-------------------------------------------------------------------------------
	// 메세지 출력
	//-------------------------------------------------------------------------------
	HTvoid						HT_vSkillInventory_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid						HT_vSkillInventory_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

private:
	//	스킬 인벤토리가 열렸는가 체크
	HTbool						m_bSkillInventoryAction;
	//	스킬 아이콘 상태
	HTint						m_iSkill_SkillIconStatus;

	//--------- 메세지 창에 대한 정보 -------------//
	BYTE						m_byMessageWin;			//  현재 메세지창
	//CHTString					m_szMessage;			//  현재 메세지창에 보여줄 내용
	CHTString					m_szMsgSkillName;		// 메세지창에 보여줄 스킬 이름
	HTbyte						m_byMsgSkillLevel;		// 메세지창에 보여줄 스킬 레벨

	//-----네트워크 관련-----//
	S_CSP_REQ_SKILL_SELECT		m_nNetWork_SkillSelect;
	BYTE						m_byResent_ServerMsg;
	DWORD						m_dwSkillIndex_LvlUp;	// 레벨을 올리려는 스킬 인덱스

	HTbool						m_bSkillInventory_SlideBarBtn;

	HTint						m_iSkillInventory_SlideBarCurPos;
	HTint						m_iSkillInventory_RidioCurGroup;
	HT_SKILL_INVENTORYCONNECT	m_sSkillInventory_Element[10];		//	인베토리에 삽입되는 요소

	//	Skill Inventory SkillPoint Cell No
	HTshort						m_snSkillInventory_SkillPoint;
	//	Skill Inventory TrimuritiSkillPoint Cell No
	HTshort						m_snSkillInventory_TrimutiritiSkillPoint;

	_SKILL_ICON					m_oSkillIcon;
	_SKILL_ARROW				m_oSkillArrow;
	_SKILL_INDEX				m_oSkillIndex;
	HTint						m_iSkillTab;
	HTint						m_iSkillInventory_EmptyBox[5][4];
};

#endif

