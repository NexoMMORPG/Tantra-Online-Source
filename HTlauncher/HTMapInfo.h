#pragma once

#ifndef __HTMAPINFO_H__
#define __HTMAPINFO_H__


class HTMapInfo
{
public:
	HTMapInfo(void);
	~HTMapInfo(void);

	//	�� ��Ʈ�� �Լ�
	HTvoid		HT_vMapControl();
	//	BGM ��Ʈ�� �Լ�
	HTvoid		HT_vBGMControl( HTint iMapID );
	//	ETC Effect Sound Ʋ���ֱ�
	HTvoid		HT_vETCEffectSoundControl();
	
	//	���� ����_����Ÿ �����ϰ� ����Ÿ ��������
	//	CanMove
	HTbool		HT_hrGetCanMove( HTvector3 vecPos );
	//	BGM On / Off
	HTvoid		HT_hrSetBGMOnOff();

public:
	HTbool		m_bBGM_Sw;
	HTbool		m_bBGM_Village_Sw;
	HTbool		m_bBGM_Field_Sw;

	//	ETC Effect Sound Ʋ���ֱ�
	DWORD		m_dwETCEffect_PassTime;
	DWORD		m_dwETCEffect_WindTime;
	DWORD		m_dwETCEffect_WindDelay;
	DWORD		m_dwETCEffect_CricketsTime;
	DWORD		m_dwETCEffect_CricketsDelay;

};


#endif