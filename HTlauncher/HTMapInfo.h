#pragma once

#ifndef __HTMAPINFO_H__
#define __HTMAPINFO_H__


class HTMapInfo
{
public:
	HTMapInfo(void);
	~HTMapInfo(void);

	//	맵 컨트롤 함수
	HTvoid		HT_vMapControl();
	//	BGM 컨트롤 함수
	HTvoid		HT_vBGMControl( HTint iMapID );
	//	ETC Effect Sound 틀어주기
	HTvoid		HT_vETCEffectSoundControl();
	
	//	셋팅 관련_데이타 셋팅하고 데이타 가져오기
	//	CanMove
	HTbool		HT_hrGetCanMove( HTvector3 vecPos );
	//	BGM On / Off
	HTvoid		HT_hrSetBGMOnOff();

public:
	HTbool		m_bBGM_Sw;
	HTbool		m_bBGM_Village_Sw;
	HTbool		m_bBGM_Field_Sw;

	//	ETC Effect Sound 틀어주기
	DWORD		m_dwETCEffect_PassTime;
	DWORD		m_dwETCEffect_WindTime;
	DWORD		m_dwETCEffect_WindDelay;
	DWORD		m_dwETCEffect_CricketsTime;
	DWORD		m_dwETCEffect_CricketsDelay;

};


#endif