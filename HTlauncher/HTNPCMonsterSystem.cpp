
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTNPCMonsterSystem.h"



HTNPCMonsterSystem::HTNPCMonsterSystem()
{
	//-----NPC �ý��� ����-----//
	g_sNPCSystem					= NULL;
	g_sNPCSystem					= new HTNPCSystem;
	
	//-----Monster �ý��� ����-----//
	g_sMonsterSystem				= NULL;
	g_sMonsterSystem				= new HTMonsterSystem;

	//-----����-----//
	//m_sSCP_INIT_MONSTER_NPC = HT_NULL;
	// = new S_SCP_INIT_MONSTER_NPC;

	//m_sSCP_MONSTER_MOVE_STEP = HT_NULL;
	//m_sSCP_MONSTER_MOVE_STEP = new S_SCP_MONSTER_MOVE_STEP;
}

HTNPCMonsterSystem::~HTNPCMonsterSystem()
{
	HT_DELETE( g_sNPCSystem );
	HT_DELETE( g_sMonsterSystem );
}

HTRESULT HTNPCMonsterSystem::HT_hNPCMonsterSystemInit()
{
	g_sMonsterSystem->HT_hMonsterSystemInit();
	g_sNPCSystem->HT_hNPCSystemInit();

	return HT_OK;
}

HTvoid HTNPCMonsterSystem::HT_vNPCMonsterSystemControl( HTfloat fElapsedTime )
{
	//-----9. NPC-----//
	g_sNPCSystem->HT_vNPCSystemControl();
	//-----10. ����-----//
	g_sMonsterSystem->HT_vMonsterSystemUpdate( fElapsedTime );
}

HTvoid HTNPCMonsterSystem::HT_vNPCSystemMonsterRender()
{
	g_sMonsterSystem->HT_vMonsterSystemRender();
}


//------------------------------//
//----------���� üũ-----------//
//------------------------------//
//----------NPC���� �ʱ�ȭ-----------//
HTvoid HTNPCMonsterSystem::HT_vNPCMonsterInit( PS_SCP_INIT_OTHER_MOB info )
{
}

//----------NPC���� �̵�-----------//
HTvoid HTNPCMonsterSystem::HT_vNPCMonsterNStep( PS_SCP_MONSTER_MOVE_NSTEP info )
{
	if( HT_FAILED( g_sMonsterSystem->HT_vMonsterSystemSet_logical_NStep( info ) ) )
	{	
		g_sMonsterSystem->HT_vRequestInitMonsterNPC( info->dwKeyID );
	}
}
