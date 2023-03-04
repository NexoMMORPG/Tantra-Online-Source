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

#define _OFFERING_OBJ_NO_S		1011	// 시바
#define _OFFERING_OBJ_NO_V		1012	// 비슈느
#define _OFFERING_OBJ_NO_B		1013	// 브라흐마

#define UPJIVAPUSTICAPORTALCOUNT	8

//	웨데이타 받아오기
//CHTWebLogIn*	m_pcPotalWebLogIn;

enum
{
	_BRAHMA,
	_VISHUNU,
	_SIVA,
};

//	향상된 이동의 지바 푸스티카
HTint g_iImprovementPustica[UPJIVAPUSTICAPORTALCOUNT][10] = {	
	                                    103, 105, 131, 124, 126,   0,   0,   0,   0,   0,
										117, 120, 119, 128,   0,   0,   0,   0,   0,   0,
										133, 134, 135, 136,   0,   0,   0,   0,   0,   0,
										139, 138, 140,   0,   0,   0,   0,   0,   0,   0,
										141, 142, 143, 191,   0,   0,   0,   0,   0,   0,
										161,   0,   0,   0,   0,   0,   0,   0,   0,   0,
										202, 203, 204, 205,   0,   0,   0,   0,   0,   0,
										221, 220, 224, 225, 226,   0,   0,   0,   0,   0 };

//	향상된 이동의 지바 푸스티카
HTint g_iLevelImprovementPustica[UPJIVAPUSTICAPORTALCOUNT][10] = {	  
	                                          0,   0,   0,  15,  15,   0,   0,   0,   0,   0,		//	만다라 지역
											 15,  15,  15,  40,   0,   0,   0,   0,   0,   0,		//	샴발라 지역		
											 40,  40,  40,  40,   0,   0,   0,   0,   0,   0,		//	지나 지역
											 40,  40,  40,   0,   0,   0,   0,   0,   0,   0,		//	파미르 고원
											 40,  40,  40,  60,   0,   0,   0,   0,   0,   0,		//	유배지
											 30,  30,  30,   0,   0,   0,   0,   0,   0,   0,
											  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
											  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };		//	주신지역


HTPortal::HTPortal(void)
{
	m_bPotal_Sw = HT_FALSE;
	//	포탈 ID
	m_iPortal_StartPortalID = 0;
	m_iPortal_TargetPortalID = 0;
	//	대화상자 스위칭 변수
	m_bPortal_ReDialogBoxActiveSw = HT_FALSE;
	//m_pcPotalWebLogIn = HT_NULL;
	//	Data Setting for MSG_Item
	m_byPlace_ForMsgItem = 0;
	m_byIndex_ForMsgItem = 0;
	//	for compare Portal item id
	m_iPotral_PortalMoveItemID = 0;
	//	 향샹된 이동의 지바 푸스티카 대화상자의 페이지
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

//	1. 포탈 초기화
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture 포탈
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalTitle, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label 현재 포탈 이름
	g_cUIManager->HT_AddTextureControl( _DIALOG_PORTALWND, 2, 10, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalPortalName, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 60, 390, 17 );
	//	Loop
	for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
	{
		//	Button 포탈 리스트1
		g_cUIManager->HT_AddButtonControl( _DIALOG_PORTALWND, 10+i, 0, 5, 85+(25*i), 9, 0, 1500, 390, 17 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_PORTALWND, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85+(25*i), 390, 17 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_PORTALWND, 10+i );
	}

	//	[_DIALOG_JIVAPUSTICAWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_JIVAPUSTICAWND, _T(""), 400, 250, g_cPortal->HT_vPortal_InputCheckJivaPustica, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_JIVAPUSTICAWND, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_JIVAPUSTICAWND, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture 지바푸스티카
	g_cUIManager->HT_AddTextureControl( _DIALOG_JIVAPUSTICAWND, 2, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalJivaPustica, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Only Label 현재 포탈 이름
	g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 60, 390, 17 );
	//	Button 만다라 마을
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 10, 0, 5, 85, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalMandaraVillage, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 10, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 10 );
	//	Button 샴발라 지역
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 11, 0, 5, 110, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalShambalraZone, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 11, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 110, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 11 );
	//	Button 지나 지역
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 12, 0, 5, 135, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalJinaZone, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 12, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 135, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 12 );
	//	Button 유배지
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 13, 0, 5, 160, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalExile, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 13, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 160, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 13 );
	//	Button 주신지역
	g_cUIManager->HT_AddButtonControl( _DIALOG_JIVAPUSTICAWND, 14, 0, 5, 185, 9, 0, 1500, 390, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalTrimuriti, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_JIVAPUSTICAWND, 14, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 185, 390, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_JIVAPUSTICAWND, 14 );

	//	[_DIALOG_UPGRADEJIVAPUSTICA]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_UPGRADEJIVAPUSTICA, _T(""), 400, 280, g_cPortal->HT_vPortal_InputCheckUpgradeJivaPustica, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_UPGRADEJIVAPUSTICA, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_UPGRADEJIVAPUSTICA, 1, 8, 3, 36, 1400, 393, 6 );
	//	Texture 향상된지바푸스티카
	g_cUIManager->HT_AddTextureControl( _DIALOG_UPGRADEJIVAPUSTICA, 2, 9, 39, 30, 1400, 150, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgPortalHighJivaPustica, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 150, 17 );
	//	Only Label 현재 포탈 이름
	g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectOtherZone, &strTemp );
    g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 57, 390, 17 );
	//	Button 앞으로
	g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 4, 148, 100, 55, 150, 149 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 4, _T("앞으로"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 66, 55, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 4 );
	//	Button 뒤로
	g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 5, 145, 282, 55, 146, 147 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 5, _T("뒤로"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 263, 55, 72, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 5 );
	//	Loop
	for( HTint i=0 ; i<UPJIVAPUSTICAPORTALCOUNT ; i++ )
	{
		//	Button 포탈 리스트1
		g_cUIManager->HT_AddButtonControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, 0, 5, 85+(25*i), 9, 0, 1500, 390, 17 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 5, 85+(25*i), 390, 17 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_UPGRADEJIVAPUSTICA, 10+i );
	}
}

//	입력함수 처리
void HTPortal::HT_vPortal_InputCheckPortal(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
		}
		//	포탈 버튼을 클릭했을때
		else if( iTargetID>=10 && iTargetID<=_GOING_PORTAL_NUM+10 )
		{
			//if( g_pDuelSystem->HT_byDuel_GetDuelMode() == eChallenge_Combat )
			//{
			//	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, _T("결투중일때는 사용할수 없습니다.") );
			//	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
			//	return;
			//}

			int iSelectBtnNo = iTargetID-10;
			//	1차지역으로 가려할때 나누어진 서버를 검색하기 위한장치
			if( g_cPortal->m_bPortal_FirstZoneSw )
			{
				g_cPortal->m_iPortal_FirstZoneIndex = iSelectBtnNo;
				//	포탈 창 닫기
				g_cPortal->HT_vPotal_AntiActive();
				//	JivaPustica For Three Mandara vilige
				if( g_cPortal->m_iPortal_JiPusticaForMantraIndex == 1 )
				{
					if( iSelectBtnNo == 0 )			g_cPortal->m_iPortal_JiPusticaForMantraIndex = 2;
					else if( iSelectBtnNo == 1 )	g_cPortal->m_iPortal_JiPusticaForMantraIndex = 3;
					else if( iSelectBtnNo == 2 )	g_cPortal->m_iPortal_JiPusticaForMantraIndex = 4;
					//	_MSG_Item -> 0 이 들어가는 m_iPortal_JiPusticaForMantraIndex 에 라디오 버튼 인덱스를 넣는다.
					g_cPortal->HT_vPortal_NetWork_CSP_MSG_Item( 0 );
				}
				//	포탈 이동 요청
				else
				{
					g_cPortal->HT_vPortal_Network_ReqPortal();
				}
			}
			else
			{
				// 포탈 번호 얻기
				g_cPortal->m_iPortal_TargetPortalID = g_cPortal->m_iGoingPortal[iSelectBtnNo];
				if( g_cPortal->m_iPortal_TargetPortalID )
				{
					//	포탈 창 닫기
					g_cPortal->HT_vPotal_AntiActive();

					CHTString strTemp;
                    // 주신전 지역을 선택했을 경우
					if( g_cPortal->m_iPortal_TargetPortalID==_KURUMA_POTAL )
					{
						switch(g_oMainCharacterInfo.byTrimuriti)
						{
							//현재는 캐릭터를 만들때 주신이 1/2/3으로 들어가고 있다. 1/2/4/로 변경되어야 한다.
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

					//	캐릭터가 앉아있다면 스킵
					if( g_cMainCharacter->HT_bMainChar_GetSitStatus() )
					{
						// 앉은 상태에서는 포탈을 탈 수 없습니다.
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
							// 이 포탈을 이용하시려면 %d레벨 이상이어야 합니다.
							g_cPortal->m_dwMessageVal = g_cPortal->m_dwLevel[iSelectBtnNo];
							g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailLevelErr, &strTemp );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
							return;
						}
						if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < (HTint)g_cPortal->m_dwFee[iSelectBtnNo] )
						{
							// 이 포탈을 이용하시려면 %d루피아가 필요합니다.
							g_cPortal->m_dwMessageVal = g_cPortal->m_dwFee[iSelectBtnNo];
							g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailMoneyErr, &strTemp );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
							return;
						}
					}

					// 주신전 지역을 선택했을 경우 주신이 없을때
					if( g_cPortal->m_iPortal_TargetPortalID==0 )
					{
						// 주신전 지역에 가실려면 자신의 주신을 가지고 있어야 합니다. 주신 선택을 원하면 제사장 바난타를 찾아가세요!
						g_cPortal->HT_vPortal_SetMessage( eMsgPortalTrimuritiErr, &strTemp );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
						return;
					}

					if( g_cStatus->HT_byGetLevel() >= g_cPortal->m_dwLevel[iSelectBtnNo] &&
						g_cEquipInventory->HT_iEquipInventory_GetPCMoney() >= (HTint)g_cPortal->m_dwFee[iSelectBtnNo] &&
						g_cPortal->m_iPortal_TargetPortalID!=0 )
					{
						//	1차지역으로 가려할때 나누어진 서버를 검색하기 위한장치
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
								//	일본과 대만 이외의 지역은 걍 넘어간다.
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
									//	포탈 이름 초기화
									g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strTemp.HT_szGetString() );
									for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
									{
										g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
									}
									// 첫번째 만다라
									// 만다라 1차지역_0
									g_cPortal->HT_vPortal_SetMessage( eMsgPortalExtraMandara1, &strTemp );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10, strTemp );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10, true);
									// 두번째 만다라
									if( iConnectNum_2 != -1 )
									{
										// 만다라 1차지역_1
										g_cPortal->HT_vPortal_SetMessage( eMsgPortalExtraMandara2, &strTemp );
										g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 11, strTemp );
										g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 11, true);
									}
									// 세번째 만다라
									if( iConnectNum_3 != -1 )
									{
										// 만다라 1차지역_2
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
//	입력함수 처리 Jiva Pustica
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
			// 선택된 라디오 번호 얻기
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
//	입력함수 처리 Upgrade Jiva Pustica
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
			// 선택된 라디오 번호 얻기
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
						// 이 포탈을 이용하시려면 %d레벨 이상이어야 합니다.
						CHTString strTemp;
						g_cPortal->m_dwMessageVal = g_iLevelImprovementPustica[g_cPortal->m_iPortal_ImprovmentPusticaPage][nSelectedRadioNo];
						g_cPortal->HT_vPortal_SetMessage( eMsgPortalDetailLevelErr, &strTemp );
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
						return;
					}
				}

				//	만다라 지역으로 이동할때
				if( g_cPortal->m_iPortal_ImprovmentPusticaPage == 0 && 
					nSelectedRadioNo<3 &&
					g_cPortal->m_iSaveSelectUpgradeJPNo == -1 )
				{
					if( g_iInationalType == INATIONALTYPE_JAPEN ||
						g_iInationalType == INATIONALTYPE_TAIWAN )
					{
						if( g_poWebLogIn->HT_bGetServerStatusCheck() )
						{
							//	세개의 만다라 마을이 떠 있는것을 체크
							HTint iConnectNum_1 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA1ST-1 );
							HTint iConnectNum_2 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1 );
							HTint iConnectNum_3 = g_cPortal->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1 );
							//	일본과 대만 이외의 지역은 걍 넘어간다.
							if( g_iInationalType != INATIONALTYPE_JAPEN &&
								g_iInationalType != INATIONALTYPE_TAIWAN )
							{
								iConnectNum_2 = -1;
								iConnectNum_3 = -1;
							}

							if( iConnectNum_2 != -1 || iConnectNum_3 != -1 )
							{
								g_cPortal->m_iSaveSelectUpgradeJPNo = nSelectedRadioNo;
								//	이동 포탈 지역
								for( HTint i=0 ; i<8 ; i++ )
								{
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10+i, _T("") );
								}

								CHTString strTemp;
								// 만다라 1차지역_0
								g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara1, &strTemp, _T(""), _T("") );
								g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 10, strTemp.HT_szGetString() );
								g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 10, true);
								// 두번째 만다라
								if( iConnectNum_2 != -1 )
								{
									// 만다라 1차지역_1
									g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara2, &strTemp, _T(""), _T("") );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 11, strTemp.HT_szGetString() );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 11, true);
								}
								// 세번째 만다라
								if( iConnectNum_3 != -1 )
								{
									// 만다라 1차지역_2
									g_cUIManager->HT_SetScriptMessage( eMsgPortalExtraMandara3, &strTemp, _T(""), _T("") );
									g_cUIManager->HT_SetTextLabelControl( _DIALOG_UPGRADEJIVAPUSTICA, 12, strTemp.HT_szGetString() );
									g_cUIManager->HT_SetButtonEnable(_DIALOG_UPGRADEJIVAPUSTICA, 12, true);
								}
								return;
							}
						}
					}
				}

				//	주신전 지역으로 이동할때
				if( g_wPotalID==161 )
				{
					if( g_iInationalType == INATIONALTYPE_KOREA ||
						g_iInationalType == INATIONALTYPE_CHINA ||
						g_iInationalType == INATIONALTYPE_JAPEN ||
						g_iInationalType == INATIONALTYPE_INDONESIA ||
						g_iInationalType == INATIONALTYPE_PHILIPPINE )
					{
						//	저랩 쿠루마
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
						//	고랩 쿠루마
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
					//	이동의 푸스티가 사용시 이펙트 틀어주기
					HTint iTempFXID;
					g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
					//	캐릭터 이동못하게 셋팅
					g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

					MSG_ITEM* info = HT_NULL;
					info = new MSG_ITEM;
					info->byType = HT_MSG_ITEM_USE;
					//	Data Setting for MSG_Item
					info->byPlace = g_cPortal->m_byPlace_ForMsgItem;
					info->byIndex = g_cPortal->m_byIndex_ForMsgItem;
					info->snWarpID = g_wPotalID;

					g_pNetWorkMgr->RequestItemUse( info );

					// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
					if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
					{
						g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
						g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
						g_cIndividualStore->HT_vIndividualStore_Close();
					}

					//-----디버깅 테스트를 위하여-----//
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

//	포탈을 클릭했을때
HTRESULT HTPortal::HT_vPortal_Click( HTint iPortalObj, HTvector3 vecPickPos )
{
	//	죽었을때 포탈 못타게 처리
	if( !g_cMainCharacter->HT_vMainChar_GetCharLive() )
		return HT_FAIL;

	//	포탈용 몹일때는 주신에 따라서 이동할수 있는 포탈을 지정해 준다.
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

	//	포탈용 몹일때 거리 체크 하지 않는다.
	if( iPortalObj != FORPOTAL_MOBID_FORCHATURANGR )//&&iPortalObj != FORPOTAL_MOBID_FORTRIMURITICAVE )
	{
        //	거리 체크
		HTvector3 vecMainCharPos = g_cMainCharacter->HT_vecGetPosition();
		HTfloat fDistance = HT_extern_fGetDisForTwoPoint( vecPickPos, vecMainCharPos );

		//	클릭한 오브젝트가 칼라 제단일때
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
		
	//	1차지역으로 가려할때 나누어진 서버를 검색하기 위한장치
	m_bPortal_FirstZoneSw = HT_FALSE;
	m_iPortal_FirstZoneIndex = 0;

	// 제련용 object일 경우
	if( m_iPortal_StartPortalID == _REFINE_OBJ_NO )
	{
		return g_cNPCControl->HT_hrNPCControl_ClickRefineObject();
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO )
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(0);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_S )		// 시바 1011
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(1);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_V )		// 비슈느 1012
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(2);
	}
	else if( m_iPortal_StartPortalID == _OFFERING_OBJ_NO_B )		// 브라흐마 1013
	{
		return g_cNPCControl->HT_hrNPCControl_ClickOfferingObject(3);
	}

	CHTString strTemp, strName;
	HTdword dwFee = 0;
	CHTString strNeedFee;

	//	ㅋㅋ
	{
		if (m_bPotal_Sw)
			g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
		else
		{
			//	포탈용 몹일때는 일단 챠투랑가 브라흐므로 셋팅한다.
			for (HTint i=0; i<_GOING_PORTAL_NUM; i++)
			{
				m_iGoingPortal[i] = g_pEngineHandler->HT_iGetGoingPotal(m_iPortal_StartPortalID, i, m_dwFee[i], m_dwLevel[i]);
			}

			//	씨발 졸라 짜증나는 코드를 여기에 넣는다. 씨바 랄라라
			HTint iTrimuritiCave = 0;
			HTint iKuruma = 0;
			HTint iChaturanga = 0;
			for (HTint i=0; i<_GOING_PORTAL_NUM; i++)
			{
				//	쿠루마 지역으로 갈려고 하면 주신에 따라서 가야될 포탈이 틀리기 때문에 일단 여기서 브라흐마 주신으로 통일시키고 밑에서 주신에 땨라 포탈을 배정한다.
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
				//	주신 던젼이면 앞에 코드보다 더 짜증나는 코드가 들어간다.
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

			//	현재 포탈 이름
			g_pEngineHandler->HT_bGetPotalName(m_iPortal_StartPortalID, &strName);
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strName.HT_szGetString() );

			//	포탈 이름을 한번 전부 초기화 시킨다.
			for( HTint i=0 ; i<_GOING_PORTAL_NUM; i++ )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
				g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10+i, false);
			}

			//	주신 던젼을 위한 셀렉트된던젼번호
			m_iTirmuritiCaveNo = -1;
			HTint iTempNo = 0;
			for( i=0 ; i<_GOING_PORTAL_NUM; i++ )
			{
				if( m_iGoingPortal[i] != 0 ) //&& m_iGoingPortal[i] != (_KURUMA_POTAL+1) && m_iGoingPortal[i] != (_KURUMA_POTAL+2))
				{
					//	이동하려는 포탈이 쿠루마이면 주신에 따라 포탈을 배정해 준다.
					if( m_iGoingPortal[i]==_KURUMA_POTAL )
					{
						//	일단 한국만
						if( g_iInationalType == INATIONALTYPE_KOREA ||
							g_iInationalType == INATIONALTYPE_CHINA ||
							g_iInationalType == INATIONALTYPE_JAPEN ||
							g_iInationalType == INATIONALTYPE_INDONESIA ||
							g_iInationalType == INATIONALTYPE_PHILIPPINE )
						{
							//	저랩 쿠루마
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
							//	고랩 쿠루마
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
						// [ 이용료 : %d 루피아 ]
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

// 차투랑가 입장권 사용시 호출
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
	//	캐릭터 이동못하게 셋팅
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );
}

//	포탈 창 닫기
HTvoid HTPortal::HT_vPotal_AntiActive()
{
	m_bPotal_Sw = HT_FALSE;
	g_cUIManager->HT_HideWindow( _DIALOG_PORTALWND );
}

//	ESC Key 누르면 창 닫기
HTvoid HTPortal::HT_vPotal_ESC_CloseWindow()
{
	//	포탈 창 닫기
	HT_vPotal_AntiActive();
}

//	캐릭터 위치체크_캐릭터 움직이면 다운시킨다
HTvoid HTPortal::HT_vPortal_CharPos_Check()
{
	if( m_bPotal_Sw == HT_FALSE )
		return;

	HTPoint pCheckGet = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if( m_pCharpos_Memory.x != pCheckGet.x || m_pCharpos_Memory.y != pCheckGet.y )
	{
		//	포탈 창 닫기
		HT_vPotal_AntiActive();
	}
}

//	향상된 이동의 지바 푸스티카 Dlg
HTvoid HTPortal::HT_vPortal_ImprovementMovePustica()
{
	//	이동 포탈 지역
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
			g_cUIManager->HT_SetScriptMessage( eMsgPortalTrimuriti, &strName, _T(""), _T("") );	//	"주신지역"
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

//	네테크워크
//	서버에 포탈 요청하기
HTvoid HTPortal::HT_vPortal_Network_ReqPortal()
{
	// 창고창이 열려있다면 닫아준다.
	if( g_cUIManager ) g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	PS_CSP_REQ_MOVE_PORTAL info = HT_NULL;
	info = new S_CSP_REQ_MOVE_PORTAL;

	if( g_wResentZoneServerID == ZONE_MANDARA2ND )
	{
		//	만다라 마을 서쪽숲
		if( m_iPortal_StartPortalID == 101 )
			m_iPortal_StartPortalID = 147;
		//	만다라 마을
		else if( m_iPortal_StartPortalID == 103 )
			m_iPortal_StartPortalID = 148;
		//	마라의 땅 입구
		else if( m_iPortal_StartPortalID == 104 )
			m_iPortal_StartPortalID = 149;
		//	격투장 가는 길
		else if( m_iPortal_StartPortalID == 105 )
			m_iPortal_StartPortalID = 150;
		//	마족마을우물
		else if( m_iPortal_StartPortalID == 131 )
			m_iPortal_StartPortalID = 151;


		//	만다라 마을 서쪽숲
		if( m_iPortal_TargetPortalID == 101 )
			m_iPortal_TargetPortalID = 147;
		//	만다라 마을
		else if( m_iPortal_TargetPortalID == 103 )
			m_iPortal_TargetPortalID = 148;
		//	마라의 땅 입구
		else if( m_iPortal_TargetPortalID == 104 )
			m_iPortal_TargetPortalID = 149;
		//	격투장 가는 길
		else if( m_iPortal_TargetPortalID == 105 )
			m_iPortal_TargetPortalID = 150;
		//	마족마을우물
		else if( m_iPortal_TargetPortalID == 131 )
			m_iPortal_TargetPortalID = 151;
	}

	if( g_wResentZoneServerID == ZONE_MANDARA3TH )
	{
		//	만다라 마을 서쪽숲
		if( m_iPortal_StartPortalID == 101 )
			m_iPortal_StartPortalID = 152;
		//	만다라 마을
		else if( m_iPortal_StartPortalID == 103 )
			m_iPortal_StartPortalID = 153;
		//	마라의 땅 입구
		else if( m_iPortal_StartPortalID == 104 )
			m_iPortal_StartPortalID = 154;
		//	격투장 가는 길
		else if( m_iPortal_StartPortalID == 105 )
			m_iPortal_StartPortalID = 155;
		//	마족마을우물
		else if( m_iPortal_StartPortalID == 131 )
			m_iPortal_StartPortalID = 156;


		//	만다라 마을 서쪽숲
		if( m_iPortal_TargetPortalID == 101 )
			m_iPortal_TargetPortalID = 152;
		//	만다라 마을
		else if( m_iPortal_TargetPortalID == 103 )
			m_iPortal_TargetPortalID = 153;
		//	마라의 땅 입구
		else if( m_iPortal_TargetPortalID == 104 )
			m_iPortal_TargetPortalID = 154;
		//	격투장 가는 길
		else if( m_iPortal_TargetPortalID == 105 )
			m_iPortal_TargetPortalID = 155;
		//	마족마을우물
		else if( m_iPortal_TargetPortalID == 131 )
			m_iPortal_TargetPortalID = 156;
	}
		

	info->wStartPortalID = m_iPortal_StartPortalID;
	info->wEndPortalID = g_wPotalID = m_iPortal_TargetPortalID;

	g_pNetWorkMgr->RequestReqMovePortal( info );

	// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_CSP_REQ_Portal : %d, %d", 
	//	info->wStartPortalID,  info->wEndPortalID);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
 
	//	캐릭터 이동못하게 셋팅
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );
}


//	서버에 포탈 요청에 대한 응답 받기 -> 전부 에러 메시지 일것임
HTvoid HTPortal::HT_vPortal_Network_SCP_Resp_Portal( PS_SCP_RESP_MOVE_PORTAL info )
{
	// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	CHTString strTemp;
	switch( info->byResult )
	{
		// 타존으로의 이동
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

			//	동접 체크
			HTint iConnectNum=0;
			
			if (g_poWebLogIn->HT_bGetServerStatusCheck())
				iConnectNum = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, byTempZone-1 );

			if( iConnectNum < CONNECTNUM_SERVERLIMIT )
			{
				g_wResentZoneServerID = byTempZone;
				//y.w.k
				//HSTLog("closelog1", ".\\Data\\[LOG]SERVER_CONNECTION.txt");
				//	현재 서버와 연결 끊음
				g_pNetWorkMgr->DisConnect();
			
				//	존서버 No, IP와 Port를 전역으로 저장
				g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
				g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
				//	서버와의 DisConnect Check Seting
				g_bPortalServerDisConnectCheckSw	= HT_FALSE;
				//	존 서버 커넥트를 기다리도록 설정
				g_bZoneServerSwitching = HT_TRUE;
				//	연결형태 셋팅
				g_byInitConnectType = CONNECT_TYPE_PORTAL;
			}
			else
			{
				// 접속하시려는 지역은 동접제한 인원이 초과하여 접속할수 없습니다. 잠시후 다시 이동해 주십시오.
				HT_vPortal_SetMessage( eMsgProtalExcessMember, &strTemp );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			}
		}
			break;
		// 이동할수 없는 상태
		case REPLY_MOVE_PORTAL_STATUS:
			// 현재 이동할수 없는 상태입니다.
			HT_vPortal_SetMessage( eMsgMoveCannotStatus, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// 이동시의 돈부족
		case REPLY_MOVE_PORTAL_WANTMONEY:
			// 루피아가 부족하여 이동할수 없습니다.
			HT_vPortal_SetMessage( eMsgPortalMoneyErr, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// 이동할수레벨
		case REPLY_MOVE_PORTAL_WANTLEVEL:
			// 현재 레벨로 이동할수 없는 지역입니다.
			HT_vPortal_SetMessage( eMsgPortalLevelErr, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
		// 기타 오류
		case REPLY_MOVE_PORTAL_FAIL:
			// 여러가지 이유로 이동할수 없습니다.
			HT_vPortal_SetMessage( eMsgPortalFail, &strTemp );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
			break;
	}

	//----------포탈이동----------//
	g_cMainCharacter->HT_vMainChar_SetCanMove();
}

//	서버에 칼라코어 등록 요청하기
HTvoid HTPortal::HT_vPortal_RegisterKalaCore( HTint iObjNo )
{
	MSG_REGISTER_KALA_CORE* info = HT_NULL;
	info = new MSG_REGISTER_KALA_CORE;

	// 칼라인지 포탈 번호를 이용하여 판별한다. 
	// 언제쯤 하드코딩을 벗어나서 데이터 의존적인 프로그램을 짤 수 있을까...
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send__MSG_REGISTER_KALA_CORE ID:%d", info->snID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	_MSG_Item
HTvoid HTPortal::HT_vPortal_NetWork_CSP_MSG_Item( HTint iIndex )
{
	//	만다라 지역 1120
	//	샴발라 지역
	if( iIndex == 0 )
	{
		//	JivaPustica For Three Mandara vilige
		if( m_iPortal_JiPusticaForMantraIndex == 0 )
		{
			if (!g_poWebLogIn->HT_bGetServerStatusCheck())
			{
				return;
			}

			//	세개의 만다라 마을이 떠 있는것을 체크
			HTint iConnectNum_1 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA1ST-1 );
			HTint iConnectNum_2 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA2ND-1 );
			HTint iConnectNum_3 = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, ZONE_MANDARA3TH-1 );
			//	일본과 대만 이외의 지역은 걍 넘어간다.
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

				//	포탈 이름 초기화
				g_cPortal->HT_vPortal_SetMessage( eMsgPortalSelectZone, &strTemp );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 3, strTemp.HT_szGetString() );
				for( HTint i=0 ; i<_GOING_PORTAL_NUM ; i++ )
				{
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10+i, _T("") );
				}
				// 첫번째 만다라
				// 만다라 1차지역_0
				this->HT_vPortal_SetMessage( eMsgPortalExtraMandara1, &strTemp );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 10, strTemp );
				g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 10, true);
				// 두번째 만다라
				if( iConnectNum_2 != -1 )
				{
					// 만다라 1차지역_1
					this->HT_vPortal_SetMessage( eMsgPortalExtraMandara2, &strTemp );
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_PORTALWND, 11, strTemp );
					g_cUIManager->HT_SetButtonEnable(_DIALOG_PORTALWND, 11, true);
				}
				// 세번째 만다라
				if( iConnectNum_3 != -1 )
				{
					// 만다라 1차지역_2
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
	//	샴발라 지역
	else if( iIndex == 1 )
	{
		if( g_cStatus->HT_byGetLevel() < 15 )
		{
			//	선미야 메시지 추가다.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 15부터 이용 할 수 있습니다.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1154;
	}
	//	지나 지역
	else if( iIndex == 2 )
	{
		if( g_cStatus->HT_byGetLevel() < 40 )
		{
			//	선미야 메시지 추가다.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 40부터 이용 할 수 있습니다.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1155;
	}
	//	유배지
	else if( iIndex == 3 )
	{
		if( g_cStatus->HT_byGetLevel() < 40 )
		{
			//	선미야 메시지 추가다.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 40부터 이용 할 수 있습니다.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}
		iIndex = 1156;
	}
	//	주신 지역 ( 브라흐마, 비슈느, 시바 )
	else if( iIndex == 4 )
	{
		if( g_cStatus->HT_byGetLevel() < 30 )
		{
			//	선미야 메시지 추가다.
			CHTString strMsg;
			strMsg.HT_szFormat("Level 30부터 이용 할 수 있습니다.");
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMsg );
			return;
		}

		if( g_iInationalType == INATIONALTYPE_KOREA ||
			g_iInationalType == INATIONALTYPE_CHINA ||
			g_iInationalType == INATIONALTYPE_JAPEN ||
			g_iInationalType == INATIONALTYPE_INDONESIA ||
			g_iInationalType == INATIONALTYPE_PHILIPPINE )
		{
			//	저랩 쿠루마
			if( g_cStatus->HT_byGetLevel()>=30 && g_cStatus->HT_byGetLevel()<=59 &&
				g_cUIStatus->HT_nGetTotalPureChakra() < 356 && g_cUISkillWindow->HT_nGetSkillPoint() < 64 )
			{
				if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			iIndex = 1337;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		iIndex = 1338;
				else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )		iIndex = 1339;
				else																return;
			}
			//	고랩 쿠루마
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

	//	이동의 푸스티가 사용시 이펙트 틀어주기
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	캐릭터 이동못하게 셋팅
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	info->byType = HT_MSG_ITEM_USE;
	//	Data Setting for MSG_Item
	info->byPlace = m_byPlace_ForMsgItem;
	info->byIndex = m_byIndex_ForMsgItem;
	info->snWarpID = iIndex;

	g_pNetWorkMgr->RequestItemUse( info );

	// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}

	
	// 창고창이 열려있다면 닫아준다.
	if( g_cUIManager ) g_cUIManager->HT_HideWindow( _DIALOG_GOODSKEEPWND );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Pustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//	_MSG_MoveOtherZone
HTvoid HTPortal::HT_vPortal_NetWork_SCP_MSG_MoveOtherZone( MSG_MoveOtherZone* info )
{ 
	HTbyte byTempZone;
	////	샴발라 지역
	//if( info->snPositionID == 1120 )
	//{
	//	byTempZone = 1;
	//}
	////	만다라 2
	//else if( info->snPositionID == 1216 )
	//{
	//	byTempZone = 18;
	//}
	////	만다라 3
	//else if( info->snPositionID == 1246 )
	//{
	//	byTempZone = 19;
	//}
	////	샴발라 지역
	//else if( info->snPositionID == 1154 )
	//{
	//	byTempZone = 2;
	//}
	////	지나 지역
	//else if( info->snPositionID == 1155 )
	//{
	//	byTempZone = 7;
	//}
	////	유배지
	//else if( info->snPositionID == 1156 )
	//{
	//	byTempZone = 9;
	//}
	////	고랩 주신 지역 ( 브라흐마, 비슈느, 시바 )
	//else if( info->snPositionID == 1158 || info->snPositionID == 1157 || info->snPositionID == 1159 )
	//{
	//	byTempZone = 10;
	//}
	////	저랩 주신 지역 ( 브라흐마, 비슈느, 시바 )
	//else if( info->snPositionID == 1337 || info->snPositionID == 1338 || info->snPositionID == 1339 )
	//{
	//	byTempZone = 20;
	//}
	//else
	//{
	//	return;
	//}

	// 만약 아이템 거래중에 포탈이동을 했다면 포탈창과 구입내역창을 닫아준다.
	if (g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) == true )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		g_cIndividualStore->HT_vIndividualStore_Close();
	}
		
	if( !g_pParamMgr->HT_bGetNPCZone( info->snPositionID, &byTempZone ) )
		return;

	//	동접 체크
	CHTString strTemp;
	HTint iConnectNum=0;
	
	if (g_poWebLogIn->HT_bGetServerStatusCheck())
		iConnectNum = this->HT_iPortal_GetConnectNum( g_iConnectServerGroupIndex+g_gServerType, byTempZone-1 );

	if( iConnectNum < CONNECTNUM_SERVERLIMIT )
	{
		g_wResentZoneServerID = byTempZone;
		//	현재 서버와 연결 끊음
		g_pNetWorkMgr->DisConnect();

		//	존서버 No, IP와 Port를 전역으로 저장
		g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
		g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
		//	서버와의 DisConnect Check Seting
		g_bPortalServerDisConnectCheckSw	= HT_FALSE;
		//	존 서버 커넥트를 기다리도록 설정
		g_bZoneServerSwitching = HT_TRUE;
		//	연결형태 셋팅
		g_byInitConnectType = CONNECT_TYPE_PUSTICA;
		//	Setting NPC ID
		g_wPotalID = info->snPositionID;
	}
	else
	{
		// 접속하시려는 지역은 동접제한 인원이 초과하여 접속할수 없습니다. 잠시후 다시 이동해 주십시오.
		HT_vPortal_SetMessage( eMsgProtalExcessMember, &strTemp );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
	}
}

//	MSG_Warp
HTvoid HTPortal::HT_vPortal_NetWork_SCP_Msg_Warp( MSG_Warp* info )
{
	g_wResentZoneServerID = info->dwPlace;
	//	현재 서버와 연결 끊음
	g_pNetWorkMgr->DisConnect();

	//	존서버 No, IP와 Port를 전역으로 저장
	g_strZoneServerIP = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].szWorldIP;
	g_iZoneServerPort = g_oWorldList[g_iConnectServerGroupIndex][g_wResentZoneServerID].snWorldPort;
	//	서버와의 DisConnect Check Seting
	g_bPortalServerDisConnectCheckSw	= HT_FALSE;
	//	존 서버 커넥트를 기다리도록 설정
	g_bZoneServerSwitching = HT_TRUE;
	//	연결형태 셋팅
	g_byInitConnectType = CONNECT_TYPE_GMRECALL;
	//	Setting NPC ID
	g_wPotalID = 0;
}

//	동접체크해오기
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
	
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vPortal_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vPortal_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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
		// 필요한 돈
		case eMsgParamNeedMoney	:	
		// 필요한 캐릭터 레벨
		case eMsgParamNeedLevel	:
			pszParam->HT_szFormat( "%d", m_dwMessageVal );
			break;
		
		// 지역 
		case eMsgParamZoneMandara1st:
			pszParam->HT_szFormat( "%d", 1 ); // 만다라 1차지역
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

	//	이동의 푸스티가 사용시 이펙트 틀어주기
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	캐릭터 이동못하게 셋팅
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

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_FortressPustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//	Set Siege Pustica
HTvoid HTPortal::HT_vPortal_SetSiegePustica( HTbyte byPlace, HTbyte byIndex )
{
	//	이동의 푸스티가 사용시 이펙트 틀어주기
	HTint iTempFXID;
	g_pEngineHandler->HT_hrStartSFX( &iTempFXID, HT_FX_MOVEPUSTICA, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	//	캐릭터 이동못하게 셋팅
	g_cMainCharacter->HT_vMainChar_SetCanNotMove( HT_FALSE );

	MSG_ITEM* info = HT_NULL;
	info = new MSG_ITEM;
	info->byType = HT_MSG_ITEM_USE;
	//	Data Setting for MSG_Item
	info->byPlace = byPlace;
	info->byIndex = byIndex;
	info->snWarpID = g_wPotalID = 223;
	g_pNetWorkMgr->RequestItemUse( info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_SiegePustica_Use : %d", info->snWarpID );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
