#ifndef _HTMessageDef_h_
#define _HTMessageDef_h_

//--------------------------------------------------------------
// Parameter
//--------------------------------------------------------------
#define HT_MSG_PARAM_NONE					0
//--------------------------------------------------------------
// Character
//--------------------------------------------------------------
// 스킬
//#define HT_MSG_SKILL_CANNOT_FIND_INFO				1081 // 스킬 정보를 찾을 수 없음
//
//#define HT_MSG_SKILL_USE_PASSIVE_ERR				1084 // 패시브 스킬은 퀵슬롯으로 이동불가
//#define HT_MSG_SKILL_USE_LEVEL_ERR					1085 // 레벨 0인 스킬은 퀵슬롯으로 이동불가
//
//#define HT_MSG_SKILL_UP_LIMIT_LEVEL					1086 // 더 이상 레벨을 올릴 수 없음
//#define HT_MSG_SKILL_UP_OK							1088 // 스킬 레벨 업 성공
//#define HT_MSG_SKILL_UP_CANNOT_LEARN				1089 // 기타 제한에 의해 스킬을 배울 수 없음
//#define HT_MSG_SKILL_UP_FAIL						1090 // 스킬 레벨업 실패

//--------------------------------------------------------------
// Parameter
//--------------------------------------------------------------
// string
#define HT_MSG_PARAM_STRING_START				1
#define HT_MSG_PARAM_STRING_END					500

// num
#define HT_MSG_PARAM_NUMBER_START				501
#define HT_MSG_PARAM_NUMBER_END					1000

typedef enum _eMsgParam
{
	eMsgParamNone				=	0,
	// string
	eMsgParamOthercharName		=	1,
	eMsgParamSourceItemName			,
	eMsgParamTargetItemName			,
	eMsgParamGuildName				,
	eMsgParamItemName				,
	eMsgParamTrimuritiName			,
	eMsgParamTribeName				,
	eMsgParamJobName				,
	eMsgParamNeedItemName			,
	eMsgParamSubItemName			,
	eMsgParamTargetEnemyName		,
	eMsgParamEnemyName				,
	eMsgParamSkillName				,
	eMsgParamMyName					,
	eMsgParamShopName				,
	eMsgParamBuyItemName			,
	eMsgParamPartymemberName		,
	eMsgParamPartyLeaderName		, // 18

	// num
	eMsgParamNeedMoney			=	501, 
	eMsgParamSpendingMoney			,
	
	eMsgParamLimitInvenDate			,
	eMsgParamLimitPrivateShopDate	,
	eMsgParamUseShopDate			,

	eMsgParamNeedLevel			=	506,
	eMsgParamSkillLevel				,

	eMsgParamBuyItemNum			=	511,
	eMsgParamBuyItemMaxNum			,
	eMsgParamMainRefineLevel		,
	eMsgParamBuyItemMinNum			,

	eMsgParamTime				=	516,
	eMsgParamPrana					,
	eMsgParamMyCharacPos			,

	eMsgParamNeedItemNum		=	521,
	eMsgParamNeedDay				,
	eMsgParamRemainDay				,
	eMsgParamNeedTrimuritiPoint		,
	eMsgParamCastGrade				,					
	eMsgParamZoneNum				,
	eMsgParamZoneMandara1st			,

	eMsgParamEffectParam1		=	531,
	eMsgParamEffectParam2			,
	eMsgParamEffectDecVal			,
	eMsgParamEffectString			,

	eMsgParamSpendingDamage		=	701,
	eMsgParamReceivedDamage			,

	eMsgParamRecoveryHp			=	705,
	eMsgParamRecoveryPrana			,

	eMsgParamLastDamage			=	1001,
	eMsgParamGuildConnect		=	1400,
} eMsgParam;
//--------------------------------------------------------------
// Common
//--------------------------------------------------------------
typedef enum _eMsgCommon
{
	eMsgNone						=	0,	// 메세지 없음

	eMsgCommonNone					=	1,	// 없음
	// 주신
	eMsgCommonTrimuritiBrahma		=	2,
	eMsgCommonTrimuritiVishunu			,
	eMsgCommonTrimuritiSiva			=	4,
	// 차크라
	eMsgCommonChakraMuscle			=	6, // 근육
	eMsgCommonChakraHeart				, // 심장
	eMsgCommonChakraNerve				, // 신경
	eMsgCommonChakraMind				, // 정신 // 9
	// 카스트
	eMsgCommonCastSudra				=	11,
	eMsgCommonCastVaisha				,
	eMsgCommonCastKshatrya				,
	eMsgCommonCastBraman				,
	eMsgCommonCastAvatara				,
	eMsgCommonCastReserve				, // 16
	// 종족
	eMsgCommonTribeNaga				=	21,		
	eMsgCommonTribeAsura				,
	eMsgCommonTribeYaksha				,
	eMsgCommonTribeDeva					,
	eMsgCommonTribeKimnara				,
	eMsgCommonTribeRakshasa				,
	eMsgCommonTribeGandharva			,
	eMsgCommonTribeGaruda				,
	eMsgCommonTribeGM					, // GM
	eMsgCommonTribeAdministrator		, // 운영자 // 30
	// 직업
	eMsgCommonJobBasic				=	31,
	// 1차 직업
	eMsgCommonJobSatvan					, // 사트반
	eMsgCommonJobDhvanta				, // 드반타
	eMsgCommonJobNirvana				, // 너바나
	eMsgCommonJobMantrika				, // 만트리카
	// 2차 직업
	eMsgCommonJobSatvan1				, // 어태커
	eMsgCommonJobSatvan2				, // 탱커
	eMsgCommonJobDhvanta1				, // 어쎄신
	eMsgCommonJobDhvanta2				, // 레인저
	eMsgCommonJobNirvana1				, // 팔라딘
	eMsgCommonJobNirvana2				, // 힐러
	eMsgCommonJobMantrika1				, // 메지션
	eMsgCommonJobMantrika2				, // 서모너 //43
	
	// 채팅
	eMsgCommonChatWhole				=	51, // 전체
	eMsgCommonChatParty					, // 파티
	//eMsgCommonChatGuild					, // 길드
	eMsgCommonChatAshuram				, // 아쉬람
	eMsgCommonChatWhisperReceive		, // %s의 귓말
	eMsgCommonChatWhisperSend			, // %s에게 귓말 // 55
	eMsgCommonChatWhisperNotSend		, // 귓속말을 보낼 수 없었습니다. 상대방이 온라인 상태가 아니거나 없는 이름을 사용하였습니다.
	eMsgCommonChatNotice				, // [공지]
	eMsgCommonChatAshuramAlliance		, // 아쉬람연합

	// Command
	eMsgCommonCommandAS				=	61, // 진정
	eMsgCommonCommandGuildWindow		, // 길드창
	eMsgCommonCommandGuildMark			, // 길드마크
	eMsgCommonCommandTrimuritiMark		, // 주신마크
	eMsgCommonCommandInvisible			, // 투명
	eMsgCommonCommandWarp				, // 워프
	eMsgCommonCommandMove				, // 이동
	eMsgCommonCommandNotice				, // 공지
	eMsgCommonCommandWholeNotice		, // 전체공지
	eMsgCommonCommandAshuramNotice		, // 공지사항-아쉬람공지
	eMsgCommonCommandAssistant			, // 조교
	eMsgCommonCommandShout				, // 외치기
	eMsgCommonCommandShoutPart			, // 외
	eMsgCommonCommandParty				, // 파티
	eMsgCommonCommandPartyPart			, // 파
	//eMsgCommonCommandGuild				, // 길드
	eMsgCommonCommandAshuram			, // 아쉬람
	eMsgCommonCommandAshuramPart		, // 아
	eMsgCommonCommandAshuramGrade		, // 아쉬람등급
	eMsgCommonCommandTrade				, // 교환
	eMsgCommonCommandEmerge				, // 탈출 
	eMsgCommonCommandWhisper			, // 귓속말
	eMsgCommonCommandWhisperPart		, // 귓
	eMsgCommonCommandWhole				, // 전체
	eMsgCommonCommandWholePart			, // 전
	eMsgCommonCommandKick				, // 킥
	eMsgCommonCommandAddress			, // 친구등록
	eMsgCommonCommandWin				, // 명령창 //87
	eMsgCommonCommandASCancel			, // 진정취소
	eMsgCommonCommandASCancel2			, // 진정취소
	eMsgCommonCommandAS2				, // 진정
		
	eMsgCommonCommandASCheck			, // gm호출확인
	eMsgCommonCommandASCheck2			, // GM호출확인

	eMsgCommonCommandDebugMode			, // Debug Mode
	eMsgCommonCommandBroadcastMode		, // BroadcastMode
	eMsgCommonCommandEngineCamera		, // Use Engine Camera
	eMsgCommonCommandGoCamera			, // Go Camera
	eMsgCommonCommandShowCursor			, // ShowCursor

	eMsgCommonCommandDuel				, // ShowCursor

	// 아이템 분류
	eMsgCommonItemClassOneHand		=	101, // 한손무기
	eMsgCommonItemClassTwoHand			, // 두손무기
	eMsgCommonItemClassArmor			, // 의복
	eMsgCommonItemClassPants			, // 바지
	eMsgCommonItemClassGloves			, // 장갑
	eMsgCommonItemClassShield			, // 방패
	eMsgCommonItemClassBelt				, // 허리띠
	eMsgCommonItemClassShoes			, // 신발
	eMsgCommonItemClassHelmet			, // 모자
	eMsgCommonItemClassEarring			, // 귀걸이
	eMsgCommonItemClassNecklace			, // 목걸이
	eMsgCommonItemClassBracelet			, // 팔찌
	eMsgCommonItemClassRing				, // 반지 // 113
	// 무기 분류
	eMsgCommonWeponClassSword		=	121, // 검
	eMsgCommonWeponClassAx				, // 도끼
	eMsgCommonWeponClassLance			, // 창
	eMsgCommonWeponClassMace			, // 둔기
	eMsgCommonWeponClassGlove			, // 격투무기
	eMsgCommonWeponClassMagic			, // 마법무기
	eMsgCommonWeponClassBow				, // 활
	eMsgCommonWeponClassDagger			, // 단검 // 128
	// 스킬 분류
	eMsgCommonSkillClassPassive		=	131, // 패시브
	eMsgCommonSkillClassAction			, // 액션
	eMsgCommonSkillClassActive			, // 액티브
	eMsgCommonSkillAttack				, // 공격
	eMsgCommonSkillDefence				, // 방어
	eMsgCommonSkillAssistance			, // 보조
	eMsgCommonSkillAssassination		, // 암살
	eMsgCommonSkillArchery				, // 궁술
	eMsgCommonSkillPhysics				, // 물리
	eMsgCommonSkillBlaze				, // 화염
	eMsgCommonSkillCold					, // 냉기
	eMsgCommonSkillLightning			, // 전격
	eMsgCommonSkillMagic				, // 마법
	eMsgCommonSkillPoison				, // 독 // 144
	eMsgCommonSkillGod					, // 주신 // 145

	// 길드
	eMsgCommonGuildMahaRaja			=	151, // 마하라자
	eMsgCommonGuildRaja					, // 라자
	eMsgCommonGuildPrubaja				, // 프루바자
	eMsgCommonGuildDandeca				, // 단디카
	eMsgCommonGuildTapasa				, // 타파사
	eMsgCommonGuildMember				, // 직위 없음

	// 시스템창
	eMsgCommonSystemNotice			=	161, // [공지]
	eMsgCommonSystemParty				, // [파티]
	eMsgCommonSystemHistory				, // [히스토리테스트]
	eMsgCommonSystemWhisper				, // [귓속말]
	eMsgCommonSystemAshuram				, // [아쉬람] // 165
	eMsgCommonSystemFile_Err		=	181, // 파일이 존재하지 않거나 형식이 잘못됐습니다.
	eMsgCommonSystemExeErr				, // 클라이언트 다운. crash파일 전송 부탁.
	eMsgCommonSystemNotAble				, // 아직 제공하지 않는 기능
	eMsgCommonSystemCannot				, // 주신전지역에서는 파티, 상거래, 길드등록, 주소록 등록이 안됩니다 //184
	eMsgGMCallTreat						, // 이전에 등록하신 GM호출 내용이 아직 처리되지 않았습니다.(185)
	eMsgGMCallRegist					, // GM호출 내용이 %d번째로 등록되었습니다.
	eMsgGMCallReRegist					, // GM호출 내용이 등록되지 않았습니다. 다시 등록해 주시기 바랍니다.
	eMsgHaveNoGMCall					, // 등록된 요청이 없습니다.
	eMsgDeleteGMCall					, // 등록된 요청이 삭제되었습니다.
	eMsgReDeleteGMCall					, // 등록된 요청 삭제가 이루어지지 않았습니다. 다시 요청해 주시기 바랍니다.
	eMsgGMCallNum						, // GM호출 내용의 대기번호는 %d입니다.
	eMsgLastDamageNotice				, // 마지막 데미지 표시
	eMsgMessageisoutoflimit				, // 최대 문장 길이를 초과하였습니다.
	eMsgReStartRemindTime				, // 게임 데이타를 저장중입니다. %d초 남았습니다.
	eMsgGameExit						, // 게임을 종료합니다. 잠시만 기다려 주십시오…
	
	// 호칭
	eMsgCommonSpecialName1			=	201, //용자
	eMsgCommonSpecialName2				, // 현자 // 202
	// 지역
	eMsgCommonZoneMandara			=	221, // 만다라
	eMsgCommonZoneMandara_1				,
	eMsgCommonZoneMandara_2				,
	eMsgCommonZoneMandara_3				,
	eMsgCommonZoneMandaraDungeon		, // 만다라 던젼
	eMsgCommonZoneShambalaDungeon		, // 샴발라 던젼
	eMsgCommonZoneJina					, // 지나
	eMsgCommonZoneTrimuriti				, // 주신전 // 228
	eMsgCommonZoneChatulangga			, // 챠투랑가
	eMsgCommonZoneForBillPotal_1		, // 유료화 포탈 1 (만다라지역)
	eMsgCommonZoneForBillPotal_2		, // 유료화 포탈 2 (샴발라지역)
	eMsgCommonZoneForBillPotal_3		, // 유료화 포탈 3 (지나지역)
	eMsgCommonZoneForBillPotal_4		, // 유료화 포탈 4 (파미르고원)
	eMsgCommonZoneForBillPotal_5		, // 유료화 포탈 5 (유배지)
	eMsgCommonZoneForBillPotal_6		, // 유료화 포탈 6 (크루마)
	eMsgCommonZoneBookDooTomb			, // 북두성군릉
	eMsgCommonZoneArenaDurga			, // 요새전
	eMsgCommonZoneBiryuCastle			, // 비류성
	eMsgCommonZoneAnakaKruma			, // 아나카쿠루마

	//	서버리스트
	eMsgCommonServerName1			=	251, // 마나스
	eMsgCommonServerName2				, // 디야나
	eMsgCommonServerName3				, // 크리야
	eMsgCommonServerName4				, // 아트만
	eMsgCommonServerName5				, // 아난다
	eMsgCommonServerName6				, // 자아나
	eMsgCommonServerName7				, // 다라나
	eMsgCommonServerName8				,  // 사마디 // 258
	eMsgCommonServerName9				,  // TestServer1
	eMsgCommonServerName10				,  // TestServer2
	eMsgCommonServerName11				,  // TestServer3

	eURLLogInEnable					= 301,	//_T("http://www.tantra-online.com/login_result/Login_Result2.asp")
	eURLIDPASSWORDCheckTestSev			,	//_T("http://www.tantra-online.com/hbmembers/game_login.asp?user_id=%s&user_pass=%s")
	eURLIDPASSWORDCheckMainSev			,	//_T("http://www.tantra-online.com/hbmembers/game_login1.asp?user_id=%s&user_pass=%s")
	eURLGMCall							,	//_T("http://www.tantra-online.com/TantraTool/GMCall/GMAppeal.asp?server_no=%s&user_id=%s&user_name=%s&appeal_text=%s")
	eURLGMCallCancel					,	//_T("http://www.tantra-online.com/TantraTool/GMCall/GMAppealCancel.asp?server_no=%s&user_id=%s&user_name=%s")
	eURLGMLog							,	//_T("//Navy//GmLog//Data//") 	
	eURLGMCallCheck						,	//_T("http://www.tantra-online.com/TantraTool/GMCall/GMAppealCheck.asp?server_no=%s&user_id=%s&user_name=%s")
	eURLGMlogout						,
	eURLperson_buy						,
	eURLfilling_cash					,
	eURLGMlogout2						,


	// 시스템창2
	eMsgCommonSystemInvalidData			=	330, // 부적절한 데이타입니다.
	eMsgCommonSystemNoRight				, // 마크 변경 권한이 없습니다.
	eMsgCommonServerMoreRupia			, // 루피아가 부족합니다.
	eMsgCommonServerMoreTani			, // 타니가 부족합니다.
	eMsgCommonServerFaild				, // 마크 변경에 실패 했습니다.
	eMsgCommonDuelRequest				, // %s님이 결투를 신청했습니다. 결투에 응하시겠습니까? 1분 동안 거부하지 않으면 결투가 승낙됩니다.
	eMsgCommonDuelDenay					, // %s님이 결투 신청을 거절했습니다.
	eMsgCommonDuelNorReqEmpty			, // %s님이 자리비움 상태입니다. 자리를 비운 플레이어에게는 결투신청을 할 수 없습니다.
	eMsgCommonDuelAutoOK				, // %s님에게 결투를 신청했습니다. 1분 후에 자동으로 결투 상태가 됩니다. 결투 신청을 취소하시겠습니까?
	eMsgCommonDuelCancel				, // 결투 상태가 취소되었습니다.
	eMsgCommonDuelMoreRhupia			, // 인벤토리에 루피아가 부족합니다. 결투를 신청하려면 10000루피아가 소모됩니다.
	eMsgCommonGuildConnect				, // %s님이 접속하였습니다.
	eMsgCommonGuildExit					, // %s님이 접속을 종료하였습니다.
	eMsgCommonAshuramGuildMsg1			, // %s님께 아쉬람 연합을 신청합니다.
	eMsgCommonAshuramGuildMsg2			, // %s님의 대답을 기다리고 있습니다.
	eMsgCommonAshuramGuildMsg3			, // %s님이 아쉬람 연합을 신청했습니다.
	eMsgCommonAshuramGuildMsg4			, // %s님이 아쉬람 연합을 거부했습니다.
	eMsgCommonAshuramGuildMsg5			, // 아쉬람 연합 신청은 마하라자만이 가능합니다.
	eMsgCommonAshuramGuildMsg6			, // 아쉬람 연합 탈퇴는 마하라자만이 가능합니다.
	eMsgCommonAshuramGuildMsg7			, // 아쉬람 연합을 맺을 상대를 선택 하세요
	eMsgCommonAshuramGuildMsg8			, // 아쉬람 연합 설정이 해체 되었습니다.
	eMsgCommonAshuramGuildMsg9			, // 아쉬람 연합 관계가 설정 되었습니다.
	eMsgCommonAshuramGuildMsg10			, // 아쉬람 연합을 맺은 아쉬람이 없습니다.
	eMsgCommonAshuramGuildMsg11			, // 이미 아쉬람 연합을 맺은 상태입니다.
	eMsgCommonAshuramGuildMsg12			, // 같은 주신의 상대만 선택할 수 있습니다.
	eMsgCommonNotHaveFotress			, // 당신의 아쉬람은 요새를 획득하지 않고 있습니다.
	eMsgCommonNoGameTime				, // 당신의 계정은 기간이 만료되었습니다.
	eMsgCommonAshuramGuildMsg13			, // 아쉬람연합을 해체한 후 다시 시도해 주십시오.
	eMsgCommonAshuramGuildMsg14			, // 마히 드루가 : [%s]>>아브 드루가 : [%s]>>단바 드루가 : [%s]>>나르 드루가 : [%s]
	eMsgCommonAshuramGuildMsg15			, // 마하라자만이 사용할 수 있습니다.
	eMsgCommonAshuramGuildMsg16			, // 마하라자 또는 라자만이 획득할 수 있습니다.
	eMsgCommonSkillZubasSkill			, // 쥬바스 스킬은 사정거리 밖에서는 사용 할 수 없습니다.
	eMsgCommonNoChatMode				, // 당신은 채팅 금지 상태입니다.
	eMsgCommonDurga0					, // 마히 드루가
	eMsgCommonDurga1					, // 아브 드루가
	eMsgCommonDurga2					, // 단바 드루가
	eMsgCommonDurga3					, // 나르 드루가
	eMsgCommonNoLoginChar				, // 이 캐릭은 블럭된 상태입니다.
	eMsgCommonAshuramGuildMsg17			, // 요새를 소유한 아쉬람끼리는 연합을 맺을 수 없습니다.
	eMsgCommonCannotGodChange			, // 주신투구 착용해제후 다시 시도해 주십시오.
	eMsgCommonAnswerUseSamudaba			, // %s가 (%d %% 경험치 회복) 사무다바 스킬을 사용했습니다. 부활 하시겠습니까?
	eMsgCommonAnswerUseSamudabaErr1		, // 시전자가 거리밖에 있어 부활하지 못했습니다.
	eMsgCommonAnswerUseSamudabaErr2		, // 시간초과로 인해 부활하지 못했습니다.
	eMsgCommonNotMoveTredeItem			, // 본 아이템은 땅에 버리거나 거래할 수 없습니다.
	eMsgCommonNotUseInDuel				, // 결투중일때는 사용할수 없습니다.
	eMsgCommonNotRegistInQuickSlot		, // 퀵슬롯에 등록불가능한 아이템입니다
	eMsgCommonPleaseInputAshramName		, // 아쉬람 이름을 입력해 주십시오
	eMsgCommonPleaseInputOpenMessage	, // 전광판 내용을 입력해 주십시오
	eMsgCommonPleaseInputCombatMessage	, // 전투명령서 내용을 입력해 주십시오
	eMsgCommonOurPlanJanuary			, // 1월에 적용 예정입니다.
	eMsgCommonExcessLoginTime			, // 로그인 시간이 초과하여 게임을 종료합니다.


	eMsgCommonCommandAshuramGuildJoin	=	400,	// /아쉬람연합
	eMsgCommonCommandAshuramGuildLeave	,			// /아쉬람연합탈퇴
	eMsgCommonCommandAshuramAlliance1	,			//	연
	eMsgCommonCommandAshuramAlliance2	,			//	연합
	eMsgCommonCommandAshuramJoinBrackets ,			//	[아쉬람연합]
	eMsgCommonCommandAshuramJoin		,			//	아쉬람연합
	eMsgCommonCommandUnionAshuram		,			//	연합아쉬람
	eMsgCommonReFresh					,			//	새로고침
	eMsgCommonScore						,			//	점
	eMsgCommonRegist					,			//	등록
	eMsgCommonDelete					,			//	삭제
	eMsgCommonConfirm					,			//	확인
	eMsgCommonCancel					,			//	취소
	eMsgCommonRupia						,			//	루피아
	eMsgCommonEachOther					,			//	상대방
	eMsgCommonMySelf					,			//	본인
	eMsgCommonJoin						,			//	가입
	eMsgCommonSecede					,			//	탈퇴
	eMsgCommonChangeStyle				,			//	모양변경
	eMsgCommonPartyMaster				,			//	파티장
	eMsgCommonRefiningTitle				,			//	제      련
	eMsgCommonRefiningTargetItem		,			//	제련 대상 아이템
	eMsgCommonRefiningItem				,			//	제련 재료
	eMsgCommonInputYouWantItem			,			//	원하는 개수를 입력하세요
	eMsgCommonInputYouWantRuphia		,			//	원하는 루피아를 입력하세요
	eMsgCommonUntilAshramCargo			,			//	%d.%d.%d(Reserved)
	eMsgCommonCommandAshuramAlliance3	,			//	아쉬람
	eMsgCommonCommandWhisper2			,			//	귓속말
	eMsgCommonDuelLimitPerson			,			//	동인인에게 3분안에 한번 이상 결투를 신청할수 없습니다.
	eMsgCommonChatRoom					,			//	/채팅방

	eMsgIntroID							=	450,	//	아이디
	eMsgIntroPassWord					,			//	비밀번호
	eMsgIntroSelectServer				,			//	서버선택
	eMsgIntroChakra						,			//	차크라
	eMsgIntroMuscleChakra				,			//	근육의차크라
	eMsgIntroNerveChakra				,			//	신경의차크라
	eMsgIntroheartChakra				,			//	심장의차크라
	eMsgIntroSoulChakra					,			//	정신의차크라
	eMsgIntroSavePos					,			//	저장위치
	eMsgIntroLeft						,			//	Left
	eMsgIntroRight						,			//	Right
	eMsgIntroCreateNewChar				,			//	새캐릭터만들기
	eMsgIntroExplainTribe				,			//	종족설명
	eMsgIntroInputName					,			//	이름입력
	eMsgIntroServicePoint				,			//	서비스 포인트
	eMsgIntroDeleteChar					,			//	캐릭터삭제
	eMsgIntroExplain					,			//	설 명
	eMsgIntroResidentNumber				,			//	주민등록번호
	eMsgIntroExplain01					,			//	삭제를 원하시면 주민등록번호를 입력하시고 확인을 눌러주세요
	eMsgIntroTopMenu01					,			//	Create Character
	eMsgIntroTopMenu02					,			//	Select Character
	eMsgIntroTopMenu03					,			//	Exit Game
	eMsgIntroExplain002					,			//	나가 족은 종족들 중에 최고의 공격력과 뛰어난 지구력을 지니고 있다.\n 단, 속도가 느리고 정교함이 떨어진다.
	eMsgIntroExplain003					,			//	아수라 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
	eMsgIntroExplain004					,			//	야크샤 족은 가장 빠르고 정확한 펀치를 날린다. 공격력은 강하지 않지만 초원에서 다져진 지구력은 그들을 더욱 강력하게 만든다.
	eMsgIntroExplain005					,			//	데바족은 물리적인 능력에서는 어떤 종족보다 약하지만 정신적인 면에서는 그 어떤 종족보다 강하다.
	eMsgIntroExplain006					,			//	킨나라 족은 종족들 중에 최고의 공격력과 뛰어난 지구력을 지니고 있다.\n 단, 속도가 느리고 정교함이 떨어진다.
	eMsgIntroExplain007					,			//	라크샤사 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
	eMsgIntroExplain008					,			//	간다르바 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
	eMsgIntroExplain009					,			//	가루다 족은 폭발적인 전투력을 갖고 있으며 마법력도 상당한 수준, 그러나 지구력이 없어 적의 공격을 오래 견디지는 못한다.
	eMsgIntorSmooth						,			//	원활
	eMsgIntorTrimuriti					,			//	주신
	eMsgIntorLimitAge					,			//	탄트라는 만15세 이상만 게임을 이용하실수 있습니다.
	eMsgIntroIDsave						,			//	ID저장하기
	eMsgFace							,			//	얼굴
	eMsgHead										//	머리

} eMsgCommon;

//--------------------------------------------------------------
// Character
//--------------------------------------------------------------
typedef enum _eMsgCharacter
{
	// 서버 상태
	eMsgLogInRegularCheck			=	1001, // 정기점검으로 인하여 로그인 할 수 없습니다.
	eMsgLogInIrregularCheck				, // 임시점검으로 인하여 로그인 할 수 없습니다.
	eMsgLogInServerUpdate				, // 서버 업데이트로 인하여 로그인 할 수 없습니다.
	eMsgLogInEtc						, // 현재는 로그인 할 수 없습니다. 잠시후 이용해 주시기 바랍니다
	eMsgLogInLogInWebErr				, // 인터넷 상황을 확인하신 후 다시 이용해 주시기 바랍니다.
	eMsgLogInInputID					, // ID와 비밀번호를 입력해주세요.
	eMsgLogInReqInitialize				, // 서버에 초기화 정보를 요청했습니다. 잠시만 기다려 주십시오.
	eMsgLogInReqInitializeAgain			, // 서버에 초기화 정보를 다시 요청하고 응답을 기다리는 중입니다.
	eMsgLogInAutoGameEnd				, // 초기화 정보 못받아서 %d초 후 게임 자동 종료
	eMsgLogInConnectionFull				, // 접속자가 많아서 접속할 수 없습니다. 잠시후 다시 접속해 주십시오. // 1010
	// 로그인
	eMsgLogInReqWeb					=	1011, // 웹에 로그인 요청
	eMsgLogInReqGameServer				, // 게임 서버에 접속 요청(1012)
	eMsgLogInReqCharacterList			, // 캐릭터 리스트 요청(1013)
	eMsgLogInReqZoneServer				, // 존서버 접속 요청(1014)
	eMsgLogInDisconnectServer			, // 서버와의 연결이 끊어졌습니다.(1015)
	eMsgLogInInvalidUser				, // 계정 없음(1016)
	eMsgLogInPasswdMismatch				, // 비밀번호가 틀림(1017)
	eMsgLogInNoResponse					, // 서버로부터 응답이 없음(1018)
	eMsgLogInBlockID					, // 과금 관련으로 접속 불가능(1019)
	eMsgLogInAlreadyLogIn				, // 이미 로그인 되어있습니다.(1020)
	eMsgLogInNeed						, // 로그인 하지 않았습니다.(1021)
	eMsgLogInOverMember					, // 동접 제한 인원 초과(1022)
	eMsgLogInHomepageWithdraw			, // 홈페이지에서 이 계정은 탈퇴 하셨습니다.(1023)
	eMsgLogInNeedExtraInfo				, // 탄트라 홈페이지에서 추가정보를 입력해 주세요.(1024)
	eMsgLogInNeedParentAgree			, // 14세 미만으로 부모님 동의서가 필요한 계정입니다.(1025)

	//eMsgLogInFail					=	1025, // 로그인 할 수 없습니다.

	// 로그아웃
	eMsgLogOutUnloading				=	1026, // 로그아웃하는 중
	eMsgLogOutSameIDLogIn				, // 동일 계정의 로그인에 의해 종료됨
	eMsgLogOutFail					=	1030 ,// 로그아웃하지 못했습니다.
	// 캐릭터 생성
	eMsgCharacListReqCreate			=	1031, // 캐릭터 생성 요청
	eMsgCharacListNotExist				, // 생성한 캐릭터가 하나도 없습니다.
	eMsgCharacListCannotCreate			, // 캐릭터를 모두 생성했습니다.
	eMsgCharacListNameLengthErr			, // 이름 길이 부적합
	eMsgCharacListInvalidName			, // 단어 부적합
	eMsgCharacListChakraPointErr		, // 서비스 차크라 포인트 남음
	eMsgCharacListAlreadyExist			, // 이미 존재하는 캐릭터 이름
	eMsgCharacListBasicChakraOver		, // 기본 차크라 오버
	eMsgCharacListCreateFail		=	1040, // 캐릭터 생성 실패
	// 캐릭터 삭제
	eMsgCharacListReqDelete			=	1041, // 캐릭터 삭제 요청
	eMsgCharacListCreateNumErr			, // 주민등록번호 오류
	eMsgCharacListDeleteFail		=	1045, // 캐릭터 삭제 실패
	// 이동
	eMsgMoveCannotStatus			=	1046, // 이동할 수 없는 상태
	eMsgMoveFail					=	1050, // 이동 실패
	// 퀘스트
	eMsgQuestTutorialStartQuestion	=	1051, // 초보자 퀘스트를 시작하시겠습니까?
	eMsgQuestRejectionConfirm			, // 정말 초보자 퀘스트를 거부하시겠습니까?

	eMsgQuestInvenLack					, // 인벤토리 공간 부족
	eMsgQuestPranaLack					, // 프라나 부족 
	eMsgQuestNotExistItem				, // 퀘스트 진행용 아이템이 없음
	eMsgQuestQuestOnlyItem				, // 퀘스트 전용 아이템이라서 판매나 양도 불가
	eMsgQuestCannotProgress				, // 1057 // 퀘스트를 진행할 수 없음
	// 루피아 이동
	eMsgRupiahMoveToNPCInven		=	1061 ,// 창고로 루피아 이동
	eMsgRupiahMoveToPCInven				, // PC인벤으로 루피아 이동
	eMsgRupiahMoveToMap					, // 땅에 루피아 버림
	eMsgRupiahReceiveQuest				, // 퀘스트에 의한 루피아 z획득
	eMsgRupiahReceive					, // 루피아 획득
	eMsgRupiahMoveAmountErr				, // 이동할 금액 부적합
	eMsgRupiahSpendingPortal			, // 포탈이용으로 루피아 소비
	eMsgRupiahSpendingQuest				, // 퀘스트에 의해 루피아 소비
	eMsgRupiahMoveDropQuestion			, // 땅에 떨어뜨리시겠습니까?
	eMsgRupiahMoveAutoReceive			, // [자동분배]%s 루피아 획득 // 1070
	eMsgRupiahMoveFail				=	1072, // 루피아 이동 실패
	// 1:1교환
	eMsgTradeReqSendQuestion		=	1073, // 교환 신청할지 확인질문
	eMsgTradeReqReceive					, // 교환 요청이 들어왔음
	eMsgTradeReqReceiveRejection		, // 교환 요청 거절
	eMsgTradeReqOtherRejection			, // 요청한 교환 거절됨 
	eMsgTradeSuccess					, // 교환 완료
	eMsgTradeCancel						, // 교환 취소
	eMsgTradeOtherInvenLack				, // 상대방 인벤토리 공간 부족
	eMsgTradeOtherDie					, // 상대방 사망으로 교환 취소
	eMsgTradeExchanging					, // 교환 중에 또 다른 캐릭터와 교환 못함 // 1081
	eMsgTradeFail					=	1085, // 교환 실패			
	// 스킬
	eMsgSkillCannotFindInfo			=	1086, // 스킬 정보를 찾을 수 없음

	eMsgSkillUseItemErr					, // 필요한 무기장착 안했음
	eMsgSkillUseSitdownErr				, // 앉은 상태에서는 사용 못함
	eMsgSkillUsePassiveErr				, // 패시브 스킬은 퀵슬롯으로 이동불가
	eMsgSkillUseLevelErr				, // 레벨 0인 스킬은 퀵슬롯으로 이동불가
	eMsgSkillUseSaveZoneErr				, // 안전지역에서는 사용 못함 // 1091

	eMsgSkillUpLimitLevel			=	1096, // 더 이상 레벨을 올릴 수 없음
	eMsgSkillUpSkillPointErr			, // 스킬 포인트 부족
	eMsgSkillUpOK						, // 스킬 레벨 업 성공
	eMsgSkillUpCannotLearn				, // 기타 제한에 의해 스킬을 배울 수 없음
	eMsgSkillUpFail					=	1105, // 스킬 레벨업 실패
	// 공격/pk
	eMsgAttackReceivePrana			=	1106, // 프라나 획득
	eMsgAttackReceiveDamage				, // 데미지 받음
	eMsgAttackSendDamage				, // 데미지 줌
	eMsgAttackTargetInSafeZone			, // 공격할 수 없는 지역에 있음
	eMsgAttackCannot					, // 공격할 수 없는 상태
	eMsgAttackCannotPKInZone			, // PK 불가 지역					
	eMsgAttackLimitPKLevel				, // PK 레벨 제한
	eMsgAttackCannotPK					, // PK 불가
	eMsgAttackNotExistTarget			, // 공격 대상이 없음
	eMsgAttackBlockSuccess				, // 블럭 성공
	eMsgAttackCannotPosition			, // 목표물을 공격할 수 없는 위치
	eMsgAttackPKWinNotify				, // %s님이 %s님에게 승리하였습니다.
	eMsgAttackPKWarning					, // [경고]PK를 하면 다른 플레이어로부터 공격 받게되며 경험치와 아이템을 잃게됩니다.
	eMsgAttackTrimuritiZoneWarning		, // [경고]주신포인트가 0인 경우 캐릭터 사망시 프라나의 5%를 상실합니다.
	eMsgAttackPKModeCancel				, // PK 모드 해제
	eMsgAttackEnemyDodge				, // 타겟이 공격 피함
	eMsgAttackDodgeSuccess				, // 회피 성공
	eMsgAttackTakeDamageWithSkill		, // %s에게 %s 스킬로 %s 데미지를 입혔습니다. 
	eMsgAttackDealDamageWithSkill		, // %s의 %s 스킬로 %s 데미지를 받았습니다.
	eMsgAttackGetSkillFromOther         , // %s이(가) %s 스킬을 걸어주었습니다
	eMsgAttackGiveSkillToOther			, // %s에게 %s 스킬을 걸었습니다.	
	eMsgAttackGetHarmFromOther			, // %s이(가) %s 스킬을 사용해서 공격했습니다.
	eMsgAttackHarmOtherWithSkill		, // %s에게 %s 스킬을 사용해서 공격했습니다.
	eMsgParameterSelf					, // 1129
	eMsgAttackFail					=	1130, // 공격 실패
	// 캐릭터 상태
	eMsgCharacterRecoveryHP			=	1131, // HP 회복
	eMsgCharacterRebirth				, // 저장지역에서 다시 태어남
	eMsgCharacterCarmaUp				, // 카르마 포인트를 없애려면 자신보다 강한 몬스터를 사냥해야 합니다.
	eMsgCharacterDead					, // %s에 의해 사망하였습니다.
	eMsgCharacterContinuousDamage		, // 지속 데미지 받고 있다.
	eMsgCharacterChakraInitQuestion		, // 차크라 포인트를 초기화하시겠습니까?
	eMsgCharacterSkillInitQuestion		, // 스킬 포인트를 초기화하시겠습니까? // 1137

	// 파티
	eMsgPartyCreateOK				=	1201, // 파티 생성 성공
	eMsgPartyCreateNameErr				, // 이미 존재하는 파티 이름
	eMsgPartyAutoRootingMode			, // 자동 분배모드
	eMsgPartyUsualRootingMode			, // 일반 분배모드
	eMsgPartyCreateErr				=	1205, // 파티 생성 실패
	eMsgPartyDissolutionQuestion	=	1206, // 파티 해체 질문
	eMsgPartyDissolutionOK				, // 파티 해체 성공
	eMsgPartyLeaderNotify				, // %s님이 파티장입니다
	eMsgPartyJoinReqReceive			=	1211, // 파티 초대 받음
	eMsgPartyJoinReqReceiveRejection	, // 파티 초대 거절
	eMsgPartyJoinReqAgreement			, // 파티 초대 승인
	eMsgPartyJoinAlreadyJoin			, // 대상 캐릭이 다른 파티에 가입
	eMsgPartyJoinAlreadyParty			, // 다른 파티에 가입하고 있는 중
	eMsgPartyJoinRejection				, // 대상 캐릭터가 파티 참여 거절
	eMsgPartyJoinAlreadyMember			, // 이미 가입되어있는 캐릭터
	eMsgPartyJoinFail				=	1218, // 파티 가입 실패
	eMsgPartySecessionMemberQuestion=	1219, // 파티에서 퇴출시키겠습니까?
	eMsgPartySecessionQuestion			, // 파티에서 탈퇴하시겠습니까?
	eMsgPartySecessionNoMaster			, // 파티장만 탈퇴시킬 수 있음
	eMsgPartySecessionOKMaster			, // 파티장에 의해 탈퇴
	eMsgPartySecessionMemberOK			, // 파티원이 탈퇴했음
	eMsgPartySecessionOK				, // 탈퇴 성공
	eMsgPartySecessionFail				, // 탈퇴 실패 // 1225
	// 포탈
	eMsgPortalExtraMandara1			=	1226, // 첫번째 만다라 지역
	eMsgPortalExtraMandara2				, // 두번째 만다라 지역
	eMsgPortalExtraMandara3				, // 세번째 만다라 지역 // 1228

	eMsgPortalNeedFee				=	1231, // 이용료
	eMsgPortalSitdownErr				, // 앉은 상태에서는 사용할 수 없음
	eMsgPortalDetailLevelErr			, // 레벨 부족 - 세부 명시 
	eMsgPortalDetailMoneyErr			, // 루피아 부족 - 세부 명시
	eMsgPortalTrimuritiErr				, // 주신 선택 필요
	eMsgPortalMoneyErr					, // 루피아 부족
	eMsgPortalLevelErr					, // 레벨 부족
	eMsgPortalCannotConnect				, // 아직 접속할 수 없는 지역
	eMsgPortalTrimuritiZoneWarning		, // 주신전에서 다른 주신의 캐릭터에게 공격받을 수 있다는 경고문
	eMsgProtalExcessMember				, // 동접제한 초과
	eMsgPortalFail					=	1245, // 이동 실패
	// 채팅
	eMsgChatInvalidWord				=	1246, // 적절하지 못한 단어 포함
	eMsgChatSaveStart					, // 대화내용 저장
	eMsgChatSaveEnd						, // 대화내용 저장 종료
	eMsgChatLogFileCloseErr				, // 로그파일 닫기 실패. 대화내용 계속 저장.
	eMsgChatLogFileOpenErr				, // 로그파일 열기 실패. 대화내용 저장 시작 못함.
	eMsgChatDifferentServer				, // 다른 서버에 위치
	eMsgChatNotLogInCharacter			, // 접속하지 않은 캐릭터
	eMsgChatFail					=	1260, // 전달 실패
	// 주소록
	eMsgAddressReqAddQuestion		=	1261, // 주소록 등록을 요청하시겠습니까?
	eMsgAddressReqReceive				, // 주소록 등록을 요청받음
	eMsgAddressAlreadyResist			, // 이미 등록되어있습니다.
    eMsgAddressReqDelQuestion			, // 주소록에서 삭제하시겠습니까? // 1254
	sMsgAddressAddress					,	//	주소록
	sMsgAddressTribe					,	//	종족
	sMsgAddressName						,	//	이름
	sMsgAddressConnect					,	//	접속
	// 길드
	eMsgGuildReqReceive				=	1271, // 길드 가입 요청 받음
	eMsgGuildReqDelMemberQuestion		, // %s를 제명하시겠습니까?
	eMsgGuildReqSecessionQuestion		, // 정말 탈퇴하시겠습니까?
	eMsgGuildBlogErr					, // 아쉬람에 가입되어 있지 않은 경우 아쉬람 블로그에 접근할 수 없습니다.
	eMsgGuildBlogMakeErr				, //
	
	eMsgGuildCreateOtherJoinErr		=	1276, // 다른 길드에 가입되어있어서 창설 불가
	eMsgGuildCreateNoTrimuritiErr		, // 주신 선택후 창설 가능
	eMsgGuildCreateNeedMoneyErr			, // 길드 창설에 필요한 돈 모자름
	eMsgGuildCreateFail					, // 길드 창설 실패
	eMsgGuildMarkConditionErr			, // 길드장만 길드마크 제작 가능

	eMsgGuildDissolutionQuestion	=	1281, // 정말 해체하시겠습니까?
	eMsgGuildMarkConditionErr2			, // 아쉬람명의 길이는 영어기준 4자부터 만드실 수 있습니다.
	eMsgGuildDissolutionOK			=	1285, // 해체 성공
	// 퀵슬롯
	eMsgQuickSlotUseTPErr			=	1286, // TP가 낮아서 스킬 사용 불가
	eMsgQuickSlotUseCoolTimeErr			, // CoolTime 제한으로 사용 불가
	// GM
	eMsgGMASReceiptOK				=	1291, // 진정 접수
	eMsgGMASReceiptLimitOver			, // 진정 처리 한도 초과. 잠시후 다시 시도해 주십시오.
	eMsgGMASReceiptFail					,// 진정이 접수되지 않았습니다. 
	// 튜토리얼 시스템
	eMsgTutorialTitle				=	1301, // 탄트라 월드에 오신 %s님에게...
	eMsgTutorialSubTitle1				,	//	첫인사
	eMsgTutorialCommand1				,	//	[캐릭터 이동방법을 배운다.]
	eMsgTutorialStep1_0					,	//	나가족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_1					,	//	킨나라족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_2					,	//	아수라족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_3					,	//	락샤샤라족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_4					,	//	야크샤족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_5					,	//	간다르바족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_6					,	//	데바족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_7					,	//	가루다족의 %s님 만다라 마을에 오신것을 진심으로 환영합니다.
	eMsgTutorialStep1_8					,	//	신목이 오늘따라 유난히 푸르르다 싶었는데 %s님을 맞이하게 되는군요. 영광입니다.

	eMsgTutorialSubTitle2			=	1313,	//	캐릭터이동방법
	eMsgTutorialStep2_0					,	//	자 그럼 이동 해볼까요?
	eMsgTutorialStep2_1					,	//	지면 저 멀리 마우스를 가져가 클릭해 보세요. 클릭을 했을 때 파란문양이 지면에 그려진다면 일단 성공!! 묽은 문얃이 그려진다면 그곳은 갈수 없는 곳이랍니다.
	eMsgTutorialStep2_2					,	//	캐릭터를 이동해 보세요

	eMsgTutorialSubTitle3			=	1317,	//	포탈 정보
	eMsgTutorialCommand3				,	//	[시점 변경을 배운다.]
	eMsgTutorialThank1					,	//	%s님 수고하셨습니다.
	eMsgTutorialThank2					,	//	멋진 컨트롤이었습니다.
	eMsgTutorialStep3_0					,	//	달리기와 걷기 변경은 'Z'로 하게 되며 원거리 이동시엔 포탈을 사용하여 공간이동을 합니다. 포탈은 만다라 마을 중앙의 신목 뒤, 역마꾼 라훌에게 가보시면 됩니다. 하지만 먼 지역엔 강한 몬스터가 출현하므로 조심하셔야 합니다.

	eMsgTutorialSubTitle4			=	1322,	//	시점 변경
	eMsgTutorialStep4_0					,	//	탄트라의 아름다운 하늘을 보신 적 있나요?
	eMsgTutorialStep4_1					,	//	시점 변경 방법을 배워서 아름다운 하늘을 감상해 보도록 하죠.
	eMsgTutorialStep4_2					,	//	마우스 오른쪽 버튼을 누른 상태에서 마우스를 이동해 보세요. 시점을 앞뒤로 변경할 때는 마우스 스크롤 버튼을 돌리시면 됩니다.
	eMsgTutorialStep4_3					,	//	시점을 변경해 보세요.

	eMsgTutorialSubTitle5			=	1327,	//	시점 변경 기능키 설명
	eMsgTutorialCommand5				,	//	[미니맵 사용법을 배운다.]
	eMsgTutorialStep5_0					,	//	조금 더 알려 드리자면 'F11'키를 누르시면 1인칭, 3인칭으로 시점전환이 가능합니다. 시점 고정키는 'F12'이며, 마우스 중앙의 스크롤 버튼을 누르시면 기본 시접으로 전환됩니다.

	eMsgTutorialSubTitle6			=	1330,	//	미니맵 사용법
	eMsgTutorialStep6_0					,	//	어디가 어딘지 분간이 안되신다구요? 미니맵을 이용하시면 지형을 쉽게 이해하실 수 있습니다.
	eMsgTutorialStep6_1					,	//	미니맵에 보이는 화살표가 자신의 위치를 나타내며 진행방향에 따라 화살표가 회전하게 됩니다. 또한 더 큰 지도를 볼 수 있는데 미니맵의 크기를 변경하는 단축키는 키보드 'M'을 눌러 변경할 수 있습니다.
	eMsgTutorialStep6_2					,	//	미니맵 크기를 바꿔 보세요.

	eMsgTutorialSubTitle7			=	1334,	//	미니맵 아이콘
	eMsgTutorialCommand7				,	//	[단축키 설명을 듣는다.]
	eMsgTutorialStep7_0					,	//	어디든지 갈수 있겠죠?\n좀더 자세한 설명을 드리자면 미니맵에 보이는 아이콘은 NPC에 대한 특징을 담고 있습니다.
	eMsgTutorialStep7_1					,	//	위와 같은 특징을 가지고 있으므로 찿아 가실때 좀더 쉽게 찿을수 있고 미니맵 상단의 숫자들은 좌표를 표시하므로 참고하시면 친구를 찿을 때 보다 편리하실 것입니다.
	eMsgTutorialStep7_2					,	//	무기점 방어구점  잡화점   창고

	eMsgTutorialSubTitle8			=	1339,	//	단축키 활용
	eMsgTutorialStep8_0					,	//	게임을 하실 때 자주 사용되는 단축키를 몇가지 설명 드리겠습니다.
	eMsgTutorialStep8_1					,	//	오른쪽 아래 보이는 아이콘은 각 기능의 단축키를 설정해 놓은 아이콘입니다.
	eMsgTutorialStep8_2					,	//	오른쪽 아래 보이는 아이콘은 각 기능의 단축키를 설정해 놓은 아이콘입니다.
	eMsgTutorialStep8_3					,	//	아이템을 장착하는 방법은 마우스 커서를 아이템 위에 올려놓고 클릭하여 장착을 할 위치에 다시 클릭해 놓으시면 됩니다.
	eMsgTutorialStep8_4					,	//	기본 무기를 장착해 보세요

	eMsgTutorialSubTitle9			=	1346,	//	단축키 활용
	eMsgTutorialCommand9				,	//	[몬스터 사냥법을 배운다.]
	eMsgTutorialStep9_0					,	//	다른 단축키에 대한 설명을 드리겠습니다.
	eMsgTutorialStep9_1					,	//	'L'키를 눌러 캐릭터의 상세한 정보를 볼 수 있습니다.
	eMsgTutorialStep9_2					,	//	'I'키를 눌러 소지품 또는 장착 아이템을 확인 할 수 있습니다.
	eMsgTutorialStep9_3					,	//	'K'키를 눌러 자신이 배운 기술들을 확인 할 수 있습니다.
	eMsgTutorialStep9_4					,	//	'U'키를 눌러 퀘스트에 관련된 정보를 볼 수 있습니다.
	eMsgTutorialStep9_5					,	//	'C'키로 명령어 관련 아이콘을 확인 할 수 있습니다.
	eMsgTutorialStep9_6					,	//	'ESC'키로 게임설정 또는 시스템 관련 설정을 변경 할 수 있습니다.
	eMsgTutorialStep9_7					,	//	플레이어를 강제적으로 공격할 수 있습니다.(PK는 살인행위이므로 상당한 불이익을 받게 됩니다.)

	eMsgTutorialSubTitle10			=	1356,	//	몬스터 사냥법
	eMsgTutorialStep10_0				,	//	자, 몬스터 사냥을 해보시겠습니다.
	eMsgTutorialStep10_1				,	//	미니맵을 보면 마을 남쪽에 빨간색 화살표가 있습니다. 화살표 아래 길을 따라 마을을 나서면 몬스터들이 출현하는 곳으로 갈 수 있습니다. 몬스터를 한번 클릭하면 몬스터의 정보가 나오며 다시 한번 클릭하면 몬스터를 공격하게 됩니다.
	eMsgTutorialStep10_2				,	//	바사붐 1마리를 사냥해 보세요.

	eMsgTutorialSubTitle11			=	1360,	//	사냥법 응용
	eMsgTutorialCommand11				,	//	[ITEM 줍는법을 배운다.]
	eMsgTutorialStep11_0				,	//	더 쉽게 사냥하는 방법을 알려드리겠습니다.
	eMsgTutorialStep11_1				,	//	명령어창을 열어보시면
	eMsgTutorialStep11_2				,	//	근접한 적을 찿는 아이콘이 있습니다.
	eMsgTutorialStep11_3				,	//	아이콘을 클릭해서 퀵바에 올려놓고 근접한 몬스터를 쉽게 찿을 수 있습니다.

	eMsgTutorialSubTitle12			=	1366,	//	아이템 줍는법
	eMsgTutorialStep12_0				,	//	아이템 줍는법을 배워 보도록 하겠습니다.
	eMsgTutorialStep12_1				,	//	몬스터가 죽고나면 아이템이 떨어집니다. 마우스 커서로 아이템을 클릭하면 집어집니다. 바사붐을 사냥한 후 떨어진는 아이템을 집어보세요
	eMsgTutorialStep12_2				,	//	아이템을 집어보세요

	eMsgTutorialSubTitle13			=	1370,	//	아이템 줍기 응용
	eMsgTutorialCommand113				,	//	[튜토리얼을 마치며]
	eMsgTutorialStep13_0				,	//	좀더 쉽게 아이템을 집는 방법을 알려드리겠습니다.
	eMsgTutorialStep13_1				,	//	명령어창을 열고 아이템 줍기 아이콘을 퀵바에 올려놓고 해당 번호를 눌러 아이템을 집으면 더욱 더 쉽게 아이템을 집을 수 있습니다.
	eMsgTutorialStep13_2				,	//	이젠 모든 튜토리얼 과정을 마치겠습니다.\n긴 시간동안 수고하셨습니다.

	eMsgTutorialSubTitle14			=	1375,	//	GM 설명
	eMsgTutorialCommand114				,	//	[초보자 퀘스트를 한다.]
	eMsgTutorialStep14_0				,	//	이제 꿈과 모험이 가득한 탄트라 월드에서 마라의 무리들과 대적하는 용사로서 갖추어야 할 기본 소양을 마스터 하였습니다.
	eMsgTutorialStep14_1				,	//	지금까지 가이드를 한 저는, 이제 GM이라는 이름으로 항상 곁에서 플레이 환경 개선은 물론 난관에 봉착하였을 때 마다 도움을 드리는 도우미가 되겠습니다.
	eMsgTutorialStep14_2				,	//	지금까지 학습하신 내용과 그것들의 응용을 실습 할 수 있는 초보자 퀘스트가 준비되어 있습니다. 몰론 초보 단계에 얻기 힘든 아이템들이 보상으로 준비되어 있으니 수행하시길 권합니다.

	eMsgYutTitle					=	1400,	//	Yut
	eMsgYutExplain01					,	//	윳놀이판 정보를 갱신합니다.
	eMsgYutBuildMoney					,	//	내 적립액
	eMsgYutTotalMoney					,	//	총 적립액
	eMsgYutUrgentAllotment				,	//	배당금 지급
	eMsgYutExplainAllotment				,	//	당첨된 배당금을 지급 받습니다.
	eMsgYutExplainMoney1				,	//	내적립
	eMsgYutExplainMoney2				,	//	적립액
	eMsgYutExplainMoney3				,	//	적립률
	eMsgYutExplainMoney4				,	//	보너스
	eMsgYutExplain02					,	//	배팅할 루피아를 입력해 주세요.
	eMsgYutExplain03					,	//	성공적으로 배팅하였습니다!!.
	eMsgYutExplain04					,	//	배팅 시간이 아닙니다. 다음 배팅 시간에 다시 참여해주세요
	eMsgYutExplain05					,	//	당첨금을 받았습니다. 인벤토리를 확인해 보세요
	eMsgYutExplain06					,	//	수령하실 당첨금이 없습니다.

	eMsgSiegeTitle					=	1420,	//	공성전
	eMsgSiegeUnionAshram				,	//	참가아쉬람
	eMsgSiegeSiegeState					,	//	공성전상황
	eMsgSiegeSiegeDeclare				,	//	공성전선포
	eMsgSiegeCastleMgr					,	//	비류성관리
	eMsgSiegeHelp						,	//	도움말
	eMsgSiegeDefenseUnion				,	//	수성 연맹
	eMsgSiegeAttackUnion				,	//	공성 연맹%d
	eMsgSiegeEmptyUnion					,	//	무소속 연합
	eMsgSiegeScoreDefenseUnion			,	//	수성 연합 : %d점
	eMsgSiegeScoreAttackUnion			,	//	공성 연맹 : %d점
	eMsgSiegeScoreEmptyUnion			,	//	무소속 연맹 : %d점
	eMsgSiegeSiegeTime					,	//	공성전시간
	eMsgSiegeSiegeNoTime				,	//	설정 시간 없음
	eMsgSiegeFriEve8					,	//	금요일 저녁 8시
	eMsgSiegeFriEve10					,	//	금요일 저녁 10시
	eMsgSiegeSatEve8					,	//	토요일 저녁 8시
	eMsgSiegeSatEve10					,	//	토요일 저녁 10시
	eMsgSiegeSunEve8					,	//	일요일 저녁 8시
	eMsgSiegeExplain01					,	//	비류성의 성주는 자신이 원하는 날짜에 공성전을\n 선포할 수 있습니다.
	eMsgSiegeExplain02					,	//	공성전은 화요일 24:00까지 선포하지 않으면 토요일\n 저녁 10시에 개최됩니다.
	eMsgSiegeApply						,	//	적용
	eMsgSiegeCollect					,	//	회수
	eMsgSiegeExplain03					,	//	비류성의 성주는 특산물 상점의 판매 가격에 소비세를 부과할 수 있습니다.
	eMsgSiegeChageRate					,	//	세율 변경
	eMsgSiegeCollectRate				,	//	세금 회수
	eMsgSiegeTrustShopRate				,	//	위탁상점세율
	eMsgSiegeInfoDefenseUnion			,	//	수성연맹정보
	eMsgSiegePageNo						,	//	PageNo : %d
	eMsgSiegeJoinUnion					,	//	연맹가입
	eMsgSiegeInfoAttackUnion			,	//	공성연맹정보1
	eMsgSiegeRequestUnionMaster			,	//	맹주신청
	eMsgSiegeRequestSiege				,	//	공성신청
	eMsgSiegeSiegeItem					,	//	공성아이템
	eMsgSiegeSiegeWiner					,	//	공성전승자
	eMsgSiegeRightCastleMaster			,	//	성주의권한
	eMsgSiegeExplain04					,	//	공성전 맹주 신청
	eMsgSiegeExplain05					,	//	공성전에는 3개의 공성 연맹이 참여할 수 있습니다. 공성전에 승리해 성주가 되기 위해선 공성 연맹의 맹주가 되어야 하는데, 자신이 원하는 공성 연맹을 선택하고 신청 비용과 공성 아이템을 지불해야 합니다. 가장 비싼 첫 번째 공성 연맹의 맹주가 되면 공성전에서 다른 연합과 동점일 때 성주가 될 수 있습니다.
	eMsgSiegeExplain06					,	//	공성전 참가 신청
	eMsgSiegeExplain07					,	//	맹주가 결정된 연맹을 선택하면 맹주의 아쉬람이 공성전에 승리할 수 있도록 도와 줄 수 있습니다. 연맹을 선택하지 않은 모든 아쉬람은 무소속으로 공성전에 창여할 수 있으며 연맹에 참여한 아쉬람은 언제든 무소속으로 변경할 수 있습니다. 무소속 연합이 공성전에 승리하면 성은 소유주가 없는 초기 상태가 됩니다.
	eMsgSiegeExplain08					,	//	공성신청
	eMsgSiegeExplain09					,	//	공성아이템
	eMsgSiegeExplain10					,	//	공성전승자
	eMsgSiegeExplain11					,	//	성주의권한
	eMsgSiegeExplain12					,	//	공성전 아이템 아디즈
	eMsgSiegeExplain13					,	//	공성전에 참여하고 싶은 아쉬람은 비류성 일대에서 아디즈를 수집해야 합니다. 아디즈는 비류성 일대에 흩어져 있는 보석입니다. 비류성의 상징물인 아디즈와 같은 이름으로 비류성의 주인들은 그 보석을 이용해 거대한 아디즈를 제작했다고 합니다.
	eMsgSiegeExplain14					,	//	아디즈는 수성 아쉬람을 도와주기 위해 허위로 공성 신청을 하는 아쉬람을 막기 위한 최소한의 장치이기도 합니다.
	eMsgSiegeExplain15					,	//	공성전의 승자
	eMsgSiegeExplain16					,	//	공성전 종료 시간에 가장 많은 공성 상징물을 차지해 높은 점수를 얻은 연맹이 공성전의 승자가 됩니다. 동점인 경우 수성 연맹, 공성 연맹1, 2, 3의 우선 순위로 승자가 결정됩니다.
	eMsgSiegeExplain17					,	//	무소속 연합의 승리
	eMsgSiegeExplain18					,	//	무소속 연합이 승리하는 경우 성은 주인이 없는 초기 상태로 바뀝니다.
	eMsgSiegeExplain19					,	//	비류성 특산물 조세권
	eMsgSiegeExplain20					,	//	비류성에는 다른 곳에서 판매하지 않는 특별한 아이템을 판매하는 상인이 있습니다. 비류성의 성주는 특산물에 추가 세율을 정할 수 있습니다.
	eMsgSiegeExplain21					,	//	윷놀이 터 조세권
	eMsgSiegeExplain22					,	//	비류성에는 NPC 사토가 운영하는 윷놀이 터가 있습니다. 비류성의 성주는 윷놀이 터 관리인 사토로부터 윷놀이 운영 이익의 일부를 비류성의 세금으로 조세할 수 있습니다.
	eMsgSiegeNameDefenseUnion			,	//	%s 수성연맹
	eMsgSiegeNameAttackUnion			,	//	%s 공성연맹
	eMsgSiegeNoBuildRupia				,	//	적립된 루피아가 없습니다.
	eMsgSiegeExplain23					,	//	인벤토리에 %s 루피아가 지급되었습니다.
	eMsgSiegeNextPage					,	//	다음 페이지

	eMsgErrorName					=	1480, // 위 계정은 없는 계정입니다. 다시 확인하시고 맞지 않으면 홈페이지에서 'ID/PASSWORD 찾기'를 이용하세요.
	eMsgErrorPassword						, // 비밀번호가 맞지 않습니다. 다시 확인하시고 맞지 않으면 홈페이지에서 'ID/PASSWORD 찾기'를 이용하세요.
	eMsgErrorServerConnect					, // 현재 서버점검중이므로 접속 하실 수 없습니다. 자세한 사항은 홈페이지 공지사항을 확인하시고 질문과 답 게시판으로 문의해 주시기 바랍니다.
	eMsgErrorIDBlock						, // 위 계정은 운영 원칙에 의거하여 압류되었습니다. 자세한 사항은 이메일을 확인하시고 질문과 답 게시판으로 문의해 주시기 바랍니다.
	eMsgLoginServerBusy						,	// 서버의 가부화로 로그인정보를 처리하지 못했을때 발생 (접속을 다시 시도해 주십시오)
	eMsgLoginServerNotBill					,	// 게임 요금을 미지금했거나 이용기간이 경과되었습니다.
	eMsgLoginServerNeedBill					,	// 탄트라는 유료 서버스가 되었습니다. 겅호의 어트랙션센터에서 이용권을 구입해 주십시요.
	eMsgLoginServerOpenWait					,	// 베타 서비스가 종료되었습니다. 정식 서비스개시까지 기다려주세요.
	eMsgLoginErrorTestServer				,	// 이 계정은 테스트 서버에 접속이 불가능합니다.
	eMsgLoginErrorAgeLimit					,	// 탄트라는 만12세 이상만 게임을 이용하실수 있습니다.

	eMsgGuildBlogOpenWarning			=	1501,
	eMsgGuildBlogOpenError1					,
	eMsgGuildBlogOpenError2					,
	eMsgGuildBlogOpenError3					,
	eMsgGuildBlogOpenError4					,
	eMsgGuildBlogOpenError5					,

	eMsgCommandTitle					=	1510,	//	Command
	eMsgCommadnSubTitle						,	//	명령
	eMsgCommadnAboutAction					,	//	행동관련
	eMsgCommadnAboutGroup					,	//	그룹관련
	eMsgCommadnAboutMotion					,	//	모션관련
	eMsgCommadDirections					,	//	지시
	eMsgCommadStop							,	//	멈춤
	eMsgCommadSiege							,	//	공성전
	eMsgCommadAutoJoin						,	//	자동가입

	eMsgInvenTitle						=	1520,	// Inventory1
	eMsgInvenSubTitle						,	//	인벤토리
	eMsgInvenPrivateShop					,	//	개인상점
	eMsgInvenTrade							,	//	물품교환
	eMsgInvenNoExpansionInven				,	//	인벤토리 확장하지 않았음
	eMsgInvenFirstInven						,	//	첫번째 인벤토리
	eMsgInvenSecondInven					,	//	두번째 인벤토리
	eMsgInvenInputMoveRupia					,	//	이동할 루피아를 입력해주세요.
	eMsgInvenNotMoveShortOfInven			,	//	인벤토리 공간이 부족하여 아이템을 이동할 수 없습니다.
	eMsgInvenNotMoveShortOfCargo			,	//	창고 공간이 부족하여 아이템을 이동할 수 없습니다.
	eMsgInvenInputMoveItem					,	//	이동할 개수를 입력해 주세요.
	eMsgInvenWrongInput						,	//	잘못 입력하셨습니다.
	eMsgInvenInventory2						,	//	Inventory2
	eMsgInvenCargo							,	//	개인창고
	eMsgInvenContribution					,	//	기부
	eMsgInvenExplain01						,	//	신은 당신의 기부를 축복으로 보답하실 것입니다.
	eMsgInvenExplain02						,	//	현재 신으로부터의 축복정도는 아래와 같습니다.
	eMsgInvenExplain03						,	//	신도들의 헌납으로 시험의 문 차투랑가의 문이 열릴 것 입니다. 게이지가 모두
	eMsgInvenExplain04						,	//	채워지면 칼라 스코어와 관계없이 5분간 차투랑가의 문이 열립니다.

	eMsgFaceHair0						= 1549, // 미용실
	eMsgFaceHair1							,	// 기존 헤어
	eMsgFaceHair2							,	// 기존 얼굴
	eMsgFaceHair3							,	// 헤어 타입
	eMsgFaceHair4							,	// 얼굴 타입
	eMsgBeautySalon							,	// 종합미용실
	eMsgSelectHair							,	// 헤어스타일 선택
	eMsgSelectFace							,	// 얼굴 선택
	eMsgNeedTany							,	// 요구타니
	eMsgKeepTany							,	// 보유타니
	eMsgSexType								,	// 성별

    eMsgAshramTitle						= 1560,	//	Ashram
	eMsgAshramInfo							,	//	아쉬람정보
	eMsgAshramNotice						,	//	공지 사항
    eMsgAshramUnionAshram					,	//	연합 아쉬람
	eMsgAshramAshramName					,	//	아쉬람 명
	eMsgAshramResigstMember					,	//	등록인원
	eMsgAshramConnectMember					,	//	접속인원
	eMsgAshramExplainNotice					,	//	공지사항입니다.
	eMsgAshramNoUnionAshram					,	//	연합 아쉬람이 없습니다.
	eMsgAshramOrganizationMember			,	//	구성인원
	eMsgAshramMakeBlog						,	//	홈피제작
	eMsgAshramEnterBlog						,	//	홈피입장
	eMsgAshramMiniBlog						,	//	미니블로그
	eMsgAshramLevel							,	//	레벨
	eMsgAshramPosition						,	//	직위
	eMsgAshramBackMark						,	//	배경문양
	eMsgAshramMark							,	//	문양
	eMsgAshramBackColor						,	//	배경색
	eMsgAshramAshramCargo					,	//	아쉬람창고%d
	eMsgAshramCargo							,	//	창고 %d
	eMsgAshramExplainCargo01				,	//	◐ 창고사용기간확인및과금 ◐
	eMsgAshramCargoName						,	//	창고명
	eMsgAshramUseYesOrNo					,	//	사용여부
	eMsgAshramNotUse						,	//	사용중아님
	eMsgAshramEnddate						,	//	만료기간
	eMsgAshramEnd							,	//	만료
	eMsgAshramDDay							,	//	D-day
	eMsgAshramPayCargo						,	//	사용료지불
	eMsgAshramSetAshramRight				,	//	아쉬람창고권한설정
	eMsgAshramReqNeedRupia					,	//	선택하신 아쉬람 창고는 %d만 루피아가 필요합니다.\n 정말 사용하시겠습니까?
	eMsgAshramSuccessCragoExpance			,	//	아쉬람 창고%d 확장에 성공하였습니다.
	eMsgAshramFaildCargoExpance				,	//	아쉬람 창고 확장에 실패하였습니다.
	eMsgAshramFaildShortOfRupia				,	//	루피아가 부족하여 요청하신 작업을 수행할수 없습니다.

	eMsgShopSale						= 1600,	//	판매
	eMsgShopSaleTotalPrice					,	//	판매총액
	eMsgShopCarryRupia						,	//	소지금액
	eMsgShopExpanceDate						,	//	확장기한
	eMsgShopMessage							,	//	메시지
	eMsgShopBuyTotalPrice					,	//	구매총액
	eMsgShopTrader							,	//	판매자
	eMsgShopBuyer							,	//	구매자
	eMsgShopExplain01						,	//	*****선택하신 아이템 구매 내역입니다.*****
	eMsgShopExplain02						,	//	***구매내역에 동의하시면 확인 버튼을 눌러 주세요***
	eMsgShopSubTotal						,	//	합계
	eMsgShopLeft							,	//	좌
	eMsgShopRight							,	//	우
	eMsgShopExplain03						,	//	프리미엄 서비스 이용내역
	eMsgShopExplain04						,	//	프리미엄 서비스의 추가 신청시 적용기간이 늘어납니다.
	eMsgShopExplain05						,	//	효과가 OFF인 상태인 경우라도 만료기간이 연장되지는 않습니다.
	eMsgShopBundle							,	//	꾸러미
	eMsgShopCharacter						,	//	캐릭터
	eMsgShopConvenience						,	//	편의성
	eMsgShopAbility							,	//	기능성
	eMsgShopspeciality						,	//	특수용
	eMsgShopReqBuyItem						,	//	정말 아이템을 사용하시겠습니까?\n[참고]자신의 컴퓨터 날짜가 정확하지 않을 경우 사용기간이 제대로 표기되지 않을 수 있습니다.

	eMsgCharInfoTitle					= 1650,	//	캐릭터 정보
	eMsgCharInfoCast						,	//	카 스 트
	eMsgCharInfoExplainAshram				,	//	아쉬람명
	eMsgCharInfoTrimuriti					,	//	주     신
	eMsgCharInfoPointTriburiti				,	//	주신포인트
	eMsgCharInfoKarma						,	//	카 르 마
	eMsgCharInfoAblitityStatus				,	//	캐릭터 능력상태
	eMsgCharInfoLifrPower					,	//	생 명 력
	eMsgCharInfoTapas						,	//	타 파 스
	eMsgCharInfoDefencePower				,	//	방 어 력
	eMsgCharInfoPhysicsAP					,	//	물리공격력
	eMsgCharInfoAttackRate					,	//	공격성공률
	eMsgCharInfoEvasionRate					,	//	회 피 율
	eMsgCharInfoChakra						,	//	차크라
	eMsgCharInfoMuscle						,	//	근     육
	eMsgCharInfoNerve						,	//	신     경
	eMsgCharInfoHeart						,	//	심     장
	eMsgCharInfoSoul						,	//	정     신
	eMsgCharInfoRemaindChakra				,	//	잔여차크라
	eMsgCharInfoResistancePower				,	//	저항력
	eMsgCharInfoFire						,	//	화     염
	eMsgCharInfoElectric					,	//	전     격
	eMsgCharInfoCold						,	//	냉     기
	eMsgCharInfoPoison						,	//	독
	eMsgCharInfoTribe						,	//	종     족
	eMsgCharInfoOccupation					,	//	직     업
	eMsgCharInfoSkillPoint					,	//	스킬포인트
	eMsgCharInfoGodPoint					,	//	주신 스킬

	eMsgQuest							= 1680,	//	Quest
	eMsgQuestDiaryQuest						,	//	퀘스트 일지
	eMsgQuestContinueQuest					,	//	진행중인 퀘스트
	eMsgQuestConditionQuest					,	//	퀘스트 조건
	eMsgQuestCompletionQuest				,	//	완료 퀘스트

	eMsgPortalTitle						= 1690,	//	포탈
	eMsgPortalPortalName					,	//	현재포탈이름
	eMsgPortalJivaPustica					,	//	지바푸스티카
	eMsgPortalSelectZone					,	//	원하시는 지역을 선택하세요
	eMsgPortalMandaraVillage				,	//	만다라 마을
	eMsgPortalShambalraZone					,	//	샴발라 지역
	eMsgPortalJinaZone						,	//	지나 지역
	eMsgPortalExile							,	//	유배지
	eMsgPortalTrimuriti						,	//	주신지역
	eMsgPortalHighJivaPustica				,	//	고급지바푸스티카
	eMsgPortalSelectOtherZone				,	//	<-다른지역 선택->

	eMsgOptionTitel						= 1710,	//	Option
	eMsgOptionBasicOption					,	//	기본옵션
	eMsgOptionGraphOption					,	//	그래픽옵션
	eMsgOptionSoundOption					,	//	사운드옵션
	eMsgOptionWindowAhlpa					,	//	윈도우감마
	eMsgOptionShowID						,	//	아이디표시
	eMsgOptionEffect						,	//	이펙트
	eMsgOptionSimpleShop					,	//	상점간소화
	eMsgOptionResolution					,	//	해상도
	eMsgOptionEffectSound					,	//	효과음
	eMsgOptionBGM							,	//	배경음악
	eMsgOptionReStart						,	//	재시작
	eMsgOptionExitGame						,	//	게임종료

	eMsgChatChangeChatMode				= 1730, //	채팅모드변환
	eMsgChatConfigChat						,	//	채팅설정
	eMsgChatShowConfigChatMsg				,	//	채팅내용표시설정
	eMsgChatUnion							,	//	연합
	eMsgChatChatLog							,	//	채팅로그
	eMsgChatList							,	//	리스트
	eMsgChatNormalMsg						,	//	일반메시지(채팅로고창)
	eMsgChatOpenMsg							,	//	전광판메시지(채팅로고창)
	eMsgChatSave							,	//	저장
	eMsgChatSystem							,	//	시스템

	eMsgRevivalRevivalCurrentPos		= 1740,	//	현재의 자리에서 부활
	eMsgRevivalRevivalSavedZone				,	//	저장된 지역에서 부활
	eMsgRevivalWebWindow					,	//	Web Window
	eMsgRevivalWebBrowser					,	//	WebBrowser를 종료합니다.
	eMsgRevivalRevivalArena					,	//	아레나 관중석에서 부활(20000 루피아 소모)
	eMsgRevivalRevivalFotress				,	//	버려진 요새에서 부활
	eMsgRevivalRevivalNorthViruCastle		,	//	비류성 북쪽 성문 근처에서 부활
	eMsgRevivalExitWeb						,	//	나가기

	eMsgRentalStoreMessage				= 1750,	// 위탁상점
	eMsgRentalStoreQuestionCancel			,	// 위탁중인 아이템을 취소 하시겠습니까?
	eMsgRentalCannotBuyBecauseTimeOver		,	// 판매 시간이 지난 아이템 입니다. 구입할 수 없습니다.
	eMsgRentalStoreQuestionBuy				,	// 정말 구입 하시겠습니까?
	eMsgRentalStoreInputFailed				,	// 잘못 입력하였습니다
	eMsgRentalStoreMovingItmeMessage1		,	// 재고 아이템이 있다면 자동으로 인벤토리로 옮깁니다.
	eMsgRentalStoreWantSellTexInput			,	// 원하는 판매 세율을 입력해 주세요. (1~7%)
	eMsgRentalStoreItemMessage				,	// 위탁 아이템
	eMsgRentalStoreItemMessage2				,	// 위탁상점(%d)
	eMsgRentalStoreItemMessage3				,	// 재고 아이템
	eMsgRentalStoreItemMessage4				,	// 위탁판매를 위한 이용비는 무료입니다.\n확인을 누르시면 판매를 시작합니다.
	eMsgRentalStoreItemMessage5				,	// 위탁판매를 위한 이용비는 %d (세금 %d%%적용) 루피아 입니다.\n확인을 누르시면 판매를 시작합니다.
	eMsgRentalStoreItemMessage6				,	// 판매 시간을 입력하세요. (1~24시간)
	eMsgRentalStoreItemMessage7				,	// 현재 판매되어 적립된 루피아는 총 %d 입니다.>>수금을 원하시면 확인버튼을 눌러주세요.
	eMsgRentalStoreItemMessage8				,	// 아이템을 위탁하였습니다.
	eMsgRentalStoreItemMessage9				,	// 아이템을 위탁하지 못했습니다.
	eMsgRentalStoreItemMessage10			,	// 아이템을 위탁을 취소하였습니다.
	eMsgRentalStoreItemMessage11			,	// 위탁한 아이템을 취소할 수 없습니다.
	eMsgRentalStoreItemMessage12			,	// 적립된 루피아가 없습니다.
	eMsgRentalStoreItemMessage13			,	// 적립된 루피아를 모두 찾았습니다.
	eMsgRentalStoreItemMessage14			,	// 세율이 변경되었습니다.
	eMsgRentalStoreItemMessage15			,	// 아이템을 구입하였습니다.
	eMsgRentalStoreItemMessage16			,	// 아이템을 구입하지 못했습니다.
	eMsgRentalStoreItemMessage17			,	// 상품 목록이 변경되어 갱신합니다.
	eMsgRentalStoreItemMessage18			,	// 30개 이상의 아이템이 재고로 쌓여 있습니다.

	eMsgChatRoomMessage1				= 1780,	// 채팅 룸
	eMsgChatRoomMessage2					,	// 새로 고침
	eMsgChatRoomMessage3					,	// 방번호
	eMsgChatRoomMessage4					,	// 방          제
	eMsgChatRoomMessage5					,	// 개설자
	eMsgChatRoomMessage6					,	// 인원
	eMsgChatRoomMessage7					,	// 방만들기
	eMsgChatRoomMessage8					,	// 입장
	eMsgChatRoomMessage9					,	// 닫기
	eMsgChatRoomMessage10					,	// 방장메뉴
	eMsgChatRoomMessage11					,	// 대화방 제목
	eMsgChatRoomMessage12					,	// 인원 제한
	eMsgChatRoomMessage13					,	// 공개 설정
	eMsgChatRoomMessage14					,	// 비밀번호 설정
	eMsgChatRoomMessage15					,	// 완료
	eMsgChatRoomMessage16					,	// 취소
	eMsgChatRoomMessage17					,	// 채팅실
	eMsgChatRoomMessage18					,	// 대화내용
	eMsgChatRoomMessage19					,	// 참여자
	eMsgChatRoomMessage20					,	// 초대하기
	eMsgChatRoomMessage21					,	// 청  소
	eMsgChatRoomMessage22					,	// 나가기
	eMsgChatRoomMessage23					,	// 번호
	eMsgChatRoomMessage24					,	// 이름
	eMsgChatRoomMessage25					,	// 채팅방에 연결을 시도합니다.
	eMsgChatRoomMessage26					,	// 채팅방으로 부터 연결해제 되었습니다.
	eMsgChatRoomMessage27					,	// 아무나 들어오세요!!
	eMsgChatRoomMessage28					,	// %d번 방에 입장하시겠습니까?
	eMsgChatRoomMessage29					,	// 비밀번호를 입력하세요.
	eMsgChatRoomMessage30					,	// 잘못 입력 하였습니다.
	eMsgChatRoomMessage31					,	// %s님을 추방하시겠습니까?
	eMsgChatRoomMessage32					,	// 방장만 초대할 수 있습니다.
	eMsgChatRoomMessage33					,	// %s님을 초대하시겠습니까?
	eMsgChatRoomMessage34					,	// 채팅방 연결에 성공하였습니다.
	eMsgChatRoomMessage35					,	// 서버가 접속을 수락하지 않았습니다.
	eMsgChatRoomMessage36					,	// 채팅방 생성 성공하였습니다.
	eMsgChatRoomMessage37					,	// 채팅방 생성 실패 하였습니다.
	eMsgChatRoomMessage38					,	// *%s님이 입장하였습니다.*
	eMsgChatRoomMessage39					,	// *%s님이 나가셨습니다.*
	eMsgChatRoomMessage40					,	// *%s님이 추방되었습니다.*
	eMsgChatRoomMessage41					,	// 채팅방에 입장하였습니다.
	eMsgChatRoomMessage42					,	// 채팅방에 입장하지 못했습니다.
	eMsgChatRoomMessage43					,	// 채팅방을 나갑니다.
	eMsgChatRoomMessage44					,	// %s님이 당신을 초대하였습니다. 수락하시겠습니까?
	eMsgChatRoomMessage45					,	// 초대가 취소되었습니다.
	eMsgChatRoomMessage46					,	// 채팅방 정보가 변경되었습니다.
	eMsgChatRoomMessage47					,	// 채팅방 정보 변경을 실패 하였습니다.
	eMsgChatRoomMessage48					,	// 방장에 의해 추방당하였습니다.

} eMsgCharacter;

//--------------------------------------------------------------
// Item
//--------------------------------------------------------------
typedef enum _eMsgItem
{
	// 공통
	eMsgItemCommonOwnerErr			=	2001, // 아이템 소유주 오류
	eMsgItemCommonInvenLack				, // 인벤토리 공간 부족
	eMsgItemCommonPositionErr			, // 이동위치 오류
	eMsgItemCommonNotExistItem			, // 존재하지 않는 아이템
	eMsgItemCommonMoneyErr				, // 루피아 부족
	eMsgItemCommonCannotFindInfo		, // 아이템 정보를 찾을 수 없음
	eMsgItemCommonNoInventory			, // pc인벤토리 이외의 공간에 있음
	
	eMsgCommonDistanceErrToNPC			, // npc와의 거리가 멀다
	eMsgCommonCannotClickNPC			, // 다른 주신지역의 npc는 클릭할 수 없음 // 2009
	eMsgItemCommonCashErr				, // 캐쉬가 부족합니다.

	// 아이템 이동
	eMsgItemMoveDistanceErr			=	2011, // 이동거리 오류
	eMsgItemMoveRoutingTime				, // 아이템 루팅 시간 오류
	eMsgItemMoveReceive					, // 아이템 획득
	eMsgItemMoveTwoHandErr				, // 양손무기 착용 오류(왼손에 아이템이 있음)
	eMsgItemMoveDropQuestion			, // 땅에 버리시겠습니까?
	eMsgItemMoveCannot					, // 이동할 수 없는 아이템
	eMsgItemMoveAutoReceive				, // [자동분배]%s, %s 획득 // 2017
	eMsgItemMoveFail				=	2020, // 그외 이유로 이동실패
	// 아이템 중첩
	eMsgItemPackDestination			=	2021, // 대상 아이템이 존재하지 않습니다.
	eMsgItemPackNotPack					, // 중첩 불가능한 아이템
	eMsgItemPackDisable					, // 서로 다른 아이템은 중첩 불가능
	eMsgItemPackNotAdd					, // 최대 중첩개수입니다.
	eMsgItemPackFail				=	2030, // 중첩 실패
	// 아이템 분해
	eMsgItemUnpackCountErr			=	2031, // 분해 개수 부적합
	eMsgItemUnpackNotUnpack				, // 언패킹 불가능한 아이템
	eMsgItemUnpackPlaceErr				, // 언패킹 자리 부적합
	eMsgItemUnpackFail				=	2040, // 분해 실패
	// 아이템 사용
	eMsgItemUseNotUse				= 	2041, // 사용할 수 없는 아이템
	eMsgItemUseCountErr					, // 아이템 카운트 에러
	eMsgItemUseConditionErr				, // 사용 제한 조건 에러
	eMsgItemUseCannot					, // 아이템을 사용할 수 없는 상태
	eMsgItemUseFail					=	2045, // 아이템 사용 실패
	// 아이템 장착
	eMsgItemEquipTypeErr			=	2046, // 장착 불가능한 아이템
	eMsgItemEquipPosErr					, // 장착 위치 오류 
	eMsgItemEquipExistItem				, // 장착 위치에 다른 아이템이 존재
	eMsgItemEquipConditionErr			, // 제한 사항에 의해 장착 못함
	// 아이템 장착-인벤토리 확장/해제
	eMsgItemEquipInvenIncOK				, // 인벤토리 확장 성공
	eMsgItemEquipInvenDecOK				, // 인벤토리 해제 성공
	eMsgItemEquipNotExistExpandInven	, // 인벤토리 확장 아이템이 없음
	eMsgItemEquipNoExpandedInven		, // 확장된 인벤토리 없음
	eMsgItemEquipInvenIncFail			, // 인벤토리 확장 실패
	eMsgItemEquipDecExistItem			, // 확장된 인벤토리에 아이템 있음
	eMsgItemEquipInvenDecFail			, // 인벤토리 해제 실패
	eMsgItemEquipInvenExpanded			, // 이미 인벤토리가 확장되어 있음
	eMsgItemEquipExpandDate				, // 인벤토리 확장기한 %s // 2058
	eMsgItemUseCannotNowZone			, // 아이템을 사용할 수 없는 지역입니다. 2059
	eMsgItemEquipFail				=	2060, // 장착 실패
	//아이템 구입
	eMsgItemBuySeveralNumOK			=	2101, // 아이템 여러개 구입 성공 
	eMsgItemBuyOneOK					, // 아이템 1개 구입 성공
	eMsgItemBuyOK						, // 아이템 구입 성공
	eMsgItemBuyMaxCountErr				, // 최대 구입 개수 오류 
	eMsgItemBuyQuestionItem				, // 아이템 구입 질문
	eMsgItemBuyQuestionItemNum			, // 아이템 구입 개수 질문
	eMsgItemBuyCannot					, // 아이템 구입 조건 부족
	eMsgItemBuyDoNot					, // %s 아이템을 구입하지 못했습니다.
	eMsgItemBuyMinCountErr				, // 최소 구입 개수 오류
	eMsgItemBuyFail					=	2110, // 구입 실패
	// 아이템 수리
	eMsgItemRepairSuccess			=	2111, // 수리 성공
	eMsgItemRepairNeedNot				, // 수리할 필요 없는 아이템
	eMsgItemRepairDoNot					, // 이곳에서 수리할 수 없는 아이템
	eMsgItemRepairOK					, // 수리되었습니다.
	eMsgItemRepairFail					, // 수리 실패
	// 아이템 판매
	eMsgItemSellSuccess				=	2116, // 판매 성공
	eMsgItemSellQuestionItem			, // 판매할 아이템 질문
	eMsgItemSellDoNot					, // 이곳에서 판매할 수 없는 아이템
	eMsgItemSellFail				=	2120, // 판매 실패 
	// 아이템 제련
	eMsgItemRefineOneOverOK			=	2121, // 제련 1단계 이상의 아이템이 성공
	eMsgItemRefineFirstOK				, // 첫번째 제련 성공
	eMsgItemRefineOK					, // 제련 성공
	eMsgItemRefineDisappear				, // 아이템 사라짐
	eMsgItemRefineOneOverErr			, // 제련 1단계 이상의 아이템이 실패
	eMsgItemRefineFirstErr				, // 첫번째 제련 실패
	eMsgItemRefineErr					, // 제련 실패
	eMsgItemRefineMeterialErr			, // 첨가 불가능한 보조재료
	eMsgItemRefineMainCannot			, // 강화제련 횟수 제한
	eMsgItemRefineSubCannot				, // 주술제련 횟수 제한
	eMsgItemRefineDoNot					, // 제련할 수 없는 아이템
	eMsgItemRefineSelectMeterial		, // 보조재료를 선택하여 주십시오.
	eMsgItemRefineSelectItem			, // 제련할 아이템을 선택하여 주십시오.
	eMsgItemRefineWarningLevel1			, // 제련 경고
	eMsgItemRefineWarningLevel2			, // 제련 경고
	eMsgItemRefineWarningLevel3			, // 제련 경고
	eMsgItemRefineWarningLevel4			, // 제련 경고
	eMsgItemRefineWarningLevel5			, // 제련 경고
	eMsgItemRefineWarningLevel6			, // 제련 경고
	eMsgItemRefineWarningLevel7			, // 제련 경고
	eMsgItemRefineWarningLevel8			, // 제련 경고
	eMsgItemRefineSubWarning			, // 주술 제련 경고
	eMsgItemRefineWarningLevel9			, // 제련 경고	
	eMsgItemRefineSubInitWarning		, // 주술제련 초기화 // 2144
	eMsgItemRefineSubInitWarning2		, // 주술제련 초기화 // 2144
	eMsgItemRefineNeedMoneyErr			, // 루피아 부족
	eMsgItemRefineInitialize			, // 제련 결과 아이템 초기화
	eMsgItemRefineWarningLevel10		, // 제련 경고	
	eMsgItemRefineWarningLevel11		, // 제련 경고	

	eMsgItemRefineFail				=	2150, // 제련 실패
	// 위치 저장
	eMsgSavePositionQuestion		=	2151, // 현재 위치를 저장하시겠습니까?
	eMsgSavePositionOK					, // 현재 위치를 저장했습니다.
	eMsgSavePositionFail			=	2155, // 현재 위치를 저장하지 못했습니다.
	// 전직
	eMsgJobChangeOK					=	2156, // 전직 성공
	eMsgJobChangeOtherChar				, // 다른 캐릭터 전직 성공
	eMsgJobChangeFail				=	2160, // 전직 실패
	// 차크라 환산
	eMsgChakraConversionOK			=	2161, // 차크라 환산 성공
	eMsgChakraConversionItemErr			, // 착용한 아이템 있음
	eMsgChakraConversionFail			, // 차크라 환산 실패	// 2163
	// 아이템 내구도
	eMsgItemDurabilityWarning		=	2165, // 아이템 내구도 낮음
	// 주신 변경
	eMsgTrimuritiChangeCondition1	=	2171, // 주신 변경 조건1-돈
	eMsgTrimuritiChangeCondition2		, // 주신 변경 조건2-돈, 아이템
	eMsgTrimuritiChangeCondition3		, // 주신 변경 조건-길드 가입 중엔 안됨
	eMsgTrimuritiChangeConditionDay		, // 주신 변경 조건-날짜
	eMsgTrimuritiChangeOK				, // 주신 변경 공지
	eMsgTrimuritiChangeQuestion			, // 주신 %s신으로 변경하시겠습니까?
	// 주신 포인트
	eMsgTrimuritiPointCondition1	=	2181, // 주신 포인트 변경 조건-돈,아이템
	eMsgTrimuritiPointCondition2		, // 주신 포인트 변경 조건-주신포인트 제한
	eMsgTrimuritiPointOK				, // 주신 포인트 변경 성공 // 2183

	eMsgShopDefaultName				=	2191, // 물건사세요
	eMsgShopNamePublicity				, // [판매]%s[%s]
	eMsgShopTotalPriceOverflow			, // 판매 총액이 너무 큽니다.
	eMsgShopNotifyCondition1			, // 1. 개인 상점 개설 시에 상점제목의 가격보다 더 높은 다른 가격으로 등록을 하는 경우
	eMsgShopNotifyCondition2			, // 2. 가격에 의도적으로 단위를 조절하기 위해 '0'을 덧붙이는 행위
	eMsgShopNotifyPunishment			, // 제재 기준 : 차 7일 계정압류, 2차 영구 계정압류
	eMsgShopExpandDate					, // 개인 상점 확장기한 %s
	eMsgShopExpandOK					, // 개인상점이 확장됐습니다.
	eMsgShopAutoRouting					, // 자동 돈줍기 기능이 적용되었습니다.
	eMsgShopAdeptDate					, // 까지 적용

	eMsgOfferingOK					=	2206, // 헌납 성공
	eMsgOfferingCannot					, // 헌납할 수 없는 아이템
	eMsgOfferingNotify1					, // 축복의 신단은 신에게 제물을 바치고 자신의 신앙심을 재확인하여 축복을 받는 기능을 가지고 있습니다.
	eMsgOfferingNotify2					, // 제물의 수량과 가치에 따라 제련확률이 증가하는 축복을 받을 수 있습니다.
	eMsgOfferingNotify3					, // 단, 축복의 신단에 기부되어지는 아이템은 사라지게 됩니다. // 2210
	eMsgOfferingNotify4					, // 상단의 게이지가 모두 차게 되면 하단의 게이지가 차게 됩니다.
	eMsgOfferingNotify5					, // 상단의 게이지와 하단의 게이지를 채우는데 소요되는 루피아 또는 아이템의 양은 다릅니다.
	eMsgOfferingFail				=	2215 // 헌납 실패

} eMsgItem;

typedef enum _eMsgInfo
{
	// 메인창 버튼 정보
	eMsgMainCheckPrimiumBuy			=	3000, // 프리미엄 아이템 구입
	eMsgMainCheckCharacInfo				, // 캐릭터 정보
	eMsgMainCheckInventory				, // 인벤토리
	eMsgMainCheckQuest					, // 퀘스트 창
	eMsgMainCheckSkill					, // 스킬
	eMsgMainCheckOption					, // 옵션
	eMsgMainCheckCommand				, // 명령
	eMsgMainCheckPK						, // PK	

	eMsgCommandSitDown					, // 앉기
	eMsgCommandWalk						, // 걷기
	eMsgCommandAttack					, // 공격
	eMsgCommandTrade					, // 교환
	eMsgCommandTarget					, // 타겟
	eMsgCommandPickUp					, // 줍기
	eMsgCommandParty					, // 파티
	eMsgCommandPartyDrop				, // 파티 탈퇴
	eMsgCommandShop						, // 개인 상점
	eMsgCommandProvocation				, // 도발
	eMsgCommandGreeting					, // 인사
	eMsgCommandRush						, // 돌격 // 3019
	eMsgCommandDuel						, // 결투

	// 아이템 정보
	eMsgItemInfoRepairTitle			=	3021, // 수리정보
	eMsgItemInfoSellTitle				, // 판매정보
	eMsgCommandWait						, // 외출(Away)
	eMsgCommandSupport					, // 도움(Assist)
	eMsgCommandBlog						, // 블로그(Blog)


	eMsgItemInfoCannotRepair		=	3026, // 수리불가
	eMsgItemInfoCannotSell				, // 판매불가
	eMsgItemInfoCannotRefine			, // 제련불가
	eMsgItemInfoCannotMainRefine		, // 강화제련 불가
	eMsgItemInfoCannotSubRefine			, // 주술제련 불가
	eMsgItemInfoUnbreakable				, // 파괴불가 // 3031
	
	eMsgItemInfoHourMinute			=	3032, // 유효시간 %d시간 %d분
	eMsgItemInfoHour					, // 유효시간 %d시간
	eMsgItemInfoMinute					, // 유효시간 %d분
	eMsgItemInfoPrice					, // %d 루피아
	eMsgItemInfoNeedMoney				, // %d 루피아 필요
	eMsgItemInfoRemainMainRefine		, // 남은 강화제련 횟수
	eMsgItemInfoRemainSubRefine			, // 남은 주술제련 횟수
	eMsgItemInfoPackCount				, // 중첩 개수
	eMsgItemInfoMaxPackCount			, // 최대 구입 개수
	eMsgItemInfoPrivateUse				, // ~전용
	eMsgItemInfoUsable					, // ~용
	eMsgItemInfoNeedLevel				, // %d 레벨 필요
	eMsgItemInfoMuscleChakra			, // 근육의 차크라 %d
	eMsgItemInfoNerveChakra				, // 신경의 차크라 %d
	eMsgItemInfoHeartChakra				, // 심장의 차크라 %d
	eMsgItemInfoSoulChakra				, // 정신의 차크라 %d
	eMsgItemInfoDurability				, // 내구도 %d / %d
	eMsgItemInfoDuration				, // 지속시간 %d초
	eMsgItemInfoAttackSpeedVeryHigh		, // 공격속도 매우빠름
	eMsgItemInfoAttackSpeedHigh			, // 공격속도 빠름
	eMsgItemInfoAttackSpeedNormal		, // 공격속도 보통
	eMsgItemInfoAttackSpeedLow			, // 공격속도 느림
	eMsgItemInfoAttackSpeedVeryLow		, // 공격속도 매우느림
	eMsgItemInfoCostHP					, // HP 소모
	eMsgItemInfoCostTP					, // TP 소모
	eMsgItemInfoCostItem				, // %s 소모
	eMsgItemInfoCostItemCount			, // %s %d개 소모 
	eMsgItemInfoPrice2					, // %s 루피아
	eMsgItemInfoPrice3					, // %s 캐쉬 // 3060
	// 스킬 정보
	eMsgSkillInfoNeedCondition		=	3061, // 요구 조건 
	eMsgSkillInfoNextCondition			, // 다음 단계 조건
	eMsgSkillInfoNeedLevel				, // 필요 레벨
	eMsgSkillInfoNeedSkillLevel			, // 필요 스킬 레벨
	eMsgSkillInfoNeedItem				, // 필요 아이템
	eMsgSkillInfoCannotFindInfo		=	3070, // 스킬 정보 찾을 수 없음
	// 적용 대상
	eMsgAllowedTargetSelf			=	3071, // 본인 	
	eMsgAllowedTargetFriendly			, // PC, 주신전에서 같은 주신			
	eMsgAllowedTargetFriendlyExceptMe	, // 자신을 제외	
	eMsgAllowedTargetParty				, // 파티원들				
	eMsgAllowedTargetGuild				, // 길드원들
	eMsgAllowedTargetAll				, 
	eMsgAllowedTargetFriendlyCorpse		, // 부활마법으로 동료의 시체에 사용
	eMsgAllowedTargetEnemeyCorpse		, // 시체폭파 마법으로 적의 시체에 사용
	eMsgAllowedTargetGate				, // 성문	// 3079
	// Effect
	eMsgEffectDamage				=	3101,
	eMsgEffectDamageLimitLevel			, // 레벨제한으로 %s%% 감소
	eMsgEffectEnergyOfSword				, // 검 공격력 %s%% - %s%% 향상
	eMsgEffectFire						, // 화염 공격력 %s - %s
	eMsgEffectCold						, // 냉기 공격력 %s - %s  //fors_debug 冷陋구橄昑鞫刻돨뒈렘
	eMsgEffectLightning					, // 전격 공격력 %s - %s
	eMsgEffectPoison					, // 독 공격력 %s - %s	
	eMsgEffectAllDamageUp				, // 모든 속성 공격력 %s%% 상승
	eMsgEffectAllDamageDown				, // 모든 속성 공격력 %s%% 감소 // 3109

	eMsgEffectDamageSplash			=	3111, // 스플래쉬 %s - %s
	eMsgEffectFireSplash				, // 화염 스플래쉬 공격력 %s - %s
	eMsgEffectColdSplash				, // 냉기 스플래쉬 공격력 %s - %s
	eMsgEffectLightningSplash			, // 전격 스플래쉬 공격력 %s - %s
	eMsgEffectPoisonSplash				, // 독 스플래쉬 공격력 %s - %s // 3115
	
	eMsgEffectSummon				=	3121, // %s %s마리 소환
	eMsgEffectIllusion					, // %s %s마리 생성	// 3122

	eMsgEffectMoveSpeedPlus			=	3131, // 이동속도 %s%% 증가
	eMsgEffectMoveSpeedMinus			, // 이동속도 %s%% 감소 
	eMsgEffectAttackSpeedPlus			, // 공격속도 %s%% 증가
	eMsgEffectAttackSpeedMinus			, // 공격속도 %s%% 감소
	eMsgEffectCastSpeedPlus				, // 캐스팅속도 %s%% 증가
	eMsgEffectCastSpeedMinus			, // 캐스팅속도 %s%% 감소 // 3136

	eMsgEffectInvisible				=	3141, // 투명상태
	eMsgEffectWizardEyes				, // 투명상태 보기
	eMsgEffectHold						, 
	eMsgEffectStun						, // 기절
	eMsgEffectSleep						, // 잠
	eMsgEffectBlind						, // 장님
	eMsgEffectTerror					, // 도망가게 한다.
	eMsgEffectTaunt						, // 약 올려서 공격하게 한다.
	eMsgEffectInvulnerable				, // 무적상태
	eMsgEffectExpandBag					, // 인벤토리 확장 %s X %s
	eMsgEffectConcentration				, // 캐스팅 성공 %s%%증가
	eMsgEffectDisruption				, // 마법 캐스팅 실패
	eMsgEffectMagicShield				, // HP가 있는 마법 방패. 최대 HP %s
	eMsgEffectStealHP					, // 데미지의 %s%% HP 훔침
	eMsgEffectStealTP					, // 데미지의 %s%% TP 훔침
	eMsgEffectBash						, // %s 확률의 추가 데미지 %s
	eMsgEffectMultipleStrike			, // %s%% 데미지 %s회
	eMsgEffectPierceStrike				, // 관통하기 - 사정거리 %s
	eMsgEffectKnockBack					, // %s 확률의 KnockBack %s
	eMsgEffectHPDown					, // HP %s%%감소
	eMsgEffectHeal						, // HP %s회복
	eMsgEffectHeal2						, // HP %s회복 - 계산식 있음
	eMsgEffectTargetHeal				, // 대상 HP %s회복
	eMsgEffectHealRate					, // HP %s%%회복
	eMsgEffectRecoverTP					, // TP %s회복
	eMsgEffectRecoverTP2				, // TP %s회복 - 계산식 있음
	eMsgEffectTargetHealTP				, // 대상 TP %s회복
	eMsgEffectRecoverTPRate				, // TP %s%%회복
	eMsgEffectiACrificeHP				, // HP %s 소모
	eMsgEffectCure						, // EffectID %s
	eMsgEffectResurrect					, // 경험치 %s 회복 - 소모 부활설 %s개
	eMsgEffectReflectDamage				, // 데미지 반사 %s%%
	eMsgEffectAbsorbDamage				, // 데미지 흡수 %s%%
	eMsgEffectRangeUp					, // 사정거리 %s증가 // 3174
	eMsgEffectReflectDamagePlus			, // 데미지 반사 %s
	eMsgEffectAbsorbElementalDamage		, // 속성 데미지 흡수 %s%%
	eMsgEffectAbsorbPartyPhs			, // %d%%만큼의 파티원의 물리 데미지를 흡수
	eMsgEffectMinusPercentHPforTime		, // 일정 시간동안 %s%%만큼 지속적으로 자신의 HP 감소
	eMsgEffectQuickDash					, // %s만큼의 거리를 순간적으로 대쉬
	eMsgEffectPlusPercentDefense		, // %s%%만큼의 방어력 상승

	eMsgEffectCriticalStrikeRate	=	3181, // %s확률의 공격력 %s%%증가
	eMsgEffectCriticalStrike			, // %s확률의 공격력 %s증가
	eMsgEffectWeaponMastery				, // %s 공격력 %s
	eMsgEffectWeaponMastery2			, // %s 공격력 %s, 공격속도 %s증가
	eMsgEffectDamagePlus				, // 공격력 %s - %s 증가
	eMsgEffectDamagePlusRate			, // 공격력 %s%% - %s%% 증가
	eMsgEffectDamageMinus				, // 공격력 %s - %s 감소
	eMsgEffectDamageMinusRate			, // 공격력 %s%% - %s%% 감소
	eMsgEffectFireDamagePlus			, // 화염 공격력 %s - %s 증가
	eMsgEffectFireDamagePlusRate		, // 화염 공격력 %s%% - %s%% 증가
	eMsgEffectFireDamageMinus			, // 화염 공격력 %s - %s 감소
	eMsgEffectFireDamageMinusRate		, // 화염 공격력 %s%% - %s%% 감소
	eMsgEffectColdDamagePlus			, // 냉기 공격력 %s - %s 증가
	eMsgEffectColdDamagePlusRate		, // 냉기 공격력 %s%% - %s%% 증가
	eMsgEffectColdDamageMinus			, // 냉기 공격력 %s - %s 감소
	eMsgEffectColdDamageMinusRate		, // 냉기 공격력 %s%% - %s%% 감소
	eMsgEffectLightningDamagePlus		, // 전격 공격력 %s - %s 증가
	eMsgEffectLightningDamagePlusRate	, // 전격 공격력 %s%% - %s%% 증가
	eMsgEffectLightningDamageMinus		, // 전격 공격력 %s - %s 감소
	eMsgEffectLightningDamageMinusRate	, // 전격 공격력 %s%% - %s%% 감소
	eMsgEffectPoisonDamagePlus			, // 독 공격력 %s - %s 증가
	eMsgEffectPoisonDamagePlusRate		, // 독 공격력 %s%% - %s%% 증가
	eMsgEffectPoisonDamageMinus			, // 독 공격력 %s - %s 감소
	eMsgEffectPoisonDamageMinusRate		, // 독 공격력 %s%% - %s%% 감소
	eMsgEffectDefenceIgnoreDamage		, // 방어력을 무시한 공격력 %s - %s
	eMsgEffectSkillDamagePlus			, // %s의 공격력 %s - %s 추가
	eMsgEffectDefenceMinusDamage		, // 방어력 %s를 감소시킨 공격력
	eMsgEffectTPBurn					, // TP데미지 %s의 %d%%를 공력력으로 변환 
	eMsgEffectTPBurn2					, // TP %s 감소// 3209
	
	eMsgEffectFireResistPlus		=	3211, // 화염 저항력 %s 증가
	eMsgEffectFireResistPlusRate		, // 화염 저항력 %s%% 증가
	eMsgEffectFireResistMinus			, // 화염 저항력 %s 감소    //fors_debug 警속槻벎죗깊斤口돨뒈렘
	eMsgEffectFireResistMinusRate		, // 화염 저항력 %s%% 감소
	eMsgEffectColdResistPlus			, // 냉기 저항력 %s 증가
	eMsgEffectColdResistPlusRate		, // 냉기 저항력 %s%% 증가
	eMsgEffectColdResistMinus			, // 냉기 저항력 %s 감소
	eMsgEffectColdResistMinusRate		, // 냉기 저항력 %s%% 감소
	eMsgEffectLightningResistPlus		, // 전격 저항력 %s 증가
	eMsgEffectLightningResistPlusRate	, // 전격 저항력 %s%% 증가
	eMsgEffectLightningResistMinus		, // 전격 저항력 %s 감소
	eMsgEffectLightningResistMinusRate	, // 전격 저항력 %s%% 감소
	eMsgEffectPoisonResistPlus			, // 독 저항력 %s 증가
	eMsgEffectPoisonResistPlusRate		, // 독 저항력 %s%% 증가
	eMsgEffectPoisonResistMinus			, // 독 저항력 %s 감소
	eMsgEffectPoisonResistMinusRate		, // 독 저항력 %s%% 감소
	eMsgEffectAllResistPlus				, // 모든 저항력 %s 증가
	eMsgEffectAllResistPlusRate			,
	eMsgEffectAllResistMinus			, // 모든 저항력 %s 감소
	eMsgEffectAllResistMinusRate		, // 3230

	eMsgEffectDamageTP					, // Duration동안 param1 만큼의 TP 데미지 
	eMsgEffectDOTbyDice					, // function확률로 duration동안 param1~param2 의 데미지
	eMsgEffectHealPlus					, // HP회복시 param1만큼의 추가회복
	eMsgEffectRecoverTPPlus				, // TP회복시 param1만큼의 추가회복

	
	eMsgEffectMusclePlus			=	3236, // 근육의 차크라 %s 증가
	eMsgEffectNervesPlus				, // 신경의 차크라 %s 증가
	eMsgEffectHeartPlus					, // 심장의 차크라 %s 증가
	eMsgEffectMindPlus					, // 정신의 차크라 %s 증가
	eMsgEffectMuscleMinus				, // 근육의 차크라 %s 감소
	eMsgEffectNervesMinus				, // 신경의 차크라 %s 감소
	eMsgEffectHeartMinus				, // 심장의 차크라 %s 감소
	eMsgEffectMindMinus					, // 정신의 차크라 %s 감소 
	eMsgEffectAllStatPlus				, // 모든 차크라 %s 증가
	eMsgEffectAllStatPlusRate			,
	eMsgEffectAllStatMinus				, // 모든 차크라 %s 감소
	eMsgEffectAllStatMinusRate			, // 3247

	eMsgEffectWeaponMastery3		=	3251, // %s 공격성공 %s증가
	eMsgEffectAttackRatePlus			, // 공격성공 %s 증가
	eMsgEffectAttackRatePlusRate		, // 공격성공 %s%% 증가
	eMsgEffectAttackRateMinus			, // 공격성공 %s 감소
	eMsgEffectAttackRateMinusRate		, // 공격성공 %s%% 감소
	eMsgEffectDodgeRatePlus				, // 회피 %s 증가
	eMsgEffectDodgeRatePlusRate			, // 회피 %s%% 증가
	eMsgEffectDodgeRateMinus			, // 회피 %s 감소
	eMsgEffectDodgeRateMinusRate		, // 회피 %s%% 감소
	eMsgEffectACPlus					, // 방어도 %s 증가
	eMsgEffectACPlusLimitLevel			, // 레벨 제한으로 %s%% 감소
	eMsgEffectACPlusRate				, // 방어도 %s%% 증가
	eMsgEffectACMinus					, // 방어도 %s 감소
	eMsgEffectACMinusLimitLevel			, // 레벨 제한으로 %s%% 감소
	eMsgEffectACMinusRate				, // 방어도 %s%% 감소
	eMsgEffectMaxHPPlus					, // 최대 HP %s 증가
	eMsgEffectMaxHPPlusRate				, // 최대 HP %s%% 증가
	eMsgEffectMaxHPMinus				, // 최대 HP %s 감소
	eMsgEffectMaxHPMinusRate			, // 최대 HP %s%% 감소
	eMsgEffectHPRecoveryPlus			, // HP 회복 %s 증가
	eMsgEffectHPRecoveryPlusRate		, // HP 회복 %s%% 증가
	eMsgEffectHPRecoveryMinus			, // HP 회복 %s 감소
	eMsgEffectHPRecoveryMinusRate		, // HP 회복 %s%% 감소
	eMsgEffectMaxTPPlus					, // 최대 TP %s 증가
	eMsgEffectMaxTPPlusRate				, // 최대 TP %s%% 증가
	eMsgEffectMaxTPMinus				, // 최대 TP %s 감소
	eMsgEffectMaxTPMinusRate			, // 최대 TP %s%% 감소
	eMsgEffectTPRecoveryPlus			, // TP 회복 %s 증가
	eMsgEffectTPRecoveryPlusRate		, // TP 회복 %s%% 증가
	eMsgEffectTPRecoveryMinus			, // TP 회복 %s 감소
	eMsgEffectTPRecoveryMinusRate		, // TP 회복 %s%% 감소
	eMsgEffectCostTP					, // TP 소모량 %s 감소
	eMsgEffectCostTPRate				, // TP 소모량 %s%% 감소
	eMsgEffectBonusExp					, // 습득 경험치 %s 증가
	eMsgEffectBonusExpRate				, // 습득 경험치 %s%% 증가
	eMsgEffectEtcSkillDisp1				, // 물리, 피어스에 대한 데미지 면역
	eMsgEffectEtcSkillDisp2				, // 물리, 스턴, 피어스에 대한 데미지 면역
	eMsgEffectEtcSkillDisp3				, // 물리, 스턴, 슬립, 피어스에 대한 데미지 면역
	eMsgEffectPlusDefense				, // %s만큼의 방어력 상승

	
	eMsgEffectResetState			=	3291, // 차크라 포인트 초기화
	eMsgEffectResetSkill				, // 스킬 포인트 초기화
	eMsgEffectPreventHPRecovery			, // HP 자동 회복 방해
	eMsgEffectPreventTPRecovery			, // TP 자동 회복 방해
	eMsgEffectSkillLevelUp				, // %s 레벨 %s 증가
	eMsgEffectDefaunt					, // 타인을 공격할 확률 증가 // 3296
	eMsgEffectRefinePlus				, // 무기 강화제련등급 %s 상승
	eMsgEffectEnhanceHardnessOfArmor	, // 장착방어구 내구도감소율 줄임
	eMsgEffectFixedDamagePlus			, // 최종 데미지 %d 추가
	eMsgEffectDamageBonusForNextAttack	, // 1회 공격데미지 %s%% 상승

	eMsgHotKeyInfoTitle				= 3301,
	eMsgHotKeyInfoForward				, // 전 : W
	eMsgHotKeyInfoBackward				, // 후 : S
	eMsgHotKeyInfoLeft					, // 좌 : A
	eMsgHotKeyInfoRight					, // 우 : D
	eMsgHotKeyInfoRun					, // 달리기 / 걷기 : Z
	eMsgHotKeyInfoSitDown				, // 앉기 / 서기 : X
	eMsgHotKeyInfoCamera				, // 카메라 고정 : F12
	eMsgHotKeyInfoDefaultCamera			, // 카메라 기본 시점 : Instert, 마우스 휠 버튼
	eMsgHotKeyInfoPointView				, // 1인칭,3인칭 전환 : F11
	eMsgHotKeyInfoZoomIn				, // 줌 인-
	eMsgHotKeyInfoZoomOut				, // 줌 아웃+
	eMsgHotKeyInfoLeft2					, // 좌 : <-
	eMsgHotKeyInfoRight2				, // 우 : ->
	eMsgHotKeyInfoSelectTarget			, // 가까운 적 선택 : E
	eMsgHotKeyInfoAttack				, // 공격 : R
	eMsgHotKeyInfoSelectMember			, // 근접한 동료 선택 : T
	eMsgHotKeyInfoPickUp				, // 줍기 : F
	eMsgHotKeyInfoPreviousQuick			, // 이전 퀵바 : -
	eMsgHotKeyInfoNextQuick				, // 다음 퀵바 : =
	eMsgHotKeyInfoQuickBar1				, // 퀵바 1 선택 : Shift + 1
	eMsgHotKeyInfoQuickBar2				, // 퀵바 2 선택 : Shift + 2
	eMsgHotKeyInfoQuickBar3				, // 퀵바 3 선택 : Shift + 3
	eMsgHotKeyInfoQuickBar4				, // 퀵바 4 선택 : Shift + 4
	eMsgHotKeyInfoQuickBar5				, // 퀵바 5 선택 : Shift + 5
	eMsgHotKeyInfoQuickSlot1			, // 퀵슬롯 1 사용 : 1
	eMsgHotKeyInfoQuickSlot2			, // 퀵슬롯 2 사용 : 2
	eMsgHotKeyInfoQuickSlot3			, // 퀵슬롯 3 사용 : 3
	eMsgHotKeyInfoQuickSlot4			, // 퀵슬롯 4 사용 : 4
	eMsgHotKeyInfoQuickSlot5			, // 퀵슬롯 5 사용 : 5
	eMsgHotKeyInfoQuickSlot6			, // 퀵슬롯 6 사용 : 6
	eMsgHotKeyInfoQuickSlot7			, // 퀵슬롯 7 사용 : 7
	eMsgHotKeyInfoQuickSlot8			, // 퀵슬롯 8 사용 : 8
	eMsgHotKeyInfoQuickSlot9			, // 퀵슬롯 9 사용 : 9
	eMsgHotKeyInfoQuickSlot0			, // 퀵슬롯 0 사용 : 0
	eMsgHotKeyInfoWholeChat				, // 전체대화
	eMsgHotKeyInfoWhisper				, // 귓속말
	eMsgHotKeyInfoPartyChat				, // 파티 대화
	eMsgHotKeyInfoAshuramChat			, // 아쉬람 대화
	eMsgHotKeyInfoRegisterAddress		, // 친구등록
	eMsgHotKeyInfoResponseWhisper		, // 귓속말 응답 : V
	eMsgHotKeyInfoActiveChat			, // 채팅창 활성 : Enter
	eMsgHotKeyInfoAshuramMemberGrade	, // 아쉬람 구성원 등급 변경 : /아쉬람등급 '이름' '등급'
	eMsgHotKeyInfoAshuramNotify			, // 아쉬람 공지사항 변경 : /공지사항 '공지내용'
	eMsgHotKeyInfoAshuramHomepage		, // 아쉬람 홈페이지 변경 : /홈페이지 '홈주소'
	eMsgHotKeyInfoCharacterInfo			, // 캐릭터 정보창
	eMsgHotKeyInfoInventory				,
	eMsgHotKeyInfoQuest					,
	eMsgHotKeyInfoSkill					,
	eMsgHotKeyInfoOption				,
	eMsgHotKeyInfoCommand				,
	eMsgHotKeyInfoGuild					,
	eMsgHotKeyInfoAddress				,
	eMsgHotKeyInfoHelp					,
	eMsgHotKeyInfoBalloon				, // 풍선말
	eMsgHotKeyInfoNameHide				, // 이름 숨기기
	eMsgHotKeyInfoUIHide				, // UI 모두 숨기기
	eMsgHotKeyInfoMiniMap				, // 미니맵
	eMsgHotKeyInfoScreenShot			, // 스크린샷
	eMsgHotKeyInfoTrade					, // 교환
	eMsgHotKeyInfoCloseWin				, // 창닫기 : ESC // 3361
	eMsgHotKeyTilte1					, // 행동관련
	eMsgHotKeyTilte2					, // 퀵슬롯바
	eMsgHotKeyTilte3					, // 채팅관련
	eMsgHotKeyTilte4					, // 윈도우관련
	eMsgHotKeyChangeChatWndStyle		, // 채팅창 스타일 변경

	eMsgPremiumReqFail				= 4001, // 서비스 신청이 실패했습니다.
	
	eMsgPremiumInfoBuyMinCount			, // 최소 %d개 구입
	eMsgPremiumInfoBuyDiscount			, // %d개 구입 시 %d%% 할인
	
	eMsgPremiumBuyQuestion			= 4010, // %s %s개를 %s캐쉬로 구입하시겠습니까?
	eMsgPremiumBuyOK					, // %s을(를) %s캐쉬로 구입했습니다.
	eMsgPremiumReqPay					, // %캐쉬로 구입하시겠습니까?
	eMsgPremiumPaySystemErr				, // 타니 결제 서버가 응답하지 않습니다. 잠시 후에 다시 시도해 주시기 바랍니다.
	eMsgPremiumPaySystemErr2			, // 타니 결제 서버 연결을 위한 프로그램 초기화에 실패했습니다.
	eMsgPremiumPaySystemErr3			, // 타니 결제 서버 연결 초기화에 실패했습니다.
	eMsgPremiumPaySystemErr4			, // 타니 결제 서버 연결을 위한 프로그램 검색에 실패했습니다.
	eMsgPremiumPaySystemErr5			, // 타니 결제 서버가 알 수 없는 오류를 만들었습니다.
	eMsgPremiumReqInvenExpandBuy		, // 구입하시겠습니까? 이미 구입했을 경우 재구입시 유효기간이 한달 더 확장됩니다.
	eMsgPremiumReq2GradeInit			, // 2차 전직을 초기화 합니다. 9900 타니가 소비되며 2차 전직이 초기화 되면 2차 전직 퀘스트를 다시 수행해야 합니다.
	eMsgPremiumReq2GradeInitErr			, // 2차 전직을 한 상태에서만 초기화가 가능합니다.
	eMsgPremiumReq2GradeInitOK			, // 2차 전직을 완료하였습니다.
	eMsgPremiumReq2GradeInitErr2		, // 장착한 아이템을 모두 해제후 다시 수행해 주십시오
	eMsgPremiumReqChkraInitQuestion		, // 재분배를 위해 차크라를 초기화 하겠습니까?  (4023)
	eMsgPremiumReqSkillInitQuestion		, // 재분배를 위해 스킬을 초기화 하겠습니까? (4024)
	eMsgPremiumReqChkraSkillQuestion	, // 재분배를 위해 차크라 및 스킬을 초기화 하겠습니까? (2025)
	eMsgPremiumReqResultOKay			, // 성공적으로 적용되었습니다.
	eMsgPremiumItemEffect1				, //4027	0	0	0	인벤토리 확장 기능이 적용되었습니다.
	eMsgPremiumItemEffect2				, //4028	0	0	0	개인상점 확장 기능이 적용되었습니다.
	eMsgPremiumItemEffect3				, //4029	0	0	0	루피아 자동 습득 기능이 적용되었습니다.
	eMsgPremiumItemEffect4				, //4030	0	0	0	아누바바 효과가 적용되었습니다.
	eMsgPremiumItemEffect5				, //4031	0	0	0	아트만 효과가 적용되었습니다.
	eMsgPremiumItemEffect6				, //4032	0	0	0	모든 차크라 상승효과가 적용되었습니다.
	eMsgPremiumItemEffect7				, //4033	0	0	0	아누바바 꾸러미의 효과가 적용되었습니다.
	eMsgPremiumItemEffect8				, //4034	0	0	0	아트만 꾸러미의 효과가 적용되었습니다.
	eMsgPremiumItemEffect9				, //4035	0	0	0	골드 꾸러미의 효과가 적용되었습니다.
	eMsgPremiumItemEffect10				, //4036	0	0	0	플래티넘 꾸러미의 효과가 적용되었습니다.
	eMsgPremiumItemEffect11				, //4037	0	0	0	적용기간은 프리미엄 서비스 이용 내역에서 확인하실 수 있습니다.
	eMsgPremiumItemMonsterEventError	, //4038	몬스터 소환 주문서는 파미르 지역에서만 사용할 수 있습니다.
	eMsgPremiumItemChaturangaEnter		, //4039	차투랑가로 입장합니다.
	eMsgPremiumItemChaturangaEnterError	, //4040	30레벨 이상의 플레이어가 차투랑가에 입장할 수 있습니다.
	eMsgPremiumItemChaturangaEnterError2, //4041	30레벨 이상의 플레이어가 차투랑가에 입장할 수 있습니다.
	eMsgEventItemUseOK					, //4042	이벤트 아이템 '아이원잇'을 적립하였습니다.
	eMsgEventItemUseError				, //4043	본 아이템은 이벤트 NPC를 통해 적립할 수 있습니다.

	eMsgInventoryExpansionDisabled		, //4044	0	0	0	인벤토리 확장 기능이 해제 되었습니다.	Inventory expansion has been disabled.
	eMsgCloseInvendowWindowTry			, //4045	0	0	0	인벤토리 창을 닫은후 다시 시도해 주십시오.	Close the inventory window and try again.
	eMsgPrivateStoreExpansionDisabled	, //4046	0	0	0	개인상점 확장 기능이 해제 되었습니다.	Private store expansion has been disabled.
	eMsgClosePrivateStoreTry			, //4047	0	0	0	개인상점 창을 닫은후 다시 시도하여 주십시오.	Close the private store window and try again.
	eMsgAutomaticRupiaDisabled			, //4048	0	0	0	루피아 자동 습득 기능이 해제 되었습니다	Automatic rupia acquisition has been disabled.
	eMsgAnubabaEffectDisabled			, //4049	0	0	0	아누바바 효과가 해제 되었습니다.	Anubaba effect has been disabled.
	eMsgAtmanEffectDisabled				, //4050	0	0	0	아트만 효과가 해제 되었습니다.	Atman effect has been disabled.
	eMsgAllChakraUpgradeDisabled		, //4051	0	0	0	모든 차크라 상승효과가 해제 되었습니다.	All chakra upgrade effect has been disabled.
	eMsgInventoryExpansionEnabled		, //4052	0	0	0	인벤토리 확장 기능이 적용 되었습니다.	Inventory expansion has been enabled.
	eMsgPrivateStoreExpansionEnabled	, //4053	0	0	0	개인상점 확장 기능이 적용 되었습니다.	Private store expansion has been enabled.
	eMsgAutomaticRupiaEnabled			, //4054	0	0	0	루피아 자동 습득 기능이 적용 되었습니다.	Automatic rupia acquisition has been enabled.
	eMsgAnubabaEffectEnabled			, //4055	0	0	0	아누바바 효과가 적용 되었습니다.	Anubaba effect has been enabled.
	eMsgAtmanEffectEnabled				, //4056	0	0	0	아트만 효과가 적용 되었습니다.	Atman effect has been enabled.
	eMsgAllChakraUpgradeEnabled			, //4057	0	0	0	모든 차크라 상승효과가 적용 되었습니다.	All chakra upgrade effect has been enabled.
	eMsgPremiumServiceName				, //4058	0	0	0	프리미엄 서비스명	Premium Service Name
	eMsgWordInUse						, //4059	0	0	0	사용여부	In Use?
	eMsgWordExpireDate					, //4060	0	0	0	만료기간	Expire Date
	eMsgWordDDay						, //4061	0	0	0	D-day	D-Day
	eMsgWordEffect						, //4062	0	0	0	효과	Effect
	eMsgWordInvenExpansion				, //4063	0	0	0	인벤토리 확장	Inventory Expansion
	eMsgWordPrivateStoreExpansion		, //4064	0	0	0	개인상점 확장	Private Store Expansion
	eMsgAutomaticRupiaAcquisition		, //4065	0	0	0	루피아 자동습득	Automatic Rupia Acquisition
	eMsgWordAnubabaCharm				, //4066	0	0	0	아누바바 부적	Anubaba Charm
	eMsgWordAtmanCharm					, //4067	0	0	0	아트만 부적	Atman Charm
	eMsgAllChakraPlus15					, //4068	0	0	0	모든 차크라 15 증가	All Chakra +15
	eMsgNotPurchased					, //4069	0	0	0	미구입	Not Purchased
	eMsgWordInUseing					, //4070	0	0	0	사용중	In Use
	eMsgWordExpired						, //4071	0	0	0	기간만료	Expired
	eMsgWordTotal						, //4072	0	0	0	합 계	Total
	eMsgExplanPremiumItem01				, //4073	0	0	0	사용전의 유효시간을 갖고 있는 아이템만 판매할 수 있습니다.	You can only sell items that have not been used and not expired
	eMsgExplanPremiumItem02				, //4074	0	0	0	최소 한묶음(250개) 단위로만 판매할 수 있습니다	You can only sell in packs of 250.
	eMsgExPlanPremiumItem03				, //4075	0	0	0	\n구매결과: 소지 %d 소비 %d\n	\nSales Result: Own %d Sold %d\n
	eMsgExPlanPremiumItem04				, //4076	0	0	0	캐릭터 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다.	Usable items for upgrading the character. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem05				, //4077	0	0	0	편의성 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다.	Usable items for upgrading the convenience. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem06				, //4078	0	0	0	기능성 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다.	Usable items for upgrading the functionality. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem07				, //4079	0	0	0	프리미엄 꾸러미 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다.	Premium package items. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem08				, //4080	0	0	0	특수 기능을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다.	Usable items for special features. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem09				, //4081	0	0	0	%s \n최소 %d개 구입(%d개 구입 시 20％할인)	%s \nPurchase minimum of %d (20% discount when purchasing %d or more)
	eMsgPriceToTaney					, //4082	0	0	0	가격: %s 타니	Price: %s Taney
	eMsgPage							, //4083	0	0	0	(Page %d/%d)	(Page %d/%d)
	eMsgExPlanPremiumItem10				, //4084	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem11				, //4085	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아트만 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem12				, //4086	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem13				, //4087	0	0	0	고급 생명의 주문서 1개\n생명의 주문서 20개\n전광판 아이템 10개\n작전 명령서 5개\n이벤트기간에 사용시 이벤트 아이템 지급\n\n30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과\n4. 모든 차크라 15 상승	1 high quality revival scroll\n20 revival scroll\n10 electronic board item\n5 strategy command\nEvent item when used during event period\nFollowing effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms\n4. All chakra +15
	eMsgExPlanPremiumItem14				, //4088	0	0	0	요술램프 1개\n(파미르지역에서 보스몬스터 랜덤 소환가능)\n요술망치 2개\n(장비중인 모든아이템 내구도수리)\n차투랑가 입장권 2개\n(차투랑가로 바로 입장가능)\n이벤트 우타라 암리타 	1 magic lamp\n(Can summon random boss monster in Pamir area)\n2 magic hammer\n(Repair all equipped items)\n2 Chaturanga entrance ticket\n(Can enter Chaturanga)\n2 packs of event Utara Amrita\2 high quality revival scroll
	eMsgSkillInitialized				, //4089	0	0	0	스킬이 초기화 되었습니다.	Skill has been initialized.
	eMsgChakraInitialized				, //4090	0	0	0	차크라가 초기화 되었습니다.	Chakra has been initialized.
	eMsgSkillChakraInitialized			, //4091	0	0	0	스킬 및 차크라가 초기화 되었습니다.	Skill and Chakra has been initialized.
	eMsgChakraCannotUpgrade				, //4092	0	0	0	차크라 제한에 걸려 차크라를 올릴 수 없습니다.	Chakra can't be upgraded due to maximum limit.
	eMsgSerialNumber					, //4093	0	0	0	일련 번호	Serial Number
	eMsgEnlistmentNotice				, //4094	0	0	0	[입영 통지서]의 	of [Enlistment Notice]
	eMsgMustHaveGodToView				, //4095	0	0	0	주신이 있어야만 열람하실 수 있습니다.	You must have a God to view this.
	eMsgExPlanPremiumItem15				, //4096	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem16				, //4097	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아트만 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem17				, //4098	0	0	0	30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem18				, //4099	0	0	0	고급 생명의 주문서 1개\n생명의 주문서 20개\n전광판 아이템 10개\n작전 명령서 5개\n이벤트기간에 사용시 이벤트 아이템 지급\n\n30일간 다음의 효과발생\n1. 인벤토리 및 개인상점 공간 확장\n2. 루피아 자동 습득\n3. 아누바바 및 아트만 부적의 효과\n4. 모든 차크라 15 상승	1 high quality revival scroll\n20 revival scroll\n10 electronic board item\n5 strategy command\nEvent item when used during event period\nFollowing effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms\n4. All chakra +15
	eMsgExPlanPremiumItem19				, //4100	0	0	0	요술램프 1개\n(파미르지역에서 보스몬스터 랜덤 소환가능)\n요술망치 2개\n(장비중인 모든아이템 내구도수리)\n차투랑가 입장권 2개\n(차투랑가로 바로 입장가능)\n이벤트 우타라 암리타 250개 2묶음\n고급 생명의 주문서 2개	1 magic lamp\n(Can summon random boss monster in Pamir area)\n2 magic hammer\n(Repair all equipped items)\n2 Chaturanga entrance ticket\n(Can enter Chaturanga)\n2 packs of event Utara Amrita\2 high quality revival scroll
	eMsgExPlanPremiumItem20				, //4101	0	0	0	"6만 5천 컬러 LCD / 듀얼 이어폰 '아이원잇 TMP-1000'>>http://www.ioneit.com"
	eMsgExPlanPremiumItem21				, //4102	0	0	0	본 아이템은 이동할 수 없습니다. 이벤트 NPC를 통해 적립하세요.
	eMsgExPlanPremiumItem22				, //4103	0	0	0	%s \n최소 %d개 구입(%d개 구입 시 10％할인)	%s \nPurchase minimum of %d (10% discount when purchasing %d or more)
	eMsgReqUsingItem					, //4104	정말 아이템을 사용하시겠습니까?
	eMsgExPlanPremiumItem23				, //4105	0	0	0	8칸의 인벤토리 공간 필요
	eMsgReQuestItemUse1					, //4106	퀘스트를 초기화 하시겠습니까?(퀘스트 다시하기1개, 망각의 샘1개 필요)
	eMsgReQuestItemUse2					, //4107	퀘스트를 초기화 하시겠습니까?(퀘스트 다시하기1개, 망각의 샘2개 필요)


	eMsgTaskQuestMaraBloodSellOK	= 5001, // 마라의 혈액류를판매했습니다.
	eMsgTaskQuestMaraSolutionMakingOK	, // 마라의 원액을 제조했습니다.
	eMsgTaskQuestPanacaMakingOK			, // 파나카류를 제조했습니다.
	eMsgTaskQuestChaturangaPieceOK		, // 카야를 합성했습니다.
	eMsgTaskQuestWeaponMakingOK			, // 무기를 제작했습니다.
	eMsgTaskQuestItemMakingOK			, // 물품을 제작했습니다.
	eMsgTaskQuestItemSeparationOK		, // 물품을 분리했습니다. // 5007
	eMsgTaskQuestNullEventOK			, // 축하합니다. 이벤트에 당첨 되었습니다. (이벤트에 참여하셨습니다.)
	eMsgTaskQuestMerryXMas				, // 메리 크리스마스!!!
	eMsgTaskQuestEventBoxOnenOK			, // 아이템을 사용했습니다.
	eMsgTaskQuestCannotFindInfo		= 5951	, // 퀘스트 정보를 찾을 수 없습니다.
	eMsgTaskQuestNPCIDErr				, // 선택한 NPC가 수행할 수 없는 퀘스트입니다.
	eMsgTaskQuestNeedItemErr			, // 필요한 아이템이 없습니다
	eMsgTaskQuestNeedMoneyErr			, // 필요한 루피아가 부족합니다.
	eMsgTaskQuestConditionErr			, // 테스크 퀘스트를 하기 위한 조건 불충분
	eMsgTaskQuestFail					, // 테스크 실패 
	eMsgTaskQuestRateErr				, // 확률에 의해 작업이 실패했습니다. // 5957
	eMsgTaskQuestNoEventErr				,  // 죄송합니다. 아직 이곳에서는 이벤트를 하지 않습니다.
	eMsgTaskQuestKarmaErr				,	// 카르마 수치가 조건에 맞지 않습니다. 
	eMsgTaskQuestLevelErr				,	// 수행에 필요한 레벨이 부족합니다.
	
	eMsgRefineErr1					= 6000,	// 기존에 제련되어 있던 속성은 사라집니다. 제련하시겠습니까?
	eMsgRefineErr2						,	// 제련을 위해 비카리 제련재료를 사용하실 필요가 없습니다.

	eMsgItemBuyMsg1					= 6002,	//0	0	0	%s %s 개를 %s 루피아에 구입 하시겠습니까?
	eMsgItemBuyMsg2						,	//0	0	0	%s %s 개를 %s 캐쉬에 구입 하시겠습니까?
	eMsgItemSellMsg1					,	//0	0	0	%s %s 개를 %s 루피아에 판매 하시겠습니까?
	eMsgItemSellMsg2						//0	0	0	%s %s 개를 %s 캐쉬에 판매 하시겠습니까?

} eMsgInfo;

#endif