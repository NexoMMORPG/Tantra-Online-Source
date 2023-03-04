//----------------------------------------------------------------------------//
//	���� �̸�	: TNNetworkQueue.h
//
//	���� ���� 	: 
//		- ��Ʈ��ũ���� �޴� �����͵��� �����ϴ� Ŭ����.
//
//	�ۼ���		:
//		- 2002/08/01, Created by Youn woo Kyoung
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#if !defined(AFX_TNNETWORKQUEUE_H__5CB8042F_3680_48DC_AE1B_D0563C00E8C1__INCLUDED_)
#define AFX_TNNETWORKQUEUE_H__5CB8042F_3680_48DC_AE1B_D0563C00E8C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TNNetworkQueue  
{
public:
	// Construction/Destruction
	TNNetworkQueue();
	virtual ~TNNetworkQueue();

	void		PopQueue();						//	Pop Data.
	void		PushQueue(PVOID a_pData);		//	Push Data.
	HSUINT		GetQueuedDataCount();			//	Queue's Data Count.
	PVOID		GetFirstPacket();				//	Queue's Header Data.

	std::queue<PVOID>		m_Queue;			//	Queue.

private:
	CRITICAL_SECTION			m_cs;			//	Queue's Criticla Section
};

#endif // !defined(AFX_TNNETWORKQUEUE_H__5CB8042F_3680_48DC_AE1B_D0563C00E8C1__INCLUDED_)
