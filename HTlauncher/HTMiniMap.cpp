
#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTMiniMap.h"
#include "HTControlDef.h"
#include "HTUIIDDef.h"

#define MINIMAP_SIZE					168
#define MINIMAP_MAXSIZE					512
#define OBJECT_MAXCOUNT					30
#define COORD_CORRECTION				6

#define _MAPSTATUS_NONE				0
#define _MAPSTATUS_MINI				1
#define _MAPSTATUS_LARGE			2

CHTMiniMap::CHTMiniMap()
{
	m_iAction		= 0;
	m_iCurHour		= 0;
	m_iCurMinute	= 0;

	m_bOtherCharShow	= HT_TRUE;
	m_bPartyMemberShow	= HT_TRUE;
	m_bMonserShow		= HT_TRUE;
	m_bDay2Night		= HT_FALSE;
	m_bNight2Day		= HT_FALSE;

	
}

CHTMiniMap::~CHTMiniMap()
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPSMALL );
	g_cUIManager->HT_DeleteWindow( _DIALOG_MINIMAPBIG );
}

HTvoid CHTMiniMap::HT_vMinMap_CeleanUp()
{
	for( HTint i=0 ; i<30 ; i++ )
	{
		g_pEngineHandler->HT_vDestroyObject( m_iOtherCharPointID[i], 19 );
		g_pEngineHandler->HT_vDestroyObject( m_iMonserID[i], 20 );
		g_pEngineHandler->HT_vDestroyObject( m_iNPCID[i], 21 );
	}

	for( i=0 ; i<5 ; i++ )
		g_pEngineHandler->HT_vDestroyObject( m_iPartyMemberID[i], 22 );

	g_pEngineHandler->HT_vDestroyObject( m_iCharPointMiniID, 23 );
}

//----------미니맵 데이타 로딩및 초기화----------//
HTRESULT CHTMiniMap::HT_hrMiniMap_Init()
{
	//	Create Window
	this->HT_vMiniMap_CreateWindow();

	// 미니맵 위에 찍을 오브젝트들
	m_iOtherCharPoint_Count = 0;
	m_iPartyMemberPoint_Count = 0;
	m_iMonserID_Count = 0;
	m_iNPCID_Count = 0;
	for( HTint i=0 ; i<30 ; i++ )
	{
		m_iOtherCharPointID[i] = g_pEngineHandler->HT_iCreate2DWindowSprite( _WHITE, 0, 0, 4, 4, g_ColorTable[6] );
		m_iMonserID[i] = g_pEngineHandler->HT_iCreate2DWindowSprite( _WHITE, 0, 0, 4, 4, g_ColorTable[11] );
		m_iNPCID[i] = g_pEngineHandler->HT_iCreate2DWindowSprite( _WHITE, 0, 0, 4, 4, g_ColorTable[15] );
	}

	for( i=0 ; i<8 ; i++ )
        m_iPartyMemberID[i] = g_pEngineHandler->HT_iCreate2DWindowSprite( _WHITE, 0, 0, 4, 4, g_ColorTable[7] );

	m_iCharPointMiniID = g_pEngineHandler->HT_iCreate2DSprite( _MINIMAP_ARROW , HTvector3( 0, 0, 0 ) );

    return HT_OK;
}

//	Create Window
HTvoid CHTMiniMap::HT_vMiniMap_CreateWindow()
{
	//	[_DIALOG_MINIMAPSMALL]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MINIMAPSMALL, _T(""), 176, 174, g_cMiniMap->HT_vEI_InputCheckForMiniMapMiniMapSmall, 2, HT_COLOR( 0.0f, 0.0f, 0.0f, 0.1f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_MINIMAPSMALL, true );	// 배경영역 클릭시 맵 픽되게
	g_cUIManager->HT_WindowArrangement( _DIALOG_MINIMAPSMALL, 9 );
	//	Image Direct 동,서,남,북
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPSMALL, 0, 70, 153, 75 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPSMALL, 0, 69, 3, 75 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPSMALL, 0, 68, 75, 150 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPSMALL, 0, 71, 75, 4 );
	//	Edit
	g_cUIManager->HT_AddLabelControl( _DIALOG_MINIMAPSMALL, 1, _T("0/0"), 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 160, 60, 15 );
	//	Button 큰맵으로
    //g_cUIManager->HT_AddButtonControl( _DIALOG_MINIMAPSMALL, 1, 
	//	[_DIALOG_MINIMAPBIG]
	//	Window 
	g_cUIManager->HT_CreateWindow( _DIALOG_MINIMAPBIG, _T(""), 514, 520, g_cMiniMap->HT_vEI_InputCheckForMiniMapMiniBig, 2, HT_COLOR( 0.0f, 0.0f, 0.0f, 0.1f ) );
	g_cUIManager->HT_SetBackgroundDownEnable( _DIALOG_MINIMAPBIG, true );	// 배경영역 클릭시 맵 픽되게
	g_cUIManager->HT_WindowArrangement( _DIALOG_MINIMAPBIG, 9 );
	//	Edit
	g_cUIManager->HT_AddLabelControl( _DIALOG_MINIMAPBIG, 1, _T("0/0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 502, 60, 15 );
	//	Image Direct 동,서,남,북
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPBIG, 0, 70, 490, 250 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPBIG, 0, 69, 3, 250 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPBIG, 0, 68, 250, 493 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_MINIMAPBIG, 0, 71, 250, 4 );
}
//	MiniMap Small
void CHTMiniMap::HT_vEI_InputCheckForMiniMapMiniMapSmall(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cMiniMap->m_iAction = _MAPSTATUS_NONE;
			g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
		}
		else if( iTargetID == 1 )
		{
			g_cMiniMap->m_iAction = _MAPSTATUS_LARGE;
			g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
			g_cUIManager->HT_ShowWindow( _DIALOG_MINIMAPBIG );
		}
	}
}
//	MiniMap Big
void CHTMiniMap::HT_vEI_InputCheckForMiniMapMiniBig(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	X
		if( iTargetID == -1 )
		{
			g_cMiniMap->m_iAction = _MAPSTATUS_NONE;
			g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
		}
		else if( iTargetID == 1 )
		{
			g_cMiniMap->m_iAction = _MAPSTATUS_MINI;
			g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
			g_cUIManager->HT_ShowWindow( _DIALOG_MINIMAPSMALL );
		}
	}
}

//----------전체 지도 로딩----------//
HTvoid CHTMiniMap::HT_vTotalMiniMap_Load()
{
	HTint iPosX, iPosY;
	g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPSMALL, iPosX, iPosY );
	m_vecTotalMinMapPos.x = (HTfloat)iPosX + 3;
	m_vecTotalMinMapPos.y = (HTfloat)iPosY + 28;
	
	if ( g_pEngineHandler->HT_bMinimapLoaded() )
		m_iTotalMiniMapID = g_pEngineHandler->HT_iCreate2DSprite( HT_MINIMAP_BMP_ID, m_vecTotalMinMapPos );
	else
		m_iTotalMiniMapID = -1;
}

//----------화면에 보일것인지? 안보일것인지?----------//
HTvoid CHTMiniMap::HT_vMiniMap_Action()
{
	//	미니맵이 떠지 말아야 할때를 아쉬람 이름 입력창, 
	//	개인상점창이 있을때 미니맵창이 안떠라고 했는데 일단 전부 삭제해둔다.
	m_iAction++;
	if (m_iAction>2) m_iAction = 0;
	switch(m_iAction)
	{
		case _MAPSTATUS_MINI:
			{
				g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
				g_cUIManager->HT_ShowWindow( _DIALOG_MINIMAPSMALL );
			}
			break;
		case _MAPSTATUS_LARGE:
			{
				g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
				g_cUIManager->HT_ShowWindow( _DIALOG_MINIMAPBIG );
			}
			break;
		case _MAPSTATUS_NONE:
			{
				g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
				g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
			}
			break;
	}

	if (m_iAction==_MAPSTATUS_NONE) return;

	HTvector3 vecPos;
	vecPos.x = m_vecTotalMinMapPos.x + (MINIMAP_SIZE/2) - COORD_CORRECTION;
	vecPos.y = m_vecTotalMinMapPos.y + (MINIMAP_SIZE/2) - COORD_CORRECTION;
	g_pEngineHandler->HT_hrMoveObject( m_iCharPointMiniID, vecPos );

	HTfloat fTime = g_pEngineHandler->HT_fGetCurrentTimeInAllDay();
}

//	ESC Key 누르면 주소창 닫기
HTvoid CHTMiniMap::HT_vMiniMap_ESC_CloseWindow()
{
	g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
	g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
	m_iAction = _MAPSTATUS_NONE;
}

//	맵을 옯겨갈때 미니맵을 초기화
HTvoid CHTMiniMap::HT_vMiniMap_MoveMap_Init()
{
	m_iAction = _MAPSTATUS_NONE;
	g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPSMALL );
	g_cUIManager->HT_HideWindow( _DIALOG_MINIMAPBIG );
}

//	퀘스트용 화살표 및 맵 포인트 찍어주기
HTvoid CHTMiniMap::HT_vMiniMap_SetStartMapPointForQuest( HTint nQuestNo, HTint nHistoryNo )
{
}

HTvoid CHTMiniMap::HT_vMiniMap_SetEndMapPointForQuest()
{
}

//----------미니맵 컨트롤----------//
HTvoid CHTMiniMap::HT_vMiniMap_Control( HTvector3 vPos )
{
	if( m_iAction==_MAPSTATUS_NONE ) return;

		CHTString	strCellPosX, strCellPosY, strCellPos;
		
		m_pMainCharPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
        sprintf(strCellPos, "  %d / %d  ", (HTint)m_pMainCharPt.x, (HTint)m_pMainCharPt.y);
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_MINIMAPSMALL, 1, strCellPos.HT_szGetString() );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_MINIMAPBIG, 1, strCellPos.HT_szGetString() );

		this->HT_hrMiniMap_MouseMove();

		if( m_iAction == _MAPSTATUS_MINI )
		{
			//----------------------------------------------------------------------
			// 미니맵의 타이틀바에 위치 표시(20030513, Chung,Daeho)
			//----------------------------------------------------------------------
			HTfloat		fTime;
			fTime = g_pEngineHandler->HT_fGetCurrentTimeInAllDay();
			this->HT_vSetTime(fTime);
			
			m_pMainCharPt.x /= 2;
			m_pMainCharPt.y /= 2;
			HTPoint pPos;
			HTvector3 vecMainCharPos;
			pPos.x = m_pMainCharPt.x - COORD_CORRECTION;
			pPos.y = m_pMainCharPt.y - COORD_CORRECTION;

	   		if( pPos.x < (MINIMAP_SIZE/2) )
			{
				vecMainCharPos.x = m_vecTotalMinMapPos.x + pPos.x;
				pPos.x = (MINIMAP_SIZE/2);
			}
			else if( pPos.x > (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2)) )
			{
				vecMainCharPos.x = m_vecTotalMinMapPos.x + (MINIMAP_SIZE/2) + ( pPos.x - (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2)) );
				pPos.x = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2));
			}
			else
			{
				vecMainCharPos.x = m_vecTotalMinMapPos.x + (MINIMAP_SIZE/2);
			}

			if( pPos.y < (MINIMAP_SIZE/2) )
			{
				vecMainCharPos.y = m_vecTotalMinMapPos.y + pPos.y;
				pPos.y = (MINIMAP_SIZE/2);
			}
			else if( pPos.y > (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2)) )
			{
				vecMainCharPos.y = m_vecTotalMinMapPos.y + (MINIMAP_SIZE/2) + ( pPos.y - (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2)) );
				pPos.y = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2));
			}
			else
			{
				vecMainCharPos.y = m_vecTotalMinMapPos.y + (MINIMAP_SIZE/2);
			}

			HTint iLTX, iLTY, iRBX, iRBY;
			iLTX = pPos.x - (MINIMAP_SIZE/2)+2;
			iLTY = pPos.y - (MINIMAP_SIZE/2);
			//iRBX = pPos.x + (MINIMAP_SIZE/2)-3;
			iRBX = pPos.x + (MINIMAP_SIZE/2)+5;
			iRBY = pPos.y + (MINIMAP_SIZE/2);
			g_pEngineHandler->HT_hrClipRotateObject( m_iTotalMiniMapID, 0.0f, iLTX, iLTY, iRBX, iRBY, (HTint)m_vecTotalMinMapPos.x, (HTint)m_vecTotalMinMapPos.y );
			//vecMainCharPos.x -= 4;
			vecMainCharPos.y -= 8;
			g_pEngineHandler->HT_hrMoveObject( m_iCharPointMiniID, vecMainCharPos );
			g_pEngineHandler->HT_hrRotateObject( m_iCharPointMiniID, g_cMainCharacter->HT_fMainChar_GetDirectAngle() );
		}
		else if( m_iAction == _MAPSTATUS_LARGE )
		{
			g_pEngineHandler->HT_hrClipRotateObject( m_iTotalMiniMapID, 0.0f, 0, 0, 512, 512, 0, 0 );
			HTvector3 vecPos;
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );
			vecPos.x = (HTfloat)iPosX + 2;
			vecPos.y = (HTfloat)iPosY + 4;
			g_pEngineHandler->HT_hrMoveObject( m_iTotalMiniMapID, vecPos );
			//g_pEngineHandler->HT_hrRenderObject( m_iTotalMiniMapID );
			vecPos.x += m_pMainCharPt.x/2-8;
			vecPos.y += m_pMainCharPt.y/2-13;
			g_pEngineHandler->HT_hrMoveObject( m_iCharPointMiniID, vecPos );
			g_pEngineHandler->HT_hrRotateObject( m_iCharPointMiniID, g_cMainCharacter->HT_fMainChar_GetDirectAngle() );
		}
		else{}

}

HTRESULT CHTMiniMap::HT_hrMiniMap_MouseMove()
{
	if( !m_iAction )
        return HT_FAIL;

	HTint iPosX, iPosY;
	if( g_cUIManager->HT_isShowWindow( _DIALOG_MINIMAPSMALL ) )
		g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPSMALL, iPosX, iPosY );
	else
        g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );

    m_vecTotalMinMapPos.x = (HTfloat)iPosX + 2;
	m_vecTotalMinMapPos.y = (HTfloat)iPosY + 4;

	return HT_FAIL;
}

//----------화면 디스플레이----------//
HTvoid CHTMiniMap::HT_vMiniMap_Render()
{
	if( m_iAction!=_MAPSTATUS_NONE )
	{
		if (m_iTotalMiniMapID > 0)
			g_pEngineHandler->HT_hrRenderObject( m_iTotalMiniMapID );

		if (m_iCharPointMiniID > 0)
			g_pEngineHandler->HT_hrRenderObject( m_iCharPointMiniID );
	}

}

HTvoid CHTMiniMap::HT_vMiniMap_Render_StartObject( BYTE byType )
{
	if( byType == 0x01 )
	{
		m_iPartyMemberPoint_Count = 0;
        m_iOtherCharPoint_Count = 0;
		m_iMonserID_Count = 0;
	}
	else if( byType == 0x03 )
	{
        m_iNPCID_Count = 0;
	}
}

HTvoid CHTMiniMap::HT_vMiniMap_Render_OtherChar( BYTE byType, HTPoint pPos )
{
	if( g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Blind )
		return;

	if( m_iAction == _MAPSTATUS_MINI )
	{
		if( byType == 0x01 )
		{
			if( !m_bOtherCharShow )
				return;

			if( m_iOtherCharPoint_Count >= OBJECT_MAXCOUNT )
				return;

			HTPoint pTempPt;
			if( m_pMainCharPt.x<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.x = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.x>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.x = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.x = m_pMainCharPt.x;

			if( m_pMainCharPt.y<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.y = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.y>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.y = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.y = m_pMainCharPt.y;

			HTvector3 vecPos;
			vecPos.x = m_vecTotalMinMapPos.x + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.x) - (pPos.x/2)))+COORD_CORRECTION;
			vecPos.y = m_vecTotalMinMapPos.y + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.y) - (pPos.y/2)))+COORD_CORRECTION;

			if( vecPos.x<m_vecTotalMinMapPos.x || vecPos.x>m_vecTotalMinMapPos.x+MINIMAP_SIZE )	return;
			if( vecPos.y<m_vecTotalMinMapPos.y || vecPos.y>m_vecTotalMinMapPos.y+MINIMAP_SIZE )	return;

			g_pEngineHandler->HT_hrMoveObject( m_iOtherCharPointID[m_iOtherCharPoint_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iOtherCharPointID[m_iOtherCharPoint_Count] );
			m_iOtherCharPoint_Count++;
		}
		else if( byType == 0x02 )
		{
			if( !m_bPartyMemberShow )
				return;

			if( m_iPartyMemberPoint_Count >= 8 )
				return;

			HTPoint pTempPt;
			if( m_pMainCharPt.x<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.x = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.x>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.x = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.x = m_pMainCharPt.x;

			if( m_pMainCharPt.y<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.y = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.y>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.y = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.y = m_pMainCharPt.y;

			HTvector3 vecPos;
			vecPos.x = m_vecTotalMinMapPos.x + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.x) - (pPos.x/2)))+COORD_CORRECTION;
			vecPos.y = m_vecTotalMinMapPos.y + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.y) - (pPos.y/2)))+COORD_CORRECTION;

			if( vecPos.x<m_vecTotalMinMapPos.x || vecPos.x>m_vecTotalMinMapPos.x+MINIMAP_SIZE )	return;
			if( vecPos.y<m_vecTotalMinMapPos.y || vecPos.y>m_vecTotalMinMapPos.y+MINIMAP_SIZE )	return;

			g_pEngineHandler->HT_hrMoveObject( m_iPartyMemberID[m_iPartyMemberPoint_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iPartyMemberID[m_iPartyMemberPoint_Count] );
			m_iPartyMemberPoint_Count++;
		}
		else if( byType == 0x03 )
		{
			if( !m_bMonserShow )
				return;	

			if( m_iMonserID_Count >= OBJECT_MAXCOUNT )
				return;

			HTPoint pTempPt;
			if( m_pMainCharPt.x<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.x = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.x>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.x = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.x = m_pMainCharPt.x;

			if( m_pMainCharPt.y<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.y = (MINIMAP_SIZE/2)+COORD_CORRECTION;
			else if( m_pMainCharPt.y>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.y = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
			else																			pTempPt.y = m_pMainCharPt.y;

			HTvector3 vecPos;
			vecPos.x = m_vecTotalMinMapPos.x + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.x) - (pPos.x/2) ))+COORD_CORRECTION;
			vecPos.y = m_vecTotalMinMapPos.y + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.y) - (pPos.y/2) ))+COORD_CORRECTION;

			if( vecPos.x<m_vecTotalMinMapPos.x || vecPos.x>m_vecTotalMinMapPos.x+MINIMAP_SIZE )	return;
			if( vecPos.y<m_vecTotalMinMapPos.y || vecPos.y>m_vecTotalMinMapPos.y+MINIMAP_SIZE )	return;

			g_pEngineHandler->HT_hrMoveObject( m_iMonserID[m_iMonserID_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iMonserID[m_iMonserID_Count] );
			m_iMonserID_Count++;
		}
	}
	else if( m_iAction == _MAPSTATUS_LARGE )
	{
		if( byType == 0x01 )
		{
			if( !m_bOtherCharShow )
				return;

			if( m_iOtherCharPoint_Count >= OBJECT_MAXCOUNT )
				return;

			HTvector3 vecPos;
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );
            vecPos.x = (HTfloat)iPosX + (pPos.x/2);
			vecPos.y = (HTfloat)iPosY + 16 + (pPos.y/2);
			g_pEngineHandler->HT_hrMoveObject( m_iOtherCharPointID[m_iOtherCharPoint_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iOtherCharPointID[m_iOtherCharPoint_Count] );
			m_iOtherCharPoint_Count++;
		}
		else if( byType == 0x02 )
		{
			if( !m_bPartyMemberShow )
				return;

			if( m_iPartyMemberPoint_Count >= 8 )
				return;

			HTvector3 vecPos;
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );
			vecPos.x = (HTfloat)iPosX + (pPos.x/2);
			vecPos.y = (HTfloat)iPosY + 16 + (pPos.y/2);

			g_pEngineHandler->HT_hrMoveObject( m_iPartyMemberID[m_iPartyMemberPoint_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iPartyMemberID[m_iPartyMemberPoint_Count] );
			m_iPartyMemberPoint_Count++;
		}
		else if( byType == 0x03 )
		{
			if( !m_bMonserShow )
				return;	

			if( m_iMonserID_Count >= OBJECT_MAXCOUNT )
				return;

			HTvector3 vecPos;
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );
            vecPos.x = (HTfloat)iPosX + (pPos.x/2);
			vecPos.y = (HTfloat)iPosY + 16 + (pPos.y/2);

			g_pEngineHandler->HT_hrMoveObject( m_iMonserID[m_iMonserID_Count], vecPos );
			g_pEngineHandler->HT_hrRenderObject( m_iMonserID[m_iMonserID_Count] );
			m_iMonserID_Count++;
		}
	}
}

HTvoid CHTMiniMap::HT_vMiniMap_Render_NPC( BYTE byType, HTPoint pPos )
{
	if( m_iNPCID_Count >= OBJECT_MAXCOUNT )
		return;

	if( m_iAction == _MAPSTATUS_MINI )
	{
		HTPoint pTempPt;
		if( m_pMainCharPt.x<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.x = (MINIMAP_SIZE/2)+COORD_CORRECTION;
		else if( m_pMainCharPt.x>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.x = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
		else																			pTempPt.x = m_pMainCharPt.x;

		if( m_pMainCharPt.y<(MINIMAP_SIZE/2)+COORD_CORRECTION )							pTempPt.y = (MINIMAP_SIZE/2)+COORD_CORRECTION;
		else if( m_pMainCharPt.y>(MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION )	pTempPt.y = (MINIMAP_MAXSIZE-(MINIMAP_SIZE/2))-COORD_CORRECTION;
		else																			pTempPt.y = m_pMainCharPt.y;

		HTvector3 vecPos;
		vecPos.x = m_vecTotalMinMapPos.x + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.x) - (pPos.x/2) ))+COORD_CORRECTION;
		vecPos.y = m_vecTotalMinMapPos.y + (HTfloat)((MINIMAP_SIZE/2) - ( (pTempPt.y) - (pPos.y/2) ))+COORD_CORRECTION;

		if( vecPos.x<m_vecTotalMinMapPos.x || vecPos.x>m_vecTotalMinMapPos.x+MINIMAP_SIZE )	return;
		if( vecPos.y<m_vecTotalMinMapPos.y || vecPos.y>m_vecTotalMinMapPos.y+MINIMAP_SIZE )	return;

		g_pEngineHandler->HT_hrMoveObject( m_iNPCID[m_iNPCID_Count], vecPos );
		g_pEngineHandler->HT_hrRenderObject( m_iNPCID[m_iNPCID_Count] );
		m_iNPCID_Count++;
	}
	else if( m_iAction == _MAPSTATUS_LARGE )
	{
		HTvector3 vecPos;
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_MINIMAPBIG, iPosX, iPosY );
		vecPos.x = (HTfloat)iPosX + (pPos.x/2);
		vecPos.y = (HTfloat)iPosY + 16 + (pPos.y/2);

		g_pEngineHandler->HT_hrMoveObject( m_iNPCID[m_iNPCID_Count], vecPos );
		g_pEngineHandler->HT_hrRenderObject( m_iNPCID[m_iNPCID_Count] );
		m_iNPCID_Count++;
	}
}

//------------------------------------------------------------
// HTvoid						HT_vSetTime(HTfloat)
// D : 현재 시간 설정
//------------------------------------------------------------
HTvoid
CHTMiniMap::HT_vSetTime(HTfloat fTime)
{
	HTfloat fCurTime;
	if (fTime<0.75f)	fCurTime = (24.0f*fTime + 6.0f);
	else				fCurTime = (24.0f*fTime - 18.0f);	

	m_iCurHour		= (HTint)fCurTime;
	m_iCurMinute	= (HTint)((fCurTime - (HTfloat)m_iCurHour)*60.0f);
}

HTbool
CHTMiniMap::HT_bMiniMap_IsOn()
{
	//if (m_iAction==1) return HT_TRUE;
	//return HT_FALSE;

	if( m_iAction == _MAPSTATUS_NONE )
		return HT_FALSE;

	return HT_TRUE;
}