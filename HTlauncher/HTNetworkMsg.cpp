#include "stdafx.h"
#include "htnetworkmsg.h"

CHTNetworkMsg::CHTNetworkMsg(void)
{
	InitializeCriticalSection( &m_cs ) ;

	m_NetHead = NULL;
	m_NetTail = NULL;

	m_nCount = 0;
}

CHTNetworkMsg::~CHTNetworkMsg(void)
{
	DeleteCriticalSection( &m_cs ) ;
}

HTvoid* CHTNetworkMsg::GetData()
{
	HTvoid* pData = NULL;

	EnterCriticalSection(&m_cs);
	if(!m_NetHead)
		return NULL;
	
	pData = m_NetHead->pData;
	LeaveCriticalSection(&m_cs);

	return pData;
}

HTint CHTNetworkMsg::GetCount()
{
	int nCount = 0;

	EnterCriticalSection(&m_cs);
	nCount = m_nCount;
	LeaveCriticalSection(&m_cs);

	return nCount;
}

HTvoid CHTNetworkMsg::AddData(HTvoid* pData)
{
	HT_NETPACKET_NODE* pNode = new HT_NETPACKET_NODE;

	EnterCriticalSection(&m_cs);

	if(m_NetTail)
	{
		m_NetTail->pNext = pNode;
		m_NetTail = pNode;
		m_NetTail->pData = pData;
		m_NetTail->pNext = NULL;
	}
	else
	{
		m_NetHead = pNode;
		m_NetTail = pNode;
		m_NetTail->pData = pData;
		m_NetTail->pNext = NULL;
	}

	++m_nCount;

	LeaveCriticalSection(&m_cs);
}

HTbool CHTNetworkMsg::DelData()
{
	EnterCriticalSection(&m_cs);

	HT_NETPACKET_NODE* pNode = m_NetHead;

	if(!m_NetHead)
		return false;

	m_NetHead = pNode->pNext;

	if(!m_NetHead)
		m_NetTail = NULL;

	HT_DELETE(pNode);

	--m_nCount;
	LeaveCriticalSection(&m_cs);

	return true;
}

// Packet을 Copy하면서 Delete시킨다.
HTbool CHTNetworkMsg::CopyData( std::vector<HTvoid*>& vectorData )
{
	EnterCriticalSection(&m_cs);

	HT_NETPACKET_NODE* pNode = m_NetHead;
	HT_NETPACKET_NODE* pNodeNext;

	while ( pNode )
	{
		vectorData.push_back( pNode->pData );

		pNodeNext = pNode->pNext;
		HT_DELETE( pNode );
		pNode = pNodeNext;
	}

	m_NetHead = m_NetTail = NULL;

	m_nCount = 0;

	LeaveCriticalSection(&m_cs);

	return true;
}
