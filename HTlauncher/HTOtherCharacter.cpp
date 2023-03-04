

#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTOtherCharacter.h"


HTOtherCharacter::HTOtherCharacter()
{
	m_cOtherCharMove = NULL;
	m_cOtherCharMove = new CHTOtherCharMove;

	m_bOtherChar_AniEventCanSw = HT_TRUE;
	m_iOtherChar_AttackAniCount	= 1;
	m_nOtherChar_WearItemID	= -1;
	m_nOtherChar_WeaponItemID		= -1;
	m_nOtherChar_AniResentState	= CHARACTER_ANISTATE_STD;
	m_nOtherChar_AttackType		= MAINCHAR_ATTACKTYPE_SKILL;
    m_bOtherChar_AttackSw		= HT_FALSE;
	//m_bOtherChar_HitSw			= HT_FALSE;
	m_bOtherChar_CastSw			= HT_FALSE;							//	ĳ��Ʈ ����
	m_nEffect_ActiveSkillID		= -1;
	m_dwOtherChar_GuildEmblemID = 0;
	m_bOtherChar_ActiveSkillIngSw = HT_FALSE;
	m_iOtherChar_AttackAniCount = 1;

	m_iOtherCharModelID = -1;

	//	���� ���� ����
	m_sOtherChar_AttackFactor		= HT_NULL;
    m_sOtherChar_AttackFactor		= new S_ATTACK_FACTOR;

	for( HTint i=0 ; i<14 ; i++ )
        m_dwEquipItem[i] = 0;

	//	ä�ø޽���
	m_byOtherChar_ChattingType = 0x00;
	m_strOtherChar_ChattingMessage.HT_hrCleanUp();

	m_bIsWeaponArmed	= HT_FALSE;
}

HTOtherCharacter::~HTOtherCharacter()
{
	g_pEngineHandler->HT_vDestroyCharacter( m_iOtherCharModelID );
	HT_DELETE( m_cOtherCharMove );
	HT_DELETE( m_sOtherChar_AttackFactor );
}

//-----------����----------//
HTvoid HTOtherCharacter::HT_vOtherCharCreate( PS_SCP_INIT_OTHER_MOB info )
{
	m_dwOtherCharKeyID		= info->nID;
	m_byOtherChar_Level		= info->byLevel;
	m_iOtherCharName		= info->szName;
	m_byOtherChar_FaceType	= info->byFace;
	m_byOtherChar_HairType  = info->byHead;
	m_byOtherChar_SpecialName = info->bySpecialName;

	//	�����ڵ� �������ֱ�
	HTint iTribe;
	HT_ConvertTribeS2C( info->snTribe, iTribe );
	m_byOtherChar_TribeType = iTribe;
	
	//	OtherChar ��ġ ����
	m_cOtherCharMove->HT_fSetOtherCharMovelogical_CellPos( info->snTargetX, info->snTargetZ );
	m_cOtherCharMove->HT_fSetOtherCharMovephysical_CellPos( info->snTargetX, info->snTargetZ );

	//	��ǥ ��ġ�� ����س���.-----//
	HTvector3 vecPos;
	HT_CELL_COORD crdCell;
	crdCell.x = info->snTargetX;
	crdCell.y = info->snTargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_cOtherCharMove->HT_fSetOtherCharMovePos( vecPos );
	//	�� ����
	m_iOtherCharModelID = g_pEngineHandler->HT_iCreateCharacter( m_byOtherChar_TribeType, vecPos, m_byOtherChar_HairType, m_byOtherChar_FaceType );
	//	���� ���� �ӵ� ����
	m_cOtherCharMove->HT_vOtherCharSetInitSpeed( m_byOtherChar_TribeType );

	//	���� �ִϸ��̼� ����
	m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
	g_pEngineHandler->HT_hrStartAnimation( m_iOtherCharModelID, m_byOtherChar_TribeType, HT_ANISTATE_STD, -1 );

	//	������ ���� ����
	for( HTint i=0 ; i<6 ; i++ )
	{
		if( info->Equip[i].snIndex )
            info->Equip[i].snIndex += HT_ITEM_INDEX_START;
	}
	//	�Ӹ� ����
	this->HT_vOtherChar_SetItemType( eTNEqu_Helmet, info->Equip[0] );
	//	�� ����(����)
	this->HT_vOtherChar_SetItemType( eTNEqu_Armor, info->Equip[1] );
	//	�� ����(����)
	this->HT_vOtherChar_SetItemType( eTNEqu_Armor, info->Equip[2] );
	//	�޼� ����
	this->HT_vOtherChar_SetItemType( eTNEqu_Shield, info->Equip[3] );
	//	������ ����
	this->HT_vOtherChar_SetItemType( eTNEqu_OneHandWeapon, info->Equip[4] );
	//	�� ����
	this->HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[5] );
	//	�尩 ����
	this->HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[6] );


	//	ĳ������ ���� ���¸� �ľ�, �ɱ�, ����, �ȱ�, �ٱ�
	m_bOtherCharMoveState = info->byDir & 0xf0;
	//if( m_bOtherCharMoveState == 0x00 )
	//{
	//		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SITDOWN;
	//		this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
	//}
	//else
	{
		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
	}

	//	HP����
	m_nOtherChar_MAX_HP				= info->nMaxHP;
	m_nOtherChar_Resent_HP			= info->nCurHP;
	//	���� ���÷��� ������
	this->HT_vOtherChar_SetInfoCancel();

	//	OtherChar�� �׾����� ó��
	m_nOtherChar_Death = OTHERCHAR_STATE_LIVE;
	m_dwOtherChar_DeathDelay = -1;

	//	GM ĳ���Ͱ� �ƴҶ��� ���� ����Ʈ �ѷ���
	if( m_byOtherChar_TribeType != 0x09 )
	{
		BYTE byAoi = g_cAoi->HT_AOI_Level( m_cOtherCharMove->HT_pGeOtherCharMoveGrid() );
		if( byAoi == AOI_LEVEL_1 || byAoi == AOI_LEVEL_CREATE )
		{
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherCharModelID, HT_FALSE );
		}
	}

	//	GM�� �������� üũ
	if( ( info->byGMStatus & 0x04 ) == 0x04 )
		g_pEngineHandler->HT_hrShowObject( m_iOtherCharModelID, HT_FALSE );

	//	��Ƽ������� �Ǵ�!
	//	0x01:��Ƽ����ƴ�, 0x02:��Ƽ���
	if( g_cParty->HT_bParty_JudgmentPartyMember( m_iOtherCharName ) )
        m_byOtherChar_PartyMember = 0x02;
	else
		m_byOtherChar_PartyMember = 0x01;

	//	�� ������
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iOtherCharModelID );

	//	��Ƽ�� ��ų ����
	m_dwActiveSkillIndex = info->dwActionSkill;
	m_byActiveSkillLevel = info->byActiveLevel;

	//---------����Ʈ_��Ƽ�� ����Ʈ Ʋ���ֱ�----------//
	HT_vOtherChar_ActiveSkillEffectOn();

	//-----���̵� ������ ����-----//
	m_dwOtherChar_IdlTime = GetTickCount() + ( rand()%IDLE_PC_TIME );

	//	��忡 ���ԵǾ� �ִٸ�
	m_dwOtherChar_GuildEmblemID = info->dwGuildMark;
	if( m_dwOtherChar_GuildEmblemID != 0 )
	{
		//	��� �̸� ����
		m_strOtherChar_GuildName = info->szGuild;
		//	��� ��ũ ǥ�� �ϱ�
		this->HT_vOtherChar_GuildEmblemOn();
	}

	//	�ֽ� ���� �ϱ�
	this->HT_vOtherChar_SetTrimuritiD( info->byTrimuriti );
	//	�ֽ� ��ũ ǥ�� �ϱ�
	this->HT_vOtherChar_TrimuritiMarkOn();
}

//-----------����----------//
HTvoid HTOtherCharacter::HT_vOtherCharDistroy()
{
	g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
	g_pEngineHandler->HT_vDestroyCharacter( m_iOtherCharModelID );
}

//-----------��Ʈ��----------//
HTvoid HTOtherCharacter::HT_vOtherCharControl( HTfloat fElapsedTime )
{
	//-----------�ٸ� ĳ���� ���� ��Ʈ��----------//
	this->HT_vOtherChar_MoveControl( fElapsedTime );

	//----------�ִϸ��̼� ��Ʈ��----------//
	this->HT_vOtherChar_AnimationControl();

	//-----------��Ʈ��_��ų ĳ���ýð� üũ----------//
	this->HT_vOtherCharControl_SkillCastTimeCheck();

	//----------OtherChar ���� ó�� ������----------//
	//this->HT_hrOtherChar_DeathDelay();
}

//-----------��Ʈ��_��ų ĳ���ýð� üũ----------//
HTvoid HTOtherCharacter::HT_vOtherCharControl_SkillCastTimeCheck()
{
	if( !m_bOtherChar_SkillCastTimeSw )
		return;

    HTdword dwPassTime = GetTickCount();
	if( dwPassTime >= (DWORD)(m_iOtherChar_SkillCastStartTime + m_iOtherChar_SkillCastTime) )
	{
		m_bOtherChar_SkillCastTimeSw = HT_FALSE;
		//	������ ĳ���� ����Ʈ�� �־����� ����
		g_pEngineHandler->HT_hrStopSFX( m_iOtherChar_SkillEffectID );

		//	Skill Attack Ani Start
		if( m_nOtherChar_AniResentState	!= CHARACTER_ANISTATE_SKILLATK )
		{		
			m_nOtherChar_AniResentState	= CHARACTER_ANISTATE_SKILLATK;
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, m_dwOhterChar_SkillID );
			HTint iTempFXID;
			g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_dwOhterChar_SkillID, HT_SFX_WHEN_ACTIVATE, m_iOtherCharModelID, HT_FALSE );
		}
	}
}

//	ĳ���� �ִϸ��̼� ����
HTvoid HTOtherCharacter::HT_vOtherChar_SetChangeAni( HTint loop, HTfloat fTime, DWORD dwSkillIndex )
{
	// � ���⸦ ���� �ִϸ��̼� ���� üũ
	if ( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_IDL ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SIT ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SITDOWN ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STANDUP )
	{
		if ( !m_bIsWeaponArmed )
		{
			g_pEngineHandler->HT_hrUnarmWeapon( m_iOtherCharModelID, (HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID );
			m_bIsWeaponArmed = HT_TRUE;
		}
	}
	else
	{
		//	��ų �׼��ϰ�쿡 
		if ( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		{
			//	��Ƽ�� ��ų �������̸�...
			if( m_bOtherChar_ActiveSkillIngSw )
			{
				g_pEngineHandler->HT_hrUnarmWeapon( m_iOtherCharModelID, (HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID );
				m_bIsWeaponArmed = HT_TRUE;
			}
			else
			{
				if ( m_nOtherChar_WeaponItemID > 0 && m_bIsWeaponArmed )
				{
					g_pEngineHandler->HT_hrEquipItem( m_iOtherCharModelID, (HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType, m_nOtherChar_WearItemID );
					m_bIsWeaponArmed = HT_FALSE;
				}
			}
		}
		else
		{
			if ( m_nOtherChar_WeaponItemID > 0 && m_bIsWeaponArmed )
			{
				g_pEngineHandler->HT_hrEquipItem( m_iOtherCharModelID, (HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType, m_nOtherChar_WearItemID );
				m_bIsWeaponArmed = HT_FALSE;
			}
		}
	}

	//	�̺�Ʈ �ް� ����
	m_bOtherChar_AniEventCanSw = HT_TRUE;

	//	�ִϸ��̼� ����
	switch( m_nOtherChar_AniResentState )
	{
		case CHARACTER_ANISTATE_STD :
			m_bOtherChar_ActiveSkillIngSw = HT_FALSE;
			m_bOtherChar_SkillCastTimeSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_WLK :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_RUN :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_IDL :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_SIT :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_SITDOWN :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
		case CHARACTER_ANISTATE_HIT :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
		case CHARACTER_ANISTATE_DIE :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
		case CHARACTER_ANISTATE_STANDUP :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
		case CHARACTER_ANISTATE_MAGIC_DEFENCE :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherCharModelID, (HTdword)m_byOtherChar_TribeType, (HT_ANIM_STATE)g_EtcAnmIndex[m_nOtherChar_AniResentState], 
				loop, m_byOtherChar_HairType, m_nOtherChar_WearItemID, fTime, m_nOtherChar_WeaponItemID );
			break;
		case CHARACTER_ANISTATE_NORMALATK :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			m_iOtherChar_AttackAniCount++;
			if( m_iOtherChar_AttackAniCount > 3 )
				m_iOtherChar_AttackAniCount = 1;
			g_pEngineHandler->HT_hrChangeAttackAnimation( m_iOtherCharModelID, (HTint)m_byOtherChar_TribeType, 
					m_nOtherChar_WeaponItemID, 1, m_byOtherChar_HairType, m_nOtherChar_WearItemID, m_iOtherChar_AttackAniCount, fTime );
			break;
		case CHARACTER_ANISTATE_SKILLREADY :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			if( m_bOtherChar_ActiveSkillIngSw )		//	��Ƽ�� ��ų �������̸�...
				g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_READY,
						(HTdword)m_byOtherChar_TribeType, 0, m_byOtherChar_HairType );
			else
                g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_READY, 
						(HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType );
			break;
		case CHARACTER_ANISTATE_SKILLCAST :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			if( m_bOtherChar_ActiveSkillIngSw )		//	��Ƽ�� ��ų �������̸�...
			{
				g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_CAST,
						(HTdword)m_byOtherChar_TribeType, 0, m_byOtherChar_HairType );
			}
			else
            	g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_CAST, 
						(HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType );
			break;
		case CHARACTER_ANISTATE_SKILLACTIVATE :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			if( m_bOtherChar_ActiveSkillIngSw )		//	��Ƽ�� ��ų �������̸�...
			{
                g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, 
						(HTdword)m_byOtherChar_TribeType,  0, m_byOtherChar_HairType );
			}
			else
				g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, 
						(HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType );
			break;
		case CHARACTER_ANISTATE_SKILLATK :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_ATTACK, 
					(HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType );
			break;
	}
}

//----------�ִϸ��̼� ��Ʈ��----------//
HTvoid HTOtherCharacter::HT_vOtherChar_AnimationControl()
{
	//	���� ����
	if( m_nOtherChar_Death == OTEHRCHAR_STATE_DEATHMOTION )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iOtherCharModelID );

	//	ĳ���� ������Ȳ�϶�
	if( m_bOtherChar_AttackSw == HT_TRUE )
	{
        //	ĳ���� ���� ����Ʈ���� ����
	    if( sAnmState == HT_AS_ATTACK )
		{
			//-----------��������Ʈ���� �ؾ����ϵ�----------//
			this->HT_vOtherChar_AttackPointCheck();
		}
		else if( sAnmState == HT_AS_STOP )
		{
			//	ĳ���� ������ ��ž�ִ��϶� ��ӵ����Ƿ� �������� ó��
			if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
			{
				//	Skill Cast Ani Start
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
				this->HT_vOtherChar_SetChangeAni( -1, 0.0f, m_dwOhterChar_SkillID );
				//	ĳ���� ����Ʈ ����
				g_pEngineHandler->HT_hrStartSFX( &m_iOtherChar_SkillEffectID, m_dwOhterChar_SkillID, HT_SFX_WHEN_CAST, m_iOtherCharModelID, HT_TRUE, 1 );
				//	ĳ���� ���۽ð��� ����
				m_iOtherChar_SkillCastStartTime = GetTickCount();
				m_bOtherChar_SkillCastTimeSw = HT_TRUE;
			}
		}
	}

	if( sAnmState == HT_AS_STOP )
	{
        //	OtherChar�� �׾����� ó��
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_DIE )
		{
			//	���� ����
			m_nOtherChar_Death = OTEHRCHAR_STATE_DEATHMOTION;
			m_dwOtherChar_DeathDelay = GetTickCount();
			return;
		}

		//	Skill Ready ���� ���̾��ٸ� ĳ���� �������� ����
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
		{
			//	ĳ���� üũ ����
			m_bOtherChar_SkillCastTimeSw = HT_TRUE;
			//	ĳ���� ���� �ð�
			m_iOtherChar_SkillCastStartTime = GetTickCount();
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
			return;
		}

		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SITDOWN )
		{
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SIT;
		}
		else
		{
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
		}

		//	ĳ���� �ִϸ��̼� ����
		this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );

		//-----���̵� ������ ����-----//
		m_dwOtherChar_IdlTime = GetTickCount();;
	}
}

//---------����Ʈ_����Ʈ ����Ʈ Ʋ���ֱ�----------//
HTvoid HTOtherCharacter::m_vOtherCharAttack_ImpactEffect( DWORD dwSkillIndex, HTint iItemIndex )
{
	HTint iEffectImpactID;
	if( dwSkillIndex == 0 )
	{
		g_pEngineHandler->HT_hrStartSFX( &iEffectImpactID, iItemIndex, m_iOtherCharModelID, HT_FALSE );
	}
	else
	{
		g_pEngineHandler->HT_hrStartSFX( &iEffectImpactID, dwSkillIndex, HT_SFX_WHEN_IMPACT, m_iOtherCharModelID, HT_FALSE );
	}
}

//---------����Ʈ_��Ƽ�� ����Ʈ Ʋ��----------//
HTvoid HTOtherCharacter::HT_vOtherChar_ActiveSkillEffectOn()
{
	if( m_dwActiveSkillIndex != 0 )
	{
        if( m_byOtherChar_PartyMember == 0x02 || g_cSystem->HT_bSystem_GetActiveSkillEffectSw() )
		{
			//	��ų ����
			g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, m_dwActiveSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, m_byActiveSkillLevel );
		}
		//	��ų �̵� �ӵ� ����
		m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( m_dwActiveSkillIndex, m_byActiveSkillLevel );
	}
}

//---------����Ʈ_��Ƽ�� ����Ʈ ����----------//
HTvoid HTOtherCharacter::HT_vOtherChar_ActiveSkillEffectOff()
{
	if( m_dwActiveSkillIndex != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
	}
}

//	��� ��ũ ���� �ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_SetGuildMarkID( HTint iGuildMarkID )
{
	m_dwOtherChar_GuildEmblemID = iGuildMarkID;
}

//	��� ��ũ ǥ�� �ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_GuildEmblemOn()
{
	if( g_bGuildMarkShow )
	{
		if( m_dwOtherChar_GuildEmblemID > 0 )
	        g_pEngineHandler->HT_hrAttachGuildMark( m_iOtherCharModelID, m_dwOtherChar_GuildEmblemID );
	}
}

//	��� ��ũ ǥ�� ���ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_GuildEmblemOff()
{
	if( m_dwOtherChar_GuildEmblemID > 0 )
        g_pEngineHandler->HT_hrDestroyGuildMark( m_iOtherCharModelID );
}

//	�ֽ� ���� �ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_SetTrimuritiD( BYTE byTrimuritii )
{
    m_byOtherChar_Trimuriti = byTrimuritii;
}
//	�ֽ� ��ũ ǥ�� �ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_TrimuritiMarkOn()
{
	if( g_bTrimuritiShow )
	{
		if( m_byOtherChar_Trimuriti > 0 )
		{
			switch( m_byOtherChar_Trimuriti )
			{
				case 1 :
					g_pEngineHandler->HT_hrAttachGodMark( m_iOtherCharModelID , m_byOtherChar_TribeType, HT_GODTYPE_BRAHMA, 1 );
					break;
				case 2 :
					g_pEngineHandler->HT_hrAttachGodMark( m_iOtherCharModelID , m_byOtherChar_TribeType, HT_GODTYPE_VISUNU, 1 );
					break;
				case 4 :
					g_pEngineHandler->HT_hrAttachGodMark( m_iOtherCharModelID , m_byOtherChar_TribeType, HT_GODTYPE_SIVA, 1 );
					break;
			}
		}
	}
}
//	�ֽ� ��ũ ǥ�� ���ϱ�
HTvoid HTOtherCharacter::HT_vOtherChar_TrimuritiMarkOff()
{
	g_pEngineHandler->HT_hrDetachGodMark( m_iOtherCharModelID );
}


//-----------�ٸ� ĳ���� ���� ��Ʈ��----------//
HTvoid HTOtherCharacter::HT_vOtherChar_MoveControl( HTfloat fElapsedTime )
{
	//	�̺�Ʈ �ް� ����
	if( !m_bOtherChar_AniEventCanSw || fElapsedTime < HT_EPSILON )
		return;

	if( m_nOtherChar_Death == OTEHRCHAR_STATE_DEATHMOTION )
		return;

	if( m_cOtherCharMove->m_iOtherCharMove_State == OTHERCHARMOVE_STAND || m_cOtherCharMove->HT_fGetOtherCharMoveSpeed() == 0.0f )
	{
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_WLK || 
			m_nOtherChar_AniResentState == CHARACTER_ANISTATE_RUN )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );

			g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMoveDirect() );
			g_pEngineHandler->HT_hrMoveObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMovePos() );

			//-----���̵� ������ ����-----//
			m_dwOtherChar_IdlTime = GetTickCount();
		}
		else if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD )
		{
			DWORD dwPassTime = GetTickCount();
			if( dwPassTime > m_dwOtherChar_IdlTime + IDLE_PC_TIME )
			{
				//	ĳ���� �ִϸ��̼� ����
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_IDL;
				this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
			}
		}
		return;
	}
	else if( m_cOtherCharMove->m_iOtherCharMove_State == OTHERCHARMOVE_GO )
	{
		m_cOtherCharMove->HT_vOtherCharMoveGo( fElapsedTime );
		m_cOtherCharMove->HT_vOtherCharMovephysicalCellMoveCheck();
		m_cOtherCharMove->HT_vOtherCharMoveStopCheck();

		g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMoveDirect() );
		g_pEngineHandler->HT_hrMoveObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMovePos() );
	}
}

//-----------�������� �Ǻ��Ͽ� �������ش�----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info )
{
	if( info.snIndex != 0 )
	{
		//	�������ش�.
		g_cEquipSystem->HT_EquipSys_Equip( m_iOtherCharModelID, m_byOtherChar_TribeType, 0, info.snIndex, m_byOtherChar_HairType, 0 );
		//	���� ������ �����ϰ�
		m_dwEquipItem[byPart] = info.snIndex;

		if ( HT_IS_ITEM_WEAR( info.snIndex ) )
		{
			m_nOtherChar_WearItemID	= info.snIndex;
		}
		else if ( HT_IS_ITEM_WEAPON( info.snIndex ) )
		{
			m_nOtherChar_WeaponItemID = info.snIndex;
		}

		//	���� ��Ʈ�� ������ ���� ȿ���� ���δ�.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			//	���� ������ �Ǿ� �ִ� (����) �������� FX ����
			if( info.byRefineLevel > 0 )
				g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherCharModelID, info.snIndex, info.byRefineLevel );
			
			// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
			if( info.byRefineLevel > 0 )
			{
				// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
				g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherCharModelID, info.snIndex, (HTESubRefineType)info.byMainRef, info.byRefineLevel );
			}
		}
	}
	else
	{
		//	Ż�� ���ش�.
		g_cEquipSystem->HT_EquipSys_UnEquip( m_iOtherCharModelID, m_byOtherChar_TribeType, m_dwEquipItem[byPart], m_byOtherChar_HairType );
		//	Ż�� ������ �����ϰ�
		m_dwEquipItem[byPart] = 0;

		if( byPart == eTNEqu_OneHandWeapon || byPart == eTNEqu_TwoHandWeapon )
			m_nOtherChar_WeaponItemID = -1;
		else if( byPart == eTNEqu_Armor )
			m_nOtherChar_WearItemID	= -1;

		//	Ż�� ��Ʈ�� ������ ���� ȿ���� ���δ�.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			// ���õ� �������� FX ���ֱ�
			// ���� ����
			g_pEngineHandler->HT_hrDetachItemMainRefineEffect( m_iOtherCharModelID, info.snIndex );
			// �Ӽ� ����
			g_pEngineHandler->HT_hrDetachItemSubRefineEffect( m_iOtherCharModelID, info.snIndex );
		}
	}

	if ( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SIT ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_RUN ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_WLK )
	{
		//	ĳ���� �ִϸ��̼� ����
		this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
	}

	//	�������ڸ� �����ߴ��� �м�
	if( m_dwEquipItem[1] == ITEMINDEX_ASSISTANTHAT )
		m_bAssistantSw = HT_TRUE;
	else
		m_bAssistantSw = HT_FALSE;
}

//---------���� ���÷��� ����----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetInfoDisplay()
{
	m_bOtherChar_Info_Sw = HT_TRUE;
}

//---------���� ���÷��� �������----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetInfoCancel()
{
	m_bOtherChar_Info_Sw = HT_FALSE;
}

//-----------�ȵ� �����ΰ� üũ----------//
HTRESULT HTOtherCharacter::HT_hrOtherChar_GetInfoStatus()
{
	return HT_OK;
}

//	��ü ���� ����
//----------���ݴ��� ������ üũ�ؿ�----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetAttack( DWORD dwSkillIndex, BYTE byAttackType, HTint iItemIndex )
{
	//	����Ʈ_����Ʈ ����Ʈ Ʋ���ֱ�
	this->m_vOtherCharAttack_ImpactEffect( dwSkillIndex, iItemIndex );

	//	���� �� ����Ʈ�� �ƴϸ� �ø�Ŀ
	if( byAttackType != MAINCHAR_ATTACKTYPE_PRANA )
		g_pEngineHandler->HT_hrFlickerObject( m_iOtherCharModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	������
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iOtherCharModelID, HT_FALSE );

	//	HIT �ִϸ��̼� Ʋ���ֱ�
	if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD || m_nOtherChar_AniResentState == CHARACTER_ANISTATE_IDL )
	{
		m_bOtherChar_HitSw = HT_TRUE;
		//	ĳ���� �ִϸ��̼� ����
		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_HIT;
		this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
	}
}

//-----------��������Ʈ���� �ؾ����ϵ�----------//
HTvoid HTOtherCharacter::HT_vOtherChar_AttackPointCheck()
{
	//-----����Ŭ���� ����-----//
	m_sOtherChar_AttackFactor->strAttackName = m_iOtherCharName;
	m_sOtherChar_AttackFactor->byAttacker = 0x01;
	m_sOtherChar_AttackFactor->byTargetType = m_byOtherChar_AttackTarget;
	m_sOtherChar_AttackFactor->byTribe = m_byOtherChar_TribeType;
	m_sOtherChar_AttackFactor->dwAttackKeyID = m_dwOtherCharKeyID;
	m_sOtherChar_AttackFactor->dwTargetKeyID = m_dwOtherChar_TargetKeyID;
	m_sOtherChar_AttackFactor->nAttackType = m_nOtherChar_AttackType;
	m_sOtherChar_AttackFactor->nCharModelID = m_iOtherCharModelID;
	m_sOtherChar_AttackFactor->vecSourcePos = m_cOtherCharMove->HT_fGetOtherCharMovePos();
	m_sOtherChar_AttackFactor->vecTargetPos = m_vecAttack_TargetPos;
	m_sOtherChar_AttackFactor->fDirect = m_cOtherCharMove->HT_fOtherCharMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), 
	m_sOtherChar_AttackFactor->vecTargetPos-m_sOtherChar_AttackFactor->vecSourcePos ) + HT_PIX2;
	m_sOtherChar_AttackFactor->nAttackItemID = m_nOtherChar_WeaponItemID;
	m_sOtherChar_AttackFactor->nAttackSkillID = m_dwOhterChar_SkillID;
	m_sOtherChar_AttackFactor->byAttackSkillIDLevel = 1;
	g_cAttackMgr->HT_vAttackMgr_Create( m_sOtherChar_AttackFactor );
	m_bOtherChar_AttackSw = HT_FALSE;
}

//-----------������ ���� ȸ��-----------//
HTvoid HTOtherCharacter::HT_vOtherChar_RotateAttack( HTvector3 vecTargetPos )
{
	HTvector3 vecMyPos = m_cOtherCharMove->HT_fGetOtherCharMovePos();

	HTvector3 vecPos = vecTargetPos - vecMyPos;
	HTfloat fDirect = m_cOtherCharMove->HT_fOtherCharMoveGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	if( fDirect < 0.0f || fDirect > HT_PI*4 )
		return;

	m_cOtherCharMove->HT_vSetOtherCharMoveDirect( fDirect );
	g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, fDirect );
}

//	�������� ��ġ ����
HTvoid HTOtherCharacter::HT_vOtherChar_AttackPosCheck( HTint nX, HTint nZ )
{
	HTPoint pPt;
	m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
	if( pPt.x != nX || pPt.y != nZ )
	{
		m_cOtherCharMove->HT_fSetOtherCharMovelogical_CellPos( nX, nZ );
		m_cOtherCharMove->HT_fSetOtherCharMovephysical_CellPos( nX, nZ );

        HTvector3 vecTemp = m_cOtherCharMove->HT_fGetOtherCharMovePos();
		g_pEngineHandler->HT_hrMoveObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMovePos() );
	}

	//	���߱�
	m_cOtherCharMove->HT_vOtherCharMoveStop();
}

//-----------��ų ����----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info )
{
	m_dwActiveSkillIndex = info->dwIndex;
	m_bOtherChar_ActiveSkillIngSw = HT_TRUE;
	if( info->byLevel <= 0 || info->byLevel > 10 )
		m_byActiveSkillLevel = 1;
	else
        m_byActiveSkillLevel = info->byLevel;

	if( m_nEffect_ActiveSkillID != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
		m_nEffect_ActiveSkillID = -1;
	}

	if( info->bySelect == 0x01 )			//	��ų ����
	{
		//	��ų �ߵ�
		HTint nEffectID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectID, info->dwIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherCharModelID, HT_FALSE, info->byLevel );

		if( m_byOtherChar_PartyMember == 0x02 || g_bDevelopingMode == HT_TRUE )
		{
			if( info->byHand == 0x02 )			//	���� ��ų, ��Ƽ�� ��ų
			{
				//	��ų ����
				g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, info->dwIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, info->byLevel );
				//	ĳ���� �ִϸ��̼� ����
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
				this->HT_vOtherChar_SetChangeAni( 1, 0.0f, m_dwActiveSkillIndex );
				//	��ų �̵� �ӵ� ����
				m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( info->dwIndex, info->byLevel );
			}
		}
	}
	else if( info->bySelect == 0x02 )		//	��ų ����
	{
		if( info->byHand == 0x02 )			//	���� ��ų, ��Ƽ�� ��ų
		{
			g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
			m_nEffect_ActiveSkillID = -1;
			//	��ų �̵� �ӵ� ����
			m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( 0, 0 );
		}
	}
}

//	��Ƽ�� ��ų ����� �޾��� �� Effect Ʋ��
HTvoid HTOtherCharacter::HT_vOtherChar_SetActiveSkillEffectOn( DWORD dwSkillIndex, HTbool bType, BYTE byLevel )
{
	g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, dwSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, bType, byLevel );
}

//-----------��Ƽ�����μ� ���� �� Ż���Ҷ�----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetPartyJoineDisband( BYTE byParty )
{
	m_byOtherChar_PartyMember = byParty;
	if( m_byOtherChar_PartyMember == 0x01 )			//	Ż��
	{
		g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
		m_nEffect_ActiveSkillID = -1;
	}
	else if( m_byOtherChar_PartyMember == 0x02 )
	{
		//	��ų ����
        g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, m_dwActiveSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, m_byActiveSkillLevel );
	}
}

//---------HP ������� üũ----------//
HTint HTOtherCharacter::HT_nOtherChar_SetHPCheck( HTint nHP )
{
	if( nHP < 0 || nHP > m_nOtherChar_Resent_HP || nHP == ATTACK_DAMAGEERRORVALUE )
	{
		m_nOtherChar_HitCount = 0;
	}
	else
	{
		m_nOtherChar_HitCount = m_nOtherChar_Resent_HP - nHP;
		m_nOtherChar_Resent_HP = nHP;

		//	�ý���â�� �޽��� �ѷ��ֱ�.
		char chName[SZNAME_LENGTH];
		CHTString::HT_hrStringCopy( chName, m_iOtherCharName, SZNAME_LENGTH);
		CHTString strMessage;
		strMessage.HT_szFormat( "%s���� ������ %d��(��) �־����ϴ�.", chName, m_nOtherChar_Resent_HP );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ATTACK, strMessage );
	}

	return m_nOtherChar_HitCount;
}


//------------------------------------------------//
//----------������ ����ϴ� ��Ʈ��ũ �Լ�---------//
//------------------------------------------------//
//	Other Character LevelUp �� �˸�
HTvoid HTOtherCharacter::HT_vOtherChar_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CHAKRAUPGRADE, m_iOtherCharModelID, HT_FALSE );
}

//---------- GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���-------------//
HTvoid HTOtherCharacter::HT_vNetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY info )
{
	if( info->byMode == 0x01 )
	{
		g_pEngineHandler->HT_hrShowObject( m_iOtherCharModelID, HT_FALSE );
	}
	else
	{
		g_pEngineHandler->HT_hrShowObject( m_iOtherCharModelID, HT_TRUE );
	}
}

//	������ �ٸ�ĳ������ �̵��� �˷����� ��
HTvoid HTOtherCharacter::HT_vNetWork_OtherChar_Action( MSG_Action* info )
{
	m_bOtherChar_AttackSw = HT_FALSE;
	m_bOtherCharMoveState = info->Effect;

	if( m_bOtherCharMoveState == 0 )
	{
		//	���� ��ġ�� ��ǥ ��ġ�� �� ��ǥ��ġ�� ������������ �̵�
		HTPoint pPt;
		m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SITDOWN;
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
		}
		else
		{
			m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
		}
	}
	else if( m_bOtherCharMoveState == 1 )
	{
		//	���� ��ġ�� ��ǥ ��ġ�� �� ��ǥ��ġ�� ������������ �̵�
		HTPoint pPt;
		m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	ĳ������ �ɾ��ְų� �ɱ� �����Ҷ��� ���� ���� Ʋ���ش�.
			if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SIT || m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SITDOWN )
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STANDUP;
			else
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;

			//	ĳ���� �ִϸ��̼� ����
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );

			//-----���̵� ������ ����-----//
			m_dwOtherChar_IdlTime = GetTickCount();
		}
		else
		{
			m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
		}

		//	OtherChar ����
        g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, (HTfloat)info->Direction/100 );
	}
	else if( m_bOtherCharMoveState == 2 )
	{
		if( m_nOtherChar_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_WLK;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
		}
		m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
	}
	else if( m_bOtherCharMoveState == 3 )
	{
		if( m_nOtherChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
		}
		m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
	}

	//----------ĳ��Ʈ ��ų ���---------//
	if( m_bOtherChar_CastSw == HT_TRUE )
	{
		//	ĳ��Ʈ ����
		m_bOtherChar_CastSw = HT_FALSE;
		//	����Ʈ�� ���� ��Ű��
		g_pEngineHandler->HT_hrStopSFX( m_iOtherChar_CastEffectID );
		m_iOtherChar_CastEffectID = 0;
	}
}

//----------ĳ��Ʈ ��ų ���� �غ�---------//
HTvoid HTOtherCharacter::HT_vOtherChar_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info )
{
	//	ĳ��Ʈ ����
	m_bOtherChar_CastSw = HT_TRUE;
	//	����Ʈ ����
	g_pEngineHandler->HT_hrStartSFX( &m_iOtherChar_CastEffectID, info->dwIndex, HT_SFX_WHEN_CAST, m_iOtherCharModelID, HT_TRUE );
}

//	��ų ĳ������ �˸�
HTvoid HTOtherCharacter::HT_vOtherChar_Network_Skill_Cast_Broadcast( S_MSG_ATTACK_OTHERMOB info )
{
	//	ĳ���� �״� �׼��� ������ � �׼ǵ� Ʋ�� ����
	if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_DIE )
		return;

	//	Combat ����
	m_bOtherChar_AttackSw = HT_TRUE;
	//	���ݹ��� ����� KeyID
	m_dwOtherChar_TargetKeyID = info.krgTarget[0].snKeyID;
	//	��ų ���� ����_ID, Level
	m_dwOhterChar_SkillID = info.iSkillID;
	m_dwOhterChar_SkillLevel;//
	//	Ŀ��Ƽ�� �� ���� ����
	m_byOtherCharCriticalHit = info.snRes;
	//	���ݴ������� �� ���̵�
	m_nAttack_TargetModelID = info.iTargetModelID;
	//	1:OtherCharecter, 2:Monster, 3:MainCharacter
	m_byOtherChar_AttackTarget	= info.byTargetType;
	//	Target�� ��ǥ
	m_vecAttack_TargetPos = info.vecTargetPos;
	// �����ڸ� ���� ȸ��
	this->HT_vOtherChar_RotateAttack( m_vecAttack_TargetPos );
	//	�������� ��ġ ����
	this->HT_vOtherChar_AttackPosCheck( info.PosX, info.PosY );
	//	���� Type ����
	m_nOtherChar_AttackType		= MAINCHAR_ATTACKTYPE_SKILL;

	//	�׼� 0�ʿ��� �Դ���?
	if( info.snRes == -1 )
	{
		if( m_dwOhterChar_SkillID != 0 )
		{
			m_dwOtherChar_SkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_dwOhterChar_SkillID );
			//	�׼� ��ų ĳ���� �ӵ�
			if( !g_pParamMgr->HT_bGetPCSkillCastingTime( m_dwOhterChar_SkillID, 1, &m_iOtherChar_SkillCastTime ) )
				m_iOtherChar_SkillCastTime = 0;
			//	Skill Ready Ani Start
			//	ĳ���� �ִϸ��̼� ����
			if( m_dwOtherChar_SkillType == HT_PCSKILLTYPE_ACTION )
			{
                m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
				this->HT_vOtherChar_SetChangeAni( 1, 0.0f, m_dwOhterChar_SkillID );
			}
			HTint iTempFXID;
			g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_dwOhterChar_SkillID, HT_SFX_WHEN_READY, m_iOtherCharModelID, HT_FALSE );
		}
		else
		{
			//	ĳ���� �ִϸ��̼� ����
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_NORMALATK;
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
		}
	}
	else
	{
		//	Set HitCount
		m_snOtherChar_Demage = info.krgTarget[0].snDamage;

		if( m_dwOhterChar_SkillID != 0 && m_nOtherChar_AniResentState != CHARACTER_ANISTATE_SKILLATK )
		{
			//	Skill Attack Ani Start
			m_nOtherChar_AniResentState	= CHARACTER_ANISTATE_SKILLATK;
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, m_dwOhterChar_SkillID );
			HTint iTempFXID;
			g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_dwOhterChar_SkillID, HT_SFX_WHEN_ACTIVATE, m_iOtherCharModelID, HT_FALSE );
		}
	}
}

//	OtherChar ���� ó��
HTvoid HTOtherCharacter::HT_hrOtherChar_Death()
{
	if( m_nOtherChar_Death == OTHERCHAR_STATE_LIVE )
	{
		m_nOtherChar_Death = OTEHRCHAR_STATE_DEATHMOTION;
		m_dwOtherChar_DeathDelay = GetTickCount();
		//	ĳ���� �ִϸ��̼� ����
		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_DIE;
		this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
	}
}

//	OtherChar ���� ó�� ������
HTvoid HTOtherCharacter::HT_hrOtherChar_DeathDelay()
{
	if( m_nOtherChar_Death == OTEHRCHAR_STATE_DEATHMOTION )
	{
		DWORD dwPassTime = GetTickCount();
		if( dwPassTime > m_dwOtherChar_DeathDelay + (IDLE_PC_TIME/2) )
		{
			m_nOtherChar_Death = OTHERCHAR_STATE_DEATH;
		}
	}
}

