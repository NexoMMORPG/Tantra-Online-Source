#define _DEFAULT_CURSOR				0

// �پƾ˷α� ����
#define _DLG_STATUS_LOADING			0	// ó���ߴ� ȭ��
#define _DLG_STATUS_LOGIN			1	// �α��δ��̾˷α�
#define _DLG_STATUS_SERVER_SELECT	2	// ���� �����ϴ� ȭ��
#define _DLG_STATUS_CHAR_SELECT		3	// ĳ���� �����ϴ� ȭ��
#define _DLG_STATUS_NEW_CHARTRIBE	4	// ĳ���� �����ϴ� ȭ��
#define _DLG_STATUS_CHAR_INFO		5	// ĳ���� �����ϴ� ȭ��

enum // �α��� ���� �޽���
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

enum // ���� ���ð��� �޽���
{
	_SELECTWORLD_MOVETO_ZONESERVER		= 101,
	_SELECTWORLD_WORLDLIST				= 102,
	_SELECTWORLD_NETWORKERROR			= 103,
	_SELECTWORLD_LOGOUT					= 104,
};

enum // ĳ���� ���� �޽���
{
	_CHAR_CHARLIST						= 101,
	_CHAR_EXITZONE						= 102,
	_CHAR__NETWORKERROR					= 103,
};

//#define _MESSAGE_NONE							_T(" ")
//#define _MESSAGE_LOGIN							_T("���̵�/�н����带 �Է��� �ֽʽÿ�.")
//#define _MESSAGE_WORLDSELECT					_T("������ ������ ������ �ֽʽÿ�.")
//#define _MESSAGE_ZONESERVER_CONNECTING			_T("�������� �������Դϴ�.")
//#define _MESSAGE_CHAR_INFO_REQUEST				_T("������ ĳ���� ������ ��û�ϰ� �ֽ��ϴ�.")
//
//
//#define _LOGIN_OK_TEXT							_T("�α��� �Ǿ����ϴ�.")
//#define _LOGIN_USERID_ERROR_TEXT				_T("�������� �ʴ� ����� ID �Դϴ�.")
//#define _LOGIN_PASSWORD_ERROR_TEXT				_T("�ùٸ��� ���� ����� ��ȣ�Դϴ�.")
//#define _LOGIN_SERVER_REPLY_ERROR_TEXT			_T("������ ������ �����ϴ�.")
//#define _LOGIN_SERVER_CONNECT_FEE_ERROR_TEXT	_T("���ݰ��� ������ ������ �Ұ��մϴ�.")
//#define _LOGIN_REUSER_ERROR_TEXT				_T("�̹� �α��� �� ������Դϴ�.")
//#define _LOGIN_USETIME_ERROR_TEXT				_T("�˼��մϴ�. ������ �̿� �ð��� �ƴմϴ�.")
//#define _LOGIN_UNKNOWN_ERROR_TEXT				_T("�� �� ���� ���� �߻��� �߻��߽��ϴ�.")
//#define _LOGIN_SERVER_CONNECT_ERROR_TEXT		_T("������ ������� �ʾҽ��ϴ�.")
//#define _LOGOUT_TEXT							_T("�α׾ƿ��Ǿ����ϴ�.")
//
//
//#define _MESSAGE_CHARLIST_ERROR					_T("�߸��� ĳ���� ����Ʈ�� �޾ҽ��ϴ�.")
//
//
//#define _SELECTWORLD_MOVETO_ZONESERVER_TEXT		_T("�������� ������ ��û�մϴ�.")
//#define _SELECTWORLD_WORLDLIST_TEXT				_T("���忡 ���� ���� ����Ʈ�� �޾ҽ��ϴ�.")
//#define _SELECTWORLD_NETWORKERROR_TEXT			_T("��Ʈ��ũ ������ �߻��Ͽ����ϴ�.")


// UI���� ����ϴ� ��Ʈ�� ��ȣ
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


//const HTtchar _TRIBE_TABLE[8][13] = { "����", "�Ƽ���", "��ũ��", "����", "Ų����", "��ũ����", "���ٸ���", "�����" };
//const HTtchar _TRIBE_EDIT_KOR[8][13] = { "( ���� )", "( Ŵ���� )", "( �Ƽ��� )", "( ��ũ���� )", "( ��ũ�� )", "( ���ٸ��� )", "( ���� )", "( ����� )" };
//const HTtchar _TRIBE_EDIT_ENG[8][13] = { "Naga", "Kimnara", "Asura", "Rakshasa", "Yaksa", "Gandarva", "Deva", "Garuda" };

//const HTtchar _CAST_TABLE[5][13] = { "�����", "���̻�", "ũ��Ʈ����", "���", "�ƹ�Ÿ��" };
//const HTtchar _TRIMURITI_TABLE[3][13] = { "����帶", "�񽴴�", "�ù�" };


