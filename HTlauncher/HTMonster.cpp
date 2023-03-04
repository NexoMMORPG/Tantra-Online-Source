#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTMonster.h"


HTint g_nMonsterIndex[24] = {   2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010,
								2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
								2021, 2022, 2023, 2024 };


HTMonster::HTMonster()
{
	m_cMoveMonster					= NULL;
	m_cMoveMonster					= new CHTMoveMonSter;
	m_iMonsterKeyID					= 0;
	//-----���� HP ǥ���ϱ����� ����ĳ���Ͱ� ����������-----//
	m_bAttack_FromMainChar			= HT_FALSE;

	//-----����Ʈ ���� �ε���-----//
	m_nTargettingEffectID			= -1;
	m_byMonster_InvadeType			= 0x00;
	m_iMonster_ScaleIndex			= 0;			//	������ �ε���
	m_nMonster_TargetHP				= ATTACK_DAMAGEERRORVALUE;
	m_nMonster_DamageHP				= ATTACK_DAMAGEERRORVALUE;
	m_byMonster_ActonEffect			= 0;

	//	���� ���� ����
	m_sMonster_AttackFactor			= HT_NULL;
    m_sMonster_AttackFactor			= new S_ATTACK_FACTOR;
}

HTMonster::~HTMonster()
{
	g_pEngineHandler->HT_vDestroyMonster( m_iMonsterModelID );
	
	HT_DELETE( m_cMoveMonster );

	if( m_nTargettingEffectID > 0 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_nTargettingEffectID );
	}
}

HTRESULT HTMonster::HT_hMonsterInit()
{
	return HT_OK;
}


//----------���� ����----------//
HTvoid HTMonster::HT_vMonsterCreate( PS_SCP_INIT_OTHER_MOB info, BYTE byInitDirect )
{
	m_iMonsterKeyID					= info->nID;
    m_iMonsterIndex					= info->snTribe;
	HTvector3 vecPos;
	HT_CELL_COORD crdCell;
	crdCell.x = info->snTargetX;
	crdCell.y = info->snTargetZ;
	g_pEngineHandler->HT_CELL_TO_3DCOORD( vecPos, crdCell );
	vecPos.y = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );
	m_byMonster_Size				= 1;

	//	������ ��ġ�� �����ϰ�
	m_cMoveMonster->HT_fSetMonsterPos( vecPos );
	m_cMoveMonster->HT_vSetMonsterlogical_Cell( info->snTargetX, info->snTargetZ );
	m_cMoveMonster->HT_vSetMonsterphysical_Cell( info->snTargetX, info->snTargetZ );
	
	//	������ ������ ��������
	//------------------------------------------------------------------
	// New Param - ����
	//------------------------------------------------------------------
	CHTString szName;
	HTbyte byteSize;
	
	if( g_pEngineHandler->HT_hrGetNPCName( m_iMonsterIndex, &szName ) == HT_OK )
		m_strName = szName;
	else
		m_strName.HT_hrCleanUp();

	g_pParamMgr->HT_bGetMonsterSize(m_iMonsterIndex, &byteSize);
	m_cMoveMonster->HT_fSetMonsterSize(byteSize);

	g_pParamMgr->HT_bGetMonsterSkillRange(m_iMonsterIndex, &m_iMaxAttackDistance);
	//------------------------------------------------------------------

	//	������ ���� �����ϰ�
	m_iMonsterModelID				= g_pEngineHandler->HT_iCreateMonster( m_iMonsterIndex, m_cMoveMonster->HT_vecGetMonsterPos() );
	//	���� �� ������
	m_fMonsterModelHeight			= g_pEngineHandler->HT_fGetObjHeight( m_iMonsterModelID );

    //-----HP����----//
	m_nMonster_MAX_HP				= info->nMaxHP;
	m_nMonster_Resent_HP			= info->nCurHP;
	//-----���� ���÷���-----//
	m_bMonster_InfoShow_Sw			= HT_FALSE;

	m_bMonster_Death_Delay			= GetTickCount();

	if( m_nMonster_Resent_HP == 0 )
	{
		m_nMonster_ResentAnm		= HT_ANISTATE_DIE;
		HT_vMonster_SetAnimation( 1 );
	}

	//-----���� ����----//
	m_bMonster_AttackSw				= HT_FALSE;
	m_bMonster_DisAttackSw			= HT_FALSE;

	//-----������ ����----//
	m_nMonster_Live					= MONSTER_STATE_LIVE;
	m_bMonster_Death_Sw				= HT_FALSE;

	//-----�¾����� �̵����̸� �̵����� ����-----//
	m_bMOnster_HitMove_Sw			= HT_FALSE;

	//-----ź�� FX �õ�-----//
	BYTE byAoi = g_cAoi->HT_AOI_Level( m_cMoveMonster->HT_pGetMonsterGrid() );
	if( byAoi == AOI_LEVEL_1 || byAoi == AOI_LEVEL_CREATE )
	{
		HTint nFXTempID;
		g_pEngineHandler->HT_hrStartSFX( &nFXTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), m_iMonsterModelID, HT_FALSE );
	}

	//	�⺻ �ִϸ��̼��� �����ְ�
    m_nMonster_ResentAnm				= HT_ANISTATE_STD;
	g_pEngineHandler->HT_hrStartAnimation( m_iMonsterModelID,  m_iMonsterIndex, HT_ANISTATE_STD, -1 );

	//-----���� ���̵� ������ ����-----//
	m_nMonster_IdlDelay					= GetTickCount() + ( rand()%IDLE_MONSTER_TIME );

	//	�ʱ� ������ ���� �����ϰ� �ѷ��ֱ�
	m_cMoveMonster->HT_vSetMonsterDirect( (HTfloat)( byInitDirect * 0.78f ) + 3.14f );
	g_pEngineHandler->HT_hrRotateObject( m_iMonsterModelID, m_cMoveMonster->HT_fGetMonsterDirect() );
}

//----------���� ������Ʈ----------//
HTvoid HTMonster::HT_vMonsterUpdate( HTfloat fElapsedTime )
{
	//----------���� �������� ������ - ȭ��󿡼� ������ ��----------//
	HT_vMonsterSet_physical_CellMove( fElapsedTime );

	//----------�ִϸ��̼� ��Ʈ�Ѱ� �׿����� ó��----------//
	HT_vMonster_AnimationControl();

	//---------������Ʈ_������ ���Ͽ�----------//
	HT_vMonsterUpdate_Death();

	//	���ݹ޾����� ���� ������
	HT_vMonster_ScaleControl();
}

//---------������Ʈ_������ ���Ͽ�----------//
HTvoid HTMonster::HT_vMonsterUpdate_Death()
{
	if( m_bMonster_Death_Sw == HT_TRUE )
	{
		DWORD dwPassTime = GetTickCount();

		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		if ( dwPassTime > m_bMonster_Death_Delay + 2000 && dwPassTime < m_bMonster_Death_Delay + 10000 )	// ������ 10�� �̸��̰� 
		{
			//---------����Ʈ_���� �׾����� ���������͵�----------//
			if ( m_nMonster_ResentAnm != HT_ANISTATE_DIE )	// �ѹ��� �����ϱ� ���Ѱ� ����.
				m_vMonster_WhenDeathEffect();
		}
		// ���� ���� ���� �ð��� ������ �������� ����ɴ´�.
		else if ( ( dwPassTime > m_bMonster_Death_Delay + 10000 ) && ( dwPassTime < m_bMonster_Death_Delay + 15000 ) )	
		{
			HTvector3 vecPos = m_cMoveMonster->HT_vecGetMonsterPos();
			vecPos.y -= (HTfloat)(dwPassTime-m_bMonster_Death_Delay-10000)*(20.0f/5000.0f);
			g_pEngineHandler->HT_hrMoveObject( m_iMonsterModelID, vecPos, HT_FALSE );
		}
		else if( dwPassTime > m_bMonster_Death_Delay + 15000 ) // ���� ������ �ð��� �� �� ��� �Ѵ�. ���� ��������.
		{
			m_nMonster_Live = MONSTER_STATE_DEATH;
		}
	}
}

//----------�ִϸ��̼� ��Ʈ�Ѱ� �׿����� ó��----------//
HTvoid HTMonster::HT_vMonster_AnimationControl()
{
	if( m_bMonster_Death_Sw == HT_TRUE )
	{
		//	������ �̵� ���϶�
		if( m_nMonster_ResentAnm==HT_ANISTATE_STD || m_nMonster_ResentAnm==HT_ANISTATE_RUN )
		{
			//	�׾߸��� �ϵ��ڵ��ؼ� ������ �ذ��߱⶧���� ����Ÿ�� �м��ؼ� ���� �� �����ؾ���
			if( g_bDevelopingMode )
			{
				if( m_iMonsterIndex != 2014 &&				//	���ī�� �ƴϰ�
					m_iMonsterIndex != 2015 )				//	��� ���ī�� �ƴҶ���
				{
					m_nMonster_ResentAnm = HT_ANISTATE_IDL;
					HT_vMonster_SetAnimation( 1 );
				}
			}
			else
			{
				m_nMonster_ResentAnm = HT_ANISTATE_IDL;
				HT_vMonster_SetAnimation( 1 );
			}
		}
		return;
	}

	HT_ANIMSTATE sAnmState = g_pEngineHandler->HT_eGetAnimState( m_iMonsterModelID );

	if( sAnmState == HT_AS_ATTACK )
	{
		//-----------������ ��������Ʈ���� ����----------//
		this->HT_vMonster_AttackPointCheck();
	}
	else if( sAnmState == HT_AS_STOP )
	{
		//---------���� �ִϸ��̼� ����----------//
		if( m_bMonster_AttackSw == HT_TRUE )
		{
			m_bMonster_AttackSw = HT_FALSE;
			m_nMonster_ResentAnm = HT_ANISTATE_STD;
			HT_vMonster_SetAnimation( -1 );
			//-----���� ���̵� ������ ����-----//
			m_nMonster_IdlDelay = GetTickCount();
		}
		//---------���ݹ��� �ִϸ��̼� ����----------//
		else if( m_bMonster_DisAttackSw == HT_TRUE )
		{
			m_bMonster_DisAttackSw = HT_FALSE;
			if( m_bMOnster_HitMove_Sw == HT_TRUE )
			{
				m_bMOnster_HitMove_Sw = HT_FALSE;
				m_cMoveMonster->HT_vSetMonster_SetHitStop( HT_TRUE );
				m_nMonster_ResentAnm = HT_ANISTATE_RUN;
			}
			else
			{
				m_nMonster_ResentAnm = HT_ANISTATE_STD;
				//-----���� ���̵� ������ ����-----//
				m_nMonster_IdlDelay = GetTickCount();
			}
			HT_vMonster_SetAnimation( -1 );
		}
		else
		{
			m_nMonster_ResentAnm = HT_ANISTATE_STD;
			//-----���� ���̵� ������ ����-----//
			m_nMonster_IdlDelay = GetTickCount();
			HT_vMonster_SetAnimation( -1 );
			//-----���� ���̵� ������ ����-----//
			m_nMonster_IdlDelay = GetTickCount();
		}
	}

	//-----���� ���̵� ������ ����-----//
    if( m_nMonster_ResentAnm == HT_ANISTATE_STD && m_nMonster_ResentAnm != HT_ANISTATE_IDL )
	{
		DWORD dwPassTime = GetTickCount();
		if( dwPassTime > m_nMonster_IdlDelay + IDLE_MONSTER_TIME )
		{
			//	�׾߸��� �ϵ��ڵ��ؼ� ������ �ذ��߱⶧���� ����Ÿ�� �м��ؼ� ���� �� �����ؾ���
			if( g_bDevelopingMode )
			{
				if( m_iMonsterIndex != 2014 &&				//	���ī�� �ƴϰ�
					m_iMonsterIndex != 2015 )				//	��� ���ī�� �ƴҶ���
				{
					m_nMonster_ResentAnm = HT_ANISTATE_IDL;
					HT_vMonster_SetAnimation( 1 );
				}
			}
			else
			{
				m_nMonster_ResentAnm = HT_ANISTATE_IDL;
				HT_vMonster_SetAnimation( 1 );
			}
		}
	}
}

//----------�ִϸ��̼� ��Ʈ��_�ȱ�/�ٱ� ��Ʈ��----------//
HTvoid HTMonster::HT_vMonster_AnimationControl_WlkRun()
{
	//	������
	if( m_byMonster_ActonEffect == 2 )
	{
		if( m_nMonster_ResentAnm != HT_ANISTATE_WLK )
		{
			m_nMonster_ResentAnm = HT_ANISTATE_WLK;
			HT_vMonster_SetAnimation( -1 );
		}
	}
	//	�۶�
	else if( m_byMonster_ActonEffect == 3 )
	{
		if( m_nMonster_ResentAnm != HT_ANISTATE_RUN )
		{
			m_nMonster_ResentAnm = HT_ANISTATE_RUN;
			HT_vMonster_SetAnimation( -1 );
		}
	}
}

//---------����Ʈ_����Ʈ ����Ʈ Ʋ���ֱ�----------//
HTvoid HTMonster::m_vMonsterAttack_ImpactEffect( DWORD dwIndex, BYTE byLevel, HTint iItemIndex )
{
	if( dwIndex == 0 )
	{
		g_pEngineHandler->HT_hrStartSFX( iItemIndex, m_nMonster_InvadeModelID, m_iMonsterModelID );
	}
	else
	{
		g_pEngineHandler->HT_hrStartSFX( dwIndex, m_nMonster_InvadeModelID, m_iMonsterModelID );
	}
}

//---------����Ʈ_���� �׾����� ���������͵�----------//
HTvoid HTMonster::m_vMonster_WhenDeathEffect()
{
	m_bMonster_Death_Sw	= HT_TRUE;

	//	�״� �ִϸ��̼� Ʋ���ֱ�
	m_nMonster_ResentAnm = HT_ANISTATE_DIE;
	HT_vMonster_SetAnimation( 1 );

	// �״� �ִϸ��̼��� �ϴ� ������ �׸��ڸ� �׸��� �ʴ´�.
	g_pEngineHandler->HT_hrShowShadow( m_iMonsterModelID, HT_FALSE );

	//---------���� ���÷��� �������----------//
	this->HT_vMonster_SetInfoCancel();

	//	����ĳ���Ͱ� ���������� HP UI �ý��ۿ� ǥ��
	if( m_bAttack_FromMainChar )
	{
		g_pMainBar->HT_vSetObjectHPOut();
		//g_pMainBar->HT_vSetObjectHPDraw( m_nMonster_Resent_HP, m_nMonster_MAX_HP );
	}

	//	�������� ������ �ð��� ����
	m_bMonster_Death_Delay		= GetTickCount();

	//	���� ������ ������ ȥ�� ����������
	HTint imsiID;
	g_pEngineHandler->HT_hrStartSFX( &imsiID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), HT_SFX_WHEN_ACTIVATE, m_iMonsterModelID, HT_FALSE );

	// �װ��� ��ü�� ������ ������������� ��ŷ�� ���� �ʾƾ� �Ѵ�.
	g_pEngineHandler->HT_hrDontClickIt( m_iMonsterModelID );

	//	���� ������ ĳ���������� ���� ����Ʈ ��������
	m_sMonster_AttackFactor->strAttackName = m_strName;
	m_sMonster_AttackFactor->byAttacker = 0x02;
	m_sMonster_AttackFactor->byTargetType = m_byMonster_InvadeType;
	m_sMonster_AttackFactor->byTribe = 0x01;
	m_sMonster_AttackFactor->dwAttackKeyID = m_iMonsterKeyID;
	m_sMonster_AttackFactor->dwTargetKeyID = m_dwMonster_InvadeKeyID;
	m_sMonster_AttackFactor->nAttackType = MAINCHAR_ATTACKTYPE_PRANA;
	m_sMonster_AttackFactor->nCharModelID = m_iMonsterModelID;
	m_nMonster_TargetHP = ATTACK_DAMAGEERRORVALUE;
	m_nMonster_DamageHP = ATTACK_DAMAGEERRORVALUE;
	m_sMonster_AttackFactor->vecSourcePos = m_cMoveMonster->HT_vecGetMonsterPos();
	m_sMonster_AttackFactor->vecTargetPos = m_vecMonster_TargetPos;
    m_sMonster_AttackFactor->fDirect = m_cMoveMonster->HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), 
		m_sMonster_AttackFactor->vecTargetPos-m_sMonster_AttackFactor->vecSourcePos ) + HT_PIX2;
	m_sMonster_AttackFactor->nAttackItemID = m_iMonsterIndex;
	m_sMonster_AttackFactor->nAttackSkillID = g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex);
    m_sMonster_AttackFactor->byAttackSkillIDLevel = 1;
	g_cAttackMgr->HT_vAttackMgr_Create( m_sMonster_AttackFactor );

	//	Ʃ�丮�� �ý����� ����
	if( m_byMonster_InvadeType == 0x03 )
        g_cTutorialSystem->HT_Tutorial_StepCheck_MsgResult( TUTORIAL_STEP_HUNTINGMONSTER );
}

//---------�ִϸ��̼� ����----------//
HTvoid HTMonster::HT_vMonster_SetAnimation( HTint nLoop )
{
    g_pEngineHandler->HT_hrChangeAnimation( m_iMonsterModelID,  m_iMonsterIndex, (HT_ANIM_STATE)m_nMonster_ResentAnm, nLoop );
}

//----------���� �������� ������ - ȭ��󿡼� ������ ��----------//
HTvoid HTMonster::HT_vMonsterSet_physical_CellMove( HTfloat fElapsedTime )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return;

	if( m_nMonster_Live == MONSTER_STATE_LIVE )
	{
		if( m_cMoveMonster->m_bMonsterMoveState == HT_TRUE )
		{
			//---------������ �̵�----------//
			m_cMoveMonster->HT_vMonsterMoving( fElapsedTime );
			m_cMoveMonster->HT_bMonsterCheckMove();
			//	�ִϸ��̼� ��Ʈ��_�ȱ�/�ٱ� ��Ʈ��
			this->HT_vMonster_AnimationControl_WlkRun();
		}
		else
		{		
			HTbool bResult = m_cMoveMonster->HT_pGetMonster_ResentMoveStatus();
			if( bResult == HT_FALSE )
			{
				if( m_nMonster_ResentAnm == HT_ANISTATE_RUN || m_nMonster_ResentAnm == HT_ANISTATE_WLK )
				{
					m_nMonster_ResentAnm = HT_ANISTATE_STD;
					HT_vMonster_SetAnimation( -1 );
					//-----���� ���̵� ������ ����-----//
					m_nMonster_IdlDelay = GetTickCount();
				}
			}
		}
		//----------Ÿ�ݰ� ���� �зȴٰ� ���ƿ���_��Ʈ��----------//
		//if( m_cMoveMonster->m_bMonster_Push_Sw == HT_TRUE )
		//{
        //    m_cMoveMonster->HT_vMonsterMove_HitPushMove();
		//}

		g_pEngineHandler->HT_hrRotateObject( m_iMonsterModelID, m_cMoveMonster->HT_fGetMonsterDirect() );
		g_pEngineHandler->HT_hrMoveObject( m_iMonsterModelID, m_cMoveMonster->HT_vecGetMonsterPos() );
	}
}

//---------���� �޾��� ��_�´� �׼� ��----------//
HTbool HTMonster::HT_vMonster_SetDisAttackOn( DWORD dwSkillIndex, BYTE byLevel, HTfloat fDirect, HTint iItemIndex )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return HT_TRUE;

	m_bMonster_DisAttackSw = HT_TRUE;
	//---------���� �޾��� ��_����Ʈ ����Ʈ Ʋ���ֱ�----------//
	this->m_vMonsterAttack_ImpactEffect( dwSkillIndex, byLevel, iItemIndex );

	//	�ø�Ŀ
	g_pEngineHandler->HT_hrFlickerObject( m_iMonsterModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	������
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iMonsterModelID, HT_FALSE );

	// �ʿ���� �Լ����� ���� (20031226, daeho)
	//---------���� ���÷��� ����----------//
	//this->HT_vMonster_SetInfoDisplay();

	//	�������� �ƴҶ��� �´� �׼�
    if( m_bMonster_AttackSw == HT_FALSE && m_cMoveMonster->m_bMonsterMoveState != HT_TRUE )
	{
		//---------�´� �ִϸ��̼�----------//
		m_nMonster_ResentAnm = HT_ANISTATE_HIT;
		HT_vMonster_SetAnimation( 1 );
	}
	else	// �´� ���ϸ��̼��� ������ �ʴ´ٸ� �´� �Ҹ��� �����Ѵ�.
	{
		g_pEngineHandler->HT_hrPlayHitSound( m_iMonsterIndex, m_iMonsterModelID );
	}

	//	�¾��� �� ���� ������ �����ֱ�
	if( m_cMoveMonster->m_bMonsterSize <= 1 )
	{
		m_iMonster_ScaleIndex = 1;
		m_fMonster_ScaleValue = 0.0f;
		m_fMonster_ScaleValueTrans = 0.075f;
	}

	//	������ �־�����
	//  �¾����� ���߱� ���� �̵����϶��� �̵� ���� ����
	//	�¾����� �и���

	return HT_TRUE;
}

//---------HP ������� üũ----------//
HTint HTMonster::HT_vMonster_SetHPCheck( DWORD dwInvadeKeyID, HTint nCurHP, HTint nDamageHP, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID )
{
	//	���⼭�� ���Ա��� ������ �������� ��� �޽����� ���ƿ� ������찡 �����ϱ� ���� �״� �ִϸ��̼� ������ üũ
	if( m_nMonster_ResentAnm == HT_ANISTATE_DIE )
        return ATTACK_DAMAGEERRORVALUE;

	if( nCurHP == ATTACK_DAMAGEERRORVALUE || nDamageHP == ATTACK_DAMAGEERRORVALUE )
		return ATTACK_DAMAGEERRORVALUE;
	
	if( nCurHP < 0 || nCurHP > m_nMonster_Resent_HP )
	{
		m_nMonster_HitCount = 0;
	}
	else
	{
		m_nMonster_HitCount = nDamageHP;
		m_nMonster_Resent_HP = nCurHP;
	}

	//	����ĳ���Ͱ� ���������� HP UI �ý��ۿ� ǥ��
	if( m_bAttack_FromMainChar && m_nMonster_HitCount != 0 )
	{
		g_pMainBar->HT_vSetObjectHPDraw( m_nMonster_Resent_HP, m_nMonster_MAX_HP );

        //	�ý���â�� �޽��� �ѷ��ֱ�.
		char chName[SZNAME_LENGTH];
		CHTString::HT_hrStringCopy( chName, m_strName, SZNAME_LENGTH);
		CHTString strMessage;
		strMessage.HT_szFormat( "%s���� ������ %d��(��) �־����ϴ�.", chName, m_nMonster_HitCount );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ATTACK, strMessage );
	}

	//	�� �������� ����Ʈ�� ������ ���� ��� ����
	m_byMonster_InvadeType = byInvadeType;
	m_dwMonster_InvadeKeyID = dwInvadeKeyID;
	m_vecMonster_TargetPos = vecInvadePos;
	m_nMonster_InvadeModelID = nInvadeModelID;

	if( m_nMonster_Resent_HP <= 0 )
	{
		//---------���� �׾����� ���������͵�----------//
		m_vMonster_WhenDeathEffect();
	}

	return m_nMonster_HitCount;
}

//---------���� ���÷��� ����----------//
HTvoid HTMonster::HT_vMonster_SetInfoDisplay(HTbool bAttack)
{
	m_bMonster_InfoShow_Sw = HT_TRUE;

	if( !g_bGamePlayMovieForGlobal )
	{
		if( m_nTargettingEffectID == -1 )
		{
			if (bAttack)
				g_pEngineHandler->HT_hrStartSFX( &m_nTargettingEffectID, HT_FX_MONSTERATTACK, m_iMonsterModelID, HT_TRUE );
			else
				g_pEngineHandler->HT_hrStartSFX( &m_nTargettingEffectID, HT_FX_MONSTERTARGETING, m_iMonsterModelID, HT_TRUE );
		}
	}
}

//---------���� ���÷��� �������----------//
HTvoid HTMonster::HT_vMonster_SetInfoCancel()
{
	m_bMonster_InfoShow_Sw = HT_FALSE;
	if( m_nTargettingEffectID != -1 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_nTargettingEffectID );
		m_nTargettingEffectID = -1;
	}
}

//----------��Ʈ��ũ_END----------//
HTvoid HTMonster::HT_vMonsterSet_logical_CellEnd( MSG_Action* info )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
	{
		return;
	}
    HTPoint pPt = m_cMoveMonster->HT_pGetMonsterCellPos();
	if( pPt.x == info->TargetX && pPt.y == info->TargetY )
		return;

	m_byMonster_ActonEffect	= info->Effect;
	m_cMoveMonster->HT_vMonsterMove_SetEnd( info->TargetX, info->TargetY, info->Speed );

	//	imsi
	m_snMonster_TargetX = info->TargetX;
	m_snMonster_TargetZ = info->TargetY;

	//	�ִϸ��̼� ��Ʈ��_�ȱ�/�ٱ� ��Ʈ��
	this->HT_vMonster_AnimationControl_WlkRun();
}

//-----------������ ���� ȸ��-----------//
HTvoid HTMonster::HT_vMonster_RotateAttack( HTvector3 vecTargetPos )
{
	HTvector3 vecMyPos = m_cMoveMonster->HT_vecGetMonsterPos();
	HTvector3 vecPos = vecTargetPos - vecMyPos;

	HTfloat fDirect = m_cMoveMonster->HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecPos ) + HT_PIX2;
	m_cMoveMonster->HT_vSetMonsterDirect( fDirect );

	if( fDirect < 0.0f || fDirect > HT_PI*4 )
		return;
	g_pEngineHandler->HT_hrRotateObject( m_iMonsterModelID, m_cMoveMonster->HT_fGetMonsterDirect() );
}

//-----------������ ��������Ʈ���� ����----------//
HTvoid HTMonster::HT_vMonster_AttackPointCheck()
{
	//-----����Ŭ���� ����-----//
	m_sMonster_AttackFactor->strAttackName = m_strName;
	m_sMonster_AttackFactor->byAttacker = 0x02;
	m_sMonster_AttackFactor->byTargetType = m_byMonster_AttackTarget;
	m_sMonster_AttackFactor->byTribe = 0x01;
	m_sMonster_AttackFactor->dwAttackKeyID = m_iMonsterKeyID;
	m_sMonster_AttackFactor->dwTargetKeyID = m_dwMonster_TargetKeyID;
	m_sMonster_AttackFactor->nAttackType = m_byMonster_AttackType;
	m_sMonster_AttackFactor->nCharModelID = m_iMonsterModelID;
	m_sMonster_AttackFactor->vecSourcePos = m_cMoveMonster->HT_vecGetMonsterPos();
	m_sMonster_AttackFactor->vecTargetPos = m_vecMonster_TargetPos;
	m_sMonster_AttackFactor->fDirect = m_cMoveMonster->HT_fMonsterGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), 
		m_sMonster_AttackFactor->vecTargetPos-m_sMonster_AttackFactor->vecSourcePos ) + HT_PIX2;
	m_sMonster_AttackFactor->nAttackItemID = 0;
	m_sMonster_AttackFactor->nAttackSkillID = m_dwMonster_Skill;
	m_sMonster_AttackFactor->byAttackSkillIDLevel = 1;
	g_cAttackMgr->HT_vAttackMgr_Create( m_sMonster_AttackFactor );

	//	�����ڿ��� Damage
	if( m_byMonster_AttackTarget == 0x03 )
        g_cMainCharacter->HT_nMainChar_SetDemageHP( m_strName, m_nMonster_DamageHP );

	//	������ ǥ��
	if( !g_bGamePlayMovieForGlobal )
        g_cHitCountMgr->HT_vHitCountMgr_Create( 0, m_nMonster_DamageHP, m_vecMonster_TargetPos );

	////	Ŀ��Ƽ�����϶� ����Ʈ
	//if( m_byMonster_CriticalHit == 1 )
	//{
	//	HTint iTargetModelID = 0;
	//	//	MainCharacter
	//	if( m_dwMonster_TargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	//		iTargetModelID = g_cMainCharacter->HT_vMainChar_GetModelID();
	//	//	OtherChar
	//	else if( SERVEROBJECT_IS_CHARACTER( m_dwMonster_TargetKeyID ) )
	//		//iTargetModelID = g_cOtherCharSystem->HT_dOtherCharSystem_GetModelID( m_dwMonster_TargetKeyID );
	//		iTargetModelID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_dwMonster_TargetKeyID );
	//	//	MOB
	//	else if( SERVEROBJECT_IS_MONSTER( m_dwMonster_TargetKeyID ) )
	//		iTargetModelID = g_sMonsterSystem->HT_strMonsterSystem_GetModelIDbyKeyID( m_dwMonster_TargetKeyID );
	//	HTint idFx;
	//	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CRITICALIMPACT, iTargetModelID, HT_FALSE );
	//}
}

//-----------���Ͱ� �״´�----------//
HTvoid HTMonster::HT_vMonster_Network_Death()
{
	m_nMonster_Resent_HP		= 0;
	m_bMonster_Death_Sw			= HT_TRUE;
	m_bMonster_Death_Delay		= GetTickCount();
}

//-----------���Ͱ� �ڷ���Ʈ �Ѵ�----------//
HTvoid HTMonster::HT_vMonster_Network_Teleport()
{
	m_nMonster_Resent_HP		= 0;
	m_bMonster_Death_Sw			= HT_TRUE;
	m_bMonster_Death_Delay		= GetTickCount();

	HTint nFXTempID;
	g_pEngineHandler->HT_hrStartSFX( &nFXTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), m_iMonsterModelID, HT_FALSE );
}

//	���ݹ޾����� ���� ������
HTvoid HTMonster::HT_vMonster_ScaleControl()
{
	if( m_iMonster_ScaleIndex == 0 )
		return;
	else if( m_iMonster_ScaleIndex == 1 )
	{
		m_fMonster_ScaleValue += m_fMonster_ScaleValueTrans;
		m_fMonster_ScaleValueTrans /= 2.5;
		if( m_fMonster_ScaleValueTrans < 0.01f )
			m_iMonster_ScaleIndex = 2;
	}
	else if( m_iMonster_ScaleIndex == 2 )
	{
		//m_fMonster_ScaleValue -= m_fMonster_ScaleValueTrans;
		//m_fMonster_ScaleValueTrans *= 2.5f;
		//if( m_fMonster_ScaleValueTrans > 0.5f )
		{
            m_iMonster_ScaleIndex = 0;
			//---------������ ��Ų�� ������----------//
			g_pEngineHandler->HT_hrScaleObject( m_iMonsterModelID, HTvector3( 1.0f, 1.0f, 1.0f ) );
			return;
		}
	}
	
	//---------������ ��Ų�� ������----------//
	g_pEngineHandler->HT_hrScaleObject( m_iMonsterModelID, HTvector3( 1.0f+m_fMonster_ScaleValue, 1.0f+m_fMonster_ScaleValue, 1.0f+m_fMonster_ScaleValue ) );
}

//	���Ͱ� ������ ��
HTvoid HTMonster::HT_vMonster_Network_SCP_Msg_Attack( S_MSG_ATTACK_OTHERMOB info )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return;

	m_nMonster_Resent_HP		= info.iCasterHP;
	m_byMonster_CriticalHit		= info.snRes;
	m_byMonster_AttackType		= MAINCHAR_ATTACKTYPE_SKILL;

	//	1:OtherCharecter, 2:Monster, 3:MainCharacter
	m_byMonster_AttackTarget	= info.byTargetType;

	m_dwMonster_TargetKeyID		= info.krgTarget[0].snKeyID;	//	���ݹ��� ����� KeyID
	m_dwMonster_Skill			= info.iSkillID;				//	������ ���
	m_vecMonster_TargetPos		= info.vecTargetPos;			//	���ݴ���� ��ġ
	
	//----------���� �Ҷ� �Ÿ� ���߾� �ֱ�----------//
	//m_cMoveMonster->HT_vMonsterMove_AttacnceCheck( info.PosX, info.PosY, m_vecMonster_TargetPos );

	//	��ų ��Ƽ����Ʈ ����Ʈ Ʋ��
	if( m_dwMonster_Skill != -1 )
	{
		HTint nEffectTempID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectTempID, m_dwMonster_Skill, HT_SFX_WHEN_ACTIVATE, m_iMonsterModelID, HT_FALSE );
	}
	//	���� ��������� ȸ��
	this->HT_vMonster_RotateAttack( m_vecMonster_TargetPos );

	//	���� �ִϸ��̼� ƴ
	g_pEngineHandler->HT_hrChangeMonsterAttackAnimation( m_iMonsterModelID, m_iMonsterIndex, m_dwMonster_Skill, 1 );

	//-----���� ���̵� ������ ����-----//
	m_nMonster_IdlDelay = GetTickCount();

	//	���� ����
	m_bMonster_AttackSw = HT_TRUE;

	//	�������� Damage
	m_nMonster_DamageHP = info.krgTarget[0].snDamage;

	//	imsi
	m_snMonster_TargetX = info.TargetX;
	m_snMonster_TargetZ = info.TargetZ;
}
