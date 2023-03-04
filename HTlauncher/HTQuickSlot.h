#pragma once

#define QUICKSLOT_MODE

//#define QUICKSLOT_STARTHIGHTTERM	1
#define QUICKSLOT_SIDECOUNT			5
#define QUICKSLOT_HIGHT				10

typedef struct HTQuickSlotInfo
{
	HTint				iIndex;
	HTint				iKeyID;
	HTint				iInvenIndex;
} HTQuickSlotInfo;

class HTQuickSlot
{
public:
	HTQuickSlot(void);
	~HTQuickSlot(void);

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vInit()
	// D : ������ �޸� �ʱ�ȭ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vInit();	

	//	Create Window
    HTvoid			HT_vQuick_CreateWindow();

	//	���_�Է��Լ� ó��
	static void		HT_vQuick_InputCheckHQuickSlot(int iAction, int iTarget, int iTargetID);

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vIconSave()
	// D : �����Կ� ��ϵǾ� �ִ� �������� �����Ͽ� ���� �α��� �� ����� �� �ֵ��� �Ѵ�.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vIconSave();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vIconLoad()
	// D : ����� ������ ������ �ε��Ѵ�.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vIconLoad();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vDeleteIconByIndex( HTdword dwIndex, HTint iKeyID )
	// D : �����Կ� ������ ����
	// I : dwIndex - �ε���, iKeyID - Ű ���̵�
	//-------------------------------------------------------------------------------------------
	HTbool			HT_vDeleteIconInResentSlotByIndex( HTdword dwIndex, HTint iKeyID );
	HTvoid			HT_vDeleteIconInAllSlotByIndex( HTdword dwIndex, HTint iKeyID );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
	// D : ������ ����
	// I : iSideNo - ���ٹ�ȣ, iCellNo - �� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vTotalDeleteIcon()
	// D : ������ ���λ���
	// I : 
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vTotalDeleteIcon( HTint iType );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vTotalCoolTimeinit()
	// D : ���� ���ư��� �ִ� ��Ÿ�ӵ� ���� �ʱ�ȭ
	// I : 
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vTotalCoolTimeInit();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vSetSide( HTint iType )
	// D : ���° �������� ������ ���ΰ� �����Ѵ�.
	// I : iType - ������ ������ ( 100:--, 101:++, ��Ÿ:������ ��ȣ )
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vSetSide( HTint iType );	
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_OnRButtonUp( HTPoint pPt, HTint iDlgNo )
	// D : ���� ���� ���� �����
	// I : pPt - ���콺 ��ǥ, iDlgNo - ���̾˷α� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_OnRButtonUp( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
	// D : ����� ����
	//-------------------------------------------------------------------------------------------
	HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vActionItem( HTint iSlotNo)
	// D : ���Կ� �ִ� ������ ���
	// I : iSlotNo - ���� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vActionItem( HTint iSlotNo);
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vAction( HTint iSlotNo )
	// D : ���Կ� ������ ����� ���
	// I : iSlotNo - ���� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vAction( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID )
	// D : ��ϵǾ� �ִ� Ű���̵� ����
	// I : dwOldKeyID - ���� Ű ���̵�, dwNewKeyID - ���ο� Ű ���̵�
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID );

	//===========================================================================================
	// Action�� ���� ���
	//===========================================================================================
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vResultActionItem( HTdword dwKeyID )
	// D : ������ ����� ���
	// I : dwKeyID - Ű���̵�
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vResultActionItem( HTdword dwKeyID );
	//===========================================================================================
	
    //	�� ���� â üũ_���콺 ���� ��ư
	HTvoid			HT_vQuickSlot_DlgCheck_LButton( HTPoint pPt, HTbool bVer = HT_TRUE );

	// ���Կ� ��ϵǾ��ִ� �������� KeyID ������ �����Ѵ�.
	HTvoid			HT_vQuickSlot_RenewalSlotItemKeyID();
	//-------------------------------------------------------
	//		��Ʈ��ũ �Լ�
	//-------------------------------------------------------
	//	�������� �����Կ� ��� ��û
	HTvoid			HT_vQuickSlot_ReqRegisterQuickSlot();
	//	�������� �����Կ� ��� ��û_���
	HTvoid			HT_vQuickSlot_ReqRegisterQuickSlot_Result();

	//------------------------------------------------------
	//		��ȯ����
	//------------------------------------------------------
	//	���Կ� ������ ����
	HTvoid			HT_bQuickSlot_SetSlot( HTint iType, HTint iIndexID, HTint iSlotNo );
	//	���Կ� ��ϵ� ��ų/�������� �ִ��� 
	//HTbool			HT_bQuickSlot_GetSlot( HTint );
	
	
	//	�ش� ���Կ� ��ġ�� �������� KeyID�� ��ų�� Index�� �Ѱ��ش�
	HTvoid			HT_vQuickSlot_GetKeyIDInSlot( HTint iSlotNo, HTint *piKeyID, HTbyte *pbyType );

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
	// D : Ű���̵� ���ǰ� �ִ��� üũ
	// I : dwIndex - �ε���, dwKeyID - Ű���̵�
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID );

	//-------------------------------------------------------------------------------------------
	// HTvoid		HT_hrContinueTimeCheck()
	// D : ���ӽð��� ������ �����۵� üũ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vContinueTimeCheck();

private:
	//-------------------------------------------------------------------------
	// HTbool			HT_bBeUsedSlot( HTint iSlotNo )
	// D : ������ ���ǰ� �ִ��� 
	//-------------------------------------------------------------------------
	HTbool			HT_bBeUsedSlot( HTint iSlotNo );

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vSetAllIcon()
	// D : ��� �������� ������ ���� �缳���Ѵ�.
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vSetAllIcon();

	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID )
	// D : �����Կ� ������ ���̱�
	// I : iDlgNo - ���̾˷α� ��ȣ, iType - Ÿ��(-2 : ���, 0 : ��ų, ELSE : UI ITEM), 
	//		iCellNo - ������ ��ȣ, iIndexID - �������� �ε���
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID );
	
	//-------------------------------------------------------------------------------------------
	// HTvoid			HT_vActionskill( HTint iSlotNo)
	// D : ���Կ� �ִ� ��ų���
	// I : iSlotNo - ���� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTvoid			HT_vActionskill( HTint iSlotNo);

	//-------------------------------------------------------------------------------------------
	// HTbool			HT_bBeUsedKey( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
	// D : ���� ��ϵǾ� �ִ� Ű���� üũ�ϰ�, ��ϵǾ� �ִ� Side�� ���� ��ȣ�� ����
	// I : dwKeyID - Ű���̵�
	// R : piSlotSide - ������ ��ȣ, piSlotNo - ���� ��ȣ
	//-------------------------------------------------------------------------------------------
	HTbool			HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo );

	//-------------------------------------------------------------------------------------------
	//	HTRESULT		HT_hrIsCoolTimeOver()
	// D : ���� �����Ϸ��� ����ų ��� �������� ��Ÿ��üũ
	// R : HT_OK - ��Ÿ�� �ʰ� ( ����� �� ���� )
	//		HT_FAIL - ��Ÿ�� ���ʰ� ( ����� �� ���� )
	//-------------------------------------------------------------------------------------------
	HTRESULT		HT_hrIsCoolTimeOver();

public:
	HTbool			m_bVerSlot;
	HTint			m_iSide;

private:
	HTint			m_iPrevSide;
	
	HTfloat			m_fQuickSlot_CoolTime[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];
	HTdword			m_dwQuickSlot_StartTimeCoolTime[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];
	HTQuickSlotInfo m_sQuickSlotInfo[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT]; // �����Կ� ��ϵ� ��ų/������ ����
	HTbool			m_bQuickSlot_ContinueSw[QUICKSLOT_SIDECOUNT][QUICKSLOT_HIGHT];		//	���Ӿ������� ��� ����

	HTint			m_iType;
	HTint			m_iSlotNo;
	HTint			m_iIndexID;
	//	�ٸ� ���Կ��� �Ѿ���� �ؽ��� ���̵�
	int				m_iSlot_TextureID;
	HTint			m_iQuickSlot_ActionSlotNo;
	HTbool			m_bQuickSlot_Loaded;

	//	������ ����� ���� �ټ�
	HTint			m_iUsedItemCount;

	//	For Continue Item
	HTint			m_iContinueItemKeyID[10];
	DWORD			m_dwContinueItemUseDelay;
};