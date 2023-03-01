#define _WIN32_WINNT 0x500 // for use "TryEnterCriticalSection"

// standard include
#include "stdafx.h"

#include <windows.h>
#include <windowsx.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BaseDef.h"
#include "TNDebug.h"


//#ifdef __ZONE_SERVER__
//
//	#ifndef _HTMEMORYMANAGER_H_
//	#include "HTMemoryManager.h"
//	#endif
//
//#endif //__ZONE_SERVER__

#include "CPSock.h"
//#include "protocol.h"
CRITICAL_SECTION	csConnecter;
unsigned char pKeyWord[256][2] = {
	235,125,  215,124,  135,105,  235,121,  235,121,  235,127,  135,125,  135,102,  205,125,  235,125,
	115,115,   35, 55,  215,145,  205,121,  225,125,  235,115,   35,125,  225,123,  135,145,  135,229,
	125,215,  115, 47,  135,105,   35,124,  205,123,  235,121,   35,125,  115,125,   32,212,  235,120,
	131,225,  235,144,   35,195,   15,135,  145,121,   35,121,  135,120,  135,132,   27,125,  235,128,
	130,110,  145,124,  135,187,  235,121,  255,  5,  235,105,  205,111,  235,121,  235, 25,    5, 47,
	194, 95,   25, 65,  235,145,  113,123,  167, 75,  230,125,  164,125,  135, 25,   33,194,  135, 22,
	235,112,  235,125,   35,125,  235,125,  235, 23,   35,128,  205,120,  235,125,  135,125,  235,123,
	139,195,  235,122,  135,125,  212,131,  209,221,  235,120,  246,126,  135,125,  136, 25,  135,245,
	135,125,  215,225,  155,135,  235,155,  205,123,   35,108,  131,127,  235, 20,  235,125,   31,115,
	235,125,  233, 15,   35, 22,  235, 25,  215,155,  141,155,  163,125,  202,115,  131,122,  135,125,

	231,125,  235,125,  231,125,  235,125,  235,125,  215,103,  235,125,  135,125,  235,125,  235,125,
	132,125,  235,125,  235,125,  231,125,  135,121,  235,152,  245,102,  235,128,  135, 26,  135,225,
	232,111,  209,121,  131,155,  225,133,  141,123,   15,121,  225,121,  235,107,  135,125,  235,124,
	 45,125,  215,221,  233,115,  235,134,   15,121,  232,121,   05,125,  215,205,  235,225,  135,221,
	215,143,    5,125,  235,122,  231,115,  235,155,  211,135,  233,124,  205, 15,  235,128,  235,121,
	132,135,   55,215,  234,121,  141,145,   11,115,   75, 25,  235,105,  145, 35,  135,129,  235,224,
	 35,225,   75,131,  163,161,  245,121,   33,125,  230,105,   35,126,  174,124,   15,225,  135,106,
	231,121,  155,125,    2,145,  235,123,  134,113,  221, 45,  135,111,  231,121,  215,124,   35, 28,
	 35,125,  235,127,  175,121,   55,104,  195,121,  205,125,  235,122,   33,125,  235, 25,  235,149,
	135,125,  225,120,  205,125,  135,125,  215,125,   35,125,  135,124,  221,145,  235,122,  235,175,

	135, 35,  235, 16,  205,223,  135,134,  135,165,  135,124,  115,126,  237,125,  215,125,  235,125,
	 15,125,  215,125,  225,122,  104,121,  214,126,  235,152,  235,121,  245,125,  225,122,  235, 35,
	 55,111,   35,124,  135,123,  215,122,  125,128,  231,103,  235,122,   35,125,  135,106,  235,165,
	 35,125,  235,127,  175,121,   55,124,  195,121,  205,125,  235,122,   33,125,  235, 25,  235,149,
	 35,125,   35,121,  213,125,  115,125,  225,122,  135,121,  235,125,  235,125,  205,122,  235, 55,
	235,115,  215,135,  231,227,  235,108,  124,145,  235,125
};

//extern	unsigned int CurrentTime;
//extern	unsigned int LastSendTime;
int		ConnectPort=0;
void	Log ( char * String1, char * String2 ,unsigned int ip);
void HSGEXLog(char* szBuf, char* file)
{
}
//////////////////////////////////////////////////////////////////////////
//
//             CPSock,  ~CPSock
//
//  ���Ź��ۿ� �۽� ���۸� �Ҵ��Ѵ�.
//  �۽Ź����� ���Ź��� ������ ���� 
//////////////////////////////////////////////////////////////////////////
int SocketInitialized = 0;


CPSock::CPSock()
{	
	Sock = 0;
	Init = 0;
	pSendBuffer      = 0;//(char *)malloc(SEND_BUFFER_SIZE);
	pRecvBuffer      = 0;//(char *)malloc(RECV_BUFFER_SIZE);

	nSendPosition    = 0;
	nSentPosition    = 0;
	nRecvPosition    = 0;
	nProcPosition    = 0;
	memset(&ThreadParm,0,sizeof(ThreadParm));
	AsyncSock=0;
	ucRecvSeq = 0;
	ucSendSeq = 0;
	oldSendChecksum = 0;
	oldRecvChecksum = 0;

	if	(SocketInitialized==0) {WSAInitialize();SocketInitialized=1;}

}

CPSock::~CPSock()
{   if (pSendBuffer	!= NULL)    delete[] pSendBuffer;//free(pSendBuffer);
    if (pRecvBuffer != NULL)    delete[] pRecvBuffer;//free(pRecvBuffer);
}

BOOL CPSock::CloseSocket(void)
{	nSendPosition    = 0;
	nSentPosition    = 0;
	 nRecvPosition    = 0;
	 nProcPosition    = 0;
	 Init             = 0;
     if (Sock!=0) closesocket(Sock);
	 Sock=0;
	 return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//
//                       WSAInitialize   
//
// WSA �ʱ�ȭ
// ���� Ŭ���̾�Ʈ ��� ���� 1ȸ�� ���� �Ѵ�
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::WSAInitialize(void)
{    WSADATA WSAData;
     if (WSAStartup(MAKEWORD(1,1), &WSAData) != 0) return FALSE;
 	 return TRUE;
}


/////////////////////////////////////////////////////////////////////////
//
//                       StartListen
//
// ���ż���(LSock)���� Listen�� �����Ѵ�.
// ������ WSA_ACCEPT�� �����Ѵ�.
// ������ LSock��, ���н� FALSE(0)�� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::StartListen( HWND hWnd, int ip,int port, int WSA )
{      
	   
	SOCKADDR_IN	local_sin;
	char		Temp[256];
	SOCKET		tSock = socket(AF_INET,SOCK_STREAM,0);
	if	(tSock==INVALID_SOCKET) 
	{	MessageBox (hWnd,"Initialize socket fail","ERROR",MB_OK);
		return FALSE;
	}
    
	gethostname(Temp, 256);
	local_sin.sin_family		= AF_INET;
	local_sin.sin_addr.s_addr	= ip;		//INADDR_ANY;
	local_sin.sin_port			= htons((unsigned short int)port);       


	if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
	{	MessageBox (hWnd,"Binding fail","ERROR",MB_OK);
		closesocket(tSock);
		return FALSE;
	}
	if	(listen(tSock,MAX_PENDING_CONNECTS) < 0)
	{	MessageBox (hWnd,"Listen fail","ERROR",MB_OK);
		closesocket(tSock);
		return FALSE;
	}
	if	(WSAAsyncSelect(tSock,hWnd, WSA ,FD_ACCEPT)>0)
	{	MessageBox (hWnd,"WSAAsyncSelect fail","ERROR",MB_OK);
		closesocket(tSock);
		return FALSE;
	}
	Sock=tSock;
	Port = port;
	IP	= ip;
	return TRUE;
}




/////////////////////////////////////////////////////////////////////////
//
//                       ConnectServer
//
//
// �־��� IP�� Port�� ������ �����Ѵ�.
//
// ������ Sock��, ���н� FALSE(0)�� �����Ѵ�.
// 
/////////////////////////////////////////////////////////////////////////
SOCKET CPSock::ConnectServer(char *HostAddr , int Port , int ip, int WSA,HWND WindowHandle)
{      
	SOCKET tSock = socket( AF_INET, SOCK_STREAM, 0);
	if	(tSock==INVALID_SOCKET) 
    {	MessageBox (NULL,"Initialize socket fail","ERROR",MB_OK);
		return FALSE;
	}
	nRecvPosition = 0;
	nSendPosition = 0;
	nProcPosition = 0;
	oldRecvChecksum = oldSendChecksum = ucRecvSeq = ucSendSeq = 0;
    if (Sock!=0) CloseSocket();

	// Bind local IP
	SOCKADDR_IN local_sin;	memset(&local_sin,	0,	sizeof(local_sin));
    local_sin.sin_family		= AF_INET;
    local_sin.sin_addr.s_addr	= ip;		//INADDR_ANY;
  	local_sin.sin_port			= 0;		//htons((unsigned short int)(ConnectPort+5000));       
	if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
    {	ConnectPort=ConnectPort+10;
		local_sin.sin_port = htons((unsigned short int)(ConnectPort+5000));       
		if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
		{	ConnectPort=ConnectPort+10;
			local_sin.sin_port = htons((unsigned short int)(ConnectPort+5000));       
			if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
			{	MessageBox (NULL,"Binding fail","ERROR",MB_OK);
				closesocket(tSock);
				return 0;
			}
		}
	}
	if	( tSock == INVALID_SOCKET)	return 0;

	// Connect
	SOCKADDR_IN InAddr;		memset(&InAddr,		0,	sizeof(InAddr));
	InAddr.sin_addr.s_addr	= inet_addr(HostAddr);
  	InAddr.sin_family		= AF_INET;
	InAddr.sin_port			= htons((unsigned short)Port);

	int nError = connect(tSock,(PSOCKADDR)&InAddr,sizeof(InAddr));

	if	( nError < 0)       
	{	closesocket(tSock);Sock=0;
		return 0;
	}

	if	(WSAAsyncSelect(tSock,WindowHandle,WSA,FD_READ|FD_CLOSE)>0) 
	{	closesocket(tSock);Sock=0;
		return 0;
	}
	//--------------------------------------------------------------- �̽������� thread�ϰ�� ���ϰ� ó���� �ȵǵ� wsa_read�� ���� ������.
	Sock=tSock;
	unsigned int InitCode = INITCODE;
	send(tSock,(char*)&InitCode,4,0);
	Init = 1;
	return tSock;
}

int ShutDown =0;
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// cp�� ������ �ı����� �����Ƿ� ���ϴ� ����. 
	CPSock * cp = (CPSock *)lpParameter;
	InitializeCriticalSection (&csConnecter);

	while(TRUE)
	{
		int ret = TryEnterCriticalSection(&csConnecter);
		if	(ret==NULL)
		{	Sleep(2000);
			continue;
		}
		if	(ShutDown)	{Sleep(1000);continue;}
		if	(cp->Sock!=NULL || cp->AsyncSock!=NULL)
		{	LeaveCriticalSection (&csConnecter);
			Sleep(2000);
			continue;
		}
		//	1�ʿ� �ѹ�
		cp->AsyncSock = cp->ConnectServer(cp->ThreadParm.HostAddr,cp->ThreadParm.Port,cp->ThreadParm.ip,cp->ThreadParm.WSA,cp->ThreadParm.WindowHandle);
		if	(cp->AsyncSock==NULL)
		{	memset(&(cp->ThreadParm),0,sizeof(cp->ThreadParm));
		}
		// �����ϸ�?
		//
		LeaveCriticalSection (&csConnecter);
		Sleep(2000);
	};
	return TRUE;
}
//	


	//SuspendThread(ThreadHandle);

// �ݵ�� ���� �ѹ��� ����Ǿ�� �Ѵ�
// ���� �������� thread�� �ڵ����� ���δ�
void CPSock::ConnectServerAsync(char *HostAddr , int Port , int ip, int WSA,HWND WindowHandle)
{
	//STRUCT_SOCKET_THREAD_PARM parm;
	strcpy(ThreadParm.HostAddr,HostAddr);
	ThreadParm.Port			= Port;
	ThreadParm.ip			= ip;
	ThreadParm.WindowHandle	= WindowHandle;
	ThreadParm.WSA			= WSA;
	HANDLE ThreadHandle = CreateThread(NULL,NULL, ThreadProc,(void *)this, 0, NULL);

}

void CPSock::RefreshRecvBuffer(void)
{	int left = nRecvPosition-nProcPosition;
	if	(left<=0) return;
	memcpy(pRecvBuffer,pRecvBuffer+nProcPosition,left);
	nProcPosition = 0;
	nRecvPosition = nRecvPosition - left;
}

void CPSock::RefreshSendBuffer(void)
{	int left = nSendPosition-nSentPosition;
	if	(left<=0) return;
	memcpy(pSendBuffer,pSendBuffer+nSentPosition,left);
	nSentPosition = 0;
	nSendPosition = nSendPosition - left;
}

/////////////////////////////////////////////////////////////////////////
//
//                       Receive
//
// WSA_READ�� ���� ������, pRecvBuffer�� �װ�, nRecvPosition�� �����Ѵ�.
// pRecvBuffer��  size��ŭ�� ������ ������ Fail.(Ŀ�ؼ��� ���´�)
//
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::Receive()
{
	 int Rest = RECV_BUFFER_SIZE - nRecvPosition;
	 int tReceiveSize = recv(Sock, (char*)(pRecvBuffer+nRecvPosition), Rest, 0);

	 if  ( tReceiveSize == SOCKET_ERROR )
	 {
		#ifdef __SERVER_CONNECTION__
		char szBuf[256];
		memset( szBuf, 0, sizeof( szBuf ) );
		sprintf( szBuf, "Sock Receive fail:%X \r\n", WSAGetLastError());
		TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
		#endif
		return FALSE;
	 }


	 nRecvPosition = nRecvPosition + tReceiveSize;

	 if  ( tReceiveSize == Rest )	
	 {
		#ifdef __SERVER_CONNECTION__
		char szBuf[256];
		memset( szBuf, 0, sizeof( szBuf ) );
		HEADER * proc = (HEADER*)(pRecvBuffer+nProcPosition);
		sprintf( szBuf, "Socket buffer full %d-%d-%d-%d \r\n",nProcPosition,nRecvPosition,proc->wType,proc->wPDULength);
		TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
		#endif
		
		RefreshRecvBuffer();
		int Rest = RECV_BUFFER_SIZE - nRecvPosition;
		int tReceiveSize = recv(Sock, (char*)(pRecvBuffer+nRecvPosition), Rest, 0);
		nRecvPosition = nRecvPosition + tReceiveSize;
		if  ( tReceiveSize == Rest )	
		{
			#ifdef __SERVER_CONNECTION__
			char szBuf[256];szBuf[0]=0;
			HEADER * proc = (HEADER*)(pRecvBuffer+nProcPosition);
			sprintf( szBuf, "Socket refresh fail %d-%d-%d-%d \r\n",nProcPosition,nRecvPosition,proc->wType,proc->wPDULength);
			TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
			#endif
		}

		
		// dump and write dump file
	 }
     return TRUE;				  
} 

/////////////////////////////////////////////////////////////////////////
//
//                       ReadMessage
//
// pRecvBuffer���� 1�� �з��� �޽����� �о� ����.
// ���� �з��� ���ؼ���, Ű���忡 ���� ���ڵ��ϰ�, üũ��� �����Ѵ�.
// üũ���� ��ġ�ϸ� nProcPosition�� �����Ѵ�.
// ó���� �޽����� ������ �����͸� �����Ѵ�.
// ó���� �޽����� ������  0�� �����Ѵ�. 
// �޽����� �ջ�Ǿ�����  ErrorCode 1�� �����Ѵ�.
// �ɰ��� ������ ������   ErrorCode 2�� �����Ѵ�. (3�� 3���� �̻� �ݺ��Ǹ� ������ ������ ���´�.)
// �޽��� �ջ�� �������� [����] ó���� �ϰ�, ������ �޽��� �ջ� ������
// ������ �ʵ��� �۾� �Ѵ�.
/////////////////////////////////////////////////////////////////////////
char * CPSock::ReadMessage(int * ErrorCode,int * ErrorType)
{
	*ErrorCode = 0;

	// Proc�� Recv�� �ʰ��� ���. (�ɰ��� ����, ��Ÿ���� ���� ����)
	if	(nProcPosition>=nRecvPosition)
	{	nRecvPosition=0;
		nProcPosition=0;
		return 0;
	}
	//  Init packet authentication
	if	(Init==0)
	{	if	(nRecvPosition-nProcPosition<4) return 0;
		int InitCode = * ((unsigned int *)(pRecvBuffer+nProcPosition));
		if	(InitCode!=INITCODE)
		{	*ErrorCode=2;
			*ErrorType=InitCode;
			return 0;
		}
		Init=1;
		nProcPosition+=4;
	}
    //	Ccheck received message is larger than HEADER
	if	(nRecvPosition-nProcPosition<sizeof(HEADER)) return 0;
	//	Check full message arrived
	int sh =sizeof(HEADER);
	unsigned short	Size		= * ((unsigned short *) (pRecvBuffer+nProcPosition+4)); Size=Size+sizeof(HEADER);
 	unsigned char	CheckSum	= * ((unsigned char  *) (pRecvBuffer+nProcPosition+3));
    unsigned int	SockType	= * ((unsigned short *) (pRecvBuffer+nProcPosition));
	unsigned int	ClentTick	= * ((unsigned int	 *) (pRecvBuffer+nProcPosition+6));
	if	(Size > MAX_MESSAGE_SIZE || Size < sizeof(HEADER)) 
	{	nRecvPosition=	0;
	    nProcPosition=	0;
		*ErrorCode   =	2;
		*ErrorType   =	Size;
		return 0;
	}

	unsigned short	Rest = nRecvPosition - nProcPosition;
	if (Size>Rest) return 0;
	
	//	Get message
	char *pMsg = &(pRecvBuffer[nProcPosition]);
	nProcPosition = nProcPosition + Size;
    if	(nRecvPosition<=nProcPosition) 
	{	nRecvPosition=0;
		nProcPosition=0;
	}

	// Compare check_sum in packet
	int KeywordFlag = oldRecvChecksum % 2;
	unsigned char Sum = 0;
	int	pos = ucRecvSeq;
	for	(int i=sizeof(HEADER); i<Size;i++,pos++)
	{	int rst = pos%256;
		unsigned char Trans = pKeyWord[rst][KeywordFlag];
		int mod = i&0x3;
		if  (mod==0) pMsg[i]=pMsg[i]-(Trans<<2); 
		if  (mod==1) pMsg[i]=pMsg[i]+(Trans>>1);
		if  (mod==2) pMsg[i]=pMsg[i]-(Trans<<1);
		if  (mod==3) pMsg[i]=pMsg[i]+(Trans>>2);
		Sum += pMsg[i];
	}

	ucRecvSeq++;
	oldRecvChecksum = CheckSum;

	// return packet, even check_sum not match
	if	(Sum!=CheckSum)
	{	*ErrorCode = 1;
		*ErrorType   = Size;
		return pMsg;
	} 
	return pMsg;
}

/////////////////////////////////////////////////////////////////////////
//
//                       AddMessage
//
// �޽����� SendBuffer�� �ϳ� ���ϰ� Encoding�ϰ� pRecvBuffer���� 1�� �з��� �޽����� �о� ����.
// ���� �з��� ���ؼ���, Ű���忡 ���� ���ڵ��ϰ�, üũ��� �����Ѵ�.
// üũ���� ��ġ�ϸ� nProcPosition�� �����Ѵ�.
// ó���� �޽����� ������ �����͸� �����Ѵ�.
// ó���� �޽����� ������  0�� �����Ѵ�. 
// �޽����� �ջ�Ǿ�����  ErrorCode 1�� �����Ѵ�.
// �ɰ��� ������ ������   ErrorCode 2�� �����Ѵ�. (3�� 3���� �̻� �ݺ��Ǹ� ������ ������ ���´�.)
// �޽��� �ջ�� �������� [����] ó���� �ϰ�, ������ �޽��� �ջ� ������
// ������ �ʵ��� �۾� �Ѵ�.
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::AddMessage(char *pMsg,int Size)
{
	if(pMsg == NULL) return FALSE;
	if(pSendBuffer == NULL) return FALSE;
	// Build header
	char			* pChar =	(char*) pMsg;
	HEADER			* pSMsg	=	(HEADER *) pMsg; 
	// check socket valid
	if	(Sock<=0)
	{	return FALSE;
	}
	// check send buffer full
	if	(nSendPosition+Size >=	SEND_BUFFER_SIZE )	
	{	
		#ifdef __SERVER_CONNECTION__
		char szBuf[256] ={0,};
		HEADER * proc = (HEADER*)(pRecvBuffer+nProcPosition);
		sprintf( szBuf, "Send Socket buffer full %d-%d-%d-%d \r\n",nSentPosition,nSendPosition,pSMsg->wType,pSMsg->wPDULength);
		TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
		#endif
		RefreshSendBuffer();
		if	(nSendPosition+Size >=	SEND_BUFFER_SIZE )
			return FALSE;
	}
	if	(Size<0 || Size>MAX_MESSAGE_SIZE)				
		return FALSE;

	unsigned char KeyWord	=	pKeyWord[ucSendSeq][0];
	unsigned char CheckSum	=	0;
	unsigned char *pSeq		=	(unsigned char*)&(pSMsg->wSeq);
	pSeq[0]					=	0;
	pSeq[1]					=	CheckSum;
	pSMsg->wPDULength		=	Size - sizeof(HEADER);
	pSMsg->dwClientTick		=	0;//CurrentTime;
	int				nTemp	=	0;

	int KeywordFlag = oldSendChecksum % 2;
 	int pos = ucSendSeq;
	for (int i=sizeof(HEADER); i<Size; i++,pos++)
	{	
		CheckSum += pMsg[i];
		int rst = pos%256;
		unsigned char Trans = pKeyWord[rst][KeywordFlag];
		int mod = i&0x3;
		if  (mod==0) pSendBuffer[nSendPosition+i]=pMsg[i]+(Trans<<2); 
		if  (mod==1) pSendBuffer[nSendPosition+i]=pMsg[i]-(Trans>>1);
		if  (mod==2) pSendBuffer[nSendPosition+i]=pMsg[i]+(Trans<<1);
		if  (mod==3) pSendBuffer[nSendPosition+i]=pMsg[i]-(Trans>>2);
	}
	
	pSeq[1]			= CheckSum;
	ucSendSeq++;
	oldSendChecksum = CheckSum;

	memcpy(pSendBuffer+nSendPosition,pSMsg,sizeof(HEADER));
	nSendPosition	=	nSendPosition  + Size;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//
//                       SendMessage
//
//
// AddMessage�� ���� SendBuffer�� �׿� �ִ� �޽����� ������.
// ��� �׿� �ִ� �ѹ��� ������. (�ʹ� ũ�� �˾Ƽ� �߸���.)
// ������ NULL�̰ų�, nSendPosition �� 0�̸� ������ �ȴ´�.
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::SendMessage(void)
{
	//char szBuf[256];
	if	(nSentPosition>0) RefreshSendBuffer();
	//if	(nSendPosition == SEND_BUFFER_SIZE) return FALSE; // ���۰� full���� ���� ������ �� ������
    if	(nSendPosition > SEND_BUFFER_SIZE || nSendPosition<0 || Sock<0)
    {	
		#ifdef  _PACKET_DEBUG
		sprintf(temp,"err send1 %d %d %d",nSendPosition,nSentPosition,Sock);
		Log(temp,"-system",0);
		#endif

		nSendPosition=0;
		nSentPosition=0;
		return FALSE;
	}

	if	(nSentPosition>nSendPosition||nSentPosition >=SEND_BUFFER_SIZE|| nSentPosition<0)
	{	
		#ifdef  _PACKET_DEBUG
		sprintf(temp,"err send2 %d %d %d",nSendPosition,nSentPosition,Sock);
		Log(temp,"-system",0);
		#endif

		nSendPosition=0;
		nSentPosition=0;
	}

	int err = 0;
	int	Left = nSendPosition - nSentPosition;
	int tSend = send(Sock,pSendBuffer+nSentPosition,Left, 0);
	if	(tSend!=SOCKET_ERROR)	nSentPosition = nSentPosition + tSend;	// ���۵ȹ���Ʈ
	else						err = WSAGetLastError();	

	if	(nSentPosition<nSendPosition||tSend==SOCKET_ERROR)
	{	
		#ifdef __SERVER_CONNECTION__
		char szBuf[128]={0,};sprintf( szBuf, "err send3 %d/%d/%d %d \r\n",tSend,nSentPosition,nSendPosition,err );
		TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
		#endif	//	#ifdef __SERVER_CONNECTION__
	}	else
	{	nSendPosition = 0;
		nSentPosition = 0;
		return TRUE;
	}

	#ifdef __SERVER_CONNECTION__
	char szBuf[128]={0,};sprintf( szBuf, "err send4 %d/%d \r\n",nSentPosition,nSendPosition );
	TimeWriteLog( szBuf, ".\\LOG\\[LOG]SERVER_CONNECTION.txt");
	#endif	//	#ifdef __SERVER_CONNECTION__

	return TRUE; 
}

/////////////////////////////////////////////////////////////////////////
//
//                       SendOneMessage
//
// AddMessage + SendMessage ��.
// SendMessage�� void �Ķ��Ÿ�� �ѱ�Ƿ� AddMessage�� �Ķ��Ÿ�� ����.
/////////////////////////////////////////////////////////////////////////
BOOL CPSock::SendOneMessage(char* Msg,int Size)
{	
	BOOL ret =AddMessage(Msg,Size);
	//if	(ret==FALSE) return ret;
	ret = SendMessage();

	return ret;
}

DWORD CPSock::GetLastError()
{
	return WSAGetLastError();
}
BOOL CPSock::SendBillMessage(char * Msg)
{ 
	 if (nSendPosition+g_cGame >= SEND_BUFFER_SIZE ) return FALSE;

	 for (int i=0;i<g_cGame;i++)
	 {	 pSendBuffer[nSendPosition+i] = Msg[i];
	 }
	 nSendPosition = nSendPosition  + g_cGame;
	 BOOL Err = SendMessage();
     return Err;
}
char * CPSock::ReadBillMessage(int * nType, int * ErrorCode,int * ErrorType)
{     
	 *ErrorCode = 0;   // ý���� ���� ������ Ȯ�ε��� �ʴ´�.
	 *ErrorType = 0; 

     // Proc�� Recv�� �ʰ��� ���. (�ɰ��� ����, ��Ÿ���� ���� ����)
	 if  (nProcPosition>=nRecvPosition)
	 {   nRecvPosition=0;
	     nProcPosition=0;
		 return 0;
	 }
	 
     // �޽����� ���� �־ 8����Ʈ �̸����� ������, ���� �����Ͱ� ����.
	 if (nRecvPosition-nProcPosition < g_cGame2 ) return 0;
	 // �޽��� ��ü�� �ִ��� �˻�
	 _AUTH_GAME2* m = (_AUTH_GAME2*) &(pRecvBuffer[nProcPosition]);
	 char *pMsg = &(pRecvBuffer[nProcPosition]);
	 if(m->Packet_Type>=_Msg_BillUserInit)
	 {	nProcPosition = nProcPosition + g_cGame2;
	 }
	 else
	 {	if (nRecvPosition-nProcPosition < g_cGame ) return 0;
		nProcPosition = nProcPosition + g_cGame;
	 }

     if (nRecvPosition<=nProcPosition) 
	 {  nRecvPosition=0;
	    nProcPosition=0;
	 }

	 return pMsg;
}

unsigned int CPSock::ConnectBillServer(char *HostAddr,int Port ,int ip,int WSA, HWND WindowHandle)
{
	char msg[256];	
	//MessageBox(hWndMain,"billing connect started.","billing connect step",MB_OK|MB_SYSTEMMODAL);
	
	SOCKADDR_IN remote_sin;
	SOCKET      tSock;
	SOCKADDR_IN local_sin;

	nRecvPosition = 0;
	nSendPosition = 0;
	nProcPosition = 0;
    if (Sock!=0) CloseSocket();
	
	tSock = socket( AF_INET, SOCK_STREAM, 0);
	if ( tSock == INVALID_SOCKET) return FALSE;
	//MessageBox(hWndMain,"create connect socket success.","billing connect step",MB_OK|MB_SYSTEMMODAL);

	local_sin.sin_family		= AF_INET;
	local_sin.sin_addr.s_addr	= ip; //INADDR_ANY;
	local_sin.sin_port			= 0;	//htons((unsigned short int)(ConnectPort+6000));       
	if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
	{	local_sin.sin_port = htons((unsigned short int)(ConnectPort+6000));
		if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
		{	ConnectPort=ConnectPort+10;
			local_sin.sin_port = htons((unsigned short int)(ConnectPort+6000));
			if	(bind(tSock,(struct sockaddr FAR *)&local_sin,sizeof(local_sin))==SOCKET_ERROR)
			{	MessageBox (NULL,"Binding fail","ERROR",MB_OK);	
				closesocket(tSock);
				return FALSE;
			}
		}
	}
//	sprintf(msg,"sock:%d ip:%d.%d.%d.%d port:%d-%d",tSock,local_sin.sin_addr.S_un.S_un_b.s_b1,local_sin.sin_addr.S_un.S_un_b.s_b2,local_sin.sin_addr.S_un.S_un_b.s_b3,local_sin.sin_addr.S_un.S_un_b.s_b4,local_sin.sin_port,ConnectPort); 
	//MessageBox(hWndMain,msg,"binding local ip",MB_OK|MB_SYSTEMMODAL);
	ConnectPort++;


	memset(&remote_sin,0,sizeof(remote_sin));
	remote_sin.sin_addr.s_addr = inet_addr(HostAddr);
	remote_sin.sin_family = AF_INET;
	remote_sin.sin_port = htons((unsigned short)Port);       
	if	( connect(tSock,(PSOCKADDR)&remote_sin,sizeof(remote_sin)) < 0)       
	{	sprintf(msg,"sock:%d ip:%d.%d.%d.%d port:%d-%d",tSock, remote_sin.sin_addr.S_un.S_un_b.s_b1,   remote_sin.sin_addr.S_un.S_un_b.s_b2,remote_sin.sin_addr.S_un.S_un_b.s_b3,remote_sin.sin_addr.S_un.S_un_b.s_b4,remote_sin.sin_port,Port); 
		//MessageBox(hWndMain,msg,"connect fail",MB_OK|MB_SYSTEMMODAL);
		int nErr = WSAGetLastError();
		closesocket(tSock);Sock=0;
		return FALSE;
	}
	sprintf(msg,"sock:%d ip:%d.%d.%d.%d port:%d-%d",tSock,remote_sin.sin_addr.S_un.S_un_b.s_b1,remote_sin.sin_addr.S_un.S_un_b.s_b2,remote_sin.sin_addr.S_un.S_un_b.s_b3,remote_sin.sin_addr.S_un.S_un_b.s_b4,remote_sin.sin_port,Port);
	//MessageBox(hWndMain,msg,"connect success",MB_OK|MB_SYSTEMMODAL);
    if	(WSAAsyncSelect(tSock,WindowHandle,WSA,FD_READ|FD_CLOSE)>0) 
	{	closesocket(tSock);Sock=0;
		return FALSE;
	}
	//IP=InAddr.sin_addr.S_un.S_addr;
	Sock=tSock;
	return tSock;
}

BOOL	CPSock::SendCashMessage(char * pMsg, int Size)
{
	if(pMsg == NULL) return FALSE;
	if(pSendBuffer == NULL) return FALSE;
	// Build header
	char			* pChar =	(char*) pMsg;
	HEADER			* pSMsg	=	(HEADER *) pMsg; 
	// check socket valid
	if	(Sock<=0)
	{	return FALSE;
	}
	// check send buffer full
	if	(nSendPosition+Size >=	SEND_BUFFER_SIZE )	
	{	
		RefreshSendBuffer();
		if	(nSendPosition+Size >=	SEND_BUFFER_SIZE )
			return FALSE;
	}
	if	(Size<0 || Size>MAX_MESSAGE_SIZE)				
		return FALSE;

	unsigned char iKeyWord	=	rand()%256; 
	unsigned char KeyWord	=	pKeyWord[iKeyWord][0];
	unsigned char CheckSum	=	0;
	unsigned char *pSeq		=	(unsigned char*)&(pSMsg->wSeq);
	pSeq[0]					=	iKeyWord;
	pSeq[1]					=	CheckSum;
	pSMsg->wPDULength		=	Size - sizeof(HEADER);
	pSMsg->dwClientTick		=	0;
	int	nTemp				=	0;

	pSeq[1]			=	CheckSum;
	memcpy(pSendBuffer+nSendPosition,pSMsg,Size);
	nSendPosition	=	nSendPosition  + Size;

	return SendMessage();
}

char *	CPSock::ReadCashMessage(int * ErrorCode,int * ErrorType)
{
	*ErrorCode = 0;

	// Proc�� Recv�� �ʰ��� ���. (�ɰ��� ����, ��Ÿ���� ���� ����)
	if	(nProcPosition>=nRecvPosition)
	{	nRecvPosition=0;
		nProcPosition=0;
		return 0;
	}
	//  Init packet authentication
	if	(Init==0)
	{	if	(nRecvPosition-nProcPosition<4) return 0;
		int InitCode = * ((unsigned int *)(pRecvBuffer+nProcPosition));
		if	(InitCode!=INITCODE)
		{	*ErrorCode=2;
			*ErrorType=InitCode;
			return 0;
		}
		Init=1;
		nProcPosition+=4;
	}
	//	Ccheck received message is larger than HEADER
	if	(nRecvPosition-nProcPosition<sizeof(HEADER)) return 0;
	//	Check full message arrived
	int sh =sizeof(HEADER);
	unsigned short	Size		= * ((unsigned short *) (pRecvBuffer+nProcPosition+4)); Size=Size+sizeof(HEADER);
	unsigned char	iKeyWord	= * ((unsigned char  *) (pRecvBuffer+nProcPosition+2));
	unsigned char	KeyWord		=	pKeyWord[iKeyWord][0];
	unsigned char	CheckSum	= * ((unsigned char  *) (pRecvBuffer+nProcPosition+3));
	unsigned int	SockType	= * ((unsigned short *) (pRecvBuffer+nProcPosition));
	unsigned int	ClentTick	= * ((unsigned int	 *) (pRecvBuffer+nProcPosition+6));
	if	(Size > MAX_MESSAGE_SIZE || Size < sizeof(HEADER)) 
	{	nRecvPosition=	0;
		nProcPosition=	0;
		*ErrorCode   =	2;
		*ErrorType   =	Size;
		return 0;
	}
	unsigned short	Rest = nRecvPosition - nProcPosition;
	if (Size>Rest) return 0;

	//	Get message
	char *pMsg = &(pRecvBuffer[nProcPosition]);
	nProcPosition = nProcPosition + Size;
	if	(nRecvPosition<=nProcPosition) 
	{	nRecvPosition=0;
		nProcPosition=0;
	}

	return pMsg;
}