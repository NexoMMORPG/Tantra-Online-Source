
#ifndef __HTMINIMAP_H__
#define __HTMINIMAP_H__


class CHTMiniMap
{
public:
	CHTMiniMap();
	~CHTMiniMap();

	HTvoid						HT_vMinMap_CeleanUp();
	HTRESULT					HT_hrMiniMap_Init();
	//	Create Window
	HTvoid						HT_vMiniMap_CreateWindow();
	//	MiniMap Small
	static void					HT_vEI_InputCheckForMiniMapMiniMapSmall(int iAction, int iTarget, int iTargetID);
	//	MiniMap Big
	static void					HT_vEI_InputCheckForMiniMapMiniBig(int iAction, int iTarget, int iTargetID);

	HTbool						HT_bMiniMap_IsOn();
	HTvoid						HT_vTotalMiniMap_Load();
	//	ESC Key ������ �̴ϸ� �ݱ�
	HTvoid						HT_vMiniMap_ESC_CloseWindow();
	//	���� ���ܰ��� �̴ϸ��� �ʱ�ȭ
	HTvoid						HT_vMiniMap_MoveMap_Init();

	//	�ý��� â���� �� ������Ʈ ����Ʈ ����
	HTvoid						HT_VMiniMap_SetOtherChar() { m_bOtherCharShow = !m_bOtherCharShow; };
	HTvoid						HT_VMiniMap_SetPartyMember() { m_bPartyMemberShow = !m_bPartyMemberShow; };
	HTvoid						HT_VMiniMap_SetMonster() { m_bMonserShow = !m_bMonserShow; };

	//	����Ʈ�� ȭ��ǥ �� �� ����Ʈ ����ֱ�
	HTvoid						HT_vMiniMap_SetStartMapPointForQuest( HTint nQuestNo, HTint nHistoryNo );
	HTvoid						HT_vMiniMap_SetEndMapPointForQuest();

	//	���콺 üũ
	HTRESULT					HT_hrMiniMap_MouseMove();

	HTvoid						HT_vMiniMap_Control( HTvector3 );
	HTvoid						HT_vMiniMap_Action();
	HTvoid						HT_vMiniMap_Render();

	HTvoid						HT_vMiniMap_Render_StartObject( BYTE );
	HTvoid						HT_vMiniMap_Render_OtherChar( BYTE, HTPoint );
	HTvoid						HT_vMiniMap_Render_NPC( BYTE, HTPoint );

private:
	//------------------------------------------------------------
	// HTvoid						HT_vSetTime(HTfloat)
	// D : ���� �ð� ����
	//------------------------------------------------------------
	HTvoid						HT_vSetTime(HTfloat);

private:
	//	�ǽð� �̴ϸ�
	HTint						m_iAction;
	HTPoint						m_pMainCharPt;

	//	��ü �̴ϸ�
	HTbool						m_bTotal_Sw;
	HTint						m_iCharPointTotalID;
	HTvector3					m_vecTotalMinMapPos;
	HTvector3					m_vecCharPointTotalPos;
	HTint						m_iTotalMiniMapID;
	HTint						m_iVillageMiniMapID;
	HTint						m_iCharPointMiniID;

	HTbool						m_bOtherCharShow;
	HTbool						m_bPartyMemberShow;
	HTbool						m_bMonserShow;
	HTint						m_iOtherCharPointID[30];
	HTint						m_iPartyMemberID[8];
	HTint						m_iMonserID[30];
	HTint						m_iNPCID[30];
	HTint						m_iOtherCharPoint_Count;
	HTint						m_iPartyMemberPoint_Count;
	HTint						m_iMonserID_Count;
	HTint						m_iNPCID_Count;

	HTint						m_iCurHour;
	HTint						m_iCurMinute;
	HTbool						m_bDay2Night;
	HTbool						m_bNight2Day;
};

#endif
