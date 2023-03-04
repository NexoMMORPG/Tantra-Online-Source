
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTMonsterSystem.h"

HTMonsterSystem::HTMonsterSystem()
{
	m_dwMonOnjID = 0;
}

HTMonsterSystem::~HTMonsterSystem()
{
}

HTvoid HTMonsterSystem::HT_vMonsterSysytem_Clean()
{
	//HT_LL_hrDeleteAll();
	//HT_DELETE( m_sMonsterHead );
}

HTRESULT HTMonsterSystem::HT_hMonsterSystemInit()
{
	m_iMonster_IndexCount = 0;
	m_sMonsterInitDirect = 0;

	//----------LL 초기화---------//
	HT_LL_vInitList();

	//----------몬스터 정보 표시위해----------//
	m_nMonster_HPIndo_Sw = HT_FALSE;

	return HT_OK;
}


//----------업데이트---------//
HTvoid HTMonsterSystem::HT_vMonsterSystemUpdate( HTfloat fElapsedTime )
{
	//----------현재 링크된 몬스터 업데이트---------//
	HT_vMonsterSystemMonUpdate( fElapsedTime );
}

//----------현재 링크된 몬스터 업데이트---------//
HTvoid HTMonsterSystem::HT_vMonsterSystemMonUpdate( HTfloat fElapsedTime )
{
	HT_MONSTER_NODE *t;
	HT_MONSTER_NODE *s;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		t->sMonster.HT_vMonsterUpdate( fElapsedTime );
		s = t;
		t = t->next;
		//	몬스터 죽음 체크
		if( s->sMonster.m_nMonster_Live == MONSTER_STATE_DEATH )
		{
			HT_LL_hrDeleteNode( s->sMonster.m_iMonsterKeyID );
		}
	}
}

//----------몬스터 지우기---------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_Delete( PS_SCP_RESP_REMOVE_MOB info )
{
	//	사망삭제일때
	if( info->byResult == 1 )
	{
		HT_MONSTER_NODE *t;
		t = m_sMonsterHead->next;

		while( t != m_sMonsterTail )
		{
			if( t->sMonster.m_iMonsterKeyID == info->nID )
			{
				if( info->byResult == 5 )
					t->sMonster.HT_vMonster_Network_Teleport();
				else
					t->sMonster.HT_vMonster_Network_Death();
				break;
			}
			t = t->next;
		}
	}
	else
	{
		HT_LL_hrDeleteNode( info->nID );
	}
}

//----------전체 몬스터 지우기---------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_TotalMonsterDelete()
{
	//----------LL 데이타 전부 지우기---------//
	HT_LL_hrDeleteAll();
}

//---------공격 관련----------//
//---------공격 받았을 때_맞는 액션 온----------//
HTbool HTMonsterSystem::HT_vMonsterSystem_SetDisAttackOn( DWORD dwKeyID, DWORD dwSkillIndex, HTfloat fDirect, BYTE byLevel, HTint iItemIndex )
{
	//-----몬스터 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_iMonsterKeyID == dwKeyID )
		{
			return t->sMonster.HT_vMonster_SetDisAttackOn( dwSkillIndex, byLevel, fDirect, iItemIndex );
		}
		t = t->next;
	}

	return HT_FALSE;
}

//---------HP 변경사항 체크, byReturnType:0x00:MainChar,0x01:OtherChar----------//
HTint HTMonsterSystem::HT_vMonsterSystem_SetHPCheck( DWORD dwKeyID, HTint nCurHP, HTint nDamageHP, BYTE byInvadeType, HTvector3 vecInvadePos, HTint nInvadeModelID )
{
	//-----몬스터 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_iMonsterKeyID == dwKeyID )
		{
			//	메인캐릭터가 때렸을때만 HP UI 시스템에 표현
			if( byInvadeType == 0x03 )
                t->sMonster.m_bAttack_FromMainChar = HT_TRUE;
			else
				t->sMonster.m_bAttack_FromMainChar = HT_FALSE;

			return t->sMonster.HT_vMonster_SetHPCheck( dwKeyID, nCurHP, nDamageHP, byInvadeType, vecInvadePos, nInvadeModelID );
		}
		t = t->next;
	}

	return 0;
}

//----------몬스터 테스트를 위한 카메라 포인트 반환---------//
HTvector3 HTMonsterSystem::HT_vMonsterSystemGetCameraPoint()
{
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	if( m_sMonsterHead->next == m_sMonsterTail )
		return g_cMainCharacter->m_cMainCharMove->HT_vecGetPosition();
	else
		return t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
}


//----------AOI 영역 체크----------//
HTvoid HTMonsterSystem::HT_vMonster_AOI_Check( HT_MONSTER_NODE *t )
{
	BYTE bResult = g_cAoi->HT_AOI_Level( t->sMonster.m_cMoveMonster->HT_pGetMonsterGrid() );

	if( bResult == AOI_LEVEL_1 )
	{
	}
	else if( bResult == AOI_LEVEL_2 )
	{
	}
	else if( bResult == AOI_LEVEL_NONE )
	{
		HT_LL_hrDeleteNode( t->sMonster.m_iMonsterKeyID );
	}
}


//----------메인캐릭터와의 관계 /  메인캐릭터 셋팅---------//
HTvoid HTMonsterSystem::HT_vMainCharacterCheck()
{
}


//----------몬스터 아이디를 체크하여 넘겨줌---------//
DWORD HTMonsterSystem::HT_bMonsterSystemComIDCheck( HTint iID )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;

	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( iID == t->sMonster.m_iMonsterModelID && t->sMonster.m_nMonster_Resent_HP > 0 )
		{
			if( !g_bGamePlayMovieForGlobal )
			{
				//---------정보 디스플레이 셋팅----------//
				m_nMonster_HPIndo_Sw = HT_TRUE;
				if (m_dwMonOnjID!=iID)
				{
					t->sMonster.HT_vMonster_SetInfoDisplay(HT_FALSE);
					m_dwMonOnjID = iID;
				}
				else
					t->sMonster.HT_vMonster_SetInfoDisplay(HT_TRUE);

				//---------몬스터 박스와 hp바 컨트롤----------//
				g_pMainBar->HT_vSetObjectTextDraw( t->sMonster.m_strName );
				g_pMainBar->HT_vSetObjectHPDraw( t->sMonster.m_nMonster_Resent_HP, t->sMonster.m_nMonster_MAX_HP );
				
			}

            return t->sMonster.m_iMonsterKeyID;
		}
		t = t->next;
	}

	return 0;
}

//----------몬스터 정보창 초기화---------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_HPWindowInit()
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;

	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_bMonster_InfoShow_Sw == HT_TRUE )
		{
			//---------정보 디스플레이 셋팅----------//
			m_nMonster_HPIndo_Sw = HT_FALSE;
			t->sMonster.HT_vMonster_SetInfoCancel();
			g_pMainBar->HT_vSetObjectHPOut();
		}
		t = t->next;
	}
}


//----------셀에 위치한 몬스터가 있는가?---------//
HTint HTMonsterSystem::HT_bMonsterSystemCheckMapCell( HTint iMapCellX, HTint iMapCellZ )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		HT_CELL_COORD crdCell;
		
		crdCell.x = t->sMonster.m_cMoveMonster->m_iMonsterphysical_CellX;
		crdCell.y = t->sMonster.m_cMoveMonster->m_iMonsterphysical_CellZ;

		HTint sum1 = crdCell.x-(t->sMonster.m_cMoveMonster->m_bMonsterSize/2);
		HTint sum2 = crdCell.x+(t->sMonster.m_cMoveMonster->m_bMonsterSize/2);

		HTint sum3 = crdCell.y-(t->sMonster.m_cMoveMonster->m_bMonsterSize/2);
		HTint sum4 = crdCell.y+(t->sMonster.m_cMoveMonster->m_bMonsterSize/2);

		for( HTint i=sum1 ; i<=sum2 ; i++ )
		{
			for( HTint j=sum3 ; j<=sum4 ; j++ )
			{
				if( iMapCellX==i &&	iMapCellZ==j )
				{
					return t->sMonster.m_iMonsterModelID;
				}
			}
		}
		t = t->next;
	}
	
	return -1;
}

//---------현재 타겟창에 몬스터 정보가 보여지고 있는 몬스터의 모델 ID 반환-------------//
DWORD HTMonsterSystem::HT_dwMosterSystem_GetTargetModelID()
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_bMonster_InfoShow_Sw == HT_TRUE )
		{
			return t->sMonster.m_iMonsterModelID;
		}
		t = t->next;
	}

	return -1;
}

//----------반환값들---------//
DWORD HTMonsterSystem::HT_MonsterSystem_GetKeyID( HTint iImageID )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( iImageID == t->sMonster.m_iMonsterModelID )
		{
			return t->sMonster.m_iMonsterKeyID;
		}
		t = t->next;
	}

	return 0;
}

DWORD HTMonsterSystem::HT_dwMonsterSystem_GetIndex( DWORD KeyID )
{
	//-----몬스터 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( KeyID == t->sMonster.m_iMonsterKeyID )
		{
			return t->sMonster.m_iMonsterIndex;
		}
		t = t->next;
	}

	return 0;
}

HTPoint HTMonsterSystem::HT_MonsterSystem_GetCellPos( DWORD dKeyID )
{
	HTPoint pCell;
	pCell.x = 0;
	pCell.y = 0;
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dKeyID == t->sMonster.m_iMonsterKeyID )
		{
			if( t->sMonster.m_bMonster_Death_Sw != HT_TRUE )
			{
				pCell.x = t->sMonster.m_cMoveMonster->m_iMonsterlogical_CellX;
				pCell.y = t->sMonster.m_cMoveMonster->m_iMonsterlogical_CellZ;
				return pCell;
			}
			else
                break;
		}
		t = t->next;
	}

	return pCell;
}

HTvector3 HTMonsterSystem::HT_MonsterSystem_GetCoordFromModelID( HTint nModelID )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( nModelID == t->sMonster.m_iMonsterModelID )
		{
            return t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

HTvector3 HTMonsterSystem::HT_MonsterSystem_GetCoordFromKeyID( DWORD dwKeyID )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwKeyID == t->sMonster.m_iMonsterKeyID && t->sMonster.m_bMonster_Death_Sw != HT_TRUE )
		{
			return t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
			//m_vecMonsterTargetPos;//
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

CHTString HTMonsterSystem::HT_strMonsterSystem_GetName( DWORD dwkeyID )
{
	CHTString strName;
	HT_MONSTER_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwkeyID == t->sMonster.m_iMonsterKeyID )
		{
			return t->sMonster.m_strName;
		}
		t = t->next;
	}

	return strName;
}

CHTString HTMonsterSystem::HT_strMonsterSystem_GetNamebyModelID( DWORD dwModelID )
{
	CHTString strName;
	HT_MONSTER_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwModelID == t->sMonster.m_iMonsterModelID )
		{
			return t->sMonster.m_strName;
		}
		t = t->next;
	}

	return strName;
}


HTint HTMonsterSystem::HT_strMonsterSystem_GetModelIDbyKeyID( DWORD dwKeyID )
{
	CHTString strName;
	HT_MONSTER_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwKeyID == t->sMonster.m_iMonsterKeyID )
		{
			return t->sMonster.m_iMonsterModelID;
		}
		t = t->next;
	}

	return -1;
}

BYTE HTMonsterSystem::HT_byMonsterSystem_GetMonsterSize( DWORD dwKeyID )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwKeyID == t->sMonster.m_iMonsterKeyID )
		{
            return t->sMonster.m_byMonster_Size;
		}
		t = t->next;
	}

	return 1;
}

//	셀좌표로 캐릭터 키아디를 알아온다
HTint HTMonsterSystem::HT_iMonsterSystem_GetKeyIDFromCell( short snCellX, short snCellZ, HTvector3* vecTargetPos )
{
	HTPoint pPt;
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		pPt = t->sMonster.m_cMoveMonster->HT_pGetMonsterCellPos();
		if( pPt.x == snCellX && pPt.y == snCellZ )
		{
			*vecTargetPos = t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
			return t->sMonster.m_iMonsterKeyID;
		}
		t = t->next;
	}

	return 0;
}

//	몬스터가 공격 대상인지 파악
HTvector3 HTMonsterSystem::HT_MonsterSystem_GetAttackPos( DWORD dwKeyID, HTint nCurHP, DWORD dwSkillIndex )
{
	//-----NPC 노드에서 체크-----//
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( dwKeyID == t->sMonster.m_iMonsterKeyID )
		{
			HTvector3 vecPos = t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
			vecPos.y = (HTfloat)t->sMonster.m_iMonsterModelID;
			//---------HP 변경사항 체크----------//
			return vecPos;
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTMonsterSystem::HT_LL_vInitList()
{
	m_sMonsterHead = NULL;
	m_sMonsterTail = NULL;

	m_sMonsterHead = new HT_MONSTER_NODE;
	m_sMonsterTail = new HT_MONSTER_NODE;

	m_sMonsterHead->next = m_sMonsterTail;
	m_sMonsterTail->next = m_sMonsterTail;

}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTRESULT HTMonsterSystem::HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info )
{
	HT_MONSTER_NODE *s;

	s = NULL;
	s = new HT_MONSTER_NODE;
    s->sMonster.HT_vMonsterCreate( info, m_sMonsterInitDirect );
	s->next = m_sMonsterHead->next;
	m_sMonsterHead->next = s;

	m_sMonsterInitDirect++;
	if( m_sMonsterInitDirect == 8 )
		m_sMonsterInitDirect = 0;

	return HT_OK;
}

//----------LL 데이타 지우기---------//
HTRESULT HTMonsterSystem::HT_LL_hrDeleteNode( DWORD iMonsterKeyID )
{
	HT_MONSTER_NODE *s;
	HT_MONSTER_NODE *p;

	p = m_sMonsterHead;
	s = p->next;
	while( s->sMonster.m_iMonsterKeyID != iMonsterKeyID && s != m_sMonsterTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sMonsterTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL 데이타 전부 지우기---------//
HTvoid HTMonsterSystem::HT_LL_hrDeleteAll()
{
	HT_MONSTER_NODE *s;
	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sMonsterHead->next = m_sMonsterTail;
}


//----------랜더---------//
HTvoid HTMonsterSystem::HT_vMonsterSystemRender()
{
	g_cMiniMap->HT_vMiniMap_Render_StartObject( 0x02 );
	HTPoint CellPt;

	HT_MONSTER_NODE *t;
	
	t = m_sMonsterHead->next;
	while( t != m_sMonsterTail )
	{
		if( g_cMiniMap->HT_bMiniMap_IsOn() )
		{
			CellPt = t->sMonster.m_cMoveMonster->HT_pGetMonsterCellPos();
			g_cMiniMap->HT_vMiniMap_Render_Monster( 0x01, CellPt );
		}

		//----------랜더_이름----------//
		if( t->sMonster.m_bMonster_InfoShow_Sw	== HT_TRUE )
		{
			//----------랜더_이름----------//
			HT_vMonsterSystem_RenderName( t );
			return;
		}
		t = t->next;
	}

	//---------정보 디스플레이 셋팅----------//
	if( m_nMonster_HPIndo_Sw == HT_TRUE )
	{
		m_nMonster_HPIndo_Sw = HT_FALSE;
		g_pMainBar->HT_vSetObjectHPOut();
	}
}

//----------랜더_이름----------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_RenderName( HT_MONSTER_NODE* t )
{
	if( g_bGamePlayMovieForGlobal )
		return;

	HTvector3 vTextPos = t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
	vTextPos.y += t->sMonster.m_fMonsterModelHeight + 5.0f;
	if( !g_bDevelopingMode )
	{
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->sMonster.m_strName, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
	else
	{
		HTPoint pPt = t->sMonster.m_cMoveMonster->HT_pGetMonsterCellPos();
        CHTString strTemp;
		char szCharName[SZNAME_LENGTH];
		strncpy( szCharName, t->sMonster.m_strName, SZNAME_LENGTH );
		strTemp.HT_szFormat( "%s,ID:%d,x:%d,z:%d-x:%d,z:%d", szCharName, t->sMonster.m_iMonsterKeyID, pPt.x, pPt.y, t->sMonster.m_snMonster_TargetX, t->sMonster.m_snMonster_TargetZ );
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, strTemp, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
}

//----------------------------------------------------//
//---------------------서버 관련----------------------//
//----------------------------------------------------//
//----------몬스터 생성-서버에서 컨트롤 해줌----------//
HTvoid HTMonsterSystem::HT_vMonsterSystemCreate( PS_SCP_INIT_OTHER_MOB info )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( info->nID == t->sMonster.m_iMonsterKeyID )
		{
			HT_LL_hrDeleteNode( info->nID );
			break;
		}
		t = t->next;
	}

	HT_LL_hrInsertAfter( info );
	m_iMonster_IndexCount++;
}

HTRESULT HTMonsterSystem::HT_vMonsterSystemSet_logical_End( MSG_Action* info )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( info->dwKeyID == t->sMonster.m_iMonsterKeyID && t->sMonster.m_nMonster_Live == MONSTER_STATE_LIVE )
		{
            if( t->sMonster.m_bMonster_Death_Sw	== HT_TRUE )
			{
				//----------이닛브로드캐스트 받지못했을때 MonsterNPC를 보정해주기 위해---------//
				HT_vRequestInitMonsterNPC( info->dwKeyID );
			}
			else
			{
				t->sMonster.HT_vMonsterSet_logical_CellEnd( info );
			}
			return HT_OK;
		}
		t = t->next;
	}

	return HT_FAIL;
}

//	몬스터가 공격합
HTvoid HTMonsterSystem::HT_vMonsterSystem_NewWork_SCP_MSG_Attack( PS_CSP_CAST_UNIT_SKILL data )
{
	//	공격자의 ID
	HTint iAttackerID;
	//	기본 공격 데이타
	S_MSG_ATTACK_OTHERMOB info;

	iAttackerID = data->snCasterKeyID;
	info.iCasterHP = data->iCasterHP;
	info.iSkillID = data->snSkillID;
	info.krgTarget[0].snKeyID = data->kTarget.snKeyID;
	info.PosX = data->snCasterX;
	info.PosY = data->snCasterZ;
	info.krgTarget[0].snDamage = data->kTarget.snDamage;

	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_iMonsterKeyID == iAttackerID )
		{
			info.vecTargetPos = HT_vMonsterSystem_GetAttackPos( info.krgTarget[0].snKeyID, info.iSkillID, &info.byTargetType );
			if( info.byTargetType != 0 )
			{
				t->sMonster.HT_vMonster_Network_SCP_Msg_Attack( info );
			}
			return;
		}
		t = t->next;
	}

	//----------이닛브로드캐스트 받지못했을때 MonsterNPC를 보정해주기 위해---------//
	HT_vRequestInitMonsterNPC( iAttackerID );
}

//----------스킬공격 준비-----------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_Skill_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info )
{
}

////	스킬 Affect을 알림
//HTvoid HTMonsterSystem::HT_vMonsterSystem_Skill_Affect_Broadcast( PS_SCP_AFFECT_SKILL_BROADCAST info )
//{
//	HT_MONSTER_NODE *t;
//	t = m_sMonsterHead->next;
//
//	while( t != m_sMonsterTail )
//	{
//		if( t->sMonster.m_iMonsterKeyID == info->dwCasterKeyID )
//		{
//			HTint iModelID;
//			HTvector3 vecTargetPos = HT_vMonsterSystem_GetAttackPos( info->dwTargetKeyID, info->iTargetHP, info->kSkill.iID, &iModelID );
//			if( vecTargetPos.x != 0 )
//			{
//				t->sMonster.HT_vMonster_Network_Skill_Affect_Broadcast( info, vecTargetPos, iModelID );
//			}
//			return;
//		}
//		t = t->next;
//	}
//
//	//----------이닛브로드캐스트 받지못했을때 MonsterNPC를 보정해주기 위해---------//
//	HT_vRequestInitMonsterNPC( info->dwCasterKeyID );
//}

//----------몬스터의 죽음----------//
HTvoid HTMonsterSystem::HT_vMonsterSystemSet_Death( PS_SCP_CHAR_MONSTER_DEATH_BROADCAST info )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( info->dwKeyID == t->sMonster.m_iMonsterKeyID )
		{	
			t->sMonster.HT_vMonster_Network_Death();
			break;
		}
		t = t->next;
	}
}

//----------워프에 의한 몬스터 사라집----------//
HTvoid HTMonsterSystem::HT_vMonsterSystem_Monster_DisApper( PS_SCP_MONSTER_DISAPPEAR info )
{
	HT_MONSTER_NODE *t;
	HT_MONSTER_NODE *s;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( info->dwKeyID == t->sMonster.m_iMonsterKeyID )
		{
			s = t;
			break;
		}
		t = t->next;
	}

	if( t != m_sMonsterTail && info->byType == 0x02 )
        HT_LL_hrDeleteNode( s->sMonster.m_iMonsterKeyID );
}

//----------이닛브로드캐스트 받지못했을때 MonsterNPC를 보정해주기 위해---------//
HTvoid HTMonsterSystem::HT_vRequestInitMonsterNPC( DWORD dwKeyID )
{
	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_새로 만들어야함 :%d", dwKeyID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//----------공격 대상을 찿아내어 그의 위치를 얻어내----------//
HTvector3 HTMonsterSystem::HT_vMonsterSystem_GetAttackPos( DWORD dwTargetKeyID, HTint iSkillID, BYTE* byTargetType )
{
	HTvector3 vecTargetPos;
	HTbyte byTemp;

	//	1:어더캐릭터 검색
	vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_SRAtkTargetCheck( dwTargetKeyID, &byTemp );
	if( vecTargetPos.x != 0 )
	{
		*byTargetType = 1;
		return vecTargetPos;
	}

	//	3:메인캐릭터 검색
	vecTargetPos = g_cMainCharacter->HT_vecMainChar_GetAtkTargetCheck( dwTargetKeyID );
	if( vecTargetPos.x != 0 )
	{
		*byTargetType = 3;
		return vecTargetPos;
	}

	return HTvector3( 0, 0, 0 );
}

//	범위공격 영역안에 들어간 몹들을 찿아옴
HTvoid HTMonsterSystem::HT_vMosterSystem_GetTerritoryArea( HTvector3 vecTargetPos, HTfloat fRange, HTint iSkillID, HTfloat fDirect, HTint *iElement )
{
	HTint iMonsterCount;
	HTfloat fDis;
	HTvector3 vecPos;
	//	전부 최대값으로 셋팅
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
		iElement[i] = 0;

    HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	iMonsterCount = 0;
	while( t != m_sMonsterTail )
	{
		//	거리를 구해내고
		vecPos = t->sMonster.m_cMoveMonster->HT_vecGetMonsterPos();
		fDis = (float)sqrt( double( ( (vecTargetPos.x - vecPos.x) * (vecTargetPos.x - vecPos.x) ) + ( (vecTargetPos.z - vecPos.z) * (vecTargetPos.z - vecPos.z) ) ) );
		if( fDis < fRange )
		{
			//	죽은 몹이 아닐때만
			if( t->sMonster.m_nMonster_Live == MONSTER_STATE_LIVE )
			{
				t->sMonster.HT_vMonster_SetDisAttackOn( iSkillID, 1, fDirect, 0 );
				iElement[iMonsterCount] = t->sMonster.m_iMonsterKeyID;
				iMonsterCount++;
				if( iMonsterCount == TN_MAX_TARGET_COUNT )
					break;
			}
		}
		t = t->next;
	}

	return;
}

//	몹이 살았는지 죽었는지 알아오기
HTbool HTMonsterSystem::HT_bMonsterSystem_GetMobLive( HTint iKeyID )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( iKeyID == t->sMonster.m_iMonsterKeyID )
		{
			if( t->sMonster.m_nMonster_Live == MONSTER_STATE_LIVE )
				return HT_TRUE;
			else
				return HT_FALSE;
		}
		t = t->next;
	}

	return HT_FALSE;
}

//	PS_SCP_RESP_UPDATE_STATUS Setting
HTvoid HTMonsterSystem::HT_vMonsterSystem_SCPRespUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_iMonsterKeyID == info->snKeyID )
		{
			t->sMonster.m_nMonster_Resent_HP = info->iHP;
			break;
		}
		t = t->next;
	}
}

//	Set Stop
HTvoid HTMonsterSystem::HT_vMonsterSystem_SetStop( HTint iKeyID )
{
	HT_MONSTER_NODE *t;
	t = m_sMonsterHead->next;

	while( t != m_sMonsterTail )
	{
		if( t->sMonster.m_iMonsterKeyID == iKeyID )
		{
			t->sMonster.m_cMoveMonster->HT_vecMonsterStopMove();
			break;
		}
		t = t->next;
	}
}
