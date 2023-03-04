#include "stdafx.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTPortal.h"

#define _PORTAL_START_NO		100
#define _PORTAL_NUM				32

#define _KURUMA_POTAL			161
#define _CHATURANGA_POTAL		173
#define _TRIMURITICAVE			181

#define _REFINE_OBJ_NO			1000
#define _OFFERING_OBJ_NO		1001

#define _OFFERING_OBJ_NO_S		1011	// �ù�
#define _OFFERING_OBJ_NO_V		1012	// �񽴴�
#define _OFFERING_OBJ_NO_B		1013	// ����帶

#define UPJIVAPUSTICAPORTALCOUNT	8

//	������Ÿ �޾ƿ���
//CHTWebLogIn*	m_pcPotalWebLogIn;

enum
{
	_BRAHMA,
	_VISHUNU,
	_SIVA,
};

//	���� �̵��� ���� Ǫ��Ƽī
HTint g_iImprovementPustica[UPJIVAPUSTICAPORTALCOUNT][10] = {	
	                                    103, 105, 131, 124, 126,   0,   0,   0,   0,   0,
										117, 120, 119, 128,   0,   0,   0,   0,   0,   0,
										133, 134, 135, 136,   0,   0,   0,   0,   0,   0,
										139, 138, 140,   0,   0,   0,   0,   0,   0,   0,
										141, 142, 143, 191,   0,   0,   0,   0,   0,   0,
										161,   0,   0,   0,   0,   0,   0,   0,   0,   0,
										202, 203, 204, 205,   0,   0,   0,   0,   0,   0,
										221, 220, 224, 225, 226,   0,   0,   0,   0,   0 };

//	���� �̵��� ���� Ǫ��Ƽī
HTint g_iLevelImprovementPustica[UPJIVAPUSTICAPORTALCOUNT][10] = {	  
	                                          0,   0,   0,  15,  15,   0,   0,   0,   0,   0,		//	���ٶ� ����
											 15,  15,  15,  40,   0,   0,   0,   0,   0,   0,		//	���߶� ����		
											 40,  40,  40,  40,   0,   0,   0,   0,   0,   0,		//	���� ����
											 40,  40,  40,   0,   0,   0,   0,   0,   0,   0,		//	�Ĺ̸� ���
											 40,  40,  40,  60,   0,   0,   0,   0,   0,   0,		//	������
											 30,  30,  30,   0,   0,   0,   0,   0,   0,   0,
											  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
											  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };		//	�ֽ�����


HTPortal::HTPortal(void)
{
	m_bPotal_Sw = HT_FALSE;
	//	��Ż ID
	m_iPortal_StartPortalID = 0;
	m_iPortal_TargetPortalID = 0;
	//	��ȭ���� ����Ī ����
	m_bPortal_ReDialogBoxActiveSw = HT_FALSE;
	//m_pcPotalWebLogIn = HT_NULL;
	//	Data Setting for MSG_Item
	m_byPlace_ForMsgItem = 0;
	m_byIndex_ForMsgItem = 0;
	//	for compare Portal item id
	m_iPotral_PortalMoveItemID = 0;
	//	 �⼧�� �̵��� ���� Ǫ��Ƽī ��ȭ������ ������
	m_iPortal_ImprovmentPusticaPage = 0;
	m_iSaveSelectUpgradeJPNo = 0;
}

HTPortal::~HTPortal(void)
{
	//HT_DELETE( m_pcPotalWebLogIn );
	g_cUIManager->HT_DeleteWindow( _DIALOG_PORTALWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_JIVAPUSTICAWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_UPGRADEJIVAPUSTICA );
}

//	1. ��Ż �ʱ�ȭ
HTvoid HTPortal::HT_vPortal_Init()
{
	//	Create Window
	this->HT_vPortal_CreateWindow();

	//m_pcPotalWebLogIn		= new CHTWebLogIn;
	//this->HT_vSetURL();
	m_bPotal_Sw				= HT_FALSE;
//	m_nPotal_Count			= _PORTAL_NUM;
//	m_nPotal_Connect		= _GOING_PORTAL_NUM;
	m_nPotal_SelectIndex	= 0;
	//	JivaPustica For Three Mandara vilige
	m_iPortal_JiPusticaForMantraIndex = 0;
}

//	Create Window
HTvoid HTPortal::HT_vPortal_CreateWindow()
{
	CHTString strTemp;
    //	[Portal]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_PORTALWND, _T(""), 400, 250, g_cPortal->HT_vPortal_InputCheckPortal, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_PORTALWND, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture ��Ż
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalTitle, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label ���� ��Ż �̸�
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalPortalName, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 60, 390, 17 );
	//	Loop
	for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
	{
		//	Button ��Ż ����Ʈ1
		g_cUIManager->HT_AddButtonControl( _DIALOG_PORTALWND, 10+i, 0, 5, 85+(25*i), 9, 0, 1500, 390, 17 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85+(25*i), 390, 17 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PORTALWND, 10+i );
	}

	//	[_DIALOG_JIVAPUSTICAWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_JIVAPUSTICAWND, _T(""), 400, 250, g_cPortal->HT_vPortal_InputCheckJivaPustica, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_JIVAPUSTICAWND, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_JIVAPUSTICAWND, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture ����Ǫ��Ƽī
	g_cUIManager->HT_AddTextureControl( _DIALOG_JIVAPUSTICAWND, 2, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalJivaPustica, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label ���� ��Ż �̸�
	g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 60, 390, 17 );
	//	Button ���ٶ� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 10, 0, 5, 85, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalMandaraVillage, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 10, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 10 );
	//	Button ���߶� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 11, 0, 5, 110, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalShambalraZone, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 11, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 110, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 11 );
	//	Button ���� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 12, 0, 5, 135, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalJinaZone, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 12, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 135, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 12 );
	//	Button ������
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 13, 0, 5, 160, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalExile, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 13, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 160, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 13 );
	//	Button �ֽ�����
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 14, 0, 5, 185, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalTrimuriti, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 14, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 185, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 14 );

	//	[_DIALOG_UPGRADEJIVAPUSTICA]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_UPGRADEJIVAPUSTICA, _T(""), 400, 280, g_cPortal->HT_vPortal_InputCheckUpgradeJivaPustica, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_UPGRADEJIVAPUSTICA, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_UPGRADEJIVAPUSTICA, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture ��������Ǫ��Ƽī
	g_cUIManager->HT_AddTextureControl( _DIALOG_UPGRADEJIVAPUSTICA, 2, 9, 39, 30, 1400, 150, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalHighJivaPustica, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 150, 17 );
	//	Only Label ���� ��Ż �̸�
	g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectOtherZone, &strTemp );
    g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 57, 390, 17 );
	//	Button ������
	g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 4, 148, 100, 55, 150, 149 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 4, _T("������"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 66, 55, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 4 );
	//	Button �ڷ�
	g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 5, 145, 282, 55, 146, 147 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 5, _T("�ڷ�"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 263, 55, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 5 );
	//	Loop
	for( HTint i=0 ; i<UPJIVAPUSTICAPORTALCOUNT ; i++ )
	{
		//	Button ��Ż ����Ʈ1
		g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, 0, 5, 85+(25*i), 9, 0, 1500, 390, 17 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85+(25*i), 390, 17 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 10+i );
	}
}

//	�Է��Լ� ó��
void HTPortal::HT_vPortal_InputCheckPortal(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
		}
		//	��Ż ��ư�� Ŭ��������
		else if( iTargetID>=10 && iTargetID<=_GOING_PORTAL_NUM+10 )
		{
			//if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
			//{
			//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, _T("�������϶��� ����Ҽ� �����ϴ�.") );
			//	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
			//	return;
			//}

			int iSelectBtnNo = iTargetID-10;
			//	1���������� �����Ҷ� �������� ������ �˻��ϱ� ������ġ
			if( g_cPortal->m_bPortal_FirstZoneSw )
			{
				g_cPortal->m_iPortal_FirstZoneIndex = iSelectBtnNo;
				//	��Ż â �ݱ�
				g_cPortal->HT_vPotal_AntiActive();
				//	JivaPustica For Three Mandara vilige
				if( g_cPortal->m_iPortal_JiPusticaForMantraIndex == 1 )
				{
					if( iSelectBtnNo == 0 )			g_cPortal->m_iPortal_JiPusticaForMantraIndex = 2;
					else if( iSelectBtnNo == 1 )	g_cPortal->m_iPortal_JiPusticaForMantraIndex = 3;
					else if( iSelectBtnNo == 2 )	g_cPortal->m_iPortal_JiPusticaForMantraIndex = 4;
					//	_MSG_Item -> 0 �� ���� m_iPortal_JiPusticaForMantraIndex �� ���� ��ư �ε����� �ִ´�.
					g_cPortal->HT_vPortal_NetWork_CSP_MSG_Item( 0 );
				}
				//	��Ż �̵� ��û
				else
				{
					g_cPortal->HT_vPortal_Network_ReqPortal();
				}
			}
			else
			{
				// ��Ż ��ȣ ���
				g_cPortal->m_iPortal_TargetPortalID = g_cPortal->m_iGoingPortal[iSelectBtnNo];
				if( g_cPortal->m_iPortal_TargetPortalID )
				{
					//	��Ż â �ݱ�
					g_cPortal->HT_vPotal_AntiActive();

					CHTString strTemp;
                    // �ֽ��� ������ �������� ���
					if( g_cPortal->m_iPortal_TargetPortalID==_KURUMA_POTAL )
					{
						switch(g_oMainCharacterInfo.byTrimuriti)
						{
							//����� ĳ���͸� ���鶧 �ֽ��� 1/2/3���� ���� �ִ�. 1/2/4/�� ����Ǿ�� �Ѵ�.
							case TRIMURITI_BRAHMA:
								g_cPortal->m_iPortal_TargetPortalID += _BRAHMA;				break;
							case TRIMURITI_VISHNU:
								g_cPortal->m_iPortal_TargetPortalID += _VISHUNU;			break;
							case TRIMURITI_SIVA:
								g_cPortal->m_iPortal_TargetPortalID += _SIVA;				break;
							default :
								g_cPortal->m_iPortal_TargetPortalID = 0;					break;
						}
					}

					//	ĳ���Ͱ� �ɾ��ִٸ� ��ŵ
					if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )
					{
						// ���� ���¿����� ��Ż�� Ż �� �����ϴ�.
						g_cPortal->HT_vPortal_SetMessage( eMsgPortalSitdownErr, &strTemp );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
						return;
					}

					if( g_cPortal->m_iTirmuritiCaveNo > -1 )
						iSelectBtnNo = g_cPortal->m_iTirmuritiCaveNo;

					if( g_cPortal->m_dwLevel[iSelectBtnNo]!=0 || g_cPortal->m_dwFee[iSelectBtnNo]!=0 )
					{
						if( g_cStatus->HT_byGetLevel() < g_cPortal->m_dwLevel[iSelectBtnNo] )
						{
							// �� ��Ż�� �̿��Ͻ÷��� %d���� �̻��̾�� �մϴ�.
							g_cPortal->m_dwMessageVal = g_cPortal->m_dwLevel[iSelectBtnNo];
							g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailLevelErr, &strTemp );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
							return;
						}
						if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < (HTint)g_cPortal->m_dwFee[iSelectBtnNo] )
						{
							// �� ��Ż�� �̿��Ͻ÷��� %d���Ǿư� �ʿ��մϴ�.
							g_cPortal->m_dwMessageVal = g_cPortal->m_dwFee[iSelectBtnNo];
							g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailMoneyErr, &strTemp );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
							return;
						}
					}

					// �ֽ��� ������ �������� ��� �ֽ��� ������
					if( g_cPortal->m_iPortal_TargetPortalID==0 )
					{
						// �ֽ��� ������ ���Ƿ��� �ڽ��� �ֽ��� ������ �־�� �մϴ�. �ֽ� ������ ���ϸ� ������ �ٳ�Ÿ�� ã�ư�����!
						g_cPortal->HT_vPortal_SetMessage( eMsgPortalTrimuritiErr, &strTemp );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
						return;
					}

					if( g_cStatus->HT_byGetLevel() >= g_cPortal->m_dwLevel[iSelectBtnNo] &&
						g_cEquipInventory->HT_iEquipInventory_GetPCMoney() >= (HTint)g_cPortal->m_dwFee[iSelectBtnNo] &&
						g_cPortal->m_iPortal_TargetPortalID!=0 )
					{
						//	1���������� �����Ҷ� �������� ������ �˻��ϱ� ������ġ
						if( g_wResentZoneServerID != ZONE_MANDARA1ST && 
							g_wResentZoneServerID != ZONE_MANDARA2ND && 
							g_wResentZoneServerID != ZONE_MANDARA3TH )
						{
							if( g_cPortal->m_iPortal_TargetPortalID == 101 || 
								g_cPortal->m_iPortal_TargetPortalID == 103 || 
								g_cPortal->m_iPortal_TargetPortalID == 131 )
							{
								if (!g_poWebLogIn->HT_bGetServerStatusCheck())
								{
									g_cPortal->HT_vPortal_Network_ReqPortal();
									return;
								}
								HTint iConnectNum_1 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA1ST-1 );
								HTint iConnectNum_2 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1 );
								HTint iConnectNum_3 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1 );
								//	�Ϻ��� �븸 �̿��� ������ �� �Ѿ��.
								if( g_iInationalType != INATIONALTYPE_JAPEN &&
									g_iInationalType != INATIONALTYPE_TAIWAN )
								{
									iConnectNum_2 = -1;
									iConnectNum_3 = -1;
								}

								if( iConnectNum_2 == -1 && iConnectNum_3 == -1 )
								{
									g_cPortal->HT_vPortal_Network_ReqPortal();
								}
								else
								{
									//	��Ż �̸� �ʱ�ȭ
									g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strTemp.HT_szGetString() );
									for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
									{
										g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
									}
									// ù��° ���ٶ�
									// ���ٶ� 1������_0
									g_cPortal->HT_vPortal_SetMessage( eMsgPortalExtraMandara1, &strTemp );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10, strTemp );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10, true);
									// �ι�° ���ٶ�
									if( iConnectNum_2 != -1 )
									{
										// ���ٶ� 1������_1
										g_cPortal->HT_vPortal_SetMessage( eMsgPortalExtraMandara2, &strTemp );
										g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 11, strTemp );
										g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 11, true);
									}
									// ����° ���ٶ�
									if( iConnectNum_3 != -1 )
									{
										// ���ٶ� 1������_2
										g_cPortal->HT_vPortal_SetMessage( eMsgPortalExtraMandara3, &strTemp );
										g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 12, strTemp );
										g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 12, true);
									}
									
									g_cPortal->m_bPortal_FirstZoneSw = HT_TRUE;
									//	JivaPustica For Three Mandara vilige
									g_cPortal->m_iPortal_JiPusticaForMantraIndex = 0;
									g_cUIManager->HT_ShowWindow( _DIALOG_PORTALWND );
									g_cPortal->m_bPotal_Sw = !g_cPortal->m_bPotal_Sw;
									return;
								}
							}
							else
							{
								g_cPortal->HT_vPortal_Network_ReqPortal();
							}
						}
						else
						{
							g_cPortal->HT_vPortal_Network_ReqPortal();
						}
					}
				}
			}
		}
	}
}
//	�Է��Լ� ó�� Jiva Pustica
void HTPortal::HT_vPortal_InputCheckJivaPustica(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_JIVAPUSTICAWND );
		}
		else if( iTargetID>=10 && iTargetID<=14 )
		{
			// ���õ� ���� ��ȣ ���
			HTint iSelectedRadioNo = iTargetID-10;
			if( iSelectedRadioNo >= 0 && iSelectedRadioNo < 10 )
			{
				//	Set MainChar Stop Move
				g_cMainCharacter->HT_vMainChar_SetStopMove();
				//	_MSG_Item
				g_cPortal->HT_vPortal_NetWork_CSP_MSG_Item( iSelectedRadioNo );
			}
			g_cUIManager->HT_HideWindow( _DIALOG_JIVAPUSTICAWND );
		}
	}
}
//	�Է��Լ� ó�� Upgrade Jiva Pustica
void HTPortal::HT_vPortal_InputCheckUpgradeJivaPustica(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_UPGRADEJIVAPUSTICA );
        }
		else if( iTargetID == 4 )
		{
			g_cPortal->m_iSaveSelectUpgradeJPNo = -1;
			g_cPortal->m_iPortal_ImprovmentPusticaPage--;
			if( g_cPortal->m_iPortal_ImprovmentPusticaPage < 0 )
				g_cPortal->m_iPortal_ImprovmentPusticaPage = 0;
			g_cPortal->HT_vPortal_ImprovementMovePustica();
		}
		else if( iTargetID == 5 )
		{
			g_cPortal->m_iSaveSelectUpgradeJPNo = -1;
			g_cPortal->m_iPortal_ImprovmentPusticaPage++;
			if( g_cPortal->m_iPortal_ImprovmentPusticaPage > UPJIVAPUSTICAPORTALCOUNT-1 )
				g_cPortal->m_iPortal_ImprovmentPusticaPage = UPJIVAPUSTICAPORTALCOUNT-1;
			g_cPortal->HT_vPortal_ImprovementMovePustica();
		}
		else if( iTargetID>=10 && iTargetID<=17 )
        {
			// ���õ� ���� ��ȣ ���
			HTint nSelectedRadioNo = iTargetID-10;
			if( nSelectedRadioNo >= 0 && nSelectedRadioNo < 10 )
			{
				if( g_cPortal->m_iSaveSelectUpgradeJPNo == -1 )
                    g_wPotalID = g_iImprovementPustica[g_cPortal->m_iPortal_ImprovmentPusticaPage][nSelectedRadioNo];
				else
				{
					if( nSelectedRadioNo == 1 )
					{
						if( g_cPortal->m_iSaveSelectUpgradeJPNo == 0 )			g_wPotalID = 148;
						else if( g_cPortal->m_iSaveSelectUpgradeJPNo == 1 )		g_wPotalID = 150;
						else													g_wPotalID = 151;
					}
					else if( nSelectedRadioNo == 2 )
					{
						if( g_cPortal->m_iSaveSelectUpgradeJPNo == 0 )			g_wPotalID = 153;
						else if( g_cPortal->m_iSaveSelectUpgradeJPNo == 1 )		g_wPotalID = 155;
						else													g_wPotalID = 156;
					}
					else
					{
						if( g_cPortal->m_iSaveSelectUpgradeJPNo == 0 )			g_wPotalID = 103;
						else if( g_cPortal->m_iSaveSelectUpgradeJPNo == 1 )		g_wPotalID = 105;
						else													g_wPotalID = 131;
					}
				}

				//	for compare Portal item id
				if( g_cPortal->m_iPotral_PortalMoveItemID != HT_ITEM_HIGHZONE_TICKET )
				{
					if( g_cStatus->HT_byGetLevel() < g_iLevelImprovementPustica[g_cPortal->m_iPortal_ImprovmentPusticaPage][nSelectedRadioNo] )
					{
						// �� ��Ż�� �̿��Ͻ÷��� %d���� �̻��̾�� �մϴ�.
						CHTString strTemp;
						g_cPortal->m_dwMessageVal = g_iLevelImprovementPustica[g_cPortal->m_iPortal_ImprovmentPusticaPage][nSelectedRadioNo];
						g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailLevelErr, &strTemp );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
						return;
					}
				}

				//	���ٶ� �������� �̵��Ҷ�
				if( g_cPortal->m_iPortal_ImprovmentPusticaPage == 0 && 
					nSelectedRadioNo<3 &&
					g_cPortal->m_iSaveSelectUpgradeJPNo == -1 )
				{
					if( g_iInationalType == INATIONALTYPE_JAPEN ||
						g_iInationalType == INATIONALTYPE_TAIWAN )
					{
						if( g_poWebLogIn->HT_bGetServerStatusCheck() )
						{
							//	������ ���ٶ� ������ �� �ִ°��� üũ
							HTint iConnectNum_1 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA1ST-1 );
							HTint iConnectNum_2 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1 );
							HTint iConnectNum_3 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1 );
							//	�Ϻ��� �븸 �̿��� ������ �� �Ѿ��.
							if( g_iInationalType != INATIONALTYPE_JAPEN &&
								g_iInationalType != INATIONALTYPE_TAIWAN )
							{
								iConnectNum_2 = -1;
								iConnectNum_3 = -1;
							}

							if( iConnectNum_2 != -1 || iConnectNum_3 != -1 )
							{
								g_cPortal->m_iSaveSelectUpgradeJPNo = nSelectedRadioNo;
								//	�̵� ��Ż ����
								for( HTint i=0 ; i<8 ; i++ )
								{
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, _T("") );
								}

								CHTString strTemp;
								// ���ٶ� 1������_0
								g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara1, &strTemp, _T(""), _T("") );
								g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10, strTemp.HT_szGetString() );
								g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 10, true);
								// �ι�° ���ٶ�
								if( iConnectNum_2 != -1 )
								{
									// ���ٶ� 1������_1
									g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara2, &strTemp, _T(""), _T("") );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 11, strTemp.HT_szGetString() );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 11, true);
								}
								// ����° ���ٶ�
								if( iConnectNum_3 != -1 )
								{
									// ���ٶ� 1������_2
									g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara3, &strTemp, _T(""), _T("") );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 12, strTemp.HT_szGetString() );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 12, true);
								}
								return;
							}
						}
					}
				}

				//	�ֽ��� �������� �̵��Ҷ�
				if( g_wPotalID==161 )
				{
					if( g_iInationalType == INATIONALTYPE_KOREA ||
						g_iInationalType == INATIONALTYPE_CHINA ||
						g_iInationalType == INATIONALTYPE_JAPEN ||
						g_iInationalType == INATIONALTYPE_INDONESIA ||
						g_iInationalType == INATIONALTYPE_PHILIPPINE )
					{
						//	���� ��縶
						if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=59 &&
							g_cUIStatus->HT_nGetTotalPureChakra() < 356 && g_cUISkillWindow->HT_nGetSkillPoint() < 64 )
						{
							if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
								g_wPotalID = 144;
							else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
								g_wPotalID = 145;
							else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
								g_wPotalID = 146;
							else
								return;
						}
						//	�� ��縶
						else
						{
							if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
								g_wPotalID = 161;
							else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
								g_wPotalID = 162;
							else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
								g_wPotalID = 163;
							else
								return;
						}
					}
					else
					{
						if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
							g_wPotalID = 161;
						else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
							g_wPotalID = 162;
						else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
							g_wPotalID = 163;
						else
							return;
					}
				}

				if( g_wPotalID != 0 )
				{
					//	�̵��� Ǫ��Ƽ�� ���� ����Ʈ Ʋ���ֱ�
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
					//	ĳ���� �̵����ϰ� ����
					g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

					MSG_ITEM* info = HT_NULL;
					info = new MSG_ITEM;
					info->byType = HT_MSG_ITEM_USE;
					//	Data Setting for MSG_Item
					info->byPlace = g_cPortal->m_byPlace_ForMsgItem;
					info->byIndex = g_cPortal->m_byIndex_ForMsgItem;
					info->snWarpID = g_wPotalID;

					g_pNetWorkMgr->RequestItemUse( info );

					// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
					if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
					{
						g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
						g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
						g_cIndividualStore->HT_vIndividualStore_Close();
					}

					//-----����� �׽�Ʈ�� ���Ͽ�-----//
					//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_UpgradePustica_Use : %d", info->snWarpID );
					//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
					HT_DELETE( info );

					g_cUIManager->HT_HideWindow( _DIALOG_UPGRADEJIVAPUSTICA );
					g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );
				}
			}
		}
	}
}

//	��Ż�� Ŭ��������
HTRESULT HTPortal::HT_vPortal_Click( HTint iPortalObj, HTvector3 vecPickPos )
{
	//	�׾����� ��Ż ��Ÿ�� ó��
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return HT_FAIL;

	//	��Ż�� ���϶��� �ֽſ� ���� �̵��Ҽ� �ִ� ��Ż�� ������ �ش�.
	if( iPortalObj == FORPOTAL_MOBID_FORCHATURANGR )
		m_iPortal_StartPortalID = 177;
	else if( iPortalObj == FORPOTAL_MOBID_FORTRIMURITICAVE )
	{
		switch(g_oMainCharacterInfo.byTrimuriti)
		{
			case TRIMURITI_BRAHMA:
				m_iPortal_StartPortalID = 180;				break;
			case TRIMURITI_VISHNU:
				m_iPortal_StartPortalID = 179;				break;
			case TRIMURITI_SIVA:
				m_iPortal_StartPortalID = 178;				break;
		}
	}
	else
		m_iPortal_StartPortalID = g_pEngineHandler->HT_iGetPortalID( iPortalObj );
	if (m_iPortal_StartPortalID==0) return HT_FAIL;

	//	��Ż�� ���϶� �Ÿ� üũ ���� �ʴ´�.
	if( iPortalObj != FORPOTAL_MOBID_FORCHATURANGR )//&&iPortalObj != FORPOTAL_MOBID_FORTRIMURITICAVE )
	{
        //	�Ÿ� üũ
		HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
		HTfloat fDistance = HT_extern_fGetDisForTwoPoint( vecPickPos, vecMainCharPos );

		//	Ŭ���� ������Ʈ�� Į�� �����϶�
		if( m_iPortal_StartPortalID >= 1100 && 
			m_iPortal_StartPortalID <= 1305 )
		{
			if( fDistance > 50 )
				return HT_FAIL;

			this->HT_vPortal_RegisterKalaCore( m_iPortal_StartPortalID );
			return HT_OK;
		}

		if( fDistance > 200 )
			return HT_FAIL;
	}
		
	//	1���������� �����Ҷ� �������� ������ �˻��ϱ� ������ġ
	m_bPortal_FirstZoneSw = HT_FALSE;
	m_iPortal_FirstZoneIndex = 0;

	// ���ÿ� object�� ���
	if( m_iPortal_StartPortalID == _REFINE_OBJ_NO )
	{
		return g_cNPCControl->HT_hrNPCControl_ClickRefineObject();
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO )
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(0);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_S )		// �ù� 1011
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(1);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_V )		// �񽴴� 1012
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(2);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_B )		// ����帶 1013
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(3);
	}

	CHTString strTemp, strName;
	HTdword dwFee = 0;
	CHTString strNeedFee;

	//	����
	{
		if (m_bPotal_Sw)
			g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
		else
		{
			//	��Ż�� ���϶��� �ϴ� í������ �����Ƿ� �����Ѵ�.
			for (HTint i=0; i<_GOING_PORTAL_NUM; i++)
			{
				m_iGoingPortal[i] = g_pEngineHandler->HT_iGetGoingPotal(m_iPortal_StartPortalID, i, m_dwFee[i], m_dwLevel[i]);
			}

			//	���� ���� ¥������ �ڵ带 ���⿡ �ִ´�. ���� �����
			HTint iTrimuritiCave = 0;
			HTint iKuruma = 0;
			HTint iChaturanga = 0;
			for (HTint i=0; i<_GOING_PORTAL_NUM; i++)
			{
				//	��縶 �������� ������ �ϸ� �ֽſ� ���� ���ߵ� ��Ż�� Ʋ���� ������ �ϴ� ���⼭ ����帶 �ֽ����� ���Ͻ�Ű�� �ؿ��� �ֽſ� �x�� ��Ż�� �����Ѵ�.
				if( m_iGoingPortal[i]==_KURUMA_POTAL || m_iGoingPortal[i]==_KURUMA_POTAL+1 || m_iGoingPortal[i]==_KURUMA_POTAL+2 )
				{
					if( iKuruma > 0 )
					{
						m_iGoingPortal[i] = 0;
					}
					else
					{
						m_iGoingPortal[i] = _KURUMA_POTAL;
						iKuruma++;
					}
				}
				else if( m_iGoingPortal[i]==_CHATURANGA_POTAL || m_iGoingPortal[i]==_CHATURANGA_POTAL+1 || m_iGoingPortal[i]==_CHATURANGA_POTAL+2 )
				{
					if( iChaturanga > 0 )
					{
						m_iGoingPortal[i] = 0;
					}
					else
					{
						m_iGoingPortal[i] = _CHATURANGA_POTAL;
						iChaturanga++;
					}
				}
				//	�ֽ� �����̸� �տ� �ڵ庸�� �� ¥������ �ڵ尡 ����.
				else if( m_iGoingPortal[i]==_TRIMURITICAVE	 || m_iGoingPortal[i]==_TRIMURITICAVE+1 || m_iGoingPortal[i]==_TRIMURITICAVE+2 || 
						 m_iGoingPortal[i]==_TRIMURITICAVE+3 || m_iGoingPortal[i]==_TRIMURITICAVE+4 || m_iGoingPortal[i]==_TRIMURITICAVE+5 || 
						 m_iGoingPortal[i]==_TRIMURITICAVE+6 || m_iGoingPortal[i]==_TRIMURITICAVE+7 || m_iGoingPortal[i]==_TRIMURITICAVE+8 )
				{
					if( iTrimuritiCave > 0 )
					{
						m_iGoingPortal[i] = 0;
					}
					else
					{
						m_iGoingPortal[i] = _TRIMURITICAVE;
						iTrimuritiCave++;
					}
				}
			}

			//	���� ��Ż �̸�
			g_pEngineHandler->HT_bGetPotalName(m_iPortal_StartPortalID, &strName);
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strName.HT_szGetString() );

			//	��Ż �̸��� �ѹ� ���� �ʱ�ȭ ��Ų��.
			for( HTint i=0 ; i<_GOING_PORTAL_NUM; i++ )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
				g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10+i, false);
			}

			//	�ֽ� ������ ���� ����Ʈ�ȴ�����ȣ
			m_iTirmuritiCaveNo = -1;
			HTint iTempNo = 0;
			for( i=0 ; i<_GOING_PORTAL_NUM; i++ )
			{
				if( m_iGoingPortal[i] != 0 ) //&& m_iGoingPortal[i] != (_KURUMA_POTAL+1) && m_iGoingPortal[i] != (_KURUMA_POTAL+2))
				{
					//	�̵��Ϸ��� ��Ż�� ��縶�̸� �ֽſ� ���� ��Ż�� ������ �ش�.
					if( m_iGoingPortal[i]==_KURUMA_POTAL )
					{
						//	�ϴ� �ѱ���
						if( g_iInationalType == INATIONALTYPE_KOREA ||
							g_iInationalType == INATIONALTYPE_CHINA ||
							g_iInationalType == INATIONALTYPE_JAPEN ||
							g_iInationalType == INATIONALTYPE_INDONESIA ||
							g_iInationalType == INATIONALTYPE_PHILIPPINE )
						{
							//	���� ��縶
							if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=59 &&
								g_cUIStatus->HT_nGetTotalPureChakra() < 356 && g_cUISkillWindow->HT_nGetSkillPoint() < 64 )
							{
								switch(g_oMainCharacterInfo.byTrimuriti)
								{
									case TRIMURITI_BRAHMA:
										m_iGoingPortal[i] = 144;				break;
									case TRIMURITI_VISHNU:
										m_iGoingPortal[i] = 145;				break;
									case TRIMURITI_SIVA:
										m_iGoingPortal[i] = 146;				break;
									default :									break;
								}
							}
							//	�� ��縶
							else
							{
								switch(g_oMainCharacterInfo.byTrimuriti)
								{
									case TRIMURITI_BRAHMA:
										m_iGoingPortal[i] = 161;				break;
									case TRIMURITI_VISHNU:
										m_iGoingPortal[i] = 162;				break;
									case TRIMURITI_SIVA:
										m_iGoingPortal[i] = 163;				break;
									default :									break;
								}
							}
						}
						else
						{
							switch(g_oMainCharacterInfo.byTrimuriti)
							{
								case TRIMURITI_BRAHMA:
									m_iGoingPortal[i] = 161;				break;
								case TRIMURITI_VISHNU:
									m_iGoingPortal[i] = 162;				break;
								case TRIMURITI_SIVA:
									m_iGoingPortal[i] = 163;				break;
								default :									break;
							}
						}
					}
					else if( m_iGoingPortal[i]==_CHATURANGA_POTAL )
					{
						switch(g_oMainCharacterInfo.byTrimuriti)
						{
							case TRIMURITI_BRAHMA:
								m_iGoingPortal[i] = 173;				break;
							case TRIMURITI_VISHNU:
								m_iGoingPortal[i] = 175;				break;
							case TRIMURITI_SIVA:
								m_iGoingPortal[i] = 174;				break;
							default :									break;
						}
					}
					else if( m_iGoingPortal[i]==_TRIMURITICAVE )
					{
						if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
						{
							if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=45 )
							{
								m_iGoingPortal[i] = 183;
								m_iTirmuritiCaveNo = 0;
							}
							else if( g_cStatus->HT_byGetLevel()>=46 && g_cStatus->HT_byGetLevel()<=61 )
							{
								m_iGoingPortal[i] = 186;
								m_iTirmuritiCaveNo = 1;
							}
							else if( g_cStatus->HT_byGetLevel()>=61 )
							{
								m_iGoingPortal[i] = 189;
								m_iTirmuritiCaveNo = 2;
							}
						}
						else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
						{
							if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=45 )
							{
								m_iGoingPortal[i] = 182;
								m_iTirmuritiCaveNo = 0;
							}
							else if( g_cStatus->HT_byGetLevel()>=46 && g_cStatus->HT_byGetLevel()<=61 )
							{
								m_iGoingPortal[i] = 185;
								m_iTirmuritiCaveNo = 1;
							}
							else if( g_cStatus->HT_byGetLevel()>=61 )
							{
								m_iGoingPortal[i] = 188;
								m_iTirmuritiCaveNo = 2;
							}
						}
						else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
						{
							if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=45 )
							{
								m_iGoingPortal[i] = 181;
								m_iTirmuritiCaveNo = 0;
							}
							else if( g_cStatus->HT_byGetLevel()>=46 && g_cStatus->HT_byGetLevel()<=61 )
							{
								m_iGoingPortal[i] = 184;
								m_iTirmuritiCaveNo = 1;
							}
							else if( g_cStatus->HT_byGetLevel()>=61 )
							{
								m_iGoingPortal[i] = 187;
								m_iTirmuritiCaveNo = 2;
							}
						}
					}

					g_pEngineHandler->HT_bGetPotalName(m_iGoingPortal[i], &strName) ;
					dwFee = g_pEngineHandler->HT_dwGetPortalFee(m_iPortal_StartPortalID, m_iGoingPortal[i]);

					if( dwFee == 0 )
					{
						if( m_iGoingPortal[i]==144 || m_iGoingPortal[i]==145 || m_iGoingPortal[i]==146 )
							dwFee = 2000;
					}
					
					if (dwFee)
					{
						// [ �̿�� : %d ���Ǿ� ]
						m_dwMessageVal = dwFee;
						HT_vPortal_SetMessage( eMsgPortalNeedFee, &strNeedFee );
						strTemp = strName + strNeedFee;
					}
					else 
					{
						strTemp = strName;
					}
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, strTemp );
					g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10+i, true);
				}
			}
			g_cUIManager->HT_ShowWindow( _DIALOG_PORTALWND );
			m_pCharpos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
			g_cMainCharacter->HT_vMainChar_SetStopMove();
		}
		m_bPotal_Sw = !m_bPotal_Sw;
		return HT_OK;
	}
	return HT_FAIL;
}

// �������� ����� ���� ȣ��
HTvoid HTPortal::HT_vPortal_Chaturanga_Enter()
{
	switch(g_oMainCharacterInfo.byTrimuriti)
	{
		case TRIMURITI_BRAHMA:
			g_wPotalID = 173;	
			break;
		case TRIMURITI_VISHNU:
			g_wPotalID = 175;	
			break;
		case TRIMURITI_SIVA:
			g_wPotalID = 174;	
			break;
		default :
			g_wPotalID = 0;
			break;
	}
	//	ĳ���� �̵����ϰ� ����
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );
}

//	��Ż â �ݱ�
HTvoid HTPortal::HT_vPotal_AntiActive()
{
	m_bPotal_Sw = HT_FALSE;
	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
}

//	ESC Key ������ â �ݱ�
HTvoid HTPortal::HT_vPotal_ESC_CloseWindow()
{
	//	��Ż â �ݱ�
	HT_vPotal_AntiActive();
}

//	ĳ���� ��ġüũ_ĳ���� �����̸� �ٿ��Ų��
HTvoid HTPortal::HT_vPortal_CharPos_Check()
{
	if( m_bPotal_Sw == HT_FALSE )
		return;

	HTPoint pCheckGet = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if( m_pCharpos_Memory.x != pCheckGet.x || m_pCharpos_Memory.y != pCheckGet.y )
	{
		//	��Ż â �ݱ�
		HT_vPotal_AntiActive();
	}
}

//	���� �̵��� ���� Ǫ��Ƽī Dlg
HTvoid HTPortal::HT_vPortal_ImprovementMovePustica()
{
	//	�̵� ��Ż ����
	CHTString strName; 
	HT_g_Script_SetMessage( eMsgCommonZoneForBillPotal_1+m_iPortal_ImprovmentPusticaPage, &strName, _T("") );
    for( HTint i=0 ; i<8 ; i++ )
	{
		if( g_iImprovementPustica[m_iPortal_ImprovmentPusticaPage][i] == 161 )
		{
			switch(g_oMainCharacterInfo.byTrimuriti)
			{
				case TRIMURITI_BRAHMA:
					g_pEngineHandler->HT_bGetPotalName(161, &strName) ;
					break;
				case TRIMURITI_VISHNU:
					g_pEngineHandler->HT_bGetPotalName(162, &strName) ;
					break;
				case TRIMURITI_SIVA:
					g_pEngineHandler->HT_bGetPotalName(163, &strName) ;
					break;
			}
			g_cUIManager->HT_SetScriptMessage( eMsgPortalTrimuriti, &strName, _T(""), _T("") );	//	"�ֽ�����"
		}
		else if( g_iImprovementPustica[m_iPortal_ImprovmentPusticaPage][i] )
            g_pEngineHandler->HT_bGetPotalName(g_iImprovementPustica[m_iPortal_ImprovmentPusticaPage][i], &strName) ;
		else
			strName.HT_hrCleanUp();

		g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, strName.HT_szGetString() );
		if( strName.HT_bIsEmpty() )
            g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 10+i, false);
		else
			g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 10+i, true);
	}
	m_iSaveSelectUpgradeJPNo = -1;
}

//	����ũ��ũ
//	������ ��Ż ��û�ϱ�
HTvoid HTPortal::HT_vPortal_Network_ReqPortal()
{
	// â��â�� �����ִٸ� �ݾ��ش�.
	if( g_cUIManager ) g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	PS_CSP_REQ_MOVE_PORTAL info = HT_NULL;
	info = new S_CSP_REQ_MOVE_PORTAL;

	if( g_wResentZoneServerID == ZONE_MANDARA2ND )
	{
		//	���ٶ� ���� ���ʽ�
		if( m_iPortal_StartPortalID == 101 )
			m_iPortal_StartPortalID = 147;
		//	���ٶ� ����
		else if( m_iPortal_StartPortalID == 103 )
			m_iPortal_StartPortalID = 148;
		//	������ �� �Ա�
		else if( m_iPortal_StartPortalID == 104 )
			m_iPortal_StartPortalID = 149;
		//	������ ���� ��
		else if( m_iPortal_StartPortalID == 105 )
			m_iPortal_StartPortalID = 150;
		//	���������칰
		else if( m_iPortal_StartPortalID == 131 )
			m_iPortal_StartPortalID = 151;


		//	���ٶ� ���� ���ʽ�
		if( m_iPortal_TargetPortalID == 101 )
			m_iPortal_TargetPortalID = 147;
		//	���ٶ� ����
		else if( m_iPortal_TargetPortalID == 103 )
			m_iPortal_TargetPortalID = 148;
		//	������ �� �Ա�
		else if( m_iPortal_TargetPortalID == 104 )
			m_iPortal_TargetPortalID = 149;
		//	������ ���� ��
		else if( m_iPortal_TargetPortalID == 105 )
			m_iPortal_TargetPortalID = 150;
		//	���������칰
		else if( m_iPortal_TargetPortalID == 131 )
			m_iPortal_TargetPortalID = 151;
	}

	if( g_wResentZoneServerID == ZONE_MANDARA3TH )
	{
		//	���ٶ� ���� ���ʽ�
		if( m_iPortal_StartPortalID == 101 )
			m_iPortal_StartPortalID = 152;
		//	���ٶ� ����
		else if( m_iPortal_StartPortalID == 103 )
			m_iPortal_StartPortalID = 153;
		//	������ �� �Ա�
		else if( m_iPortal_StartPortalID == 104 )
			m_iPortal_StartPortalID = 154;
		//	������ ���� ��
		else if( m_iPortal_StartPortalID == 105 )
			m_iPortal_StartPortalID = 155;
		//	���������칰
		else if( m_iPortal_StartPortalID == 131 )
			m_iPortal_StartPortalID = 156;


		//	���ٶ� ���� ���ʽ�
		if( m_iPortal_TargetPortalID == 101 )
			m_iPortal_TargetPortalID = 152;
		//	���ٶ� ����
		else if( m_iPortal_TargetPortalID == 103 )
			m_iPortal_TargetPortalID = 153;
		//	������ �� �Ա�
		else if( m_iPortal_TargetPortalID == 104 )
			m_iPortal_TargetPortalID = 154;
		//	������ ���� ��
		else if( m_iPortal_TargetPortalID == 105 )
			m_iPortal_TargetPortalID = 155;
		//	���������칰
		else if( m_iPortal_TargetPortalID == 131 )
			m_iPortal_TargetPortalID = 156;
	}
		

	info->wStartPortalID = m_iPortal_StartPortalID;
	info->wEndPortalID = g_wPotalID = m_iPortal_TargetPortalID;

	g_pNetWorkMgr->RequestReqMovePortal( info );

	// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_CSP_REQ_Portal : %d, %d", 
	//	info->wStartPortalID,  info->wEndPortalID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
 
	//	ĳ���� �̵����ϰ� ����
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );
}


//	������ ��Ż ��û�� ���� ���� �ޱ� -> ���� ���� �޽��� �ϰ���
HTvoid HTPortal::HT_vPortal_Network_SCP_Resp_Portal( PS_SCP_RESP_MOVE_PORTAL info )
{
	// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	CHTString strTemp;
	switch( info->byResult )
	{
		// Ÿ�������� �̵�
		case REPLY_MOVE_PORTAL_OUTAREA:
		{
			HTbyte byTempZone;
			if( info->byZone == 1 )
			{
				if( m_iPortal_FirstZoneIndex == 0 )
					byTempZone = ZONE_MANDARA1ST;
				else if( m_iPortal_FirstZoneIndex == 1 )
					byTempZone = ZONE_MANDARA2ND;
				else if( m_iPortal_FirstZoneIndex == 2 )
					byTempZone = ZONE_MANDARA3TH;
				else
					byTempZone = ZONE_MANDARA1ST;
			}
			else
			{
             	byTempZone = info->byZone;
			}

			//	���� üũ
			HTint iConnectNum=0;
			
			if (g_poWebLogIn->HT_bGetServerStatusCheck())
				iConnectNum = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, byTempZone-1 );

			if( iConnectNum < CONNECTNUM_SERVERLIMIT )
			{
				g_wResentZoneServerID = byTempZone;
				//y.w.k
				//HSTLog("closelog1", ".\\Data\\[LOG]SERVER_CONNECTION.txt");
				//	���� ������ ���� ����
				g_pNetWorkMgr->DisConnect();
			
				//	������ No, IP�� Port�� �������� ����
				g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
				g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
				//	�������� DisConnect Check Seting
				g_bPortalServerDisConnectCheckSw	= HT_FALSE;
				//	�� ���� Ŀ��Ʈ�� ��ٸ����� ����
				g_bZoneServerSwitching = HT_TRUE;
				//	�������� ����
				g_byInitConnectType = CONNECT_TYPE_PORTAL;
			}
			else
			{
				// �����Ͻ÷��� ������ �������� �ο��� �ʰ��Ͽ� �����Ҽ� �����ϴ�. ����� �ٽ� �̵��� �ֽʽÿ�.
				HT_vPortal_SetMessage( eMsgProtalExcessMember, &strTemp );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			}
		}
			break;
		// �̵��Ҽ� ���� ����
		case REPLY_MOVE_PORTAL_STATUS:
			// ���� �̵��Ҽ� ���� �����Դϴ�.
			HT_vPortal_SetMessage( eMsgMoveCannotStatus, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// �̵����� ������
		case REPLY_MOVE_PORTAL_WANTMONEY:
			// ���Ǿư� �����Ͽ� �̵��Ҽ� �����ϴ�.
			HT_vPortal_SetMessage( eMsgPortalMoneyErr, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// �̵��Ҽ�����
		case REPLY_MOVE_PORTAL_WANTLEVEL:
			// ���� ������ �̵��Ҽ� ���� �����Դϴ�.
			HT_vPortal_SetMessage( eMsgPortalLevelErr, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// ��Ÿ ����
		case REPLY_MOVE_PORTAL_FAIL:
			// �������� ������ �̵��Ҽ� �����ϴ�.
			HT_vPortal_SetMessage( eMsgPortalFail, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
	}

	//----------��Ż�̵�----------//
	g_cMainCharacter->HT_vMainChar_SetCanMove();
}

//	������ Į���ھ� ��� ��û�ϱ�
HTvoid HTPortal::HT_vPortal_RegisterKalaCore( HTint iObjNo )
{
	MSG_REGISTER_KALA_CORE* info = HT_NULL;
	info = new MSG_REGISTER_KALA_CORE;

	// Į������ ��Ż ��ȣ�� �̿��Ͽ� �Ǻ��Ѵ�. 
	// ������ �ϵ��ڵ��� ����� ������ �������� ���α׷��� © �� ������...
	switch(iObjNo)
	{
		case 1105:
			info->snID = g_krgKalaAltar2[0].sID;		break;
		case 1101:
			info->snID = g_krgKalaAltar2[1].sID;		break;
		case 1102:
			info->snID = g_krgKalaAltar2[2].sID;		break;
		case 1103:
			info->snID = g_krgKalaAltar2[3].sID;		break;
		case 1104:
			info->snID = g_krgKalaAltar2[4].sID;		break;

		case 1205:
			info->snID = g_krgKalaAltar2[5].sID;		break;
		case 1201:
			info->snID = g_krgKalaAltar2[6].sID;		break;
		case 1202:
			info->snID = g_krgKalaAltar2[7].sID;		break;
		case 1203:
			info->snID = g_krgKalaAltar2[8].sID;		break;
		case 1204:
			info->snID = g_krgKalaAltar2[9].sID;		break;

		case 1305:
			info->snID = g_krgKalaAltar2[10].sID;	break;
		case 1301:
			info->snID = g_krgKalaAltar2[11].sID;	break;
		case 1302:
			info->snID = g_krgKalaAltar2[12].sID;	break;
		case 1303:
			info->snID = g_krgKalaAltar2[13].sID;	break;
		case 1304:
			info->snID = g_krgKalaAltar2[14].sID;	break;
		default:
			return;
	}

	g_pNetWorkMgr->RequestReqRegisterKalaCore( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send__MSG_REGISTER_KALA_CORE ID:%d", info->snID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	_MSG_Item
HTvoid HTPortal::HT_vPortal_NetWork_CSP_MSG_Item( HTint iIndex )
{
	//	���ٶ� ���� 1120
	//	���߶� ����
	if( iIndex == 0 )
	{
		//	JivaPustica For Three Mandara vilige
		if( m_iPortal_JiPusticaForMantraIndex == 0 )
		{
			if (!g_poWebLogIn->HT_bGetServerStatusCheck())
			{
				return;
			}

			//	������ ���ٶ� ������ �� �ִ°��� üũ
			HTint iConnectNum_1 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA1ST-1 );
			HTint iConnectNum_2 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1 );
			HTint iConnectNum_3 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1 );
			//	�Ϻ��� �븸 �̿��� ������ �� �Ѿ��.
			if( g_iInationalType != INATIONALTYPE_JAPEN &&
				g_iInationalType != INATIONALTYPE_TAIWAN )
			{
				iConnectNum_2 = -1;
				iConnectNum_3 = -1;
			}

			if( iConnectNum_2 == -1 && iConnectNum_3 == -1 )
			{
				iIndex = 1120;
			}
			else
			{
				CHTString strTemp;

				//	��Ż �̸� �ʱ�ȭ
				g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strTemp.HT_szGetString() );
				for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
				{
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
				}
				// ù��° ���ٶ�
				// ���ٶ� 1������_0
				this->HT_vPortal_SetMessage( eMsgPortalExtraMandara1, &strTemp );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10, strTemp );
				g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10, true);
				// �ι�° ���ٶ�
				if( iConnectNum_2 != -1 )
				{
					// ���ٶ� 1������_1
					this->HT_vPortal_SetMessage( eMsgPortalExtraMandara2, &strTemp );
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 11, strTemp );
					g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 11, true);
				}
				// ����° ���ٶ�
				if( iConnectNum_3 != -1 )
				{
					// ���ٶ� 1������_2
					this->HT_vPortal_SetMessage( eMsgPortalExtraMandara3, &strTemp );
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 12, strTemp );
					g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 12, true);
				}
				
				m_bPortal_FirstZoneSw = HT_TRUE;
				//	JivaPustica For Three Mandara vilige
				m_iPortal_JiPusticaForMantraIndex = 1;
				g_cUIManager->HT_ShowWindow( _DIALOG_PORTALWND );
				m_bPotal_Sw = !g_cPortal->m_bPotal_Sw;
				return;
			}
		}
		else
		{
			if( m_iPortal_JiPusticaForMantraIndex == 2 )
				iIndex = 1120;
			else if( m_iPortal_JiPusticaForMantraIndex == 3 )
				iIndex = 1216;
			else if( m_iPortal_JiPusticaForMantraIndex == 4 )
				iIndex = 1246;
			else
				return;
			//	JivaPustica For Three Mandara vilige
			m_iPortal_JiPusticaForMantraIndex = 0;
		}
	}
	//	���߶� ����
	else if( iIndex == 1 )
	{
		if( g_cStatus->HT_byGetLevel() < 15 )
		{
			//	���̾� �޽��� �߰���.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 15���� �̿� �� �� �ֽ��ϴ�.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1154;
	}
	//	���� ����
	else if( iIndex == 2 )
	{
		if( g_cStatus->HT_byGetLevel() < 40 )
		{
			//	���̾� �޽��� �߰���.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 40���� �̿� �� �� �ֽ��ϴ�.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1155;
	}
	//	������
	else if( iIndex == 3 )
	{
		if( g_cStatus->HT_byGetLevel() < 40 )
		{
			//	���̾� �޽��� �߰���.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 40���� �̿� �� �� �ֽ��ϴ�.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1156;
	}
	//	�ֽ� ���� ( ����帶, �񽴴�, �ù� )
	else if( iIndex == 4 )
	{
		if( g_cStatus->HT_byGetLevel() < 30 )
		{
			//	���̾� �޽��� �߰���.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 30���� �̿� �� �� �ֽ��ϴ�.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}

		if( g_iInationalType == INATIONALTYPE_KOREA ||
			g_iInationalType == INATIONALTYPE_CHINA ||
			g_iInationalType == INATIONALTYPE_JAPEN ||
			g_iInationalType == INATIONALTYPE_INDONESIA ||
			g_iInationalType == INATIONALTYPE_PHILIPPINE )
		{
			//	���� ��縶
			if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=59 &&
				g_cUIStatus->HT_nGetTotalPureChakra() < 356 && g_cUISkillWindow->HT_nGetSkillPoint() < 64 )
			{
				if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			iIndex = 1337;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		iIndex = 1338;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		iIndex = 1339;
				else																return;
			}
			//	�� ��縶
			else
			{
				if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			iIndex = 1255;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		iIndex = 1254;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		iIndex = 1256;
				else																return;
			}
		}
		else
		{
			if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )				iIndex = 1255;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		iIndex = 1254;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		iIndex = 1256;
				else																return;
		}
	}
	else
	{
		return;
	}

	//	�̵��� Ǫ��Ƽ�� ���� ����Ʈ Ʋ���ֱ�
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	ĳ���� �̵����ϰ� ����
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	info->byType = HT_MSG_ITEM_USE;
	//	Data Setting for MSG_Item
	info->byPlace = m_byPlace_ForMsgItem;
	info->byIndex = m_byIndex_ForMsgItem;
	info->snWarpID = iIndex;

	g_pNetWorkMgr->RequestItemUse( info );

	// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	
	// â��â�� �����ִٸ� �ݾ��ش�.
	if( g_cUIManager ) g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Pustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//	_MSG_MoveOtherZone
HTvoid HTPortal::HT_vPortal_NetWork_SCP_MSG_MoveOtherZone( MSG_MoveOtherZone* info )
{ 
	HTbyte byTempZone;
	////	���߶� ����
	//if( info->snPositionID == 1120 )
	//{
	//	byTempZone = 1;
	//}
	////	���ٶ� 2
	//else if( info->snPositionID == 1216 )
	//{
	//	byTempZone = 18;
	//}
	////	���ٶ� 3
	//else if( info->snPositionID == 1246 )
	//{
	//	byTempZone = 19;
	//}
	////	���߶� ����
	//else if( info->snPositionID == 1154 )
	//{
	//	byTempZone = 2;
	//}
	////	���� ����
	//else if( info->snPositionID == 1155 )
	//{
	//	byTempZone = 7;
	//}
	////	������
	//else if( info->snPositionID == 1156 )
	//{
	//	byTempZone = 9;
	//}
	////	�� �ֽ� ���� ( ����帶, �񽴴�, �ù� )
	//else if( info->snPositionID == 1158 || info->snPositionID == 1157 || info->snPositionID == 1159 )
	//{
	//	byTempZone = 10;
	//}
	////	���� �ֽ� ���� ( ����帶, �񽴴�, �ù� )
	//else if( info->snPositionID == 1337 || info->snPositionID == 1338 || info->snPositionID == 1339 )
	//{
	//	byTempZone = 20;
	//}
	//else
	//{
	//	return;
	//}

	// ���� ������ �ŷ��߿� ��Ż�̵��� �ߴٸ� ��Żâ�� ���Գ���â�� �ݾ��ش�.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}
		
	if( !g_pParamMgr->HT_bGetNPCZone( info->snPositionID, &byTempZone ) )
		return;

	//	���� üũ
	CHTString strTemp;
	HTint iConnectNum=0;
	
	if (g_poWebLogIn->HT_bGetServerStatusCheck())
		iConnectNum = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, byTempZone-1 );

	if( iConnectNum < CONNECTNUM_SERVERLIMIT )
	{
		g_wResentZoneServerID = byTempZone;
		//	���� ������ ���� ����
		g_pNetWorkMgr->DisConnect();

		//	������ No, IP�� Port�� �������� ����
		g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
		g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
		//	�������� DisConnect Check Seting
		g_bPortalServerDisConnectCheckSw	= HT_FALSE;
		//	�� ���� Ŀ��Ʈ�� ��ٸ����� ����
		g_bZoneServerSwitching = HT_TRUE;
		//	�������� ����
		g_byInitConnectType = CONNECT_TYPE_PUSTICA;
		//	Setting NPC ID
		g_wPotalID = info->snPositionID;
	}
	else
	{
		// �����Ͻ÷��� ������ �������� �ο��� �ʰ��Ͽ� �����Ҽ� �����ϴ�. ����� �ٽ� �̵��� �ֽʽÿ�.
		HT_vPortal_SetMessage( eMsgProtalExcessMember, &strTemp );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
	}
}

//	MSG_Warp
HTvoid HTPortal::HT_vPortal_NetWork_SCP_Msg_Warp( MSG_Warp* info )
{
	g_wResentZoneServerID = info->dwPlace;
	//	���� ������ ���� ����
	g_pNetWorkMgr->DisConnect();

	//	������ No, IP�� Port�� �������� ����
	g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
	g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
	//	�������� DisConnect Check Seting
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;
	//	�� ���� Ŀ��Ʈ�� ��ٸ����� ����
	g_bZoneServerSwitching = HT_TRUE;
	//	�������� ����
	g_byInitConnectType = CONNECT_TYPE_GMRECALL;
	//	Setting NPC ID
	g_wPotalID = 0;
}

//	����üũ�ؿ���
HTint HTPortal::HT_iPortal_GetConnectNum( HTint iGroup, HTint iConnectZone )
{
	if( !g_bDevelopingMode )
        return g_poWebLogIn->HT_iGetCCUserNum( iGroup, iConnectZone );
	else
		return 1;
}

HTvoid HTPortal::HT_vPortal_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vPortal_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vPortal_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vPortal_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vPortal_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vPortal_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vPortal_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid HTPortal::HT_vPortal_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// �ʿ��� ��
		case eMsgParamNeedMoney	:	
		// �ʿ��� ĳ���� ����
		case eMsgParamNeedLevel	:
			pszParam->HT_szFormat( "%d", m_dwMessageVal );
			break;
		
		// ���� 
		case eMsgParamZoneMandara1st:
			pszParam->HT_szFormat( "%d", 1 ); // ���ٶ� 1������
			break;

		default:
			break;
	}
}

//	Data Setting for MSG_Item
HTvoid HTPortal::HT_vPortal_SetDataForMsgItem( HTbyte byPlace, HTbyte byIndex, HTint iItemID )
{
	//	for compare Portal item id
	m_iPotral_PortalMoveItemID = iItemID;
	//	Data Setting for MSG_Item
	m_byPlace_ForMsgItem = byPlace;
	m_byIndex_ForMsgItem = byIndex;
    //	JivaPustica For Three Mandara vilige
	m_iPortal_JiPusticaForMantraIndex = 0;
	m_pCharpos_Memory = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
}

//	Set Portress Pustica
HTvoid HTPortal::HT_vPortal_SetPortressPustica( HTbyte byPlace, HTbyte byIndex )
{
	int iStrongGuild = g_cGuildSystem->HT_iGuildNet_MyStrongGuildSequence();
	if( iStrongGuild<0 || iStrongGuild>3 )
	{
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonNotHaveFotress, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
		return;
	}

	//	�̵��� Ǫ��Ƽ�� ���� ����Ʈ Ʋ���ֱ�
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	ĳ���� �̵����ϰ� ����
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	info->byType = HT_MSG_ITEM_USE;
	//	Data Setting for MSG_Item
	info->byPlace = byPlace;
	info->byIndex = byIndex;
	if( iStrongGuild == 0 )
        info->snWarpID = g_wPotalID = ePortal_Stronghold_NW;
	else if( iStrongGuild == 1 )
        info->snWarpID = g_wPotalID = ePortal_Stronghold_NE;
	else if( iStrongGuild == 2 )
        info->snWarpID = g_wPotalID = ePortal_Stronghold_SW;
	else if( iStrongGuild == 3 )
        info->snWarpID = g_wPotalID = ePortal_Stronghold_SE;
	g_pNetWorkMgr->RequestItemUse( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_FortressPustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//	Set Siege Pustica
HTvoid HTPortal::HT_vPortal_SetSiegePustica( HTbyte byPlace, HTbyte byIndex )
{
	//	�̵��� Ǫ��Ƽ�� ���� ����Ʈ Ʋ���ֱ�
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	ĳ���� �̵����ϰ� ����
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	info->byType = HT_MSG_ITEM_USE;
	//	Data Setting for MSG_Item
	info->byPlace = byPlace;
	info->byIndex = byIndex;
	info->snWarpID = g_wPotalID = 223;
	g_pNetWorkMgr->RequestItemUse( info );
	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_SiegePustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
