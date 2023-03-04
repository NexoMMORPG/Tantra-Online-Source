#pragma once

class HTSound
{
public:
	HTSound(void);
	~HTSound(void);
	HTvoid				m_vSound_CleanUp();


	HTvoid				m_vSound_Init();
	// 0 : nIndex : 사운드 인덱스
	// 1 : nLoopCount : 반복 횟수
	// 2 : byReset 0:리셋하고 틀기,1:이어틀기
	// 3 : byVolum : 볼륨 ( 0 ~ 1 )
	HTvoid				m_vSound_Play( HTint nIndex, HTint nLoopCount, BYTE byReset, HTfloat byVolum );
	// 스톱 사운드
	HTvoid				m_vSound_Stop( HTint nIndex );

	// 0 : nIndex : 사운드 인덱스
	// 1 : byFadeInOut : 0:페이드 아웃, 1:페이드 인
	HTvoid				m_vSound_FadeEffect( HTint nIndex, BYTE byFadeInOut );




private:
	HTint				m_Sound_ID[200];
};
