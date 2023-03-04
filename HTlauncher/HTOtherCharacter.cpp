

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
	m_bOtherChar_CastSw			= HT_FALSE;							//	캐스트 유무
	m_nEffect_ActiveSkillID		= -1;
	m_dwOtherChar_GuildEmblemID = 0;
	m_bOtherChar_ActiveSkillIngSw = HT_FALSE;
	m_iOtherChar_AttackAniCount = 1;

	m_iOtherCharModelID = -1;

	//	공격 인자 생성
	m_sOtherChar_AttackFactor		= HT_NULL;
    m_sOtherChar_AttackFactor		= new S_ATTACK_FACTOR;

	for( HTint i=0 ; i<14 ; i++ )
        m_dwEquipItem[i] = 0;

	//	채팅메시지
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

//-----------생성----------//
HTvoid HTOtherCharacter::HT_vOtherCharCreate( PS_SCP_INIT_OTHER_MOB info )
{
	m_dwOtherCharKeyID		= info->nID;
	m_byOtherChar_Level		= info->byLevel;
	m_iOtherCharName		= info->szName;
	m_byOtherChar_FaceType	= info->byFace;
	m_byOtherChar_HairType  = info->byHead;
	m_byOtherChar_SpecialName = info->bySpecialName;

	//	종족코드 보정해주기
	HTint iTribe;
	HT_ConvertTribeS2C( info->snTribe, iTribe );
	m_byOtherChar_TribeType = iTribe;
	
	//	OtherChar 위치 셋팅
	m_cOtherCharMove->HT_fSetOtherCharMovelogical_CellPos( info->snTargetX, info->snTargetZ );
	m_cOtherCharMove->HT_fSetOtherCharMovephysical_CellPos( info->snTargetX, info->snTargetZ );

	//	좌표 위치를 계산해낸다.-----//
	HTvector3 vecPos;
	HT_CELL_COORD crdCell;
	crdCell.x = info->snTargetX;
	crdCell.y = info->snTargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_cOtherCharMove->HT_fSetOtherCharMovePos( vecPos );
	//	모델 생성
	m_iOtherCharModelID = g_pEngineHandler->HT_iCreateCharacter( m_byOtherChar_TribeType, vecPos, m_byOtherChar_HairType, m_byOtherChar_FaceType );
	//	최초 종족 속도 셋팅
	m_cOtherCharMove->HT_vOtherCharSetInitSpeed( m_byOtherChar_TribeType );

	//	최초 애니매이션 셋팅
	m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
	g_pEngineHandler->HT_hrStartAnimation( m_iOtherCharModelID, m_byOtherChar_TribeType, HT_ANISTATE_STD, -1 );

	//	아이템 장착 셋팅
	for( HTint i=0 ; i<6 ; i++ )
	{
		if( info->Equip[i].snIndex )
            info->Equip[i].snIndex += HT_ITEM_INDEX_START;
	}
	//	머리 장착
	this->HT_vOtherChar_SetItemType( eTNEqu_Helmet, info->Equip[0] );
	//	몸 장착(상의)
	this->HT_vOtherChar_SetItemType( eTNEqu_Armor, info->Equip[1] );
	//	몸 장착(하의)
	this->HT_vOtherChar_SetItemType( eTNEqu_Armor, info->Equip[2] );
	//	왼손 장착
	this->HT_vOtherChar_SetItemType( eTNEqu_Shield, info->Equip[3] );
	//	오른손 장착
	this->HT_vOtherChar_SetItemType( eTNEqu_OneHandWeapon, info->Equip[4] );
	//	발 장착
	this->HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[5] );
	//	장갑 장착
	this->HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[6] );


	//	캐릭터의 현재 상태를 파악, 앉기, 서기, 걷기, 뛰기
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

	//	HP관련
	m_nOtherChar_MAX_HP				= info->nMaxHP;
	m_nOtherChar_Resent_HP			= info->nCurHP;
	//	정보 디스플레이 셋팅취
	this->HT_vOtherChar_SetInfoCancel();

	//	OtherChar가 죽었을때 처리
	m_nOtherChar_Death = OTHERCHAR_STATE_LIVE;
	m_dwOtherChar_DeathDelay = -1;

	//	GM 캐릭터가 아닐때만 생성 이펙트 뿌려줌
	if( m_byOtherChar_TribeType != 0x09 )
	{
		BYTE byAoi = g_cAoi->HT_AOI_Level( m_cOtherCharMove->HT_pGeOtherCharMoveGrid() );
		if( byAoi == AOI_LEVEL_1 || byAoi == AOI_LEVEL_CREATE )
		{
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherCharModelID, HT_FALSE );
		}
	}

	//	GM이 투명인지 체크
	if( ( info->byGMStatus & 0x04 ) == 0x04 )
		g_pEngineHandler->HT_hrShowObject( m_iOtherCharModelID, HT_FALSE );

	//	파티멤버임을 판단!
	//	0x01:파티멤버아님, 0x02:파티멤버
	if( g_cParty->HT_bParty_JudgmentPartyMember( m_iOtherCharName ) )
        m_byOtherChar_PartyMember = 0x02;
	else
		m_byOtherChar_PartyMember = 0x01;

	//	모델 사이즈
	m_fModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iOtherCharModelID );

	//	액티브 스킬 셋팅
	m_dwActiveSkillIndex = info->dwActionSkill;
	m_byActiveSkillLevel = info->byActiveLevel;

	//---------이펙트_액티브 이펙트 틀어주기----------//
	HT_vOtherChar_ActiveSkillEffectOn();

	//-----아이들 동작을 위해-----//
	m_dwOtherChar_IdlTime = GetTickCount() + ( rand()%IDLE_PC_TIME );

	//	길드에 가입되어 있다면
	m_dwOtherChar_GuildEmblemID = info->dwGuildMark;
	if( m_dwOtherChar_GuildEmblemID != 0 )
	{
		//	길드 이름 저장
		m_strOtherChar_GuildName = info->szGuild;
		//	길드 마크 표현 하기
		this->HT_vOtherChar_GuildEmblemOn();
	}

	//	주신 셋팅 하기
	this->HT_vOtherChar_SetTrimuritiD( info->byTrimuriti );
	//	주신 마크 표현 하기
	this->HT_vOtherChar_TrimuritiMarkOn();
}

//-----------삭제----------//
HTvoid HTOtherCharacter::HT_vOtherCharDistroy()
{
	g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
	g_pEngineHandler->HT_vDestroyCharacter( m_iOtherCharModelID );
}

//-----------컨트롤----------//
HTvoid HTOtherCharacter::HT_vOtherCharControl( HTfloat fElapsedTime )
{
	//-----------다른 캐릭터 무빙 컨트롤----------//
	this->HT_vOtherChar_MoveControl( fElapsedTime );

	//----------애니매이션 컨트롤----------//
	this->HT_vOtherChar_AnimationControl();

	//-----------컨트롤_스킬 캐스팅시간 체크----------//
	this->HT_vOtherCharControl_SkillCastTimeCheck();

	//----------OtherChar 죽음 처리 딜레이----------//
	//this->HT_hrOtherChar_DeathDelay();
}

//-----------컨트롤_스킬 캐스팅시간 체크----------//
HTvoid HTOtherCharacter::HT_vOtherCharControl_SkillCastTimeCheck()
{
	if( !m_bOtherChar_SkillCastTimeSw )
		return;

    HTdword dwPassTime = GetTickCount();
	if( dwPassTime >= (DWORD)(m_iOtherChar_SkillCastStartTime + m_iOtherChar_SkillCastTime) )
	{
		m_bOtherChar_SkillCastTimeSw = HT_FALSE;
		//	기존에 캐스팅 이펙트가 있었으면 정지
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

//	캐릭터 애니매이션 셋팅
HTvoid HTOtherCharacter::HT_vOtherChar_SetChangeAni( HTint loop, HTfloat fTime, DWORD dwSkillIndex )
{
	// 등에 무기를 차고 애니매이션 할지 체크
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
		//	스킬 액션일경우에 
		if ( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLCAST ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE ||
			 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		{
			//	액티브 스킬 시전중이면...
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

	//	이벤트 받게 셋팅
	m_bOtherChar_AniEventCanSw = HT_TRUE;

	//	애니매이션 셋팅
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
			if( m_bOtherChar_ActiveSkillIngSw )		//	액티브 스킬 지전중이면...
				g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_READY,
						(HTdword)m_byOtherChar_TribeType, 0, m_byOtherChar_HairType );
			else
                g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherCharModelID, dwSkillIndex, HT_SKILLANISEQ_READY, 
						(HTint)m_byOtherChar_TribeType, m_nOtherChar_WeaponItemID, m_byOtherChar_HairType );
			break;
		case CHARACTER_ANISTATE_SKILLCAST :
			m_bOtherChar_AniEventCanSw = HT_FALSE;
			if( m_bOtherChar_ActiveSkillIngSw )		//	액티브 스킬 지전중이면...
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
			if( m_bOtherChar_ActiveSkillIngSw )		//	액티브 스킬 지전중이면...
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

//----------애니매이션 컨트롤----------//
HTvoid HTOtherCharacter::HT_vOtherChar_AnimationControl()
{
	//	죽음 셋팅
	if( m_nOtherChar_Death == OTEHRCHAR_STATE_DEATHMOTION )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iOtherCharModelID );

	//	캐릭터 전투상황일때
	if( m_bOtherChar_AttackSw == HT_TRUE )
	{
        //	캐릭터 공격 포인트에서 할일
	    if( sAnmState == HT_AS_ATTACK )
		{
			//-----------공격포인트에서 해야할일들----------//
			this->HT_vOtherChar_AttackPointCheck();
		}
		else if( sAnmState == HT_AS_STOP )
		{
			//	캐스팅 동작이 스탑애니일때 계속들어오므로 못들어오게 처리
			if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
			{
				//	Skill Cast Ani Start
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
				this->HT_vOtherChar_SetChangeAni( -1, 0.0f, m_dwOhterChar_SkillID );
				//	캐스팅 이펙트 시작
				g_pEngineHandler->HT_hrStartSFX( &m_iOtherChar_SkillEffectID, m_dwOhterChar_SkillID, HT_SFX_WHEN_CAST, m_iOtherCharModelID, HT_TRUE, 1 );
				//	캐스팅 시작시간을 설정
				m_iOtherChar_SkillCastStartTime = GetTickCount();
				m_bOtherChar_SkillCastTimeSw = HT_TRUE;
			}
		}
	}

	if( sAnmState == HT_AS_STOP )
	{
        //	OtherChar가 죽었을때 처리
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_DIE )
		{
			//	죽음 셋팅
			m_nOtherChar_Death = OTEHRCHAR_STATE_DEATHMOTION;
			m_dwOtherChar_DeathDelay = GetTickCount();
			return;
		}

		//	Skill Ready 동작 중이었다면 캐스팅 동작으로 연결
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
		{
			//	캐스팅 체크 설정
			m_bOtherChar_SkillCastTimeSw = HT_TRUE;
			//	캐스팅 시작 시간
			m_iOtherChar_SkillCastStartTime = GetTickCount();
			//	캐릭터 애니매이션 셋팅
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

		//	캐릭터 애니매이션 셋팅
		this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );

		//-----아이들 동작을 위해-----//
		m_dwOtherChar_IdlTime = GetTickCount();;
	}
}

//---------이펙트_임팩트 이펙트 틀어주기----------//
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

//---------이펙트_액티브 이펙트 틀기----------//
HTvoid HTOtherCharacter::HT_vOtherChar_ActiveSkillEffectOn()
{
	if( m_dwActiveSkillIndex != 0 )
	{
        if( m_byOtherChar_PartyMember == 0x02 || g_cSystem->HT_bSystem_GetActiveSkillEffectSw() )
		{
			//	스킬 지속
			g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, m_dwActiveSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, m_byActiveSkillLevel );
		}
		//	스킬 이동 속도 적용
		m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( m_dwActiveSkillIndex, m_byActiveSkillLevel );
	}
}

//---------이펙트_액티브 이펙트 꺼기----------//
HTvoid HTOtherCharacter::HT_vOtherChar_ActiveSkillEffectOff()
{
	if( m_dwActiveSkillIndex != 0 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
	}
}

//	길드 마크 셋팅 하기
HTvoid HTOtherCharacter::HT_vOtherChar_SetGuildMarkID( HTint iGuildMarkID )
{
	m_dwOtherChar_GuildEmblemID = iGuildMarkID;
}

//	길드 마크 표현 하기
HTvoid HTOtherCharacter::HT_vOtherChar_GuildEmblemOn()
{
	if( g_bGuildMarkShow )
	{
		if( m_dwOtherChar_GuildEmblemID > 0 )
	        g_pEngineHandler->HT_hrAttachGuildMark( m_iOtherCharModelID, m_dwOtherChar_GuildEmblemID );
	}
}

//	길드 마크 표현 안하기
HTvoid HTOtherCharacter::HT_vOtherChar_GuildEmblemOff()
{
	if( m_dwOtherChar_GuildEmblemID > 0 )
        g_pEngineHandler->HT_hrDestroyGuildMark( m_iOtherCharModelID );
}

//	주신 셋팅 하기
HTvoid HTOtherCharacter::HT_vOtherChar_SetTrimuritiD( BYTE byTrimuritii )
{
    m_byOtherChar_Trimuriti = byTrimuritii;
}
//	주신 마크 표현 하기
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
//	주신 마크 표현 안하기
HTvoid HTOtherCharacter::HT_vOtherChar_TrimuritiMarkOff()
{
	g_pEngineHandler->HT_hrDetachGodMark( m_iOtherCharModelID );
}


//-----------다른 캐릭터 무빙 컨트롤----------//
HTvoid HTOtherCharacter::HT_vOtherChar_MoveControl( HTfloat fElapsedTime )
{
	//	이벤트 받게 셋팅
	if( !m_bOtherChar_AniEventCanSw || fElapsedTime < HT_EPSILON )
		return;

	if( m_nOtherChar_Death == OTEHRCHAR_STATE_DEATHMOTION )
		return;

	if( m_cOtherCharMove->m_iOtherCharMove_State == OTHERCHARMOVE_STAND || m_cOtherCharMove->HT_fGetOtherCharMoveSpeed() == 0.0f )
	{
		if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_WLK || 
			m_nOtherChar_AniResentState == CHARACTER_ANISTATE_RUN )
		{
			//	캐릭터 애니매이션 셋팅
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );

			g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMoveDirect() );
			g_pEngineHandler->HT_hrMoveObject( m_iOtherCharModelID, m_cOtherCharMove->HT_fGetOtherCharMovePos() );

			//-----아이들 동작을 위해-----//
			m_dwOtherChar_IdlTime = GetTickCount();
		}
		else if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD )
		{
			DWORD dwPassTime = GetTickCount();
			if( dwPassTime > m_dwOtherChar_IdlTime + IDLE_PC_TIME )
			{
				//	캐릭터 애니매이션 셋팅
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

//-----------아이템을 판별하여 셋팅해준다----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info )
{
	if( info.snIndex != 0 )
	{
		//	장착해준다.
		g_cEquipSystem->HT_EquipSys_Equip( m_iOtherCharModelID, m_byOtherChar_TribeType, 0, info.snIndex, m_byOtherChar_HairType, 0 );
		//	장착 정보르 저장하고
		m_dwEquipItem[byPart] = info.snIndex;

		if ( HT_IS_ITEM_WEAR( info.snIndex ) )
		{
			m_nOtherChar_WearItemID	= info.snIndex;
		}
		else if ( HT_IS_ITEM_WEAPON( info.snIndex ) )
		{
			m_nOtherChar_WeaponItemID = info.snIndex;
		}

		//	장착 파트가 무기라면 제련 효과를 붙인다.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			//	메인 제련이 되어 있는 (무기) 아이템의 FX 설정
			if( info.byRefineLevel > 0 )
				g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherCharModelID, info.snIndex, info.byRefineLevel );
			
			// 속성 제련 되어 있는 (무기) 아이템의 경우
			if( info.byRefineLevel > 0 )
			{
				// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
				g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherCharModelID, info.snIndex, (HTESubRefineType)info.byMainRef, info.byRefineLevel );
			}
		}
	}
	else
	{
		//	탈착 해준다.
		g_cEquipSystem->HT_EquipSys_UnEquip( m_iOtherCharModelID, m_byOtherChar_TribeType, m_dwEquipItem[byPart], m_byOtherChar_HairType );
		//	탈착 정보르 저장하고
		m_dwEquipItem[byPart] = 0;

		if( byPart == eTNEqu_OneHandWeapon || byPart == eTNEqu_TwoHandWeapon )
			m_nOtherChar_WeaponItemID = -1;
		else if( byPart == eTNEqu_Armor )
			m_nOtherChar_WearItemID	= -1;

		//	탈착 파트가 무기라면 제련 효과를 붙인다.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			// 제련된 아이템의 FX 없애기
			// 메인 제련
			g_pEngineHandler->HT_hrDetachItemMainRefineEffect( m_iOtherCharModelID, info.snIndex );
			// 속성 제련
			g_pEngineHandler->HT_hrDetachItemSubRefineEffect( m_iOtherCharModelID, info.snIndex );
		}
	}

	if ( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SIT ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_RUN ||
		 m_nOtherChar_AniResentState == CHARACTER_ANISTATE_WLK )
	{
		//	캐릭터 애니매이션 셋팅
		this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
	}

	//	조교모자를 착용했는지 분석
	if( m_dwEquipItem[1] == ITEMINDEX_ASSISTANTHAT )
		m_bAssistantSw = HT_TRUE;
	else
		m_bAssistantSw = HT_FALSE;
}

//---------정보 디스플레이 셋팅----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetInfoDisplay()
{
	m_bOtherChar_Info_Sw = HT_TRUE;
}

//---------정보 디스플레이 셋팅취소----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetInfoCancel()
{
	m_bOtherChar_Info_Sw = HT_FALSE;
}

//-----------픽된 상태인가 체크----------//
HTRESULT HTOtherCharacter::HT_hrOtherChar_GetInfoStatus()
{
	return HT_OK;
}

//	전체 공격 관련
//----------공격당한 순간을 체크해옴----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetAttack( DWORD dwSkillIndex, BYTE byAttackType, HTint iItemIndex )
{
	//	이펙트_임팩트 이펙트 틀어주기
	this->m_vOtherCharAttack_ImpactEffect( dwSkillIndex, iItemIndex );

	//	프라나 업 이펙트가 아니면 플리커
	if( byAttackType != MAINCHAR_ATTACKTYPE_PRANA )
		g_pEngineHandler->HT_hrFlickerObject( m_iOtherCharModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	라이팅
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iOtherCharModelID, HT_FALSE );

	//	HIT 애니매이션 틀어주기
	if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_STD || m_nOtherChar_AniResentState == CHARACTER_ANISTATE_IDL )
	{
		m_bOtherChar_HitSw = HT_TRUE;
		//	캐릭터 애니매이션 셋팅
		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_HIT;
		this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
	}
}

//-----------공격포인트에서 해야할일들----------//
HTvoid HTOtherCharacter::HT_vOtherChar_AttackPointCheck()
{
	//-----공격클래스 생성-----//
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

//-----------공격을 위한 회전-----------//
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

//	공격자의 위치 보정
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

	//	멈추기
	m_cOtherCharMove->HT_vOtherCharMoveStop();
}

//-----------스킬 셋팅----------//
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

	if( info->bySelect == 0x01 )			//	스킬 선택
	{
		//	스킬 발동
		HTint nEffectID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectID, info->dwIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherCharModelID, HT_FALSE, info->byLevel );

		if( m_byOtherChar_PartyMember == 0x02 || g_bDevelopingMode == HT_TRUE )
		{
			if( info->byHand == 0x02 )			//	왼쪽 스킬, 액티브 스킬
			{
				//	스킬 지속
				g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, info->dwIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, info->byLevel );
				//	캐릭터 애니매이션 셋팅
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
				this->HT_vOtherChar_SetChangeAni( 1, 0.0f, m_dwActiveSkillIndex );
				//	스킬 이동 속도 적용
				m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( info->dwIndex, info->byLevel );
			}
		}
	}
	else if( info->bySelect == 0x02 )		//	스킬 해제
	{
		if( info->byHand == 0x02 )			//	왼쪽 스킬, 액티브 스킬
		{
			g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
			m_nEffect_ActiveSkillID = -1;
			//	스킬 이동 속도 적용
			m_cOtherCharMove->HT_vOtherCharSetSpeedSkill( 0, 0 );
		}
	}
}

//	액티브 스킬 상용을 받았을 때 Effect 틀기
HTvoid HTOtherCharacter::HT_vOtherChar_SetActiveSkillEffectOn( DWORD dwSkillIndex, HTbool bType, BYTE byLevel )
{
	g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, dwSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, bType, byLevel );
}

//-----------파티원으로서 가입 및 탈퇴할때----------//
HTvoid HTOtherCharacter::HT_vOtherChar_SetPartyJoineDisband( BYTE byParty )
{
	m_byOtherChar_PartyMember = byParty;
	if( m_byOtherChar_PartyMember == 0x01 )			//	탈퇴
	{
		g_pEngineHandler->HT_hrStopSFX( m_nEffect_ActiveSkillID );
		m_nEffect_ActiveSkillID = -1;
	}
	else if( m_byOtherChar_PartyMember == 0x02 )
	{
		//	스킬 지속
        g_pEngineHandler->HT_hrStartSFX( &m_nEffect_ActiveSkillID, m_dwActiveSkillIndex, HT_SFX_WHEN_STATE, m_iOtherCharModelID, HT_TRUE, m_byActiveSkillLevel );
	}
}

//---------HP 변경사항 체크----------//
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

		//	시스템창에 메시지 뿌려주기.
		char chName[SZNAME_LENGTH];
		CHTString::HT_hrStringCopy( chName, m_iOtherCharName, SZNAME_LENGTH);
		CHTString strMessage;
		strMessage.HT_szFormat( "%s에게 데미지 %d를(을) 주었습니다.", chName, m_nOtherChar_Resent_HP );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ATTACK, strMessage );
	}

	return m_nOtherChar_HitCount;
}


//------------------------------------------------//
//----------서버와 통신하는 네트워크 함수---------//
//------------------------------------------------//
//	Other Character LevelUp 을 알림
HTvoid HTOtherCharacter::HT_vOtherChar_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CHAKRAUPGRADE, m_iOtherCharModelID, HT_FALSE );
}

//---------- GM의 투명모드를 설정 또는 해제를 요청한다를 알린다-------------//
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

//	서버가 다른캐릭터의 이동을 알려왔을 때
HTvoid HTOtherCharacter::HT_vNetWork_OtherChar_Action( MSG_Action* info )
{
	m_bOtherChar_AttackSw = HT_FALSE;
	m_bOtherCharMoveState = info->Effect;

	if( m_bOtherCharMoveState == 0 )
	{
		//	현재 위치와 목표 위치를 비교 목표위치에 도착못했으면 이동
		HTPoint pPt;
		m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	캐릭터 애니매이션 셋팅
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
		//	현재 위치와 목표 위치를 비교 목표위치에 도착못했으면 이동
		HTPoint pPt;
		m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	캐릭터의 앉아있거나 앉기 동작할때만 서기 동작 틀어준다.
			if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SIT || m_nOtherChar_AniResentState == CHARACTER_ANISTATE_SITDOWN )
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STANDUP;
			else
				m_nOtherChar_AniResentState = CHARACTER_ANISTATE_STD;

			//	캐릭터 애니매이션 셋팅
			this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );

			//-----아이들 동작을 위해-----//
			m_dwOtherChar_IdlTime = GetTickCount();
		}
		else
		{
			m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
		}

		//	OtherChar 방향
        g_pEngineHandler->HT_hrRotateObject( m_iOtherCharModelID, (HTfloat)info->Direction/100 );
	}
	else if( m_bOtherCharMoveState == 2 )
	{
		if( m_nOtherChar_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	캐릭터 애니매이션 셋팅
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_WLK;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
		}
		m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
	}
	else if( m_bOtherCharMoveState == 3 )
	{
		if( m_nOtherChar_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	캐릭터 애니매이션 셋팅
			m_nOtherChar_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherChar_SetChangeAni( -1, 0.0f, 0 );
		}
		m_cOtherCharMove->HT_vOtherCharMoveCheckTargetCell( info );
	}

	//----------캐스트 스킬 쥐소---------//
	if( m_bOtherChar_CastSw == HT_TRUE )
	{
		//	캐스트 유무
		m_bOtherChar_CastSw = HT_FALSE;
		//	이펙트를 정지 시키고
		g_pEngineHandler->HT_hrStopSFX( m_iOtherChar_CastEffectID );
		m_iOtherChar_CastEffectID = 0;
	}
}

//----------캐스트 스킬 공격 준비---------//
HTvoid HTOtherCharacter::HT_vOtherChar_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info )
{
	//	캐스트 유무
	m_bOtherChar_CastSw = HT_TRUE;
	//	이펙트 시작
	g_pEngineHandler->HT_hrStartSFX( &m_iOtherChar_CastEffectID, info->dwIndex, HT_SFX_WHEN_CAST, m_iOtherCharModelID, HT_TRUE );
}

//	스킬 캐스팅을 알림
HTvoid HTOtherCharacter::HT_vOtherChar_Network_Skill_Cast_Broadcast( S_MSG_ATTACK_OTHERMOB info )
{
	//	캐릭터 죽는 액션이 들어갔으면 어떤 액션도 틀지 않음
	if( m_nOtherChar_AniResentState == CHARACTER_ANISTATE_DIE )
		return;

	//	Combat 셋팅
	m_bOtherChar_AttackSw = HT_TRUE;
	//	공격받은 대상의 KeyID
	m_dwOtherChar_TargetKeyID = info.krgTarget[0].snKeyID;
	//	스킬 관련 설정_ID, Level
	m_dwOhterChar_SkillID = info.iSkillID;
	m_dwOhterChar_SkillLevel;//
	//	커리티컬 힛 판정 여부
	m_byOtherCharCriticalHit = info.snRes;
	//	공격당한자의 모델 아이디
	m_nAttack_TargetModelID = info.iTargetModelID;
	//	1:OtherCharecter, 2:Monster, 3:MainCharacter
	m_byOtherChar_AttackTarget	= info.byTargetType;
	//	Target의 좌표
	m_vecAttack_TargetPos = info.vecTargetPos;
	// 공격자를 향해 회전
	this->HT_vOtherChar_RotateAttack( m_vecAttack_TargetPos );
	//	공격자의 위치 보정
	this->HT_vOtherChar_AttackPosCheck( info.PosX, info.PosY );
	//	공격 Type 셋팅
	m_nOtherChar_AttackType		= MAINCHAR_ATTACKTYPE_SKILL;

	//	액션 0초에서 왔느냐?
	if( info.snRes == -1 )
	{
		if( m_dwOhterChar_SkillID != 0 )
		{
			m_dwOtherChar_SkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_dwOhterChar_SkillID );
			//	액션 스킬 캐스팅 속도
			if( !g_pParamMgr->HT_bGetPCSkillCastingTime( m_dwOhterChar_SkillID, 1, &m_iOtherChar_SkillCastTime ) )
				m_iOtherChar_SkillCastTime = 0;
			//	Skill Ready Ani Start
			//	캐릭터 애니매이션 셋팅
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
			//	캐릭터 애니매이션 셋팅
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

//	OtherChar 죽음 처리
HTvoid HTOtherCharacter::HT_hrOtherChar_Death()
{
	if( m_nOtherChar_Death == OTHERCHAR_STATE_LIVE )
	{
		m_nOtherChar_Death = OTEHRCHAR_STATE_DEATHMOTION;
		m_dwOtherChar_DeathDelay = GetTickCount();
		//	캐릭터 애니매이션 셋팅
		m_nOtherChar_AniResentState = CHARACTER_ANISTATE_DIE;
		this->HT_vOtherChar_SetChangeAni( 1, 0.0f, 0 );
	}
}

//	OtherChar 죽음 처리 딜레이
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

