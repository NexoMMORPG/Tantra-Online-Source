#ifndef _HTMessageDef_h_
#define _HTMessageDef_h_

//--------------------------------------------------------------
// Parameter
//--------------------------------------------------------------
#define HT_MSG_PARAM_NONE					0
//--------------------------------------------------------------
// Character
//--------------------------------------------------------------
// ��ų
//#define HT_MSG_SKILL_CANNOT_FIND_INFO				1081 // ��ų ������ ã�� �� ����
//
//#define HT_MSG_SKILL_USE_PASSIVE_ERR				1084 // �нú� ��ų�� ���������� �̵��Ұ�
//#define HT_MSG_SKILL_USE_LEVEL_ERR					1085 // ���� 0�� ��ų�� ���������� �̵��Ұ�
//
//#define HT_MSG_SKILL_UP_LIMIT_LEVEL					1086 // �� �̻� ������ �ø� �� ����
//#define HT_MSG_SKILL_UP_OK							1088 // ��ų ���� �� ����
//#define HT_MSG_SKILL_UP_CANNOT_LEARN				1089 // ��Ÿ ���ѿ� ���� ��ų�� ��� �� ����
//#define HT_MSG_SKILL_UP_FAIL						1090 // ��ų ������ ����

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
	eMsgNone						=	0,	// �޼��� ����

	eMsgCommonNone					=	1,	// ����
	// �ֽ�
	eMsgCommonTrimuritiBrahma		=	2,
	eMsgCommonTrimuritiVishunu			,
	eMsgCommonTrimuritiSiva			=	4,
	// ��ũ��
	eMsgCommonChakraMuscle			=	6, // ����
	eMsgCommonChakraHeart				, // ����
	eMsgCommonChakraNerve				, // �Ű�
	eMsgCommonChakraMind				, // ���� // 9
	// ī��Ʈ
	eMsgCommonCastSudra				=	11,
	eMsgCommonCastVaisha				,
	eMsgCommonCastKshatrya				,
	eMsgCommonCastBraman				,
	eMsgCommonCastAvatara				,
	eMsgCommonCastReserve				, // 16
	// ����
	eMsgCommonTribeNaga				=	21,		
	eMsgCommonTribeAsura				,
	eMsgCommonTribeYaksha				,
	eMsgCommonTribeDeva					,
	eMsgCommonTribeKimnara				,
	eMsgCommonTribeRakshasa				,
	eMsgCommonTribeGandharva			,
	eMsgCommonTribeGaruda				,
	eMsgCommonTribeGM					, // GM
	eMsgCommonTribeAdministrator		, // ��� // 30
	// ����
	eMsgCommonJobBasic				=	31,
	// 1�� ����
	eMsgCommonJobSatvan					, // ��Ʈ��
	eMsgCommonJobDhvanta				, // ���Ÿ
	eMsgCommonJobNirvana				, // �ʹٳ�
	eMsgCommonJobMantrika				, // ��Ʈ��ī
	// 2�� ����
	eMsgCommonJobSatvan1				, // ����Ŀ
	eMsgCommonJobSatvan2				, // ��Ŀ
	eMsgCommonJobDhvanta1				, // ����
	eMsgCommonJobDhvanta2				, // ������
	eMsgCommonJobNirvana1				, // �ȶ��
	eMsgCommonJobNirvana2				, // ����
	eMsgCommonJobMantrika1				, // ������
	eMsgCommonJobMantrika2				, // ����� //43
	
	// ä��
	eMsgCommonChatWhole				=	51, // ��ü
	eMsgCommonChatParty					, // ��Ƽ
	//eMsgCommonChatGuild					, // ���
	eMsgCommonChatAshuram				, // �ƽ���
	eMsgCommonChatWhisperReceive		, // %s�� �Ӹ�
	eMsgCommonChatWhisperSend			, // %s���� �Ӹ� // 55
	eMsgCommonChatWhisperNotSend		, // �ӼӸ��� ���� �� �������ϴ�. ������ �¶��� ���°� �ƴϰų� ���� �̸��� ����Ͽ����ϴ�.
	eMsgCommonChatNotice				, // [����]
	eMsgCommonChatAshuramAlliance		, // �ƽ�������

	// Command
	eMsgCommonCommandAS				=	61, // ����
	eMsgCommonCommandGuildWindow		, // ���â
	eMsgCommonCommandGuildMark			, // ��帶ũ
	eMsgCommonCommandTrimuritiMark		, // �ֽŸ�ũ
	eMsgCommonCommandInvisible			, // ����
	eMsgCommonCommandWarp				, // ����
	eMsgCommonCommandMove				, // �̵�
	eMsgCommonCommandNotice				, // ����
	eMsgCommonCommandWholeNotice		, // ��ü����
	eMsgCommonCommandAshuramNotice		, // ��������-�ƽ�������
	eMsgCommonCommandAssistant			, // ����
	eMsgCommonCommandShout				, // ��ġ��
	eMsgCommonCommandShoutPart			, // ��
	eMsgCommonCommandParty				, // ��Ƽ
	eMsgCommonCommandPartyPart			, // ��
	//eMsgCommonCommandGuild				, // ���
	eMsgCommonCommandAshuram			, // �ƽ���
	eMsgCommonCommandAshuramPart		, // ��
	eMsgCommonCommandAshuramGrade		, // �ƽ������
	eMsgCommonCommandTrade				, // ��ȯ
	eMsgCommonCommandEmerge				, // Ż�� 
	eMsgCommonCommandWhisper			, // �ӼӸ�
	eMsgCommonCommandWhisperPart		, // ��
	eMsgCommonCommandWhole				, // ��ü
	eMsgCommonCommandWholePart			, // ��
	eMsgCommonCommandKick				, // ű
	eMsgCommonCommandAddress			, // ģ�����
	eMsgCommonCommandWin				, // ���â //87
	eMsgCommonCommandASCancel			, // �������
	eMsgCommonCommandASCancel2			, // �������
	eMsgCommonCommandAS2				, // ����
		
	eMsgCommonCommandASCheck			, // gmȣ��Ȯ��
	eMsgCommonCommandASCheck2			, // GMȣ��Ȯ��

	eMsgCommonCommandDebugMode			, // Debug Mode
	eMsgCommonCommandBroadcastMode		, // BroadcastMode
	eMsgCommonCommandEngineCamera		, // Use Engine Camera
	eMsgCommonCommandGoCamera			, // Go Camera
	eMsgCommonCommandShowCursor			, // ShowCursor

	eMsgCommonCommandDuel				, // ShowCursor

	// ������ �з�
	eMsgCommonItemClassOneHand		=	101, // �Ѽչ���
	eMsgCommonItemClassTwoHand			, // �μչ���
	eMsgCommonItemClassArmor			, // �Ǻ�
	eMsgCommonItemClassPants			, // ����
	eMsgCommonItemClassGloves			, // �尩
	eMsgCommonItemClassShield			, // ����
	eMsgCommonItemClassBelt				, // �㸮��
	eMsgCommonItemClassShoes			, // �Ź�
	eMsgCommonItemClassHelmet			, // ����
	eMsgCommonItemClassEarring			, // �Ͱ���
	eMsgCommonItemClassNecklace			, // �����
	eMsgCommonItemClassBracelet			, // ����
	eMsgCommonItemClassRing				, // ���� // 113
	// ���� �з�
	eMsgCommonWeponClassSword		=	121, // ��
	eMsgCommonWeponClassAx				, // ����
	eMsgCommonWeponClassLance			, // â
	eMsgCommonWeponClassMace			, // �б�
	eMsgCommonWeponClassGlove			, // ��������
	eMsgCommonWeponClassMagic			, // ��������
	eMsgCommonWeponClassBow				, // Ȱ
	eMsgCommonWeponClassDagger			, // �ܰ� // 128
	// ��ų �з�
	eMsgCommonSkillClassPassive		=	131, // �нú�
	eMsgCommonSkillClassAction			, // �׼�
	eMsgCommonSkillClassActive			, // ��Ƽ��
	eMsgCommonSkillAttack				, // ����
	eMsgCommonSkillDefence				, // ���
	eMsgCommonSkillAssistance			, // ����
	eMsgCommonSkillAssassination		, // �ϻ�
	eMsgCommonSkillArchery				, // �ü�
	eMsgCommonSkillPhysics				, // ����
	eMsgCommonSkillBlaze				, // ȭ��
	eMsgCommonSkillCold					, // �ñ�
	eMsgCommonSkillLightning			, // ����
	eMsgCommonSkillMagic				, // ����
	eMsgCommonSkillPoison				, // �� // 144
	eMsgCommonSkillGod					, // �ֽ� // 145

	// ���
	eMsgCommonGuildMahaRaja			=	151, // ���϶���
	eMsgCommonGuildRaja					, // ����
	eMsgCommonGuildPrubaja				, // �������
	eMsgCommonGuildDandeca				, // �ܵ�ī
	eMsgCommonGuildTapasa				, // Ÿ�Ļ�
	eMsgCommonGuildMember				, // ���� ����

	// �ý���â
	eMsgCommonSystemNotice			=	161, // [����]
	eMsgCommonSystemParty				, // [��Ƽ]
	eMsgCommonSystemHistory				, // [�����丮�׽�Ʈ]
	eMsgCommonSystemWhisper				, // [�ӼӸ�]
	eMsgCommonSystemAshuram				, // [�ƽ���] // 165
	eMsgCommonSystemFile_Err		=	181, // ������ �������� �ʰų� ������ �߸��ƽ��ϴ�.
	eMsgCommonSystemExeErr				, // Ŭ���̾�Ʈ �ٿ�. crash���� ���� ��Ź.
	eMsgCommonSystemNotAble				, // ���� �������� �ʴ� ���
	eMsgCommonSystemCannot				, // �ֽ������������� ��Ƽ, ��ŷ�, �����, �ּҷ� ����� �ȵ˴ϴ� //184
	eMsgGMCallTreat						, // ������ ����Ͻ� GMȣ�� ������ ���� ó������ �ʾҽ��ϴ�.(185)
	eMsgGMCallRegist					, // GMȣ�� ������ %d��°�� ��ϵǾ����ϴ�.
	eMsgGMCallReRegist					, // GMȣ�� ������ ��ϵ��� �ʾҽ��ϴ�. �ٽ� ����� �ֽñ� �ٶ��ϴ�.
	eMsgHaveNoGMCall					, // ��ϵ� ��û�� �����ϴ�.
	eMsgDeleteGMCall					, // ��ϵ� ��û�� �����Ǿ����ϴ�.
	eMsgReDeleteGMCall					, // ��ϵ� ��û ������ �̷������ �ʾҽ��ϴ�. �ٽ� ��û�� �ֽñ� �ٶ��ϴ�.
	eMsgGMCallNum						, // GMȣ�� ������ ����ȣ�� %d�Դϴ�.
	eMsgLastDamageNotice				, // ������ ������ ǥ��
	eMsgMessageisoutoflimit				, // �ִ� ���� ���̸� �ʰ��Ͽ����ϴ�.
	eMsgReStartRemindTime				, // ���� ����Ÿ�� �������Դϴ�. %d�� ���ҽ��ϴ�.
	eMsgGameExit						, // ������ �����մϴ�. ��ø� ��ٷ� �ֽʽÿ���
	
	// ȣĪ
	eMsgCommonSpecialName1			=	201, //����
	eMsgCommonSpecialName2				, // ���� // 202
	// ����
	eMsgCommonZoneMandara			=	221, // ���ٶ�
	eMsgCommonZoneMandara_1				,
	eMsgCommonZoneMandara_2				,
	eMsgCommonZoneMandara_3				,
	eMsgCommonZoneMandaraDungeon		, // ���ٶ� ����
	eMsgCommonZoneShambalaDungeon		, // ���߶� ����
	eMsgCommonZoneJina					, // ����
	eMsgCommonZoneTrimuriti				, // �ֽ��� // 228
	eMsgCommonZoneChatulangga			, // í������
	eMsgCommonZoneForBillPotal_1		, // ����ȭ ��Ż 1 (���ٶ�����)
	eMsgCommonZoneForBillPotal_2		, // ����ȭ ��Ż 2 (���߶�����)
	eMsgCommonZoneForBillPotal_3		, // ����ȭ ��Ż 3 (��������)
	eMsgCommonZoneForBillPotal_4		, // ����ȭ ��Ż 4 (�Ĺ̸����)
	eMsgCommonZoneForBillPotal_5		, // ����ȭ ��Ż 5 (������)
	eMsgCommonZoneForBillPotal_6		, // ����ȭ ��Ż 6 (ũ�縶)
	eMsgCommonZoneBookDooTomb			, // �ϵμ�����
	eMsgCommonZoneArenaDurga			, // �����
	eMsgCommonZoneBiryuCastle			, // �����
	eMsgCommonZoneAnakaKruma			, // �Ƴ�ī��縶

	//	��������Ʈ
	eMsgCommonServerName1			=	251, // ������
	eMsgCommonServerName2				, // ��߳�
	eMsgCommonServerName3				, // ũ����
	eMsgCommonServerName4				, // ��Ʈ��
	eMsgCommonServerName5				, // �Ƴ���
	eMsgCommonServerName6				, // �ھƳ�
	eMsgCommonServerName7				, // �ٶ�
	eMsgCommonServerName8				,  // �縶�� // 258
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


	// �ý���â2
	eMsgCommonSystemInvalidData			=	330, // �������� ����Ÿ�Դϴ�.
	eMsgCommonSystemNoRight				, // ��ũ ���� ������ �����ϴ�.
	eMsgCommonServerMoreRupia			, // ���Ǿư� �����մϴ�.
	eMsgCommonServerMoreTani			, // Ÿ�ϰ� �����մϴ�.
	eMsgCommonServerFaild				, // ��ũ ���濡 ���� �߽��ϴ�.
	eMsgCommonDuelRequest				, // %s���� ������ ��û�߽��ϴ�. ������ ���Ͻðڽ��ϱ�? 1�� ���� �ź����� ������ ������ �³��˴ϴ�.
	eMsgCommonDuelDenay					, // %s���� ���� ��û�� �����߽��ϴ�.
	eMsgCommonDuelNorReqEmpty			, // %s���� �ڸ���� �����Դϴ�. �ڸ��� ��� �÷��̾�Դ� ������û�� �� �� �����ϴ�.
	eMsgCommonDuelAutoOK				, // %s�Կ��� ������ ��û�߽��ϴ�. 1�� �Ŀ� �ڵ����� ���� ���°� �˴ϴ�. ���� ��û�� ����Ͻðڽ��ϱ�?
	eMsgCommonDuelCancel				, // ���� ���°� ��ҵǾ����ϴ�.
	eMsgCommonDuelMoreRhupia			, // �κ��丮�� ���Ǿư� �����մϴ�. ������ ��û�Ϸ��� 10000���Ǿư� �Ҹ�˴ϴ�.
	eMsgCommonGuildConnect				, // %s���� �����Ͽ����ϴ�.
	eMsgCommonGuildExit					, // %s���� ������ �����Ͽ����ϴ�.
	eMsgCommonAshuramGuildMsg1			, // %s�Բ� �ƽ��� ������ ��û�մϴ�.
	eMsgCommonAshuramGuildMsg2			, // %s���� ����� ��ٸ��� �ֽ��ϴ�.
	eMsgCommonAshuramGuildMsg3			, // %s���� �ƽ��� ������ ��û�߽��ϴ�.
	eMsgCommonAshuramGuildMsg4			, // %s���� �ƽ��� ������ �ź��߽��ϴ�.
	eMsgCommonAshuramGuildMsg5			, // �ƽ��� ���� ��û�� ���϶��ڸ��� �����մϴ�.
	eMsgCommonAshuramGuildMsg6			, // �ƽ��� ���� Ż��� ���϶��ڸ��� �����մϴ�.
	eMsgCommonAshuramGuildMsg7			, // �ƽ��� ������ ���� ��븦 ���� �ϼ���
	eMsgCommonAshuramGuildMsg8			, // �ƽ��� ���� ������ ��ü �Ǿ����ϴ�.
	eMsgCommonAshuramGuildMsg9			, // �ƽ��� ���� ���谡 ���� �Ǿ����ϴ�.
	eMsgCommonAshuramGuildMsg10			, // �ƽ��� ������ ���� �ƽ����� �����ϴ�.
	eMsgCommonAshuramGuildMsg11			, // �̹� �ƽ��� ������ ���� �����Դϴ�.
	eMsgCommonAshuramGuildMsg12			, // ���� �ֽ��� ��븸 ������ �� �ֽ��ϴ�.
	eMsgCommonNotHaveFotress			, // ����� �ƽ����� ����� ȹ������ �ʰ� �ֽ��ϴ�.
	eMsgCommonNoGameTime				, // ����� ������ �Ⱓ�� ����Ǿ����ϴ�.
	eMsgCommonAshuramGuildMsg13			, // �ƽ��������� ��ü�� �� �ٽ� �õ��� �ֽʽÿ�.
	eMsgCommonAshuramGuildMsg14			, // ���� ��簡 : [%s]>>�ƺ� ��簡 : [%s]>>�ܹ� ��簡 : [%s]>>���� ��簡 : [%s]
	eMsgCommonAshuramGuildMsg15			, // ���϶��ڸ��� ����� �� �ֽ��ϴ�.
	eMsgCommonAshuramGuildMsg16			, // ���϶��� �Ǵ� ���ڸ��� ȹ���� �� �ֽ��ϴ�.
	eMsgCommonSkillZubasSkill			, // ��ٽ� ��ų�� �����Ÿ� �ۿ����� ��� �� �� �����ϴ�.
	eMsgCommonNoChatMode				, // ����� ä�� ���� �����Դϴ�.
	eMsgCommonDurga0					, // ���� ��簡
	eMsgCommonDurga1					, // �ƺ� ��簡
	eMsgCommonDurga2					, // �ܹ� ��簡
	eMsgCommonDurga3					, // ���� ��簡
	eMsgCommonNoLoginChar				, // �� ĳ���� ���� �����Դϴ�.
	eMsgCommonAshuramGuildMsg17			, // ����� ������ �ƽ��������� ������ ���� �� �����ϴ�.
	eMsgCommonCannotGodChange			, // �ֽ����� ���������� �ٽ� �õ��� �ֽʽÿ�.
	eMsgCommonAnswerUseSamudaba			, // %s�� (%d %% ����ġ ȸ��) �繫�ٹ� ��ų�� ����߽��ϴ�. ��Ȱ �Ͻðڽ��ϱ�?
	eMsgCommonAnswerUseSamudabaErr1		, // �����ڰ� �Ÿ��ۿ� �־� ��Ȱ���� ���߽��ϴ�.
	eMsgCommonAnswerUseSamudabaErr2		, // �ð��ʰ��� ���� ��Ȱ���� ���߽��ϴ�.
	eMsgCommonNotMoveTredeItem			, // �� �������� ���� �����ų� �ŷ��� �� �����ϴ�.
	eMsgCommonNotUseInDuel				, // �������϶��� ����Ҽ� �����ϴ�.
	eMsgCommonNotRegistInQuickSlot		, // �����Կ� ��ϺҰ����� �������Դϴ�
	eMsgCommonPleaseInputAshramName		, // �ƽ��� �̸��� �Է��� �ֽʽÿ�
	eMsgCommonPleaseInputOpenMessage	, // ������ ������ �Է��� �ֽʽÿ�
	eMsgCommonPleaseInputCombatMessage	, // ������ɼ� ������ �Է��� �ֽʽÿ�
	eMsgCommonOurPlanJanuary			, // 1���� ���� �����Դϴ�.
	eMsgCommonExcessLoginTime			, // �α��� �ð��� �ʰ��Ͽ� ������ �����մϴ�.


	eMsgCommonCommandAshuramGuildJoin	=	400,	// /�ƽ�������
	eMsgCommonCommandAshuramGuildLeave	,			// /�ƽ�������Ż��
	eMsgCommonCommandAshuramAlliance1	,			//	��
	eMsgCommonCommandAshuramAlliance2	,			//	����
	eMsgCommonCommandAshuramJoinBrackets ,			//	[�ƽ�������]
	eMsgCommonCommandAshuramJoin		,			//	�ƽ�������
	eMsgCommonCommandUnionAshuram		,			//	���վƽ���
	eMsgCommonReFresh					,			//	���ΰ�ħ
	eMsgCommonScore						,			//	��
	eMsgCommonRegist					,			//	���
	eMsgCommonDelete					,			//	����
	eMsgCommonConfirm					,			//	Ȯ��
	eMsgCommonCancel					,			//	���
	eMsgCommonRupia						,			//	���Ǿ�
	eMsgCommonEachOther					,			//	����
	eMsgCommonMySelf					,			//	����
	eMsgCommonJoin						,			//	����
	eMsgCommonSecede					,			//	Ż��
	eMsgCommonChangeStyle				,			//	��纯��
	eMsgCommonPartyMaster				,			//	��Ƽ��
	eMsgCommonRefiningTitle				,			//	��      ��
	eMsgCommonRefiningTargetItem		,			//	���� ��� ������
	eMsgCommonRefiningItem				,			//	���� ���
	eMsgCommonInputYouWantItem			,			//	���ϴ� ������ �Է��ϼ���
	eMsgCommonInputYouWantRuphia		,			//	���ϴ� ���ǾƸ� �Է��ϼ���
	eMsgCommonUntilAshramCargo			,			//	%d.%d.%d(Reserved)
	eMsgCommonCommandAshuramAlliance3	,			//	�ƽ���
	eMsgCommonCommandWhisper2			,			//	�ӼӸ�
	eMsgCommonDuelLimitPerson			,			//	�����ο��� 3�оȿ� �ѹ� �̻� ������ ��û�Ҽ� �����ϴ�.
	eMsgCommonChatRoom					,			//	/ä�ù�

	eMsgIntroID							=	450,	//	���̵�
	eMsgIntroPassWord					,			//	��й�ȣ
	eMsgIntroSelectServer				,			//	��������
	eMsgIntroChakra						,			//	��ũ��
	eMsgIntroMuscleChakra				,			//	��������ũ��
	eMsgIntroNerveChakra				,			//	�Ű�����ũ��
	eMsgIntroheartChakra				,			//	��������ũ��
	eMsgIntroSoulChakra					,			//	��������ũ��
	eMsgIntroSavePos					,			//	������ġ
	eMsgIntroLeft						,			//	Left
	eMsgIntroRight						,			//	Right
	eMsgIntroCreateNewChar				,			//	��ĳ���͸����
	eMsgIntroExplainTribe				,			//	��������
	eMsgIntroInputName					,			//	�̸��Է�
	eMsgIntroServicePoint				,			//	���� ����Ʈ
	eMsgIntroDeleteChar					,			//	ĳ���ͻ���
	eMsgIntroExplain					,			//	�� ��
	eMsgIntroResidentNumber				,			//	�ֹε�Ϲ�ȣ
	eMsgIntroExplain01					,			//	������ ���Ͻø� �ֹε�Ϲ�ȣ�� �Է��Ͻð� Ȯ���� �����ּ���
	eMsgIntroTopMenu01					,			//	Create Character
	eMsgIntroTopMenu02					,			//	Select Character
	eMsgIntroTopMenu03					,			//	Exit Game
	eMsgIntroExplain002					,			//	���� ���� ������ �߿� �ְ��� ���ݷ°� �پ �������� ���ϰ� �ִ�.\n ��, �ӵ��� ������ �������� ��������.
	eMsgIntroExplain003					,			//	�Ƽ��� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
	eMsgIntroExplain004					,			//	��ũ�� ���� ���� ������ ��Ȯ�� ��ġ�� ������. ���ݷ��� ������ ������ �ʿ����� ������ �������� �׵��� ���� �����ϰ� �����.
	eMsgIntroExplain005					,			//	�������� �������� �ɷ¿����� � �������� �������� �������� �鿡���� �� � �������� ���ϴ�.
	eMsgIntroExplain006					,			//	Ų���� ���� ������ �߿� �ְ��� ���ݷ°� �پ �������� ���ϰ� �ִ�.\n ��, �ӵ��� ������ �������� ��������.
	eMsgIntroExplain007					,			//	��ũ���� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
	eMsgIntroExplain008					,			//	���ٸ��� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
	eMsgIntroExplain009					,			//	����� ���� �������� �������� ���� ������ �����µ� ����� ����, �׷��� �������� ���� ���� ������ ���� �ߵ����� ���Ѵ�.
	eMsgIntorSmooth						,			//	��Ȱ
	eMsgIntorTrimuriti					,			//	�ֽ�
	eMsgIntorLimitAge					,			//	źƮ��� ��15�� �̻� ������ �̿��ϽǼ� �ֽ��ϴ�.
	eMsgIntroIDsave						,			//	ID�����ϱ�
	eMsgFace							,			//	��
	eMsgHead										//	�Ӹ�

} eMsgCommon;

//--------------------------------------------------------------
// Character
//--------------------------------------------------------------
typedef enum _eMsgCharacter
{
	// ���� ����
	eMsgLogInRegularCheck			=	1001, // ������������ ���Ͽ� �α��� �� �� �����ϴ�.
	eMsgLogInIrregularCheck				, // �ӽ��������� ���Ͽ� �α��� �� �� �����ϴ�.
	eMsgLogInServerUpdate				, // ���� ������Ʈ�� ���Ͽ� �α��� �� �� �����ϴ�.
	eMsgLogInEtc						, // ����� �α��� �� �� �����ϴ�. ����� �̿��� �ֽñ� �ٶ��ϴ�
	eMsgLogInLogInWebErr				, // ���ͳ� ��Ȳ�� Ȯ���Ͻ� �� �ٽ� �̿��� �ֽñ� �ٶ��ϴ�.
	eMsgLogInInputID					, // ID�� ��й�ȣ�� �Է����ּ���.
	eMsgLogInReqInitialize				, // ������ �ʱ�ȭ ������ ��û�߽��ϴ�. ��ø� ��ٷ� �ֽʽÿ�.
	eMsgLogInReqInitializeAgain			, // ������ �ʱ�ȭ ������ �ٽ� ��û�ϰ� ������ ��ٸ��� ���Դϴ�.
	eMsgLogInAutoGameEnd				, // �ʱ�ȭ ���� ���޾Ƽ� %d�� �� ���� �ڵ� ����
	eMsgLogInConnectionFull				, // �����ڰ� ���Ƽ� ������ �� �����ϴ�. ����� �ٽ� ������ �ֽʽÿ�. // 1010
	// �α���
	eMsgLogInReqWeb					=	1011, // ���� �α��� ��û
	eMsgLogInReqGameServer				, // ���� ������ ���� ��û(1012)
	eMsgLogInReqCharacterList			, // ĳ���� ����Ʈ ��û(1013)
	eMsgLogInReqZoneServer				, // ������ ���� ��û(1014)
	eMsgLogInDisconnectServer			, // �������� ������ ���������ϴ�.(1015)
	eMsgLogInInvalidUser				, // ���� ����(1016)
	eMsgLogInPasswdMismatch				, // ��й�ȣ�� Ʋ��(1017)
	eMsgLogInNoResponse					, // �����κ��� ������ ����(1018)
	eMsgLogInBlockID					, // ���� �������� ���� �Ұ���(1019)
	eMsgLogInAlreadyLogIn				, // �̹� �α��� �Ǿ��ֽ��ϴ�.(1020)
	eMsgLogInNeed						, // �α��� ���� �ʾҽ��ϴ�.(1021)
	eMsgLogInOverMember					, // ���� ���� �ο� �ʰ�(1022)
	eMsgLogInHomepageWithdraw			, // Ȩ���������� �� ������ Ż�� �ϼ̽��ϴ�.(1023)
	eMsgLogInNeedExtraInfo				, // źƮ�� Ȩ���������� �߰������� �Է��� �ּ���.(1024)
	eMsgLogInNeedParentAgree			, // 14�� �̸����� �θ�� ���Ǽ��� �ʿ��� �����Դϴ�.(1025)

	//eMsgLogInFail					=	1025, // �α��� �� �� �����ϴ�.

	// �α׾ƿ�
	eMsgLogOutUnloading				=	1026, // �α׾ƿ��ϴ� ��
	eMsgLogOutSameIDLogIn				, // ���� ������ �α��ο� ���� �����
	eMsgLogOutFail					=	1030 ,// �α׾ƿ����� ���߽��ϴ�.
	// ĳ���� ����
	eMsgCharacListReqCreate			=	1031, // ĳ���� ���� ��û
	eMsgCharacListNotExist				, // ������ ĳ���Ͱ� �ϳ��� �����ϴ�.
	eMsgCharacListCannotCreate			, // ĳ���͸� ��� �����߽��ϴ�.
	eMsgCharacListNameLengthErr			, // �̸� ���� ������
	eMsgCharacListInvalidName			, // �ܾ� ������
	eMsgCharacListChakraPointErr		, // ���� ��ũ�� ����Ʈ ����
	eMsgCharacListAlreadyExist			, // �̹� �����ϴ� ĳ���� �̸�
	eMsgCharacListBasicChakraOver		, // �⺻ ��ũ�� ����
	eMsgCharacListCreateFail		=	1040, // ĳ���� ���� ����
	// ĳ���� ����
	eMsgCharacListReqDelete			=	1041, // ĳ���� ���� ��û
	eMsgCharacListCreateNumErr			, // �ֹε�Ϲ�ȣ ����
	eMsgCharacListDeleteFail		=	1045, // ĳ���� ���� ����
	// �̵�
	eMsgMoveCannotStatus			=	1046, // �̵��� �� ���� ����
	eMsgMoveFail					=	1050, // �̵� ����
	// ����Ʈ
	eMsgQuestTutorialStartQuestion	=	1051, // �ʺ��� ����Ʈ�� �����Ͻðڽ��ϱ�?
	eMsgQuestRejectionConfirm			, // ���� �ʺ��� ����Ʈ�� �ź��Ͻðڽ��ϱ�?

	eMsgQuestInvenLack					, // �κ��丮 ���� ����
	eMsgQuestPranaLack					, // ���� ���� 
	eMsgQuestNotExistItem				, // ����Ʈ ����� �������� ����
	eMsgQuestQuestOnlyItem				, // ����Ʈ ���� �������̶� �Ǹų� �絵 �Ұ�
	eMsgQuestCannotProgress				, // 1057 // ����Ʈ�� ������ �� ����
	// ���Ǿ� �̵�
	eMsgRupiahMoveToNPCInven		=	1061 ,// â��� ���Ǿ� �̵�
	eMsgRupiahMoveToPCInven				, // PC�κ����� ���Ǿ� �̵�
	eMsgRupiahMoveToMap					, // ���� ���Ǿ� ����
	eMsgRupiahReceiveQuest				, // ����Ʈ�� ���� ���Ǿ� zȹ��
	eMsgRupiahReceive					, // ���Ǿ� ȹ��
	eMsgRupiahMoveAmountErr				, // �̵��� �ݾ� ������
	eMsgRupiahSpendingPortal			, // ��Ż�̿����� ���Ǿ� �Һ�
	eMsgRupiahSpendingQuest				, // ����Ʈ�� ���� ���Ǿ� �Һ�
	eMsgRupiahMoveDropQuestion			, // ���� ����߸��ðڽ��ϱ�?
	eMsgRupiahMoveAutoReceive			, // [�ڵ��й�]%s ���Ǿ� ȹ�� // 1070
	eMsgRupiahMoveFail				=	1072, // ���Ǿ� �̵� ����
	// 1:1��ȯ
	eMsgTradeReqSendQuestion		=	1073, // ��ȯ ��û���� Ȯ������
	eMsgTradeReqReceive					, // ��ȯ ��û�� ������
	eMsgTradeReqReceiveRejection		, // ��ȯ ��û ����
	eMsgTradeReqOtherRejection			, // ��û�� ��ȯ ������ 
	eMsgTradeSuccess					, // ��ȯ �Ϸ�
	eMsgTradeCancel						, // ��ȯ ���
	eMsgTradeOtherInvenLack				, // ���� �κ��丮 ���� ����
	eMsgTradeOtherDie					, // ���� ������� ��ȯ ���
	eMsgTradeExchanging					, // ��ȯ �߿� �� �ٸ� ĳ���Ϳ� ��ȯ ���� // 1081
	eMsgTradeFail					=	1085, // ��ȯ ����			
	// ��ų
	eMsgSkillCannotFindInfo			=	1086, // ��ų ������ ã�� �� ����

	eMsgSkillUseItemErr					, // �ʿ��� �������� ������
	eMsgSkillUseSitdownErr				, // ���� ���¿����� ��� ����
	eMsgSkillUsePassiveErr				, // �нú� ��ų�� ���������� �̵��Ұ�
	eMsgSkillUseLevelErr				, // ���� 0�� ��ų�� ���������� �̵��Ұ�
	eMsgSkillUseSaveZoneErr				, // �������������� ��� ���� // 1091

	eMsgSkillUpLimitLevel			=	1096, // �� �̻� ������ �ø� �� ����
	eMsgSkillUpSkillPointErr			, // ��ų ����Ʈ ����
	eMsgSkillUpOK						, // ��ų ���� �� ����
	eMsgSkillUpCannotLearn				, // ��Ÿ ���ѿ� ���� ��ų�� ��� �� ����
	eMsgSkillUpFail					=	1105, // ��ų ������ ����
	// ����/pk
	eMsgAttackReceivePrana			=	1106, // ���� ȹ��
	eMsgAttackReceiveDamage				, // ������ ����
	eMsgAttackSendDamage				, // ������ ��
	eMsgAttackTargetInSafeZone			, // ������ �� ���� ������ ����
	eMsgAttackCannot					, // ������ �� ���� ����
	eMsgAttackCannotPKInZone			, // PK �Ұ� ����					
	eMsgAttackLimitPKLevel				, // PK ���� ����
	eMsgAttackCannotPK					, // PK �Ұ�
	eMsgAttackNotExistTarget			, // ���� ����� ����
	eMsgAttackBlockSuccess				, // �� ����
	eMsgAttackCannotPosition			, // ��ǥ���� ������ �� ���� ��ġ
	eMsgAttackPKWinNotify				, // %s���� %s�Կ��� �¸��Ͽ����ϴ�.
	eMsgAttackPKWarning					, // [���]PK�� �ϸ� �ٸ� �÷��̾�κ��� ���� �ްԵǸ� ����ġ�� �������� �ҰԵ˴ϴ�.
	eMsgAttackTrimuritiZoneWarning		, // [���]�ֽ�����Ʈ�� 0�� ��� ĳ���� ����� ������ 5%�� ����մϴ�.
	eMsgAttackPKModeCancel				, // PK ��� ����
	eMsgAttackEnemyDodge				, // Ÿ���� ���� ����
	eMsgAttackDodgeSuccess				, // ȸ�� ����
	eMsgAttackTakeDamageWithSkill		, // %s���� %s ��ų�� %s �������� �������ϴ�. 
	eMsgAttackDealDamageWithSkill		, // %s�� %s ��ų�� %s �������� �޾ҽ��ϴ�.
	eMsgAttackGetSkillFromOther         , // %s��(��) %s ��ų�� �ɾ��־����ϴ�
	eMsgAttackGiveSkillToOther			, // %s���� %s ��ų�� �ɾ����ϴ�.	
	eMsgAttackGetHarmFromOther			, // %s��(��) %s ��ų�� ����ؼ� �����߽��ϴ�.
	eMsgAttackHarmOtherWithSkill		, // %s���� %s ��ų�� ����ؼ� �����߽��ϴ�.
	eMsgParameterSelf					, // 1129
	eMsgAttackFail					=	1130, // ���� ����
	// ĳ���� ����
	eMsgCharacterRecoveryHP			=	1131, // HP ȸ��
	eMsgCharacterRebirth				, // ������������ �ٽ� �¾
	eMsgCharacterCarmaUp				, // ī���� ����Ʈ�� ���ַ��� �ڽź��� ���� ���͸� ����ؾ� �մϴ�.
	eMsgCharacterDead					, // %s�� ���� ����Ͽ����ϴ�.
	eMsgCharacterContinuousDamage		, // ���� ������ �ް� �ִ�.
	eMsgCharacterChakraInitQuestion		, // ��ũ�� ����Ʈ�� �ʱ�ȭ�Ͻðڽ��ϱ�?
	eMsgCharacterSkillInitQuestion		, // ��ų ����Ʈ�� �ʱ�ȭ�Ͻðڽ��ϱ�? // 1137

	// ��Ƽ
	eMsgPartyCreateOK				=	1201, // ��Ƽ ���� ����
	eMsgPartyCreateNameErr				, // �̹� �����ϴ� ��Ƽ �̸�
	eMsgPartyAutoRootingMode			, // �ڵ� �й���
	eMsgPartyUsualRootingMode			, // �Ϲ� �й���
	eMsgPartyCreateErr				=	1205, // ��Ƽ ���� ����
	eMsgPartyDissolutionQuestion	=	1206, // ��Ƽ ��ü ����
	eMsgPartyDissolutionOK				, // ��Ƽ ��ü ����
	eMsgPartyLeaderNotify				, // %s���� ��Ƽ���Դϴ�
	eMsgPartyJoinReqReceive			=	1211, // ��Ƽ �ʴ� ����
	eMsgPartyJoinReqReceiveRejection	, // ��Ƽ �ʴ� ����
	eMsgPartyJoinReqAgreement			, // ��Ƽ �ʴ� ����
	eMsgPartyJoinAlreadyJoin			, // ��� ĳ���� �ٸ� ��Ƽ�� ����
	eMsgPartyJoinAlreadyParty			, // �ٸ� ��Ƽ�� �����ϰ� �ִ� ��
	eMsgPartyJoinRejection				, // ��� ĳ���Ͱ� ��Ƽ ���� ����
	eMsgPartyJoinAlreadyMember			, // �̹� ���ԵǾ��ִ� ĳ����
	eMsgPartyJoinFail				=	1218, // ��Ƽ ���� ����
	eMsgPartySecessionMemberQuestion=	1219, // ��Ƽ���� �����Ű�ڽ��ϱ�?
	eMsgPartySecessionQuestion			, // ��Ƽ���� Ż���Ͻðڽ��ϱ�?
	eMsgPartySecessionNoMaster			, // ��Ƽ�常 Ż���ų �� ����
	eMsgPartySecessionOKMaster			, // ��Ƽ�忡 ���� Ż��
	eMsgPartySecessionMemberOK			, // ��Ƽ���� Ż������
	eMsgPartySecessionOK				, // Ż�� ����
	eMsgPartySecessionFail				, // Ż�� ���� // 1225
	// ��Ż
	eMsgPortalExtraMandara1			=	1226, // ù��° ���ٶ� ����
	eMsgPortalExtraMandara2				, // �ι�° ���ٶ� ����
	eMsgPortalExtraMandara3				, // ����° ���ٶ� ���� // 1228

	eMsgPortalNeedFee				=	1231, // �̿��
	eMsgPortalSitdownErr				, // ���� ���¿����� ����� �� ����
	eMsgPortalDetailLevelErr			, // ���� ���� - ���� ��� 
	eMsgPortalDetailMoneyErr			, // ���Ǿ� ���� - ���� ���
	eMsgPortalTrimuritiErr				, // �ֽ� ���� �ʿ�
	eMsgPortalMoneyErr					, // ���Ǿ� ����
	eMsgPortalLevelErr					, // ���� ����
	eMsgPortalCannotConnect				, // ���� ������ �� ���� ����
	eMsgPortalTrimuritiZoneWarning		, // �ֽ������� �ٸ� �ֽ��� ĳ���Ϳ��� ���ݹ��� �� �ִٴ� ���
	eMsgProtalExcessMember				, // �������� �ʰ�
	eMsgPortalFail					=	1245, // �̵� ����
	// ä��
	eMsgChatInvalidWord				=	1246, // �������� ���� �ܾ� ����
	eMsgChatSaveStart					, // ��ȭ���� ����
	eMsgChatSaveEnd						, // ��ȭ���� ���� ����
	eMsgChatLogFileCloseErr				, // �α����� �ݱ� ����. ��ȭ���� ��� ����.
	eMsgChatLogFileOpenErr				, // �α����� ���� ����. ��ȭ���� ���� ���� ����.
	eMsgChatDifferentServer				, // �ٸ� ������ ��ġ
	eMsgChatNotLogInCharacter			, // �������� ���� ĳ����
	eMsgChatFail					=	1260, // ���� ����
	// �ּҷ�
	eMsgAddressReqAddQuestion		=	1261, // �ּҷ� ����� ��û�Ͻðڽ��ϱ�?
	eMsgAddressReqReceive				, // �ּҷ� ����� ��û����
	eMsgAddressAlreadyResist			, // �̹� ��ϵǾ��ֽ��ϴ�.
    eMsgAddressReqDelQuestion			, // �ּҷϿ��� �����Ͻðڽ��ϱ�? // 1254
	sMsgAddressAddress					,	//	�ּҷ�
	sMsgAddressTribe					,	//	����
	sMsgAddressName						,	//	�̸�
	sMsgAddressConnect					,	//	����
	// ���
	eMsgGuildReqReceive				=	1271, // ��� ���� ��û ����
	eMsgGuildReqDelMemberQuestion		, // %s�� �����Ͻðڽ��ϱ�?
	eMsgGuildReqSecessionQuestion		, // ���� Ż���Ͻðڽ��ϱ�?
	eMsgGuildBlogErr					, // �ƽ����� ���ԵǾ� ���� ���� ��� �ƽ��� ��α׿� ������ �� �����ϴ�.
	eMsgGuildBlogMakeErr				, //
	
	eMsgGuildCreateOtherJoinErr		=	1276, // �ٸ� ��忡 ���ԵǾ��־ â�� �Ұ�
	eMsgGuildCreateNoTrimuritiErr		, // �ֽ� ������ â�� ����
	eMsgGuildCreateNeedMoneyErr			, // ��� â���� �ʿ��� �� ���ڸ�
	eMsgGuildCreateFail					, // ��� â�� ����
	eMsgGuildMarkConditionErr			, // ����常 ��帶ũ ���� ����

	eMsgGuildDissolutionQuestion	=	1281, // ���� ��ü�Ͻðڽ��ϱ�?
	eMsgGuildMarkConditionErr2			, // �ƽ������� ���̴� ������� 4�ں��� ����� �� �ֽ��ϴ�.
	eMsgGuildDissolutionOK			=	1285, // ��ü ����
	// ������
	eMsgQuickSlotUseTPErr			=	1286, // TP�� ���Ƽ� ��ų ��� �Ұ�
	eMsgQuickSlotUseCoolTimeErr			, // CoolTime �������� ��� �Ұ�
	// GM
	eMsgGMASReceiptOK				=	1291, // ���� ����
	eMsgGMASReceiptLimitOver			, // ���� ó�� �ѵ� �ʰ�. ����� �ٽ� �õ��� �ֽʽÿ�.
	eMsgGMASReceiptFail					,// ������ �������� �ʾҽ��ϴ�. 
	// Ʃ�丮�� �ý���
	eMsgTutorialTitle				=	1301, // źƮ�� ���忡 ���� %s�Կ���...
	eMsgTutorialSubTitle1				,	//	ù�λ�
	eMsgTutorialCommand1				,	//	[ĳ���� �̵������ ����.]
	eMsgTutorialStep1_0					,	//	�������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_1					,	//	Ų�������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_2					,	//	�Ƽ������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_3					,	//	������������ %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_4					,	//	��ũ������ %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_5					,	//	���ٸ������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_6					,	//	�������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_7					,	//	��������� %s�� ���ٶ� ������ ���Ű��� �������� ȯ���մϴ�.
	eMsgTutorialStep1_8					,	//	�Ÿ��� ���õ��� ������ Ǫ������ �;��µ� %s���� �����ϰ� �Ǵ±���. �����Դϴ�.

	eMsgTutorialSubTitle2			=	1313,	//	ĳ�����̵����
	eMsgTutorialStep2_0					,	//	�� �׷� �̵� �غ����?
	eMsgTutorialStep2_1					,	//	���� �� �ָ� ���콺�� ������ Ŭ���� ������. Ŭ���� ���� �� �Ķ������� ���鿡 �׷����ٸ� �ϴ� ����!! ���� ������ �׷����ٸ� �װ��� ���� ���� ���̶��ϴ�.
	eMsgTutorialStep2_2					,	//	ĳ���͸� �̵��� ������

	eMsgTutorialSubTitle3			=	1317,	//	��Ż ����
	eMsgTutorialCommand3				,	//	[���� ������ ����.]
	eMsgTutorialThank1					,	//	%s�� �����ϼ̽��ϴ�.
	eMsgTutorialThank2					,	//	���� ��Ʈ���̾����ϴ�.
	eMsgTutorialStep3_0					,	//	�޸���� �ȱ� ������ 'Z'�� �ϰ� �Ǹ� ���Ÿ� �̵��ÿ� ��Ż�� ����Ͽ� �����̵��� �մϴ�. ��Ż�� ���ٶ� ���� �߾��� �Ÿ� ��, ������ ���ǿ��� �����ø� �˴ϴ�. ������ �� ������ ���� ���Ͱ� �����ϹǷ� �����ϼž� �մϴ�.

	eMsgTutorialSubTitle4			=	1322,	//	���� ����
	eMsgTutorialStep4_0					,	//	źƮ���� �Ƹ��ٿ� �ϴ��� ���� �� �ֳ���?
	eMsgTutorialStep4_1					,	//	���� ���� ����� ����� �Ƹ��ٿ� �ϴ��� ������ ������ ����.
	eMsgTutorialStep4_2					,	//	���콺 ������ ��ư�� ���� ���¿��� ���콺�� �̵��� ������. ������ �յڷ� ������ ���� ���콺 ��ũ�� ��ư�� �����ø� �˴ϴ�.
	eMsgTutorialStep4_3					,	//	������ ������ ������.

	eMsgTutorialSubTitle5			=	1327,	//	���� ���� ���Ű ����
	eMsgTutorialCommand5				,	//	[�̴ϸ� ������ ����.]
	eMsgTutorialStep5_0					,	//	���� �� �˷� �帮�ڸ� 'F11'Ű�� �����ø� 1��Ī, 3��Ī���� ������ȯ�� �����մϴ�. ���� ����Ű�� 'F12'�̸�, ���콺 �߾��� ��ũ�� ��ư�� �����ø� �⺻ �������� ��ȯ�˴ϴ�.

	eMsgTutorialSubTitle6			=	1330,	//	�̴ϸ� ����
	eMsgTutorialStep6_0					,	//	��� ����� �а��� �ȵǽŴٱ���? �̴ϸ��� �̿��Ͻø� ������ ���� �����Ͻ� �� �ֽ��ϴ�.
	eMsgTutorialStep6_1					,	//	�̴ϸʿ� ���̴� ȭ��ǥ�� �ڽ��� ��ġ�� ��Ÿ���� ������⿡ ���� ȭ��ǥ�� ȸ���ϰ� �˴ϴ�. ���� �� ū ������ �� �� �ִµ� �̴ϸ��� ũ�⸦ �����ϴ� ����Ű�� Ű���� 'M'�� ���� ������ �� �ֽ��ϴ�.
	eMsgTutorialStep6_2					,	//	�̴ϸ� ũ�⸦ �ٲ� ������.

	eMsgTutorialSubTitle7			=	1334,	//	�̴ϸ� ������
	eMsgTutorialCommand7				,	//	[����Ű ������ ��´�.]
	eMsgTutorialStep7_0					,	//	������ ���� �ְ���?\n���� �ڼ��� ������ �帮�ڸ� �̴ϸʿ� ���̴� �������� NPC�� ���� Ư¡�� ��� �ֽ��ϴ�.
	eMsgTutorialStep7_1					,	//	���� ���� Ư¡�� ������ �����Ƿ� �O�� ���Ƕ� ���� ���� �O���� �ְ� �̴ϸ� ����� ���ڵ��� ��ǥ�� ǥ���ϹǷ� �����Ͻø� ģ���� �O�� �� ���� ���Ͻ� ���Դϴ�.
	eMsgTutorialStep7_2					,	//	������ ����  ��ȭ��   â��

	eMsgTutorialSubTitle8			=	1339,	//	����Ű Ȱ��
	eMsgTutorialStep8_0					,	//	������ �Ͻ� �� ���� ���Ǵ� ����Ű�� ��� ���� �帮�ڽ��ϴ�.
	eMsgTutorialStep8_1					,	//	������ �Ʒ� ���̴� �������� �� ����� ����Ű�� ������ ���� �������Դϴ�.
	eMsgTutorialStep8_2					,	//	������ �Ʒ� ���̴� �������� �� ����� ����Ű�� ������ ���� �������Դϴ�.
	eMsgTutorialStep8_3					,	//	�������� �����ϴ� ����� ���콺 Ŀ���� ������ ���� �÷����� Ŭ���Ͽ� ������ �� ��ġ�� �ٽ� Ŭ���� �����ø� �˴ϴ�.
	eMsgTutorialStep8_4					,	//	�⺻ ���⸦ ������ ������

	eMsgTutorialSubTitle9			=	1346,	//	����Ű Ȱ��
	eMsgTutorialCommand9				,	//	[���� ��ɹ��� ����.]
	eMsgTutorialStep9_0					,	//	�ٸ� ����Ű�� ���� ������ �帮�ڽ��ϴ�.
	eMsgTutorialStep9_1					,	//	'L'Ű�� ���� ĳ������ ���� ������ �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_2					,	//	'I'Ű�� ���� ����ǰ �Ǵ� ���� �������� Ȯ�� �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_3					,	//	'K'Ű�� ���� �ڽ��� ��� ������� Ȯ�� �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_4					,	//	'U'Ű�� ���� ����Ʈ�� ���õ� ������ �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_5					,	//	'C'Ű�� ��ɾ� ���� �������� Ȯ�� �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_6					,	//	'ESC'Ű�� ���Ӽ��� �Ǵ� �ý��� ���� ������ ���� �� �� �ֽ��ϴ�.
	eMsgTutorialStep9_7					,	//	�÷��̾ ���������� ������ �� �ֽ��ϴ�.(PK�� ���������̹Ƿ� ����� �������� �ް� �˴ϴ�.)

	eMsgTutorialSubTitle10			=	1356,	//	���� ��ɹ�
	eMsgTutorialStep10_0				,	//	��, ���� ����� �غ��ðڽ��ϴ�.
	eMsgTutorialStep10_1				,	//	�̴ϸ��� ���� ���� ���ʿ� ������ ȭ��ǥ�� �ֽ��ϴ�. ȭ��ǥ �Ʒ� ���� ���� ������ ������ ���͵��� �����ϴ� ������ �� �� �ֽ��ϴ�. ���͸� �ѹ� Ŭ���ϸ� ������ ������ ������ �ٽ� �ѹ� Ŭ���ϸ� ���͸� �����ϰ� �˴ϴ�.
	eMsgTutorialStep10_2				,	//	�ٻ�� 1������ ����� ������.

	eMsgTutorialSubTitle11			=	1360,	//	��ɹ� ����
	eMsgTutorialCommand11				,	//	[ITEM �ݴ¹��� ����.]
	eMsgTutorialStep11_0				,	//	�� ���� ����ϴ� ����� �˷��帮�ڽ��ϴ�.
	eMsgTutorialStep11_1				,	//	��ɾ�â�� ����ø�
	eMsgTutorialStep11_2				,	//	������ ���� �O�� �������� �ֽ��ϴ�.
	eMsgTutorialStep11_3				,	//	�������� Ŭ���ؼ� ���ٿ� �÷����� ������ ���͸� ���� �O�� �� �ֽ��ϴ�.

	eMsgTutorialSubTitle12			=	1366,	//	������ �ݴ¹�
	eMsgTutorialStep12_0				,	//	������ �ݴ¹��� ��� ������ �ϰڽ��ϴ�.
	eMsgTutorialStep12_1				,	//	���Ͱ� �װ��� �������� �������ϴ�. ���콺 Ŀ���� �������� Ŭ���ϸ� �������ϴ�. �ٻ���� ����� �� �������� �������� �������
	eMsgTutorialStep12_2				,	//	�������� �������

	eMsgTutorialSubTitle13			=	1370,	//	������ �ݱ� ����
	eMsgTutorialCommand113				,	//	[Ʃ�丮���� ��ġ��]
	eMsgTutorialStep13_0				,	//	���� ���� �������� ���� ����� �˷��帮�ڽ��ϴ�.
	eMsgTutorialStep13_1				,	//	��ɾ�â�� ���� ������ �ݱ� �������� ���ٿ� �÷����� �ش� ��ȣ�� ���� �������� ������ ���� �� ���� �������� ���� �� �ֽ��ϴ�.
	eMsgTutorialStep13_2				,	//	���� ��� Ʃ�丮�� ������ ��ġ�ڽ��ϴ�.\n�� �ð����� �����ϼ̽��ϴ�.

	eMsgTutorialSubTitle14			=	1375,	//	GM ����
	eMsgTutorialCommand114				,	//	[�ʺ��� ����Ʈ�� �Ѵ�.]
	eMsgTutorialStep14_0				,	//	���� �ް� ������ ������ źƮ�� ���忡�� ������ ������� �����ϴ� ���μ� ���߾�� �� �⺻ �Ҿ��� ������ �Ͽ����ϴ�.
	eMsgTutorialStep14_1				,	//	���ݱ��� ���̵带 �� ����, ���� GM�̶�� �̸����� �׻� �翡�� �÷��� ȯ�� ������ ���� ������ �����Ͽ��� �� ���� ������ �帮�� ����̰� �ǰڽ��ϴ�.
	eMsgTutorialStep14_2				,	//	���ݱ��� �н��Ͻ� ����� �װ͵��� ������ �ǽ� �� �� �ִ� �ʺ��� ����Ʈ�� �غ�Ǿ� �ֽ��ϴ�. ���� �ʺ� �ܰ迡 ��� ���� �����۵��� �������� �غ�Ǿ� ������ �����Ͻñ� ���մϴ�.

	eMsgYutTitle					=	1400,	//	Yut
	eMsgYutExplain01					,	//	�������� ������ �����մϴ�.
	eMsgYutBuildMoney					,	//	�� ������
	eMsgYutTotalMoney					,	//	�� ������
	eMsgYutUrgentAllotment				,	//	���� ����
	eMsgYutExplainAllotment				,	//	��÷�� ������ ���� �޽��ϴ�.
	eMsgYutExplainMoney1				,	//	������
	eMsgYutExplainMoney2				,	//	������
	eMsgYutExplainMoney3				,	//	������
	eMsgYutExplainMoney4				,	//	���ʽ�
	eMsgYutExplain02					,	//	������ ���ǾƸ� �Է��� �ּ���.
	eMsgYutExplain03					,	//	���������� �����Ͽ����ϴ�!!.
	eMsgYutExplain04					,	//	���� �ð��� �ƴմϴ�. ���� ���� �ð��� �ٽ� �������ּ���
	eMsgYutExplain05					,	//	��÷���� �޾ҽ��ϴ�. �κ��丮�� Ȯ���� ������
	eMsgYutExplain06					,	//	�����Ͻ� ��÷���� �����ϴ�.

	eMsgSiegeTitle					=	1420,	//	������
	eMsgSiegeUnionAshram				,	//	�����ƽ���
	eMsgSiegeSiegeState					,	//	��������Ȳ
	eMsgSiegeSiegeDeclare				,	//	����������
	eMsgSiegeCastleMgr					,	//	���������
	eMsgSiegeHelp						,	//	����
	eMsgSiegeDefenseUnion				,	//	���� ����
	eMsgSiegeAttackUnion				,	//	���� ����%d
	eMsgSiegeEmptyUnion					,	//	���Ҽ� ����
	eMsgSiegeScoreDefenseUnion			,	//	���� ���� : %d��
	eMsgSiegeScoreAttackUnion			,	//	���� ���� : %d��
	eMsgSiegeScoreEmptyUnion			,	//	���Ҽ� ���� : %d��
	eMsgSiegeSiegeTime					,	//	�������ð�
	eMsgSiegeSiegeNoTime				,	//	���� �ð� ����
	eMsgSiegeFriEve8					,	//	�ݿ��� ���� 8��
	eMsgSiegeFriEve10					,	//	�ݿ��� ���� 10��
	eMsgSiegeSatEve8					,	//	����� ���� 8��
	eMsgSiegeSatEve10					,	//	����� ���� 10��
	eMsgSiegeSunEve8					,	//	�Ͽ��� ���� 8��
	eMsgSiegeExplain01					,	//	������� ���ִ� �ڽ��� ���ϴ� ��¥�� ��������\n ������ �� �ֽ��ϴ�.
	eMsgSiegeExplain02					,	//	�������� ȭ���� 24:00���� �������� ������ �����\n ���� 10�ÿ� ���ֵ˴ϴ�.
	eMsgSiegeApply						,	//	����
	eMsgSiegeCollect					,	//	ȸ��
	eMsgSiegeExplain03					,	//	������� ���ִ� Ư�깰 ������ �Ǹ� ���ݿ� �Һ񼼸� �ΰ��� �� �ֽ��ϴ�.
	eMsgSiegeChageRate					,	//	���� ����
	eMsgSiegeCollectRate				,	//	���� ȸ��
	eMsgSiegeTrustShopRate				,	//	��Ź��������
	eMsgSiegeInfoDefenseUnion			,	//	������������
	eMsgSiegePageNo						,	//	PageNo : %d
	eMsgSiegeJoinUnion					,	//	���Ͱ���
	eMsgSiegeInfoAttackUnion			,	//	������������1
	eMsgSiegeRequestUnionMaster			,	//	���ֽ�û
	eMsgSiegeRequestSiege				,	//	������û
	eMsgSiegeSiegeItem					,	//	����������
	eMsgSiegeSiegeWiner					,	//	����������
	eMsgSiegeRightCastleMaster			,	//	�����Ǳ���
	eMsgSiegeExplain04					,	//	������ ���� ��û
	eMsgSiegeExplain05					,	//	���������� 3���� ���� ������ ������ �� �ֽ��ϴ�. �������� �¸��� ���ְ� �Ǳ� ���ؼ� ���� ������ ���ְ� �Ǿ�� �ϴµ�, �ڽ��� ���ϴ� ���� ������ �����ϰ� ��û ���� ���� �������� �����ؾ� �մϴ�. ���� ��� ù ��° ���� ������ ���ְ� �Ǹ� ���������� �ٸ� ���հ� ������ �� ���ְ� �� �� �ֽ��ϴ�.
	eMsgSiegeExplain06					,	//	������ ���� ��û
	eMsgSiegeExplain07					,	//	���ְ� ������ ������ �����ϸ� ������ �ƽ����� �������� �¸��� �� �ֵ��� ���� �� �� �ֽ��ϴ�. ������ �������� ���� ��� �ƽ����� ���Ҽ����� �������� â���� �� ������ ���Ϳ� ������ �ƽ����� ������ ���Ҽ����� ������ �� �ֽ��ϴ�. ���Ҽ� ������ �������� �¸��ϸ� ���� �����ְ� ���� �ʱ� ���°� �˴ϴ�.
	eMsgSiegeExplain08					,	//	������û
	eMsgSiegeExplain09					,	//	����������
	eMsgSiegeExplain10					,	//	����������
	eMsgSiegeExplain11					,	//	�����Ǳ���
	eMsgSiegeExplain12					,	//	������ ������ �Ƶ���
	eMsgSiegeExplain13					,	//	�������� �����ϰ� ���� �ƽ����� ����� �ϴ뿡�� �Ƶ�� �����ؾ� �մϴ�. �Ƶ���� ����� �ϴ뿡 ����� �ִ� �����Դϴ�. ������� ��¡���� �Ƶ���� ���� �̸����� ������� ���ε��� �� ������ �̿��� �Ŵ��� �Ƶ�� �����ߴٰ� �մϴ�.
	eMsgSiegeExplain14					,	//	�Ƶ���� ���� �ƽ����� �����ֱ� ���� ������ ���� ��û�� �ϴ� �ƽ����� ���� ���� �ּ����� ��ġ�̱⵵ �մϴ�.
	eMsgSiegeExplain15					,	//	�������� ����
	eMsgSiegeExplain16					,	//	������ ���� �ð��� ���� ���� ���� ��¡���� ������ ���� ������ ���� ������ �������� ���ڰ� �˴ϴ�. ������ ��� ���� ����, ���� ����1, 2, 3�� �켱 ������ ���ڰ� �����˴ϴ�.
	eMsgSiegeExplain17					,	//	���Ҽ� ������ �¸�
	eMsgSiegeExplain18					,	//	���Ҽ� ������ �¸��ϴ� ��� ���� ������ ���� �ʱ� ���·� �ٲ�ϴ�.
	eMsgSiegeExplain19					,	//	����� Ư�깰 ������
	eMsgSiegeExplain20					,	//	��������� �ٸ� ������ �Ǹ����� �ʴ� Ư���� �������� �Ǹ��ϴ� ������ �ֽ��ϴ�. ������� ���ִ� Ư�깰�� �߰� ������ ���� �� �ֽ��ϴ�.
	eMsgSiegeExplain21					,	//	������ �� ������
	eMsgSiegeExplain22					,	//	��������� NPC ���䰡 ��ϴ� ������ �Ͱ� �ֽ��ϴ�. ������� ���ִ� ������ �� ������ ����κ��� ������ � ������ �Ϻθ� ������� �������� ������ �� �ֽ��ϴ�.
	eMsgSiegeNameDefenseUnion			,	//	%s ��������
	eMsgSiegeNameAttackUnion			,	//	%s ��������
	eMsgSiegeNoBuildRupia				,	//	������ ���Ǿư� �����ϴ�.
	eMsgSiegeExplain23					,	//	�κ��丮�� %s ���Ǿư� ���޵Ǿ����ϴ�.
	eMsgSiegeNextPage					,	//	���� ������

	eMsgErrorName					=	1480, // �� ������ ���� �����Դϴ�. �ٽ� Ȯ���Ͻð� ���� ������ Ȩ���������� 'ID/PASSWORD ã��'�� �̿��ϼ���.
	eMsgErrorPassword						, // ��й�ȣ�� ���� �ʽ��ϴ�. �ٽ� Ȯ���Ͻð� ���� ������ Ȩ���������� 'ID/PASSWORD ã��'�� �̿��ϼ���.
	eMsgErrorServerConnect					, // ���� �����������̹Ƿ� ���� �Ͻ� �� �����ϴ�. �ڼ��� ������ Ȩ������ ���������� Ȯ���Ͻð� ������ �� �Խ������� ������ �ֽñ� �ٶ��ϴ�.
	eMsgErrorIDBlock						, // �� ������ � ��Ģ�� �ǰ��Ͽ� �з��Ǿ����ϴ�. �ڼ��� ������ �̸����� Ȯ���Ͻð� ������ �� �Խ������� ������ �ֽñ� �ٶ��ϴ�.
	eMsgLoginServerBusy						,	// ������ ����ȭ�� �α��������� ó������ �������� �߻� (������ �ٽ� �õ��� �ֽʽÿ�)
	eMsgLoginServerNotBill					,	// ���� ����� �������߰ų� �̿�Ⱓ�� ����Ǿ����ϴ�.
	eMsgLoginServerNeedBill					,	// źƮ��� ���� �������� �Ǿ����ϴ�. ��ȣ�� ��Ʈ���Ǽ��Ϳ��� �̿���� ������ �ֽʽÿ�.
	eMsgLoginServerOpenWait					,	// ��Ÿ ���񽺰� ����Ǿ����ϴ�. ���� ���񽺰��ñ��� ��ٷ��ּ���.
	eMsgLoginErrorTestServer				,	// �� ������ �׽�Ʈ ������ ������ �Ұ����մϴ�.
	eMsgLoginErrorAgeLimit					,	// źƮ��� ��12�� �̻� ������ �̿��ϽǼ� �ֽ��ϴ�.

	eMsgGuildBlogOpenWarning			=	1501,
	eMsgGuildBlogOpenError1					,
	eMsgGuildBlogOpenError2					,
	eMsgGuildBlogOpenError3					,
	eMsgGuildBlogOpenError4					,
	eMsgGuildBlogOpenError5					,

	eMsgCommandTitle					=	1510,	//	Command
	eMsgCommadnSubTitle						,	//	���
	eMsgCommadnAboutAction					,	//	�ൿ����
	eMsgCommadnAboutGroup					,	//	�׷����
	eMsgCommadnAboutMotion					,	//	��ǰ���
	eMsgCommadDirections					,	//	����
	eMsgCommadStop							,	//	����
	eMsgCommadSiege							,	//	������
	eMsgCommadAutoJoin						,	//	�ڵ�����

	eMsgInvenTitle						=	1520,	// Inventory1
	eMsgInvenSubTitle						,	//	�κ��丮
	eMsgInvenPrivateShop					,	//	���λ���
	eMsgInvenTrade							,	//	��ǰ��ȯ
	eMsgInvenNoExpansionInven				,	//	�κ��丮 Ȯ������ �ʾ���
	eMsgInvenFirstInven						,	//	ù��° �κ��丮
	eMsgInvenSecondInven					,	//	�ι�° �κ��丮
	eMsgInvenInputMoveRupia					,	//	�̵��� ���ǾƸ� �Է����ּ���.
	eMsgInvenNotMoveShortOfInven			,	//	�κ��丮 ������ �����Ͽ� �������� �̵��� �� �����ϴ�.
	eMsgInvenNotMoveShortOfCargo			,	//	â�� ������ �����Ͽ� �������� �̵��� �� �����ϴ�.
	eMsgInvenInputMoveItem					,	//	�̵��� ������ �Է��� �ּ���.
	eMsgInvenWrongInput						,	//	�߸� �Է��ϼ̽��ϴ�.
	eMsgInvenInventory2						,	//	Inventory2
	eMsgInvenCargo							,	//	����â��
	eMsgInvenContribution					,	//	���
	eMsgInvenExplain01						,	//	���� ����� ��θ� �ູ���� �����Ͻ� ���Դϴ�.
	eMsgInvenExplain02						,	//	���� �����κ����� �ູ������ �Ʒ��� �����ϴ�.
	eMsgInvenExplain03						,	//	�ŵ����� �峳���� ������ �� ���������� ���� ���� �� �Դϴ�. �������� ���
	eMsgInvenExplain04						,	//	ä������ Į�� ���ھ�� ������� 5�а� ���������� ���� �����ϴ�.

	eMsgFaceHair0						= 1549, // �̿��
	eMsgFaceHair1							,	// ���� ���
	eMsgFaceHair2							,	// ���� ��
	eMsgFaceHair3							,	// ��� Ÿ��
	eMsgFaceHair4							,	// �� Ÿ��
	eMsgBeautySalon							,	// ���չ̿��
	eMsgSelectHair							,	// ��Ÿ�� ����
	eMsgSelectFace							,	// �� ����
	eMsgNeedTany							,	// �䱸Ÿ��
	eMsgKeepTany							,	// ����Ÿ��
	eMsgSexType								,	// ����

    eMsgAshramTitle						= 1560,	//	Ashram
	eMsgAshramInfo							,	//	�ƽ�������
	eMsgAshramNotice						,	//	���� ����
    eMsgAshramUnionAshram					,	//	���� �ƽ���
	eMsgAshramAshramName					,	//	�ƽ��� ��
	eMsgAshramResigstMember					,	//	����ο�
	eMsgAshramConnectMember					,	//	�����ο�
	eMsgAshramExplainNotice					,	//	���������Դϴ�.
	eMsgAshramNoUnionAshram					,	//	���� �ƽ����� �����ϴ�.
	eMsgAshramOrganizationMember			,	//	�����ο�
	eMsgAshramMakeBlog						,	//	Ȩ������
	eMsgAshramEnterBlog						,	//	Ȩ������
	eMsgAshramMiniBlog						,	//	�̴Ϻ�α�
	eMsgAshramLevel							,	//	����
	eMsgAshramPosition						,	//	����
	eMsgAshramBackMark						,	//	��湮��
	eMsgAshramMark							,	//	����
	eMsgAshramBackColor						,	//	����
	eMsgAshramAshramCargo					,	//	�ƽ���â��%d
	eMsgAshramCargo							,	//	â�� %d
	eMsgAshramExplainCargo01				,	//	�� â����ⰣȮ�ιװ��� ��
	eMsgAshramCargoName						,	//	â���
	eMsgAshramUseYesOrNo					,	//	��뿩��
	eMsgAshramNotUse						,	//	����߾ƴ�
	eMsgAshramEnddate						,	//	����Ⱓ
	eMsgAshramEnd							,	//	����
	eMsgAshramDDay							,	//	D-day
	eMsgAshramPayCargo						,	//	��������
	eMsgAshramSetAshramRight				,	//	�ƽ���â����Ѽ���
	eMsgAshramReqNeedRupia					,	//	�����Ͻ� �ƽ��� â��� %d�� ���Ǿư� �ʿ��մϴ�.\n ���� ����Ͻðڽ��ϱ�?
	eMsgAshramSuccessCragoExpance			,	//	�ƽ��� â��%d Ȯ�忡 �����Ͽ����ϴ�.
	eMsgAshramFaildCargoExpance				,	//	�ƽ��� â�� Ȯ�忡 �����Ͽ����ϴ�.
	eMsgAshramFaildShortOfRupia				,	//	���Ǿư� �����Ͽ� ��û�Ͻ� �۾��� �����Ҽ� �����ϴ�.

	eMsgShopSale						= 1600,	//	�Ǹ�
	eMsgShopSaleTotalPrice					,	//	�Ǹ��Ѿ�
	eMsgShopCarryRupia						,	//	�����ݾ�
	eMsgShopExpanceDate						,	//	Ȯ�����
	eMsgShopMessage							,	//	�޽���
	eMsgShopBuyTotalPrice					,	//	�����Ѿ�
	eMsgShopTrader							,	//	�Ǹ���
	eMsgShopBuyer							,	//	������
	eMsgShopExplain01						,	//	*****�����Ͻ� ������ ���� �����Դϴ�.*****
	eMsgShopExplain02						,	//	***���ų����� �����Ͻø� Ȯ�� ��ư�� ���� �ּ���***
	eMsgShopSubTotal						,	//	�հ�
	eMsgShopLeft							,	//	��
	eMsgShopRight							,	//	��
	eMsgShopExplain03						,	//	�����̾� ���� �̿볻��
	eMsgShopExplain04						,	//	�����̾� ������ �߰� ��û�� ����Ⱓ�� �þ�ϴ�.
	eMsgShopExplain05						,	//	ȿ���� OFF�� ������ ���� ����Ⱓ�� ��������� �ʽ��ϴ�.
	eMsgShopBundle							,	//	�ٷ���
	eMsgShopCharacter						,	//	ĳ����
	eMsgShopConvenience						,	//	���Ǽ�
	eMsgShopAbility							,	//	��ɼ�
	eMsgShopspeciality						,	//	Ư����
	eMsgShopReqBuyItem						,	//	���� �������� ����Ͻðڽ��ϱ�?\n[����]�ڽ��� ��ǻ�� ��¥�� ��Ȯ���� ���� ��� ���Ⱓ�� ����� ǥ����� ���� �� �ֽ��ϴ�.

	eMsgCharInfoTitle					= 1650,	//	ĳ���� ����
	eMsgCharInfoCast						,	//	ī �� Ʈ
	eMsgCharInfoExplainAshram				,	//	�ƽ�����
	eMsgCharInfoTrimuriti					,	//	��     ��
	eMsgCharInfoPointTriburiti				,	//	�ֽ�����Ʈ
	eMsgCharInfoKarma						,	//	ī �� ��
	eMsgCharInfoAblitityStatus				,	//	ĳ���� �ɷ»���
	eMsgCharInfoLifrPower					,	//	�� �� ��
	eMsgCharInfoTapas						,	//	Ÿ �� ��
	eMsgCharInfoDefencePower				,	//	�� �� ��
	eMsgCharInfoPhysicsAP					,	//	�������ݷ�
	eMsgCharInfoAttackRate					,	//	���ݼ�����
	eMsgCharInfoEvasionRate					,	//	ȸ �� ��
	eMsgCharInfoChakra						,	//	��ũ��
	eMsgCharInfoMuscle						,	//	��     ��
	eMsgCharInfoNerve						,	//	��     ��
	eMsgCharInfoHeart						,	//	��     ��
	eMsgCharInfoSoul						,	//	��     ��
	eMsgCharInfoRemaindChakra				,	//	�ܿ���ũ��
	eMsgCharInfoResistancePower				,	//	���׷�
	eMsgCharInfoFire						,	//	ȭ     ��
	eMsgCharInfoElectric					,	//	��     ��
	eMsgCharInfoCold						,	//	��     ��
	eMsgCharInfoPoison						,	//	��
	eMsgCharInfoTribe						,	//	��     ��
	eMsgCharInfoOccupation					,	//	��     ��
	eMsgCharInfoSkillPoint					,	//	��ų����Ʈ
	eMsgCharInfoGodPoint					,	//	�ֽ� ��ų

	eMsgQuest							= 1680,	//	Quest
	eMsgQuestDiaryQuest						,	//	����Ʈ ����
	eMsgQuestContinueQuest					,	//	�������� ����Ʈ
	eMsgQuestConditionQuest					,	//	����Ʈ ����
	eMsgQuestCompletionQuest				,	//	�Ϸ� ����Ʈ

	eMsgPortalTitle						= 1690,	//	��Ż
	eMsgPortalPortalName					,	//	������Ż�̸�
	eMsgPortalJivaPustica					,	//	����Ǫ��Ƽī
	eMsgPortalSelectZone					,	//	���Ͻô� ������ �����ϼ���
	eMsgPortalMandaraVillage				,	//	���ٶ� ����
	eMsgPortalShambalraZone					,	//	���߶� ����
	eMsgPortalJinaZone						,	//	���� ����
	eMsgPortalExile							,	//	������
	eMsgPortalTrimuriti						,	//	�ֽ�����
	eMsgPortalHighJivaPustica				,	//	�������Ǫ��Ƽī
	eMsgPortalSelectOtherZone				,	//	<-�ٸ����� ����->

	eMsgOptionTitel						= 1710,	//	Option
	eMsgOptionBasicOption					,	//	�⺻�ɼ�
	eMsgOptionGraphOption					,	//	�׷��ȿɼ�
	eMsgOptionSoundOption					,	//	����ɼ�
	eMsgOptionWindowAhlpa					,	//	�����차��
	eMsgOptionShowID						,	//	���̵�ǥ��
	eMsgOptionEffect						,	//	����Ʈ
	eMsgOptionSimpleShop					,	//	��������ȭ
	eMsgOptionResolution					,	//	�ػ�
	eMsgOptionEffectSound					,	//	ȿ����
	eMsgOptionBGM							,	//	�������
	eMsgOptionReStart						,	//	�����
	eMsgOptionExitGame						,	//	��������

	eMsgChatChangeChatMode				= 1730, //	ä�ø�庯ȯ
	eMsgChatConfigChat						,	//	ä�ü���
	eMsgChatShowConfigChatMsg				,	//	ä�ó���ǥ�ü���
	eMsgChatUnion							,	//	����
	eMsgChatChatLog							,	//	ä�÷α�
	eMsgChatList							,	//	����Ʈ
	eMsgChatNormalMsg						,	//	�Ϲݸ޽���(ä�÷ΰ�â)
	eMsgChatOpenMsg							,	//	�����Ǹ޽���(ä�÷ΰ�â)
	eMsgChatSave							,	//	����
	eMsgChatSystem							,	//	�ý���

	eMsgRevivalRevivalCurrentPos		= 1740,	//	������ �ڸ����� ��Ȱ
	eMsgRevivalRevivalSavedZone				,	//	����� �������� ��Ȱ
	eMsgRevivalWebWindow					,	//	Web Window
	eMsgRevivalWebBrowser					,	//	WebBrowser�� �����մϴ�.
	eMsgRevivalRevivalArena					,	//	�Ʒ��� ���߼����� ��Ȱ(20000 ���Ǿ� �Ҹ�)
	eMsgRevivalRevivalFotress				,	//	������ ������� ��Ȱ
	eMsgRevivalRevivalNorthViruCastle		,	//	����� ���� ���� ��ó���� ��Ȱ
	eMsgRevivalExitWeb						,	//	������

	eMsgRentalStoreMessage				= 1750,	// ��Ź����
	eMsgRentalStoreQuestionCancel			,	// ��Ź���� �������� ��� �Ͻðڽ��ϱ�?
	eMsgRentalCannotBuyBecauseTimeOver		,	// �Ǹ� �ð��� ���� ������ �Դϴ�. ������ �� �����ϴ�.
	eMsgRentalStoreQuestionBuy				,	// ���� ���� �Ͻðڽ��ϱ�?
	eMsgRentalStoreInputFailed				,	// �߸� �Է��Ͽ����ϴ�
	eMsgRentalStoreMovingItmeMessage1		,	// ��� �������� �ִٸ� �ڵ����� �κ��丮�� �ű�ϴ�.
	eMsgRentalStoreWantSellTexInput			,	// ���ϴ� �Ǹ� ������ �Է��� �ּ���. (1~7%)
	eMsgRentalStoreItemMessage				,	// ��Ź ������
	eMsgRentalStoreItemMessage2				,	// ��Ź����(%d)
	eMsgRentalStoreItemMessage3				,	// ��� ������
	eMsgRentalStoreItemMessage4				,	// ��Ź�ǸŸ� ���� �̿��� �����Դϴ�.\nȮ���� �����ø� �ǸŸ� �����մϴ�.
	eMsgRentalStoreItemMessage5				,	// ��Ź�ǸŸ� ���� �̿��� %d (���� %d%%����) ���Ǿ� �Դϴ�.\nȮ���� �����ø� �ǸŸ� �����մϴ�.
	eMsgRentalStoreItemMessage6				,	// �Ǹ� �ð��� �Է��ϼ���. (1~24�ð�)
	eMsgRentalStoreItemMessage7				,	// ���� �ǸŵǾ� ������ ���Ǿƴ� �� %d �Դϴ�.>>������ ���Ͻø� Ȯ�ι�ư�� �����ּ���.
	eMsgRentalStoreItemMessage8				,	// �������� ��Ź�Ͽ����ϴ�.
	eMsgRentalStoreItemMessage9				,	// �������� ��Ź���� ���߽��ϴ�.
	eMsgRentalStoreItemMessage10			,	// �������� ��Ź�� ����Ͽ����ϴ�.
	eMsgRentalStoreItemMessage11			,	// ��Ź�� �������� ����� �� �����ϴ�.
	eMsgRentalStoreItemMessage12			,	// ������ ���Ǿư� �����ϴ�.
	eMsgRentalStoreItemMessage13			,	// ������ ���ǾƸ� ��� ã�ҽ��ϴ�.
	eMsgRentalStoreItemMessage14			,	// ������ ����Ǿ����ϴ�.
	eMsgRentalStoreItemMessage15			,	// �������� �����Ͽ����ϴ�.
	eMsgRentalStoreItemMessage16			,	// �������� �������� ���߽��ϴ�.
	eMsgRentalStoreItemMessage17			,	// ��ǰ ����� ����Ǿ� �����մϴ�.
	eMsgRentalStoreItemMessage18			,	// 30�� �̻��� �������� ���� �׿� �ֽ��ϴ�.

	eMsgChatRoomMessage1				= 1780,	// ä�� ��
	eMsgChatRoomMessage2					,	// ���� ��ħ
	eMsgChatRoomMessage3					,	// ���ȣ
	eMsgChatRoomMessage4					,	// ��          ��
	eMsgChatRoomMessage5					,	// ������
	eMsgChatRoomMessage6					,	// �ο�
	eMsgChatRoomMessage7					,	// �游���
	eMsgChatRoomMessage8					,	// ����
	eMsgChatRoomMessage9					,	// �ݱ�
	eMsgChatRoomMessage10					,	// ����޴�
	eMsgChatRoomMessage11					,	// ��ȭ�� ����
	eMsgChatRoomMessage12					,	// �ο� ����
	eMsgChatRoomMessage13					,	// ���� ����
	eMsgChatRoomMessage14					,	// ��й�ȣ ����
	eMsgChatRoomMessage15					,	// �Ϸ�
	eMsgChatRoomMessage16					,	// ���
	eMsgChatRoomMessage17					,	// ä�ý�
	eMsgChatRoomMessage18					,	// ��ȭ����
	eMsgChatRoomMessage19					,	// ������
	eMsgChatRoomMessage20					,	// �ʴ��ϱ�
	eMsgChatRoomMessage21					,	// û  ��
	eMsgChatRoomMessage22					,	// ������
	eMsgChatRoomMessage23					,	// ��ȣ
	eMsgChatRoomMessage24					,	// �̸�
	eMsgChatRoomMessage25					,	// ä�ù濡 ������ �õ��մϴ�.
	eMsgChatRoomMessage26					,	// ä�ù����� ���� �������� �Ǿ����ϴ�.
	eMsgChatRoomMessage27					,	// �ƹ��� ��������!!
	eMsgChatRoomMessage28					,	// %d�� �濡 �����Ͻðڽ��ϱ�?
	eMsgChatRoomMessage29					,	// ��й�ȣ�� �Է��ϼ���.
	eMsgChatRoomMessage30					,	// �߸� �Է� �Ͽ����ϴ�.
	eMsgChatRoomMessage31					,	// %s���� �߹��Ͻðڽ��ϱ�?
	eMsgChatRoomMessage32					,	// ���常 �ʴ��� �� �ֽ��ϴ�.
	eMsgChatRoomMessage33					,	// %s���� �ʴ��Ͻðڽ��ϱ�?
	eMsgChatRoomMessage34					,	// ä�ù� ���ῡ �����Ͽ����ϴ�.
	eMsgChatRoomMessage35					,	// ������ ������ �������� �ʾҽ��ϴ�.
	eMsgChatRoomMessage36					,	// ä�ù� ���� �����Ͽ����ϴ�.
	eMsgChatRoomMessage37					,	// ä�ù� ���� ���� �Ͽ����ϴ�.
	eMsgChatRoomMessage38					,	// *%s���� �����Ͽ����ϴ�.*
	eMsgChatRoomMessage39					,	// *%s���� �����̽��ϴ�.*
	eMsgChatRoomMessage40					,	// *%s���� �߹�Ǿ����ϴ�.*
	eMsgChatRoomMessage41					,	// ä�ù濡 �����Ͽ����ϴ�.
	eMsgChatRoomMessage42					,	// ä�ù濡 �������� ���߽��ϴ�.
	eMsgChatRoomMessage43					,	// ä�ù��� �����ϴ�.
	eMsgChatRoomMessage44					,	// %s���� ����� �ʴ��Ͽ����ϴ�. �����Ͻðڽ��ϱ�?
	eMsgChatRoomMessage45					,	// �ʴ밡 ��ҵǾ����ϴ�.
	eMsgChatRoomMessage46					,	// ä�ù� ������ ����Ǿ����ϴ�.
	eMsgChatRoomMessage47					,	// ä�ù� ���� ������ ���� �Ͽ����ϴ�.
	eMsgChatRoomMessage48					,	// ���忡 ���� �߹���Ͽ����ϴ�.

} eMsgCharacter;

//--------------------------------------------------------------
// Item
//--------------------------------------------------------------
typedef enum _eMsgItem
{
	// ����
	eMsgItemCommonOwnerErr			=	2001, // ������ ������ ����
	eMsgItemCommonInvenLack				, // �κ��丮 ���� ����
	eMsgItemCommonPositionErr			, // �̵���ġ ����
	eMsgItemCommonNotExistItem			, // �������� �ʴ� ������
	eMsgItemCommonMoneyErr				, // ���Ǿ� ����
	eMsgItemCommonCannotFindInfo		, // ������ ������ ã�� �� ����
	eMsgItemCommonNoInventory			, // pc�κ��丮 �̿��� ������ ����
	
	eMsgCommonDistanceErrToNPC			, // npc���� �Ÿ��� �ִ�
	eMsgCommonCannotClickNPC			, // �ٸ� �ֽ������� npc�� Ŭ���� �� ���� // 2009
	eMsgItemCommonCashErr				, // ĳ���� �����մϴ�.

	// ������ �̵�
	eMsgItemMoveDistanceErr			=	2011, // �̵��Ÿ� ����
	eMsgItemMoveRoutingTime				, // ������ ���� �ð� ����
	eMsgItemMoveReceive					, // ������ ȹ��
	eMsgItemMoveTwoHandErr				, // ��չ��� ���� ����(�޼տ� �������� ����)
	eMsgItemMoveDropQuestion			, // ���� �����ðڽ��ϱ�?
	eMsgItemMoveCannot					, // �̵��� �� ���� ������
	eMsgItemMoveAutoReceive				, // [�ڵ��й�]%s, %s ȹ�� // 2017
	eMsgItemMoveFail				=	2020, // �׿� ������ �̵�����
	// ������ ��ø
	eMsgItemPackDestination			=	2021, // ��� �������� �������� �ʽ��ϴ�.
	eMsgItemPackNotPack					, // ��ø �Ұ����� ������
	eMsgItemPackDisable					, // ���� �ٸ� �������� ��ø �Ұ���
	eMsgItemPackNotAdd					, // �ִ� ��ø�����Դϴ�.
	eMsgItemPackFail				=	2030, // ��ø ����
	// ������ ����
	eMsgItemUnpackCountErr			=	2031, // ���� ���� ������
	eMsgItemUnpackNotUnpack				, // ����ŷ �Ұ����� ������
	eMsgItemUnpackPlaceErr				, // ����ŷ �ڸ� ������
	eMsgItemUnpackFail				=	2040, // ���� ����
	// ������ ���
	eMsgItemUseNotUse				= 	2041, // ����� �� ���� ������
	eMsgItemUseCountErr					, // ������ ī��Ʈ ����
	eMsgItemUseConditionErr				, // ��� ���� ���� ����
	eMsgItemUseCannot					, // �������� ����� �� ���� ����
	eMsgItemUseFail					=	2045, // ������ ��� ����
	// ������ ����
	eMsgItemEquipTypeErr			=	2046, // ���� �Ұ����� ������
	eMsgItemEquipPosErr					, // ���� ��ġ ���� 
	eMsgItemEquipExistItem				, // ���� ��ġ�� �ٸ� �������� ����
	eMsgItemEquipConditionErr			, // ���� ���׿� ���� ���� ����
	// ������ ����-�κ��丮 Ȯ��/����
	eMsgItemEquipInvenIncOK				, // �κ��丮 Ȯ�� ����
	eMsgItemEquipInvenDecOK				, // �κ��丮 ���� ����
	eMsgItemEquipNotExistExpandInven	, // �κ��丮 Ȯ�� �������� ����
	eMsgItemEquipNoExpandedInven		, // Ȯ��� �κ��丮 ����
	eMsgItemEquipInvenIncFail			, // �κ��丮 Ȯ�� ����
	eMsgItemEquipDecExistItem			, // Ȯ��� �κ��丮�� ������ ����
	eMsgItemEquipInvenDecFail			, // �κ��丮 ���� ����
	eMsgItemEquipInvenExpanded			, // �̹� �κ��丮�� Ȯ��Ǿ� ����
	eMsgItemEquipExpandDate				, // �κ��丮 Ȯ����� %s // 2058
	eMsgItemUseCannotNowZone			, // �������� ����� �� ���� �����Դϴ�. 2059
	eMsgItemEquipFail				=	2060, // ���� ����
	//������ ����
	eMsgItemBuySeveralNumOK			=	2101, // ������ ������ ���� ���� 
	eMsgItemBuyOneOK					, // ������ 1�� ���� ����
	eMsgItemBuyOK						, // ������ ���� ����
	eMsgItemBuyMaxCountErr				, // �ִ� ���� ���� ���� 
	eMsgItemBuyQuestionItem				, // ������ ���� ����
	eMsgItemBuyQuestionItemNum			, // ������ ���� ���� ����
	eMsgItemBuyCannot					, // ������ ���� ���� ����
	eMsgItemBuyDoNot					, // %s �������� �������� ���߽��ϴ�.
	eMsgItemBuyMinCountErr				, // �ּ� ���� ���� ����
	eMsgItemBuyFail					=	2110, // ���� ����
	// ������ ����
	eMsgItemRepairSuccess			=	2111, // ���� ����
	eMsgItemRepairNeedNot				, // ������ �ʿ� ���� ������
	eMsgItemRepairDoNot					, // �̰����� ������ �� ���� ������
	eMsgItemRepairOK					, // �����Ǿ����ϴ�.
	eMsgItemRepairFail					, // ���� ����
	// ������ �Ǹ�
	eMsgItemSellSuccess				=	2116, // �Ǹ� ����
	eMsgItemSellQuestionItem			, // �Ǹ��� ������ ����
	eMsgItemSellDoNot					, // �̰����� �Ǹ��� �� ���� ������
	eMsgItemSellFail				=	2120, // �Ǹ� ���� 
	// ������ ����
	eMsgItemRefineOneOverOK			=	2121, // ���� 1�ܰ� �̻��� �������� ����
	eMsgItemRefineFirstOK				, // ù��° ���� ����
	eMsgItemRefineOK					, // ���� ����
	eMsgItemRefineDisappear				, // ������ �����
	eMsgItemRefineOneOverErr			, // ���� 1�ܰ� �̻��� �������� ����
	eMsgItemRefineFirstErr				, // ù��° ���� ����
	eMsgItemRefineErr					, // ���� ����
	eMsgItemRefineMeterialErr			, // ÷�� �Ұ����� �������
	eMsgItemRefineMainCannot			, // ��ȭ���� Ƚ�� ����
	eMsgItemRefineSubCannot				, // �ּ����� Ƚ�� ����
	eMsgItemRefineDoNot					, // ������ �� ���� ������
	eMsgItemRefineSelectMeterial		, // ������Ḧ �����Ͽ� �ֽʽÿ�.
	eMsgItemRefineSelectItem			, // ������ �������� �����Ͽ� �ֽʽÿ�.
	eMsgItemRefineWarningLevel1			, // ���� ���
	eMsgItemRefineWarningLevel2			, // ���� ���
	eMsgItemRefineWarningLevel3			, // ���� ���
	eMsgItemRefineWarningLevel4			, // ���� ���
	eMsgItemRefineWarningLevel5			, // ���� ���
	eMsgItemRefineWarningLevel6			, // ���� ���
	eMsgItemRefineWarningLevel7			, // ���� ���
	eMsgItemRefineWarningLevel8			, // ���� ���
	eMsgItemRefineSubWarning			, // �ּ� ���� ���
	eMsgItemRefineWarningLevel9			, // ���� ���	
	eMsgItemRefineSubInitWarning		, // �ּ����� �ʱ�ȭ // 2144
	eMsgItemRefineSubInitWarning2		, // �ּ����� �ʱ�ȭ // 2144
	eMsgItemRefineNeedMoneyErr			, // ���Ǿ� ����
	eMsgItemRefineInitialize			, // ���� ��� ������ �ʱ�ȭ
	eMsgItemRefineWarningLevel10		, // ���� ���	
	eMsgItemRefineWarningLevel11		, // ���� ���	

	eMsgItemRefineFail				=	2150, // ���� ����
	// ��ġ ����
	eMsgSavePositionQuestion		=	2151, // ���� ��ġ�� �����Ͻðڽ��ϱ�?
	eMsgSavePositionOK					, // ���� ��ġ�� �����߽��ϴ�.
	eMsgSavePositionFail			=	2155, // ���� ��ġ�� �������� ���߽��ϴ�.
	// ����
	eMsgJobChangeOK					=	2156, // ���� ����
	eMsgJobChangeOtherChar				, // �ٸ� ĳ���� ���� ����
	eMsgJobChangeFail				=	2160, // ���� ����
	// ��ũ�� ȯ��
	eMsgChakraConversionOK			=	2161, // ��ũ�� ȯ�� ����
	eMsgChakraConversionItemErr			, // ������ ������ ����
	eMsgChakraConversionFail			, // ��ũ�� ȯ�� ����	// 2163
	// ������ ������
	eMsgItemDurabilityWarning		=	2165, // ������ ������ ����
	// �ֽ� ����
	eMsgTrimuritiChangeCondition1	=	2171, // �ֽ� ���� ����1-��
	eMsgTrimuritiChangeCondition2		, // �ֽ� ���� ����2-��, ������
	eMsgTrimuritiChangeCondition3		, // �ֽ� ���� ����-��� ���� �߿� �ȵ�
	eMsgTrimuritiChangeConditionDay		, // �ֽ� ���� ����-��¥
	eMsgTrimuritiChangeOK				, // �ֽ� ���� ����
	eMsgTrimuritiChangeQuestion			, // �ֽ� %s������ �����Ͻðڽ��ϱ�?
	// �ֽ� ����Ʈ
	eMsgTrimuritiPointCondition1	=	2181, // �ֽ� ����Ʈ ���� ����-��,������
	eMsgTrimuritiPointCondition2		, // �ֽ� ����Ʈ ���� ����-�ֽ�����Ʈ ����
	eMsgTrimuritiPointOK				, // �ֽ� ����Ʈ ���� ���� // 2183

	eMsgShopDefaultName				=	2191, // ���ǻ缼��
	eMsgShopNamePublicity				, // [�Ǹ�]%s[%s]
	eMsgShopTotalPriceOverflow			, // �Ǹ� �Ѿ��� �ʹ� Ů�ϴ�.
	eMsgShopNotifyCondition1			, // 1. ���� ���� ���� �ÿ� ���������� ���ݺ��� �� ���� �ٸ� �������� ����� �ϴ� ���
	eMsgShopNotifyCondition2			, // 2. ���ݿ� �ǵ������� ������ �����ϱ� ���� '0'�� �����̴� ����
	eMsgShopNotifyPunishment			, // ���� ���� : �� 7�� �����з�, 2�� ���� �����з�
	eMsgShopExpandDate					, // ���� ���� Ȯ����� %s
	eMsgShopExpandOK					, // ���λ����� Ȯ��ƽ��ϴ�.
	eMsgShopAutoRouting					, // �ڵ� ���ݱ� ����� ����Ǿ����ϴ�.
	eMsgShopAdeptDate					, // ���� ����

	eMsgOfferingOK					=	2206, // �峳 ����
	eMsgOfferingCannot					, // �峳�� �� ���� ������
	eMsgOfferingNotify1					, // �ູ�� �Ŵ��� �ſ��� ������ ��ġ�� �ڽ��� �žӽ��� ��Ȯ���Ͽ� �ູ�� �޴� ����� ������ �ֽ��ϴ�.
	eMsgOfferingNotify2					, // ������ ������ ��ġ�� ���� ����Ȯ���� �����ϴ� �ູ�� ���� �� �ֽ��ϴ�.
	eMsgOfferingNotify3					, // ��, �ູ�� �Ŵܿ� ��εǾ����� �������� ������� �˴ϴ�. // 2210
	eMsgOfferingNotify4					, // ����� �������� ��� ���� �Ǹ� �ϴ��� �������� ���� �˴ϴ�.
	eMsgOfferingNotify5					, // ����� �������� �ϴ��� �������� ä��µ� �ҿ�Ǵ� ���Ǿ� �Ǵ� �������� ���� �ٸ��ϴ�.
	eMsgOfferingFail				=	2215 // �峳 ����

} eMsgItem;

typedef enum _eMsgInfo
{
	// ����â ��ư ����
	eMsgMainCheckPrimiumBuy			=	3000, // �����̾� ������ ����
	eMsgMainCheckCharacInfo				, // ĳ���� ����
	eMsgMainCheckInventory				, // �κ��丮
	eMsgMainCheckQuest					, // ����Ʈ â
	eMsgMainCheckSkill					, // ��ų
	eMsgMainCheckOption					, // �ɼ�
	eMsgMainCheckCommand				, // ���
	eMsgMainCheckPK						, // PK	

	eMsgCommandSitDown					, // �ɱ�
	eMsgCommandWalk						, // �ȱ�
	eMsgCommandAttack					, // ����
	eMsgCommandTrade					, // ��ȯ
	eMsgCommandTarget					, // Ÿ��
	eMsgCommandPickUp					, // �ݱ�
	eMsgCommandParty					, // ��Ƽ
	eMsgCommandPartyDrop				, // ��Ƽ Ż��
	eMsgCommandShop						, // ���� ����
	eMsgCommandProvocation				, // ����
	eMsgCommandGreeting					, // �λ�
	eMsgCommandRush						, // ���� // 3019
	eMsgCommandDuel						, // ����

	// ������ ����
	eMsgItemInfoRepairTitle			=	3021, // ��������
	eMsgItemInfoSellTitle				, // �Ǹ�����
	eMsgCommandWait						, // ����(Away)
	eMsgCommandSupport					, // ����(Assist)
	eMsgCommandBlog						, // ��α�(Blog)


	eMsgItemInfoCannotRepair		=	3026, // �����Ұ�
	eMsgItemInfoCannotSell				, // �ǸźҰ�
	eMsgItemInfoCannotRefine			, // ���úҰ�
	eMsgItemInfoCannotMainRefine		, // ��ȭ���� �Ұ�
	eMsgItemInfoCannotSubRefine			, // �ּ����� �Ұ�
	eMsgItemInfoUnbreakable				, // �ı��Ұ� // 3031
	
	eMsgItemInfoHourMinute			=	3032, // ��ȿ�ð� %d�ð� %d��
	eMsgItemInfoHour					, // ��ȿ�ð� %d�ð�
	eMsgItemInfoMinute					, // ��ȿ�ð� %d��
	eMsgItemInfoPrice					, // %d ���Ǿ�
	eMsgItemInfoNeedMoney				, // %d ���Ǿ� �ʿ�
	eMsgItemInfoRemainMainRefine		, // ���� ��ȭ���� Ƚ��
	eMsgItemInfoRemainSubRefine			, // ���� �ּ����� Ƚ��
	eMsgItemInfoPackCount				, // ��ø ����
	eMsgItemInfoMaxPackCount			, // �ִ� ���� ����
	eMsgItemInfoPrivateUse				, // ~����
	eMsgItemInfoUsable					, // ~��
	eMsgItemInfoNeedLevel				, // %d ���� �ʿ�
	eMsgItemInfoMuscleChakra			, // ������ ��ũ�� %d
	eMsgItemInfoNerveChakra				, // �Ű��� ��ũ�� %d
	eMsgItemInfoHeartChakra				, // ������ ��ũ�� %d
	eMsgItemInfoSoulChakra				, // ������ ��ũ�� %d
	eMsgItemInfoDurability				, // ������ %d / %d
	eMsgItemInfoDuration				, // ���ӽð� %d��
	eMsgItemInfoAttackSpeedVeryHigh		, // ���ݼӵ� �ſ����
	eMsgItemInfoAttackSpeedHigh			, // ���ݼӵ� ����
	eMsgItemInfoAttackSpeedNormal		, // ���ݼӵ� ����
	eMsgItemInfoAttackSpeedLow			, // ���ݼӵ� ����
	eMsgItemInfoAttackSpeedVeryLow		, // ���ݼӵ� �ſ����
	eMsgItemInfoCostHP					, // HP �Ҹ�
	eMsgItemInfoCostTP					, // TP �Ҹ�
	eMsgItemInfoCostItem				, // %s �Ҹ�
	eMsgItemInfoCostItemCount			, // %s %d�� �Ҹ� 
	eMsgItemInfoPrice2					, // %s ���Ǿ�
	eMsgItemInfoPrice3					, // %s ĳ�� // 3060
	// ��ų ����
	eMsgSkillInfoNeedCondition		=	3061, // �䱸 ���� 
	eMsgSkillInfoNextCondition			, // ���� �ܰ� ����
	eMsgSkillInfoNeedLevel				, // �ʿ� ����
	eMsgSkillInfoNeedSkillLevel			, // �ʿ� ��ų ����
	eMsgSkillInfoNeedItem				, // �ʿ� ������
	eMsgSkillInfoCannotFindInfo		=	3070, // ��ų ���� ã�� �� ����
	// ���� ���
	eMsgAllowedTargetSelf			=	3071, // ���� 	
	eMsgAllowedTargetFriendly			, // PC, �ֽ������� ���� �ֽ�			
	eMsgAllowedTargetFriendlyExceptMe	, // �ڽ��� ����	
	eMsgAllowedTargetParty				, // ��Ƽ����				
	eMsgAllowedTargetGuild				, // ������
	eMsgAllowedTargetAll				, 
	eMsgAllowedTargetFriendlyCorpse		, // ��Ȱ�������� ������ ��ü�� ���
	eMsgAllowedTargetEnemeyCorpse		, // ��ü���� �������� ���� ��ü�� ���
	eMsgAllowedTargetGate				, // ����	// 3079
	// Effect
	eMsgEffectDamage				=	3101,
	eMsgEffectDamageLimitLevel			, // ������������ %s%% ����
	eMsgEffectEnergyOfSword				, // �� ���ݷ� %s%% - %s%% ���
	eMsgEffectFire						, // ȭ�� ���ݷ� %s - %s
	eMsgEffectCold						, // �ñ� ���ݷ� %s - %s  //fors_debug ��װ��������ʾ�ĵط�
	eMsgEffectLightning					, // ���� ���ݷ� %s - %s
	eMsgEffectPoison					, // �� ���ݷ� %s - %s	
	eMsgEffectAllDamageUp				, // ��� �Ӽ� ���ݷ� %s%% ���
	eMsgEffectAllDamageDown				, // ��� �Ӽ� ���ݷ� %s%% ���� // 3109

	eMsgEffectDamageSplash			=	3111, // ���÷��� %s - %s
	eMsgEffectFireSplash				, // ȭ�� ���÷��� ���ݷ� %s - %s
	eMsgEffectColdSplash				, // �ñ� ���÷��� ���ݷ� %s - %s
	eMsgEffectLightningSplash			, // ���� ���÷��� ���ݷ� %s - %s
	eMsgEffectPoisonSplash				, // �� ���÷��� ���ݷ� %s - %s // 3115
	
	eMsgEffectSummon				=	3121, // %s %s���� ��ȯ
	eMsgEffectIllusion					, // %s %s���� ����	// 3122

	eMsgEffectMoveSpeedPlus			=	3131, // �̵��ӵ� %s%% ����
	eMsgEffectMoveSpeedMinus			, // �̵��ӵ� %s%% ���� 
	eMsgEffectAttackSpeedPlus			, // ���ݼӵ� %s%% ����
	eMsgEffectAttackSpeedMinus			, // ���ݼӵ� %s%% ����
	eMsgEffectCastSpeedPlus				, // ĳ���üӵ� %s%% ����
	eMsgEffectCastSpeedMinus			, // ĳ���üӵ� %s%% ���� // 3136

	eMsgEffectInvisible				=	3141, // �������
	eMsgEffectWizardEyes				, // ������� ����
	eMsgEffectHold						, 
	eMsgEffectStun						, // ����
	eMsgEffectSleep						, // ��
	eMsgEffectBlind						, // ���
	eMsgEffectTerror					, // �������� �Ѵ�.
	eMsgEffectTaunt						, // �� �÷��� �����ϰ� �Ѵ�.
	eMsgEffectInvulnerable				, // ��������
	eMsgEffectExpandBag					, // �κ��丮 Ȯ�� %s X %s
	eMsgEffectConcentration				, // ĳ���� ���� %s%%����
	eMsgEffectDisruption				, // ���� ĳ���� ����
	eMsgEffectMagicShield				, // HP�� �ִ� ���� ����. �ִ� HP %s
	eMsgEffectStealHP					, // �������� %s%% HP ��ħ
	eMsgEffectStealTP					, // �������� %s%% TP ��ħ
	eMsgEffectBash						, // %s Ȯ���� �߰� ������ %s
	eMsgEffectMultipleStrike			, // %s%% ������ %sȸ
	eMsgEffectPierceStrike				, // �����ϱ� - �����Ÿ� %s
	eMsgEffectKnockBack					, // %s Ȯ���� KnockBack %s
	eMsgEffectHPDown					, // HP %s%%����
	eMsgEffectHeal						, // HP %sȸ��
	eMsgEffectHeal2						, // HP %sȸ�� - ���� ����
	eMsgEffectTargetHeal				, // ��� HP %sȸ��
	eMsgEffectHealRate					, // HP %s%%ȸ��
	eMsgEffectRecoverTP					, // TP %sȸ��
	eMsgEffectRecoverTP2				, // TP %sȸ�� - ���� ����
	eMsgEffectTargetHealTP				, // ��� TP %sȸ��
	eMsgEffectRecoverTPRate				, // TP %s%%ȸ��
	eMsgEffectiACrificeHP				, // HP %s �Ҹ�
	eMsgEffectCure						, // EffectID %s
	eMsgEffectResurrect					, // ����ġ %s ȸ�� - �Ҹ� ��Ȱ�� %s��
	eMsgEffectReflectDamage				, // ������ �ݻ� %s%%
	eMsgEffectAbsorbDamage				, // ������ ��� %s%%
	eMsgEffectRangeUp					, // �����Ÿ� %s���� // 3174
	eMsgEffectReflectDamagePlus			, // ������ �ݻ� %s
	eMsgEffectAbsorbElementalDamage		, // �Ӽ� ������ ��� %s%%
	eMsgEffectAbsorbPartyPhs			, // %d%%��ŭ�� ��Ƽ���� ���� �������� ���
	eMsgEffectMinusPercentHPforTime		, // ���� �ð����� %s%%��ŭ ���������� �ڽ��� HP ����
	eMsgEffectQuickDash					, // %s��ŭ�� �Ÿ��� ���������� �뽬
	eMsgEffectPlusPercentDefense		, // %s%%��ŭ�� ���� ���

	eMsgEffectCriticalStrikeRate	=	3181, // %sȮ���� ���ݷ� %s%%����
	eMsgEffectCriticalStrike			, // %sȮ���� ���ݷ� %s����
	eMsgEffectWeaponMastery				, // %s ���ݷ� %s
	eMsgEffectWeaponMastery2			, // %s ���ݷ� %s, ���ݼӵ� %s����
	eMsgEffectDamagePlus				, // ���ݷ� %s - %s ����
	eMsgEffectDamagePlusRate			, // ���ݷ� %s%% - %s%% ����
	eMsgEffectDamageMinus				, // ���ݷ� %s - %s ����
	eMsgEffectDamageMinusRate			, // ���ݷ� %s%% - %s%% ����
	eMsgEffectFireDamagePlus			, // ȭ�� ���ݷ� %s - %s ����
	eMsgEffectFireDamagePlusRate		, // ȭ�� ���ݷ� %s%% - %s%% ����
	eMsgEffectFireDamageMinus			, // ȭ�� ���ݷ� %s - %s ����
	eMsgEffectFireDamageMinusRate		, // ȭ�� ���ݷ� %s%% - %s%% ����
	eMsgEffectColdDamagePlus			, // �ñ� ���ݷ� %s - %s ����
	eMsgEffectColdDamagePlusRate		, // �ñ� ���ݷ� %s%% - %s%% ����
	eMsgEffectColdDamageMinus			, // �ñ� ���ݷ� %s - %s ����
	eMsgEffectColdDamageMinusRate		, // �ñ� ���ݷ� %s%% - %s%% ����
	eMsgEffectLightningDamagePlus		, // ���� ���ݷ� %s - %s ����
	eMsgEffectLightningDamagePlusRate	, // ���� ���ݷ� %s%% - %s%% ����
	eMsgEffectLightningDamageMinus		, // ���� ���ݷ� %s - %s ����
	eMsgEffectLightningDamageMinusRate	, // ���� ���ݷ� %s%% - %s%% ����
	eMsgEffectPoisonDamagePlus			, // �� ���ݷ� %s - %s ����
	eMsgEffectPoisonDamagePlusRate		, // �� ���ݷ� %s%% - %s%% ����
	eMsgEffectPoisonDamageMinus			, // �� ���ݷ� %s - %s ����
	eMsgEffectPoisonDamageMinusRate		, // �� ���ݷ� %s%% - %s%% ����
	eMsgEffectDefenceIgnoreDamage		, // ������ ������ ���ݷ� %s - %s
	eMsgEffectSkillDamagePlus			, // %s�� ���ݷ� %s - %s �߰�
	eMsgEffectDefenceMinusDamage		, // ���� %s�� ���ҽ�Ų ���ݷ�
	eMsgEffectTPBurn					, // TP������ %s�� %d%%�� ���·����� ��ȯ 
	eMsgEffectTPBurn2					, // TP %s ����// 3209
	
	eMsgEffectFireResistPlus		=	3211, // ȭ�� ���׷� %s ����
	eMsgEffectFireResistPlusRate		, // ȭ�� ���׷� %s%% ����
	eMsgEffectFireResistMinus			, // ȭ�� ���׷� %s ����    //fors_debug ���Ч���б���Ϣ�ĵط�
	eMsgEffectFireResistMinusRate		, // ȭ�� ���׷� %s%% ����
	eMsgEffectColdResistPlus			, // �ñ� ���׷� %s ����
	eMsgEffectColdResistPlusRate		, // �ñ� ���׷� %s%% ����
	eMsgEffectColdResistMinus			, // �ñ� ���׷� %s ����
	eMsgEffectColdResistMinusRate		, // �ñ� ���׷� %s%% ����
	eMsgEffectLightningResistPlus		, // ���� ���׷� %s ����
	eMsgEffectLightningResistPlusRate	, // ���� ���׷� %s%% ����
	eMsgEffectLightningResistMinus		, // ���� ���׷� %s ����
	eMsgEffectLightningResistMinusRate	, // ���� ���׷� %s%% ����
	eMsgEffectPoisonResistPlus			, // �� ���׷� %s ����
	eMsgEffectPoisonResistPlusRate		, // �� ���׷� %s%% ����
	eMsgEffectPoisonResistMinus			, // �� ���׷� %s ����
	eMsgEffectPoisonResistMinusRate		, // �� ���׷� %s%% ����
	eMsgEffectAllResistPlus				, // ��� ���׷� %s ����
	eMsgEffectAllResistPlusRate			,
	eMsgEffectAllResistMinus			, // ��� ���׷� %s ����
	eMsgEffectAllResistMinusRate		, // 3230

	eMsgEffectDamageTP					, // Duration���� param1 ��ŭ�� TP ������ 
	eMsgEffectDOTbyDice					, // functionȮ���� duration���� param1~param2 �� ������
	eMsgEffectHealPlus					, // HPȸ���� param1��ŭ�� �߰�ȸ��
	eMsgEffectRecoverTPPlus				, // TPȸ���� param1��ŭ�� �߰�ȸ��

	
	eMsgEffectMusclePlus			=	3236, // ������ ��ũ�� %s ����
	eMsgEffectNervesPlus				, // �Ű��� ��ũ�� %s ����
	eMsgEffectHeartPlus					, // ������ ��ũ�� %s ����
	eMsgEffectMindPlus					, // ������ ��ũ�� %s ����
	eMsgEffectMuscleMinus				, // ������ ��ũ�� %s ����
	eMsgEffectNervesMinus				, // �Ű��� ��ũ�� %s ����
	eMsgEffectHeartMinus				, // ������ ��ũ�� %s ����
	eMsgEffectMindMinus					, // ������ ��ũ�� %s ���� 
	eMsgEffectAllStatPlus				, // ��� ��ũ�� %s ����
	eMsgEffectAllStatPlusRate			,
	eMsgEffectAllStatMinus				, // ��� ��ũ�� %s ����
	eMsgEffectAllStatMinusRate			, // 3247

	eMsgEffectWeaponMastery3		=	3251, // %s ���ݼ��� %s����
	eMsgEffectAttackRatePlus			, // ���ݼ��� %s ����
	eMsgEffectAttackRatePlusRate		, // ���ݼ��� %s%% ����
	eMsgEffectAttackRateMinus			, // ���ݼ��� %s ����
	eMsgEffectAttackRateMinusRate		, // ���ݼ��� %s%% ����
	eMsgEffectDodgeRatePlus				, // ȸ�� %s ����
	eMsgEffectDodgeRatePlusRate			, // ȸ�� %s%% ����
	eMsgEffectDodgeRateMinus			, // ȸ�� %s ����
	eMsgEffectDodgeRateMinusRate		, // ȸ�� %s%% ����
	eMsgEffectACPlus					, // �� %s ����
	eMsgEffectACPlusLimitLevel			, // ���� �������� %s%% ����
	eMsgEffectACPlusRate				, // �� %s%% ����
	eMsgEffectACMinus					, // �� %s ����
	eMsgEffectACMinusLimitLevel			, // ���� �������� %s%% ����
	eMsgEffectACMinusRate				, // �� %s%% ����
	eMsgEffectMaxHPPlus					, // �ִ� HP %s ����
	eMsgEffectMaxHPPlusRate				, // �ִ� HP %s%% ����
	eMsgEffectMaxHPMinus				, // �ִ� HP %s ����
	eMsgEffectMaxHPMinusRate			, // �ִ� HP %s%% ����
	eMsgEffectHPRecoveryPlus			, // HP ȸ�� %s ����
	eMsgEffectHPRecoveryPlusRate		, // HP ȸ�� %s%% ����
	eMsgEffectHPRecoveryMinus			, // HP ȸ�� %s ����
	eMsgEffectHPRecoveryMinusRate		, // HP ȸ�� %s%% ����
	eMsgEffectMaxTPPlus					, // �ִ� TP %s ����
	eMsgEffectMaxTPPlusRate				, // �ִ� TP %s%% ����
	eMsgEffectMaxTPMinus				, // �ִ� TP %s ����
	eMsgEffectMaxTPMinusRate			, // �ִ� TP %s%% ����
	eMsgEffectTPRecoveryPlus			, // TP ȸ�� %s ����
	eMsgEffectTPRecoveryPlusRate		, // TP ȸ�� %s%% ����
	eMsgEffectTPRecoveryMinus			, // TP ȸ�� %s ����
	eMsgEffectTPRecoveryMinusRate		, // TP ȸ�� %s%% ����
	eMsgEffectCostTP					, // TP �Ҹ� %s ����
	eMsgEffectCostTPRate				, // TP �Ҹ� %s%% ����
	eMsgEffectBonusExp					, // ���� ����ġ %s ����
	eMsgEffectBonusExpRate				, // ���� ����ġ %s%% ����
	eMsgEffectEtcSkillDisp1				, // ����, �Ǿ�� ���� ������ �鿪
	eMsgEffectEtcSkillDisp2				, // ����, ����, �Ǿ�� ���� ������ �鿪
	eMsgEffectEtcSkillDisp3				, // ����, ����, ����, �Ǿ�� ���� ������ �鿪
	eMsgEffectPlusDefense				, // %s��ŭ�� ���� ���

	
	eMsgEffectResetState			=	3291, // ��ũ�� ����Ʈ �ʱ�ȭ
	eMsgEffectResetSkill				, // ��ų ����Ʈ �ʱ�ȭ
	eMsgEffectPreventHPRecovery			, // HP �ڵ� ȸ�� ����
	eMsgEffectPreventTPRecovery			, // TP �ڵ� ȸ�� ����
	eMsgEffectSkillLevelUp				, // %s ���� %s ����
	eMsgEffectDefaunt					, // Ÿ���� ������ Ȯ�� ���� // 3296
	eMsgEffectRefinePlus				, // ���� ��ȭ���õ�� %s ���
	eMsgEffectEnhanceHardnessOfArmor	, // ������ ������������ ����
	eMsgEffectFixedDamagePlus			, // ���� ������ %d �߰�
	eMsgEffectDamageBonusForNextAttack	, // 1ȸ ���ݵ����� %s%% ���

	eMsgHotKeyInfoTitle				= 3301,
	eMsgHotKeyInfoForward				, // �� : W
	eMsgHotKeyInfoBackward				, // �� : S
	eMsgHotKeyInfoLeft					, // �� : A
	eMsgHotKeyInfoRight					, // �� : D
	eMsgHotKeyInfoRun					, // �޸��� / �ȱ� : Z
	eMsgHotKeyInfoSitDown				, // �ɱ� / ���� : X
	eMsgHotKeyInfoCamera				, // ī�޶� ���� : F12
	eMsgHotKeyInfoDefaultCamera			, // ī�޶� �⺻ ���� : Instert, ���콺 �� ��ư
	eMsgHotKeyInfoPointView				, // 1��Ī,3��Ī ��ȯ : F11
	eMsgHotKeyInfoZoomIn				, // �� ��-
	eMsgHotKeyInfoZoomOut				, // �� �ƿ�+
	eMsgHotKeyInfoLeft2					, // �� : <-
	eMsgHotKeyInfoRight2				, // �� : ->
	eMsgHotKeyInfoSelectTarget			, // ����� �� ���� : E
	eMsgHotKeyInfoAttack				, // ���� : R
	eMsgHotKeyInfoSelectMember			, // ������ ���� ���� : T
	eMsgHotKeyInfoPickUp				, // �ݱ� : F
	eMsgHotKeyInfoPreviousQuick			, // ���� ���� : -
	eMsgHotKeyInfoNextQuick				, // ���� ���� : =
	eMsgHotKeyInfoQuickBar1				, // ���� 1 ���� : Shift + 1
	eMsgHotKeyInfoQuickBar2				, // ���� 2 ���� : Shift + 2
	eMsgHotKeyInfoQuickBar3				, // ���� 3 ���� : Shift + 3
	eMsgHotKeyInfoQuickBar4				, // ���� 4 ���� : Shift + 4
	eMsgHotKeyInfoQuickBar5				, // ���� 5 ���� : Shift + 5
	eMsgHotKeyInfoQuickSlot1			, // ������ 1 ��� : 1
	eMsgHotKeyInfoQuickSlot2			, // ������ 2 ��� : 2
	eMsgHotKeyInfoQuickSlot3			, // ������ 3 ��� : 3
	eMsgHotKeyInfoQuickSlot4			, // ������ 4 ��� : 4
	eMsgHotKeyInfoQuickSlot5			, // ������ 5 ��� : 5
	eMsgHotKeyInfoQuickSlot6			, // ������ 6 ��� : 6
	eMsgHotKeyInfoQuickSlot7			, // ������ 7 ��� : 7
	eMsgHotKeyInfoQuickSlot8			, // ������ 8 ��� : 8
	eMsgHotKeyInfoQuickSlot9			, // ������ 9 ��� : 9
	eMsgHotKeyInfoQuickSlot0			, // ������ 0 ��� : 0
	eMsgHotKeyInfoWholeChat				, // ��ü��ȭ
	eMsgHotKeyInfoWhisper				, // �ӼӸ�
	eMsgHotKeyInfoPartyChat				, // ��Ƽ ��ȭ
	eMsgHotKeyInfoAshuramChat			, // �ƽ��� ��ȭ
	eMsgHotKeyInfoRegisterAddress		, // ģ�����
	eMsgHotKeyInfoResponseWhisper		, // �ӼӸ� ���� : V
	eMsgHotKeyInfoActiveChat			, // ä��â Ȱ�� : Enter
	eMsgHotKeyInfoAshuramMemberGrade	, // �ƽ��� ������ ��� ���� : /�ƽ������ '�̸�' '���'
	eMsgHotKeyInfoAshuramNotify			, // �ƽ��� �������� ���� : /�������� '��������'
	eMsgHotKeyInfoAshuramHomepage		, // �ƽ��� Ȩ������ ���� : /Ȩ������ 'Ȩ�ּ�'
	eMsgHotKeyInfoCharacterInfo			, // ĳ���� ����â
	eMsgHotKeyInfoInventory				,
	eMsgHotKeyInfoQuest					,
	eMsgHotKeyInfoSkill					,
	eMsgHotKeyInfoOption				,
	eMsgHotKeyInfoCommand				,
	eMsgHotKeyInfoGuild					,
	eMsgHotKeyInfoAddress				,
	eMsgHotKeyInfoHelp					,
	eMsgHotKeyInfoBalloon				, // ǳ����
	eMsgHotKeyInfoNameHide				, // �̸� �����
	eMsgHotKeyInfoUIHide				, // UI ��� �����
	eMsgHotKeyInfoMiniMap				, // �̴ϸ�
	eMsgHotKeyInfoScreenShot			, // ��ũ����
	eMsgHotKeyInfoTrade					, // ��ȯ
	eMsgHotKeyInfoCloseWin				, // â�ݱ� : ESC // 3361
	eMsgHotKeyTilte1					, // �ൿ����
	eMsgHotKeyTilte2					, // �����Թ�
	eMsgHotKeyTilte3					, // ä�ð���
	eMsgHotKeyTilte4					, // ���������
	eMsgHotKeyChangeChatWndStyle		, // ä��â ��Ÿ�� ����

	eMsgPremiumReqFail				= 4001, // ���� ��û�� �����߽��ϴ�.
	
	eMsgPremiumInfoBuyMinCount			, // �ּ� %d�� ����
	eMsgPremiumInfoBuyDiscount			, // %d�� ���� �� %d%% ����
	
	eMsgPremiumBuyQuestion			= 4010, // %s %s���� %sĳ���� �����Ͻðڽ��ϱ�?
	eMsgPremiumBuyOK					, // %s��(��) %sĳ���� �����߽��ϴ�.
	eMsgPremiumReqPay					, // %ĳ���� �����Ͻðڽ��ϱ�?
	eMsgPremiumPaySystemErr				, // Ÿ�� ���� ������ �������� �ʽ��ϴ�. ��� �Ŀ� �ٽ� �õ��� �ֽñ� �ٶ��ϴ�.
	eMsgPremiumPaySystemErr2			, // Ÿ�� ���� ���� ������ ���� ���α׷� �ʱ�ȭ�� �����߽��ϴ�.
	eMsgPremiumPaySystemErr3			, // Ÿ�� ���� ���� ���� �ʱ�ȭ�� �����߽��ϴ�.
	eMsgPremiumPaySystemErr4			, // Ÿ�� ���� ���� ������ ���� ���α׷� �˻��� �����߽��ϴ�.
	eMsgPremiumPaySystemErr5			, // Ÿ�� ���� ������ �� �� ���� ������ ��������ϴ�.
	eMsgPremiumReqInvenExpandBuy		, // �����Ͻðڽ��ϱ�? �̹� �������� ��� �籸�Խ� ��ȿ�Ⱓ�� �Ѵ� �� Ȯ��˴ϴ�.
	eMsgPremiumReq2GradeInit			, // 2�� ������ �ʱ�ȭ �մϴ�. 9900 Ÿ�ϰ� �Һ�Ǹ� 2�� ������ �ʱ�ȭ �Ǹ� 2�� ���� ����Ʈ�� �ٽ� �����ؾ� �մϴ�.
	eMsgPremiumReq2GradeInitErr			, // 2�� ������ �� ���¿����� �ʱ�ȭ�� �����մϴ�.
	eMsgPremiumReq2GradeInitOK			, // 2�� ������ �Ϸ��Ͽ����ϴ�.
	eMsgPremiumReq2GradeInitErr2		, // ������ �������� ��� ������ �ٽ� ������ �ֽʽÿ�
	eMsgPremiumReqChkraInitQuestion		, // ��й踦 ���� ��ũ�� �ʱ�ȭ �ϰڽ��ϱ�?  (4023)
	eMsgPremiumReqSkillInitQuestion		, // ��й踦 ���� ��ų�� �ʱ�ȭ �ϰڽ��ϱ�? (4024)
	eMsgPremiumReqChkraSkillQuestion	, // ��й踦 ���� ��ũ�� �� ��ų�� �ʱ�ȭ �ϰڽ��ϱ�? (2025)
	eMsgPremiumReqResultOKay			, // ���������� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect1				, //4027	0	0	0	�κ��丮 Ȯ�� ����� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect2				, //4028	0	0	0	���λ��� Ȯ�� ����� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect3				, //4029	0	0	0	���Ǿ� �ڵ� ���� ����� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect4				, //4030	0	0	0	�ƴ��ٹ� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect5				, //4031	0	0	0	��Ʈ�� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect6				, //4032	0	0	0	��� ��ũ�� ���ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect7				, //4033	0	0	0	�ƴ��ٹ� �ٷ����� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect8				, //4034	0	0	0	��Ʈ�� �ٷ����� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect9				, //4035	0	0	0	��� �ٷ����� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect10				, //4036	0	0	0	�÷�Ƽ�� �ٷ����� ȿ���� ����Ǿ����ϴ�.
	eMsgPremiumItemEffect11				, //4037	0	0	0	����Ⱓ�� �����̾� ���� �̿� �������� Ȯ���Ͻ� �� �ֽ��ϴ�.
	eMsgPremiumItemMonsterEventError	, //4038	���� ��ȯ �ֹ����� �Ĺ̸� ���������� ����� �� �ֽ��ϴ�.
	eMsgPremiumItemChaturangaEnter		, //4039	���������� �����մϴ�.
	eMsgPremiumItemChaturangaEnterError	, //4040	30���� �̻��� �÷��̾ ���������� ������ �� �ֽ��ϴ�.
	eMsgPremiumItemChaturangaEnterError2, //4041	30���� �̻��� �÷��̾ ���������� ������ �� �ֽ��ϴ�.
	eMsgEventItemUseOK					, //4042	�̺�Ʈ ������ '���̿���'�� �����Ͽ����ϴ�.
	eMsgEventItemUseError				, //4043	�� �������� �̺�Ʈ NPC�� ���� ������ �� �ֽ��ϴ�.

	eMsgInventoryExpansionDisabled		, //4044	0	0	0	�κ��丮 Ȯ�� ����� ���� �Ǿ����ϴ�.	Inventory expansion has been disabled.
	eMsgCloseInvendowWindowTry			, //4045	0	0	0	�κ��丮 â�� ������ �ٽ� �õ��� �ֽʽÿ�.	Close the inventory window and try again.
	eMsgPrivateStoreExpansionDisabled	, //4046	0	0	0	���λ��� Ȯ�� ����� ���� �Ǿ����ϴ�.	Private store expansion has been disabled.
	eMsgClosePrivateStoreTry			, //4047	0	0	0	���λ��� â�� ������ �ٽ� �õ��Ͽ� �ֽʽÿ�.	Close the private store window and try again.
	eMsgAutomaticRupiaDisabled			, //4048	0	0	0	���Ǿ� �ڵ� ���� ����� ���� �Ǿ����ϴ�	Automatic rupia acquisition has been disabled.
	eMsgAnubabaEffectDisabled			, //4049	0	0	0	�ƴ��ٹ� ȿ���� ���� �Ǿ����ϴ�.	Anubaba effect has been disabled.
	eMsgAtmanEffectDisabled				, //4050	0	0	0	��Ʈ�� ȿ���� ���� �Ǿ����ϴ�.	Atman effect has been disabled.
	eMsgAllChakraUpgradeDisabled		, //4051	0	0	0	��� ��ũ�� ���ȿ���� ���� �Ǿ����ϴ�.	All chakra upgrade effect has been disabled.
	eMsgInventoryExpansionEnabled		, //4052	0	0	0	�κ��丮 Ȯ�� ����� ���� �Ǿ����ϴ�.	Inventory expansion has been enabled.
	eMsgPrivateStoreExpansionEnabled	, //4053	0	0	0	���λ��� Ȯ�� ����� ���� �Ǿ����ϴ�.	Private store expansion has been enabled.
	eMsgAutomaticRupiaEnabled			, //4054	0	0	0	���Ǿ� �ڵ� ���� ����� ���� �Ǿ����ϴ�.	Automatic rupia acquisition has been enabled.
	eMsgAnubabaEffectEnabled			, //4055	0	0	0	�ƴ��ٹ� ȿ���� ���� �Ǿ����ϴ�.	Anubaba effect has been enabled.
	eMsgAtmanEffectEnabled				, //4056	0	0	0	��Ʈ�� ȿ���� ���� �Ǿ����ϴ�.	Atman effect has been enabled.
	eMsgAllChakraUpgradeEnabled			, //4057	0	0	0	��� ��ũ�� ���ȿ���� ���� �Ǿ����ϴ�.	All chakra upgrade effect has been enabled.
	eMsgPremiumServiceName				, //4058	0	0	0	�����̾� ���񽺸�	Premium Service Name
	eMsgWordInUse						, //4059	0	0	0	��뿩��	In Use?
	eMsgWordExpireDate					, //4060	0	0	0	����Ⱓ	Expire Date
	eMsgWordDDay						, //4061	0	0	0	D-day	D-Day
	eMsgWordEffect						, //4062	0	0	0	ȿ��	Effect
	eMsgWordInvenExpansion				, //4063	0	0	0	�κ��丮 Ȯ��	Inventory Expansion
	eMsgWordPrivateStoreExpansion		, //4064	0	0	0	���λ��� Ȯ��	Private Store Expansion
	eMsgAutomaticRupiaAcquisition		, //4065	0	0	0	���Ǿ� �ڵ�����	Automatic Rupia Acquisition
	eMsgWordAnubabaCharm				, //4066	0	0	0	�ƴ��ٹ� ����	Anubaba Charm
	eMsgWordAtmanCharm					, //4067	0	0	0	��Ʈ�� ����	Atman Charm
	eMsgAllChakraPlus15					, //4068	0	0	0	��� ��ũ�� 15 ����	All Chakra +15
	eMsgNotPurchased					, //4069	0	0	0	�̱���	Not Purchased
	eMsgWordInUseing					, //4070	0	0	0	�����	In Use
	eMsgWordExpired						, //4071	0	0	0	�Ⱓ����	Expired
	eMsgWordTotal						, //4072	0	0	0	�� ��	Total
	eMsgExplanPremiumItem01				, //4073	0	0	0	������� ��ȿ�ð��� ���� �ִ� �����۸� �Ǹ��� �� �ֽ��ϴ�.	You can only sell items that have not been used and not expired
	eMsgExplanPremiumItem02				, //4074	0	0	0	�ּ� �ѹ���(250��) �����θ� �Ǹ��� �� �ֽ��ϴ�	You can only sell in packs of 250.
	eMsgExPlanPremiumItem03				, //4075	0	0	0	\n���Ű��: ���� %d �Һ� %d\n	\nSales Result: Own %d Sold %d\n
	eMsgExPlanPremiumItem04				, //4076	0	0	0	ĳ���� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�.	Usable items for upgrading the character. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem05				, //4077	0	0	0	���Ǽ� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�.	Usable items for upgrading the convenience. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem06				, //4078	0	0	0	��ɼ� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�.	Usable items for upgrading the functionality. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem07				, //4079	0	0	0	�����̾� �ٷ��� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�.	Premium package items. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem08				, //4080	0	0	0	Ư�� ����� ���� �Ҹ� �����۵� �Դϴ�. ������ ���Ͻô� �������� ������ �Ǵ� ���Ź�ư�� Ŭ���Ͻø�, ������ �����մϴ�.	Usable items for special features. You can purchase by clicking the item's icon or the purchase button.
	eMsgExPlanPremiumItem09				, //4081	0	0	0	%s \n�ּ� %d�� ����(%d�� ���� �� 20������)	%s \nPurchase minimum of %d (20% discount when purchasing %d or more)
	eMsgPriceToTaney					, //4082	0	0	0	����: %s Ÿ��	Price: %s Taney
	eMsgPage							, //4083	0	0	0	(Page %d/%d)	(Page %d/%d)
	eMsgExPlanPremiumItem10				, //4084	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem11				, //4085	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. ��Ʈ�� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem12				, //4086	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem13				, //4087	0	0	0	��� ������ �ֹ��� 1��\n������ �ֹ��� 20��\n������ ������ 10��\n���� ��ɼ� 5��\n�̺�Ʈ�Ⱓ�� ���� �̺�Ʈ ������ ����\n\n30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��\n4. ��� ��ũ�� 15 ���	1 high quality revival scroll\n20 revival scroll\n10 electronic board item\n5 strategy command\nEvent item when used during event period\nFollowing effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms\n4. All chakra +15
	eMsgExPlanPremiumItem14				, //4088	0	0	0	������� 1��\n(�Ĺ̸��������� �������� ���� ��ȯ����)\n�����ġ 2��\n(������� �������� ����������)\n�������� ����� 2��\n(���������� �ٷ� ���尡��)\n�̺�Ʈ ��Ÿ�� �ϸ�Ÿ 	1 magic lamp\n(Can summon random boss monster in Pamir area)\n2 magic hammer\n(Repair all equipped items)\n2 Chaturanga entrance ticket\n(Can enter Chaturanga)\n2 packs of event Utara Amrita\2 high quality revival scroll
	eMsgSkillInitialized				, //4089	0	0	0	��ų�� �ʱ�ȭ �Ǿ����ϴ�.	Skill has been initialized.
	eMsgChakraInitialized				, //4090	0	0	0	��ũ�� �ʱ�ȭ �Ǿ����ϴ�.	Chakra has been initialized.
	eMsgSkillChakraInitialized			, //4091	0	0	0	��ų �� ��ũ�� �ʱ�ȭ �Ǿ����ϴ�.	Skill and Chakra has been initialized.
	eMsgChakraCannotUpgrade				, //4092	0	0	0	��ũ�� ���ѿ� �ɷ� ��ũ�� �ø� �� �����ϴ�.	Chakra can't be upgraded due to maximum limit.
	eMsgSerialNumber					, //4093	0	0	0	�Ϸ� ��ȣ	Serial Number
	eMsgEnlistmentNotice				, //4094	0	0	0	[�Կ� ������]�� 	of [Enlistment Notice]
	eMsgMustHaveGodToView				, //4095	0	0	0	�ֽ��� �־�߸� �����Ͻ� �� �ֽ��ϴ�.	You must have a God to view this.
	eMsgExPlanPremiumItem15				, //4096	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem16				, //4097	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. ��Ʈ�� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem17				, //4098	0	0	0	30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��	Following effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms
	eMsgExPlanPremiumItem18				, //4099	0	0	0	��� ������ �ֹ��� 1��\n������ �ֹ��� 20��\n������ ������ 10��\n���� ��ɼ� 5��\n�̺�Ʈ�Ⱓ�� ���� �̺�Ʈ ������ ����\n\n30�ϰ� ������ ȿ���߻�\n1. �κ��丮 �� ���λ��� ���� Ȯ��\n2. ���Ǿ� �ڵ� ����\n3. �ƴ��ٹ� �� ��Ʈ�� ������ ȿ��\n4. ��� ��ũ�� 15 ���	1 high quality revival scroll\n20 revival scroll\n10 electronic board item\n5 strategy command\nEvent item when used during event period\nFollowing effects for 30 days.\n1. Expansion of inventory and private store space.\n2. Automatic acquisition of rupia.\n3. Effect of Anubaba and Atman charms\n4. All chakra +15
	eMsgExPlanPremiumItem19				, //4100	0	0	0	������� 1��\n(�Ĺ̸��������� �������� ���� ��ȯ����)\n�����ġ 2��\n(������� �������� ����������)\n�������� ����� 2��\n(���������� �ٷ� ���尡��)\n�̺�Ʈ ��Ÿ�� �ϸ�Ÿ 250�� 2����\n��� ������ �ֹ��� 2��	1 magic lamp\n(Can summon random boss monster in Pamir area)\n2 magic hammer\n(Repair all equipped items)\n2 Chaturanga entrance ticket\n(Can enter Chaturanga)\n2 packs of event Utara Amrita\2 high quality revival scroll
	eMsgExPlanPremiumItem20				, //4101	0	0	0	"6�� 5õ �÷� LCD / ��� �̾��� '���̿��� TMP-1000'>>http://www.ioneit.com"
	eMsgExPlanPremiumItem21				, //4102	0	0	0	�� �������� �̵��� �� �����ϴ�. �̺�Ʈ NPC�� ���� �����ϼ���.
	eMsgExPlanPremiumItem22				, //4103	0	0	0	%s \n�ּ� %d�� ����(%d�� ���� �� 10������)	%s \nPurchase minimum of %d (10% discount when purchasing %d or more)
	eMsgReqUsingItem					, //4104	���� �������� ����Ͻðڽ��ϱ�?
	eMsgExPlanPremiumItem23				, //4105	0	0	0	8ĭ�� �κ��丮 ���� �ʿ�
	eMsgReQuestItemUse1					, //4106	����Ʈ�� �ʱ�ȭ �Ͻðڽ��ϱ�?(����Ʈ �ٽ��ϱ�1��, ������ ��1�� �ʿ�)
	eMsgReQuestItemUse2					, //4107	����Ʈ�� �ʱ�ȭ �Ͻðڽ��ϱ�?(����Ʈ �ٽ��ϱ�1��, ������ ��2�� �ʿ�)


	eMsgTaskQuestMaraBloodSellOK	= 5001, // ������ ���׷����Ǹ��߽��ϴ�.
	eMsgTaskQuestMaraSolutionMakingOK	, // ������ ������ �����߽��ϴ�.
	eMsgTaskQuestPanacaMakingOK			, // �ĳ�ī���� �����߽��ϴ�.
	eMsgTaskQuestChaturangaPieceOK		, // ī�߸� �ռ��߽��ϴ�.
	eMsgTaskQuestWeaponMakingOK			, // ���⸦ �����߽��ϴ�.
	eMsgTaskQuestItemMakingOK			, // ��ǰ�� �����߽��ϴ�.
	eMsgTaskQuestItemSeparationOK		, // ��ǰ�� �и��߽��ϴ�. // 5007
	eMsgTaskQuestNullEventOK			, // �����մϴ�. �̺�Ʈ�� ��÷ �Ǿ����ϴ�. (�̺�Ʈ�� �����ϼ̽��ϴ�.)
	eMsgTaskQuestMerryXMas				, // �޸� ũ��������!!!
	eMsgTaskQuestEventBoxOnenOK			, // �������� ����߽��ϴ�.
	eMsgTaskQuestCannotFindInfo		= 5951	, // ����Ʈ ������ ã�� �� �����ϴ�.
	eMsgTaskQuestNPCIDErr				, // ������ NPC�� ������ �� ���� ����Ʈ�Դϴ�.
	eMsgTaskQuestNeedItemErr			, // �ʿ��� �������� �����ϴ�
	eMsgTaskQuestNeedMoneyErr			, // �ʿ��� ���Ǿư� �����մϴ�.
	eMsgTaskQuestConditionErr			, // �׽�ũ ����Ʈ�� �ϱ� ���� ���� �����
	eMsgTaskQuestFail					, // �׽�ũ ���� 
	eMsgTaskQuestRateErr				, // Ȯ���� ���� �۾��� �����߽��ϴ�. // 5957
	eMsgTaskQuestNoEventErr				,  // �˼��մϴ�. ���� �̰������� �̺�Ʈ�� ���� �ʽ��ϴ�.
	eMsgTaskQuestKarmaErr				,	// ī���� ��ġ�� ���ǿ� ���� �ʽ��ϴ�. 
	eMsgTaskQuestLevelErr				,	// ���࿡ �ʿ��� ������ �����մϴ�.
	
	eMsgRefineErr1					= 6000,	// ������ ���õǾ� �ִ� �Ӽ��� ������ϴ�. �����Ͻðڽ��ϱ�?
	eMsgRefineErr2						,	// ������ ���� ��ī�� ������Ḧ ����Ͻ� �ʿ䰡 �����ϴ�.

	eMsgItemBuyMsg1					= 6002,	//0	0	0	%s %s ���� %s ���Ǿƿ� ���� �Ͻðڽ��ϱ�?
	eMsgItemBuyMsg2						,	//0	0	0	%s %s ���� %s ĳ���� ���� �Ͻðڽ��ϱ�?
	eMsgItemSellMsg1					,	//0	0	0	%s %s ���� %s ���Ǿƿ� �Ǹ� �Ͻðڽ��ϱ�?
	eMsgItemSellMsg2						//0	0	0	%s %s ���� %s ĳ���� �Ǹ� �Ͻðڽ��ϱ�?

} eMsgInfo;

#endif