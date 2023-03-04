#include "stdafx.h"
#include "HTControlDef.h"
#include "HTEngineHandler.h"
#include "htsound.h"



HTSound::HTSound(void)
{
}

HTSound::~HTSound(void)
{
}

HTvoid HTSound::m_vSound_CleanUp()
{
	/*
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_CLICK] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_CLICKCHOOSE] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_CLICKERROR] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_CLICKNOTIFY] );

	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_NORWALK] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_NORRUN] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_ATTWALK] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_ATTRUN] );

	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDEFFECT_WIND] );

	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDBGM_MANDATA1ST_VILLAGE] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDBGM_MANDATA1ST_FIELD] );
	g_pEngineHandler->HT_vDestroyObject( m_Sound_ID[SOUNDBGM_MANDATA1ST_ENDING] );
	*/
}

HTvoid HTSound::m_vSound_Init()
{
	//	Mouse Click Effect
/*	m_Sound_ID[SOUNDEFFECT_CLICK] = g_pEngineHandler->HT_iCreateSound( 33501 );
	m_Sound_ID[SOUNDEFFECT_CLICKCHOOSE] = g_pEngineHandler->HT_iCreateSound( 33502 );
	m_Sound_ID[SOUNDEFFECT_CLICKERROR] = g_pEngineHandler->HT_iCreateSound( 33503 );
	m_Sound_ID[SOUNDEFFECT_CLICKNOTIFY] = g_pEngineHandler->HT_iCreateSound( 33503 );

	//	Character Move Effect
	m_Sound_ID[SOUNDEFFECT_NORWALK] = g_pEngineHandler->HT_iCreateSound( 31010 );
	m_Sound_ID[SOUNDEFFECT_NORRUN] = g_pEngineHandler->HT_iCreateSound( 31013 );
	m_Sound_ID[SOUNDEFFECT_ATTWALK] = g_pEngineHandler->HT_iCreateSound( 31016 );
	m_Sound_ID[SOUNDEFFECT_ATTRUN] = g_pEngineHandler->HT_iCreateSound( 31019 );
	m_Sound_ID[SOUNDEFFECT_SIT] = g_pEngineHandler->HT_iCreateSound( 31021 );

	//	Wind
	m_Sound_ID[SOUNDEFFECT_WIND] = g_pEngineHandler->HT_iCreateSound( 33504 );
	m_Sound_ID[SOUNDEFFECT_DRICKETS] = g_pEngineHandler->HT_iCreateSound( 33505 );

	//	BGM
	m_Sound_ID[SOUNDBGM_MANDATA1ST_VILLAGE] = g_pEngineHandler->HT_iCreateSound( 30002 );
	m_Sound_ID[SOUNDBGM_MANDATA1ST_FIELD] = g_pEngineHandler->HT_iCreateSound( 30003 );
	m_Sound_ID[SOUNDBGM_MANDATA1ST_ENDING] = g_pEngineHandler->HT_iCreateSound( 30004 );
	*/
}

// 0 : nIndex : ���� �ε���
// 1 : nLoopCount : �ݺ� Ƚ��
// 2 : byReset 0:�����ϰ� Ʋ��,1:�̾�Ʋ��
// 3 : byVolum : ���� ( 0 ~ 1 )
HTvoid HTSound::m_vSound_Play( HTint nIndex, HTint nLoopCount, BYTE byReset, HTfloat byVolum )
{
	//if( byReset == 0 )
	//	g_pEngineHandler->HT_hrStopSound( m_Sound_ID[nIndex] );

	//g_pEngineHandler->HT_hrPlaySound( m_Sound_ID[nIndex], nLoopCount );

	g_pEngineHandler->HT_hrPlaySound( nIndex, nLoopCount );
}

// ���� ����
HTvoid HTSound::m_vSound_Stop( HTint nIndex )
{
//	g_pEngineHandler->HT_hrStopSound( m_Sound_ID[nIndex] );
}

// 0 : nIndex : ���� �ε���
// 1 : byFadeInOut : 0:���̵� �ƿ�, 1:���̵� ��
HTvoid HTSound::m_vSound_FadeEffect( HTint nIndex, BYTE byFadeInOut )
{
}

