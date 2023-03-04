#pragma once

//----------Network Packet Data struct----------//
typedef struct _HT_NETPACKET_NODE
{
	HTvoid* pData;
	_HT_NETPACKET_NODE* pNext;
} HT_NETPACKET_NODE;

class CHTNetworkMsg
{
public:
	CHTNetworkMsg(void);
	~CHTNetworkMsg(void);

	HTvoid*	GetData();
	HTint				GetCount();

	HTvoid				AddData(HTvoid* pData);
	HTbool				DelData();
	HTbool				CopyData( std::vector<HTvoid*>& vectorData );

private:
	//	Packet List Head and Tail
	HT_NETPACKET_NODE* m_NetHead;
	HT_NETPACKET_NODE* m_NetTail;

	//	Network Packet Count
	HTint m_nCount;

	CRITICAL_SECTION	m_cs;			//	Criticla Section
};
