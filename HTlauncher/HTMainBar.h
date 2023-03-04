//======================================================================
// HTMainBar.h
// 화면 하단의 메인 바
// (주)한빛소프트 게임개발팀 서명석		2003.03.07
//======================================================================
#pragma once

#define			MYSKILL_COUNT					10

class CHTMainBar
{
public:
	CHTMainBar();
	~CHTMainBar();

	HTvoid			HT_vLoad();
	HTvoid			HT_vMainBar_CreateWindow();

	//	입력 메세지 처리
	//	Main Bar
	static void		HT_vMainBar_InputCheckForMainBar(int iAction, int iTarget, int iTargetID);
	//	Main Char HP
	static void		HT_vMainBar_InputCheckForMainCharHP(int iAction, int iTarget, int iTargetID);
	//	Prana Bar
	static void		HT_vMainBar_InputCheckForPranaBar(int iAction, int iTarget, int iTargetID);
	//	Buff Skill
	static void		HT_vMainBar_InputCheckForBuffSkill(int iAction, int iTarget, int iTargetID);

	//	Set PK Button
	HTvoid			HT_vMainBar_GameSystem_SetForPKButton();

	//	메인바_스케쥴러
	HTvoid			HT_vMainBar_Control( HTfloat );
	//	오브젝트 상자에 텍스트를 쓴다.
    HTvoid			HT_vSetObjectTextDraw( CHTString );
	//	오브젝트 상자에 HP를 그린다.
	HTvoid			HT_vSetObjectHPDraw( HTint, HTint );
	//	오브젝트 상자에 HP를 그리지 않게 하다
	HTvoid			HT_vSetObjectHPOut();
	//	오브젝트 상자에 Name를 그리지 않게 하다
	HTvoid			HT_vSetObjectNameOut();

    // 데이터 업데이트
	//----------------------------------------------------------------------------------
	// 새로운UI수정(20030728)
	//----------------------------------------------------------------------------------
	HTvoid			HT_vPranaUpdate( HTint iTotalPrana );
	HTvoid			HT_vHPUpdate(HTint iCurHP, HTint iMaxHP );				// HP 정보를 업데이트 한다.
	HTvoid			HT_vMainBar_SetCurTransparent( HTint iCurHP, HTint iMaxHP );	// 물약에 의한 HP 정보를 업데이트 한다.
	//----------------------------------------------------------------------------------
	//--------------------------------------------------------------
	// D : Tapas
	//--------------------------------------------------------------
	HTvoid			HT_vMainBar_SetCurTP( HTint, HTint );					//	CUR TP 셋팅
	HTint			HT_iMainBar_GetCurTP()	{ return m_iMainBar_CurTP; };	//	CUR TP 가져오기
	HTint			HT_iMainBar_GetMaxTP()	{ return m_iMainBar_MaxTP; };

	//==============================================================
	// 새로운UI수정(20030728)
	//==============================================================
	//--------------------------------------------------------------
	// HTint			HT_iGetCurChacra()
	// D : 현재 보여주고 있는 차크라를 보여준다.
	//--------------------------------------------------------------
	HTint			HT_iGetCurChacra()	{ return m_iCurChacra; };
	HTbool			HT_bGetPKButton()	{ return m_bMainBar_PKButton;	};

	//	레벨업에 필요한 프라나 셋팅
	HTvoid			HT_vMainBar_SetNeedPrana( HTint iNeedPrana )	{	m_dwNeedPrana = iNeedPrana;	};

	//	나의스킬 셋팅
	HTvoid			HT_vMainBar_SetMySkill( HTint iSkillID, BYTE byActor, HTshort snSkillLevel );
	//	나의스킬 끝나는 시간 Check
	HTvoid			HT_vMainBar_MySkillEndTimeCheck();
	//	나의스킬 Init
	HTvoid			HT_vMainBar_MySkillInit();
	//	나의스킬 원하는 녀석만 Delete
	HTvoid			HT_vMainBar_MySkillSetDelete( HTint iSkillID );

private:
	//	선택한 대상의 이름
	CHTString		m_strPickObjectName;

	// HP와 프라나 정보
	CHTString		m_strHP;
	CHTString		m_strPRANA;

	//	프라나 
	HTint			m_iScreenWidth;
	HTint			m_iScreenHIGHT;

	// Sprite의 ID
	HTint			m_iActionSkillID;			// Action Skill
	HTint			m_iActiveSkillID;			// Active Skill

	//	스킬 총 카운트
	HTint			m_nSkillTotalCount;

	// 레벨업에 필요한 프라나
	DWORD			m_dwNeedPrana;

	//	챠크라 필요량 표시
	HTbool			m_bChacraBoxSw;

	// 새로운UI수정(20030728)
	HTint			m_iCurChacra;
	HTint			m_iTotalPrana;

	//	타파스
	HTint			m_iMainBar_MaxTP;
	HTint			m_iMainBar_CurTP;

	//	나의 스킬
	HTint			m_iMainBar_MySkillID[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillStartTime[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillDurationTime[MYSKILL_COUNT];
	HTbool			m_bMainBar_MySkillBufWaring[MYSKILL_COUNT];
	HTint			m_iMainBar_MySkillSaveBufWaringNo[MYSKILL_COUNT];

	//	PK Button
	HTbool			m_bMainBar_PKButton;

	//	아이템 판매를 하지 않는 나라를 위ㅐ서
	HTint			m_iForDelPriminumIconX;
};
