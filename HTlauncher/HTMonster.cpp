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
	//-----몬스터 HP 표현하기위해 메인캐릭터가 때렸을때만-----//
	m_bAttack_FromMainChar			= HT_FALSE;

	//-----이펙트 관련 인덱스-----//
	m_nTargettingEffectID			= -1;
	m_byMonster_InvadeType			= 0x00;
	m_iMonster_ScaleIndex			= 0;			//	스케일 인덱스
	m_nMonster_TargetHP				= ATTACK_DAMAGEERRORVALUE;
	m_nMonster_DamageHP				= ATTACK_DAMAGEERRORVALUE;
	m_byMonster_ActonEffect			= 0;

	//	공격 인자 생성
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


//----------몬스터 생성----------//
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

	//	몬스터의 위치를 셋팅하고
	m_cMoveMonster->HT_fSetMonsterPos( vecPos );
	m_cMoveMonster->HT_vSetMonsterlogical_Cell( info->snTargetX, info->snTargetZ );
	m_cMoveMonster->HT_vSetMonsterphysical_Cell( info->snTargetX, info->snTargetZ );
	
	//	몬스터의 정보를 가져오고
	//------------------------------------------------------------------
	// New Param - 선미
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

	//	몬스터의 모델을 생성하고
	m_iMonsterModelID				= g_pEngineHandler->HT_iCreateMonster( m_iMonsterIndex, m_cMoveMonster->HT_vecGetMonsterPos() );
	//	몬스터 모델 사이즈
	m_fMonsterModelHeight			= g_pEngineHandler->HT_fGetObjHeight( m_iMonsterModelID );

    //-----HP관련----//
	m_nMonster_MAX_HP				= info->nMaxHP;
	m_nMonster_Resent_HP			= info->nCurHP;
	//-----정보 디스플레이-----//
	m_bMonster_InfoShow_Sw			= HT_FALSE;

	m_bMonster_Death_Delay			= GetTickCount();

	if( m_nMonster_Resent_HP == 0 )
	{
		m_nMonster_ResentAnm		= HT_ANISTATE_DIE;
		HT_vMonster_SetAnimation( 1 );
	}

	//-----공격 관련----//
	m_bMonster_AttackSw				= HT_FALSE;
	m_bMonster_DisAttackSw			= HT_FALSE;

	//-----몬스터의 생명----//
	m_nMonster_Live					= MONSTER_STATE_LIVE;
	m_bMonster_Death_Sw				= HT_FALSE;

	//-----맞았을때 이동중이면 이동정보 저장-----//
	m_bMOnster_HitMove_Sw			= HT_FALSE;

	//-----탄생 FX 시동-----//
	BYTE byAoi = g_cAoi->HT_AOI_Level( m_cMoveMonster->HT_pGetMonsterGrid() );
	if( byAoi == AOI_LEVEL_1 || byAoi == AOI_LEVEL_CREATE )
	{
		HTint nFXTempID;
		g_pEngineHandler->HT_hrStartSFX( &nFXTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), m_iMonsterModelID, HT_FALSE );
	}

	//	기본 애니매이션을 시켜주고
    m_nMonster_ResentAnm				= HT_ANISTATE_STD;
	g_pEngineHandler->HT_hrStartAnimation( m_iMonsterModelID,  m_iMonsterIndex, HT_ANISTATE_STD, -1 );

	//-----몬스터 아이들 동작을 위해-----//
	m_nMonster_IdlDelay					= GetTickCount() + ( rand()%IDLE_MONSTER_TIME );

	//	초기 몬스터의 방향 랜덤하게 뿌려주기
	m_cMoveMonster->HT_vSetMonsterDirect( (HTfloat)( byInitDirect * 0.78f ) + 3.14f );
	g_pEngineHandler->HT_hrRotateObject( m_iMonsterModelID, m_cMoveMonster->HT_fGetMonsterDirect() );
}

//----------몬스터 업데이트----------//
HTvoid HTMonster::HT_vMonsterUpdate( HTfloat fElapsedTime )
{
	//----------몬스터 물리적인 셀무브 - 화면상에서 움직일 때----------//
	HT_vMonsterSet_physical_CellMove( fElapsedTime );

	//----------애니매이션 컨트롤과 그에따른 처리----------//
	HT_vMonster_AnimationControl();

	//---------업데이트_죽음에 관하여----------//
	HT_vMonsterUpdate_Death();

	//	공격받았을때 몬스터 스케일
	HT_vMonster_ScaleControl();
}

//---------업데이트_죽음에 관하여----------//
HTvoid HTMonster::HT_vMonsterUpdate_Death()
{
	if( m_bMonster_Death_Sw == HT_TRUE )
	{
		DWORD dwPassTime = GetTickCount();

		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		if ( dwPassTime > m_bMonster_Death_Delay + 2000 && dwPassTime < m_bMonster_Death_Delay + 10000 )	// 죽은지 10초 미만이고 
		{
			//---------이펙트_몬스터 죽었을때 여러가지것들----------//
			if ( m_nMonster_ResentAnm != HT_ANISTATE_DIE )	// 한번만 실행하기 위한거 같다.
				m_vMonster_WhenDeathEffect();
		}
		// 죽은 다음 일정 시간이 지나면 땅속으로 가라앉는다.
		else if ( ( dwPassTime > m_bMonster_Death_Delay + 10000 ) && ( dwPassTime < m_bMonster_Death_Delay + 15000 ) )	
		{
			HTvector3 vecPos = m_cMoveMonster->HT_vecGetMonsterPos();
			vecPos.y -= (HTfloat)(dwPassTime-m_bMonster_Death_Delay-10000)*(20.0f/5000.0f);
			g_pEngineHandler->HT_hrMoveObject( m_iMonsterModelID, vecPos, HT_FALSE );
		}
		else if( dwPassTime > m_bMonster_Death_Delay + 15000 ) // 죽은 다음의 시간을 좀 더 길게 한다. 드디어 없어진다.
		{
			m_nMonster_Live = MONSTER_STATE_DEATH;
		}
	}
}

//----------애니매이션 컨트롤과 그에따른 처리----------//
HTvoid HTMonster::HT_vMonster_AnimationControl()
{
	if( m_bMonster_Death_Sw == HT_TRUE )
	{
		//	몬스터의 이동 중일때
		if( m_nMonster_ResentAnm==HT_ANISTATE_STD || m_nMonster_ResentAnm==HT_ANISTATE_RUN )
		{
			//	그야말로 하드코딩해서 억지로 해결했기때문에 데이타를 분석해서 차후 꼭 수정해야함
			if( g_bDevelopingMode )
			{
				if( m_iMonsterIndex != 2014 &&				//	헤루카가 아니고
					m_iMonsterIndex != 2015 )				//	아즈나 헤루카가 아닐때만
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
		//-----------몬스터의 공격포인트에서 할일----------//
		this->HT_vMonster_AttackPointCheck();
	}
	else if( sAnmState == HT_AS_STOP )
	{
		//---------공격 애니매이션 이후----------//
		if( m_bMonster_AttackSw == HT_TRUE )
		{
			m_bMonster_AttackSw = HT_FALSE;
			m_nMonster_ResentAnm = HT_ANISTATE_STD;
			HT_vMonster_SetAnimation( -1 );
			//-----몬스터 아이들 동작을 위해-----//
			m_nMonster_IdlDelay = GetTickCount();
		}
		//---------공격받은 애니매이션 이후----------//
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
				//-----몬스터 아이들 동작을 위해-----//
				m_nMonster_IdlDelay = GetTickCount();
			}
			HT_vMonster_SetAnimation( -1 );
		}
		else
		{
			m_nMonster_ResentAnm = HT_ANISTATE_STD;
			//-----몬스터 아이들 동작을 위해-----//
			m_nMonster_IdlDelay = GetTickCount();
			HT_vMonster_SetAnimation( -1 );
			//-----몬스터 아이들 동작을 위해-----//
			m_nMonster_IdlDelay = GetTickCount();
		}
	}

	//-----몬스터 아이들 동작을 위해-----//
    if( m_nMonster_ResentAnm == HT_ANISTATE_STD && m_nMonster_ResentAnm != HT_ANISTATE_IDL )
	{
		DWORD dwPassTime = GetTickCount();
		if( dwPassTime > m_nMonster_IdlDelay + IDLE_MONSTER_TIME )
		{
			//	그야말로 하드코딩해서 억지로 해결했기때문에 데이타를 분석해서 차후 꼭 수정해야함
			if( g_bDevelopingMode )
			{
				if( m_iMonsterIndex != 2014 &&				//	헤루카가 아니고
					m_iMonsterIndex != 2015 )				//	아즈나 헤루카가 아닐때만
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

//----------애니매이션 컨트롤_걷기/뛰기 컨트롤----------//
HTvoid HTMonster::HT_vMonster_AnimationControl_WlkRun()
{
	//	걸을때
	if( m_byMonster_ActonEffect == 2 )
	{
		if( m_nMonster_ResentAnm != HT_ANISTATE_WLK )
		{
			m_nMonster_ResentAnm = HT_ANISTATE_WLK;
			HT_vMonster_SetAnimation( -1 );
		}
	}
	//	뛸때
	else if( m_byMonster_ActonEffect == 3 )
	{
		if( m_nMonster_ResentAnm != HT_ANISTATE_RUN )
		{
			m_nMonster_ResentAnm = HT_ANISTATE_RUN;
			HT_vMonster_SetAnimation( -1 );
		}
	}
}

//---------이펙트_임팩트 이펙트 틀어주기----------//
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

//---------이펙트_몬스터 죽었을때 여러가지것들----------//
HTvoid HTMonster::m_vMonster_WhenDeathEffect()
{
	m_bMonster_Death_Sw	= HT_TRUE;

	//	죽는 애니매이션 틀어주기
	m_nMonster_ResentAnm = HT_ANISTATE_DIE;
	HT_vMonster_SetAnimation( 1 );

	// 죽는 애니메이션을 하는 동안은 그림자를 그리지 않는다.
	g_pEngineHandler->HT_hrShowShadow( m_iMonsterModelID, HT_FALSE );

	//---------정보 디스플레이 셋팅취소----------//
	this->HT_vMonster_SetInfoCancel();

	//	메인캐릭터가 때렸을때만 HP UI 시스템에 표현
	if( m_bAttack_FromMainChar )
	{
		g_pMainBar->HT_vSetObjectHPOut();
		//g_pMainBar->HT_vSetObjectHPDraw( m_nMonster_Resent_HP, m_nMonster_MAX_HP );
	}

	//	죽을때의 딜레이 시간을 위해
	m_bMonster_Death_Delay		= GetTickCount();

	//	몬스터 죽을때 몬스터의 혼이 빠져나가기
	HTint imsiID;
	g_pEngineHandler->HT_hrStartSFX( &imsiID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), HT_SFX_WHEN_ACTIVATE, m_iMonsterModelID, HT_FALSE );

	// 죽고나서 시체가 완전히 사라질때까지는 픽킹이 되지 않아야 한다.
	g_pEngineHandler->HT_hrDontClickIt( m_iMonsterModelID );

	//	몬스터 죽을때 캐릭터쪽으로 프라나 이펙트 빨려들어가기
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

	//	튜토리얼 시스템을 위함
	if( m_byMonster_InvadeType == 0x03 )
        g_cTutorialSystem->HT_Tutorial_StepCheck_MsgResult( TUTORIAL_STEP_HUNTINGMONSTER );
}

//---------애니매이션 셋팅----------//
HTvoid HTMonster::HT_vMonster_SetAnimation( HTint nLoop )
{
    g_pEngineHandler->HT_hrChangeAnimation( m_iMonsterModelID,  m_iMonsterIndex, (HT_ANIM_STATE)m_nMonster_ResentAnm, nLoop );
}

//----------몬스터 물리적인 셀무브 - 화면상에서 움직일 때----------//
HTvoid HTMonster::HT_vMonsterSet_physical_CellMove( HTfloat fElapsedTime )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return;

	if( m_nMonster_Live == MONSTER_STATE_LIVE )
	{
		if( m_cMoveMonster->m_bMonsterMoveState == HT_TRUE )
		{
			//---------몬스터의 이동----------//
			m_cMoveMonster->HT_vMonsterMoving( fElapsedTime );
			m_cMoveMonster->HT_bMonsterCheckMove();
			//	애니매이션 컨트롤_걷기/뛰기 컨트롤
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
					//-----몬스터 아이들 동작을 위해-----//
					m_nMonster_IdlDelay = GetTickCount();
				}
			}
		}
		//----------타격감 관련 밀렸다가 돌아오기_컨트롤----------//
		//if( m_cMoveMonster->m_bMonster_Push_Sw == HT_TRUE )
		//{
        //    m_cMoveMonster->HT_vMonsterMove_HitPushMove();
		//}

		g_pEngineHandler->HT_hrRotateObject( m_iMonsterModelID, m_cMoveMonster->HT_fGetMonsterDirect() );
		g_pEngineHandler->HT_hrMoveObject( m_iMonsterModelID, m_cMoveMonster->HT_vecGetMonsterPos() );
	}
}

//---------공격 받았을 때_맞는 액션 온----------//
HTbool HTMonster::HT_vMonster_SetDisAttackOn( DWORD dwSkillIndex, BYTE byLevel, HTfloat fDirect, HTint iItemIndex )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return HT_TRUE;

	m_bMonster_DisAttackSw = HT_TRUE;
	//---------공격 받았을 때_임펙트 이펙트 틀어주기----------//
	this->m_vMonsterAttack_ImpactEffect( dwSkillIndex, byLevel, iItemIndex );

	//	플리커
	g_pEngineHandler->HT_hrFlickerObject( m_iMonsterModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );

	//	라이팅
	HTint nEffectLightterID;
	g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_iMonsterModelID, HT_FALSE );

	// 필요없는 함수여서 삭제 (20031226, daeho)
	//---------정보 디스플레이 셋팅----------//
	//this->HT_vMonster_SetInfoDisplay();

	//	공격중이 아닐때만 맞는 액션
    if( m_bMonster_AttackSw == HT_FALSE && m_cMoveMonster->m_bMonsterMoveState != HT_TRUE )
	{
		//---------맞는 애니매이션----------//
		m_nMonster_ResentAnm = HT_ANISTATE_HIT;
		HT_vMonster_SetAnimation( 1 );
	}
	else	// 맞는 에니메이션이 나오지 않는다면 맞는 소리라도 나야한다.
	{
		g_pEngineHandler->HT_hrPlayHitSound( m_iMonsterIndex, m_iMonsterModelID );
	}

	//	맞았을 때 몬스터 스케일 시켜주기
	if( m_cMoveMonster->m_bMonsterSize <= 1 )
	{
		m_iMonster_ScaleIndex = 1;
		m_fMonster_ScaleValue = 0.0f;
		m_fMonster_ScaleValueTrans = 0.075f;
	}

	//	예전에 있었던것
	//  맞았을때 멈추기 위해 이동중일때는 이동 정보 저장
	//	맞았을때 밀리기

	return HT_TRUE;
}

//---------HP 변경사항 체크----------//
HTint HTMonster::HT_vMonster_SetHPCheck( DWORD dwInvadeKeyID, HTint nCurHP, HTint nDamageHP, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID )
{
	//	여기서의 진입금지 조건은 서버에서 사망 메시지가 날아와 있을경우가 있으니까 몬스터 죽는 애니매이션 온으로 체크
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

	//	메인캐릭터가 때렸을때만 HP UI 시스템에 표현
	if( m_bAttack_FromMainChar && m_nMonster_HitCount != 0 )
	{
		g_pMainBar->HT_vSetObjectHPDraw( m_nMonster_Resent_HP, m_nMonster_MAX_HP );

        //	시스템창에 메시지 뿌려주기.
		char chName[SZNAME_LENGTH];
		CHTString::HT_hrStringCopy( chName, m_strName, SZNAME_LENGTH);
		CHTString strMessage;
		strMessage.HT_szFormat( "%s에게 데미지 %d를(을) 주었습니다.", chName, m_nMonster_HitCount );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ATTACK, strMessage );
	}

	//	피 빨려가는 이펙트를 날리기 위한 몇가지 사항
	m_byMonster_InvadeType = byInvadeType;
	m_dwMonster_InvadeKeyID = dwInvadeKeyID;
	m_vecMonster_TargetPos = vecInvadePos;
	m_nMonster_InvadeModelID = nInvadeModelID;

	if( m_nMonster_Resent_HP <= 0 )
	{
		//---------몬스터 죽었을때 여러가지것들----------//
		m_vMonster_WhenDeathEffect();
	}

	return m_nMonster_HitCount;
}

//---------정보 디스플레이 셋팅----------//
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

//---------정보 디스플레이 셋팅취소----------//
HTvoid HTMonster::HT_vMonster_SetInfoCancel()
{
	m_bMonster_InfoShow_Sw = HT_FALSE;
	if( m_nTargettingEffectID != -1 )
	{
        g_pEngineHandler->HT_hrStopSFX( m_nTargettingEffectID );
		m_nTargettingEffectID = -1;
	}
}

//----------네트워크_END----------//
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

	//	애니매이션 컨트롤_걷기/뛰기 컨트롤
	this->HT_vMonster_AnimationControl_WlkRun();
}

//-----------공격을 위한 회전-----------//
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

//-----------몬스터의 공격포인트에서 할일----------//
HTvoid HTMonster::HT_vMonster_AttackPointCheck()
{
	//-----공격클래스 생성-----//
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

	//	공격자에게 Damage
	if( m_byMonster_AttackTarget == 0x03 )
        g_cMainCharacter->HT_nMainChar_SetDemageHP( m_strName, m_nMonster_DamageHP );

	//	데미지 표시
	if( !g_bGamePlayMovieForGlobal )
        g_cHitCountMgr->HT_vHitCountMgr_Create( 0, m_nMonster_DamageHP, m_vecMonster_TargetPos );

	////	커리티컬힛일때 이펙트
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

//-----------몬스터가 죽는다----------//
HTvoid HTMonster::HT_vMonster_Network_Death()
{
	m_nMonster_Resent_HP		= 0;
	m_bMonster_Death_Sw			= HT_TRUE;
	m_bMonster_Death_Delay		= GetTickCount();
}

//-----------몬스터가 텔레포트 한다----------//
HTvoid HTMonster::HT_vMonster_Network_Teleport()
{
	m_nMonster_Resent_HP		= 0;
	m_bMonster_Death_Sw			= HT_TRUE;
	m_bMonster_Death_Delay		= GetTickCount();

	HTint nFXTempID;
	g_pEngineHandler->HT_hrStartSFX( &nFXTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_iMonsterIndex), m_iMonsterModelID, HT_FALSE );
}

//	공격받았을때 몬스터 스케일
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
			//---------스케일 시킨것 돌리기----------//
			g_pEngineHandler->HT_hrScaleObject( m_iMonsterModelID, HTvector3( 1.0f, 1.0f, 1.0f ) );
			return;
		}
	}
	
	//---------스케일 시킨것 돌리기----------//
	g_pEngineHandler->HT_hrScaleObject( m_iMonsterModelID, HTvector3( 1.0f+m_fMonster_ScaleValue, 1.0f+m_fMonster_ScaleValue, 1.0f+m_fMonster_ScaleValue ) );
}

//	몬스터가 공격을 함
HTvoid HTMonster::HT_vMonster_Network_SCP_Msg_Attack( S_MSG_ATTACK_OTHERMOB info )
{
	if( m_bMonster_Death_Sw	== HT_TRUE )
		return;

	m_nMonster_Resent_HP		= info.iCasterHP;
	m_byMonster_CriticalHit		= info.snRes;
	m_byMonster_AttackType		= MAINCHAR_ATTACKTYPE_SKILL;

	//	1:OtherCharecter, 2:Monster, 3:MainCharacter
	m_byMonster_AttackTarget	= info.byTargetType;

	m_dwMonster_TargetKeyID		= info.krgTarget[0].snKeyID;	//	공격받은 대상의 KeyID
	m_dwMonster_Skill			= info.iSkillID;				//	몬스터의 기술
	m_vecMonster_TargetPos		= info.vecTargetPos;			//	공격대상의 위치
	
	//----------공격 할때 거리 맞추어 주기----------//
	//m_cMoveMonster->HT_vMonsterMove_AttacnceCheck( info.PosX, info.PosY, m_vecMonster_TargetPos );

	//	스킬 액티베이트 이펙트 틀기
	if( m_dwMonster_Skill != -1 )
	{
		HTint nEffectTempID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectTempID, m_dwMonster_Skill, HT_SFX_WHEN_ACTIVATE, m_iMonsterModelID, HT_FALSE );
	}
	//	방향 상대편으로 회전
	this->HT_vMonster_RotateAttack( m_vecMonster_TargetPos );

	//	공격 애니매이션 틈
	g_pEngineHandler->HT_hrChangeMonsterAttackAnimation( m_iMonsterModelID, m_iMonsterIndex, m_dwMonster_Skill, 1 );

	//-----몬스터 아이들 동작을 위해-----//
	m_nMonster_IdlDelay = GetTickCount();

	//	공격 셋팅
	m_bMonster_AttackSw = HT_TRUE;

	//	공격자의 Damage
	m_nMonster_DamageHP = info.krgTarget[0].snDamage;

	//	imsi
	m_snMonster_TargetX = info.TargetX;
	m_snMonster_TargetZ = info.TargetZ;
}
