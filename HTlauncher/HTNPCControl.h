//--------------------------------------------------------------------------------//
// 설명 : NPC 관련 기능(제조, 기술습득, 차크라/브라만포인트 확장, 물품보관 등)
// 작성일자 / 작성자 : 2003.4.21 김선미
//--------------------------------------------------------------------------------//
#ifndef __HTNPCCONTROL_H__
#define __HTNPCCONTROL_H__

#include "HTNPC.h"

typedef enum _eEconomy_Item
{
	eEconomy_Item_Sword = 0,	// 검
	eEconomy_Item_Dagger ,		// 단검 - 2
	eEconomy_Item_Lance,		// 창
	eEconomy_Item_Axe,			// 도끼
	eEconomy_Item_Mace,			// 타격무기 - 6	
	eEconomy_Item_Glove,		// 격투무기
	eEconomy_Item_Throw,		// 투척무기
	eEconomy_Item_Magic,		// 마법무기
	eEconomy_Item_Armor = 10,
	eEconomy_Item_Helmet,		// 모자
	eEconomy_Item_Boots,		// 신발
	eEconomy_Item_Belt,			// 벨트
	eEconomy_Item_Shield,		// 방패
	eEconomy_Item_Bracelet,		// 팔찌
	eEconomy_Item_Necklace,		// 목걸이
	eEconomy_Item_Earring,		// 귀걸이
//	eEconomy_Item_Ring,			// 반지
	eEconomy_Item_Etc,
//	eEconomy_Item_Potion,		// 물약
	eEconomy_Item_None
} eEconomy_Item;

typedef struct _ECONOMY_ITEM_INFO
{
	HTint				iIndex;
	HTint				iImageID;
	//BYTE				byFriendly;	// 친밀도 레벨
	BYTE				byWinIndex;	// 몇 번째 리스트 창에 있는지(창 단위로 보여진다). 0부터 시작
	HTint				iXpos;		// 리스트 창에서의 위치
	HTint				iYpos;
	HTint				iWidth;		// 아이템 크기
	HTint				iLength;
	//HTbool			bSelect;	// 아이템이 선택됐는가

	_ECONOMY_ITEM_INFO* pNext;
} ECONOMY_ITEM_INFO;

typedef struct _ECONOMY_LIST
{
//	HTint				iCount;		// 리스트에 등록되어있는 아이템 수
	ECONOMY_ITEM_INFO*	pInfoHead;
	ECONOMY_ITEM_INFO*	pInfoTail;
	vector<BYTE>		vWinCount;	// 리스트 창별 아이템 개수
} ECONOMY_LIST;

// 거래소 관련 데이터 구조
//typedef struct _HT_TRADE_ITEM
//{
//	DWORD		dwIndex;		// 아이템 index
//	DWORD		dwKeyID;		// 아이템 keyID. 
//	HTshort		snPackCount;	// 중첩개수
//	BYTE		byState;		// 등록/보관 상태
//} HT_TRADE_ITEM;
//
//typedef struct _HT_TRADE_LIST
//{
//	DWORD			dwTradeID;		// 거래 ID
//	CHTString		szCharName;		// 등록한 캐릭터 이름
//	CHTString		szTitle;		// 거래 제목
//	HTint			nRupiah;		// 원하는 금액
//	BYTE			byItemCount;	// 등록한 아이템 개수. 최대 3개
//	HT_TRADE_ITEM	sItem[3];
//} HT_TRADE_LIST;

#define LIST_WIDTH 6	// 리스트 X 칸 수
#define LIST_LENGTH 11	// 리스트 Y 칸 수

#define LIST_WIDTH_PRIMIUM	2	// 프리미엄 아이템 X 칸 수
#define LIST_LENGTH_PRIMIUM	5	// 프리미엄 아이템 Y 칸 수

//#define PRODUCTION_RUPIAH_EDITBOX		0

//#define ITEM_MAKE_PREV_BUTTON			2
//#define ITEM_MAKE_NEXT_BUTTON			3

class CHTNPCControl
{
public:
	CHTNPCControl();
	~CHTNPCControl();
	
	HTvoid			HT_vNPCControl_Init();
	HTvoid			HT_vNPCControl_CleanUp();

	HTvoid			HT_vNPCControl_Control();

	//-------------------------------------------------------------------
	// 창 띄우기/지우기
	//-------------------------------------------------------------------
	HTvoid			HT_vNPCControl_Active( DWORD dwNPCIndex/*, DWORD dwKeyID*/);
	// 아이템 리스트 창
	HTvoid			HT_vNPCControl_ItemListWin_Active();
	// 제련창 띄우기
	HTvoid			HT_vNPCControl_ItemWorkWin_Active();
	// 인벤토리 창 팝업 : 제조/수리/해체를 선택했을 때
	HTvoid			HT_vNPCControl_PopUpInventory(HTint nWinIndex);
	// 헌납창 띄우기
	HTvoid			HT_vNPCControl_OfferingWin_Active( HTshort sGauge );

	// 캐릭터 위치체크_캐릭터 움직이면 창을 다운시킨다
	HTvoid			HT_vNPCControl_CharPos_Check();
	// 대화상자 닫기
	HTvoid			HT_vNPCControl_DialogWin_AntiActive();
	// 리스트상자 닫기
	HTvoid			HT_vNPCControl_ListAntiActive();
	// ESC키/X버튼을 눌렀을때 리스트창 닫기
	HTvoid			HT_vNPCControl_ItemListClose();
	// ESC키/X버튼을 눌렀을때 제련창 닫기
	HTvoid			HT_vNPCControl_ESC_ItemWorkClose();
	// ESC/X버튼에 의한 NPC인벤토리 제거
	HTvoid			HT_vNPCControl_Inventory_Close();
	// ESC키/X버튼을 눌렀을때 헌납창 닫기
	HTvoid			HT_vNPCControl_ESC_OfferingwinClose();

	//-------------------------------------------------------------------
	// 창에 대한 마우스 입력 체크
	//-------------------------------------------------------------------
	//완료메세지 창 
	HTRESULT		HT_hrNPCControl_Complete_Message( HTint iProp, HTint iInductNo );
	// 대화상자 체크
	HTvoid			HT_vNPCControl_ButtonCheck_Dialog(HTPoint pPt);
	// 캐릭터 정보창으로 들어온 버튼 클릭 이벤트를 처리한다
	HTvoid			HT_vNPCControl_IncreaseChakra(HTint iBtnNo);

	//-------------------------------------------------------------------
	// 대화상자
	//-------------------------------------------------------------------
	// 다음단계로 대화상자 대화 바꾸기
	HTvoid			HT_vNPCControl_GetNextStep(HTint nSelNum);
	// 화면에 보여줄 대화 설정
	HTvoid			HT_vNPCControl_SetText();
	// 질의문에 삽입할 parameter text설정
	HTvoid			HT_vNPCControl_SetParameterText();
	// 현재 단계에서 해야할 서버 요청 수행
	HTvoid			HT_vNPCControl_ServerEvent();
	// 현재 단계에서 해야할 클라이언트 이벤트
	HTvoid			HT_vNPCControl_ClientEvent();

	//-------------------------------------------------------------------
	// 아이템 구입
	//-------------------------------------------------------------------
	// shop list 만들기
	HTvoid			HT_vNPCControl_GetItemList();

	// 프리미엄 아이템 리스트 생성
	HTvoid			HT_vNPCControl_GetPrimiumItemList();

	// 프리미엄 출력창 셋팅
	HTvoid			HT_vNPCControl_PrimiumItemListWin_Active(HTint iNum, HTint iPage);

	// 프리미엄 아이템 리스트창 제어
	HTdword			HT_vNPCControl_Get_Primium_List_ItemIndex(HTPoint pPt);

	// shop list에 아이템 넣기
	HTvoid			HT_vNPCControl_InsertItemInShopList( HTint iIndex );

	// 현재 마우스의 위치가 리스트에 있는 아이템 위에 있는지 검사
	HTint			HT_nNPCControl_ItemListMouseCheck_OnItem( HTint nCol, HTint nRow);
	// 그림 지우기
	HTvoid			HT_vNPCControl_ButtonCheck_List_Delete();
	// 현재 선택된 NPC의 아이템 리스트 비활성화 
	HTvoid			HT_vNPCControl_ButtonCheck_ItemList_AntiActive();
	// 제조창 아이템 정보 데이터 모두 지우기
	HTvoid			HT_vNPCControl_DeleteWorkItemInfo();
	// 같은 분류에서 index가 같은 아이템이 있는지 검사
	HTbool			HT_bNPCControl_CheckItemIndex(HTint iItemClass, DWORD dwIndex);
	// 아이템이 놓일 위치 검색
	HTbool			HT_bNPCControl_ItemListCheck(HTint iItemClass, BYTE byWinCount, HTint nSellX, 
														HTint nSellY, HTint nItemWidth, HTint nItemLength);
	// 아이템 구입할 개수 쓰기
	HTvoid			HT_vNPCControl_ItemMakeCount_SetText();
	// 마우스 포인트가 위치한 아이템의 제조 정보를 얻어온다
	HTint			HT_nNPCControl_GetItemInfo(HTint iItemIndex, HT_ITEMINFO& vInfo);

	// 유료화 아이템의 구입 가격 계산
	HTint			HT_iNPCControl_CalPurchasingPriceForChargeItem( HTint iItemIndex, HTint iCount );
	// 유료화 아이템의 최소 구매 개수
	HTint			HT_iNPCControl_GetMinCountForChargeItem( HTint iItemIndex );
	// 유료화 아이템의 할인적용 구매 개수
	HTint			HT_iNPCControl_GetDiscountNumForChargeItem( HTint iItemIndex );
	//-------------------------------------------------------------------
	// 아이템 제련
	//-------------------------------------------------------------------
	// 제련을 위한 object를 클릭했는지 검사
	HTRESULT		HT_hrNPCControl_ClickRefineObject( );
	// 제련할 아이템 클릭했을 경우
	HTRESULT		HT_hrNPCControl_ItemWork_LButtonClick( DWORD dwItemKeyID );
	// 제련 이미지 지우기
	HTvoid			HT_vNPCControl_ButtonCheck_Work_Delete();
	// 제련 전체 캔슬
	HTvoid			HT_vNPCControl_ButtonCheck_Work_TotalCancel();
	// 제련 확인
	HTvoid			HT_vNPCControl_ButtonCheck_Work_Ok();
	// 보조재료가 첨가 가능한 것인지 검사
	HTint			HT_nNPCControl_CheckAidItemCondition(CHTString& strName);
	// 제련창에서 취소한 보조자원 지우기
	HTbool			HT_bNPCControl_CancelSupportResource( DWORD dwItemKeyID );
	// 보조자원 채우기
	HTbool			HT_bNPCControl_SetAidItemResource( DWORD dwItemKeyID );
	
	// 강화제련 단계 별 제련 아이템의 경고문 구하기
	HTint			HT_iNPCControl_GetMainRefineWarning( HTint iRefineLevel, HTdword dwMainRefineIndex );

	//-------------------------------------------------------------------
	// 수리/해체
	//-------------------------------------------------------------------
	HTvoid			HT_vNPCControl_FixDisjoint_LButtonClick( DWORD dwItemKeyID );
	// 수리/해체가 가능한 아이템인지 속성과 현재 NPC를 검사한다
	HTbool			HT_bNPCControl_CheckItemAttriForFixDisjoint(DWORD dwItemKeyID);

	//-------------------------------------------------------------------
	// 스킬
	//-------------------------------------------------------------------
	// 기술 리스트를 받기 전에 저장할 장소 초기화
	HTvoid			HT_vNPCControl_SkillList_Delete();
	// 나열된 스킬 중 마우스로 클릭한 스킬의 이름
	CHTString		HT_szNPCControl_GetSelectSkillName() ;
	// 삭제 가능한 스킬 리스트 가져오기
	HTvoid			HT_vNPCControl_GetSkillList();

	//-------------------------------------------------------------------
	// 주신 선택/변경, 아쉬람 생성, 아쉬람 마크 제작/변경
	//-------------------------------------------------------------------
	// 주신 변경 조건 검사
	HTbool			HT_bNPCControl_CheckConditionTrimuritiChange( );
	// 주신 포인트 확장 조건 검사
	HTbool			HT_bNPCControl_CheckConditionBrahmanPointRising();

	// 아쉬람 생성 성공했을 때 
	HTvoid			HT_vNPCControl_Create_Guild( );
	// 길드마크 생성 성공했을 때 
	HTvoid			HT_vNPCControl_Create_GuildMark( );

	// 차크라 초기화 조건 검사
	HTbool			HT_bNPCControl_CheckConditionChakraInit();
	// 스킬 초기화 조건 검사
	HTbool			HT_bNPCControl_CheckConditionSkillInit();
	
	// 쿠폰 등록 조건 검사
	HTbool			HT_bNPCControl_CheckConditionCoupon();
	// 쿠폰 등록에 관한 메세지창 띄우기
	HTvoid			HT_vNPCControl_SetCouponNotifyMessage( HTbyte byLevel );
	
	//-------------------------------------------------------------------
	// 제련확률 상승-헌납
	//-------------------------------------------------------------------
	// 헌납을 위한 object를 클릭했는지 검사
	HTRESULT		HT_hrNPCControl_ClickOfferingObject(HTint iNum);
	// 헌납할 아이템 클릭했을 경우
	HTvoid			HT_vNPCControl_ButtonCheck_OfferingWin( int iAction, int iTarget, int iTargetID );
	// 헌납 아이템 지우기
	HTvoid			HT_vNPCControl_OfferingItemDeleteAll( );
	HTvoid			HT_vNPCControl_OfferingItemDelete( HTint iPos );
	// 헌납 아이템 추가
	HTvoid			HT_vNPCControl_OfferingItemAdd( DWORD dwItemKeyID );
	// 헌납 전체 취소
	HTvoid			HT_vNPCControl_Offering_Cancel();
 	
	// 헌납액 설정
	HTvoid			HT_vNPCControl_Offering_SetRupiah( HTdword dwRupiah );
	// 헌납 게이지 변경
	HTvoid			HT_vNPCControl_Offering_SetGauge( HTshort sGauge );
	// 헌납창에 있는 아이템 KeyID 구하기
	HTint			HT_iNPCControl_GetKeyIDInOfferingWin( HTint iPos );
	// 헌납창 축복 수치 계산
	HTint			HT_iNPCControl_CalRefineRateUpConst( );

	//-------------------------------------------------------------------
	// 반환 함수
	//-------------------------------------------------------------------
	HTint			HT_iNPCControl_ActiveNPCIndex()	{ return m_iNPCIndex; }
	HTbool			HT_bNPCControl_IsItemMake();
	HTbool			HT_bNPCControl_IsItemWorkActive();
	HTbool			HT_bNPCControl_IsItemFixActive();
	HTbool			HT_bNPCControl_IsItemDisjointActive();
	HTbool			HT_bNPCControl_IsChakraUpStep();
	HTbool			HT_bNPCControl_IsBrahmanUpStep();
	HTbool			HT_bNPCControl_IsRegistLotteryActive();
	HTbool			HT_bNPCControl_IsGuilCreateStep();

	// 메세지 윈도우가 활성화되어있는지
	HTbool			HT_bNPCControl_IsMessageWinActive();
	HTbool			HT_bNPCControl_IsCompleteMsgWinActive();
	HTbool			HT_bNPCControl_IsConfirmMsgWinActive();

	// 서버에 대한 요청 결과에 에러가 있는지(HT_TRUE) 없는지(HT_FALSE)
	HTbool			HT_bNPCControl_RequestResult() { return m_bMessage_Error; };
	// 현재 시간(해/달이 떠있는 시간)을 얻어온다
	HTfloat			HT_fNPCControl_GetCurTime();

	//	m_nCash를 얻어온다.
	HTint			HT_iNPCControl_GetCash() { return m_nCash; };
	HTint			HT_iGetCashNPC(int TabID);

	//-------------------------------------------------------------------
	// 테스크 
	//-------------------------------------------------------------------
	HTbool			HT_bNPCControl_CheckSourceForTaskQuest( HTint iTaskID );

	//////////////////////////////////////////////////////////////////////////////////
	// 네트워크 관련 함수
	//////////////////////////////////////////////////////////////////////////////////
	// 아이템 제조
	HTvoid			HT_vNetWork_CSP_Req_Item_Buy();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info );

	// 아이템 제련
	HTvoid		HT_vNetWork_CSP_REQ_ITEM_REFINING();
	HTvoid		HT_vNetWork_SCP_RESP_ITEM_REFINING( PS_SCP_RESP_ITEM_REFINING );

	// 아이템 수리
	HTvoid		HT_vNetWork_CSP_REQ_ITEM_REPAIR();
	HTvoid		HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR );

	// 아이템 판매
	HTvoid			HT_vNetWork_CSP_Req_Item_Sell();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info );

	// 차크라 포인트 확장
	HTvoid      HT_vNetWork_CSP_REQ_Increase_Chakra();

	// 서버에 차크라 재분배 요청
	HTvoid		HT_vNetWork_SCP_Resp_ChangeChakraToPrana(PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA info);
	
	// 복권 등록 결과일 경우
	HTvoid		HT_vNetWork_RegistLottery(BYTE byResult, DWORD dwKeyID = 0 );

	// 위치 저장
	HTvoid		HT_vNetWork_SCP_Resp_SavePosition( PS_RESULT info );

	// PVP 순위 리스트 요청
	HTvoid		HT_vNetWork_SCP_Resp_PVP_Rank();

	// 주신 선택
	HTvoid		HT_vNetWork_CSP_Req_Select_Trimuriti(BYTE byType);
	HTvoid		HT_vNetWork_SCP_Resp_Select_Trimuriti( MSG_TrimuritySelect* info );

	// 주신 포인트 확장
	HTvoid		HT_vNetWork_SCP_Resp_Rising_Brahman( MSG_TrimurityPoint* info );

	// 전직
	HTvoid		HT_vNetWork_CSP_REQ_Change_Job( );
	HTvoid		HT_vNetwork_SCP_Resp_Change_Job(MSG_CLASS* info);

	// 현재 헌납 수치 요청 결과
	HTvoid		HT_vNetWork_SCP_Resp_RefineScale( MSG_RefineScale* info );

	// 헌납 요청
	HTvoid		HT_vNetWork_CSP_Req_ItemOffering();
	HTvoid		HT_vNetWork_CSP_Req_RupiahOffering(HTint nRupiah);
	HTvoid		HT_vNetWork_SCP_Resp_ItemOffering( MSG_ItemContribution* info );

	// 테스크 요청
	HTvoid		HT_vNetWork_CSP_Req_TaskQuest( HTint iTaskQuest );
	HTvoid		HT_vNetWork_SCP_Resp_TaskQuest( MSG_STANDARDPARM* info );
	
	// 캐쉬 정보 얻기
	HTvoid			HT_vNetWork_CSP_Req_Item_Cash();
	HTvoid			HT_vNetWork_SCP_Resp_Item_Cash( Msg_Cash* info );

	// 차크라/스킬 초기화 정보 얻기
	HTvoid			HT_vNetWork_CSP_Req_CharacterInitialize(HTint iCommand = 2, HTint iType = 0);
	HTvoid			HT_vNetWork_SCP_Resp_Item_CharacterInitialize( Msg_NPCCommand* info );
	
	
	// 기능성 유료화 아이템 신청
	HTvoid			HT_vNetWork_CSP_Resp_Charge_Function_Item( HTdword dwItemIndex );
	HTvoid			HT_vNetWork_SCP_Resp_Charge_Function_Item( Msg_Time* info );

private:
	HTvoid			HT_vNPCControl_SetMessage( HTint idMessage );
	HTvoid			HT_vNPCControl_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );
	// 테스크 퀘스트 소스 검사
	HTbool			HT_bNPCControl_CheckSourceForTaskQuest( HTbyte byType, HTshort sItemID, HTint iSourceCount );
	// 2차 전직용 아이템 검사
	HTint			HT_iNPCControl_CheckItemForChangeJob2();
	//-------------------------------------------------------------------
	// 차투랑가 보드
	//-------------------------------------------------------------------
	// 차투랑가 보드 열기
	HTvoid			HT_vNPCControl_ActiveChaturangaBoard();
	typedef enum _eChaturangaSquad
	{
		eChaturangaNorth = 0,
		eChaturangaSouth,
		eChaturangaCavalry,
		eChaturangaTank,
		eChaturangaCorporal,
		eChaturangaStaff
	} eChaturangaSquad;

	// 차투랑가 보드에 말 표시하기
	HTvoid			HT_vNPCControl_SetChaturangaPiece( eChaturangaSquad eSquad );

public:
	HTbool					m_bNPCActive;
	//---------캐릭터 위치를 가지고 있음---------//
	HTPoint					m_pCharPos_Memory;

	//---------- 현재 창에 대한 정보 --------------//
	HTint					m_iResent;				// 현재 상태 1:대화상자,2:리스트,3:제작,4:수리,5:해체
	BYTE					m_byResent_ServerMsg;	// 현재 서버 요청/결과 메세지

	//---------- 아이템 제조 관련 정보 ------------//
	eEconomy_Item			m_iEconomy_Resent_Item;			//  현재 나타난 아이템 분류.
	BYTE					m_byEconomy_Resent_WinIndex;	//  현재 보여주고 있는 리스트 창의 index
	eEconomy_Item			m_iEconomy_NPC;					//  현재 선택된 NPC(:매번 선택한 NPC를 인덱스로 구분하기 귀찮아서)
	
	HTint					m_iWorkItemCount;				// 구입할 아이템 개수
	HTint					m_iWorkItemMinCount;			// 최소 구입개수
	DWORD					m_dwBuyItem;					// 구입할 아이템 인덱스
	
	CHTString				m_szLottoryNum;					// only event 

	//---------아아템 제련에 관련한 변수---------//
	DWORD					m_dwWorkItem;					// 제작할 아이템 인덱스/KeyID
	HT_ITEMINFO				m_vItemInfo;
	
	HTint					m_nEconomy_Work_LimitRupiah;	// 필요한 돈
	HTint					m_nEconomy_Work_ResRupiah;		// 현재 가지고 있는 돈 (루피아)
	HTint					m_nCash;						// 현재 가지고 있는 돈 (캐쉬)
	HTint					m_nItemCost;					// 제련할 아이템 기본 가격
	DWORD					m_nEconomy_Work_SubItemIndex;

	DWORD					m_nEconomy_Work_SubItemKeyID[5];

	//---------아아템 수리/해체에 관련한 변수---------//
	DWORD					m_dwFixDisjointKeyID;	// 수리/해체할 아이템 KeyID
	HTint					m_iSpendMoney;			// 수리/해체시 사용한/얻은 돈-Message에 사용하기 위해 저장
	BYTE					m_bySelectPart;			// 선택한 차크라, 주신

	//--------- NPC Dialog창에 표시할 정보 관련 ----------//
	HTint					m_iNPCIndex;		//  상인 NPC의 고유 인덱스

	CHTString				m_szNPCName;			// NPC 이름
	DWORD					m_dwNeedValue;			// 필요한 프라나, 남은 캐쉬 등
	CHTString				m_szName;
	HTtchar					m_szQuestion[1000];
	
	HTbyte					m_byParameter;
	HTint					m_nSelectCount;		// 선택문 개수

	HTbool					m_bNextStepByClientEvent; // 클라이언트 이벤트에 의해서 다음 단계로 넘어갔는지..
	HTint					m_Question;

	//--------- 메세지 창에 대한 정보 -------------//
	BYTE					m_byMessageWin;			//  현재 메세지창
	HTbool					m_bMessage_Error;		//  현재 메세지창의 내용이 실패메세지 인지..
	CHTString				m_szMessage;			//  현재 메세지창에 보여줄 내용
	CHTString				m_szObjectName;			//	메세지에 보여주기 위한 특정 object 이름

	//---------- 제작 가능한 아이템 리스트 정보 ------------//
	ECONOMY_LIST			m_Economy_List[8];				// 제작 가능한 아이템 정보

	HTint					m_iMerchantNo;

	HTint					m_iDurgaReceiptofMoney;			// 요새전 적립금액

	//-------------------------------------------------------------------
	// 스킬
	//-------------------------------------------------------------------
	// 습득 가능한 스킬 리스트 정보
	HTint					m_nSkillList_Count;			// 습득가능한 스킬 개수
	HTint					m_nSkillList_Index[50];		// 습득가능한 스킬 인덱스
	CHTString				m_szSkillList_Name[50];		// 습득 가능한 스킬의 이름
	HTint					m_nSkillList_Type[50];		// 스킬의 종류

	// 스킬 등록 인덱스
	DWORD					m_dwSkillRegistIndex;
	BYTE					m_dwSkillRegistType;

	// 스킬/스텟 재분배 이벤트
	HTint					m_nCommand;			// 재분배 (스킬=1/차크라=2) 선택여부
	HTint					m_nType;			// 재분배 사용 여부 (0 = 처음아님, 1 = 처음)
	BYTE					m_nFirst;
	BYTE					m_nFirst2;
	HTint					m_nResult;
	HTint					m_nLevel;
	HTint					m_nRupia;
	DWORD					m_nNowRupia;
	DWORD					m_nNeedRupia;

	//-------------------------------------------------------------------
	// 헌납 - 제련확률 상승 작업
	//-------------------------------------------------------------------
	HTshort					m_sRefineRateGauge;
	HTfloat					m_fGaugeTimer;
	HTint					m_iOfferingItemKeyID[MAX_ITEM_CONTRIBUTION]; // 아이템 키아이디
	HTint					m_iOfferingItemPlace[MAX_ITEM_CONTRIBUTION]; // 아이템 위치
	HTbyte					m_byOfferingItemNum;
	HTbool					m_bPress_OK_Button;
	HTdword					m_dwOfferingRupiah;
	HTint					m_nOfferingObjectNumber;
	HTint					m_nOfferingDialogNumber;


	//-------------------------------------------------------------------
	// 테스크 
	//-------------------------------------------------------------------
	HTint					m_iTaskQuestID;
	HTint					m_iQuestQuizCount; // 문제 번호
	HTint					m_iEventItem;	// 이벤트 아이템 갯수 저장

	// 프리미엄 아이템 데이터 수집
	HTint					m_PrimiumItem[5][30];	// 0 = 패키지, 1 = 공격력, 2 = 방어력, 3 = 편의성, 4 = 특수성
	HTint					m_iMaxPage;
	HTint					m_iNowPage;
	//HTbool					m_bPrimium_Button;		// 프리미엄 버튼을 눌렀는지 여부 판단 

	//-------------------------------------------------------------------
	// 주신변경 비용
	//-------------------------------------------------------------------
	HTfloat					HT_bNPCControl_CheckTrimuritiChangeCost();	// 주신변경 비용검사

	HTint					m_snBrahmaCount;	// 브라흐마 
	HTint					m_snVishnuCount;	// 비슈느
	HTint					m_snSivaCount;		// 시바
	HTbool					m_bTrimutiri;		// 주신 선택인지 조회인지 구분

private:
	CHTTimer*				m_pTimer;
};

#endif
