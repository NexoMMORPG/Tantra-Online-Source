#pragma once

class HTSystem
{
public:
	HTSystem(void);
	~HTSystem(void);

	int					m_iOption0;		// 알파값
	bool				m_bOption1;		// 아이디표시
	bool				m_bOption2;		// 이펙트
	bool				m_bOption3;		// 상점간소화
	int					m_iOption4;		// 사운드
	int					m_iOption5;		// 음악
	bool				m_bOption6;		// 슬롯셋팅
	bool				m_bOption7;		// 캐릭터 생기고 사라지고 셋팅

	
	HTvoid				HT_vSystem_CleanUp();

	HTvoid				HT_vSystem_Init();
	//	Create Window
	HTvoid				HT_vSystem_CreateWindow();
	//	입력함수 처리
	static void			HT_vSystem_InputCheckSystem(int iAction, int iTarget, int iTargetID);

	HTbool				HT_bSystem_GetActiveSw()	{ return m_bSystem_WindowActiveSw; };
	//----------활성화 / 비활성화----------//
	HTvoid				HT_vSystem_ActiveSw();
	//	ESC Key 누르면 시스템창 닫기
	HTvoid				HT_vSystem_ESC_CloseWindow();

	// 종료 창 버튼 활성화 / 비 활성화

	HTbool				HT_bSystem_GetActiveSkillEffectSw()	{ return m_bSystem_ActiveSkillEffectSw; };

	HTbool				HT_bSystem_GetMyNameShow() { return m_bMyNameShow; }
	HTbool				HT_bSystem_GetNPCNameShow() { return m_bNPCNameShow; }
	HTbool				HT_bSystem_GetOtherCharNameShow() { return m_bOtherCharNameShow; }
	HTbool				HT_bSystem_GetShopModelMode() { return m_bShopModelMode; }
	HTbool				HT_bSystem_GetF1ToF10Mode() { return m_bF1ToF10SlotMode; }

public:

	HTbool						m_bSystem_ExitSw;
	HTbool						m_bSystem_WindowActiveSw;
	HTvector3					m_vSystem_WindowPos;
	HTbool						m_bSystem_ActiveSkillEffectSw;

	HTfloat						m_fBright;
	HTfloat						m_fStreamVolume;
	HTfloat						m_fSampleVolume;


private:
	HTint						m_iSelectSlideNo;	//20030521,DAEHO

	HTbool						m_bMyNameShow;	// 본인 이름 표시
	HTbool						m_bNPCNameShow; // 몬스터, NPC 이름 표시
	HTbool						m_bOtherCharNameShow; // 다른 플레이어 이름 표시
	HTbool						m_bInitUI;
	HTbool						m_bRootingMode;	// 아이템 자동분배 모드
	HTbool						m_bChattingMode; // 채팅모드
	HTbool						m_bMinimapMode; // 채팅모드
	HTbool						m_bShopModelMode;	//	개인상점 Model 모드
	HTbool						m_bF1ToF10SlotMode;		//	F1-F10까지 슬롯/스킬 모드 변환
};
