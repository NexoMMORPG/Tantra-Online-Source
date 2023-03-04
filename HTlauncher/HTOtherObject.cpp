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
	//	������Ʈ �� ��¿���
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
	
	//	�����ڵ� �������ֱ�
	//	���϶�
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
	{
		m_iOther_WeaponItemID = m_pObjectInfo->snTribe;
		m_iOther_TribeCode = m_pObjectInfo->snTribe;

		//	������ ������ ��������
		CHTString szName;
		//if( g_pEngineHandler->HT_hrGetNPCName( m_iOther_TribeCode, &szName ) == HT_OK )
		if( g_pParamMgr->HT_bGetMonsterName( m_iOther_TribeCode, &szName ) == true )
			m_strOther_Name = szName;

		g_pParamMgr->HT_bGetMonsterSize(m_iOther_TribeCode, &m_byOther_Size);

		//	�ֽ��ڵ� �������ֱ�
		if( m_pObjectInfo->byTrimuriti == 5 )		m_pObjectInfo->byTrimuriti = TRIMURITI_BRAHMA;
		else if( m_pObjectInfo->byTrimuriti == 6 )	m_pObjectInfo->byTrimuriti = TRIMURITI_VISHNU;
		else if( m_pObjectInfo->byTrimuriti == 7 )	m_pObjectInfo->byTrimuriti = TRIMURITI_SIVA;
	}
	//	ĳ�����϶�
	else
	{
		m_byOther_Size = 1;
        HT_ConvertTribeS2C( m_pObjectInfo->snTribe, m_iOther_TribeCode );
	}

	if( m_byOther_Size < 1 )
		m_byOther_Size = 1;
	
	//	OtherChar ��ġ ����
	HTvector3 vecPos;
	HT_CELL_COORD crdCell;
	crdCell.x = m_pObjectInfo->snTargetX;
	crdCell.y = m_pObjectInfo->snTargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecPos );

	//	������ ���� ����
	for( HTint i=0 ; i<7 ; i++ )
	{
		if( m_pObjectInfo->Equip[i].snIndex )
			m_pObjectInfo->Equip[i].snIndex += HT_ITEM_INDEX_START;
	}

	//	������Ʈ �� ��¿��� �Ǵ��Ͽ� �� ����
	if( m_bOther_ShowObject )
		this->HT_vOtherObject_CreateModel();

	//	�㵵
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

	//	���� �ִϸ��̼� ����
	//m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
	//g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, m_iOther_TribeCode, HT_ANISTATE_STD, -1 );

	//	Setting Hide Infomation
	this->HT_vOtherObject_SetHideInfomation();

	//	Live
	m_iOther_LiveIndex = OTHERCHAR_STATE_LIVE;

	//	GM ĳ���Ͱ� �ƴҶ��� ���� ����Ʈ �ѷ���
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
		//	��Ƽ������� �Ǵ�!
		//	0x01:��Ƽ����ƴ�, 0x02:��Ƽ���
		if( g_cParty->HT_bParty_IsPartyMember( m_strOther_Name.HT_szGetString() ) )
			m_byOther_PartyMember = 0x02;
		else
			m_byOther_PartyMember = 0x01;

		//	��忡 ���ԵǾ� �ִٸ�
		CHTString strTemp;
		strTemp.HT_hrCleanUp();
		strTemp = m_pObjectInfo->szGuild;
		if( !strTemp.HT_bIsEmpty() )
		{
			//	��� ��ũ ǥ�� �ϱ�
			if( g_bGuildMarkShow )
                this->HT_vOtherObject_SetGuildMarkOn();
			//	Guild Member Check
			this->HT_vOtherObject_SetMyGuildCheck( m_pObjectInfo->szGuild );
		}

		//	�ֽ��� �ִٸ�
		if( info->byTrimuriti )
		{
			//	�ֽ� ��ũ ǥ�� �ϱ�
			this->HT_vOtherObject_SetTrimuritiMarkOn();
		}

		//	�������� üũ
		if( m_iOther_TribeCode == 9 )
            if( m_pObjectInfo->byGMStatus & 0x02 )
				g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );
	}

	//	�������� üũ
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
		g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );

#ifdef GM_CHAR_HIDE
	if( m_iOther_TribeCode == 9 )
		g_pEngineHandler->HT_hrShowObject( m_iOtherModelID, HT_FALSE );
#endif

	//	���̵� ������ ����
	m_iOther_IdlTime = GetTickCount() + ( rand()%IDLE_PC_TIME );

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		// ��� ����� (������ ���� �����޴� ���) 2005. 1. 31 ������
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
		//	�ֽ��� �����θ� �ٸ� �ֽ��̸� ���� ����
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti != m_pObjectInfo->byTrimuriti )
				m_bOther_DefinZoneAttackTarget = TRUE;
			else
				m_bOther_DefinZoneAttackTarget = FALSE;
		}
		//	����� �����̸� �ڽ��� ��峪 ���ձ�尡 �ƴϸ� ���� ����
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			if( strlen(m_pObjectInfo->szGuild) > 0 )
			{
				CHTString strMyGuild = g_cGuildSystem->HT_strGuild_GetGuildName();
				CHTString strArlliedGuild = g_cGuildSystem->HT_strGuild_AlliedGuildName( 0 );
				//	Ÿ ��� üũ
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
		//	�Ϲ� �ʵ�� �ٸ� ������ Ÿ�Եȴ�.
		else
		{
			m_bOther_DefinZoneAttackTarget = FALSE;
		}
	}
	else
	{
		m_bOther_DefinZoneAttackTarget = TRUE;
		//	�ֽ��� �����θ� �ٸ� �ֽ��̸� ���� ����
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti == m_pObjectInfo->byTrimuriti )
				m_bOther_DefinZoneAttackTarget = FALSE;
		}
		//	����� �����̸� �ڽ��� ����� üũ
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			HTint iMyStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();
			//	�ڽ��� ����� üũ
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

	//	�׾ �¾���� �˻�
	if( info->nCurHP <= 0 )
	{
		//	Live
		m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
		m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}

	//	Ʈ���̵� ��� üũ
	if( !g_cSystem->HT_bSystem_GetShopModelMode() &&
		m_pObjectInfo->byTradeMode != 0 )
	{
		//	ĳ���� �ִϸ��̼� ����
		m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
}

//	Create Model
HTvoid HTOtherObject::HT_vOtherObject_CreateModel()
{
	//	Ȥ�ó� �̳��� �����Ǿ� �ִٸ� ����
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

	//	���� �ִϸ��̼� ����
	m_iOther_AniResentState = CHARACTER_ANISTATE_STD;

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		HTbool bTrue = HT_FALSE;
        //	Ʈ���̵� ��� üũ
        if( m_pObjectInfo->byTradeMode == 0 )
			bTrue = HT_TRUE;
		else if( !g_cSystem->HT_bSystem_GetShopModelMode() )
			bTrue = HT_TRUE;

		if( bTrue )
		{
			m_iOtherModelID = g_pEngineHandler->HT_iCreateCharacter( m_iOther_TribeCode, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos(), m_pObjectInfo->byHead, m_pObjectInfo->byFace );

			//	�Ӹ� ����
			this->HT_vOtherObject_SetItemType( eTNEqu_Helmet, m_pObjectInfo->Equip[0] );
			//	�� ����(����)
			this->HT_vOtherObject_SetItemType( eTNEqu_Armor, m_pObjectInfo->Equip[1] );
			//	�� ����(����)
			this->HT_vOtherObject_SetItemType( eTNEqu_Pants, m_pObjectInfo->Equip[2] );
			//	�޼� ����
			this->HT_vOtherObject_SetItemType( eTNEqu_Shield, m_pObjectInfo->Equip[3] );
			//	������ ����
			this->HT_vOtherObject_SetItemType( eTNEqu_OneHandWeapon, m_pObjectInfo->Equip[4] );
			//	�� ����
			this->HT_vOtherObject_SetItemType( eTNEqu_Boots, m_pObjectInfo->Equip[5] );
			//	�尩 ����
			this->HT_vOtherObject_SetItemType( eTNEqu_Gloves, m_pObjectInfo->Equip[6] );
			//	Start Ani
            g_pEngineHandler->HT_hrStartAnimation( m_iOtherModelID, m_iOther_TribeCode, HT_ANISTATE_STD, -1 );
			//	if Trade Mode then change ani
			if( m_pObjectInfo->byTradeMode != 0 )
			{
				//	ĳ���� �ִϸ��̼� ����
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
	//	�� ������
	m_fOther_ModelHeight = g_pEngineHandler->HT_fGetObjHeight( m_iOtherModelID );
}
//	Delete Model
HTvoid HTOtherObject::HT_vOtherObject_DeleteModel()
{
	//	�����Ǿ� �ִ� �ѵ鸸 ����
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
	//	ĳ�����϶��� Skip
	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
		return;

	//	������ �Կ��� ���� ��ü�� ���ܵα� ����
	if( g_bGamePlayMovieForGlobal )
		return;

	if( m_iOther_LiveIndex == OTHERCHAR_STATE_LIVE )
		return;

	HTint iPassTime = GetTickCount();

	if( m_iOther_LiveIndex == OTEHRCHAR_STATE_SUMMONS )
	{
		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		if ( iPassTime > m_iOther_LiveDelayTime + 500 && iPassTime < m_iOther_LiveDelayTime + 4000 )
		{
			//	����Ʈ_���� �׾����� ���������͵�
			if ( m_iOther_AniResentState != CHARACTER_ANISTATE_IDL )
			{
				m_iOther_AniResentState = CHARACTER_ANISTATE_IDL;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
			}
		}
		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		else if ( ( iPassTime > m_iOther_LiveDelayTime + 4000 ) && ( iPassTime < m_iOther_LiveDelayTime + 20000 ) )
		{
			if( m_bOther_DownEarthSw == HT_FALSE )
			{
				//	Setting Up/Down_Death Mode
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( 0.0f, -0.5f, m_fOther_ModelHeight, HT_FALSE );
				m_bOther_DownEarthSw = HT_TRUE;

				//	���� ����Ʈ
				HTint idFx;
				if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
					g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWBORN, m_iOtherModelID, HT_FALSE );
				else
					g_pEngineHandler->HT_hrStartSFX( &idFx, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), m_iOtherModelID, HT_FALSE );
			}
		}
		// ���� ������ �ð��� �� �� ��� �Ѵ�. ���� ��������.
		else if( iPassTime > m_iOther_LiveDelayTime + 20000 )
		{
			m_iOther_LiveIndex = OTHERCHAR_STATE_DEATH;
		}
	}
	else
	{
		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		if ( iPassTime > m_iOther_LiveDelayTime + 2000 && iPassTime < m_iOther_LiveDelayTime + 10000 )
		{
			//	����Ʈ_���� �׾����� ���������͵�
			if ( m_iOther_AniResentState != CHARACTER_ANISTATE_DIE )	// �ѹ��� �����ϱ� ���Ѱ� ����.
				this->HT_vOtherObject_WhenDeathEffect();

			//	���� ���϶��� �ٷ� �׵��� �Ѵ�.
			if( m_pObjectInfo->byDir )
				m_iOther_LiveDelayTime -= 10000;
		}
		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		else if ( ( iPassTime > m_iOther_LiveDelayTime + 10000 ) && ( iPassTime < m_iOther_LiveDelayTime + 25000 ) )
		{
			if( m_bOther_DownEarthSw == HT_FALSE )
			{
				//	Setting Up/Down_Death Mode
				m_pOther_MoveSystem->HT_vOtherObjectMove_SetUpDown( 0.0f, -0.5f, m_fOther_ModelHeight, HT_FALSE );
				m_bOther_DownEarthSw = HT_TRUE;
			}
		}
		// ���� ������ �ð��� �� �� ��� �Ѵ�. ���� ��������.
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
				//	����Ʈ�� ���� �������� ���ֱ�
				if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
				//	ĳ���� ����Ʈ ����
				g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
				//if( m_iOther_ApplySkillEffectID == -1 )
				//	m_iOther_ApplySkillEffectID = 0;
				//	ĳ���� ���۽ð��� ����
				m_iOther_ApplySkillStartTime = GetTickCount();
				//	ĳ���� ���ӽð��� ����
				g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
			}
		}
		else if( m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLCAST )
		{
			HTdword dwPassTime = GetTickCount();
			if( dwPassTime >= (DWORD)(m_iOther_ApplySkillStartTime + m_iOther_ApplySkillContinueTime) )
			{
				//	������ ĳ���� ����Ʈ�� �־����� ����
				if( m_iOther_ApplySkillEffectID != -1 )
					g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
				m_iOther_ApplySkillEffectID = -1;

				//	���� Type ����
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
					//	��Ƽ����Ʈ �ִϸ��̼� Ʋ���ش�.
					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLACTIVATE;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );

					// ��Ƽ����Ʈ ����Ʈ ����
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE, 5 );

					//	V3�� ���� �۾��Ѱ�
					if( m_iOther_DurationSkillEffectID )
					{
						g_pEngineHandler->HT_hrStopSFX( m_iOther_DurationSkillEffectID );
						m_iOther_DurationSkillEffectID = 0;
					}

					HTdword dwSkillType = g_pEngineHandler->HT_dwGetSkillType( m_iOther_ApplySkillIndex );

					//	���ӽ�ų�� �ڱ��ڽŰ� Ÿ�ο��� Ʋ��� �ɶ��� �Ǵ�
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
					//	V3�� ���� �۾��Ѱ�
					else
					{
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_DurationSkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, HT_TRUE, 1 );
					}

					//	�෹�̼� Ÿ��(���ӽð�)�� ����
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
	// bIsWeaponBack�� TRUE�� ��� ���� ���� ���� ���⸦ � ���̰� ��ų �ִϸ��̼��� �����ؾ� �Ѵ�.
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
		//	������ � ���⸦ ���� �ִϸ��̼� �ؾߵɶ�
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

	//	�������������� � ���⸦ ���ߵɶ�
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

	//	�ִϸ��̼� ����
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
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
			if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )		//	��Ƽ�� ��ų �������̸�...
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

	//	������ ���÷���
	this->HT_vOtherObject_SetAttachRefineEffect();
}
//	Animation Animation Check
HTvoid HTOtherObject::HT_vOtherObject_AnimationCheck()
{
	//	Death ��ȯ Check
	if( m_iOther_LiveIndex == OTEHRCHAR_STATE_DEATHMOTION ||
		m_iOther_LiveIndex == OTEHRCHAR_STATE_SUMMONS )
		return;

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iOtherModelID );

	//	���� �ִϸ��̼��϶�
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_NORMALATK ||
		m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLATK )
	{
		//	ĳ���� ���� ����Ʈ���� ����
	    if( sAnmState == HT_AS_ATTACK &&
			m_bOther_AtkptCheck == HT_TRUE )
		{
			m_bOther_AtkPtFromTimeSw = HT_FALSE;
			this->HT_vOtherObject_AttackPoint();
			return;
		}
	}

	//	ĳ���� �ִϸ��̼��� �ؾ� �ɶ�
	//	ĳ���� ������ ��ž�ִ��϶� ��ӵ����Ƿ� �������� ó��
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_SKILLREADY )
	{
		if( sAnmState == HT_AS_STOP )
		{
			//	Skill Cast Ani Start
			m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, m_iOther_ApplySkillIndex );
			//	����Ʈ�� ���� �������� ���ֱ�
			if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
			//	ĳ���� ����Ʈ ����
			g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
			//if( m_iOther_ApplySkillEffectID == -1 )
			//	m_iOther_ApplySkillEffectID = 0;
			//	ĳ���� ���۽ð��� ����
			m_iOther_ApplySkillStartTime = GetTickCount();
			//	ĳ���� ���ӽð��� ����
			g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
			return;
		}
	}

	//	OtherChar�� �׾����� ó��
	if( m_iOther_AniResentState == CHARACTER_ANISTATE_DIE )
	{
		if( sAnmState == HT_AS_STOP )
		{
			//	���� ����
			m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
			m_iOther_LiveDelayTime = GetTickCount();
			return;
		}
	}

	//	�ɴ� �����϶�
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

				//	���̵� ������ ����
				m_iOther_IdlTime = GetTickCount();
			}
			return;
		}
	}
}

//	Control AttackPointCheck From Time -> ������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
HTvoid HTOtherObject::HT_vOtherObject_ControlAttackPointCheckFromTime()
{
	//	���� ����
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
				//	Yut Move End Point�� üũ�Ͽ� ���� ������ �� ������ �ش�.
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

	//	���������� ������Ʈ�� �ʿ� ���Ž��� �ش�.
    g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );
}
//	Move Rotate Control
HTvoid HTOtherObject::HT_vOtherObject_RotateControl( HTfloat fElapsedTime )
{
	//	�з������� Skip
	if( m_pOther_MoveSystem->m_snEffect == 6 )
		return;

	HTfloat fCharAngle = m_pOther_MoveSystem->HT_fOtherObjectMove_GetDirect();
	
	if( fCharAngle != m_fOther_ShowAngle )
	{
		//	1. ���簢�� ���� Display���� ��������� ����
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

		//	2. ���簢���� ����
		if( m_iOther_ProgressAngle == 1 )
		{
			m_fOther_ShowAngle += fSpeed;
			//	�ִ밪�� �Ѿ�� �ּҰ�����
			if( m_fOther_ShowAngle > HT_PIX2+HT_PI )
			{
				m_fOther_ShowAngle = HT_PI;
			}
		}
		else if( m_iOther_ProgressAngle == -1 )
		{
			m_fOther_ShowAngle -= fSpeed;
			//	�ּҰ����� ������ �ִ밪����
			if( m_fOther_ShowAngle < HT_PI )
			{
				m_fOther_ShowAngle = HT_PIX2+HT_PI;
			}
		}

		//	�ʱ�ȭ
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
	//	���� �����϶�
	if( m_pOther_MoveSystem->HT_fOtherObjectMove_GetCurSpeed() == 0.0f )
	{
		//	���� �޾����� �̵��ؼ� �����°� ����
		if( m_bOther_AttackMoveSw )
		{
			// �����ڸ� ���� ȸ��
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
						//	���� Type ����
						m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_SKILL;

						//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
						m_bOther_AtkPtFromTimeSw = HT_TRUE;
						m_iOther_AtkptFromTimeDelay = 100;
						m_iOther_AtkptFromTimeStartTime = GetTickCount();
					}
					else if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTIVE )
					{
						m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
						this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
						//	ĳ���� ���۽ð�
						m_iOther_ApplySkillStartTime = GetTickCount();
						//	ĳ���� ���ӽð�
						g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
						//	����Ʈ�� ���� �������� ���ֱ�
						if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
						//	ĳ���� ����Ʈ ����
						g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_CAST, m_iOtherModelID, HT_TRUE, 1 );
						//if( m_iOther_ApplySkillEffectID == 0 )
						//	m_iOther_ApplySkillEffectID = -1;
						//	���� Type ����
						m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_NONE;
					}
				}
				else
				{
					//	ĳ���� �ִϸ��̼� ����
					m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
					//	���� Type ����
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_AUTOATTACK;

					//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
					m_bOther_AtkPtFromTimeSw = HT_TRUE;
					m_iOther_AtkptFromTimeDelay = 100;
					m_iOther_AtkptFromTimeStartTime = GetTickCount();
				}
			}
			else
			{
				//	���� �ִϸ��̼� ����
				m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
				//	���� Type ����
				m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_AUTOATTACK;

				//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
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
				//	ĳ���� �ִϸ��̼� ����
				m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
				this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );

				//-----���̵� ������ ����-----//
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
	//	��������Ʈ
	m_bOther_AtkptCheck = HT_FALSE;

	//-----����Ŭ���� ����-----//
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
	//	���� Demage Count
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        if( m_iOther_TargetKeyID[i] == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			HTbyte byAttacker = 1;
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )		byAttacker = 1;
			else														byAttacker = 2;

			//	����ĳ���Ϳ� ���Ѽ� ����
			g_cMainCharacter->HT_vMainCHar_SCP_SetAffections( m_iOther_TargetAffaction );

			CHTString strMsg, szMessage;
			if( m_byOther_TargetRes[i] == 2 )
			{
				g_cHitCountMgr->HT_vHitCountMgr_Create( byAttacker, m_byOther_TargetRes[i], 0, m_vecOther_AttackTargetPos, 0, HT_FALSE );
				// %s�� ������ ȸ���߽��ϴ�.
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
						//	s(��)�κ��� %s �������� �޾ҽ��ϴ�.
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
						//	������ ������ ǥ��
						CHTString szParam, strTemp;
						strTemp.HT_szFormat("%d", m_iOther_TargetDamageHP[i] );
						HT_g_Script_SetMessage( eMsgLastDamageNotice, &szParam, strTemp.HT_szGetString() );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szParam.HT_szGetString() );
					}
				}
				//	���� ����� HP
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

	//	�������� KeyID
	m_iOther_InvadeKeyID = iInvadeKeyID;

	//	Impact Effect
	if( iSkillID == 0 )
	{
		g_pEngineHandler->HT_hrStartSFX( iItemID, iInvadeModelID, m_iOtherModelID );
	}
	else
	{
		//	���¿� �ɷ��������� Ÿ�� ����Ʈ �Ѹ��� �ʴ´�.
        g_pEngineHandler->HT_hrStartSFX( iSkillID, iInvadeModelID, m_iOtherModelID );
	}

	//	�ø�Ŀ
	g_pEngineHandler->HT_hrFlickerObject( m_iOtherModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	������
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iOtherModelID, HT_FALSE );

	HTbyte bySkillType = 0;
	if( iSkillID )
        g_pParamMgr->HT_bGetPCSkillType( iSkillID, 1, &bySkillType );

	if( !bySkillType )
	{
		//	�������� �ƴҶ��� �´� �׼�
		if( m_iOther_AniResentState == CHARACTER_ANISTATE_STD ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_IDL ||
			m_iOther_AniResentState == CHARACTER_ANISTATE_SIT )
		{
			if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
				m_iOther_AniResentState = CHARACTER_ANISTATE_HIT;
			else
				m_iOther_AniResentState = CHARACTER_ANISTATE_MOBHIT;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

			//	���� �޴°Ϳ� ���� Object�� �����.
			m_bStopWhenInvadeSw = HT_TRUE;
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
		}
		else	// �´� ���ϸ��̼��� ������ �ʴ´ٸ� �´� �Ҹ��� �����Ѵ�.
		{
			g_pEngineHandler->HT_hrPlayHitSound( m_pObjectInfo->snTribe, m_iOtherModelID );
		}
	}

	//-----���̵� ������ ����-----//
	m_iOther_IdlTime = GetTickCount();
}
//	Effect Recive Active Skill Use From OtherObject
HTvoid HTOtherObject::HT_vOtherObject_EffectActiveSkillEffectOn( HTint iSkillIndex, HTbool bType, BYTE byLevel )
{
	//	ĳ���� ���۽ð��� ����
	m_iOther_ApplySkillStartTime = GetTickCount();
	//	ĳ���� ���ӽð��� ����
	g_pParamMgr->HT_bGetPCSkillCastingTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
	//	����Ʈ�� ���� �������� ���ֱ�
	if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
	//	StartFX
	g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, iSkillIndex, HT_SFX_WHEN_STATE, m_iOtherModelID, bType, byLevel );
}
//	Effect When OtherObject Death
HTvoid HTOtherObject::HT_vOtherObject_WhenDeathEffect()
{
	//	����Ʈ���ֱ�
	if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}
	
	m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
	this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

	// �״� �ִϸ��̼��� �ϴ� ������ �׸��ڸ� �׸��� �ʴ´�.
	g_pEngineHandler->HT_hrShowShadow( m_iOtherModelID, HT_FALSE );
	//	���� ���÷��� �������
	this->HT_vOtherObject_SetHideInfomation();
	//	�������� ������ �ð��� ����
	m_iOther_LiveDelayTime		= GetTickCount();
	//	���� ������ ������ ȥ�� ����������
	HTint imsiID;
	g_pEngineHandler->HT_hrStartSFX( &imsiID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pObjectInfo->snTribe), HT_SFX_WHEN_ACTIVATE, m_iOtherModelID, HT_FALSE );
	// �װ��� ��ü�� ������ ������������� ��ŷ�� ���� �ʾƾ� �Ѵ�.
	g_pEngineHandler->HT_hrDontClickIt( m_iOtherModelID );

	//	Get Source
	m_vecOther_AttackSourcePos = m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
	m_vecOther_AttackSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackSourcePos.x, m_vecOther_AttackSourcePos.z );
	//	Get Target
	m_vecOther_AttackTargetPos = HTvector3( 0, 0, 0 );

	//	Ʃ�丮�� �ý����� ����
	HTbyte byInvadeType = 0;
	if( m_iOther_InvadeKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		if (g_cTutorialSystem)
		{
			if (_DIALOG_TUTORIALWND_10==g_cTutorialSystem->HT_iGetTutorialStep())
				g_cTutorialSystem->HT_vAddTutorialStep( TUTORIAL_STEP_GETITEM );
		}
	}

	//	���� ������ ĳ���������� ���� ����Ʈ ��������
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

	//	���� �� ����Ʈ Ʋ���ش�
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
	//	�ø�Ŀ
    g_pEngineHandler->HT_hrFlickerObject( m_iOtherModelID, HT_COLOR( r, g, b, 1.0f ), fTime );
}

//	Setting
//	Setting Set Item 
HTvoid HTOtherObject::HT_vOtherObject_SetItemType( BYTE byPart, STRUCT_ITEMVIEW info )
{
	if( info.snIndex != 0 )
	{
		//	����
		HTdword iNormalIndex, iLeftIndex;
		iNormalIndex = info.snIndex;	iLeftIndex = 0;
        if( byPart == eTNEqu_Shield )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalIndex ) )
			{	iLeftIndex = iNormalIndex;	iNormalIndex = 0;		}
		}
        g_cEquipSystem->HT_EquipSys_Equip( m_iOtherModelID, m_iOther_TribeCode, iNormalIndex, iLeftIndex, m_pObjectInfo->byHead );

		//	���� ������ �����ϰ�
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

		//	���� ��Ʈ�� ������ ���� ȿ���� ���δ�.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			//	���� ������ �Ǿ� �ִ� (����) �������� FX ����
			if( info.byRefineLevel > 0 )
				g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherModelID, info.snIndex, info.byRefineLevel );
			
			// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
			if( info.byRefineLevel > 0 )
			{
				// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
				g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherModelID, info.snIndex, (HTESubRefineType)info.byMainRef, info.byRefineLevel );
			}
		}
	}
	else
	{
        //	Ż��
		HTint iNormalItem, iLeftItem;
		iNormalItem = m_iOther_EquipItem[byPart], iLeftItem = 0;
		if( byPart == eTNEqu_Shield )
		{
			if( g_pEngineHandler->HT_bIsShortSword( iNormalItem ) )
			{	iLeftItem = iNormalItem;  iNormalItem = 0;		}
		}
		g_cEquipSystem->HT_EquipSys_UnEquip( m_iOtherModelID, m_iOther_TribeCode, iNormalItem, iLeftItem, m_pObjectInfo->byHead );
		//	Ż�� ������ �����ϰ�
		m_iOther_EquipItem[byPart] = 0;
		m_byOther_MainRef[byPart] = 0;
		m_byOther_RefineLevel[byPart] = 0;

		if( byPart == eTNEqu_OneHandWeapon || byPart == eTNEqu_TwoHandWeapon )
			m_iOther_WeaponItemID = -1;
		else if( byPart == eTNEqu_Armor )
			m_iOther_WearItemID	= -1;

		//	Ż�� ��Ʈ�� ������ ���� ȿ���� ���δ�.
		if( byPart == eTNEqu_OneHandWeapon )
		{
			// ���õ� �������� FX ���ֱ�
			// ���� ����
			g_pEngineHandler->HT_hrDetachItemMainRefineEffect( m_iOtherModelID, info.snIndex );
			// �Ӽ� ����
			g_pEngineHandler->HT_hrDetachItemSubRefineEffect( m_iOtherModelID, info.snIndex );
		}
	}

	if ( m_iOther_AniResentState == CHARACTER_ANISTATE_STD ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_SIT ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_RUN ||
		 m_iOther_AniResentState == CHARACTER_ANISTATE_WLK )
	{
		//	ĳ���� �ִϸ��̼� ����
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
	}

	//	�������ڸ� �����ߴ��� �м�
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
	//	����Կ��� ���� ���� Ÿ���� �ִϸ��̼��� �Ⱥ��̰� �ϱ� ����
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
	//	GM�϶� ���� üũ
	if( m_pObjectInfo->byGMStatus == 2 )
		m_pObjectInfo->iAffections = iAffections | 0x00000020;

	//	Affections Fx On/Off
	HTdword dwFXID = g_pEngineHandler->HT_dwGetAffectionFXID( iAffections, m_pObjectInfo->iAffections );
    //if ( iAffections == eTNVSAfn_MoveSpeed140R ) dwFXID = 1010090; //fors_debug ֱ�Ӹ�ֵ �³��
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
			if( !(iAffections&eTNVSAfn_MagicShield) &&  !(iAffections&eTNVSAfn_EnhancedMagicShield) ) //fors_debug ħ������� eTNVSAfn_EnhancedMagicShield
			{
				g_pEngineHandler->HT_hrStartSFX( &m_iOther_FXAffections, dwFXID, m_iOtherModelID, HT_TRUE );
			}
		}
	}
    
	//	���� üũ
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
	{
		//	WizardEyesSw Check
		if( !m_bOther_MainCharWizardEyesSw )
		{
			//	���Ž�ų�� �����ٸ� ���õǾ����� ���� Ǯ���ش�.
			this->HT_vOtherObject_SetHideInfomation();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
			//	���� ����ĳ���Ͱ� �����ϴ� ĳ���Ͱ� �ڽ��̸� �������
			if( g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID() == m_pObjectInfo->nID )
                g_cMainCharacter->HT_vMainChar_SetAttackCancel( 25 );
			this->HT_vOtherObject_SetModelHide( HT_FALSE );
			//	���Ÿ� Ȱ��ȭ�ǰ� �ٸ����͵��� ������� ó��
			m_pObjectInfo->iAffections = eTNVSAfn_Invisible;
		}
	}
	else
	{
		this->HT_vOtherObject_SetModelHide( HT_TRUE );
	}

	//	��������
	//if( m_pObjectInfo->iAffections & eTNVSAfn_Stun ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Sleep ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Hold ||
	//	m_pObjectInfo->iAffections & eTNVSAfn_Hold2 )
	//	this->HT_vOtherObject_EffectFaintingstateOn();

	//	ĳ���� �� ����
    if( m_pObjectInfo->iAffections & eTNVSAfn_Fire )
	{
		this->HT_vOtherObject_EffectSetModelColor( 1.0f, 1.0f, 0.0f, 2.0f );	//	���
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Cold )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.0f, 1.0f, 1.0f, 2.0f );	//	û��
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Lightning )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.9f, 0.5f, 0.0f, 2.0f );	//	���� û��
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_Poison )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.0f, 1.0f, 0.0f, 2.0f );	//	���
	}
	if( m_pObjectInfo->iAffections & eTNVSAfn_ProtectFromPK )
	{
		this->HT_vOtherObject_EffectSetModelColor( 0.3f, 1.0f, 0.3f, 2.0f );	//	���
	}

	//	Ÿ�R�� �ٽ� üũ
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
		//	0:��ŷ�����
		if( info->byTradeMode == HT_STORE_MODE_END )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_AniResentState = CHARACTER_ANISTATE_STANDUP;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
		//	1:��ŷ���
		else if( info->byTradeMode == HT_STORE_MODE_START ||
				 info->byTradeMode == HT_STORE_MODE_START+1 )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_AniResentState = CHARACTER_ANISTATE_SITDOWN;
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		}
	}
	else
	{
		//	������Ʈ �� ��¿��� �Ǵ��Ͽ� �� ����
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
		//	���� ���°� ���� ���¶�� ���̰� �Ѵ�.
		if( (m_pObjectInfo->iAffections & eTNVSAfn_Invisible) != 0 &&
			(m_pObjectInfo->byGMStatus & 0x02) == 0 )
            this->HT_vOtherObject_SetModelHide( HT_TRUE );
	}
	else
	{
		//	���� ���°� ���� ���¶�� �ٽ� �Ⱥ��̰� �Ѵ�.
		if( (m_pObjectInfo->iAffections & eTNVSAfn_Invisible ) != 0 )
            this->HT_vOtherObject_SetModelHide( HT_FALSE );
	}

	//	Ÿ�R�� �ٽ� üũ
	this->HT_vOtherObject_SetTargetting();
}
//	������ ���÷���
HTvoid HTOtherObject::HT_vOtherObject_SetAttachRefineEffect( )
{
	//	���϶��� ��ŵ
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
		return;

	//	���� ��Ʈ�� ������ ���� ȿ���� ���δ�.
	if( m_iOther_EquipItem[eTNEqu_OneHandWeapon] > 0 )
	{
		//	���� ������ �Ǿ� �ִ� (����) �������� FX ����
		if( m_byOther_RefineLevel[eTNEqu_OneHandWeapon] > 0 )
			g_pEngineHandler->HT_hrAttachItemMainRefineEffect( m_iOtherModelID, m_iOther_EquipItem[eTNEqu_OneHandWeapon], m_byOther_RefineLevel[eTNEqu_OneHandWeapon] );
		
		// �Ӽ� ���� �Ǿ� �ִ� (����) �������� ���
		if( m_byOther_RefineLevel[eTNEqu_OneHandWeapon] > 0 )
		{
			// HT_SUBREFINETYPE_NONE, HT_SUBREFINETYPE_FIRE, HT_SUBREFINETYPE_ICE, HT_SUBREFINETYPE_LIGHTING,HT_SUBREFINETYPE_POISON,
			g_pEngineHandler->HT_hrAttachItemSubRefineEffect( m_iOtherModelID, m_iOther_EquipItem[eTNEqu_OneHandWeapon], (HTESubRefineType)m_byOther_MainRef[eTNEqu_OneHandWeapon], m_byOther_RefineLevel[eTNEqu_OneHandWeapon] );
		}
	}
}
//	Setting Targetting
//	1. ĳ���� ������������ ȣ��
//	2. Msg_set_zone_setting���� ȣ��
//	3. Msg_chage_trimuriti���� ȣ��
//	4. MSG_GuildUpdate �� Msg_StrongHoldUpdate���� ȣ��
//	5. PK Button�������� üũ
//	6. �հŸ��� �̵��� ������ (����, ����)
//	7. ��Ƽ ������ ����
HTvoid HTOtherObject::HT_vOtherObject_SetTargetting()
{
	HTint iMyStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();
	CHTString strMyGuild = g_cGuildSystem->HT_strGuild_GetGuildName();
	CHTString strAshiram1 = g_cGuildSystem->HT_strGuild_AlliedGuildName(0);
	BOOL bPKButton = g_pMainBar->HT_bGetPKButton();

	//	���� False�� ��
	m_bOhter_Targetting = HT_FALSE;

	//	GM�̸� ������ Ÿ���� �Ҽ� ����.
	if( m_iOther_TribeCode == 9 )
        return;

	//	�������� üũ
	if( m_pObjectInfo->iAffections & eTNVSAfn_Invisible )
	{
		//	���� ���ڵ���̸� ������ ���� ������ Ÿ�����Ҽ� ����.
		if( !m_bOther_MainCharWizardEyesSw )
			return;
	}

	//	���̸� �Ʒ������� üũ�ϰ� �ش����� ������ ���� Ÿ���� ����
	if( SERVEROBJECT_IS_MONSTER( m_pObjectInfo->nID ) )
	{
		//	�ֽ��� �����θ� �ٸ� �ֽ��̸� ���� ����
		if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		{
			if( g_oMainCharacterInfo.byTrimuriti == m_pObjectInfo->byTrimuriti )
				return;
		}
		//	����� �����̸� �ڽ��� ����� üũ
		else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
		{
			//	�ڽ��� ����� üũ
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
		//	Ÿ�R�� ���� ���ƾ� �� �� ���̵�
		if( m_iOther_TribeCode>=2850 && m_iOther_TribeCode<=2899 )
			return;
		
		//	���� Ÿ���� ����
		m_bOhter_Targetting = HT_TRUE;
		return;
	}

	//	�ֽ���, ����� ������ �ƴϰ� �������� 0�ΰ��
	if( ( HT_FAILED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) && HT_FAILED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) ) &&
		g_snResentZoneSiege == 0 )
	{
		//	PK Button �� ������ �ְ� 20���� �̻��϶� �׸��� ��Ƽ���� �ƴҶ��� Ÿ���� �����ϴ�.
		if( bPKButton == TRUE && 
			m_pObjectInfo->byLevel >= 20 &&
			g_cStatus->HT_byGetLevel() >= 20 &&
			m_byOther_PartyMember != 0x02 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}

		//	���� ����̸� ���� ����� TargetKeyID �� ������ Ÿ���� �����ϴ�.
		if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat && 
			g_pDuelSystem->HT_iDuel_GetDuelCharKeyID() == m_pObjectInfo->nID )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	�ֽ��� �����̸�
	else if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
	{
		//	���� �ֽ��� ���� ������ Ÿ���� ����
		if( g_oMainCharacterInfo.byTrimuriti != m_pObjectInfo->byTrimuriti )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	����� �����̸�
	else if( HT_SUCCEED( HT_IS_FORETRESSZONE( g_wResentZoneServerID ) ) )
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		HTPoint pPt2 = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( (pPt.x>=285 && pPt.x<=345 &&	pPt.y>=677 && pPt.y<=736) ||
			(pPt2.x>=285 && pPt2.x<=345 && pPt2.y>=677 && pPt2.y<=736) )
		{
			//	�ٷ� ��Ƽ���϶� Ÿ���� ����
			if( m_byOther_PartyMember != 0x02 )
			{
				m_bOhter_Targetting = HT_TRUE;
				return;
			}
		}
		//	�ƽ����� ������ ���� ����
		else if( strlen(m_pObjectInfo->szGuild) == 0 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
		//	�ƽ����� ������
		else
		{
			//	Ÿ ��� üũ
			if( strMyGuild.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 &&
				strAshiram1.HT_iStringCompare( m_pObjectInfo->szGuild ) != 0 )
			{
				m_bOhter_Targetting = HT_TRUE;
				return;
			}
		}
	}
	//	Zone Setting 1�϶� 
	else if( g_snResentZoneSiege == 1 )
	{
		//	�� ��(������)�� �ֽ��� �ٸ��� ���� ���̴�.
		if( g_cMainCharacter->HT_byMainChar_GetClanValue() != m_pObjectInfo->byClan )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}
	}
	//	Zone Setting 0�϶� 
	else if( g_snResentZoneSiege == 0 )
	{
		//	PK Button �� ������ �ְ� 20���� �̻��϶� �׸��� ��Ƽ���� �ƴҶ��� Ÿ���� �����ϴ�.
		if( bPKButton == TRUE && 
			m_pObjectInfo->byLevel >= 20 &&
			g_cStatus->HT_byGetLevel() >= 20 &&
			m_byOther_PartyMember != 0x02 )
		{
			m_bOhter_Targetting = HT_TRUE;
			return;
		}

		//	���� ����̸� ���� ����� TargetKeyID �� ������ Ÿ���� �����ϴ�.
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
	//	���̶��� ������ �浹 üũ
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
//	Network	GM�� �����带 ���� �Ǵ� ������ ��û�Ѵٸ� �˸���
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
	//	���� �޴°Ϳ� ���� Object�� �����.
	m_bStopWhenInvadeSw = HT_FALSE;
	m_iOther_ActionEffect = info->Effect;

	HTfloat fMoveDistance;
	//	�ɱ�, ����, �ȱ�, �ٱ� ���� �׼��� �� �ʹ� �ָ� ������ �ִٸ� �ٷ� ���� ���� ������.
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

			//-----����� �׽�Ʈ�� ���Ͽ�-----//
			g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("�̵��� ��ġ���� ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
			if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

			//	OtherChar ��ġ ����
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
		//	���� ��ġ�� ��ǥ ��ġ�� �� ��ǥ��ġ�� ������������ �̵�
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	ĳ���� �ִϸ��̼� ����
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
		//	���� ��ġ�� ��ǥ ��ġ�� �� ��ǥ��ġ�� ������������ �̵�
		HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
		if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		{
			//	ĳ������ �ɾ��ְų� �ɱ� �����Ҷ��� ���� ���� Ʋ���ش�.
			if( m_iOther_AniResentState == CHARACTER_ANISTATE_SIT || m_iOther_AniResentState == CHARACTER_ANISTATE_SITDOWN )
				m_iOther_AniResentState = CHARACTER_ANISTATE_STANDUP;
			else
				m_iOther_AniResentState = CHARACTER_ANISTATE_STD;

			//	ĳ���� �ִϸ��̼� ����
			this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );

			//-----���̵� ������ ����-----//
			m_iOther_IdlTime = GetTickCount();
		}
		else
		{
			m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
		}

		//	Object ����
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( (HTfloat)info->Direction/100 );
	}
	//	Walk
	else if( info->Effect == 2 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_WLK )
		{
			//	ĳ���� �ִϸ��̼� ����
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
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		if( fMoveDistance > 10 )
			info->Speed += 2;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}
	//	����
	else if( info->Effect == 5 )
	{
		//	Setting Targetting
		this->HT_vOtherObject_SetTargetting();

		//	��ǥ�� ���
		HTvector3 vecTargetPos;
		HT_CELL_COORD crdCell;
		crdCell.x = info->TargetX;
		crdCell.y = info->TargetY;
		g_pEngineHandler->HT_CELL_TO_3DCOORD( vecTargetPos, crdCell );
		m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurCoodPos( vecTargetPos );

		//	ĳ���� �ִϸ��̼� ����
		m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
		this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		g_pEngineHandler->HT_hrMoveObject( m_iOtherModelID, m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos() );

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("������Ʈ ���� ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	knock-back
	else if( info->Effect == 6 )
	{
		if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
			m_iOther_AniResentState = CHARACTER_ANISTATE_HIT;
		else
			m_iOther_AniResentState = CHARACTER_ANISTATE_MOBHIT;
		//	ĳ���� �ִϸ��̼� ����
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
		info->Speed = 10;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("������Ʈ ���� ID:%d, x:%d, z:%d", info->dwKeyID, info->TargetX, info->TargetY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	}
	//	Run
	else if( info->Effect == 7 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_STD )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_AniResentState = CHARACTER_ANISTATE_STD;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}
	//	����
	else if( info->Effect == 8 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_PROVOKE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	�λ�
	else if( info->Effect == 9 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_BOW;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	����
	else if( info->Effect == 10 )
	{
		m_iOther_AniResentState = CHARACTER_ANISTATE_CHARGE;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
	//	�뽬
	else if( info->Effect == 11 )
	{
		if( m_iOther_AniResentState != CHARACTER_ANISTATE_RUN )
		{
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
		}
		info->Speed = 40;
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemReciveActionMsg( info );
	}

	//----------ĳ��Ʈ ��ų ���---------//
	if( m_iOther_ApplySkillEffectID != -1 )
	{
		//	����Ʈ�� ���� ��Ű��
		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
		m_iOther_ApplySkillEffectID = -1;
	}
}
//	Network Apply Skill Brodcast
HTvoid HTOtherObject::HT_vOtherObject_NetworkApplySkillBroadcast( S_MSG_ATTACK_OTHERMOB info )
{
	HTint i;

	//	��������Ʈ Check
	HTbool bAtkptCheck = HT_FALSE;
	if( m_bOther_AtkptCheck == HT_FALSE )
	{
		m_bOther_AtkptCheck = HT_TRUE;
		if( info.snRes != -1 )
			bAtkptCheck = HT_TRUE;
	}
	//	Object HP
	m_pObjectInfo->nCurHP = info.iCasterHP;
	//	��ų ���� ����_ID, Level
    m_iOther_ApplySkillIndex = info.iSkillID;
	//	Source�� ��ǥ
	m_vecOther_AttackSourcePos = m_pOther_MoveSystem->HT_vecOtherObjectMove_GetCurCoodPos();
	m_vecOther_AttackSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackSourcePos.x, m_vecOther_AttackSourcePos.z );
	//	Target�� ��ǥ
	m_vecOther_AttackTargetPos = info.vecTargetPos;
	m_vecOther_AttackTargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_vecOther_AttackTargetPos.x, m_vecOther_AttackTargetPos.z );
	// �����ڸ� ���� ȸ��
	HTvector3 vecPos = m_vecOther_AttackTargetPos - m_vecOther_AttackSourcePos;
	HTfloat fDirect = HT_extern_fGetRidan( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	m_pOther_MoveSystem->HT_vOtherObjectMove_SetCurDirect( fDirect );

	//	��ų �Ӽ� ����
	if( info.snRes != -1 )
        m_iOther_TargetAffaction = info.krgTarget[0].iAffection;
	//	��ų �Ӽ� ����
	CHTString strTemp;
	strTemp.HT_szFormat( "Affection:%x\n", m_iOther_TargetAffaction );
	HT_g_vLogFile( strTemp.HT_szGetString() );
	//	���� Demage Count Setting
	for( i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
		//	����
		m_byOther_TargetRes[i] = info.krgTarget[i].byRes;
		//	���ݹ��� ����� KeyID 0�̸� ���� �ʱ�ȭó��
		if( info.krgTarget[i].snKeyID == 0 )
		{
			//	���� Demage Count
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
					//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
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
						//	������ ���� ���ʹ� �ִϸ��̼� ����Ʈ�� ���ƿ��� �ʱ� ������ �ð����� üũ�ؾ��Ѵ�.
						m_bOther_AtkPtFromTimeSw = HT_TRUE;
						m_iOther_AtkptFromTimeDelay = 100;
						m_iOther_AtkptFromTimeStartTime = GetTickCount();
					}

					////	���� ����Ʈ�� ����� ���¶��n.n
					//if( bAtkptCheck )
					//{
					//	//	Atack Atk Message
					//	this->HT_vOtherObject_AttackMessage();
					//}
				}
				else
				{
					//	���� Demage Count
					m_iOther_TargetDamageHP[i] = -1;
					m_iOther_TargetHP[i] = -1;
					//m_iOther_TargetAffaction = 0;
				}
				//	���ǽ�ų ����
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

	////	���� ����Ʈ�� ����� ���¶��n.n
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


	//	�ʹ� �ָ� ������ �ִٸ� �ٷ� ���� ���� ������.
	HTPoint pPt = m_pOther_MoveSystem->HT_pOtherObjectMove_GetCellPos();
	HTfloat fDistance = (float)sqrt( double( (pPt.x - info.PosX) * (pPt.x - info.PosX) ) 
							     	+ double( (pPt.y - info.PosY) * (pPt.y - info.PosY) ) );
	if( fDistance > 20 )
	{
		HTvector3 vecPos;
		//	�̵����̾��ٸ� ���߰�
		m_pOther_MoveSystem->HT_vOtherObjectMove_MoveSystemStop();
		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("������ ��ġ���� ID:%d, x:%d, z:%d", m_pObjectInfo->nID, info.PosX, info.PosY );
		if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
		//	OtherChar ��ġ ����
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
			//	ĳ���� �ִϸ��̼� ����
			m_iOther_ActionEffect = 3;
			m_iOther_AniResentState = CHARACTER_ANISTATE_RUN;
			this->HT_vOtherObject_SetChangeAnimation( -1, 0.0f, 0 );
			//	���� �޾����� �̵��ؼ� �����°� ����_�ʱ� ���� 0���϶��� �������ش�. �ȱ׷��� �ι� �׼��Ѵ�.
			if( info.snRes == -1 )
			{
				m_bOther_AttackMoveSw = HT_TRUE;
			}
			return;
		}
	}

	if( SERVEROBJECT_IS_CHARACTER( m_pObjectInfo->nID ) )
	{
		//	�׼� 0�ʿ��� �Դ���?
		if( info.snRes == -1 )
		{
			if( m_iOther_ApplySkillIndex != 0 )
			{
				m_iOther_ApplySkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_iOther_ApplySkillIndex );
				if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTION )
				{
					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLREADY;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
					//	ĳ���� ���۽ð�
					m_iOther_ApplySkillStartTime = GetTickCount();
					//	ĳ���� ���ӽð�
					m_iOther_ApplySkillContinueTime = 1000;
					//	FX ����
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_READY, m_iOtherModelID, HT_FALSE );
					//	���� Type ����
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_SKILL;
				}
				else if( m_iOther_ApplySkillType == HT_PCSKILLTYPE_ACTIVE )
				{
					//-----����� �׽�Ʈ�� ���Ͽ�-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Recive_Skill_Ready_Start : %d", m_iOther_ApplySkillIndex );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

					m_iOther_AniResentState = CHARACTER_ANISTATE_SKILLCAST;
					this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, m_iOther_ApplySkillIndex );
					//	ĳ���� ���۽ð�
					m_iOther_ApplySkillStartTime = GetTickCount();
					//	ĳ���� ���ӽð�
					g_pParamMgr->HT_bGetPCSkillReadyTime( m_iOther_ApplySkillIndex, 1, &m_iOther_ApplySkillContinueTime );
					//	����Ʈ�� ���� �������� ���ֱ�
					if( m_iOther_ApplySkillEffectID != -1 )		g_pEngineHandler->HT_hrStopSFX( m_iOther_ApplySkillEffectID );
					//	ĳ���� ����Ʈ ����
					g_pEngineHandler->HT_hrStartSFX( &m_iOther_ApplySkillEffectID, m_iOther_ApplySkillIndex, HT_SFX_WHEN_READY, m_iOtherModelID, HT_TRUE, 1 );
					if( m_iOther_ApplySkillEffectID == 0 )
						m_iOther_ApplySkillEffectID = -1;
					//	���� Type ����
					m_iOther_AttackType	= MAINCHAR_ATTACKTYPE_NONE;
				}
			}
			else
			{
				//	ĳ���� �ִϸ��̼� ����
				m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
				this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
				//	���� Type ����
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
		//	���� �ִϸ��̼� ����
		m_iOther_AniResentState = CHARACTER_ANISTATE_NORMALATK;
		this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	}
}
//	Network Recive Death Message
HTvoid HTOtherObject::HT_vOtherObject_Death()
{
	//	����Ʈ���ֱ�
    if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}

	m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;
	//	HP Bar�� ǥ��
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
	//	����Ʈ���ֱ�
    if( m_iOther_FXAffections != -1 )
	{
		g_pEngineHandler->HT_hrStopSFX( m_iOther_FXAffections );
		m_iOther_FXAffections = -1;
	}

	m_iOther_LiveIndex = OTEHRCHAR_STATE_SUMMONS;

	//	�������� ������ �ð��� ����
	m_iOther_LiveDelayTime		= GetTickCount();
}
//	Network Teleport
HTvoid HTOtherObject::HT_vOtherObject_NetworkTeleport()
{
	//	�ڷ���Ʈ �ִϰ� �����ϱ� ���̵�� ����ؼ� Ʋ���ش�.
	m_iOther_AniResentState = CHARACTER_ANISTATE_IDL;
	this->HT_vOtherObject_SetChangeAnimation( 1, 0.0f, 0 );
	//	������ �ִϻ��´� �׾��ٰ� ���߾��ش�. ���������� ������� ���ؼ�
	m_iOther_AniResentState = CHARACTER_ANISTATE_DIE;
	m_iOther_LiveIndex = OTEHRCHAR_STATE_DEATHMOTION;

	// �״� �ִϸ��̼��� �ϴ� ������ �׸��ڸ� �׸��� �ʴ´�.
	g_pEngineHandler->HT_hrShowShadow( m_iOtherModelID, HT_FALSE );
	//	���� ���÷��� �������
	this->HT_vOtherObject_SetHideInfomation();
	//	�������� ������ �ð��� ����
	m_iOther_LiveDelayTime		= GetTickCount();
	// �װ��� ��ü�� ������ ������������� ��ŷ�� ���� �ʾƾ� �Ѵ�.
	g_pEngineHandler->HT_hrDontClickIt( m_iOtherModelID );

	//	����Ʈ Ʋ���ش�.
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
		//	ĳ���� �ִϸ��̼� ����
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
