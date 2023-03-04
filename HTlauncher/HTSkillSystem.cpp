
#include "stdAfx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSkillInventory.h"


HTSkillSystem::HTSkillSystem()
{
	//----------LL 초기화---------//
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

	//	전체 스킬 셋팅
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
		// 실제로 존재하는 스킬인지 파악. 
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

//	스킬 리스트 북 초기화_서버에서 초기 스킬 리스트를 받는다.
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
			// GM의 경우는 리턴
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

				//	스킬레벨이 전부 0으로 떨어졌는지 체크
				if( t->sSkill.m_bySkill_Level > 0 )
					iSkillLevelCount++;
				break;
			}*/

			// 해당 스킬 ID를 찾아 스킬 레벨 셋팅
			if ( t->sSkill.m_dwSkill_Index == i + iStart)
			{
				t->sSkill.m_bySkill_Level = bySkill[i];

				//	데바/가루다 스킬중 3302(아바리) 스킬 처리_사정거리 추가
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
	// 스킬정보가 제대로 기록되어 있는지 파일저장 (선영범)
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
		
		HT_g_vLogFile( "\n스킬 정보를 잘못받아서 다시 요청함...\n" );

		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat( "Send_MSG_InitSkill" );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

		HT_DELETE( info );
	}
*/
	// 스킬트리 다시 그리기
	g_cSkillInventory->HT_hrSkillItemInit();
	//	순서상 아이템과 스킬이후에 정보가 내려오기 때문에 퀵슬롯 로딩을 여기서 함
	g_cQuickSlot->HT_vIconLoad();
}

//----------반환값들----------//
//----------스킬의 레벨---------//
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

//	레벨업으로 변경된 스킬의 공격속도를 셋팅
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

//	레벨업으로 변경된 스킬의 캐스팅속도를 셋팅
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

//	레벨업으로 변경된 스킬의 사정거리
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

//	레벨으로 변경된 스킬의 이동속도를 셋팅
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
			//	데바/가루다 스킬중 3302(아바리) 스킬 처리_사정거리 추가
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

// 스킬 이름 조사
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

//	스킬의 종족,주신,자유스킬 차례를 넘겨줌
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

//	서버로부터 스킬 Learn 정보를 받느다.
HTvoid HTSkillSystem::HT_vSkillSystem_SetLearn( S_TNSKILL_DATA info )
{
	HT_SKILL_NODE *t;
	
	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		if( t->sSkill.m_dwSkill_Index == info.snID )
		{
			t->sSkill.m_bySkill_Level = info.byLevel;
			//	데바/가루다 스킬중 3302(아바리) 스킬 처리_사정거리 추가
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

//----------스킬의 이미지 아이디를 넘겨줌---------//
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

//	전체 스킬 지우기
HTvoid HTSkillSystem::HT_vSkillSystem_TotalSkillDelete()
{
	m_bTribeAttack_Count = 0;
	m_bJusinAttack_Count = 0;
	m_bFreeAttack_Count = 0;
	HT_LL_hrDeleteAll();
}

//	전체 스킬의 레벨을 전부 초기화
HTvoid HTSkillSystem::HT_vSkillSystem_TotalSkillLevelInit()
{
	HT_SKILL_NODE *t;

	t = m_sSkillHead->next;
	while( t != m_sSkillTail )
	{
		t->sSkill.m_bySkill_Level = 0;
		t = t->next;
	}

	//	아이콘 전부 삭제
	g_cQuickSlot->HT_vTotalDeleteIcon( 0 );
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTSkillSystem::HT_LL_vInitList()
{
	m_sSkillHead = NULL;
	m_sSkillTail = NULL;

	m_sSkillHead = new HT_SKILL_NODE;
	m_sSkillTail = new HT_SKILL_NODE;

	m_sSkillHead->next = m_sSkillTail;
	m_sSkillTail->next = m_sSkillTail;

}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
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

//----------LL 데이타 지우기---------//
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

//----------LL 데이타 전부 지우기---------//
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

//----------등록되어있는 스킬인지 검사-----------//
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
// 예외 - 스킬 정보의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
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
			// 스킬 정보 얻어오기
			HT_ITEM_DATA* pData = HT_NULL;
			HT_ITEM_EXPANSION_DATA* pExtData = HT_NULL;
			CHTString str;

			HTbyte byteOut;
			HTint iOut = 0;
			HTshort sOut = 0;

			// 스킬 이름
			if( g_pEngineHandler->HT_hrGetPCSkillName( t->sSkill.m_dwSkill_Index, &str ) == HT_FAIL )
				return winSizeX;

			vInfo.strName.str = str;
			if( t->sSkill.m_bySkill_Level > 0 ) // 스킬 레벨
			{
				str.HT_szFormat("  Lvl %d", t->sSkill.m_bySkill_Level); 
				vInfo.strName.str += str;
			}
			vInfo.strName.color = g_ColorTable[15];		// white
			winSizeX = vInfo.strName.str.HT_nGetSize();

			// 설명
			g_pEngineHandler->HT_hrGetPCSkillDesc( t->sSkill.m_dwSkill_Index, &vInfo.strDescription.str );
			if( vInfo.strDescription.str == HT_INFO_SKILL_DESCRIPT_NULL )
				vInfo.strDescription.str.HT_hrCleanUp();
			else
				vInfo.strDescription.color = g_ColorTable[16]; //light grey

			// 스킬 타입
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
			
			// 다음 레벨의 제한사항
			// 스킬 정보 Lock 설정
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
					// 요구 레벨 조건
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedCondition, &pData->str );
				else
				{
					// 다음 레벨 조건
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNextCondition, &pData->str );
					bNextInfo = HT_TRUE ; // 다음 레벨의 세부 정보를 보여줌
				}

				pData->color = g_ColorTable[17];	// yellow
				vInfo.vLimitStr.push_back(pData);
				winSizeX = max(winSizeX, pData->str.HT_nGetSize());

				// 요구레벨
				if( g_pParamMgr->HT_bGetPCSkillReqLevel( &byteOut ) == true && byteOut > 0 )
				{
					pData = new HT_ITEM_DATA;
					// %d Level 필요
					HT_vSkillSystem_SetMessage( eMsgItemInfoNeedLevel, &str );
					pData->str.HT_szFormat( str.HT_szGetString(), byteOut );


					if( g_cStatus->HT_byGetLevel() >= byteOut )
						pData->color = g_ColorTable[17];	// yellow
					else
						pData->color = g_ColorTable[11];	//red

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				// 습득조건 스킬
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
					// %s Lvl %d 필요
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
					// %s Lvl %d 필요		
					CHTString szMessage;
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedSkillLevel, &szMessage );
					pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteOut );

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
				g_pParamMgr->HT_bUnLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level+1 );
			}

			// 현제 레벨의 스킬 정보 Lock 설정
			if( g_pParamMgr->HT_bLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level ) == false )
				return winSizeX;

			//-----제한사항------//
			// 요구되는 장착_무기타입
			if( g_pParamMgr->HT_bGetPCSkillReqWeaponType( &iOut ) == true && iOut > 0 )
			{
				HTRESULT tribe = HT_FALSE;
				str.HT_hrCleanUp();

				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				if( BIT_AND( _ITEM_TYPE_WEPON_SWORD, iOut ) )
				{
					//str = "검"; 
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassSword, &pExtData->basic.str );
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_AX, iOut ) )
				{
					if(tribe) //str += ", 도끼";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str = "도끼";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_LANCE, iOut ) )
				{
					if(tribe) //str += ", 창";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "창";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_MACE, iOut ) )
				{
					if(tribe) //str += ", 둔기";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "둔기";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_GLOVE, iOut ) )
				{
					if(tribe) //str += ", 격투무기";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "격투무기";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_WAND, iOut ) )
				{
					if(tribe) //str += ", 마법무기";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "마법무기";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_BOW, iOut ) )
				{
					if(tribe) //str += ", 활";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "활";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &pExtData->basic.str);
					tribe = HT_TRUE;
				}
				if( BIT_AND( _ITEM_TYPE_WEPON_DAGGER, iOut ) )
				{
					if(tribe) //str += ", 단검";
					{
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &str);
						pExtData->basic.str = pExtData->basic.str + _T(", ") + str;
					}
					else	//str += "단검";
						HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &pExtData->basic.str);
					tribe = HT_TRUE;
				}

				//str += " 전용";
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
			
			// 요구되는 아이템
			if( g_pParamMgr->HT_bGetPCSkillidReqItem( &iOut ) == true && iOut > 0 )
			{
				if( g_pParamMgr->HT_bGetItemName( iOut, &str) == true )
				{
					pData = new HT_ITEM_DATA;
					// %s 필요
					CHTString szMessage;
					HT_vSkillSystem_SetMessage( eMsgSkillInfoNeedItem, &szMessage);
					pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString() );

					// 왼손에 장착한 아이템의 index 구하기
					HTdword dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_LEFT_HAND );
					HTdword dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
					// PC 인벤토리 또는 왼손에 장착한 아이템이 필요한 아이템인지
					if( g_cItemSystem->HT_iItemSystem_GetItemCountOnPcInven( iOut ) || ( dwIndex == iOut ) )
						pData->color = g_ColorTable[16]; //light grey
					else
						pData->color = g_ColorTable[11];	//red

					vInfo.vLimitStr.push_back(pData);
					winSizeX = max(winSizeX, pData->str.HT_nGetSize());
				}
			}
			// 지속시간
			//if( g_pParamMgr->HT_bGetPCSkillDuration( &iOut ) == true && iOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("   (지속시간:%d초)", iOut/HT_ITEM_DURATION_DIVIDING );		

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

					// 지속시간
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect1Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간:%d초)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// 다음 단계
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

							// 지속시간
							if( g_pParamMgr->HT_bGetPCSkillEffect1Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (지속시간:%d초)
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

					// 지속시간
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect2Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간:%d초)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// 다음 단계
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

							// 지속시간
							if( g_pParamMgr->HT_bGetPCSkillEffect2Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (지속시간:%d초)
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

					// 지속시간
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect3Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간:%d초)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// 다음 단계
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

							// 지속시간
							if( g_pParamMgr->HT_bGetPCSkillEffect3Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (지속시간:%d초)
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

					// 지속시간
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect4Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간:%d초)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// 다음 단계
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

							// 지속시간
							if( g_pParamMgr->HT_bGetPCSkillEffect4Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (지속시간:%d초)
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

					// 지속시간
					HTint iDuration = 0;
					if( g_pParamMgr->HT_bGetPCSkillEffect5Duration( &iDuration ) == true && iDuration > 0 )
					{
						pExtData = new HT_ITEM_EXPANSION_DATA;
						ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

						pExtData->basic.color = g_ColorTable[16]; //light grey
						//    (지속시간:%d초)
						HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
						pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iDuration/HT_ITEM_DURATION_DIVIDING);

						vInfo.vAttributeStr.push_back(pExtData);
						winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
					}
					// 다음 단계
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

							// 지속시간
							if( g_pParamMgr->HT_bGetPCSkillEffect5Duration( t->sSkill.m_dwSkill_Index, 
																	t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
							{
								pData = new HT_ITEM_DATA;
								ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

								pData->color = g_ColorTable[16]; //light grey
								//   (지속시간:%d초)
								HT_vSkillSystem_SetMessage( eMsgItemInfoDuration, &str );
								pData->str.HT_szFormat( str.HT_szGetString(), iOut/HT_ITEM_DURATION_DIVIDING);

								vNextInfo.push_back(pData);
								winSizeX = max(winSizeX, pData->str.HT_nGetSize());
							}
						}
					} // end of if( bNextInfo )
				} // end of if( HT_bSkillSystem_GetEffect( iOut, &str, iParam1, iParam2, iFunction, 0, dwIndex ) == HT_TRUE )
			} // end of if( g_pParamMgr->HT_bGetPCSkillEffect1ID( &iOut ) == true && iOut > 0 )
			// 사정거리
			//if( g_pParamMgr->HT_bGetPCSkillRange( &iOut ) && iOut > 0 )
			//{
			//	pExtData = new HT_ITEM_EXPANSION_DATA;
			//	ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

			//	pExtData->basic.color = g_ColorTable[16]; //light grey
			//	pExtData->basic.str.HT_szFormat("사정거리 %d", iOut);		

			//	vInfo.vAttributeStr.push_back(pExtData);
			//	winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
			//}
			// 적용대상
			if( g_pParamMgr->HT_bGetPCSkillAllowedTarget( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				switch( iOut )
				{
					case  _TARGET_SELF				: // PC본인
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetSelf, &pExtData->basic.str ); break;
					case  _TARGET_FRIENDLY			: // field에서는 PC, 주신전에서는 같은 주신
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendly, &pExtData->basic.str ); break;				
					case  _TARGET_FRIENDLY_EXCEPT_ME: // 자신을 제외
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendlyExceptMe, &pExtData->basic.str ); break;			
					case  _TARGET_ENEMEY			: pExtData->basic.str.HT_szFormat(""); 
						/*HT_vSkillSystem_SetMessage( eMsgAllowedTargetSelf, &pExtData->basic.str );*/ break;		
					case  _TARGET_PARTY				: // 파티원들 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetParty, &pExtData->basic.str ); break;		
					case  _TARGET_GUILD				: // 길드원들
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetGuild, &pExtData->basic.str ); break;				
					case  _TARGET_ALL				: // ALL 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetAll, &pExtData->basic.str ); break;	
					case  _TARGET_FRIENDLY_CORPSE	: // 동료의 시체. 부활 마법에서 사용 
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetFriendlyCorpse, &pExtData->basic.str ); break;		
					case  _TARGET_ENEMEY_CORPSE		: // 적의 시체. 시체 폭파 마법에서 사용
						HT_vSkillSystem_SetMessage( eMsgAllowedTargetEnemeyCorpse, &pExtData->basic.str ); break;		
					case  _TARGET_GATE				: // 공성전시 성문에 사용
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
			// 소모 HP
			if( g_pParamMgr->HT_bGetPCSkillCostHP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// 소모 HP %d
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostHP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// 다음 단계
				if( bNextInfo )
				{
					if( g_pParamMgr->HT_bGetPCSkillCostHP( t->sSkill.m_dwSkill_Index, 
												t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
					{
						pData = new HT_ITEM_DATA;
						ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

						pData->color = g_ColorTable[16]; //light grey
						// 소모 HP %d	
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostHP, &str );
						pData->str.HT_szFormat( str.HT_szGetString(), iOut);

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			// 소모 TP
			if( g_pParamMgr->HT_bGetPCSkillCostTP( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				// 소모 TP %d
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostTP, &str );
				pExtData->basic.str.HT_szFormat( str.HT_szGetString(), iOut);

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// 다음 단계
				if( bNextInfo )
				{
					if( g_pParamMgr->HT_bGetPCSkillCostTP( t->sSkill.m_dwSkill_Index, 
												t->sSkill.m_bySkill_Level+1, &iOut ) == true && iOut > 0 )
					{
						pData = new HT_ITEM_DATA;
						ZeroMemory(pData, sizeof(HT_ITEM_DATA) );

						pData->color = g_ColorTable[16]; //light grey
						// 소모 TP %d
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostTP, &str );
						pData->str.HT_szFormat( str.HT_szGetString(), iOut);

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}
			// 소모 Item
			if( g_pParamMgr->HT_bGetPCSkillidCostItem( &iOut ) == true && iOut > 0 )
			{
				pExtData = new HT_ITEM_EXPANSION_DATA;
				ZeroMemory(pExtData, sizeof(HT_ITEM_EXPANSION_DATA) );

				pExtData->basic.color = g_ColorTable[16]; //light grey
				
				CHTString str;
				g_pParamMgr->HT_bGetItemName( iOut, &str );
				HTbyte byteCount = 0;
				g_pParamMgr->HT_bGetPCSkillCostItemCount( &byteCount );

				// %s %d개 소모
				CHTString szMessage;
				HT_vSkillSystem_SetMessage( eMsgItemInfoCostItemCount, &szMessage );
				pExtData->basic.str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteCount );

				vInfo.vAttributeStr.push_back(pExtData);
				winSizeX = max(winSizeX, pExtData->basic.str.HT_nGetSize());
				// 다음 단계
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
						// %s %d개 소모
						CHTString szMessage;
						HT_vSkillSystem_SetMessage( eMsgItemInfoCostItemCount, &szMessage );
						pData->str.HT_szFormat( szMessage.HT_szGetString(), str.HT_szGetString(), byteCount );

						vNextInfo.push_back(pData);
						winSizeX = max(winSizeX, pData->str.HT_nGetSize());
					}
				}
			}

			// 스킬 정보 Lock 해제
			g_pParamMgr->HT_bUnLockID( t->sSkill.m_dwSkill_Index, t->sSkill.m_bySkill_Level );
			break;
		} // end of if( t->sSkill.m_dwSkill_Index == dwIndex )
		t = t->next;
	} // end of while( t != m_sSkillTail )

	return winSizeX;
}

// 데미지 Effect의 실제 데미지 수치 계산하기
HTvoid HTSkillSystem::HT_bSkillSystem_SetDamageParam( HTint iEffectID, HTint iParam1, HTint iParam2 )
{
	HTint iSoul = g_cStatus->HT_nGetChakraSoul();
	HTint iNerve = g_cStatus->HT_nGetChakraNerve();
	HTint iMinDamage = 0, iMaxDamage = 0;
	
	/*HTdword dwKeyID = g_cItemSystem->HT_dwSystem_GetItemEquipKeyID( ITEM_LOCATION_EQUIP_RIGHT_HAND );
	if( g_cItemSystem->HT_sItemSystem_GetItemType( dwKeyID ) == _ITEM_TYPE_WEPON_WAND )
	{
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwKeyID );
		if( dwItemIndex > 0 ) // 장착한 아이템의 공격력 알아오기
		{
			HTint iEffectID = 0, iParam1 = 0, iParam2 = 0;
			// 아이템 기본 속성
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
			// 아이템 제련 속성
			//g_cItemSystem->HT_byItemSystem_GetMainRefineLevel
			//g_cItemSystem->HT_bItemSystem_GetMainRefineEffect
			
		}
	}*/
	m_iParam1 = HTint( 0.003*(iSoul+iNerve+100)*iParam1 + (iSoul+iNerve-23)/2 
					+ 0.05*iMinDamage*iNerve/* +0.05*지팡이속성*신경(데바/간다르바만 적용)*/ +iMinDamage );
	m_iParam2 = HTint( 0.003*(iSoul+iNerve+100)*iParam2 + (iSoul+iNerve-23)/2 
					+ 0.05*iMaxDamage*iNerve/* +0.05*지팡이속성*신경(데바/간다르바만 적용)*/ +iMaxDamage );
}

// 스킬 Effect가 공격력 종류인지
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
	// 데바/가루다 스킬 중 공격력만 값을 계산한다.
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
		case eTNAfn_DamageTP: // Duration동안 param1 만큼의 TP 데미지 
			HT_vSkillSystem_SetMessage( eMsgEffectDamageTP, pString );
            break;
		case eTNAfn_DOTbyDice: // function확률로 duration동안 param1~param2 의 데미지
			HT_vSkillSystem_SetMessage( eMsgEffectDOTbyDice, pString );
            break;
		case eTNAfn_HealPlus: //HP회복시 param1만큼의 추가회복
			HT_vSkillSystem_SetMessage( eMsgEffectHealPlus, pString );
			break;
		case eTNAfn_RecoverTPPlus:	//TP회복시 param1만큼의 추가회복
			HT_vSkillSystem_SetMessage( eMsgEffectRecoverTPPlus, pString );
			break;
		case eTNAfn_Damage :
			if( iDecreaseVal > 0 )
				// 공격력 %d - %d(레벨 제한으로 %d%%감소), iParam1, iParam2, iDecreaseVal
				HT_vSkillSystem_SetMessage( eMsgEffectDamageLimitLevel, pString );
			else
				// 공격력 %d - %d, iParam1, iParam2); 
				HT_vSkillSystem_SetMessage( eMsgEffectDamage, pString );
			break;
		case eTNAfn_DamageSplash :
			// 스플래쉬 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDamageSplash, pString );
			break;
		//case eTNAfn_EnergyOfSword :
		// 검 공격력 %d%% - %d%% 향상, iParam1, iParam2
		//	HT_vSkillSystem_SetMessage( eMsgEffectEnergyOfSword, pString );
		//	break;
		case eTNAfn_PierceDamage :
			// 방어력을 무시한 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDefenceIgnoreDamage, pString );
			break;
		case eTNAfn_Fire :
			// 화염 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectFire, pString );
			break;			
		case eTNAfn_Cold :
			// 냉기 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectCold, pString );
			break;			
		case eTNAfn_Lightning :
			// 전격 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectLightning, pString );
			break;		
		case eTNAfn_Poison	 :
			// 독 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPoison, pString );
			break;
		case eTNAfn_FireSplash :
			// 화염 스플래쉬 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectFireSplash, pString );
			break;			
		case eTNAfn_ColdSplash :
			// 냉기 스플래쉬 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectColdSplash, pString );
			break;			
		case eTNAfn_LightningSplash :
			// 전격 스플래쉬 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectLightningSplash, pString );
			break;		
		case eTNAfn_PoisonSplash	 :
			// 독 스플래쉬 공격력 %d - %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPoisonSplash, pString );
			break;
		//case eTNAfn_AdditionalDamage :
		case eTNAfn_BonusDamage :
		case eTNAfn_BonusDamage2 :
			// %s의 공격력 %d - %d 추가, skillName, iParam1, iParam2
			g_pEngineHandler->HT_hrGetPCSkillName( iFunction, &m_szParamString );
			HT_vSkillSystem_SetMessage( eMsgEffectSkillDamagePlus, pString );
			break;

		case eTNAfn_Summon :
		{
			//g_pEngineHandler->HT_hrGetMonsterName( iParam1 , &m_szParamString );
			g_pParamMgr->HT_bGetMonsterName( iParam1, &m_szParamString );
			//pString->HT_szFormat("%s %d마리 소환", strName.HT_szGetString(), iParam2);
			HT_vSkillSystem_SetMessage( eMsgEffectSummon, pString );
		}
			break;			
		case eTNAfn_Illusion :
		{
			//g_pEngineHandler->HT_hrGetMonsterName( iParam1 , &m_szParamString );
			g_pParamMgr->HT_bGetMonsterName( iParam1, &m_szParamString );
			// %s %d마리 생성, strName.HT_szGetString(), iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectIllusion, pString );
		}
			break;	
		case eTNAfn_MoveSpeedPlus :
			// 이동속도 %d증가, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMoveSpeedPlus, pString );
			break;		
		case eTNAfn_AttackSpeedPlus :
			// 공격속도 %d증가, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAttackSpeedPlus, pString );
			break;	
		case eTNAfn_MoveSpeedMinus :
			// 이동속도 %d감소, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMoveSpeedMinus, pString );
			break;		
		case eTNAfn_AttackSpeedMinus :
			// 공격속도 %d감소, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAttackSpeedMinus, pString );
			break;	
		//case eTNAfn_CastSpeedMinus :
		//	// 캐스팅 속도 %d감소, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCastSpeedMinus, pString );
		//	break;	
		//case eTNAfn_CastSpeedPlus :
		//	// 캐스팅 속도 %d증가, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCastSpeedPlus, pString );
		//	break;	
		case eTNAfn_Invisible :
			//pString->HT_szFormat("투명상태");
			HT_vSkillSystem_SetMessage( eMsgEffectInvisible, pString );
			break;
		case eTNAfn_WizardEyes :
			//pString->HT_szFormat("투명상태 보기");
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
			//pString->HT_szFormat("인벤토리 확장 %dX%d", iParam1, iParam2);
			HT_vSkillSystem_SetMessage( eMsgEffectExpandBag, pString );
			break;

		case eTNAfn_Concentration :
			//pString->HT_szFormat("Cast 성공 %d%% 증가", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectConcentration, pString );
			break;
		case eTNAfn_Disruption :
			//pString->HT_szFormat("마법 Casting 실패");
			HT_vSkillSystem_SetMessage( eMsgEffectDisruption, pString );
			break;
		case eTNAfn_Invulnerable :
			//pString->HT_szFormat("무적상태");
			HT_vSkillSystem_SetMessage( eMsgEffectInvulnerable, pString );
			break;
		case eTNAfn_MagicShield :
			//pString->HT_szFormat("Max HP %d", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMagicShield, pString );
			break;

		case eTNAfn_StealHP :
			//pString->HT_szFormat("데미지의 %d%% HP 훔침", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectStealHP, pString );
			break;		
		case eTNAfn_StealTP :
			//pString->HT_szFormat("데미지의 %d%% TP 훔침", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectStealTP, pString );
			break;		
		case eTNAfn_MultipleStrike :
			//pString->HT_szFormat("%d%% 데미지 %d회", iParam2, iParam1 );
			HT_vSkillSystem_SetMessage( eMsgEffectMultipleStrike, pString );
			break;	
		case eTNAfn_CriticalStrike :
			// %d확률의 공격력 %d%%증가, iParam1, iParam2
			if( iFunction == 0 )
				HT_vSkillSystem_SetMessage( eMsgEffectCriticalStrikeRate, pString );
			else // %d확률의 공격력 %d증가, iParam1, iParam2
				HT_vSkillSystem_SetMessage( eMsgEffectCriticalStrike, pString );
			break;	
		case eTNAfn_PierceStrike :
			// 방어력을 무시한 공격력 %d%%, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectPierceStrike, pString );
			break;
		case eTNAfn_PierceStrike2 :
			// 방어력 %d를 감소시킨 공격력, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectDefenceMinusDamage, pString );
			break;
		case eTNAfn_HPDown :
			// HP %d%%감소, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectHPDown, pString );
			break;
		case eTNAfn_KnockBack :
			// %d확률의 KnockBack %d, iParam1, iParam2
			HT_vSkillSystem_SetMessage( eMsgEffectKnockBack, pString );
			break;
		case eTNAfn_SpiritLink :
			// %d%%만큼의 파티원의 물리 데미지를 흡수
			HT_vSkillSystem_SetMessage( eMsgEffectAbsorbPartyPhs, pString );
			break;
		case eTNAfn_Heal :
		{
			if( iFunction == 0 )
				// HP %d회복 , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectHeal, pString );
			else if( iFunction == 1 )
			{
				// 대상HP %d회복 , iParam1*정신/50
				m_szParamString.HT_szFormat("%d", iParam1*(1+g_cStatus->HT_nGetChakraSoul()/50) );
				HT_vSkillSystem_SetMessage( eMsgEffectTargetHeal, pString );
			}
			else if( iFunction == 2 )
			{
				// HP %d회복 , iParam1+총HP/iParam2
				m_szParamString.HT_szFormat("%d", iParam1+g_cMainCharacter->HT_nMainChar_GetMAXHP()/iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectHeal2, pString );
			}
			else
				// HP %d%%회복 , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectHealRate, pString );
		}
			break;	
		case eTNAfn_RecoverTP :
		{
			if( iFunction == 0 )
				// TP %d회복 , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTP, pString );
			else if( iFunction == 1 )
			{
				// 대상TP %d회복 , iParam1*정신/50
				m_szParamString.HT_szFormat("%d", iParam1*g_cStatus->HT_nGetChakraSoul()/50);
				HT_vSkillSystem_SetMessage( eMsgEffectTargetHealTP, pString );
			}
			else if( iFunction == 2 )
			{
				// TP %d회복 , iParam1+총TP/iParam2
				m_szParamString.HT_szFormat("%d", iParam1+g_pMainBar->HT_iMainBar_GetMaxTP()/iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTP2, pString );
			}
			else
				// TP %d%%회복 , iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectRecoverTPRate, pString );
		}
			break;		
		//case eTNAfn_iACrificeHP :
		//	// HP 소모 %d, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectiACrificeHP, pString );
		//	break;
		//case eTNAfn_Cure :
		//	// EffectID %d, iParam1
		//	HT_vSkillSystem_SetMessage( eMsgEffectCure, pString );
		//	break;
		case eTNAfn_TPBurn :
		{
			if( iParam2 == 0 )
				// TP %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPBurn2, pString );
			else
				// TP %d를 %d%% 공격력으로 전환, iParam1, iParam2
				HT_vSkillSystem_SetMessage( eMsgEffectTPBurn, pString );
		}
			break;
		case eTNAfn_Resurrect :
			// 경험치 %d회복
			HT_vSkillSystem_SetMessage( eMsgEffectResurrect, pString );
			break;		
		case eTNAfn_ReflectDamage :
			if( iFunction == 1 )
				// 데미지 반사 %d%%, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectReflectDamage, pString );
			else // 데미지 반사 %d, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectReflectDamagePlus, pString );
			break;	
		case eTNAfn_AbsorbDamage :
			// 데미지 흡수 %d%%, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAbsorbDamage, pString );
			break;	
		case eTNAfn_AbsorbElementalDamage : 
			// 속성 데미지 흡수 &d%%, iParam1
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
			// 타인을 공격할 확률 증가
			HT_vSkillSystem_SetMessage( eMsgEffectDefaunt, pString );
			break;
		case eTNAfn_RangeUp :
			// 사정거리 %d증가, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectRangeUp, pString );
			break;	

		case eTNAfn_WeaponMastery :
		//case eTNAfn_WeaponMastery2 :
		{
			switch( iFunction )
			{
				case _ITEM_TYPE_WEPON_SWORD	: //str.HT_szFormat("검");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassSword, &m_szParamString ); break;
				case _ITEM_TYPE_WEPON_AX : //str.HT_szFormat("도끼");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassAx, &m_szParamString ); break;
				case _ITEM_TYPE_WEPON_LANCE	: //str.HT_szFormat("창");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassLance, &m_szParamString ); break;			
				case _ITEM_TYPE_WEPON_MACE	: //str.HT_szFormat("둔기");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMace, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_GLOVE	: //str.HT_szFormat("격투 무기");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassGlove, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_WAND	: //str.HT_szFormat("마법 무기");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassMagic, &m_szParamString ); break;			
				case _ITEM_TYPE_WEPON_BOW	: //str.HT_szFormat("활");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassBow, &m_szParamString ); break;	
				case _ITEM_TYPE_WEPON_DAGGER : //str.HT_szFormat("단검");
					HT_vSkillSystem_SetMessage( eMsgCommonWeponClassDagger, &m_szParamString ); break;
				default : return HT_FALSE;
			}
			
			if ( iEffectID == eTNAfn_WeaponMastery )
			{
				//pString->HT_szFormat("%s 공격력 %d, 공격 속도 %d증가", str.HT_szGetString(), iParam1, iParam2);
				if( iParam2 == 0 ) // %s 공격력 %d
					HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery, pString );
				else // %s 공격력 %d, 공격 속도 %d증가
					HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery2, pString );
			}
			else
				//pString->HT_szFormat("%s 공격성공 %d증가", str.HT_szGetString(), iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectWeaponMastery3, pString );
		}
			break;
		case eTNAfn_DamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlus, pString );
			else
				//pString->HT_szFormat("공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_DamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("공격력 %d - %d 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamageMinus, pString );
			else
				//pString->HT_szFormat("공격력 %d%% - %d%% 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamageMinusRate, pString );
		}
			break;
		case eTNAfn_FireDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("화염 공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamagePlus, pString );
			else
				//pString->HT_szFormat("화염 공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_FireDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("화염 공격력 %d - %d 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamageMinus, pString );
			else
				//pString->HT_szFormat("화염 공격력 %d%% - %d%% 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectFireDamageMinusRate, pString );
		}
			break;
		case eTNAfn_ColdDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("냉기 공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamagePlus, pString );
			else
				//pString->HT_szFormat("냉기 공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_ColdDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("냉기 공격력 %d - %d 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamageMinus, pString );
			else
				//pString->HT_szFormat("냉기 공격력 %d%% - %d%% 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectColdDamageMinusRate, pString );
		}
			break;
		case eTNAfn_LightningDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("전격 공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamagePlus, pString );
			else
				//pString->HT_szFormat("전격 공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_LightningDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("전격 공격력 %d - %d 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamageMinus, pString );
			else
				//pString->HT_szFormat("전격 공격력 %d%% - %d%% 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectLightningDamageMinusRate, pString );
		}
			break;
		case eTNAfn_PoisonDamagePlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("독 공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamagePlus, pString );
			else
				//pString->HT_szFormat("독 공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamagePlusRate, pString );
		}
			break;		
		case eTNAfn_PoisonDamageMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("독 공격력 %d - %d 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamageMinus, pString );
			else
				//pString->HT_szFormat("독 공격력 %d%% - %d%% 감소", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonDamageMinusRate, pString );
		}
			break;
		case eTNAfn_FireResistPlus :
		{
			if( iFunction == 1 )
				// 화염 저항력 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistPlusRate, pString );
			else
				// 화염 저항력 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistPlus, pString );
		}
			break;		
		case eTNAfn_FireResistMinus:
		{
			if( iFunction == 1 )
				// 화염 저항력 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistMinusRate, pString );
			else
				// 화염 저항력 %d 감소, iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectFireResistMinus, pString );
		}
			break;
		case eTNAfn_ColdResistPlus :
		{
			if( iFunction == 1 )
				// 냉기 저항력 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistPlusRate, pString );	
			else
				// 냉기 저항력 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistPlus, pString );
		}
			break;	
		case eTNAfn_ColdResistMinus :
		{
			if( iFunction == 1 )
				// 냉기 저항력 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistMinusRate, pString );
			else
				// 냉기 저항력 %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectColdResistMinus, pString );
		}
			break;
		case eTNAfn_LightningResistPlus :
		{
			if( iFunction == 1 )
				// 전격 저항력 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistPlusRate, pString );
			else
				// 전격 저항력 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistPlus, pString );
		}
			break;	
		case eTNAfn_LightningResistMinus :
		{
			if( iFunction == 1 )
				// 전격 저항력 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistMinusRate, pString );
			else
				// 전격 저항력 %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectLightningResistMinus, pString );
		}
			break;
		case eTNAfn_PoisonResistPlus :
		{
			if( iFunction == 1 )
				// 독 저항력 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistPlusRate, pString );
			else
				// 독 저항력 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistPlus, pString );
		}
			break;		
		case eTNAfn_PoisonResistMinus :
		{
			if( iFunction == 1 )
				// 독 저항력 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistMinusRate, pString );
			else
				// 독 저항력 %d감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectPoisonResistMinus, pString );
		}
			break;
		case eTNAfn_AllResistPlus :
		{
			if( iFunction == 0 )
				// 모든 저항력 %d증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistPlus, pString );
			else
				// 모든 저항력 %d%%증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistPlusRate, pString );
		}
			break;
		case eTNAfn_AllResistMinus :
		{
			if( iFunction == 0 )
				// 모든 저항력 %d감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistMinus, pString );
			else
				// 모든 저항력 %d%%감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllResistMinusRate, pString );
		}
			break;
		case eTNAfn_AllStatePlus :
		{
			if( iFunction == 0 )
				// 모든 차크라 %d증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatPlus, pString );
			else
				// 모든 차크라 %d%%증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatPlusRate, pString );
		}
			break;
		case eTNAfn_AllStateMinus :
		{
			if( iFunction == 0 )
				// 모든 차크라 %d감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatMinus, pString );
			else
				// 모든 차크라 %d%%감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAllStatMinusRate, pString );
		}
			break;
		case eTNAfn_AllDamagePlus :
			// 모든 속성 공격력 %d%% 상승, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAllDamageUp, pString );
			break;
		case eTNAfn_AllDamageMinus :
			// 모든 속성 공격력 %d%% 감소, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectAllDamageDown, pString );
			break;
		case eTNAfn_MusclePlus :
			// 근육의 차크라 %d 증가", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMusclePlus, pString );
			break;		
		case eTNAfn_MuscleMinus :
			// 근육의 차크라 %d 감소", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMuscleMinus, pString );
			break;
		case eTNAfn_NervesPlus :
			// 신경의 차크라 %d 증가", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectNervesPlus, pString );
			break;		
		case eTNAfn_NervesMinus :
			// 신경의 차크라 %d 감소", iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectNervesMinus, pString );
			break;
		case eTNAfn_HeartPlus :
			// 심장의 차크라 %d 증가", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectHeartPlus, pString );
			break;		
		case eTNAfn_HeartMinus :
			// 심장의 차크라 %d 감소", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectHeartMinus, pString );
			break;
		case eTNAfn_MindPlus :
			// 정신의 차크라 %d 증가", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMindPlus, pString );
			break;		
		case eTNAfn_MindMinus :
			// 정신의 차크라 %d 감소", iParam1);
			HT_vSkillSystem_SetMessage( eMsgEffectMindMinus, pString );
			break;
		case eTNAfn_AttackRatePlus :
		{
			if( iFunction == 1 )
				// 공격성공 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRatePlusRate, pString );
			else
				// 공격성공 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRatePlus, pString );
		}
			break;		
		case eTNAfn_AttackRateMinus :
		{
			if( iFunction == 1 )
				// 공격성공 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRateMinusRate, pString );
			else
				// 공격성공 %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectAttackRateMinus, pString );
		}
			break;
		case eTNAfn_DodgeRatePlus :
		{
			if( iFunction == 1 )
				// 회피 %d%% 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRatePlusRate, pString );
			else
				// 회피 %d 증가, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRatePlus, pString );
		}
			break;		
		case eTNAfn_DodgeRateMinus :
		{
			if( iFunction == 1 )
				// 회피 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRateMinusRate, pString );
			else
				// 회피 %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectDodgeRateMinus, pString );
		}
			break;
		case eTNAfn_ACPlus :
		{
			if( iFunction == 0 )
			{
				if( iDecreaseVal > 0 )
					//pString->HT_szFormat("방어도 %d 증가(레벨 제한으로 %d%%감소)", iParam1, iDecreaseVal );
					HT_vSkillSystem_SetMessage( eMsgEffectACPlusLimitLevel, pString );
				else
					//pString->HT_szFormat("방어도 %d 증가", iParam1);
					HT_vSkillSystem_SetMessage( eMsgEffectACPlus, pString );
			}
			else
				//pString->HT_szFormat("방어도 %d%% 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACPlusRate, pString );
		}
			break;		
		case eTNAfn_ACMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("방어도 %d 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACMinus, pString );
			else
				//pString->HT_szFormat("방어도 %d%% 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectACMinusRate, pString );
		}
			break;
		case eTNAfn_MaxHPPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("최대 HP %d 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlus, pString );
			else
				//pString->HT_szFormat("최대 HP %d%% 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxHPMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("최대 HP %d 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinus, pString );
			else
				//pString->HT_szFormat("최대 HP %d%% 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinusRate, pString );
		}
			break;
		case eTNAfn_MaxHPPPlus :
		{
			//최대 HP %d%% 증가, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMaxHPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxHPPMinus :
		{
			// 최대 HP %d%% 감소, iParam1
			HT_vSkillSystem_SetMessage( eMsgEffectMaxHPMinusRate, pString );
		}
			break;
		case eTNAfn_SaveTPCost : // TP 소모량 %d 감소
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("TP 소모량 %d 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectCostTP, pString );
			else
				//pString->HT_szFormat("TP 소모량 %d%% 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectCostTPRate, pString );
		}
			break;
		case eTNAfn_HPRecoveryPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("HP 회복 %d 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryPlus, pString );
			else
				//pString->HT_szFormat("HP 회복 %d%% 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryPlusRate, pString );
		}
			break;		
		case eTNAfn_HPRecoveryMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("HP 회복 %d 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryMinus, pString );
			else
				//pString->HT_szFormat("HP 회복 %d%% 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectHPRecoveryMinusRate, pString );
		}
			break;
		case eTNAfn_MaxTPPlus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("최대 TP %d 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPPlus, pString );
			else
				//pString->HT_szFormat("최대 TP %d%% 증가", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPPlusRate, pString );
		}
			break;		
		case eTNAfn_MaxTPMinus :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("최대 TP %d 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPMinus, pString );
			else
				//pString->HT_szFormat("최대 TP %d%% 감소", iParam1);
				HT_vSkillSystem_SetMessage( eMsgEffectMaxTPMinusRate, pString );
		}
			break;
		case eTNAfn_TPRecoveryPlus :
		{
			if( iFunction == 0 )
				// TP 회복 %d 증가", iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryPlus, pString );
			else
				// TP 회복 %d%% 증가", iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryPlusRate, pString );
		}
			break;		
		case eTNAfn_TPRecoveryMinus :
		{
			if( iFunction == 0 )
				// TP 회복 %d 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryMinus, pString );
			else
				// TP 회복 %d%% 감소, iParam1
				HT_vSkillSystem_SetMessage( eMsgEffectTPRecoveryMinusRate, pString );
		}
			break;

		case eTNAfn_EnhanceWeapon : 
			// 무기 강화제련등급 +n 상승 
			HT_vSkillSystem_SetMessage( eMsgEffectRefinePlus, pString );
			break;
	
		case eTNAfn_ResetStat :
			// 차크라 초기화
			HT_vSkillSystem_SetMessage( eMsgEffectResetState, pString );
			break;
		case eTNAfn_ResetSkill :
			// 스킬 초기화
			HT_vSkillSystem_SetMessage( eMsgEffectResetSkill, pString );
			break;		
		case eTNAfn_PreventRegenHP :
			// HP 자동 회복 방해
			HT_vSkillSystem_SetMessage( eMsgEffectPreventHPRecovery, pString );
			break;
		case eTNAfn_PreventRegenTP :
			// TP 자동 회복 방해
			HT_vSkillSystem_SetMessage( eMsgEffectPreventTPRecovery, pString );
			break;	
		case eTNAfn_SkillUp :
			// %s 레벨 %d 증가, skillname, iParam2
			g_pEngineHandler->HT_hrGetPCSkillName( iParam1, &m_szParamString );
			HT_vSkillSystem_SetMessage( eMsgEffectSkillLevelUp, pString );
			break;		

		case eTNAfn_EnhanceHardnessOfArmor :
			// 장착방어구 내구도감소율 줄임
			HT_vSkillSystem_SetMessage( eMsgEffectEnhanceHardnessOfArmor, pString );
			break;

		case eTNAfn_FixedDamagePlus :
			// 최종 데미지 %s~%s 추가
			HT_vSkillSystem_SetMessage( eMsgEffectFixedDamagePlus, pString );
			break;

		case eTNAfn_FixedDamagePlus2 :
			// 최종 데미지 %s~%s 추가
			HT_vSkillSystem_SetMessage( eMsgEffectFixedDamagePlus, pString );
			break;

		case eTNAfn_DamageBonusForNextAttack :	
			// 1회 공격데미지 %s%% 상승
			HT_vSkillSystem_SetMessage( eMsgEffectDamageBonusForNextAttack, pString );
			break;

		case eTNAfn_PercentDamage :
			// 일정 시간동안 %s%%만큼 지속적으로 자신의 HP 감소
			HT_vSkillSystem_SetMessage( eMsgEffectMinusPercentHPforTime, pString );
			break;
		case eTNAfn_Dash :
			// %s만큼의 거리를 순간적으로 대쉬
			HT_vSkillSystem_SetMessage( eMsgEffectQuickDash, pString );
			break;
		case eTNAfn_DefensePlus :
			if( iFunction == 0 )
				// %s만큼의 방어력 상승
				HT_vSkillSystem_SetMessage( eMsgEffectPlusDefense, pString );
			else
				// %s%%만큼의 방어력 상승
				HT_vSkillSystem_SetMessage( eMsgEffectPlusPercentDefense, pString );
			break;

		case eTNAfn_DamagePlus2 :
		{
			if( iFunction == 0 )
				//pString->HT_szFormat("공격력 %d - %d 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlus, pString );
			else
				//pString->HT_szFormat("공격력 %d%% - %d%% 증가", iParam1, iParam2);
				HT_vSkillSystem_SetMessage( eMsgEffectDamagePlusRate, pString );
		}
			break;

		case eTNAfn_BonusExp :
			if( iFunction == 0 )
			{
				// 습득 경험치 %s 증가
				HT_vSkillSystem_SetMessage( eMsgEffectBonusExp, pString );
			}
			else
			{
				// 습득 경험치 %s% 증가
				HT_vSkillSystem_SetMessage( eMsgEffectBonusExpRate, pString );
			}
			break;
		case 2241 :
			{
				switch (iParam1)	// 레벨별 내용 변경
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

//---마우스 포인트를 넘겨받아 활성화된 스킬 중에 포인트 위치에 있는것의 Index를 반환----//
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
	// 예외 - 스킬 정보의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
	//------------------------------------------------------------------------------------//
	// 변수가 3개 일 때
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
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vSkillSystem_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSkillSystem_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
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

		case 535:	// 임시용 코드임 
			{
				int iLevel = HT_bySkillSystem_GetSkill_Level(m_iFunction);
				pszParam->HT_szFormat( "%d", m_iParam1 * iLevel);
			}
			break;

		case 536:	// 임시용 코드임 
			{
				int iLevel = HT_bySkillSystem_GetSkill_Level(m_iFunction);
				pszParam->HT_szFormat( "%d", m_iParam2 * iLevel);
			}
			break;
		default:
			break;
	}
}