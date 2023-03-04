#pragma once

#define _GOING_PORTAL_NUM	5
class HTPortal
{
public:
	HTPortal(void);
	~HTPortal(void);
    
	//	��Ż �ʱ�ȭ
	HTvoid			HT_vPortal_Init();
	//	Create Window
	HTvoid			HT_vPortal_CreateWindow();
	//	�Է��Լ� ó�� ��Ż
	static void		HT_vPortal_InputCheckPortal(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� Jiva Pustica
	static void		HT_vPortal_InputCheckJivaPustica(int iAction, int iTarget, int iTargetID);
	//	�Է��Լ� ó�� Upgrade Jiva Pustica
	static void		HT_vPortal_InputCheckUpgradeJivaPustica(int iAction, int iTarget, int iTargetID);

	//	��Ż Ŭ��
	HTRESULT		HT_vPortal_Click( HTint iPortalObj, HTvector3 vecPickPos );
	//	��Ż â �ݱ�
	HTvoid			HT_vPotal_AntiActive();
	//	ESC Key ������ â �ݱ�
	HTvoid			HT_vPotal_ESC_CloseWindow();
	//	ĳ���� ��ġüũ_ĳ���� �����̸� �ٿ��Ų��
	HTvoid			HT_vPortal_CharPos_Check();
	//	���� �̵��� ���� Ǫ��Ƽī Dlg
	HTvoid			HT_vPortal_ImprovementMovePustica();
	// �������� ����� ���� ��Ŷ ���� �Լ�
	HTvoid			HT_vPortal_Chaturanga_Enter();
	
	//	��ũ��ũ
	//	������ ��Ż ��û�ϱ�
	HTvoid			HT_vPortal_Network_ReqPortal();
	//	������ ��Ż ��û�� ���� ���� �ޱ� -> ���� ���� �޽��� �ϰ���
	HTvoid			HT_vPortal_Network_SCP_Resp_Portal( PS_SCP_RESP_MOVE_PORTAL info );
	//	������ Į���ھ� ��� ��û�ϱ�
	HTvoid			HT_vPortal_RegisterKalaCore( HTint iObjNo );
	//	_MSG_Item
	HTvoid			HT_vPortal_NetWork_CSP_MSG_Item( HTint iIndex );
	//	_MSG_MoveOtherZone
	HTvoid			HT_vPortal_NetWork_SCP_MSG_MoveOtherZone( MSG_MoveOtherZone* info );
	//	MSG_Warp
	HTvoid			HT_vPortal_NetWork_SCP_Msg_Warp( MSG_Warp* info );


	//	����üũ�ؿ���
	HTint			HT_iPortal_GetConnectNum( HTint iGroup, HTint iConnectZone );

	//	Data Setting for MSG_Item
	HTvoid			HT_vPortal_SetDataForMsgItem( HTbyte byPlace, HTbyte byIndex, HTint iItemID );

	//	Set Portress Pustica
	HTvoid			HT_vPortal_SetPortressPustica( HTbyte byPlace, HTbyte byIndex );
	//	Set Siege Pustica
	HTvoid			HT_vPortal_SetSiegePustica( HTbyte byPlace, HTbyte byIndex );
	
private:
	HTvoid			HT_vPortal_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid			HT_vPortal_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

public:
	HTbool			m_bPotal_Sw;

	//	1���������� �����Ҷ� �������� ������ �˻��ϱ� ������ġ
	HTbool			m_bPortal_FirstZoneSw;
	HTint			m_iPortal_FirstZoneIndex;

	//HTint			m_nPotal_Count;
	//HTint			m_nPotal_Connect;

	HTint			m_nPotal_SelectIndex;
	//	��Ż Ŭ�������� ĳ���� ��ġ ���
	HTPoint			m_pCharpos_Memory;

	//	Data Setting for MSG_Item
	HTbyte			m_byPlace_ForMsgItem;
	HTbyte			m_byIndex_ForMsgItem;

private:
	HTint			m_iGoingPortal[_GOING_PORTAL_NUM];
	HTdword			m_dwFee[_GOING_PORTAL_NUM];
	HTdword			m_dwLevel[_GOING_PORTAL_NUM];
	//	��Ż ID
	HTint			m_iPortal_StartPortalID;
	HTint			m_iPortal_TargetPortalID;
	//	��ȭ���� ����Ī ����
	HTbool			m_bPortal_ReDialogBoxActiveSw;

	//	�޼��� ��¿�
	HTdword			m_dwMessageVal;

	//	 �⼧�� �̵��� ���� Ǫ��Ƽī ��ȭ������ ������
	HTint			m_iPortal_ImprovmentPusticaPage;
	//	JivaPustica For Three Mandara vilige
	HTint			m_iPortal_JiPusticaForMantraIndex;
	//	for compare Portal item id
	HTint			m_iPotral_PortalMoveItemID;
	//	�ֽ� ������ ���� ����Ʈ�ȴ�����ȣ
	HTint			m_iTirmuritiCaveNo;
	//	���ٶ� ������ ������ ��������쿡 ����
	HTint			m_iSaveSelectUpgradeJPNo;
};
