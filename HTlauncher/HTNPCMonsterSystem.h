
#ifndef __HTNPCMONSTERSYSTEM_H__
#define __HTNPCMONSTERSYSTEM_H__

#include "HTNPCSystem.h"
#include "HTMonsterSystem.h"


class HTNPCMonsterSystem
{
public:
	HTNPCMonsterSystem();
	~HTNPCMonsterSystem();

	HTRESULT					HT_hNPCMonsterSystemInit();
	HTvoid						HT_vNPCMonsterSystemControl( HTfloat );


	
	//----------��Ʈ��ũ����----------//
	HTvoid						HT_vNPCMonsterInit( PS_SCP_INIT_OTHER_MOB );		//	NPC���� �ʱ�ȭ
	HTvoid						HT_vNPCMonsterNStep( PS_SCP_MONSTER_MOVE_NSTEP );	//	NPC���� ����� �̵�

	HTvoid						HT_vNPCSystemMonsterRender();

public:
	//PS_SCP_INIT_MONSTER_NPC		m_sSCP_INIT_MONSTER_NPC;
	//PS_SCP_MONSTER_MOVE_STEP	m_sSCP_MONSTER_MOVE_STEP;


private:

};

#endif

