// ExceptionHandler.cpp: implementation of the CExceptionHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExceptionHandler.h"

#include "pch.h"
#include "BugslayerUtil.h"
#include "CrashHandler.h"
#include "..\HTextern.h"

#pragma comment(lib, "UnhandledException/BugslayerUtil.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#else

#endif

LONG __stdcall CrashHandlerExceptionFilter( EXCEPTION_POINTERS* pExPtrs);

IExceptionHandler* CExceptionHandler::m_pOuter = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExceptionHandler::CExceptionHandler()
{
	SetUnhandledExceptionFilter(CrashHandlerExceptionFilter);

}

CExceptionHandler::~CExceptionHandler()
{

}


//*****************************************************************************
// CrashHandlerExceptionFilter()
// Purpose : [ ���α׷��� �浹���� ��, ������ �����ϱ� ���ؼ� ȣ��˴ϴ�. ]
// Parameters :	
// [pExPtrs] :
// Returns :	LONG __stdcall
// Last Update : 2001-06-13
//*****************************************************************************
LONG __stdcall CrashHandlerExceptionFilter( EXCEPTION_POINTERS* pExPtrs)
{
	LONG lRet;

// ����� ��� �϶����� �߰� ������ �������� �ʰ�
// EXCEPTION_CONTINUE_SEARCH  ���� ���������ν�
// ���α׷��Ӱ� ����� �� �� �ֵ��� �մϴ�.
#ifdef _DEBUG
	lRet = EXCEPTION_CONTINUE_SEARCH ;
	return lRet;
#else
	lRet = EXCEPTION_EXECUTE_HANDLER;
#endif

	char strText[4096], strStack[4096], strTmp[2048];
	memset( strText, 0, 4096 );
	memset( strStack, 0, 512 );
	memset( strTmp, 0, 2048 );

	// �� �׾����� �˾Ƴ����� �մϴ�.
	strncpy( strText, GetFaultReason(pExPtrs), 511 );
	strncpy( strStack, strstr( strText, "at" )+3, 512 );
	strncat( strText, "\n", 1 );
	strncpy( strTmp, GetRegisterString(pExPtrs), 512 );
	strncat( strText, strTmp, 511 );
	strncat( strText, "\n", 1 );
	strncpy( strTmp, GetFirstStackTraceString(GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs), 1024 );
	strncat( strText, strTmp, 512 );
	//HT_g_vLogFile( strText );

	// mss32.dll���� �״°��� �����Ѵ�.
	if ( strstr( strText, "mss32.dll" ) || strstr( strText, "AIL_sprintf" ) )
	{
		return lRet;
	}

	LPCTSTR pStrNext = HT_NULL;
	while ( pStrNext = GetNextStackTraceString(GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs) )
	{
		if ( strlen( strText ) + strlen( pStrNext ) >= 4096 )
			break;

		strncat( strText, "\n", 1 );
		strncat( strText, pStrNext, 511 );
		HT_g_vLogFile( strText );
	}

#ifndef _DEBUG
	if ( g_iInationalType == INATIONALTYPE_KOREA )
	{
		CHTString strUserInfo;
		strUserInfo = _T("\nAccount[") + g_strLoginID + _T("]\tCharacterName[") + g_oMainCharacterInfo.szCharName + _T("]");
		if ( strlen( strText ) + strUserInfo.HT_nGetSize() < 4096 )
			strncat( strText, (HTtchar*)strUserInfo, strUserInfo.HT_nGetSize() + 1 );
	}	
#endif
	
	CExceptionHandler::m_pOuter->ExceptionInformation(strText, strStack);

	return lRet;
}

