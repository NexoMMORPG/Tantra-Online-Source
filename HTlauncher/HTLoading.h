#ifndef __HTINTROLOADING_H__
#define __HTINTROLOADING_H__

#define INTRO_LOADING_MAX_STEP 10

class CHTUISystem;

class CHTLoading
{
public:
	CHTLoading();
	~CHTLoading();

	HTRESULT		HT_htLoadIntroUIResources();
	HTRESULT		HT_hrLoadIntroResources();
	HTRESULT		HT_hrLoadCharacterResource();
	HTRESULT		HT_hrLoadMainResources( HTdword mapID );

	HTRESULT		HT_hrUnloadAll();
	HTRESULT		HT_hrUnloadIntroResources();

	HTRESULT		HT_hrLoadMap( HTdword mapID );
	HTRESULT		HT_hrUnloadMap();


private:
	HTvoid			Msg(TCHAR *szFormat, ...);


public:
	HTbool			m_bMainUILoaded;
	HTbool			m_bIntroUILoaded;
	HTbool			m_bIntroMapLoaded;
	HTbool			m_bSoundLoaded;
	HTbool			m_bFXLoaded;
	HTbool			m_bCharacterLoaded;
	HTbool			m_bItemLoaded;

	HTbool			m_bMapLoaded;
	HTdword			m_dwLoadedMapID;
	HTdword			m_idIntroBGM;

private:
};

#endif