//////////////////////////////////////////////////////////////////////////////////////////
// 설명 : 위탁 상점 클래스
// 
// 작성자 : 선영범
// 2005.10.13
//
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HTRentalStore_H_
#define _HTRentalStore_H_

class CHTRentalStore
{
public:
	CHTRentalStore(void);
	~CHTRentalStore(void);
	
	// 위탁상점에 나열할 아이템 배열
	STRUCT_RENTALITEM	ItemList[MAX_USERRENTALITEM];			// 판매중인 아이템 리스트 저장배열
	DWORD				m_iStoreItemKeyID[MAX_USERRENTALITEM];	// 아이템 판매 정보를 보기위한 KeyID 저장배열
	WORD				m_wIndex[MAX_USERRENTALITEM];			// 나의 아이템 리스트 인덱스 저장 번호

	HTint				m_iStoreIndex;							// 선택한 상점 인덱스
	HTint				m_iNPCIndex;							// 선택한 상점 NPC 인덱스
	HTint				m_iBage;								// 재고 아이템 패킷 받은 횟수 기록

	// 위탁요청을 위한 필요정보
	DWORD				m_dwSelectKeyID;						// 키아이디

	DWORD				m_dwHour;								// 초단위
	DWORD				m_dwIndex;								// 인벤토리내 인덱스
	DWORD				m_dwMoney;								// 판매할 금액
	int					m_iTex;									// 세금
	float				m_fTotalTex;							// 위탁판매를 위한 총세금
	int					m_iStore_MsgBoxType;					// 메시지박스 구별을 위한 내부처리용 플래그 변수

	int					m_nWindowType;							// 현재 윈도우 팝업상태 (나의 아이템 = 0, 상점 아이템 = 1)

	// Initialize Rental Store
	HTvoid			HT_vRentalStore_CleanUp();
	HTvoid			HT_vRentalStore_Init();

	// Window Processing Functions
	HTvoid			HT_vRentalStore_CreateWindow();		// 윈도우 생성
	HTvoid			HT_vRentalStore_PopupWindow();		// 윈도우 팝업

	// MessageBox Processing Functions
	HTvoid			HT_vRentalStore_TexWin_Active();
	HTvoid			HT_vRentalStore_PriceWin_Active();
	HTvoid			HT_vRentalStore_TimeWin_Active();
	HTvoid			HT_vRentalStore_GetPriceWin_Active();

	// Sell & Buy Processing Functions
	HTvoid			HT_vRentalStore_SelectItemForSell( HTdword dwItemKeyID, int iInvenID ); // 인벤에 있는 물품 판매 하기

	// Window Procedure Functions
	static void		HT_vEI_InputCheckForRentalStore(int iAction, int iTarget, int iTargetID);
	static void		HT_vEI_InputCheckForBuyListWnd(int iAction, int iTarget, int iTargetID); //	Bye List Wnd
 
	// 스크립트로부터 전달된 처리 함수
	HTvoid HT_EventReqRentalAdminSellInfo();		// 비류성 위탁판매 관리자 (자신의 아이템 판매현황 보기) - 3042 - (판매 리스트창 팝업)
	HTvoid HT_EventReqRentalAdminReciveItem();		// 비류성 위탁판매 관리자 (자신의 아이템 돌려받기) - 3043 - (보관중인 아이템 찾기요청 패킷 호출)
	HTvoid HT_EventReqRentalAdminReciveList();		// 비류성 위탁판매 관리자 (자신의 아이템 돌려받을 리스트 보기) - 3044 - (보관중인 리스트창 팝업)
	HTvoid HT_EventReqRentalBuyList();				// 비류성 위탁판매 일반인 (판매중인 아이템 목록보기) - 3045 (위탁상점창 팝업) - 구입모드
	HTvoid HT_EventReqRentalSell();					// 비류성 위탁판매 일반인 (자신의 아이템 판매) - 3046 (위탁상점창 팝업) - 판매모드
	HTvoid HT_EventReqRentalUsingTex();				// 비류성 위탁판매 일반인 (위탁판매 이용 세금 보기) - 3047 (스크립트로 출력)
	HTvoid HT_EventReqRentalItemRupia();			// 비류성 위탁판매 관리자 (위탁판매 아이템 루피아 보기) - 3048 (스크립트로 출력)
	HTvoid HT_EventReqRentalSetTex();				// 비류성 위탁판매 일반인 (위탁판매 이용 세금 설정) - 3049 (스크립트로 출력)

	HTint	HT_iRentalStore_GetKeyIDInSellWin( HTint iPos );	// 판매창에 등록된 아이템 KeyID 구하기
	HTint	HT_iRentalStore_GetKeyIDInBuyWin( HTint iPos );		// 구매창에 등록된 아이템 KeyID 구하기
	HTint	HT_iRentalStore_GetRupiah( HTdword dwKeyID );		// 판매목록의 아이템 가격 구하기
	HTint	HT_iRentalStore_GetPackCount( HTdword dwKeyID );	// 판매목록의 아이템 개수 구하기

	// Network Functions
	// Request Part
	HTvoid HT_vRequestMyRentalItemList();					// 나의 위탁 아이템 리스트를 요청
	HTvoid HT_RequestRentalItemList(DWORD dwStoreIndex);	// 특정 위탁상점의 아이템리스트 요청
	HTvoid HT_RequestRentalItemAdd();						// 아이템을 위탁함
	HTvoid HT_RequestRentalItemCancel();					// 위탁한 아이템을 취소
	HTvoid HT_RequestRentalGetMoney(int iType);				// 저장된 나의 돈 찾기 0 = 조회, 1 = 찾기
	HTvoid HT_RequestRentalGetItem();						// 저장된 내 물품 찾기 (기간 지난 아이템들)
	HTvoid HT_RequestRentalTex(int iType);					// 위탁상점의 세율 정함 0 = 조회, 1 = 찾기
	HTvoid HT_RequestRentalStoreClose();					// 위탁상점 성주가 닫기
	HTvoid HT_RequestRentalItemBuy();						// 위탁상점에서 아이템 구입
	HTvoid HT_RequestRentalStockItemList();					// 서버에 재고아이템리스트를 요청한다.
//	HTvoid HT_RequestRentalStockItem();						// 서버에 재고아이템을 요청한다.

	// Recive Part
	HTvoid HT_vRentalStore_SCP_MyRentalItemList( Msg_MyRentalItemList* info );	// 나의 위탁 아이템 리스트를 요청 응답
	HTvoid HT_vRentalStore_SCP_RentalItemList( Msg_RentalItemList* info );		// 특정 위탁상점의 아이템리스트 요청 응답
	HTvoid HT_vRentalStore_SCP_RentalItemAdd( Msg_RentalItemAdd* info );		// 아이템을 위탁함 응답
	HTvoid HT_vRentalStore_SCP_RentalItemCancel( Msg_RentalItemCancel* info );	// 위탁한 아이템을 취소 응답
	HTvoid HT_vRentalStore_SCP_RentalGetMoney( Msg_RentalGetMoney* info );		// 저장된 나의 돈 찾기 응답
	HTvoid HT_vRentalStore_SCP_RentalGetItem( Msg_RentalGetItem* info );		// 저장된 내 물품 찾기 (재고 아이템들) 응답
	HTvoid HT_vRentalStore_SCP_RentalTex( Msg_SetRentalTex* info );				// 위탁상점의 세율 정함 응답
	HTvoid HT_vRentalStore_SCP_RentalStoreClose( Msg_RentalStoreClose* info );	// 위탁상점 성주가 닫기 응답
	HTvoid HT_vRentalStore_SCP_RentalItemBuy( Msg_RentalItemBuy* info );		// 위탁상점에서 아이템 구입 응답
	HTvoid HT_vRentalStore_SCP_RentalStockItemList( Msg_RentalStockItemList* info );// 서버에 재고아이템리스트를 요청한다. 응답
//	HTvoid HT_vRentalStore_SCP_RentalStockItem( Msg_RentalStockItem* info );// 서버에 재고아이템을 요청한다. 응답
};

#endif