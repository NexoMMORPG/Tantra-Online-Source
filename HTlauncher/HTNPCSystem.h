
#ifndef __HTNPCSYSTEM_H__
#define __HTNPCSYSTEM_H__

#include "HTNPC.h"

#define NPC_DISTANCE_LIMIT		6	// NPC ���� �Ÿ� ����
#define MAX_SELECT_COUNT		10	// ���ù� �ִ� ����

#define DIALOG_WIN_POSX			10
#define DIALOG_WIN_POSY			140 

//----------NPC LL ������ ���� ����ü----------//
typedef struct _HT_NPC_NODE
{
	HTNPC							sNPC;
	struct _HT_NPC_NODE				*next;

} HT_NPC_NODE;

//class HTNPCScriptMgr;
//----------NPC ��ü �ý��۰� LL�� ���� ����----------//
class HTNPCSystem
{
public:
	HTNPCSystem();
	~HTNPCSystem();
	HTvoid					HT_vNPCSystem_CleanUp();

	HTRESULT				HT_hNPCSystemInit();
	HTvoid					HT_vNPCSystemControl();

	//-------���� Zone�� �ִ� NPC ����--------//
	HTvoid					HT_vNPCSystem_CreateNPC();

	HTint					HT_vNPCSystemCheckMapCell( HTint, HTint );	//������ �ʼ����� NPC�� �ִ°�?

	//----------NPC�� �� ���� ��---------//
	HTint					HT_vNPCSystemComIDCheck( HTint iID );
	//----------NPC ����â �ʱ�ȭ---------//
	HTvoid					HT_vNPCSystem_HPWindowInit();
	//----------NPC ���� Ŭ����---------//
	HTvoid					HT_vNPCSystem_TotalNPCDelete();

	//---------- Ư�� NPC ����� -------------//
	HTbool					HT_bNPCSystem_DeleteNPC( DWORD dwNPCKeyID );
	// Ư�� NPC �����
	HTbool					HT_bNPCSystem_CreateNPC(HTint iNPCIndex);

	//----------��ȯ / ���ð� ��----------//
	HTvoid					HT_vNPCSystem_AntiActiveNPC();
	DWORD					HT_pNPCSystem_GetIndexFromModelID( HTint );
	HTPoint					HT_pNPCSystem_GetCellPosFromIndex( DWORD );
	HTvector3				HT_vNPCSystem_GetCoordFromModelID( DWORD dwID );

	HTvoid					HT_vNPCSystem_GetName(DWORD dwIndex, CHTString& szName);	// �̸�
	HTvoid					HT_vNPCSystem_GetNameForModelID(DWORD dwModelID, CHTString& szName);
	//HTint					HT_nNPCSystem_GetGroupbyFamily(DWORD dwKeyID);				// NPC ���� ȹ��
	DWORD					HT_dwNPCSystem_GetActiveNPCIndex() { return m_dwActiveNPCID; };// ���� Ȱ��ȭ �Ǿ��ִ� NPC KeyID
	//---------���� Ÿ��â�� ������ �������� �ִ� NPC �� ID ��ȯ-------------//
	DWORD					HT_vNPCSystem_GetTargetModelID();
	//	Returns Get	bCheck2ObjCollide
	HTint					HT_iNPCSystem_GetCheck2ObjCollide( HTint iKeyID, HTvector3 vecMainCharPos, HTfloat ColidSize );

	//------------ģ�е� ��� - NPC ���뺰 ģ�е�+��� ����Ʈ-------------//
	HTvoid					HT_vNPCSystem_CalNPCRelative(/*HTint nGroupbyFamily,*/ HTint& nTotalPoint, HTint& nSection);
	//----------�ȵ� NPC�� ��ɺ��� ����----------//
	HTvoid					HT_pNPCSystem_PickConnect( HTint );

	//	Set
	//	Set Chat Msg
	HTvoid					HT_vNPCSystem_SetChatMsg( HTint iID, CHTString strMessage );

	//----------����----------//
	HTvoid					HT_vNPCSystemRender();
	//----------����_�̸�----------//
	HTvoid					HT_vNPCSystem_RenderName( HT_NPC_NODE* t );
	//	Render MiniMap Point
	HTvoid					HT_vNPCSystem_MiniMapPoint();

	//----------------------------------------------------//
	//---------------------���� ����----------------------//
	//----------------------------------------------------//
	//----------NPC ģ�е� ����� ��û�Ѵ�----------//
	//HTvoid					HT_CSP_REQ_NPC_POINT_UP( DWORD );
	//----------NPC ģ�е� ����� ��û�Ѵ�_���----------//
	//HTvoid					HT_SCP_REQ_NPC_POINT_UP_Result( PS_SCP_RESP_NPC_POINT_UP info );

	//-----------����Ʈ ���� ���¸� �˷��ش�-----------//
	HTvoid		HT_vNetWork_CSP_Req_Quest_Notify_Level( );
	HTvoid		HT_vNetWork_SCP_RESP_Quest_Notify_Level(PS_SCP_QUEST_NOTIFY_LEVEL info);
	
	//-----------���� Ȱ��ȭ�� NPC�� �������� ����Ʈ ���� ���� ����-----------//
	HTvoid		HT_vNPCSystem_SetLastQuestStatus(BYTE byQuestIndex, BYTE byLevel, BYTE byLevelTime = 1);
	//-----------�ó����� ����Ʈ�� ���� ���� ���� ����-----------//
	HTvoid		HT_vNPCSystem_SetNextQuestStatus();

	//-----------���� ����ǰ� �ִ� ����Ʈ ��ȣ�� ���´�--------//
	BYTE		HT_byNPCSystem_GetLastQuestIndex() 	{	return m_byQuestIndex; 	}
	//-------���� Ȱ��ȭ�� NPC�� �������� ����Ʈ ���� ���¸� ���´�--------//
	BYTE		HT_byNPCSystem_GetLastQuestLevel() 	{	return m_byLevel; 	}
	BYTE		HT_byNPCSystem_GetLastQuestLevelTime() 	{	return m_byLevel_Time; 	}

private:
	HTvoid					HT_LL_vInitList();
	HTbool					HT_LL_bDeleteNode( int );
	HTvoid					HT_LL_hrDeleteAll();
	HTRESULT				HT_LL_hrInsertAfter( HTint iNPCIndex, short snX, short snZ );

public:
	HTint					m_iNPC_Count;
	//CHTString				m_RelativeStr[11];	// ģ�е��� ���� ����

	//----------OtherChar ���� ǥ������----------//
	HTbool					m_bNPC_Info_Sw;


	HT_NPC_NODE*			m_sNPCHead;
	HT_NPC_NODE*			m_sNPCTail;
	DWORD					m_dwActiveNPCID;	// ���� ������ NPC�� KeyID. ����Ʈ ��� �䱸�� ����� ó���ϱ� ����..

	//-----Quest--------//
	BYTE					m_byQuestIndex;
	BYTE					m_byLevel;
	BYTE					m_byLevel_Time;	// �ó���������Ʈ��. Level�� ����. ��)1�� or 2�� ����
};

#endif

