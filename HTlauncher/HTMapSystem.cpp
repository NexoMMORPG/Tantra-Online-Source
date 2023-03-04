#include "stdafx.h"
#include "HTMapSystem.h"
#include "HTEngineHandler.h"
#include "HTExtern.h"

//#define HT_MAPSYSTEM_SAVETML

CHTMapSystem::CHTMapSystem()
{
	m_p3DMgr = HT_NULL;
	m_dwCellCount = 0;
	m_strMapName = _T("");
	m_wMapIndex = 0;
	m_bPKInfo = HT_FALSE;
	m_wMapSizeX = 0;
	m_wMapSizeZ = 0;
	m_ppCell = HT_NULL;

	m_ppMap = HT_NULL;

	m_nVisibleObjs = 0;

	m_fHeuristic = 2.0f;
	m_fCostToMoveOneCell = 1.0f;

	m_fLODDistanceLow1		= 0.0f;
	m_fLODDistanceLow2		= 0.0f;
	m_fLODDistanceLow3		= 0.0f;
	m_fLODDistanceHigh1		= 0.0f;
	m_fLODDistanceHigh2		= 0.0f;
	m_fLODDistanceHigh3		= 0.0f;
	m_fLODDistanceFar		= 0.0f;
	m_fLODDistanceFarSM		= 0.0f;

	m_dwBGMID = 0;
	m_vectorSoundSpaces.clear();
	m_setBeforeAmbientSoundIDs.clear();
	m_setAfterAmbientSoundIDs.clear();
	m_mapAmbientSampleHandles.clear();
	m_setCurrentAmbientSoundIDs.clear();
	m_iRoomType = 0;

	// 지역 표시
	m_iAreaID	= 0;
	m_vectorAreaIndicate.clear();

	m_ppDLMap = HT_NULL;
	m_mapSaveObjs.clear();
	m_setLoadedObjIDs.clear();
	m_setCreatedObjIDs.clear();

	m_ppHPVS = HT_NULL;
	m_bHPVSMode = HT_FALSE;
	m_fHPVSGridSize = 0.0f;
	m_iHPVSNodeCountX = 0;
	m_iHPVSNodeCountZ = 0;

	m_mapBoundDataPlane.clear();
	m_mapBoundDataBox.clear();
	m_mapBoundDataCylinder.clear();
	m_mapBoundObjs.clear();
	m_arrShootPoint.clear();

	m_ppbyFootSound = HT_NULL;
	m_wGridSizeX	= 0;
	m_wGridSizeZ	= 0;
}

CHTMapSystem::~CHTMapSystem()
{
	HT_vFreeAllNodes();

	std::vector<HTSoundSpaceNode*>::iterator it = m_vectorSoundSpaces.begin();
	while ( it != m_vectorSoundSpaces.end() )
	{
		HT_DELETE( *it );
		it++;
	}

	// Area Indicate
	std::vector<HTAreaIndicate*>::iterator itArea = m_vectorAreaIndicate.begin();
	while ( itArea != m_vectorAreaIndicate.end() )
	{
		HT_DELETE( *itArea );
		itArea++;
	}

	for ( HTint i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		HT_DELETEARRAY( m_ppDLMap[i] );
	}
	HT_DELETEARRAY( m_ppDLMap );

	std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itSaveObj = m_mapSaveObjs.begin();
	while ( itSaveObj != m_mapSaveObjs.end() )
	{
		HT_MAP_SAVEOBJ* pObj = itSaveObj->second;
		HT_DELETE( pObj );
		itSaveObj = m_mapSaveObjs.erase( itSaveObj );
	}

	for ( i = 0; i < m_iHPVSNodeCountZ; i++ )
	{
		HT_DELETEARRAY( m_ppHPVS[i] );
	}
	HT_DELETEARRAY( m_ppHPVS );
}

HTRESULT CHTMapSystem::HT_hrCreate( HTint iWidthX, HTint iWidthZ, IHT3DMgr* p3DMgr )
{
	HTuint i;

	HT_ASSERT( p3DMgr != HT_NULL );

	m_p3DMgr = p3DMgr;

	m_ppMap = new HTGrassMapNode*[HT_MAPNODE_NUM];
	HT_ASSERT( m_ppMap != HT_NULL );

	for ( i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		m_ppMap[i] = new HTGrassMapNode[HT_MAPNODE_NUM];
		HT_ASSERT( m_ppMap[i] != HT_NULL );

		for ( HTint j = 0; j < HT_MAPNODE_NUM; j++ )
		{
			m_ppMap[i][j].m_setObjects.clear();
			m_ppMap[i][j].m_setSMObjects.clear();
			m_ppMap[i][j].m_vectorBoundObjs.clear();
			m_ppMap[i][j].m_boxArea.vecMin = HTvector3( j * HT_MAPNODE_SIZE, HT_MIN_MAPHEIGHT, i * HT_MAPNODE_SIZE );
			m_ppMap[i][j].m_boxArea.vecMax = HTvector3( (j+1) * HT_MAPNODE_SIZE, HT_MAX_MAPHEIGHT, (i+1) * HT_MAPNODE_SIZE );
		}
	}

	m_nVisibleObjs = 0;
	m_listVisibleObjs.clear();

	// 풀처리를 위한 2차원 배열의 맵을 생성한다.
	m_ppGrassMap = new HTGrassMapNode*[HT_GRASSMAPNODE_NUM];
	HT_ASSERT( m_ppGrassMap != HT_NULL );

	for ( i = 0; i < HT_GRASSMAPNODE_NUM; i++ )
	{
		m_ppGrassMap[i] = new HTGrassMapNode[HT_GRASSMAPNODE_NUM];
		HT_ASSERT( m_ppGrassMap[i] != HT_NULL );

		for ( HTint j = 0; j < HT_GRASSMAPNODE_NUM; j++ )
		{
			m_ppGrassMap[i][j].m_setObjects.clear();
			m_ppGrassMap[i][j].m_boxArea.vecMin = HTvector3( i * HT_GRASSMAPNODE_SIZE, HT_MIN_MAPHEIGHT, j * HT_GRASSMAPNODE_SIZE );
			m_ppGrassMap[i][j].m_boxArea.vecMax = HTvector3( (i+1) * HT_GRASSMAPNODE_SIZE, HT_MAX_MAPHEIGHT, (j+1) * HT_GRASSMAPNODE_SIZE );
		}
	}

	return ( HT_OK );
}

// Load Map Data
HTRESULT CHTMapSystem::HT_hrLoad( CHTString& strFile )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	oFile.HT_bRead( &m_oHeader, sizeof(HT_HEADER) );

	CHTString strBuf;
	oFile.HT_bReadString( strBuf, 26, '\n' );
	m_strMapName = strBuf;

	oFile.HT_bRead( &m_wMapIndex, 2 );
	oFile.HT_bRead( &m_bPKInfo, 1 );
	oFile.HT_bRead( &m_wMapSizeX, 2 );
	oFile.HT_bRead( &m_wMapSizeZ, 2 );

	oFile.HT_bRead( &m_dwCellCount, 4 );

	HT_CELL_INFO* pCell = new HT_CELL_INFO[m_dwCellCount];

	m_ppCell = new HT_CELL_NODE*[m_wMapSizeZ];

	for ( HTdword i = 0; i < m_wMapSizeZ; i++ )
	{
		m_ppCell[i] = (HT_CELL_NODE*)malloc(sizeof(HT_CELL_NODE)*m_wMapSizeX);
		memset( m_ppCell[i], 0, sizeof(HT_CELL_NODE) * m_wMapSizeX );
	}

	oFile.HT_bRead( pCell, sizeof(HT_CELL_INFO)*m_dwCellCount );

	for ( i = 0; i < m_wMapSizeZ; i++ )
	{
		for ( HTint j = 0; j < m_wMapSizeX; j++ )
		{
			m_ppCell[j][i].wObjHeight = pCell[i*m_wMapSizeX+j].wObjHeight;
			m_ppCell[j][i].wState = pCell[i*m_wMapSizeX+j].wState;

			// 특정셀에는 보안코드를 삽입한다.
			//if (j == 0 && i == 97)
			//	pCell[i*m_wMapSizeX+j].wState = g_wResentZoneServerID+1000;


			if( g_wResentZoneServerID == ZONE_CHATURANGGA )
			{
				if(m_ppCell[j][i].wState & HT_CELL_SAFE_ZONE)
					m_ppCell[j][i].wState = m_ppCell[j][i].wState ^ HT_CELL_SAFE_ZONE;
			}
		}
	}

	HT_CELL_NODE* pNode;
	HTdword idx = 0;
	for ( i = 0; i < m_dwCellCount-m_wMapSizeX*m_wMapSizeZ; i++ )
	{
		idx = m_wMapSizeX*m_wMapSizeZ+i;

		HT_CELL_NODE* pNewNode = new HT_CELL_NODE;
		memset( pNewNode, 0, sizeof(HT_CELL_NODE) );

		pNode = &m_ppCell[pCell[idx].wX][pCell[idx].wZ];
		pNode->pNextNode = pNewNode;

		pNewNode->wObjHeight = pCell[idx].wObjHeight;
		pNewNode->wState = pCell[idx].wState;
	}
/*
	// 임시 저장파일 (보안 TCC 파일을 만들기 위해 사용합니다.)
	// --------------------------------------------------------------------------------------
	CHTFile oFile2;
	CHTString str2;
	str2.HT_szFormat("%s.tcc2", strFile.HT_szGetString());

	if ( oFile2.HT_bOpen( str2, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	oFile2.HT_bWrite( &m_oHeader, sizeof(HT_HEADER) );
	oFile2.HT_bWrite( strBuf, 26 );
	oFile2.HT_bWrite( &m_wMapIndex, 2 );
	oFile2.HT_bWrite( &m_bPKInfo, 1 );
	oFile2.HT_bWrite( &m_wMapSizeX, 2 );
	oFile2.HT_bWrite( &m_wMapSizeZ, 2 );
	oFile2.HT_bWrite( &m_dwCellCount, 4 );
	oFile2.HT_bWrite( pCell, sizeof(HT_CELL_INFO)*m_dwCellCount );
	oFile2.HT_vClose();
	// ---------------------------------------------------------------------------------------
*/
	HT_DELETEARRAY( pCell );

	oFile.HT_vClose();
/*
	// 노무브 검사
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		if (m_ppCell[0][97].wState != g_wResentZoneServerID + 1000) 
		{
			// 단 18, 19번 만다라의 경우는 만다라 1로 인식하여 처리.
			// 14, 15번 칼리아의 경우도 칼리아 1로 인식하여 처리.
			if (g_wResentZoneServerID == 18 && m_ppCell[0][97].wState == 1001 || 
				g_wResentZoneServerID == 19 && m_ppCell[0][97].wState == 1001 || 
				g_wResentZoneServerID == 14 && m_ppCell[0][97].wState == 1013 || 
				g_wResentZoneServerID == 15 && m_ppCell[0][97].wState == 1013)
				return HT_OK;

			// 그렇지 않은 경우는 노무브 파일이 비정상적이므로 강제 종료 (리소스 셈... ㅋ)
			// 죄송합니다. 서버와 연결이 끊어졌습니다. 다시 연결해주십시오.
			exit(1);
		}
	}
*/
	return ( HT_OK );
}

HTRESULT CHTMapSystem::HT_hrDestroy()
{
	HTdword i;

	m_listVisibleObjs.clear();

	std::map<HTint, HT_MAP_REMEMBEROBJ*>::iterator it;
	it = m_hashmapObjects.begin();
	while ( it != m_hashmapObjects.end() )
	{
		HT_DELETE( it->second );
		it = m_hashmapObjects.erase( it );
	}

	for ( i = 0; i < HT_GRASSMAPNODE_NUM; i++ )
	{
		HT_DELETEARRAY( m_ppGrassMap[i] );
	}
	HT_DELETEARRAY( m_ppGrassMap );

	for ( i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		HT_DELETEARRAY( m_ppMap[i] );
	}
	HT_DELETEARRAY( m_ppMap );

	HT_CELL_NODE *pNode, *pNextNode;
	for ( i = 0; i < m_wMapSizeX; i++ )
	{
		for ( HTdword j = 0; j < m_wMapSizeZ; j++ )
		{
			pNode = m_ppCell[i][j].pNextNode;
			while( pNode )
			{
				pNextNode = pNode->pNextNode;
				HT_DELETE( pNode );
				pNode = pNextNode;
			}
		}
		free( m_ppCell[i] );
	}
	HT_DELETEARRAY( m_ppCell );

	// 현재 틀고 있는 공간음을 모두 스톱시킨다.
	std::set<HTdword>::iterator itSound = m_setCurrentAmbientSoundIDs.begin();
	while ( itSound != m_setCurrentAmbientSoundIDs.end() )
	{
		std::map<HTdword,HSAMPLE>::iterator itSample = m_mapAmbientSampleHandles.find( *itSound );
		if ( itSample != m_mapAmbientSampleHandles.end() )
		{
			m_p3DMgr->HT_hrStopSound( itSample->second );
			m_mapAmbientSampleHandles.erase( itSample );
		}

		itSound++;
	}
	m_setCurrentAmbientSoundIDs.clear();

	std::map<HTint,HTBoundPlane*>::iterator itPlane = m_mapBoundDataPlane.begin();
	while ( itPlane != m_mapBoundDataPlane.end() )
	{
		HT_DELETE( itPlane->second );
		itPlane++;
	}

	std::map<HTint,HTBoundBox*>::iterator itBox = m_mapBoundDataBox.begin();
	while ( itBox != m_mapBoundDataBox.end() )
	{
		HT_DELETE( itBox->second );
		itBox++;
	}

	std::map<HTint,HTBoundCylinder*>::iterator itCylinder = m_mapBoundDataCylinder.begin();
	while ( itCylinder != m_mapBoundDataCylinder.end() )
	{
		HT_DELETE( itCylinder->second );
		itCylinder++;
	}

	std::map<HTint,HTBoundObj*>::iterator itObj = m_mapBoundObjs.begin();
	while ( itObj != m_mapBoundObjs.end() )
	{
		HT_DELETE( itObj->second );
		itObj++;
	}

	return ( HT_OK );
}
 
HTRESULT				
CHTMapSystem::HT_hrInsertObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HT_OBJSIZETYPE eType, HTbyte byFloor, HTdword dwResID, HT_EOBJ_PROPERTY* pProperty )
{
	if ( !pBB || !pmatTrasform )
	{
		return ( HT_FAIL );
	}

	// If already inserted
	//std::map<HTint, HT_MAP_REMEMBEROBJ*>::iterator itHash = m_hashmapObjects.find( idObj );
	//if ( itHash != m_hashmapObjects.end() )
	//{
	//	return ( HT_OK );	
	//}

	// AABB의 8점
	HTvector3 arrvecBox[8] = 
	{
		HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMin.z),
		HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMin.z),
		HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMin.z),	
		HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMin.z),	
		HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMax.z),	
		HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMax.z),	
		HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMax.z),
		HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMax.z),
	};

	// AABB->OBB의 8점을 계산한다.
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[0], &arrvecBox[0], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[1], &arrvecBox[1], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[2], &arrvecBox[2], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[3], &arrvecBox[3], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[4], &arrvecBox[4], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[5], &arrvecBox[5], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[6], &arrvecBox[6], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[7], &arrvecBox[7], pmatTrasform );

	// OBB의 8점을 2차원 평면에 투영 => y 값 무시
	// 투영된 8점을 가지고 2차원 AABB 계산
	HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
	fMinX = arrvecBox[0].x;	fMinZ = arrvecBox[0].z;
	fMaxX = arrvecBox[0].x;	fMaxZ = arrvecBox[0].z;

	HTint i, j;
	for ( i = 1; i < 8; i++ )
	{
		if ( arrvecBox[i].x < fMinX )	fMinX = arrvecBox[i].x;
		if ( arrvecBox[i].z < fMinZ )	fMinZ = arrvecBox[i].z;
		if ( arrvecBox[i].x > fMaxX )	fMaxX = arrvecBox[i].x;
		if ( arrvecBox[i].z > fMaxZ )	fMaxZ = arrvecBox[i].z;
	}
	
	HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
	HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
	HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
	HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

	std::map<HTint, HT_MAP_REMEMBEROBJ*>::iterator it = m_hashmapObjects.find( idObj );
	if ( it != m_hashmapObjects.end() )
	{
		this->HT_hrDeleteObject( idObj, eType, byFloor );
	}

	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;

#ifdef HT_MAPSYSTEM_SAVETML
	HT_MAP_SAVEOBJ* pSaveObj = new HT_MAP_SAVEOBJ;
	pSaveObj->bGrass = HT_FALSE;
	pSaveObj->dwResID = dwResID;
	pSaveObj->matTransform = *pmatTrasform;
	if ( pProperty )	memcpy( &pSaveObj->oProperty, pProperty, sizeof(HT_EOBJ_PROPERTY) );
#endif

	// 오브젝트의 2차원 AABB의 영역에 있는 맵 노드들과의 체크를 한다.
	for ( i = iMinZ; i <= iMaxZ; i++ )
	{
		for ( j = iMinX; j <= iMaxX; j++ )
		{
			if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
				continue;

			// 여기서는 AABB 영역의 맵 노드에 오브젝트를 다 박는 것이다.
			// 이렇게 하면 걸치지 않은 영역에도 박는 것이므로 효율의 저하가 있으나,
			// 이러한 경우가 많지 않을 거라 가정한다.
			m_ppMap[i][j].m_setObjects.insert( idObj );

			pRememberNode->vectorMapNodes.push_back( &m_ppMap[i][j] );

#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( i, j ) );
#endif
		}
	}

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

#ifdef HT_MAPSYSTEM_SAVETML
	m_mapSaveObjs.insert( std::map<HTint,HT_MAP_SAVEOBJ*>::value_type( idObj, pSaveObj ) );
#endif

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrInsertSMObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HTdword dwResID, HT_EOBJ_PROPERTY* pProperty )
{
	if ( !pBB || !pmatTrasform )
		return ( HT_FAIL );

	// AABB의 8점
	HTvector3 arrvecBox[8] = 
	{
		HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMin.z),
			HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMin.z),
			HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMin.z),	
			HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMin.z),	
			HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMax.z),	
			HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMax.z),	
			HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMax.z),
			HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMax.z),
	};

	// AABB->OBB의 8점을 계산한다.
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[0], &arrvecBox[0], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[1], &arrvecBox[1], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[2], &arrvecBox[2], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[3], &arrvecBox[3], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[4], &arrvecBox[4], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[5], &arrvecBox[5], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[6], &arrvecBox[6], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[7], &arrvecBox[7], pmatTrasform );

	// OBB의 8점을 2차원 평면에 투영 => y 값 무시
	// 투영된 8점을 가지고 2차원 AABB 계산
	HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
	fMinX = arrvecBox[0].x;	fMinZ = arrvecBox[0].z;
	fMaxX = arrvecBox[0].x;	fMaxZ = arrvecBox[0].z;

	HTint i, j;
	for ( i = 1; i < 8; i++ )
	{
		if ( arrvecBox[i].x < fMinX )	fMinX = arrvecBox[i].x;
		if ( arrvecBox[i].z < fMinZ )	fMinZ = arrvecBox[i].z;
		if ( arrvecBox[i].x > fMaxX )	fMaxX = arrvecBox[i].x;
		if ( arrvecBox[i].z > fMaxZ )	fMaxZ = arrvecBox[i].z;
	}

	HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
	HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
	HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
	HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;

#ifdef HT_MAPSYSTEM_SAVETML
	HT_MAP_SAVEOBJ* pSaveObj = new HT_MAP_SAVEOBJ;
	pSaveObj->bGrass = HT_FALSE;
	pSaveObj->dwResID = dwResID;
	pSaveObj->matTransform = *pmatTrasform;
	if ( pProperty )	memcpy( &pSaveObj->oProperty, pProperty, sizeof(HT_EOBJ_PROPERTY) );
#endif

	// 오브젝트의 2차원 AABB의 영역에 있는 맵 노드들과의 체크를 한다.
	for ( i = iMinZ; i <= iMaxZ; i++ )
	{
		for ( j = iMinX; j <= iMaxX; j++ )
		{
			if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
				continue;

			m_ppMap[i][j].m_setSMObjects.insert( idObj );

			pRememberNode->vectorMapNodes.push_back( &m_ppMap[i][j] );

#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( i, j ) );
#endif
		}
	}

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

#ifdef HT_MAPSYSTEM_SAVETML
	m_mapSaveObjs.insert( std::map<HTint,HT_MAP_SAVEOBJ*>::value_type( idObj, pSaveObj ) );
#endif

	return ( HT_OK );
}

HTfloat CHTMapSystem::HT_fPlanePointDistance( HTplane* pPlane, HTvector3* pVector )
{
	HTfloat fDenominator = sqrtf( (pPlane->a * pPlane->a) + (pPlane->b * pPlane->b) + (pPlane->c * pPlane->c) );
	return ( HT_ABS( CHTPlane::HT_fplaneDotCoord( pPlane, pVector ) ) / fDenominator );
}

HTRESULT CHTMapSystem::HT_hrSetCellMoveDisable( HT_CELL_COORD& rCell, HT_OBJSIZETYPE eType, HTbyte byFloor )
{
	// TODO : 맵 가장자리 부근의 처리인데 이걸로는 Large는 체크못한다.
	if ( rCell.x < 1 || rCell.y < 1 || rCell.x >= m_wMapSizeX || rCell.y >= m_wMapSizeZ )
	{
		return ( HT_FAIL );
	}

	switch( eType )
	{
	case HT_OBJSIZE_SMALL:
		if ( //m_ppCell[idxDstX][idxDstZ].byFloor == byFloor &&
			!( m_ppCell[rCell.x][rCell.y].wState & HT_CELL_MOVE_DISABLE ) )
		{
			m_ppCell[rCell.x][rCell.y].wState += HT_CELL_MOVE_DISABLE;
		}
		//else
		//{
		//	HT_CELL_NODE* pNode = m_ppCell[idxDstX][idxDstZ].pNextNode;
		//	while ( pNode )
		//	{
		//		if ( pNode->byFloor == byFloor && !(pNode->wState & HT_CELL_MOVE_DISABLE) )
		//			pNode->wState += HT_CELL_MOVE_DISABLE;

		//		pNode = pNode->pNextNode;
		//	}
		//}
		return ( HT_OK );
		// TODO : 
	case HT_OBJSIZE_MEDIUM:
		break;
	case HT_OBJSIZE_LARGE:
		break;
	default:
		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTMapSystem::HT_hrSetCellMoveEnable( HT_CELL_COORD& rCell, HT_OBJSIZETYPE eType, HTbyte byFloor )
{
	// TODO : 맵 가장자리 부근의 처리인데 이걸로는 Large는 체크못한다.
	if ( rCell.x < 1 || rCell.y < 1 || rCell.x >= m_wMapSizeX || rCell.y >= m_wMapSizeZ )
	{
		return ( HT_FAIL );
	}

	switch( eType )
	{
	case HT_OBJSIZE_SMALL:
		if ( //m_ppCell[idxDstX][idxDstZ].byFloor == byFloor &&
			( m_ppCell[rCell.x][rCell.y].wState & HT_CELL_MOVE_DISABLE ) )
		{
			m_ppCell[rCell.x][rCell.y].wState -= HT_CELL_MOVE_DISABLE;
		}
		//else
		//{
		//	HT_CELL_NODE* pNode = m_ppCell[idxDstX][idxDstZ].pNextNode;
		//	while ( pNode )
		//	{
		//		if ( pNode->byFloor == byFloor && !(pNode->wState & HT_CELL_MOVE_DISABLE) )
		//			pNode->wState += HT_CELL_MOVE_DISABLE;

		//		pNode = pNode->pNextNode;
		//	}
		//}
		return ( HT_OK );
		// TODO : 
	case HT_OBJSIZE_MEDIUM:
		break;
	case HT_OBJSIZE_LARGE:
		break;
	default:
		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTMapSystem::HT_hrDeleteObject( HTint idObj, HT_OBJSIZETYPE eType, HTbyte byFloor )
{
	std::map<HTint, HT_MAP_REMEMBEROBJ*>::iterator itElement = m_hashmapObjects.find( idObj );
	if ( itElement != m_hashmapObjects.end() )
	{
		std::vector<HTGrassMapNode*>::iterator itNodes;
		HT_MAP_REMEMBEROBJ* pRObj = itElement->second;
		if ( !pRObj )
		{
			return ( HT_FAIL );
		}
		itNodes = pRObj->vectorMapNodes.begin();
		while ( itNodes != pRObj->vectorMapNodes.end() )
		{
			(*itNodes)->m_setObjects.erase( idObj );
			(*itNodes)->m_setSMObjects.erase( idObj );
			itNodes++;
		}
		pRObj->vectorMapNodes.clear();

		HT_DELETE( pRObj );
		
		m_hashmapObjects.erase( itElement );
	}
	else
	{
		return ( HT_FAIL );
	}

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrMoveObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HT_OBJSIZETYPE eType, HTbyte byFloor )
{
	if ( HT_SUCCEED( HT_hrDeleteObject( idObj, eType, byFloor ) ) )
		HT_hrInsertObject( idObj, pBB, pmatTrasform, eType, byFloor );

	return ( HT_OK );
}

HTbool
CHTMapSystem::HT_bNoAttackMonster( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	HT_CELL_COORD crdCell;
	HT_3DCOORD_TO_CELL( vecTo, crdCell );

	// TODO : 맵 가장자리 부근의 처리인데 이걸로는 Large는 체크못한다.
	if ( crdCell.x < 1 || crdCell.y < 1 || crdCell.x >= m_wMapSizeX || crdCell.y >= m_wMapSizeZ )
	{
		return ( HT_FALSE );
	}

	HTbool bNoAttack = HT_FALSE;
	switch( eType )
	{
	case HT_OBJSIZE_SMALL:
		bNoAttack = HT_bIsAttackMonsterDisable( crdCell.x, crdCell.y, byFloor );
		break;
	case HT_OBJSIZE_MEDIUM:
		if ( HT_bIsAttackMonsterDisable( crdCell.x, crdCell.x, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x, crdCell.x-1, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x, crdCell.y+1, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x-1, crdCell.y, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x-1, crdCell.y-1, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x-1, crdCell.y+1, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x+1, crdCell.y, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x+1, crdCell.y-1, byFloor ) ||
			 HT_bIsAttackMonsterDisable( crdCell.x+1, crdCell.y+1, byFloor ) )
			bNoAttack = HT_FALSE;
		else
			bNoAttack = HT_TRUE;
		break;
	case HT_OBJSIZE_LARGE:
		// TODO
		break;
	default:
		return ( HT_FALSE );
	}

	return ( bNoAttack );
}

HTbool CHTMapSystem::HT_bCanAttack( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	HT_CELL_COORD crdCell;
	HT_3DCOORD_TO_CELL( vecTo, crdCell );

	// TODO : 맵 가장자리 부근의 처리인데 이걸로는 Large는 체크못한다.
	if ( crdCell.x < 1 || crdCell.y < 1 || crdCell.x >= m_wMapSizeX || crdCell.y >= m_wMapSizeZ )
	{
		return ( HT_FALSE );
	}

	HTbool bCanAttack = HT_FALSE;
	switch( eType )
	{
	case HT_OBJSIZE_SMALL:
		bCanAttack = HT_bIsCellAttackEnable( crdCell.x, crdCell.y, byFloor );
		break;
	case HT_OBJSIZE_MEDIUM:
		if ( HT_bIsCellAttackEnable( crdCell.x, crdCell.x, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x, crdCell.x-1, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x, crdCell.y+1, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x-1, crdCell.y, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x-1, crdCell.y-1, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x-1, crdCell.y+1, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x+1, crdCell.y, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x+1, crdCell.y-1, byFloor ) ||
			 HT_bIsCellAttackEnable( crdCell.x+1, crdCell.y+1, byFloor ) )
			bCanAttack = HT_FALSE;
		else
			bCanAttack = HT_TRUE;
		break;
	case HT_OBJSIZE_LARGE:
		// TODO
		break;
	default:
		return ( HT_FALSE );
	}

	return ( bCanAttack );

}
HTbool CHTMapSystem::HT_bCanMove( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor )
{
	HT_CELL_COORD crdCell;
	HT_3DCOORD_TO_CELL( vecTo, crdCell );

	// TODO : 맵 가장자리 부근의 처리인데 이걸로는 Large는 체크못한다.
	if ( crdCell.x < 1 || crdCell.y < 1 || crdCell.x >= m_wMapSizeX || crdCell.y >= m_wMapSizeZ )
	{
		return ( HT_FALSE );
	}

	HTbool bCanMove = HT_FALSE;
	switch( eType )
	{
	case HT_OBJSIZE_SMALL:
		bCanMove = !HT_bIsCellMoveDisable( crdCell.x, crdCell.y, byFloor );
		break;
	case HT_OBJSIZE_MEDIUM:
		if ( HT_bIsCellMoveDisable( crdCell.x, crdCell.x, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x, crdCell.x-1, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x, crdCell.y+1, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x-1, crdCell.y, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x-1, crdCell.y-1, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x-1, crdCell.y+1, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x+1, crdCell.y, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x+1, crdCell.y-1, byFloor ) ||
			 HT_bIsCellMoveDisable( crdCell.x+1, crdCell.y+1, byFloor ) )
			bCanMove = HT_FALSE;
		else
			bCanMove = HT_TRUE;
		break;
	case HT_OBJSIZE_LARGE:
		// TODO
		break;
	default:
		return ( HT_FALSE );
	}

	return ( bCanMove );
}

HTRESULT
CHTMapSystem::HT_hrOpenShootPoint(CHTString& strFile)
{
	m_arrShootPoint.clear();
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	HTint iNum, iVersion;
	HTvector3 vecShootPos;
	oFile.HT_bRead( &iNum, sizeof(HTint) );
	oFile.HT_bRead( &iVersion, sizeof(HTint) );
	for (HTint i=0; i<iNum; i++)
	{
		oFile.HT_bRead( &vecShootPos, sizeof(HTvector3));
		m_arrShootPoint.push_back(vecShootPos);
	}
	oFile.HT_vClose();
	return HT_OK;
}

//HTRESULT				
//CHTMapSystem::HT_hrUpdateShootingPoint(std::vector<HTint> vectorViewingObjs)
//{	
//	m_arrShootPoint.clear();
//	
//	std::vector<HTint>::iterator itObj = vectorViewingObjs.begin();
//	std::vector<HTvector3>	vecShoot;	vecShoot.clear();
//
//	CHTEngineObj* pObj;
//	HTint iShootNum, i;
//	static std::vector<HTvector3>		pVecShootPT;
//	m_arrShootPoint.clear();
//
//	while (itObj != vectorViewingObjs.end())
//	{
//		if ( m_p3DMgr->HT_eGetEObjectType( *itObj ) == HT_EOBJTYPE_RIGIDMODEL )
//		{
//			if ( HT_FAILED(m_p3DMgr->HT_hrGetEObject( *itObj, &pObj )))	continue;
//
//			iShootNum = pObj->HT_iGetShootPointNum();
//			if ( 0!=iShootNum && pObj)
//			{
//				pObj->HT_hrGetShootPointVec(pVecShootPT);
//				for (i=0; i<iShootNum; i++)
//				{
//					m_arrShootPoint.push_back( pVecShootPT[i] );
//				}
//			}
//		}
//		itObj++;
//	}
//	return HT_OK;
//}

HTRESULT				
CHTMapSystem::HT_hrUpdateViewingNodes( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, std::vector<HTint>& vectorViewingObjs, std::vector<HTint>& vectorUpdateObjs )
{
	HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
	HTint i, j;
	HTint iMinX, iMinZ, iMaxX, iMaxZ;

	std::set<HTint> setViewingObjs;
	std::set<HTint> setUpdateObjs;
	setViewingObjs.clear();
	setUpdateObjs.clear();

	if ( m_bHPVSMode )
	{
		// 뷰프러스텀을 전부 체크할 필요없이, 카메라 위치가 속한 HPVS Node를 기준으로 영역을 구한다.
		HTint iX, iZ, iStartX, iStartZ;
		HTint iRadius = (HTint)(m_fHPVSGridSize / 160.0f);
		iX = (HTint)floorf(arrFrustumPoints[0].x / m_fHPVSGridSize);
		iZ = (HTint)floorf(arrFrustumPoints[0].z / m_fHPVSGridSize);

		if ( iX >= 0 && iX < m_iHPVSNodeCountX && iZ >= 0 && iZ < m_iHPVSNodeCountZ )
		{
			iStartX = iX * iRadius;
			iStartZ = iZ * iRadius;
			for ( i = iStartZ; i <= iStartZ + iRadius; i++ )
			{
				for ( j = iStartX; j <= iStartX + iRadius; j++ )
				{
					if ( i >= 0 && j >= 0 && i < HT_MAPNODE_NUM && j < HT_MAPNODE_NUM )
					{
						// 먼저 노드의 바운드박스가 보이는지 검사해서,
						HTVisibilityFlag eVisible;
						CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
							m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

						// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
						if ( eVisible == HT_VISIBILITY_ALL )
						{
							setViewingObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
						}
						// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
						else if ( eVisible == HT_VISIBILITY_SOME )
						{
							std::set<HTint>::iterator itObjs;
							itObjs = m_ppMap[i][j].m_setObjects.begin();
							while ( itObjs != m_ppMap[i][j].m_setObjects.end() )
							{
								if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
								{
									setViewingObjs.insert( setViewingObjs.end(), *itObjs );
								}
								itObjs++;
							}
						}
						// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
						else
						{
						}

						setUpdateObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
					}
				}
			}
			std::list<HTint>::iterator it = m_ppHPVS[iZ][iX].listViewingNodes.begin();
			while ( it != m_ppHPVS[iZ][iX].listViewingNodes.end() )
			{
				iStartX = ( *it % m_iHPVSNodeCountX ) * iRadius;
				iStartZ = (*it / m_iHPVSNodeCountZ) * iRadius;
				for ( i = iStartZ; i <= iStartZ + iRadius; i++ )
				{
					for ( j = iStartX; j <= iStartX + iRadius; j++ )
					{
						if ( i >= 0 && j >= 0 && i < HT_MAPNODE_NUM && j < HT_MAPNODE_NUM )
						{
							// 먼저 노드의 바운드박스가 보이는지 검사해서,
							HTVisibilityFlag eVisible;
							CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
								m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

							// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
							if ( eVisible == HT_VISIBILITY_ALL )
							{
								setViewingObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
							}
							// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
							else if ( eVisible == HT_VISIBILITY_SOME )
							{
								std::set<HTint>::iterator itObjs;
								itObjs = m_ppMap[i][j].m_setObjects.begin();
								while ( itObjs != m_ppMap[i][j].m_setObjects.end() )
								{
									if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
									{
										setViewingObjs.insert( setViewingObjs.end(), *itObjs );
									}
									itObjs++;
								}
							}
							// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
							else
							{
							}

							setUpdateObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
						}
					}
				}
				it++;
			}

			vectorViewingObjs.assign( setViewingObjs.begin(), setViewingObjs.end() );
			vectorUpdateObjs.assign( setUpdateObjs.begin(), setUpdateObjs.end() );
		}
		else
		{
			return ( HT_FAIL );
		}
	}
	else
	{
		// 먼저 뷰프러스텀의 5점을 2차원 평면으로 투영시켜 그 점들의 AABB 영역을 구한다.
		fMinX = arrFrustumPoints[0].x;	fMinZ = arrFrustumPoints[0].z;
		fMaxX = arrFrustumPoints[0].x;	fMaxZ = arrFrustumPoints[0].z;

		for ( i = 1; i < 5; i++ )
		{
			if ( arrFrustumPoints[i].x < fMinX )	fMinX = arrFrustumPoints[i].x;
			if ( arrFrustumPoints[i].z < fMinZ )	fMinZ = arrFrustumPoints[i].z;
			if ( arrFrustumPoints[i].x > fMaxX )	fMaxX = arrFrustumPoints[i].x;
			if ( arrFrustumPoints[i].z > fMaxZ )	fMaxZ = arrFrustumPoints[i].z;
		}

		iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
		iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
		iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
		iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

		// 뷰프러스텀의 2차원 AABB의 영역에 있는 맵 노드들을 가지고 체크를 한다.
		for ( i = iMinZ; i <= iMaxZ; i++ )
		{
			for ( j = iMinX; j <= iMaxX; j++ )
			{
				if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
					continue;

				// 먼저 노드의 바운드박스가 보이는지 검사해서,
				HTVisibilityFlag eVisible;
				CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
					m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

				// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
				if ( eVisible == HT_VISIBILITY_ALL )
				{
					setViewingObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
				}
				// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
				else if ( eVisible == HT_VISIBILITY_SOME )
				{
					std::set<HTint>::iterator itObjs;
					itObjs = m_ppMap[i][j].m_setObjects.begin();
					while ( itObjs != m_ppMap[i][j].m_setObjects.end() )
					{
						if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
						{
							setViewingObjs.insert( setViewingObjs.end(), *itObjs );
						}
						itObjs++;
					}
				}
				// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
				else
				{
				}

				setUpdateObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
			}
		}

		// Object 들의 LOD를 세팅해준다.
		HTfloat fDistFromEye;
		HTint iCurLOD;
		std::set<HTint>::iterator itObjToLOD = setViewingObjs.begin();

		while ( itObjToLOD != setViewingObjs.end() )
		{
			fDistFromEye = m_p3DMgr->HT_fGetDistanceFromCamera( *itObjToLOD );

			if ( m_p3DMgr->HT_eGetEObjectType( *itObjToLOD ) == HT_EOBJTYPE_SKINNEDMODEL )
			{
				iCurLOD = HT_iComputeCharLOD( fDistFromEye, 0 );
			}
			else
				iCurLOD = HT_iComputeLOD( fDistFromEye, 0 );

			if ( iCurLOD == HT_TYPE_LOD_TOOFAR )
			{
				itObjToLOD = setViewingObjs.erase( itObjToLOD );
			}
			else
			{
				m_p3DMgr->HT_vSetLODLevel( *itObjToLOD, iCurLOD );
				++itObjToLOD;
			}
		}

		vectorViewingObjs.assign( setViewingObjs.begin(), setViewingObjs.end() );
		vectorUpdateObjs.assign( setUpdateObjs.begin(), setUpdateObjs.end() );
	}

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrUpdateViewingSMNodes( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, std::vector<HTint>& vectorViewingObjs )
{
	HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
	HTint i, j;
	HTint iMinX, iMinZ, iMaxX, iMaxZ;

	std::set<HTint> setViewingSMObjs;
	setViewingSMObjs.clear();

	if ( m_bHPVSMode )
	{
		// 뷰프러스텀을 전부 체크할 필요없이, 카메라 위치가 속한 HPVS Node를 기준으로 영역을 구한다.
		HTint iX, iZ, iStartX, iStartZ;
		HTint iRadius = (HTint)(m_fHPVSGridSize / 160.0f);
		iX = (HTint)floorf(arrFrustumPoints[0].x / m_fHPVSGridSize);
		iZ = (HTint)floorf(arrFrustumPoints[0].z / m_fHPVSGridSize);

		if ( iX >= 0 && iX < m_iHPVSNodeCountX && iZ >= 0 && iZ < m_iHPVSNodeCountZ )
		{
			iStartX = iX * iRadius;
			iStartZ = iZ * iRadius;
			for ( i = iStartZ; i <= iStartZ + iRadius; i++ )
			{
				for ( j = iStartX; j <= iStartX + iRadius; j++ )
				{
					if ( i >= 0 && j >= 0 && i < HT_MAPNODE_NUM && j < HT_MAPNODE_NUM )
					{
						// 먼저 노드의 바운드박스가 보이는지 검사해서,
						HTVisibilityFlag eVisible;
						CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
							m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

						// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
						if ( eVisible == HT_VISIBILITY_ALL )
						{
							setViewingSMObjs.insert( m_ppMap[i][j].m_setSMObjects.begin(), m_ppMap[i][j].m_setSMObjects.end() );
						}
						// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
						else if ( eVisible == HT_VISIBILITY_SOME )
						{
							std::set<HTint>::iterator itObjs;
							itObjs = m_ppMap[i][j].m_setSMObjects.begin();
							while ( itObjs != m_ppMap[i][j].m_setSMObjects.end() )
							{
								if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
								{
									setViewingSMObjs.insert( setViewingSMObjs.end(), *itObjs );
								}
								itObjs++;
							}
						}
						// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
						else
						{
						}
					}
				}
			}
			std::list<HTint>::iterator it = m_ppHPVS[iZ][iX].listViewingNodes.begin();
			while ( it != m_ppHPVS[iZ][iX].listViewingNodes.end() )
			{
				iStartX = ( *it % m_iHPVSNodeCountX ) * iRadius;
				iStartZ = (*it / m_iHPVSNodeCountZ) * iRadius;
				for ( i = iStartZ; i <= iStartZ + iRadius; i++ )
				{
					for ( j = iStartX; j <= iStartX + iRadius; j++ )
					{
						if ( i >= 0 && j >= 0 && i < HT_MAPNODE_NUM && j < HT_MAPNODE_NUM )
						{
							// 먼저 노드의 바운드박스가 보이는지 검사해서,
							HTVisibilityFlag eVisible;
							CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
								m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

							// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
							if ( eVisible == HT_VISIBILITY_ALL )
							{
								setViewingSMObjs.insert( m_ppMap[i][j].m_setSMObjects.begin(), m_ppMap[i][j].m_setSMObjects.end() );
							}
							// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
							else if ( eVisible == HT_VISIBILITY_SOME )
							{
								std::set<HTint>::iterator itObjs;
								itObjs = m_ppMap[i][j].m_setSMObjects.begin();
								while ( itObjs != m_ppMap[i][j].m_setSMObjects.end() )
								{
									if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
									{
										setViewingSMObjs.insert( setViewingSMObjs.end(), *itObjs );
									}
									itObjs++;
								}
							}
							// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
							else
							{
							}
						}
					}
				}
				it++;
			}
		}
		else
		{
			return ( HT_FAIL );
		}
	}
	else
	{
		// 먼저 뷰프러스텀의 5점을 2차원 평면으로 투영시켜 그 점들의 AABB 영역을 구한다.
		fMinX = arrFrustumPoints[0].x;	fMinZ = arrFrustumPoints[0].z;
		fMaxX = arrFrustumPoints[0].x;	fMaxZ = arrFrustumPoints[0].z;

		for ( i = 1; i < 5; i++ )
		{
			if ( arrFrustumPoints[i].x < fMinX )	fMinX = arrFrustumPoints[i].x;
			if ( arrFrustumPoints[i].z < fMinZ )	fMinZ = arrFrustumPoints[i].z;
			if ( arrFrustumPoints[i].x > fMaxX )	fMaxX = arrFrustumPoints[i].x;
			if ( arrFrustumPoints[i].z > fMaxZ )	fMaxZ = arrFrustumPoints[i].z;
		}

		iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
		iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
		iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
		iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

		// 뷰프러스텀의 2차원 AABB의 영역에 있는 맵 노드들을 가지고 체크를 한다.
		for ( i = iMinZ; i <= iMaxZ; i++ )
		{
			for ( j = iMinX; j <= iMaxX; j++ )
			{
				if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
					continue;

				// 먼저 노드의 바운드박스가 보이는지 검사해서,
				HTVisibilityFlag eVisible;
				CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, 
					m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, pFrustum );

				// 노드가 프러스텀 안에 포함된다면, 다 그리라고 하고,
				if ( eVisible == HT_VISIBILITY_ALL )
				{
					setViewingSMObjs.insert( m_ppMap[i][j].m_setSMObjects.begin(), m_ppMap[i][j].m_setSMObjects.end() );
				}
				// 노드가 걸려있다면 그 안의 오브젝트들을 하나하나 검사하고,
				else if ( eVisible == HT_VISIBILITY_SOME )
				{
					std::set<HTint>::iterator itObjs;
					itObjs = m_ppMap[i][j].m_setSMObjects.begin();
					while ( itObjs != m_ppMap[i][j].m_setSMObjects.end() )
					{
						if ( m_p3DMgr->HT_bIsInsideFrustum( *itObjs ) )
						{
							setViewingSMObjs.insert( m_ppMap[i][j].m_setSMObjects.begin(), m_ppMap[i][j].m_setSMObjects.end() );
						}
						itObjs++;
					}
				}
				// 노드가 밖에 있다면, 그 안의 오브젝트를 그릴 필요없다.
				else
				{
				}
			}
		}
		// SM Object 들의 LOD를 세팅해준다.
		HTfloat fDistFromEye;
		HTint iCurLOD;
		std::set<HTint>::iterator itObjToLOD;
		itObjToLOD = setViewingSMObjs.begin();

		while ( itObjToLOD != setViewingSMObjs.end() )
		{
			fDistFromEye = m_p3DMgr->HT_fGetDistanceFromCamera( *itObjToLOD );
			iCurLOD = HT_iComputeLOD( fDistFromEye, 0 );

			if ( fDistFromEye >= m_fLODDistanceFarSM )
			{
				itObjToLOD = setViewingSMObjs.erase( itObjToLOD );
			}
			else
			{
				m_p3DMgr->HT_vSetLODLevel( *itObjToLOD, iCurLOD );
				++itObjToLOD;
			}
		}
	}

	// SM Object들도 포함시킨다.
	vectorViewingObjs.insert( vectorViewingObjs.end(), setViewingSMObjs.begin(), setViewingSMObjs.end() );

	return ( HT_OK );
}

HTRESULT CHTMapSystem::HT_hrPick( HTRay& rRay, std::list<HTint>& listObjs )
{
	HTint iCenterX = (HTint)floorf(rRay.m_vecStartPos.x / HT_MAPNODE_SIZE);
	HTint iCenterZ = (HTint)floorf(rRay.m_vecStartPos.z / HT_MAPNODE_SIZE);

	std::set<HTint> setObjs;
	setObjs.clear();
	listObjs.clear();

	// ray의 중심점이 포함된 노드를 중심으로 반경 얼마 안에 있는 것만 체크를 한다.
	// 그 영역은 AOI의 거리를 고려하여 정해지는데, 일단 7*7 노드 즉 112m * 112m 로 정해놓는다.
	HTint iRadiusNode = 3;
	for ( HTint i = iCenterZ - iRadiusNode; i <= iCenterZ + iRadiusNode; i++ )
	{
		for ( HTint j = iCenterX - iRadiusNode; j <= iCenterX + iRadiusNode; j++ )
		{
			if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
				continue;

			if ( CHTIntersect::HT_bIsRayBoxIntersect( m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, rRay ) )
			{
				setObjs.insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
			}
		}
	}

	listObjs.assign( setObjs.begin(), setObjs.end() );

	return ( HT_OK );
}

HT_TILE_TYPE CHTMapSystem::HT_eGetTileType( HTint iX, HTint iZ, HTint iF )
{
//	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_TILE_NONE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
//		return ( (HT_TILE_TYPE)m_ppCell[iX][iZ].byFeature );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( (HT_TILE_TYPE)pNode->byFeature );

	//		pNode = pNode->pNextNode;
	//	}
	//}

	return ( HT_TILE_NONE );
}

HTbool CHTMapSystem::HT_bIsCellSafeZone( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_FALSE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_SAFE_ZONE) ? (HT_TRUE) : (HT_FALSE) );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( ( pNode->wState & HT_CELL_SAFE_ZONE) ? (HT_TRUE) : (HT_FALSE) );

	//		pNode = pNode->pNextNode;
	//	}
	//}

	return ( HT_FALSE );
}

HTbool CHTMapSystem::HT_bIsCellConflict( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_FALSE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_CONFLICT) ? (HT_TRUE) : (HT_FALSE) );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( ( pNode->wState & HT_CELL_CONFLICT) ? (HT_TRUE) : (HT_FALSE) );

	//		pNode = pNode->pNextNode;
	//	}
	//}

	return ( HT_FALSE );
}

HTbool CHTMapSystem::HT_bIsCellPKZone( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_FALSE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_PK_ZONE) ? (HT_TRUE) : (HT_FALSE) );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( ( pNode->wState & HT_CELL_PK_ZONE) ? (HT_TRUE) : (HT_FALSE) );

	//		pNode = pNode->pNextNode;
	//	}
	//}

	return ( HT_FALSE );
}

HTbool CHTMapSystem::HT_bIsCellTemple( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_FALSE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_TEMPLE) ? (HT_TRUE) : (HT_FALSE) );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( ( pNode->wState & HT_CELL_INTERIOR) ? (HT_TRUE) : (HT_FALSE) );

	//		pNode = pNode->pNextNode;
	//	}
	//}

	return ( HT_FALSE );
}

HTbool CHTMapSystem::HT_bIsAttackMonsterDisable( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_TRUE );

	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_NOATTACKMONSTER) ? (HT_TRUE) : (HT_FALSE) );
	}
}

HTbool CHTMapSystem::HT_bIsCellAttackEnable( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_TRUE );

	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_ATTACKENABLE) ? (HT_TRUE) : (HT_FALSE) );
	}
}

HTbool CHTMapSystem::HT_bIsCellMoveDisable( HTint iX, HTint iZ, HTint iF )
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_TRUE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_MOVE_DISABLE) ? (HT_TRUE) : (HT_FALSE) );
	}
	//else
	//{
	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
	//	while ( pNode )
	//	{
	//		if ( pNode->byFloor == iF )
	//			return ( ( pNode->wState & HT_CELL_MOVE_DISABLE) ? (HT_TRUE) : (HT_FALSE) );

	//		pNode = pNode->pNextNode;
	//	}
	//}

//	return ( HT_FALSE );
}

//HTbool CHTMapSystem::HT_bIsCellVishunu( HTint iX, HTint iZ, HTint iF )
//{
//	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
//		return ( HT_FALSE );
//
////	if ( m_ppCell[iX][iZ].byFloor == iF )
//	{
//		return ( ( m_ppCell[iX][iZ].wState & HT_CELL_SIT_DISABLE) ? (HT_TRUE) : (HT_FALSE) );
//	}
//	//else
//	//{
//	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
//	//	while ( pNode )
//	//	{
//	//		if ( pNode->byFloor == iF )
//	//			return ( ( pNode->wState & HT_CELL_SIT_DISABLE) ? (HT_TRUE) : (HT_FALSE) );
//
//	//		pNode = pNode->pNextNode;
//	//	}
//	//}
//
//	return ( HT_FALSE );
//}

//HTbool CHTMapSystem::HT_bIsCellSiva( HTint iX, HTint iZ, HTint iF )
//{
//	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
//		return ( HT_FALSE );
//
////	if ( m_ppCell[iX][iZ].byFloor == iF )
//	{
//		return ( ( m_ppCell[iX][iZ].wState & HT_MAP_OBJECT_SIT_DISABLE) ? (HT_TRUE) : (HT_FALSE) );
//	}
//	//else
//	//{
//	//	HT_CELL_NODE* pNode = m_ppCell[iX][iZ].pNextNode;
//	//	while ( pNode )
//	//	{
//	//		if ( pNode->byFloor == iF )
//	//			return ( ( pNode->wState & HT_CELL_SIT_DISABLE) ? (HT_TRUE) : (HT_FALSE) );
//
//	//		pNode = pNode->pNextNode;
//	//	}
//	//}
//
//	return ( HT_FALSE );
//}


//--------------------------------------------------------------------------
// WORD		HT_wGetObjHeight(HTint iX, HTint iZ, HTint iF )
// D : 올라갈 오브젝트의 높이 얻기
// I : iX, iZ - 좌표, iF - 층
// R : 오브젝트의 높이
//--------------------------------------------------------------------------
WORD
CHTMapSystem::HT_wGetObjHeight(HTint iX, HTint iZ, HTint iF ) // 대호 추가
{
	if ( iX < 0 || iZ < 0 || iX >= m_wMapSizeX || iZ >= m_wMapSizeZ )
		return ( HT_FALSE );

//	if ( m_ppCell[iX][iZ].byFloor == iF )
	{
		return m_ppCell[iX][iZ].wObjHeight;
	}
}

HTRESULT CHTMapSystem::HT_hrAStarSearch( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal, HTint* nNode, HT_CELL_COORD* arrNode )
{
	HTint i;
	HTbool bInOpen, bInClosed;

	// 목표지점이 갈 수 없는 곳이면 계산하지 않고 바로 끝낸다.
	if ( HT_bIsCellMoveDisable( rGoal.x, rGoal.y, 0 ) )
	{
		*nNode = 0;
		return ( HT_FAIL );
	}

	HT_vFreeAllNodes();

	// 시작 노드를 초기화한다.
	HT_MAP_PATHNODE* pStartNode = new HT_MAP_PATHNODE;
	pStartNode->celLocation = rStart;
	pStartNode->fCostFromStart = 0.0f;
	pStartNode->fCostToGoal = HT_fPathCostEstimate( rStart, rGoal );
	pStartNode->pParent = HT_NULL;

	m_prqueOpen.push( pStartNode );

	while ( !m_prqueOpen.empty() )
	{
		HT_MAP_PATHNODE* pNode = m_prqueOpen.top();	// 노드가 최저비용을 가지는 경우
		m_prqueOpen.pop();

		// 목표에 도달했으면
		if ( pNode->celLocation.x == rGoal.x && pNode->celLocation.y == rGoal.y )
		{
			*nNode = 0;
//			m_vectorFoundPath.clear();
			while ( pNode )
			{
				arrNode[*nNode].x = pNode->celLocation.x;
				arrNode[*nNode].y = pNode->celLocation.y;
				++(*nNode);
//				m_vectorFoundPath.push_back( pNode->celLocation );
				pNode = pNode->pParent;
			}

			return ( HT_OK );
		}
		else
		{
			//	0  1  2
			//  3     4
			//  5  6  7
			for ( i = 0; i < 8; i++ )
			{
				// 자식노드들이 생성되어 있지 않다면, 인접 셀의 정보로 생성시켜라.
				HT_CELL_COORD cellChild;
				switch ( i )
				{
				case 0:
					cellChild.x = pNode->celLocation.x - 1;
					cellChild.y = pNode->celLocation.y - 1;
					break;
				case 1:
					cellChild.x = pNode->celLocation.x;
					cellChild.y = pNode->celLocation.y - 1;
					break;
				case 2:
					cellChild.x = pNode->celLocation.x + 1;
					cellChild.y = pNode->celLocation.y - 1;
					break;
				case 3:
					cellChild.x = pNode->celLocation.x - 1;
					cellChild.y = pNode->celLocation.y;
					break;
				case 4:
					cellChild.x = pNode->celLocation.x + 1;
					cellChild.y = pNode->celLocation.y;
					break;
				case 5:
					cellChild.x = pNode->celLocation.x - 1;
					cellChild.y = pNode->celLocation.y + 1;
					break;
				case 6:
					cellChild.x = pNode->celLocation.x;
					cellChild.y = pNode->celLocation.y + 1;
					break;
				case 7:
					cellChild.x = pNode->celLocation.x + 1;
					cellChild.y = pNode->celLocation.y + 1;
					break;
				}

				if ( !HT_bIsCellMoveDisable( cellChild.x, cellChild.y, 0 ) )
				{
					if ( HT_bIsInClosed( cellChild ) )
					{
						pNode->pChilds[i] = HT_pGetNodeInClosed( cellChild );
						bInClosed = HT_TRUE;
					}
					else
					{
						bInClosed = HT_FALSE;
					}

					if ( HT_bIsInOpen( cellChild ) )
					{
						pNode->pChilds[i] = HT_pGetNodeInOpen( cellChild );
						bInOpen = HT_TRUE;
					}
					else if ( bInClosed )
					{
						bInOpen = HT_FALSE;
					}
					else
					{
						pNode->pChilds[i] = new HT_MAP_PATHNODE;
						pNode->pChilds[i]->celLocation.x = cellChild.x;
						pNode->pChilds[i]->celLocation.y = cellChild.y;
						
						bInOpen = HT_FALSE;
					}

					HTfloat fNewCost = pNode->fCostFromStart + 
						HT_fTraverseCost( pNode, pNode->pChilds[i] );

					// 이 노드가 존재하며, 더 나은 결과가 아니라면 무시한다.
					if ( ( bInClosed || bInOpen ) &&
						pNode->pChilds[i]->fCostFromStart <= fNewCost )
					{
						continue;
					}
					else	// 새로운 더 나은 정보를 저장한다.
					{
						pNode->pChilds[i]->pParent = pNode;
						pNode->pChilds[i]->fCostFromStart = fNewCost;
						pNode->pChilds[i]->fCostToGoal = HT_fPathCostEstimate( 
							pNode->pChilds[i]->celLocation, rGoal );
						pNode->pChilds[i]->fTotalCost = pNode->pChilds[i]->fCostFromStart +
							pNode->pChilds[i]->fCostToGoal;

						HT_vRemoveNodeInClosed( pNode->pChilds[i] );
						
						if ( bInOpen )
						{
							HT_vRemoveNodeInOpen( pNode->pChilds[i] );
						}
						else
						{
							m_prqueOpen.push( pNode->pChilds[i] );
						}
					}
				}
			}
		}
		
		m_listClosed.push_back( pNode );
	}

	return ( HT_FAIL );
}

HTvoid CHTMapSystem::HT_vFreeAllNodes()
{
	while( !m_prqueOpen.empty() )
	{
		HT_DELETE( m_prqueOpen.top() );
		m_prqueOpen.pop();
	}

	// iterate closed list and delete unused nodes
	std::list<HT_MAP_PATHNODE*>::iterator iterClosed;
	for( iterClosed = m_listClosed.begin(); iterClosed != m_listClosed.end(); )
	{
		HT_DELETE( *iterClosed );
		iterClosed = m_listClosed.erase( iterClosed );
	}

	m_listClosed.clear();

	m_vectorFoundPath.clear();

}

HTfloat CHTMapSystem::HT_fPathCostEstimate( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal )
{
	// 정사각형 타일에서의 거리
//	return ( HT_ABS( HT_ABS( rGoal.x - rStart.x ) - HT_ABS( rGoal.y - rStart.y ) ) + 
//		HT_MIN( HT_ABS( rGoal.x - rStart.x ), HT_ABS( rGoal.y - rStart.y ) ) * sqrtf( 2.0f ) );

	// 유클리드 좌표계의 거리
	return ( sqrtf( (HTfloat)( (rGoal.x - rStart.x)*(rGoal.x - rStart.x) + 
		(rGoal.y - rStart.y)*(rGoal.y - rStart.y) ) * m_fHeuristic ) );
}

HTfloat CHTMapSystem::HT_fTraverseCost( HT_MAP_PATHNODE* pParent, HT_MAP_PATHNODE* pChild )
{
	// 현재는 부모와 자식간의 이동 비용이 타일 한칸 이동 비용과 같다고 본다.
	// 즉 타일들에 여러가지 비용이 적용되지 않고 일정한 비용이 든다고 가정한다.
	return ( m_fCostToMoveOneCell );
}

HTbool CHTMapSystem::HT_bIsInClosed( HT_CELL_COORD& rCell )
{
	std::list<HT_MAP_PATHNODE*>::iterator iterClosed;
	for( iterClosed = m_listClosed.begin(); iterClosed != m_listClosed.end(); ++iterClosed )
	{
		if ( (*iterClosed)->celLocation.x == rCell.x &&
			(*iterClosed)->celLocation.y == rCell.y )
			return ( HT_TRUE );
	}

	return ( HT_FALSE );
}

HTbool CHTMapSystem::HT_bIsInOpen( HT_CELL_COORD& rCell )
{
	// TODO : 있나만 보는 함수인데도 불구하고, 접근자가 없어서 이런 짓들을 한다.
	std::list<HT_MAP_PATHNODE*> listTmp;
	HT_MAP_PATHNODE* pTmpNode;

	while( !m_prqueOpen.empty() )
	{
		pTmpNode = m_prqueOpen.top();
		if ( pTmpNode->celLocation.x == rCell.x &&
			 pTmpNode->celLocation.y == rCell.y )
		{
			std::list<HT_MAP_PATHNODE*>::iterator it = listTmp.begin();
			while ( it != listTmp.end() )
			{
				m_prqueOpen.push( *it );
				it = listTmp.erase( it );
			}
			return ( HT_TRUE );
		}

		m_prqueOpen.pop();
		listTmp.push_back( pTmpNode );
	}

	std::list<HT_MAP_PATHNODE*>::iterator it = listTmp.begin();
	while ( it != listTmp.end() )
	{
		m_prqueOpen.push( *it );
		it = listTmp.erase( it );
	}

	return ( HT_FALSE );
}

HTvoid CHTMapSystem::HT_vRemoveNodeInClosed( HT_MAP_PATHNODE* pNode )
{
	std::list<HT_MAP_PATHNODE*>::iterator iterClosed;
	for( iterClosed = m_listClosed.begin(); iterClosed != m_listClosed.end(); ++iterClosed )
	{
		if ( (*iterClosed) == pNode )
		{
			HT_DELETE( *iterClosed );
			m_listClosed.erase( iterClosed );
			return;
		}
	}
}

HTvoid CHTMapSystem::HT_vRemoveNodeInOpen( HT_MAP_PATHNODE* pNode )
{
	std::list<HT_MAP_PATHNODE*> listTmp;
	HT_MAP_PATHNODE* pTmpNode;

	while( !m_prqueOpen.empty() )
	{
		pTmpNode = m_prqueOpen.top();
		m_prqueOpen.pop();

		if ( pTmpNode == pNode )
		{
			HT_DELETE( pTmpNode );

			std::list<HT_MAP_PATHNODE*>::iterator it = listTmp.begin();
			while ( it != listTmp.end() )
			{
				m_prqueOpen.push( *it );
				it = listTmp.erase( it );
			}
			return;
		}
		else
		{
			listTmp.push_back( pTmpNode );
		}
	}

	std::list<HT_MAP_PATHNODE*>::iterator it;
	it = listTmp.begin();
	while ( it != listTmp.end() )
	{
		m_prqueOpen.push( *it );
		it = listTmp.erase( it );
	}
}

HT_MAP_PATHNODE* CHTMapSystem::HT_pGetNodeInClosed( HT_CELL_COORD& rCell )
{
	std::list<HT_MAP_PATHNODE*>::iterator iterClosed;
	for( iterClosed = m_listClosed.begin(); iterClosed != m_listClosed.end(); ++iterClosed )
	{
		if ( (*iterClosed)->celLocation.x == rCell.x &&
			(*iterClosed)->celLocation.y == rCell.y )
		{
			return ( *iterClosed );
		}
	}

	return ( HT_FALSE );
}

HT_MAP_PATHNODE* CHTMapSystem::HT_pGetNodeInOpen( HT_CELL_COORD& rCell )
{
	std::list<HT_MAP_PATHNODE*> listTmp;
	HT_MAP_PATHNODE* pTmpNode;

	while( !m_prqueOpen.empty() )
	{
		pTmpNode = m_prqueOpen.top();
		if ( pTmpNode->celLocation.x == rCell.x &&
			 pTmpNode->celLocation.y == rCell.y )
		{
			std::list<HT_MAP_PATHNODE*>::iterator it = listTmp.begin();
			while ( it != listTmp.end() )
			{
				m_prqueOpen.push( *it );
				it = listTmp.erase( it );
			}

			return ( pTmpNode );
		}

		m_prqueOpen.pop();
		listTmp.push_back( pTmpNode );
	}

	std::list<HT_MAP_PATHNODE*>::iterator it = listTmp.begin();
	while ( it != listTmp.end() )
	{
		m_prqueOpen.push( *it );
		it = listTmp.erase( it );
	}

	return ( HT_NULL );
}

HTRESULT				
CHTMapSystem::HT_hrInsertGrassObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HTdword dwResID, HT_EOBJ_PROPERTY* pProperty )
{
	// 먼저 중심점이 포함된 노드는 반드시 오브젝트를 넣게 된다.
	HTint x = (HTint)floorf(pmatTrasform->_41 / HT_GRASSMAPNODE_SIZE);
	HTint z = (HTint)floorf(pmatTrasform->_43 / HT_GRASSMAPNODE_SIZE);

	if ( x < 0 || z < 0 || x >= HT_GRASSMAPNODE_NUM || z >= HT_GRASSMAPNODE_NUM )
		return ( HT_FAIL );

	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;
#ifdef HT_MAPSYSTEM_SAVETML
	HT_MAP_SAVEOBJ* pSaveObj = new HT_MAP_SAVEOBJ;
	pSaveObj->bGrass = HT_TRUE;
	pSaveObj->dwResID = dwResID;
	pSaveObj->matTransform = *pmatTrasform;
	if ( pProperty )	memcpy( &pSaveObj->oProperty, pProperty, sizeof(HT_EOBJ_PROPERTY) );
#endif

	m_ppGrassMap[x][z].m_setObjects.insert( idObj );
	pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x][z] );

#ifdef HT_MAPSYSTEM_SAVETML
	pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x, z ) );
#endif

	// 풀은 한 노드의 넓이만큼 크지 않다고 가정하고, 주위의 이웃하는 8노드까지만 검사한다.
	if ( x-1 >= 0 )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x-1][z].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x-1][z].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x-1, z ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x-1][z] );
		}
	}
	if ( x+1 < HT_GRASSMAPNODE_NUM )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x+1][z].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x+1][z].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x+1, z ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x+1][z] );
		}
	}
	if ( x-1 >= 0 && z-1 >= 0 )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x-1][z-1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x-1][z-1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x-1, z-1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x-1][z-1] );
		}
	}
	if ( z-1 >= 0 )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x][z-1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x][z-1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x, z-1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x][z-1] );
		}
	}
	if ( x+1 < HT_GRASSMAPNODE_NUM && z-1 >= 0 )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x+1][z-1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x+1][z-1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x+1, z-1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x+1][z-1] );
		}
	}
	if ( x-1 >= 0 && z+1 < HT_GRASSMAPNODE_NUM )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x-1][z+1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x-1][z+1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x-1, z+1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x-1][z+1] );
		}
	}
	if ( z+1 < HT_GRASSMAPNODE_NUM )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x][z+1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x][z+1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x, z+1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x][z+1] );
		}
	}
	if ( x+1 < HT_GRASSMAPNODE_NUM && z+1 < HT_GRASSMAPNODE_NUM )
	{
		if ( CHTIntersect::HT_iIntersectAABBvsOBB( m_ppGrassMap[x+1][z+1].m_boxArea, *pBB, *pmatTrasform ) == HT_INTERSECT_TRUE )
		{
			m_ppGrassMap[x+1][z+1].m_setObjects.insert( idObj );
#ifdef HT_MAPSYSTEM_SAVETML
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( x+1, z+1 ) );
#endif
			pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[x+1][z+1] );
		}
	}

#ifdef HT_MAPSYSTEM_SAVETML
	m_mapSaveObjs.insert( std::map<HTint,HT_MAP_SAVEOBJ*>::value_type( idObj, pSaveObj ) );
#endif

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

	return ( HT_OK );
}

HTRESULT 
CHTMapSystem::HT_hrUpdateViewingGrasses( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, HTfloat fCullingDist, HTfloat fGrassAlphaDistance, std::vector<HTint>& arrGrasses )
{
	if ( !arrFrustumPoints || !pFrustum )
		return ( HT_FAIL );

	m_setViewingGrass.clear();

	{
		// 먼저 뷰프러스텀의 5점을 풀컬링 거리로 줄인다.
		HTvector3 arrvecGrassFrustum[5];
		HTvector3 vecNormal;

		// 실제 컬링 거리와 카메라 뷰프러스텀 거리간의 보정값
		HTfloat fError = 2.0f;

		arrvecGrassFrustum[0] = arrFrustumPoints[0];	// 0 은 eye position이니까 그대로 두고

		vecNormal = arrFrustumPoints[1] - arrFrustumPoints[0];
		CHTVector::HT_pvecVec3Normalize( &vecNormal, &vecNormal );
		arrvecGrassFrustum[1] = arrFrustumPoints[0] + fError*fCullingDist*vecNormal;

		vecNormal = arrFrustumPoints[2] - arrFrustumPoints[0];
		CHTVector::HT_pvecVec3Normalize( &vecNormal, &vecNormal );
		arrvecGrassFrustum[2] = arrFrustumPoints[0] + fError*fCullingDist*vecNormal;

		vecNormal = arrFrustumPoints[3] - arrFrustumPoints[0];
		CHTVector::HT_pvecVec3Normalize( &vecNormal, &vecNormal );
		arrvecGrassFrustum[3] = arrFrustumPoints[0] + fError*fCullingDist*vecNormal;

		vecNormal = arrFrustumPoints[4] - arrFrustumPoints[0];
		CHTVector::HT_pvecVec3Normalize( &vecNormal, &vecNormal );
		arrvecGrassFrustum[4] = arrFrustumPoints[0] + fError*fCullingDist*vecNormal;

		// 2차원 평면으로 투영시켜 그 점들의 AABB 영역을 구한다.
		HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
		fMinX = arrvecGrassFrustum[0].x;	fMinZ = arrvecGrassFrustum[0].z;
		fMaxX = arrvecGrassFrustum[0].x;	fMaxZ = arrvecGrassFrustum[0].z;

		HTint i, j;
		for ( i = 1; i < 5; i++ )
		{
			if ( arrvecGrassFrustum[i].x < fMinX )	fMinX = arrvecGrassFrustum[i].x;
			if ( arrvecGrassFrustum[i].z < fMinZ )	fMinZ = arrvecGrassFrustum[i].z;
			if ( arrvecGrassFrustum[i].x > fMaxX )	fMaxX = arrvecGrassFrustum[i].x;
			if ( arrvecGrassFrustum[i].z > fMaxZ )	fMaxZ = arrvecGrassFrustum[i].z;
		}

		HTint iMinX = (HTint)floorf(fMinX / HT_GRASSMAPNODE_SIZE);
		HTint iMinZ = (HTint)floorf(fMinZ / HT_GRASSMAPNODE_SIZE);
		HTint iMaxX = (HTint)floorf(fMaxX / HT_GRASSMAPNODE_SIZE);
		HTint iMaxZ = (HTint)floorf(fMaxZ / HT_GRASSMAPNODE_SIZE);

		std::set<HTint> setViewingObjs;
		setViewingObjs.clear();

		// 축소판 뷰프러스텀의 2차원 AABB의 영역에 있는 맵 노드들을 가지고 체크를 한다.
		for ( j = iMinZ; j <= iMaxZ; j++ )
		{
			for ( i = iMinX; i <= iMaxX; i++ )
			{
				if ( i < 0 || j < 0 || i >= HT_GRASSMAPNODE_NUM || j >= HT_GRASSMAPNODE_NUM )
					continue;

				HTVisibilityFlag eVisible;
				CHTIntersect::HT_hrCheckBoxVisibility( &eVisible, m_ppGrassMap[i][j].m_boxArea.vecMin,
					m_ppGrassMap[i][j].m_boxArea.vecMax, pFrustum );
				if ( eVisible == HT_VISIBILITY_SOME || eVisible == HT_VISIBILITY_ALL )
				{
					m_setViewingGrass.insert( m_ppGrassMap[i][j].m_setObjects.begin(),
						m_ppGrassMap[i][j].m_setObjects.end() );
				}
			}
		}
	}

	// 보이는 풀들을 가지고 거리에 따라 알파를 먹여서 부드럽게 등장시킨다.
	HTfloat fDistObject;
	arrGrasses.clear();
	arrGrasses.assign( m_setViewingGrass.begin(), m_setViewingGrass.end() );

	HTvector3 vecEye;
	vecEye = arrFrustumPoints[0];

	std::vector<HTint>::iterator itGrasses;
	itGrasses = arrGrasses.begin();
	while ( itGrasses != arrGrasses.end() )
	{
		HTvector3 vecPos;
		if ( HT_SUCCEED( m_p3DMgr->HT_hrGetPosition( *itGrasses, vecPos ) ) )
		{
			vecPos = vecEye - vecPos;
			fDistObject = CHTVector::HT_fVec3Length( &vecPos );
		}
		else
		{
			itGrasses++;
			continue;
		}

		HTfloat fDistAlpha = fCullingDist - fDistObject;
		if ( fDistAlpha < fGrassAlphaDistance )
		{
			if ( fDistAlpha > 0.0f )
				m_p3DMgr->HT_hrChangeColor( *itGrasses, HT_COLOR( 1.0f, 1.0f, 1.0f, (fDistAlpha/fGrassAlphaDistance) ) );
			else
			{
				itGrasses = arrGrasses.erase( itGrasses );
				continue;
			}
		}
		else
		{
			// 거리 안에 있는 풀들은 원래의 알파값을 적용시켜야 한다.
			m_p3DMgr->HT_hrChangeColor( *itGrasses, HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		}
		itGrasses++;
	}

	return ( HT_OK );
}

HTint 
CHTMapSystem::HT_iComputeLOD( HTfloat fDistFromCam, HTint iPrevLOD )
{
#if 1
	if ( -m_fLODDistanceLow1 <= fDistFromCam && fDistFromCam <= m_fLODDistanceLow1 )
	{
		return ( HT_TYPE_LOD_CLOSEST );
	}
	else if ( fDistFromCam > m_fLODDistanceLow1 && fDistFromCam <= m_fLODDistanceLow2 )
	{
		return ( HT_TYPE_LOD_NEAR );
	}
	else if ( fDistFromCam > m_fLODDistanceLow2 && fDistFromCam <= m_fLODDistanceLow3 )
	{
		return ( HT_TYPE_LOD_MEDIUM );
	}
	else if ( fDistFromCam > m_fLODDistanceLow3 && fDistFromCam <= m_fLODDistanceFar )
	{
		return ( HT_TYPE_LOD_FAR );
	}
	else
	{
		return ( HT_TYPE_LOD_TOOFAR );
	}
#else
	if ( fDistFromCam < m_fLODDistanceLow1 )
	{
		return ( HT_TYPE_LOD_CLOSEST );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh1 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceLow2 )
	{
		return ( HT_TYPE_LOD_NEAR );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh2 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceLow3 )
	{
		return ( HT_TYPE_LOD_MEDIUM );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh3 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceFar )
	{
		return ( HT_TYPE_LOD_FAR );
	}
	else
	{
		return ( HT_TYPE_LOD_TOOFAR );
	}
#endif
}

HTRESULT				
CHTMapSystem::HT_hrSetLODValues( HTfloat fL1, HTfloat fL2, HTfloat fL3, HTfloat fH1, HTfloat fH2, HTfloat fH3, 
								HTfloat fFar, HTfloat fSMFar, HTfloat fCL1, HTfloat fCL2, HTfloat fCL3 )
{
	m_fLODDistanceLow1 = fL1;
	m_fLODDistanceLow2 = fL2;
	m_fLODDistanceLow3 = fL3;
	m_fLODDistanceHigh1 = fH1;
	m_fLODDistanceHigh2 = fH2;
	m_fLODDistanceHigh3 = fH3;
	m_fLODDistanceFar = fFar;
	m_fLODDistanceFarSM = fSMFar;
	m_fCharLODDistance1 = fCL1;
	m_fCharLODDistance2 = fCL2;
	m_fCharLODDistance3 = fCL3;
	return ( HT_OK );
}

HTint 
CHTMapSystem::HT_iComputeCharLOD( HTfloat fDistFromCam, HTint iPrevLOD )
{
#if 1
	if ( -m_fCharLODDistance1 <= fDistFromCam && fDistFromCam <= m_fCharLODDistance1 )
	{
		return ( HT_TYPE_LOD_CLOSEST );
	}
	else if ( fDistFromCam > m_fCharLODDistance1 && fDistFromCam <= m_fCharLODDistance2 )
	{
		return ( HT_TYPE_LOD_NEAR );
	}
	else if ( fDistFromCam > m_fCharLODDistance2 && fDistFromCam <= m_fCharLODDistance3 )
	{
		return ( HT_TYPE_LOD_MEDIUM );
	}
	else if ( fDistFromCam > m_fCharLODDistance3 && fDistFromCam <= m_fLODDistanceFar )
	{
		return ( HT_TYPE_LOD_FAR );
	}
	else
	{
		return ( HT_TYPE_LOD_TOOFAR );
	}
#else
	if ( fDistFromCam < m_fLODDistanceLow1 )
	{
		return ( HT_TYPE_LOD_CLOSEST );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh1 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceLow2 )
	{
		return ( HT_TYPE_LOD_NEAR );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh2 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceLow3 )
	{
		return ( HT_TYPE_LOD_MEDIUM );
	}
	else if ( fDistFromCam < m_fLODDistanceHigh3 )
	{
		return ( iPrevLOD );
	}
	else if ( fDistFromCam < m_fLODDistanceFar )
	{
		return ( HT_TYPE_LOD_FAR );
	}
	else
	{
		return ( HT_TYPE_LOD_TOOFAR );
	}
#endif
}

HTRESULT				
CHTMapSystem::HT_hrLoadMapSound( CHTString& strFile )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	HTint iVersion;

	CHTString strBuf;
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );	// read version
	
	if ( strBuf == _T("[VERSION_1001]") )
		iVersion = 1001;
	else if ( strBuf == _T("[VERSION_1002]") )
		iVersion = 1002;
	else
		iVersion = 0;

	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	HTint iSoundSpaceCount = atoi( strBuf );

	HTSoundSpaceNode* pSpace = HT_NULL;

	for ( HTint i = 0; i < iSoundSpaceCount; i++ )
	{
		pSpace = new HTSoundSpaceNode;

		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->dwBGMID = strBuf.HT_iToInt();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->rcArea.fLeft = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->rcArea.fBottom = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->rcArea.fRight = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->rcArea.fTop = strBuf.HT_fToFloat();

		HTint iCount = 0;
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		iCount = strBuf.HT_iToInt();
		for ( HTint j = 0; j < iCount; j++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			pSpace->vectorDaySounds.push_back( strBuf.HT_iToInt() );
		}

		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		iCount = strBuf.HT_iToInt();
		for ( HTint j = 0; j < iCount; j++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			pSpace->vectorNightSounds.push_back( strBuf.HT_iToInt() );
		}

		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pSpace->iRoomType = strBuf.HT_iToInt();

		m_vectorSoundSpaces.push_back( pSpace );
	}

	oFile.HT_vClose();

	return ( HT_OK );
}

//-------------------------------------------------------------------------------------
// HTRESULT				HT_hrLoadMapAreaIndicator( CHTString& strFile )
// D : 지역표시 정보 로드
// I : strFile - 지역이 표시되어 있는 맵에 해당하는 파일이름
// R : HT_TRUE/HT_FALSE
//-------------------------------------------------------------------------------------
HTRESULT				
CHTMapSystem::HT_hrLoadMapAreaIndicator( CHTString& strFile )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	HTint iVersion;

	CHTString strBuf;
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );	// read version
	
	if ( strBuf == _T("[VERSION_1001]") )
		iVersion = 1001;
	else if ( strBuf == _T("[VERSION_1002]") )
		iVersion = 1002;
	else
		iVersion = 0;

	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	HTint iAreaCount = atoi( strBuf );

	HTAreaIndicate* pArea = HT_NULL;

	for ( HTint i = 0; i < iAreaCount; i++ )
	{
		pArea = new HTAreaIndicate;
		ZeroMemory(pArea, sizeof (HTAreaIndicate));
		
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pArea->rcArea.fLeft = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pArea->rcArea.fBottom = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pArea->rcArea.fRight = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pArea->rcArea.fTop = strBuf.HT_fToFloat();
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		pArea->dwAreaID = strBuf.HT_iToInt();

		m_vectorAreaIndicate.push_back( pArea );
	}

	oFile.HT_vClose();

	return ( HT_OK );
}

//----------------------------------------------------------
// HTRESULT				HT_hrSetIndicateArea()
// D : Area Indicate
// I : vecPos - 위치
// R : Indicated Area Number
//----------------------------------------------------------
HTint
CHTMapSystem::HT_iSetArea(HTvector3& vecPos)
{
	std::vector<HTAreaIndicate*>::iterator it = m_vectorAreaIndicate.begin();
	while ( it != m_vectorAreaIndicate.end() )
	{
		if ( vecPos.x > (*it)->rcArea.fLeft && vecPos.x < (*it)->rcArea.fRight &&
			vecPos.z > (*it)->rcArea.fBottom && vecPos.z < (*it)->rcArea.fTop )
		{
			m_iAreaID = (*it)->dwAreaID;
			return m_iAreaID;
		}
		it++;
	}
	m_iAreaID = -1;
	return m_iAreaID;
}

HTRESULT				 
CHTMapSystem::HT_hrNotifySoundMove( HTbool bDay, HTvector3& vecPos )
{
	m_setAfterAmbientSoundIDs.clear();

	std::vector<HTSoundSpaceNode*>::iterator it = m_vectorSoundSpaces.begin();
	while ( it != m_vectorSoundSpaces.end() )
	{
		if ( vecPos.x > (*it)->rcArea.fLeft && vecPos.x < (*it)->rcArea.fRight &&
			vecPos.z > (*it)->rcArea.fBottom && vecPos.z < (*it)->rcArea.fTop )
		{
			if ( (*it)->dwBGMID != m_dwBGMID )
			{
				m_dwBGMID = (*it)->dwBGMID;
				//g_pEngineHandler->HT_hrPlaySound( m_dwBGMID, -1 );
			}

			if ( bDay )
			{
				std::vector<HTdword>::iterator itToPlaySound = (*it)->vectorDaySounds.begin();
				while ( itToPlaySound != (*it)->vectorDaySounds.end() )
				{
					m_setAfterAmbientSoundIDs.insert( (*itToPlaySound) );
					itToPlaySound++;
				}
			}
			else
			{
				std::vector<HTdword>::iterator itToPlaySound = (*it)->vectorNightSounds.begin();
				while ( itToPlaySound != (*it)->vectorNightSounds.end() )
				{
					m_setAfterAmbientSoundIDs.insert( (*itToPlaySound) );
					itToPlaySound++;
				}
			}

			if ( (*it)->iRoomType != m_iRoomType && (*it)->iRoomType != 0 )
			{
				m_iRoomType = (*it)->iRoomType;
				g_pEngineHandler->HT_hrSetSoundRoomType( m_iRoomType );
			}
		}

		it++;
	}

	HSAMPLE hSound;
	std::set<HTdword> setDiff;
	std::set<HTdword>::iterator itDiff;
	setDiff.clear();
	// 앞으로 플레이해야할 사운드들이다.
	set_difference( m_setAfterAmbientSoundIDs.begin(), m_setAfterAmbientSoundIDs.end(),
		m_setBeforeAmbientSoundIDs.begin(), m_setBeforeAmbientSoundIDs.end(), inserter( setDiff, setDiff.begin() ) );
	itDiff = setDiff.begin();
	while ( itDiff != setDiff.end() )
	{
		m_p3DMgr->HT_hrPlaySound( *itDiff, 0, HTvector3(0.0f,0.0f,0.0f), HT_NULL, &hSound );
		m_mapAmbientSampleHandles.insert( std::map<HTdword,HSAMPLE>::value_type( *itDiff, hSound ) );
		m_setCurrentAmbientSoundIDs.insert( *itDiff );
		itDiff++;
	}

	setDiff.clear();
	// 전에 틀었는데 없어져야할 사운드들이다.
	set_difference( m_setBeforeAmbientSoundIDs.begin(), m_setBeforeAmbientSoundIDs.end(),
		m_setAfterAmbientSoundIDs.begin(), m_setAfterAmbientSoundIDs.end(), inserter( setDiff, setDiff.begin() ) );
	itDiff = setDiff.begin();
	while ( itDiff != setDiff.end() )
	{
		std::map<HTdword,HSAMPLE>::iterator itSample = m_mapAmbientSampleHandles.find( *itDiff );
		if ( itSample != m_mapAmbientSampleHandles.end() )
		{
			m_p3DMgr->HT_hrStopSound( itSample->second );
			m_mapAmbientSampleHandles.erase( itSample );
			m_setCurrentAmbientSoundIDs.erase( *itDiff );
		}

		itDiff++;
	}

	m_setBeforeAmbientSoundIDs.clear();
	m_setBeforeAmbientSoundIDs.insert( m_setAfterAmbientSoundIDs.begin(), m_setAfterAmbientSoundIDs.end() );

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrSaveDLMap( CHTString& strFile, std::vector<HTdword>& vectorModelIDs, std::vector<HTdword>& vectorAniIDs )
{
	// 먼저 일반 오브젝트와 SM오브젝트의 아이디를 정리하여 DLMap에 넣는다.
	m_ppDLMap = new std::set<HTdword>*[HT_MAPNODE_NUM];
	HT_ASSERT( m_ppMap != HT_NULL );

	std::set<HTint>::iterator itObjs;

	for ( HTint i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		m_ppDLMap[i] = new std::set<HTdword>[HT_MAPNODE_NUM];
		HT_ASSERT( m_ppDLMap[i] != HT_NULL );

		for ( HTint j = 0; j < HT_MAPNODE_NUM; j++ )
		{
			m_ppDLMap[i][j].clear();

			m_ppDLMap[i][j].insert( m_ppMap[i][j].m_setObjects.begin(), m_ppMap[i][j].m_setObjects.end() );
			m_ppDLMap[i][j].insert( m_ppMap[i][j].m_setSMObjects.begin(), m_ppMap[i][j].m_setSMObjects.end() );
		}
	}

	// 그 다음에 풀 오브젝트들을 DLMap에 넣는다.
	for ( i = 0; i < HT_GRASSMAPNODE_NUM; i++ )
	{
		for ( HTint j = 0; j < HT_GRASSMAPNODE_NUM; j++ )
		{
			itObjs = m_ppGrassMap[j][i].m_setObjects.begin();
			while ( itObjs != m_ppGrassMap[j][i].m_setObjects.end() )
			{
				m_ppDLMap[i/4][j/4].insert( m_ppGrassMap[j][i].m_setObjects.begin(), m_ppGrassMap[j][i].m_setObjects.end() );
				itObjs++;
			}
		}
	}

	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	// 먼저 DLMap을 저장한다.
	std::set<HTdword>::iterator itDLMap;
	for ( i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		for ( HTint j = 0; j < HT_MAPNODE_NUM; j++ )
		{
			oFile.HT_bWrite( (HTint)m_ppDLMap[i][j].size() );
			itDLMap = m_ppDLMap[i][j].begin();
			while ( itDLMap != m_ppDLMap[i][j].end() )
			{
				oFile.HT_bWrite( (HTint)(*itDLMap) );
				itDLMap++;
			}
		}
	}

	HTmatrix matTransform;
	// 이번에는 박혀진 상태의 오브젝트에 대해 저장을 해 놓는다. 이렇게 하면 다음 로딩때 어떤 노드에 박힐지에 대한
	// 계산을 안 해도 되기 때문이다.
	std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itSaveObjs = m_mapSaveObjs.begin();
	oFile.HT_bWrite( (HTint)m_mapSaveObjs.size() );

	while ( itSaveObjs != m_mapSaveObjs.end() )
	{
		oFile.HT_bWrite( (HTint)(itSaveObjs->first) );

		if ( itSaveObjs->second )
		{
			oFile.HT_bWrite( (HTbyte)(itSaveObjs->second->bGrass) );
			oFile.HT_bWrite( (HTint)(itSaveObjs->second->dwResID) );
			oFile.HT_bWrite( (HTint)(itSaveObjs->second->vectorNodes.size()) );
			std::vector<HT_MAP_INT2DCOORD>::iterator itNodes = itSaveObjs->second->vectorNodes.begin();
			while ( itNodes != itSaveObjs->second->vectorNodes.end() )
			{
				oFile.HT_bWrite( (HTint)((*itNodes).iX) );
				oFile.HT_bWrite( (HTint)((*itNodes).iZ) );
				itNodes++;
			}
			matTransform = itSaveObjs->second->matTransform;
			oFile.HT_bWrite( matTransform._11 );oFile.HT_bWrite( matTransform._12 );oFile.HT_bWrite( matTransform._13 );oFile.HT_bWrite( matTransform._14 );
			oFile.HT_bWrite( matTransform._21 );oFile.HT_bWrite( matTransform._22 );oFile.HT_bWrite( matTransform._23 );oFile.HT_bWrite( matTransform._24 );
			oFile.HT_bWrite( matTransform._31 );oFile.HT_bWrite( matTransform._32 );oFile.HT_bWrite( matTransform._33 );oFile.HT_bWrite( matTransform._34 );
			oFile.HT_bWrite( matTransform._41 );oFile.HT_bWrite( matTransform._42 );oFile.HT_bWrite( matTransform._43 );oFile.HT_bWrite( matTransform._44 );
			oFile.HT_bWrite( &itSaveObjs->second->oProperty, sizeof(HT_EOBJ_PROPERTY) );
		}

		itSaveObjs++;
	}

	oFile.HT_bWrite( (HTint)vectorModelIDs.size() );
	std::vector<HTdword>::iterator itModelIDs = vectorModelIDs.begin();
	while ( itModelIDs != vectorModelIDs.end() )
	{
		oFile.HT_bWrite( (HTint)(*itModelIDs) );
		itModelIDs++;
	}

	oFile.HT_bWrite( (HTint)vectorAniIDs.size() );
	std::vector<HTdword>::iterator itAniIDs = vectorAniIDs.begin();
	while ( itAniIDs != vectorAniIDs.end() )
	{
		oFile.HT_bWrite( (HTint)(*itAniIDs) );
		itAniIDs++;
	}

	oFile.HT_vClose();

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrLoadDLMap( CHTString& strFile, std::vector<HTdword>& vectorModelIDs, std::vector<HTdword>& vectorAniIDs )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	m_ppDLMap = new std::set<HTdword>*[HT_MAPNODE_NUM];
	HT_ASSERT( m_ppMap != HT_NULL );

	HTint iCount, iReadBuf;
	std::set<HTdword>::iterator itDLMap;
	for ( HTint i = 0; i < HT_MAPNODE_NUM; i++ )
	{
		m_ppDLMap[i] = new std::set<HTdword>[HT_MAPNODE_NUM];
		HT_ASSERT( m_ppDLMap[i] != HT_NULL );

		for ( HTint j = 0; j < HT_MAPNODE_NUM; j++ )
		{
			oFile.HT_bRead( &iCount );
			for ( HTint k = 0; k < iCount; k++ )
			{
				oFile.HT_bRead( &iReadBuf );
				m_ppDLMap[i][j].insert( iReadBuf );
			}
		}
	}

	HTmatrix matTransform;
	HTbyte byReadBuf;
	HTint iTempCount, iTempX, iTempZ, iResID;
	HT_MAP_SAVEOBJ* pSaveObj;

	oFile.HT_bRead( &iCount );

	HTint idObj;
	for ( i = 0; i < iCount; i++ )
	{
		pSaveObj = new HT_MAP_SAVEOBJ;

		oFile.HT_bRead( &idObj );

		oFile.HT_bRead( &byReadBuf );	// grass or not
		if ( byReadBuf ) pSaveObj->bGrass = 1;
		else pSaveObj->bGrass = 0;
		oFile.HT_bRead( &iResID );
		pSaveObj->dwResID = iResID;

		oFile.HT_bRead( &iTempCount );
		pSaveObj->vectorNodes.clear();
		for ( HTint j = 0; j < iTempCount; j++ )
		{
			oFile.HT_bRead( &iTempX );
			oFile.HT_bRead( &iTempZ );
			pSaveObj->vectorNodes.push_back( HT_MAP_INT2DCOORD( iTempX, iTempZ ) );
		}
		oFile.HT_bRead( &matTransform._11 );oFile.HT_bRead( &matTransform._12 );oFile.HT_bRead( &matTransform._13 );oFile.HT_bRead( &matTransform._14 );
		oFile.HT_bRead( &matTransform._21 );oFile.HT_bRead( &matTransform._22 );oFile.HT_bRead( &matTransform._23 );oFile.HT_bRead( &matTransform._24 );
		oFile.HT_bRead( &matTransform._31 );oFile.HT_bRead( &matTransform._32 );oFile.HT_bRead( &matTransform._33 );oFile.HT_bRead( &matTransform._34 );
		oFile.HT_bRead( &matTransform._41 );oFile.HT_bRead( &matTransform._42 );oFile.HT_bRead( &matTransform._43 );oFile.HT_bRead( &matTransform._44 );
		pSaveObj->matTransform = matTransform;
		oFile.HT_bRead( &pSaveObj->oProperty, sizeof(HT_EOBJ_PROPERTY) );

		// 나머지 초기화
		pSaveObj->idDayFX = 0;
		pSaveObj->idNightFX = 0;
		pSaveObj->idRenewal = 0;

		m_mapSaveObjs.insert( std::map<HTint,HT_MAP_SAVEOBJ*>::value_type( idObj, pSaveObj ) );
	}

	oFile.HT_bRead( &iCount );
	for ( i = 0; i < iCount; i++ )
	{
		oFile.HT_bRead( &iTempX );
		vectorModelIDs.push_back( iTempX );
	}
	
	oFile.HT_bRead( &iCount );
	for ( i = 0; i < iCount; i++ )
	{
		oFile.HT_bRead( &iTempX );
		vectorAniIDs.push_back( iTempX );
	}

	oFile.HT_vClose();

	// HPVS 처리 => 위치에 따라 생성할 오브젝트들을 HPVS Node에 박아놓는다.
	if ( m_bHPVSMode )
	{
		std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itSaveObj = m_mapSaveObjs.begin();
		HTint iX, iZ;
		while ( itSaveObj != m_mapSaveObjs.end() )
		{
			if ( itSaveObj->second )
			{
				iX = (HTint)floorf( itSaveObj->second->matTransform._41 / m_fHPVSGridSize );
				iZ = (HTint)floorf( itSaveObj->second->matTransform._43 / m_fHPVSGridSize );

				if ( iX >= 0 && iX < m_iHPVSNodeCountX && iZ >= 0 && iZ < m_iHPVSNodeCountZ )
				{
					m_ppHPVS[iZ][iX].setObjectIDs.insert( itSaveObj->first );
					m_ppHPVS[iZ][iX].setResIDs.insert( itSaveObj->second->dwResID );
				}
			}
			itSaveObj++;
		}
	}

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrInsertObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes )
{
	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;

	std::vector<HT_MAP_INT2DCOORD>::iterator it = vectorNodes.begin();
	while ( it != vectorNodes.end() )
	{
		m_ppMap[(*it).iX][(*it).iZ].m_setObjects.insert( idObj );
		pRememberNode->vectorMapNodes.push_back( &m_ppMap[(*it).iX][(*it).iZ] );
		it++;
	}

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrInsertGrassObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes )
{
	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;
	std::vector<HT_MAP_INT2DCOORD>::iterator it = vectorNodes.begin();
	while ( it != vectorNodes.end() )
	{
		m_ppGrassMap[(*it).iX][(*it).iZ].m_setObjects.insert( idObj );
		pRememberNode->vectorMapNodes.push_back( &m_ppGrassMap[(*it).iX][(*it).iZ] );
		it++;
	}

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrInsertSMObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes )
{
	HT_MAP_REMEMBEROBJ* pRememberNode = new HT_MAP_REMEMBEROBJ;

	std::vector<HT_MAP_INT2DCOORD>::iterator it = vectorNodes.begin();
	while ( it != vectorNodes.end() )
	{
		m_ppMap[(*it).iX][(*it).iZ].m_setSMObjects.insert( idObj );
		pRememberNode->vectorMapNodes.push_back( &m_ppMap[(*it).iX][(*it).iZ] );
		it++;
	}

	m_hashmapObjects.insert( std::map<HTint, HT_MAP_REMEMBEROBJ*>::value_type( idObj, pRememberNode ) ); 

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrGetIDToLoad( HTvector3& vecPos, HTfloat fCamFarZ, std::set<HTint>& setToLoad, 
							   std::set<HTint>& setToUnload, std::set<HTint>& setToCreate, std::set<HTint>& setToDestroy )
{
	HTint iStartX, iStartZ, iRadius;
	std::map<HTint,HT_MAP_SAVEOBJ*>::iterator itSaveObj;
	std::set<HTdword> setCurrent;
	std::set<HTint> setCurrentCreated;
	setCurrent.clear();
	setCurrentCreated.clear();
	std::set<HTdword>::iterator itDLMap;

	if ( m_bHPVSMode )	// HPVS 의 경우는 따로 처리한다.
	{
		HTint iX, iZ;
		iX = (HTint)floorf(vecPos.x / m_fHPVSGridSize);
		iZ = (HTint)floorf(vecPos.z / m_fHPVSGridSize);
		iRadius = (HTint)(m_fHPVSGridSize / 160.0f);

		if ( iX >= 0 && iX < m_iHPVSNodeCountX && iZ >= 0 && iZ < m_iHPVSNodeCountZ )
		{
			setCurrent.insert( m_ppHPVS[iZ][iX].setResIDs.begin(), m_ppHPVS[iZ][iX].setResIDs.end() );
			setCurrentCreated.insert( m_ppHPVS[iZ][iX].setObjectIDs.begin(), m_ppHPVS[iZ][iX].setObjectIDs.end() );

			std::list<HTint>::iterator it = m_ppHPVS[iZ][iX].listViewingNodes.begin();
			while ( it != m_ppHPVS[iZ][iX].listViewingNodes.end() )
			{
				iStartX = (*it) % m_iHPVSNodeCountX;
				iStartZ = (*it) / m_iHPVSNodeCountZ;

				setCurrent.insert( m_ppHPVS[iStartZ][iStartX].setResIDs.begin(), m_ppHPVS[iStartZ][iStartX].setResIDs.end() );
				setCurrentCreated.insert( m_ppHPVS[iStartZ][iStartX].setObjectIDs.begin(), m_ppHPVS[iStartZ][iStartX].setObjectIDs.end() );

				it++;
			}
		}
	}
	else
	{
		iStartX = (HTint)(vecPos.x / 160.0f);		// 여기서 160.0이란 로딩노드가 한 칸이 16m = 160.0 이기때문이지
		iStartZ = (HTint)(vecPos.z / 160.0f);
		iRadius = (HTint)(fCamFarZ / 160.0f);

		for ( HTint i = iStartZ - iRadius; i <= iStartZ + iRadius; i++ )
		{
			for ( HTint j = iStartX - iRadius; j <= iStartX + iRadius; j++ )
			{
				if ( i >= 0 && j >= 0 && i < HT_MAPNODE_NUM && j < HT_MAPNODE_NUM )
				{
					itDLMap = m_ppDLMap[i][j].begin();
					while ( itDLMap != m_ppDLMap[i][j].end() )
					{
						itSaveObj = m_mapSaveObjs.find( *itDLMap );
						if ( itSaveObj != m_mapSaveObjs.end() && itSaveObj->second )
						{
							setCurrent.insert( itSaveObj->second->dwResID );
							setCurrentCreated.insert( *itDLMap );
						}
						itDLMap++;
					}
				}
			}
		}
	}

	// 로드할 그리고 언로드할 리소스 아이디에 대한 분류 작업
	setToLoad.clear();
	set_difference( setCurrent.begin(), setCurrent.end(),
		m_setLoadedObjIDs.begin(), m_setLoadedObjIDs.end(), inserter( setToLoad, setToLoad.begin() ) );

	setToUnload.clear();
	set_difference( m_setLoadedObjIDs.begin(), m_setLoadedObjIDs.end(),
		setCurrent.begin(), setCurrent.end(), inserter( setToUnload, setToUnload.begin() ) );

	m_setLoadedObjIDs.clear();
	m_setLoadedObjIDs.insert( setCurrent.begin(), setCurrent.end() );

	// 생성할 그리고 소멸할 엔진 오브젝트에 대한 분류작업
	setToCreate.clear();
	set_difference( setCurrentCreated.begin(), setCurrentCreated.end(),
		m_setCreatedObjIDs.begin(), m_setCreatedObjIDs.end(), inserter( setToCreate, setToCreate.begin() ) );

	setToDestroy.clear();
	set_difference( m_setCreatedObjIDs.begin(), m_setCreatedObjIDs.end(),
		setCurrentCreated.begin(), setCurrentCreated.end(), inserter( setToDestroy, setToDestroy.begin() ) );

	m_setCreatedObjIDs.clear();
	m_setCreatedObjIDs.insert( setCurrentCreated.begin(), setCurrentCreated.end() );

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrLoadMapHPVS( CHTString& strFile )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	HTint iVersion;

	CHTString strBuf;
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );	// read version
	
	if ( strBuf == _T("[VERSION_1001]") )
		iVersion = 1001;
	else if ( strBuf == _T("[VERSION_1002]") )
		iVersion = 1002;
	else
		iVersion = 0;

	oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
	m_iHPVSNodeCountX = strBuf.HT_iToInt();
	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	m_iHPVSNodeCountZ = strBuf.HT_iToInt();

	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	m_fHPVSGridSize = strBuf.HT_fToFloat();

	m_ppHPVS = new HT_MAP_HPVSNODE*[m_iHPVSNodeCountZ];

	HTint iCount;
	for ( HTint i = 0; i < m_iHPVSNodeCountZ; i++ )
	{
		m_ppHPVS[i] = new HT_MAP_HPVSNODE[m_iHPVSNodeCountX];

		for ( HTint j = 0; j < m_iHPVSNodeCountX; j++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );

			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			iCount = strBuf.HT_iToInt();
			for ( HTint k = 0; k < iCount; k++ )
			{
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				m_ppHPVS[i][j].listViewingNodes.push_back( strBuf.HT_iToInt() );
			}
		}
	}

	oFile.HT_vClose();

	m_bHPVSMode = HT_TRUE;

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrLoadMapBound( CHTString& strFile )
{
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	CHTString strBuf;

	oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
	HTint iColObjCount = strBuf.HT_iToInt();

	HTint idBDPlane = 0;
	HTint idBDBox = 0;
	HTint idBDCylinder = 0;
	HTint idBoundObj = 0;

	HTBoundPlane* pBPlane;
	HTBoundBox* pBBox;
	HTBoundCylinder* pBCylinder;

	std::set<HTint> setOnlyNewPlane;
	std::set<HTint> setOnlyNewBox;
	std::set<HTint> setOnlyNewCylinder;

	for ( HTint i = 0; i < iColObjCount; i++ )
	{
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		HTint iPrimCount = strBuf.HT_iToInt();

		setOnlyNewPlane.clear();
		setOnlyNewBox.clear();
		setOnlyNewCylinder.clear();

		for ( HTint j = 0; j < iPrimCount; j++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			HTint iType = strBuf.HT_iToInt();

			switch ( iType ) 
			{
			case HT_BOUNDPRIM_PLANE:
				pBPlane = new HTBoundPlane;

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[0].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[0].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBPlane->vecPoint[0].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[1].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[1].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBPlane->vecPoint[1].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[2].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[2].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBPlane->vecPoint[2].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[3].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBPlane->vecPoint[3].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBPlane->vecPoint[3].z = strBuf.HT_fToFloat();

				setOnlyNewPlane.insert( idBDPlane );

				m_mapBoundDataPlane.insert( std::map<HTint,HTBoundPlane*>::value_type( idBDPlane++, pBPlane ) );

				break;

			case HT_BOUNDPRIM_BOX:
				pBBox = new HTBoundBox;

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[0].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[0].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[0].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[1].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[1].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[1].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[2].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[2].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[2].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[3].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[3].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[3].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[4].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[4].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[4].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[5].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[5].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[5].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[6].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[6].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[6].z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[7].x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBBox->vecPoint[7].y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBBox->vecPoint[7].z = strBuf.HT_fToFloat();

				setOnlyNewBox.insert( idBDBox );

				m_mapBoundDataBox.insert( std::map<HTint,HTBoundBox*>::value_type( idBDBox++, pBBox ) );
				break;

			case HT_BOUNDPRIM_CYLINDER:
				pBCylinder = new HTBoundCylinder;

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBCylinder->vecBottomCenter.x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBCylinder->vecBottomCenter.y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBCylinder->vecBottomCenter.z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBCylinder->vecTopCenter.x = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
				pBCylinder->vecTopCenter.y = strBuf.HT_fToFloat();
				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBCylinder->vecTopCenter.z = strBuf.HT_fToFloat();

				oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
				pBCylinder->fRadius = strBuf.HT_fToFloat();

				setOnlyNewCylinder.insert( idBDCylinder );

				m_mapBoundDataCylinder.insert( std::map<HTint,HTBoundCylinder*>::value_type( idBDCylinder++, pBCylinder ) );
				break;

			default:
				MessageBox(NULL,"HT_hrLoadMapBound","Unknown Bounding Primitive!",MB_OK);
				break;
			}
		}

		HTmatrix matRead;
		oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
		HTint iMatrixCount = strBuf.HT_iToInt();
		for ( HTint k = 0; k < iMatrixCount; k++ )
		{
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._11 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._12 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._13 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			matRead._14 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._21 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._22 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._23 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			matRead._24 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._31 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._32 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._33 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			matRead._34 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._41 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._42 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, ' ' );
			matRead._43 = strBuf.HT_fToFloat();
			oFile.HT_bReadString( strBuf, HT_MAX_STR, '\n' );
			matRead._44 = strBuf.HT_fToFloat();

			HTBoundObj* pBoundObj;

			std::set<HTint>::iterator itOnlyNew;
			itOnlyNew = setOnlyNewPlane.begin();
			while ( itOnlyNew != setOnlyNewPlane.end() )
			{
				std::map<HTint,HTBoundPlane*>::iterator itPlane = m_mapBoundDataPlane.find( *itOnlyNew );
				if ( itPlane != m_mapBoundDataPlane.end() )
				{
					pBoundObj = new HTBoundObj;
					pBoundObj->eType = HT_BOUNDPRIM_PLANE;
					pBoundObj->matTransform = matRead;
					pBoundObj->idBoundData = itPlane->first;

					m_mapBoundObjs.insert( std::map<HTint,HTBoundObj*>::value_type( idBoundObj, pBoundObj ) );

					HT_hrInsertBoundPlane( idBoundObj, pBoundObj );

					idBoundObj++;
				}
				itOnlyNew++;
			}

			itOnlyNew = setOnlyNewBox.begin();
			while ( itOnlyNew != setOnlyNewBox.end() )
			{
				std::map<HTint,HTBoundBox*>::iterator itBox = m_mapBoundDataBox.find( *itOnlyNew );
				if ( itBox != m_mapBoundDataBox.end() )
				{
					pBoundObj = new HTBoundObj;
					pBoundObj->eType = HT_BOUNDPRIM_BOX;
					pBoundObj->matTransform = matRead;
					pBoundObj->idBoundData = itBox->first;

					m_mapBoundObjs.insert( std::map<HTint,HTBoundObj*>::value_type( idBoundObj, pBoundObj ) );

					HT_hrInsertBoundBox( idBoundObj, pBoundObj );

					idBoundObj++;
				}
				itOnlyNew++;
			}

			itOnlyNew = setOnlyNewCylinder.begin();
			while ( itOnlyNew != setOnlyNewCylinder.end() )
			{
				std::map<HTint,HTBoundCylinder*>::iterator itCylinder = m_mapBoundDataCylinder.find( *itOnlyNew );
				if ( itCylinder != m_mapBoundDataCylinder.end() )
				{
					pBoundObj = new HTBoundObj;
					pBoundObj->eType = HT_BOUNDPRIM_CYLINDER;
					pBoundObj->matTransform = matRead;
					pBoundObj->idBoundData = itCylinder->first;

					m_mapBoundObjs.insert( std::map<HTint,HTBoundObj*>::value_type( idBoundObj, pBoundObj ) );

					HT_hrInsertBoundCylinder( idBoundObj, pBoundObj );

					idBoundObj++;
				}
				itOnlyNew++;
			}
		}
	}

	oFile.HT_vClose();

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrInsertBoundPlane( HTint idBoundObj, HTBoundObj* pBoundObj )
{
	if ( pBoundObj && pBoundObj->eType == HT_BOUNDPRIM_PLANE )
	{
		std::map<HTint,HTBoundPlane*>::iterator it = m_mapBoundDataPlane.find( pBoundObj->idBoundData );
		if ( it != m_mapBoundDataPlane.end() )
		{
			if ( it->second )
			{
				HTvector3 arrvecPlane[4] = 
				{
					HTvector3(it->second->vecPoint[0].x, it->second->vecPoint[0].y, it->second->vecPoint[0].z),
					HTvector3(it->second->vecPoint[1].x, it->second->vecPoint[1].y, it->second->vecPoint[1].z),
					HTvector3(it->second->vecPoint[2].x, it->second->vecPoint[2].y, it->second->vecPoint[2].z),	
					HTvector3(it->second->vecPoint[3].x, it->second->vecPoint[3].y, it->second->vecPoint[3].z),	
				};

				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[0], &arrvecPlane[0], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[1], &arrvecPlane[1], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[2], &arrvecPlane[2], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[3], &arrvecPlane[3], &(pBoundObj->matTransform) );

				HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
				fMinX = arrvecPlane[0].x;	fMinZ = arrvecPlane[0].z;
				fMaxX = arrvecPlane[0].x;	fMaxZ = arrvecPlane[0].z;

				HTint i, j;
				for ( i = 1; i < 4; i++ )
				{
					if ( arrvecPlane[i].x < fMinX )	fMinX = arrvecPlane[i].x;
					if ( arrvecPlane[i].z < fMinZ )	fMinZ = arrvecPlane[i].z;
					if ( arrvecPlane[i].x > fMaxX )	fMaxX = arrvecPlane[i].x;
					if ( arrvecPlane[i].z > fMaxZ )	fMaxZ = arrvecPlane[i].z;
				}
				
				HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
				HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
				HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
				HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

				for ( i = iMinZ; i <= iMaxZ; i++ )
				{
					for ( j = iMinX; j <= iMaxX; j++ )
					{
						if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
							continue;

						m_ppMap[i][j].m_vectorBoundObjs.push_back( idBoundObj );
					}
				}
				return ( HT_OK );
			}
		}
	}

	return ( HT_FAIL );
}

HTRESULT				
CHTMapSystem::HT_hrInsertBoundBox( HTint idBoundObj, HTBoundObj* pBoundObj )
{
	if ( pBoundObj && pBoundObj->eType == HT_BOUNDPRIM_BOX )
	{
		std::map<HTint,HTBoundBox*>::iterator it = m_mapBoundDataBox.find( pBoundObj->idBoundData );
		if ( it != m_mapBoundDataBox.end() )
		{
			if ( it->second )
			{
				HTvector3 arrvecPlane[8] = 
				{
					HTvector3(it->second->vecPoint[0].x, it->second->vecPoint[0].y, it->second->vecPoint[0].z),
					HTvector3(it->second->vecPoint[1].x, it->second->vecPoint[1].y, it->second->vecPoint[1].z),
					HTvector3(it->second->vecPoint[2].x, it->second->vecPoint[2].y, it->second->vecPoint[2].z),	
					HTvector3(it->second->vecPoint[3].x, it->second->vecPoint[3].y, it->second->vecPoint[3].z),	
					HTvector3(it->second->vecPoint[4].x, it->second->vecPoint[4].y, it->second->vecPoint[4].z),	
					HTvector3(it->second->vecPoint[5].x, it->second->vecPoint[5].y, it->second->vecPoint[5].z),	
					HTvector3(it->second->vecPoint[6].x, it->second->vecPoint[6].y, it->second->vecPoint[6].z),	
					HTvector3(it->second->vecPoint[7].x, it->second->vecPoint[7].y, it->second->vecPoint[7].z),	
				};

				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[0], &arrvecPlane[0], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[1], &arrvecPlane[1], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[2], &arrvecPlane[2], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[3], &arrvecPlane[3], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[4], &arrvecPlane[4], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[5], &arrvecPlane[5], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[6], &arrvecPlane[6], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[7], &arrvecPlane[7], &(pBoundObj->matTransform) );

				HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
				fMinX = arrvecPlane[0].x;	fMinZ = arrvecPlane[0].z;
				fMaxX = arrvecPlane[0].x;	fMaxZ = arrvecPlane[0].z;

				HTint i, j;
				for ( i = 1; i < 8; i++ )
				{
					if ( arrvecPlane[i].x < fMinX )	fMinX = arrvecPlane[i].x;
					if ( arrvecPlane[i].z < fMinZ )	fMinZ = arrvecPlane[i].z;
					if ( arrvecPlane[i].x > fMaxX )	fMaxX = arrvecPlane[i].x;
					if ( arrvecPlane[i].z > fMaxZ )	fMaxZ = arrvecPlane[i].z;
				}
				
				HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
				HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
				HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
				HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

				for ( i = iMinZ; i <= iMaxZ; i++ )
				{
					for ( j = iMinX; j <= iMaxX; j++ )
					{
						if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
							continue;

						m_ppMap[i][j].m_vectorBoundObjs.push_back( idBoundObj );
					}
				}
				return ( HT_OK );
			}
		}
	}

	return ( HT_FAIL );
}

HTRESULT				
CHTMapSystem::HT_hrInsertBoundCylinder( HTint idBoundObj, HTBoundObj* pBoundObj )
{
	if ( pBoundObj && pBoundObj->eType == HT_BOUNDPRIM_CYLINDER )
	{
		std::map<HTint,HTBoundCylinder*>::iterator it = m_mapBoundDataCylinder.find( pBoundObj->idBoundData );
		if ( it != m_mapBoundDataCylinder.end() )
		{
			if ( it->second )
			{
				HTvector3 arrvecPlane[2] = 
				{
					HTvector3(it->second->vecBottomCenter.x, it->second->vecBottomCenter.y, it->second->vecBottomCenter.z),
					HTvector3(it->second->vecTopCenter.x, it->second->vecTopCenter.y, it->second->vecTopCenter.z),
				};

				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[0], &arrvecPlane[0], &(pBoundObj->matTransform) );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[1], &arrvecPlane[1], &(pBoundObj->matTransform) );

				HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
				HTint i, j;
				if ( arrvecPlane[0].x < arrvecPlane[1].x )	
				{
					fMinX = arrvecPlane[0].x;	fMaxX = arrvecPlane[1].x;
				}
				else
				{
					fMinX = arrvecPlane[1].x;	fMaxX = arrvecPlane[0].x;
				}
				if ( arrvecPlane[0].z < arrvecPlane[1].z )	
				{
					fMinZ = arrvecPlane[0].z;	fMaxZ = arrvecPlane[1].z;
				}
				else
				{
					fMinZ = arrvecPlane[1].z;	fMaxZ = arrvecPlane[0].z;
				}

				fMinX -= (HT_ROOT_2*(it->second->fRadius));
				fMaxX += (HT_ROOT_2*(it->second->fRadius));
				fMinZ -= (HT_ROOT_2*(it->second->fRadius));
				fMaxZ += (HT_ROOT_2*(it->second->fRadius));
				
				HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
				HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
				HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
				HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

				for ( i = iMinZ; i <= iMaxZ; i++ )
				{
					for ( j = iMinX; j <= iMaxX; j++ )
					{
						if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
							continue;

						m_ppMap[i][j].m_vectorBoundObjs.push_back( idBoundObj );
					}
				}
				return ( HT_OK );
			}
		}
	}

	return ( HT_FAIL );
}

HTRESULT				
CHTMapSystem::HT_hrMoveObject( HTint idObj, HTvector3& vecStartPos, HTfloat fRadius, HTvector3& vecTargetPos, HTvector3& vecNextpos )
{
	vecNextpos = vecStartPos;

	// 맵 노드에서 일단 뺀다.
	HT_hrDeleteObject( idObj, HT_OBJSIZE_NONE, 0 );

	//----------------------------------------------------------------------
	// 충돌을 계산한다.
	HTbool bCollided = HT_FALSE;

	// 먼저 가고자 하는 위치에 해당하는 맵 노드들에 속한 충돌오브젝트 리스트를 가져온다.
	std::set<HTint> setBoundObjs;
	setBoundObjs.clear();

	// 먼저 가고자 하는 위치에 해당하는 맵 노드들에 속한 충돌오브젝트 리스트를 가져온다.
	// ray의 중심점이 포함된 노드를 중심으로 반경 얼마 안에 있는 것만 체크를 한다.
	// 그 영역은 갑작스런 이동이 없다고 가정하고, 일단 3*3 노드 즉 48m * 48m 로 정해놓는다.
	HTRay rRay;
	rRay.HT_hrInit( vecStartPos, vecTargetPos );

	HTint iCenterX = (HTint)floorf(rRay.m_vecStartPos.x / HT_MAPNODE_SIZE);
	HTint iCenterZ = (HTint)floorf(rRay.m_vecStartPos.z / HT_MAPNODE_SIZE);
	HTint iRadiusNode = 1;
	for ( HTint i = iCenterZ - iRadiusNode; i <= iCenterZ + iRadiusNode; i++ )
	{
		for ( HTint j = iCenterX - iRadiusNode; j <= iCenterX + iRadiusNode; j++ )
		{
			if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
				continue;

			if ( CHTIntersect::HT_bIsRayBoxIntersect( m_ppMap[i][j].m_boxArea.vecMin, m_ppMap[i][j].m_boxArea.vecMax, rRay ) )
			{
				setBoundObjs.insert( m_ppMap[i][j].m_vectorBoundObjs.begin(), m_ppMap[i][j].m_vectorBoundObjs.end() );
			}
		}
	}

	HTvector3 vecCollidedPos, vecFinalCollidedPos, vecFinalNextPos, vecOnceStartPos, vecOnceTargetPos;
	std::map<HTint,HTBoundObj*>::iterator itObj;
	if ( !setBoundObjs.empty() )
	{
		HTfloat fNearDist, fDist;
		HTbool bCollidedOnce;

		vecOnceStartPos = vecStartPos;
		vecOnceTargetPos = vecTargetPos;

		// 충돌이 일어나서 충돌점으로부터 튕겨진 점까지 가다가 충돌이 있을 수 있으므로, 충돌이 안 일어날때까지
		// 검사를 해야하지만, 무한루프에 빠질 위험이 있으며 성능에 영향을 줄 수 있으므로 3번까지만 검사한다.
		for ( HTint i = 0; i < 999; i++ )
		{
			fNearDist = FLT_MAX;
			bCollidedOnce = HT_FALSE;
			std::set<HTint>::iterator it = setBoundObjs.begin();
			while ( it != setBoundObjs.end() )
			{
				itObj = m_mapBoundObjs.find( *it );
				if ( itObj != m_mapBoundObjs.end() )
				{
					if ( itObj->second )
					{
						if ( HT_hrCheckCollision( vecOnceStartPos, fRadius, itObj->second, vecOnceTargetPos, vecNextpos, 
													vecCollidedPos ) == HT_RESULT_COLLISION_DETECTED )
						{
							// 여러개의 것과 충돌이 일어난 경우, 가장 가까운 곳에서 일어난 충돌을 기억한다.
							fDist = CHTVector::HT_fVec3Length(&(vecCollidedPos-vecOnceStartPos));
							if ( fDist < fNearDist )	
							{
								fNearDist = fDist;
								vecFinalCollidedPos = vecCollidedPos;
								vecFinalNextPos = vecNextpos;
								vecOnceStartPos = vecCollidedPos;
								vecOnceTargetPos = vecNextpos;
								bCollidedOnce = HT_TRUE;
								bCollided = HT_TRUE;
							}
						}
					}
					else
					{
					}
				}
				else
				{
				}
				it++;
			}

			if ( !bCollidedOnce )
			{
				break;
			}
		}
	}

	HT_AABB oAABB;
	HTmatrix matTransform;
	g_pEngineHandler->HT_hrGetBoundingBox( idObj, &oAABB, &matTransform );

	if ( !bCollided )
	{
		vecNextpos = vecTargetPos;
	}
	else
	{
		vecNextpos = vecFinalNextPos;
	}

	matTransform._41 = vecNextpos.x; matTransform._42 = vecNextpos.y; matTransform._43 = vecNextpos.z;

	// 이동된 위치로 맵 노드에 박는다.
	HT_hrInsertObject( idObj, &oAABB, &matTransform, HT_OBJSIZE_NONE, 0 );

	if ( bCollided )	return ( HT_RESULT_COLLISION_DETECTED );
	else				return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrRenderBoundObjs( HT_AABB* pBB, HTmatrix* pmatTrasform )
{
	if ( !pBB || !pmatTrasform )
	{
		return ( HT_FAIL );
	}

	std::set<HTint> setBoundObjs;
	setBoundObjs.clear();

	// AABB의 8점
	HTvector3 arrvecBox[8] = 
	{
		HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMin.z),
		HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMin.z),
		HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMin.z),	
		HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMin.z),	
		HTvector3(pBB->vecMin.x, pBB->vecMin.y, pBB->vecMax.z),	
		HTvector3(pBB->vecMax.x, pBB->vecMin.y, pBB->vecMax.z),	
		HTvector3(pBB->vecMin.x, pBB->vecMax.y, pBB->vecMax.z),
		HTvector3(pBB->vecMax.x, pBB->vecMax.y, pBB->vecMax.z),
	};

	// AABB->OBB의 8점을 계산한다.
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[0], &arrvecBox[0], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[1], &arrvecBox[1], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[2], &arrvecBox[2], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[3], &arrvecBox[3], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[4], &arrvecBox[4], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[5], &arrvecBox[5], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[6], &arrvecBox[6], pmatTrasform );
	CHTVector::HT_pvecVec3TransformCoord( &arrvecBox[7], &arrvecBox[7], pmatTrasform );

	// OBB의 8점을 2차원 평면에 투영 => y 값 무시
	// 투영된 8점을 가지고 2차원 AABB 계산
	HTfloat fMinX, fMinZ, fMaxX, fMaxZ;
	fMinX = arrvecBox[0].x;	fMinZ = arrvecBox[0].z;
	fMaxX = arrvecBox[0].x;	fMaxZ = arrvecBox[0].z;

	HTint i, j;
	for ( i = 1; i < 8; i++ )
	{
		if ( arrvecBox[i].x < fMinX )	fMinX = arrvecBox[i].x;
		if ( arrvecBox[i].z < fMinZ )	fMinZ = arrvecBox[i].z;
		if ( arrvecBox[i].x > fMaxX )	fMaxX = arrvecBox[i].x;
		if ( arrvecBox[i].z > fMaxZ )	fMaxZ = arrvecBox[i].z;
	}
	
	HTint iMinX = (HTint)floorf(fMinX / HT_MAPNODE_SIZE);
	HTint iMinZ = (HTint)floorf(fMinZ / HT_MAPNODE_SIZE);
	HTint iMaxX = (HTint)floorf(fMaxX / HT_MAPNODE_SIZE);
	HTint iMaxZ = (HTint)floorf(fMaxZ / HT_MAPNODE_SIZE);

	// 오브젝트의 2차원 AABB의 영역에 있는 맵 노드들과의 체크를 한다.
	for ( i = iMinZ; i <= iMaxZ; i++ )
	{
		for ( j = iMinX; j <= iMaxX; j++ )
		{
			if ( i < 0 || j < 0 || i >= HT_MAPNODE_NUM || j >= HT_MAPNODE_NUM )
				continue;

			setBoundObjs.insert( m_ppMap[i][j].m_vectorBoundObjs.begin(), m_ppMap[i][j].m_vectorBoundObjs.end() );
		}
	}

	if ( setBoundObjs.empty() )	// 충돌할 대상이 없는 것이다 
	{
	}
	else
	{
		std::map<HTint,HTBoundPlane*>::iterator itPlane;
		std::map<HTint,HTBoundBox*>::iterator itBox;
		std::map<HTint,HTBoundCylinder*>::iterator itCylinder;
		std::map<HTint,HTBoundObj*>::iterator itObj;
		HTBoundObj* pObj;

		std::set<HTint>::iterator it = setBoundObjs.begin();
		while ( it != setBoundObjs.end() )
		{
			itObj = m_mapBoundObjs.find( *it );
			if ( itObj != m_mapBoundObjs.end() )
			{
				if ( itObj->second )
				{
					pObj = itObj->second;
					switch ( pObj->eType )
					{
					case HT_BOUNDPRIM_PLANE:
						itPlane = m_mapBoundDataPlane.find( pObj->idBoundData );
						if ( itPlane != m_mapBoundDataPlane.end() )
						{
							if ( itPlane->second )
							{
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itPlane->second->vecPoint[0], itPlane->second->vecPoint[1], 
									itPlane->second->vecPoint[3], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itPlane->second->vecPoint[0], itPlane->second->vecPoint[3], 
									itPlane->second->vecPoint[2], pObj->matTransform );
							}
						}
						break;
					case HT_BOUNDPRIM_BOX:
						itBox = m_mapBoundDataBox.find( pObj->idBoundData );
						if ( itBox != m_mapBoundDataBox.end() )
						{
							if ( itBox->second )
							{
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[4], itBox->second->vecPoint[5], itBox->second->vecPoint[7], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[4], itBox->second->vecPoint[7], itBox->second->vecPoint[6], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[0], itBox->second->vecPoint[1], itBox->second->vecPoint[5], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[0], itBox->second->vecPoint[5], itBox->second->vecPoint[4], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[1], itBox->second->vecPoint[3], itBox->second->vecPoint[7], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[1], itBox->second->vecPoint[7], itBox->second->vecPoint[5], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[3], itBox->second->vecPoint[2], itBox->second->vecPoint[6], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[3], itBox->second->vecPoint[6], itBox->second->vecPoint[7], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[2], itBox->second->vecPoint[0], itBox->second->vecPoint[4], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[2], itBox->second->vecPoint[4], itBox->second->vecPoint[6], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[0], itBox->second->vecPoint[1], itBox->second->vecPoint[3], pObj->matTransform );
								g_pEngineHandler->HT_hrDrawBoundingTriangle( itBox->second->vecPoint[0], itBox->second->vecPoint[3], itBox->second->vecPoint[2], pObj->matTransform );
							}
						}
						break;
					case HT_BOUNDPRIM_CYLINDER:
						break;
					}
				}
			}
			it++;
		}
	}

	return ( HT_OK );
}

HTRESULT				
CHTMapSystem::HT_hrCheckCollision( HTvector3& vecStartPos, HTfloat fRadius, HTBoundObj* pObj, HTvector3& vecTargetPos, HTvector3& vecNextpos, HTvector3& vecCollisionPos )
{
	HTbool bCollided = HT_FALSE;
	HTvector3 arrvecPlane[8], vecResultPos, vecFinalResultPos, vecFinalCollidedPos;
	HTfloat fTempLength, fNearLength;

	std::map<HTint,HTBoundPlane*>::iterator itPlane;
	std::map<HTint,HTBoundBox*>::iterator itBox;
	std::map<HTint,HTBoundCylinder*>::iterator itCylinder;

	HTvector3 vecYUp, vecLeft, vecRight;
	vecYUp = HTvector3( 0.0f,1.0f,0.0f );
	CHTVector::HT_pvecVec3Cross( &vecLeft, &vecYUp, &(vecTargetPos-vecStartPos) );
	CHTVector::HT_pvecVec3Normalize( &vecLeft, &vecLeft );
	vecLeft *= fRadius;
	vecRight = -vecLeft;
	
	if ( pObj->eType == HT_BOUNDPRIM_PLANE )
	{
		fNearLength = FLT_MAX;
		itPlane = m_mapBoundDataPlane.find( pObj->idBoundData );
		if ( itPlane != m_mapBoundDataPlane.end() )
		{
			if ( itPlane->second )
			{
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[0], &itPlane->second->vecPoint[0], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[1], &itPlane->second->vecPoint[1], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[2], &itPlane->second->vecPoint[2], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[3], &itPlane->second->vecPoint[3], &pObj->matTransform );

				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[1], arrvecPlane[3], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fNearLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					vecFinalResultPos = vecResultPos;
					vecFinalCollidedPos = vecCollisionPos;
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[3], arrvecPlane[2], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos+vecLeft, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[1], arrvecPlane[3], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos+HTvector3( 3.0f, 0.0f, 0.0f )));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos+vecLeft, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[3], arrvecPlane[2], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos+HTvector3( 3.0f, 0.0f, 0.0f )));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos+vecRight, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[1], arrvecPlane[3], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos+HTvector3( -3.0f, 0.0f, 0.0f )));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos+vecRight, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[3], arrvecPlane[2], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos+HTvector3( -3.0f, 0.0f, 0.0f )));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
			}
		}
		else
		{
		}
	}
	else if ( pObj->eType == HT_BOUNDPRIM_BOX )
	{
		fNearLength = FLT_MAX;
		itBox = m_mapBoundDataBox.find( pObj->idBoundData );
		if ( itBox != m_mapBoundDataBox.end() )
		{
			if ( itBox->second )
			{
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[0], &itBox->second->vecPoint[0], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[1], &itBox->second->vecPoint[1], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[2], &itBox->second->vecPoint[2], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[3], &itBox->second->vecPoint[3], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[4], &itBox->second->vecPoint[4], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[5], &itBox->second->vecPoint[5], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[6], &itBox->second->vecPoint[6], &pObj->matTransform );
				CHTVector::HT_pvecVec3TransformCoord( &arrvecPlane[7], &itBox->second->vecPoint[7], &pObj->matTransform );

				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[4], arrvecPlane[5], arrvecPlane[7], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fNearLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					vecFinalResultPos = vecResultPos;
					vecFinalCollidedPos = vecCollisionPos;
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[4], arrvecPlane[7], arrvecPlane[6], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[1], arrvecPlane[5], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[5], arrvecPlane[4], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[1], arrvecPlane[3], arrvecPlane[7], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[1], arrvecPlane[7], arrvecPlane[5], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[3], arrvecPlane[2], arrvecPlane[6], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[3], arrvecPlane[6], arrvecPlane[7], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[2], arrvecPlane[0], arrvecPlane[4], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[2], arrvecPlane[4], arrvecPlane[6], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[1], arrvecPlane[3], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
				if ( CHTIntersect::HT_bIsCollidedShpereTriangle( vecStartPos, fRadius, vecTargetPos-vecStartPos,
					arrvecPlane[0], arrvecPlane[3], arrvecPlane[2], &vecCollisionPos, &vecResultPos ) )
				{
					bCollided = HT_TRUE;
					fTempLength = CHTVector::HT_fVec3Length(&(vecCollisionPos-vecStartPos));
					if ( fTempLength < fNearLength )
					{
						fNearLength = fTempLength;
						vecFinalResultPos = vecResultPos;
						vecFinalCollidedPos = vecCollisionPos;
					}
				}
			}
		}
	}
	else if ( pObj->eType == HT_BOUNDPRIM_CYLINDER )
	{
		itCylinder = m_mapBoundDataCylinder.find( pObj->idBoundData );
		if ( itCylinder != m_mapBoundDataCylinder.end() )
		{
		}
	}

	if ( bCollided )
	{
		vecCollisionPos = vecFinalCollidedPos;
		vecNextpos = vecFinalResultPos;
		return ( HT_RESULT_COLLISION_DETECTED );
	}
	else				
	{
		vecCollisionPos = HTvector3(0.0f,0.0f,0.0f);
		vecNextpos = vecTargetPos;
		return ( HT_OK );
	}
}

HTRESULT				
CHTMapSystem::HT_hrStopAmbientSounds()
{
	// 현재 틀고 있는 공간음을 모두 스톱시킨다.
	std::set<HTdword>::iterator itSound = m_setCurrentAmbientSoundIDs.begin();
	while ( itSound != m_setCurrentAmbientSoundIDs.end() )
	{
		std::map<HTdword,HSAMPLE>::iterator itSample = m_mapAmbientSampleHandles.find( *itSound );
		if ( itSample != m_mapAmbientSampleHandles.end() )
		{
			m_p3DMgr->HT_hrStopSound( itSample->second );
			m_mapAmbientSampleHandles.erase( itSample );
		}

		itSound++;
	}

	m_setCurrentAmbientSoundIDs.clear();

	m_setBeforeAmbientSoundIDs.clear();

	return ( HT_OK );
}

HTbool
CHTMapSystem::HT_bGetNearestShoot(HTvector3 vecChar, HTfloat& fRetDist, HTvector3& vecShootPos)
{
	std::vector<HTvector3>::iterator itObj = m_arrShootPoint.begin();

	HTbool bHaveShoot = HT_FALSE;
	HTfloat fDist, fRDist = 1000000.0f;
	HTvector3 vecRet;
	HTvector3 vecData = HTvector3(0.0f, 0.0f, 0.0f);
	while (itObj != m_arrShootPoint.end())
	{
		bHaveShoot = HT_TRUE;
		vecData.x = itObj->x;
		vecData.y = itObj->y;
		vecData.z = itObj->z;
		
		fDist = ( vecData.x - vecChar.x )*( vecData.x - vecChar.x ) + 
					( vecData.z - vecChar.z )*( vecData.z - vecChar.z );

		fDist = (HTfloat)sqrt(fDist);

		if ( fRDist>fDist )
		{
			fRDist = fDist;
			vecShootPos = vecData;
		}
		itObj++;
	}
	return bHaveShoot;
}

HTRESULT
CHTMapSystem::HT_hrOpenFootSound(CHTString& strFile)
{
	HTint i, j;
	if (m_ppbyFootSound)
	{
		for (i=0; i<m_wGridSizeZ; i++) HT_DELETEARRAY(m_ppbyFootSound);
		HT_DELETEARRAY(m_ppbyFootSound);
	}
	
	CHTFile oFile;
	if ( oFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) == HT_FALSE )
	{
		return ( HT_FAIL );
	}

	HTint iVersion;
	
	oFile.HT_bRead( &iVersion, sizeof(HTword) );
	oFile.HT_bRead( &m_wGridSizeX, sizeof(HTword) );
	oFile.HT_bRead( &m_wGridSizeZ, sizeof(HTword) );
	
	m_ppbyFootSound = new BYTE*[m_wGridSizeZ];
	for (i=0; i<m_wGridSizeZ; i++)
		m_ppbyFootSound[i] = new BYTE[m_wGridSizeX];

	for (i=0; i<m_wGridSizeZ; i++)
		for (j=0; j<m_wGridSizeX; j++)
			oFile.HT_bRead( &m_ppbyFootSound[i][j], sizeof(BYTE));

	oFile.HT_vClose();

	return HT_OK;
}

//----------------------------------------------------------------
// HTint					HT_iGetMapStatus(HTvector3 vecChar)
// D : 캐릭터의 위치에 따라 발소리 얻기
// I : vecPos - 위치
// R : 발소리 번호
//----------------------------------------------------------------
HTint
CHTMapSystem::HT_iGetMapStatus(HTvector3 vecChar)
{
	if (!m_ppbyFootSound) return 0;
	HTint iGridRowNo, iGridColNo;
	iGridRowNo = (HTint)(vecChar.z/20.0f);
	iGridColNo = (HTint)(vecChar.x/20.0f);

	if (iGridRowNo>(m_wGridSizeZ-1)) return 0;
	if (iGridColNo>(m_wGridSizeX-1)) return 0;

	return m_ppbyFootSound[iGridRowNo][iGridColNo];

}