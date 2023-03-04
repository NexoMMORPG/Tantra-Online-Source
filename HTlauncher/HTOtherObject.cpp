#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htotherobject.h"

HTint g_iYutMoveCellX[30] = { 0, 675, 675, 675, 675, 675, 675, 671, 668, 665, 662, 658, 658, 658, 658, 658, 658, 662, 666, 668, 671, 661, 663, 666, 670, 672, 672, 670, 663, 661 };
HTint g_iYutMoveCellZ[30] = { 0, 427, 423, 420, 417, 414, 410, 410, 410, 410, 410, 410, 414, 417, 420, 423, 427, 427, 427, 427, 427, 413, 416, 419, 421, 424, 413, 416, 421, 424 };

HTOtherObject::HTOtherObject(void)
{
	m_pObjectInfo = HT_NULL;
	m_iOtherModelID = -1;
	m_fOther_ModelHeight = 0.0f;
	m_iOther_TribeCode = -1;
	m_pOther_MoveSystem = HT_NULL;
    m_oOther_AttackFactor = HT_NULL;
	m_iOther_AniResentState = -1;
	m_iOther_AttackAniCount = -1;
	for ( HTint i = 0; i < 16; ++i )
	{
		m_iOther_EquipItem[i] = -1;
		m_byOther_MainRef[i] = -1;
		m_byOther_RefineLevel[i] = -1;
	}
	m_bOther_IsWeaponArmed = HT_FALSE;
	m_iOther_WearItemID = -1;
	m_iOther_WeaponItemID = -1;
	m_bOther_AssistantSw = HT_FALSE;

	m_bOther_InfoSw = HT_FALSE;
	m_iOther_LiveIndex = -1;
	m_iOther_LiveDelayTime = -1;
	m_iOther_IdlTime = -1;
	m_fOther_ShowAngle = 0.0f;
	m_iOther_ProgressAngle = -1;
	m_iOther_ApplySkillIndex = -1;
	m_iOther_ApplySkillType = -1;
	m_iOther_ApplySkillEffectID = -1;
	m_iOther_DurationSkillEffectID = -1;
	m_iOther_ApplySkillStartTime = -1;
	m_iOther_ApplySkillContinueTime = -1;
	m_byOther_PartyMember = 0;
	m_iOther_AttackType = -1;
	m_vecOther_AttackTargetPos = HTvector3( 0.0f, 0.0f, 0.0f );
	m_vecOther_AttackSourcePos = HTvector3( 0.0f, 0.0f, 0.0f );
	m_iOther_InvadeKeyID = -1;
	m_iOther_ChatMsgStartTime = -1;
	m_iTargettingEffectID = -1;
	m_bStopWhenInvadeSw = HT_FALSE;
	m_bOther_AttackMoveSw = HT_FALSE;
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        m_iOther_TargetDamageHP[i] = -1;
		m_iOther_TargetKeyID[i] = -1;
		m_iOther_TargetHP[i] = -1;
		m_byOther_TargetRes[i] = -1;
	}
	m_iOther_TargetAffaction = 0;
	m_iOther_ActionEffect = -1;
	m_byOther_Size = 0;
	m_bOther_AtkPtFromTimeSw = HT_NULL;
	m_iOther_AtkptFromTimeDelay = 0;
	m_iOther_AtkptFromTimeStartTime = 0;
	m_bOther_AtkptCheck = HT_FALSE;
	m_bOther_DownEarthSw = HT_FALSE;
	m_iOther_FXAffections = -1;
	m_bOther_MyGuildMemberSw = HT_FALSE;
	m_bOther_MainCharWizardEyesSw = HT_FALSE;
	m_strOther_CastName.HT_hrCleanUp();
	m_bOther_DefinZoneAttackTarget = HT_FALSE;
	m_iOther_EndPoint = 0;
	m_pOther_EndPoint.x = 0;
	m_pOther_EndPoint.x = 0;
	m_bOhter_Targetting = HT_FALSE;
	m_bOther_CollisonCheck = HT_FALSE;
}

HTOtherObject::~HTOtherObject(void)
{
	if( m_iOther_ApplySkillEffectID != -1 )
		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
	if( m_iOtherModelID != -1 )
        g_pEngineHandler->HT_vDestroyCharacter( m_iOtherModelID, 8 );
	if( m_oOther_AttackFactor )
        HT_DELETE( m_oOther_AttackFactor );
	if( m_pOther_MoveSystem )
        HT_DELETE( m_pOther_MoveSystem );
	if( m_pObjectInfo )
        HT_DELETE( m_pObjectInfo );
	if( m_iTargettingEffectID != -1 )
		g_pEngineHandler->HT_hrStopSFX( m_iTargettingEffectID );
	if( m_iOther_FXAffections != -1 )
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
}

//	Init Other Mob
HTvoid HTOtherObject::HT_vOtherObject_Create( PS_SCP_INIT_OTHER_MOB info, BOOL bObjectShow )
{
	//	오브젝트 모델 출력여부
	m_bOther_ShowObject = bObjectShow;
	//	Atk / Move System Create
	m_oOther_AttackFactor = HT_NULL;
	m_oOther_AttackFactor = new S_ATTACK_FACTOR;
	m_pOther_MoveSystem = HT_NULL;
	m_pOther_MoveSystem = new HTOtherObjectMove;

	m_pObjectInfo = new S_SCP_INIT_OTHER_MOB;
	//	Object Factor Init
	ZeroMemory( m_pObjectInfo, sizeof(S_SCP_INIT_OTHER_MOB) );
	memcpy( m_pObjectInfo, info, sizeof( S_SCP_INIT_OTHER_MOB ) );
	m_strOther_Name = m_pObjectInfo->szName;
	
	//	종족코드 보정해주기
	//	몹일때
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
	{
		m_iOther_WeaponItemID = m_pObjectInfo->snTribe;
		m_iOther_TribeCode = m_pObjectInfo->snTribe;

		//	몬스터의 정보를 가져오고
		CHTString szName;
		//if( g_pEngineHandler->HT_hrGetNPCName( m_iOther_TribeCode, &szName ) == HT_OK )
		if( g_pParamMgr->HT_bGetMonsterName( m_iOther_TribeCode, &szName ) == true )
			m_strOther_Name = szName;

		g_pParamMgr->HT_bGetMonsterSize(m_iOther_TribeCode, &m_byOther_Size);

		//	주신코드 보정해주기
		if( m_pObjectInfo->byTrimuriti == 5 )		m_pObjectInfo->byTrimuriti = TRIMURITI_BRAHMA;
		else if( m_pObjectInfo->byTrimuriti == 6 )	m_pObjectInfo->byTrimuriti = TRIMURITI_VISHNU;
		else if( m_pObjectInfo->byTrimuriti == 7 )	m_pObjectInfo->byTrimuriti = TRIMURITI_SIVA;
	}
	//	캐릭터일때
	else
	{
		m_byOther_Size = 1;
        HT_ConvertTribeS2C( m_pObjectInfo->snTribe, m_iOther_TribeCode );
	}

	if( m_byOther_Size < 1 )
		m_byOther_Size = 1;
	
	//	OtherChar 위치 셋팅
	HTvector3 vecPos;
	HT_CELL_COORD crdCell;
	crdCell.x = m_pObjectInfo->snTargetX;
	crdCell.y = m_pObjectInfo->snTargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecPos );

	//	아이템 장착 셋팅
	for( HTint i=0 ; i<7 ; i++ )
	{
		if( m_pObjectInfo->Equip[i].snIndex )
			m_pObjectInfo->Equip[i].snIndex += HT_ITEM_INDEX_START;
	}

	//	오브젝트 모델 출력여부 판단하여 모델 생성
	if( m_bOther_ShowObject )
		this->HT_vOtherObject_CreateModel();

	//	긱도
	if( m_pObjectInfo->byDir == 0 )
	{
		//	Randeom
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( (HTfloat)((rand()%628+314))/100.0f );
	}
	else
	{
		if( g_iInationalType==INATIONALTYPE_KOREA || 
			g_iInationalType==INATIONALTYPE_INDONESIA || 
			g_iInationalType==INATIONALTYPE_PHILIPPINE ||
			g_iInationalType==INATIONALTYPE_JAPEN )
            m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-((33-m_pObjectInfo->byDir)*(HT_PIX2/32)) );
		else
		{
			if( m_pObjectInfo->byDir == 1 )		//	North
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2 );
			else if( m_pObjectInfo->byDir == 2 )		//	South
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+HT_PI );
			else if( m_pObjectInfo->byDir == 3 )		//	West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-(HT_PI/2) );
			else if( m_pObjectInfo->byDir == 4 )		//	East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+(HT_PI/2) );
			else if( m_pObjectInfo->byDir == 5 )		//	South-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-(HT_PI/4) );
			else if( m_pObjectInfo->byDir == 6 )		//	South-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+(HT_PI/4) );
			else if( m_pObjectInfo->byDir == 7 )		//	North-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+HT_PI+(HT_PI/4) );
			else if( m_pObjectInfo->byDir == 8 )		//	North-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+HT_PI-(HT_PI/4) );
			else if( m_pObjectInfo->byDir == 9)			//	South-East-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+((HT_PI/8)*5) );
			else if( m_pObjectInfo->byDir == 10)		//	South-West-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-((HT_PI/8)*3) );
			else if( m_pObjectInfo->byDir == 11)		//	North-West-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-((HT_PI/8)*5) );
			else if( m_pObjectInfo->byDir == 12)		//	North-East-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+((HT_PI/8)*3) );
			else if( m_pObjectInfo->byDir == 13)		//	South-South-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+((HT_PI/8)*7) );
			else if( m_pObjectInfo->byDir == 14)		//	South-South-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-((HT_PI/8)*1) );
			else if( m_pObjectInfo->byDir == 15)		//	North-North-West
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2-((HT_PI/8)*7) );
			else if( m_pObjectInfo->byDir == 16)		//	North-North-East
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( HT_PIX2+((HT_PI/8)*1) );
		}
	}

	//	Setting at World
	m_fOther_ShowAngle = m_pOther_MoveSystem->HT_fOtherObjectMove_GetDirect();
	g_pEngineHandler->HT_hrRotateObject( m_iOtherModelID, m_fOther_ShowAngle );

	//	Pop Type
	//	Setting Up/Down_Up
	if( info->byPopType == 1 )
        m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( -(m_fOther_ModelHeight*1.5f), 0.5f, 0.0f, HT_FALSE );
	//	Setting Up/Down_Slow Down
	else if( info->byPopType == 2 )
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( (m_fOther_ModelHeight*1.5f), -0.5f, 0.0f, HT_FALSE );
	//	Setting Up/Down_Accel Down
	else if( info->byPopType == 3 )
        m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( (m_fOther_ModelHeight*2.0f), -1.0f, 0.0f, HT_TRUE );
    g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );

	//	최초 애니매이션 셋팅
	//m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
	//g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, m_iOther_TribeCode, HT_ANISTATE_STD, -1 );

	//	Setting Hide Infomation
	this->HT_vOtherObject_SetHideInfomation();

	//	Live
	m_iOther_LiveIndex = OTHERCHAR_STATE_LIVE;

	//	GM 캐릭터가 아닐때만 생성 이펙트 뿌려줌
	if( m_iOther_TribeCode != 9 )
	{
		BYTE byAoi = g_cAoi->HT_AOI_Level( m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos() );
		if( byAoi <= AOI_LEVEL_5 )
		{
			HTint idFx;
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
				g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherModelID, HT_FALSE );
			else
				g_pEngineHandler->HT_hrStartSFX( &idFx, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), m_iOtherModelID, HT_FALSE );
		}
	}

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		//	파티멤버임을 판단!
		//	0x01:파티멤버아님, 0x02:파티멤버
		if( g_cParty->HT_bParty_IsPartyMember( m_strOther_Name.HT_szGetString() ) )
			m_byOther_PartyMember = 0x02;
		else
			m_byOther_PartyMember = 0x01;

		//	길드에 가입되어 있다면
		CHTString strTemp;
		strTemp.HT_hrCleanUp();
		strTemp = m_pObjectInfo->szGuild;
		if( !strTemp.HT_bIsEmpty() )
		{
			//	길드 마크 표현 하기
			if( g_bGuildMarkShow )
                this->HT_vOtherObject_SetGuildMarkOn();
			//	Guild Member Check
			this->HT_vOtherObject_SetMyGuildCheck( m_pObjectInfo->szGuild );
		}

		//	주신이 있다면
		if( info->byTrimuriti )
		{
			//	주신 마크 표현 하기
			this->HT_vOtherObject_SetTrimuritiMarkOn();
		}

		//	투명인지 체크
		if( m_iOther_TribeCode == 9 )
            if( m_pObjectInfo->byGMStatus & 0x02 )
				g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );
	}

	//	투명인지 체크
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
		g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );

#ifdef GM_CHAR_HIDE
	if( m_iOther_TribeCode == 9 )
		g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );
#endif

	//	아이들 동작을 위해
	m_iOther_IdlTime = GetTickCount() + ( rand()%IDLE_PC_TIME );

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		// 계급 변경됨 (서버로 부터 내려받는 방식) 2005. 1. 31 선영범
		if (eTNCaste_Sudra3 <= m_pObjectInfo->byCaste && eTNCaste_Sudra1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastSudra, &m_strOther_CastName, _T("") );
		else if (eTNCaste_Baisha3 <= m_pObjectInfo->byCaste && eTNCaste_Baisha1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastVaisha, &m_strOther_CastName, _T("") );
		else if (eTNCaste_Cushatri3 <= m_pObjectInfo->byCaste && eTNCaste_Cushatri1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastKshatrya, &m_strOther_CastName, _T("") );
		else if (eTNCaste_Braman3 <= m_pObjectInfo->byCaste && eTNCaste_Braman1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastBraman, &m_strOther_CastName, _T("") );
		else if (eTNCaste_Avatara3 <= m_pObjectInfo->byCaste && eTNCaste_Avatara1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastAvatara, &m_strOther_CastName, _T("") );
		else if (eTNCaste_MahaRaja3 <= m_pObjectInfo->byCaste && eTNCaste_MahaRaja1 >= m_pObjectInfo->byCaste)
			HT_g_Script_SetMessage( eMsgCommonCastReserve, &m_strOther_CastName, _T("") );
		else
			HT_g_Script_SetMessage( eMsgCommonNone, &m_strOther_CastName, _T("") );

		if( g_iInationalType == INATIONALTYPE_KOREA )
		{
			m_strOther_CastName--;
			m_strOther_CastName--;
		}
	}
	else
	{
		//	Cast Name
		m_strOther_CastName.HT_hrCleanUp();
	}

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		//	주신전 지역인면 다른 주신이면 공격 가능
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti != m_pObjectInfo->byTrimuriti )
				m_bOther_DefinZoneAttackTarget = TRUE;
			else
				m_bOther_DefinZoneAttackTarget = FALSE;
		}
		//	요새전 지역이면 자신의 길드나 연합길드가 아니면 공격 가능
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			if( strlen(m_pObjectInfo->szGuild) > 0 )
			{
				CHTString strMyGuild = g_cGuildSystem->HT_strGuild_GetGuildName();
				CHTString strArlliedGuild = g_cGuildSystem->HT_strGuild_AlliedGuildName( 0 );
				//	타 길드 체크
				if( strMyGuild.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 &&
					strArlliedGuild.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 )
					m_bOther_DefinZoneAttackTarget = TRUE;
				else
					m_bOther_DefinZoneAttackTarget = FALSE;
			}
			else
			{
				m_bOther_DefinZoneAttackTarget = TRUE;
			}
		}
		//	일반 필드면 다른 로직을 타게된다.
		else
		{
			m_bOther_DefinZoneAttackTarget = FALSE;
		}
	}
	else
	{
		m_bOther_DefinZoneAttackTarget = TRUE;
		//	주신전 지역인면 다른 주신이면 공격 가능
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti == m_pObjectInfo->byTrimuriti )
				m_bOther_DefinZoneAttackTarget = FALSE;
		}
		//	요새전 지역이면 자신의 경비병을 체크
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			HTint iMyStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();
			//	자신의 경비병을 체크
			if( (iMyStrongGuild==0 && m_pObjectInfo->byTrimuriti==14 ) ||
				(iMyStrongGuild==1 && m_pObjectInfo->byTrimuriti==15 ) ||
				(iMyStrongGuild==2 && m_pObjectInfo->byTrimuriti==16 ) ||
				(iMyStrongGuild==3 && m_pObjectInfo->byTrimuriti==17 ) )
				m_bOther_DefinZoneAttackTarget = FALSE;
		}
	}

	//	Setting Targetting
	this->HT_vOtherObject_SetTargetting();

	//	Setting Collison
	this->HT_vOtherObject_SetCollison();

	//	죽어서 태어났는지 검사
	if( info->nCurHP <= 0 )
	{
		//	Live
		m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
		m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}

	//	트레이드 모드 체크
	if( !g_cSystem->HT_bSystem_GetShopModelMode() &&
		m_pObjectInfo->byTradeMode != 0 )
	{
		//	캐릭터 애니매이션 셋팅
		m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
}

//	Create Model
HTvoid HTOtherObject::HT_vOtherObject_CreateModel()
{
	//	혹시나 이넘이 생성되어 있다면 삭제
	if( m_iTargettingEffectID != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iTargettingEffectID );
		m_iTargettingEffectID = -1;
	}
	if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}
	if( m_iOtherModelID != -1 )
	{
        g_pEngineHandler->HT_vDestroyCharacter( m_iOtherModelID, 8 );
		m_iOtherModelID = -1;
	}

	//	최초 애니매이션 셋팅
	m_iOther_AniResentState = CHARACTER_ANISTATE_STD;

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		HTbool bTrue = HT_FALSE;
        //	트레이드 모드 체크
        if( m_pObjectInfo->byTradeMode == 0 )
			bTrue = HT_TRUE;
		else if( !g_cSystem->HT_bSystem_GetShopModelMode() )
			bTrue = HT_TRUE;

		if( bTrue )
		{
			m_iOtherModelID = g_pEngineHandler->HT_iCreateCharacter( m_iOther_TribeCode, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos(), m_pObjectInfo->byHead, m_pObjectInfo->byFace );

			//	머리 장착
			this->HT_vOtherObject_SetItemType( eTNEqu_Helmet, m_pObjectInfo->Equip[0] );
			//	몸 장착(상의)
			this->HT_vOtherObject_SetItemType( eTNEqu_Armor, m_pObjectInfo->Equip[1] );
			//	몸 장착(하의)
			this->HT_vOtherObject_SetItemType( eTNEqu_Pants, m_pObjectInfo->Equip[2] );
			//	왼손 장착
			this->HT_vOtherObject_SetItemType( eTNEqu_Shield, m_pObjectInfo->Equip[3] );
			//	오른손 장착
			this->HT_vOtherObject_SetItemType( eTNEqu_OneHandWeapon, m_pObjectInfo->Equip[4] );
			//	발 장착
			this->HT_vOtherObject_SetItemType( eTNEqu_Boots, m_pObjectInfo->Equip[5] );
			//	장갑 장착
			this->HT_vOtherObject_SetItemType( eTNEqu_Gloves, m_pObjectInfo->Equip[6] );
			//	Start Ani
            g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, m_iOther_TribeCode, HT_ANISTATE_STD, -1 );
			//	if Trade Mode then change ani
			if( m_pObjectInfo->byTradeMode != 0 )
			{
				//	캐릭터 애니매이션 셋팅
				m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
			}
		}
		else
		{
			if( m_pObjectInfo->byTradeMode == 1 )
			{
				m_iOtherModelID = g_pEngineHandler->HT_iCreateMonster( 2482, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
				g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, 2482, HT_ANISTATE_STD, -1 );
			}
			else if( m_pObjectInfo->byTradeMode == 2 )
			{
				m_iOtherModelID = g_pEngineHandler->HT_iCreateMonster( 2483, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
				g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, 2483, HT_ANISTATE_STD, -1 );
			}
		}
	}
	else
	{
		m_iOtherModelID = g_pEngineHandler->HT_iCreateMonster( m_iOther_TribeCode, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
		g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, m_iOther_TribeCode, HT_ANISTATE_STD, -1 );
	}
	//	모델 사이즈
	m_fOther_ModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iOtherModelID );
}
//	Delete Model
HTvoid HTOtherObject::HT_vOtherObject_DeleteModel()
{
	//	생성되어 있는 넘들만 삭제
	if( m_iTargettingEffectID != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iTargettingEffectID );
		m_iTargettingEffectID = -1;
	}
	if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}
	if( m_iOtherModelID != -1 )
	{
        g_pEngineHandler->HT_vDestroyCharacter( m_iOtherModelID, 8 );
		m_iOtherModelID = -1;
	}
}

//	Control
HTvoid HTOtherObject::HT_vOtherObject_Control( HTfloat fElapsedTime )
{
	//	Move System
	this->HT_vOtherObject_MoveControl( fElapsedTime );
	//	Rotate Control
	this->HT_vOtherObject_RotateControl( fElapsedTime );
	//	Move Stand Control
	this->HT_vOtherObject_StandControl(fElapsedTime );
	//	Animation Animation Check
	this->HT_vOtherObject_AnimationCheck();
	//	Control AttackPointCheck From Time
	this->HT_vOtherObject_ControlAttackPointCheckFromTime();
	//	Control Active Skill Cast Time Check
	this->HT_vOtherObject_ControlActiveSkillCastTimeCheck();
	//	Control Death Delay
	this->HT_vOtherObject_ControlDeathDelay();
}
//	Control Death Delay
HTvoid HTOtherObject::HT_vOtherObject_ControlDeathDelay()
{
	//	캐릭터일때는 Skip
	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
		return;

	//	동영상 촬영을 위해 시체를 남겨두기 위해
	if( g_bGamePlayMovieForGlobal )
		return;

	if( m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE )
		return;

	HTint iPassTime = GetTickCount();

	if( m_iOther_LiveIndex == OTEHRCHAR_STATE_SUMMONS )
	{
		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		if ( iPassTime > m_iOther_LiveDelayTime + 500 && iPassTime < m_iOther_LiveDelayTime + 4000 )
		{
			//	이펙트_몬스터 죽었을때 여러가지것들
			if ( m_iOther_AniResentState != CHARACTER_ANISTATE_IDL )
			{
				m_iOther_AniResentState = CHARACTER_ANISTATE_IDL;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
			}
		}
		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		else if ( ( iPassTime > m_iOther_LiveDelayTime + 4000 ) && ( iPassTime < m_iOther_LiveDelayTime + 20000 ) )
		{
			if( m_bOther_DownEarthSw == HT_FALSE )
			{
				//	Setting Up/Down_Death Mode
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( 0.0f, -0.5f, m_fOther_ModelHeight, HT_FALSE );
				m_bOther_DownEarthSw = HT_TRUE;

				//	생성 이펙트
				HTint idFx;
				if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
					g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherModelID, HT_FALSE );
				else
					g_pEngineHandler->HT_hrStartSFX( &idFx, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), m_iOtherModelID, HT_FALSE );
			}
		}
		// 죽은 다음의 시간을 좀 더 길게 한다. 드디어 없어진다.
		else if( iPassTime > m_iOther_LiveDelayTime + 20000 )
		{
			m_iOther_LiveIndex = OTHERCHAR_STATE_DEATH;
		}
	}
	else
	{
		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		if ( iPassTime > m_iOther_LiveDelayTime + 2000 && iPassTime < m_iOther_LiveDelayTime + 10000 )
		{
			//	이펙트_몬스터 죽었을때 여러가지것들
			if ( m_iOther_AniResentState != CHARACTER_ANISTATE_DIE )	// 한번만 실행하기 위한거 같다.
				this->HT_vOtherObject_WhenDeathEffect();

			//	몹이 문일때는 바로 죽도록 한다.
			if( m_pObjectInfo->byDir )
				m_iOther_LiveDelayTime -= 10000;
		}
		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		else if ( ( iPassTime > m_iOther_LiveDelayTime + 10000 ) && ( iPassTime < m_iOther_LiveDelayTime + 25000 ) )
		{
			if( m_bOther_DownEarthSw == HT_FALSE )
			{
				//	Setting Up/Down_Death Mode
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( 0.0f, -0.5f, m_fOther_ModelHeight, HT_FALSE );
				m_bOther_DownEarthSw = HT_TRUE;
			}
		}
		// 죽은 다음의 시간을 좀 더 길게 한다. 드디어 없어진다.
		else if( iPassTime > m_iOther_LiveDelayTime + 25000 )
		{
			m_iOther_LiveIndex = OTHERCHAR_STATE_DEATH;
		}
	}
}

//	Control Active Skill Cast Time Check
HTvoid HTOtherObject::HT_vOtherObject_ControlActiveSkillCastTimeCheck()
{
	//if( m_iOther_ApplySkillEffectID != -1 )
	{
		if( m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
		{
			HTdword dwPassTime = GetTickCount();
			if( dwPassTime >= (DWORD)(m_iOther_ApplySkillStartTime + m_iOther_ApplySkillContinueTime) )
			{
				//	Skill Cast Ani Start
				m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
				this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, m_iOther_ApplySkillIndex );
				//	이펙트가 켜져 있을때는 꺼주기
				if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
				//	캐스팅 이펙트 시작
				g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
				//if( m_iOther_ApplySkillEffectID == -1 )
				//	m_iOther_ApplySkillEffectID = 0;
				//	캐스팅 시작시간을 설정
				m_iOther_ApplySkillStartTime = GetTickCount();
				//	캐스팅 지속시간을 설정
				g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
			}
		}
		else if( m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLCAST )
		{
			HTdword dwPassTime = GetTickCount();
			if( dwPassTime >= (DWORD)(m_iOther_ApplySkillStartTime + m_iOther_ApplySkillContinueTime) )
			{
				//	기존에 캐스팅 이펙트가 있었으면 정지
				if( m_iOther_ApplySkillEffectID != -1 )
					g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
				m_iOther_ApplySkillEffectID = -1;

				//	공격 Type 셋팅
				if( m_iOther_AttackType	== MAINCHAR_ATTACKTYPE_SKILL )
				{
					//	Skill Attack Ani Start
					m_iOther_AniResentState	= CHARACTER_ANISTATE_SKILLATK;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE );
				}
				else
				{
					//	액티베이트 애니매이션 틀어준다.
					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLACTIVATE;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );

					// 액티베이트 이펙트 시전
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE, 5 );

					//	V3랑 따로 작업한것
					if( m_iOther_DurationSkillEffectID )
					{
						g_pEngineHandler->HT_hrStopSFX( m_iOther_DurationSkillEffectID );
						m_iOther_DurationSkillEffectID = 0;
					}

					HTdword dwSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iOther_ApplySkillIndex );

					//	지속스킬과 자기자신과 타인에게 틀어야 될때를 판단
					if( dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME ||
						dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACK ||
						dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACKED ||
						dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY )
					{
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_DurationSkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, HT_FALSE, 1 );
					}
					else if( dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME ||
							dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME_WITHENERGY ||
							dwSkillType == HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER )
					{
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_DurationSkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, HT_TRUE, 1 );
					}
					//	V3랑 따로 작업한것
					else
					{
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_DurationSkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, HT_TRUE, 1 );
					}

					//	듀레이션 타임(지속시간)을 구함
					g_pParamMgr->HT_bGetPCSkillDuration( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
					m_iOther_ApplySkillStartTime		= GetTickCount();
				}
			}
		}
	}

	if( m_iOther_DurationSkillEffectID )
	{
		HTdword dwPassTime = GetTickCount();
		if( dwPassTime >= (DWORD)(m_iOther_ApplySkillStartTime + m_iOther_ApplySkillContinueTime) )
		{
			g_pEngineHandler->HT_hrStopSFX( m_iOther_DurationSkillEffectID );
			m_iOther_DurationSkillEffectID = 0;
		}
	}
}

//	Animation Set Change Animation
HTvoid HTOtherObject::HT_vOtherObject_SetChangeAnimation( HTint loop, HTfloat fTime, DWORD dwSkillIndex )
{
	// bIsWeaponBack이 TRUE인 경우 현재 장착 중인 무기를 등에 붙이고 스킬 애니메이션을 시전해야 한다.
	HTint iItemIndex = m_iOther_WeaponItemID;
	HTbool	bEquip = HT_TRUE;
	DWORD dwSkillUseType = 0;

	HTint iShieldItem, iLeftItem;
	iShieldItem = m_pObjectInfo->Equip[3].snIndex ; iLeftItem = 0;
	if( g_pEngineHandler->HT_bIsShortSword( iShieldItem ) )
		iLeftItem = iShieldItem;	iShieldItem = 0;

	if( dwSkillIndex )
	{
		HTbool bIsWeaponBack = g_pEngineHandler->HT_bIsWeaponBack( dwSkillIndex );
		if( bIsWeaponBack )
		{
			g_pEngineHandler->HT_hrUnarmWeapon( m_iOtherModelID, m_iOther_TribeCode, m_iOther_WeaponItemID, iShieldItem, iLeftItem );
			m_bOther_IsWeaponArmed = HT_TRUE;
			iItemIndex = -1;
			bEquip = HT_FALSE;
		}
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );
	}
	else
	{
		//	무조건 등에 무기를 차고 애니매이션 해야될때
		if( m_iOther_AniResentState == CHARACTER_ANISTATE_IDL ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_SIT ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_SITDOWN ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_STANDUP ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_BOW ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_CHARGE ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_PROVOKE )
		{
			g_pEngineHandler->HT_hrUnarmWeapon( m_iOtherModelID, m_iOther_TribeCode, m_iOther_WeaponItemID, iShieldItem, iLeftItem );
			m_bOther_IsWeaponArmed = HT_TRUE;
			iItemIndex = -1;
			bEquip = HT_FALSE;
		}
	}

	//	안전지역에서만 등에 무기를 차야될때
	if( bEquip )
	{
		HTbool bSafeZoneSw = HT_FALSE;
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 ) )
			bSafeZoneSw = HT_TRUE;
	
		if( bSafeZoneSw )
		{
			g_pEngineHandler->HT_hrUnarmWeapon( m_iOtherModelID, m_iOther_TribeCode, m_iOther_WeaponItemID, iShieldItem, iLeftItem );
			m_bOther_IsWeaponArmed = HT_TRUE;
			iItemIndex = -1;
			bEquip = HT_FALSE;
		}
	}

	if( bEquip )
	{
		if ( m_iOther_WeaponItemID > 0 && m_bOther_IsWeaponArmed )
		{
			g_cEquipSystem->HT_EquipSys_Equip( m_iOtherModelID, m_iOther_TribeCode, m_iOther_WeaponItemID, m_pObjectInfo->Equip[3].snIndex, m_pObjectInfo->byHead );
			if( iShieldItem )
                g_cEquipSystem->HT_EquipSys_Equip( m_iOtherModelID, m_iOther_TribeCode, iShieldItem, 0, m_pObjectInfo->byHead );
			m_bOther_IsWeaponArmed = HT_FALSE;
		}
	}

	//	애니매이션 셋팅
	switch( m_iOther_AniResentState )
	{
		case CHARACTER_ANISTATE_STD :
			if( m_pObjectInfo->byTradeMode == 0 )
			{
				g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
					loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			}
			else
			{
				if( g_cSystem->HT_bSystem_GetShopModelMode() )
				{
					if( m_pObjectInfo->byTradeMode == 1 )
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2482, HT_ANISTATE_STD, loop );
					else
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2483, HT_ANISTATE_STD, loop );
				}
				else
				{
					g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
					loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
				}
			}
			break;
		case CHARACTER_ANISTATE_WLK :
			if( m_pObjectInfo->byTradeMode == 0 )
                g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
					loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			else
			{
				if( g_cSystem->HT_bSystem_GetShopModelMode() )
				{
					if( m_pObjectInfo->byTradeMode == 1 )
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2482, HT_ANISTATE_WLK, loop );
					else
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2483, HT_ANISTATE_WLK, loop );
				}
				else
				{
					g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
							loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
				}
			}
			break;
		case CHARACTER_ANISTATE_RUN :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_IDL :
			if( m_pObjectInfo->byTradeMode == 0 )
			{
				if ( HT_FAILED( g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
                				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex ) ) )
				{
					m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
					g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
							-1, m_pObjectInfo->byHead, m_iOther_WearItemID, 0.0f, iItemIndex );
				}
			}
			else
			{
				if( g_cSystem->HT_bSystem_GetShopModelMode() )
				{
					if( m_pObjectInfo->byTradeMode == 1 )
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2482, HT_ANISTATE_IDL, loop );
					else
						g_pEngineHandler->HT_hrChangeAnimation(  m_iOtherModelID, 2483, HT_ANISTATE_IDL, loop );
				}
				else
				{
					if ( HT_FAILED( g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
                				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex ) ) )
					{
						m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
						g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
								-1, m_pObjectInfo->byHead, m_iOther_WearItemID, 0.0f, iItemIndex );
					}
				}
			}
			break;
		case CHARACTER_ANISTATE_SIT :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_SITDOWN :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_HIT :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_DIE :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_STANDUP :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
		case CHARACTER_ANISTATE_MAGIC_DEFENCE :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_BOW	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_CHARGE	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_PROVOKE	:
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID, (HTdword)m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], 
				loop, m_pObjectInfo->byHead, m_iOther_WearItemID, fTime, iItemIndex );
			break;
		case CHARACTER_ANISTATE_NORMALATK :
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
			{
				m_iOther_AttackAniCount++;
				if( m_iOther_AttackAniCount > 3 )
					m_iOther_AttackAniCount = 1;
				g_pEngineHandler->HT_hrChangeAttackAnimation( m_iOtherModelID, (HTint)m_iOther_TribeCode, iItemIndex, 1, iLeftItem, m_pObjectInfo->byHead, m_iOther_WearItemID, m_iOther_AttackAniCount, fTime );
			}
			else
			{
				g_pEngineHandler->HT_hrChangeMonsterAttackAnimation( m_iOtherModelID, m_iOther_TribeCode, m_iOther_ApplySkillIndex, 1 );
			}
			break;
		case CHARACTER_ANISTATE_MOBHIT :
			g_pEngineHandler->HT_hrChangeAnimation( m_iOtherModelID,  m_iOther_TribeCode, (HT_ANIM_STATE)g_EtcAnmIndex[m_iOther_AniResentState], loop );
			break;
		case CHARACTER_ANISTATE_SKILLREADY :
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
			{
				if( HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_READY, (HTdword)m_iOther_TribeCode, 0, m_pObjectInfo->byHead ) ) )
					m_iOther_ApplySkillContinueTime = 0;
			}
			else
			{
                if( HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_READY, (HTint)m_iOther_TribeCode, iItemIndex, m_pObjectInfo->byHead ) ) )
					m_iOther_ApplySkillContinueTime = 0;
			}
			break;
		case CHARACTER_ANISTATE_SKILLCAST :
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
			{
				if( HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_CAST, (HTdword)m_iOther_TribeCode, 0, m_pObjectInfo->byHead ) ) )
					m_iOther_ApplySkillContinueTime = 0;
			}
			else
			{
            	if( HT_FAILED( g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_CAST, (HTint)m_iOther_TribeCode, iItemIndex, m_pObjectInfo->byHead ) ) )
					m_iOther_ApplySkillContinueTime = 0;
			}
			break;
		case CHARACTER_ANISTATE_SKILLACTIVATE :
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	액티브 스킬 지전중이면...
			{
                g_pEngineHandler->HT_hrChangeSkillActiveAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, (HTdword)m_iOther_TribeCode,  0, m_pObjectInfo->byHead );
			}
			else
				g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_ACTIVATE, (HTint)m_iOther_TribeCode, iItemIndex, m_pObjectInfo->byHead );
			break;
		case CHARACTER_ANISTATE_SKILLATK :
			g_pEngineHandler->HT_hrChangeSkillActionAnimation( m_iOtherModelID, dwSkillIndex, HT_SKILLANISEQ_ATTACK, (HTint)m_iOther_TribeCode, iItemIndex, m_pObjectInfo->byHead );
			break;
	}

	//	아이템 제련레벨
	this->HT_vOtherObject_SetAttachRefineEffect();
}
//	Animation Animation Check
HTvoid HTOtherObject::HT_vOtherObject_AnimationCheck()
{
	//	Death 소환 Check
	if( m_iOther_LiveIndex == OTEHRCHAR_STATE_DEATHMOTION ||
		m_iOther_LiveIndex == OTEHRCHAR_STATE_SUMMONS )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iOtherModelID );

	//	공격 애니매이션일때
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLATK )
	{
		//	캐릭터 공격 포인트에서 할일
	    if( sAnmState == HT_AS_ATTACK &&
			m_bOther_AtkptCheck == HT_TRUE )
		{
			m_bOther_AtkPtFromTimeSw = HT_FALSE;
			this->HT_vOtherObject_AttackPoint();
			return;
		}
	}

	//	캐스팅 애니매이션을 해야 될때
	//	캐스팅 동작이 스탑애니일때 계속들어오므로 못들어오게 처리
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
	{
		if( sAnmState == HT_AS_STOP )
		{
			//	Skill Cast Ani Start
			m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, m_iOther_ApplySkillIndex );
			//	이펙트가 켜져 있을때는 꺼주기
			if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
			//	캐스팅 이펙트 시작
			g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
			//if( m_iOther_ApplySkillEffectID == -1 )
			//	m_iOther_ApplySkillEffectID = 0;
			//	캐스팅 시작시간을 설정
			m_iOther_ApplySkillStartTime = GetTickCount();
			//	캐스팅 지속시간을 설정
			g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
			return;
		}
	}

	//	OtherChar가 죽었을때 처리
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_DIE )
	{
		if( sAnmState == HT_AS_STOP )
		{
			//	죽음 셋팅
			m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
			m_iOther_LiveDelayTime = GetTickCount();
			return;
		}
	}

	//	앉는 동작일때
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_SITDOWN )
	{
		if( sAnmState == HT_AS_STOP )
		{
			m_iOther_AniResentState = CHARACTER_ANISTATE_SIT;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
			return;
		}
	}

	//	Last Check
	if( sAnmState == HT_AS_STOP )
	{
		if( m_iOther_AniResentState == CHARACTER_ANISTATE_WLK ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_RUN || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_IDL || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_HIT || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_STANDUP || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_MAGIC_DEFENCE || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_MOBHIT || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_NORMALATK || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLACTIVATE || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLATK )
		{
			if( m_pObjectInfo->byTradeMode == 0 || 
				!g_cSystem->HT_bSystem_GetShopModelMode() )
			{
				m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
				this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );

				//	아이들 동작을 위해
				m_iOther_IdlTime = GetTickCount();
			}
			return;
		}
	}
}

//	Control AttackPointCheck From Time -> 보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
HTvoid HTOtherObject::HT_vOtherObject_ControlAttackPointCheckFromTime()
{
	//	죽음 셋팅
	if( m_iOther_LiveIndex == OTEHRCHAR_STATE_DEATHMOTION )
		return;

	if( m_bOther_AtkPtFromTimeSw )
	{
		HTint iPassTime = (HTint)GetTickCount();
		if( iPassTime > m_iOther_AtkptFromTimeStartTime + m_iOther_AtkptFromTimeDelay )
		{
			m_bOther_AtkPtFromTimeSw = HT_FALSE;
			for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
			{
				if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
				{
					if( m_iOther_TargetDamageHP[i] > 0 &&
						m_iOther_TargetHP[i] < g_cMainCharacter->HT_nMainChar_GetResentHP() )
					{
						this->HT_vOtherObject_AttackPoint();
					}
				}
			}
		}
	}
}

//	Move Control
//	Move Check
HTvoid HTOtherObject::HT_vOtherObject_MoveControl( HTfloat fElapsedTime )
{
	//	Error Check
	if( fElapsedTime < HT_EPSILON )
		return;

	//	Move Up/Down Control
	m_pOther_MoveSystem->HT_vOtherObjectMove_UpDownControl();

	if( m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE )
	{
		if( m_pOther_MoveSystem->m_byMoveState == OTHERCHARMOVE_GO )
		{
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemGo( fElapsedTime );
			if( HT_SUCCEED( m_pOther_MoveSystem->HT_hrOtherObjectMove_MoveSystemStopCheck() ) )
			{
				//	Yut Move End Point를 체크하여 값이 있으면 더 움직여 준다.
				if( m_iOther_EndPoint != 0 )
				{
					MSG_Action* info = NULL;
					info = new MSG_Action;
					info->TargetX = g_iYutMoveCellX[m_iOther_EndPoint];
					info->TargetY = g_iYutMoveCellZ[m_iOther_EndPoint];
					info->Speed = 6;
					m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
					HT_DELETE( info );
					m_iOther_EndPoint = 0;
				}
			}
		}
	}

	//	마지막으로 오브젝트를 맵에 갱신시켜 준다.
    g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
}
//	Move Rotate Control
HTvoid HTOtherObject::HT_vOtherObject_RotateControl( HTfloat fElapsedTime )
{
	//	밀려나기라면 Skip
	if( m_pOther_MoveSystem->m_snEffect == 6 )
		return;

	HTfloat fCharAngle = m_pOther_MoveSystem->HT_fOtherObjectMove_GetDirect();
	
	if( fCharAngle != m_fOther_ShowAngle )
	{
		//	1. 실재각을 향한 Display각의 진행방향을 구함
		HTfloat fAngleDifference = m_fOther_ShowAngle - fCharAngle;
		if( fAngleDifference > 0 )
		{
			if( fAngleDifference > HT_PI )
                m_iOther_ProgressAngle = 1;
			else
				m_iOther_ProgressAngle = -1;
		}
		else if( fAngleDifference < 0 )
		{
			if( fAngleDifference < -HT_PI )
                m_iOther_ProgressAngle = -1;
			else
				m_iOther_ProgressAngle = 1;
		}

		if( fAngleDifference < 0 ) fAngleDifference *= -1;

		HTfloat fMoveSpeed = (HTfloat)(m_pOther_MoveSystem->HT_fOtherObjectMove_GetCurSpeed()/5.0f);
		HTfloat fSpeed;
		fSpeed = ( HT_PI * (fElapsedTime) )*(1.5f+fMoveSpeed);

		//	2. 실재각으로 진행
		if( m_iOther_ProgressAngle == 1 )
		{
			m_fOther_ShowAngle += fSpeed;
			//	최대값을 넘어가면 최소값으로
			if( m_fOther_ShowAngle > HT_PIX2+HT_PI )
			{
				m_fOther_ShowAngle = HT_PI;
			}
		}
		else if( m_iOther_ProgressAngle == -1 )
		{
			m_fOther_ShowAngle -= fSpeed;
			//	최소값보다 작으면 최대값으로
			if( m_fOther_ShowAngle < HT_PI )
			{
				m_fOther_ShowAngle = HT_PIX2+HT_PI;
			}
		}

		//	초기화
		if( fAngleDifference <= fSpeed )
		{
			m_fOther_ShowAngle = fCharAngle;
		}

		g_pEngineHandler->HT_hrRotateObject( m_iOtherModelID, m_fOther_ShowAngle );
	}
}
//	Move Stand Control
HTvoid HTOtherObject::HT_vOtherObject_StandControl( HTfloat fElapsedTime )
{
	//	정지 상태일때
	if( m_pOther_MoveSystem->HT_fOtherObjectMove_GetCurSpeed() == 0.0f )
	{
		//	공격 받았을때 이동해서 때리는것 셋팅
		if( m_bOther_AttackMoveSw )
		{
			// 공격자를 향해 회전
			//if( m_vecOther_AttackTargetPos.x != 0 )
			{
				HTvector3 vecPos = m_vecOther_AttackTargetPos - m_vecOther_AttackSourcePos;
				HTfloat fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( fDirect );
			}

			m_bOther_AttackMoveSw = HT_FALSE;
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
			{
				if( m_iOther_ApplySkillIndex != 0 )
				{
					m_iOther_ApplySkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_iOther_ApplySkillIndex );
					if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTION )
					{
						m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
						this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
						HTint iTempFXID;
						g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_READY, m_iOtherModelID, HT_FALSE );
						//	공격 Type 셋팅
						m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_SKILL;

						//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
						m_bOther_AtkPtFromTimeSw = HT_TRUE;
						m_iOther_AtkptFromTimeDelay = 100;
						m_iOther_AtkptFromTimeStartTime = GetTickCount();
					}
					else if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTIVE )
					{
						m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
						this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
						//	캐스팅 시작시간
						m_iOther_ApplySkillStartTime = GetTickCount();
						//	캐스팅 지속시간
						g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
						//	이펙트가 켜져 있을때는 꺼주기
						if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
						//	캐스팅 이펙트 시작
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
						//if( m_iOther_ApplySkillEffectID == 0 )
						//	m_iOther_ApplySkillEffectID = -1;
						//	공격 Type 셋팅
						m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_NONE;
					}
				}
				else
				{
					//	캐릭터 애니매이션 셋팅
					m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
					//	공격 Type 셋팅
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_AUTOATTACK;

					//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
					m_bOther_AtkPtFromTimeSw = HT_TRUE;
					m_iOther_AtkptFromTimeDelay = 100;
					m_iOther_AtkptFromTimeStartTime = GetTickCount();
				}
			}
			else
			{
				//	공격 애니매이션 셋팅
				m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
				//	공격 Type 셋팅
				m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_AUTOATTACK;

				//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
				m_bOther_AtkPtFromTimeSw = HT_TRUE;
				g_pParamMgr->HT_bGetMonsterSkillCastingTime( m_iOther_ApplySkillIndex, &m_iOther_AtkptFromTimeDelay );
				m_iOther_AtkptFromTimeStartTime = GetTickCount();
			}
		}

		if( m_iOther_AniResentState == CHARACTER_ANISTATE_WLK || 
			m_iOther_AniResentState == CHARACTER_ANISTATE_RUN )
		{
			if( m_pObjectInfo->byTradeMode == 0 || 
				!g_cSystem->HT_bSystem_GetShopModelMode() )
			{
				//	캐릭터 애니매이션 셋팅
				m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
				this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );

				//-----아이들 동작을 위해-----//
				m_iOther_IdlTime = GetTickCount();
			}
		}
		else if( m_iOther_AniResentState == CHARACTER_ANISTATE_STD )
		{
			if( !g_bGamePlayMovieForGlobal )
			{
				HTint dwPassTime = GetTickCount();
				if( dwPassTime > (m_iOther_IdlTime + IDLE_PC_TIME) )
				{
					m_iOther_AniResentState = CHARACTER_ANISTATE_IDL;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
				}
			}
		}
	}
}

//	Attack
//	Attack Point
HTvoid HTOtherObject::HT_vOtherObject_AttackPoint()
{
	//	공격포인트
	m_bOther_AtkptCheck = HT_FALSE;

	//-----공격클래스 생성-----//
	m_oOther_AttackFactor->strAttackName = m_strOther_Name.HT_szGetString();
	m_oOther_AttackFactor->byTribe = m_iOther_TribeCode;
	m_oOther_AttackFactor->dwAttackKeyID = m_pObjectInfo->nID;
	m_oOther_AttackFactor->nCharModelID = m_iOtherModelID;
	m_oOther_AttackFactor->nAttackItemID = m_iOther_WeaponItemID;
	m_oOther_AttackFactor->nAttackSkillID = m_iOther_ApplySkillIndex;
	m_oOther_AttackFactor->byAttackSkillIDLevel = 1;
	m_oOther_AttackFactor->dwTargetKeyID = m_iOther_TargetKeyID[0];
	m_oOther_AttackFactor->nAttackType = m_iOther_AttackType;
	m_oOther_AttackFactor->vecSourcePos = m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();//m_vecOther_AttackSourcePos;
	m_oOther_AttackFactor->vecTargetPos = m_vecOther_AttackTargetPos;
	m_oOther_AttackFactor->fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), m_vecOther_AttackTargetPos - m_vecOther_AttackSourcePos ) + HT_PIX2;
	g_cAttackMgr->HT_vAttackMgr_Create( m_oOther_AttackFactor );

	//	Atack Atk Message
	g_imsi_button[5]++;
	this->HT_vOtherObject_AttackMessage();
}
//	Atack Atk Message
HTvoid HTOtherObject::HT_vOtherObject_AttackMessage()
{
	//	공격 Demage Count
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			HTbyte byAttacker = 1;
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )		byAttacker = 1;
			else														byAttacker = 2;

			//	메인캐릭터에 어팩션 적용
			g_cMainCharacter->HT_vMainCHar_SCP_SetAffections( m_iOther_TargetAffaction );

			CHTString strMsg, szMessage;
			if( m_byOther_TargetRes[i] == 2 )
			{
				g_cHitCountMgr->HT_vHitCountMgr_Create( byAttacker, m_byOther_TargetRes[i], 0, m_vecOther_AttackTargetPos, 0, HT_FALSE );
				// %s의 공격을 회피했습니다.
				if( g_pMessageMgr->HT_bGetMessage( eMsgAttackDodgeSuccess, &szMessage ) == true )
				{
					strMsg.HT_szFormat( szMessage.HT_szGetString(), m_strOther_Name.HT_szGetString() );
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
				}
			}
			else if( m_byOther_TargetRes[i] == 0 ||
					 m_byOther_TargetRes[i] == 1 )
			{
				if( m_iOther_TargetDamageHP[i] > 0 )
				{
					if( m_iOther_TargetDamageHP[1] > 0 )	g_cHitCountMgr->HT_vHitCountMgr_Create( byAttacker, m_byOther_TargetRes[i], m_iOther_TargetDamageHP[i], g_cMainCharacter->HT_vecGetPosition(), i, HT_TRUE );
					else									g_cHitCountMgr->HT_vHitCountMgr_Create( byAttacker, m_byOther_TargetRes[i], m_iOther_TargetDamageHP[i], g_cMainCharacter->HT_vecGetPosition(), i, HT_FALSE );

					//	Hit Message Set
					if( g_cMainCharacter->HT_vMainChar_GetCharLive() == HT_TRUE )
					{
						//	s(으)로부터 %s 데미지를 받았습니다.
						if( g_pMessageMgr->HT_bGetMessage( eMsgAttackReceiveDamage, &szMessage ) == true )
						{
							CHTString szParam;
							szParam.HT_szFormat("%d", m_iOther_TargetDamageHP[i] );
							strMsg.HT_szFormat( szMessage.HT_szGetString(), m_strOther_Name.HT_szGetString(), szParam.HT_szGetString() );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMsg );

						}
					}
					else
					{
						//eMsgLastDamageNotice
						//	마지막 데미지 표시
						CHTString szParam, strTemp;
						strTemp.HT_szFormat("%d", m_iOther_TargetDamageHP[i] );
						HT_g_Script_SetMessage( eMsgLastDamageNotice, &szParam, strTemp.HT_szGetString() );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szParam.HT_szGetString() );
					}
				}
				//	공격 대상의 HP
				if( m_iOther_TargetHP[i] != -1 )
				{
					if( m_iOther_TargetHP[i] != 0 )
					{
                        g_cMainCharacter->HT_nMainChar_SetCurHP( m_iOther_TargetHP[i] );
					}
					else
					{
						if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
							g_cMainCharacter->HT_nMainChar_SetCurHP( m_iOther_TargetHP[i] );
					}
				}
			}
		}
	}
}

//	Effect
//	Effect When Invade From OtherObject
HTvoid HTOtherObject::HT_vOtherObject_EffectAttack( HTint iSkillID, HTint iItemID, HTint iInvadeModelID, HTint iInvadeKeyID )
{
	if( m_iOther_LiveIndex != OTHERCHAR_STATE_LIVE )
		return;

	//	공격자의 KeyID
	m_iOther_InvadeKeyID = iInvadeKeyID;

	//	Impact Effect
	if( iSkillID == 0 )
	{
		g_pEngineHandler->HT_hrStartSFX( iItemID, iInvadeModelID, m_iOtherModelID );
	}
	else
	{
		//	상태에 걸려있을때는 타격 이펙트 뿌리지 않는다.
        g_pEngineHandler->HT_hrStartSFX( iSkillID, iInvadeModelID, m_iOtherModelID );
	}

	//	플리커
	g_pEngineHandler->HT_hrFlickerObject( m_iOtherModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	라이팅
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iOtherModelID, HT_FALSE );

	HTbyte bySkillType = 0;
	if( iSkillID )
        g_pParamMgr->HT_bGetPCSkillType( iSkillID, 1, &bySkillType );

	if( !bySkillType )
	{
		//	공격중이 아닐때만 맞는 액션
		if( m_iOther_AniResentState == CHARACTER_ANISTATE_STD ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_IDL ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_SIT )
		{
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
				m_iOther_AniResentState = CHARACTER_ANISTATE_HIT;
			else
				m_iOther_AniResentState = CHARACTER_ANISTATE_MOBHIT;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

			//	공격 받는것에 의해 Object가 멈춘다.
			m_bStopWhenInvadeSw = HT_TRUE;
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
		}
		else	// 맞는 에니메이션이 나오지 않는다면 맞는 소리라도 나야한다.
		{
			g_pEngineHandler->HT_hrPlayHitSound( m_pObjectInfo->snTribe, m_iOtherModelID );
		}
	}

	//-----아이들 동작을 위해-----//
	m_iOther_IdlTime = GetTickCount();
}
//	Effect Recive Active Skill Use From OtherObject
HTvoid HTOtherObject::HT_vOtherObject_EffectActiveSkillEffectOn( HTint iSkillIndex, HTbool bType, BYTE byLevel )
{
	//	캐스팅 시작시간을 설정
	m_iOther_ApplySkillStartTime = GetTickCount();
	//	캐스팅 지속시간을 설정
	g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
	//	이펙트가 켜져 있을때는 꺼주기
	if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
	//	StartFX
	g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, iSkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, bType, byLevel );
}
//	Effect When OtherObject Death
HTvoid HTOtherObject::HT_vOtherObject_WhenDeathEffect()
{
	//	이펙트꺼주기
	if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}
	
	m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
	this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

	// 죽는 애니메이션을 하는 동안은 그림자를 그리지 않는다.
	g_pEngineHandler->HT_hrShowShadow( m_iOtherModelID, HT_FALSE );
	//	정보 디스플레이 셋팅취소
	this->HT_vOtherObject_SetHideInfomation();
	//	죽을때의 딜레이 시간을 위해
	m_iOther_LiveDelayTime		= GetTickCount();
	//	몬스터 죽을때 몬스터의 혼이 빠져나가기
	HTint imsiID;
	g_pEngineHandler->HT_hrStartSFX( &imsiID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE );
	// 죽고나서 시체가 완전히 사라질때까지는 픽킹이 되지 않아야 한다.
	g_pEngineHandler->HT_hrDontClickIt( m_iOtherModelID );

	//	Get Source
	m_vecOther_AttackSourcePos = m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
	m_vecOther_AttackSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackSourcePos.x, m_vecOther_AttackSourcePos.z );
	//	Get Target
	m_vecOther_AttackTargetPos = HTvector3( 0, 0, 0 );

	//	튜토리얼 시스템을 위함
	HTbyte byInvadeType = 0;
	if( m_iOther_InvadeKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if (g_cTutorialSystem)
		{
			if (_DIALOG_TUTORIALWND_10==g_cTutorialSystem->HT_iGetTutorialStep())
				g_cTutorialSystem->HT_vAddTutorialStep( TUTORIAL_STEP_GETITEM );
		}
	}

	//	몬스터 죽을때 캐릭터쪽으로 프라나 이펙트 빨려들어가기
	m_oOther_AttackFactor->strAttackName = m_strOther_Name.HT_szGetString();
	m_oOther_AttackFactor->byTribe = 0x01;
	m_oOther_AttackFactor->dwAttackKeyID = m_pObjectInfo->nID;
	m_oOther_AttackFactor->dwTargetKeyID = m_iOther_InvadeKeyID;
    m_oOther_AttackFactor->nAttackType = MAINCHAR_ATTACKTYPE_PRANA;
	m_oOther_AttackFactor->nCharModelID = m_iOtherModelID;
	m_oOther_AttackFactor->vecSourcePos = m_vecOther_AttackSourcePos;
	m_oOther_AttackFactor->vecTargetPos = m_vecOther_AttackTargetPos;
    m_oOther_AttackFactor->fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), m_vecOther_AttackTargetPos - m_vecOther_AttackSourcePos ) + HT_PIX2;
	m_oOther_AttackFactor->nAttackItemID = m_iOther_WeaponItemID;
	m_oOther_AttackFactor->nAttackSkillID = g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe);
    m_oOther_AttackFactor->byAttackSkillIDLevel = 1;
	g_cAttackMgr->HT_vAttackMgr_Create( m_oOther_AttackFactor );

	//	프라나 업 이펙트 틀어준다
	//HTint nTempID;
	//g_pEngineHandler->HT_hrStartSFX( &nTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), HT_SFX_WHEN_IMPACT, m_iOtherModelID, HT_FALSE );
}
//	Effect EffectStunSleepHoldOn
HTvoid HTOtherObject::HT_vOtherObject_EffectFaintingstateOn()
{
	if( m_iOther_AniResentState != CHARACTER_ANISTATE_STD )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
	}
	m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
}
//	Effect EffectSetModelColor
HTvoid HTOtherObject::HT_vOtherObject_EffectSetModelColor( HTfloat r, HTfloat g, HTfloat b, HTfloat fTime )
{
	//	플리커
    g_pEngineHandler->HT_hrFlickerObject( m_iOtherModelID, HT_COLOR( r, g, b, 1.0f ), fTime );
}

//	Setting
//	Setting Set Item 
HTvoid HTOtherObject::HT_vOtherObject_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info )
{
	if( info.snIndex != 0 )
	{
		//	장착
		HTdword iNormalIndex, iLeftIndex;
		iNormalIndex = info.snIndex;	iLeftIndex = 0;
        if( byPart == eTNEqu_Shield )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalIndex ) )
			{	iLeftIndex = iNormalIndex;	iNormalIndex = 0;		}
		}
        g_cEquipSystem->HT_EquipSys_Equip( m_iOtherModelID, m_iOther_TribeCode, iNormalIndex, iLeftIndex, m_pObjectInfo->byHead );

		//	장착 정보르 저장하고
		m_iOther_EquipItem[byPart] = info.snIndex;
		m_byOther_MainRef[byPart] = info.byMainRef;
		m_byOther_RefineLevel[byPart] = info.byRefineLevel;

		if ( HT_IS_ITEM_WEAR( info.snIndex ) )
		{
			m_iOther_WearItemID	= info.snIndex;
		}
		else if ( HT_IS_ITEM_WEAPON( info.snIndex ) )
		{
			m_iOther_WeaponItemID = info.snIndex;
		}

		//	장착 파트가 무기라면 제련 효과를 붙인다.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			//	메인 제련이 되어 있는 (무기) 아이템의 FX 설정
			if( info.byRefineLevel > 0 )
				g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherModelID, info.snIndex, info.byRefineLevel );
			
			// 속성 제련 되어 있는 (무기) 아이템의 경우
			if( info.byRefineLevel > 0 )
			{
				// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
				g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherModelID, info.snIndex, (HTESubRefineType)info.byMainRef, info.byRefineLevel );
			}
		}
	}
	else
	{
        //	탈착
		HTint iNormalItem, iLeftItem;
		iNormalItem = m_iOther_EquipItem[byPart], iLeftItem = 0;
		if( byPart == eTNEqu_Shield )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalItem ) )
			{	iLeftItem = iNormalItem;  iNormalItem = 0;		}
		}
		g_cEquipSystem->HT_EquipSys_UnEquip( m_iOtherModelID, m_iOther_TribeCode, iNormalItem, iLeftItem, m_pObjectInfo->byHead );
		//	탈착 정보르 저장하고
		m_iOther_EquipItem[byPart] = 0;
		m_byOther_MainRef[byPart] = 0;
		m_byOther_RefineLevel[byPart] = 0;

		if( byPart == eTNEqu_OneHandWeapon || byPart == eTNEqu_TwoHandWeapon )
			m_iOther_WeaponItemID = -1;
		else if( byPart == eTNEqu_Armor )
			m_iOther_WearItemID	= -1;

		//	탈착 파트가 무기라면 제련 효과를 붙인다.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			// 제련된 아이템의 FX 없애기
			// 메인 제련
			g_pEngineHandler->HT_hrDetachItemMainRefineEffect( m_iOtherModelID, info.snIndex );
			// 속성 제련
			g_pEngineHandler->HT_hrDetachItemSubRefineEffect( m_iOtherModelID, info.snIndex );
		}
	}

	if ( m_iOther_AniResentState == CHARACTER_ANISTATE_STD ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_SIT ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_RUN ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_WLK )
	{
		//	캐릭터 애니매이션 셋팅
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
	}

	//	조교모자를 착용했는지 분석
	if( m_iOther_EquipItem[1] == ITEMINDEX_ASSISTANTHAT )
		m_bOther_AssistantSw = HT_TRUE;
	else
		m_bOther_AssistantSw = HT_FALSE;
}
//	Setting Set Guild Mark ID
HTvoid HTOtherObject::HT_vOtherObject_SetGuildMarkID( HTint iGuildMarkID )
{
	m_pObjectInfo->dwGuildMark = iGuildMarkID;
}
//	Setting Show Guild Mark
HTvoid HTOtherObject::HT_vOtherObject_SetGuildMarkOn()
{
	if( m_pObjectInfo->dwGuildMark )
	{
		 g_pEngineHandler->HT_hrAttachGuildMark( m_iOtherModelID, m_pObjectInfo->dwGuildMark );
	}
}
//	Setting Hide Guild Mark
HTvoid HTOtherObject::HT_vOtherObject_SetGuildMarkOff()
{
	if( m_pObjectInfo->dwGuildMark > 0 )
        g_pEngineHandler->HT_hrDestroyGuildMark( m_iOtherModelID );
}
//	Setting Set Trimuriti ID
HTvoid HTOtherObject::HT_vOtherObject_SetSetTrimuritiID( BYTE TrimuritiID )
{
	m_pObjectInfo->byTrimuriti = TrimuritiID;
}
//	Setting Show Trimuriti Mark
HTvoid HTOtherObject::HT_vOtherObject_SetTrimuritiMarkOn()
{
	if( g_bTrimuritiShow )
	{
		switch( m_pObjectInfo->byTrimuriti )
		{
			case 1 :
				g_pEngineHandler->HT_hrAttachGodMark( m_iOtherModelID , m_iOther_TribeCode, HT_GODTYPE_BRAHMA, 1 );
				break;
			case 2 :
				g_pEngineHandler->HT_hrAttachGodMark( m_iOtherModelID , m_iOther_TribeCode, HT_GODTYPE_VISUNU, 1 );
				break;
			case 4 :
				g_pEngineHandler->HT_hrAttachGodMark( m_iOtherModelID , m_iOther_TribeCode, HT_GODTYPE_SIVA, 1 );
				break;
		}
	}
}
//	Setting Hide Trimuriti Mark
HTvoid HTOtherObject::HT_vOtherObject_SetTrimuritiMarkOff()
{
	g_pEngineHandler->HT_hrDetachGodMark( m_iOtherModelID );
}
//	Setting HP
HTvoid HTOtherObject::HT_iOtherObject_SetHPCheck( HTint iHP )
{
	m_pObjectInfo->nCurHP = iHP;
}
//	Setting Show Infomation
HTvoid HTOtherObject::HT_vOtherObject_SetShowInfomation( HTbool bAttack )
{
	//	방송촬영을 위해 몬스터 타겥팅 애니매이션이 안보이게 하기 위해
	if( g_bGamePlayMovieForGlobal )
		return;

	m_bOther_InfoSw = HT_TRUE;

	if( m_iTargettingEffectID )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iTargettingEffectID );
		m_iTargettingEffectID = 0;
	}

    if( m_iTargettingEffectID == 0 )
	{
		if (bAttack)
			g_pEngineHandler->HT_hrStartSFX( &m_iTargettingEffectID, HT_FX_MONSTERATTACK, m_iOtherModelID, HT_TRUE );
		else
			g_pEngineHandler->HT_hrStartSFX( &m_iTargettingEffectID, HT_FX_MONSTERTARGETING, m_iOtherModelID, HT_TRUE );
	}
}
//	Setting Hide Infomation
HTvoid HTOtherObject::HT_vOtherObject_SetHideInfomation()
{
	m_bOther_InfoSw = HT_FALSE;

	if( m_iTargettingEffectID != 0 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_iTargettingEffectID );
		m_iTargettingEffectID = 0;
	}
}
//	Setting Party Join and Disband
HTvoid HTOtherObject::HT_vOtherObject_SetPartyJoineDisband( BYTE byParty )
{
	m_byOther_PartyMember = byParty;
}
//	Setting Model Hide
HTvoid HTOtherObject::HT_vOtherObject_SetModelHide( HTbool bType )
{
	g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, bType );
#ifdef GM_CHAR_HIDE
	if( m_iOther_TribeCode == 9 )
		g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );
#endif
}
//	Setting Affections
HTvoid HTOtherObject::HT_vOtherObject_SetAffections( __int64  iAffections )
{
	m_pObjectInfo->iAffections = iAffections;
	//	GM일때 투명 체크
	if( m_pObjectInfo->byGMStatus == 2 )
		m_pObjectInfo->iAffections = iAffections | 0x00000020;

	//	Affections Fx On/Off
	HTdword dwFXID = g_pEngineHandler->HT_dwGetAffectionFXID( iAffections, m_pObjectInfo->iAffections );
    //if ( iAffections == eTNVSAfn_MoveSpeed140R ) dwFXID = 1010090; //fors_debug 殮쌈립令 劤녁곪
	if( dwFXID == 0 )
	{
		if( m_iOther_FXAffections != -1 )
		{
			g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
			m_iOther_FXAffections = -1;
		}
	}
	else
	{
		if( m_iOther_FXAffections != -1 )
			g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );

		if( g_iInationalType == INATIONALTYPE_JAPEN )
		{
			g_pEngineHandler->HT_hrStartSFX( &m_iOther_FXAffections, dwFXID, m_iOtherModelID, HT_TRUE );
		}
		else
		{
			if( !(iAffections&eTNVSAfn_MagicShield) &&  !(iAffections&eTNVSAfn_EnhancedMagicShield) ) //fors_debug 침제뜀宮밑 eTNVSAfn_EnhancedMagicShield
			{
				g_pEngineHandler->HT_hrStartSFX( &m_iOther_FXAffections, dwFXID, m_iOtherModelID, HT_TRUE );
			}
		}
	}
    
	//	은신 체크
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
	{
		//	WizardEyesSw Check
		if( !m_bOther_MainCharWizardEyesSw )
		{
			//	은신스킬이 쓰였다면 선택되어진것 전부 풀어준다.
			this->HT_vOtherObject_SetHideInfomation();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
			//	현재 메인캐릭터가 공격하는 캐릭터가 자신이면 공격취소
			if( g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID() == m_pObjectInfo->nID )
                g_cMainCharacter->HT_vMainChar_SetAttackCancel( 25 );
			this->HT_vOtherObject_SetModelHide( HT_FALSE );
			//	은신만 활성화되고 다른모든것들은 사라지게 처리
			m_pObjectInfo->iAffections = eTNVSAfn_Invisible;
		}
	}
	else
	{
		this->HT_vOtherObject_SetModelHide( HT_TRUE );
	}

	//	정지상태
	//if( m_pObjectInfo->iAffections & eTNVSAfn_Stun ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Sleep ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Hold ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Hold2 )
	//	this->HT_vOtherObject_EffectFaintingstateOn();

	//	캐릭터 색 관련
    if( m_pObjectInfo->iAffections & eTNVSAfn_Fire )
	{
		this->HT_vOtherObject_EffectSetModelColor( 1.0f, 1.0f, 0.0f, 2.0f );	//	노랑
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Cold )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.0f, 1.0f, 1.0f, 2.0f );	//	청록
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Lightning )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.9f, 0.5f, 0.0f, 2.0f );	//	연한 청록
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Poison )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.0f, 1.0f, 0.0f, 2.0f );	//	녹색
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_ProtectFromPK )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.3f, 1.0f, 0.3f, 2.0f );	//	녹색
	}

	//	타켙팅 다시 체크
	this->HT_vOtherObject_SetTargetting();
}
//	Setting TradeMode
HTvoid HTOtherObject::HT_vOtherObject_SetTradeMode( MSG_MobStatus* info )
{
	//	Mode Save
	m_pObjectInfo->byTradeMode = info->byTradeMode;
	strncpy( m_pObjectInfo->szTrade, info->szTrade, SZTRADE_LENGTH );

	if( !g_cSystem->HT_bSystem_GetShopModelMode() )
	{
		//	0:상거래안함
		if( info->byTradeMode == HT_STORE_MODE_END )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_STANDUP;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
		//	1:상거래함
		else if( info->byTradeMode == HT_STORE_MODE_START ||
				 info->byTradeMode == HT_STORE_MODE_START+1 )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
	}
	else
	{
		//	오브젝트 모델 출력여부 판단하여 모델 생성
		if( m_bOther_ShowObject )
			this->HT_vOtherObject_CreateModel();
	}
}
//	Setting MyGuildName
HTvoid HTOtherObject::HT_vOtherObject_SetMyGuildCheck( CHTString strGuildName )
{
	//	Guild Member
	CHTString strMainCharGuildName = g_cGuildSystem->HT_strGuild_GetGuildName();
	if( strMainCharGuildName.HT_iStringCompare( strGuildName.HT_szGetString() ) == 0 )
		m_bOther_MyGuildMemberSw = HT_TRUE;
}
//	Setting MainCharWizardEyesSw
HTvoid HTOtherObject::HT_vOtherObject_SetMainCharWizardEyes( HTbool bTrue )
{
	//	WizardEyesSw
	m_bOther_MainCharWizardEyesSw = bTrue;

	if( m_bOther_MainCharWizardEyesSw )
	{
		//	지금 상태가 투명 상태라면 보이게 한다.
		if( (m_pObjectInfo->iAffections & eTNVSAfn_Invisible) != 0 &&
			(m_pObjectInfo->byGMStatus & 0x02) == 0 )
            this->HT_vOtherObject_SetModelHide( HT_TRUE );
	}
	else
	{
		//	지금 상태가 투명 상태라면 다시 안보이게 한다.
		if( (m_pObjectInfo->iAffections & eTNVSAfn_Invisible ) != 0 )
            this->HT_vOtherObject_SetModelHide( HT_FALSE );
	}

	//	타켙팅 다시 체크
	this->HT_vOtherObject_SetTargetting();
}
//	아이템 제련레벨
HTvoid HTOtherObject::HT_vOtherObject_SetAttachRefineEffect( )
{
	//	몹일때는 스킵
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
		return;

	//	장착 파트가 무기라면 제련 효과를 붙인다.
	if( m_iOther_EquipItem[eTNEqu_OneHandWeapon] > 0 )
	{
		//	메인 제련이 되어 있는 (무기) 아이템의 FX 설정
		if( m_byOther_RefineLevel[eTNEqu_OneHandWeapon] > 0 )
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherModelID, m_iOther_EquipItem[eTNEqu_OneHandWeapon], m_byOther_RefineLevel[eTNEqu_OneHandWeapon] );
		
		// 속성 제련 되어 있는 (무기) 아이템의 경우
		if( m_byOther_RefineLevel[eTNEqu_OneHandWeapon] > 0 )
		{
			// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
			g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherModelID, m_iOther_EquipItem[eTNEqu_OneHandWeapon], (HTESubRefineType)m_byOther_MainRef[eTNEqu_OneHandWeapon], m_byOther_RefineLevel[eTNEqu_OneHandWeapon] );
		}
	}
}
//	Setting Targetting
//	1. 캐릭터 생성시점에서 호출
//	2. Msg_set_zone_setting에서 호출
//	3. Msg_chage_trimuriti에서 호출
//	4. MSG_GuildUpdate 와 Msg_StrongHoldUpdate에서 호출
//	5. PK Button눌렀을때 체크
//	6. 먼거리를 이동해 왔을때 (워프, 보정)
//	7. 파티 됐을때 지정
HTvoid HTOtherObject::HT_vOtherObject_SetTargetting()
{
	HTint iMyStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();
	CHTString strMyGuild = g_cGuildSystem->HT_strGuild_GetGuildName();
	CHTString strAshiram1 = g_cGuildSystem->HT_strGuild_AlliedGuildName(0);
	BOOL bPKButton = g_pMainBar->HT_bGetPKButton();

	//	최초 False로 지
	m_bOhter_Targetting = HT_FALSE;

	//	GM이면 무조건 타겥팅 할수 없다.
	if( m_iOther_TribeCode == 9 )
        return;

	//	투명인지 체크
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
	{
		//	내가 위자드아이를 가지고 있지 않으면 타겥팅할수 없다.
		if( !m_bOther_MainCharWizardEyesSw )
			return;
	}

	//	몹이면 아래조건을 체크하고 해당하지 않으면 전부 타겥팅 가능
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
	{
		//	주신전 지역인면 다른 주신이면 공격 가능
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti == m_pObjectInfo->byTrimuriti )
				return;
		}
		//	요새전 지역이면 자신의 경비병을 체크
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			//	자신의 경비병을 체크
			if( (iMyStrongGuild==0 && m_pObjectInfo->byTrimuriti==14 ) ||
				(iMyStrongGuild==1 && m_pObjectInfo->byTrimuriti==15 ) ||
				(iMyStrongGuild==2 && m_pObjectInfo->byTrimuriti==16 ) ||
				(iMyStrongGuild==3 && m_pObjectInfo->byTrimuriti==17 ) )
				return;
		}
		else if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
		{
			if( m_pObjectInfo->byClan == 10 ||
				g_cMainCharacter->HT_byMainChar_GetClanValue() == m_pObjectInfo->byClan )
				return;
		}
		//	타켙팅 되지 말아야 될 몹 아이디
		if( m_iOther_TribeCode>=2850 && m_iOther_TribeCode<=2899 )
			return;
		
		//	이제 타겥팅 가능
		m_bOhter_Targetting = HT_TRUE;
		return;
	}

	//	주신전, 요새전 지역이 아니고 존셋팅이 0인경우
	if( ( HT_FAILED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) && HT_FAILED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) ) &&
		g_snResentZoneSiege == 0 )
	{
		//	PK Button 이 눌러져 있고 20레벨 이상일때 그리고 파티원이 아닐때만 타겥팅 가능하다.
		if( bPKButton == TRUE && 
			m_pObjectInfo->byLevel >= 20 &&
			g_cStatus->HT_byGetLevel() >= 20 &&
			m_byOther_PartyMember != 0x02 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}

		//	결투 모드이며 결투 대상의 TargetKeyID 가 같으면 타겥팅 가능하다.
		if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat && 
			g_pDuelSystem->HT_iDuel_GetDuelCharKeyID() == m_pObjectInfo->nID )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	주신전 지역이면
	else if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		//	나와 주신이 같지 않으면 타겥팅 가능
		if( g_oMainCharacterInfo.byTrimuriti != m_pObjectInfo->byTrimuriti )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	요새전 지역이면
	else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		HTPoint pPt2 = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( (pPt.x>=285 && pPt.x<=345 &&	pPt.y>=677 && pPt.y<=736) ||
			(pPt2.x>=285 && pPt2.x<=345 && pPt2.y>=677 && pPt2.y<=736) )
		{
			//	다룬 파티원일때 타겥팅 가능
			if( m_byOther_PartyMember != 0x02 )
			{
				m_bOhter_Targetting = HT_TRUE;
				return;
			}
		}
		//	아쉬람이 없으면 공격 가능
		else if( strlen(m_pObjectInfo->szGuild) == 0 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
		//	아쉬람이 있으면
		else
		{
			//	타 길드 체크
			if( strMyGuild.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 &&
				strAshiram1.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 )
			{
				m_bOhter_Targetting = HT_TRUE;
				return;
			}
		}
	}
	//	Zone Setting 1일때 
	else if( g_snResentZoneSiege == 1 )
	{
		//	이 때(공성전)는 주신이 다르면 전부 적이다.
		if( g_cMainCharacter->HT_byMainChar_GetClanValue() != m_pObjectInfo->byClan )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	Zone Setting 0일때 
	else if( g_snResentZoneSiege == 0 )
	{
		//	PK Button 이 눌러져 있고 20레벨 이상일때 그리고 파티원이 아닐때만 타겥팅 가능하다.
		if( bPKButton == TRUE && 
			m_pObjectInfo->byLevel >= 20 &&
			g_cStatus->HT_byGetLevel() >= 20 &&
			m_byOther_PartyMember != 0x02 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}

		//	결투 모드이며 결투 대상의 TargetKeyID 가 같으면 타겥팅 가능하다.
		if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat && 
			g_pDuelSystem->HT_iDuel_GetDuelCharKeyID() == m_pObjectInfo->nID )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
}
//	Setting Collison
HTvoid HTOtherObject::HT_vOtherObject_SetCollison()
{
	//	문이랑은 무조건 충돌 체크
	if( HT_SUCCEED( HT_IS_MOBGATE( m_pObjectInfo->snTribe ) ) )
	{
		m_bOther_CollisonCheck = HT_TRUE;
	}
}

//	Network
//	Network	LevelUp Brodcast
HTvoid HTOtherObject::HT_vOtherObject_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CHAKRAUPGRADE, m_iOtherModelID, HT_FALSE );
}
//	Network	GM의 투명모드를 설정 또는 해제를 요청한다를 알린다
HTvoid HTOtherObject::HT_vOtherObject_NetworkGMMode_Notify( BYTE byGMMode )
{
	m_pObjectInfo->byGMStatus = byGMMode;
	if( m_pObjectInfo->byGMStatus & 0x02 )
		this->HT_vOtherObject_SetModelHide( HT_FALSE );
	else
		this->HT_vOtherObject_SetModelHide( HT_TRUE );
}
//	Network	Recive OtherObjct Move Message
HTvoid HTOtherObject::HT_vOtherObject_NetworkAction( MSG_Action* info )
{
	//	공격 받는것에 의해 Object가 멈춘다.
	m_bStopWhenInvadeSw = HT_FALSE;
	m_iOther_ActionEffect = info->Effect;

	HTfloat fMoveDistance;
	//	앉기, 서기, 걷기, 뛰기 등의 액션일 때 너무 멀리 떨어져 있다면 바로 워프 시켜 버린다.
	if( info->Effect == 0 ||
		info->Effect == 1 ||
		info->Effect == 2 ||
		info->Effect == 3 )
	{
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		fMoveDistance = (float)sqrt( double( (pPt.x - info->TargetX) * (pPt.x - info->TargetX) ) 
									+ double( (pPt.y - info->TargetY) * (pPt.y - info->TargetY) ) );
		if( fMoveDistance > 20 )
		{
			//	Setting Targetting
			this->HT_vOtherObject_SetTargetting();

			//-----디버깅 테스트를 위하여-----//
			g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("이동자 위치보정 ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
			if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			//	OtherChar 위치 셋팅
			HTvector3 vecPos;
			HT_CELL_COORD crdCell;
			crdCell.x = info->TargetX;
			crdCell.y = info->TargetY;
			g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
			m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecPos );
			g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
			return;
		}		
	}

	//	sit
	if( info->Effect == 0 )
	{
		//	현재 위치와 목표 위치를 비교 목표위치에 도착못했으면 이동
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
		else
		{
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
		}
	}
	//	Stand
	else if( info->Effect == 1 )
	{
		//	현재 위치와 목표 위치를 비교 목표위치에 도착못했으면 이동
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	캐릭터의 앉아있거나 앉기 동작할때만 서기 동작 틀어준다.
			if( m_iOther_AniResentState == CHARACTER_ANISTATE_SIT || m_iOther_AniResentState == CHARACTER_ANISTATE_SITDOWN )
				m_iOther_AniResentState = CHARACTER_ANISTATE_STANDUP;
			else
				m_iOther_AniResentState = CHARACTER_ANISTATE_STD;

			//	캐릭터 애니매이션 셋팅
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

			//-----아이들 동작을 위해-----//
			m_iOther_IdlTime = GetTickCount();
		}
		else
		{
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
		}

		//	Object 방향
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( (HTfloat)info->Direction/100 );
	}
	//	Walk
	else if( info->Effect == 2 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_WLK;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		if( fMoveDistance > 10 )
			info->Speed += 2;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}
	//	Run
	else if( info->Effect == 3 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		if( fMoveDistance > 10 )
			info->Speed += 2;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}
	//	워프
	else if( info->Effect == 5 )
	{
		//	Setting Targetting
		this->HT_vOtherObject_SetTargetting();

		//	목표셀 계산
		HTvector3 vecTargetPos;
		HT_CELL_COORD crdCell;
		crdCell.x = info->TargetX;
		crdCell.y = info->TargetY;
		g_pEngineHandler->HT_CELL_TO_3DCOORD( vecTargetPos, crdCell );
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecTargetPos );

		//	캐릭터 애니매이션 셋팅
		m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );

		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("오브젝트 워프 ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	knock-back
	else if( info->Effect == 6 )
	{
		if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
			m_iOther_AniResentState = CHARACTER_ANISTATE_HIT;
		else
			m_iOther_AniResentState = CHARACTER_ANISTATE_MOBHIT;
		//	캐릭터 애니매이션 셋팅
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		info->Speed = 10;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );

		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("오브젝트 낙백 ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	Run
	else if( info->Effect == 7 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_STD )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}
	//	도발
	else if( info->Effect == 8 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_PROVOKE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	인사
	else if( info->Effect == 9 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_BOW;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	돌격
	else if( info->Effect == 10 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_CHARGE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	대쉬
	else if( info->Effect == 11 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		info->Speed = 40;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}

	//----------캐스트 스킬 쥐소---------//
	if( m_iOther_ApplySkillEffectID != -1 )
	{
		//	이펙트를 정지 시키고
		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
		m_iOther_ApplySkillEffectID = -1;
	}
}
//	Network Apply Skill Brodcast
HTvoid HTOtherObject::HT_vOtherObject_NetworkApplySkillBroadcast( S_MSG_ATTACK_OTHERMOB info )
{
	HTint i;

	//	공격포인트 Check
	HTbool bAtkptCheck = HT_FALSE;
	if( m_bOther_AtkptCheck == HT_FALSE )
	{
		m_bOther_AtkptCheck = HT_TRUE;
		if( info.snRes != -1 )
			bAtkptCheck = HT_TRUE;
	}
	//	Object HP
	m_pObjectInfo->nCurHP = info.iCasterHP;
	//	스킬 관련 설정_ID, Level
    m_iOther_ApplySkillIndex = info.iSkillID;
	//	Source의 좌표
	m_vecOther_AttackSourcePos = m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
	m_vecOther_AttackSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackSourcePos.x, m_vecOther_AttackSourcePos.z );
	//	Target의 좌표
	m_vecOther_AttackTargetPos = info.vecTargetPos;
	m_vecOther_AttackTargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackTargetPos.x, m_vecOther_AttackTargetPos.z );
	// 공격자를 향해 회전
	HTvector3 vecPos = m_vecOther_AttackTargetPos - m_vecOther_AttackSourcePos;
	HTfloat fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( fDirect );

	//	스킬 속성 적용
	if( info.snRes != -1 )
        m_iOther_TargetAffaction = info.krgTarget[0].iAffection;
	//	스킬 속성 적용
	CHTString strTemp;
	strTemp.HT_szFormat( "Affection:%x\n", m_iOther_TargetAffaction );
	HT_g_vLogFile( strTemp.HT_szGetString() );
	//	공격 Demage Count Setting
	for( i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
		//	판정
		m_byOther_TargetRes[i] = info.krgTarget[i].byRes;
		//	공격받은 대상의 KeyID 0이면 전부 초기화처리
		if( info.krgTarget[i].snKeyID == 0 )
		{
			//	공격 Demage Count
			m_iOther_TargetKeyID[i] = -1;
			m_iOther_TargetDamageHP[i] = -1;
			m_iOther_TargetHP[i] = -1;
		}
		else
		{
			m_iOther_TargetKeyID[i] = info.krgTarget[i].snKeyID;
			//	Setting Demage
			if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
			{
				if( info.krgTarget[i].iDamage > 0 )
				{
					m_iOther_TargetDamageHP[i] = info.krgTarget[i].iDamage;
					m_iOther_TargetHP[i] = info.krgTarget[i].iHP;
				}
				if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
				{
					g_cGameSystem->HT_vGameSystem_SetKillerName( m_strOther_Name.HT_szGetString() );
					//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
					m_bOther_AtkPtFromTimeSw = HT_TRUE;
					g_pParamMgr->HT_bGetMonsterSkillCastingTime( m_iOther_ApplySkillIndex, &m_iOther_AtkptFromTimeDelay );
					m_iOther_AtkptFromTimeStartTime = GetTickCount();
				}
			}
			else
			{
				if( info.snRes != -1 )
				{
					if( info.krgTarget[i].iDamage > 0 )
					{
						m_iOther_TargetDamageHP[i] = info.krgTarget[i].iDamage;
						m_iOther_TargetHP[i] = info.krgTarget[i].iHP;
					}
					if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
					{
						g_cGameSystem->HT_vGameSystem_SetKillerName( m_strOther_Name.HT_szGetString() );
						//	보이지 않은 몬스터는 애니매이션 포인트가 날아오지 않기 때문에 시간으로 체크해야한다.
						m_bOther_AtkPtFromTimeSw = HT_TRUE;
						m_iOther_AtkptFromTimeDelay = 100;
						m_iOther_AtkptFromTimeStartTime = GetTickCount();
					}

					////	공격 포인트가 수행된 상태라면n.n
					//if( bAtkptCheck )
					//{
					//	//	Atack Atk Message
					//	this->HT_vOtherObject_AttackMessage();
					//}
				}
				else
				{
					//	공격 Demage Count
					m_iOther_TargetDamageHP[i] = -1;
					m_iOther_TargetHP[i] = -1;
					//m_iOther_TargetAffaction = 0;
				}
				//	나의스킬 셋팅
				if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
				{
					if( info.iSkillID!=0 && info.dwDurationTime!=0 )
					{
						g_pMainBar->HT_vMainBar_SetMySkill( info.iSkillID, 2, info.snSkillLevel );
					}
				}
			}
		}
	}

	////	공격 포인트가 수행된 상태라면n.n
	//if( bAtkptCheck )
	//{
	//	//	Atack Atk Message
	//	this->HT_vOtherObject_AttackMessage();
	//}

	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Unit_Skill_Target %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
	//	 m_iOther_TargetDamageHP[0], m_iOther_TargetDamageHP[1], m_iOther_TargetDamageHP[2], m_iOther_TargetDamageHP[3],
	//	 m_iOther_TargetDamageHP[4], m_iOther_TargetDamageHP[5], m_iOther_TargetDamageHP[6], m_iOther_TargetDamageHP[7],
	//	 m_iOther_TargetDamageHP[8], m_iOther_TargetDamageHP[9], m_iOther_TargetDamageHP[10], m_iOther_TargetDamageHP[11],
	//	 m_iOther_TargetDamageHP[12], m_iOther_TargetDamageHP[13], m_iOther_TargetDamageHP[14], m_iOther_TargetDamageHP[15]);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;


	//	너무 멀리 떨어져 있다면 바로 워프 시켜 버린다.
	HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
	HTfloat fDistance = (float)sqrt( double( (pPt.x - info.PosX) * (pPt.x - info.PosX) ) 
							     	+ double( (pPt.y - info.PosY) * (pPt.y - info.PosY) ) );
	if( fDistance > 20 )
	{
		HTvector3 vecPos;
		//	이동중이었다면 멈추고
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
		//-----디버깅 테스트를 위하여-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("공격자 위치보정 ID:%d, x:%d, z:%d", m_pObjectInfo->nID, info.PosX, info.PosY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		//	OtherChar 위치 셋팅
		HTvector3 vecTempPos;
		HT_CELL_COORD crdCell;
		crdCell.x = info.PosX;
		crdCell.y = info.PosY;
		g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecPos );
		g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
	}
	else if( fDistance > 1 )
	{
		if(HT_SUCCEED( m_pOther_MoveSystem->HT_hrOtherObjectMove_SetTargetCellPos( info.PosX, info.PosY )))
		{
			//	캐릭터 애니매이션 셋팅
			m_iOther_ActionEffect = 3;
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
			//	공격 받았을때 이동해서 때리는것 셋팅_초기 공격 0초일때만 셋팅해준다. 안그러면 두번 액션한다.
			if( info.snRes == -1 )
			{
				m_bOther_AttackMoveSw = HT_TRUE;
			}
			return;
		}
	}

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		//	액션 0초에서 왔느냐?
		if( info.snRes == -1 )
		{
			if( m_iOther_ApplySkillIndex != 0 )
			{
				m_iOther_ApplySkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_iOther_ApplySkillIndex );
				if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTION )
				{
					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
					//	캐스팅 시작시간
					m_iOther_ApplySkillStartTime = GetTickCount();
					//	캐스팅 지속시간
					m_iOther_ApplySkillContinueTime = 1000;
					//	FX 시전
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_READY, m_iOtherModelID, HT_FALSE );
					//	공격 Type 셋팅
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_SKILL;
				}
				else if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTIVE )
				{
					//-----디버깅 테스트를 위하여-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Skill_Ready_Start : %d", m_iOther_ApplySkillIndex );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
					//	캐스팅 시작시간
					m_iOther_ApplySkillStartTime = GetTickCount();
					//	캐스팅 지속시간
					g_pParamMgr->HT_bGetPCSkillReadyTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
					//	이펙트가 켜져 있을때는 꺼주기
					if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
					//	캐스팅 이펙트 시작
					g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_READY, m_iOtherModelID, HT_TRUE, 1 );
					if( m_iOther_ApplySkillEffectID == 0 )
						m_iOther_ApplySkillEffectID = -1;
					//	공격 Type 셋팅
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_NONE;
				}
			}
			else
			{
				//	캐릭터 애니매이션 셋팅
				m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
				//	공격 Type 셋팅
				m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_AUTOATTACK;
			}
		}
	}
	else
	{
		m_iOther_AttackType = MAINCHAR_ATTACKTYPE_SKILL;

		// Activate FX
		HTint iTemp;
		g_pEngineHandler->HT_hrStartSFX( &iTemp, m_iOther_ApplySkillIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE );

		m_iOther_WeaponItemID = m_pObjectInfo->snTribe;
		//	공격 애니매이션 셋팅
		m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
}
//	Network Recive Death Message
HTvoid HTOtherObject::HT_vOtherObject_Death()
{
	//	이펙트꺼주기
    if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}

	m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
	//	HP Bar에 표현
	g_pMainBar->HT_vSetObjectHPDraw( 0, m_pObjectInfo->nMaxHP );

	if( m_iOther_AniResentState != CHARACTER_ANISTATE_DIE )
	{
		//	Char
		if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
		{
			m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
		//	Mob
		else
		{
			this->HT_vOtherObject_WhenDeathEffect();
		}
	}
}
//	Network Recive Summons Message 
HTvoid HTOtherObject::HT_vOtherObject_NetworkSummons()
{
	//	이펙트꺼주기
    if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}

	m_iOther_LiveIndex = OTEHRCHAR_STATE_SUMMONS;

	//	죽을때의 딜레이 시간을 위해
	m_iOther_LiveDelayTime		= GetTickCount();
}
//	Network Teleport
HTvoid HTOtherObject::HT_vOtherObject_NetworkTeleport()
{
	//	텔레포트 애니가 없으니까 아이들로 대신해서 틀어준다.
	m_iOther_AniResentState = CHARACTER_ANISTATE_IDL;
	this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	//	하지만 애니상태는 죽었다고 맞추어준다. 점진적으로 사라지기 위해서
	m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
	m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;

	// 죽는 애니메이션을 하는 동안은 그림자를 그리지 않는다.
	g_pEngineHandler->HT_hrShowShadow( m_iOtherModelID, HT_FALSE );
	//	정보 디스플레이 셋팅취소
	this->HT_vOtherObject_SetHideInfomation();
	//	죽을때의 딜레이 시간을 위해
	m_iOther_LiveDelayTime		= GetTickCount();
	// 죽고나서 시체가 완전히 사라질때까지는 픽킹이 되지 않아야 한다.
	g_pEngineHandler->HT_hrDontClickIt( m_iOtherModelID );

	//	이펙트 틀어준다.
	HTint idFx;
	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherModelID, HT_FALSE );
		m_iOther_LiveIndex = OTHERCHAR_STATE_DEATH;
	}
	else
	{
		g_pEngineHandler->HT_hrStartSFX( &idFx, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), m_iOtherModelID, HT_FALSE );
		m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
	}
}
//	Network YutMove
HTvoid HTOtherObject::HT_vOtherObject_NetworkYutMove( Msg_YutMove* info )
{
	//	Find Turn Point
	int iTurnPoint = 0;
	m_iOther_EndPoint = info->wToIndex;
	if( info->wFromIndex>=2 && info->wFromIndex<=5 && info->wToIndex>6 )
		iTurnPoint = 6;
	else if( info->wFromIndex>=7 && info->wFromIndex<=10 && info->wToIndex>11 )
		iTurnPoint = 11;
	else if( info->wFromIndex>=12 && info->wFromIndex<=15 && info->wToIndex>11 )
		iTurnPoint = 16;
	else if( info->wFromIndex==6 && info->wToIndex>=24 && info->wToIndex<=25 )
		iTurnPoint = 23;
	else
	{
		iTurnPoint = info->wToIndex;
		m_iOther_EndPoint = 0;
	}

	//	Run
	if( m_iOther_AniResentState != CHARACTER_ANISTATE_RUN )
	{
		//	캐릭터 애니매이션 셋팅
		m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
	}

	MSG_Action* pData = NULL;
	pData = new MSG_Action;
	pData->TargetX = g_iYutMoveCellX[iTurnPoint];
	pData->TargetY = g_iYutMoveCellZ[iTurnPoint];
	pData->Speed = 6;
	m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( pData );
	HT_DELETE( pData );
}
