//----------------------------------------------------------------------------//
//																			  //
//	Project : Tantra game resource manager      							  //
//	Purpose : resource manager impls.                              			  //
//	File	: HTOption.h      												  //
//	Author	: Assrada														  //
//	History : 2003/02/24, Initiated by Assrada 								  //
//				- init                                         				  //
//																			  //
//  Copyright (c) 2000-2003 Hanbitsoft Corp.  All rights reserved.			  //
//----------------------------------------------------------------------------//

#ifndef _HTOPTION_H_
#define _HTOPTION_H_

enum HT_OPTION_SPEC_LEVEL 
{
	HT_OPT_SPEC_LOW = 1,
	HT_OPT_SPEC_MED = 2,
	HT_OPT_SPEC_HIG = 3,
	HT_OPT_SPEC_USER = 4,
};

enum HT_OPTION_SHADOW
{ 
	HT_OPT_NOSHADOW			= 0,
	HT_OPT_CIRCLESHADOW		= 1,
	HT_OPT_REALTIMESHADOW	= 2,
};

enum HT_OPTION_SOUNDPROVIDER
{
	HT_OPT_MILES			= 0,
	HT_OPT_EAX2				= 1,
	HT_OPT_DOLBYSROUND		= 2,
	HT_OPT_DIRECTSOUND		= 3,
};
#define _PROVIDER_NUM			HT_OPT_DIRECTSOUND+1

enum HT_OPTION_SPEAKERTYPE
{ 
	HT_OPT_2SPEAKER			= 0,
	HT_OPT_HEADPHONE		= 1,	
	HT_OPT_4SPEAKER			= 2,
	HT_OPT_51SPEAKER		= 3,
	HT_OPT_71SPEAKER		= 4,
};
#define _SPEAKER_TYPE_NUM			HT_OPT_71SPEAKER+1

enum HT_OPTION_DETAILLEVEL
{ 
	HT_OPT_LOW				= 0,
	HT_OPT_MEDIUM			= 1,
	HT_OPT_HIGH				= 2,
};
#define _DETAIL_NUM			HT_OPT_HIGH+1

enum HT_OPTION_CURSOR_TYPE
{ 
	HT_OPT_CURSOR_WINDOW	= 0,
	HT_OPT_CURSOR_IMAGE		= 1,
};

class CHTUserSetting
{
public:
								CHTUserSetting();
								~CHTUserSetting();

	bool						HT_bLoad( TCHAR* szFile );

	HT_OPTION_SPEC_LEVEL		HT_eGetSpecLevel()				{ return ( m_eSpecLevel );	}
	HT_OPTION_SHADOW			HT_eGetShadowType()				{ return ( m_eShadowType ); }
	HT_OPTION_SOUNDPROVIDER		HT_eGet3DSoundProvider()		{ return ( m_e3DSoundProviderType ); }
	HT_OPTION_SPEAKERTYPE		HT_eGetSpeakerType()			{ return ( m_eSpeakerChannelType ); }
	HT_OPTION_DETAILLEVEL		HT_eGetTextureDetail()			{ return ( m_eTextureDetailLevel ); }
	HT_OPTION_DETAILLEVEL		HT_eGetModelDetail()			{ return ( m_eModelDetailLevel ); }
	HT_OPTION_DETAILLEVEL		HT_eGetHeightMapDetail()		{ return ( m_eTerrainDetailLevel ); }
	int							HT_iGetScreenWidth()			{ return ( m_iScreenWidth ); }
	int							HT_iGetScreenHeight()			{ return ( m_iScreenHeight ); }
	int							HT_iGetScreenColorDepth()		{ return ( m_iScreenColorDepth ); }

	HT_OPTION_DETAILLEVEL		HT_eGetCameraRange()			{ return ( m_eCameraRangeType ); }
	HT_OPTION_DETAILLEVEL		HT_eGetFXRange()				{ return ( m_eFXRangeType ); }
	HT_OPTION_DETAILLEVEL		HT_eGetObjectRange()			{ return ( m_eObjectRangeType ); }

	HT_OPTION_CURSOR_TYPE		HT_eGetCursorType()				{ return ( m_eCursorType ); }

private:

	HT_OPTION_SPEC_LEVEL		m_eSpecLevel;
	HT_OPTION_SHADOW			m_eShadowType;
	HT_OPTION_DETAILLEVEL		m_eTerrainDetailLevel;
	HT_OPTION_DETAILLEVEL		m_eTextureDetailLevel;
	HT_OPTION_DETAILLEVEL		m_eModelDetailLevel;
	HT_OPTION_DETAILLEVEL		m_eCameraRangeType;
	HT_OPTION_DETAILLEVEL		m_eFXRangeType;
	HT_OPTION_DETAILLEVEL		m_eObjectRangeType;
	HT_OPTION_SOUNDPROVIDER		m_e3DSoundProviderType;
	HT_OPTION_SPEAKERTYPE		m_eSpeakerChannelType;
	HT_OPTION_CURSOR_TYPE		m_eCursorType;

	int							m_iScreenWidth;
	int							m_iScreenHeight;
	int							m_iScreenColorDepth;
};


#endif	// #ifndef _HTOPTION_H_