/*
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Refine Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_REFINE = _DIALOG_REFINE;	// ����â ������ �ε��� ����
class CHTUIRefineWindow
{
private:

public:
	int			m_SetItemNumber;
	int			m_iWindowIndex[5];
	int			m_iControlIndex[5];

	int			m_iRefineAniNo;				// ���� �ִϸ��̼� �ε��� ��
	int			m_nMessageBoxNo;						// �˾��� �޽��� �ڽ���?

	CHTUIRefineWindow(void);
	~CHTUIRefineWindow(void);

	void		HT_vRefineWindow_WindowHide();												// ����â �����츦 �������� �� �Լ��� ����Ѵ�.
	void		HT_vRefineWindow_Init();														// ó�� ������ �ѹ��� ���� (UI ������)
	void		HT_vRefineWindow_WindowPopup();												// ó�� ȭ�� �˾��� ȣ�� (�ܺο��� �ʿ��Ҷ� ȣ���ϴ� �Լ�)
	void		HT_vRefineWindow_SetInfo();													// ȭ�� ���Ž� ȣ�� (UI ���ź�)
	static void HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// �Է� ó�� �Լ� (UI �Է������)
};
*/