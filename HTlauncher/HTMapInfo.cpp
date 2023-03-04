#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htmapinfo.h"

HTMapInfo::HTMapInfo(void)
{
	m_bBGM_Sw = HT_TRUE;
	m_bBGM_Village_Sw = HT_FALSE;
	m_bBGM_Field_Sw = HT_FALSE;

	m_dwETCEffect_WindTime = GetTickCount();
	m_dwETCEffect_WindDelay = rand()%10+10;
	m_dwETCEffect_CricketsTime = GetTickCount();
	m_dwETCEffect_CricketsDelay = rand()%10+10;;
}

HTMapInfo::~HTMapInfo(void)
{
}

//	맵 컨트롤 함수
HTvoid HTMapInfo::HT_vMapControl()
{
	//	ETC Effect Sound 틀어주기
	HT_vETCEffectSoundControl();
}

//	BGM 컨트롤 함수
HTvoid HTMapInfo::HT_vBGMControl( HTint iMapID )
{
	if (m_bBGM_Sw)
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		HTbool bType;
		if( iMapID == MAP_KATHANA3_BIRYUCASTLE )
		{
			if( pPt.x>300 && pPt.x<690 && pPt.y>300 && pPt.y<790 )
				bType = HT_TRUE;
			else
				bType = HT_FALSE;
		}
		else
		{
			bType = g_pEngineHandler->HT_bIsCellSafeZone( pPt.x, pPt.y, 0 );
		}

		g_pEngineHandler->HT_vSetStreamVolume(g_cSystem->m_fStreamVolume);

		if( bType == HT_TRUE )
		{
			m_bBGM_Village_Sw = HT_TRUE;
			m_bBGM_Field_Sw = HT_FALSE;

			switch(iMapID)
			{
				case MAP_MANDARA_1ST:
				case MAP_MANDARA_2ND:
					if (m_giBGM != SOUNDBGM_MANDATA1ST_VILLAGE)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA1ST_VILLAGE, -1 );
					m_giBGM = SOUNDBGM_MANDATA1ST_VILLAGE;
					break;
				case MAP_MANDARA_DUNGEON_1ST:
				case MAP_MANDARA_DUNGEON_2ND:
				case MAP_MANDARA_DUNGEON_3RD:
				case MAP_MANDARA_DUNGEON_4TH:
					if (m_giBGM != SOUNDBGM_MANDATA_DUNGEON)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA_DUNGEON, -1 );
					m_giBGM = SOUNDBGM_MANDATA_DUNGEON;
					break;
				case MAP_JINA_1ST:
				case MAP_JINA_3RD:
				case MAP_JINA_GUILD:
					if (m_giBGM != SOUNDBGM_JINA_VILLAGE)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JINA_VILLAGE, -1 );
					m_giBGM = SOUNDBGM_JINA_VILLAGE;
					break;
				case MAP_JINA_2ND:
					if (m_giBGM != SOUNDBGM_PAMIRFIELD)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_PAMIRFIELD, -1 );
					m_giBGM = SOUNDBGM_PAMIRFIELD;
					break;
				case MAP_KATHANA3_BIRYUCASTLE:
					//	공성전 중인지 아닌지 체크
					if( g_snResentZoneSiege == 0 )
					{
						if (m_giBGM != SOUNDBGM_JAPAN_VILLAGE)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JAPAN_VILLAGE, -1 );
						m_giBGM = SOUNDBGM_JAPAN_VILLAGE;
					}
					else
					{
						if (m_giBGM != SOUNDBGM_JAPAN_BATTLE)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JAPAN_BATTLE, -1 );
						m_giBGM = SOUNDBGM_JAPAN_BATTLE;
					}
					break;
				default:
					if (m_giBGM != SOUNDBGM_MANDATA1ST_VILLAGE)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA1ST_VILLAGE, -1 );
					m_giBGM = SOUNDBGM_MANDATA1ST_VILLAGE;
					break;
			}
		}
		else
		{
			m_bBGM_Field_Sw = HT_TRUE;
			m_bBGM_Village_Sw = HT_FALSE;

			switch(iMapID)
			{
				case MAP_MANDARA_1ST:
				case MAP_MANDARA_2ND:
					if (m_giBGM != SOUNDBGM_MANDATA1ST_FIELD)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA1ST_FIELD, -1 );
					m_giBGM = SOUNDBGM_MANDATA1ST_FIELD;
					break;
				case MAP_MANDARA_DUNGEON_1ST:
				case MAP_MANDARA_DUNGEON_2ND:
				case MAP_MANDARA_DUNGEON_3RD:
				case MAP_MANDARA_DUNGEON_4TH:
					if (m_giBGM != SOUNDBGM_MANDATA_DUNGEON)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA_DUNGEON, -1 );
					m_giBGM = SOUNDBGM_MANDATA_DUNGEON;
					break;
				case MAP_JINA_1ST:
				case MAP_JINA_3RD:
				case MAP_JINA_GUILD:
					if (m_giBGM != SOUNDBGM_JINA_VILLAGE)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JINA_VILLAGE, -1 );
					m_giBGM = SOUNDBGM_JINA_VILLAGE;
					break;
				case MAP_JINA_2ND:
					if (m_giBGM != SOUNDBGM_PAMIRFIELD)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_PAMIRFIELD, -1 );
					m_giBGM = SOUNDBGM_PAMIRFIELD;
					break;
				case MAP_JINA_4TH:
				case MAP_JINA_7TH_CAVE:	// 북두성군 묘
					if( g_iInationalType == INATIONALTYPE_KOREA )
					{
						if (m_giBGM != SOUNDBGM_NEWKRUMA)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_NEWKRUMA, -1 );
						m_giBGM = SOUNDBGM_NEWKRUMA;
					}
					else
					{
						if (m_giBGM != SOUNDBGM_LOWKRUMA)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_LOWKRUMA, -1 );
						m_giBGM = SOUNDBGM_LOWKRUMA;
					}
					break;
				case MAP_KATHANA3_BIRYUCASTLE:
					//	공성전 중인지 아닌지 체크
					if( g_snResentZoneSiege == 0 )
					{
						if (m_giBGM != SOUNDBGM_JAPAN_FIELD)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JAPAN_FIELD, -1 );
						m_giBGM = SOUNDBGM_JAPAN_FIELD;
					}
					else
					{
						if (m_giBGM != SOUNDBGM_JAPAN_BATTLE)
							g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_JAPAN_BATTLE, -1 );
						m_giBGM = SOUNDBGM_JAPAN_BATTLE;
					}
					break;
				case MAP_LOWKRUMA:
					if (m_giBGM != SOUNDBGM_LOWKRUMA)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_LOWKRUMA, -1 );
					m_giBGM = SOUNDBGM_LOWKRUMA;
					break;
				default:
					if (m_giBGM != SOUNDBGM_MANDATA1ST_FIELD)
						g_pEngineHandler->HT_hrPlaySound( SOUNDBGM_MANDATA1ST_FIELD, -1 );
					m_giBGM = SOUNDBGM_MANDATA1ST_FIELD;
					break;
			}	
		}
	}
}

//	ETC Effect Sound 틀어주기
HTvoid HTMapInfo::HT_vETCEffectSoundControl()
{
	if( m_bBGM_Sw == HT_FALSE )
		return;

	m_dwETCEffect_PassTime = GetTickCount();
}

//	CanMove
HTbool HTMapInfo::HT_hrGetCanMove( HTvector3 vecPos )
{
	return g_pEngineHandler->HT_bCanMove( HT_OBJSIZE_SMALL, vecPos, 0 );
}

//	BGM On / Off
HTvoid HTMapInfo::HT_hrSetBGMOnOff()
{
	m_giBGM = 0;
	if( m_bBGM_Sw == HT_TRUE )
	{
		m_bBGM_Sw = HT_FALSE;

		g_pEngineHandler->HT_hrStopStreamSound();
	}
	else
	{
		g_pEngineHandler->HT_hrStartStreamSound();

		m_bBGM_Village_Sw = HT_FALSE;
		m_bBGM_Field_Sw = HT_FALSE;
		m_bBGM_Sw = HT_TRUE;
	}
}

