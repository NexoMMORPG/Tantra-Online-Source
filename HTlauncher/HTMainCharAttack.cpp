#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htmaincharattack.h"


#define FOLLOWATTACK_NONE				0
#define FOLLOWATTACK_FOLLOWSKILL		1 
#define FOLLOWATTACK_FOLLOWDART			2

// 새로운UI수정(20030728)
//	0:OtherChar, 2:Monster, 3:CriticalHit
HTint g_nHitNumber[3][10] = { 23887, 23888, 23889, 23890, 23891, 23892, 23893, 23894, 23895, 23896,
							  23867, 23868, 23869, 23870, 23871, 23872, 23873, 23874, 23875, 23876,
							  23877, 23878, 23879, 23880, 23881, 23882, 23883, 23884, 23885, 23886 };

//	캠지터 ID
HTint g_nCamjitterID[3] = { HT_FX_CAMJITTER_01, HT_FX_CAMJITTER_02, HT_FX_CAMJITTER_03 };


//---------------------------------------------------------------------------------
//
//		Attack 클래스
//
//---------------------------------------------------------------------------------
HTAttack::HTAttack(void)
{
    //	모델 아이디 초기화
	m_oFollowFX.idModel			= -1;		//	널모델 / 투척무기용
	m_oFollowFX.idFX			= -1;		//	이펙트 아이디

	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	m_nAttack_LiveTime = GetTickCount();
}

HTAttack::~HTAttack(void)
{
	//	모델 아이디 지우기
	if( m_oFollowFX.idModel > 0 )		//	널모델 / 투척무기용
	{
        g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel );
		m_oFollowFX.idModel = -1;
	}
	if( m_oFollowFX.idFX != -1 )	//	이펙트 아이디
		g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );

	HT_DELETE( m_pFactor );
}

//	초기 데이타 셋팅
HTvoid HTAttack::HT_vAttack_SetInitData( P_ATTACK_FACTOR info )
{
	//	캐릭터 정보 셋팅
	m_pFactor = HT_NULL;
	m_pFactor = new S_ATTACK_FACTOR;
    memcpy( m_pFactor, info, sizeof(S_ATTACK_FACTOR) );
	
	m_pFactor->byAttackSkillIDLevel = 1;
	m_dwAttack_SkillType		= 0;
	m_bAttack_DartSw			= HT_FALSE;
	m_nAttack_Process			= ATTACKPROCESS_ATTACKPOINT;
	//	날아가는 타입
	m_iAttack_FolowType			= FOLLOWTYPE_JKSHOMER;
}

//	두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터
HTfloat HTAttack::HT_fAttackGetAngle(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	내적구하기 -> 벡터의 관계(각도)를 알기 위해
	float sqrt_A = (float)sqrt(A.x*A.x + A.z*A.z);	//  A 벡터의 절대값(길이) 구하기 
	float sqrt_B = (float)sqrt(B.x*B.x + B.z*B.z);	//  B 벡터의 절대값(길이) 구하기 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  세값을 이용해서 각도 구하기

	HTfloat acos = acosf( cos );					//	코사인값을 라디안값 바꾸기
	float direction = A.z*B.x - B.z*A.x;			//	왼쪽 오른쪽 비교
	if(direction < 0)								//	dirction 음이면 왼쪽 , 양이면 오른쪽
		acos *= -1;
	return acos;
}

//	공격 컨트롤
HTvoid HTAttack::HT_vAttack_Control( HTfloat fElapsedTime )
{
	switch( m_nAttack_Process )
	{
		case ATTACKPROCESS_ATTACKPOINT :
			HT_vAttack_AttackPoint();
			break;
		case  ATTACKPROCESS_FOLLOWEFFET :
			HT_vAttack_AttackFollowEffect( fElapsedTime );
			break;
		default :
			break;
	}

	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	HT_vAttack_LiveTimeControl();
}

//	공격 포인트에서 할일
HTvoid HTAttack::HT_vAttack_AttackPoint()
{
	//	날아가는 널모델/표창 생성
	if( HT_IS_ITEM_DART( m_pFactor->nAttackItemID ) )
	{
		m_bAttack_DartSw = HT_TRUE;
		HT_vAttack_SetWithFollow();
		return;
	}

	//	액션 스킬 타입을 얻어온다.
	m_dwAttack_SkillType = g_pEngineHandler->HT_dwGetSkillType( m_pFactor->nAttackSkillID );
	
	//	PC스킬인지 Monster스킬인지 파악!
	if( m_pFactor->byAttacker == 0x02 )		//	Monster
	{
		if( m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_NOCAST_LONG || 
			m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_YESCAST_LONG ||
			m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			this->HT_vAttack_SetWithFollow();				//	팔로우가 있는 공격
		}

		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	팔로우 없이 공격
		}
	}
	else										//	PC
	{
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			this->HT_vAttack_SetWithFollow();				//	팔로우가 있는 공격
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	팔로우 없이 공격
		}
	}
}

//	공격 포인트에서 할일_팔로우가없는 공격 셋팅
HTvoid HTAttack::HT_vAttack_SetWithOutFollow()
{
	HT_vAttack_SetAttackPoint();

	//	공격대상에게 해줘야 할것들
	if( m_pFactor->byTargetType == 0x01 )
		g_cOtherCharSystem->HT_vOtherCharSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillAttribute );
	else if( m_pFactor->byTargetType == 0x02 )
		g_sMonsterSystem->HT_vMonsterSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->fDirect, m_pFactor->byAttackSkillIDLevel );
	else if( m_pFactor->byTargetType == 0x03 )
		g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, m_pFactor->dwAttackKeyID );
	//	액션 스킬 타입이 범위공격과 피어싱이 아닐때만 틀어준다.
	else if( m_pFactor->byTargetType == 0x04 )
	{
		HTint iTempEffectID;
		g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, HT_FX_NORMALATTACKIMPACT, m_oFollowFX.idModel, HT_FALSE );
	}
}

//	공격 포인트에서 팔로우 이펙트 셋팅
HTvoid HTAttack::HT_vAttack_SetWithFollow()
{
	//	Follow(총알) 계산
	HT_vAttack_DistanceCheck();
	
	if( m_fAttack_Distance > 200.0f )
	{
		m_nAttack_Process = ATTACKPROCESS_NONE;
		return;
	}

	//	캐릭터 높이를 감안하여 Y값 보정
	m_oFollowFX.vecPos.y += 10.0f;
	//	목표위치 셋팅
	m_oFollowFX.vecTarget = m_pFactor->vecTargetPos;
	//	시간 셋팅
	m_oFollowFX.fTime = 0.0f;
	//	투척무기일때
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK )
	{
		m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateFieldItem( m_pFactor->nAttackItemID, m_oFollowFX.vecPos );
		m_nAttack_DartAngle = HT_PI;
	}
	else
	{
		m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateNullModel( m_oFollowFX.vecPos );
		g_pEngineHandler->HT_hrStartSFX( &m_oFollowFX.idFX, m_pFactor->nAttackSkillID, HT_SFX_WHEN_FOLLOW, m_oFollowFX.idModel, HT_TRUE, m_pFactor->byAttackSkillIDLevel );
	}

	//	날아가는 타입
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_Set_JKS_FlyingObject_Homer();
			break;
	}

	//	프로세스 팔로우로 넘김
	m_nAttack_Process = ATTACKPROCESS_FOLLOWEFFET;
}

// 생성시 필요한 init 부분
HTvoid HTAttack::HT_vAttack_Set_JKS_FlyingObject_Homer()
{
	// jks - 초기 속도 설정 
    //oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
    // get random number between (-2.0f ~ 2.0f)
    m_oFollowFX.curVel.x = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
    // get random number between (-2.0f ~ 2.0f)
    m_oFollowFX.curVel.z = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
    // get random number between (0.0f ~ 4.0f)
    m_oFollowFX.curVel.y = (rand()%4) + (rand() / (HTfloat)RAND_MAX); //jks
    //oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
}

//	공격 포인트에서 할일_공격 거리 계산
HTvoid HTAttack::HT_vAttack_DistanceCheck()
{
	m_pFactor->vecSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_pFactor->vecSourcePos.x, m_pFactor->vecSourcePos.z )+10;;
	m_pFactor->vecTargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_pFactor->vecTargetPos.x, m_pFactor->vecTargetPos.z )+10;
	m_fAttack_Hight = m_pFactor->vecTargetPos.y - m_oFollowFX.vecPos.y;

	HTvector3 vecVector = m_pFactor->vecTargetPos - m_pFactor->vecSourcePos;
	m_fAttack_Direct = HT_fAttackGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector );

	//	공격 갈 거리
	m_fAttack_Distance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) ) * 1.3f;
	m_fAttack_DistanceTrans	= 0;			//	공격 갈 거리 변화
}

//	팔로우 이펙트
HTvoid HTAttack::HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime )
{
	//	날아가는 타입
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			this->HT_vAttack_AttackFollowEffectGo( fElapsedTime );
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( fElapsedTime );
			break;
	}

	//	팔로우 이펙트_체크
	HT_vAttack_AttackFollowCheck();
}

//	팔로우 이펙트 go
HTvoid HTAttack::HT_vAttack_AttackFollowEffectGo( HTfloat fElapsedTime )
{
	if( fElapsedTime <= HT_EPSILON )
		return;

	//----------표창을때 회전하면서 날아가게...----------//
	if( m_bAttack_DartSw == HT_TRUE )
	{
		m_nAttack_DartAngle += 0.5f;
		if( m_nAttack_DartAngle > HT_PI + HT_PIX2 )
		{
			m_nAttack_DartAngle = HT_PI;
		}

		if ( m_oFollowFX.idModel > 0 )
			g_pEngineHandler->HT_hrRotateObject( m_oFollowFX.idModel, m_nAttack_DartAngle );
	}

	//	Follow Object 위치 구하기
	float fx, fz, fy;
	fx = sinf( m_fAttack_Direct ) * ( 200.0f*fElapsedTime );
	fz = cosf( m_fAttack_Direct ) * ( 200.0f*fElapsedTime );
	m_oFollowFX.vecPos.x += fx;
	m_oFollowFX.vecPos.z += fz;

	if( fx<0 )		fx *= -1;
	if( fz<0 )		fz *= -1;

	m_fAttack_DistanceTrans += fx + fz;
	fy = ( m_fAttack_Hight*m_fAttack_DistanceTrans ) / m_fAttack_Distance;
	m_oFollowFX.vecPos.y = m_pFactor->vecSourcePos.y + fy;

	if ( m_oFollowFX.idModel > 0 )
		g_pEngineHandler->HT_hrMoveObject( m_oFollowFX.idModel, m_oFollowFX.vecPos );
}

//	jks - code for homing flying object.
HTvoid HTAttack::HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( HTfloat fElapsedTime )
{
	m_oFollowFX.fTime += fElapsedTime;
	{
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
		HTvector3   vectorToTarget;              // jks - vector from source to destination
        HTvector3   temp;                        // jks - temporary vector

        // jks - get direction(from source to dest.) vector 
        CHTVector::HT_pvecVec3Subtract(&vectorToTarget, &m_oFollowFX.vecTarget, &m_oFollowFX.vecPos);
		CHTVector::HT_pvecVec3Normalize( &vectorToTarget, &vectorToTarget );
        // jks - velocity correction 
        CHTVector::HT_pvecVec3Scale(&temp, &m_oFollowFX.curVel,(VECTOR_CORRECTION_FACTOR-1));
        CHTVector::HT_pvecVec3Add(&temp, &temp, &vectorToTarget);
        CHTVector::HT_pvecVec3Scale(&m_oFollowFX.curVel, &temp, (1.0f/VECTOR_CORRECTION_FACTOR));
        // jks - apply speed 
        CHTVector::HT_pvecVec3Scale(&m_oFollowFX.curVel, &m_oFollowFX.curVel, (MAX_SPEED));
        // jks - update flying object position
        CHTVector::HT_pvecVec3Add(&m_oFollowFX.vecPos, &m_oFollowFX.vecPos, &m_oFollowFX.curVel);

		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
	}
}

//	팔로우 이펙트_체크
HTvoid HTAttack::HT_vAttack_AttackFollowCheck()
{
	HTfloat fDistance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) );
    
	if( m_fAttack_DistanceTrans >= m_fAttack_Distance || fDistance<5.0f )
	{
		//	널 모델 지우기
		if ( m_oFollowFX.idModel > 0 )
		{
			g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel );
			m_oFollowFX.idModel = -1;
		}

		if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_SKILL || m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );
			m_oFollowFX.idFX = -1;
		}

		//	적이 맞았을때 취해야 할 액션들
		HT_vAttack_SetAttackPoint();

		//	공격대상에게 해줘야 할것들
		if( m_pFactor->byTargetType == 0x01 )
			g_cOtherCharSystem->HT_vOtherCharSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillAttribute );
		else if( m_pFactor->byTargetType == 0x02 )
			g_sMonsterSystem->HT_vMonsterSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->fDirect, m_pFactor->byAttackSkillIDLevel );
		else if( m_pFactor->byTargetType == 0x03 )
			g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, m_pFactor->dwAttackKeyID );
		//	액션 스킬 타입이 범위공격과 피어싱이 아닐때만 틀어준다.
		else if( m_pFactor->byTargetType == 0x04 )
		{
			HTint iTempEffectID;
			g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, HT_FX_NORMALATTACKIMPACT, m_oFollowFX.idModel, HT_FALSE );
		}
	}
}

//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
HTvoid HTAttack::HT_vAttack_LiveTimeControl()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_nAttack_LiveTime+10000 )
	{
		m_nAttack_Process = ATTACKPROCESS_DAETH;
	}	
}

//	적이 맞았을때 취해야 할 액션들
HTvoid HTAttack::HT_vAttack_SetAttackPoint()
{
	//----------타격 사운드 틀어주기----------//
	if( m_pFactor->byAttacker != 0x02 || m_pFactor->nAttackItemID == 0 )			//	몬스터가 아닐경우에만
	{
		if( m_pFactor->byAttackSkillAttribute == 0x01 )
            g_pEngineHandler->HT_hrPlayAttackOKSound( m_pFactor->byTribe, m_pFactor->nAttackItemID );
	}

	//	액션 스킬 타입이 범위공격과 피어싱이 아닐때만 틀어준다.
	if( m_pFactor->byTargetType != 0x04 )
	{
		//	플리커 아니면 프나나 업 이펙트
		if( m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )
			g_pEngineHandler->HT_hrFlickerObject( m_pFactor->iTargetModelID, HT_COLOR( 1.00f, 0.10f, 0.00f, 1.0f ), 0.4f );
		else
		{
			HTint nTempID;
			g_pEngineHandler->HT_hrStartSFX( &nTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pFactor->nAttackItemID), HT_SFX_WHEN_IMPACT, m_pFactor->iTargetModelID, HT_FALSE );
		}

		//	Light
		if( m_pFactor->byMaxDamageType == 0x01 )
		{
			HTint nEffectLightterID;
			g_pEngineHandler->HT_hrStartSFX( &nEffectLightterID, HT_FX_DYNALIGHT_02, m_pFactor->iTargetModelID, HT_FALSE );
		}
	}

	//	캠지터
	if( m_pFactor->byCriticalHit == 0x01 )
	{
		HTint nEffectCamjitterID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectCamjitterID, HT_FX_CAMJITTER_03, m_pFactor->nCharModelID, HT_FALSE );
	}

	//	공격자가 메인캐릭터일때 서버에 정보를 알려준다.
	if( m_pFactor->byAttacker == 0x03 )
        this->HT_vNetWork_CSP_MSG_Attack();

	//	이 공격 클래스 리스트에서 삭제
	m_nAttack_Process = ATTACKPROCESS_DAETH;
}

//	서버에 공격 요청함
HTvoid HTAttack::HT_vNetWork_CSP_MSG_Attack()
{
	MSG_Attack* info = HT_NULL;
	info = new MSG_Attack;
	ZeroMemory( info, sizeof(MSG_Attack) );

	info->AttackerID = (unsigned short)m_pFactor->dwAttackKeyID;
	info->SkillIndex = m_pFactor->nAttackSkillID;
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_pFactor->vecSourcePos, crdCell );
	info->PosX = crdCell.x;
	info->PosY = crdCell.y;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_pFactor->vecTargetPos, crdCell );
	info->TargetX = crdCell.x;
	info->TargetY = crdCell.y;
	info->Dam[0].TargetID = (unsigned short)m_pFactor->dwTargetKeyID;

	g_pNetWorkMgr->RequestMSG_Attack( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_MSG_Attack" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}



//---------------------------------------------------------------------------------
//
//		Attack 클래스 관리
//
//---------------------------------------------------------------------------------
HTMainCharAttack::HTMainCharAttack()
{
	m_nAttackMaxDemage = 0;
	HT_LL_vInitList();
}

HTMainCharAttack::~HTMainCharAttack()
{
}

//	어택 클래스 생성
HTvoid HTMainCharAttack::HT_vAttackSystem_Create( P_ATTACK_FACTOR info )
{
	//----------LL 데이타 삽입-헤드 바로 뒤에---------//
	HT_LL_hrInsertAfter( info );
}

//	어택 클래스 컨트롤
HTvoid HTMainCharAttack::HT_vAttackSystem_Control( HTfloat fElapsedTime )
{
	//-----NPC 노드에서 체크-----//
	HT_ATTACK_NODE *t;
	
	t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		t->cAttack.HT_vAttack_Control( fElapsedTime );
        t = t->next;
	}
	//----------LL 데이타 지우기---------//
	HT_LL_hrDeleteNode();
}

//	전체 공격 리스트 삭제
HTvoid HTMainCharAttack::HT_vAttackSystem_AllDelete()
{
	//----------LL 데이타 전부 지우기---------//
	//HT_LL_hrDeleteAll();

	m_nAttackMaxDemage = 0;
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTMainCharAttack::HT_LL_vInitList()
{
	m_sAttackHead = NULL;
	m_sAttackTail = NULL;

	m_sAttackHead = new HT_ATTACK_NODE;
	m_sAttackTail = new HT_ATTACK_NODE;

	m_sAttackHead->next = m_sAttackTail;
	m_sAttackTail->next = m_sAttackTail;
}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTvoid HTMainCharAttack::HT_LL_hrInsertAfter( P_ATTACK_FACTOR info )
{
    HT_ATTACK_NODE *s;
	s = NULL;
	s = new HT_ATTACK_NODE;
	s->cAttack.HT_vAttack_SetInitData( info );
	s->next = m_sAttackHead->next;
	m_sAttackHead->next = s;
}

//----------LL 데이타 지우기---------//
HTRESULT HTMainCharAttack::HT_LL_hrDeleteNode()
{
	HT_ATTACK_NODE *s;
	HT_ATTACK_NODE *p;

	p = m_sAttackHead;
	s = p->next;
	while( s->cAttack.m_nAttack_Process != ATTACKPROCESS_DAETH && s != m_sAttackTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sAttackTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL 데이타 전부 지우기---------//
HTvoid HTMainCharAttack::HT_LL_hrDeleteAll()
{
	HT_ATTACK_NODE *s;
	HT_ATTACK_NODE *t;
	
	t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sAttackHead->next = m_sAttackTail;
}
