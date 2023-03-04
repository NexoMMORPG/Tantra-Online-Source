
#include "stdAfx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSkillInventory.h"


HTSkillSystem::HTSkillSystem()
{
	//----------LL �ʱ�ȭ---------//
	HT_LL_vInitList();
}

HTSkillSystem::~HTSkillSystem()
{
	HT_DELETE( m_sSkillHead );
	HT_DELETE( m_sSkillTail );
}

HTvoid HTSkillSystem::HT_vSkillSystem_CleanUp()
{
	HT_LL_hrDeleteAll();
}

HTRESULT HTSkillSystem::HT_hSkillSystemInit()
{
	m_bTribeAttack_Count		= 1;
	m_bFreeAttack_Count			= 1;
	m_bJusinAttack_Count		= 1;
	m_bJusinFreeAttack_Count	= 0;
	m_bJobSkill_Count			= 0;
	m_dwKeyID_Count				= 0;
	m_bSkillDataCheck			= FALSE;

	//	��ü ��ų ����
	HT_SKILLINSERT_FLAG sInsertData;
	HTbyte byteTmp;
	int iStart, iEnd;
	
	switch ( g_byCharacterServerTribe[g_oMainCharacterInfo.snTribe-1] )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			iStart = HT_PARAMTYPE_PCSKILL_NAGAKIN_START;
			iEnd = HT_PARAMTYPE_PCSKILL_NAGAKIN_END;		
		break;

		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			iStart = HT_PARAMTYPE_PCSKILL_ASURARAK_START;
			iEnd = HT_PARAMTYPE_PCSKILL_ASURARAK_END;
		break;

		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			iStart = HT_PARAMTYPE_PCSKILL_DEVAGARU_START;
			iEnd = HT_PARAMTYPE_PCSKILL_DEVAGARU_END;
		break;

		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			iStart = HT_PARAMTYPE_PCSKILL_YAKGAN_START;
			iEnd = HT_PARAMTYPE_PCSKILL_YAKGAN_END;
		break;

		default:
			return HT_FAIL;
	}

	for ( HTint iSkillID = iEnd ; iSkillID >= iStart ; --iSkillID )
	{
		// ������ �����ϴ� ��ų���� �ľ�. 
		if ( g_pParamMgr->HT_bGetPCSkillMaxLevel( iSkillID, 1, &byteTmp ) && byteTmp != 0 )
		{
			sInsertData.dwSkill_Index = iSkillID;
			sInsertData.bySkill_Level = 0;
			sInsertData.bySkill_Type = 0x00;
			sInsertData.bySkill_Count = 100 - m_bTribeAttack_Count;
			m_bTribeAttack_Count++;

			HT_LL_hrInsertAfter( sInsertData );
		}
		else
		{
			sInsertData.dwSkill_Index = iSkillID;
			sInsertData.bySkill_Level = 0;
			sInsertData.bySkill_Type = 99;
			sInsertData.bySkill_Count = 100 - m_bTribeAttack_Count;
			m_bTribeAttack_Count++;

			HT_LL_hrInsertAfter( sInsertData );
		}
	}

	return HT_OK;
}

//	��ų ����Ʈ �� �ʱ�ȭ_�������� �ʱ� ��ų ����Ʈ�� �޴´�.
HTvoid HTSkillSystem::HT_vSkillSystem_Init_SkillBook( BYTE bySkill[MAX_SKILL] )
{ 
	//int iSkillLevelCount;
	HT_SKILL_NODE *t;

	int iStart, iEnd;
	
	switch ( g_byCharacterServerTribe[g_oMainCharacterInfo.snTribe-1] )
	{
		case TRIBE_NAGA	 :		
		case TRIBE_KINNARA :
			iStart = HT_PARAMTYPE_PCSKILL_NAGAKIN_START;
			iEnd = HT_PARAMTYPE_PCSKILL_NAGAKIN_END;		
		break;

		case TRIBE_ASURA :		
		case TRIBE_RAKSHASA :
			iStart = HT_PARAMTYPE_PCSKILL_ASURARAK_START;
			iEnd = HT_PARAMTYPE_PCSKILL_ASURARAK_END;
		break;

		case TRIBE_DEVA :
		case TRIBE_GARUDA:
			iStart = HT_PARAMTYPE_PCSKILL_DEVAGARU_START;
			iEnd = HT_PARAMTYPE_PCSKILL_DEVAGARU_END;
		break;

		case TRIBE_YAKSA :		
		case TRIBE_GANDHARVA:
			iStart = HT_PARAMTYPE_PCSKILL_YAKGAN_START;
			iEnd = HT_PARAMTYPE_PCSKILL_YAKGAN_END;
		break;

		default:
			// GM�� ���� ����
			return;
	}

//	iSkillLevelCount = 0;
	for( HTint i=0 ; i<MAX_SKILL ; i++ )
	{
		t = m_sSkillHead->next;
		while( t != m_sSkillTail )
		{
			/*
			if( i == t->sSkill.m_bySkill_TribeCount )
			{
				t->sSkill.m_bySkill_Level = bySkill[i];

				//	��ų������ ���� 0���� ���������� üũ
				if( t->sSkill.m_bySkill_Level > 0 )
					iSkillLevelCount++;
				break;
			}*/

			// �ش� ��ų ID�� ã�� ��ų ���� ����
			if ( t->sSkill.m_dwSkill_Index == i + iStart)
			{
				t->sSkill.m_bySkill_Level = bySkill[i];

				//	����/����� ��ų�� 3302(�ƹٸ�) ��ų ó��_�����Ÿ� �߰�
				if( t->sSkill.m_dwSkill_Index == 3302 )
				{
					HTint iRange;
					if( g_pParamMgr->HT_bGetPCSkillEffect1Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level, &iRange ) )
                        g_cMainCharacter->HT_vMainChar_SetPassiveSkillRange( iRange );
				}
				break;
			}

			t = t->next;
		}
	}
/*
	// ��ų������ ����� ��ϵǾ� �ִ��� �������� (������)
	HT_SKILL_NODE *tt;
	tt = m_sSkillHead->next;
	char szTemp[128];
	while( tt != m_sSkillTail )
	{
		sprintf( szTemp, "[ID:%d = %d], ", tt->sSkill.m_dwSkill_Index, tt->sSkill.m_bySkill_Level);
		HT_g_vLogFile( szTemp );
		tt = tt->next;
	}
	HT_g_vLogFile( "\nSet SCP_SKILL RECEIVE DATA...\n" );
*/

/*
	if( m_bSkillDataCheck == HT_FALSE &&
		iSkillLevelCount == 0 )
	{
		m_bSkillDataCheck = HT_TRUE;

		MSG_InitSkill* info = HT_NULL;
		info = new MSG_InitSkill;
		ZeroMemory( info, sizeof(MSG_InitSkill) );

		g_pNetWorkMgr->RequestInitSkill( info );
		
		HT_g_vLogFile( "\n��ų ������ �߸��޾Ƽ� �ٽ� ��û��...\n" );

		//-----����� �׽�Ʈ�� ���Ͽ�-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_MSG_InitSkill" );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

		HT_DELETE( info );
	}
*/
	// ��ųƮ�� �ٽ� �׸���
	g_cSkillInventory->HT_hrSkillItemInit();
	//	������ �����۰� ��ų���Ŀ� ������ �������� ������ ������ �ε��� ���⼭ ��
	g_cQuickSlot->HT_vIconLoad();
}

//----------��ȯ����----------//
//----------��ų�� ����---------//
BYTE HTSkillSystem::HT_bySkillSystem_GetSkill_Level( DWORD dwIndex )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwIndex )
			return t->sSkill.m_bySkill_Level;
		t = t->next;
	}

	return 0;
}

//	���������� ����� ��ų�� ���ݼӵ��� ����
HTvoid HTSkillSystem::HT_vSkillSystem_SetAttackSpeedVariation( DWORD dwSkillIndex, short snSpeed )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			t->sSkill.m_snSkill_AttackSpeed = snSpeed;
		t = t->next;
	}
}

//	���������� ����� ��ų�� ĳ���üӵ��� ����
HTvoid HTSkillSystem::HT_vSkillSystem_SetCastingSpeedVariation( DWORD dwSkillIndex, short snSpeed )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			t->sSkill.m_snSkill_CastingSpeed = snSpeed;
		t = t->next;
	}
}

//	���������� ����� ��ų�� �����Ÿ�
HTvoid HTSkillSystem::HT_vSkillSystem_SetShootRange( DWORD dwSkillIndex, BYTE byShootRange )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			t->sSkill.m_bySkill_ShootRange = byShootRange;
		t = t->next;
	}
}

//	�������� ����� ��ų�� �̵��ӵ��� ����
HTvoid HTSkillSystem::HT_vSkillSystem_SetMovingSpeed( DWORD dwSkillIndex, short snSpeed )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			t->sSkill.m_snSkill_MovingSpeed = snSpeed;
		t = t->next;
	}
}

HTvoid HTSkillSystem::HT_vSkillSystem_SetSkill_Level(DWORD dwIndex, BYTE byLevel)
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwIndex )
		{
			t->sSkill.m_bySkill_Level = byLevel;
			//	����/����� ��ų�� 3302(�ƹٸ�) ��ų ó��_�����Ÿ� �߰�
			if( t->sSkill.m_dwSkill_Index == 3302 )
			{
				HTint iRange;
				if( g_pParamMgr->HT_bGetPCSkillEffect1Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level, &iRange ) )
                    g_cMainCharacter->HT_vMainChar_SetPassiveSkillRange( iRange );
			}
			return;
		}
		t = t->next;
	}
}

// ��ų �̸� ����
CHTString HTSkillSystem::HT_szSkillSystem_GetSkillName(DWORD dwIndex)	
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwIndex )
		{
			if( t->sSkill.m_bySkill_Level <= 0 )
				return _T(" ");

			CHTString szName;
			g_pEngineHandler->HT_hrGetPCSkillName( t->sSkill.m_dwSkill_Index, &szName );
			return szName;
		}
		t = t->next;
	}

	return _T(" ");
}

//	��ų�� ����,�ֽ�,������ų ���ʸ� �Ѱ���
HTvoid HTSkillSystem::HT_vSkillSystem_GetSkillSequenceCount( HTint iType, HTint iIndex, HT_SKILL_INVENTORYCONNECT *sElement )
{
	HTint iCount;
	HT_SKILL_NODE *t;

	iCount = 0;
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_bySkill_TribeCount >= iIndex )
		{
			if( t->sSkill.m_bSkill_Type == (BYTE)iType )
			{
				sElement[iCount].dwSkillIndex = t->sSkill.m_dwSkill_Index;
				sElement[iCount].byLevel = t->sSkill.m_bySkill_Level;
				sElement[iCount].iSkillIconID = t->sSkill.m_dwSkill_UIICONID;
				iCount++;
				if( iCount == 10 )
					return;
			}
		}
		t = t->next;
	}
}

HTint HTSkillSystem::HT_vSkillSystem_GetSkillEffect1Param1( DWORD dwSkillIndex )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
		{
			HTint iValue;
			if( g_pParamMgr->HT_bGetPCSkillEffect1Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level, &iValue ) )
			{
				return iValue;
			}
			return 0;
		}
		t = t->next;
	}
	return 0;
}

//	Get
//	Return Get Plus Level
HTbyte HTSkillSystem::HT_bySkillSystem_GetSkillPlusLevel( DWORD dwSkillIndex )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			return t->sSkill.m_bySkill_PlusLevel;
		t = t->next;
	}

	return 0;
}

//	Set
//	Set Plus Level
HTvoid HTSkillSystem::HT_vSkillSystem_SetSkillPlusLevel( DWORD dwSkillIndex, HTbyte byLevel, HTbyte byPlusLevel )
{
	HT_SKILL_NODE* t;
	t = m_sSkillHead->next;

	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
		{
			t->sSkill.m_bySkill_Level = byLevel;
			t->sSkill.m_bySkill_PlusLevel = byPlusLevel;
			return;
		}
		t = t->next;
	}
}

//	�����κ��� ��ų Learn ������ �޴���.
HTvoid HTSkillSystem::HT_vSkillSystem_SetLearn( S_TNSKILL_DATA info )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == info.snID )
		{
			t->sSkill.m_bySkill_Level = info.byLevel;
			//	����/����� ��ų�� 3302(�ƹٸ�) ��ų ó��_�����Ÿ� �߰�
			if( t->sSkill.m_dwSkill_Index == 3302 )
			{
				HTint iRange;
				if( g_pParamMgr->HT_bGetPCSkillEffect1Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level, &iRange ) )
                    g_cMainCharacter->HT_vMainChar_SetPassiveSkillRange( iRange );
			}
			return;
		}
		t = t->next;
	}
}

//----------��ų�� �̹��� ���̵� �Ѱ���---------//
HTint HTSkillSystem::HT_vSkillSystem_GetSkill_UIIconID( DWORD dwSkillIndex )
{/*
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwSkillIndex )
			return t->sSkill.m_dwSkill_UIICONID;
		t = t->next;
	}
*/
	int hr = g_cUISkillWindow->HT_vGetSkillIcon(dwSkillIndex);
	if (hr)	return hr;

	return -1;
}

//	��ü ��ų �����
HTvoid HTSkillSystem::HT_vSkillSystem_TotalSkillDelete()
{
	m_bTribeAttack_Count = 0;
	m_bJusinAttack_Count = 0;
	m_bFreeAttack_Count = 0;
	HT_LL_hrDeleteAll();
}

//	��ü ��ų�� ������ ���� �ʱ�ȭ
HTvoid HTSkillSystem::HT_vSkillSystem_TotalSkillLevelInit()
{
	HT_SKILL_NODE *t;

	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		t->sSkill.m_bySkill_Level = 0;
		t = t->next;
	}

	//	������ ���� ����
	g_cQuickSlot->HT_vTotalDeleteIcon( 0 );
}

//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid HTSkillSystem::HT_LL_vInitList()
{
	m_sSkillHead = NULL;
	m_sSkillTail = NULL;

	m_sSkillHead = new HT_SKILL_NODE;
	m_sSkillTail = new HT_SKILL_NODE;

	m_sSkillHead->next = m_sSkillTail;
	m_sSkillTail->next = m_sSkillTail;

}

//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
HTRESULT HTSkillSystem::HT_LL_hrInsertAfter( HT_SKILLINSERT_FLAG info )
{
	HT_SKILL_NODE *s;

	s = NULL;
	s = new HT_SKILL_NODE;
	s->sSkill.HT_hrSkill_Insert( info );
	s->next = m_sSkillHead->next;
	m_sSkillHead->next = s;

	return HT_OK;
}

//----------LL ����Ÿ �����---------//
HTRESULT HTSkillSystem::HT_LL_hrDeleteNode( DWORD dwSkillIndex )
{
	HT_SKILL_NODE *s;
	HT_SKILL_NODE *p;

	p = m_sSkillHead;
	s = p->next;
	while( s->sSkill.m_dwSkill_Index != dwSkillIndex && s != m_sSkillTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sSkillTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL ����Ÿ ���� �����---------//
HT_SKILL_NODE *HTSkillSystem::HT_LL_hrDeleteAll()
{
	HT_SKILL_NODE *s;
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sSkillHead->next = m_sSkillTail;

	return m_sSkillHead;
}

//----------��ϵǾ��ִ� ��ų���� �˻�-----------//
HTbool HTSkillSystem::HT_bSkillSystem_IsRegistedSkill(DWORD dwIndex)
{
	HT_SKILL_NODE* t;
	t = m_sSkillHead->next;

	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwIndex )
			return HT_TRUE;

		t = t->next;
	}

	return HT_FALSE;
}

//------------------------------------------------------------------------------------//
// ���� - ��ų ������ ��� �޼����� �����ϰ�, �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
//------------------------------------------------------------------------------------//
HTint HTSkillSystem::HT_iGetSkillInfo( DWORD dwIndex, HT_ITEMINFO& vInfo, vector<HT_ITEM_DATA*>& vNextInfo )
{
	HT_SKILL_NODE* t;
	t = m_sSkillHead->next;

	HTint winSizeX = 0;

	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == dwIndex )
		{
			// ��ų ���� ������
			HT_ITEM_DATA* pData = HT_NULL;
			HT_ITEM_EXPANSION_DATA* pExtData = HT_NULL;
			CHTString str;

			HTbyte byteOut;
			HTint iOut = 0;
			HTshort sOut = 0;

			// ��ų �̸�
			if( g_pEngineHandler->HT_hrGetPCSkillName( t->sSkill.m_dwSkill_Index, &str ) == HT_FAIL )
				return winSizeX;

			vInfo.strName.str = str;
			if( t->sSkill.m_bySkill_Level > 0 ) // ��ų ����
			{
				str.HT_szFormat("  Lvl %d", t->sSkill.m_bySkill_Level); 
				vInfo.strName.str += str;
			}
			vInfo.strName.color = g_ColorTable[15];		// white
			winSizeX = vInfo.strName.str.HT_nGetSize();

			// ����
			g_pEngineHandler->HT_hrGetPCSkillDesc( t->sSkill.m_dwSkill_Index, &vInfo.strDescription.str );
			if( vInfo.strDescription.str == HT_INFO_SKILL_DESCRIPT_NULL )
				vInfo.strDescription.str.HT_hrCleanUp();
			else
				vInfo.strDescription.color = g_ColorTable[16]; //light grey

			// ��ų Ÿ��
			HTdword dwSkillType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( t->sSkill.m_dwSkill_Index );
			if ( dwSkillType == HT_PCSKILLTYPE_PASSIVE )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				pExtData->basic.color = g_ColorTable[16]; //light grey
				// Passive
				HT_vSkillSystem_SetMessage( eMsgCommonSkillClassPassive, &pExtData->basic.str);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			
			// ���� ������ ���ѻ���
			// ��ų ���� Lock ����
			HTbyte byMaxLevel = 0;
			HTbool bNextInfo = HT_FALSE;
			if( t->sSkill.m_bySkill_Level == 0 )
				g_pParamMgr->HT_bGetPCSkillMaxLevel( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &byMaxLevel );
			else
				g_pParamMgr->HT_bGetPCSkillMaxLevel( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level, &byMaxLevel );

			if( byMaxLevel > 0 && t->sSkill.m_bySkill_Level < byMaxLevel && 
				g_pParamMgr->HT_bLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1 ) == true )
			{
				pData = new HT_ITEM_DATA;
				if( t->sSkill.m_bySkill_Level == 0 )
					// �䱸 ���� ����
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedCondition, &pData->str );
				else
				{
					// ���� ���� ����
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNextCondition, &pData->str );
					bNextInfo = HT_TRUE ; // ���� ������ ���� ������ ������
				}

				pData->color = g_ColorTable[17];	// yellow
				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());

				// �䱸����
				if( g_pParamMgr->HT_bGetPCSkillReqLevel( &byteOut ) == true && byteOut > 0 )
				{
					pData = new HT_ITEM_DATA;
					// %d Level �ʿ�
					HT_vSkillSystem_SetMessage( eMsgItemInfoNeedLevel, &str );
					pData->str.HT_szFormat( str.HT_szGetString(), byteOut );


					if( g_cStatus->HT_byGetLevel() >= byteOut )
						pData->color = g_ColorTable[17];	// yellow
					else
						pData->color = g_ColorTable[11];	//red

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				// �������� ��ų
				if( g_pParamMgr->HT_bGetPCSkillReqSkill1( &iOut ) == true && iOut > 0 )
				{
					g_pEngineHandler->HT_hrGetPCSkillName( iOut, &str);
					g_pParamMgr->HT_bGetPCSkillReqSkill1_Lvl( &byteOut );

					pData = new HT_ITEM_DATA;

					HTbyte byCurLevel = HT_bySkillSystem_GetSkill_Level( iOut );
					if( byCurLevel >= byteOut )
						pData->color = g_ColorTable[17];	// yellow
					else
						pData->color = g_ColorTable[11];	//red
					// %s Lvl %d �ʿ�
					CHTString szMessage;
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedSkillLevel, &szMessage );
					pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteOut );

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				if( g_pParamMgr->HT_bGetPCSkillReqSkill2( &iOut ) == true && iOut > 0 )
				{
					g_pEngineHandler->HT_hrGetPCSkillName( iOut, &str);
					g_pParamMgr->HT_bGetPCSkillReqSkill2_Lvl( &byteOut );

					pData = new HT_ITEM_DATA;

					HTbyte byCurLevel = HT_bySkillSystem_GetSkill_Level( iOut );
					if( byCurLevel >= byteOut )
						pData->color = g_ColorTable[17];	// yellow
					else
						pData->color = g_ColorTable[11];	//red
					// %s Lvl %d �ʿ�		
					CHTString szMessage;
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedSkillLevel, &szMessage );
					pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteOut );

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				g_pParamMgr->HT_bUnLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1 );
			}

			// ���� ������ ��ų ���� Lock ����
			if( g_pParamMgr->HT_bLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level ) == false )
				return winSizeX;

			//-----���ѻ���------//
			// �䱸�Ǵ� ����_����Ÿ��
			if( g_pParamMgr->HT_bGetPCSkillReqWeaponType( &iOut ) == true && iOut > 0 )
			{
				HTRESULT tribe = HT_FALSE;
				str.HT_hrCleanUp();

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				if( BIT_AND( _ITEM_TYPE_WEPON_SWORD, iOut ) )
				{
					//str = "��"; 
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassSword, &pExtData->basic.str );
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_AX, iOut ) )
				{
					if(tribe) //str += ", ����";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str = "����";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_LANCE, iOut ) )
				{
					if(tribe) //str += ", â";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "â";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_MACE, iOut ) )
				{
					if(tribe) //str += ", �б�";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "�б�";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_GLOVE, iOut ) )
				{
					if(tribe) //str += ", ��������";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "��������";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_WAND, iOut ) )
				{
					if(tribe) //str += ", ��������";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "��������";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_BOW, iOut ) )
				{
					if(tribe) //str += ", Ȱ";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "Ȱ";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_DAGGER, iOut ) )
				{
					if(tribe) //str += ", �ܰ�";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "�ܰ�";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &pExtData->basic.str);
					tribe = HT_TRUE;
				}

				//str += " ����";
				HT_vSkillSystem_SetMessage( eMsgItemInfoPrivateUse, &str);
				pExtData->basic.str = pExtData->basic.str + _T(" ") + str;	

				HTdword dwItemKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
				HTshort sItemType = g_cItemSystem->HT_sItemSystem_GetItemType( dwItemKeyID );
				if( BIT_AND( sItemType, iOut ) )
					pExtData->basic.color = g_ColorTable[16]; //light grey
				else
					pExtData->basic.color = g_ColorTable[11]; //red

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			}
			
			// �䱸�Ǵ� ������
			if( g_pParamMgr->HT_bGetPCSkillidReqItem( &iOut ) == true && iOut > 0 )
			{
				if( g_pParamMgr->HT_bGetItemName( iOut, &str) == true )
				{
					pData = new HT_ITEM_DATA;
					// %s �ʿ�
					CHTString szMessage;
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedItem, &szMessage);
					pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString() );

					// �޼տ� ������ �������� index ���ϱ�
					HTdword dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
					HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
					// PC �κ��丮 �Ǵ� �޼տ� ������ �������� �ʿ��� ����������
					if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( iOut ) || ( dwIndex == iOut ) )
						pData->color = g_ColorTable[16]; //light grey
					else
						pData->color = g_ColorTable[11];	//red

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
			}
			// ���ӽð�
			//if( g_pParamMgr->HT_bGetPCSkillDuration( &iOut ) == true && iOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("   (���ӽð�:%d��)", iOut/HT_ITEM_DURATION_DIVIDING );		

			//	vInfo.vAttributeStr.push_back(pExtData);
			//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			//}
			// Effect 1
			if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			{
				HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetPCSkillEffect1Param1( &iParam1 );
				g_pParamMgr->HT_bGetPCSkillEffect1Param2( &iParam2 );
				g_pParamMgr->HT_bGetPCSkillEffect1Function( &iFunction ); 
				if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[16]; //light grey
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð�
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect1Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð�:%d��)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// ���� �ܰ�
					if( bNextInfo )
					{
						iParam1 = iParam2 = iFunction = 0;
						str.HT_hrCleanUp();

						g_pParamMgr->HT_bGetPCSkillEffect1Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam1 );
						g_pParamMgr->HT_bGetPCSkillEffect1Param2( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam2 );
						g_pParamMgr->HT_bGetPCSkillEffect1Function( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iFunction ); 
						if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
						{
							pData = new HT_ITEM_DATA;
							ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

							pData->color = g_ColorTable[16]; //light grey
							pData->str = str;		

							vNextInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());

							// ���ӽð�
							if( g_pParamMgr->HT_bGetPCSkillEffect1Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (���ӽð�:%d��)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// Effect 2
			if( g_pParamMgr->HT_bGetPCSkillEffect2ID( &iOut ) == true && iOut > 0 )
			{
				HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetPCSkillEffect2Param1( &iParam1 );
				g_pParamMgr->HT_bGetPCSkillEffect2Param2( &iParam2 );
				g_pParamMgr->HT_bGetPCSkillEffect2Function( &iFunction ); 
				if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[16]; //light grey
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð�
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect2Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð�:%d��)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// ���� �ܰ�
					if( bNextInfo )
					{
						iParam1 = iParam2 = iFunction = 0;
						str.HT_hrCleanUp();

						g_pParamMgr->HT_bGetPCSkillEffect2Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam1 );
						g_pParamMgr->HT_bGetPCSkillEffect2Param2( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam2 );
						g_pParamMgr->HT_bGetPCSkillEffect2Function( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iFunction ); 
						if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
						{
							pData = new HT_ITEM_DATA;
							ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

							pData->color = g_ColorTable[16]; //light grey
							pData->str = str;		

							vNextInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());

							// ���ӽð�
							if( g_pParamMgr->HT_bGetPCSkillEffect2Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (���ӽð�:%d��)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// Effect 3
			if( g_pParamMgr->HT_bGetPCSkillEffect3ID( &iOut ) == true && iOut > 0 )
			{
				HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetPCSkillEffect3Param1( &iParam1 );
				g_pParamMgr->HT_bGetPCSkillEffect3Param2( &iParam2 );
				g_pParamMgr->HT_bGetPCSkillEffect3Function( &iFunction ); 
				if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[16]; //light grey
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð�
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect3Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð�:%d��)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// ���� �ܰ�
					if( bNextInfo )
					{
						iParam1 = iParam2 = iFunction = 0;
						str.HT_hrCleanUp();

						g_pParamMgr->HT_bGetPCSkillEffect3Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam1 );
						g_pParamMgr->HT_bGetPCSkillEffect3Param2( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam2 );
						g_pParamMgr->HT_bGetPCSkillEffect3Function( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iFunction ); 
						if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
						{
							pData = new HT_ITEM_DATA;
							ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

							pData->color = g_ColorTable[16]; //light grey
							pData->str = str;		

							vNextInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());

							// ���ӽð�
							if( g_pParamMgr->HT_bGetPCSkillEffect3Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (���ӽð�:%d��)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// Effect 4
			if( g_pParamMgr->HT_bGetPCSkillEffect4ID( &iOut ) == true && iOut > 0 )
			{
				HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetPCSkillEffect4Param1( &iParam1 );
				g_pParamMgr->HT_bGetPCSkillEffect4Param2( &iParam2 );
				g_pParamMgr->HT_bGetPCSkillEffect4Function( &iFunction ); 
				if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[16]; //light grey
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð�
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect4Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð�:%d��)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// ���� �ܰ�
					if( bNextInfo )
					{
						iParam1 = iParam2 = iFunction = 0;
						str.HT_hrCleanUp();

						g_pParamMgr->HT_bGetPCSkillEffect4Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam1 );
						g_pParamMgr->HT_bGetPCSkillEffect4Param2( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam2 );
						g_pParamMgr->HT_bGetPCSkillEffect4Function( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iFunction ); 
						if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
						{
							pData = new HT_ITEM_DATA;
							ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

							pData->color = g_ColorTable[16]; //light grey
							pData->str = str;		

							vNextInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());

							// ���ӽð�
							if( g_pParamMgr->HT_bGetPCSkillEffect4Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (���ӽð�:%d��)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// Effect 5
			if( g_pParamMgr->HT_bGetPCSkillEffect5ID( &iOut ) == true && iOut > 0 )
			{
				HTint iParam1 = 0, iParam2 = 0, iFunction = 0;
				str.HT_hrCleanUp();

				g_pParamMgr->HT_bGetPCSkillEffect5Param1( &iParam1 );
				g_pParamMgr->HT_bGetPCSkillEffect5Param2( &iParam2 );
				g_pParamMgr->HT_bGetPCSkillEffect5Function( &iFunction ); 
				if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
				{
					pExtData = new HT_ITEM_EXPANSION_DATA;
					ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

					pExtData->basic.color = g_ColorTable[16]; //light grey
					pExtData->basic.str = str;		

					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());

					// ���ӽð�
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect5Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (���ӽð�:%d��)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// ���� �ܰ�
					if( bNextInfo )
					{
						iParam1 = iParam2 = iFunction = 0;
						str.HT_hrCleanUp();

						g_pParamMgr->HT_bGetPCSkillEffect5Param1( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam1 );
						g_pParamMgr->HT_bGetPCSkillEffect5Param2( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iParam2 );
						g_pParamMgr->HT_bGetPCSkillEffect5Function( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1, &iFunction ); 
						if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
						{
							pData = new HT_ITEM_DATA;
							ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

							pData->color = g_ColorTable[16]; //light grey
							pData->str = str;		

							vNextInfo.push_back(pData);
							winSizeX = max(winSizeX, pData->str.HT_nGetSize());

							// ���ӽð�
							if( g_pParamMgr->HT_bGetPCSkillEffect5Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (���ӽð�:%d��)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// �����Ÿ�
			//if( g_pParamMgr->HT_bGetPCSkillRange( &iOut ) && iOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("�����Ÿ� %d", iOut);		

			//	vInfo.vAttributeStr.push_back(pExtData);
			//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			//}
			// ������
			if( g_pParamMgr->HT_bGetPCSkillAllowedTarget( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				switch( iOut )
				{
					case  _TARGET_SELF				: // PC����
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetSelf, &pExtData->basic.str ); break;
					case  _TARGET_FRIENDLY			: // field������ PC, �ֽ��������� ���� �ֽ�
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendly, &pExtData->basic.str ); break;				
					case  _TARGET_FRIENDLY_EXCEPT_ME: // �ڽ��� ����
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendlyExceptMe, &pExtData->basic.str ); break;			
					case  _TARGET_ENEMEY			: pExtData->basic.str.HT_szFormat(""); 
						/*HT_vSkillSystem_SetMessage( eMsgAllowedTargetSelf, &pExtData->basic.str );*/ break;		
					case  _TARGET_PARTY				: // ��Ƽ���� 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetParty, &pExtData->basic.str ); break;		
					case  _TARGET_GUILD				: // ������
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetGuild, &pExtData->basic.str ); break;				
					case  _TARGET_ALL				: // ALL 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetAll, &pExtData->basic.str ); break;	
					case  _TARGET_FRIENDLY_CORPSE	: // ������ ��ü. ��Ȱ �������� ��� 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendlyCorpse, &pExtData->basic.str ); break;		
					case  _TARGET_ENEMEY_CORPSE		: // ���� ��ü. ��ü ���� �������� ���
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetEnemeyCorpse, &pExtData->basic.str ); break;		
					case  _TARGET_GATE				: // �������� ������ ���
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetGate, &pExtData->basic.str ); break;	
					default: pExtData->basic.str.HT_hrCleanUp(); break;
				}

				if( pExtData->basic.str.HT_nGetSize() > 0 )
				{
					vInfo.vAttributeStr.push_back(pExtData);
					winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				}
				else
					delete pExtData;
			}
			// �Ҹ� HP
			if( g_pParamMgr->HT_bGetPCSkillCostHP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// �Ҹ� HP %d
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostHP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// ���� �ܰ�
				if( bNextInfo )
				{
					if( g_pParamMgr->HT_bGetPCSkillCostHP( t->sSkill.m_dwSkill_Index, 
												t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
					{
						pData = new HT_ITEM_DATA;
						ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

						pData->color = g_ColorTable[16]; //light grey
						// �Ҹ� HP %d	
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostHP, &str );
						pData->str.HT_szFormat( str.HT_szGetString(), iOut);

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			// �Ҹ� TP
			if( g_pParamMgr->HT_bGetPCSkillCostTP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// �Ҹ� TP %d
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostTP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// ���� �ܰ�
				if( bNextInfo )
				{
					if( g_pParamMgr->HT_bGetPCSkillCostTP( t->sSkill.m_dwSkill_Index, 
												t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
					{
						pData = new HT_ITEM_DATA;
						ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

						pData->color = g_ColorTable[16]; //light grey
						// �Ҹ� TP %d
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostTP, &str );
						pData->str.HT_szFormat( str.HT_szGetString(), iOut);

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			// �Ҹ� Item
			if( g_pParamMgr->HT_bGetPCSkillidCostItem( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				
				CHTString str;
				g_pParamMgr->HT_bGetItemName( iOut, &str );
				HTbyte byteCount = 0;
				g_pParamMgr->HT_bGetPCSkillCostItemCount( &byteCount );

				// %s %d�� �Ҹ�
				CHTString szMessage;
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostItemCount, &szMessage );
				pExtData->basic.str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteCount );

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// ���� �ܰ�
				if( bNextInfo )
				{
					if( g_pParamMgr->HT_bGetPCSkillidCostItem( t->sSkill.m_dwSkill_Index, 
												t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
					{
						pData = new HT_ITEM_DATA;
						ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

						pData->color = g_ColorTable[16]; //light grey
						g_pParamMgr->HT_bGetPCSkillCostItemCount( t->sSkill.m_dwSkill_Index, 
																  t->sSkill.m_bySkill_Level+1, &byteCount );
						// %s %d�� �Ҹ�
						CHTString szMessage;
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostItemCount, &szMessage );
						pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteCount );

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}

			// ��ų ���� Lock ����
			g_pParamMgr->HT_bUnLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level );
			break;
		} // end of if( t->sSkill.m_dwSkill_Index == dwIndex )
		t = t->next;
	} // end of while( t != m_sSkillTail )

	return winSizeX;
}

// ������ Effect�� ���� ������ ��ġ ����ϱ�
HTvoid HTSkillSystem::HT_bSkillSystem_SetDamageParam( HTint iEffectID, HTint iParam1, HTint iParam2 )
{
	HTint iSoul = g_cStatus->HT_nGetChakraSoul();
	HTint iNerve = g_cStatus->HT_nGetChakraNerve();
	HTint iMinDamage = 0, iMaxDamage = 0;
	
	/*HTdword dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( g_cItemSystem->HT_sItemSystem_GetItemType( dwKeyID ) == _ITEM_TYPE_WEPON_WAND )
	{
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
		if( dwItemIndex > 0 ) // ������ �������� ���ݷ� �˾ƿ���
		{
			HTint iEffectID = 0, iParam1 = 0, iParam2 = 0;
			// ������ �⺻ �Ӽ�
			if( g_pParamMgr->HT_bGetItemEffect1ID( dwItemIndex, &iEffectID ) && HT_bSkillSystem_IsDamageEffect( iEffectID ) )
			{
				iParam1 = iParam2 = 0;
				g_pParamMgr->HT_bGetItemEffect1Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect1Param2( &iParam2 );
				iMinDamage += iParam1; iMaxDamage += iParam2;
			}
			if( g_pParamMgr->HT_bGetItemEffect2ID( dwItemIndex, &iEffectID ) && HT_bSkillSystem_IsDamageEffect( iEffectID ) )
			{
				iParam1 = iParam2 = 0;
				g_pParamMgr->HT_bGetItemEffect2Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect2Param2( &iParam2 );
				iMinDamage += iParam1; iMaxDamage += iParam2;
			}
			if( g_pParamMgr->HT_bGetItemEffect3ID( dwItemIndex, &iEffectID ) && HT_bSkillSystem_IsDamageEffect( iEffectID ) )
			{
				iParam1 = iParam2 = 0;
				g_pParamMgr->HT_bGetItemEffect3Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect3Param2( &iParam2 );
				iMinDamage += iParam1; iMaxDamage += iParam2;
			}
			if( g_pParamMgr->HT_bGetItemEffect4ID( dwItemIndex, &iEffectID ) && HT_bSkillSystem_IsDamageEffect( iEffectID ) )
			{
				iParam1 = iParam2 = 0;
				g_pParamMgr->HT_bGetItemEffect4Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect4Param2( &iParam2 );
				iMinDamage += iParam1; iMaxDamage += iParam2;
			}
			if( g_pParamMgr->HT_bGetItemEffect5ID( dwItemIndex, &iEffectID ) && HT_bSkillSystem_IsDamageEffect( iEffectID ) )
			{
				iParam1 = iParam2 = 0;
				g_pParamMgr->HT_bGetItemEffect5Param1( &iParam1 );
				g_pParamMgr->HT_bGetItemEffect5Param2( &iParam2 );
				iMinDamage += iParam1; iMaxDamage += iParam2;
			}
			// ������ ���� �Ӽ�
			//g_cItemSystem->HT_byItemSystem_GetMainRefineLevel
			//g_cItemSystem->HT_bItemSystem_GetMainRefineEffect
			
		}
	}*/
	m_iParam1 = HTint( 0.003*(iSoul+iNerve+100)*iParam1 + (iSoul+iNerve-23)/2 
					+ 0.05*iMinDamage*iNerve/* +0.05*�����̼Ӽ�*�Ű�(����/���ٸ��ٸ� ����)*/ +iMinDamage );
	m_iParam2 = HTint( 0.003*(iSoul+iNerve+100)*iParam2 + (iSoul+iNerve-23)/2 
					+ 0.05*iMaxDamage*iNerve/* +0.05*�����̼Ӽ�*�Ű�(����/���ٸ��ٸ� ����)*/ +iMaxDamage );
}

// ��ų Effect�� ���ݷ� ��������
HTbool HTSkillSystem::HT_bSkillSystem_IsDamageEffect( HTint iEffectID )
{
	if( iEffectID == eTNAfn_Damage )
				//|| iEffectID == eTNAfn_Fire || iEffectID == eTNAfn_Cold 
				//|| iEffectID == eTNAfn_Lightning || iEffectID == eTNAfn_Poison
				//|| iEffectID == eTNAfn_DamageSplash || iEffectID == eTNAfn_FireSplash 
				//|| iEffectID == eTNAfn_ColdSplash	|| iEffectID == eTNAfn_LightningSplash 
				//|| iEffectID == eTNAfn_PoisonSplash )
		return HT_TRUE;
	else
		return HT_FALSE;
}

HTbool HTSkillSystem::HT_bSkillSystem_GetEffect
( HTint iEffectID, CHTString* pString, HTint iParam1, HTint iParam2, HTint iFunction, HTint iDecreaseVal, HTint idSkill )
{ 
	// ����/����� ��ų �� ���ݷ¸� ���� ����Ѵ�.
	if( CHTParamIDCheck::HT_bIsPCSkillDevGaru( idSkill ) && HT_bSkillSystem_IsDamageEffect(iEffectID ) )
		HT_bSkillSystem_SetDamageParam( iEffectID, iParam1, iParam2 );
	else
	{
		m_iParam1 = iParam1;
		m_iParam2 = iParam2;
	}
	m_iDecreaseVal = iDecreaseVal;

	CHTString szMessage;
	switch( iEffectID )
	{
		case eTNAfn_DamageTP: // Duration���� param1 ��ŭ�� TP ������ 
			HT_vSkillSystem_SetMessage( eMsgEffectDamageTP, pString );
            break;
		case eTNAfn_DOTbyDice: // functionȮ���� duration���� param1~param2 �� ������
			HT_vSkillSystem_SetMessage( eMsgEffectDOTbyDice, pString );
            break;
		case eTNAfn_HealPlus: //HPȸ���� param1��ŭ�� �߰�ȸ��
			HT_vSkillSystem_SetMessage( eMsgEffectHealPlus, pString );
			break;
		case eTNAfn_RecoverTPPlus:	//TPȸ���� param1��ŭ�� �߰�ȸ��
			HT_vSkillSystem_SetMessage( eMsgEffectRecoverTPPlus, pString );
			break;
		case eTNAfn_Damage :
			if( iDecreaseVal > 0 )
				// ���ݷ� %d - %d(���� �������� %d%%����), iParam1, iParam2, iDecreaseVal
				HT_vSkillSystem_SetMessage( eMsgEffectDamageLimitLevel, pString );
			else
				// ���ݷ� %d - %d, iParam1, iParam2); 
				HT_vSkillSystem_SetMessage( eMsgEffectDamage, pString );
			break;
		case eTNAfn_DamageSplash :
			// ���÷��� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDamageSplash, pString );
			break;
		//case eTNAfn_EnergyOfSword :
		// �� ���ݷ� %d%% - %d%% ���, iParam1, iParam2
		//	HT_vSkillSystem_SetMessage( eMsgEffectEnergyOfSword, pString );
		//	break;
		case eTNAfn_PierceDamage :
			// ������ ������ ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDefenceIgnoreDamage, pString );
			break;
		case eTNAfn_Fire :
			// ȭ�� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectFire, pString );
			break;			
		case eTNAfn_Cold :
			// �ñ� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectCold, pString );
			break;			
		case eTNAfn_Lightning :
			// ���� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectLightning, pString );
			break;		
		case eTNAfn_Poison	 :
			// �� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPoison, pString );
			break;
		case eTNAfn_FireSplash :
			// ȭ�� ���÷��� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectFireSplash, pString );
			break;			
		case eTNAfn_ColdSplash :
			// �ñ� ���÷��� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectColdSplash, pString );
			break;			
		case eTNAfn_LightningSplash :
			// ���� ���÷��� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectLightningSplash, pString );
			break;		
		case eTNAfn_PoisonSplash	 :
			// �� ���÷��� ���ݷ� %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPoisonSplash, pString );
			break;
		//case eTNAfn_AdditionalDamage :
		case eTNAfn_BonusDamage :
		case eTNAfn_BonusDamage2 :
			// %s�� ���ݷ� %d - %d �߰�, skillName, iParam1, iParam2
			g_pEngineHandler->HT_hrGetPCSkillName( iFunction, &m_szParamString );
			HT_vSkillSystem_SetMessage( eMsgEffectSkillDamagePlus, pString );
			break;

		case eTNAfn_Summon :
		{
			//g_pEngineHandler->HT_hrGetMonsterName( iParam1 , &m_szParamString );
			g_pParamMgr->HT_bGetMonsterName( iParam1, &m_szParamString );
			//pString->HT_szFormat("%s %d���� ��ȯ", strName.HT_szGetString(), iParam2);
			HT_vSkillSystem_SetMessage( eMsgEffectSummon, pString );
		}
			break;			
		case eTNAfn_Illusion :
		{
			//g_pEngineHandler->HT_hrGetMonsterName( iParam1 , &m_szParamString );
			g_pParamMgr->HT_bGetMonsterName( iParam1, &m_szParamString );
			// %s %d���� ����, strName.HT_szGetString(), iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectIllusion, pString );
		}
			break;	
		case eTNAfn_MoveSpeedPlus :
			// �̵��ӵ� %d����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMoveSpeedPlus, pString );
			break;		
		case eTNAfn_AttackSpeedPlus :
			// ���ݼӵ� %d����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAttackSpeedPlus, pString );
			break;	
		case eTNAfn_MoveSpeedMinus :
			// �̵��ӵ� %d����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMoveSpeedMinus, pString );
			break;		
		case eTNAfn_AttackSpeedMinus :
			// ���ݼӵ� %d����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAttackSpeedMinus, pString );
			break;	
		//case eTNAfn_CastSpeedMinus :
		//	// ĳ���� �ӵ� %d����, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCastSpeedMinus, pString );
		//	break;	
		//case eTNAfn_CastSpeedPlus :
		//	// ĳ���� �ӵ� %d����, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCastSpeedPlus, pString );
		//	break;	
		case eTNAfn_Invisible :
			//pString->HT_szFormat("�������");
			HT_vSkillSystem_SetMessage( eMsgEffectInvisible, pString );
			break;
		case eTNAfn_WizardEyes :
			//pString->HT_szFormat("������� ����");
			HT_vSkillSystem_SetMessage( eMsgEffectWizardEyes, pString );
			break;
		case eTNAfn_Hold :
			//pString->HT_szFormat("HOLD");
			HT_vSkillSystem_SetMessage( eMsgEffectHold, pString );
			break;			
		case eTNAfn_Stun :
			//pString->HT_szFormat("STUN");
			HT_vSkillSystem_SetMessage( eMsgEffectStun, pString );
			break;			
		case eTNAfn_Sleep :
			//pString->HT_szFormat("SLEEP");
			HT_vSkillSystem_SetMessage( eMsgEffectSleep, pString );
			break;			
		case eTNAfn_Blind :
			//pString->HT_szFormat("BLIND");
			HT_vSkillSystem_SetMessage( eMsgEffectBlind, pString );
			break;			
		case eTNAfn_ExpandBag30 :
			//pString->HT_szFormat("�κ��丮 Ȯ�� %dX%d", iParam1, iParam2);
			HT_vSkillSystem_SetMessage( eMsgEffectExpandBag, pString );
			break;

		case eTNAfn_Concentration :
			//pString->HT_szFormat("Cast ���� %d%% ����", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectConcentration, pString );
			break;
		case eTNAfn_Disruption :
			//pString->HT_szFormat("���� Casting ����");
			HT_vSkillSystem_SetMessage( eMsgEffectDisruption, pString );
			break;
		case eTNAfn_Invulnerable :
			//pString->HT_szFormat("��������");
			HT_vSkillSystem_SetMessage( eMsgEffectInvulnerable, pString );
			break;
		case eTNAfn_MagicShield :
			//pString->HT_szFormat("Max HP %d", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMagicShield, pString );
			break;

		case eTNAfn_StealHP :
			//pString->HT_szFormat("�������� %d%% HP ��ħ", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectStealHP, pString );
			break;		
		case eTNAfn_StealTP :
			//pString->HT_szFormat("�������� %d%% TP ��ħ", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectStealTP, pString );
			break;		
		case eTNAfn_MultipleStrike :
			//pString->HT_szFormat("%d%% ������ %dȸ", iParam2, iParam1 );
			HT_vSkillSystem_SetMessage( eMsgEffectMultipleStrike, pString );
			break;	
		case eTNAfn_CriticalStrike :
			// %dȮ���� ���ݷ� %d%%����, iParam1, iParam2
			if( iFunction == 0 )
				HT_vSkillSystem_SetMessage( eMsgEffectCriticalStrikeRate, pString );
			else // %dȮ���� ���ݷ� %d����, iParam1, iParam2
				HT_vSkillSystem_SetMessage( eMsgEffectCriticalStrike, pString );
			break;	
		case eTNAfn_PierceStrike :
			// ������ ������ ���ݷ� %d%%, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPierceStrike, pString );
			break;
		case eTNAfn_PierceStrike2 :
			// ���� %d�� ���ҽ�Ų ���ݷ�, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDefenceMinusDamage, pString );
			break;
		case eTNAfn_HPDown :
			// HP %d%%����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectHPDown, pString );
			break;
		case eTNAfn_KnockBack :
			// %dȮ���� KnockBack %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectKnockBack, pString );
			break;
		case eTNAfn_SpiritLink :
			// %d%%��ŭ�� ��Ƽ���� ���� �������� ���
			HT_vSkillSystem_SetMessage( eMsgEffectAbsorbPartyPhs, pString );
			break;
		case eTNAfn_Heal :
		{
			if( iFunction == 0 )
				// HP %dȸ�� , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectHeal, pString );
			else if( iFunction == 1 )
			{
				// ���HP %dȸ�� , iParam1*����/50
				m_szParamString.HT_szFormat("%d", iParam1*(1+g_cStatus->HT_nGetChakraSoul()/50) );
				HT_vSkillSystem_SetMessage( eMsgEffectTargetHeal, pString );
			}
			else if( iFunction == 2 )
			{
				// HP %dȸ�� , iParam1+��HP/iParam2
				m_szParamString.HT_szFormat("%d", iParam1+g_cMainCharacter->HT_nMainChar_GetMAXHP()/iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectHeal2, pString );
			}
			else
				// HP %d%%ȸ�� , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectHealRate, pString );
		}
			break;	
		case eTNAfn_RecoverTP :
		{
			if( iFunction == 0 )
				// TP %dȸ�� , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTP, pString );
			else if( iFunction == 1 )
			{
				// ���TP %dȸ�� , iParam1*����/50
				m_szParamString.HT_szFormat("%d", iParam1*g_cStatus->HT_nGetChakraSoul()/50);
				HT_vSkillSystem_SetMessage( eMsgEffectTargetHealTP, pString );
			}
			else if( iFunction == 2 )
			{
				// TP %dȸ�� , iParam1+��TP/iParam2
				m_szParamString.HT_szFormat("%d", iParam1+g_pMainBar->HT_iMainBar_GetMaxTP()/iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTP2, pString );
			}
			else
				// TP %d%%ȸ�� , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTPRate, pString );
		}
			break;		
		//case eTNAfn_iACrificeHP :
		//	// HP �Ҹ� %d, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectiACrificeHP, pString );
		//	break;
		//case eTNAfn_Cure :
		//	// EffectID %d, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCure, pString );
		//	break;
		case eTNAfn_TPBurn :
		{
			if( iParam2 == 0 )
				// TP %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPBurn2, pString );
			else
				// TP %d�� %d%% ���ݷ����� ��ȯ, iParam1, iParam2
				HT_vSkillSystem_SetMessage( eMsgEffectTPBurn, pString );
		}
			break;
		case eTNAfn_Resurrect :
			// ����ġ %dȸ��
			HT_vSkillSystem_SetMessage( eMsgEffectResurrect, pString );
			break;		
		case eTNAfn_ReflectDamage :
			if( iFunction == 1 )
				// ������ �ݻ� %d%%, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectReflectDamage, pString );
			else // ������ �ݻ� %d, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectReflectDamagePlus, pString );
			break;	
		case eTNAfn_AbsorbDamage :
			// ������ ��� %d%%, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAbsorbDamage, pString );
			break;	
		case eTNAfn_AbsorbElementalDamage : 
			// �Ӽ� ������ ��� &d%%, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAbsorbElementalDamage, pString );
			break;	
		case eTNAfn_Terror :
			// TERROR
			HT_vSkillSystem_SetMessage( eMsgEffectTerror, pString );
			break;			
		case eTNAfn_Taunt :
			// HAUL
			HT_vSkillSystem_SetMessage( eMsgEffectTaunt, pString );
			break;
		case eTNAfn_DeTaunt :
			// Ÿ���� ������ Ȯ�� ����
			HT_vSkillSystem_SetMessage( eMsgEffectDefaunt, pString );
			break;
		case eTNAfn_RangeUp :
			// �����Ÿ� %d����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectRangeUp, pString );
			break;	

		case eTNAfn_WeaponMastery :
		//case eTNAfn_WeaponMastery2 :
		{
			switch( iFunction )
			{
				case _ITEM_TYPE_WEPON_SWORD	: //str.HT_szFormat("��");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassSword, &m_szParamString ); break;
				case _ITEM_TYPE_WEPON_AX : //str.HT_szFormat("����");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &m_szParamString ); break;
				case _ITEM_TYPE_WEPON_LANCE	: //str.HT_szFormat("â");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &m_szParamString ); break;			
				case _ITEM_TYPE_WEPON_MACE	: //str.HT_szFormat("�б�");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_GLOVE	: //str.HT_szFormat("���� ����");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_WAND	: //str.HT_szFormat("���� ����");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &m_szParamString ); break;			
				case _ITEM_TYPE_WEPON_BOW	: //str.HT_szFormat("Ȱ");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_DAGGER : //str.HT_szFormat("�ܰ�");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &m_szParamString ); break;
				default : return HT_FALSE;
			}
			
			if ( iEffectID == eTNAfn_WeaponMastery )
			{
				//pString->HT_szFormat("%s ���ݷ� %d, ���� �ӵ� %d����", str.HT_szGetString(), iParam1, iParam2);
				if( iParam2 == 0 ) // %s ���ݷ� %d
					HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery, pString );
				else // %s ���ݷ� %d, ���� �ӵ� %d����
					HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery2, pString );
			}
			else
				//pString->HT_szFormat("%s ���ݼ��� %d����", str.HT_szGetString(), iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery3, pString );
		}
			break;
		case eTNAfn_DamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlus, pString );
			else
				//pString->HT_szFormat("���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_DamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamageMinus, pString );
			else
				//pString->HT_szFormat("���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamageMinusRate, pString );
		}
			break;
		case eTNAfn_FireDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("ȭ�� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamagePlus, pString );
			else
				//pString->HT_szFormat("ȭ�� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_FireDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("ȭ�� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamageMinus, pString );
			else
				//pString->HT_szFormat("ȭ�� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamageMinusRate, pString );
		}
			break;
		case eTNAfn_ColdDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ñ� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamagePlus, pString );
			else
				//pString->HT_szFormat("�ñ� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_ColdDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ñ� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamageMinus, pString );
			else
				//pString->HT_szFormat("�ñ� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamageMinusRate, pString );
		}
			break;
		case eTNAfn_LightningDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("���� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamagePlus, pString );
			else
				//pString->HT_szFormat("���� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_LightningDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("���� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamageMinus, pString );
			else
				//pString->HT_szFormat("���� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamageMinusRate, pString );
		}
			break;
		case eTNAfn_PoisonDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamagePlus, pString );
			else
				//pString->HT_szFormat("�� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_PoisonDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�� ���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamageMinus, pString );
			else
				//pString->HT_szFormat("�� ���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamageMinusRate, pString );
		}
			break;
		case eTNAfn_FireResistPlus :
		{
			if( iFunction == 1 )
				// ȭ�� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistPlusRate, pString );
			else
				// ȭ�� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistPlus, pString );
		}
			break;		
		case eTNAfn_FireResistMinus:
		{
			if( iFunction == 1 )
				// ȭ�� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistMinusRate, pString );
			else
				// ȭ�� ���׷� %d ����, iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistMinus, pString );
		}
			break;
		case eTNAfn_ColdResistPlus :
		{
			if( iFunction == 1 )
				// �ñ� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistPlusRate, pString );	
			else
				// �ñ� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistPlus, pString );
		}
			break;	
		case eTNAfn_ColdResistMinus :
		{
			if( iFunction == 1 )
				// �ñ� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistMinusRate, pString );
			else
				// �ñ� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistMinus, pString );
		}
			break;
		case eTNAfn_LightningResistPlus :
		{
			if( iFunction == 1 )
				// ���� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistPlusRate, pString );
			else
				// ���� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistPlus, pString );
		}
			break;	
		case eTNAfn_LightningResistMinus :
		{
			if( iFunction == 1 )
				// ���� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistMinusRate, pString );
			else
				// ���� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistMinus, pString );
		}
			break;
		case eTNAfn_PoisonResistPlus :
		{
			if( iFunction == 1 )
				// �� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistPlusRate, pString );
			else
				// �� ���׷� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistPlus, pString );
		}
			break;		
		case eTNAfn_PoisonResistMinus :
		{
			if( iFunction == 1 )
				// �� ���׷� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistMinusRate, pString );
			else
				// �� ���׷� %d����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistMinus, pString );
		}
			break;
		case eTNAfn_AllResistPlus :
		{
			if( iFunction == 0 )
				// ��� ���׷� %d����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistPlus, pString );
			else
				// ��� ���׷� %d%%����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistPlusRate, pString );
		}
			break;
		case eTNAfn_AllResistMinus :
		{
			if( iFunction == 0 )
				// ��� ���׷� %d����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistMinus, pString );
			else
				// ��� ���׷� %d%%����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistMinusRate, pString );
		}
			break;
		case eTNAfn_AllStatePlus :
		{
			if( iFunction == 0 )
				// ��� ��ũ�� %d����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatPlus, pString );
			else
				// ��� ��ũ�� %d%%����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatPlusRate, pString );
		}
			break;
		case eTNAfn_AllStateMinus :
		{
			if( iFunction == 0 )
				// ��� ��ũ�� %d����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatMinus, pString );
			else
				// ��� ��ũ�� %d%%����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatMinusRate, pString );
		}
			break;
		case eTNAfn_AllDamagePlus :
			// ��� �Ӽ� ���ݷ� %d%% ���, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAllDamageUp, pString );
			break;
		case eTNAfn_AllDamageMinus :
			// ��� �Ӽ� ���ݷ� %d%% ����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAllDamageDown, pString );
			break;
		case eTNAfn_MusclePlus :
			// ������ ��ũ�� %d ����", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMusclePlus, pString );
			break;		
		case eTNAfn_MuscleMinus :
			// ������ ��ũ�� %d ����", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMuscleMinus, pString );
			break;
		case eTNAfn_NervesPlus :
			// �Ű��� ��ũ�� %d ����", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectNervesPlus, pString );
			break;		
		case eTNAfn_NervesMinus :
			// �Ű��� ��ũ�� %d ����", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectNervesMinus, pString );
			break;
		case eTNAfn_HeartPlus :
			// ������ ��ũ�� %d ����", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectHeartPlus, pString );
			break;		
		case eTNAfn_HeartMinus :
			// ������ ��ũ�� %d ����", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectHeartMinus, pString );
			break;
		case eTNAfn_MindPlus :
			// ������ ��ũ�� %d ����", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMindPlus, pString );
			break;		
		case eTNAfn_MindMinus :
			// ������ ��ũ�� %d ����", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMindMinus, pString );
			break;
		case eTNAfn_AttackRatePlus :
		{
			if( iFunction == 1 )
				// ���ݼ��� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRatePlusRate, pString );
			else
				// ���ݼ��� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRatePlus, pString );
		}
			break;		
		case eTNAfn_AttackRateMinus :
		{
			if( iFunction == 1 )
				// ���ݼ��� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRateMinusRate, pString );
			else
				// ���ݼ��� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRateMinus, pString );
		}
			break;
		case eTNAfn_DodgeRatePlus :
		{
			if( iFunction == 1 )
				// ȸ�� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRatePlusRate, pString );
			else
				// ȸ�� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRatePlus, pString );
		}
			break;		
		case eTNAfn_DodgeRateMinus :
		{
			if( iFunction == 1 )
				// ȸ�� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRateMinusRate, pString );
			else
				// ȸ�� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRateMinus, pString );
		}
			break;
		case eTNAfn_ACPlus :
		{
			if( iFunction == 0 )
			{
				if( iDecreaseVal > 0 )
					//pString->HT_szFormat("�� %d ����(���� �������� %d%%����)", iParam1, iDecreaseVal );
					HT_vSkillSystem_SetMessage( eMsgEffectACPlusLimitLevel, pString );
				else
					//pString->HT_szFormat("�� %d ����", iParam1);
					HT_vSkillSystem_SetMessage( eMsgEffectACPlus, pString );
			}
			else
				//pString->HT_szFormat("�� %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACPlusRate, pString );
		}
			break;		
		case eTNAfn_ACMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�� %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACMinus, pString );
			else
				//pString->HT_szFormat("�� %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACMinusRate, pString );
		}
			break;
		case eTNAfn_MaxHPPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ִ� HP %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlus, pString );
			else
				//pString->HT_szFormat("�ִ� HP %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxHPMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ִ� HP %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinus, pString );
			else
				//pString->HT_szFormat("�ִ� HP %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinusRate, pString );
		}
			break;
		case eTNAfn_MaxHPPPlus :
		{
			//�ִ� HP %d%% ����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxHPPMinus :
		{
			// �ִ� HP %d%% ����, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinusRate, pString );
		}
			break;
		case eTNAfn_SaveTPCost : // TP �Ҹ� %d ����
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("TP �Ҹ� %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectCostTP, pString );
			else
				//pString->HT_szFormat("TP �Ҹ� %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectCostTPRate, pString );
		}
			break;
		case eTNAfn_HPRecoveryPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("HP ȸ�� %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryPlus, pString );
			else
				//pString->HT_szFormat("HP ȸ�� %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryPlusRate, pString );
		}
			break;		
		case eTNAfn_HPRecoveryMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("HP ȸ�� %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryMinus, pString );
			else
				//pString->HT_szFormat("HP ȸ�� %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryMinusRate, pString );
		}
			break;
		case eTNAfn_MaxTPPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ִ� TP %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPPlus, pString );
			else
				//pString->HT_szFormat("�ִ� TP %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxTPMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("�ִ� TP %d ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPMinus, pString );
			else
				//pString->HT_szFormat("�ִ� TP %d%% ����", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPMinusRate, pString );
		}
			break;
		case eTNAfn_TPRecoveryPlus :
		{
			if( iFunction == 0 )
				// TP ȸ�� %d ����", iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryPlus, pString );
			else
				// TP ȸ�� %d%% ����", iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryPlusRate, pString );
		}
			break;		
		case eTNAfn_TPRecoveryMinus :
		{
			if( iFunction == 0 )
				// TP ȸ�� %d ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryMinus, pString );
			else
				// TP ȸ�� %d%% ����, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryMinusRate, pString );
		}
			break;

		case eTNAfn_EnhanceWeapon : 
			// ���� ��ȭ���õ�� +n ��� 
			HT_vSkillSystem_SetMessage( eMsgEffectRefinePlus, pString );
			break;
	
		case eTNAfn_ResetStat :
			// ��ũ�� �ʱ�ȭ
			HT_vSkillSystem_SetMessage( eMsgEffectResetState, pString );
			break;
		case eTNAfn_ResetSkill :
			// ��ų �ʱ�ȭ
			HT_vSkillSystem_SetMessage( eMsgEffectResetSkill, pString );
			break;		
		case eTNAfn_PreventRegenHP :
			// HP �ڵ� ȸ�� ����
			HT_vSkillSystem_SetMessage( eMsgEffectPreventHPRecovery, pString );
			break;
		case eTNAfn_PreventRegenTP :
			// TP �ڵ� ȸ�� ����
			HT_vSkillSystem_SetMessage( eMsgEffectPreventTPRecovery, pString );
			break;	
		case eTNAfn_SkillUp :
			// %s ���� %d ����, skillname, iParam2
			g_pEngineHandler->HT_hrGetPCSkillName( iParam1, &m_szParamString );
			HT_vSkillSystem_SetMessage( eMsgEffectSkillLevelUp, pString );
			break;		

		case eTNAfn_EnhanceHardnessOfArmor :
			// ������ ������������ ����
			HT_vSkillSystem_SetMessage( eMsgEffectEnhanceHardnessOfArmor, pString );
			break;

		case eTNAfn_FixedDamagePlus :
			// ���� ������ %s~%s �߰�
			HT_vSkillSystem_SetMessage( eMsgEffectFixedDamagePlus, pString );
			break;

		case eTNAfn_FixedDamagePlus2 :
			// ���� ������ %s~%s �߰�
			HT_vSkillSystem_SetMessage( eMsgEffectFixedDamagePlus, pString );
			break;

		case eTNAfn_DamageBonusForNextAttack :	
			// 1ȸ ���ݵ����� %s%% ���
			HT_vSkillSystem_SetMessage( eMsgEffectDamageBonusForNextAttack, pString );
			break;

		case eTNAfn_PercentDamage :
			// ���� �ð����� %s%%��ŭ ���������� �ڽ��� HP ����
			HT_vSkillSystem_SetMessage( eMsgEffectMinusPercentHPforTime, pString );
			break;
		case eTNAfn_Dash :
			// %s��ŭ�� �Ÿ��� ���������� �뽬
			HT_vSkillSystem_SetMessage( eMsgEffectQuickDash, pString );
			break;
		case eTNAfn_DefensePlus :
			if( iFunction == 0 )
				// %s��ŭ�� ���� ���
				HT_vSkillSystem_SetMessage( eMsgEffectPlusDefense, pString );
			else
				// %s%%��ŭ�� ���� ���
				HT_vSkillSystem_SetMessage( eMsgEffectPlusPercentDefense, pString );
			break;

		case eTNAfn_DamagePlus2 :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("���ݷ� %d - %d ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlus, pString );
			else
				//pString->HT_szFormat("���ݷ� %d%% - %d%% ����", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlusRate, pString );
		}
			break;

		case eTNAfn_BonusExp :
			if( iFunction == 0 )
			{
				// ���� ����ġ %s ����
				HT_vSkillSystem_SetMessage( eMsgEffectBonusExp, pString );
			}
			else
			{
				// ���� ����ġ %s% ����
				HT_vSkillSystem_SetMessage( eMsgEffectBonusExpRate, pString );
			}
			break;
		case 2241 :
			{
				switch (iParam1)	// ������ ���� ����
				{
				case 33:
					HT_vSkillSystem_SetMessage( eMsgEffectEtcSkillDisp1, pString );
					break;
				case 289:
					HT_vSkillSystem_SetMessage( eMsgEffectEtcSkillDisp2, pString );
					break;
				case 801:
					HT_vSkillSystem_SetMessage( eMsgEffectEtcSkillDisp3, pString );
					break;
				}
			}
			break;
		
		default:
			return HT_FALSE;
	}

	return HT_TRUE;
}

//---���콺 ����Ʈ�� �Ѱܹ޾� Ȱ��ȭ�� ��ų �߿� ����Ʈ ��ġ�� �ִ°��� Index�� ��ȯ----//
//DWORD HTSkillSystem::HT_dwSkillSystem_MousePtToSkillPosCheck( HTPoint pPt )
DWORD HTSkillSystem::HT_dwSkillSystem_MousePtToSkillPosCheck( HTint iBitmapNo )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if(t->sSkill.m_iSkill_BitmapNo == iBitmapNo)
		{
			return t->sSkill.m_dwSkill_Index;
		}

		t = t->next;
	}

	return -1;
}

HTvoid HTSkillSystem::HT_vSkillSystem_SetMessage( HTint idMessage, CHTString* pstrMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	//------------------------------------------------------------------------------------//
	// ���� - ��ų ������ ��� �޼����� �����ϰ�, �Ķ���� ���� �ܺο��� ���� �Է��ϴ� ������� �Ѵ�. 
	//------------------------------------------------------------------------------------//
	// ������ 3�� �� ��
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vSkillSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSkillSystem_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vSkillSystem_SetParamTextForMessage( sParam3, &szOut3 );

		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vSkillSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSkillSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vSkillSystem_SetParamTextForMessage( sParam1, &szOut1 );
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pstrMessage = szString;
}


HTvoid HTSkillSystem::HT_vSkillSystem_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// Param1
		case eMsgParamEffectParam1	:
			pszParam->HT_szFormat( "%d", m_iParam1 );
			break;

		// Param2
		case eMsgParamEffectParam2	:
			pszParam->HT_szFormat( "%d", m_iParam2 );
			break;

		case eMsgParamEffectDecVal	:
			pszParam->HT_szFormat( "%d", m_iDecreaseVal );
			break;

		case eMsgParamEffectString	:
			*pszParam = m_szParamString;
			break;

		case 535:	// �ӽÿ� �ڵ��� 
			{
				int iLevel = HT_bySkillSystem_GetSkill_Level(m_iFunction);
				pszParam->HT_szFormat( "%d", m_iParam1 * iLevel);
			}
			break;

		case 536:	// �ӽÿ� �ڵ��� 
			{
				int iLevel = HT_bySkillSystem_GetSkill_Level(m_iFunction);
				pszParam->HT_szFormat( "%d", m_iParam2 * iLevel);
			}
			break;
		default:
			break;
	}
}