
#include "stdAfx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

HTNPCSystem::HTNPCSystem():m_dwActiveNPCID(0)
{
}

HTNPCSystem::~HTNPCSystem()
{
}

HTvoid HTNPCSystem::HT_vNPCSystem_CleanUp()
{
	HT_LL_hrDeleteAll();
	HT_DELETE( m_sNPCHead );
	HT_DELETE( m_sNPCTail );
}

HTRESULT HTNPCSystem::HT_hNPCSystemInit()
{
	//----------LL 초기화---------//
	HT_LL_vInitList();

	//----------OtherChar 정보 표시위해----------//
	m_bNPC_Info_Sw		= HT_FALSE;
	
	m_dwActiveNPCID = 0;
	m_byQuestIndex = m_byLevel = m_byLevel_Time = 0;

	return HT_OK;
}

//-------현재 Zone에 있는 NPC 생성--------//
HTvoid HTNPCSystem::HT_vNPCSystem_CreateNPC()
{
	//	NPC를 생성
	std::vector<HTIDLevel> vectorIDLevel;
	std::vector<HTIDLevel>::iterator vec_It;
	HTint id = 0;
	HTshort sPosX = 0, sPosZ = 0;
	HTbyte byZone = 0;
	HTbool bFlag;

	if( g_pParamMgr->HT_bGetNPCAllID( &vectorIDLevel ) )
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;

			// 한국, 중국을 제외한 나머지 국가는 크리슈나 NPC가 안나온다.
			bFlag = HT_TRUE;
			switch(g_iInationalType)
			{
				case INATIONALTYPE_KOREA:
				case INATIONALTYPE_CHINA:
				case INATIONALTYPE_INDONESIA:
				case INATIONALTYPE_JAPEN:
					break;
				case INATIONALTYPE_PHILIPPINE:
				case INATIONALTYPE_TAIWAN:
					{
						if( id == 1263 ||	//	크리슈나	만다라
							id == 1264 ||	//	크리슈나	샴발라
							id == 1265 ||	//	크리슈나	지나
							id == 1266 )	//	크리슈나	유배지
							bFlag = HT_FALSE;
					}
					break;
			}

			// 위탁상점 NPC는 필리핀과 한국에서만 나온다.
			if( id >= 1307 && id <= 1329 )
			{
				switch(g_iInationalType)
				{
					case INATIONALTYPE_KOREA:
					case INATIONALTYPE_JAPEN:
					case INATIONALTYPE_PHILIPPINE:
					case INATIONALTYPE_CHINA:
						break;
					default:
						bFlag = HT_FALSE;
						break;
				}
			}

			// 모든 나라에 대한 체크 여부 (퀘스트) 다음과 같은 NPC는 삭제하고 시작한다.
			if ( id == 1305) bFlag = HT_FALSE;	// 토용
			if ( id == 1304) bFlag = HT_FALSE;	// 토용장인
			if ( id == 1306) bFlag = HT_FALSE;	// 북두성군

			if ( id == 1437) bFlag = HT_FALSE;	// 주정뱅이
			if ( id == 1438) bFlag = HT_FALSE;	// 유리
			if ( id == 1439) bFlag = HT_FALSE;	// 나오키
			if ( id == 1440) bFlag = HT_FALSE;	// 전쟁터 폐혀지역의 정찰병
			if ( id == 1441) bFlag = HT_FALSE;	// 버려진 요새의 정찰병
			if ( id == 1442) bFlag = HT_FALSE;	// 갓파부락의 정찰병
			if ( id == 1443) bFlag = HT_FALSE;	// 광산지역의 정찰병

			if (bFlag == HT_TRUE)
			{
				if( g_pParamMgr->HT_bLockID( id ) == true )
				{
					g_pParamMgr->HT_bGetNPCZone( &byZone );
					if( (g_wResentZoneServerID) == (WORD)byZone )	// 현재 Zone에 있는 NPC인지
					{
						g_pParamMgr->HT_bGetNPCPosition( &sPosX, &sPosZ );
						if( sPosX != 0 && sPosZ != 0 )
							this->HT_LL_hrInsertAfter( id, sPosX, sPosZ );
					}
					g_pParamMgr->HT_bUnLockID( id );
				}
			}

			++vec_It;
		}
	}
}

// 특정 NPC 생성
bool HTNPCSystem::HT_bNPCSystem_CreateNPC(HTint iNPCIndex)
{
	//	NPC를 생성
	HTshort sPosX = 0, sPosZ = 0;

	if( g_pParamMgr->HT_bLockID( iNPCIndex ) == true )
	{
		g_pParamMgr->HT_bGetNPCPosition( &sPosX, &sPosZ );
		this->HT_LL_hrInsertAfter( iNPCIndex, sPosX, sPosZ );
		g_pParamMgr->HT_bUnLockID( iNPCIndex );
		return true;
	}
	return false;
}

//----------업데이트/컨트롤---------//
HTvoid HTNPCSystem::HT_vNPCSystemControl()
{
	HT_NPC_NODE *t;
	HT_NPC_NODE *s;
	
	t = m_sNPCHead->next;
	while( t != m_sNPCTail )
	{
		t->sNPC.HT_vNpcControl();
		s = t;
		t = t->next;
	}
}

//----------NPC 를 픽 했을 때---------//
HTint HTNPCSystem::HT_vNPCSystemComIDCheck( HTint iID )
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( iID == n->sNPC.m_iNpcModelID )
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
			{
				if( n->sNPC.m_dwNpcIndex == 1157 || n->sNPC.m_dwNpcIndex == 1159 )
				{
					CHTString strMessage;
					// 다른 주신지경의 NPC는 선택할수 없습니다.
					if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCannotClickNPC, &strMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
                    return 0;
				}
			}
			else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
			{
				if( n->sNPC.m_dwNpcIndex == 1158 || n->sNPC.m_dwNpcIndex == 1159 )
                 {
					CHTString strMessage;
					// 다른 주신지경의 NPC는 선택할수 없습니다.
					if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCannotClickNPC, &strMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
                    return 0;
				}
			}
			else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
			{
				if( n->sNPC.m_dwNpcIndex == 1157 || n->sNPC.m_dwNpcIndex == 1158 )
                {
					CHTString strMessage;
					// 다른 주신지경의 NPC는 선택할수 없습니다.
					if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCannotClickNPC, &strMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
                    return 0;
				}
			}

			//---------정보 디스플레이 셋팅----------//
			m_bNPC_Info_Sw = HT_TRUE;
			n->sNPC.HT_vNPC_SetInfoDisplay();
			//---------NPC 믈릭----------//
			n->sNPC.HT_vNPC_Click();
			//	정보 셋팅
			g_pMainBar->HT_vSetObjectTextDraw( n->sNPC.m_strNPCName );
			return n->sNPC.m_iNpcModelID;
		}
		n = n->next;
	}

	return 0;
}

//---------현재 타겟창에 정보가 보여지고 있는 NPC 모델 ID 반환-------------//
DWORD HTNPCSystem::HT_vNPCSystem_GetTargetModelID()
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( n->sNPC.m_bNPC_Info_Sw == HT_TRUE )
		{
			return n->sNPC.m_iNpcModelID;
		}
		n = n->next;
	}

	return -1;
}

//	Returns Get	bCheck2ObjCollide
HTint HTNPCSystem::HT_iNPCSystem_GetCheck2ObjCollide( HTint iKeyID, HTvector3 vecMainCharPos, HTfloat ColidSize )
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		//	충돌하면 상대방 KeyID 반환
		if( g_pEngineHandler->HT_bCheck2ObjCollide( n->sNPC.m_iNpcModelID, vecMainCharPos, ColidSize ) )
		{
			return n->sNPC.m_iNpcModelID;
		}
		n = n->next;
	}

	return 0;
}

//----------NPC 정보창 초기화---------//
HTvoid HTNPCSystem::HT_vNPCSystem_HPWindowInit()
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *t;
	t = m_sNPCHead->next;

	while( t != m_sNPCTail )
	{
		if( t->sNPC.m_bNPC_Info_Sw == HT_TRUE )
		{
            //---------정보 디스플레이 셋팅----------//
			m_bNPC_Info_Sw = HT_FALSE;
			t->sNPC.HT_vNPC_SetInfoCancel();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
		}
		t = t->next;
	}
}

//----------NPC 전부 클리어---------//
HTvoid HTNPCSystem::HT_vNPCSystem_TotalNPCDelete()
{
	//----------LL 데이타 전부 지우기---------//
	HT_LL_hrDeleteAll();
}

//----------지정한 맵셀위에 NPC가 있는가?---------//
HTint HTNPCSystem::HT_vNPCSystemCheckMapCell( HTint iMapCellX, HTint iMapCellZ )
{
	//-----NPC 노드에서 체크-----//
/*	HT_NPC_NODE *t;
	t = m_sNPCHead->next;
	while( t != m_sNPCTail )
	{
		for( HTint i=t->sNPC.m_vNPCMapCellX-(t->sNPC.m_byNpcCellSize/2) ; i<t->sNPC.m_vNPCMapCellX+(t->sNPC.m_byNpcCellSize/2) ; i++ )
		{
			for( HTint j=t->sNPC.m_vNPCMapCellZ-(t->sNPC.m_byNpcCellSize/2) ; j<t->sNPC.m_vNPCMapCellZ+(t->sNPC.m_byNpcCellSize/2) ; j++ )
			{
				if( iMapCellX==i &&	iMapCellZ==j )
				{
					return t->sNPC.m_iNpcModelID;
				}
			}
		}
		t = t->next;
	}
*/
	return -1;
}
 
//----------반환값들----------//
//----------픽된 NPC를 기능별로 연결----------//
HTvoid HTNPCSystem::HT_pNPCSystem_PickConnect( HTint nTempID )
{
	// 개인 상점 열기/구입 일 경우, 다른 작업(1:1trade 등)을 하고 있을 경우 처리하지 않는다
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return;
 
	DWORD dwIndex = HT_pNPCSystem_GetIndexFromModelID( nTempID );
	
	if( dwIndex == 0 || dwIndex == -1 )	// nTempID에 해당하는 NPC를 찾지 못했음
		return;

	// NPC와의 거리 체크
	HTPoint pNPCCellPos = HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
	HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
	pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;
	
	// NPC와의 거리가 제한 내인 경우에는 NPC의 이벤트를 처리함
	if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x <= NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
	{
		DWORD dwActiveNPC = g_cNPCControl->HT_iNPCControl_ActiveNPCIndex();
		if( dwIndex == dwActiveNPC ) // 현재 같은 NPC가 활성화되어 있는 경우 처리 안함
			return;
		else if( dwActiveNPC != 0 )	// 활성화되어있는  NPC가 있는 경우
		{
			// 대화상자 닫기 - NPC와 관련된 모든 창 닫기
			g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();	
		}

		m_dwActiveNPCID = dwIndex;

		// NPC를 클릭했을때, NPC에 따른 반응소리를 틀어준다.
		HTdword dwSoundID = g_pEngineHandler->HT_dwGetNPCClickSoundID( dwIndex );
		g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );

		HT_vNetWork_CSP_Req_Quest_Notify_Level();
		//------------------------------------------------
		// NPC 창 뜨도록 임시 설정.2003.11.28 선미
		//S_SCP_QUEST_NOTIFY_LEVEL info;
		//info.snNPCIndex = (HTshort)dwIndex;
		//info.byIndex = 81;
		//info.byLevel = 1;
		//g_sNPCSystem->HT_vNetWork_SCP_RESP_Quest_Notify_Level( &info );
		//------------------------------------------------
	}
	// NPC와의 거리가 제한보다 먼 경우에는 메시지를 표시하고 처리하지 않음
	else
	{
		CHTString strMessage;
		// NPC와의 거리가 멉니다.
		if( g_pMessageMgr->HT_bGetMessage( eMsgCommonDistanceErrToNPC, &strMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
	}
}

//-----------현재 활성화 되어있는 NPC를 비활성화로 설정----------//
HTvoid	HTNPCSystem::HT_vNPCSystem_AntiActiveNPC(/*DWORD dwKeyID*/)
{
//	if(m_dwActiveNPCID == dwKeyID)
		m_dwActiveNPCID = 0;

	m_byQuestIndex = m_byLevel = m_byLevel_Time = 0;
}

HTPoint HTNPCSystem::HT_pNPCSystem_GetCellPosFromIndex( DWORD dwNPCIndex )
{
	HTPoint pCellPos;
	pCellPos.x = 0; pCellPos.y = 0;

	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( dwNPCIndex == n->sNPC.m_dwNpcIndex )
		{
			pCellPos.x = n->sNPC.m_vNPCMapCellX;
			pCellPos.y = n->sNPC.m_vNPCMapCellZ;
			return pCellPos;
		}
		n = n->next;
	}

	return pCellPos;
}

HTvector3 HTNPCSystem::HT_vNPCSystem_GetCoordFromModelID( DWORD dwID )
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( dwID == n->sNPC.m_iNpcModelID )
		{
			return n->sNPC.m_cNPCMove->HT_vecNPCMove_GetPos();
		}
		n = n->next;
	}

	return HTvector3( 0, 0, 0 );;
}

DWORD HTNPCSystem::HT_pNPCSystem_GetIndexFromModelID( HTint nModelID )
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( nModelID == n->sNPC.m_iNpcModelID )
		{
			return n->sNPC.m_dwNpcIndex;
		}
		n = n->next;
	}

	return 0;
}
//----------NPC 이름 알아오기 ------//
HTvoid HTNPCSystem::HT_vNPCSystem_GetName(DWORD dwIndex, CHTString& szName)
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( dwIndex == n->sNPC.m_dwNpcIndex )
		{
			szName = n->sNPC.m_strNPCName;
			break;
		}
		n = n->next;
	}
}

//----------NPC 이름 알아오기 ------//
HTvoid HTNPCSystem::HT_vNPCSystem_GetNameForModelID(DWORD dwModelID, CHTString& szName)
{
	//-----NPC 노드에서 체크-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		if( dwModelID == n->sNPC.m_iNpcModelID )
		{
			szName = n->sNPC.m_strNPCName;
			break;
		}
		n = n->next;
	}
}

//	Set
//	Set Chat Msg
HTvoid HTNPCSystem::HT_vNPCSystem_SetChatMsg( HTint iID, CHTString strMessage )
{
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;

	while( n != m_sNPCTail )
	{
		if( n->sNPC.m_dwNpcIndex == iID )
		{
			n->sNPC.m_strNPCChatMsg.HT_hrCleanUp();
			//	채팅메시지
			if( strMessage.HT_nGetSize() < 60 )
				n->sNPC.m_strNPCChatMsg = strMessage;
			else
			{
				CHTString::HT_hrStringCopy( n->sNPC.m_strNPCChatMsg, strMessage, 55 );
				n->sNPC.m_strNPCChatMsg += _T("...");		
			}
			n->sNPC.m_dwNPCChatMsgStartTime = timeGetTime();
            break;
		}
		n = n->next;
	}
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTNPCSystem::HT_LL_vInitList()
{
	m_sNPCHead = NULL;
	m_sNPCTail = NULL;

	m_sNPCHead = new HT_NPC_NODE;
	m_sNPCTail = new HT_NPC_NODE;

	m_sNPCHead->next = m_sNPCTail;
	m_sNPCTail->next = m_sNPCTail;

}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTRESULT HTNPCSystem::HT_LL_hrInsertAfter( HTint iNPCIndex, short snX, short snZ )
{
	HT_NPC_NODE *s;

	s = NULL;
	s = new HT_NPC_NODE;
	s->sNPC.HT_vNpc_Input( iNPCIndex, snX, snZ );
	s->next = m_sNPCHead->next;
	m_sNPCHead->next = s;

	return HT_OK;
}

//---------- 특정 NPC 지우기 -------------//
HTbool HTNPCSystem::HT_bNPCSystem_DeleteNPC( DWORD dwNPCKeyID )
{
	return HT_LL_bDeleteNode(dwNPCKeyID);
}

//----------LL 데이타 지우기---------//
HTbool HTNPCSystem::HT_LL_bDeleteNode( int iNPCKeyID )
{
	HT_NPC_NODE *s;
	HT_NPC_NODE *p;

	p = m_sNPCHead;
	s = p->next;
	while( s->sNPC.m_dwNpcIndex != iNPCKeyID && s != m_sNPCTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sNPCTail )
	{
		p->next = s->next;
		s->sNPC.HT_vNpcDistroy();
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL 데이타 전부 지우기---------//
HTvoid HTNPCSystem::HT_LL_hrDeleteAll()
{
	HT_NPC_NODE *s;
	HT_NPC_NODE *t;
	
	t = m_sNPCHead->next;
	while( t != m_sNPCTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sNPCHead->next = m_sNPCTail;
}

//----------랜더---------//
HTvoid HTNPCSystem::HT_vNPCSystemRender()
{
	HT_NPC_NODE *t;
	t = m_sNPCHead->next;

	//	방송모드일때는 스킵
	if( g_bGamePlayMovieForGlobal )
		return;

	while( t != m_sNPCTail )
	{
		//----------랜더_이름----------//
		HT_vNPCSystem_RenderName( t );
		t = t->next;
	}

	//---------정보 디스플레이 셋팅----------//
	if( m_bNPC_Info_Sw == HT_TRUE )
	{
		m_bNPC_Info_Sw = HT_FALSE;
		//g_pMainBar->HT_vSetObjectHPOut();
	}
}

//----------랜더_이름----------//
HTvoid HTNPCSystem::HT_vNPCSystem_RenderName( HT_NPC_NODE* t )
{
	BYTE bResult = g_cAoi->HT_AOI_Level( t->sNPC.HT_vNpcGetCell() );
	if( bResult <= AOI_LEVEL_6 )
	{
		HTvector3 vTextPos = t->sNPC.m_cNPCMove->HT_vecNPCMove_GetPos();
		vTextPos.y += 25;
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->sNPC.m_strNPCName, vTextPos, HT_COLOR( 1.00f, 1.00f, 0.00f, 1.0f ) );

		//   -> 채팅 메시지 표시
		if( !t->sNPC.m_strNPCChatMsg.HT_bIsEmpty() )
		{
			DWORD dwPassTime = timeGetTime();
			g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, (HTtchar*)t->sNPC.m_strNPCChatMsg, vTextPos, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.7f ), 3.0f );
			vTextPos.y += 2.0f;
			if( dwPassTime > t->sNPC.m_dwNPCChatMsgStartTime + CHATMSGDELAYTIME )
				t->sNPC.m_strNPCChatMsg.HT_hrCleanUp();
		}
	}
}

//	Render MiniMap Point
HTvoid HTNPCSystem::HT_vNPCSystem_MiniMapPoint()
{
	HTPoint CellPt;
	g_cMiniMap->HT_vMiniMap_Render_StartObject( 0x03 );

	HT_NPC_NODE *t;
	t = m_sNPCHead->next;

	while( t != m_sNPCTail )
	{
		if( g_cMiniMap->HT_bMiniMap_IsOn() )
		{
			CellPt.x = t->sNPC.m_cNPCMove->m_pPatrol_Node[0].x;
			CellPt.y = t->sNPC.m_cNPCMove->m_pPatrol_Node[0].y;
			g_cMiniMap->HT_vMiniMap_Render_NPC( 0x01, CellPt );
		}
		t = t->next;
	}
}

//----------------------------------------------------//
// 서버 관련
//----------------------------------------------------//
//------------친밀도 계산 - NPC 계통별 친밀도+브라만 포인트-------------//
HTvoid HTNPCSystem::HT_vNPCSystem_CalNPCRelative(/*HTint nGroupbyFamily, */HTint& nTotalPoint, HTint& nSection)
{
	nTotalPoint = g_cStatus->HT_byGetLevel();
	
	// 만다라 마을 NPC를 기준으로 만들었음. 다른 마을이 추가될 경우 수정해야함.
	if( nTotalPoint <= 10)
		nSection = 1;
	else if( 10 < nTotalPoint && nTotalPoint <= 20)
		nSection = 2;
	else if( 20 < nTotalPoint && nTotalPoint <= 30)
		nSection = 3;
	else if( 30 < nTotalPoint && nTotalPoint <= 40)
		nSection = 4;
	else if( 40 < nTotalPoint && nTotalPoint <= 50)
		nSection = 5;
	else if( 50 < nTotalPoint && nTotalPoint <= 60)
		nSection = 6;
	else if( 60 < nTotalPoint && nTotalPoint <= 70)
		nSection = 7;
	else if( 70 < nTotalPoint && nTotalPoint <= 80)
		nSection = 8;
	else if( 80 < nTotalPoint && nTotalPoint <= 90)
		nSection = 9;
	else //if( 520 < nTotalPoint )
		nSection = 10;
}

//-----------현재 활성화된 NPC를 기준으로 퀘스트 진행 상태 설정-----------//
HTvoid HTNPCSystem::HT_vNPCSystem_SetLastQuestStatus(BYTE byQuestIndex, BYTE byLevel, BYTE byLevelTime)
{
	m_byQuestIndex = byQuestIndex;	// 퀘스트 번호
	m_byLevel = byLevel;
	m_byLevel_Time = byLevelTime;
}

//-----------시나리오 퀘스트의 다음 진행 상태 설정-----------//
HTvoid HTNPCSystem::HT_vNPCSystem_SetNextQuestStatus()
{
	g_pEngineHandler->HT_vGetNextQuestLevel(m_byLevel, m_byLevel_Time);
	
	if( m_byLevel == 0 && m_byLevel_Time == 0 )
		m_byQuestIndex = 0;	// 퀘스트 없음
}

//-----------퀘스트 진행 상태를 알려준다-----------//
HTvoid HTNPCSystem::HT_vNetWork_CSP_Req_Quest_Notify_Level( )
{ 
	PS_CSP_QUEST_NOTIFY_LEVEL info = HT_NULL;
	info = new S_CSP_QUEST_NOTIFY_LEVEL;

	info->snNPCIndex = (HTshort)m_dwActiveNPCID;

	g_pNetWorkMgr->RequestQuestNotifyLevel( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_QuestNotifyLevel : %d", info->snNPCIndex);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid HTNPCSystem::HT_vNetWork_SCP_RESP_Quest_Notify_Level(PS_SCP_QUEST_NOTIFY_LEVEL info)
{
	short int snNpcIndex = 0;
	// 임시 코딩 (만다라 2,3 존에서 대화를 걸었을 경우 퀘스트 진행을 위해 1번존 index로 변경)

	switch( info->snNPCIndex)
	{
		// 무기 상인
	case 1101 :	// 만다라
	case 1205 :	// 18번 만다라
	case 1235 :	// 19번 만다라
		{
			snNpcIndex = 1101;
		}
		break;

		// 방어구 상인
	case 1102 :	// 만다라
	case 1206 :	// 18번 만다라
	case 1236 :	// 19번 만다라
		{
			snNpcIndex = 1102;
		}
		break;

		// 액세서리 상인 
	case 1103 :	// 만다라
	case 1207 :	// 18번 만다라
	case 1237 :	// 19번 만다라
		{
			snNpcIndex = 1103;
		}
		break;

		// 승려
	case 1104 :	// 만다라
	case 1208 :	// 18번 만다라
	case 1238 :	// 19번 만다라
		{
			snNpcIndex = 1104;
		}
		break;

		//	물품보관지기
	case 1105 :	// 만다라
	case 1209 :	// 18번 만다라
	case 1239 :	// 19번 만다라
		{
			snNpcIndex = 1105;
		}
		break;

		// 수비대장
	case 1108 :	// 만다라 
	case 1212 : // 18번 만다라
	case 1242 :	// 19번 만다라
		{
			snNpcIndex = 1108;
		}
		break;

		// 역마꾼(게이트)
	case 1106 :	// 만다라
	case 1210 : // 18번 만다라
	case 1240 :	// 19번 만다라
		{
			snNpcIndex = 1106;
		}
		break;
		// 주술사(마법동물대여)
	case 1107 :		// 만다라
	case 1211 :		// 18번 만다라
	case 1241 :		// 19번 만다라
		{
			snNpcIndex = 1107;
		}
		break;
		// 병사1
	case 1001 :	// 만다라
	case 1201 :	// 18번 만다라
	case 1231 :	// 19번 만다라
		{
			snNpcIndex = 1001;
		}
		break;
		// 병사2
	case 1002 :	// 만다라
	case 1202 :	// 18번 만다라
	case 1232 :	// 19번 만다라
		{
			snNpcIndex = 1002;
		}
		break;
		//	남자아이1
	case 1003 :	// 만다라
	case 1203 : // 18번 만다라
	case 1233 : // 19번 만다라
		{
			snNpcIndex = 1003;
		}
		break;

		//	여자아이1
	case 1005 :	// 만다라
	case 1204 : // 18번 만다라
	case 1234 : // 19번 만다라
		{
			snNpcIndex = 1005;
		}
		break;

		// 퀘스트용 병사 NPC
	case 1115 :	// 공동 협의체
	case 1213 :	// 18번 만다라
	case 1243 : // 19번 만다라
		{
			snNpcIndex = 1115;
		}
		break;

		// 스포르바다 병사 NPC
	case 1116 :
	case 1214 : // 18번 만다라
	case 1244 : // 19번 만다라
		{
			snNpcIndex = 1116;
		}
		break;

		// 아바타라의 무덤 아이
	case 1117 :
	case 1215 : // 18번 만다라
	case 1245 : // 19번 만다라
		{
			snNpcIndex = 1117;
		}
		break;
	default:
		snNpcIndex = info->snNPCIndex;
		break;
	}

	//---뒤늦게 메세지가 왔을 경우를 대비해서----//
	// 개인 상점 열기/구입 일 경우 || 다른 작업(1:1trade 등)을 하고 있을 경우
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return;
 
	// NPC와의 거리 체크
	HTPoint pNPCCellPos = HT_pNPCSystem_GetCellPosFromIndex( info->snNPCIndex );
	HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
	pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;
	
	// NPC와의 거리가 제한 내인 경우에는 NPC의 이벤트를 처리함
	if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x > NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
		return;

	//m_dwActiveNPCID = info->snNPCIndex;
	m_dwActiveNPCID = snNpcIndex;	// 위에서 정의한 만다라 1 존의 NPC index를 대입하여 처리함

	// 캐릭터의 가장 마지막 퀘스트의 현재 상태 설정
	m_byQuestIndex = info->byIndex;	// 퀘스트 번호

	// 퀘스트 진행상태. 1:시작, 2~:진행중, 255:완료
	if( info->byIndex <= TUTORIAL_QUEST_END )	// 튜토리얼 퀘스트
		m_byLevel = info->byLevel;
	else if( info->byIndex <= SCENARIO_QUEST_6_END )	// 시나리오 퀘스트
	{
		m_byLevel = m_byLevel_Time = 0;
		g_pEngineHandler->HT_vGetQuestLevel(info->byLevel, m_byLevel, m_byLevel_Time);
		
		// -------------------------------- 임시(지나2차 퀘스트 수행불가 처리) ------------------------------
		//if (info->byIndex == QUEST_JINA_1 && info->byLevel == QUEST_STATUS_START)
//			m_byLevel = m_byLevel_Time = 0;

		// 2차 전직퀘스트를 완료했을 경우 스킬 트리를 새로 그려준다
		if( info->byIndex == QUEST_SHAMBALA_11 && info->byLevel == QUEST_STATUS_SUCCESS )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_SKILL ) ) // 기존 스킬창 닫기
				g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
			
			g_cSkillInventory->HT_hrSkillItemInit(); // 스킬트리 다시 그리기
		}
	}
	// 독립 퀘스트 - 차크라/스킬 초기화 퀘스트 2004.3.17
	//else if( info->byIndex == QUEST_INDEPENDENCE_1 || info->byIndex == QUEST_INDEPENDENCE_2 )
	//{
	//	m_byLevel = m_byLevel_Time = 1;
	//}
	else
		m_byLevel = m_byLevel_Time = 0;

	// NPC창 띄우기
	g_cNPCControl->HT_vNPCControl_Active( info->snNPCIndex );
}
