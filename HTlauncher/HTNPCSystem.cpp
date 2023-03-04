
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
	//----------LL �ʱ�ȭ---------//
	HT_LL_vInitList();

	//----------OtherChar ���� ǥ������----------//
	m_bNPC_Info_Sw		= HT_FALSE;
	
	m_dwActiveNPCID = 0;
	m_byQuestIndex = m_byLevel = m_byLevel_Time = 0;

	return HT_OK;
}

//-------���� Zone�� �ִ� NPC ����--------//
HTvoid HTNPCSystem::HT_vNPCSystem_CreateNPC()
{
	//	NPC�� ����
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

			// �ѱ�, �߱��� ������ ������ ������ ũ������ NPC�� �ȳ��´�.
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
						if( id == 1263 ||	//	ũ������	���ٶ�
							id == 1264 ||	//	ũ������	���߶�
							id == 1265 ||	//	ũ������	����
							id == 1266 )	//	ũ������	������
							bFlag = HT_FALSE;
					}
					break;
			}

			// ��Ź���� NPC�� �ʸ��ɰ� �ѱ������� ���´�.
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

			// ��� ���� ���� üũ ���� (����Ʈ) ������ ���� NPC�� �����ϰ� �����Ѵ�.
			if ( id == 1305) bFlag = HT_FALSE;	// ���
			if ( id == 1304) bFlag = HT_FALSE;	// �������
			if ( id == 1306) bFlag = HT_FALSE;	// �ϵμ���

			if ( id == 1437) bFlag = HT_FALSE;	// ��������
			if ( id == 1438) bFlag = HT_FALSE;	// ����
			if ( id == 1439) bFlag = HT_FALSE;	// ����Ű
			if ( id == 1440) bFlag = HT_FALSE;	// ������ ���������� ������
			if ( id == 1441) bFlag = HT_FALSE;	// ������ ����� ������
			if ( id == 1442) bFlag = HT_FALSE;	// ���ĺζ��� ������
			if ( id == 1443) bFlag = HT_FALSE;	// ���������� ������

			if (bFlag == HT_TRUE)
			{
				if( g_pParamMgr->HT_bLockID( id ) == true )
				{
					g_pParamMgr->HT_bGetNPCZone( &byZone );
					if( (g_wResentZoneServerID) == (WORD)byZone )	// ���� Zone�� �ִ� NPC����
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

// Ư�� NPC ����
bool HTNPCSystem::HT_bNPCSystem_CreateNPC(HTint iNPCIndex)
{
	//	NPC�� ����
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

//----------������Ʈ/��Ʈ��---------//
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

//----------NPC �� �� ���� ��---------//
HTint HTNPCSystem::HT_vNPCSystemComIDCheck( HTint iID )
{
	//-----NPC ��忡�� üũ-----//
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
					// �ٸ� �ֽ������� NPC�� �����Ҽ� �����ϴ�.
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
					// �ٸ� �ֽ������� NPC�� �����Ҽ� �����ϴ�.
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
					// �ٸ� �ֽ������� NPC�� �����Ҽ� �����ϴ�.
					if( g_pMessageMgr->HT_bGetMessage( eMsgCommonCannotClickNPC, &strMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
                    return 0;
				}
			}

			//---------���� ���÷��� ����----------//
			m_bNPC_Info_Sw = HT_TRUE;
			n->sNPC.HT_vNPC_SetInfoDisplay();
			//---------NPC �ɸ�----------//
			n->sNPC.HT_vNPC_Click();
			//	���� ����
			g_pMainBar->HT_vSetObjectTextDraw( n->sNPC.m_strNPCName );
			return n->sNPC.m_iNpcModelID;
		}
		n = n->next;
	}

	return 0;
}

//---------���� Ÿ��â�� ������ �������� �ִ� NPC �� ID ��ȯ-------------//
DWORD HTNPCSystem::HT_vNPCSystem_GetTargetModelID()
{
	//-----NPC ��忡�� üũ-----//
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
	//-----NPC ��忡�� üũ-----//
	HT_NPC_NODE *n;
	n = m_sNPCHead->next;
	while( n != m_sNPCTail )
	{
		//	�浹�ϸ� ���� KeyID ��ȯ
		if( g_pEngineHandler->HT_bCheck2ObjCollide( n->sNPC.m_iNpcModelID, vecMainCharPos, ColidSize ) )
		{
			return n->sNPC.m_iNpcModelID;
		}
		n = n->next;
	}

	return 0;
}

//----------NPC ����â �ʱ�ȭ---------//
HTvoid HTNPCSystem::HT_vNPCSystem_HPWindowInit()
{
	//-----NPC ��忡�� üũ-----//
	HT_NPC_NODE *t;
	t = m_sNPCHead->next;

	while( t != m_sNPCTail )
	{
		if( t->sNPC.m_bNPC_Info_Sw == HT_TRUE )
		{
            //---------���� ���÷��� ����----------//
			m_bNPC_Info_Sw = HT_FALSE;
			t->sNPC.HT_vNPC_SetInfoCancel();
			g_pMainBar->HT_vSetObjectHPOut();
			g_pMainBar->HT_vSetObjectNameOut();
		}
		t = t->next;
	}
}

//----------NPC ���� Ŭ����---------//
HTvoid HTNPCSystem::HT_vNPCSystem_TotalNPCDelete()
{
	//----------LL ����Ÿ ���� �����---------//
	HT_LL_hrDeleteAll();
}

//----------������ �ʼ����� NPC�� �ִ°�?---------//
HTint HTNPCSystem::HT_vNPCSystemCheckMapCell( HTint iMapCellX, HTint iMapCellZ )
{
	//-----NPC ��忡�� üũ-----//
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
 
//----------��ȯ����----------//
//----------�ȵ� NPC�� ��ɺ��� ����----------//
HTvoid HTNPCSystem::HT_pNPCSystem_PickConnect( HTint nTempID )
{
	// ���� ���� ����/���� �� ���, �ٸ� �۾�(1:1trade ��)�� �ϰ� ���� ��� ó������ �ʴ´�
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return;
 
	DWORD dwIndex = HT_pNPCSystem_GetIndexFromModelID( nTempID );
	
	if( dwIndex == 0 || dwIndex == -1 )	// nTempID�� �ش��ϴ� NPC�� ã�� ������
		return;

	// NPC���� �Ÿ� üũ
	HTPoint pNPCCellPos = HT_pNPCSystem_GetCellPosFromIndex( dwIndex );
	HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
	pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;
	
	// NPC���� �Ÿ��� ���� ���� ��쿡�� NPC�� �̺�Ʈ�� ó����
	if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x <= NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
	{
		DWORD dwActiveNPC = g_cNPCControl->HT_iNPCControl_ActiveNPCIndex();
		if( dwIndex == dwActiveNPC ) // ���� ���� NPC�� Ȱ��ȭ�Ǿ� �ִ� ��� ó�� ����
			return;
		else if( dwActiveNPC != 0 )	// Ȱ��ȭ�Ǿ��ִ�  NPC�� �ִ� ���
		{
			// ��ȭ���� �ݱ� - NPC�� ���õ� ��� â �ݱ�
			g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();	
		}

		m_dwActiveNPCID = dwIndex;

		// NPC�� Ŭ��������, NPC�� ���� �����Ҹ��� Ʋ���ش�.
		HTdword dwSoundID = g_pEngineHandler->HT_dwGetNPCClickSoundID( dwIndex );
		g_pEngineHandler->HT_hrPlaySound( dwSoundID, 1 );

		HT_vNetWork_CSP_Req_Quest_Notify_Level();
		//------------------------------------------------
		// NPC â �ߵ��� �ӽ� ����.2003.11.28 ����
		//S_SCP_QUEST_NOTIFY_LEVEL info;
		//info.snNPCIndex = (HTshort)dwIndex;
		//info.byIndex = 81;
		//info.byLevel = 1;
		//g_sNPCSystem->HT_vNetWork_SCP_RESP_Quest_Notify_Level( &info );
		//------------------------------------------------
	}
	// NPC���� �Ÿ��� ���Ѻ��� �� ��쿡�� �޽����� ǥ���ϰ� ó������ ����
	else
	{
		CHTString strMessage;
		// NPC���� �Ÿ��� �ٴϴ�.
		if( g_pMessageMgr->HT_bGetMessage( eMsgCommonDistanceErrToNPC, &strMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
	}
}

//-----------���� Ȱ��ȭ �Ǿ��ִ� NPC�� ��Ȱ��ȭ�� ����----------//
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

	//-----NPC ��忡�� üũ-----//
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
	//-----NPC ��忡�� üũ-----//
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
	//-----NPC ��忡�� üũ-----//
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
//----------NPC �̸� �˾ƿ��� ------//
HTvoid HTNPCSystem::HT_vNPCSystem_GetName(DWORD dwIndex, CHTString& szName)
{
	//-----NPC ��忡�� üũ-----//
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

//----------NPC �̸� �˾ƿ��� ------//
HTvoid HTNPCSystem::HT_vNPCSystem_GetNameForModelID(DWORD dwModelID, CHTString& szName)
{
	//-----NPC ��忡�� üũ-----//
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
			//	ä�ø޽���
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

//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid HTNPCSystem::HT_LL_vInitList()
{
	m_sNPCHead = NULL;
	m_sNPCTail = NULL;

	m_sNPCHead = new HT_NPC_NODE;
	m_sNPCTail = new HT_NPC_NODE;

	m_sNPCHead->next = m_sNPCTail;
	m_sNPCTail->next = m_sNPCTail;

}

//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
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

//---------- Ư�� NPC ����� -------------//
HTbool HTNPCSystem::HT_bNPCSystem_DeleteNPC( DWORD dwNPCKeyID )
{
	return HT_LL_bDeleteNode(dwNPCKeyID);
}

//----------LL ����Ÿ �����---------//
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

//----------LL ����Ÿ ���� �����---------//
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

//----------����---------//
HTvoid HTNPCSystem::HT_vNPCSystemRender()
{
	HT_NPC_NODE *t;
	t = m_sNPCHead->next;

	//	��۸���϶��� ��ŵ
	if( g_bGamePlayMovieForGlobal )
		return;

	while( t != m_sNPCTail )
	{
		//----------����_�̸�----------//
		HT_vNPCSystem_RenderName( t );
		t = t->next;
	}

	//---------���� ���÷��� ����----------//
	if( m_bNPC_Info_Sw == HT_TRUE )
	{
		m_bNPC_Info_Sw = HT_FALSE;
		//g_pMainBar->HT_vSetObjectHPOut();
	}
}

//----------����_�̸�----------//
HTvoid HTNPCSystem::HT_vNPCSystem_RenderName( HT_NPC_NODE* t )
{
	BYTE bResult = g_cAoi->HT_AOI_Level( t->sNPC.HT_vNpcGetCell() );
	if( bResult <= AOI_LEVEL_6 )
	{
		HTvector3 vTextPos = t->sNPC.m_cNPCMove->HT_vecNPCMove_GetPos();
		vTextPos.y += 25;
		g_pEngineHandler->HT_hrRenderText( HT_FONT_GULIM_12, t->sNPC.m_strNPCName, vTextPos, HT_COLOR( 1.00f, 1.00f, 0.00f, 1.0f ) );

		//   -> ä�� �޽��� ǥ��
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
// ���� ����
//----------------------------------------------------//
//------------ģ�е� ��� - NPC ���뺰 ģ�е�+��� ����Ʈ-------------//
HTvoid HTNPCSystem::HT_vNPCSystem_CalNPCRelative(/*HTint nGroupbyFamily, */HTint& nTotalPoint, HTint& nSection)
{
	nTotalPoint = g_cStatus->HT_byGetLevel();
	
	// ���ٶ� ���� NPC�� �������� �������. �ٸ� ������ �߰��� ��� �����ؾ���.
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

//-----------���� Ȱ��ȭ�� NPC�� �������� ����Ʈ ���� ���� ����-----------//
HTvoid HTNPCSystem::HT_vNPCSystem_SetLastQuestStatus(BYTE byQuestIndex, BYTE byLevel, BYTE byLevelTime)
{
	m_byQuestIndex = byQuestIndex;	// ����Ʈ ��ȣ
	m_byLevel = byLevel;
	m_byLevel_Time = byLevelTime;
}

//-----------�ó����� ����Ʈ�� ���� ���� ���� ����-----------//
HTvoid HTNPCSystem::HT_vNPCSystem_SetNextQuestStatus()
{
	g_pEngineHandler->HT_vGetNextQuestLevel(m_byLevel, m_byLevel_Time);
	
	if( m_byLevel == 0 && m_byLevel_Time == 0 )
		m_byQuestIndex = 0;	// ����Ʈ ����
}

//-----------����Ʈ ���� ���¸� �˷��ش�-----------//
HTvoid HTNPCSystem::HT_vNetWork_CSP_Req_Quest_Notify_Level( )
{ 
	PS_CSP_QUEST_NOTIFY_LEVEL info = HT_NULL;
	info = new S_CSP_QUEST_NOTIFY_LEVEL;

	info->snNPCIndex = (HTshort)m_dwActiveNPCID;

	g_pNetWorkMgr->RequestQuestNotifyLevel( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_QuestNotifyLevel : %d", info->snNPCIndex);
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );	
}

HTvoid HTNPCSystem::HT_vNetWork_SCP_RESP_Quest_Notify_Level(PS_SCP_QUEST_NOTIFY_LEVEL info)
{
	short int snNpcIndex = 0;
	// �ӽ� �ڵ� (���ٶ� 2,3 ������ ��ȭ�� �ɾ��� ��� ����Ʈ ������ ���� 1���� index�� ����)

	switch( info->snNPCIndex)
	{
		// ���� ����
	case 1101 :	// ���ٶ�
	case 1205 :	// 18�� ���ٶ�
	case 1235 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1101;
		}
		break;

		// �� ����
	case 1102 :	// ���ٶ�
	case 1206 :	// 18�� ���ٶ�
	case 1236 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1102;
		}
		break;

		// �׼����� ���� 
	case 1103 :	// ���ٶ�
	case 1207 :	// 18�� ���ٶ�
	case 1237 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1103;
		}
		break;

		// �·�
	case 1104 :	// ���ٶ�
	case 1208 :	// 18�� ���ٶ�
	case 1238 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1104;
		}
		break;

		//	��ǰ��������
	case 1105 :	// ���ٶ�
	case 1209 :	// 18�� ���ٶ�
	case 1239 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1105;
		}
		break;

		// �������
	case 1108 :	// ���ٶ� 
	case 1212 : // 18�� ���ٶ�
	case 1242 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1108;
		}
		break;

		// ������(����Ʈ)
	case 1106 :	// ���ٶ�
	case 1210 : // 18�� ���ٶ�
	case 1240 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1106;
		}
		break;
		// �ּ���(���������뿩)
	case 1107 :		// ���ٶ�
	case 1211 :		// 18�� ���ٶ�
	case 1241 :		// 19�� ���ٶ�
		{
			snNpcIndex = 1107;
		}
		break;
		// ����1
	case 1001 :	// ���ٶ�
	case 1201 :	// 18�� ���ٶ�
	case 1231 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1001;
		}
		break;
		// ����2
	case 1002 :	// ���ٶ�
	case 1202 :	// 18�� ���ٶ�
	case 1232 :	// 19�� ���ٶ�
		{
			snNpcIndex = 1002;
		}
		break;
		//	���ھ���1
	case 1003 :	// ���ٶ�
	case 1203 : // 18�� ���ٶ�
	case 1233 : // 19�� ���ٶ�
		{
			snNpcIndex = 1003;
		}
		break;

		//	���ھ���1
	case 1005 :	// ���ٶ�
	case 1204 : // 18�� ���ٶ�
	case 1234 : // 19�� ���ٶ�
		{
			snNpcIndex = 1005;
		}
		break;

		// ����Ʈ�� ���� NPC
	case 1115 :	// ���� ����ü
	case 1213 :	// 18�� ���ٶ�
	case 1243 : // 19�� ���ٶ�
		{
			snNpcIndex = 1115;
		}
		break;

		// �������ٴ� ���� NPC
	case 1116 :
	case 1214 : // 18�� ���ٶ�
	case 1244 : // 19�� ���ٶ�
		{
			snNpcIndex = 1116;
		}
		break;

		// �ƹ�Ÿ���� ���� ����
	case 1117 :
	case 1215 : // 18�� ���ٶ�
	case 1245 : // 19�� ���ٶ�
		{
			snNpcIndex = 1117;
		}
		break;
	default:
		snNpcIndex = info->snNPCIndex;
		break;
	}

	//---�ڴʰ� �޼����� ���� ��츦 ����ؼ�----//
	// ���� ���� ����/���� �� ��� || �ٸ� �۾�(1:1trade ��)�� �ϰ� ���� ���
	if( g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND2) ||
		g_cUIManager->HT_isShowWindow(_DIALOG_TRADEWND) )
		return;
 
	// NPC���� �Ÿ� üũ
	HTPoint pNPCCellPos = HT_pNPCSystem_GetCellPosFromIndex( info->snNPCIndex );
	HTPoint pCheckGetPos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	pCheckGetPos.x = pCheckGetPos.x - pNPCCellPos.x;
	pCheckGetPos.y = pCheckGetPos.y - pNPCCellPos.y;
	
	// NPC���� �Ÿ��� ���� ���� ��쿡�� NPC�� �̺�Ʈ�� ó����
	if( pCheckGetPos.x*pCheckGetPos.x + pCheckGetPos.y*pCheckGetPos.x > NPC_DISTANCE_LIMIT * NPC_DISTANCE_LIMIT )
		return;

	//m_dwActiveNPCID = info->snNPCIndex;
	m_dwActiveNPCID = snNpcIndex;	// ������ ������ ���ٶ� 1 ���� NPC index�� �����Ͽ� ó����

	// ĳ������ ���� ������ ����Ʈ�� ���� ���� ����
	m_byQuestIndex = info->byIndex;	// ����Ʈ ��ȣ

	// ����Ʈ �������. 1:����, 2~:������, 255:�Ϸ�
	if( info->byIndex <= TUTORIAL_QUEST_END )	// Ʃ�丮�� ����Ʈ
		m_byLevel = info->byLevel;
	else if( info->byIndex <= SCENARIO_QUEST_6_END )	// �ó����� ����Ʈ
	{
		m_byLevel = m_byLevel_Time = 0;
		g_pEngineHandler->HT_vGetQuestLevel(info->byLevel, m_byLevel, m_byLevel_Time);
		
		// -------------------------------- �ӽ�(����2�� ����Ʈ ����Ұ� ó��) ------------------------------
		//if (info->byIndex == QUEST_JINA_1 && info->byLevel == QUEST_STATUS_START)
//			m_byLevel = m_byLevel_Time = 0;

		// 2�� ��������Ʈ�� �Ϸ����� ��� ��ų Ʈ���� ���� �׷��ش�
		if( info->byIndex == QUEST_SHAMBALA_11 && info->byLevel == QUEST_STATUS_SUCCESS )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_SKILL ) ) // ���� ��ųâ �ݱ�
				g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
			
			g_cSkillInventory->HT_hrSkillItemInit(); // ��ųƮ�� �ٽ� �׸���
		}
	}
	// ���� ����Ʈ - ��ũ��/��ų �ʱ�ȭ ����Ʈ 2004.3.17
	//else if( info->byIndex == QUEST_INDEPENDENCE_1 || info->byIndex == QUEST_INDEPENDENCE_2 )
	//{
	//	m_byLevel = m_byLevel_Time = 1;
	//}
	else
		m_byLevel = m_byLevel_Time = 0;

	// NPCâ ����
	g_cNPCControl->HT_vNPCControl_Active( info->snNPCIndex );
}
