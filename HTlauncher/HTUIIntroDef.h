#define _DEFAULT_CURSOR				0

// 다아알로그 상태
#define _DLG_STATUS_LOADING			0	// 처음뜨는 화면
#define _DLG_STATUS_LOGIN			1	// 로그인다이알로그
#define _DLG_STATUS_SERVER_SELECT	2	// 서버 선택하는 화면
#define _DLG_STATUS_CHAR_SELECT		3	// 캐릭터 선택하는 화면
#define _DLG_STATUS_NEW_CHARTRIBE	4	// 캐릭터 생성하는 화면
#define _DLG_STATUS_CHAR_INFO		5	// 캐릭터 생성하는 화면

enum // 로그인 관련 메시지
{
	_LOGIN_OK							= 101,
	_LOGIN_USERID_ERROR					= 102,
	_LOGIN_PASSWORD_ERROR				= 103,
	_LOGIN_SERVER_REPLY_ERROR			= 104,
	_LOGIN_SERVER_CONNECT_FEE_ERROR		= 105,
	_LOGIN_REUSER_ERROR					= 106,
	_LOGIN_USETIME_ERROR				= 107,
	_LOGIN_UNKNOWN_ERROR				= 108,
	_LOGIN_SERVER_CONNECT_ERROR			= 109,	
};

enum // 월드 선택관련 메시지
{
	_SELECTWORLD_MOVETO_ZONESERVER		= 101,
	_SELECTWORLD_WORLDLIST				= 102,
	_SELECTWORLD_NETWORKERROR			= 103,
	_SELECTWORLD_LOGOUT					= 104,
};

enum // 캐릭터 관련 메시지
{
	_CHAR_CHARLIST						= 101,
	_CHAR_EXITZONE						= 102,
	_CHAR__NETWORKERROR					= 103,
};

//#define _MESSAGE_NONE							_T(" ")
//#define _MESSAGE_LOGIN							_T("아이디/패스워드를 입력해 주십시오.")
//#define _MESSAGE_WORLDSELECT					_T("접속할 서버를 선택해 주십시오.")
//#define _MESSAGE_ZONESERVER_CONNECTING			_T("존서버에 연결중입니다.")
//#define _MESSAGE_CHAR_INFO_REQUEST				_T("서버에 캐릭터 정보를 요청하고 있습니다.")
//
//
//#define _LOGIN_OK_TEXT							_T("로그인 되었습니다.")
//#define _LOGIN_USERID_ERROR_TEXT				_T("존재하지 않는 사용자 ID 입니다.")
//#define _LOGIN_PASSWORD_ERROR_TEXT				_T("올바르지 않은 사용자 암호입니다.")
//#define _LOGIN_SERVER_REPLY_ERROR_TEXT			_T("서버가 응답이 없습니다.")
//#define _LOGIN_SERVER_CONNECT_FEE_ERROR_TEXT	_T("과금관련 에러로 접속이 불가합니다.")
//#define _LOGIN_REUSER_ERROR_TEXT				_T("이미 로그인 된 사용자입니다.")
//#define _LOGIN_USETIME_ERROR_TEXT				_T("죄송합니다. 지금은 이용 시간이 아닙니다.")
//#define _LOGIN_UNKNOWN_ERROR_TEXT				_T("알 수 없는 에러 발생가 발생했습니다.")
//#define _LOGIN_SERVER_CONNECT_ERROR_TEXT		_T("서버에 연결되지 않았습니다.")
//#define _LOGOUT_TEXT							_T("로그아웃되었습니다.")
//
//
//#define _MESSAGE_CHARLIST_ERROR					_T("잘못된 캐릭터 리스트를 받았습니다.")
//
//
//#define _SELECTWORLD_MOVETO_ZONESERVER_TEXT		_T("존서버에 접속을 요청합니다.")
//#define _SELECTWORLD_WORLDLIST_TEXT				_T("월드에 관한 정보 리스트를 받았습니다.")
//#define _SELECTWORLD_NETWORKERROR_TEXT			_T("네트워크 에러가 발생하였습니다.")


// UI에서 사용하는 비트맵 번호
enum 
{
	UI_BLACK,
	UI_DKGRAY,
	UI_GRAY,
	UI_IVORY,
	UI_PINK,
	UI_INTRO_TANTRA_LOGO,
	UI_INTRO_TANTRA_PIC,
	UI_INTRO_TANTRA_LETTER,
	UI_LOGIN_TITLE,
	UI_SERVER_SELECT_TITLE,
	UI_CHAR_SELECT_TITLE,
	UI_CHARFACE_GAN1_NORMAL,
	UI_CHARFACE_GAN1_SELECT,
	UI_CHARFACE_GAN2_NORMAL,
	UI_CHARFACE_GAN2_SELECT,
	UI_CHARFACE_GAN3_NORMAL,
	UI_CHARFACE_GAN3_SELECT,
	UI_CHARFACE_NAG1_NORMAL,
	UI_CHARFACE_NAG1_SELECT,
	UI_CHARFACE_NAG2_NORMAL,
	UI_CHARFACE_NAG2_SELECT,
	UI_CHARFACE_NAG3_NORMAL,
	UI_CHARFACE_NAG3_SELECT,
	UI_CHARFACE_RAK1_NORMAL,
	UI_CHARFACE_RAK1_SELECT,
	UI_CHARFACE_RAK2_NORMAL,
	UI_CHARFACE_RAK2_SELECT,
	UI_CHARFACE_RAK3_NORMAL,
	UI_CHARFACE_RAK3_SELECT,
	UI_CHARFACE_YAK1_NORMAL,
	UI_CHARFACE_YAK1_SELECT,
	UI_CHARFACE_YAK2_NORMAL,
	UI_CHARFACE_YAK2_SELECT,
	UI_CHARFACE_YAK3_NORMAL,
	UI_CHARFACE_YAK3_SELECT,
};

enum
{
	_CS_ENGLISH		= 0x0001,
	_CS_NUMBER		= 0x0002,
	_CS_HANGUL		= 0x0004,
};


#define _CHAR_a		97
#define _CHAR_z		122
#define _CHAR_A		65
#define _CHAR_Z		90
#define _CHAR_0		48
#define _CHAR_9		57

#define _TRIBE_NAGA			0x01
#define _TRIBE_ASURA		0x02
#define _TRIBE_YAKSA		0x03
#define _TRIBE_DEVA			0x04
#define _TRIBE_KIMNARA		0x05
#define _TRIBE_RAKSHASA		0x06
#define _TRIBE_GANDHARVA	0x07
#define _TRIBE_GARUDA		0x08

#define _NEWCHAR_TRIBE_NAGA			0
#define _NEWCHAR_TRIBE_KIMNARA		1
#define _NEWCHAR_TRIBE_ASURA		2
#define _NEWCHAR_TRIBE_RAKSHASA		3
#define _NEWCHAR_TRIBE_YAKSA		4
#define _NEWCHAR_TRIBE_GANDHARVA	5
#define _NEWCHAR_TRIBE_DEVA			6
#define _NEWCHAR_TRIBE_GARUDA		7

#define UI_CHARFACE_GAN1_NORMAL			11
#define UI_CHARFACE_GAN1_SELECT			12
#define UI_CHARFACE_GAN2_NORMAL			13
#define UI_CHARFACE_GAN2_SELECT			14
#define UI_CHARFACE_GAN3_NORMAL			15
#define UI_CHARFACE_GAN3_SELECT			16
#define UI_CHARFACE_NAG1_NORMAL			17
#define UI_CHARFACE_NAG1_SELECT			18
#define UI_CHARFACE_NAG2_NORMAL			19
#define UI_CHARFACE_NAG2_SELECT			20
#define UI_CHARFACE_NAG3_NORMAL			21
#define UI_CHARFACE_NAG3_SELECT			22
#define UI_CHARFACE_RAK1_NORMAL			23
#define UI_CHARFACE_RAK1_SELECT			24
#define UI_CHARFACE_RAK2_NORMAL			25
#define UI_CHARFACE_RAK2_SELECT			26
#define UI_CHARFACE_RAK3_NORMAL			27
#define UI_CHARFACE_RAK3_SELECT			28
#define UI_CHARFACE_YAK1_NORMAL			29
#define UI_CHARFACE_YAK1_SELECT			30
#define UI_CHARFACE_YAK2_NORMAL			31
#define UI_CHARFACE_YAK2_SELECT			32
#define UI_CHARFACE_YAK3_NORMAL			33
#define UI_CHARFACE_YAK3_SELECT			34

//---------------------------------------------------
// WILL ADD
//---------------------------------------------------
#define UI_CHARFACE_ASURA1_NORMAL		11
#define UI_CHARFACE_ASURA1_SELECT		12
#define UI_CHARFACE_ASURA2_NORMAL		13
#define UI_CHARFACE_ASURA2_SELECT		14
#define UI_CHARFACE_ASURA3_NORMAL		15
#define UI_CHARFACE_ASURA3_SELECT		16
#define UI_CHARFACE_DEVA1_NORMAL		17
#define UI_CHARFACE_DEVA1_SELECT		18
#define UI_CHARFACE_DEVA2_NORMAL		19
#define UI_CHARFACE_DEVA2_SELECT		20
#define UI_CHARFACE_DEVA3_NORMAL		21
#define UI_CHARFACE_DEVA3_SELECT		22
#define UI_CHARFACE_KIMNARA1_NORMAL		23
#define UI_CHARFACE_KIMNARA1_SELECT		24
#define UI_CHARFACE_KIMNARA2_NORMAL		25
#define UI_CHARFACE_KIMNARA2_SELECT		26
#define UI_CHARFACE_KIMNARA3_NORMAL		27
#define UI_CHARFACE_KIMNARA3_SELECT		28
#define UI_CHARFACE_GARUDA1_NORMAL		29
#define UI_CHARFACE_GARUDA1_SELECT		30
#define UI_CHARFACE_GARUDA2_NORMAL		31
#define UI_CHARFACE_GARUDA2_SELECT		32
#define UI_CHARFACE_GARUDA3_NORMAL		33
#define UI_CHARFACE_GARUDA3_SELECT		34
//---------------------------------------------------

#define _NEWCHAR_BOARD					24
#define _NEWCHAR_TRIBE_ENG				1
#define _NEWCHAR_TRIBE_KOR				2

#define _FACENUM_PER_TRIBE				6

#define _FACE_TYPE_1					1
#define _FACE_TYPE_2					2
#define _FACE_TYPE_3					3

#define _FACE_RADIO						0
#define _TRIMULITI_RADIO				1

#define _CHARSEL_TRIBE					1
#define _CHARSEL_TRIMUL					3
#define _CHARSEL_CAST					5
#define _CHARSEL_CHAKRAMUSCLE			7
#define _CHARSEL_CHAKRANERVE			8
#define _CHARSEL_CHAKRAHEART			9
#define _CHARSEL_CHAKRASOUL				10
#define _CHARSEL_BRAHMANPOINT			12
#define _CHARSEL_TEXT_NUM				13

#define _CHARSEL_CHARINFO_BASE1			17
#define _CHARSEL_CHARINFO_BASE2			18
#define _CHARSEL_CHARINFO_BASE3			19


//const HTtchar _TRIBE_TABLE[8][13] = { "나가", "아수라", "야크사", "데바", "킨나라", "라크샤사", "간다르바", "가루다" };
//const HTtchar _TRIBE_EDIT_KOR[8][13] = { "( 나가 )", "( 킴나라 )", "( 아수라 )", "( 라크샤사 )", "( 야크사 )", "( 간다르바 )", "( 데바 )", "( 가루다 )" };
//const HTtchar _TRIBE_EDIT_ENG[8][13] = { "Naga", "Kimnara", "Asura", "Rakshasa", "Yaksa", "Gandarva", "Deva", "Garuda" };

//const HTtchar _CAST_TABLE[5][13] = { "수드라", "바이샤", "크샤트리아", "브라만", "아바타라" };
//const HTtchar _TRIMURITI_TABLE[3][13] = { "브라흐마", "비슈느", "시바" };


