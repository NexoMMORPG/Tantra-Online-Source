//----------------------------------------------------------------------------//
//																			  //
//	Project : Tantra game resource manager      							  //
//	Purpose : resource manager impls.                              			  //
//	File	: HTResMgr.h      												  //
//	Author	: Assrada														  //
//	History : 2002/09/25, Initiated by Assrada 								  //
//				- init                                         				  //
//																			  //
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.			  //
//----------------------------------------------------------------------------//

#ifndef _HTRESMGR_H_
#define _HTRESMGR_H_

//--------------------------------------------------------------------------
#define HT_MAX_XML_STR			40
#define HT_MAX_XML_MONSTR		50

class CHTXMLParser;

typedef struct _HT_ResTableType01
{
	HTtchar   	strFile[HT_MAX_XML_STR];
} HT_ResTableType01;

typedef struct _HT_ResTableType02
{
	HTtchar   	strMapName[HT_MAX_XML_STR];
	HTtchar   	strFileTHM[HT_MAX_XML_STR];
	HTtchar   	strFileTMO[HT_MAX_XML_STR];
	HTtchar   	strFileTME[HT_MAX_XML_STR];
	HTtchar   	strFileTCC[HT_MAX_XML_STR];
	HTtchar   	strFileCFG[HT_MAX_XML_STR];
	HTtchar   	strFileBMP[HT_MAX_XML_STR];	// 20021106 대호
	HTdword		dwMaterial;
	HTtchar   	strFileOBJ[HT_MAX_XML_STR];
	HTtchar   	strFileTEX[HT_MAX_XML_STR];
	HTtchar   	strFileMON[HT_MAX_XML_STR];
	HTtchar   	strFileMONANI[HT_MAX_XML_STR];
	HTtchar   	strFileMONTEX[HT_MAX_XML_STR];
	HTtchar   	strFileNPC[HT_MAX_XML_STR];
	HTtchar   	strFileNPCANI[HT_MAX_XML_STR];
	HTtchar   	strFileNPCTEX[HT_MAX_XML_STR];
	HTtchar   	strFXFiles[HT_MAX_XML_STR];
	HTtchar   	strNPCSoundFiles[HT_MAX_XML_STR];
	HTtchar   	strMonSoundFiles[HT_MAX_XML_STR];
	HTtchar   	strFileMinimap[HT_MAX_XML_STR];
	HTtchar   	strFileNPCScript[HT_MAX_XML_STR];
	HTtchar   	strFileObjRes[HT_MAX_XML_STR];		// 20031008 대호 (오브젝트 리소스 분리)
	HTtchar   	strFilePopObjPack[HT_MAX_XML_STR];	// 20031008 대호 (오브젝트 리소스 분리)
	HTtchar   	strFilePopTexPack[HT_MAX_XML_STR];	// 20031008 대호 (오브젝트 리소스 분리)
} HT_ResTableType02;

typedef struct _HT_ResTableType03
{
	HT_COLOR	clrDiffuse;
	HT_COLOR	clrAmbient;
	HT_COLOR	clrSpecular;
	HT_COLOR	clrEmissive;
	HTfloat		fPower;
} HT_ResTableType03;

typedef struct _HT_ResTableType04
{
	HTdword		dwModelID;
	HTdword		dwDefaultUpWearID;
	HTdword		dwDefaultDownWearID;
	HTdword		dwDefaultHandWearID;
	HTdword		dwDefaultShoesID;
	HTdword		dwHeadTypeAID;
	HTdword		dwHeadTypeBID;
	HTdword		dwHeadTypeCID;
	HTdword		dwHeadTypeDID;
	HTdword		dwHeadTypeEID;
	HTdword		dwHeadTypeFID;
	HTdword		dwHeadTypeGID;
	HTdword		dwHeadTypeHID;
	HTdword		dwMaterialID;
} HT_ResTableType04;

typedef struct _HT_ResTableType05
{
	HTdword		dwFaceMesh;
	HTdword		dwFaceTexID;
	HTdword		dwHairModelID;
	HTdword		dwHairTexID;
	HTdword		dwHairType;
} HT_ResTableType05;

//typedef struct _HT_ResTableType06 {} HT_ResTableType06;

// UpWear
typedef struct _HT_ResTableType061
{
	HTdword   	dwChestMesh;
	HTdword		dwChestTexID;

	HTdword   	dwRUArmMesh;
	HTdword   	dwLUArmMesh;
	HTdword		dwRUArmTexID;
	HTdword		dwLUArmTexID;

	HTdword   	dwSkirtMesh;
	HTdword		dwSkirtTexID;
	HTdword		dwApronModelID;
	HTdword		dwApronTexID;
	HTdword		dwApronBackModelID;
	HTdword		dwApronBackTexID;

	HTdword		dwShoulderLModelID;
	HTdword		dwShoulderLTexID;
	HTdword		dwShoulderRModelID;
	HTdword		dwShoulderRTexID;

	HTbool		bSkirtType;
} HT_ResTableType061;

// DownWear
typedef struct _HT_ResTableType062
{
	HTdword   	dwPantsMesh;
	HTdword		dwPantsMesh2nd;
	HTdword		dwPantsTexID;

	HTdword		dwKneeLModelID;
	HTdword		dwKneeLTexID;
	HTdword		dwKneeRModelID;
	HTdword		dwKneeRTexID;

	HTdword		dwThighLModelID;
	HTdword		dwThighLTexID;
	HTdword		dwThighRModelID;
	HTdword		dwThighRTexID;
} HT_ResTableType062;

// HandWear
typedef struct _HT_ResTableType063
{
	HTdword   	dwRLArmMesh;
	HTdword   	dwLLArmMesh;
	HTdword		dwRLArmTexID;
	HTdword		dwLLArmTexID;
	HTdword   	dwRHandMesh;
	HTdword   	dwLHandMesh;
	HTdword		dwRHandTexID;
	HTdword		dwLHandTexID;
} HT_ResTableType063;

typedef struct _HT_ResTableType07
{
	HTdword		dwRBootsMesh;
	HTdword		dwLBootsMesh;
	HTdword		dwBootsTexID;

} HT_ResTableType07;

typedef struct _HT_ResTableType08
{
	HTdword		dwNAGID;
	HTdword		dwYAKID;
	HTdword		dwASUID;
	HTdword		dwDEVID;
	HTdword		dwKIMID;
	HTdword		dwGANID;
	HTdword		dwRAKID;
	HTdword		dwGARID;

	HTdword		dwNAGSoundID1;
	HTdword		dwNAGSoundID2;
	HTdword		dwNAGSoundID3;
	HTdword		dwYAKSoundID1;
	HTdword		dwYAKSoundID2;
	HTdword		dwYAKSoundID3;
	HTdword		dwASUSoundID1;
	HTdword		dwASUSoundID2;
	HTdword		dwASUSoundID3;
	HTdword		dwDEVSoundID1;
	HTdword		dwDEVSoundID2;
	HTdword		dwDEVSoundID3;
	HTdword		dwKIMSoundID1;
	HTdword		dwKIMSoundID2;
	HTdword		dwKIMSoundID3;
	HTdword		dwGANSoundID1;
	HTdword		dwGANSoundID2;
	HTdword		dwGANSoundID3;
	HTdword		dwRAKSoundID1;
	HTdword		dwRAKSoundID2;
	HTdword		dwRAKSoundID3;
	HTdword		dwGARSoundID1;
	HTdword		dwGARSoundID2;
	HTdword		dwGARSoundID3;

	HTdword		dwNAGFApronAniID;
	HTdword		dwNAGBApronAniID;
	HTdword		dwYAKFApronAniID;
	HTdword		dwYAKBApronAniID;
	HTdword		dwASUFApronAniID;
	HTdword		dwASUBApronAniID;
	HTdword		dwDEVFApronAniID;
	HTdword		dwDEVBApronAniID;
	HTdword		dwKIMFApronAniID;
	HTdword		dwKIMBApronAniID;
	HTdword		dwGANFApronAniID;
	HTdword		dwGANBApronAniID;
	HTdword		dwRAKFApronAniID;
	HTdword		dwRAKBApronAniID;
	HTdword		dwGARFApronAniID;
	HTdword		dwGARBApronAniID;

} HT_ResTableType08;

// UpWearItem, DownWearItem, HandWearItem
typedef struct _HT_ResTableType081
{
	HTdword		dwNAGID;
	HTdword		dwYAKID;
	HTdword		dwASUID;
	HTdword		dwDEVID;
	HTdword		dwKIMID;
	HTdword		dwGANID;
	HTdword		dwRAKID;
	HTdword		dwGARID;
} HT_ResTableType081;

typedef struct _HT_ResTableType09
{
	HTtchar   	strNPCName[HT_MAX_XML_STR];
	HTdword		dwTMD;
	HTdword		dwTAM_STD;
	HTdword		dwTAM_WLK;
	HTdword		dwTAM_IDL;
	HTdword		dwMaterialID;	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTdword		dwStateSoundID;	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTdword		dwClickSoundID;	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTdword		dwIdleFX;		// 20021103 HK : NPC의 Idle 애니메이션이 시작할 때마다 발생하는 이펙트ID
	HTdword		dwMovSoundID;
} HT_ResTableType09;

typedef struct _HT_ResTableType10
{
	HTtchar   	strMonsterName[HT_MAX_XML_MONSTR];
	HTuint		nNumMesh;
	HTdword		dwBasicModel;
	HTdword		dwMesh1;
	HTdword		dwMesh2;
	HTdword		dwMesh3;
	HTdword		dwMesh4;
	HTdword		dwMesh5;
	HTdword		dwTex1;
	HTdword		dwTex2;
	HTdword		dwTex3;
	HTdword		dwTex4;
	HTdword		dwTex5;
	HTdword		dwItemR;
	HTdword		dwItemRTex;
	HTdword		dwItemL;
	HTdword		dwItemLTex;
	HTdword		dwTAM_STD;
	HTdword		dwTAM_WLK;
	HTdword		dwTAM_RUN;
	HTdword		dwTAM_IDL;
	HTdword		dwTAM_ATK1;
	HTdword		dwTAM_ATK2;
	HTdword		dwTAM_HIT;
	HTdword		dwTAM_DIE;
	HTdword		dwMaterialID;
	HTdword		dwMonFXID;
	HTfloat		fMonScale;
	HT_COLOR	clrMon;
} HT_ResTableType10;

typedef struct _HT_ResTableType11
{
	HTtchar   	strItemName[HT_MAX_XML_STR];
	HTdword		dwSocketModelID;
	HTdword		dwSocketTexID;
	HTdword		dwSecondSocketModelID;
	HTtchar   	strHideMeshName[HT_MAX_XML_STR];
	HTdword		dwFallenModelID;
	HTdword		dwFallenModelTexID;
	HTdword		dwInvenTexID;
	HTtchar   	strSocketName[HT_MAX_XML_STR];
	HTdword		dwWearItemID;
	HTdword		dwShoesItemID;
	HTdword		dwMaterialID;
	HTdword		dwEquipSoundID;
	HTdword		dwUnEquipSoundID;
	HTdword		dwItemType;
	HTdword		dwItemRefining012ID;
	HTdword		dwItemRefining345ID;
	HTdword		dwItemRefining678ID;
	HTdword		dwItemRefining910ID;
	HTdword		dwItemRefining1112ID;
	HTdword		dwItemRefining13ID;
	HTdword		dwItemRefining14ID;
	HTdword		dwItemRefining15ID;
} HT_ResTableType11;

typedef struct _HT_ResTableType13	// 20021113 HK : 수정
{
	HTdword		dwAttackSoundID1;
	HTdword		dwAttackSoundID2;						// 본 FX는 세 단계로 구성된다.
	HTdword		dwHitSoundID;							// 먼저 몬스터가 죽는 시점에 발생하는 FX,
	HTdword		dwHit2SoundID;							// 몬스터가 죽은 이후 Prana가 PC에게 날라가는 FX,
	HTdword		dwWalkSoundID;							// 프라나가 PC에 흡수되는 FX로 구성되어진다.
	HTdword		dwRunSoundID;							// 각각을 편의상 Activate, Follow, Impact로 명명한다.
	HTdword		dwIdleSoundID;							// 여기 나오는 FXID, "dwDieFX"는 Activate를 의미하고
	HTdword		dwDieSoundID;							// Follow는 "dwDieFX+1", Impact는 "dwDieFX+2"로 한다.
} HT_ResTableType13;

//typedef struct _HT_ResTableType15
//{
//	HTtchar   	strFileName[HT_MAX_XML_STR];
//	HTdword		dwDayFXID;		// 20021204 HK : 수정
//	HTdword		dwNightFXID;	// 20021204 HK : 수정 : 낮과 밤에 FX에 서로 다름을 처리하기 위함이다.
//	HTbool		bPick;
//} HT_ResTableType15;

typedef struct _HT_ResTableType20
{
	HTdword		dwImpactFX;

	HTdword		dwMan01AnimID;
	HTdword		dwMan02AnimID;
	HTdword		dwMan03AnimID;
	HTdword		dwWom01AnimID;
	HTdword		dwWom02AnimID;
	HTdword		dwWom03AnimID;

	HTdword		dwNAGSoundID1;
	HTdword		dwNAGSoundID2;
	HTdword		dwNAGSoundID3;
	HTdword		dwYAKSoundID1;
	HTdword		dwYAKSoundID2;
	HTdword		dwYAKSoundID3;
	HTdword		dwASUSoundID1;
	HTdword		dwASUSoundID2;
	HTdword		dwASUSoundID3;
	HTdword		dwDEVSoundID1;
	HTdword		dwDEVSoundID2;
	HTdword		dwDEVSoundID3;
	HTdword		dwKIMSoundID1;
	HTdword		dwKIMSoundID2;
	HTdword		dwKIMSoundID3;
	HTdword		dwGANSoundID1;
	HTdword		dwGANSoundID2;
	HTdword		dwGANSoundID3;
	HTdword		dwRAKSoundID1;
	HTdword		dwRAKSoundID2;
	HTdword		dwRAKSoundID3;
	HTdword		dwGARSoundID1;
	HTdword		dwGARSoundID2;
	HTdword		dwGARSoundID3;

	HTdword		dwAttackOKSoundID1;
	HTdword		dwAttackOKSoundID2;
	HTdword		dwAttackOKSoundID3;

	HTdword		dwSwingSoundID1;
	HTdword		dwSwingSoundID2;
	HTdword		dwSwingSoundID3;

	HTdword		dwManFApronAnimID1;
	HTdword		dwManBApronAnimID1;
	HTdword		dwWomFApronAnimID1;
	HTdword		dwWomBApronAnimID1;
	HTdword		dwManFApronAnimID2;
	HTdword		dwManBApronAnimID2;
	HTdword		dwWomFApronAnimID2;
	HTdword		dwWomBApronAnimID2;
	HTdword		dwManFApronAnimID3;
	HTdword		dwManBApronAnimID3;
	HTdword		dwWomFApronAnimID3;
	HTdword		dwWomBApronAnimID3;

	HTdword		dwATKSTDAniID;
	HTdword		dwATKWLKAniID;
	HTdword		dwATKRUNAniID;
	HTdword		dwHITAniID;

} HT_ResTableType20;

typedef struct _HT_ResTableType21
{
	HTtchar   	strFile[HT_MAX_XML_STR];
	HTfloat		fNAGScale;
	HTfloat		fASUScale;
	HTfloat		fYAKScale;
	HTfloat		fDEVScale;
	HTfloat		fKIMScale;
	HTfloat		fRAKScale;
	HTfloat		fGANScale;
	HTfloat		fGARScale;
} HT_ResTableType21;

typedef struct _HT_ResTableType23
{
	HTtchar   	strFile[HT_MAX_XML_STR];
	HTdword		dwHain1AniID;
	HTdword		dwHain2AniID;
} HT_ResTableType23;

typedef struct _HT_ResTableType24
{
	HTdword		dwColor;
} HT_ResTableType24;

typedef struct _HT_ResTableType25
{
	HTdword		dwFrom;
	HTdword		dwTo;
	HTtchar   	strName[HT_MAX_XML_STR];
} HT_ResTableType25;

typedef struct _HT_ResTableType26
{
	HTvector3	vecScaleStart;
	HTvector3	vecScaleEnd;
	HTdword		dwColorStart;
	HTdword		dwColorEnd;
	HTfloat		fStart2EndTime;
} HT_ResTableType26;

typedef struct _HT_ResTableType27
{
	HTtchar   	strName[HT_MAX_XML_STR];
	HTdword		dwStatus;
	HTdword		dwSound[4];
} HT_ResTableType27;

typedef struct _HT_ResTableType28
{
	HTdword		dwPortalID;
	HTchar  	strName[HT_MAX_XML_STR];

	HTdword		dwServerID;

	HTdword		dwStartX;
	HTdword		dwStartZ;
	HTdword		dwEndX;
	HTdword		dwEndZ;

	HTdword		dwGoPortal[5];
	HTdword		dwPortalFee[5];
	HTdword		dwPortalLevel[5];
} HT_ResTableType28;

typedef std::map<HTdword,HT_ResTableType01*>::value_type HT_ResTableType01_Value;
typedef std::map<HTdword,HT_ResTableType01*>::iterator HT_ResTableType01_It;
typedef std::map<HTdword,HT_ResTableType02*>::value_type HT_ResTableType02_Value;
typedef std::map<HTdword,HT_ResTableType02*>::iterator HT_ResTableType02_It;
typedef std::map<HTdword,HT_ResTableType03*>::value_type HT_ResTableType03_Value;
typedef std::map<HTdword,HT_ResTableType03*>::iterator HT_ResTableType03_It;
typedef std::map<HTdword,HT_ResTableType04*>::value_type HT_ResTableType04_Value;
typedef std::map<HTdword,HT_ResTableType04*>::iterator HT_ResTableType04_It;
typedef std::map<HTdword,HT_ResTableType05*>::value_type HT_ResTableType05_Value;
typedef std::map<HTdword,HT_ResTableType05*>::iterator HT_ResTableType05_It;
typedef std::map<HTdword,HT_ResTableType061*>::value_type HT_ResTableType061_Value;
typedef std::map<HTdword,HT_ResTableType061*>::iterator HT_ResTableType061_It;
typedef std::map<HTdword,HT_ResTableType062*>::value_type HT_ResTableType062_Value;
typedef std::map<HTdword,HT_ResTableType062*>::iterator HT_ResTableType062_It;
typedef std::map<HTdword,HT_ResTableType063*>::value_type HT_ResTableType063_Value;
typedef std::map<HTdword,HT_ResTableType063*>::iterator HT_ResTableType063_It;
typedef std::map<HTdword,HT_ResTableType07*>::value_type HT_ResTableType07_Value;
typedef std::map<HTdword,HT_ResTableType07*>::iterator HT_ResTableType07_It;
typedef std::map<HTdword,HT_ResTableType08*>::value_type HT_ResTableType08_Value;
typedef std::map<HTdword,HT_ResTableType08*>::iterator HT_ResTableType08_It;
typedef std::map<HTdword,HT_ResTableType081*>::value_type HT_ResTableType081_Value;
typedef std::map<HTdword,HT_ResTableType081*>::iterator HT_ResTableType081_It;
typedef std::map<HTdword,HT_ResTableType09*>::value_type HT_ResTableType09_Value;
typedef std::map<HTdword,HT_ResTableType09*>::iterator HT_ResTableType09_It;
typedef std::map<HTdword,HT_ResTableType10*>::value_type HT_ResTableType10_Value;
typedef std::map<HTdword,HT_ResTableType10*>::iterator HT_ResTableType10_It;
typedef std::map<HTdword,HT_ResTableType11*>::value_type HT_ResTableType11_Value;
typedef std::map<HTdword,HT_ResTableType11*>::iterator HT_ResTableType11_It;
typedef std::map<HTdword,HT_ResTableType13*>::value_type HT_ResTableType13_Value;
typedef std::map<HTdword,HT_ResTableType13*>::iterator HT_ResTableType13_It;
//typedef std::map<HTdword,HT_ResTableType15*>::value_type HT_ResTableType15_Value;
//typedef std::map<HTdword,HT_ResTableType15*>::iterator HT_ResTableType15_It;
typedef std::map<HTdword,HT_ResTableType20*>::value_type HT_ResTableType20_Value;
typedef std::map<HTdword,HT_ResTableType20*>::iterator HT_ResTableType20_It;
typedef std::map<HTdword,HT_ResTableType21*>::value_type HT_ResTableType21_Value;
typedef std::map<HTdword,HT_ResTableType21*>::iterator HT_ResTableType21_It;
typedef std::map<HTdword,HT_ResTableType23*>::value_type HT_ResTableType23_Value;
typedef std::map<HTdword,HT_ResTableType23*>::iterator HT_ResTableType23_It;
typedef std::map<HTdword,HT_ResTableType24*>::value_type HT_ResTableType24_Value;
typedef std::map<HTdword,HT_ResTableType24*>::iterator HT_ResTableType24_It;
typedef std::map<HTdword,HT_ResTableType25*>::value_type HT_ResTableType25_Value;
typedef std::map<HTdword,HT_ResTableType25*>::iterator HT_ResTableType25_It;
typedef std::map<HTdword,HT_ResTableType26*>::value_type HT_ResTableType26_Value;
typedef std::map<HTdword,HT_ResTableType26*>::iterator HT_ResTableType26_It;

typedef std::map<HTdword,HT_ResTableType27*>::value_type HT_ResTableType27_Value;
typedef std::map<HTdword,HT_ResTableType27*>::iterator HT_ResTableType27_It;

typedef std::map<HTdword,HT_ResTableType28*>::value_type HT_ResTableType28_Value;
typedef std::map<HTdword,HT_ResTableType28*>::iterator HT_ResTableType28_It;

//-------------------------------------------------------------------------------------

class CHTBaseResTable
{
public:
	CHTBaseResTable()
	{
		m_strTable = _T("");
		m_nItems = 0;
	}
	virtual ~CHTBaseResTable()	{}

	virtual HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable ) = 0;

	virtual HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable ) = 0;
	virtual HTRESULT	HT_hrSave( CHTFile* pFile ) = 0;

	virtual HTbool		HT_bGetName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTdword		HT_dwGetIDByIndex( HTuint idxRow )	{ return ( 0 ); }

	virtual HTbool		HT_bGetTHMFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetTMOFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetTMEFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetTCCFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetCFGFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetBMPFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }		// 20021106 대호
	virtual HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetOBJPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetOBJTEXPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMONPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMONANIPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMONTEXPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNPCPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNPCANIPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNPCTEXPAKFileName( HTdword dwID, CHTString& strFile )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetFXFilesName( HTdword dwID, CHTString& strName )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNPCSoundFilesName( HTdword dwID, CHTString& strName )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMonSoundFilesName( HTdword dwID, CHTString& strName )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMinimapFilesName( HTdword dwID, CHTString& strName )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNPCScriptFilesName( HTdword dwID, CHTString& strName )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetObjResFilesName( HTdword dwID, CHTString& strName ){ return HT_FALSE; };
	virtual HTbool		HT_bGetPopObjPackFilesName( HTdword dwID, CHTString& strName ){ return HT_FALSE; };
	virtual HTbool		HT_bGetPopTexPackFilesName( HTdword dwID, CHTString& strName ){ return HT_FALSE; };

	virtual HTbool		HT_bGetDiffuseColor( HTdword dwID, HT_COLOR& clrWant )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetAmbientColor( HTdword dwID, HT_COLOR& clrWant )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSpecularColor( HTdword dwID, HT_COLOR& clrWant )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetEmissiveColor( HTdword dwID, HT_COLOR& clrWant )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetPower( HTdword dwID, HTfloat& fPower )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDefaultUpWearID( HTdword dwID, HTdword& dwWearID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDefaultDownWearID( HTdword dwID, HTdword& dwWearID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDefaultHandWearID( HTdword dwID, HTdword& dwWearID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDefaultShoesID( HTdword dwID, HTdword& dwShoesID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeAID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeBID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeCID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeDID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeEID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeFID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeGID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHeadTypeHID( HTdword dwID, HTdword& dwHeadID )	{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetFaceMesh( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetFaceTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHairModelID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHairTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHairType( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetUpWearMeshes( HTdword dwID,
		HTdword& dwChestMesh, HTdword& dwChestTexID,
		HTdword& dwRUArmMesh, HTdword& dwLUArmMesh, HTdword& dwRUArmTexID, HTdword& dwLUArmTexID,
		HTdword& dwSkirtMesh, HTdword& dwSkirtTexID,
		HTdword& dwApronModelID, HTdword& dwApronTexID, HTdword& dwApronBackModelID, HTdword& dwApronBackTexID,
		HTdword& dwShoulderLModelID, HTdword& dwShoulderLTexID, HTdword& dwShoulderRModelID, HTdword& dwShoulderRTexID,
		HTbool& bSkirtType ) { return HT_FALSE; };

	virtual HTbool		HT_bGetDownWearMeshes( HTdword dwID,
		HTdword& dwPantsMesh, HTdword& dw2ndPantsMesh, HTdword& dwPantsTexID,
		HTdword& dwKneeLModelID, HTdword& dwKneeLTexID, HTdword& dwKneeRModelID, HTdword& dwKneeRTexID,
		HTdword& dwThighLModelID, HTdword& dwThighLTexID, HTdword& dwThighRModelID, HTdword& dwThighRTexID ) { return HT_FALSE; };

	virtual HTbool		HT_bGetHandWearMeshes( HTdword dwID,
		HTdword& dwRLArmMesh, HTdword& dwLLArmMesh, HTdword& dwRLArmTexID, HTdword& dwLLArmTexID,
		HTdword& dwRHandMesh, HTdword& dwLHandMesh, HTdword& dwRHandTexID, HTdword& dwLHandTexID ) { return HT_FALSE; };

	virtual HTbool		HT_bGetChestMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetChestTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetPantsMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetPantsTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRUArmMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLUArmMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRUArmTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLUArmTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRLArmMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLLArmMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRLArmTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLLArmTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRHandMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLHandMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRHandTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLHandTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSkirtMesh( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSkirtTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetApronModelID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetApronTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetApronBackModelID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetApronBackTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetShoulderLModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetShoulderLTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetShoulderRModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetShoulderRTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetKneeLModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKneeLTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKneeRModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKneeRTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetThighLModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetThighLTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetThighRModelID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetThighRTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetRBootsMesh( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetLBootsMesh( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetBootsTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX )		{ return HT_FALSE; }

	virtual HTbool		HT_bGetNAGID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetYAKID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetASUID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDEVID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKIMID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGANID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRAKID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGARID( HTdword dwID, HTdword& dwOutID )				{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetManAnim1ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetManAnim2ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetManAnim3ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWomAnim1ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWomAnim2ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWomAnim3ID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetAttackOKID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetAttackOKID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetAttackOKID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetSwingSoundID1( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSwingSoundID2( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSwingSoundID3( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetWPNATKSTDAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWPNATKWLKAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWPNATKRUNAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWPNHITAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }

	// For NPC only
	virtual HTbool		HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMOVAniID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetStateSoundID( HTdword dwID, HTdword& dwStateSoundID ){ return( HT_FALSE ); }	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	virtual HTbool		HT_bGetClickSoundID( HTdword dwID, HTdword& dwClickSoundID ){ return( HT_FALSE ); }	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	virtual HTbool		HT_bGetIdleFX( HTdword dwID, HTdword& dwIdleFX )			{ return( HT_FALSE ); }	// 20021103 HK : Idle 애니메이션이 시작할 때 같이 시작하는 FX
	virtual HTbool		HT_bGetMovSoundID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetWLKAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRUNAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetATK1AniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetATK2AniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetHITAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDIEAniID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMonFXID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMonScale( HTdword dwID, HTfloat& fScale )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetMonColor( HTdword dwID, HT_COLOR& clrMon )		{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetSocketModelID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSocketTexID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetFallenModelID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetFallenModelTexID( HTdword dwID, HTdword& dwFallenModelTexID ) { return( HT_FALSE ); }
	virtual HTbool		HT_bGetInvenTexID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetSocketName( HTdword dwID, CHTString& strFile )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetWearItemID( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetShoesItemID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetEquipSoundID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetUnEquipSoundID( HTdword dwID, HTdword& dwOutID )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemType( HTdword dwID, HTdword& dwOutID )			{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining012( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining345( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining678( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining910( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining1112( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining13( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining14( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetItemRifining15( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }

	virtual HTbool		HT_bGetNAGScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetASUScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetYAKScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDEVScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetKIMScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetRAKScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGANScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetGARScale( HTdword dwID, HTfloat& fFactor )		{ return( HT_FALSE ); }

	//20021101 HK : 폐기.. 기획변경
	//virtual HTbool		HT_bGetImpactFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetCastFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetActivateFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetStateFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetSkillIconID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }

	//virtual HTbool		HT_bGetMonNormalAtkFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonSpecialAtkFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonStateFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonIdleFXName( HTdword dwID, CHTString& strName )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonDieFXName( HTdword dwID, CHTString& strName )		{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonAttackSoundID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }
	//virtual HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwOutID )	{ return( HT_FALSE ); }

	// For Field FXMon
	virtual HTbool		HT_bGetMonAttackSoundID1( HTdword dwID, HTdword& dwAttackSoundID )	{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonAttackSoundID2( HTdword dwID, HTdword& dwAttackSoundID )	{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwHitSoundID )			{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonHit2SoundID( HTdword dwID, HTdword& dwHit2SoundID )		{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonWalkSoundID( HTdword dwID, HTdword& dwWalkSoundID )		{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonRunSoundID( HTdword dwID, HTdword& dwRunSoundID )			{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwIdleSoundID )		{ return HT_FALSE; };
	virtual HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwDieSoundID )			{ return HT_FALSE; };

	// For Field FX
	virtual HTbool		HT_bGetFXID( HTdword dwID, HTdword& dwOutID )						{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetDayFXID( HTdword dwID, HTdword& dwOutID )					{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetNightFXID( HTdword dwID, HTdword& dwOutID )					{ return( HT_FALSE ); }
	virtual HTbool		HT_bGetPickFlag( HTdword dwID, HTbool& bPick )						{ return( HT_FALSE ); }

	// 20021101 HK : For PC Skill

	// 20021101 HK : For Monster Skill

	// 20021101 HK : For FX

	virtual HTbool		HT_bGetManFApronAnimID1( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetManBApronAnimID1( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomFApronAnimID1( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomBApronAnimID1( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetManFApronAnimID2( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetManBApronAnimID2( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomFApronAnimID2( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomBApronAnimID2( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetManFApronAnimID3( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetManBApronAnimID3( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomFApronAnimID3( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetWomBApronAnimID3( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };

	virtual HTbool		HT_bGetNAGFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetNAGBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetYAKFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetYAKBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetASUFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetASUBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetDEVFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetDEVBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetKIMFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetKIMBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetGANFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetGANBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetRAKFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetRAKBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetGARFApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };
	virtual HTbool		HT_bGetGARBApronAnimID( HTdword dwID, HTdword& dwOutID )	  { return HT_FALSE; };

	virtual HTbool		HT_bGetSecondSocketModelID( HTdword dwID, HTdword& dwOutID )  { return HT_FALSE; };
	virtual HTbool		HT_bGetHideMeshName( HTdword dwID, CHTString& strName )		{ return HT_FALSE; };

	virtual HTbool		HT_bGetHair1AniID( HTdword dwID, HTdword& dwOutID )		{ return HT_FALSE; };
	virtual HTbool		HT_bGetHair2AniID( HTdword dwID, HTdword& dwOutID )		{ return HT_FALSE; };

	virtual HTbool		HT_bGetDWColor( HTdword dwID, HTdword& dwColor )		{ return HT_FALSE; };

	HTuint		HT_nGetItemCount()					{ return( m_nItems ); }
	CHTString&	HT_strGetTableName()				{ return( m_strTable ); }

	virtual HTbool		HT_bGetAreaFrom( HTdword dwID, HTdword& dwOutID ) { return HT_FALSE; };
	virtual HTbool		HT_bGetAreaTo( HTdword dwID, HTdword& dwOutID ) { return HT_FALSE; };
	virtual HTbool		HT_bGetAreaName( HTdword dwID, CHTString& strName ) { return HT_FALSE; };
	virtual HTbool		HT_bGetAreaName( HTdword dwFrom, HTdword dwTo, CHTString& strName ) { return HT_FALSE; };

	// 아이템 제련 Item Refining
	virtual HTbool		HT_bGetScaleStart( HTdword dwID, HTvector3& vecScaleStart ) { return HT_FALSE; };
	virtual HTbool		HT_bGetScaleEnd( HTdword dwID, HTvector3& vecScaleEnd ) { return HT_FALSE; };

	virtual HTbool		HT_bGetColorStart( HTdword dwID, HTdword& dwColorStart ) { return HT_FALSE; };
	virtual HTbool		HT_bGetColorEnd( HTdword dwID, HTdword& dwColorEnd ) { return HT_FALSE; };

	virtual HTbool		HT_bGetStart2EndTime( HTdword dwID, HTfloat& fStart2EndTime ) { return HT_FALSE; };

	virtual HTbool		HT_bGetItemRifiningScaleColorTime( HTdword dwID, HTvector3& vecScaleStart, HTvector3& vecScaleEnd, HTdword& dwColorStart, HTdword& dwColorEnd, HTfloat& fStart2EndTime ) { return HT_FALSE; }

	virtual HTdword		HT_dwGetFootSound( HTdword dwID, HTint iMapStatus, HTint iStatus ){ return 0; };
	virtual HTbool		HT_bGetMonModelTexItem( HTdword dwID,
		HTuint& nNumMesh, HTdword& dwBasicModel,
		HTdword& dwMesh1, HTdword& dwMesh2, HTdword& dwMesh3, HTdword& dwMesh4, HTdword& dwMesh5,
		HTdword& dwTex1, HTdword& dwTex2, HTdword& dwTex3, HTdword& dwTex4, HTdword& dwTex5,
		HTdword& dwItemR, HTdword& dwItemRTex, HTdword& dwItemL, HTdword& dwItemLTex ) { return HT_FALSE; }

protected:
	CHTString			m_strTable;
	HTuint				m_nItems;
};

class CHTResTableType01 : public CHTBaseResTable
{
public:
	CHTResTableType01();
	~CHTResTableType01();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType01*>	m_mapTable;
};

class CHTResTableType02 : public CHTBaseResTable
{
public:
	CHTResTableType02();
	~CHTResTableType02();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetTHMFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTMOFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTMEFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTCCFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetCFGFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetBMPFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID );
	HTbool		HT_bGetOBJPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetOBJTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONANIPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCANIPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetFXFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetNPCSoundFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetMonSoundFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetMinimapFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetNPCScriptFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetObjResFilesName( HTdword dwID, CHTString& strName );		// 오브젝트 리소스 분리 (20031008 DaeHo)
	HTbool		HT_bGetPopObjPackFilesName( HTdword dwID, CHTString& strName );		// 오브젝트 리소스 분리 (20031008 DaeHo)
	HTbool		HT_bGetPopTexPackFilesName( HTdword dwID, CHTString& strName );		// 오브젝트 리소스 분리 (20031008 DaeHo)


	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType02*>	m_mapTable;
};

class CHTResTableType03 : public CHTBaseResTable
{
public:
	CHTResTableType03();
	~CHTResTableType03();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetDiffuseColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetAmbientColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetSpecularColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetEmissiveColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetPower( HTdword dwID, HTfloat& fPower );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType03*>	m_mapTable;
};

class CHTResTableType04 : public CHTBaseResTable
{
public:
	CHTResTableType04();
	~CHTResTableType04();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID );
	HTbool		HT_bGetDefaultUpWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultDownWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultHandWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultShoesID( HTdword dwID, HTdword& dwShoesID );
	HTbool		HT_bGetHeadTypeAID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeBID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeCID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeDID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeEID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeFID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeGID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeHID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMaterialID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType04*>	m_mapTable;
};

class CHTResTableType05 : public CHTBaseResTable
{
public:
	CHTResTableType05();
	~CHTResTableType05();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetFaceMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFaceTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairType( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType05*>	m_mapTable;
};

//class CHTResTableType06 : public CHTBaseResTable
//{
//public:
//	CHTResTableType06();
//	~CHTResTableType06();
//
//	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
//	HTdword		HT_dwGetIDByIndex( HTuint idxRow );
//
//	HTbool		HT_bGetChestMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetChestTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetPantsMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetPantsTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRUArmMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLUArmMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRUArmTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLUArmTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRLArmMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLLArmMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRLArmTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLLArmTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRHandMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLHandMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetRHandTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetLHandTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetSkirtMesh( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetSkirtTexID( HTdword dwID, HTdword& dwOutID );
//
//	HTbool		HT_bGetApronModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetApronTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetApronBackModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetApronBackTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetShoulderLModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetShoulderLTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetShoulderRModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetShoulderRTexID( HTdword dwID, HTdword& dwOutID );
//
//	HTbool		HT_bGetKneeLModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetKneeLTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetKneeRModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetKneeRTexID( HTdword dwID, HTdword& dwOutID );
//
//	HTbool		HT_bGetThighLModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetThighLTexID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetThighRModelID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetThighRTexID( HTdword dwID, HTdword& dwOutID );
//
//	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
//	HTRESULT	HT_hrSave( CHTFile* pFile );
//
//private:
//	std::map<HTdword,HT_ResTableType06*>	m_mapTable;
//};

class CHTResTableType061 : public CHTBaseResTable
{
public:
	CHTResTableType061();
	~CHTResTableType061();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	HTbool		HT_bGetUpWearMeshes( HTdword dwID,
		HTdword& dwChestMesh, HTdword& dwChestTexID,
		HTdword& dwRUArmMesh, HTdword& dwLUArmMesh, HTdword& dwRUArmTexID, HTdword& dwLUArmTexID,
		HTdword& dwSkirtMesh, HTdword& dwSkirtTexID,
		HTdword& dwApronModelID, HTdword& dwApronTexID, HTdword& dwApronBackModelID, HTdword& dwApronBackTexID,
		HTdword& dwShoulderLModelID, HTdword& dwShoulderLTexID, HTdword& dwShoulderRModelID, HTdword& dwShoulderRTexID,
		HTbool& bSkirtType );

private:
	std::map<HTdword,HT_ResTableType061*>	m_mapTable;
};

class CHTResTableType062 : public CHTBaseResTable
{
public:
	CHTResTableType062();
	~CHTResTableType062();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	HTbool		HT_bGetDownWearMeshes( HTdword dwID,
		HTdword& dwPantsMesh, HTdword& dw2ndPantsMesh, HTdword& dwPantsTexID,
		HTdword& dwKneeLModelID, HTdword& dwKneeLTexID, HTdword& dwKneeRModelID, HTdword& dwKneeRTexID,
		HTdword& dwThighLModelID, HTdword& dwThighLTexID, HTdword& dwThighRModelID, HTdword& dwThighRTexID );

private:
	std::map<HTdword,HT_ResTableType062*>	m_mapTable;
};

class CHTResTableType063 : public CHTBaseResTable
{
public:
	CHTResTableType063();
	~CHTResTableType063();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	HTbool		HT_bGetHandWearMeshes( HTdword dwID,
		HTdword& dwRLArmMesh, HTdword& dwLLArmMesh, HTdword& dwRLArmTexID, HTdword& dwLLArmTexID,
		HTdword& dwRHandMesh, HTdword& dwLHandMesh, HTdword& dwRHandTexID, HTdword& dwLHandTexID );

private:
	std::map<HTdword,HT_ResTableType063*>	m_mapTable;
};


class CHTResTableType07 : public CHTBaseResTable
{
public:
	CHTResTableType07();
	~CHTResTableType07();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetRBootsMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLBootsMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetBootsTexID( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType07*>	m_mapTable;
};

class CHTResTableType08 : public CHTBaseResTable
{
public:
	CHTResTableType08();
	~CHTResTableType08();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetNAGID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetNAGBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARBApronAnimID( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType08*>	m_mapTable;
};

class CHTResTableType081 : public CHTBaseResTable
{
public:
	CHTResTableType081();
	~CHTResTableType081();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetNAGID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARID( HTdword dwID, HTdword& dwOutID );

private:
	std::map<HTdword,HT_ResTableType081*>	m_mapTable;
};

class CHTResTableType09 : public CHTBaseResTable
{
public:
	CHTResTableType09();
	~CHTResTableType09();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID );
	HTbool		HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMOVAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID );			// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetStateSoundID( HTdword dwID, HTdword& dwStateSoundID );	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetClickSoundID( HTdword dwID, HTdword& dwClickSoundID );	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetIdleFX( HTdword dwID, HTdword& dwIdleFX );				// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetMovSoundID( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType09*>	m_mapTable;
};

class CHTResTableType10 : public CHTBaseResTable
{
public:
	CHTResTableType10();
	~CHTResTableType10();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	//HTbool		HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID );
	HTbool		HT_bGetMonModelTexItem( HTdword dwID,
		HTuint& nNumMesh, HTdword& dwBasicModel,
		HTdword& dwMesh1, HTdword& dwMesh2, HTdword& dwMesh3, HTdword& dwMesh4, HTdword& dwMesh5,
		HTdword& dwTex1, HTdword& dwTex2, HTdword& dwTex3, HTdword& dwTex4, HTdword& dwTex5,
		HTdword& dwItemR, HTdword& dwItemRTex, HTdword& dwItemL, HTdword& dwItemLTex );

	HTbool		HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWLKAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRUNAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetATK1AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetATK2AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHITAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDIEAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMonFXID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMonScale( HTdword dwID, HTfloat& fScale );
	HTbool		HT_bGetMonColor( HTdword dwID, HT_COLOR& clrMon );

	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID );
	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType10*>	m_mapTable;
};

class CHTResTableType11 : public CHTBaseResTable
{
public:
	CHTResTableType11();
	~CHTResTableType11();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetSocketModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSocketTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFallenModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFallenModelTexID( HTdword dwID, HTdword& dwFallenModelTexID );
	HTbool		HT_bGetInvenTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSocketName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetWearItemID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoesItemID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID );
	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetEquipSoundID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetUnEquipSoundID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSecondSocketModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHideMeshName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetItemType( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining012( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining345( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining678( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining910( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining1112( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining13( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining14( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining15( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType11*>	m_mapTable;
};

//20021101 HK : 폐기.. 기획변경
//class CHTResTableType12 : public CHTBaseResTable
//{
//public:
//	CHTResTableType12();
//	~CHTResTableType12();
//
//	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
//	HTdword		HT_dwGetIDByIndex( HTuint idxRow );
//
//	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetImpactFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetCastFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetActivateFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetStateFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetSkillIconID( HTdword dwID, HTdword& dwOutID );
//
//private:
//	std::map<HTdword,HT_ResTableType12*>	m_mapTable;
//};

//20021101 HK : 폐기.. 기획변경
//class CHTResTableType13 : public CHTBaseResTable
//{
//public:
//	CHTResTableType13();
//	~CHTResTableType13();
//
//	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
//	HTdword		HT_dwGetIDByIndex( HTuint idxRow );
//
//	HTbool		HT_bGetMonNormalAtkFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetMonSpecialAtkFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetMonStateFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetMonIdleFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetMonDieFXName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetMonAttackSoundID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwOutID );
//	HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwOutID );
//
//private:
//	std::map<HTdword,HT_ResTableType13*>	m_mapTable;
//};

class CHTResTableType13 : public CHTBaseResTable
{
public:
	CHTResTableType13();
	~CHTResTableType13();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetMonAttackSoundID1( HTdword dwID, HTdword& dwAttackSoundID );
	HTbool		HT_bGetMonAttackSoundID2( HTdword dwID, HTdword& dwAttackSoundID );
	HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwHitSoundID );
	HTbool		HT_bGetMonHit2SoundID( HTdword dwID, HTdword& dwHit2SoundID );
	HTbool		HT_bGetMonWalkSoundID( HTdword dwID, HTdword& dwWalkSoundID );
	HTbool		HT_bGetMonRunSoundID( HTdword dwID, HTdword& dwRunSoundID );
	HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwIdleSoundID );
	HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwDieSoundID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType13*>	m_mapTable;
};

//class CHTResTableType14 : public CHTBaseResTable
//{
//public:
//	CHTResTableType14();
//	~CHTResTableType14();
//
//	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
//	HTdword		HT_dwGetIDByIndex( HTuint idxRow );
//
//	HTbool		HT_bGetFieldWhenActive( HTdword dwID, HTdword& dwWhen );
//	HTbool		HT_bGetFieldFxName( HTdword dwID, CHTString& strName );
//	HTbool		HT_bGetFieldWhereID( HTdword dwID, HTdword& dwWhen );
//
//private:
//	std::map<HTdword,HT_ResTableType14*>	m_mapTable;
//};

//class CHTResTableType15 : public CHTBaseResTable
//{
//public:
//	CHTResTableType15();
//	~CHTResTableType15();
//
//	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
//	HTdword		HT_dwGetIDByIndex( HTuint idxRow );
//
//	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );
//	HTbool		HT_bGetDayFXID( HTdword dwID, HTdword& dwFXID );
//	HTbool		HT_bGetNightFXID( HTdword dwID, HTdword& dwFXID );
//	HTbool		HT_bGetPickFlag( HTdword dwID, HTbool& bPick );
//
//	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
//	HTRESULT	HT_hrSave( CHTFile* pFile );
//
//private:
//	std::map<HTdword,HT_ResTableType15*>	m_mapTable;
//};

// 20021101 HK : For PC Skill

// 20021101 HK : For FX

// 20021101 HK : For Monster Skill

class CHTResTableType20 : public CHTBaseResTable
{
public:
	CHTResTableType20();
	~CHTResTableType20();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX );

	HTbool		HT_bGetManAnim1ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManAnim2ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManAnim3ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim1ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim2ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim3ID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetAttackOKID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAttackOKID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAttackOKID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetSwingSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSwingSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSwingSoundID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetManFApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManFApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManFApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetWPNATKSTDAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNATKWLKAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNATKRUNAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNHITAniID( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType20*>	m_mapTable;
};

class CHTResTableType21 : public CHTBaseResTable
{
public:
	CHTResTableType21();
	~CHTResTableType21();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNAGScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetASUScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetYAKScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetDEVScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetKIMScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetRAKScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetGANScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetGARScale( HTdword dwID, HTfloat& fFactor );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType21*>	m_mapTable;
};


class CHTResTableType23 : public CHTBaseResTable
{
public:
	CHTResTableType23();
	~CHTResTableType23();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetHair1AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHair2AniID( HTdword dwID, HTdword& dwOutID );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType23*>	m_mapTable;
};

class CHTResTableType24 : public CHTBaseResTable
{
public:
	CHTResTableType24();
	~CHTResTableType24();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetDWColor( HTdword dwID, HTdword& dwColor );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType24*>	m_mapTable;
};

class CHTResTableType25 : public CHTBaseResTable
{
public:
	CHTResTableType25();
	~CHTResTableType25();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetAreaFrom( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAreaTo( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAreaName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetAreaName( HTdword dwFrom, HTdword dwTo, CHTString& strFile );

	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

private:
	std::map<HTdword,HT_ResTableType25*>	m_mapTable;
};

class CHTResTableType26 : public CHTBaseResTable
{
public:
	CHTResTableType26();
	~CHTResTableType26();

	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	HTbool		HT_bGetScaleStart( HTdword dwID, HTvector3& vecScaleStart );
	HTbool		HT_bGetScaleEnd( HTdword dwID, HTvector3& vecScaleEnd );

	HTbool		HT_bGetColorStart( HTdword dwID, HTdword& dwColorStart );
	HTbool		HT_bGetColorEnd( HTdword dwID, HTdword& dwColorEnd );

	HTbool		HT_bGetStart2EndTime( HTdword dwID, HTfloat& fStart2EndTime );

	HTbool		HT_bGetItemRifiningScaleColorTime( HTdword dwID, HTvector3& vecScaleStart, HTvector3& vecScaleEnd, HTdword& dwColorStart, HTdword& dwColorEnd, HTfloat& fStart2EndTime );

private:
	std::map<HTdword,HT_ResTableType26*>	m_mapTable;
};

class CHTResTableType27 : public CHTBaseResTable
{
public:
	CHTResTableType27();
	~CHTResTableType27();

	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );

	HTdword		HT_dwGetFootSound( HTdword dwID, HTint iMapStatus, HTint iStatus );
private:
	std::map<HTdword,HT_ResTableType27*>	m_mapTable;
};



//-------------------------------------------------------------------------------------
// 이름 : 역참조 비교연산자형 선언
// 설명 : STL의 map에 첫번째인 키값이 스트링포인터이기때문에 비교형이 선언되어야
// 제대로 값들이 정렬되어 들어가고, 찾을 수 있다. 그렇지 않으면 포인터값으로
// 비교를 하게되는 상황이 벌어진다. 
struct SHTDerefLessStr
{
	template<typename PtrType>
		HTbool operator()( PtrType pStr1, PtrType pStr2 ) const
	{
		HTint i = stricmp( pStr1, pStr2 );
		if ( i < 0 )
			return ( HT_TRUE );
		else
			return ( HT_FALSE );
	}
};

typedef std::map<HTtchar*,CHTBaseResTable*,SHTDerefLessStr>::value_type HT_ResMgr_Value;
typedef std::map<HTtchar*,CHTBaseResTable*,SHTDerefLessStr>::iterator HT_ResMgr_It;

//-------------------------------------------------------------------------------------

class CHTResMgr
{
public:
	CHTResMgr();
	~CHTResMgr();

	HTRESULT	HT_hrInit( CHTString& strXMLFile );
	HTtchar*	HT_pGetTableName( HTdword dwID );
	HTdword		HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow );
	HTuint		HT_nGetItemCount( CHTString& strTable );
	CHTBaseResTable* HT_pGetTable( HTdword dwID );

	HTRESULT	HT_hrLoad( CHTString& strFile );
	HTRESULT	HT_hrSave( CHTString& strFile );

	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetFileName( HTdword dwID, CHTString& strFile );

	HTbool		HT_bGetTHMFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTMOFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTMEFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetTCCFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetCFGFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetBMPFileName( HTdword dwID, CHTString& strFile );	// 20021106 대호
	HTbool		HT_bGetMaterialID( HTdword dwID, HTdword& dwMtrlID );
	HTbool		HT_bGetOBJPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetOBJTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONANIPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetMONTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCANIPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetNPCTEXPAKFileName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetFXFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetNPCSoundFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetMonSoundFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetMinimapFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetNPCScriptFilesName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetObjResFilesName( HTdword dwID, CHTString& strName );	// 오브젝트 리소스 분리 (20031008 DaeHo)
	HTbool		HT_bGetPopObjPackFilesName( HTdword dwID, CHTString& strName );	// 오브젝트 리소스 분리 (20031008 DaeHo)
	HTbool		HT_bGetPopTexPackFilesName( HTdword dwID, CHTString& strName );	// 오브젝트 리소스 분리 (20031008 DaeHo)

	// 20030308 몬스터의 ID로부터 몬스터FX ID를 구하기 위함
	HTbool		HT_bGetMonFXIDFromMonID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetDiffuseColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetAmbientColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetSpecularColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetEmissiveColor( HTdword dwID, HT_COLOR& clrWant );
	HTbool		HT_bGetPower( HTdword dwID, HTfloat& fPower );

	HTbool		HT_bGetModelFileID( HTdword dwID, HTdword& dwModelFileID );
	HTbool		HT_bGetDefaultUpWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultDownWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultHandWearID( HTdword dwID, HTdword& dwWearID );
	HTbool		HT_bGetDefaultShoesID( HTdword dwID, HTdword& dwShoesID );
	HTbool		HT_bGetHeadTypeAID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeBID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeCID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeDID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeEID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeFID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeGID( HTdword dwID, HTdword& dwHeadID );
	HTbool		HT_bGetHeadTypeHID( HTdword dwID, HTdword& dwHeadID );

	HTbool		HT_bGetFaceMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFaceTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHairType( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetUpWearMeshes( HTdword dwID,
		HTdword& dwChestMesh, HTdword& dwChestTexID,
		HTdword& dwRUArmMesh, HTdword& dwLUArmMesh, HTdword& dwRUArmTexID, HTdword& dwLUArmTexID,
		HTdword& dwSkirtMesh, HTdword& dwSkirtTexID,
		HTdword& dwApronModelID, HTdword& dwApronTexID, HTdword& dwApronBackModelID, HTdword& dwApronBackTexID,
		HTdword& dwShoulderLModelID, HTdword& dwShoulderLTexID, HTdword& dwShoulderRModelID, HTdword& dwShoulderRTexID,
		HTbool& bSkirtType );

	HTbool		HT_bGetDownWearMeshes( HTdword dwID,
		HTdword& dwPantsMesh, HTdword& dw2ndPantsMesh, HTdword& dwPantsTexID,
		HTdword& dwKneeLModelID, HTdword& dwKneeLTexID, HTdword& dwKneeRModelID, HTdword& dwKneeRTexID,
		HTdword& dwThighLModelID, HTdword& dwThighLTexID, HTdword& dwThighRModelID, HTdword& dwThighRTexID );

	HTbool		HT_bGetHandWearMeshes( HTdword dwID,
		HTdword& dwRLArmMesh, HTdword& dwLLArmMesh, HTdword& dwRLArmTexID, HTdword& dwLLArmTexID,
		HTdword& dwRHandMesh, HTdword& dwLHandMesh, HTdword& dwRHandTexID, HTdword& dwLHandTexID );

	HTbool		HT_bGetChestMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetChestTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetPantsMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetPantsTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRUArmMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLUArmMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRUArmTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLUArmTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRLArmMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLLArmMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRLArmTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLLArmTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRHandMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLHandMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRHandTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLHandTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSkirtMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSkirtTexID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetApronModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetApronTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetApronBackModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetApronBackTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoulderLModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoulderLTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoulderRModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoulderRTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKneeLModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKneeLTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKneeRModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKneeRTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetThighLModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetThighLTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetThighRModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetThighRTexID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetRBootsMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetLBootsMesh( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetBootsTexID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX );

	HTbool		HT_bGetNAGID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetManAnim1ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManAnim2ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManAnim3ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim1ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim2ID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomAnim3ID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID1( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID2( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKSoundID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARSoundID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetSTDAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMOVAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWLKAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRUNAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetIDLAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetStateSoundID( HTdword dwID, HTdword& dwStateSoundID );	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetClickSoundID( HTdword dwID, HTdword& dwClickSoundID );	// 20021103 HK : 종현 선배님의 XML 파일에 있는 내용을 참조하여 추가
	HTbool		HT_bGetIdleFX( HTdword dwID, HTdword& dwIdleFX );				// 20021103 HK : Idle 애니메이션이 시작할 때 같이 시작하는 FX
	HTbool		HT_bGetMovSoundID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetATK1AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetATK2AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHITAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDIEAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMonFXID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetMonScale( HTdword dwID, HTfloat& fScale );
	HTbool		HT_bGetMonColor( HTdword dwID, HT_COLOR& clrMon );

	HTbool		HT_bGetSocketModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSocketTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFallenModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetFallenModelTexID( HTdword dwID, HTdword& dwFallenModelTexID );
	HTbool		HT_bGetInvenTexID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSocketName( HTdword dwID, CHTString& strFile );
	HTbool		HT_bGetWearItemID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetShoesItemID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetEquipSoundID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetUnEquipSoundID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemType( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining012( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining345( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining678( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining910( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining1112( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining13( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining14( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetItemRifining15( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetASUScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetYAKScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetDEVScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetKIMScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetRAKScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetGANScale( HTdword dwID, HTfloat& fFactor );
	HTbool		HT_bGetGARScale( HTdword dwID, HTfloat& fFactor );

	HTbool		HT_bGetAttackOKID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAttackOKID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetAttackOKID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetSwingSoundID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSwingSoundID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetSwingSoundID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetWPNATKSTDAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNATKWLKAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNATKRUNAniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWPNHITAniID( HTdword dwID, HTdword& dwOutID );


	//20021101 HK : 폐기.. 기획변경
	//HTbool		HT_bGetImpactFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetCastFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetActivateFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetStateFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetSkillIconID( HTdword dwID, HTdword& dwOutID );

	//20021101 HK : 폐기.. 기획변경
	//HTbool		HT_bGetMonNormalAtkFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetMonSpecialAtkFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetMonStateFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetMonIdleFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetMonDieFXName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetMonAttackSoundID( HTdword dwID, HTdword& dwOutID );
	//HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwOutID );
	//HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwOutID );
	//HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwOutID );

	// For FX Mon
	HTbool		HT_bGetMonAttackSoundID1( HTdword dwID, HTdword& dwAttackSoundID );
	HTbool		HT_bGetMonAttackSoundID2( HTdword dwID, HTdword& dwAttackSoundID );
	HTbool		HT_bGetMonHitSoundID( HTdword dwID, HTdword& dwHitSoundID );
	HTbool		HT_bGetMonHit2SoundID( HTdword dwID, HTdword& dwHit2SoundID );
	HTbool		HT_bGetMonWalkSoundID( HTdword dwID, HTdword& dwWalkSoundID );
	HTbool		HT_bGetMonRunSoundID( HTdword dwID, HTdword& dwRunSoundID );
	HTbool		HT_bGetMonIdleSoundID( HTdword dwID, HTdword& dwIdleSoundID );
	HTbool		HT_bGetMonDieSoundID( HTdword dwID, HTdword& dwDieSoundID );

	// For Field FX
	//	HTbool		HT_bGetFieldWhenActive( HTdword dwID, HTdword& dwWhen );
	//	HTbool		HT_bGetFieldFxName( HTdword dwID, CHTString& strName );
	//	HTbool		HT_bGetFieldWhereID( HTdword dwID, HTdword& dwWhen );
	//	HTbool		HT_bGetFXID( HTdword dwID, HTdword& dwOutID );

	//HTbool		HT_bGetDayFXID( HTdword dwID, HTdword& dwFXID );
	//HTbool		HT_bGetNightFXID( HTdword dwID, HTdword& dwFXID );
	//HTbool		HT_bGetPickFlag( HTdword dwID, HTbool& bPick );

	// 20021101 HK : For PC Skill


	// 20021101 HK : For FX

	HTbool		HT_bGetManFApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID1( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManFApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID2( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManFApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetManBApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomFApronAnimID3( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetWomBApronAnimID3( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetNAGFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetNAGBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetYAKBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetASUBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetDEVBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetKIMBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGANBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetRAKBApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARFApronAnimID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetGARBApronAnimID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetSecondSocketModelID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHideMeshName( HTdword dwID, CHTString& strName );

	HTbool		HT_bGetHair1AniID( HTdword dwID, HTdword& dwOutID );
	HTbool		HT_bGetHair2AniID( HTdword dwID, HTdword& dwOutID );

	HTbool		HT_bGetGuildBackTex( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetGuildEmblemTex( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetGuildTitleTex( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetGuildEmblemDWColor( HTdword dwID, HTdword& dwColor );

	HTbool		HT_bGetAreaFrom( HTdword dwID, HTdword& dwFrom );
	HTbool		HT_bGetAreaTo( HTdword dwID, HTdword& dwFrom );
	HTbool		HT_bGetAreaName( HTdword dwID, CHTString& strName );
	//HTbool		HT_bGetAreaName( HTdword dwFrom, HTdword dwTo, CHTString& strFile );
	HTbool		HT_bGetAreaName(HTdword dwID, HTint iFromID, HTint iToID, CHTString& strAreaName);

	HTbool		HT_bGetItemRifiningScaleStart( HTdword dwID, HTvector3& vecScaleStart );
	HTbool		HT_bGetItemRifiningScaleEnd( HTdword dwID, HTvector3& vecScaleEnd );
	HTbool		HT_bGetItemRifiningColorStart( HTdword dwID, HTdword& dwColorStart );
	HTbool		HT_bGetItemRifiningColorEnd( HTdword dwID, HTdword& dwColorEnd );
	HTbool		HT_bGetItemRifiningStart2EndTime( HTdword dwID, HTfloat& fStart2EndTime );
	HTbool		HT_bGetItemRifiningScaleColorTime( HTdword dwID, HTvector3& vecScaleStart, HTvector3& vecScaleEnd, HTdword& dwColorStart, HTdword& dwColorEnd, HTfloat& fStart2EndTime );

	HTdword		HT_dwGetFootSound( HTdword dwID, HTint iMapStatus, HTint iStatus );
	HTbool		HT_bGetMonModelTexItem( HTdword dwID,
		HTuint& nNumMesh, HTdword& dwBasicModel,
		HTdword& dwMesh1, HTdword& dwMesh2, HTdword& dwMesh3, HTdword& dwMesh4, HTdword& dwMesh5,
		HTdword& dwTex1, HTdword& dwTex2, HTdword& dwTex3, HTdword& dwTex4, HTdword& dwTex5,
		HTdword& dwItemR, HTdword& dwItemRTex, HTdword& dwItemL, HTdword& dwItemLTex );

private:

	std::map<HTtchar*,CHTBaseResTable*,SHTDerefLessStr>	m_mapTables;
};

#endif	// #ifndef _HTRESMGR_H_