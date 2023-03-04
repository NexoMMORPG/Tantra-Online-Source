#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htotherobjectsystem.h"

HTOtherObjectSystem::HTOtherObjectSystem(void)
{
	//	¸µÄ¿µå ¸®½ºÆ® ÃÊ±âÈ­
	this->HT_LL_vInitList();
}

HTOtherObjectSystem::~HTOtherObjectSystem(void)
{
	HT_DELETE( m_sOtherObjectHead );
	HT_DELETE( m_sOtherObjectTail );
}

//	Init
//	Init Init
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_Init()
{
	//	OtherObject Á¤º¸ Ç¥½ÃÀ§ÇØ
	m_bOOSystem_HPInfoSw = HT_FALSE;
	//	ÀÌ¸§ º¸¿©ÁÖ±â
	m_bOOSystem_NameShowSw = HT_TRUE;
	//	Ã¤ÆÃ ¸Þ½ÃÁö º¸¿©ÁÖ±â
	m_bOOSystem_ChatMsgShowSw = HT_TRUE;
	//	MainChar¿¡°Ô ¸¶¹ýÀÇ ´« ½ºÅ³ÀÌ ¼ÂÆÃµÇ¾î ÀÖ´Â°¡?
	m_bOOsystem_MainCharWizardEyesSw = HT_FALSE;
	// Trade ¿äÃ»ÀÌ µé¾î¿ÔÀ» °æ¿ì Client Ä³¸¯ÅÍ Á¤º¸¿Í ´Þ¶ó¼­ initChar¸¦ ¿äÃ»Çß´ÂÁö..
	ZeroMemory( &m_sCharInfoForTrade, sizeof( S_CSP_REQ_TRADE ) );
	//	Show Object
	m_bOOSystem_ShowObject = HT_TRUE;
}

//	Destory
//	Destory TotalObjectDelete
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_TotalObjectDelete()
{
	this->HT_LL_hrDeleteAll();
}

//	Control
//	Control Control
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_Control( HTfloat fElapsedTime )
{
	HT_OTHEROBJECT_NODE *t;
	HT_OTHEROBJECT_NODE *s;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_Control( fElapsedTime );
		s = t;
		t = t->next;

		//	OtherChar Á×À½ Ã¼Å©
		if( s->oOtherObject.m_iOther_LiveIndex == OTHERCHAR_STATE_DEATH )
		{
			////-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("OtherMob_Death id:%d", s->oOtherObject.m_pObjectInfo->nID );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			this->HT_LL_hrDeleteNode( s->oOtherObject.m_pObjectInfo->nID );
		}
		//	AOI Check
		else if( g_cAoi->HT_AOI_Level( s->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos() ) == AOI_LEVEL_NONE )
		{
			////-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
			//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Out From AOI id:%d", s->oOtherObject.m_pObjectInfo->nID );
			//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			this->HT_LL_hrDeleteNode( s->oOtherObject.m_pObjectInfo->nID );
		}
	}
}

//	Input
//	Input Key
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_InputKey()
{
}

//	Effect
//	Effect Hit Action
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_EffectHitAction( HTint iTargetKeyID, HTint iSkillID, HTint iItemID, HTint iInvadeModelID, HTint iInvadeKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	
	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iTargetKeyID )
		{
			t->oOtherObject.HT_vOtherObject_EffectAttack( iSkillID, iItemID, iInvadeModelID, iInvadeKeyID );
			return;
		}
		t = t->next;
	}
}
//	Effect Item Use
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_EffectItemUse( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	
	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			HTint nEffectID;
			g_pEngineHandler->HT_hrStartSFX( &nEffectID, HT_FX_SPRINGRECOVERY, t->oOtherObject.m_iOtherModelID, HT_FALSE );
			return;
		}
		t = t->next;
	}
}
//	Effect Recive Active Skill
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_EffectReciveActiveSkill( DWORD dwKeyID, DWORD dwSkillIndex, HTbool bType, BYTE byLevel )
{
}
//	Effect Active Skill Effect On
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_EffectActiveSkillOn()
{
}
//	Effect Active Skill Effect Off
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_EffectActiveSkillOff()
{
}

//	Setting
//	Setting HP Window Init
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_HPWindowInit()
{
	//-----NPC ³ëµå¿¡¼­ Ã¼Å©-----//
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_bOther_InfoSw == HT_TRUE )
		{
            //---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
			m_bOOSystem_HPInfoSw = HT_FALSE;
			t->oOtherObject.HT_vOtherObject_SetHideInfomation();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
		}
		t = t->next;
	}
}
//	Setting Show Name
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetShowName()
{
	if( m_bOOSystem_NameShowSw == HT_TRUE )
		m_bOOSystem_NameShowSw = HT_FALSE;
	else
		m_bOOSystem_NameShowSw = HT_TRUE;
}
//	Setting Show Name
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetShowName( HTbool bTrue )
{
	m_bOOSystem_NameShowSw = bTrue;
}
//	Setting Show Chat Msg
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetShowChatMsg()
{
	if( m_bOOSystem_ChatMsgShowSw == HT_TRUE )
		m_bOOSystem_ChatMsgShowSw = HT_FALSE;
	else
		m_bOOSystem_ChatMsgShowSw = HT_TRUE;
}
//	Setting Guild MarkID
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetGuildMarkID( CHTString strName, HTint iGuildMarkID, CHTString strGuildName )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_strOther_Name.HT_szGetString() ) == 0 )
		{
			t->oOtherObject.HT_vOtherObject_SetGuildMarkID( iGuildMarkID );
			strncpy( t->oOtherObject.m_pObjectInfo->szGuild, strGuildName.HT_szGetString(), GUILDNAME_LENGTH );
			t->oOtherObject.HT_vOtherObject_SetMyGuildCheck( strGuildName.HT_szGetString() );
			break;
		}
		t = t->next;
	}
}
//	Setting Guild Compare
HTRESULT HTOtherObjectSystem::HT_hrOtherObjectSystem_CompareGuild( HTint iKeyID, HTint iGuildMark )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			if( t->oOtherObject.m_pObjectInfo->dwGuildMark == iGuildMark )
				return HT_OK;
			else
                return HT_FAIL;
		}
		t = t->next;
	}

	return HT_FAIL;
}
//	Setting Show Guild Mark
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetShowGuildMark()
{
	if( !g_bGuildMarkShow )
		return;

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetGuildMarkOn();
		t = t->next;
	}
}
//	Setting Hide Guild Mark
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetHideGuildMark()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetGuildMarkOff();
		t = t->next;
	}
}
//	Setting Trimuriti
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetTrimuritiD( CHTString strName, BYTE byTrimuritii )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_strOther_Name.HT_szGetString() ) == 0 )
		{
			t->oOtherObject.HT_vOtherObject_SetSetTrimuritiID( byTrimuritii );
			break;
		}
		t = t->next;
	}
}
//	Setting Trimuriti
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetTrimuritiD( HTint iKeyID, BYTE byTrimuritii )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.HT_vOtherObject_SetSetTrimuritiID( byTrimuritii );
			break;
		}
		t = t->next;
	}
}
//	Setting Show Trimuriti Mark
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetShowTrimuritiMark()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetTrimuritiMarkOn();
		t = t->next;
	}
}
//	Setting Hide Trimuriti Mark
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetHideTrimuritiMark()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetTrimuritiMarkOff();
		t = t->next;
	}
}
//	Setting Party Join or Disband
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetPartyJoineDisband( CHTString strName, BYTE byParty )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_strOther_Name.HT_szGetString() ) == 0 )
		{
			t->oOtherObject.HT_vOtherObject_SetPartyJoineDisband( byParty );
			break;
		}
		t = t->next;
	}
}
//	Setting Party Join
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetPartyJoin( CHTString strName, HTbyte byParty )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_strOther_Name.HT_szGetString() ) == 0 )
		{
			t->oOtherObject.HT_vOtherObject_SetPartyJoineDisband( byParty );
			break;
		}
		t = t->next;
	}
}
//	Setting Stop Move
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetStop( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
			break;
		}
		t = t->next;
	}
}
//	Setting WizardEyes
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetWizardEyes( __int64 iWizardEyes )
{
	if( !iWizardEyes )
		m_bOOsystem_MainCharWizardEyesSw = HT_FALSE;
	else
        m_bOOsystem_MainCharWizardEyesSw = HT_TRUE;
    
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetMainCharWizardEyes( m_bOOsystem_MainCharWizardEyesSw );
		t = t->next;
	}
}
//	Setting AttackTargetting
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetAttackTargetting( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			//---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
			m_bOOSystem_HPInfoSw = HT_TRUE;
			if( !t->oOtherObject.m_bOther_InfoSw )
			{
				t->oOtherObject.HT_vOtherObject_SetShowInfomation( HT_TRUE );
				m_iOOSystem_ModelID = t->oOtherObject.m_iOtherModelID;
				//	HP hp¹Ù ÄÁÆ®·Ñ----------//
				g_pMainBar->HT_vSetObjectTextDraw( t->oOtherObject.m_strOther_Name.HT_szGetString() );
				g_pMainBar->HT_vSetObjectHPDraw( t->oOtherObject.m_pObjectInfo->nCurHP, t->oOtherObject.m_pObjectInfo->nMaxHP );
			}
			break;
		}
		t = t->next;
	}
}
//	Setting Affections
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetAffections( HTint iKeyID, __int64 iAffections )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.HT_vOtherObject_SetAffections( iAffections );
			break;
		}
		t = t->next;
	}
}
//	Setting TradeMode
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetTradeMode(MSG_MobStatus* info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			t->oOtherObject.HT_vOtherObject_SetTradeMode( info );
			break;
		}
		t = t->next;
	}
}
//	Setting ½Ã°£Â÷·Î ¸ÞÀÎÄ³¸¯ÅÍÀÇ HP°¡ º¯È­¹«½ÖÇÏ°Ô º¸ÀÌ´Â°Í º¸Á¤
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetMainCharHPCorrect( HTint iCurHP )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
		{
			if( t->oOtherObject.m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			{
				t->oOtherObject.m_iOther_TargetHP[i] = iCurHP;
			}
		}
		t = t->next;
	}
}
//	Setting Init Targetting
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetInitTargetting()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetHideInfomation();
		//	HP hp¹Ù ÄÁÆ®·Ñ----------//
		g_pMainBar->HT_vSetObjectTextDraw( _T("") );
		g_pMainBar->HT_vSetObjectHPDraw( 0, 0 );
		t = t->next;
	}
}
//	Setting Strong Ashiram
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetStrongAshiram( CHTString strAshiram1, CHTString strAshiram2 )
{
	CHTString strMyGuild = strAshiram1.HT_szGetString();
	CHTString strArlliedGuild = strAshiram2.HT_szGetString();
	HTint iMyStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
		{
			//	ÁÖ½ÅÀü Áö¿ªÀÎ¸é ´Ù¸¥ ÁÖ½ÅÀÌ¸é °ø°Ý °¡´É
			if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
			{
				if( g_oMainCharacterInfo.byTrimuriti != t->oOtherObject.m_pObjectInfo->byTrimuriti )
					t->oOtherObject.m_bOther_DefinZoneAttackTarget = TRUE;
				else
					t->oOtherObject.m_bOther_DefinZoneAttackTarget = FALSE;
			}
			//	¿ä»õÀü Áö¿ªÀÌ¸é ÀÚ½ÅÀÇ ±æµå³ª ¿¬ÇÕ±æµå°¡ ¾Æ´Ï¸é °ø°Ý °¡´É
			else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				if( strlen(t->oOtherObject.m_pObjectInfo->szGuild) > 0 )
				{
					//	Å¸ ±æµå Ã¼Å©
					if( strMyGuild.HT_iStringCompare( t->oOtherObject.m_pObjectInfo->szGuild ) != 0 &&
						strArlliedGuild.HT_iStringCompare( t->oOtherObject.m_pObjectInfo->szGuild ) != 0 )
						t->oOtherObject.m_bOther_DefinZoneAttackTarget = TRUE;
					else
						t->oOtherObject.m_bOther_DefinZoneAttackTarget = FALSE;
				}
				else
				{
					t->oOtherObject.m_bOther_DefinZoneAttackTarget = TRUE;
				}
			}
			//	ÀÏ¹Ý ÇÊµå¸é ´Ù¸¥ ·ÎÁ÷À» Å¸°ÔµÈ´Ù.
			else
			{
				t->oOtherObject.m_bOther_DefinZoneAttackTarget = FALSE;
			}
		}
		else
		{
			t->oOtherObject.m_bOther_DefinZoneAttackTarget = TRUE;
			//	ÁÖ½ÅÀü Áö¿ªÀÎ¸é ´Ù¸¥ ÁÖ½ÅÀÌ¸é °ø°Ý °¡´É
			if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
			{
				if( g_oMainCharacterInfo.byTrimuriti == t->oOtherObject.m_pObjectInfo->byTrimuriti )
					t->oOtherObject.m_bOther_DefinZoneAttackTarget = FALSE;
			}
			//	¿ä»õÀü Áö¿ªÀÌ¸é ÀÚ½ÅÀÇ °æºñº´À» Ã¼Å©
			else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
			{
				//	ÀÚ½ÅÀÇ °æºñº´À» Ã¼Å©
				if( (iMyStrongGuild==0 && t->oOtherObject.m_pObjectInfo->byTrimuriti==14 ) ||
					(iMyStrongGuild==1 && t->oOtherObject.m_pObjectInfo->byTrimuriti==15 ) ||
					(iMyStrongGuild==2 && t->oOtherObject.m_pObjectInfo->byTrimuriti==16 ) ||
					(iMyStrongGuild==3 && t->oOtherObject.m_pObjectInfo->byTrimuriti==17 ) )
					t->oOtherObject.m_bOther_DefinZoneAttackTarget = FALSE;
			}
		}
		t = t->next;
	}
}
//	Setting Item Effect
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetItemEffect( HTint iUserKeyID, HTint iItemID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( iUserKeyID == t->oOtherObject.m_pObjectInfo->nID )
		{
		//	HTint idFX;
	//		g_pParamMgr->HT_bGetItemFXEffectID( iItemID, &idFX );

//			HTint id;
//			if ( idFX ) g_pEngineHandler->HT_hrStartSFX( &id, idFX, t->oOtherObject.m_iOtherModelID, HT_FALSE );

			return;
		}
		t = t->next;
	}
}
//	Setting	Targetting
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetTargetting()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		t->oOtherObject.HT_vOtherObject_SetTargetting();
		t = t->next;
	}
}
//	Setting	Targetting
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetTargetting( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.HT_vOtherObject_SetTargetting();
			return;
		}
		t = t->next;
	}
}
//	Setting	Change Shop Mode
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetChangeShopMode()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->byTradeMode != 0 )
            t->oOtherObject.HT_vOtherObject_CreateModel();
		t = t->next;
	}
}
//	Setting	Change Animation
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetChangeAnimation( HTint iKeyID, HTint iAniType, HTint iAniCount )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.m_iOther_AniResentState = iAniType;
			t->oOtherObject.HT_vOtherObject_SetChangeAnimation( iAniCount, 0.0f, 0 );
			return;
		}
		t = t->next;
	}
}
//	Setting Init Guild Name
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetInitGuild( CHTString strName )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_pObjectInfo->szName ) == 0 )
		{
			ZeroMemory( t->oOtherObject.m_pObjectInfo->szGuild, SZGUILD_LENGTH );
			t->oOtherObject.HT_vOtherObject_SetGuildMarkOff();
			return;
		}
		t = t->next;
	}
}
//	Setting Object Show
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_SetObjectShow( HTbool bShow )
{
	//	Show Object
	m_bOOSystem_ShowObject = bShow;

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( m_bOOSystem_ShowObject )
			t->oOtherObject.HT_vOtherObject_CreateModel();
		else
			t->oOtherObject.HT_vOtherObject_DeleteModel();
		t = t->next;
	}
}

//	Returns
//	Returns Show Chat Msg
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_GetShowChatMsg()
{
	return m_bOOSystem_ChatMsgShowSw;
}
//	Returns ÇØ´ç¼¿¿¡ À§Ä¡ÇÑ ¿ÀºêÁ§Æ®°¡ ÀÖ´Â°¡?
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetCheckMapCell( HTint iMapCellX, HTint iMapCellZ )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		HTPoint pPt = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( pPt.x==iMapCellX && pPt.y==iMapCellZ )
		{
			return t->oOtherObject.m_pObjectInfo->nID;
		}
		t = t->next;
	}
	return 0;
}
//	Returns Get ModelID From KeyID
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetModelID( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_iOtherModelID;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get KeyID From ModelID
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetKeyID( HTint iModelID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOtherModelID == iModelID )
		{
			return t->oOtherObject.m_pObjectInfo->nID;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Level From KeyID
HTbyte HTOtherObjectSystem::HT_byOtherObjectSystem_GetLevel( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->byLevel;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Name From KeyID
CHTString HTOtherObjectSystem::HT_strOtherObjectSystem_GetNameFromKeyID( HTint ikeyID )
{
	CHTString strName;
	HT_OTHEROBJECT_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == ikeyID )
		{
			return t->oOtherObject.m_strOther_Name.HT_szGetString();
		}
		t = t->next;
	}

	return strName;
}
//	Returns Get Name From ModelID
CHTString HTOtherObjectSystem::HT_strOtherObjectSystem_GetNameFromModelID( HTint iModelID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOtherModelID == iModelID )
		{
			if( t->oOtherObject.m_pObjectInfo->byGMStatus & 0x02 )
				return _T("");
			else
                return t->oOtherObject.m_strOther_Name.HT_szGetString();
		}
		t = t->next;
	}

	return _T("");
}
//	Returns Get Cur Cell Pos From KeyID
HTPoint HTOtherObjectSystem::HT_pOtherObjectSystem_GetCellPosFromKeyID( HTint iKeyID, HTint iSkillID )
{
	HTPoint	pCellPos;
	pCellPos.x = 0; pCellPos.y = 0;

	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			if( t->oOtherObject.m_pObjectInfo->nCurHP > 0 )
				return t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
			else
			{
				//	ºÎÈ°½ºÅ³ÀÏ¶§¸¦ Ã¼Å©
				if( iSkillID == HT_SKILLINDEX_SAMUDABA )
					return t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
				else
                    return pCellPos;
			}
		}
		t = t->next;
	}

	return pCellPos;
}
//	Returns Get Cur Cood Pos From KeyID
HTvector3 HTOtherObjectSystem::HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}
//	Returns Get Target Cood Pos From KeyID
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_GetTargetCoodFromKeyID( HTint iKeyID )
{
	return HT_TRUE;
}
//	Returns Get KeyID From Cell Pos For Piercing
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetKeyIDFromCellForPiercing( HTdword dwSkillType, HTvector3 vecCurPos, HTint *iElement )
{
	HTvector3 vecObjectPos;
	HTint iCount = 0;
	HTfloat fTerm;
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;
	HTbool bTrue;

	while( t != m_sOtherObjectTail )
	{
		vecObjectPos = t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
		fTerm = HT_extern_fGetDisForTwoPoint( vecObjectPos, vecCurPos );
		if( fTerm < MAP_CELL_SIZE*(t->oOtherObject.m_byOther_Size+2) )
		{
			bTrue = HT_TRUE;
			for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
			{
				if( iElement[i] > 0 )
				{
					if( t->oOtherObject.m_pObjectInfo->nID == iElement[i] )
						bTrue = HT_FALSE;
				}
			}

			if( bTrue )
			{
				if( t->oOtherObject.m_bOhter_Targetting == HT_TRUE )
					return t->oOtherObject.m_pObjectInfo->nID;

				////	Á¶°Ç¿¡ ÇÕ´çÇÑÁö Ã¼Å©ÇÏ°í ÇÕ´çÇÏ¸é ID, ¸®ÅÏ
				////	Ä³¸¯ÅÍÀÏ¶§
				//if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
				//{
				//	//	ÁÖ½ÅÀüÁö¿ª
				//	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
				//	{
				//		if( t->oOtherObject.m_pObjectInfo->byTrimuriti != g_oMainCharacterInfo.byTrimuriti )
				//		{
				//			return t->oOtherObject.m_pObjectInfo->nID;
				//		}
				//	}
				//	//	ÁÖ½ÅÀüÁö¿ª ¾Æ´Ò¶§
				//	else
				//	{
				//		//	PK¹öÆ°ÀÌ ´­·¯Á® ÀÖ°Å³ª 20·¹º§ ÀÌ»óÀÏ¶§
				//		if( g_pMainBar->HT_bGetPKButton() ||
				//			g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
				//		{
				//			if( t->oOtherObject.m_byOther_PartyMember != 0x02 &&
				//				t->oOtherObject.m_pObjectInfo->byLevel >= 20 )
				//			{
				//				return t->oOtherObject.m_pObjectInfo->nID;
				//			}
				//		}
				//	}
				//}
				////	¸ó½ºÅÍÀÏ¶§
				//else
				//{
				//	return t->oOtherObject.m_pObjectInfo->nID;
				//}
			}
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Cur Cood Pos From ModelID
HTvector3 HTOtherObjectSystem::HT_vecOtherObjectSystem_GetCoordPosFromModelID( HTint iModelID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOtherModelID == iModelID )
		{
			return t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}
//	Returns Get ModelID on TargetWindow
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetTargetModelIDOnTargetWindow()
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_bOther_InfoSw == HT_TRUE )
		{
			return t->oOtherObject.m_iOtherModelID;
		}
		t = t->next;
	}

	return -1;
}
//	Returns Get Object Live From KeyID
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_GetLiveFromKeyID( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			if( (t->oOtherObject.m_iOther_LiveIndex==OTHERCHAR_STATE_LIVE) )
			{
				if( (t->oOtherObject.m_pObjectInfo->iAffections & eTNVSAfn_Invisible) == 0 )
				{
					return HT_TRUE;
				}
				else
				{
					if( (g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_WizardEyes) != 0 )
						return HT_TRUE;
					else
						return HT_FALSE;
				}
			}
			else
				return HT_FALSE;
		}
		t = t->next;
	}

	return HT_FALSE;
}
//	Returns Get ¹üÀ§°ø°Ý ¿µ¿ª¾È¿¡ µé¾î°£ Object
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_GetTerritoryArea( HTvector3 vecTargetPos, HTfloat fRange, HTint iSkillID, HTint iInvadeModelID, HTint iInvadeKeyID, HTbyte byGood, HTint *iElement )
{
	HTint iObjectCount;
	HTfloat fDis;
	HTvector3 vecPos;
	
    HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	iObjectCount = 0;
	if( iElement[iObjectCount] != 0 )
		iObjectCount++;
	
	while( t != m_sOtherObjectTail )
	{
		//	°Å¸®¸¦ ±¸ÇØ³»°í
		vecPos = t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
		fDis = (float)sqrt( double( ( (vecTargetPos.x - vecPos.x) * (vecTargetPos.x - vecPos.x) ) + ( (vecTargetPos.z - vecPos.z) * (vecTargetPos.z - vecPos.z) ) ) );
		if( fDis < fRange )
		{
			//	Á×Àº »óÅÂ°¡ ¾Æ´Ï°í
			if( t->oOtherObject.m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE )
			{
				//	ÁÁÀº½ºÅ³
				if( byGood )
				{
					//	Ä³¸¯ÅÍÀÏ¶§¸¸
					if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
					{
						//	Å¸±RÆÃÀÌ °¡´ÉÇÏÁö ¾ÊÀ¸¸é °°Àº ÆíÀÌ´Ù.
						if( t->oOtherObject.m_bOhter_Targetting == HT_FALSE )
						{
							iElement[iObjectCount] = t->oOtherObject.m_pObjectInfo->nID;
							iObjectCount++;
							if( iObjectCount == TN_MAX_TARGET_COUNT )
								break;
						}
					}
				}
				//	³ª»Û½ºÅ³
				else
				{
					//	Å¸±RÆÃÀÌ °¡´ÉÇÏÁö ¾ÊÀ¸¸é °°Àº ÆíÀÌ´Ù.
					if( t->oOtherObject.m_bOhter_Targetting == HT_TRUE )
					{
						t->oOtherObject.HT_vOtherObject_EffectAttack( iSkillID, 0, iInvadeModelID, iInvadeKeyID );
						iElement[iObjectCount] = t->oOtherObject.m_pObjectInfo->nID;
						iObjectCount++;
						if( iObjectCount == TN_MAX_TARGET_COUNT )
							break;
					}
				}
			}
		}
		t = t->next;
	}

	return;
}
//	Returns °ø°ÝÀÚÀÇ À§Ä¡¸¦ Æ÷ÂøÇØ¿È
HTvector3 HTOtherObjectSystem::HT_vecOtherObjectSystem_SRAttackPos( DWORD dwTargetKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == dwTargetKeyID )
		{
			HTvector3 vecPos = t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
			vecPos.y = (HTfloat)t->oOtherObject.m_iOtherModelID;
			return vecPos;
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

//	Returns Get Object Index
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetIndex( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->snTribe;
		}
		t = t->next;
	}

	return 0;
}

//	Returns Get Trimuriti
HTbyte HTOtherObjectSystem::HT_byOtherObjectSystem_GetTrimuriti( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->byTrimuriti;
		}
		t = t->next;
	}

	return 0;
}

//	Returns Get ÇÃ·¹ÀÌ¾î¿Í °¡Àå °¡±î¿î Àû KeyIDªO±â
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetObjectKeyIDMostNearMainChar( HTint iBeforeTargetID )
{
	HTPoint pMainPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTPoint pObjectPt;
	HTint iMostNearKeyID = 0;
	HTint iMostNear = 100;
	HTint iCurNear;
	HTbool	bCheckSw = HT_FALSE;
	HTbool  bBeforeTargetSw = HT_FALSE;
    
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE &&
			t->oOtherObject.m_iOther_TribeCode != 0x09 )
		{
			//	ÀÌÀü Å¸·ÀÌ ¾Æ´Ò¶§
			if( t->oOtherObject.m_pObjectInfo->nID != iBeforeTargetID )
			{
				if( t->oOtherObject.m_bOhter_Targetting == HT_TRUE )
				{
					pObjectPt = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
					iCurNear = (HTint)sqrt( double( (pObjectPt.x - pMainPt.x) * (pObjectPt.x - pMainPt.x) ) 
										+ double( (pObjectPt.y - pMainPt.y) * (pObjectPt.y - pMainPt.y) ) );

					if( iCurNear < iMostNear )
					{
						iMostNear = iCurNear;
						iMostNearKeyID = t->oOtherObject.m_pObjectInfo->nID;
						bCheckSw = HT_TRUE;
					}
				}
			}
			//	ÀÌÀü Å¸·ÀÏ¶§
			else  if( t->oOtherObject.m_pObjectInfo->nID == iBeforeTargetID )
			{
				if( t->oOtherObject.m_bOhter_Targetting == HT_TRUE )
                    bBeforeTargetSw = HT_TRUE;
			}
		}
		t = t->next;
	}

	//	¾Æ¹«°Íµµ ÇÈÇÑ°Ô ¾øÀ»¶§
	if( bCheckSw == HT_FALSE )
	{
		//	ÀÌÀü°Í¸¸ ÇÈµÆÀ»¶§
		if( bBeforeTargetSw == HT_TRUE )
            iMostNearKeyID = iBeforeTargetID;
	}

	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		//	Set Info
		if( t->oOtherObject.m_pObjectInfo->nID == iMostNearKeyID )
		{
			//---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
			m_bOOSystem_HPInfoSw = HT_TRUE;
			t->oOtherObject.HT_vOtherObject_SetShowInfomation( HT_FALSE );
			m_iOOSystem_ModelID = t->oOtherObject.m_iOtherModelID;
			//	HP hp¹Ù ÄÁÆ®·Ñ----------//
			g_pMainBar->HT_vSetObjectTextDraw( t->oOtherObject.m_strOther_Name.HT_szGetString() );
			g_pMainBar->HT_vSetObjectHPDraw( t->oOtherObject.m_pObjectInfo->nCurHP, t->oOtherObject.m_pObjectInfo->nMaxHP );
		}
		//	Hide Info
		else// if( t->oOtherObject.m_pObjectInfo->nID == iBeforeTargetID )// && iMostNearKeyID != 0 )
		{
			t->oOtherObject.HT_vOtherObject_SetHideInfomation();
		}

		t = t->next;
	}

	return iMostNearKeyID;
}
//	Returns Get ÇÃ·¹ÀÌ¾î¿Í °¡Àå °¡±î¿î µ¿·á KeyIDªO±â
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetAssociateKeyIDMostNearMainChar( HTint iBeforeTargetID )
{
	HTPoint pMainPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTPoint pObjectPt;
	HTint iMostNearKeyID = 0;
	HTint iMostNear = 100;
	HTint iCurNear;
    
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( //t->oOtherObject.m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE &&
			t->oOtherObject.m_iOther_TribeCode != 0x09 &&
			t->oOtherObject.m_pObjectInfo->nID != iBeforeTargetID &&
			(t->oOtherObject.m_pObjectInfo->iAffections & eTNVSAfn_Invisible) == 0 )
		{
			HTbool bTrue = HT_TRUE;
			//	¸ó½ºÅÍÀÏ¶§´Â ¹«Á¶°Ç false
			if( SERVEROBJECT_IS_MONSTER( t->oOtherObject.m_pObjectInfo->nID ) )
				bTrue = HT_FALSE;
			//	Ä³¸¯ÅÍÀÏ¶§´Â
			else
			{
				//	1. PK¹öÆ°ÀÌ ´­·¯ÀÜ »óÅÂÀÌ¸é false
				if( g_pMainBar->HT_bGetPKButton() ||
					g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
                    bTrue = HT_FALSE;
				//	2. ÁÖ½ÅÀüÁö¿ªÀÌ¸é¼­ ´Ù¸¥ ÁÖ½ÅÀÏ¶§´Â false
				if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) && 
					g_oMainCharacterInfo.byTrimuriti != t->oOtherObject.m_pObjectInfo->byTrimuriti )
					bTrue = HT_FALSE;
			}

			if( bTrue )
			{
				pObjectPt = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
				iCurNear = (HTint)sqrt( double( (pObjectPt.x - pMainPt.x) * (pObjectPt.x - pMainPt.x) ) 
									+ double( (pObjectPt.y - pMainPt.y) * (pObjectPt.y - pMainPt.y) ) );

				if( iCurNear < iMostNear )
				{
					iMostNear = iCurNear;
					iMostNearKeyID = t->oOtherObject.m_pObjectInfo->nID;
				}
			}
		}
		t = t->next;
	}

	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		//	Set Info
		if( t->oOtherObject.m_pObjectInfo->nID == iMostNearKeyID )
		{
			//---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
			m_bOOSystem_HPInfoSw = HT_TRUE;
			t->oOtherObject.HT_vOtherObject_SetShowInfomation( HT_FALSE );
			m_iOOSystem_ModelID = t->oOtherObject.m_iOtherModelID;
			//	HP hp¹Ù ÄÁÆ®·Ñ----------//
			g_pMainBar->HT_vSetObjectTextDraw( t->oOtherObject.m_strOther_Name.HT_szGetString() );
			g_pMainBar->HT_vSetObjectHPDraw( t->oOtherObject.m_pObjectInfo->nCurHP, t->oOtherObject.m_pObjectInfo->nMaxHP );
		}
		//	Hide Info
		else if( t->oOtherObject.m_pObjectInfo->nID == iBeforeTargetID &&
				 iMostNearKeyID !=0 )
		{
			t->oOtherObject.HT_vOtherObject_SetHideInfomation();
		}

		t = t->next;
	}

	return iMostNearKeyID;
}
//	Returns Get TradeMode
HTbyte HTOtherObjectSystem::HT_byOtherObjectSystem_GetTradeMode( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->byTradeMode;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Party
HTbyte HTOtherObjectSystem::HT_byOtherObjectSystem_GetParty( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_byOther_PartyMember;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get class1
HTbyte HTOtherObjectSystem::HT_byOtherObjectSystem_GetClass1( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->byClass1;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get KeyID Form Name
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetKeyIDFromName( CHTString strName )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( strName.HT_iStringCompare( t->oOtherObject.m_strOther_Name.HT_szGetString() ) == 0 )
		{
			return t->oOtherObject.m_pObjectInfo->nID;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get ItemIndex of Equip
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetItemIndexofEquip( HTint iKeyID, HTint iPart )
{
	if( iPart<0 && iPart>6 )
		return 0;

	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return (HTint)t->oOtherObject.m_pObjectInfo->Equip[iPart].snIndex;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get	bCheck2ObjCollide
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_GetCheck2ObjCollide( HTint iKeyID, HTvector3 vecMainCharPos, HTfloat ColidSize )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		//	iKeyID°¡ 0 ÀÌ¸é MOB°ú Ãæµ¹Ã¼Å©
		if( iKeyID == 0 )
		{
			//	»ì¾ÒÀ»¶§¸¸ Ã¼Å©
			if( t->oOtherObject.m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE )
			{
				//	¹æÇâ Á¤º¸ ÀÖÀ»¶§¸¸ °Ë»ç, °ÅÀÇ ¹®ÀÏ °æ¿ìÀÌ´Ù.
				//if( HT_SUCCEED( HT_IS_MOBGATE( t->oOtherObject.m_pObjectInfo->snTribe ) ) )
				if( t->oOtherObject.m_bOther_CollisonCheck == HT_TRUE )
				{
					//	Ãæµ¹ÇÏ¸é »ó´ë¹æ KeyID ¹ÝÈ¯
					if( g_pEngineHandler->HT_bCheck2ObjCollide( t->oOtherObject.m_iOtherModelID, vecMainCharPos, ColidSize ) )
					{
						return t->oOtherObject.m_iOtherModelID;
					}
				}
				else
				{
					////	ÁÖ½ÅÀü Áö¿ªÀÎ¸é
					//if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
					//{
					//	if( t->oOtherObject.m_pObjectInfo->byClan != g_cMainCharacter->HT_byMainChar_GetClanValue() )
					//	{
					//		if( g_pEngineHandler->HT_bCheck2ObjCollide( t->oOtherObject.m_iOtherModelID, vecMainCharPos, ColidSize ) )
     //                           return t->oOtherObject.m_iOtherModelID;
					//	}
					//}

					//	ÁÖ½ÅÀü Áö¿ªÀÏ¶§´Â Àû Ä³¸¯ÅÍ¿Í Ãæµ¹Ã¼Å©
					if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) ||
						HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) || 
						HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
					{
						if( ( t->oOtherObject.m_bOther_DefinZoneAttackTarget == TRUE ) )
						{
							if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
							{
								//	Ãæµ¹ÇÏ¸é »ó´ë¹æ KeyID ¹ÝÈ¯
								if( g_pEngineHandler->HT_bCheck2ObjCollide( t->oOtherObject.m_iOtherModelID, vecMainCharPos, ColidSize ) )
								{
									return t->oOtherObject.m_iOtherModelID;
								}
							}
							else
							{
								HTbyte byReserved7;
								if( g_pParamMgr->HT_bGetMonsterReserved7( t->oOtherObject.m_iOther_TribeCode, &byReserved7 ) == true )
								{
									//	°¡µåÀÏ¶§¹®
									if( 0x02 & byReserved7 )
									{
										//	Ãæµ¹ÇÏ¸é »ó´ë¹æ KeyID ¹ÝÈ¯
										if( g_pEngineHandler->HT_bCheck2ObjCollide( t->oOtherObject.m_iOtherModelID, vecMainCharPos, ColidSize ) )
										{
											return t->oOtherObject.m_iOtherModelID;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			//	¹æÇâ Á¤º¸ ÀÖÀ»¶§¸¸ °Ë»ç
			if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
			{
				//	Ãæµ¹ÇÏ¸é TRUE, Ãæµ¹ÇÏÁö ¾ÊÀ¸¸é FALSE¸¦ ¹ÝÈ¯
				if( g_pEngineHandler->HT_bCheck2ObjCollide( t->oOtherObject.m_iOtherModelID, vecMainCharPos, ColidSize ) )
				{
					return t->oOtherObject.m_iOtherModelID;
				}
			}
		}

		t = t->next;
	}

	return 0;
}
//	Returns Get	bCheck2ObjCollide
HTshort HTOtherObjectSystem::HT_vOtherObjectSystem_GetKarma( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->snKarma;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get	Attack Target
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_GetAttackTarget( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_bOther_DefinZoneAttackTarget;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Check Can Attack Target For Normal Attack
HTRESULT HTOtherObjectSystem::HT_bOtherObjectSystem_GetCheckCanAttackTargetForNormal( HTint iTargetKeyID, HTPoint pMainCharPt )
{
	if( iTargetKeyID == 0 )
		return HT_FAIL;

    HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iTargetKeyID )
		{
			//	Ä³¸¯ÀÏ¶§
			if( SERVEROBJECT_IS_CHARACTER( iTargetKeyID ) )
			{
				//	¿ä»õÀü Áö¿ªÀÇ °áÅõÀå¿¡ ÀÖÀ»°æ¿ì ÆÄÆ¼°¡ ¾Æ´Ï¸é °ø°Ý
				if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
				{
					HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
					HTPoint pPt2 = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
					if( pPt.x>=285 && pPt.x<=345 &&	pPt.y>=677 && pPt.y<=736 &&
						pPt2.x>=285 && pPt2.x<=345 && pPt2.y>=677 && pPt2.y<=736 )
					{
						//	°°Àº ÆÄÆ¼ÀÏ¶§µµ °ø°Ý ½ºÅµ
						if( t->oOtherObject.m_byOther_PartyMember != 0x02 )
							return HT_OK;
					}
				}

				//	ÁÖ½ÅÀü Áö¿ª°ú ¿ä»õÀü Áö¿ªÀÌ¸é¼­ °ø°Ý ´ë»óÀÚ¶ó¸é ¹«Á¶°Ç °ø°Ý
				if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == TRUE )
					return HT_OK;

				//	PK ¹öÆ°ÀÌ ºñ È°¼ºÈ­ »óÅÂÀÌ°í °áÅõ¸ðµå°¡ ¾Æ´Ï¸é
				if( !g_pMainBar->HT_bGetPKButton() &&
					g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
					return HT_FAIL;

				//	°áÅõ ¸ðµåÀÌ¸ç TargetKeyID °¡ Æ²¸®¸é ½ºÅµ
				if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat && 
					g_pDuelSystem->HT_iDuel_GetDuelCharKeyID() != iTargetKeyID )
					return HT_FAIL;

				//	°áÅõ¸ðµå°¡ ¾Æ´Ï°í ³ª¿Í »ó´ë¹æÀÌ ·¹º§ 20ÀÌÇÏÀÌ¸é
				if( iTargetKeyID != g_cMainCharacter->HT_iMainChar_GetKeyID() &&
					g_pDuelSystem->HT_byDuel_GetDuelMode() != eChallenge_Combat )
				{
					if( g_cStatus->HT_byGetLevel() < 20 )
						return HT_FAIL;

					if(	t->oOtherObject.m_pObjectInfo->byLevel < 20 )
						return HT_FAIL;
				}
			}
			//	¸÷ÀÏ¶§
			else
			{
				//	class1ÀÌ 19ÀÌ¸é _MSG_CONTZCT_NPC ¸Þ½ÃÁö¸¦ º¸³½´Ù.
                if( t->oOtherObject.m_pObjectInfo->byClass1 == 19 )
					this->HT_vOtherObjectSystem_NetWorkCONTACT_NPC( iTargetKeyID );

				//	ÁÖ½ÅÀü Áö¿ª°ú ¿ä»õÀü Áö¿ªÀÌ¸é¼­ °ø°Ý ´ë»óÀÚ°¡ ¾Æ´Ï¸é ¹«Á¶°Ç ½ºÅµ
				if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == FALSE )
					return HT_FAIL;
			}
			return HT_OK;
		}
		t = t->next;
	}

	return HT_FAIL;
}
//	Returns Get Check Can Attack Target For Skill Attack
HTRESULT HTOtherObjectSystem::HT_bOtherObjectSystem_GetCheckCanAttackTargetForSkill( HTbool bTimeCheckForSkillStart, HTint iTargetKeyID, HTPoint pMainCharPt, HTint iSkill, HTint& iMainChar_Target_KeyID, HTint& iMainChar_MemoryTargetKeyID )
{
	if( iTargetKeyID == 0 )
		return HT_FAIL;

	HTint iMainCharKeyID = g_cMainCharacter->HT_iMainChar_GetKeyID();
	HTbyte bySkillGoodType = 0;
	g_pParamMgr->HT_bGetPCSkillType( iSkill, 1, &bySkillGoodType );	//	0:³ª»Û°Í, 1:ÁÁÀº°Í

	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iTargetKeyID )
		{
			//	ÁÁÀº ½ºÅ³
			if( bySkillGoodType )
			{
				//	TargetÀÌ MOB ÀÏ¶§
				if( SERVEROBJECT_IS_MONSTER( iTargetKeyID ) )
				{
					//	Object Targeting EFfect off
					this->HT_vOtherObjectSystem_HPWindowInit();
					//	Target ´ë»óÀ» MainChar
					if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == TRUE )
					{
						//	ÀúÀåÅ¸·À» °ø°ÝÆ÷ÀÎÆ® ÀÌÀü¿¡ ¹Ù·Î ½ºÅ³ µé¾î°¡¸é ¸÷À¸·Î °ø°ÝÆ÷ÀÎÆ® ÀÌÈÄ¸é Å¸·À» ¸ÞÀÎÄ³¸¯ÅÍ·Î
						if( bTimeCheckForSkillStart )
                            iMainChar_MemoryTargetKeyID = iTargetKeyID;
						else
							iMainChar_MemoryTargetKeyID = iMainCharKeyID;
					}
					//	ÇöÀç Å¸·À» °ø°ÝÆ÷ÀÎÆ® ÀÌÀü¿¡ ¹Ù·Î ¸ÞÀÎÄ³¸¯ÅÍ·Î, °ø°ÝÆ÷ÀÎÆ® ÀÌÈÄ¸é ¸÷À¸·Î
					if( bTimeCheckForSkillStart )
                        iMainChar_Target_KeyID = iMainCharKeyID;
					else
						iMainChar_Target_KeyID = iTargetKeyID;
				}
				//	OtherChar ÀÏ¶§
				else if( iTargetKeyID != iMainCharKeyID )
				{
					//	¿ä»õÀü Áö¿ªÀÇ °áÅõÀå¿¡ ÀÖÀ»°æ¿ì ÆÄÆ¼°¡ ¾Æ´Ï¸é °ø°Ý
					if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
					{
						HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
						HTPoint pPt2 = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
						if( pPt.x>=285 && pPt.x<=345 &&	pPt.y>=677 && pPt.y<=736 &&
							pPt2.x>=285 && pPt2.x<=345 && pPt2.y>=677 && pPt2.y<=736 )
						{
							//	°°Àº ÆÄÆ¼ÀÏ¶§µµ °ø°Ý ½ºÅµ
							if( t->oOtherObject.m_byOther_PartyMember == 0x02 )
								return HT_OK;
							else
								return HT_FAIL;
						}
					}

					//	PK ¹öÆ° È°¼ºÈ­ ÀÌ°í °áÅõ ¸ðµåÀÏ¶§´Â ´ë»óÀ» ¸ÞÀÎÄ³¸¯ÅÍ·Î ÇÑ´Ù.
					if( g_pMainBar->HT_bGetPKButton() ||
						g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
					{
						//	Object Targeting EFfect off
						this->HT_vOtherObjectSystem_HPWindowInit();
						//	Target ´ë»óÀ» MainChar
						if( bTimeCheckForSkillStart )
						{
							iMainChar_MemoryTargetKeyID = iTargetKeyID;
							iMainChar_Target_KeyID = iMainCharKeyID;
						}
						else
						{
							iMainChar_MemoryTargetKeyID = iMainCharKeyID;
							iMainChar_Target_KeyID = iTargetKeyID;
						}
					}
					//	PK ¹öÆ° ºñÈ°¼ºÈ­ ÀÏ¶§
					else
					{
						//	ÁÖ½ÅÀü Áö¿ª°ú ¿ä»õÀü Áö¿ªÀÌ¸é¼­ °ø°Ý °¡´É Ä³¸¯ÀÌ¸é
						if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == TRUE )
						{
							//	Object Targeting EFfect off
							g_cOtherObjectSystem->HT_vOtherObjectSystem_HPWindowInit();
							//	Target ´ë»óÀ» MainChar
							if( bTimeCheckForSkillStart )
							{
								iMainChar_MemoryTargetKeyID = iTargetKeyID;
								iMainChar_Target_KeyID = iMainCharKeyID;
							}
							else
							{
								iMainChar_MemoryTargetKeyID = iMainCharKeyID;
								iMainChar_Target_KeyID = iTargetKeyID;
							}
						}
						else
						{
							iMainChar_MemoryTargetKeyID = iMainCharKeyID;
						}
					}
				}
				return HT_OK;
			}
			//	³ª»Û ½ºÅ³
			else
			{
				//	-> OtherChar ÀÏ¶§
				if( SERVEROBJECT_IS_CHARACTER( iTargetKeyID ) )
				{
					//	¿ä»õÀü Áö¿ªÀÇ °áÅõÀå¿¡ ÀÖÀ»°æ¿ì ÆÄÆ¼°¡ ¾Æ´Ï¸é °ø°Ý
					if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
					{
						HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
						HTPoint pPt2 = t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
						if( pPt.x>=285 && pPt.x<=345 &&	pPt.y>=677 && pPt.y<=736 &&
							pPt2.x>=285 && pPt2.x<=345 && pPt2.y>=677 && pPt2.y<=736 )
						{
							//	°°Àº ÆÄÆ¼ÀÏ¶§µµ °ø°Ý ½ºÅµ
							if( t->oOtherObject.m_byOther_PartyMember != 0x02 )
								return HT_OK;
						}
					}

					//	ÁÖ½ÅÀü Áö¿ª°ú ¿ä»õÀü Áö¿ªÀÌ¸é¼­ °ø°Ý ´ë»óÀÚ¶ó¸é ¹«Á¶°Ç °ø°Ý
					if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == TRUE )
						return HT_OK;

					//	°°Àº ÆÄÆ¼ÀÏ¶§ °ø°Ý ½ºÅµ
					if( t->oOtherObject.m_byOther_PartyMember == 0x02 )
						return HT_FAIL;
				}
				//	¸÷ÀÏ¶§´Â °ø°Ý ºÒ°¡ÇÑ Å¸·ÀÎÁö¸¸ ÆÄ¾Ç
				else
				{
					if( t->oOtherObject.m_bOther_DefinZoneAttackTarget == FALSE )
						return HT_FAIL;
				}
				//	¿¹¾à°ø°ÝÀÚ ¼ÂÆÃ
				iMainChar_MemoryTargetKeyID = iTargetKeyID;
			}
			break;
		}
		t = t->next;
	}

	if( t == m_sOtherObjectTail )
	{
		//	ÁÁÀº ½ºÅ³
		if( bySkillGoodType )
		{
			iMainChar_Target_KeyID = iMainCharKeyID;
			return HT_OK;
		}
		else
		{
			return HT_FAIL;
		}
	}

	return HT_OK;
}
//	Returns Get Ashiram Name From KeyID
CHTString HTOtherObjectSystem::HT_strOtherObjectSystem_GetAshiramNameFromKeyID( HTint iKeyID )
{
	CHTString strName;
	HT_OTHEROBJECT_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			strName = t->oOtherObject.m_pObjectInfo->szGuild;
			return strName.HT_szGetString();
		}
		t = t->next;
	}

	return strName;
}
//	Returns Get Cast Name From KeyID
CHTString HTOtherObjectSystem::HT_strOtherObjectSystem_GetCastNameFromKeyID( HTint iKeyID )
{
	CHTString strName;
	HT_OTHEROBJECT_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_strOther_CastName.HT_szGetString();
		}
		t = t->next;
	}

	return strName;
}
//	Returns Get DefineZoneAttackTarget
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_GetDefineZoneAttackTargetFromKeyID( HTint iKeyID )
{
	CHTString strName;
	HT_OTHEROBJECT_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_bOther_DefinZoneAttackTarget;
		}
		t = t->next;
	}
	return HT_FALSE;
}
//	Returns Get Affection
__int64	HTOtherObjectSystem::HT_iOtherObjectSystem_GetAffection( HTint iKeyID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			return t->oOtherObject.m_pObjectInfo->iAffections;
		}
		t = t->next;
	}

	return 0;
}
//	Returns Get Targetting
HTbool HTOtherObjectSystem::HT_hrOtherObjectSystem_GetTargetting( HTint iKeID )
{
	HT_OTHEROBJECT_NODE *t;

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeID )
		{
			//	class1ÀÌ 19ÀÌ¸é _MSG_CONTZCT_NPC ¸Þ½ÃÁö¸¦ º¸³½´Ù.
            if( t->oOtherObject.m_pObjectInfo->byClass1 == 19 )
			{
				this->HT_vOtherObjectSystem_NetWorkCONTACT_NPC( iKeID );
				return HT_FALSE;
			}
			return t->oOtherObject.m_bOhter_Targetting;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//	Setting and Returns
//	Setting and Returns Pick Check From ModelID
HTint HTOtherObjectSystem::HT_iOtherObjectSystem_SRPickIDCheck( HTint iModelID )
{
	//-----NPC ³ëµå¿¡¼­ Ã¼Å©-----//
	HT_OTHEROBJECT_NODE *t;
	
	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOtherModelID == iModelID )
		{
			//	Ã­Åõ¶û°¡¿ë Æ÷Å» ¸ó½ºÅÍ ÀÏ¶§
			if( t->oOtherObject.m_pObjectInfo->snTribe == FORPOTAL_MOBID_FORCHATURANGR )
			{
				if( g_oMainCharacterInfo.byTrimuriti == t->oOtherObject.m_pObjectInfo->byTrimuriti )
				{
					if( HT_SUCCEED( g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORCHATURANGR, t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() ) ) )
						return FORPOTAL_MOBID_FORCHATURANGR;
				}
			}
			//	Ã­Åõ¶û°¡¿ë Æ÷Å» ¸ó½ºÅÍ ÀÏ¶§
			else if( t->oOtherObject.m_pObjectInfo->snTribe == FORPOTAL_MOBID_FORTRIMURITICAVE )
			{
                if( HT_SUCCEED( g_cPortal->HT_vPortal_Click( FORPOTAL_MOBID_FORTRIMURITICAVE, t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() ) ) )
					return FORPOTAL_MOBID_FORTRIMURITICAVE;
			}
			//	GM ¾Æ´Ò¶§
			else if( t->oOtherObject.m_iOther_TribeCode != 0x09 )
			{
				//---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
				m_bOOSystem_HPInfoSw = HT_TRUE;
				if (m_iOOSystem_ModelID!=iModelID)
				{
					t->oOtherObject.HT_vOtherObject_SetShowInfomation( HT_FALSE );
					m_iOOSystem_ModelID = iModelID;
				}
				else
				{
					t->oOtherObject.HT_vOtherObject_SetShowInfomation( HT_TRUE );
				}
				//	HP hp¹Ù ÄÁÆ®·Ñ----------//
				g_pMainBar->HT_vSetObjectTextDraw( t->oOtherObject.m_strOther_Name.HT_szGetString() );
				g_pMainBar->HT_vSetObjectHPDraw( t->oOtherObject.m_pObjectInfo->nCurHP, t->oOtherObject.m_pObjectInfo->nMaxHP );

				return t->oOtherObject.m_pObjectInfo->nID;
			}
		}
		t = t->next;
	}

	return 0;
}
//	Setting and Returns ³»°¡ °ø°Ý ´ë»óÀÎÁö ÆÄ¾Ç
HTvector3 HTOtherObjectSystem::HT_vecOtherObjectSystem_SRAtkTargetCheck( HTint iTargetKeyID )
{
	HTvector3 vecTargetPos = HTvector3( 0, 0, 0 );

	//	1:OtherObject Check
	vecTargetPos = this->HT_vecOtherObjectSystem_SRAttackPos( iTargetKeyID );
	if( vecTargetPos.x != 0 )
	{
		return vecTargetPos;
	}

	//	3:MainChar Check
	vecTargetPos = g_cMainCharacter->HT_vecMainChar_GetAtkTargetCheck( iTargetKeyID );
	if( vecTargetPos.x != 0 )
	{
		return vecTargetPos;
	}

	return HTvector3( 0, 0, 0 );
}

//	Render
//	Render Control
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_Render()
{
	if( g_bGamePlayMovieForGlobal )
		return;

	//	Show Object
	if( !m_bOOSystem_ShowObject )
		return;

	HTbool	bBreakPoint = HT_FALSE;
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		//	1. Åõ¸í ¸ðµå Ã¼Å©
		//   -> GM Åõ¸í
		if( ( t->oOtherObject.m_pObjectInfo->byGMStatus & 0x02 ) == 0 )
		{
			//   -> Affections Åõ¸í / ¸¶¹ýÀÇ ´«°ú ¿¬°èÇØ¼­ ¼³Á¤ ÀÌ¸§/Ã¤ÆÃ¸Þ½ÃÁö
			if( m_bOOsystem_MainCharWizardEyesSw == HT_TRUE )
				this->HT_vOtherObjectSystem_RenderName( t );
			else if( (t->oOtherObject.m_pObjectInfo->iAffections&eTNVSAfn_Invisible) == 0 )
				this->HT_vOtherObjectSystem_RenderName( t );
		}

		if( t->oOtherObject.m_bOther_InfoSw	== HT_TRUE )
		{
			bBreakPoint = HT_TRUE;
		}

		t = t->next;
	}

	//---------Á¤º¸ µð½ºÇÃ·¹ÀÌ ¼ÂÆÃ----------//
	if( m_bOOSystem_HPInfoSw == HT_TRUE && bBreakPoint == HT_FALSE )
	{
		m_bOOSystem_HPInfoSw = HT_FALSE;
		g_pMainBar->HT_vSetObjectHPOut();
		g_pMainBar->HT_vSetObjectNameOut();
	}
}
//	Render Name
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_RenderName( HT_OTHEROBJECT_NODE* t )
{
	HTvector3 vTextPos = t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
	vTextPos.y += t->oOtherObject.m_fOther_ModelHeight + 3.0f;
	//    -> »ö±ò ÆÇÁ¤
	HTint iColor;
	iColor = 15;
	HT_COLOR cFontColor = HT_COLOR( 0.0f,0.0f,0.0f,0.0f );

	//	2. Ä³¸¯ÅÍ
	//	»ó´ë¹æ Ä³¸¯ ÀÌ¸§
	if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
	{
		//    -> »ö±ò ÆÇÁ¤
		//       -> Å¬¸¯ÇÑ »óÅÂ³Ä?	-> ³ë¶û
		if( t->oOtherObject.m_bOther_InfoSw == HT_TRUE )								iColor = 12;
		//		 -> ÁÖ½ÅÀü Áö¿ª¿¡¼­´Â Ä³¸¯ÅÍ ÀÌ¸§ ÁÖ½Å »ö±ò·Î Ç¥½Ã
		else if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) &&
			g_oMainCharacterInfo.byTrimuriti != t->oOtherObject.m_pObjectInfo->byTrimuriti )
		{
			//	ºê¶óÈå¸¶ ³ë¶û
			if( t->oOtherObject.m_pObjectInfo->byTrimuriti == TRIMURITI_BRAHMA )		iColor = 17;
			//	ºñ½´´À »¡°­
			else if( t->oOtherObject.m_pObjectInfo->byTrimuriti == TRIMURITI_VISHNU )	iColor = 18;
			//	½Ã¹Ù ÆÄ¶û
			else if( t->oOtherObject.m_pObjectInfo->byTrimuriti == TRIMURITI_SIVA )		iColor = 2;
		}
		//	ºñ·ù¼º Áö¿ªÀÏ¶§
		else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) &&
			t->oOtherObject.m_pObjectInfo->byClan >= 19 )
		{
			//	¼ö¼º
			if( t->oOtherObject.m_pObjectInfo->byClan == 19 )		cFontColor = HT_COLOR( 0.59f, 0.86f, 0.59f, 1.0f );
			//	°ø¼º1
			else if( t->oOtherObject.m_pObjectInfo->byClan == 20 )	cFontColor = HT_COLOR( 0.99f, 0.54f, 0.57f, 1.0f );
			//	°ø¼º2
			else if( t->oOtherObject.m_pObjectInfo->byClan == 21 )	cFontColor = HT_COLOR( 0.99f, 0.74f, 1.00f, 1.0f );
			//	°ø¼º3
			else if( t->oOtherObject.m_pObjectInfo->byClan == 22 )	cFontColor = HT_COLOR( 0.73f, 0.71f, 0.97f, 1.0f );
			//	¹«¼Ò¼Ó
			else if( t->oOtherObject.m_pObjectInfo->byClan == 23 )	cFontColor = HT_COLOR( 0.67f, 0.67f, 0.66f, 1.0f );
		}
		//       -> Ä«¿À³Ä? 		-> »¡°­
		else if( t->oOtherObject.m_pObjectInfo->snKarma > 0 )							iColor = 11;
		//       -> º¸¶óµ¹ÀÌ³Ä? 	-> º¸¶ó
		else if( t->oOtherObject.m_pObjectInfo->iAffections & eTNVSAfn_PKAttacker )		iColor = 10;
		//       -> ÆÄÆ¼³Ä?			-> ÀÚÁÖ
		else if( t->oOtherObject.m_byOther_PartyMember == 0x02 )						iColor = 7;
		//       -> ±æµå³Ä?			-> ¿À·£Áö
		else if( t->oOtherObject.m_bOther_MyGuildMemberSw == HT_TRUE )					iColor = 6;
		//       -> ÀÏ¹Ý			-> ¹é»ö
		else																			iColor = 15;
		//	Set Color
		if( cFontColor.a == 0.0f )
            cFontColor = g_ColorTable[iColor];

		////	PC¹æ ÀÌº¥Æ®
		//if( t->oOtherObject.m_pObjectInfo->dwEvent & 0x00000001 &&
		//	t->oOtherObject.m_pObjectInfo->byLevel < 60 )
		//{
		//	cFontColor.r -= 0.2f; if(cFontColor.r<0.0f)	cFontColor.r = 0.0f;
		//	cFontColor.g -= 0.2f; if(cFontColor.g<0.0f)	cFontColor.g = 0.0f;
		//	cFontColor.b -= 0.2f; if(cFontColor.b<0.0f)	cFontColor.b = 0.0f;
		//}

		//	-> ÀÌ¸§ Ç¥½Ã ½ºÀ§Ä¡°¡ ÄÑÁ® ÀÖ³Ä?
		if( m_bOOSystem_NameShowSw )
		{
			if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) &&
				t->oOtherObject.m_pObjectInfo->byTrimuriti != g_oMainCharacterInfo.byTrimuriti )
			{
				if( !g_bDevelopingMode )
				{
					m_strOOSystem_ShowObjectName.HT_szFormat( "%s %s", t->oOtherObject.m_pObjectInfo->szGuild, t->oOtherObject.m_strOther_CastName.HT_szGetString() );
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, m_strOOSystem_ShowObjectName.HT_szGetString(), vTextPos, cFontColor );
				}
				else
				{
					CHTString strName;
					strName.HT_szFormat( "%s,ID:%d,Af:%I64x,Af:%I64x", t->oOtherObject.m_strOther_Name.HT_szGetString(), t->oOtherObject.m_pObjectInfo->nID, t->oOtherObject.m_pObjectInfo->iAffections, t->oOtherObject.m_pObjectInfo->iAffections );
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strName, vTextPos, cFontColor );
				}
			}
			else
			{ 
				//    -> ±æµå ÀÌ¸§ Ç¥½Ã
				if( strlen( t->oOtherObject.m_pObjectInfo->szGuild ) > 0 )
				{
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->oOtherObject.m_pObjectInfo->szGuild, vTextPos, cFontColor );
					vTextPos.y += 2.0f;
				}
				//    -> Ä³¸¯ÅÍ ÀÌ¸§
				//       -> ºñ°³¹ß¸ðµå : ´Þ¶û Ä³¸¯ÅÍ ÀÌ¸§¸¸
				if( !g_bDevelopingMode )
				{
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->oOtherObject.m_strOther_Name.HT_szGetString(), vTextPos, cFontColor );
				}
				//       -> °³¹ß¸ðµå : Ä³¸¯ÅÍ ÀÏ¹ÝÁ¤º¸ Ç¥½Ã
				else
				{
					CHTString strName;
					strName.HT_szFormat( "%s,ID:%d,Af:%I64x,byDir:%d", t->oOtherObject.m_strOther_Name.HT_szGetString(), t->oOtherObject.m_pObjectInfo->nID, t->oOtherObject.m_pObjectInfo->iAffections, t->oOtherObject.m_pObjectInfo->byDir );
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strName, vTextPos, cFontColor );
				}
			}
			vTextPos.y += 2.0f;
			//    -> Æ¯¼öÄªÈ£
		}
		//	-> Ã¤ÆÃ Ç¥½Ã ½ºÀ§Ä¡°¡ ÄÑÁ® ÀÖ³Ä?
		if( m_bOOSystem_ChatMsgShowSw )
		{
			//   -> Ã¤ÆÃ ¸Þ½ÃÁö Ç¥½Ã
			if( !t->oOtherObject.m_strOther_ChatgMeg.HT_bIsEmpty() )
			{
				HTint iPassTime = GetTickCount();
				g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, (HTtchar*)t->oOtherObject.m_strOther_ChatgMeg, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 3.0f );
				vTextPos.y += 2.0f;
				if( iPassTime > t->oOtherObject.m_iOther_ChatMsgStartTime + CHATMSGDELAYTIME )
					t->oOtherObject.m_strOther_ChatgMeg.HT_hrCleanUp();
			}
		}
		//    -> »óÁ¡¸ðµå ¸Þ½ÃÁö
		if( t->oOtherObject.m_pObjectInfo->byTradeMode != 0 )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->oOtherObject.m_pObjectInfo->szTrade, vTextPos, g_ColorTable[5] );
			vTextPos.y += 2.0f;
		}
	}
	//	3. ¸ó½ºÅÍ
	else
	{
		//	-> ÀÌ¸§ Ç¥½Ã ½ºÀ§Ä¡°¡ ÄÑÁ® ÀÖ³Ä?
		if( m_bOOSystem_NameShowSw )
		{
			//    -> »ö±ò ÆÇÁ¤
			//       -> Å¬¸¯ÇÑ »óÅÂ³Ä?	-> ³ë¶û
			if( t->oOtherObject.m_bOther_InfoSw == HT_TRUE )
			{
				iColor = 12;
				//    -> Ä³¸¯ÅÍ ÀÌ¸§
				//       -> ºñ°³¹ß¸ðµå : ´Þ¶û Ä³¸¯ÅÍ ÀÌ¸§¸¸
				if( !g_bDevelopingMode )
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->oOtherObject.m_strOther_Name.HT_szGetString(), vTextPos, g_ColorTable[iColor] );
				//       -> °³¹ß¸ðµå : Ä³¸¯ÅÍ ÀÏ¹ÝÁ¤º¸ Ç¥½Ã
				else
				{
					CHTString strName;
					strName.HT_szFormat( "%s,ID:%d,Af:%I64x,byDir:%d", t->oOtherObject.m_strOther_Name.HT_szGetString(), t->oOtherObject.m_pObjectInfo->nID, t->oOtherObject.m_pObjectInfo->iAffections, t->oOtherObject.m_pObjectInfo->byDir );
					g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strName, vTextPos, g_ColorTable[iColor] );
				}
				vTextPos.y += 2.0f;
			}
		}

		//    -> Ã¤ÆÃ ¸Þ½ÃÁö
		if( m_bOOSystem_ChatMsgShowSw )
		{
			HTint iPassTime = GetTickCount();
			if( !t->oOtherObject.m_strOther_ChatgMeg.HT_bIsEmpty() )
			{
				g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->oOtherObject.m_strOther_ChatgMeg, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 3.0f );
				vTextPos.y += 2.0f;
				
				if( iPassTime > t->oOtherObject.m_iOther_ChatMsgStartTime + CHATMSGDELAYTIME )
					t->oOtherObject.m_strOther_ChatgMeg.HT_hrCleanUp();
			}
		}
	}
}
//	Render MinimapPoint
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_RenderMinimapPoint()
{
	if( !g_cMiniMap->HT_bMiniMap_IsOn() )
		return;
	g_cMiniMap->HT_vMiniMap_Render_StartObject( 0x01 );

	HT_OTHEROBJECT_NODE *t;

	{
		t = m_sOtherObjectHead->next;
		while( t != m_sOtherObjectTail )
		{
			if( SERVEROBJECT_IS_MONSTER( t->oOtherObject.m_pObjectInfo->nID ) )
			{
				g_cMiniMap->HT_vMiniMap_Render_OtherChar( 0x03, t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos() );
			}
			t = t->next;
		}
	}

	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		if( SERVEROBJECT_IS_CHARACTER( t->oOtherObject.m_pObjectInfo->nID ) )
		{
			//	GMÀÌ ¾Æ´Ò¶§¸¸ Ç¥½Ã
			//	Åõ¸í¸ðµå ¾Æ´Ò¶§
			if( t->oOtherObject.m_iOther_TribeCode != 0x09 &&
				(t->oOtherObject.m_pObjectInfo->iAffections & eTNVSAfn_Invisible) == 0 )
			{
				g_cMiniMap->HT_vMiniMap_Render_OtherChar( t->oOtherObject.m_byOther_PartyMember, t->oOtherObject.m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos() );
			}
		}
		t = t->next;
	}
}

//	Network
//	Network Object Insert
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkObjectInsert( PS_SCP_INIT_OTHER_MOB info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			this->HT_LL_hrDeleteNode( info->nID );
			break;
		}
		t = t->next;
	}

	this->HT_LL_hrInsertAfter( info );

	// Trade ¿äÃ»ÀÌ µé¾î¿ÔÀ» ¶§ Client Ä³¸¯ÅÍ Á¤º¸¿Í ´Þ¶ó¼­ initChar¸¦ ¿äÃ»ÇÑ °æ¿ì
	if( m_sCharInfoForTrade.nID )
	{
		if ( g_cExchangeSystem ) g_cExchangeSystem->HT_vNetWork_SCP_Resp_Trade( &m_sCharInfoForTrade );
		ZeroMemory( &m_sCharInfoForTrade, sizeof( S_CSP_REQ_TRADE ) );
	}
}
//	Network Object Remove Mob
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkObjectRemoveMob( PS_SCP_RESP_REMOVE_MOB info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			if( info->byResult == 1 )
			{
				if ( info->byRemoveType == 1 )
					t->oOtherObject.HT_vOtherObject_NetworkSummons();
				else
					t->oOtherObject.HT_vOtherObject_Death();
			}
			else if( info->byResult == 5 )
			{
				if ( info->byRemoveType == 1 )
					t->oOtherObject.HT_vOtherObject_NetworkSummons();
				else
					t->oOtherObject.HT_vOtherObject_NetworkTeleport();
			}
			else
                HT_LL_hrDeleteNode( info->nID );
			return;
		}
		t = t->next;
	}
}
//	Network GM¸ðµå¸¦ ¼³Á¤ ¶Ç´Â ÇØÁ¦¸¦ ¿äÃ»ÇÑ´Ù¸¦ ¾Ë¸°´Ù
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_GMMode_Notify( HTint iKeyID, BYTE byGMMode )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;
    
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iKeyID )
		{
			t->oOtherObject.HT_vOtherObject_NetworkGMMode_Notify( byGMMode );
			break;
		}
		t = t->next;
	}
}
//	Network LevelUp Broadcast
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->dwKeyID )
		{
			t->oOtherObject.HT_vOtherObject_NetworkLevelUpBrodcast( info  );
			return;
		}
		t = t->next;
	}
}
//	Newwork Equip
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkEquip( PS_SCP_RESP_EQUIP_SET info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			for( HTint i=0 ; i<7 ; i++ )
			{
				if( info->Equip[i].snIndex )
					info->Equip[i].snIndex += HT_ITEM_INDEX_START;
			}

			//	¾ÆÀÌÅÛ ÀåÂø ^^;
			//	¸Ó¸® ÀåÂø
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Helmet, info->Equip[0] );
			//	¸ö ÀåÂø(»óÀÇ)
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Armor, info->Equip[1] );
			//	¸ö ÀåÂø(ÇÏÀÇ)
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Pants, info->Equip[2] );
			//	¿Þ¼Õ ÀåÂø
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Shield, info->Equip[3] );
			//	¿À¸¥¼Õ ÀåÂø
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_OneHandWeapon, info->Equip[4] );
			//	¹ß ÀåÂø
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Boots, info->Equip[5] );
			//	Àå°© ÀåÂø
			t->oOtherObject.HT_vOtherObject_SetItemType( eTNEqu_Gloves, info->Equip[6] );
			return;
		}
		t = t->next;
	}
}
//	Newwork Setting ¾ÆÀÌÅÛ ¼Ò¸ð·Î »ç¶óÁü
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NewworkItemAbrasion(PS_SCP_ITEM_ABRASION_BROADCAST info)
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	//CHTString str; //µð¹ö±ë¿ë
	//-----0x01:¸Ó¸®,0x02:±Í°ÉÀÌ,0x03:¸ñ°ÉÀÌ,0x04:¸ö,0x05:º§Æ®,0x06:¾ç¼Õ,0x07:¿À¸¥¼Õ
	//-----0x08:¿Þ¼Õ,0x09:¿À¸¥¼Õ or ¿Þ¼Õ,0x0a:¿À¸¥¼Õ À§,0x0b:¿À¸¥¼Õ ¾Æ·¡,0x0c:¿Þ¼Õ À§,0x0d:¿Þ¼Õ ¾Æ·¡,0x0e:¹ß
	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->dwKeyID )
		{
			//str.HT_szFormat("\n¾ÆÀÌÅÛ »ç¶óÁü:KeyID(%d)-", info->dwKeyID);

			//----------¾ÆÀÌÅÛ ÀåÂø ½Ã½ºÅÛ----------//
			if( info->dwIndexWeapon == 0 )		//	¹«±â
			{
				//str += ("¹«±â »ç¶óÁü");
				g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, t->oOtherObject.m_iOther_EquipItem[0x07], 0, t->oOtherObject.m_pObjectInfo->byHead );
			}
			if( info->dwIndexBody == 0)			// °©¿Ê
			{
				//str += ("°©¿Ê »ç¶óÁü");
                g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, t->oOtherObject.m_iOther_EquipItem[0x04], 0, t->oOtherObject.m_pObjectInfo->byHead );
			}
			if( info->dwIndexShield == 0)		// ¹æÆÐ
			{
				HTint iNormalItem, iLeftItem;
				iNormalItem = t->oOtherObject.m_iOther_EquipItem[0x08], iLeftItem = 0;
				if( g_pEngineHandler->HT_bIsShortSword( iNormalItem ) )
				{	iLeftItem = iNormalItem;		iNormalItem = 0; 		}
		        g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, iNormalItem, iNormalItem, t->oOtherObject.m_pObjectInfo->byHead );
			}
			if( info->dwIndexHead == 0)			// Åõ±¸
                g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, t->oOtherObject.m_iOther_EquipItem[0x01], 0, t->oOtherObject.m_pObjectInfo->byHead );

			if( info->dwIndexFoot == 0)			// ½Å¹ß
			{
				//str += ("½Å¹ß »ç¶óÁü");
                g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, t->oOtherObject.m_iOther_EquipItem[0x0e], 0, t->oOtherObject.m_pObjectInfo->byHead );
			}
			if( info->dwIndexBelt == 0)			// º§Æ®
                g_cEquipSystem->HT_EquipSys_UnEquip( t->oOtherObject.m_iOtherModelID, t->oOtherObject.m_iOther_TribeCode, t->oOtherObject.m_iOther_EquipItem[0x05], 0, t->oOtherObject.m_pObjectInfo->byHead );

			return;
		}

		t = t->next;
	}
}
//	Newwork ChatMsg
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkChatMsg( DWORD dwKeyID, CHTString strMessage )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == dwKeyID )
		{
			//	Ã¤ÆÃ¸Þ½ÃÁö
			if( strMessage.HT_nGetSize() < 60 )
				t->oOtherObject.m_strOther_ChatgMeg = strMessage;
			else
			{
				t->oOtherObject.m_strOther_ChatgMeg.HT_hrCleanUp();
				CHTString::HT_hrStringCopy( t->oOtherObject.m_strOther_ChatgMeg, strMessage, 55 );
				t->oOtherObject.m_strOther_ChatgMeg += _T("...");		
			}
			t->oOtherObject.m_iOther_ChatMsgStartTime = GetTickCount();
            break;
		}
		t = t->next;
	}
}
//	Network Msg Action
HTRESULT HTOtherObjectSystem::HT_hrOtherObjectSystem_Network_MsgAction( MSG_Action* info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->dwKeyID )
		{
			t->oOtherObject.HT_vOtherObject_NetworkAction( info );
			return HT_OK;
		}
		t = t->next;
	}

	//----------ÀÌ´Öºê·ÎµåÄ³½ºÆ® ¹ÞÁö¸øÇßÀ»¶§ OtherChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ---------//
	this->HT_vOtherObjectSystem_NetworkRequestInitOtherMob( info->dwKeyID, info->TargetX, info->TargetY );
	return HT_FAIL;
}
//	Network UnitSkill
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkUnitSkill( PS_CSP_CAST_UNIT_SKILL pData )
{
	//	0º¸´Ù Å©¸é ¿¡·¯ ±×·¡¼­ ÀüºÎ ½ºÅµ
	if( pData->snRes > 0 )
		return;

	//	»ó´ë¹æÀÌ Á×¾ú´ÂÁö ÆÄ¾Ç
	if( pData->kTarget.snKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if( g_cMainCharacter->m_bMainChar_Live == HT_FALSE )
			return;
	}
	else
	{
		if( this->HT_bOtherObjectSystem_GetLiveFromKeyID( pData->kTarget.snKeyID ) == HT_FALSE )
			return;
	}

	//	°ø°ÝÀÚÀÇ ID
	HTint iAttackerID;
	//	±âº» °ø°Ý µ¥ÀÌÅ¸
	S_MSG_ATTACK_OTHERMOB info;
	memset( &info, 0, sizeof( S_MSG_ATTACK_OTHERMOB ) );

	info.snRes = pData->snRes;
	iAttackerID = pData->snCasterKeyID;
	info.iSkillID = pData->snSkillID;
	info.PosX = pData->snCasterX;
	info.PosY = pData->snCasterZ;
	info.TargetX = pData->snMapX;
	info.TargetZ = pData->snMapZ;
	info.iCasterHP = pData->iCasterHP;
	info.dwDurationTime = pData->dwDurationTime;
	info.snSkillLevel = pData->bySkillLevel;
	info.krgTarget[0].snKeyID = pData->kTarget.snKeyID;
	info.krgTarget[0].iDamage = pData->kTarget.iDamage;
	info.krgTarget[0].iHP = pData->kTarget.iHP;
	info.krgTarget[0].iAffection = pData->kTarget.iAffection;
	info.krgTarget[0].byRes = pData->kTarget.byRes;
	//	¿¡ÄÚ°¡ ¾Æ´Ò¶§¸¸ Àû¿ë½ÃÅ²´Ù.
	if( info.snRes != -1 )
        this->HT_vOtherObjectSystem_SetAffections( info.krgTarget[0].snKeyID, info.krgTarget[0].iAffection );

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iAttackerID )
		{
			info.vecTargetPos = this->HT_vecOtherObjectSystem_SRAtkTargetCheck( info.krgTarget[0].snKeyID );
			if( info.vecTargetPos.x != 0 )
			{
                t->oOtherObject.HT_vOtherObject_NetworkApplySkillBroadcast( info );
				//	Network Serch OtherObject From KeyID
				this->HT_vOtherObjectSystem_NetworkSerchMobFromKeyID( info.krgTarget[0].snKeyID );
			}
			return;
		}
		t = t->next;
	}

	//	Á»´õ ÁöÄÑº¸°í Ç®ÀÚ....
	//	ÀÌ´Öºê·ÎµåÄ³½ºÆ® ¹ÞÁö¸øÇßÀ»¶§ OtherChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ
	//	this->HT_vOtherObjectSystem_NetworkRequestInitOtherMob( iAttackerID, pData->snCasterX, pData->snCasterZ );
}
//	Network AreaSkill
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkAreaSkill( PS_CSP_CAST_AREA_SKILL pData )
{
	//	0º¸´Ù Å©¸é ¿¡·¯ ±×·¡¼­ ÀüºÎ ½ºÅµ
	if( pData->snRes > 0 )
		return;

	//	°ø°ÝÀÚÀÇ ID
	HTint iAttackerID;
	//	±âº» °ø°Ý µ¥ÀÌÅ¸
	S_MSG_ATTACK_OTHERMOB info;
	memset( &info, 0, sizeof( S_MSG_ATTACK_OTHERMOB ) );

	info.snRes = pData->snRes;
	iAttackerID = pData->snCasterKeyID;
	info.iSkillID = pData->snSkillID;
	info.PosX = pData->snCasterX;
	info.PosY = pData->snCasterZ;
	info.TargetX = pData->snMapX;
	info.TargetZ = pData->snMapZ;
	info.iCasterHP = pData->iCasterHP;
	info.dwDurationTime = pData->dwDurationTime;
	info.snSkillLevel = pData->bySkillLevel;
	HT_CELL_COORD crdCell;
	crdCell.x = info.TargetX;
	crdCell.y = info.TargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( info.vecTargetPos, crdCell );

    for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
	{
		info.krgTarget[i].snKeyID = pData->krgTarget[i].snKeyID;
		info.krgTarget[i].iDamage = pData->krgTarget[i].iDamage;
		info.krgTarget[i].iHP = pData->krgTarget[i].iHP;
		info.krgTarget[i].iAffection = pData->krgTarget[i].iAffection;
		info.krgTarget[i].byRes = pData->krgTarget[i].byRes;
		//	¿¡ÄÚ°¡ ¾Æ´Ò¶§¸¸ Àû¿ë½ÃÅ²´Ù.fors_debug ÉÁÉäÀàÈº¹¥?
		if( info.snRes != -1 )
		{
            this->HT_vOtherObjectSystem_SetAffections( info.krgTarget[i].snKeyID, info.krgTarget[i].iAffection );
			//	Set Effect
			if( pData->krgTarget[i].snKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			{
				//	¾îÆÑ¼Ç °ªÀÇ Ã¹¹øÂ°¸¦ ¼ÂÆÃÇØÁØ´Ù. ¿Ö³Ä¸é OtherObject °¡¼­´Â ¸ÞÀÎÄ³¸¯ÅÍ¸¸ ¼ÂÆÃÇØÁÖ±â ¶§¹®¿¡..
				info.krgTarget[0].iAffection = pData->krgTarget[i].iAffection;
				g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( pData->snSkillID, this->HT_iOtherObjectSystem_GetItemIndexofEquip( pData->snCasterKeyID, 4), this->HT_iOtherObjectSystem_GetModelID( pData->snCasterKeyID ) );
			}
			else
			{
				this->HT_vOtherObjectSystem_EffectHitAction( pData->krgTarget[i].snKeyID, pData->snSkillID, this->HT_iOtherObjectSystem_GetItemIndexofEquip( pData->snCasterKeyID, 4), this->HT_iOtherObjectSystem_GetModelID( pData->snCasterKeyID ), (HTint)pData->snCasterKeyID );
			}
		}
		else
		{
			info.krgTarget[i].snKeyID = -1;
		}
	}

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == iAttackerID )
		{
			info.vecTargetPos = this->HT_vecOtherObjectSystem_SRAtkTargetCheck( info.krgTarget[0].snKeyID );
            t->oOtherObject.HT_vOtherObject_NetworkApplySkillBroadcast( info );
			return;
		}
		t = t->next;
	}

	//	ÀÌ´Öºê·ÎµåÄ³½ºÆ® ¹ÞÁö¸øÇßÀ»¶§ OtherChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ
	this->HT_vOtherObjectSystem_NetworkRequestInitOtherMob( iAttackerID, pData->snCasterX, pData->snCasterZ );
}
//	PS_SCP_RESP_UPDATE_STATUS Setting
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->snKeyID )
		{
			t->oOtherObject.m_pObjectInfo->snKarma = info->snKarma;
			t->oOtherObject.m_pObjectInfo->nCurHP = info->iHP;
			//	HP Bar¿¡ Ç¥Çö
			if( t->oOtherObject.m_bOther_InfoSw )
			{
				g_pMainBar->HT_vSetObjectTextDraw( t->oOtherObject.m_strOther_Name.HT_szGetString() );
				g_pMainBar->HT_vSetObjectHPDraw( t->oOtherObject.m_pObjectInfo->nCurHP, t->oOtherObject.m_pObjectInfo->nMaxHP );
			}

			this->HT_vOtherObjectSystem_SetAffections( info->snKeyID, info->iAffections );
			return;
		}
		t = t->next;
	}

	//----------ÀÌ´Öºê·ÎµåÄ³½ºÆ® ¹ÞÁö¸øÇßÀ»¶§ OtherChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ---------//
	this->HT_vOtherObjectSystem_NetworkRequestInitOtherMob( info->snKeyID, 0, 0 );
}
//	Network Serch OtherObject From KeyID
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkSerchMobFromKeyID( DWORD dwKeyID )
{
	//	°ø°Ý´ë»óÀÌ ¸ÞÀÎÄ³¸¯ÅÍÀÌ¸é ½ºÅµ
	if( g_cMainCharacter->HT_iMainChar_GetKeyID() == dwKeyID )
		return;

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == dwKeyID )
			return;
		t = t->next;
	}

	//----------ÀÌ´Öºê·ÎµåÄ³½ºÆ® ¹ÞÁö¸øÇßÀ»¶§ OtherChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ---------//
	this->HT_vOtherObjectSystem_NetworkRequestInitOtherMob( dwKeyID, 0, 0 );
}
//	Network ÃÖ±âÈ­ ¿äÃ» ¹ÞÁö ¾Ê¾ÒÀ»¶§ herChar¸¦ º¸Á¤ÇØÁÖ±â À§ÇØ
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkRequestInitOtherMob( DWORD dwKeyID, short snX, short snZ )
{
	//HTPoint pPt;
	//pPt.x = snX;
	//pPt.y = snZ;
	//BYTE bResult = g_cAoi->HT_AOI_Level( pPt );
	//if( bResult == AOI_LEVEL_NONE )
	//	return;

	if( dwKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		return;

	MSG_REQMobByID* info = HT_NULL;
	info = new MSG_REQMobByID;
	info->MobID = (short)dwKeyID;

	if ( g_pNetWorkMgr )
	{
		if( SERVEROBJECT_IS_MONSTER( info->MobID ) )
            g_pNetWorkMgr->RequestInitMobByID( info );
		else if( SERVEROBJECT_IS_CHARACTER( info->MobID ) )
			g_pNetWorkMgr->RequestInitMobByID( info );
	}
	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQMobByID ID:%d", info->MobID  );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );
}

//	±³È¯ ¿äÃ» »ó´ëÀÇ Á¤º¸°¡ ¸ÂÁö ¾ÊÀ» °æ¿ì º¸Á¤ÇØÁÖ±â À§ÇØ
HTbool HTOtherObjectSystem::HT_bOtherObjectSystem_CheckOtherMobForTrade( PS_CSP_REQ_TRADE infoTrade )
{
	if( infoTrade->szCharName == NULL )
		return HT_FALSE;

	// Trade ¿äÃ»ÀÌ µé¾î¿ÔÀ» ¶§ Client Ä³¸¯ÅÍ Á¤º¸¿Í ´Ù¸¦ °æ¿ì initChar¸¦ ¿äÃ»
	CHTString szName = this->HT_strOtherObjectSystem_GetNameFromKeyID( infoTrade->OpponentID );
	if( szName.HT_iStringCompare( infoTrade->szCharName ) == 0 )
		return HT_TRUE;
	
	// ±³È¯ ¿äÃ»ÇÑ Ä³¸¯ÅÍÀÇ Á¤º¸¸¦ ´Ù½Ã ¿äÃ»
	memcpy( &m_sCharInfoForTrade, infoTrade, sizeof(S_CSP_REQ_TRADE) );

	MSG_REQMobByID* info = HT_NULL;
	info = new MSG_REQMobByID;

	info->MobID = (short)infoTrade->nID;
	if ( g_pNetWorkMgr )
	{
		if( SERVEROBJECT_IS_MONSTER( info->MobID ) )
            g_pNetWorkMgr->RequestInitMobByID( info );
		else if( SERVEROBJECT_IS_CHARACTER( info->MobID ) )
			g_pNetWorkMgr->RequestInitMobByID( info );
	}
	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_REQMobByID ID:%d", info->MobID  );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	
	HT_DELETE( info );

	return HT_FALSE;
}

//	Setting GuildNotify
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkGuildNotify( MSG_GuildNotify* info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			if( info->nMark == 0 )
			{
				memset( t->oOtherObject.m_pObjectInfo->szGuild, 0, GUILDNAME_LENGTH );
				t->oOtherObject.HT_vOtherObject_SetGuildMarkOff();
				t->oOtherObject.HT_vOtherObject_SetGuildMarkID( info->nMark );
			}
			else
			{
				strncpy( t->oOtherObject.m_pObjectInfo->szGuild, info->GuildName, GUILDNAME_LENGTH );
				t->oOtherObject.HT_vOtherObject_SetGuildMarkID( info->nMark );
				t->oOtherObject.HT_vOtherObject_SetGuildMarkOn();
			}
			break;
		}
		t = t->next;
	}
}

//	Network_ºÒ²É³îÀÌ
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetworkFireFxBroadcast( PS_SCP_FIRE_FX_BROADCAST info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->dwKeyID )
		{
			//	ºÒ²É³îÀÌ ÀÌÆåÆ®
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, info->iFX, t->oOtherObject.m_iOtherModelID, HT_FALSE );
			return;
		}
		t = t->next;
	}
}
//	°°Àº ÁÖ½ÅÀÇ NPC¸¦ Å¬¸¯ÇßÀ» ¶§ º¸³»´Â ¸Þ½ÃÁö _MSG_CONTACT_NPC
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetWorkCONTACT_NPC( DWORD dwTargetKeyID )
{
	HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
	HTvector3 vecOtherCharPos = HTvector3( 0, 0, 0 );

	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == dwTargetKeyID )
		{
			vecOtherCharPos = t->oOtherObject.m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
			break;
		}
		t = t->next;
	}

    //	°Å¸® Ã¼Å©
	HTfloat fDistance = HT_extern_fGetDisForTwoPoint( vecOtherCharPos, vecMainCharPos );
	if( fDistance > 50 )
		return;

	MSG_CONTACT_NPC* info = HT_NULL;
	info = new MSG_CONTACT_NPC;
	info->snNPCID = (HTshort)dwTargetKeyID;

	g_pNetWorkMgr->ReqestMsgContactNpc( info );

	////-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_MsgContactNPC" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Network_YutMove
HTvoid HTOtherObjectSystem::HT_vOtherObjectSystem_NetWorkYutMove( Msg_YutMove* info )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_pObjectInfo->nID == info->nID )
		{
			t->oOtherObject.HT_vOtherObject_NetworkYutMove( info );
			return;
		}
		t = t->next;
	}
}


HTvoid HTOtherObjectSystem::HT_LL_vInitList()
{
	m_sOtherObjectHead = NULL;
	m_sOtherObjectTail = NULL;

	m_sOtherObjectHead = new HT_OTHEROBJECT_NODE;
	m_sOtherObjectTail = new HT_OTHEROBJECT_NODE;

	m_sOtherObjectHead->next = m_sOtherObjectTail;
	m_sOtherObjectTail->next = m_sOtherObjectTail;
}
HTRESULT HTOtherObjectSystem::HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info )
{
	HT_OTHEROBJECT_NODE *s;

	s = NULL;
	s = new HT_OTHEROBJECT_NODE;
	ZeroMemory( &s->oOtherObject, sizeof( HTOtherObject ) );
	s->oOtherObject.HT_vOtherObject_Create( info, m_bOOSystem_ShowObject );
	s->next = m_sOtherObjectHead->next;
	m_sOtherObjectHead->next = s;

	return HT_OK;
}
HTRESULT HTOtherObjectSystem::HT_LL_hrDeleteNode( int iKeyID )
{
	HT_OTHEROBJECT_NODE *s;
	HT_OTHEROBJECT_NODE *p;

	p = m_sOtherObjectHead;
	s = p->next;
	while( s->oOtherObject.m_pObjectInfo->nID != iKeyID && s != m_sOtherObjectTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sOtherObjectTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}
HTvoid HTOtherObjectSystem::HT_LL_hrDeleteAll()
{
	HT_OTHEROBJECT_NODE *s;
	HT_OTHEROBJECT_NODE *t;
	
	t = m_sOtherObjectHead->next;
	while( t != m_sOtherObjectTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sOtherObjectHead->next = m_sOtherObjectTail;
}

HTRESULT
HTOtherObjectSystem::HT_hrGetCharacterAccount( const HTint idKey, CHTString* pszAccount )
{
	HT_OTHEROBJECT_NODE *t;
	t = m_sOtherObjectHead->next;

	while( t != m_sOtherObjectTail )
	{
		if( t->oOtherObject.m_iOtherModelID == idKey )
		{
			if ( pszAccount )
			{
				*pszAccount = t->oOtherObject.m_pObjectInfo->szAccount;
				return HT_OK;
			}
		}

		t = t->next;
	}

	return HT_FAIL;
}