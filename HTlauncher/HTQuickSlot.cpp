#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTQuickSlot.h"

#define HT_COMMAND_QUICKSLOT_MINUS_INDEX		100
#define _SLOT_PREV	100
#define _SLOT_NEXT	101

#define UI_SLOTSTARTVALUE				10

typedef struct _HT_QUICKSLOT_DATA
{
	HTint	iInvenIndex;
	HTint	iIndex;
} _HT_QUICKSLOT_DATA;


HTQuickSlot::HTQuickSlot(void)
{
	m_bQuickSlot_Loaded		= HT_FALSE;
	
	m_bVerSlot				= true;
	m_iPrevSide					= 0;
	m_iSide						= 0;
	//	�ٸ� ���Կ��� �Ѿ���� �ؽ��� ���̵�
	m_iSlot_TextureID			= 0;
}

HTQuickSlot::~HTQuickSlot(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_HQUICKSLOT );
	g_cUIManager->HT_DeleteWindow( _DIALOG_WQUICKSLOT );
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vInit()
// D : ������ �޸� �ʱ�ȭ
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vInit()
{	
	//	Create Window
	this->HT_vQuick_CreateWindow();
	g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );

	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			ZeroMemory(&m_sQuickSlotInfo[i][j], sizeof (HTQuickSlotInfo));
			m_sQuickSlotInfo[i][j].iInvenIndex = -1;	// �������� ��� 0���� �����Ѵ�.

			m_dwQuickSlot_StartTimeCoolTime[i][j] = timeGetTime();
			m_fQuickSlot_CoolTime[i][j] = 0;
			m_bQuickSlot_ContinueSw[i][j] = 0;
		}
	}

	//	������ ����� ���� �ټ�
	m_iUsedItemCount = 0;

	//	Slot No
	m_iSlotNo = 0;

	//	For Continue Item
	for( i=0 ; i<10 ; i++ )
        m_iContinueItemKeyID[i] = 0;
	m_dwContinueItemUseDelay = timeGetTime();
}

//	Create Window
HTvoid HTQuickSlot::HT_vQuick_CreateWindow()
{
	HTint i;
	CHTString strTemp;

	//	[_DIALOG_WQUICKSLOT]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_WQUICKSLOT, _T(""), 440, 40, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	g_cUIManager->HT_MoveWindow( _DIALOG_WQUICKSLOT, 175, 0 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_WQUICKSLOT, TRUE, 0,0, 11,38 );
	//	��� ��
	g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 173, 0, 2 );
	//	�ϴ� ��
	g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 174, 402, 3 );
	//	�ϴ� ��ư(��)
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 5, 151, 402, 3, 152, 153 );
	//	�ϴ� ��ư(�Ʒ�)
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 6, 60, 402, 25, 61, 62 );
	//	��纯��
	g_cUIManager->HT_AddButtonControl( _DIALOG_WQUICKSLOT, 7, 57, 417, 10, 58, 59 );
	//	Slot Number
	g_cUIManager->HT_AddLabelControl( _DIALOG_WQUICKSLOT, 8, _T("1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 413, 5, 32, 32 );

	//	Loop
	for( i=0 ; i<10 ; i++ )
	{
		//g_cUIManager->HT_AddTextureControl( _DIALOG_WQUICKSLOT, 0, 172, 12+(i*39), 0 );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, 172, 14+(39*i), 2);
		g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, 4, 4);
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_WQUICKSLOT, UI_SLOTSTARTVALUE+i, HT_TRUE );
		//	Slot Sequence
		strTemp.HT_szFormat( "%d", i+1 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_WQUICKSLOT, 0, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 25+(39*i), 14, 32, 32 );
	}

		//	[_DIALOG_HQUICKSLOT]
	//	Window
	//g_cUIManager->HT_CreateWindow( 555, _T(""), 40, 440, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	//g_cUIManager->HT_WindowArrangement( 555, 7 );

	//	[_DIALOG_HQUICKSLOT]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_HQUICKSLOT, _T(""), 40, 440, g_cQuickSlot->HT_vQuick_InputCheckHQuickSlot, 0 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_HQUICKSLOT, 7 );
	g_cUIManager->HT_SetMovingRegion( _DIALOG_HQUICKSLOT, TRUE, 0,0, 38,11 );
	//	��� ��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 170, 1, 0 );
	//	�ϴ� ��
	g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 174, 0, 403 );
	//	�ϴ� ��ư(��)
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 1, 151, 0, 402, 152, 153 );
	//	�ϴ� ��ư(�Ʒ�)
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 2, 60, 0, 425, 61, 62 );
	//	��纯��
	g_cUIManager->HT_AddButtonControl( _DIALOG_HQUICKSLOT, 3, 57, 15, 409, 58, 59 );
	//	Slot Number
	g_cUIManager->HT_AddLabelControl( _DIALOG_HQUICKSLOT, 4, _T("1"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 11, 405, 32, 32 );

	//	Loop
	for( i=0 ; i<10 ; i++ )
	{
		//g_cUIManager->HT_AddTextureControl( _DIALOG_HQUICKSLOT, 0, 172, 0, 12+(i*39) );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, 172, 2, 14+(i*39));
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, HT_TRUE );
		g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_HQUICKSLOT, UI_SLOTSTARTVALUE+i, 4, 4);
		//	Slot Sequence
		strTemp.HT_szFormat( "%d", i+1 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_HQUICKSLOT, 0, strTemp.HT_szGetString(), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 14, 24+(i*39), 32, 32 );
	}
}

//	���_�Է��Լ� ó��
void HTQuickSlot::HT_vQuick_InputCheckHQuickSlot(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	�������� ��� ������ ���� Ŭ��������
		if( iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		//	�������� ��� ������ ��������� ���� ����
		else if( iTargetID == -1 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}

		if( iAction == UI_ACTION_MOUSE_LCLK )
		{
			if( iTargetID>=UI_SLOTSTARTVALUE && iTargetID<=UI_SLOTSTARTVALUE+10 )
			{
				//	control ��ư�� ������ �������� Delete
				if( GetAsyncKeyState( VK_CONTROL ) < 0 )
					g_cQuickSlot->HT_OnRButtonUp( iTargetID );
				else
                    g_cQuickSlot->HT_vAction( iTargetID-UI_SLOTSTARTVALUE );
			}
		}
		//else if( iAction == UI_ACTION_MOUSE_RCLK )
		//{
		//	g_cQuickSlot->HT_OnRButtonUp( iTargetID );
		//}
		else if( iAction == UI_ACTION_MOUSE_L_UP )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();

			unsigned int iWIndex, iCIndex;
			g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, g_cQuickSlot->m_iSlot_TextureID );

			//	�κ��丮���� �Ѿ�� �������϶�
			if( iWIndex == _DIALOG_EQUPINVENTORY || iWIndex == _DIALOG_INVENTORY2)
			{
				//	Item KeyID�� ������
				HTdword dwType = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation( iCIndex );
				//	PC�κ��丮 ���� �������� �̵� ����
				if( iCIndex>=100 && iCIndex<=200 )
					g_cQuickSlot->HT_bQuickSlot_SetSlot( dwType, g_cItemSystem->HT_dwSystem_GetItemIndex( dwType ), iTargetID-UI_SLOTSTARTVALUE );
			}
			//	��ų â���� �Ѿ�� ��ų�϶�
			else if( iWIndex == _DIALOG_SKILL )
			{
				HTdword dwSkillIndex = g_cUISkillWindow->HT_vGetSkillIndex( iCIndex );
				DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );
				if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE )
				{	
					CHTString str;
					HT_g_Script_SetMessage( eMsgSkillUsePassiveErr, &str, _T("") );		
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, str);
					return;
				}
				if( g_cUISkillWindow->HT_vGetSkillLevel(dwSkillIndex) <= 0 )
					return;

				g_cQuickSlot->HT_bQuickSlot_SetSlot( 0, g_cUISkillWindow->HT_vGetSkillIndex(iCIndex), iTargetID-UI_SLOTSTARTVALUE );
			}
			//	Ŀ�ǵ� â���� �Ѿ�� ����϶�
			else if( iWIndex == _DIALOG_COMMANDWND )
			{
				if( iCIndex > 0 && iCIndex < 100 )
					g_cQuickSlot->HT_bQuickSlot_SetSlot( -2, iCIndex, iTargetID-UI_SLOTSTARTVALUE );
			}
		}
	}
	else if( iTarget == UI_TARGET_BUTTON )
	{
		//	Button Up
		if( iTargetID == 1 || iTargetID == 5 )
		{
			g_cQuickSlot->HT_vSetSide( _SLOT_PREV );
		}
		//	Button Down
		else if( iTargetID == 2 || iTargetID == 6 )
		{
			g_cQuickSlot->HT_vSetSide( _SLOT_NEXT );
		}
		//	Button Down
		else if( iTargetID == 3 || iTargetID == 7 )
		{
			if( g_cUIManager->HT_isShowWindow( _DIALOG_HQUICKSLOT ) )
			{
				//	���� �κ��丮�� ��ġ�� ���ؿͼ� �ױ⿡ �˾��Ѵ�.
				g_cQuickSlot->m_bVerSlot = false;
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_HQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_MoveWindow( _DIALOG_WQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_HideWindow( _DIALOG_HQUICKSLOT );
				g_cUIManager->HT_ShowWindow( _DIALOG_WQUICKSLOT );
			}
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_WQUICKSLOT ) )
			{
				g_cQuickSlot->m_bVerSlot = true;
				HTint iPosX, iPosY;
				g_cUIManager->HT_GetWindowPos( _DIALOG_WQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_MoveWindow( _DIALOG_HQUICKSLOT, iPosX, iPosY );
				g_cUIManager->HT_HideWindow( _DIALOG_WQUICKSLOT );
				g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vIconSave()
// D : �����Կ� ��ϵǾ� �ִ� �������� �����Ͽ� ���� �α��� �� ����� �� �ֵ��� �Ѵ�.
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vIconSave()
{
	_HT_QUICKSLOT_DATA sBufferData;

	CHTString szFileName;
	szFileName.HT_szFormat("system\\QuickSlot_%d_%s.sys", g_iConnectServerGroupIndex, g_oMainCharacterInfo.szCharName );

	FILE*	fp;
	fp = fopen( szFileName.HT_szGetString(), "wb" );
	if (!fp) return;

	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			sBufferData.iIndex = m_sQuickSlotInfo[i][j].iIndex;
			sBufferData.iInvenIndex = m_sQuickSlotInfo[i][j].iInvenIndex;
			fwrite( &sBufferData, sizeof(_HT_QUICKSLOT_DATA), 1, fp);
		}
	}
	
	fclose(fp);
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vIconLoad()
// D : ����� ������ ������ �ε��Ѵ�.
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vIconLoad()
{
	if( m_bQuickSlot_Loaded )
	{
		// ��Ż ���� ������ ĳ���� ������ �ʱ�ȭ�� �� 
		HT_vQuickSlot_RenewalSlotItemKeyID();
		return;
	}
	
	CHTString szFileName;
	szFileName.HT_szFormat("system\\QuickSlot_%d_%s.sys", g_iConnectServerGroupIndex, g_oMainCharacterInfo.szCharName );

	m_bQuickSlot_Loaded = HT_TRUE;

	_HT_QUICKSLOT_DATA	sBufferData;

    FILE*	fp;
	fp = fopen( szFileName, "rb" );
	if (!fp) return;

	HTint iKeyID = 0;
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			fread(&sBufferData, sizeof(_HT_QUICKSLOT_DATA), 1, fp);
			iKeyID = 0;
			
			if( sBufferData.iIndex != 0 )
			{
				HT_Trace("HT_vQuickSlot_Load : [%d][%d]%d-%d\n", i, j, sBufferData.iIndex, sBufferData.iInvenIndex );

				//	Command/��ų/������ �ε��� ��
				//	Command	�϶��� �׳� �Ѿ
				if( sBufferData.iInvenIndex < -1 )
				{
					iKeyID = -2;
					m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
					m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
					m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
				}
				//	��ų�϶�
				else if( sBufferData.iInvenIndex == -1 )
				{
					iKeyID = 0;
					if( g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( sBufferData.iIndex ) > 0 )
					{
						m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
						m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
						m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
					}
				}
				//	�������϶�
				else if( sBufferData.iInvenIndex >= 0 )
				{
					BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, sBufferData.iInvenIndex, iKeyID );
					if( g_cItemSystem->HT_dwSystem_GetItemIndex( iKeyID ) == sBufferData.iIndex )
					{
						m_sQuickSlotInfo[i][j].iIndex = sBufferData.iIndex;
						m_sQuickSlotInfo[i][j].iKeyID = iKeyID;
						m_sQuickSlotInfo[i][j].iInvenIndex = sBufferData.iInvenIndex;
					}
				}
			}
		}
	}

	fclose(fp);

	//	���ٿ� ������ ����
	this->HT_vSetAllIcon();
}

// ���Կ� ��ϵǾ��ִ� �������� KeyID ������ �����Ѵ�.
HTvoid HTQuickSlot::HT_vQuickSlot_RenewalSlotItemKeyID()
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			// ��ϵ� �������� ������
			if( m_sQuickSlotInfo[i][j].iKeyID > 0 )	
			{
				BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, m_sQuickSlotInfo[i][j].iInvenIndex, m_sQuickSlotInfo[i][j].iKeyID );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iIndexID )
// D : �����Կ� ������ ���̱�
// I : iDlgNo - ���̾˷α� ��ȣ, iType - Ÿ��(-2 : ���, 0 : ��ų, ELSE : UI ITEM), 
//		iCellNo - ������ ��ȣ, iIndexID - �������� �ε���
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vAttachIcon( HTint iDlgNo, HTint iType, HTint iCellNo, HTint iTextureID )
{
	if( iTextureID > 0 )
	{
		//	Set Icon Image
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, iTextureID );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, iTextureID );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vSetAllIcon()
// D : ��� �������� ������ ���� �缳���Ѵ�. (������ ���� UI�� �����Ѵ�.)
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vSetAllIcon()
{
	for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
	{
		if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex < -1 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iIndex )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, m_sQuickSlotInfo[m_iSlotNo][j].iIndex );
		}
		else if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex == -1 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iIndex )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, g_cSkillSystem->HT_vSkillSystem_GetSkill_UIIconID( m_sQuickSlotInfo[m_iSlotNo][j].iIndex ) );
		}
		else if( m_sQuickSlotInfo[m_iSlotNo][j].iInvenIndex >= 0 )
		{
			if( m_sQuickSlotInfo[m_iSlotNo][j].iKeyID )
                this->HT_vAttachIcon( m_iSlotNo, m_sQuickSlotInfo[m_iSlotNo][j].iKeyID, j, g_cItemSystem->HT_iItemSystem_GetTextureIDFromKeyID( m_sQuickSlotInfo[m_iSlotNo][j].iKeyID ) );
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
// D : ������ ����
// I : iSideNo - ���ٹ�ȣ, iCellNo - �� ��ȣ
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vDeleteIcon( HTint iSideNo, HTint iCellNo )
{
	m_sQuickSlotInfo[iSideNo][iCellNo].iIndex = 0;
	m_sQuickSlotInfo[iSideNo][iCellNo].iKeyID = 0;
	m_sQuickSlotInfo[iSideNo][iCellNo].iInvenIndex = -1; // �������� ��� 0���� �����ϹǷ�

	//	Icon Image Delete
	if (m_iSide == iSideNo)
	{
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, 0 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, iCellNo+UI_SLOTSTARTVALUE, 0 );
	}

	//	���� �ð��� �����Ǿ� �ִٸ� �ʱ�ȭ
	m_bQuickSlot_ContinueSw[iSideNo][iCellNo] = HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vTotalDeleteIcon()
// D : ������ ���λ���
// I : iType - Ÿ��( -2:���, 0:��ų, 1:UI ITEM), 
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vTotalDeleteIcon( HTint iType )
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == iType )
                this->HT_vDeleteIcon( i, j );
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vTotalCoolTimeinit()
// D : ���� ���ư��� �ִ� ��Ÿ�ӵ� ���� �ʱ�ȭ
// I : 
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vTotalCoolTimeInit()
{
	for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT ; i++ )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; j++ )
		{
			//	���ӽð� ����
			m_bQuickSlot_ContinueSw[i][j] = HT_FALSE;
			//	��Ÿ�� ���۽ð� ����
			m_dwQuickSlot_StartTimeCoolTime[i][j] = 0;
			m_fQuickSlot_CoolTime[i][j] = 0;
		}
	}

	for( i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE );
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vDeleteIcon( HTdword dwIndex, HTint iKeyID )
// D : �����Կ� ������ ����
// I : dwIndex - �ε���, iKeyID - Ű ���̵�
//-------------------------------------------------------------------------------------------
HTbool HTQuickSlot::HT_vDeleteIconInResentSlotByIndex( HTdword dwIndex, HTint iKeyID )
{	
	// 2004. 6. 9 �߰�: ������ (��ų������ ��Ÿ�ӽð����� ���� ��ų�� �ٸ� ���ٿ��� ��� �� ���� �Ǵ� ���� �ذ�)
	// �ذ��� : ��� ���ٸ� �����Ͽ� �ش� ��ų�� ��Ÿ�� ���̶�� ������ �̵��� ��ҽ�Ų��.
	for( HTint j = 0 ; j < QUICKSLOT_SIDECOUNT ; ++j )
	{
		for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		{
			if( m_sQuickSlotInfo[j][i].iIndex == dwIndex && m_sQuickSlotInfo[j][i].iKeyID == iKeyID )
			{
				DWORD dwPassTime = timeGetTime();
				if(!(dwPassTime > m_dwQuickSlot_StartTimeCoolTime[j][i]+m_fQuickSlot_CoolTime[j][i]) )
					return HT_FALSE;
			}
		}
	}

	DWORD dwPassTime = timeGetTime();
	if(!(dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][m_iSlotNo]+m_fQuickSlot_CoolTime[m_iSide][m_iSlotNo]) )
		return HT_FALSE;

	// �� ���ٿ��� ��ø ��ų ������ ��� ���� ���� �� ����
	for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
	{
		if( m_sQuickSlotInfo[m_iSide][i].iIndex == dwIndex && m_sQuickSlotInfo[m_iSide][i].iKeyID == iKeyID )
		{
			this->HT_vDeleteIcon( m_iSide, i );
			return HT_TRUE;
		}
	}
	return HT_TRUE;
}

HTvoid HTQuickSlot::HT_vDeleteIconInAllSlotByIndex( HTdword dwIndex, HTint iKeyID )
{	
	for( HTint j = 0 ; j < QUICKSLOT_SIDECOUNT ; ++j )
	{
		for( HTint i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		{
			if( m_sQuickSlotInfo[j][i].iIndex == dwIndex && m_sQuickSlotInfo[j][i].iKeyID == iKeyID )
			{

				this->HT_vDeleteIcon( j, i );
				// �ٸ� â�� ���� �������� ��ϵǾ����� ��츦 ���ؼ� return ���� �ʴ´�.
				//return;
			}
		}
	}
}

//	�� ���� â üũ
HTvoid HTQuickSlot::HT_vQuickSlot_DlgCheck_LButton( HTPoint pPt, HTbool bVer )
{
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_OnRButtonUp( HTPoint pPt, HTint iDlgNo )
// D : ���콺 ������ ��ư�� �� �Ǿ��� ���
// I : pPt - ���콺 ��ǥ, iDlgNo - ���̾˷α� ��ȣ
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_OnRButtonUp( HTint iSlotNo )
{
	if( iSlotNo<UI_SLOTSTARTVALUE || m_iSlotNo>=(QUICKSLOT_HIGHT+UI_SLOTSTARTVALUE) ) return;

	// 2004. 6. 10 �߰�: ������ (��ų ������ ������߿� ������ ������û�� �����Ǵ� ���� ����)
	// �ذ��� : �����Ϸ��� ���ٰ� ����� �������� �����Ͽ� ����� ���̸� ������ ��ҽ�Ų��.
	DWORD dwPassTime = timeGetTime();
	DWORD aa = m_dwQuickSlot_StartTimeCoolTime[m_iSide][iSlotNo-QUICKSLOT_HIGHT]+(DWORD)m_fQuickSlot_CoolTime[m_iSide][iSlotNo-QUICKSLOT_HIGHT];
	if(!(dwPassTime > aa) )
		return;

	this->HT_vDeleteIcon( m_iSide, iSlotNo-UI_SLOTSTARTVALUE );
}

// ��ϵ� �������� KeyID �ٲٱ�
HTbool HTQuickSlot::HT_bChangeIconByKeyID( HTdword dwOldKeyID, HTdword dwNewKeyID )
{
	HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwNewKeyID );
	// �ٲ� KeyID�� �̹� �����Կ� ��ϵǾ����� ���
	if( this->HT_bBeUsedKeyID( dwIndex, dwNewKeyID ) )
	{
		// �ٸ� ����â�� ���� �������� ��ϵǾ����� ��츦 ���ؼ�
		this->HT_vDeleteIconInAllSlotByIndex( dwIndex, (HTint)dwOldKeyID );
		return HT_TRUE;
	}
	else
	{
		HTint iSideCount = 0, i = 0;
		// ��ϵ� �������� PC�κ��丮�� ��ġ�� �ٲ�� KeyID�� ����ȴ�
		for( iSideCount = 0 ; iSideCount < QUICKSLOT_SIDECOUNT ; ++iSideCount )
		{
			for( i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
			{
				if( m_sQuickSlotInfo[iSideCount][i].iKeyID == dwOldKeyID )
				{
					// ������ ��ġ ����
					HT_ITEMSETTING_FLAG sLocRoom;
					if( g_cItemSystem->HT_bItemSystem_GetItemPos( dwNewKeyID, sLocRoom ) )
					{
						m_sQuickSlotInfo[iSideCount][i].iInvenIndex = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
														+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
						m_sQuickSlotInfo[iSideCount][i].iKeyID = dwNewKeyID;

						m_dwQuickSlot_StartTimeCoolTime[iSideCount][i] = 0;
						m_fQuickSlot_CoolTime[iSideCount][i] = 0;
						// �ٸ� ����â�� ���� �������� ��ϵǾ����� ��츦 ���ؼ� return���� �ʴ´�.
						//return HT_TRUE;
					}
					else
						return HT_FALSE;
				}
			} // end of for( i = 0 ; i < QUICKSLOT_HIGHT ; ++i )
		} // end of for( iSideCount = 0 ; iSideCount < QUICKSLOT_SIDECOUNT ; ++iSideCount )
	}

	return HT_TRUE;
}

//------------ ��Ʈ��ũ �Լ� ------------------//
//	�������� �����Կ� ��� ��û
HTvoid HTQuickSlot::HT_vQuickSlot_ReqRegisterQuickSlot()
{
	//	�������� ������ �ȵǾ����� �ϴ� �ٷ� �����û�� �θ���.
	this->HT_vQuickSlot_ReqRegisterQuickSlot_Result();
}

//	�������� �����Կ� ��� ��û_���
HTvoid HTQuickSlot::HT_vQuickSlot_ReqRegisterQuickSlot_Result()
{
	// �̹� ��ϵ� ��ɾ�/��ų/�������� �ٽ� ����� ��� ������ ����� ���� �����
	if( m_iType == -2 ) // ��ɾ�
		this->HT_vDeleteIconInResentSlotByIndex( g_cCommand->HT_iCommand_GetBitmapImage(), m_iType );
	else				// ��ų/������
		if(this->HT_vDeleteIconInResentSlotByIndex( m_iIndexID, m_iType ) == HT_FALSE)
			return;

	//	Command�ϰ��
	if( m_iType == -2 )
	{
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iSlot_TextureID;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = ( m_iIndexID - HT_COMMAND_QUICKSLOT_MINUS_INDEX );
	}
	//	Skill�� ���
	else if( m_iType == 0 )
	{
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iIndexID;
		m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = -1;
	}
	//	Item�� ���
	else
	{
		HT_ITEMSETTING_FLAG sLocRoom;
		if( g_cItemSystem->HT_bItemSystem_GetItemPos( m_iType, sLocRoom ) )
		{
			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iInvenIndex = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
											+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);

			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iKeyID = m_iType;
			m_sQuickSlotInfo[m_iSide][m_iSlotNo].iIndex = m_iIndexID;
		}
	}

	//	�̹��� ����ֱ�
	this->HT_vAttachIcon( m_iSide, m_iType, m_iSlotNo, m_iSlot_TextureID );

	//	Save
	this->HT_vIconSave();
}

//------------------------------------------------------------
//		��ȯ����
//------------------------------------------------------------
//	���Կ� ������ ����
//	iType : -2:Command, 0:��ų, ?:ItemKeyID
HTvoid HTQuickSlot::HT_bQuickSlot_SetSlot( HTint iType, HTint iIndexID, HTint iSlotNo )
{
	//	�������϶� �Ҹ����� �˻�
	if( iType > 0 )
	{
		// ȭ���� ������ �Ҹ� �����۸� ��� ����, ����ȭ ������ ���Ե� ���� �����۵� üũ
		if( ( !CHTParamIDCheck::HT_bIsItemUsable( iIndexID ) && !CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndexID )) || 
			  CHTParamIDCheck::HT_bIsItemUsableArrow( iIndexID ) ) 
		{
			CHTString str;
			g_cUIManager->HT_SetScriptMessage( eMsgCommonNotRegistInQuickSlot, &str, _T(""), _T("") );	//	�����Կ� ��ϺҰ����� �������Դϴ�.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, str);
            return;
		}
	}

	m_iSlotNo			= iSlotNo;
	if( m_iSlotNo<0 || m_iSlotNo>=QUICKSLOT_HIGHT )
		return;

	m_iType			= iType;
	m_iIndexID		= iIndexID;

	//	�������� �����Կ� ��� ��û
	this->HT_vQuickSlot_ReqRegisterQuickSlot();
}
//	������ ������ ������
//HTbool HTQuickSlot::HT_bQuickSlot_GetSlot( HTint iSlotNo )
HTbool HTQuickSlot::HT_bBeUsedSlot( HTint iSlotNo )
{
	if( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex == 0 ) return HT_FALSE;
	return HT_TRUE;
}

//-------------------------------------------------------------------------
// HTbool			HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
// D : Ű���̵� ���ǰ� �ִ��� üũ
// I : dwIndex - �ε���, dwKeyID - Ű���̵�
//-------------------------------------------------------------------------
HTbool 
HTQuickSlot::HT_bBeUsedKeyID( HTdword dwIndex, HTdword dwKeyID )
{
	for( HTint i=0; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( HTint j=0; j<QUICKSLOT_HIGHT; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iIndex == dwIndex && m_sQuickSlotInfo[i][j].iKeyID == dwKeyID ) 
				return HT_TRUE;
		}
	}
 
	return HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vAction( HTint iSlotNo )
// D : ���Կ� ������ ����� ���
// I : iSlotNo - ���� ��ȣ
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vAction( HTint iSlotNo )
{
	//	1. ������ ������� �Ǵ�
	if( HT_FALSE==this->HT_bBeUsedSlot( iSlotNo ) )	return;

	//	��� ��û�� ������ ��ȣ ����
	m_iQuickSlot_ActionSlotNo = iSlotNo;

	// ���ٿ� ��ϵǾ� �ִ� ���� ������ ���� �б�
	switch(m_sQuickSlotInfo[m_iSide][iSlotNo].iKeyID)
	{
		case -2:
			//	OnChar Message Skip
			g_bSkipMessageOnChar = HT_TRUE;
            g_cCommand->HT_vCommand_SetQuickSlotCmdUse( m_sQuickSlotInfo[m_iSide][iSlotNo].iInvenIndex + HT_COMMAND_QUICKSLOT_MINUS_INDEX );
			break;
		case 0:
			this->HT_vActionskill( iSlotNo );
			break;
		default:
			{
				// �����Ϸ��� ���ٰ� ����� �������� �����Ͽ� ����� ���̸� ������ ��ҽ�Ų��.
				//	���� �������� ��� ( ����ȭ ������ )
				if( CHTParamIDCheck::HT_bIsItemChargeContinuance( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex ) )
				{
					this->HT_vActionItem( iSlotNo );
				}
				else
				{
					DWORD dwPassTime = timeGetTime();
					if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][iSlotNo]+m_fQuickSlot_CoolTime[m_iSide][iSlotNo] )
					{
						if( !g_cItemControl->HT_vItemControl_GetItemUseSw() )
							this->HT_vActionItem( iSlotNo );
					}
				}
			}
			break;
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vActionItem( HTint iSlotNo)
// D : ���Կ� �ִ� ������ ���
// I : iSlotNo - ���� ��ȣ
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vActionItem( HTint iSlotNo )
{
	int i, j;
	HTbool bContinueSw = HT_FALSE;
	HTint iKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo].iKeyID;

	for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == iKeyID )
			{
				if( m_bQuickSlot_ContinueSw[i][j] == HT_TRUE )
					bContinueSw = HT_TRUE;
			}
		}
	}

	//	���� �ð��� �����Ǿ� �ִٸ� �ʱ�ȭ�ϰ� ��ŵ
	if( bContinueSw == HT_TRUE )
	{
		//	���� ������ �ټ��� ����
		HTint iItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( iKeyID );
	
		//	�������� ���� ���� �������� ����
		if( iItemCount == -1 )
		{
			// �ٸ� ����â�� �Ȱ��� �������� ������� ��츦 ����
			this->HT_vDeleteIconInAllSlotByIndex( m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex, iKeyID );
			//	Save
			this->HT_vIconSave();
		}
		else
		{
			//	���� �ʱ�ȭ
			for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
			{
				for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
				{
					if( m_sQuickSlotInfo[i][j].iKeyID == iKeyID &&
						m_sQuickSlotInfo[i][j].iIndex == m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex )
					{
						g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, 0, 0 );
						g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, 0, 0 );
						m_bQuickSlot_ContinueSw[i][j] = HT_FALSE;	//	���ӽð� ����
						m_fQuickSlot_CoolTime[i][j] = 0;
						m_dwQuickSlot_StartTimeCoolTime[i][j] = 0;
					}
				}
			}
		}
	}
	//	���� �ð��� �����Ǿ� ���� �������� ��
	else
	{
		g_cItemControl->HT_hrItemControl_ItemUse( iKeyID );
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vResultActionItem( HTdword dwKeyID )
// D : ������ ����� ���
// I : dwKeyID - Ű���̵�
//-------------------------------------------------------------------------------------------
HTvoid 
HTQuickSlot::HT_vResultActionItem( HTdword dwKeyID )
{
	// �������� ��ϵ� ���� ��ġ�� �˻��Ѵ�.
	HTint iSlotSide = -1, iSlotNo = -1;
	if( !this->HT_bBeUsedKeyID( dwKeyID, &iSlotSide, &iSlotNo )  )
	{
		HT_Trace("\nHT_vQuickSlot_SetActionSlot_item_Result-%d(%d,%d)\n ", dwKeyID, iSlotSide, iSlotNo );
		return;
	}

	// ����� �������� ����
	HTint iIndexID = m_sQuickSlotInfo[iSlotSide][iSlotNo].iIndex;	
	HTint iKeyID = m_sQuickSlotInfo[iSlotSide][iSlotNo].iKeyID;

	//	���� ������ �ټ��� ����
	m_iUsedItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( iKeyID );

	//	���� �ð����� �ڵ����� �������� ����ߴ°�?
	if( m_bQuickSlot_ContinueSw[iSlotSide][iSlotNo] == HT_TRUE )
	{
		//	�������� ���� ���� �������� ����
		if( m_iUsedItemCount == -1 )
		{
			// �ٸ� ����â�� �Ȱ��� �������� ������� ��츦 ����
			this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
			//	Save
			this->HT_vIconSave();
		}
		return;
	}

	//	�������� ���������� ��ٿ�Ÿ�� ����
	if( m_iUsedItemCount > 0 )
        this->HT_hrSetCoolTime( 0x01, iIndexID, 1 );

	// ������ �������� ó������ ����
	if( m_iUsedItemCount > 0 )
		return;

	// ���� ����(�ε����� ����)�� �������� �κ��丮���� ã�Ƽ� �ٽ� ä���.
	HTdword dwFindKeyID = 0;		// ã�� �������� KeyID
	HT_ITEMSETTING_FLAG sLocRoom;	// ã�� �������� ��ġ
	g_cItemSystem->HT_vItemSystem_GetItemPos( iIndexID, iKeyID, ITEM_LOCATION_PC, dwFindKeyID, sLocRoom);
	//	���� �������� ��� ( ����ȭ ������ )
	if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndexID ) )
	{
		// �ٸ� ����â�� �Ȱ��� �������� ������� ��츦 ����
		this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
		//	Save
		this->HT_vIconSave();
	}
	// ��� �����Կ� ��ϵ��� ���� ���� ������ �������� ������
	else if( dwFindKeyID != 0 && this->HT_bBeUsedKeyID( iIndexID, dwFindKeyID ) == HT_FALSE )
	{
		//	�ٸ� ����â�� �Ȱ��� �������� ������� ��츦 ����
		this->HT_bChangeIconByKeyID( iKeyID, dwFindKeyID );
		//	��Ÿ�� �� ����
		this->HT_hrSetCoolTime( 0x01, iIndexID, 1 );
	}
	// �������� ��� ����Ͽ����Ƿ� ���� �����
	else
	{
		// �ٸ� ����â�� �Ȱ��� �������� ������� ��츦 ����
		this->HT_vDeleteIconInAllSlotByIndex( iIndexID, iKeyID );
		//	Save
		this->HT_vIconSave();
	}
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vActionskill( HTint iSlotNo)
// D : ���Կ� �ִ� ��ų���
// I : iSlotNo - ���� ��ȣ
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vActionskill( HTint iSlotNo )
{
	if( g_cMainCharacter->HT_nMainChar_GetResentHP() <= 0 )
		return;

	if( g_cMainCharacter->HT_iMainChar_GetAttack_Type() == MAINCHAR_ATTACKTYPE_SKILL )
	{
		return;
	}

	DWORD dwSkillIndex = m_sQuickSlotInfo[m_iSide][iSlotNo].iIndex;
	BYTE byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwSkillIndex );
	DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwSkillIndex );

	//	Ÿ�Ľ� ����Ʈ üũ
	HTint iReqTPPoint;
	g_pParamMgr->HT_bGetPCSkillCostTP( dwSkillIndex, byLevel, &iReqTPPoint );
	if( g_pMainBar->HT_iMainBar_GetCurTP() < iReqTPPoint )
	{
		//TapasPoint�� ���� ��ų�� ���� �����ϴ�.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgQuickSlotUseTPErr, &szMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return;
	}
	//	��Ÿ�� ī��Ʈ ����
	if( HT_FAILED( this->HT_hrIsCoolTimeOver() ) )
	{
		//CoolTime�� ������ �ɷȽ��ϴ�.
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgQuickSlotUseCoolTimeErr, &szMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return;
	}

	if( dwSkillUseType == HT_PCSKILLTYPE_ACTION )
	{
		//	�繫�ٹ� ��ų ����ص� �ųİ� �����
		if( dwSkillIndex == HT_SKILLINDEX_SAMUDABA )
		{
			g_cGameSystem->HT_vGameSystem_ReqAnswerUseSamudaba( 1, g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID(), 0, g_cSkillSystem->HT_vSkillSystem_GetSkillEffect1Param1( dwSkillIndex ) );
			return;
		}

		//----------�׼� ��ų ����----------//
		g_cMainCharacter->HT_vMainChar_SetActionSkill( dwSkillIndex );
	}
	else if( dwSkillUseType == HT_PCSKILLTYPE_ACTIVE )
	{
		//----------��Ƽ�� ��ų ����----------//
		g_cMainCharacter->HT_vMainChar_SetActiveSkill( dwSkillIndex );
	}
}

// �ش� ���Կ� ��ġ�� �������� KeyID�� ��ų�� Index�� �Ѱ��ش�
HTvoid HTQuickSlot::HT_vQuickSlot_GetKeyIDInSlot( HTint iSlotNo, HTint *piKeyID, HTbyte *pbyType )
{
	if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID != 0 )	
	{
		if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID == -2 )// ��ɾ�
		{
			*piKeyID =  m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iInvenIndex + HT_COMMAND_QUICKSLOT_MINUS_INDEX;
			*pbyType = _QUICKSLOT_TYPE_COMMAND;
		}
		else // ������
		{
			*piKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iKeyID;
			*pbyType = _QUICKSLOT_TYPE_ITEM;
		}
	}
	else if( m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iIndex != 0 )	// ��ų
	{
		*piKeyID = m_sQuickSlotInfo[m_iSide][iSlotNo-UI_SLOTSTARTVALUE].iIndex;
		*pbyType = _QUICKSLOT_TYPE_SKILL;
	}
	else
	{
		*piKeyID = 0;
		*pbyType = _QUICKSLOT_TYPE_NONE;
	}
}

//-------------------------------------------------------------------------------------------
// HTbool			HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
// D : ���� ��ϵǾ� �ִ� Ű���� üũ�ϰ�, ��ϵǾ� �ִ� Side�� ���� ��ȣ�� ����
// I : dwKeyID - Ű���̵�
// R : piSlotSide - ������ ��ȣ, piSlotNo - ���� ��ȣ
//-------------------------------------------------------------------------------------------
HTbool 
HTQuickSlot::HT_bBeUsedKeyID( HTdword dwKeyID, HTint* piSlotSide, HTint* piSlotNo )
{
	for( HTint i = 0 ; i < QUICKSLOT_SIDECOUNT ; ++i )
	{
		for( HTint j = 0 ; j < QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[i][j].iKeyID == dwKeyID )
			{	
				*piSlotSide = i;
				*piSlotNo = j;
				return HT_TRUE;
			}
		}
	}
	return HT_FALSE;
}

//-------------------------------------------------------------------------------------------
// HTvoid			HT_vSetSide( HTint iType )
// D : ���° �������� ������ ���ΰ� �����Ѵ�.
// I : iType - ������ ������ ( 100:--, 101:++, ��Ÿ:������ ��ȣ )
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vSetSide( HTint iType )
{
	//	Check Slot
	m_iPrevSide = m_iSide;
	switch(iType)
	{
		case _SLOT_PREV:	
			m_iSide--;			break;
		case _SLOT_NEXT:
			m_iSide++;			break;
		default:			
			m_iSide = iType;	break;
	}
	if( m_iSide < 0 )							m_iSide = QUICKSLOT_SIDECOUNT-1;
	else if( m_iSide >= QUICKSLOT_SIDECOUNT )	m_iSide = 0;

	//	Set Slot Number
	CHTString strTemp;
	strTemp.HT_szFormat( "%d", m_iSide+1 );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_HQUICKSLOT, 4, strTemp.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_WQUICKSLOT, 8, strTemp.HT_szGetString() );

	//	Icon Image Delete
	for( HTint i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		g_cUIManager->HT_SetSlotImage( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE+1, 0 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE+1, 0 );
	}

	//	������ �� ����
	for( i=0 ; i<QUICKSLOT_HIGHT ; i++ )
	{
		if( 0==m_sQuickSlotInfo[m_iSide][i].iIndex )
		{
			this->HT_vDeleteIcon( m_iSide, i );
		}
		else
		{
			if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex < -1 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, m_sQuickSlotInfo[m_iSide][i].iIndex );
			else if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex == -1 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, g_cSkillSystem->HT_vSkillSystem_GetSkill_UIIconID( m_sQuickSlotInfo[m_iSide][i].iIndex ) );
			else if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex >= 0 )
				this->HT_vAttachIcon( m_iSide, m_sQuickSlotInfo[m_iSide][i].iKeyID, i, g_pEngineHandler->HT_dwGetItemUIID( m_sQuickSlotInfo[m_iSide][i].iIndex ) );
		}
	}

	//	About Cool Time
	HTdword dwPassTime = timeGetTime();
	//	��Ÿ�� �缳��
	for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		if( m_sQuickSlotInfo[m_iSide][i].iIndex != 0 )
		{
			for( HTint j=0 ; j<5 ; j++ )
			{
				for( HTint k=0 ; k<QUICKSLOT_HIGHT ; k++ )
				{
					if( m_sQuickSlotInfo[m_iSide][i].iKeyID == m_sQuickSlotInfo[j][k].iKeyID &&
						m_sQuickSlotInfo[m_iSide][i].iIndex == m_sQuickSlotInfo[j][k].iIndex &&
						m_sQuickSlotInfo[m_iSide][i].iInvenIndex == m_sQuickSlotInfo[j][k].iInvenIndex &&
						dwPassTime < m_dwQuickSlot_StartTimeCoolTime[j][k]+m_fQuickSlot_CoolTime[j][k] )
					{
						m_fQuickSlot_CoolTime[m_iSide][i] = m_fQuickSlot_CoolTime[j][k];
						m_dwQuickSlot_StartTimeCoolTime[m_iSide][i] = m_dwQuickSlot_StartTimeCoolTime[j][k];
						m_bQuickSlot_ContinueSw[m_iSide][i] = m_bQuickSlot_ContinueSw[j][k];
					}
				}
			}
		}
	}
	//	������ ��Ÿ�� ���� ����
    for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		//	Set UI
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE );
		g_cUIManager->HT_SetSlotBoxCoolTimeCancel( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE );
	}
	//	������ ��Ÿ�� ����
	for (i=0; i<QUICKSLOT_HIGHT; i++)
	{
		//	���� �ð��� �����Ǿ� �������� üũ
		if( dwPassTime < m_dwQuickSlot_StartTimeCoolTime[m_iSide][i]+m_fQuickSlot_CoolTime[m_iSide][i] )
		{
			HTint iUsedItemCount;
			HTint iCoolTime;
			HTbool bContinue = HT_FALSE;
			HTdword dwTermTime = dwPassTime - m_dwQuickSlot_StartTimeCoolTime[m_iSide][i];
            if( m_sQuickSlotInfo[m_iSide][i].iInvenIndex >= 0 )
			{
				iUsedItemCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_sQuickSlotInfo[m_iSide][i].iKeyID );
				if( CHTParamIDCheck::HT_bIsItemChargeContinuance( m_sQuickSlotInfo[m_iSide][i].iIndex ) &&
					m_iUsedItemCount > 0 )
				{
					bContinue = HT_TRUE;
				}
			}

			//	������ ���� ��
            if( !bContinue)
			{
				//	Set UI
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][i], dwTermTime );
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][i], dwTermTime );
			}
			//	������ �ִ� ��
			else
			{
				//	���� �������� ���� �ð��� �ϵ� �ڵ��Ǿ� �ִ�.
				//	���� ������ �ټ��� �̿��Ͽ� ��ü ��Ÿ���� ����
				iCoolTime = 59000 * (iUsedItemCount+1);
				//	Set UI
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, i+UI_SLOTSTARTVALUE, iCoolTime, dwTermTime );
				g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, i+UI_SLOTSTARTVALUE, iCoolTime, dwTermTime );

			}
		}
	}
}

//-------------------------------------------------------------------------------------------
// HTRESULT		HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
// D : ����� ����
//-------------------------------------------------------------------------------------------
HTRESULT 
HTQuickSlot::HT_hrSetCoolTime( BYTE byType, HTint iIndex, BYTE byLevel )
{
	HTint	iCoolTime;
	HTbool	bContinue = HT_FALSE;
	if( byType == 0x01 )
	{
		g_pParamMgr->HT_bGetItemCoolDownTime( iIndex, &iCoolTime );

		//	���� �������� ��� ( ����ȭ ������ )
		if( CHTParamIDCheck::HT_bIsItemChargeContinuance( iIndex ) &&
			m_iUsedItemCount > 0 )
		{
			bContinue = HT_TRUE;
			//	���� �������� ���� �ð��� �ϵ� �ڵ��Ǿ� �ִ�.
			iCoolTime = 59000;
		}
	}
	else
	{
		g_pParamMgr->HT_bGetPCSkillCoolDownTime( iIndex, byLevel, &iCoolTime );
		// ���������� Ŭ���̾�Ʈ�� �������� 1.1�� ���Ѵ�. ���� �����ǵ��� �ؾ� �Ѵ�.
	}

	//	���� �뷱�� ����
	if( byType = 0x02 && iCoolTime != 59000 )
	{
		if( g_oMainCharacterInfo.snTribe == 4 || g_oMainCharacterInfo.snTribe == 8 )
		{
			float fChakraSoul = (HTfloat)g_cStatus->HT_nGetChakraSoul();
			if( fChakraSoul >= 500 )	fChakraSoul = 500;
			if( fChakraSoul>100 )
			{
				HTint iCurrectTime = (HTint)(iCoolTime*((fChakraSoul-100.0f)/800.0f));
				iCoolTime = iCoolTime - iCurrectTime;
				if( iCoolTime < 0 )
					iCoolTime = 0;
			}
		}
	}

	// ���� �������̳� ��ų�� ���� ���Կ� ��ϵ� �� ��Ÿ���� ���� ����ǵ��� �Ѵ�.	
	//for( HTint i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( HTint j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			if( m_sQuickSlotInfo[m_iSide][j].iIndex == iIndex )
			{
				//	������ ���� ������/��ų �� ���
				if( bContinue == HT_FALSE )
				{
					m_fQuickSlot_CoolTime[m_iSide][j] = (HTfloat)(iCoolTime);
					m_dwQuickSlot_StartTimeCoolTime[m_iSide][j] = timeGetTime();
					//	Set UI
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][j], 0 );
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, (HTdword)m_fQuickSlot_CoolTime[m_iSide][j], 0 );
				}
				else
				{
					//	���ӽð� ����
					m_bQuickSlot_ContinueSw[m_iSide][j] = HT_TRUE;
					//	������ 1���� ��Ÿ���� �̸� �����ϰ�
					m_fQuickSlot_CoolTime[m_iSide][j] = (HTfloat)(iCoolTime);
					//	���� ������ �ټ��� �̿��Ͽ� ��ü ��Ÿ���� ����
					iCoolTime = iCoolTime * (m_iUsedItemCount+1);
					m_dwQuickSlot_StartTimeCoolTime[m_iSide][j] = timeGetTime();
					//	Set UI
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_HQUICKSLOT, j+UI_SLOTSTARTVALUE, iCoolTime, 0 );
					g_cUIManager->HT_SetSlotBoxCoolTime( _DIALOG_WQUICKSLOT, j+UI_SLOTSTARTVALUE, iCoolTime, 0 );
				}
			}
		}
	}
	return HT_OK;
}

//-------------------------------------------------------------------------------------------
//	HTRESULT		HT_hrIsCoolTimeOver()
// D : ���� �����Ϸ��� ����ų ��� �������� ��Ÿ��üũ
// R : HT_OK - ��Ÿ�� �ʰ� ( ����� �� ���� )
//		HT_FAIL - ��Ÿ�� ���ʰ� ( ����� �� ���� )
//-------------------------------------------------------------------------------------------
HTRESULT 
HTQuickSlot::HT_hrIsCoolTimeOver()
{
	DWORD dwPassTime = timeGetTime();
	if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[m_iSide][m_iQuickSlot_ActionSlotNo]+m_fQuickSlot_CoolTime[m_iSide][m_iQuickSlot_ActionSlotNo] )
		return HT_OK;
	else
		return HT_FAIL;
}

//-------------------------------------------------------------------------------------------
// HTvoid		HT_hrContinueTimeCheck()
// D : ���ӽð��� ������ �����۵� üũ
//-------------------------------------------------------------------------------------------
HTvoid HTQuickSlot::HT_vContinueTimeCheck()
{
	HTint i,j;

	//	Get m_bPotionItemUse_Sw
	if( !g_cItemControl->HT_vItemControl_GetItemUseSw() )
	{
		//	For Continue Item
		for( i=0 ; i<10 ; i++ )
		{
			if( m_iContinueItemKeyID[i] != 0 )
			{
				//	������ ����� ��� ��û�Ѵ�.
				g_cItemControl->HT_hrItemControl_ItemUse( m_iContinueItemKeyID[i] );
				if( g_cItemControl->HT_vItemControl_GetItemUseSw() )
                    m_iContinueItemKeyID[i] = 0;
				return;
			}
		}
	}

	DWORD dwPassTime = timeGetTime();
	for( i=0 ; i<QUICKSLOT_SIDECOUNT; ++i )
	{
		for( j=0 ; j<QUICKSLOT_HIGHT ; ++j )
		{
			//	���� �ð��� �����Ǿ� �������� üũ
			if( m_bQuickSlot_ContinueSw[i][j] == HT_TRUE )
			{
				if( dwPassTime > m_dwQuickSlot_StartTimeCoolTime[i][j]+m_fQuickSlot_CoolTime[i][j] )
				{
					for( int k=0 ; k<10 ; k++ )
					{
						if( m_iContinueItemKeyID[k] == 0 && 
							m_iContinueItemKeyID[k] != m_sQuickSlotInfo[i][j].iKeyID )
						{
							m_iContinueItemKeyID[k] = m_sQuickSlotInfo[i][j].iKeyID;
							break;
						}
					}
					//g_cItemControl->HT_hrItemControl_ItemUse( m_sQuickSlotInfo[i][j].iKeyID );
					//	��Ÿ�� ������ �ٽ� ���� ���ش�.
					m_dwQuickSlot_StartTimeCoolTime[i][j] = dwPassTime;
					return;
				}
			}
		}
	}
}

