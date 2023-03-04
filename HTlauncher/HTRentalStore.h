//////////////////////////////////////////////////////////////////////////////////////////
// ���� : ��Ź ���� Ŭ����
// 
// �ۼ��� : ������
// 2005.10.13
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTRentalStore_H_
#define _HTRentalStore_H_

class CHTRentalStore
{
public:
	CHTRentalStore(void);
	~CHTRentalStore(void);
	
	// ��Ź������ ������ ������ �迭
	STRUCT_RENTALITEM	ItemList[MAX_USERRENTALITEM];			// �Ǹ����� ������ ����Ʈ ����迭
	DWORD				m_iStoreItemKeyID[MAX_USERRENTALITEM];	// ������ �Ǹ� ������ �������� KeyID ����迭
	WORD				m_wIndex[MAX_USERRENTALITEM];			// ���� ������ ����Ʈ �ε��� ���� ��ȣ

	HTint				m_iStoreIndex;							// ������ ���� �ε���
	HTint				m_iNPCIndex;							// ������ ���� NPC �ε���
	HTint				m_iBage;								// ��� ������ ��Ŷ ���� Ƚ�� ���

	// ��Ź��û�� ���� �ʿ�����
	DWORD				m_dwSelectKeyID;						// Ű���̵�

	DWORD				m_dwHour;								// �ʴ���
	DWORD				m_dwIndex;								// �κ��丮�� �ε���
	DWORD				m_dwMoney;								// �Ǹ��� �ݾ�
	int					m_iTex;									// ����
	float				m_fTotalTex;							// ��Ź�ǸŸ� ���� �Ѽ���
	int					m_iStore_MsgBoxType;					// �޽����ڽ� ������ ���� ����ó���� �÷��� ����

	int					m_nWindowType;							// ���� ������ �˾����� (���� ������ = 0, ���� ������ = 1)

	// Initialize Rental Store
	HTvoid			HT_vRentalStore_CleanUp();
	HTvoid			HT_vRentalStore_Init();

	// Window Processing Functions
	HTvoid			HT_vRentalStore_CreateWindow();		// ������ ����
	HTvoid			HT_vRentalStore_PopupWindow();		// ������ �˾�

	// MessageBox Processing Functions
	HTvoid			HT_vRentalStore_TexWin_Active();
	HTvoid			HT_vRentalStore_PriceWin_Active();
	HTvoid			HT_vRentalStore_TimeWin_Active();
	HTvoid			HT_vRentalStore_GetPriceWin_Active();

	// Sell & Buy Processing Functions
	HTvoid			HT_vRentalStore_SelectItemForSell( HTdword dwItemKeyID, int iInvenID ); // �κ��� �ִ� ��ǰ �Ǹ� �ϱ�

	// Window Procedure Functions
	static void		HT_vEI_InputCheckForRentalStore(int iAction, int iTarget, int iTargetID);
	static void		HT_vEI_InputCheckForBuyListWnd(int iAction, int iTarget, int iTargetID); //	Bye List Wnd
 
	// ��ũ��Ʈ�κ��� ���޵� ó�� �Լ�
	HTvoid HT_EventReqRentalAdminSellInfo();		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �Ǹ���Ȳ ����) - 3042 - (�Ǹ� ����Ʈâ �˾�)
	HTvoid HT_EventReqRentalAdminReciveItem();		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �����ޱ�) - 3043 - (�������� ������ ã���û ��Ŷ ȣ��)
	HTvoid HT_EventReqRentalAdminReciveList();		// ����� ��Ź�Ǹ� ������ (�ڽ��� ������ �������� ����Ʈ ����) - 3044 - (�������� ����Ʈâ �˾�)
	HTvoid HT_EventReqRentalBuyList();				// ����� ��Ź�Ǹ� �Ϲ��� (�Ǹ����� ������ ��Ϻ���) - 3045 (��Ź����â �˾�) - ���Ը��
	HTvoid HT_EventReqRentalSell();					// ����� ��Ź�Ǹ� �Ϲ��� (�ڽ��� ������ �Ǹ�) - 3046 (��Ź����â �˾�) - �ǸŸ��
	HTvoid HT_EventReqRentalUsingTex();				// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� ���� ����) - 3047 (��ũ��Ʈ�� ���)
	HTvoid HT_EventReqRentalItemRupia();			// ����� ��Ź�Ǹ� ������ (��Ź�Ǹ� ������ ���Ǿ� ����) - 3048 (��ũ��Ʈ�� ���)
	HTvoid HT_EventReqRentalSetTex();				// ����� ��Ź�Ǹ� �Ϲ��� (��Ź�Ǹ� �̿� ���� ����) - 3049 (��ũ��Ʈ�� ���)

	HTint	HT_iRentalStore_GetKeyIDInSellWin( HTint iPos );	// �Ǹ�â�� ��ϵ� ������ KeyID ���ϱ�
	HTint	HT_iRentalStore_GetKeyIDInBuyWin( HTint iPos );		// ����â�� ��ϵ� ������ KeyID ���ϱ�
	HTint	HT_iRentalStore_GetRupiah( HTdword dwKeyID );		// �ǸŸ���� ������ ���� ���ϱ�
	HTint	HT_iRentalStore_GetPackCount( HTdword dwKeyID );	// �ǸŸ���� ������ ���� ���ϱ�

	// Network Functions
	// Request Part
	HTvoid HT_vRequestMyRentalItemList();					// ���� ��Ź ������ ����Ʈ�� ��û
	HTvoid HT_RequestRentalItemList(DWORD dwStoreIndex);	// Ư�� ��Ź������ �����۸���Ʈ ��û
	HTvoid HT_RequestRentalItemAdd();						// �������� ��Ź��
	HTvoid HT_RequestRentalItemCancel();					// ��Ź�� �������� ���
	HTvoid HT_RequestRentalGetMoney(int iType);				// ����� ���� �� ã�� 0 = ��ȸ, 1 = ã��
	HTvoid HT_RequestRentalGetItem();						// ����� �� ��ǰ ã�� (�Ⱓ ���� �����۵�)
	HTvoid HT_RequestRentalTex(int iType);					// ��Ź������ ���� ���� 0 = ��ȸ, 1 = ã��
	HTvoid HT_RequestRentalStoreClose();					// ��Ź���� ���ְ� �ݱ�
	HTvoid HT_RequestRentalItemBuy();						// ��Ź�������� ������ ����
	HTvoid HT_RequestRentalStockItemList();					// ������ �������۸���Ʈ�� ��û�Ѵ�.
//	HTvoid HT_RequestRentalStockItem();						// ������ ���������� ��û�Ѵ�.

	// Recive Part
	HTvoid HT_vRentalStore_SCP_MyRentalItemList( Msg_MyRentalItemList* info );	// ���� ��Ź ������ ����Ʈ�� ��û ����
	HTvoid HT_vRentalStore_SCP_RentalItemList( Msg_RentalItemList* info );		// Ư�� ��Ź������ �����۸���Ʈ ��û ����
	HTvoid HT_vRentalStore_SCP_RentalItemAdd( Msg_RentalItemAdd* info );		// �������� ��Ź�� ����
	HTvoid HT_vRentalStore_SCP_RentalItemCancel( Msg_RentalItemCancel* info );	// ��Ź�� �������� ��� ����
	HTvoid HT_vRentalStore_SCP_RentalGetMoney( Msg_RentalGetMoney* info );		// ����� ���� �� ã�� ����
	HTvoid HT_vRentalStore_SCP_RentalGetItem( Msg_RentalGetItem* info );		// ����� �� ��ǰ ã�� (��� �����۵�) ����
	HTvoid HT_vRentalStore_SCP_RentalTex( Msg_SetRentalTex* info );				// ��Ź������ ���� ���� ����
	HTvoid HT_vRentalStore_SCP_RentalStoreClose( Msg_RentalStoreClose* info );	// ��Ź���� ���ְ� �ݱ� ����
	HTvoid HT_vRentalStore_SCP_RentalItemBuy( Msg_RentalItemBuy* info );		// ��Ź�������� ������ ���� ����
	HTvoid HT_vRentalStore_SCP_RentalStockItemList( Msg_RentalStockItemList* info );// ������ �������۸���Ʈ�� ��û�Ѵ�. ����
//	HTvoid HT_vRentalStore_SCP_RentalStockItem( Msg_RentalStockItem* info );// ������ ���������� ��û�Ѵ�. ����
};

#endif