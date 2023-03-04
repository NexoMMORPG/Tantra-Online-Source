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
// Purpose : [ 프로그램이 충돌했을 때, 정보를 수집하기 위해서 호출됩니다. ]
// Parameters :	
// [pExPtrs] :
// Returns :	LONG __stdcall
// Last Update : 2001-06-13
//*****************************************************************************
LONG __stdcall CrashHandlerExceptionFilter( EXCEPTION_POINTERS* pExPtrs)
{
	LONG lRet;

// 디버깅 모드 일때에는 추가 정보를 보여주지 않고
// EXCEPTION_CONTINUE_SEARCH  값을 리턴함으로써
// 프로그래머가 디버깅 할 수 있도록 합니다.
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

	// 왜 죽었는지 알아내도록 합니다.
	strncpy( strText, GetFaultReason(pExPtrs), 511 );
	strncpy( strStack, strstr( strText, "at" )+3, 512 );
	strncat( strText, "\n", 1 );
	strncpy( strTmp, GetRegisterString(pExPtrs), 512 );
	strncat( strText, strTmp, 511 );
	strncat( strText, "\n", 1 );
	strncpy( strTmp, GetFirstStackTraceString(GSTSO_PARAMS|GSTSO_MODULE|GSTSO_SYMBOL|GSTSO_SRCLINE, pExPtrs), 1024 );
	strncat( strText, strTmp, 512 );
	//HT_g_vLogFile( strText );

	// mss32.dll에서 죽는것은 무시한다.
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

