

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

	//---------정보 디스플레이 셋팅----------//
	HTvoid						HT_vNPC_SetInfoDisplay();
	//---------정보 디스플레이 셋팅취소----------//
	HTvoid						HT_vNPC_SetInfoCancel();

	HTvoid						HT_vNPC_Click();
	HTvoid						HT_vNPC_OtherInput();

	HTRESULT					HT_vNpcRender();

private:


public:
	HTint						m_iNpcModelID;					//	NPC Model ID
	DWORD						m_dwNpcIndex;					//	NPC Index
//	HTbyte						m_byNpcCellSize;				//	NPC가 차지하는 셀 크기
	HTvector3					m_vNPCPosition;					//	NPC의 위치
	HTint						m_vNPCMapCellX;					//	NPC의 맵 셀 위치
	HTint						m_vNPCMapCellZ;					//	NPC의 맵 셀 위치
	CHTString					m_strNPCName;					//	NPC 머리위에 떠는 기능(이름)
//	HTint						m_nGroupbyFamily;				// 계통
	HTint						m_iNPCActive;					//	NPC 활성화 상태

	BYTE						m_bBeforAoi;

	//	NPC 정보 표시 여부
	HTbool						m_bNPC_Info_Sw;

	//	NPC 이동 클래스
	CHTNPCMove					*m_cNPCMove;

	//	NPC 애니매이션 컨트롤을 위해
	HTint						m_nNPCAnm_Type;

	//	지정 되었음을 보여주는 이펙트
	HTint						m_nNPCTargettingEffectID;
	//	Chat Msg
	CHTString					m_strNPCChatMsg;
	HTdword						m_dwNPCChatMsgStartTime;


private:
};

#endif

