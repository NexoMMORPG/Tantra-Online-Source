#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htmaincharattack.h"


#define FOLLOWATTACK_NONE				0
#define FOLLOWATTACK_FOLLOWSKILL		1 
#define FOLLOWATTACK_FOLLOWDART			2

// ���ο�UI����(20030728)
//	0:OtherChar, 2:Monster, 3:CriticalHit
HTint g_nHitNumber[3][10] = { 23887, 23888, 23889, 23890, 23891, 23892, 23893, 23894, 23895, 23896,
							  23867, 23868, 23869, 23870, 23871, 23872, 23873, 23874, 23875, 23876,
							  23877, 23878, 23879, 23880, 23881, 23882, 23883, 23884, 23885, 23886 };

//	ķ���� ID
HTint g_nCamjitterID[3] = { HT_FX_CAMJITTER_01, HT_FX_CAMJITTER_02, HT_FX_CAMJITTER_03 };


//---------------------------------------------------------------------------------
//
//		Attack Ŭ����
//
//---------------------------------------------------------------------------------
HTAttack::HTAttack(void)
{
    //	�� ���̵� �ʱ�ȭ
	m_oFollowFX.idModel			= -1;		//	�θ� / ��ô�����
	m_oFollowFX.idFX			= -1;		//	����Ʈ ���̵�

	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	m_nAttack_LiveTime = GetTickCount();
}

HTAttack::~HTAttack(void)
{
	//	�� ���̵� �����
	if( m_oFollowFX.idModel > 0 )		//	�θ� / ��ô�����
	{
        g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel );
		m_oFollowFX.idModel = -1;
	}
	if( m_oFollowFX.idFX != -1 )	//	����Ʈ ���̵�
		g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );

	HT_DELETE( m_pFactor );
}

//	�ʱ� ����Ÿ ����
HTvoid HTAttack::HT_vAttack_SetInitData( P_ATTACK_FACTOR info )
{
	//	ĳ���� ���� ����
	m_pFactor = HT_NULL;
	m_pFactor = new S_ATTACK_FACTOR;
    memcpy( m_pFactor, info, sizeof(S_ATTACK_FACTOR) );
	
	m_pFactor->byAttackSkillIDLevel = 1;
	m_dwAttack_SkillType		= 0;
	m_bAttack_DartSw			= HT_FALSE;
	m_nAttack_Process			= ATTACKPROCESS_ATTACKPOINT;
	//	���ư��� Ÿ��
	m_iAttack_FolowType			= FOLLOWTYPE_JKSHOMER;
}

//	�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����
HTfloat HTAttack::HT_fAttackGetAngle(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	�������ϱ� -> ������ ����(����)�� �˱� ����
	float sqrt_A = (float)sqrt(A.x*A.x + A.z*A.z);	//  A ������ ���밪(����) ���ϱ� 
	float sqrt_B = (float)sqrt(B.x*B.x + B.z*B.z);	//  B ������ ���밪(����) ���ϱ� 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  ������ �̿��ؼ� ���� ���ϱ�

	HTfloat acos = acosf( cos );					//	�ڻ��ΰ��� ���Ȱ� �ٲٱ�
	float direction = A.z*B.x - B.z*A.x;			//	���� ������ ��
	if(direction < 0)								//	dirction ���̸� ���� , ���̸� ������
		acos *= -1;
	return acos;
}

//	���� ��Ʈ��
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

	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	HT_vAttack_LiveTimeControl();
}

//	���� ����Ʈ���� ����
HTvoid HTAttack::HT_vAttack_AttackPoint()
{
	//	���ư��� �θ�/ǥâ ����
	if( HT_IS_ITEM_DART( m_pFactor->nAttackItemID ) )
	{
		m_bAttack_DartSw = HT_TRUE;
		HT_vAttack_SetWithFollow();
		return;
	}

	//	�׼� ��ų Ÿ���� ���´�.
	m_dwAttack_SkillType = g_pEngineHandler->HT_dwGetSkillType( m_pFactor->nAttackSkillID );
	
	//	PC��ų���� Monster��ų���� �ľ�!
	if( m_pFactor->byAttacker == 0x02 )		//	Monster
	{
		if( m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_NOCAST_LONG || 
			m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_YESCAST_LONG ||
			m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			this->HT_vAttack_SetWithFollow();				//	�ȷο찡 �ִ� ����
		}

		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	�ȷο� ���� ����
		}
	}
	else										//	PC
	{
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			this->HT_vAttack_SetWithFollow();				//	�ȷο찡 �ִ� ����
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	�ȷο� ���� ����
		}
	}
}

//	���� ����Ʈ���� ����_�ȷο찡���� ���� ����
HTvoid HTAttack::HT_vAttack_SetWithOutFollow()
{
	HT_vAttack_SetAttackPoint();

	//	���ݴ�󿡰� ����� �Ұ͵�
	if( m_pFactor->byTargetType == 0x01 )
		g_cOtherCharSystem->HT_vOtherCharSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillAttribute );
	else if( m_pFactor->byTargetType == 0x02 )
		g_sMonsterSystem->HT_vMonsterSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->fDirect, m_pFactor->byAttackSkillIDLevel );
	else if( m_pFactor->byTargetType == 0x03 )
		g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, m_pFactor->dwAttackKeyID );
	//	�׼� ��ų Ÿ���� �������ݰ� �Ǿ���� �ƴҶ��� Ʋ���ش�.
	else if( m_pFactor->byTargetType == 0x04 )
	{
		HTint iTempEffectID;
		g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, HT_FX_NORMALATTACKIMPACT, m_oFollowFX.idModel, HT_FALSE );
	}
}

//	���� ����Ʈ���� �ȷο� ����Ʈ ����
HTvoid HTAttack::HT_vAttack_SetWithFollow()
{
	//	Follow(�Ѿ�) ���
	HT_vAttack_DistanceCheck();
	
	if( m_fAttack_Distance > 200.0f )
	{
		m_nAttack_Process = ATTACKPROCESS_NONE;
		return;
	}

	//	ĳ���� ���̸� �����Ͽ� Y�� ����
	m_oFollowFX.vecPos.y += 10.0f;
	//	��ǥ��ġ ����
	m_oFollowFX.vecTarget = m_pFactor->vecTargetPos;
	//	�ð� ����
	m_oFollowFX.fTime = 0.0f;
	//	��ô�����϶�
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

	//	���ư��� Ÿ��
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_Set_JKS_FlyingObject_Homer();
			break;
	}

	//	���μ��� �ȷο�� �ѱ�
	m_nAttack_Process = ATTACKPROCESS_FOLLOWEFFET;
}

// ������ �ʿ��� init �κ�
HTvoid HTAttack::HT_vAttack_Set_JKS_FlyingObject_Homer()
{
	// jks - �ʱ� �ӵ� ���� 
    //oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
    // get random number between (-2.0f ~ 2.0f)
    m_oFollowFX.curVel.x = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
    // get random number between (-2.0f ~ 2.0f)
    m_oFollowFX.curVel.z = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
    // get random number between (0.0f ~ 4.0f)
    m_oFollowFX.curVel.y = (rand()%4) + (rand() / (HTfloat)RAND_MAX); //jks
    //oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
}

//	���� ����Ʈ���� ����_���� �Ÿ� ���
HTvoid HTAttack::HT_vAttack_DistanceCheck()
{
	m_pFactor->vecSourcePos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_pFactor->vecSourcePos.x, m_pFactor->vecSourcePos.z )+10;;
	m_pFactor->vecTargetPos.y = g_pEngineHandler->HT_fGetTerrainHeight( m_pFactor->vecTargetPos.x, m_pFactor->vecTargetPos.z )+10;
	m_fAttack_Hight = m_pFactor->vecTargetPos.y - m_oFollowFX.vecPos.y;

	HTvector3 vecVector = m_pFactor->vecTargetPos - m_pFactor->vecSourcePos;
	m_fAttack_Direct = HT_fAttackGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector );

	//	���� �� �Ÿ�
	m_fAttack_Distance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) ) * 1.3f;
	m_fAttack_DistanceTrans	= 0;			//	���� �� �Ÿ� ��ȭ
}

//	�ȷο� ����Ʈ
HTvoid HTAttack::HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime )
{
	//	���ư��� Ÿ��
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			this->HT_vAttack_AttackFollowEffectGo( fElapsedTime );
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( fElapsedTime );
			break;
	}

	//	�ȷο� ����Ʈ_üũ
	HT_vAttack_AttackFollowCheck();
}

//	�ȷο� ����Ʈ go
HTvoid HTAttack::HT_vAttack_AttackFollowEffectGo( HTfloat fElapsedTime )
{
	if( fElapsedTime <= HT_EPSILON )
		return;

	//----------ǥâ���� ȸ���ϸ鼭 ���ư���...----------//
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

	//	Follow Object ��ġ ���ϱ�
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

//	�ȷο� ����Ʈ_üũ
HTvoid HTAttack::HT_vAttack_AttackFollowCheck()
{
	HTfloat fDistance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) );
    
	if( m_fAttack_DistanceTrans >= m_fAttack_Distance || fDistance<5.0f )
	{
		//	�� �� �����
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

		//	���� �¾����� ���ؾ� �� �׼ǵ�
		HT_vAttack_SetAttackPoint();

		//	���ݴ�󿡰� ����� �Ұ͵�
		if( m_pFactor->byTargetType == 0x01 )
			g_cOtherCharSystem->HT_vOtherCharSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillAttribute );
		else if( m_pFactor->byTargetType == 0x02 )
			g_sMonsterSystem->HT_vMonsterSystem_SetDisAttackOn( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->fDirect, m_pFactor->byAttackSkillIDLevel );
		else if( m_pFactor->byTargetType == 0x03 )
			g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, m_pFactor->dwAttackKeyID );
		//	�׼� ��ų Ÿ���� �������ݰ� �Ǿ���� �ƴҶ��� Ʋ���ش�.
		else if( m_pFactor->byTargetType == 0x04 )
		{
			HTint iTempEffectID;
			g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, HT_FX_NORMALATTACKIMPACT, m_oFollowFX.idModel, HT_FALSE );
		}
	}
}

//	�� Ŭ������ ����� ���� ������ ������ġ->������
HTvoid HTAttack::HT_vAttack_LiveTimeControl()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_nAttack_LiveTime+10000 )
	{
		m_nAttack_Process = ATTACKPROCESS_DAETH;
	}	
}

//	���� �¾����� ���ؾ� �� �׼ǵ�
HTvoid HTAttack::HT_vAttack_SetAttackPoint()
{
	//----------Ÿ�� ���� Ʋ���ֱ�----------//
	if( m_pFactor->byAttacker != 0x02 || m_pFactor->nAttackItemID == 0 )			//	���Ͱ� �ƴҰ�쿡��
	{
		if( m_pFactor->byAttackSkillAttribute == 0x01 )
            g_pEngineHandler->HT_hrPlayAttackOKSound( m_pFactor->byTribe, m_pFactor->nAttackItemID );
	}

	//	�׼� ��ų Ÿ���� �������ݰ� �Ǿ���� �ƴҶ��� Ʋ���ش�.
	if( m_pFactor->byTargetType != 0x04 )
	{
		//	�ø�Ŀ �ƴϸ� ������ �� ����Ʈ
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

	//	ķ����
	if( m_pFactor->byCriticalHit == 0x01 )
	{
		HTint nEffectCamjitterID;
		g_pEngineHandler->HT_hrStartSFX( &nEffectCamjitterID, HT_FX_CAMJITTER_03, m_pFactor->nCharModelID, HT_FALSE );
	}

	//	�����ڰ� ����ĳ�����϶� ������ ������ �˷��ش�.
	if( m_pFactor->byAttacker == 0x03 )
        this->HT_vNetWork_CSP_MSG_Attack();

	//	�� ���� Ŭ���� ����Ʈ���� ����
	m_nAttack_Process = ATTACKPROCESS_DAETH;
}

//	������ ���� ��û��
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_MSG_Attack" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}



//---------------------------------------------------------------------------------
//
//		Attack Ŭ���� ����
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

//	���� Ŭ���� ����
HTvoid HTMainCharAttack::HT_vAttackSystem_Create( P_ATTACK_FACTOR info )
{
	//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
	HT_LL_hrInsertAfter( info );
}

//	���� Ŭ���� ��Ʈ��
HTvoid HTMainCharAttack::HT_vAttackSystem_Control( HTfloat fElapsedTime )
{
	//-----NPC ��忡�� üũ-----//
	HT_ATTACK_NODE *t;
	
	t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		t->cAttack.HT_vAttack_Control( fElapsedTime );
        t = t->next;
	}
	//----------LL ����Ÿ �����---------//
	HT_LL_hrDeleteNode();
}

//	��ü ���� ����Ʈ ����
HTvoid HTMainCharAttack::HT_vAttackSystem_AllDelete()
{
	//----------LL ����Ÿ ���� �����---------//
	//HT_LL_hrDeleteAll();

	m_nAttackMaxDemage = 0;
}

//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid HTMainCharAttack::HT_LL_vInitList()
{
	m_sAttackHead = NULL;
	m_sAttackTail = NULL;

	m_sAttackHead = new HT_ATTACK_NODE;
	m_sAttackTail = new HT_ATTACK_NODE;

	m_sAttackHead->next = m_sAttackTail;
	m_sAttackTail->next = m_sAttackTail;
}

//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
HTvoid HTMainCharAttack::HT_LL_hrInsertAfter( P_ATTACK_FACTOR info )
{
    HT_ATTACK_NODE *s;
	s = NULL;
	s = new HT_ATTACK_NODE;
	s->cAttack.HT_vAttack_SetInitData( info );
	s->next = m_sAttackHead->next;
	m_sAttackHead->next = s;
}

//----------LL ����Ÿ �����---------//
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

//----------LL ����Ÿ ���� �����---------//
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
