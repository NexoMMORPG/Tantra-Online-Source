
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTOtherCharacterSystem.h"



HTOtherCharacterSystem::HTOtherCharacterSystem()
{
	m_SCP_OTHER_CHAR_MOVE = HT_NULL;
	m_SCP_OTHER_CHAR_MOVE = new S_SCP_OTHER_CHAR_MOVE;

	//	이름 보여주기
	m_bOtherChar_NameShowSw = HT_TRUE;
	//	채팅 메시지 보여주기
	m_bOtherChar_ChatMsgShowSw = HT_TRUE;
}


HTOtherCharacterSystem::~HTOtherCharacterSystem()
{
	HT_DELETE( m_SCP_OTHER_CHAR_MOVE );
}

HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_CleanUp()
{
//	HT_LL_hrDeleteAll();
//	HT_DELETE( m_sOtherCharHead );
}

HTRESULT HTOtherCharacterSystem::HT_hOtherCharSystemInit()
{
	m_iOtherChar_IndexCount = 0;

	//----------LL 초기화---------//
	HT_LL_vInitList();

	//----------OtherChar 정보 표시위해----------//
	m_nOtherChar_HPInfo_Sw		= HT_FALSE;
	
	return HT_OK;
}

//----------컨트롤----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystemControl( HTfloat fElapsedTime )
{
	//----------임시로 키입력을 받을것이다.---------//
	HT_vOtherCharSystemImsiKeyInput();

	HT_OTHERCHARACTER_NODE *t;
	HT_OTHERCHARACTER_NODE *s;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherCharControl( fElapsedTime );
		s = t;
		t = t->next;

		//	OtherChar 죽음 체크
		if( s->sOtherCharacter.m_nOtherChar_Death == OTHERCHAR_STATE_DEATH )
		{
			HT_LL_hrDeleteNode( s->sOtherCharacter.m_dwOtherCharKeyID );
		}
	}
}

//----------임시로 키입력을 받을것이다.---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystemImsiKeyInput()
{
}

//----------전 OtherChar 삭제--------//
HTvoid HTOtherCharacterSystem::HT_vecOtherCharSystem_TotalCharDelete()
{
	//----------LL 데이타 전부 지우기---------//
	HT_LL_hrDeleteAll();
}

//----------Other Character의 아이디를 체크하여 KeyID를 넘겨줌-Pick와 연결하여_없으면 0을 Return---------//
DWORD HTOtherCharacterSystem::HT_iOtherCharSystemComIDCheck( HTint iID )
{
	//-----NPC 노드에서 체크-----//
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		//	키아이디가 같고 GM 아닐때
		if( iID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			if( t->sOtherCharacter.m_byOtherChar_TribeType != 0x09 )
			{
				//---------정보 디스플레이 셋팅----------//
				m_nOtherChar_HPInfo_Sw = HT_TRUE;
				t->sOtherCharacter.HT_vOtherChar_SetInfoDisplay();
				g_pMainBar->HT_vSetObjectTextDraw( t->sOtherCharacter.m_iOtherCharName );
				return t->sOtherCharacter.m_dwOtherCharKeyID;
			}
		}
		t = t->next;
	}

	return 0;
}

//----------OtherCharSystem 정보창 초기화---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharacterSystem_HPWindowInit()
{
	//-----NPC 노드에서 체크-----//
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_bOtherChar_Info_Sw == HT_TRUE )
		{
            //---------정보 디스플레이 셋팅----------//
			m_nOtherChar_HPInfo_Sw = HT_FALSE;
			t->sOtherCharacter.HT_vOtherChar_SetInfoCancel();
			g_pMainBar->HT_vSetObjectHPOut();
		}
		t = t->next;
	}
}

//----------아이템 사용 이펙트 셋팅----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetItemUseEffect( DWORD dwKeyID )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			HTint nEffectID;
			g_pEngineHandler->HT_hrStartSFX( &nEffectID, HT_FX_SPRINGRECOVERY, t->sOtherCharacter.m_iOtherCharModelID, HT_FALSE );
			return;
		}
		t = t->next;
	}
}

//----------셀에 위치한 캐릭터가 있는가?---------//
DWORD HTOtherCharacterSystem::HT_dOtherCharSystem_CheckMapCell( HTint iMapCellX, HTint iMapCellZ )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( iMapCellX == t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharphysical_CellX && 
			iMapCellZ == t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharphysical_CellZ )
		{
			return t->sOtherCharacter.m_dwOtherCharKeyID;
		}
		
		t = t->next;
	}

	return -1;
}

//----------AOI 영역 체크----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_AOI_Check( HT_OTHERCHARACTER_NODE *t )
{
	BYTE bResult = g_cAoi->HT_AOI_Level( t->sOtherCharacter.m_cOtherCharMove->HT_pGeOtherCharMoveGrid() );

	if( bResult == AOI_LEVEL_1 )
	{
	}
	else if( bResult == AOI_LEVEL_2 )
	{
	}
	else if( bResult == AOI_LEVEL_NONE )
	{
		HT_LL_hrDeleteNode( t->sOtherCharacter.m_dwOtherCharKeyID );
	}
}

//	이름 보여주기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetShowName()
{
	if( m_bOtherChar_NameShowSw == HT_TRUE )
		m_bOtherChar_NameShowSw = HT_FALSE;
	else
		m_bOtherChar_NameShowSw = HT_TRUE;
}

//	채팅 메시지 보여주기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetShowChatMsg()
{
	if( m_bOtherChar_ChatMsgShowSw == HT_TRUE )
		m_bOtherChar_ChatMsgShowSw = HT_FALSE;
	else
		m_bOtherChar_ChatMsgShowSw = HT_TRUE;
}

//----------반환값들----------//
DWORD HTOtherCharacterSystem::HT_dOtherCharSystem_GetModelID( DWORD iKeyID )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( iKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			return t->sOtherCharacter.m_iOtherCharModelID;
		}
		t = t->next;
	}

	return -1;
}

DWORD HTOtherCharacterSystem::HT_dOtherCharSystem_GetKeyID( HTint iImageID )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( iImageID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			return t->sOtherCharacter.m_dwOtherCharKeyID;
		}
		t = t->next;
	}

	return 0;
}

HTbyte HTOtherCharacterSystem::HT_dOtherCharSystem_byGetLevel( HTint iKeyID )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( iKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			return t->sOtherCharacter.m_byOtherChar_Level;
		}
		t = t->next;
	}

	return 0;
}

HTPoint HTOtherCharacterSystem::HT_dOtherCharSystem_GetCellPos( DWORD dwKeyID )
{
	HTPoint	pCellPos;
	pCellPos.x = 0; pCellPos.y = 0;

	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			if( t->sOtherCharacter.m_nOtherChar_Resent_HP > 0 )
			{
				pCellPos.x = t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharlogical_CellX;
				pCellPos.y = t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharlogical_CellZ;
				return pCellPos;
			}
			else
				break;
		}
		t = t->next;
	}

	return pCellPos;
}


HTPoint HTOtherCharacterSystem::HT_dOtherCharSystem_GetCellPosbyModelID( HTint iImageID )
{
	HTPoint	pCellPos;
	pCellPos.x = 0; pCellPos.y = 0;

	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( iImageID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			pCellPos.x = t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharlogical_CellX;
			pCellPos.y = t->sOtherCharacter.m_cOtherCharMove->m_iOtherCharlogical_CellZ;
			return pCellPos;
		}
		t = t->next;
	}

	return pCellPos;
}

//----------OtherChar의 위치를 얻어옴---------//
HTvector3 HTOtherCharacterSystem::HT_vecOtherCharSystem_GetCoordPos( DWORD dwKeyID )
{
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwKeyID == t->sOtherCharacter.m_dwOtherCharKeyID && t->sOtherCharacter.m_nOtherChar_Death != OTHERCHAR_STATE_DEATH )
		{
			return t->sOtherCharacter.m_cOtherCharMove->HT_fGetOtherCharMovePos();
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

//	셀좌표로 캐릭터 키아디를 알아온다
HTint HTOtherCharacterSystem::HT_iOtherCharSystem_GetKeyIDFromCell( short snCellX, short snCellZ, HTvector3* vecTargetPos )
{
	HTPoint pPt;
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &pPt );
		if( pPt.x == snCellX && pPt.y == snCellZ )
		{
			*vecTargetPos = t->sOtherCharacter.m_cOtherCharMove->HT_fGetOtherCharMovePos();
			return t->sOtherCharacter.m_dwOtherCharKeyID;
		}
		t = t->next;
	}

	return 0;
}

HTvector3 HTOtherCharacterSystem::HT_vecOtherCharSystem_GetCoordPosbyModelID( DWORD dwModelID )
{
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwModelID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			return t->sOtherCharacter.m_cOtherCharMove->HT_fGetOtherCharMovePos();
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

//-----------픽된 상태인가 체크----------//
HTRESULT HTOtherCharacterSystem::HT_hrOtherCharSystem_GetInfoStatus( HTint nModelID )
{
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( nModelID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			return t->sOtherCharacter.HT_hrOtherChar_GetInfoStatus();
		}
		t = t->next;
	}

	return HT_FAIL;
}

CHTString HTOtherCharacterSystem::HT_strOtherCharSytem_GetName( DWORD dwkeyID )
{
	CHTString strName;
	HT_OTHERCHARACTER_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwkeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			return t->sOtherCharacter.m_iOtherCharName;
		}
		t = t->next;
	}

	return strName;
}

CHTString HTOtherCharacterSystem::HT_strOtherCharSytem_GetNamebyModelID( DWORD dwModelID )
{
	CHTString strName;
	HT_OTHERCHARACTER_NODE *t;

	strName.HT_hrCleanUp();

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwModelID == t->sOtherCharacter.m_iOtherCharModelID )
		{
			return t->sOtherCharacter.m_iOtherCharName;
		}
		t = t->next;
	}

	return strName;
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTOtherCharacterSystem::HT_LL_vInitList()
{
	m_sOtherCharHead = NULL;
	m_sOtherCharTail = NULL;

	m_sOtherCharHead = new HT_OTHERCHARACTER_NODE;
	m_sOtherCharTail = new HT_OTHERCHARACTER_NODE;

	m_sOtherCharHead->next = m_sOtherCharTail;
	m_sOtherCharTail->next = m_sOtherCharTail;

}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTRESULT HTOtherCharacterSystem::HT_LL_hrInsertAfter( PS_SCP_INIT_OTHER_MOB info )
{
	HT_OTHERCHARACTER_NODE *s;

	s = NULL;
	s = new HT_OTHERCHARACTER_NODE;
	s->sOtherCharacter.HT_vOtherCharCreate( info );
	s->next = m_sOtherCharHead->next;
	m_sOtherCharHead->next = s;

	return HT_OK;
}

//----------LL 데이타 지우기---------//
HTRESULT HTOtherCharacterSystem::HT_LL_hrDeleteNode( int iKeyID )
{
	HT_OTHERCHARACTER_NODE *s;
	HT_OTHERCHARACTER_NODE *p;

	p = m_sOtherCharHead;
	s = p->next;
	while( s->sOtherCharacter.m_dwOtherCharKeyID != iKeyID && s != m_sOtherCharTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sOtherCharTail )
	{
		p->next = s->next;
		s->sOtherCharacter.HT_vOtherCharDistroy();
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL 데이타 전부 지우기---------//
HTvoid HTOtherCharacterSystem::HT_LL_hrDeleteAll()
{
	HT_OTHERCHARACTER_NODE *s;
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sOtherCharHead->next = m_sOtherCharTail;
}


//----------랜더---------//
HTvoid HTOtherCharacterSystem::HT_OtherCharSystem_Render()
{
	HTbool	bBreakPoint = HT_FALSE;
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	g_cMiniMap->HT_vMiniMap_Render_StartObject( 0x01 );
	HTPoint CellPt;

	while( t != m_sOtherCharTail )
	{
		//	미니맵이 떠있을때와 GM이 아닐때만 표시
		if( g_cMiniMap->HT_bMiniMap_IsOn() && t->sOtherCharacter.m_byOtherChar_TribeType != 0x09 )
		{
			t->sOtherCharacter.m_cOtherCharMove->HT_vGetOtherCharMove_physicalCellPos( &CellPt );
			g_cMiniMap->HT_vMiniMap_Render_OtherChar( t->sOtherCharacter.m_byOtherChar_PartyMember, CellPt );
		}

		//----------랜더_이름/채팅메시지----------//
		HT_vOtherCharSystem_RenderName( t );

		if( t->sOtherCharacter.m_bOtherChar_Info_Sw	== HT_TRUE )
		{
			bBreakPoint = HT_TRUE;
		}

		t = t->next;
	}

	//---------정보 디스플레이 셋팅----------//
	if( m_nOtherChar_HPInfo_Sw == HT_TRUE && bBreakPoint == HT_FALSE )
	{
		m_nOtherChar_HPInfo_Sw = HT_FALSE;
		g_pMainBar->HT_vSetObjectHPOut();
	}
}

//----------랜더_이름----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_RenderName( HT_OTHERCHARACTER_NODE* t )
{
	if( t->sOtherCharacter.m_byOtherChar_TribeType == 0x09 )
		return;

	HTvector3 vTextPos = t->sOtherCharacter.m_cOtherCharMove->HT_fGetOtherCharMovePos();
	vTextPos.y += t->sOtherCharacter.m_fModelHeight + 3.0f;

	//	상대방 캐릭 이름
	if( m_bOtherChar_NameShowSw )
	{
		//-----조교인지 아닌지 체크-----//
		if(	t->sOtherCharacter.m_bAssistantSw == HT_FALSE )
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->sOtherCharacter.m_iOtherCharName, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		else
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->sOtherCharacter.m_iOtherCharName, vTextPos, HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
		vTextPos.y += 2.0f;

		//	특수칭호
		if(	t->sOtherCharacter.m_byOtherChar_SpecialName == 0x01 )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, _T("*[용자]*"), vTextPos, HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
			vTextPos.y += 2.0f;
		}
		else if( t->sOtherCharacter.m_byOtherChar_SpecialName == 0x02 )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, _T("*[현자]*"), vTextPos, HT_COLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
			vTextPos.y += 2.0f;
		}
	}

	//	채팅메시지
	if( m_bOtherChar_ChatMsgShowSw )
	{
		DWORD dwPassTime = GetTickCount();
		if( !t->sOtherCharacter.m_strOtherChar_ChattingMessage.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, (HTtchar*)t->sOtherCharacter.m_strOtherChar_ChattingMessage, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 3.0f );
			
			if( dwPassTime > t->sOtherCharacter.m_dwOtherChar_ChatMsgDelay + CHATMSGDELAYTIME )
				t->sOtherCharacter.m_strOtherChar_ChattingMessage.HT_hrCleanUp();
		}
	}
}

//----------서버 데이타 체크하여 처리---------//
//----------캐릭터 생성---------//
HTRESULT HTOtherCharacterSystem::HT_hrOtherCharSystem_Insert( PS_SCP_INIT_OTHER_MOB info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( info->nID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			HT_LL_hrDeleteNode( info->nID );
			break;
		}
		t = t->next;
	}

	HT_LL_hrInsertAfter( info );
	m_iOtherChar_IndexCount++;

	return HT_OK;
}

//----------Other Character의 이동을 서버가 알려줄 때---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_Action_Brodcast( MSG_Action* info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			t->sOtherCharacter.HT_vNetWork_OtherChar_Action( info );
			return;
		}
		t = t->next;
	}

	//----------이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해---------//
	HT_vOtherCharSystem_NetWork_RequestInitOtherChar( info->dwKeyID );
}

//----------Other Character가 로그 아웃 했을 때---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NewWork_RemoveMob( PS_SCP_RESP_REMOVE_MOB info )
{
	//----------Other Character LogOut 서버 데이타---------//
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->nID )
		{
			if( info->byResult == 1 )
				t->sOtherCharacter.HT_hrOtherChar_Death();
			else
                HT_LL_hrDeleteNode( info->nID );
			return;
		}
		t = t->next;
	}
}

//----------Other Character가 장착했을 때---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_ItemEquipmentBrodcast( PS_SCP_RESP_EQUIP_SET info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->nID )
		{
			for( HTint i=0 ; i<7 ; i++ )
			{
				if( info->Equip[i].snIndex )
					info->Equip[i].snIndex += HT_ITEM_INDEX_START;
			}

			//	아이템 장착 ^^;
			//	머리 장착
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Helmet, info->Equip[0] );
			//	몸 장착(상의)
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Armor, info->Equip[1] );
			//	몸 장착(하의)
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Pants, info->Equip[2] );
			//	왼손 장착
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Shield, info->Equip[3] );
			//	오른손 장착
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_OneHandWeapon, info->Equip[4] );
			//	발 장착
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[5] );
			//	장갑 장착
			t->sOtherCharacter.HT_vOtherChar_SetItemType( eTNEqu_Boots, info->Equip[6] );
			return;
		}
		t = t->next;
	}
}

//----------Other Character LevelUp 을 알림---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_LevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			t->sOtherCharacter.HT_vOtherChar_LevelUpBrodcast( info );
			return;
		}
		t = t->next;
	}
}

HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_ItemAbrasionBroadcast(PS_SCP_ITEM_ABRASION_BROADCAST info)
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	CHTString str; //디버깅용
	//-----0x01:머리,0x02:귀걸이,0x03:목걸이,0x04:몸,0x05:벨트,0x06:양손,0x07:오른손
	//-----0x08:왼손,0x09:오른손 or 왼손,0x0a:오른손 위,0x0b:오른손 아래,0x0c:왼손 위,0x0d:왼손 아래,0x0e:발
	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			str.HT_szFormat("\n아이템 사라짐:KeyID(%d)-", info->dwKeyID);

			//----------아이템 장착 시스템----------//
			if( info->dwIndexWeapon == 0 )		//	무기
			{
				str += ("무기 사라짐");
				g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x07], t->sOtherCharacter.m_byOtherChar_HairType );
			}
			if( info->dwIndexBody == 0)			// 갑옷
			{
				str += ("갑옷 사라짐");
                g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x04], t->sOtherCharacter.m_byOtherChar_HairType );
			}
			if( info->dwIndexShield == 0)		// 방패
                g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x08], t->sOtherCharacter.m_byOtherChar_HairType );

			if( info->dwIndexHead == 0)			// 투구
                g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x01], t->sOtherCharacter.m_byOtherChar_HairType );

			if( info->dwIndexFoot == 0)			// 신발
			{
				str += ("신발 사라짐");
                g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x0e], t->sOtherCharacter.m_byOtherChar_HairType );
			}
			if( info->dwIndexBelt == 0)			// 벨트
                g_cEquipSystem->HT_EquipSys_UnEquip( t->sOtherCharacter.m_iOtherCharModelID, t->sOtherCharacter.m_byOtherChar_TribeType, t->sOtherCharacter.m_dwEquipItem[0x05], t->sOtherCharacter.m_byOtherChar_HairType );

			return;
		}

		t = t->next;
	}
}

//---------공격 관련----------//
//----------내가 공격대상인지 파악---------//
HTvector3 HTOtherCharacterSystem::HT_vecOtherCharSystem_GetAtkTargetCheck( DWORD dwTargetKeyID, HTint nCurHP, DWORD dwSkillIndex )
{
	HT_OTHERCHARACTER_NODE *t;

	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwTargetKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			HTvector3 vecPos = t->sOtherCharacter.m_cOtherCharMove->HT_fGetOtherCharMovePos();
			vecPos.y = (HTfloat)t->sOtherCharacter.m_iOtherCharModelID;
			return vecPos;
		}
		t = t->next;
	}

	return HTvector3( 0, 0, 0 );
}

//---------공격 받았을 때_맞는 액션 온----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetDisAttackOn( DWORD dwKeyID, DWORD dwSkillIndex, BYTE byAttackType, HTint iItemIndex )
{
	HT_OTHERCHARACTER_NODE *t;
	
	t = m_sOtherCharHead->next;
	while( t != m_sOtherCharTail )
	{
		if( dwKeyID == t->sOtherCharacter.m_dwOtherCharKeyID )
		{
			t->sOtherCharacter.HT_vOtherChar_SetAttack( dwSkillIndex, byAttackType, iItemIndex );
			return;
		}
		t = t->next;
	}
}

//---------HP 변경사항 체크, byReturnType:0x00:현재HP,0x01:맞은HP----------//
HTint HTOtherCharacterSystem::HT_nOtherCharacterSystem_GetHPCheck( DWORD dwKeyID, HTint nHP, BYTE byReturnType )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == dwKeyID )
		{
			if( byReturnType == 0x00 )
                return t->sOtherCharacter.m_nOtherChar_Resent_HP;
			else
				return t->sOtherCharacter.HT_nOtherChar_SetHPCheck( nHP );
		}
		t = t->next;
	}

	return 0;
}

//---------액티브 이펙트를 받았을 때----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetActiveEffectOn( DWORD dwKeyID, DWORD dwSkillIndex, HTbool bType, BYTE byLevel )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == dwKeyID )
		{
			t->sOtherCharacter.HT_vOtherChar_SetActiveSkillEffectOn( dwSkillIndex, bType, byLevel );
			break;
		}
		t = t->next;
	}
}

//----------Other Character가 스킬 공격 준비를 할 때---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_Skill_Ready_Char_Broadcast( PS_SCP_SKILL_READY_CHAR_BROADCAST info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			t->sOtherCharacter.HT_vOtherChar_Ready_Char_Broadcast( info );
			return;
		}
		t = t->next;
	}

	//----------이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해---------//
	HT_vOtherCharSystem_NetWork_RequestInitOtherChar( info->dwKeyID );
}

//----------Other Character가 사망했을 때----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_Death( PS_SCP_CHAR_MONSTER_DEATH_BROADCAST info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			t->sOtherCharacter.HT_hrOtherChar_Death();
			break;
		}
		t = t->next;
	}
}

HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_ChattingMessage( DWORD dwKeyID, BYTE byType, CHTString strMessage )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == dwKeyID )
		{
			//	채팅메시지
			t->sOtherCharacter.m_byOtherChar_ChattingType = byType;
			if( strMessage.HT_nGetSize() < 60 )
                t->sOtherCharacter.m_strOtherChar_ChattingMessage = strMessage;
			else
			{
				t->sOtherCharacter.m_strOtherChar_ChattingMessage.HT_hrCleanUp();
				CHTString::HT_hrStringCopy( t->sOtherCharacter.m_strOtherChar_ChattingMessage, strMessage, 55 );
				t->sOtherCharacter.m_strOtherChar_ChattingMessage += _T("...");		
			}
			t->sOtherCharacter.m_dwOtherChar_ChatMsgDelay = GetTickCount();
            break;
		}
		t = t->next;
	}
}

//-----------스킬 셋팅----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetActiveSkill( PS_SCP_RESP_SKILL_SELECT_BROADCAST info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->dwKeyID )
		{
			t->sOtherCharacter.HT_vOtherChar_SetActiveSkill( info );
			break;
		}
		t = t->next;
	}
}

//-----------액티브 스킬 이펙트 틀기----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_ActiveSkillEffectOn()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_ActiveSkillEffectOn();
		t = t->next;
	}
}

//-----------액티브 스킬 이펙트 꺼기----------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_ActiveSkillEffectOff()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_ActiveSkillEffectOff();
		t = t->next;
	}
}

//	길드 마크 셋팅 하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetGuildMarkID( CHTString strName, HTint iGuildMark )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( strName.HT_iStringCompare( t->sOtherCharacter.m_iOtherCharName ) == 0 )
		{
			t->sOtherCharacter.HT_vOtherChar_SetGuildMarkID( iGuildMark );
			break;
		}
		t = t->next;
	}
}

//	길드 마크 표현 하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_GuildEmblemOn()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_GuildEmblemOn();
		t = t->next;
	}
}

//	길드 마크 표현 안하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_GuildEmblemOff()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_GuildEmblemOff();
		t = t->next;
	}
}

//	주신 셋팅 하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetTrimuritiD( CHTString strName, BYTE byTrimuritii )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( strName.HT_iStringCompare( t->sOtherCharacter.m_iOtherCharName ) == 0 )
		{
			t->sOtherCharacter.HT_vOtherChar_SetTrimuritiD( byTrimuritii );
			break;
		}
		t = t->next;
	}
}
//	주신 마크 표현 하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_TrimuritiMarkOn()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_TrimuritiMarkOn();
		t = t->next;
	}
}
//	주신 마크 표현 안하기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_TrimuritiMarkOff()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		t->sOtherCharacter.HT_vOtherChar_TrimuritiMarkOff();
		t = t->next;
	}
}

//-----------파티원으로서 가입 및 탈퇴할때----------//
HTvoid HTOtherCharacterSystem::HT_vOtherChar_SetPartyJoineDisband( CHTString strName, BYTE byParty )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( strName.HT_iStringCompare( t->sOtherCharacter.m_iOtherCharName ) == 0 )
		{
			t->sOtherCharacter.HT_vOtherChar_SetPartyJoineDisband( byParty );
			break;
		}
		t = t->next;
	}
}

//----------이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해---------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_RequestInitOtherChar( DWORD dwKeyID )
{
	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_다시 만들어야 함" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//---------- GM의 투명모드를 설정 또는 해제를 요청한다를 알린다-------------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_NetWork_SCP_TRANSPARENCY_MODE_NOTIFY( PS_SCP_TRANSPARENCY_MODE_NOTIFY info )
{
	HTint nCompare;
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;
    
	while( t != m_sOtherCharTail )
	{
		nCompare = t->sOtherCharacter.m_iOtherCharName.HT_iStringCompare( info->szCharName );
		if( nCompare == 0 )
		{
			t->sOtherCharacter.HT_vNetWork_SCP_TRANSPARENCY_MODE_NOTIFY( info );
			break;
		}
		t = t->next;
	}
}

//----------공격 대상을 찿아내어 그의 위치를 얻어내----------//
HTvector3 HTOtherCharacterSystem::HT_vOtherCharSystem_GetAttackPos( DWORD dwTargetKeyID, DWORD dwSkillIndex, BYTE* byTargetType, HTint* iTargetModelID )
{
	HTvector3 vecTargetPos = HTvector3( 0, 0, 0 );

	//	1:어더캐릭터 검색
	vecTargetPos = this->HT_vecOtherCharSystem_GetAtkTargetCheck( dwTargetKeyID, 99, dwSkillIndex );
	if( vecTargetPos.x != 0 )
	{
		*byTargetType = 1;
		*iTargetModelID = (HTint)vecTargetPos.y;
		return vecTargetPos;
	}

	//	3:메인캐릭터 검색
	vecTargetPos = g_cMainCharacter->HT_vecMainChar_GetAtkTargetCheck( dwTargetKeyID );
	if( vecTargetPos.x != 0 )
	{
		*byTargetType = 3;
		*iTargetModelID = (HTint)vecTargetPos.y;
		return vecTargetPos;
	}

	return HTvector3( 0, 0, 0 );
}

//---------현재 타겟창에 정보가 보여지고 있는 캐릭터의 모델 ID 반환-------------//
DWORD HTOtherCharacterSystem::HT_dwOtherCharacterSystem_GetTargetModelID()
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_bOtherChar_Info_Sw == HT_TRUE )
		{
			return t->sOtherCharacter.m_iOtherCharModelID;
		}
		t = t->next;
	}

	return -1;
}

//-----------파티 가입/탈퇴를 셋팅-------------//
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetPartyJoin( CHTString strTemp, HTbool bType )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( strTemp.HT_iStringCompare( t->sOtherCharacter.m_iOtherCharName ) == 0 )
		{
			if( bType == HT_TRUE )	t->sOtherCharacter.m_byOtherChar_PartyMember = 0x02;
			else					t->sOtherCharacter.m_byOtherChar_PartyMember = 0x01;
			return;
		}
		t = t->next;
	}
}

HTRESULT HTOtherCharacterSystem::HT_hrOtherCharSystem_CompareGuild( HTint iKeyID, HTint iGuildMark )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == iKeyID )
		{
			if( t->sOtherCharacter.m_dwOtherChar_GuildEmblemID == iGuildMark )
				return HT_OK;
			else
                return HT_FAIL;
		}
		t = t->next;
	}

	return HT_FAIL;
}

//	스킬 캐스팅을 알림
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_Network_Skill_Unit_Skill_Broadcast( PS_CSP_CAST_UNIT_SKILL pData )
{
	//	공격자의 ID
	HTint iAttackerID;
	//	기본 공격 데이타
	S_MSG_ATTACK_OTHERMOB info;
	memset( &info, 0, sizeof( S_MSG_ATTACK_OTHERMOB ) );

	info.snRes = pData->snRes;
	iAttackerID = pData->snCasterKeyID;
	info.iSkillID = pData->snSkillID;
	info.PosX = pData->snCasterX;
	info.PosY = pData->snCasterZ;
	info.TargetX = pData->snMapX;
	info.TargetZ = pData->snMapZ;
	info.krgTarget[0].snKeyID = pData->kTarget.snKeyID;
	info.krgTarget[0].snDamage = pData->kTarget.snDamage;

	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == iAttackerID )
		{
			info.vecTargetPos = this->HT_vOtherCharSystem_GetAttackPos( info.krgTarget[0].snKeyID, info.iSkillID, &info.byTargetType, &info.iTargetModelID );
			if( info.byTargetType != 0 )
			{
				t->sOtherCharacter.HT_vOtherChar_Network_Skill_Cast_Broadcast( info );
			}
			return;
		}
		t = t->next;
	}

	//	이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해
	this->HT_vOtherCharSystem_NetWork_RequestInitOtherChar( iAttackerID );
}

HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_Network_Skill_Area_Skill_Broadcast( PS_CSP_CAST_AREA_SKILL pData )
{
	//	공격자의 ID
	HTint iAttackerID;
	//	기본 공격 데이타
	S_MSG_ATTACK_OTHERMOB info;
	memset( &info, 0, sizeof( S_MSG_ATTACK_OTHERMOB ) );

	info.snRes = pData->snRes;
	iAttackerID = pData->snCasterKeyID;
	info.iSkillID = pData->snSkillID;
	info.PosX = pData->snCasterX;
	info.PosY = pData->snCasterZ;
	info.TargetX = pData->snMapX;
	info.TargetZ = pData->snMapZ;
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; ++i )
	{
		info.krgTarget[i].snKeyID = pData->krgTarget[i].snKeyID;
		info.krgTarget[i].snDamage = pData->krgTarget[i].snDamage;
	}	

	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == iAttackerID )
		{
			info.vecTargetPos = this->HT_vOtherCharSystem_GetAttackPos( info.krgTarget[0].snKeyID, info.iSkillID, &info.byTargetType, &info.iTargetModelID );
			if( info.byTargetType != 0 )
			{
				t->sOtherCharacter.HT_vOtherChar_Network_Skill_Cast_Broadcast( info );
			}
			return;
		}
		t = t->next;
	}

	//	이닛브로드캐스트 받지못했을때 OtherChar를 보정해주기 위해
	this->HT_vOtherCharSystem_NetWork_RequestInitOtherChar( iAttackerID );
}

//	PS_SCP_RESP_UPDATE_STATUS Setting
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SCPRespUpdateStatus( PS_SCP_RESP_UPDATE_STATUS info )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == info->snKeyID )
		{
			t->sOtherCharacter.m_nOtherChar_Resent_HP = info->iHP;
			break;
		}
		t = t->next;
	}
}

//	동작 멈추기
HTvoid HTOtherCharacterSystem::HT_vOtherCharSystem_SetStop( HTint iKeyID )
{
	HT_OTHERCHARACTER_NODE *t;
	t = m_sOtherCharHead->next;

	while( t != m_sOtherCharTail )
	{
		if( t->sOtherCharacter.m_dwOtherCharKeyID == iKeyID )
		{
			t->sOtherCharacter.m_cOtherCharMove->HT_vOtherCharMoveStop();
			break;
		}
		t = t->next;
	}
}

//[선미-액션가면]  님의 말:
//HT_Othercharacter.cpp => m_cOtherCharMove의
//m_vecOtherTargetPos, m_fOtherCharResentDirect, m_vecOtherCharVelocity, m_fOtherCharSpeedGrade
//[선미-액션가면]  님의 말:
//-값을 가지는 변수들입니다
//[선미-액션가면]  님의 말:
//m_vecOtherTargetPos는 y좌표값이 -
