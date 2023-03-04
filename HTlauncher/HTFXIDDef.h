#ifndef _HTFXIDDEF_H_
#define _HTFXIDDEF_H_

#define HT_FXID_PCSKILL_START				3001
#define HT_FXID_PCSKILL_END					3499

//#define HT_FXID_MONSTERSKILL_START			3501
//#define HT_FXID_MONSTERSKILL_END			3999
#define HT_FXID_MONSTERSKILL_START			41001
#define HT_FXID_MONSTERSKILL_END			43999

#define HT_FXID_MONSTEREFFECT_START			61001
#define HT_FXID_MONSTEREFFECT_END			61999

//#define HT_FXID_FXNAME_START				1000001
//#define HT_FXID_FXNAME_END					1099999

	#define HT_FXID_FXNAME_PCSKILL_START		1000001
	#define HT_FXID_FXNAME_PCSKILL_END			1009999

	#define HT_FXID_FXNAME_PCEFFECT_START		1010001
	#define HT_FXID_FXNAME_PCEFFECT_END			1019999

	#define HT_FXID_FXNAME_MONSTERSKILL_START	1200001
	#define HT_FXID_FXNAME_MONSTERSKILL_END		1299999

	#define HT_FXID_FXNAME_MONSTERETC_START		1300001
	#define HT_FXID_FXNAME_MONSTERETC_END		1399999

	#define HT_FXID_FXNAME_FIELDEFFECT_START	1400001
	#define HT_FXID_FXNAME_FIELDEFFECT_END		1499999

#define HT_FXID_PCSKILLTYPE_START			1100001
#define HT_FXID_PCSKILLTYPE_END				1199999

	#define HT_FXID_PCSKILLACTION_START			1100001
	#define HT_FXID_PCSKILLACTION_END			1109999

	#define HT_FXID_PCSKILLACTIVE_START			1110001
	#define HT_FXID_PCSKILLACTIVE_END			1119999

#define HT_FXID_MODEL_START					2000001
#define HT_FXID_MODEL_END					2099999

	#define HT_FXID_MODEL_PC_START				2000001
	#define HT_FXID_MODEL_PC_END				2009999

	#define HT_FXID_MODEL_MAP_START				2010001
	#define HT_FXID_MODEL_MAP_END				2019999

#define HT_FXID_TEXTURE_START				2100001
#define HT_FXID_TEXTURE_END					2199999

	#define HT_FXID_TEXTURE_PC_START			2100001
	#define HT_FXID_TEXTURE_PC_END				2109999

	#define HT_FXID_TEXTURE_MAP_START			2110001
	#define HT_FXID_TEXTURE_MAP_END				2119999

#define HT_FXID_ANIMATION_START				2200001
#define HT_FXID_ANIMATION_END				2299999

	#define HT_FXID_ANIMATION_PC_START			2200001
	#define HT_FXID_ANIMATION_PC_END			2209999

	#define HT_FXID_ANIMATION_MAP_START			2210001
	#define HT_FXID_ANIMATION_MAP_END			2219999

#define HT_FXID_SOUND_START					2300001
#define HT_FXID_SOUND_END					2399999

	#define HT_FXID_SOUND_PC_START				2300001
	#define HT_FXID_SOUND_PC_END				2309999

	#define HT_FXID_SOUND_MAP_START				2310001
	#define HT_FXID_SOUND_MAP_END				2319999

#define HT_FXRES_TABLENAME_PCSKILL				_T("PCSkill")
#define HT_FXRES_TABLENAME_PCSKILLACTION		_T("PCSkillAction")
#define HT_FXRES_TABLENAME_PCSKILLACTIVE		_T("PCSkillActive")
#define HT_FXRES_TABLENAME_FXSKILL				_T("FXSkill")
#define HT_FXRES_TABLENAME_FXETC				_T("FXEtc")
#define HT_FXRES_TABLENAME_MONSTERSKILL			_T("MonsterSkill")
#define HT_FXRES_TABLENAME_MONSTEREFFECT		_T("MonsterEffect")
#define HT_FXRES_TABLENAME_FXMONSTERSKILL		_T("FXMonsterSkill")
#define HT_FXRES_TABLENAME_FXMONSTERETC			_T("FXMonsterEtc")
#define HT_FXRES_TABLENAME_FXFIELD				_T("FXField")
#define HT_FXRES_TABLENAME_MODEL				_T("Model")
#define HT_FXRES_TABLENAME_TEXTURE				_T("Texture")
#define HT_FXRES_TABLENAME_ANIMATION			_T("Animation")
#define HT_FXRES_TABLENAME_SOUND				_T("Sound")

#define HT_IS_PCSKILL( i )						( ( (i) >= HT_FXID_PCSKILL_START ) && ( (i) <= HT_FXID_PCSKILL_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_PCSKILLACTION( i )				( ( (i) >= HT_FXID_PCSKILLACTION_START ) && ( (i) <= HT_FXID_PCSKILLACTION_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_PCSKILLACTIVE( i )				( ( (i) >= HT_FXID_PCSKILLACTIVE_START ) && ( (i) <= HT_FXID_PCSKILLACTIVE_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_MONSTERSKILL( i )					( ( (i) >= HT_FXID_MONSTERSKILL_START ) && ( (i) <= HT_FXID_MONSTERSKILL_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_MONSTEREFFECT( i )				( ( (i) >= HT_FXID_MONSTEREFFECT_START ) && ( (i) <= HT_FXID_MONSTEREFFECT_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_FXNAME( i )						( ( (i) >= HT_FXID_FXNAME_START ) && ( (i) <= HT_FXID_FXNAME_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXNAME_PCSKILL( i )			( ( (i) >= HT_FXID_FXNAME_PCSKILL_START ) && ( (i) <= HT_FXID_FXNAME_PCSKILL_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXNAME_PCEFFECT( i )			( ( (i) >= HT_FXID_FXNAME_PCEFFECT_START ) && ( (i) <= HT_FXID_FXNAME_PCEFFECT_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXNAME_MONSTERSKILL( i )		( ( (i) >= HT_FXID_FXNAME_MONSTERSKILL_START ) && ( (i) <= HT_FXID_FXNAME_MONSTERSKILL_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXNAME_MONSTERETC( i )		( ( (i) >= HT_FXID_FXNAME_MONSTERETC_START ) && ( (i) <= HT_FXID_FXNAME_MONSTERETC_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXNAME_FIELDEFFECT( i )		( ( (i) >= HT_FXID_FXNAME_FIELDEFFECT_START ) && ( (i) <= HT_FXID_FXNAME_FIELDEFFECT_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_FXMODEL( i )						( ( (i) >= HT_FXID_MODEL_START ) && ( (i) <= HT_FXID_MODEL_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXMODEL_PC( i )				( ( (i) >= HT_FXID_MODEL_PC_START ) && ( (i) <= HT_FXID_MODEL_PC_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXMODEL_MAP( i )				( ( (i) >= HT_FXID_MODEL_MAP_START ) && ( (i) <= HT_FXID_MODEL_MAP_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_FXTEXTURE( i )					( ( (i) >= HT_FXID_TEXTURE_START ) && ( (i) <= HT_FXID_TEXTURE_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXTEXTURE_PC( i )				( ( (i) >= HT_FXID_TEXTURE_PC_START ) && ( (i) <= HT_FXID_TEXTURE_PC_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXTEXTURE_MAP( i )			( ( (i) >= HT_FXID_TEXTURE_MAP_START ) && ( (i) <= HT_FXID_TEXTURE_MAP_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_FXANIMATION( i )					( ( (i) >= HT_FXID_ANIMATION_START ) && ( (i) <= HT_FXID_ANIMATION_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXANIMATION_PC( i )			( ( (i) >= HT_FXID_ANIMATION_PC_START ) && ( (i) <= HT_FXID_ANIMATION_PC_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXANIMATION_MAP( i )			( ( (i) >= HT_FXID_ANIMATION_MAP_START ) && ( (i) <= HT_FXID_ANIMATION_MAP_END ) ? HT_TRUE : HT_FALSE )
#define HT_IS_FXSOUND( i )						( ( (i) >= HT_FXID_SOUND_START ) && ( (i) <= HT_FXID_SOUND_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXSOUND_PC( i )				( ( (i) >= HT_FXID_SOUND_PC_START ) && ( (i) <= HT_FXID_SOUND_PC_END ) ? HT_TRUE : HT_FALSE )
	#define HT_IS_FXSOUND_MAP( i )				( ( (i) >= HT_FXID_SOUND_MAP_START ) && ( (i) <= HT_FXID_SOUND_MAP_END ) ? HT_TRUE : HT_FALSE )

#define HT_FXCATEGORY_PCETC				100
#define HT_FXCATEGORY_PCFREE			21
#define HT_FXCATEGORY_PCGODBRAHMA		13
#define HT_FXCATEGORY_PCGODSHIBA		11
#define HT_FXCATEGORY_PCGODVISHUNU		12
#define HT_FXCATEGORY_PCRACEASURAK		1
#define HT_FXCATEGORY_PCRACEDEVGAR		4
#define HT_FXCATEGORY_PCRACENAGAKIN		2
#define HT_FXCATEGORY_PCRACEYAKGAN		3
#define HT_FXCATEGORY_FIELD				1000
#define HT_FXCATEGORY_MONSTERSKILL		2000
#define HT_FXCATEGORY_MONSTERETC		3000

// 20021101 HK : For FX
// Skill Type Define
#define HT_SKILL_TYPE_ACTION_NOCAST_SHORT	1
#define HT_SKILL_TYPE_ACTION_YESCAST_SHORT	2
#define HT_SKILL_TYPE_ACTION_NOCAST_LONG	3
#define HT_SKILL_TYPE_ACTION_YESCAST_LONG	4
#define HT_SKILL_TYPE_ACTIVE_YESSTATE		5
#define HT_SKILL_TYPE_ACTIVE_NOSTATE		6

// PCSkill Action Type
#define HT_PCSKILLTYPE_ACTION							10
#define HT_PCSKILLTYPE_ACTION_SHORT						1
#define HT_PCSKILLTYPE_ACTION_LONG_WITHOUTFOLLOW		2
#define HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW			3
#define HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW	4
#define HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW		5
#define HT_PCSKILLTYPE_ACTION_PIERCING					6

// PCSkill Active Type
#define HT_PCSKILLTYPE_ACTIVE									20
#define HT_PCSKILLTYPE_ACTIVE_NOSTATE							21
#define HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME					22
#define HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME					23
#define HT_PCSKILLTYPE_ACTIVE_STATE_LOOP_TOME_WITHENERGY		24
#define HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACK			25
#define HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_PERATTACKED		26
#define HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOPARTY				27
#define HT_PCSKILLTYPE_ACTIVE_STATE_ONCE_TOME_WITHNEARMONSTER	28

// PCSkill Passive Type
#define HT_PCSKILLTYPE_PASSIVE		40

// 스킬에 따른 Animation을 위해 적어둔다.
#define HT_SKILL_ANITYPE_ACTION				1	// 공격형 스킬
#define HT_SKILL_ANITYPE_CURE				5	// 치료 스킬
#define HT_SKILL_ANITYPE_DEFENCE			6	// 방어 스킬
#define HT_SKILL_ANITYPE_ASSIST				7	// 보조 스킬

// 20021101 HK : For FX
// FX Where do attach defines
#define HT_FX_WHERE_ATTACKER_NOSOCKET	0
#define HT_FX_WHERE_ATTACKER_SOCKET1	1
#define HT_FX_WHERE_ATTACKER_SOCKET2	2
#define HT_FX_WHERE_ATTACKER_SOCKET3	3
#define HT_FX_WHERE_ATTACKER_SOCKET4	4
#define HT_FX_WHERE_ATTACKER_SOCKET5	5
#define HT_FX_WHERE_ATTACKER_SOCKET6	6

#define HT_FX_WHERE_OPPONENT_NOSOCKET	100
#define HT_FX_WHERE_OPPONENT_SOCKET1	101
#define HT_FX_WHERE_OPPONENT_SOCKET2	102
#define HT_FX_WHERE_OPPONENT_SOCKET3	103
#define HT_FX_WHERE_OPPONENT_SOCKET4	104
#define HT_FX_WHERE_OPPONENT_SOCKET5	105
#define HT_FX_WHERE_OPPONENT_SOCKET6	106

#define HT_FX_WHERE_BULLET_NOSOCKET		200

#define HT_FX_ATTACKER_ATTACH_SOCKET1	CHTString( _T("Hat") )			// 머리
#define HT_FX_ATTACKER_ATTACH_SOCKET2	CHTString( _T("RightHand") )	// 오른손
#define HT_FX_ATTACKER_ATTACH_SOCKET3	CHTString( _T("LeftHand") )		// 왼손
#define HT_FX_ATTACKER_ATTACH_SOCKET4	CHTString( _T("Din") )			// PC의 가슴
#define HT_FX_ATTACKER_ATTACH_SOCKET5	CHTString( _T("Dout") )			// 몬스터의 가슴
#define HT_FX_ATTACKER_ATTACH_SOCKET6	CHTString( _T("SFX1") )			// 기타 Effect

#define HT_FX_OPPONENT_ATTACH_SOCKET1	CHTString( _T("Hat") )			// 머리
#define HT_FX_OPPONENT_ATTACH_SOCKET2	CHTString( _T("RightHand") )	// 오른손
#define HT_FX_OPPONENT_ATTACH_SOCKET3	CHTString( _T("LeftHand") )		// 왼손
#define HT_FX_OPPONENT_ATTACH_SOCKET4	CHTString( _T("Din") )			// PC의 가슴
#define HT_FX_OPPONENT_ATTACH_SOCKET5	CHTString( _T("Dout") )			// 몬스터의 가슴
#define HT_FX_OPPONENT_ATTACH_SOCKET6	CHTString( _T("SFX1") )			// 기타 Effect

// 특정 FX
#define HT_FX_NEWBORN				1010001	// 첫등장
#define HT_FX_NEWSKILL				1010002	// 새기술습득
#define HT_FX_CHAKRAUPGRADE			1010003	// 차크라 상승
#define HT_FX_CASTUPGRADE			1010004	// 카스트상승
#define HT_FX_BRAMANUPGRADE			1010005	// 브라만 상승 시
#define HT_FX_FAINTINGSTATE			1010006	// 기절상태
#define HT_FX_NORMALATTACKIMPACT	1010007	// 노멀 타격
#define HT_FX_SPRINGRECOVERY		1010008	// 회복의 샘 회복
#define HT_FX_TERRAINTARGETING		1010009	// 지면 이동 지점 표시
#define HT_FX_NPCTARGETING			1010010	// NPC 지정 표시
#define HT_FX_MONSTERTARGETING		1010011	// Monster 지정 표시
#define HT_FX_MONSTERATTACK			1010031	// Monster 공격표시
#define HT_FX_NOMOVETARGETTING		1010012	// 갈 수 없는 곳을 클릭한 경우
#define HT_FX_GODBRAHMASELECT		1400013	// intro 주신 Brahma
#define HT_FX_GODVISHUNUSELECT		1400014	// intro 주신 vishunu
#define HT_FX_GODSHIVASELECT		1400015	// intro 주신 shiva
#define HT_FX_INTROCHARACTERSELECT	1400016	// 케릭 선택시
#define HT_FX_FOOTDUST				1010013	// 발먼지
#define HT_FX_CRITICALIMPACT		1010017	// 크리티컬 임팩트
#define HT_FX_FOOTGRASS				1010014	// 잔디 발먼지
#define HT_FX_CAMJITTER_01			1101003	// CamJitter
#define HT_FX_CAMJITTER_02			1101004	// CamJitter
#define HT_FX_CAMJITTER_03			1101005	// CamJitter
#define HT_FX_DYNALIGHT_01			1101006	// DynaLight
#define HT_FX_DYNALIGHT_02			1101007	// DynaLight
#define HT_FX_DYNALIGHT_03			1101008	// DynaLight
#define HT_FX_ITEMTARGETTING		1010021	// Item Picking
#define HT_FX_QUESTCOMPLETE			1010025 // 퀘스트 종료
#define HT_FX_QUESTEQUATION			1010023 // 퀘스트 해당 인물
#define HT_FX_INTROBACK				1400021	// 인트로에서 벚꽃이 날리는 것과 같은 FX효과
#define HT_FX_TERRITORY_1			1010026
#define HT_FX_TERRITORY_2			1010027
#define HT_FX_TERRITORY_3			1010028
#define HT_FX_ARROWFOLLOW			1010060 // 화살이 날라갈 때 달려있는 FX
#define HT_FX_MOVEPUSTICA			1010058 // 이동의 푸스티카
#define HT_FX_PARTYMEMBERCALL		1010066 // 파티 소환 주문서 FX
#define HT_FX_INTROMFIRE			1300143 // 로그인 화면의 불

enum HTSkillAniSeq
{
	HT_SKILLANISEQ_READY,
	HT_SKILLANISEQ_CAST,
	HT_SKILLANISEQ_ATTACK,
	HT_SKILLANISEQ_ACTIVATE,
};

enum HTSkillItemType
{
	HT_SKILLITEM_1H,
	HT_SKILLITEM_2HSWORD,
	HT_SKILLITEM_2HAXE,
	HT_SKILLITEM_BOW,
	HT_SKILLITEM_FIST
};

enum HTESubRefineType
{
	HT_SUBREFINETYPE_NONE,
	HT_SUBREFINETYPE_FIRE,
	HT_SUBREFINETYPE_ICE,
	HT_SUBREFINETYPE_LIGHTING,
	HT_SUBREFINETYPE_POISON,
};

#endif