#include "stdafx.h"
#include "HTRefine.h"

/*
//
// CHTUIRefineWindow Class �ɹ� �Լ��� ��Ƴ��ҽ��ϴ�.
//

CHTUIRefineWindow::CHTUIRefineWindow() {}
CHTUIRefineWindow::~CHTUIRefineWindow() {}

// ����â�� �����մϴ�.
void CHTUIRefineWindow::HT_vRefineWindow_Init()
{
	// ������ ����
	g_cUIManager->HT_CreateWindow(UI_WINDOW_REFINE, _T("Refine"), 330, 238, g_cUIRefineWindow->HT_hrRefineWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_REFINE, 5);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 3, 37, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 39, 31, 1400, 89, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTitle, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 39, 31, 89, 19);//��      ��
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 129, 37, 1400, 198, 6);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 56, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTargetItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 56, 152, 19);//���� ��� ������

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 122, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 122, 152, 19);//���� ���

	// �ٸ�ź �ؽ�ó �ִϸ��̼� 74- 79
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59);
	g_cUIManager->HT_AddTimerControl(UI_WINDOW_REFINE, 1, 100);
	g_cUIManager->HT_EnableOnTimerControl(UI_WINDOW_REFINE, 1);

	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE,1, 31 ,17, 59);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 16, 164, 1400, 130, 18);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 164, 58, 19);//���Ǿ�

	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 1, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 71, 164, 59, 19);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_REFINE, 1, 5);

	// ���� ���� �߰� 62
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,1, 66 ,205, 81);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 1, 2, 2);

	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,2, 66 ,168, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 2, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,3, 66 ,205, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 3, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,4, 66 ,242, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 4, 2, 2);

	// ��ư 99, 97, 98
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 1,  159, 56, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 56, 201, 64, 19);//Ȯ     ��
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 2,  159, 156, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 156, 201, 64, 19);//��     ��

	m_iRefineAniNo = 0;
	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;
	g_cUIRefineWindow->m_iWindowIndex[4] = 0;
}

// ������ ���� ���Ž� ȣ�� (�̰����� UI Widnow�� ��Ʈ�� ������ ���� �� ��ġ�� �Ѵ�.)
void CHTUIRefineWindow::HT_vRefineWindow_SetInfo()
{

}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIRefineWindow::HT_vRefineWindow_WindowPopup()
{
}

// �ܺο��� ��� (�� �������� Ŭ������ UI�޴����� ���ٸ� �ǹ̾���)
void CHTUIRefineWindow::HT_vRefineWindow_WindowHide()
{
	for (int i = 1; i < 4; ++i)
	{
		g_cUIManager->HT_SetSlotBoxControlEnable(m_iWindowIndex[i], m_iControlIndex[i], true);
	}

	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;

	g_cUIManager->HT_HideWindow( UI_WINDOW_REFINE );
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void CHTUIRefineWindow::HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
		case 2:	// ��ҹ�ư
			// ����â ���� �ִ� ������ �̹����� �����
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Delete();
			g_cNPCControl->m_iResent = 0;
			g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
			break;
		case 1:	// Ȯ�ι�ư
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Ok();
			//g_cUIManager->HT_HideWindow(UI_WINDOW_REFINE);
			break;
    	}
		break;
	case UI_TARGET_TIMER:	// Ÿ�̸�
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_REFINE, 99); 

		switch(g_cUIRefineWindow->m_iRefineAniNo)
		{
			case 0: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
			case 1: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 2: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 3: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 4: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 5: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 79 ,17, 59); break;
			case 6: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 7: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 8: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 9: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 10: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 11: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
		}

		g_cUIRefineWindow->m_iRefineAniNo++;
		if (g_cUIRefineWindow->m_iRefineAniNo > 11) g_cUIRefineWindow->m_iRefineAniNo = 0;
		break;
	case UI_TARGET_MESSAGEBOX:	// �޽��� �ڽ� ó��
		switch(iTargetID)
		{
		case 2:	// Ȯ��
			if (g_cUIRefineWindow->m_nMessageBoxNo == 1) // ��Ȯ��â�̸�...
				g_cNPCControl->HT_vNetWork_CSP_REQ_ITEM_REFINING();	// ���ý���
			break;
		default:
			break;
		}
		break;
	case UI_TARGET_SLOTBOX:
		if (iAction == UI_ACTION_MOUSE_L_UP)
		{
			unsigned int	nWindowIndex = 0, nControlIndex = 0;
			int iTextureID = 0;
			g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);

			if (nWindowIndex == _DIALOG_EQUPINVENTORY || nWindowIndex == _DIALOG_INVENTORY2)	// �κ��丮���� �ű�͸� ó���� �������� �̵� ����
			{
				// ����ϰ� �ִ� �κ��丮 �������� �ű�ٸ� ������ �̵� ����ó��
				if (nControlIndex < _SLOTCURRECT_INVEN) 
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
					return;
				}

				DWORD dwKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
				
				g_cUIRefineWindow->m_iWindowIndex[0] = nWindowIndex;
				g_cUIRefineWindow->m_iControlIndex[0] = nControlIndex;

				if (g_cNPCControl->HT_hrNPCControl_ItemWork_LButtonClick( dwKeyID ) == HT_FAIL)
				{
					g_cUIManager->HT_SetSlotBoxControlEnable(nWindowIndex, nControlIndex, true);
					g_cUIManager->HT_RefuseSlotImageMoving();
				}
			}
			else
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
			}
			break;
		}
	}
}
*/