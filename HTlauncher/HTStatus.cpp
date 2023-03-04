#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htstatus.h"

HTStatus::HTStatus(void)
{
}

HTStatus::~HTStatus(void)
{
	g_cUIManager->HT_DeleteWindow(_DIALOG_BEAUTYSALON);
	g_cUIManager->HT_DeleteWindow(_DIALOG_BEAUTYSALON2);
	HT_DELETE( m_sStatus_CharParms );
}

HTvoid HTStatus::HT_vStatus_CleanUp()
{
}

HTvoid HTStatus::HT_vStatus_Init()
{
	//	Create Window
	this->HT_vStatus_CreateWindow();

	m_sStatus_CharParms = HT_NULL;
	m_sStatus_CharParms = new S_SCP_CHAR_PARAMS_CHANGE;

	//----------����â ����---------//
	m_bStatus_Active		= HT_FALSE;

	m_nCharacterHair = -1;   // ĳ���� ��� (���� �̿�� �̿�ø� ���)
	m_nCharacterFace = -1;	// ĳ���� ��
	m_nCharacterTribe = -1;	// ĳ���� ����

	//	Bye Tany
	m_iBuyTany = 0;;
	//	���� Ȱ��ȭ�� �̿�� ������
	m_iBeautyWndNo = 0;
}

//	Create Window
HTvoid HTStatus::HT_vStatus_CreateWindow()
{
	//	[_DIALOG_BEAUTYSALON]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_BEAUTYSALON, _T(""), 330, 267, g_cStatus->HT_vParty_InputCheckForBeautySalon, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_BEAUTYSALON, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_BEAUTYSALON, 0, 8, 3, 36, 1400, 323, 6 );
	//	Label �̿��
	g_cUIManager->HT_AddTextureControl( _DIALOG_BEAUTYSALON, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgBeautySalon, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//���չ̿��
	//	Label ��� ��Ÿ�� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgSelectHair, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 72, 150, 17 );//��Ÿ�� ����
	//	Label �� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgFaceHair4, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 112, 150, 17 );//�� ����
	//	Label �䱸Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgNeedTany, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 121, 163, 100, 14 );//�䱸Ÿ��
	//	Label ����Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgKeepTany, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 121, 184, 100, 14 );//����Ÿ��
	//	Label ���Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 1, eMsgFaceHair4, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 74, 92, 141, 14 );//���Ÿ��
	//	Label ��Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 2, eMsgFaceHair4, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 74, 132, 141, 14 );//��Ÿ��
	//	Label �䱸Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 163, 50, 14 );
	//	Label ����Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 184, 50, 14 );
	//	Button ��Ÿ�� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 1, 148, 58, 92, 149, 150 );
	//	Button ��Ÿ�� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 2, 145, 215, 92, 146, 147 );
	//	Button �� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 3, 148, 58, 132, 149, 150 );
	//	Button �� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 4, 145, 215, 132, 146, 147 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 5, 159, 42, 166, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgSexType, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 42, 166, 64, 19 );//����
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 6, 159, 56, 225, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 225, 64, 19 );//Ȯ��
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON, 7, 159, 157, 225, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 225, 64, 19 );//���

	//	[_DIALOG_BEAUTYSALON2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_BEAUTYSALON2, _T(""), 330, 267, g_cStatus->HT_vParty_InputCheckForBeautySalon, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_BEAUTYSALON2, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_BEAUTYSALON2, 0, 8, 3, 36, 1400, 323, 6 );
	//	Label �̿��
	g_cUIManager->HT_AddTextureControl( _DIALOG_BEAUTYSALON2, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgFaceHair0, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//�̿��
	//	Label ��� ��Ÿ�� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgSelectHair, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 72, 150, 17 );//��Ÿ�� ����
	//	Label �� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgSelectFace, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 112, 150, 17 );//�� ����
	//	Label �䱸Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgNeedTany, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 121, 163, 100, 14 );//�䱸Ÿ��
	//	Label ����Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgKeepTany, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 121, 184, 100, 14 );//����Ÿ��
	//	Label ���Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 1, eMsgFaceHair3, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 74, 92, 141, 14 );//���Ÿ��
	//	Label ��Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 2, eMsgFaceHair4, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 74, 132, 141, 14 );//��Ÿ��
	//	Label �䱸Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 163, 50, 14 );
	//	Label ����Ÿ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 184, 50, 14 );
	//	Button ��Ÿ�� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 1, 148, 58, 92, 149, 150 );
	//	Button ��Ÿ�� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 2, 145, 215, 92, 146, 147 );
	//	Button �� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 3, 148, 58, 132, 149, 150 );
	//	Button �� ���� ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 4, 145, 215, 132, 146, 147 );
	//	Button Ȯ��
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 6, 159, 56, 225, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BEAUTYSALON2, 6 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 225, 64, 19 );//Ȯ��
	//	Button ���
	g_cUIManager->HT_AddButtonControl( _DIALOG_BEAUTYSALON2, 7, 159, 157, 225, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BEAUTYSALON2, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BEAUTYSALON2, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 225, 64, 19 );//���
}

//	�Է� �޼��� ó��
//	Beauty Salon
void HTStatus::HT_vParty_InputCheckForBeautySalon(int iAction, int iTarget, int iTargetID)
{
    int iDlgNo;

	if( g_cUIManager->HT_isShowWindow(_DIALOG_BEAUTYSALON) )	iDlgNo = _DIALOG_BEAUTYSALON;
	else														iDlgNo = _DIALOG_BEAUTYSALON2;

	iDlgNo = g_cStatus->m_iBeautyWndNo;

	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow( iDlgNo );
			return;
		}
		if( iTargetID == 1 || iTargetID == 2 )
			g_cStatus->HT_vStatus_BeautyFace_MouseCheck( iTargetID );
		else if( iTargetID == 3 || iTargetID == 4 )
			g_cStatus->HT_vStatus_BeautyHear_MouseCheck( iTargetID );
		else if( iTargetID == 5 )
			g_cStatus->HT_vStatus_BeautyTribe_MouseCheck( iTargetID );
		else if( iTargetID == 6 )
		{
			if( iDlgNo == _DIALOG_BEAUTYSALON )
			{
				g_cStatus->HT_vStatus_BeautyOK_MouseCheck( g_cStatus->m_iBuyTany, iDlgNo );
			}
			else
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cStatus->m_dwBeautyItemKeyID, 0X01 );
				g_cNPCControl->m_nCash = 0;
				// �̿�� �̿���� �̿�ÿ� iBuyTany�� 0���� ������.
				g_cStatus->HT_vStatus_BeautyOK_MouseCheck( 0, iDlgNo );
			}
			g_cUIManager->HT_HideWindow( iDlgNo );
			return;
		}
		else if( iTargetID == 7 )
		{
			g_cStatus->m_nCharacterTribe = -1;		// ó������ �ʱ�ȭ
			g_cStatus->HT_vStatus_Beauty_Render( iDlgNo );
			g_cMainCharacter->HT_vMainChar_ChangeSexDelCre( g_cStatus->m_nCharacterTribe, g_cStatus->m_nCharacterHair, g_cStatus->m_nCharacterFace );
			g_cUIManager->HT_HideWindow( iDlgNo );
			return;
		}
	}

	//	���� ���� ��� �� ó��
	HTint	iHairTany = 0, iFaceTany = 0, iSexTany = 0;
	// Step 3) �̿�� ���� ���
	switch(g_cStatus->m_nCharacterTribe)
	{
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
			g_pParamMgr->HT_bGetItemCash(eItem_ChangeSex, &iSexTany );	// ������ȯ
			break;
		default:
			iSexTany = 0;
			break;
	}
	if (g_cStatus->m_nCharacterTribe == g_oMainCharacterInfo.snTribe) iSexTany = 0; // ���������� ������

	switch(g_cStatus->m_nCharacterHair)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:
			g_pParamMgr->HT_bGetItemCash(eItem_ChangeOldHair, &iHairTany );	// �������
			break;
		case 6:	case 7:	case 8:
			g_pParamMgr->HT_bGetItemCash(eItem_ChangeHair, &iHairTany );	// �ű����
			break;
		default:
			iHairTany = 0;
			break;
	}
	if (g_cStatus->m_nCharacterHair == g_oMainCharacterInfo.byHeadType) iHairTany = 0; // �������� ������

	switch(g_cStatus->m_nCharacterFace)
	{
		case 1:	case 2:	case 3:	case 4:	case 5:	
			g_pParamMgr->HT_bGetItemCash(eItem_ChangeOldFace, &iFaceTany );	// ������
			break;
		case 6:	case 7:	case 8:
			g_pParamMgr->HT_bGetItemCash(eItem_ChangeFace, &iFaceTany );	// �űԾ�
			break;
		default:
			iFaceTany = 0;
			break;
	}
	if (g_cStatus->m_nCharacterFace == g_oMainCharacterInfo.byFaceType) iFaceTany = 0; // �������� ������

	g_cStatus->m_iBuyTany = (iHairTany + iFaceTany + iSexTany);

	// Step 5) SET TEXT & RENDER
	g_cStatus->HT_vStatus_Beauty_Render(iDlgNo);
	
	CHTString strString;
	CHTString strName; 
	if (iDlgNo == _DIALOG_BEAUTYSALON)
	{
		strName.HT_szFormat( "%d", g_cStatus->m_iBuyTany );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BEAUTYSALON, 3, strName );
		strName.HT_szFormat( "%d", g_cNPCControl->HT_iNPCControl_GetCash() );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BEAUTYSALON, 4, strName );
	}
}

//---------����â Ȱ��ȭ üũ----------//
HTbool HTStatus::HT_bStatus_GetActive()
{
	return m_bStatus_Active;
}

//----------Ȱ��ȭ----------//
HTvoid HTStatus::HT_vStatus_ActiveSw()
{
	if( g_cUIManager->HT_isShowWindow( _DIALOG_STATUS ) )
	{
		HT_vStatus_SetAntiActive();
	}
	else
	{
		HT_vStatus_SetActive();
	}
}

//---------�ܺο��� ����_â����----------//
HTvoid HTStatus::HT_vStatus_SetActive()
{
	m_bStatus_Active = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_STATUS );
}

//---------�ܺο��� ����_â�ݱ�----------//
HTvoid HTStatus::HT_vStatus_SetAntiActive()
{
	m_bStatus_Active = HT_FALSE;
	g_cUIManager->HT_HideWindow( _DIALOG_STATUS );
}

//	ESC Key ������ â �����
HTvoid HTStatus::HT_vStatus_ESC_CloseWindow()
{
	//---------�ܺο��� ����_â�ݱ�----------//
	HT_vStatus_SetAntiActive();
}

//---------��ȯ �� �� ����----------//
HTvoid HTStatus::HT_vStatus_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	CHTString szOut1, szOut2, szOut3;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		// sParam1
		HT_vStatus_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vStatus_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vStatus_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		// sParam1
		HT_vStatus_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vStatus_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		// sParam1
		HT_vStatus_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid HTStatus::HT_vStatus_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	HTint iCast;

	switch( sParam )
	{
		// ī��Ʈ ���
		case eMsgParamCastGrade :
		{
			// ���������� ����� ī��Ʈ ����, �ؿܴ� ���� �������� ���� [Ű���� : ī��Ʈ]
			//if( g_iInationalType == INATIONALTYPE_KOREA )
				iCast = g_byteMainCharacterCaste + 1; //HT_iStatus_GetCastClass();
			//else
			//	iCast = HT_iStatus_GetCastClass();

			if( iCast == _CHARAC_CAST_SUDRA_3 || iCast == _CHARAC_CAST_VAISHA_3 || iCast == _CHARAC_CAST_KSHATRYA_3
				 || iCast == _CHARAC_CAST_BRAMAN_3 || iCast == _CHARAC_CAST_AVATARA_3 || iCast == _CHARAC_CAST_RESERVE_3 )
				*pszParam = _T("3");
			else if( iCast == _CHARAC_CAST_SUDRA_2 || iCast == _CHARAC_CAST_VAISHA_2 || iCast == _CHARAC_CAST_KSHATRYA_2
				 || iCast == _CHARAC_CAST_BRAMAN_2 || iCast == _CHARAC_CAST_AVATARA_2 || iCast == _CHARAC_CAST_RESERVE_2 )
				*pszParam = _T("2");
			else if( iCast == _CHARAC_CAST_SUDRA_1 || iCast == _CHARAC_CAST_VAISHA_1 || iCast == _CHARAC_CAST_KSHATRYA_1
				 || iCast == _CHARAC_CAST_BRAMAN_1 || iCast == _CHARAC_CAST_AVATARA_1 || iCast == _CHARAC_CAST_RESERVE_1 )
				*pszParam = _T("1");
			else
				*pszParam = _T("0");

		}
			break;
		default:
			break;
	}
}

// �ֽ� �̸�
CHTString HTStatus::HT_szStatus_GetTrimuriti()
{
	CHTString strTrimuriti;

	if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )			//strTrimuriti = _T("����帶");
		HT_vStatus_SetMessage( eMsgCommonTrimuritiBrahma, &strTrimuriti);
	else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )		//strTrimuriti = _T("�񽴴�");
		HT_vStatus_SetMessage( eMsgCommonTrimuritiVishunu, &strTrimuriti);
	else if( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )																	//strTrimuriti = _T("�ù�");
		HT_vStatus_SetMessage( eMsgCommonTrimuritiSiva, &strTrimuriti);
	else																//strString.HT_szFormat("����");
		HT_vStatus_SetMessage( eMsgCommonNone, &strTrimuriti);

	return strTrimuriti;
}

HTint HTStatus::HT_nGetChakraMuscle()
{
	return m_sStatus_CharInfo.krgChakra[1].snMuscle;
}

HTint HTStatus::HT_nGetChakraHeart()
{
	return m_sStatus_CharInfo.krgChakra[1].snHeart;
}

HTint HTStatus::HT_nGetChakraNerve()
{
	return m_sStatus_CharInfo.krgChakra[1].snNerves;
}

HTint HTStatus::HT_nGetChakraSoul()
{
	return m_sStatus_CharInfo.krgChakra[1].snMind;
}

HTbyte HTStatus::HT_byGetLevel()
{
	return m_sStatus_CharInfo.byLevel;
}

HTint HTStatus::HT_iGetKarmaPoint()
{
	return g_oMainCharacterInfo.snKarma;
}

HTint HTStatus::HT_nGetPureChakraMuscle()
{
	return m_sStatus_CharInfo.krgChakra[0].snMuscle;
}

HTint HTStatus::HT_nGetPureChakraHeart()
{
	return m_sStatus_CharInfo.krgChakra[0].snHeart;
}

HTint HTStatus::HT_nGetPureChakraNerve()
{
	return m_sStatus_CharInfo.krgChakra[0].snNerves;
}

HTint HTStatus::HT_nGetPureChakraSoul()
{
	return m_sStatus_CharInfo.krgChakra[0].snMind;
}

// ���� ���ϱ�
CHTString HTStatus::HT_szStatus_GetJobName()
{
	CHTString strString;

	if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL0 )
		HT_vStatus_SetMessage( eMsgCommonJobBasic, &strString);

	else if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL1 )
	{
		switch( g_oMainCharacterInfo.byClass2 )
		{
			case CLASS_SATVAN	: //strString.HT_szFormat("��Ʈ��");	break;
				HT_vStatus_SetMessage( eMsgCommonJobSatvan, &strString); break;
			case CLASS_DHVANTA	: //strString.HT_szFormat("���Ÿ");	break;
				HT_vStatus_SetMessage( eMsgCommonJobDhvanta, &strString); break;
			case CLASS_NIRVANA	: //strString.HT_szFormat("�ʹٳ�");	break;
				HT_vStatus_SetMessage( eMsgCommonJobNirvana, &strString); break;
			case CLASS_MANTRIKA	: //strString.HT_szFormat("��Ʈ��ī");	break;
				HT_vStatus_SetMessage( eMsgCommonJobMantrika, &strString); break;
			default				: //strString.HT_szFormat("����");	break;
				HT_vStatus_SetMessage( eMsgCommonNone, &strString); break;
		}
	}
	else // if( g_oMainCharacterInfo.byClass1 == CLASS_LEVEL2 )
	{
		switch( g_oMainCharacterInfo.byClass2 )
		{
			case CLASS_SATVAN1: // ��Ʈ��
				HT_vStatus_SetMessage( eMsgCommonJobSatvan1, &strString); break;
			case CLASS_SATVAN2: // �ٳ���
				HT_vStatus_SetMessage( eMsgCommonJobSatvan2, &strString); break;
			case CLASS_DHVANTA1: // ���Ÿ
				HT_vStatus_SetMessage( eMsgCommonJobDhvanta1, &strString); break;
			case CLASS_DHVANTA2: // ī����
				HT_vStatus_SetMessage( eMsgCommonJobDhvanta2, &strString); break;
			case CLASS_NIRVANA1: // ��ī����
				HT_vStatus_SetMessage( eMsgCommonJobNirvana1, &strString); break;
			case CLASS_NIRVANA2: // ���̵��
				HT_vStatus_SetMessage( eMsgCommonJobNirvana2, &strString); break;
			case CLASS_MANTRIKA1: // �ƺ�ī��
				HT_vStatus_SetMessage( eMsgCommonJobMantrika1, &strString); break;
			case CLASS_MANTRIKA2: // �縶��Ʈ
				HT_vStatus_SetMessage( eMsgCommonJobMantrika2, &strString); break;
			default: // ����
				HT_vStatus_SetMessage( eMsgCommonNone, &strString); break;
		}
	}

	return strString;
}

HTint HTStatus::HT_iStatus_GetJob1ForTribe()
{
	switch( g_oMainCharacterInfo.snTribe )
	{
		case HT_ID_CHARACTER_NAGA:
		case HT_ID_CHARACTER_KIMNARA:
			return CLASS_SATVAN;

		case HT_ID_CHARACTER_ASURA:
		case HT_ID_CHARACTER_RAKSHASA:
			return CLASS_DHVANTA;

		case HT_ID_CHARACTER_YAKSA:
		case HT_ID_CHARACTER_GANDHARVA:
			return CLASS_NIRVANA;

		case HT_ID_CHARACTER_DEVA:
		case HT_ID_CHARACTER_GARUDA:
			return CLASS_MANTRIKA;

		default:
			break;
	}

	return -1;
}

CHTString HTStatus::HT_szStatus_GetCastClass()
{ 
	CHTString strString;

	//if( g_iInationalType != INATIONALTYPE_KOREA )
	//{
	//	HTint iBrahmanPoint = g_oMainCharacterInfo.nBrahmanPoint;

	//	// �����
	//	if( iBrahmanPoint <= _CHARAC_CAST_SUDRA_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastSudra, &strString);
	//	// ���̻�
	//	else if ( _CHARAC_CAST_VAISHA_3_START	<= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastVaisha, &strString);
	//	// ũ��Ʈ����
	//	else if ( _CHARAC_CAST_KSHATRYA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastKshatrya, &strString);
	//	// ���
	//	else if ( _CHARAC_CAST_BRAMAN_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastBraman, &strString);
	//	// �ƹ�Ÿ��
	//	else if ( _CHARAC_CAST_AVATARA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastAvatara, &strString);
	//	// ����
	//	else if ( _CHARAC_CAST_RESERVE_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_1_END )
	//		HT_vStatus_SetMessage( eMsgCommonCastReserve, &strString);
	//	else
	//		HT_vStatus_SetMessage( eMsgCommonNone, &strString);
	//}
	//else
	//{
		// ��� ����� (������ ���� �����޴� ���) 2005. 1. 31 ������

		if (eTNCaste_Sudra3 <= g_byteMainCharacterCaste && eTNCaste_Sudra1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastSudra, &strString);
		else if (eTNCaste_Baisha3 <= g_byteMainCharacterCaste && eTNCaste_Baisha1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastVaisha, &strString);
		else if (eTNCaste_Cushatri3 <= g_byteMainCharacterCaste && eTNCaste_Cushatri1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastKshatrya, &strString);
		else if (eTNCaste_Braman3 <= g_byteMainCharacterCaste && eTNCaste_Braman1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastBraman, &strString);
		else if (eTNCaste_Avatara3 <= g_byteMainCharacterCaste && eTNCaste_Avatara1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastAvatara, &strString);
		else if (eTNCaste_MahaRaja3 <= g_byteMainCharacterCaste && eTNCaste_MahaRaja1 >= g_byteMainCharacterCaste)
			HT_vStatus_SetMessage( eMsgCommonCastReserve, &strString);
		else
			HT_vStatus_SetMessage( eMsgCommonNone, &strString);
	//}

	return strString;
}

HTint HTStatus::HT_iStatus_GetCastClass()
{
	HTint iBrahmanPoint = g_oMainCharacterInfo.nBrahmanPoint;
	// ����� 3��
	if( iBrahmanPoint <= _CHARAC_CAST_SUDRA_3_END )										
		return _CHARAC_CAST_SUDRA_3;
	// ����� 2��
	else if ( _CHARAC_CAST_SUDRA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_2_END )
		return _CHARAC_CAST_SUDRA_2;
	// ����� 1��
	else if ( _CHARAC_CAST_SUDRA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_SUDRA_1_END )
		return _CHARAC_CAST_SUDRA_1;
	// ���̻� 3��
	else if ( _CHARAC_CAST_VAISHA_3_START	<= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_3_END )
		return _CHARAC_CAST_VAISHA_3;
	// ���̻� 2��
	else if ( _CHARAC_CAST_VAISHA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_2_END )
		return _CHARAC_CAST_VAISHA_2;
	// ���̻� 1��
	else if ( _CHARAC_CAST_VAISHA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_VAISHA_1_END )
		return _CHARAC_CAST_VAISHA_1;
	// ũ��Ʈ���� 3��
	else if ( _CHARAC_CAST_KSHATRYA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_3_END )
		return _CHARAC_CAST_KSHATRYA_3;
	// ũ��Ʈ���� 2��
	else if ( _CHARAC_CAST_KSHATRYA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_2_END )
		return _CHARAC_CAST_KSHATRYA_2;
	// ũ��Ʈ���� 1��
	else if ( _CHARAC_CAST_KSHATRYA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_KSHATRYA_1_END )
		return _CHARAC_CAST_KSHATRYA_1;
	// ��� 3��
	else if ( _CHARAC_CAST_BRAMAN_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_3_END )
		return _CHARAC_CAST_BRAMAN_3;
	// ��� 2��
	else if ( _CHARAC_CAST_BRAMAN_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_2_END )
		return _CHARAC_CAST_BRAMAN_2;
	// ��� 1��
	else if ( _CHARAC_CAST_BRAMAN_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_BRAMAN_1_END )
		return _CHARAC_CAST_BRAMAN_1;
	// �ƹ�Ÿ�� 3��
	else if ( _CHARAC_CAST_AVATARA_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_3_END )
		return _CHARAC_CAST_AVATARA_3;
	// �ƹ�Ÿ�� 2��
	else if ( _CHARAC_CAST_AVATARA_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_2_END )
		return _CHARAC_CAST_AVATARA_2;
	// �ƹ�Ÿ�� 1��
	else if ( _CHARAC_CAST_AVATARA_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_AVATARA_1_END )
		return _CHARAC_CAST_AVATARA_1;
	// ���� 3��
	else if ( _CHARAC_CAST_RESERVE_3_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_3_END )
		return _CHARAC_CAST_RESERVE_3;
	// ���� 2��
	else if ( _CHARAC_CAST_RESERVE_2_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_2_END )
		return _CHARAC_CAST_RESERVE_2;
	// ���� 1��
	else if ( _CHARAC_CAST_RESERVE_1_START <= iBrahmanPoint && iBrahmanPoint <= _CHARAC_CAST_RESERVE_1_END )
		return _CHARAC_CAST_RESERVE_1;
	
	else
		return _CHARAC_CAST_NONE;
}

//----------��Ʈ�� ��� �κ�----------//
//----------ü���� �Ķ��Ÿ----------//
HTvoid HTStatus::HT_vStatus_ChangeParams( PS_SCP_CHAR_PARAMS_CHANGE info )
{
	memcpy( m_sStatus_CharParms, info, sizeof(S_SCP_CHAR_PARAMS_CHANGE) );
	m_nStatus_ChakraPoint = m_sStatus_CharParms->snChakraMuscle+m_sStatus_CharParms->snChakraHeart+m_sStatus_CharParms->snChakraNerve+m_sStatus_CharParms->snChakraSoul;
	//---------��������â ����---------//
	//	g_pMainBar->HT_vSetNextChakra(0);
	
	if( g_cUIManager->HT_isShowWindow(_DIALOG_GOODSKEEPWND) == HT_TRUE )
	{
		g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPWND);
	}
}

HTvoid HTStatus::HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info )
{
	m_sStatus_CharInfo.iTitle = info->iTitle;				// Title
	m_sStatus_CharInfo.snCPRemaining = info->snCPRemaining;	// ���� ��ũ�� ����Ʈ

	// 0:base chakra, 1:changed chakra
	HTbool bChange = HT_FALSE;	// ��ũ�� or Level �� ����ƴ��� �˻�
	// Level
	m_sStatus_CharInfo.byLevel = info->byLevel;      // �� Level
	
	// ����
	if( info->krgChakra[0].snMuscle != m_sStatus_CharInfo.krgChakra[0].snMuscle )
		bChange = HT_TRUE;
	m_sStatus_CharInfo.krgChakra[0].snMuscle = info->krgChakra[0].snMuscle;
	// �Ű�
	if( info->krgChakra[0].snNerves != m_sStatus_CharInfo.krgChakra[0].snNerves )
		bChange = HT_TRUE;
	m_sStatus_CharInfo.krgChakra[0].snNerves = info->krgChakra[0].snNerves; 
	// ����
	if( info->krgChakra[0].snHeart != m_sStatus_CharInfo.krgChakra[0].snHeart )
		bChange = HT_TRUE;
	m_sStatus_CharInfo.krgChakra[0].snHeart	 = info->krgChakra[0].snHeart; 
	// ����
	if( info->krgChakra[0].snMind != m_sStatus_CharInfo.krgChakra[0].snMind )
		bChange = HT_TRUE;
	m_sStatus_CharInfo.krgChakra[0].snMind	 = info->krgChakra[0].snMind; 
	//	íũ�� �ø��� ����Ʈ
	if( bChange == HT_TRUE )
	{
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CHAKRAUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
		// ���� �̺�Ʈ�� ���� �˸�â ����
		//g_cNPCControl->HT_vNPCControl_SetCouponNotifyMessage( m_sStatus_CharInfo.byLevel );
	}

	m_sStatus_CharInfo.krgChakra[1].snMuscle = info->krgChakra[1].snMuscle; 
	m_sStatus_CharInfo.krgChakra[1].snNerves = info->krgChakra[1].snNerves; 
	m_sStatus_CharInfo.krgChakra[1].snHeart	 = info->krgChakra[1].snHeart; 
	m_sStatus_CharInfo.krgChakra[1].snMind	 = info->krgChakra[1].snMind; 
	m_sStatus_CharInfo.snAC = info->snAC;         // AC
	m_sStatus_CharInfo.snAttackRate = info->snAttackRate; // Attack Rate
	m_sStatus_CharInfo.snDodgeRate = info->snDodgeRate;  // Dodge Rate
	// ����
	m_sStatus_CharInfo.kResist.snCold		= info->kResist.snCold;     
	m_sStatus_CharInfo.kResist.snFire		= info->kResist.snFire;
	m_sStatus_CharInfo.kResist.snLightning  = info->kResist.snLightning;
	m_sStatus_CharInfo.kResist.snPoison		= info->kResist.snPoison;

	m_sStatus_CharInfo.kDamage.iMin = info->kDamage.iMin;
	m_sStatus_CharInfo.kDamage.iMax = info->kDamage.iMax;
	m_sStatus_CharInfo.kDamage.iFire = info->kDamage.iFire;
	m_sStatus_CharInfo.kDamage.iCold = info->kDamage.iCold;
	m_sStatus_CharInfo.kDamage.iLightning = info->kDamage.iLightning;
	m_sStatus_CharInfo.kDamage.iPoison = info->kDamage.iPoison;

	// Prana, BrahmanPoint, snAttackRate, snDodgeRate
	g_oMainCharacterInfo.nBrahmanPoint = info->iBramanPoint;
	//g_oMainCharacterInfo.nPrana = info->iPrana;

	// �κ��丮 â�� ���� �ִٸ� ����Ұ��ɹ� ����
	if( g_cUIManager->HT_isShowWindow(_DIALOG_GOODSKEEPWND) == HT_TRUE )
	{
		g_cItemSystem->HT_vItemSystem_RenewalPossibleBar(_DIALOG_GOODSKEEPWND);
	}
}

HTvoid HTStatus::HT_vStatus_SetChakra_Rising( PS_SCP_RESP_CHAKRA_RISING info )
{
	g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->nPrana );
	
	m_nStatus_ChakraPoint					= info->nChakraPoint;
	m_sStatus_CharParms->snChakraMuscle		= info->snChakraMuscle;
	m_sStatus_CharParms->snChakraHeart		= info->snChakraHeart;
	m_sStatus_CharParms->snChakraNerve		= info->snChakraNerve;
	m_sStatus_CharParms->snChakraSoul		= info->snChakraSoul;

	g_pMainBar->HT_vHPUpdate(g_cMainCharacter->HT_nMainChar_GetResentHP(), g_cMainCharacter->HT_nMainChar_GetMAXHP() );
}

//	Network	LevelUp Brodcast
HTvoid HTStatus::HT_vStatus_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info )
{
	HTint idFx;
	g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_CHAKRAUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
}

// �̿�� ������ ���� ����
HTvoid HTStatus::HT_vStatus_Beauty_Render(HTint iDlgNo)
{
	// Step 1) ó�� ����� ĳ���� �⺻ �������� ����
	if (m_nCharacterTribe == -1) 
	{
		m_iBuyTany = 0;

		m_nCharacterHair = g_oMainCharacterInfo.byHeadType;
		m_nCharacterFace = g_oMainCharacterInfo.byFaceType;
		m_nCharacterTribe = g_oMainCharacterInfo.snTribe;
	}

	CHTString strString;
	CHTString strName; 

	// SET TEXT & RENDER
	if (m_nCharacterHair == g_oMainCharacterInfo.byHeadType) 
	{
		HT_vStatus_SetMessage( eMsgFaceHair1, &strName);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, strName );
	}
	else
	{
		HT_vStatus_SetMessage( eMsgFaceHair3, &strName);
		strString.HT_szFormat("%s %d", strName.HT_szGetString(), m_nCharacterHair);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, strString );
	}
	
	if (m_nCharacterFace == g_oMainCharacterInfo.byFaceType) 
	{
		HT_vStatus_SetMessage( eMsgFaceHair2, &strName);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, strName );
	}
	else
	{
		HT_vStatus_SetMessage( eMsgFaceHair4, &strName);
		strString.HT_szFormat("%s %d", strName.HT_szGetString(), m_nCharacterFace);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, strString );
	}

	//	Bye Tany
	//m_iBuyTany = 0;
	//	���� Ȱ��ȭ�� �̿�� ������
	m_iBeautyWndNo = iDlgNo;
}


//	MainChar BeautyFace
HTvoid HTStatus::HT_vStatus_BeautyFace_MouseCheck( HTint iButtonNo )
{
	if (iButtonNo == 1)	// ��Ÿ�� ���� << ��ư
	{
		if ( --m_nCharacterHair < 1 )
		{
			if( m_nCharacterTribe == 1 )
				m_nCharacterHair = 7;
			else
                m_nCharacterHair = 8;
		}
	}
	else if (iButtonNo == 2)	// ��Ÿ�� ���� >> ��ư
	{
		if( m_nCharacterTribe == 1 )
		{
			if ( ++m_nCharacterHair > 7 ) m_nCharacterHair = 1;
		}
		else
		{
			if ( ++m_nCharacterHair > 8 ) m_nCharacterHair = 1;
		}
	}

	g_pEngineHandler->HT_hrChangeHead( g_cMainCharacter->m_iMainChar_ModelID, m_nCharacterTribe, m_nCharacterHair, m_nCharacterFace);
}

//	MainChar BeautyHear
HTvoid HTStatus::HT_vStatus_BeautyHear_MouseCheck( HTint iButtonNo )
{
	if (iButtonNo == 3)	// �󱼺��� << ��ư
	{
		if ( --m_nCharacterFace < 1 ) m_nCharacterFace = 8;
	}
	else if (iButtonNo == 4)	// �󱼺��� >> ��ư
	{
		if ( ++m_nCharacterFace > 8 ) m_nCharacterFace = 1;
	}

	g_pEngineHandler->HT_hrChangeHead( g_cMainCharacter->m_iMainChar_ModelID, m_nCharacterTribe, m_nCharacterHair, m_nCharacterFace);
}

//	MainChar BeautyTribe
HTvoid HTStatus::HT_vStatus_BeautyTribe_MouseCheck( HTint iButtonNo )
{
	// ���� ��ȯ��
	if ( m_nCharacterTribe >= 1 && m_nCharacterTribe <= 4 ) m_nCharacterTribe = m_nCharacterTribe + 4;
	else if ( m_nCharacterTribe >= 5 && m_nCharacterTribe <= 8 ) m_nCharacterTribe = m_nCharacterTribe - 4;
	else m_nCharacterTribe = m_nCharacterTribe; // GM

	//	Set Change Sex
	g_cMainCharacter->HT_vMainChar_ChangeSexDelCre( m_nCharacterTribe, m_nCharacterHair, m_nCharacterFace );

	//	Set Equip
	g_cItemSystem->HT_vItemSyste_TribeEquipItemReEquip( m_nCharacterTribe );
	//for( HTint i = 0; i < 7 ; ++i )
	//	g_pEngineHandler->HT_hrEquipItem( g_cMainCharacter->m_iMainChar_ModelID, m_nCharacterTribe, g_oMainCharacterInfo.Equip[i].snIndex );

	//	��� ��ũ ǥ�� �ϱ�
	g_cGuildSystem->HT_vGuild_EmblemOn();
	//	�ֽ� ��ũ ǥ�� �ϱ�
	g_cGuildSystem->HT_vTrimutiri_MarkOn();
}

//	MainChar BeautyOK
HTvoid HTStatus::HT_vStatus_BeautyOK_MouseCheck( HTint iBuyTany, HTint iDlgNo )
{
	HTint iTany = g_cNPCControl->HT_iNPCControl_GetCash();

    // ���� ������ �� �ִ� ����� Ÿ�ϰ� ������ ��Ȯ��â ���
	// �׷��� ������ â�� �ݰ� Ÿ�ϰ� �����ϴٴ� �����޽��� ���
	if (iBuyTany > iTany)
	{
		// �ý��� â�� ǥ��
		CHTString strName;
		HT_vStatus_SetMessage( eMsgItemCommonCashErr, &strName);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strName );

		//	MainChar BeautyBack
		this->HT_vStatus_BeautyBack();
	}
	else
	{
		this->HT_vStatus_NetworkReqBeauty();
	}
}

//	MainChar BeautyBack
HTvoid HTStatus::HT_vStatus_BeautyBack()
{
	// ���� ���·� �ǵ���
	m_nCharacterTribe = -1;

	//	Set Change Sex
	g_cMainCharacter->HT_vMainChar_ChangeSexDelCre( g_oMainCharacterInfo.snTribe, g_oMainCharacterInfo.byHeadType, g_oMainCharacterInfo.byFaceType );

	//	Set Equip
	g_cItemSystem->HT_vItemSyste_TribeEquipItemReEquip( g_oMainCharacterInfo.snTribe );

	//for( HTint i = 0; i < 7 ; ++i )
	//	g_pEngineHandler->HT_hrEquipItem( g_cMainCharacter->m_iMainChar_ModelID, g_oMainCharacterInfo.snTribe, g_oMainCharacterInfo.Equip[i].snIndex );

	//	��� ��ũ ǥ�� �ϱ�
	g_cGuildSystem->HT_vGuild_EmblemOn();
	//	�ֽ� ��ũ ǥ�� �ϱ�
	g_cGuildSystem->HT_vTrimutiri_MarkOn();
}

//	MainChar Request Beauty
HTvoid HTStatus::HT_vStatus_NetworkReqBeauty()
{
	MSG_Beauty* info;
	info = new MSG_Beauty;
	memset( info, 0, sizeof( MSG_Beauty ) );

	info->byFace = m_nCharacterFace;
	info->byHead = m_nCharacterHair;
	info->snTribe = g_byCharacterServerTribe[m_nCharacterTribe-1];

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send: %d,%d,%d", info->byFace, info->byHead, info->snTribe );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	g_pNetWorkMgr->RequestMsgBeauty( info );

	HT_DELETE( info );
}

//	MainChar Recive Beauty
HTvoid HTStatus::HT_vStatus_NetworkReciveBeauty( MSG_Beauty* info )
{
	if( info->byResult == 0 )
	{
		CHTString strName;
		HT_vStatus_SetMessage( eMsgPremiumReqResultOKay, &strName);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, strName );

		g_oMainCharacterInfo.byHeadType = m_nCharacterHair;
		g_oMainCharacterInfo.byFaceType = m_nCharacterFace;
		g_oMainCharacterInfo.snTribe = m_nCharacterTribe;

		//	MainChar BeautyBack
		this->HT_vStatus_BeautyBack();
	}
	else
	{
		//	MainChar BeautyBack
		this->HT_vStatus_BeautyBack();
	}
}
