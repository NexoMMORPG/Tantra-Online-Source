//////////////////////////////////////////////////////////////////////////////////////////
// ���� : ������, ��ų ����â ����
// 
// �ۼ��� : �輱��
//
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTOBJECTINFO_H__
#define __HTOBJECTINFO_H__

#include "HTControlDef.h"

typedef enum 
{ 
	eInfo_Character = 1, 
	eInfo_Monster,
	eInfo_NPC,
	eInfo_Item,
	eInfo_Item_Economy,
	eInfo_Item_Work,
	eInfo_Item_Fix,
	eInfo_Item_Disjoint,
	eInfo_Item_Store_Sell,
	eInfo_Item_Store_Buy,
	eInfo_Skill,
	eInfo_MainCheck,
	eInfo_ART,			// ���ι��� Address, Run, Trade
	eInfo_QuickSlotCommand,	// ������â�� ��ɾ�
	eInfo_QuickSlot,
	eInfo_None,
	eInfo_Item_RentalStore
} eInfoType;

#define INFODATA_POSX 10
#define INFODATA_POSY 10

class HTObjectInfo
{
public:
	HTObjectInfo(void); 
	~HTObjectInfo(void);
	
	//	���� �ʱ�ȭ, �׸� �ε�
	HTvoid		HT_vObjectInfo_Init();

	//	���콺 ����Ʈ�� üũ
	HTvoid		HT_vObjectInfo_MousePtCheck( HTPoint pPt);
	HTvoid		HT_vObjectInfo_InfoCheck(unsigned int iIndex, unsigned int iCIndex );

	//	����â�� Ȱ��ȭ ������
	HTvoid		HT_vObjectInfo_Active( HTPoint pPt);
	//	����â�� ��Ȱ��ȭ ������
	HTvoid		HT_vObjectInfo_AntiActive();

	//	��ü �ؽ�Ʈ ���� ��Ʈ��
	HTvoid		HT_vObjectInfo_SetInfoText();

	// ������ ��� �����
	HTvoid		HT_vObjectInfo_DeleteAll();

	HTbool		HT_bObjectInfo_IsActive()	{ return m_bInfoWinImageSw; }
	HTvoid		HT_vObjectInfo_Active_NPC(int iObjID);

	unsigned int		nWindowIndex;
	unsigned int		nControlIndex;
private:
	HTvector3			m_pInfoPos;			// ����â ���� ��ġ
	HTbool				m_bInfoWinImageSw;	// ����â�� Ȱ��ȭ �Ǿ�����
	HTint				m_iInfoWinImageID;	// ����â �̹��� ���̵�
	HTint				m_iRenderType;		
	DWORD				m_dwObjectKeyID;	// �κ��丮�� �ִ� ������ ������ ����
	DWORD				m_dwObjectModelID;	// ���ͳ� ĳ������ ������ ����
	HTint				m_iEconomy_ItemIndex;//����â�� ������ ������ ����

	HT_ITEMINFO				m_stItemInfo;			// ����â�� ��Ÿ�� ������
	vector<HT_ITEM_DATA*>	m_vFixDisjointInfo;	// ����/��ü
	HTbool					m_bFixDisjointPossible;	// ����/��ü ��������(Ŀ�� ������ ���ؼ�)
	vector<HT_ITEM_DATA*>	m_vSkillNextInfo;
	HT_ITEMINFO				m_stSkillInfo;
	CHTString			m_szName;			// ĳ����/������ �̸�
	CHTString			m_szNeedPrana;		// ��ũ������Ʈ/�������Ʈ�� �ø������� �ʿ��� ���󳪾�
	HTint				m_nLocation;		// ������ ��ġ. tradeâ���� ����ŷ�� ������ ������..
											// (����ŷ �����¶� KeyID�� ������ ���� ����Ѵ�.) 

	HTPoint				m_ptWinSize;		// ����â ũ��
};

#endif