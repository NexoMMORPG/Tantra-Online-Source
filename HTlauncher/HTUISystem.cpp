#include "stdafx.h"
#include "HTUISystem.h"
#include "HTControlDef.h"
#include "HTextern.h"


#define _ANCHOR_SCREEN_WIDTH	1024
#define _ANCHOR_SCREEN_HEIGHT	768
#define	_FONT_RADIO_MARGIN		1
#define	_FONT_HEIGHT_MARGIN		2
#define	_LONGTEXT_LINE_SPACE	2
#define	_RADIO_SPACE_FROM_TEXT	5
#define	_FONT_EDIT_MARGIN		3

#define _NORMAL					0
#define _OVER					1
#define _DOWN					2
 
#define _2DSPRITE				2
#define _EMBLEM					3
#define _2DSPRITE_WITH_NOCOLOR	4

#define _DIALOG_LAYER			0x1000

typedef struct _HT_DIALOG_POS
{
	HTint	iPosX;
	HTint	iPosY;
} _HT_DIALOG_POS;

typedef struct _HT_SAVE_INFO
{
	CHTString	strCompany;
	HTint		iVersion;	
	HTint		iScreenWidth;
	HTint		iScreenHeight;
} _HT_SAVE_INFO;

#define _UI_VERSION		2004

#define _BLEND_COLOR	HT_COLOR(220.0f/255.0f,	30.0f/255.0f, 30.0f/255.0f,		23.0f/100.0f)
#define _OCCUPY_COLOR	HT_COLOR(30.0f/255.0f,	30.0f/255.0f, 220.0f/255.0f,	23.0f/100.0f)

CHTUISystem::CHTUISystem()
{
}

CHTUISystem::~CHTUISystem()
{	
}
