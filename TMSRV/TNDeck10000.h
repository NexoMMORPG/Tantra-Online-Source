/****************************************************************************************

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2003-09-09

	������ :
	������ :

	������Ʈ�� : 

	���� : TNDeck class�� size 10000���θ� �����ؼ� static���� �������� ��.

****************************************************************************************/
#ifndef __TNDeck10000_h__
#define __TNDeck10000_h__

#include <windows.h>

class TNDeck10000
{
public :
	TNDeck10000() ;
	~TNDeck10000() ;
	
	void Init() ;
	enum { eDeck_MaxSize = 10000, };
//Public Operations
public :
	byte Random() ;
	void Shuffle() ;
	void AddCard( byte a_byNum, int a_iCount ) ;
	void ClearCards() ;
	

private :
	int m_iIndex ;
	//int m_iSize ;

	byte m_byrgCard[10000] ;
};




#endif