#pragma once

class HTStatus
{
public:
	HTStatus(void);
	~HTStatus(void);

	HTvoid		HT_vStatus_CleanUp();

	HTvoid		HT_vStatus_Init();
	//	Create Window
	HTvoid		HT_vStatus_CreateWindow();
	//	입력 메세지 처리
	//	Beauty Salon
	static void			HT_vParty_InputCheckForBeautySalon(int iAction, int iTarget, int iTargetID);

	HTvoid		HT_vStatus_ActiveSw();
	HTvoid		HT_vStatus_SetActive();
	HTvoid		HT_vStatus_SetAntiActive();
	//	ESC Key 누르면 창 닫기
	HTvoid		HT_vStatus_ESC_CloseWindow();


	//---------반환 값 및 셋팅----------//
	HTvoid		HT_vStatus_SetMessage( HTint idMessage, CHTString* pszMessage );
	HTvoid		HT_vStatus_SetParamTextForMessage( HTshort sParam, CHTString* pszParam );

	CHTString	HT_szStatus_GetTrimuriti();
	HTbool		HT_bStatus_GetActive();
	HTvoid      HT_vStatus_HPCheck();
	HTvoid		HT_vStatus_SetChakra_Rising( PS_SCP_RESP_CHAKRA_RISING );
	CHTString	HT_szStatus_GetJobName();	// 전직 이후 직업이름
	HTint		HT_iStatus_GetJob1ForTribe();

	HTint		HT_nGetChakraMuscle();
	HTint		HT_nGetChakraHeart();
	HTint		HT_nGetChakraNerve();
	HTint		HT_nGetChakraSoul();
	//HTint		HT_nGetTotalChakra();
	HTbyte		HT_byGetLevel();
	HTint		HT_iGetKarmaPoint();

	CHTString	HT_szStatus_GetCastClass();
	HTint		HT_iStatus_GetCastClass();

	// 아이템 등의 의해서 더해진 차크라 옵션
	HTint		HT_nGetPureChakraMuscle();
	HTint		HT_nGetPureChakraHeart();
	HTint		HT_nGetPureChakraNerve();
	HTint		HT_nGetPureChakraSoul();

	//---------네트윅 통신 부분----------//
	HTvoid		HT_vStatus_ChangeParams( PS_SCP_CHAR_PARAMS_CHANGE );
	HTvoid		HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info );

	//	Network	LevelUp Brodcast
	HTvoid		HT_vStatus_NetworkLevelUpBrodcast( PS_SCP_LEVEL_UP_BROADCAST info );

	//	MainChar BeautyFace
	HTvoid		HT_vStatus_BeautyFace_MouseCheck( HTint iButtonNo );
	//	MainChar BeautyHear
	HTvoid		HT_vStatus_BeautyHear_MouseCheck( HTint iButtonNo );
	//	MainChar BeautyTribe
	HTvoid		HT_vStatus_BeautyTribe_MouseCheck( HTint iButtonNo );
	//	MainChar BeautyOK
	HTvoid		HT_vStatus_BeautyOK_MouseCheck( HTint iBuyTany, HTint iDlgNo );
	//	MainChar BeautyBack
	HTvoid		HT_vStatus_BeautyBack();
	//	MainChar Request Beauty
	HTvoid		HT_vStatus_NetworkReqBeauty();
	//	MainChar Recive Beauty
	HTvoid		HT_vStatus_NetworkReciveBeauty( MSG_Beauty* info );
	// Set Render
	HTvoid		HT_vStatus_Beauty_Render(HTint iDlgNo);
	
public:
	PS_SCP_CHAR_PARAMS_CHANGE	m_sStatus_CharParms;
	S_SCP_RESP_UPDATE_UI		m_sStatus_CharInfo;

	HTshort						m_snAttackRate;
	HTshort						m_snDodgeRate;
	
	HTint						m_nStatus_ChakraPoint;
	HTbool						m_bStatus_Active;

	HTint						m_nCharacterHair;   // 캐릭터 헤어 (종합 미용실 이용시만 사용)
	HTint						m_nCharacterFace;	// 캐릭터 얼굴
	HTint						m_nCharacterTribe;	// 캐릭터 종족
	DWORD						m_dwBeautyItemKeyID;	// 미용실 아이템 키아이디

	//	Bye Tany
	HTint						m_iBuyTany;
	//	현재 활성화된 미용실 윈도우
	HTint						m_iBeautyWndNo;
};

