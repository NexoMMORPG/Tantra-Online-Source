//----------------------------------------------------------------------------//
//	파일 이름	: TNNetworkQueue.cpp
//
//	파일 설명 	: 
//		- 네트워크에서 받는 데이터들을 저장하는 클레스.
//
//	작성자		:
//		- 2002/08/01, Created by Youn woo Kyoung
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#include "stdafx.h"
#include "TNNetworkQueue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TNNetworkQueue::TNNetworkQueue()
{
	InitializeCriticalSection( &m_cs ) ;
}

TNNetworkQueue::~TNNetworkQueue()
{
	DeleteCriticalSection( &m_cs ) ;
}


//////////////////////////////////////////
//	Pop Data Function	_2002.07.31_y.w.k
//////////////////////////////////////////
void TNNetworkQueue::PopQueue()
{
	EnterCriticalSection( &m_cs ) ;
	m_Queue.pop();
	LeaveCriticalSection( &m_cs ) ;
}


/////////////////////////////////////////////
//	Push Data Function	_2002.07.31_y.w.k
/////////////////////////////////////////////
void TNNetworkQueue::PushQueue(PVOID a_pData)
{
	EnterCriticalSection( &m_cs ) ;
	m_Queue.push(a_pData);
	LeaveCriticalSection( &m_cs ) ;
}


///////////////////////////////////////////
//	Queue's Data Count.	_2002.07.31_y.w.k
///////////////////////////////////////////
HSUINT TNNetworkQueue::GetQueuedDataCount()
{
	HSUINT nCount;

	EnterCriticalSection( &m_cs ) ;
	nCount = m_Queue.size();
	LeaveCriticalSection( &m_cs ) ;

	return nCount;
}


/////////////////////////////////////////////
//	Queue's Header Data.	_2002.07.31_y.w.k
/////////////////////////////////////////////
PVOID TNNetworkQueue::GetFirstPacket()
{
	PVOID pData;
	EnterCriticalSection( &m_cs ) ;
	if(m_Queue.empty())
		return NULL;

	pData = m_Queue.front();
	m_Queue.pop();
	LeaveCriticalSection( &m_cs ) ;

	return pData;
}
