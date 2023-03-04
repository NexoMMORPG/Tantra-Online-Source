#pragma once

class HTSound
{
public:
	HTSound(void);
	~HTSound(void);
	HTvoid				m_vSound_CleanUp();


	HTvoid				m_vSound_Init();
	// 0 : nIndex : ���� �ε���
	// 1 : nLoopCount : �ݺ� Ƚ��
	// 2 : byReset 0:�����ϰ� Ʋ��,1:�̾�Ʋ��
	// 3 : byVolum : ���� ( 0 ~ 1 )
	HTvoid				m_vSound_Play( HTint nIndex, HTint nLoopCount, BYTE byReset, HTfloat byVolum );
	// ���� ����
	HTvoid				m_vSound_Stop( HTint nIndex );

	// 0 : nIndex : ���� �ε���
	// 1 : byFadeInOut : 0:���̵� �ƿ�, 1:���̵� ��
	HTvoid				m_vSound_FadeEffect( HTint nIndex, BYTE byFadeInOut );




private:
	HTint				m_Sound_ID[200];
};
