/*
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Refine Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_REFINE = _DIALOG_REFINE;	// 제련창 윈도우 인덱스 선언
class CHTUIRefineWindow
{
private:

public:
	int			m_SetItemNumber;
	int			m_iWindowIndex[5];
	int			m_iControlIndex[5];

	int			m_iRefineAniNo;				// 제련 애니메이션 인덱스 값
	int			m_nMessageBoxNo;						// 팝업된 메시지 박스는?

	CHTUIRefineWindow(void);
	~CHTUIRefineWindow(void);

	void		HT_vRefineWindow_WindowHide();												// 제련창 윈도우를 닫을때는 이 함수를 사용한다.
	void		HT_vRefineWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vRefineWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vRefineWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// 입력 처리 함수 (UI 입력제어부)
};
*/