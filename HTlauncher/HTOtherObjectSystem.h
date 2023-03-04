#pragma once

#include "HTOtherObject.h"

//	��Ŀ�� ����Ʈ ����
typedef struct _HT_OTHEROBJECT_NODE
{
	HTOtherObject					oOtherObject;
	struct _HT_OTHEROBJECT_NODE		*next;

} HT_OTHEROBJECT_NODE;


class HTOtherObjectSystem
{
public:
	HTOtherObjectSystem(void);
	~HTOtherObjectSystem(void);

	//	Init
	//	Init Init
	HTvoid						HT_vOtherObjectSystem_Init();

	//	Destory
	//	Destory TotalObjectDelete
	HTvoid						HT_vOtherObjectSystem_TotalObjectDelete();

	//	Control
	//	Control Control
	HTvoid						HT_vOtherObjectSystem_Control( HTfloat fElapsedTime );

	//	Input
	//	Input Key
	HTvoid						HT_vOtherObjectSystem_InputKey();

	//	Effect
	//	Effect Hit Action
	HTvoid						HT_vOtherObjectSystem_EffectHitAction( HTint iTargetKeyID, HTint iSkillID, HTint iItemID, HTint iInvadeModelID, HTint iInvadeKeyID );
	//	Effect Item Use
	HTvoid						HT_vOtherObjectSystem_EffectItemUse( HTint iKeyID );
	//	Effect Recive Active Skill
	HTvoid						HT_vOtherObjectSystem_EffectReciveActiveSkill( DWORD dwKeyID, DWORD dwSkillIndex, HTbool bType, BYTE byLevel );
	//	Effect Active Skill Effect On
	HTvoid						HT_vOtherObjectSystem_EffectActiveSkillOn();
	//	Effect Active Skill Effect Off
	HTvoid						HT_vOtherObjectSystem_EffectActiveSkillOff();
	
	//	Setting
	//	Setting HP Window Init
	HTvoid						HT_vOtherObjectSystem_HPWindowInit();
	//	Setting Show Name
	HTvoid						HT_vOtherObjectSystem_SetShowName();
	//	Setting Show Name
	HTvoid						HT_vOtherObjectSystem_SetShowName( HTbool bTrue );
	//	Setting Show Chat Msg
	HTvoid						HT_vOtherObjectSystem_SetShowChatMsg();
	//	Setting Guild MarkID
	HTvoid						HT_vOtherObjectSystem_SetGuildMarkID( CHTString strName, HTint iGuildMarkID, CHTString strGuildName );
	//	Setting Guild Compare
	HTRESULT					HT_hrOtherObjectSystem_CompareGuild( HTint iKeyID, HTint iGuildMark );
	//	Setting Show Guild Mark
	HTvoid						HT_vOtherObjectSystem_SetShowGuildMark();
	//	Setting Hide Guild Mark
	HTvoid						HT_vOtherObjectSystem_SetHideGuildMark();
	//	Setting Trimuriti
	HTvoid						HT_vOtherObjectSystem_SetTrimuritiD( CHTString strName, BYTE byTrimuritii );
	//	Setting Trimuriti
	HTvoid						HT_vOtherObjectSystem_SetTrimuritiD( HTint iKeyID, BYTE byTrimuritii );
	//	Setting Show Trimuriti Mark
	HTvoid						HT_vOtherObjectSystem_SetShowTrimuritiMark();
	//	Setting Hide Trimuriti Mark
	HTvoid						HT_vOtherObjectSystem_SetHideTrimuritiMark();
	//	Setting Party Join or Disband
	HTvoid						HT_vOtherObjectSystem_SetPartyJoineDisband( CHTString, BYTE );
	//	Setting Party Join
	HTvoid						HT_vOtherObjectSystem_SetPartyJoin( CHTString, HTbyte );
	//	Setting Stop Move
	HTvoid						HT_vOtherObjectSystem_SetStop( HTint iKeyID );
	//	Setting WizardEyes
	HTvoid						HT_vOtherObjectSystem_SetWizardEyes( __int64 iWizardEyes );
	//	Setting AttackTargetting
	HTvoid						HT_vOtherObjectSystem_SetAttackTargetting( HTint iKeyID );
	//	Setting Affections
	HTvoid						HT_vOtherObjectSystem_SetAffections( HTint iKeyID, __int64 iAffections );
	//	Setting TradeMode
	HTvoid						HT_vOtherObjectSystem_SetTradeMode( MSG_MobStatus* info );
	//	Setting �ð����� ����ĳ������ HP�� ��ȭ�����ϰ� ���̴°� ����
	HTvoid						HT_vOtherObjectSystem_SetMainCharHPCorrect( HTint iCurHP );
	//	Setting Init Targetting
	HTvoid						HT_vOtherObjectSystem_SetInitTargetting();
	//	Setting Strong Ashiram
	HTvoid						HT_vOtherObjectSystem_SetStrongAshiram( CHTString strAshiram1, CHTString strAshiram2 );
	//	Setting Item Effect
	HTvoid						HT_vOtherObjectSystem_SetItemEffect( HTint iUserKeyID, HTint iItemID );
	//	Setting	Targetting
	HTvoid						HT_vOtherObjectSystem_SetTargetting();
	//	Setting	Targetting
	HTvoid						HT_vOtherObjectSystem_SetTargetting( HTint iKeyID );
	//	Setting	Change Shop Mode
	HTvoid						HT_vOtherObjectSystem_SetChangeShopMode();
	//	Setting	Change Animation
	HTvoid						HT_vOtherObjectSystem_SetChangeAnimation( HTint iKeyID, HTint iAniType, HTint iAniCount );
	//	Setting Init Guild Name
	HTvoid						HT_vOtherObjectSystem_SetInitGuild( CHTString strName );
	//	Setting Object Show
	HTvoid						HT_vOtherObjectSystem_SetObjectShow( HTbool bShow );
		
	//	Returns
	//	Returns Show Chat Msg
	HTbool						HT_bOtherObjectSystem_GetShowChatMsg();
	//	Returns �ش缿�� ��ġ�� ������Ʈ�� �ִ°�?
	HTint						HT_iOtherObjectSystem_GetCheckMapCell( HTint iMapCellX, HTint iMapCellZ );
	//	Returns Get ModelID From KeyID
	HTint						HT_iOtherObjectSystem_GetModelID( HTint iKeyID );
	//	Returns Get KeyID From ModelID
	HTint						HT_iOtherObjectSystem_GetKeyID( HTint iModelID );
	//	Returns Get Level From KeyID
	HTbyte						HT_byOtherObjectSystem_GetLevel( HTint iKeyID );
	//	Returns Get Name From KeyID
	CHTString					HT_strOtherObjectSystem_GetNameFromKeyID( HTint ikeyID );
	//	Returns Get Name From ModelID
	CHTString					HT_strOtherObjectSystem_GetNameFromModelID( HTint iModelID );
	//	Returns Get Cur Cell Pos From KeyID
	HTPoint						HT_pOtherObjectSystem_GetCellPosFromKeyID( HTint iKeyID, HTint iSkillID );
	//	Returns Get Cur Cood Pos From KeyID
	HTvector3					HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( HTint iKeyID );
	//	Returns Get Target Cood Pos From KeyID
	HTbool						HT_bOtherObjectSystem_GetTargetCoodFromKeyID( HTint iKeyID );
	//	Returns Get KeyID From Cell Pos For Piercing
	HTint						HT_iOtherObjectSystem_GetKeyIDFromCellForPiercing( HTdword dwSkillType, HTvector3 vecCurPos, HTint *iElement );
	//	Returns Get Cur Cood Pos From ModelID
	HTvector3					HT_vecOtherObjectSystem_GetCoordPosFromModelID( HTint iModelID );
	//	Returns Get ModelID on TargetWindow
	HTint						HT_iOtherObjectSystem_GetTargetModelIDOnTargetWindow();
	//	Returns Get Object Live From KeyID
	HTbool						HT_bOtherObjectSystem_GetLiveFromKeyID( HTint iKeyID );
	//	Returns Get �������� �����ȿ� �� Object
	HTvoid						HT_vOtherObjectSystem_GetTerritoryArea( HTvector3 vecTargetPos, HTfloat fRange, HTint iSkillID, HTint iInvadeModelID, HTint iInvadeKeyID, HTbyte byGood, HTint *iElement );
	//	Returns �������� ��ġ�� �����ؿ�
	HTvector3					HT_vecOtherObjectSystem_SRAttackPos( DWORD dwTargetKeyID );
	//	Returns Get Object Index
	HTint						HT_iOtherObjectSystem_GetIndex( HTint iKeyID );
	//	Returns Get Trimuriti
	HTbyte						HT_byOtherObjectSystem_GetTrimuriti( HTint iKeyID );
	//	Returns Get �÷��̾�� ���� ����� Object KeyID�O��
	HTint						HT_iOtherObjectSystem_GetObjectKeyIDMostNearMainChar( HTint iBeforeTargetID );
	//	Returns Get �÷��̾�� ���� ����� ���� KeyID�O��
	HTint						HT_iOtherObjectSystem_GetAssociateKeyIDMostNearMainChar( HTint iBeforeTargetID );
	//	Returns Get TradeMode
	HTbyte						HT_byOtherObjectSystem_GetTradeMode( HTint iKeyID );
	//	Returns Get Party
	HTbyte						HT_byOtherObjectSystem_GetParty( HTint iKeyID );
	//	Returns Get class1
	HTbyte						HT_byOtherObjectSystem_GetClass1( HTint iKeyID );
	//	Returns Get KeyID Form Name
	HTint						HT_iOtherObjectSystem_GetKeyIDFromName( CHTString strName );
	//	Returns Get ItemIndex of Equip
	HTint						HT_iOtherObjectSystem_GetItemIndexofEquip( HTint iKeyID, HTint iPart );
	//	Returns Get	bCheck2ObjCollide
	HTint						HT_iOtherObjectSystem_GetCheck2ObjCollide( HTint iKeyID, HTvector3 vecMainCharPos, HTfloat ColidSize );
	//	Returns Get	bCheck2ObjCollide
	HTshort						HT_vOtherObjectSystem_GetKarma( HTint iKeyID );
	//	Returns Get	Attack Target
	HTbool						HT_bOtherObjectSystem_GetAttackTarget( HTint iKeyID );
	//	Returns Get Check Can Attack Target For Normal Attack
	HTRESULT					HT_bOtherObjectSystem_GetCheckCanAttackTargetForNormal( HTint iTargetKeyID, HTPoint pMainCharPt );
	//	Returns Get Check Can Attack Target For Skill Attack
	HTRESULT					HT_bOtherObjectSystem_GetCheckCanAttackTargetForSkill( HTbool bTimeCheckForSkillStart, HTint iTargetKeyID, HTPoint pMainCharPt, HTint iSkill, HTint& iMainChar_Target_KeyID, HTint& iMainChar_MemoryTargetKeyID );
	//	Returns Get Ashiram Name From KeyID
	CHTString					HT_strOtherObjectSystem_GetAshiramNameFromKeyID( HTint iKeyID );
	//	Returns Get Cast Name From KeyID
	CHTString					HT_strOtherObjectSystem_GetCastNameFromKeyID( HTint iKeyID );
	//	Returns Get DefineZoneAttackTarget
	HTbool						HT_bOtherObjectSystem_GetDefineZoneAttackTargetFromKeyID( HTint iKeyID );
	//	Returns Get Affection
	__int64						HT_iOtherObjectSystem_GetAffection( HTint iKeyID );
	//	Returns Get Targetting
	HTbool						HT_hrOtherObjectSystem_GetTargetting( HTint iKeID );
	//	Returns Get Object Show
	HTbool						HT_bOtherObjectSystem_GetShowCheck()	{	return m_bOOSystem_ShowObject;	};

	//	Setting and Returns
	//	Setting and Returns Pick Check From ModelID
	HTint						HT_iOtherObjectSystem_SRPickIDCheck( HTint iModelID );
	//	Setting and Returns ���� ���� ������� �ľ�
	HTvector3					HT_vecOtherObjectSystem_SRAtkTargetCheck( HTint iTargetKeyID );

	//	Render
	//	Render Control
	HTvoid						HT_vOtherObjectSystem_Render();
	//	Render Name
	HTvoid						HT_vOtherObjectSystem_RenderName( HT_OTHEROBJECT_NODE* t );
	//	Render MinimapPoint
	HTvoid						HT_vOtherObjectSystem_RenderMinimapPoint();
	
	//	Network
	//	Network Object Insert
	HTvoid						HT_vOtherObjectSystem_NetworkObjectInsert( PS_SCP_INIT_OTHER_MOB info );
    //	Network Object Remove Mob
	HTvoid						HT_vOtherObjectSystem_NetworkObjectRemoveMob( PS_SCP_RESP_REMOVE_MOB info );
	//	Network GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���
	HTvoid						HT_vOtherObjectSystem_GMMode_Notify( HTint iKeyID, BYTE byGMMode );
	//	Network LevelUp Broadcast
	HTvoid						HT_vOtherObjectSystem_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );
	//	Newwork Equip
	HTvoid						HT_vOtherObjectSystem_NetworkEquip( PS_SCP_RESP_EQUIP_SET info );
	//	Newwork Setting ������ �Ҹ�� �����
	HTvoid						HT_vOtherObjectSystem_NewworkItemAbrasion(PS_SCP_ITEM_ABRASION_BROADCAST info);
	//	Newwork ChatMsg
	HTvoid						HT_vOtherObjectSystem_NetworkChatMsg( DWORD dwKeyID, CHTString strMessage );
	//	Network Msg Action
	HTRESULT					HT_hrOtherObjectSystem_Network_MsgAction( MSG_Action* info );
	//	Network UnitSkill
	HTvoid						HT_vOtherObjectSystem_NetworkUnitSkill( PS_CSP_CAST_UNIT_SKILL info );
	//	Network AreaSkill
	HTvoid						HT_vOtherObjectSystem_NetworkAreaSkill( PS_CSP_CAST_AREA_SKILL info );
	//	PS_SCP_RESP_UPDATE_STATUS Setting
	HTvoid						HT_vOtherObjectSystem_NetworkUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info );
	//	Network Serch OtherObject From KeyID
	HTvoid						HT_vOtherObjectSystem_NetworkSerchMobFromKeyID( DWORD dwKeyID );
	//	Network �ʱ�ȭ ��û ���� �ʾ����� herChar�� �������ֱ� ����
	HTvoid						HT_vOtherObjectSystem_NetworkRequestInitOtherMob( DWORD dwKeyID, short snX, short snZ );
	//	��ȯ ��û ����� ������ ���� ���� ��� �������ֱ� ����
	HTbool						HT_bOtherObjectSystem_CheckOtherMobForTrade( PS_CSP_REQ_TRADE info );
	//	Network GuildNotify
	HTvoid						HT_vOtherObjectSystem_NetworkGuildNotify( MSG_GuildNotify* info );
	//	Network_�Ҳɳ���
	HTvoid						HT_vOtherObjectSystem_NetworkFireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info );
	//	_MSG_CONTACT_NPC
	HTvoid						HT_vOtherObjectSystem_NetWorkCONTACT_NPC( DWORD dwTargetKeyID );
	//	Network_YutMove
	HTvoid						HT_vOtherObjectSystem_NetWorkYutMove( Msg_YutMove* info );

	// �ش� ĳ������ ������ ��´�.
	HTRESULT					HT_hrGetCharacterAccount( const HTint idKey, CHTString* pszAccount );

private:
	HTvoid						HT_LL_vInitList();
	HTRESULT					HT_LL_hrDeleteNode( int );
	HTRESULT					HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info );
	HTvoid						HT_LL_hrDeleteAll();

private:
	HT_OTHEROBJECT_NODE*		m_sOtherObjectHead;
	HT_OTHEROBJECT_NODE*		m_sOtherObjectTail;
	// Trade ��û�� ������ �� Client ĳ���� ������ �޶� initChar�� ��û�ߴ���..
	S_CSP_REQ_TRADE				m_sCharInfoForTrade; 
public:
	//	OtherObject ���� ǥ������
	HTbool						m_bOOSystem_HPInfoSw;
	//	�̸� �����ֱ�
	HTbool						m_bOOSystem_NameShowSw;
	//	ä�� �޽��� �����ֱ�
	HTbool						m_bOOSystem_ChatMsgShowSw;
	//	�ѹ� ����� �� ID ���
	HTint						m_iOOSystem_ModelID;
	//	MainChar���� ������ �� ��ų�� ���õǾ� �ִ°�?
	HTbool						m_bOOsystem_MainCharWizardEyesSw;
	//	Show Object Name
	CHTString					m_strOOSystem_ShowObjectName;
	//	Show Object
	HTbool						m_bOOSystem_ShowObject;
};


