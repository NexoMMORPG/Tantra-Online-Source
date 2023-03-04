
#include "stdafx.h"
#include "HTLoading.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

// LOG IF FAILED
#define LIF(x) if (HT_FAILED(hr=(x))) \
    {Msg(_T("HT_FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}


CHTLoading::CHTLoading()
{
	// 20021122Tenma_test
/*	HTvector3 TempPos;
	TempPos = HTvector3( 0.0f, 0.0f, 0.0f );
	m_UI_LOADING_BACK = g_pEngineHandler->HT_iCreate2DSprite( 26005, TempPos );
	TempPos = HTvector3( 312.0f, 500.0f, 0.0f );
	m_UI_LOADING_BAR = g_pEngineHandler->HT_iCreate2DSprite( 26025, TempPos );
*/

	// No resources are loaded
	m_bMainUILoaded		= HT_FALSE;
	m_bIntroUILoaded	= HT_FALSE;
	m_bSoundLoaded		= HT_FALSE;
	m_bFXLoaded			= HT_FALSE;
	m_bCharacterLoaded	= HT_FALSE;
	m_bItemLoaded		= HT_FALSE;

	m_bMapLoaded		= HT_FALSE;
	m_dwLoadedMapID		= -1;
}

CHTLoading::~CHTLoading()
{
	// Destory
//	g_pEngineHandler->HT_vDestroyObject(m_UI_LOADING_BACK);
}

HTRESULT CHTLoading::HT_htLoadIntroUIResources()
{
	HTRESULT hr;

	// Load Intro UI data
	if( m_bIntroUILoaded == HT_FALSE )
	{
		LIF(g_pEngineHandler->HT_hrLoadIntroUIData());
		m_bIntroUILoaded = HT_TRUE;
	}

	// 인트로 BGM
	if( !m_bSoundLoaded )
	{
		// Load sound data
		LIF(g_pEngineHandler->HT_hrLoadSoundData());
		m_bSoundLoaded = HT_TRUE;
		
		//	Play
		g_pEngineHandler->HT_hrStartStreamSound();	
		g_pEngineHandler->HT_hrPlayIntroBGM();
	}

	return HT_OK;
}

HTRESULT CHTLoading::HT_hrLoadIntroResources()
{
	HTRESULT hr;

	if( !m_bSoundLoaded )
	{
		// Load sound data
		LIF(g_pEngineHandler->HT_hrLoadSoundData());
		m_bSoundLoaded = HT_TRUE;
	}

	if( !m_bMapLoaded )
	{
		g_pEngineHandler->HT_hrLoadMap(MAP_INTRO);
		g_pEngineHandler->HT_hrLoadMapSystem(MAP_INTRO);
		g_pEngineHandler->HT_hrLoadMapObjs(MAP_INTRO);
		m_bMapLoaded = HT_TRUE;
	}

	//	이 부분은 인트로와 메인게임에서 다같이 써이는 부분이다.
	if( !m_bFXLoaded )
	{
		// Load FX data
		LIF( g_pEngineHandler->HT_hrLoadFXPCResource() );
		LIF( g_pEngineHandler->HT_hrCreateFXPCMgr() );
		m_bFXLoaded = HT_TRUE;
	}

	//	이 부분은 인트로와 메인게임에서 다같이 써이는 부분이다.
	if( !m_bItemLoaded )
	{
		// Load item data
		LIF(g_pEngineHandler->HT_hrLoadItemData());
		m_bItemLoaded = HT_TRUE;
	}
	
	return HT_OK;
}

HTRESULT CHTLoading::HT_hrLoadCharacterResource()
{
	//	이 부분은 인트로와 메인게임에서 다같이 써이는 부분이다.
	if( !m_bCharacterLoaded )
	{
		// Load character data
		//LIF(g_pEngineHandler->HT_hrLoadCharacterData());
		m_bCharacterLoaded = HT_TRUE;
		return HT_OK;
	}
	else
	{
        return HT_FAIL;
	}
}

HTRESULT CHTLoading::HT_hrUnloadIntroResources()
{
	HTRESULT hr;

	if( m_bIntroUILoaded )
	{
		// Unload Intro UI data
		LIF(g_pEngineHandler->HT_hrUnLoadIntroUIData());
		m_bIntroUILoaded = HT_FALSE;
	}

	if( m_bMapLoaded )
	{
		LIF(g_pEngineHandler->HT_hrUnloadMap());
		m_bMapLoaded = HT_FALSE;
	}

	//	인트로용 사운드는 왜 삭제하지 않는걸까?

	return HT_OK;
}

HTRESULT CHTLoading::HT_hrLoadMainResources( HTdword mapID )
{
	//	해당 번호의 맵을 로드
	if( mapID == 40018 ||
		mapID == 40019 )
        mapID = 40001;

	HTRESULT hr;

	if( !m_bMainUILoaded )
	{	
		LIF(g_pEngineHandler->HT_hrLoadGuildMark());
		// Load main UI data
		LIF(g_pEngineHandler->HT_hrLoadMainUIData());
		m_bMainUILoaded = HT_TRUE;
	}

	//	로딩이미지 랜더2
	g_pEngineHandler->HT_hrRenderLoadingBGI();
	g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.2f );

	// If the map data is present and has the same ID of which the map being loaded.
	if( m_bMapLoaded && m_dwLoadedMapID != mapID )
	{
		// Unload Intro UI data and set the loaded flag false
		LIF(g_pEngineHandler->HT_hrUnloadMap());
		m_bMapLoaded = HT_FALSE;
	}

	if( !m_bMapLoaded )
	{
		//	로딩이미지 랜더3
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.3f );

		// Load Map	
		LIF(g_pEngineHandler->HT_hrLoadMap(	mapID ));

		//	로딩이미지 랜더4
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.6f );

		// Load Map System
		LIF(g_pEngineHandler->HT_hrLoadMapSystem( mapID ));

		//	로딩이미지 랜더5
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.7f );

		// Load Map Objects
		LIF(g_pEngineHandler->HT_hrLoadMapObjs( mapID ));
		m_bMapLoaded = HT_TRUE;
		m_dwLoadedMapID = mapID;
	}

	return HT_OK;
}


// Unload all resources
HTRESULT CHTLoading::HT_hrUnloadAll()
{
	if( m_bIntroUILoaded )
	{
		// Unload Intro UI data
		//LIF(g_pEngineHandler->HT_hrUnLoadIntroUIData());
		m_bIntroUILoaded = HT_FALSE;
	}

	if( m_bMainUILoaded )
	{
		// Unload Intro UI data
		//LIF(g_pEngineHandler->HT_hrUnLoadMainUIData());
		m_bMainUILoaded = HT_FALSE;
	}

	if( m_bFXLoaded )
	{
		// Unload Intro UI data
		//g_pEngineHandler->HT_hrDestoryFXPCMgr();
		//g_pEngineHandler->HT_hrUnloadFXPCResource();
		m_bFXLoaded = HT_FALSE;
	}


	if( m_bCharacterLoaded )
	{
		// Unload Intro UI data
		g_pEngineHandler->HT_hrUnLoadCharacterData();
		m_bCharacterLoaded = HT_FALSE;
	}

	if( m_bItemLoaded )
	{
		// Unload Intro UI data
		g_pEngineHandler->HT_hrUnLoadItemData();
		m_bItemLoaded = HT_FALSE;
	}

	if( m_bMapLoaded )
	{
		// Unload Intro UI data
		//LIF(g_pEngineHandler->HT_hrUnloadMap());
		m_bMapLoaded = HT_FALSE;
		m_dwLoadedMapID = -1;
	}

	if( m_bSoundLoaded )
	{
		// Unload Sound data
		//LIF(g_pEngineHandler->HT_hrUnLoadSoundData());
		m_bSoundLoaded = HT_FALSE;
	}

    return HT_OK;
}

HTRESULT CHTLoading::HT_hrLoadMap( HTdword mapID )
{
	//	해당 번호의 맵을 로드
	if( mapID == 40018 ||
		mapID == 40019 )
        mapID = 40001;

	HTRESULT hr;

	g_cMapInfo->m_bBGM_Village_Sw = HT_FALSE;
	g_cMapInfo->m_bBGM_Field_Sw = HT_FALSE;

	// If the map data is present and has the same ID of which the map being loaded.
	if( m_bMapLoaded && m_dwLoadedMapID != mapID )
	{
		// Unload Intro UI data and set the loaded flag false
		LIF(g_pEngineHandler->HT_hrUnloadMap());
		m_bMapLoaded = HT_FALSE;

		//	로딩이미지 랜더
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.2f );
	}

	if( !m_bMapLoaded )
	{
		// Load Map	
		LIF(g_pEngineHandler->HT_hrLoadMap(	mapID ));

		//	로딩이미지 랜더
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.6f );

		// Load Map System
		LIF(g_pEngineHandler->HT_hrLoadMapSystem( mapID ));

		//	로딩이미지 랜더
		g_pEngineHandler->HT_hrRenderLoadingBGI();
		g_pEngineHandler->HT_hrRenderLoadingProgress( HT_TRUE, 0.7f );

		// Load Map Objects
		LIF(g_pEngineHandler->HT_hrLoadMapObjs( mapID ));

		m_bMapLoaded = HT_TRUE;
		m_dwLoadedMapID = mapID;
	}

	return HT_OK;
}


HTRESULT CHTLoading::HT_hrUnloadMap()
{
	HTRESULT hr;

	if( m_bMapLoaded )
	{
		LIF(g_pEngineHandler->HT_hrUnloadMap());
	}
	m_dwLoadedMapID = -1;
	m_bMapLoaded = HT_FALSE;
	
	return HT_OK;
}

HTvoid CHTLoading::Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // This sample uses a simple message box to convey warning and error
    // messages.   You may want to display a debug string or suppress messages
    // altogether, depending on your application.
	MessageBox(NULL, szBuffer, TEXT("Data Load, Unload"), MB_OK);
}
