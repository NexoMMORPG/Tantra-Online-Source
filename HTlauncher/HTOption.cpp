#include "stdafx.h"
#include "HTOption.h"

CHTUserSetting::CHTUserSetting()
{
	m_eSpecLevel = HT_OPT_SPEC_MED;

	m_eShadowType = HT_OPT_CIRCLESHADOW;
	m_eTerrainDetailLevel = HT_OPT_MEDIUM;
	m_eTextureDetailLevel = HT_OPT_MEDIUM;
	m_eModelDetailLevel = HT_OPT_MEDIUM;
	m_eCameraRangeType = HT_OPT_MEDIUM;
	m_eFXRangeType = HT_OPT_MEDIUM;
	m_eObjectRangeType = HT_OPT_MEDIUM;
	m_eCursorType = HT_OPT_CURSOR_IMAGE;

	m_e3DSoundProviderType = HT_OPT_MILES;
	m_eSpeakerChannelType = HT_OPT_2SPEAKER;

	m_iScreenWidth = 1024;
	m_iScreenHeight = 768;
	m_iScreenColorDepth = 16;
}

CHTUserSetting::~CHTUserSetting()
{
}

bool					
CHTUserSetting::HT_bLoad( TCHAR* szFile )
{
	FILE* fp;
	fp = fopen( szFile, "rb" );
	if ( !fp )
		return ( false );

	BYTE byVersion;
	fread( &byVersion, sizeof(BYTE), 1, fp );

	fread( &m_iScreenWidth, sizeof(DWORD), 1, fp );
	fread( &m_iScreenHeight, sizeof(DWORD), 1, fp );
	fread( &m_iScreenColorDepth, sizeof(DWORD), 1, fp );

	fread( &m_eSpecLevel, sizeof(BYTE), 1, fp );
	fread( &m_eShadowType, sizeof(BYTE), 1, fp );
	fread( &m_eTerrainDetailLevel, sizeof(BYTE), 1, fp );
	fread( &m_eTextureDetailLevel, sizeof(BYTE), 1, fp );
	fread( &m_eModelDetailLevel, sizeof(BYTE), 1, fp );
	fread( &m_eCameraRangeType, sizeof(BYTE), 1, fp );
	fread( &m_eFXRangeType, sizeof(BYTE), 1, fp );
	fread( &m_eObjectRangeType, sizeof(BYTE), 1, fp );
	fread( &m_e3DSoundProviderType, sizeof(BYTE), 1, fp );
	fread( &m_eSpeakerChannelType, sizeof(BYTE), 1, fp );

	fread( &m_eCursorType, sizeof(BYTE), 1, fp );

	fclose( fp );

	return ( true );
}

