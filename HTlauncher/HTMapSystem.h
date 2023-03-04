#ifndef _HTMAPSYSTEM_H_
#define _HTMAPSYSTEM_H_

#define HT_ROOT_2		1.41421356f

// �ʿ����� �ּ�/�ִ� ���̰�
#define HT_MIN_MAPHEIGHT		-200.0f
#define HT_MAX_MAPHEIGHT		1500.0f

// �� ������Ʈ�� ���� �� ��尪 ����
#define HT_MAPNODE_SIZE			160.0f
#define HT_MAPNODE_NUM			64

// Ǯó���� ���� �� ��忡 ���� �� ����
// ���� �� 1024.0f * 1024.0f�� ��츦 ����� ���̴�. ( 40.0f * 256 = 1024.0f )
#define HT_GRASSMAPNODE_SIZE	40.0f
#define HT_GRASSMAPNODE_NUM		256

typedef enum _HT_RESULT_FILTEROBJ
{
	HT_FILTEROBJ_OUT,
	HT_FILTEROBJ_IN,
	HT_FILTEROBJ_HANGON,

} HT_RESULT_FILTEROBJ;

typedef enum _HTBoundPrimitive
{
	HT_BOUNDPRIM_PLANE		= 0,
	HT_BOUNDPRIM_BOX		= 1,
	HT_BOUNDPRIM_CYLINDER	= 2,
} HTBoundPrimitive;

typedef struct _HTBoundPlane
{
	HTvector3		vecPoint[4];
} HTBoundPlane;

typedef struct _HTBoundBox
{
	HTvector3		vecPoint[8];
} HTBoundBox;

typedef struct _HTBoundCylinder
{
	HTvector3		vecBottomCenter;
	HTvector3		vecTopCenter;
	HTfloat			fRadius;
} HTBoundCylinder;

typedef struct _HTBoundObj
{
	HTBoundPrimitive		eType;
	HTmatrix				matTransform;
	HTint					idBoundData;	// bound data map �� Ű ��!
} HTBoundObj;

// Ǯ ó���� ���� �� ���
typedef struct _HTGrassMapNode
{
	HT_AABB						m_boxArea;		// ����� �ٿ�� ����
	std::set<HTint>				m_setObjects;	// ��尡 ������ ������Ʈ���� ����Ʈ 
	std::set<HTint>				m_setSMObjects;	// ��尡 ������ SM ������Ʈ���� ����Ʈ 

	std::vector<HTint>			m_vectorBoundObjs;	// ��尡 ������ �ٿ�� ������Ʈ���� ����Ʈ

} HTGrassMapNode;

typedef struct _HT_FRECT
{
	HTfloat		fLeft;
	HTfloat		fRight;
	HTfloat		fTop;
	HTfloat		fBottom;

	_HT_FRECT()
	{
		fLeft = fRight = fTop = fBottom = 0.0f;
	}

} HT_FRECT;

typedef struct _HTSoundSpaceNode
{
	HTdword		dwBGMID;
	HT_FRECT	rcArea;
	HTint		iRoomType;
	std::vector<HTdword>	vectorDaySounds;
	std::vector<HTdword>	vectorNightSounds;

	_HTSoundSpaceNode()
	{
		dwBGMID = 0;
		iRoomType = 0;
		vectorDaySounds.clear();
		vectorNightSounds.clear();
	}

	~_HTSoundSpaceNode()
	{
		vectorDaySounds.clear();
		vectorNightSounds.clear();
	}

} HTSoundSpaceNode;

typedef struct _HTAreaIndicate
{
	HTdword		dwAreaID;
	HT_FRECT	rcArea;

	_HTAreaIndicate()
	{
		dwAreaID = 0;
	}

	~_HTAreaIndicate(){}	

} HTAreaIndicate;

typedef struct _HT_MAP_INT2DCOORD
{
	HTint				iX;
	HTint				iZ;

	_HT_MAP_INT2DCOORD()
	{
		iX = iZ = 0;
	}

	_HT_MAP_INT2DCOORD( HTint iSrcX, HTint iSrcZ )
	{
		iX = iSrcX;
		iZ = iSrcZ;
	}

} HT_MAP_INT2DCOORD;

typedef struct _HT_MAP_SAVEOBJ
{
	HTbool							bGrass;
	HTdword							dwResID;
	std::vector<HT_MAP_INT2DCOORD>	vectorNodes;
	HTmatrix						matTransform;
	HT_EOBJ_PROPERTY				oProperty;

	HTint							idRenewal;
	HTint							idDayFX;
	HTint							idNightFX;

} HT_MAP_SAVEOBJ;

typedef struct _HT_MAP_HPVSNODE
{
	std::set<HTdword>				setResIDs;
	std::list<HTint>				listViewingNodes;
	std::set<HTint>					setObjectIDs;
} HT_MAP_HPVSNODE;

// A* search�� ���� �ڷᱸ��
typedef struct _HT_MAP_PATHNODE
{
	HT_CELL_COORD		celLocation;
	HTfloat				fCostFromStart;
	HTfloat				fCostToGoal;
	HTfloat				fTotalCost;
	_HT_MAP_PATHNODE*	pParent;
	_HT_MAP_PATHNODE*	pChilds[8];

	_HT_MAP_PATHNODE()
	{
		celLocation.x = 0; celLocation.y = 0;
		fCostFromStart = 0.0f;
		fCostToGoal = 0.0f;
		fTotalCost = 0.0f;
		pParent = HT_NULL;
		pChilds[0] = pChilds[1] = pChilds[2] = pChilds[3] = HT_NULL;
		pChilds[4] = pChilds[5] = pChilds[6] = pChilds[7] = HT_NULL;
	}

} HT_MAP_PATHNODE;

// ����Ÿ���� Shooting Point�� ����
typedef struct _HT_MAP_SHOOTPT
{
	std::vector<HTvector3>	arrvecShoot;
} HT_MAP_SHOOTPT;


class PQCompareFn 
{
	public:
		bool operator() ( const HT_MAP_PATHNODE *x, const HT_MAP_PATHNODE *y ) const
		{
			return x->fTotalCost > y->fTotalCost;
		}
};


class CHTMapSystem
{
public:
							CHTMapSystem();
							~CHTMapSystem();

	HTRESULT				HT_hrCreate( HTint iWidth, HTint iHeight, IHT3DMgr* p3DMgr );
	HTRESULT				HT_hrDestroy();
	HTRESULT				HT_hrLoad( CHTString& strFile );
	HTRESULT				HT_hrInsertObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HT_OBJSIZETYPE eType, HTbyte byFloor, HTdword dwResID = 0, HT_EOBJ_PROPERTY* pProperty = HT_NULL );
	HTRESULT				HT_hrDeleteObject( HTint idObj, HT_OBJSIZETYPE eType, HTbyte byFloor );
	HTRESULT				HT_hrMoveObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HT_OBJSIZETYPE eType, HTbyte byFloor );
	HTRESULT				HT_hrInsertGrassObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HTdword dwResID = 0, HT_EOBJ_PROPERTY* pProperty = HT_NULL );
	HTRESULT				HT_hrInsertSMObject( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform, HTdword dwResID = 0, HT_EOBJ_PROPERTY* pProperty = HT_NULL );
	HTRESULT				HT_hrInsertObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes );
	HTRESULT				HT_hrInsertGrassObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes );
	HTRESULT				HT_hrInsertSMObject( HTint idObj, std::vector<HT_MAP_INT2DCOORD>& vectorNodes );

	HTRESULT				HT_hrLoadMapSound( CHTString& strFile );
	HTRESULT				HT_hrLoadMapHPVS( CHTString& strFile );
	HTRESULT				HT_hrLoadMapBound( CHTString& strFile );
	HTbool					HT_bIsIndoorMap()	{ return ( m_bHPVSMode );	}

	//-------------------------------------------------------------------------------------
	// HTRESULT				HT_hrLoadMapAreaIndicator( CHTString& strFile )
	// D : ����ǥ�� ���� �ε�
	// I : strFile - ������ ǥ�õǾ� �ִ� �ʿ� �ش��ϴ� �����̸�
	// R : HT_TRUE/HT_FALSE
	//-------------------------------------------------------------------------------------
	HTRESULT				HT_hrLoadMapAreaIndicator( CHTString& strFile );

	//-------------------------------------------------------------------------------------
	// HTint				HT_iGetIndicatedArea()
	// D : ���� ���� ǥ�� ���
	// R : ������ȣ
	//-------------------------------------------------------------------------------------
	HTint					HT_iGetIndicatedArea(){ return m_iAreaID; }


	HTint					HT_iComputeLOD( HTfloat fDistFromCam, HTint iPrevLOD );
	HTint					HT_iComputeCharLOD( HTfloat fDistFromCam, HTint iPrevLOD );
	HTRESULT				HT_hrUpdateViewingNodes( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, std::vector<HTint>& vectorViewingObjs, std::vector<HTint>& vectorUpdateObjs );
	HTRESULT				HT_hrUpdateViewingSMNodes( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, std::vector<HTint>& vectorViewingObjs );
	HTRESULT				HT_hrUpdateViewingGrasses( HTvector3* arrFrustumPoints, HTFrustumPlane* pFrustum, HTfloat fCullingDist, HTfloat fGrassAlphaDistance, std::vector<HTint>& arrGrasses );

	HTRESULT				HT_hrPick( HTRay& rRay, std::list<HTint>& listObjs );

	HTbool					HT_bCanMove( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );
	HTbool					HT_bCanAttack( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );
	HTbool					HT_bNoAttackMonster( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );

	HT_TILE_TYPE			HT_eGetTileType( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellSafeZone( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellConflict( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellPKZone( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellTemple( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellMoveDisable( HTint iX, HTint iZ, HTint iF );

	HTbool					HT_bIsCellAttackEnable( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsAttackMonsterDisable( HTint iX, HTint iZ, HTint iF );

	//HTbool					HT_bIsCellVishunu( HTint iX, HTint iZ, HTint iF );
	//HTbool					HT_bIsCellSiva( HTint iX, HTint iZ, HTint iF );
	//--------------------------------------------------------------------------
	// HTword				HT_wGetObjHeight(HTint iX, HTint iZ, HTint iF )
	// D : �ö� ������Ʈ�� ���� ���
	// I : iX, iZ - ��ǥ, iF - ��
	// R : ������Ʈ�� ����
	//--------------------------------------------------------------------------
	HTword					HT_wGetObjHeight(HTint iX, HTint iZ, HTint iF );// ��ȣ �߰�

	HTRESULT				HT_hrAStarSearch( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal, HTint* nNode, HT_CELL_COORD* arrNode );

	__inline HTvoid			HT_3DCOORD_TO_CELL( HTvector3& vecPos, HT_CELL_COORD& rCell )
	{
		rCell.x = (HTint)floorf(vecPos.x / HT_MAP_CELLSIZE);
		rCell.y = m_wMapSizeZ - (HTint)floorf(vecPos.z / HT_MAP_CELLSIZE) - 1;
	};
	__inline HTvoid			HT_CELL_TO_3DCOORD( HTvector3& vecPos, HT_CELL_COORD& rCell )
	{
		vecPos.x = rCell.x * HT_MAP_CELLSIZE + 2.5f;
		vecPos.z = HT_MAP_CELLSIZE * ( m_wMapSizeZ - 1 )- rCell.y * HT_MAP_CELLSIZE + 2.5f;
	};

	HTRESULT				HT_hrSetLODValues( HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat, HTfloat );

	HTRESULT				HT_hrNotifySoundMove( HTbool bDay, HTvector3& vecPos );

	// Dynamic Loading
	HTRESULT				HT_hrLoadDLMap( CHTString& strFile, std::vector<HTdword>&, std::vector<HTdword>& );
	HTRESULT				HT_hrSaveDLMap( CHTString& strFile, std::vector<HTdword>&, std::vector<HTdword>& );
	HTRESULT				HT_hrGetIDToLoad( HTvector3& vecPos, HTfloat fCamFarZ, std::set<HTint>& setToLoad, 
		std::set<HTint>& setToUnload, std::set<HTint>& setToCreate, std::set<HTint>& setToDestroy );

	// Collision Detection
	HTRESULT				HT_hrMoveObject( HTint idObj, HTvector3& vecStartPos, HTfloat fRadius, HTvector3& vecTargetPos, HTvector3& vecNextpos );
	HTRESULT				HT_hrRenderBoundObjs( HT_AABB* pBB, HTmatrix* pmatTrasform );

	HTRESULT				HT_hrStopAmbientSounds();

	//----------------------------------------------------------------
	// HTint				HT_iSetArea()
	// D : Area Indicate
	// I : vecPos - ��ġ
	// R : Indicated Area Number
	//----------------------------------------------------------------
	HTint					HT_iSetArea(HTvector3& vecPos);

	//HTRESULT				HT_hrUpdateShootingPoint(std::vector<HTint> vectorViewingObjs);
	HTbool					HT_bGetNearestShoot(HTvector3 vecChar, HTfloat& fRetDist, HTvector3& vecShootPos);
	HTRESULT				HT_hrOpenShootPoint(CHTString& strFile);
	HTRESULT				HT_hrOpenFootSound(CHTString& strFile);

	//----------------------------------------------------------------
	// HTint					HT_iGetMapStatus(HTvector3 vecChar)
	// D : ĳ������ ��ġ�� ���� �߼Ҹ� ���
	// I : vecPos - ��ġ
	// R : �߼Ҹ� ��ȣ
	//----------------------------------------------------------------
	HTint					HT_iGetMapStatus(HTvector3 vecChar);

private:
	IHT3DMgr*				m_p3DMgr;

	// Map Data
	HT_HEADER				m_oHeader;
	HTdword					m_dwCellCount;
	CHTString				m_strMapName;
	HTword					m_wMapIndex;
	HTbool					m_bPKInfo;
	HTword					m_wMapSizeX;
	HTword					m_wMapSizeZ;
	 
	// Cell Map
	HT_CELL_NODE**			m_ppCell;

	// ASS 20021125 : QuadTree�� 2D array�� ��ü�Ѵ�.
	// ��������� 1000���� ������Ʈ�� 512 * 512 �ʿ� ������, 200 ���� �� ��带 �˻��ϰ� 200���� ������Ʈ��
	// �������� �ø� ����� �Ѵ�. �̸� 100���� �� ��� �˻�� 100���� ������Ʈ �ø��� �ϴ� 2D Array�� �ٲٴ� ����
	// �����̴�.
	HTGrassMapNode**		m_ppMap;

	// Ǯ ������Ʈ ó���� ���� 2���� ��
	HTGrassMapNode**		m_ppGrassMap;
	std::set<HTint>			m_setViewingGrass;

	// �ε��� ���� 2���� ��
	std::set<HTdword>**	m_ppDLMap;
	// ���� �ε�Ǿ� �ִ� ���ҽ� ���̵��
	std::set<HTdword>		m_setLoadedObjIDs;
	// ���� ������ ������Ʈ��
	std::set<HTint>			m_setCreatedObjIDs;
	// �ʿ� �ڴ� ������Ʈ�� �����ؼ� ���� �ε嶧���� ������ ��带 ������� �ʰ� �ٷ� �ڱ� ���� �ڷᱸ���̴�.

	std::set<HT_MAP_SHOOTPT>	m_oShootPT;
public:
	std::map<HTint,HT_MAP_SAVEOBJ*>	m_mapSaveObjs;
private:

	// HPVS map
	HT_MAP_HPVSNODE**		m_ppHPVS;
	HTint					m_iHPVSNodeCountX;
	HTint					m_iHPVSNodeCountZ;
	HTbool					m_bHPVSMode;
	HTfloat					m_fHPVSGridSize;

	// ��������Ƽ üũ�� ���� ���̺�
	HTuint					m_nVisibleObjs;
	std::list<HTint>		m_listVisibleObjs;

	typedef struct _HT_MAP_REMEMBEROBJ
	{
		std::vector<HTGrassMapNode*>	vectorMapNodes;
	} HT_MAP_REMEMBEROBJ;
	std::map<HTint, HT_MAP_REMEMBEROBJ*>	m_hashmapObjects;

	// LOD setting
	HTfloat		m_fLODDistanceLow1, m_fLODDistanceLow2, m_fLODDistanceLow3;
	HTfloat		m_fLODDistanceHigh1, m_fLODDistanceHigh2, m_fLODDistanceHigh3;
	HTfloat		m_fLODDistanceFar, m_fLODDistanceFarSM;
	HTfloat		m_fCharLODDistance1, m_fCharLODDistance2, m_fCharLODDistance3;

	// �������� ���� �ڷ� ����
	HTdword							m_dwBGMID;
	std::vector<HTSoundSpaceNode*>	m_vectorSoundSpaces;
	std::set<HTdword>				m_setBeforeAmbientSoundIDs;
	std::set<HTdword>				m_setAfterAmbientSoundIDs;
	std::set<HTdword>				m_setCurrentAmbientSoundIDs;
	std::map<HTdword,HSAMPLE>		m_mapAmbientSampleHandles;
	HTint							m_iRoomType;

	// Area Indicate�� ���� �ڷᱸ��
	std::vector<_HTAreaIndicate*>	m_vectorAreaIndicate;
	HTint							m_iAreaID;

	// �浹ó���� ���� �ڷᱸ��
	std::map<HTint,HTBoundPlane*>		m_mapBoundDataPlane;
	std::map<HTint,HTBoundBox*>			m_mapBoundDataBox;
	std::map<HTint,HTBoundCylinder*>	m_mapBoundDataCylinder;
	std::map<HTint,HTBoundObj*>			m_mapBoundObjs;

	HTRESULT				HT_hrInsertBoundPlane( HTint idBoundObj, HTBoundObj* pBoundObj );
	HTRESULT				HT_hrInsertBoundBox( HTint idBoundObj, HTBoundObj* pBoundObj );
	HTRESULT				HT_hrInsertBoundCylinder( HTint idBoundObj, HTBoundObj* pBoundObj );

	HTfloat					HT_fPlanePointDistance( HTplane* pPlane, HTvector3* pVector );

	HTRESULT				HT_hrSetCellMoveDisable( HT_CELL_COORD& rCell, HT_OBJSIZETYPE eType, HTbyte byFloor );
	HTRESULT				HT_hrSetCellMoveEnable( HT_CELL_COORD& rCell, HT_OBJSIZETYPE eType, HTbyte byFloor );

	// A* search�� ���� �ڷᱸ��
	std::priority_queue<HT_MAP_PATHNODE*,std::vector<HT_MAP_PATHNODE*>,PQCompareFn>	m_prqueOpen;
	std::list<HT_MAP_PATHNODE*>		m_listClosed;
	HTfloat							m_fHeuristic;	// Ÿ�ϴ� �ּ� ���� ��� 
	HTfloat							m_fCostToMoveOneCell;
	std::vector<HT_CELL_COORD>		m_vectorFoundPath;

	HTvoid					HT_vFreeAllNodes();
	HTfloat					HT_fPathCostEstimate( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal );
	HTfloat					HT_fTraverseCost( HT_MAP_PATHNODE* pParent, HT_MAP_PATHNODE* pChild );
	HTbool					HT_bIsInClosed( HT_CELL_COORD& rCell );
	HTbool					HT_bIsInOpen( HT_CELL_COORD& rCell );
	HTvoid					HT_vRemoveNodeInClosed( HT_MAP_PATHNODE* pNode );
	HTvoid					HT_vRemoveNodeInOpen( HT_MAP_PATHNODE* pNode );
	HT_MAP_PATHNODE*		HT_pGetNodeInClosed( HT_CELL_COORD& rCell );
	HT_MAP_PATHNODE*		HT_pGetNodeInOpen( HT_CELL_COORD& rCell );

	HTRESULT				HT_hrCheckCollision( HTvector3& vecStartPos, HTfloat fRadius, HTBoundObj* pObj, HTvector3& vecTargetPos, HTvector3& vecNextpos, HTvector3& vecCollisionPos );

	// Shooting Point�� ���� �ڷᱸ��
	std::vector<HTvector3>	m_arrShootPoint;
	BYTE**					m_ppbyFootSound;
	HTword					m_wGridSizeX;
	HTword					m_wGridSizeZ;

	
};

#endif	// #ifndef _HTMAPSYSTEM_H_