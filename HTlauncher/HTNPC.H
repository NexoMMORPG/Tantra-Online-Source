

#ifndef __HTNPC_H__
#define __HTNPC_H__

#include "htnpcmove.h"

class HTNPC
{
public:

	HTNPC();
	~HTNPC();

	HTRESULT					HT_vNpc_Input( HTint iNPCIndex, short snX, short snZ );
	HTRESULT					HT_vNpcDistroy();
    
	HTRESULT					HT_vNpcControl();
	
	
	HTPoint						HT_vNpcGetCell();

	//---------���� ���÷��� ����----------//
	HTvoid						HT_vNPC_SetInfoDisplay();
	//---------���� ���÷��� �������----------//
	HTvoid						HT_vNPC_SetInfoCancel();

	HTvoid						HT_vNPC_Click();
	HTvoid						HT_vNPC_OtherInput();

	HTRESULT					HT_vNpcRender();

private:


public:
	HTint						m_iNpcModelID;					//	NPC Model ID
	DWORD						m_dwNpcIndex;					//	NPC Index
//	HTbyte						m_byNpcCellSize;				//	NPC�� �����ϴ� �� ũ��
	HTvector3					m_vNPCPosition;					//	NPC�� ��ġ
	HTint						m_vNPCMapCellX;					//	NPC�� �� �� ��ġ
	HTint						m_vNPCMapCellZ;					//	NPC�� �� �� ��ġ
	CHTString					m_strNPCName;					//	NPC �Ӹ����� ���� ���(�̸�)
//	HTint						m_nGroupbyFamily;				// ����
	HTint						m_iNPCActive;					//	NPC Ȱ��ȭ ����

	BYTE						m_bBeforAoi;

	//	NPC ���� ǥ�� ����
	HTbool						m_bNPC_Info_Sw;

	//	NPC �̵� Ŭ����
	CHTNPCMove					*m_cNPCMove;

	//	NPC �ִϸ��̼� ��Ʈ���� ����
	HTint						m_nNPCAnm_Type;

	//	���� �Ǿ����� �����ִ� ����Ʈ
	HTint						m_nNPCTargettingEffectID;
	//	Chat Msg
	CHTString					m_strNPCChatMsg;
	HTdword						m_dwNPCChatMsgStartTime;


private:
};

#endif
