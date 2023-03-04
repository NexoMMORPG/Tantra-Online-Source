//======================================================================
// HTUIIDDef.h
// UI를 구성하는 요소들의 아이디 정의
// 2003. 7. 28.  	(주)한빛소프트 게임개발팀 정대호
// 2004. 8. 10.  	(주)한빛소프트 게임개발팀 선영범
//======================================================================
#ifndef _HTUIIDDEF_H
#define _HTUIIDDEF_H

#define _WHITE			26007
#define _MINIMAP_ARROW	26076

//----------------------------------------------------------------------
// 다이알로그  Intro
//----------------------------------------------------------------------
#define _DIALOG_KATHANALOGO			101
#define _DIALOG_LOGINBOX			102
#define _DIALOG_SERVERSELECT		103
#define _DIALOG_CHARACTERINFO1		104
#define _DIALOG_CHARACTERINFO2		105
#define _DIALOG_CHARACTERINFO3		106
#define _DIALOG_CHARACTERCREATE		107
#define _DIALOG_INPUTJUMINNO		108
#define _DIALOG_TOPMENU				109
#define _DIALOG_LIMIT12AGE			110
#define _DIALOG_3MANDARAVILLAGE		111

//----------------------------------------------------------------------
// 다이알로그  Main
//----------------------------------------------------------------------
#define _DIALOG_CHARINFO			1	// 캐릭터 정보
#define _DIALOG_INVEN				7	// 인벤토리
#define _DIALOG_GOODSKEEPING		9	// 물품보관
#define _DIALOG_TRADE				11	// 트레이드
#define _DIALOG_ITEMINFO			21	// 아이템정보
#define _DIALOG_ACCESSORY_MERCHANT	36	// 악세사리 상인
#define _DIALOG_PRIVATE_SHOP		62	// 개인상점
#define _DIALOG_PRIVATE_SHOP_BUY	63	// 개인상점_사기
#define	_DIALOG_PRIMIUM_BUY1		102	// 프리미엄 아이템 구입창1
#define	_DIALOG_PRIMIUM_BUY2		103	// 프리미엄 아이템 구입창2
#define	_DIALOG_PRIMIUM_BUY3		105	// 프리미엄 아이템 구입창3


//	New UI
#define _DIALOG_BACKGROUND			200	// 메시지처리용 (숨겨진 윈도우)
#define _DIALOG_INIT				201	// 이닛
#define _DIALOG_CHATTINGBOX			202	// 채팅 박스
#define _DIALOG_MAINBAR				203	// Main Bar
#define _DIALOG_EQUPINVENTORY		204	// Equip Inventory
#define _DIALOG_ADDRESS				205	// Address
#define _DIALOG_MAINCHARHP			206	// MainChar HP
#define _DIALOG_SIEGE1				207	// 공성전1 참가아쉬람
#define _DIALOG_SIEGE2				208	// 공성전2 공성전상황
#define _DIALOG_SIEGE3				209	// 공성전3 공성전선포
#define _DIALOG_SIEGE4				210	// 공성전4 비류성관리
#define _DIALOG_EMPTY1				211	// 빈 ID
#define _DIALOG_COMMANDWND			212 // 명령
#define _DIALOG_OPTIONWND			213 // 옵션창
#define _DIALOG_PORTALWND			214 // 포탈탕
#define _DIALOG_JIVAPUSTICAWND		215 // 지바 푸스티카
#define _DIALOG_UPGRADEJIVAPUSTICA	216 // 향상된 지바 푸스티카
#define _DIALOG_ASHRAMINFO			217 // 아쉬람 정보창
#define _DIALOG_ASHRAMMEMBERLISET	218 // 아쉬람 구성인원
#define _DIALOG_HQUICKSLOT			219 // 세로 퀵슬롯
#define _DIALOG_WQUICKSLOT			220 // 가로 퀵슬롯
#define _DIALOG_PRANABAR			221 // 프라나바
#define _DIALOG_GOODSKEEPWND		222 // 개인창고
#define _DIALOG_DEATHMSG			223 // 죽을때 떠는 창
#define _DIALOG_DEATHMSGFOTRESS		224	// 요새전에서서 죽을때 떠는창
#define _DIALOG_TRADEWND			225	// 교환창
#define _DIALOG_CHARITYWND1			226	// 축복의 신로1 만다라
#define _DIALOG_CHARITYWND2			227	// 축복의 신로2 쿠루마
#define _DIALOG_DISCONNECTSERVER	228	// 서버와 연결이 끊어졌을떄
#define _DIALOG_PARTYWND			229	// 파티 윈도우
#define _DIALOG_BEAUTYSALON			230	// 종합 미용실
#define	_DIALOG_BEAUTYSALON2		231	// 종합 미용실 이용권창
#define _DIALOG_INDIVIDUALWND1		232	// 개인상점 파는 사람에게 떠는 창
#define _DIALOG_INDIVIDUALWND2		233	// 개인상점 사는 사람에게 떠는 창
#define	_DIALOG_MERCHANT			234	// 상점 구매창
#define _DIALOG_QUEST				235 // 퀘스트창
#define _DIALOG_REFINE				236 // 제련창
#define _DIALOG_SKILL				237 // 스킬창
#define _DIALOG_NPCWINDOW			238	// NPC 대화창
#define _DIALOG_STATUS				239	// 상태창
#define _DIALOG_MERCHANT_PREMIUM	240 // 프리미엄 아이템 구입창
#define _DIALOG_GAMBLE_YUT			241 // 윷놀이 상황판
#define _DIALOG_INVENTORY2			242 // 윷놀이 상황판
#define _DIALOG_OPENMESSAGE			243 // 전광판
#define _DIALOG_MINIMAPSMALL		244 // 미니맵 작은것
#define _DIALOG_MINIMAPBIG			245 // 미니맵 큰것
#define	_DIALOG_AMBLEM				246	// 아쉬람 만들기창
#define	_DIALOG_REVIVEWND			247	// 부활창
#define	_DIALOG_ANSWERUSESAMUDABA	248	// 사무다바 확인창
#define	_DIALOG_MESSAGEBOX_MGR		249	// 메시지박스 처리 윈도우
#define	_DIALOG_BUFFSKILL			250	// 버퍼스킬
#define	_DIALOG_BYELISTWND			251	// 개인상점 아이템 구입시 리스트
#define	_DIALOG_WHISPERLISTWND		252	// 귓속말 리스트
#define	_DIALOG_NOTIFYWND			253	// 공지창
#define _DIALOG_SIEGEJOININFO_0		254	// 공성전 연맹 참가 정보0
#define _DIALOG_SIEGEJOININFO_1		255	// 공성전 연맹 참가 정보1
#define _DIALOG_SIEGEJOININFO_2		256	// 공성전 연맹 참가 정보2
#define _DIALOG_SIEGEJOININFO_3		257	// 공성전 연맹 참가 정보3
#define _DIALOG_SIEGEHELP_1			258	// 공성정 도움말1
#define _DIALOG_SIEGEHELP_2			259	// 공성정 도움말2
#define _DIALOG_SIEGEHELP_3			260	// 공성정 도움말3
#define _DIALOG_SIEGEHELP_4			261	// 공성정 도움말4
#define _DIALOG_HELPWND_1			262	// 도움말1
#define _DIALOG_HELPWND_2			263	// 도움말2
#define _DIALOG_HELPWND_3			264	// 도움말3
#define _DIALOG_HELPWND_4			265	// 도움말4
#define _DIALOG_ATTENDANCECHECK		266	// 출석체크
#define _DIALOG_WINEVENTWND			267	// 이벤트 당첨1
#define _DIALOG_TUTORIALWND_1		268	// 튜토리얼1
#define _DIALOG_TUTORIALWND_2		269	// 튜토리얼2
#define _DIALOG_TUTORIALWND_3		270	// 튜토리얼3
#define _DIALOG_TUTORIALWND_4		271	// 튜토리얼4
#define _DIALOG_TUTORIALWND_5		272	// 튜토리얼5
#define _DIALOG_TUTORIALWND_6		273	// 튜토리얼6
#define _DIALOG_TUTORIALWND_7		274	// 튜토리얼7
#define _DIALOG_TUTORIALWND_8		275	// 튜토리얼8
#define _DIALOG_TUTORIALWND_9		276	// 튜토리얼9
#define _DIALOG_TUTORIALWND_10		277	// 튜토리얼10
#define _DIALOG_TUTORIALWND_11		278	// 튜토리얼11
#define _DIALOG_TUTORIALWND_12		279	// 튜토리얼12
#define _DIALOG_TUTORIALWND_13		280	// 튜토리얼13
#define _DIALOG_TUTORIALWND_14		281	// 튜토리얼14
#define _DIALOG_WEBBROWSER			282	// 웹브라우저
#define _DIALOG_CHATCONFIG			283	// 채팅설정
#define _DIALOG_WINEVENT2WND		284	// 이벤트 당첨2
#define _DIALOG_MINIMAINBAR			285	// Mini Main Bar
#define	_DIALOG_MY_USEINFO_V3		286	// 내 사용 내역
#define	_DIALOG_ASHRAMCAGO			287	// 아쉬람 창고
#define _DIALOG_SANCTIONASHCAGO     288 // 아쉬람 창고 결재
#define _DIALOG_SETLEVELASHCAGO     289 // 아쉬람 창고 권한 설정
#define _DIALOG_CHATTING2BOX		290	// 채팅 박스2
#define _DIALOG_CHATTING3BOX		291	// 채팅 박스3
#define _DIALOG_RENTALSTORE			292	// 위탁상점창
#define _DIALOG_RENTALSTORE_SLIST	293	// 위탁상점 판매중인 물품 리스트창
#define _DIALOG_RENTALSTORE_RLIST	294	// 위탁상점 재고로 남은 물품 리스트창
#define _DIALOG_RENTALSTORE_BLIST	295	// 위탁상점 구매내역 리스트창
#define _DIALOG_CHATLOG1			296	// 채팅로고(일반메시지)
#define _DIALOG_CHATLOG2			297	// 채팅로고(전광판메시지)
#define _DIALOG_CHATLOGCONFIG		298	// 채팅설정(채팅로그창)
#define _DIALOG_CHATROOM			299	// 채팅방 (대기실)
#define _DIALOG_CHATROOM_CREATE		300	// 채팅방 (생성창)
#define _DIALOG_CHATROOM_MSG		301	// 채팅방 (채팅창)
#define _DIALOG_CHATROOM_WAITING	302	// 채팅방 (대기자)
#define _DIALOG_QUIZ				303	// 퀴즈

//	MessageBox Type
#define _MESSAGEBOX_NONE			0
#define _MESSAGEBOX_THROWITEM		1
#define _MESSAGEBOX_RUPIAH			2
#define _MESSAGEBOX_THROWRUPIAH		3
#define _MESSAGEBOX_UNPACKING		4

//	Slot Currect
#define _SLOTCURRECT_INVEN			100
#define _SLOTCURRECT_ADDINVEN		24

//----------------------------------------------------------------------
// 버튼 메시지
//----------------------------------------------------------------------
#define _BTN_MSG_CANCEL				0	// CANCEL
#define _BTN_MSG_OK					1	// OK
#define _BTN_MSG_UPGRADE			11	// UPGRADE
#define _BTN_MSG_MINUS				21	// MINUS
#define _BTN_MSG_PLUS				22	// PLUS
#define _BTN_MSG_X					23	// X
#define _BTN_MSG_LEFTCIRCLEARROW	31	// LEFT CIRCLE ARROW
#define _BTN_MSG_RIGHTCIRCLEARROW	32	// RIGHT CIRCLE ARROW
#define _BTN_MSG_RUPIA				2	// RUPIA
#define _BTN_MSG_LEFT_ARROW			41	// LEFT_ARROW
#define _BTN_MSG_RIGHT_ARROW		42	// RIGHT_ARROW
#define _BTN_MSG_DIAL0				100	// DIAL 0
#define _BTN_MSG_DIAL1				101	// DIAL 1
#define _BTN_MSG_DIAL2				102	// DIAL 2
#define _BTN_MSG_DIAL3				103	// DIAL 3
#define _BTN_MSG_DIAL4				104	// DIAL 4
#define _BTN_MSG_DIAL5				105	// DIAL 5
#define _BTN_MSG_DIAL6				106	// DIAL 6
#define _BTN_MSG_DIAL7				107	// DIAL 7
#define _BTN_MSG_DIAL8				108	// DIAL 8
#define _BTN_MSG_DIAL9				109	// DIAL 9
#define _BTN_MSG_DIAL_DEL			110	// DIAL GO
#define _BTN_MSG_FOLD_UP			51	// FOLD_UP
#define _BTN_MSG_FOLD_DOWN			52	// FOLD_DOWN
#define _BTN_MSG_TRI_UP				61	// TRI_UP
#define _BTN_MSG_TRI_DOWN			62	// TRI_DOWN
#define _BTN_MSG_PARTY_CREATE		71	// 파티생성
#define _BTN_MSG_PARTY_JOIN			72	// 파티가입
#define _BTN_MSG_PARTY_MINI			73	// 파티미니
#define _BTN_MSG_PARTY_WITHDRAW		74	// 파티탈퇴

#define _BTN_MSG_GAME_END			80	// 게임종료
#define _BTN_MSG_RESTART			81	// 재시작
#define _BTN_MSG_GM_CALL			82	// GM호출
#define _BTN_MSG_HELP				83	// HELP

#define _BTN_MSG_REFINE				91	// 제련하기
#define _BTN_MSG_SLIDEUP			111	// 슬라이드위로버튼
#define _BTN_MSG_SLIDEDOWN			112	// 슬라이드아래로버튼
#define _BTN_MSG_CHAT_OPEN			121	// 채팅열기
#define _BTN_MSG_CHAT_CLOSE			122	// 채팅닫기
#define _BTN_TUTORIAL_PREV			201	// 튜토리얼 앞으로
#define _BTN_TUTORIAL_NEXT			202	// 튜토리얼 뒤
#define _BTN_ADDRESS_REGISTER		211	// 주소록에 등록
#define _BTN_ADDRESS_DEL			212	// 주소록에서 삭제
#define _BTN_GUILD_CREATE			221
#define _BTN_GUILD_JOIN				222
#define _BTN_GUILD_MEMBER			223
#define _BTN_GUILD_DISJOIN			224
#define _BTN_GUILD_EXPEL			225
#define _BTN_RANK_PREV				123
#define _BTN_RANK_NEXT				124
#define _BTN_RANK_FIRST				125
#define _BTN_RANK_LAST				126
#define _BTN_RANK_1					127
#define _BTN_RANK_2					128
#define _BTN_RANK_3					129
#define _BTN_RANK_4					130
#define _BTN_RANK_5					131
#define _BTN_SEARCH					132
#define _BTN_QUICKSKILL_CLOSE		141
#define _BTN_BAG_MINIMIZE			142
#define _BTN_MSG_TOMINIMAP			91
#define _BTN_MSG_TOMAP				92
#define _BTN_CHAT_MODE				3
#define _BTN_CHATTING_SET			4
#define _BTN_APPLY					5

#define _BTN_COMMAND_PARTYWITHDRAW	150
#define _BTN_COMMAND_SIT			151
#define _BTN_COMMAND_WALK			152
#define _BTN_COMMAND_ATTACK			153
#define _BTN_COMMAND_TRACE			154
#define _BTN_COMMAND_HELP			155
#define _BTN_COMMAND_TRADE			156
#define _BTN_COMMAND_TARGET			157
#define _BTN_COMMAND_PICKUP			158
#define _BTN_COMMAND_SHOP			159
#define _BTN_COMMAND_PARTY			160
#define _BTN_COMMAND_PROVOKE		170
#define _BTN_COMMAND_GREET			171
#define _BTN_COMMAND_RUSH			172
#define _BTN_CHATURANGA_COMPOSITE	173
#define _BTN_COMMAND_BLOG			209
#define _BTN_COMMAND_DUEL			210
#define _BTN_COMMAND_EMPTYPLACE		211
#define _BTN_COMMAND_ASSIST			212

#define _BTN_GUILD_NAME				161
#define _BTN_GUILD_LEVEL			162
#define _BTN_GUILD_CONNECT			163
#define _BTN_GUILD_HOMEPAGE_MAKE	206
#define _BTN_GUILD_HOMEPAGE_ENTER	207

#define _BTN_TUTQUEST_CHARMOVE			301
#define _BTN_TUTQUEST_VIEWCHANGE		302
#define _BTN_TUTQUEST_MINIMAPUSE		303
#define _BTN_TUTQUEST_SHORTKEY			304
#define _BTN_TUTQUEST_MONSTER_HUNT		305
#define _BTN_TUTQUEST_ITEM_PICKUP		306
#define _BTN_TUTQUEST_TUTORIAL_GIFT		307
#define _BTN_TUTQUEST_PRAVARTA_QUEST	308

#define	_CHAKRA_MUSCLE				0
#define	_CHAKRA_NERVE				1
#define	_CHAKRA_HEART				2
#define	_CHAKRA_SPIRIT				3

//----------------------------------------------------------------------
// 메인체크박스
//----------------------------------------------------------------------
// Version 1002
#define	_MAINCHECK_CHECK_ADDRESS	0
#define	_MAINCHECK_CHECK_RUN		1
#define	_MAINCHECK_CHECK_TRADE		2
#define	_MAINCHECK_CHECK_STATUS		0
#define	_MAINCHECK_CHECK_INVEN		1
#define	_MAINCHECK_CHECK_SKILL		3
#define	_MAINCHECK_CHECK_QUEST		2
#define	_MAINCHECK_CHECK_PARTY		7
#define	_MAINCHECK_CHECK_SYSTEM		4
#define	_MAINCHECK_CHECK_NUM		_MAINCHECK_CHECK_SYSTEM+1

#define	_MAINCHECK_BUTTON_UP_MUSCLE		0
#define	_MAINCHECK_BUTTON_UP_HEART		1
#define	_MAINCHECK_BUTTON_UP_NERVE		2
#define	_MAINCHECK_BUTTON_UP_SPIRIT		3
#define	_MAINCHECK_BUTTON_UP_BRAHMAN	4

// Version 1003
#define _MAINCHECK_CHECK_PREMIUM_1003	0
#define _MAINCHECK_CHECK_STATUS_1003	1
#define _MAINCHECK_CHECK_INVEN_1003		2
#define _MAINCHECK_CHECK_QUEST_1003		3
#define _MAINCHECK_CHECK_SKILL_1003		4
#define _MAINCHECK_CHECK_OPTION_1003	5
#define _MAINCHECK_CHECK_CMD_1003		6
#define _MAINCHECK_CHECK_PK_1003		7

#define _SUBCHECK_CHECK_PREMIUM_1003	0
#define _SUBCHECK_CHECK_INVEN_1003		1
#define _SUBCHECK_CHECK_OPTION_1003		2
#define _SUBCHECK_CHECK_CMD_1003		3

//----------------------------------------------------------------------
// 캐릭터 정보
//----------------------------------------------------------------------
#define _CHARINFO_EDIT_NAME				0
#define _CHARINFO_EDIT_LEVEL			1
#define _CHARINFO_EDIT_RACE				2
#define _CHARINFO_EDIT_CAST				3
#define _CHARINFO_EDIT_GUILDNAME		4
#define _CHARINFO_EDIT_BRAHMAN			5
#define _CHARINFO_EDIT_JOB				6
#define _CHARINFO_EDIT_GOD				7
#define _CHARINFO_EDIT_EXTRANAME		8
#define _CHARINFO_EDIT_HP				9
#define _CHARINFO_EDIT_TAPAS			10
//#define _CHARINFO_EDIT_MAGICATTACK		10
#define _CHARINFO_EDIT_PHYSICALATTACK	11
#define _CHARINFO_EDIT_ATTACKSUCCESS	12
#define _CHARINFO_EDIT_DEFENCE			13
#define _CHARINFO_EDIT_AVOIDSUCCESS		14
#define _CHARINFO_EDIT_TENDENCY			15
#define _CHARINFO_EDIT_MUSCLE			16
#define _CHARINFO_EDIT_NERVE			17
#define _CHARINFO_EDIT_HEART			18
#define _CHARINFO_EDIT_SPIRIT			19
#define _CHARINFO_EDIT_MUSCLE_PLUS		20
#define _CHARINFO_EDIT_NERVE_PLUS		21
#define _CHARINFO_EDIT_HEART_PLUS		22
#define _CHARINFO_EDIT_SPIRIT_PLUS		23
#define _CHARINFO_EDIT_FIRE				24
#define _CHARINFO_EDIT_THUNDER			25
#define _CHARINFO_EDIT_COLD				26
#define _CHARINFO_EDIT_POISON			27
#define _CHARINFO_EDIT_CHAKRA			28


#define _CHARINFO_BUTTON_MUSCLE			0
#define _CHARINFO_BUTTON_NERVE			1
#define _CHARINFO_BUTTON_HEART			2
#define _CHARINFO_BUTTON_SPIRIT			3
//#define _CHARINFO_BUTTON_BRAHMAN		4


//----------------------------------------------------------------------
// 캐릭터 정보 소형
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// 포탈
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// HP & PRANA
//----------------------------------------------------------------------
#define	_HPPR_TEXT_CHAKRA				0
//#define	_HPPR_TEXT_HP					2
#define	_HPPR_TEXT_PR					3
#define	_HPPR_TEXT_LSKILL_SHORTCUT		4
#define	_HPPR_TEXT_RSKILL_SHORTCUT		5

#define	_HPPR_EDIT_HP					1
#define	_HPPR_EDIT_TP					2
#define	_HPPR_EDIT_PR					3


#define	_HPPR_EDIT_NEED_PRANA			0
#define _HPPR_BMP_HP_TRANSPARENT		2
#define _HPPR_BMP_HP					3
#define _HPPR_BMP_TP					4
//#define _HPPR_BMP_TP_RESIDUE			18
#define _HPPR_BMP_PR					5
//#define _HPPR_BMP_HP_RRESIDUE			16
//#define _HPPR_BMP_PR_RRESIDUE			20



//#define _HPPR_BMP_CAST_ICON				9
//#define _HPPR_BMP_LSKILL_ICON			20
//#define _HPPR_BMP_RSKILL_ICON			21
//----------------------------------------------------------------------
// 몬스터 HP
//----------------------------------------------------------------------
#define _MONHP_BMP_HP					2
//#define _MONHP_BMP_MONHP_LRESIDUE		4
//#define _MONHP_BMP_MONHP_RRESIDUE		5

#define	_MONHP_EDIT_MONHP				0
#define	_MONHP_EDIT_MONNAME				1
//#define _MONHP_DURABLE_ATTACK1			0
//#define _MONHP_DURABLE_ATTACK2			1
//#define _MONHP_DURABLE_DEFENCE1			2
//#define _MONHP_DURABLE_DEFENCE2			3

//----------------------------------------------------------------------
// 스킬
//----------------------------------------------------------------------
#define _SKILL1_TAB_TRIBE					0
#define _SKILL1_TAB_TRIMURITI				1
#define _SKILL1_TAB_FREE					2

#define _SKILL1_LEVELUP_TRIBE0				9
#define _SKILL1_LEVELUP_TRIBE1				10
#define _SKILL1_LEVELUP_TRIBE2				11
#define _SKILL1_LEVELUP_TRIBE3				12
#define _SKILL1_LEVELUP_TRIBE4				13
#define _SKILL1_LEVELUP_TRIBE5				14
#define _SKILL1_LEVELUP_TRIBE6				15
#define _SKILL1_LEVELUP_TRIBE7				16
#define _SKILL1_LEVELUP_TRIBE8				17
#define _SKILL1_LEVELUP_TRIBE9				18

#define _SKILL1_LEVELUP_GOD1				19
#define _SKILL1_LEVELUP_GOD2				20
#define _SKILL1_LEVELUP_GOD3				21
#define _SKILL1_LEVELUP_GOD4				22
#define _SKILL1_LEVELUP_GOD5				23

#define _SKILL1_LEVELUP_FREE0				24
#define _SKILL1_LEVELUP_FREE1				25
#define _SKILL1_LEVELUP_FREE2				26
#define _SKILL1_LEVELUP_FREE3				27
#define _SKILL1_LEVELUP_FREE4				28
#define _SKILL1_LEVELUP_FREE5				29
#define _SKILL1_LEVELUP_FREE6				30
#define _SKILL1_LEVELUP_FREE7				31
#define _SKILL1_LEVELUP_FREE8				32
#define _SKILL1_LEVELUP_FREE9				33

#define _SKILL1_LEVELUP_VOCATION0			34
#define _SKILL1_LEVELUP_VOCATION1			35
#define _SKILL1_LEVELUP_VOCATION2			36
#define _SKILL1_LEVELUP_VOCATION3			37
#define _SKILL1_LEVELUP_VOCATION4			38

#define _SKILL1_START						40
#define _SKILL1_END							59

#define _SKILL_LEVELUP_START				_SKILL1_LEVELUP_TRIBE0

#define _NEWSKILL_BOX_START					20
#define _NEWSKILL_ICON_START				40
#define _NEWSKILL_ARROW_START				60

#define _NEWSKILL_UPBTN_START				3
#define _NEWSKILL_TRIBE						22

#define _NEWSKILL_VIEWSKILL_NUM				20
#define _NEWSKILL_VIEWSKILLARROW_NUM		16
//----------------------------------------------------------------------
// 퀵슬롯
//----------------------------------------------------------------------
#define _QUICKSLOT_BEGIN								1
#define _QUICKSLOT_END									10

#define _QUICKSLOT_HIGHT								10

#define _QUICKSLOT_TYPE_NONE							0
#define _QUICKSLOT_TYPE_SKILL							1
#define _QUICKSLOT_TYPE_ITEM							2
#define _QUICKSLOT_TYPE_COMMAND							3
//----------------------------------------------------------------------
// 벨트
//----------------------------------------------------------------------
//#define _BELT_SLOT1							8
//#define _BELT_SLOT2							9
//#define _BELT_SLOT3							10
//#define _BELT_SLOT4							11
//#define _BELT_SLOT5							12
//#define _BELT_SLOT_NUM						5
//
//#define _BELT_TEXT1							0
//#define _BELT_TEXT2							1
//#define _BELT_TEXT3							2
//#define _BELT_TEXT4							3
//#define _BELT_TEXT5							4

//----------------------------------------------------------------------
// 아이템 헌납
//----------------------------------------------------------------------
#define _OFFERING_GAUGE_BAR					9
#define _OFFERING_GAUGE_BAR2				20
#define _OFFERING_EDIT_MONEY				0

#define _OFFERING_BEGIN						10
#define _OFFERING_END						19

#define _OFFERING_WIDTH						5

//----------------------------------------------------------------------
// 인벤
//----------------------------------------------------------------------
#define	_INVEN_HEAD							1
#define	_INVEN_BODY							2
#define	_INVEN_BELT							3
#define	_INVEN_FOOT							5
#define	_INVEN_RIGHT_EARING					13	// 오른쪽 귀걸이
#define	_INVEN_LEFT_EARING					14	// 왼쪽 귀걸이
#define	_INVEN_NECKLACE						6
#define	_INVEN_ATTACK_WEAPON				7
#define	_INVEN_DEFENCE_WEAPON				15
#define	_INVEN_RIGHT_ARMLET					9	// 오른쪽
#define	_INVEN_LEFT_ARMLET					11	// 왼쪽
#define	_INVEN_RIGHT_RING					10	// 오른쪽
#define	_INVEN_LEFT_RING					12	// 왼쪽
#define	_INVEN_BAG							18
#define	_INVEN_TROUSERS						4
#define	_INVEN_GLOVES						8

#define	_INVEN_WIDTH						6
#define _INVEN_HEIGHT						4

#define _INVEN_TAP_GROUP					0
#define _INVEN_TAP_BAG1						0
#define _INVEN_TAP_BAG2						1
#define _INVEN_TAP_BAG3						2
#define _INVEN_MYPREDATE					1	// 인벤토리 확장 유효기간 표시
//----------------------------------------------------------------------
// 차투랑가 보드 (추가 선영범 - 2004. 6. 17)
//----------------------------------------------------------------------
//#define	_CHATURANGA_SAVE_BEGIN				11
//#define	_CHATURANGA_SAVE_END				35
//#define	_CHATURANGA_SAVE_INVEN_WIDTH		5
//#define _CHATURANGA_SAVE_INVEN_HEIGHT		5

//----------------------------------------------------------------------
// 물품보관(교환소랑 같이 사용함)
//----------------------------------------------------------------------
#define	_GOODSKEEP_SAVE_BEGIN				2
#define	_GOODSKEEP_SAVE_END					121
//#define	_GOODSKEEP_RUPIA_BITMAP				84
#define	_GOODSKEEP_INVEN_WIDTH				10
#define _GOODSKEEP_INVEN_HEIGHT				12

//----------------------------------------------------------------------
// 위탁상점
//----------------------------------------------------------------------
#define	_RENTALSTORE_INVEN_BEGIN			10
#define _RENTALSTORE_INVEN_END				40

#define	_RENTALSTORE_INVEN_WIDTH			6
#define _RENTALSTORE_INVEN_HEIGHT			5

//----------------------------------------------------------------------
// 교환
//----------------------------------------------------------------------
#define _TRADE_MY_BEGIN						21
#define _TRADE_MY_END						28
#define _TRADE_INVEN_YOU_START				10
#define _TRADE_INVEN_YOU_END				20
#define _TRADE_INVEN_WIDTH					4
#define _TRADE_INVEN_HEIGHT					2

#define _TRADE_EDIT_OTHER_MONEY				0
#define _TRADE_EDIT_MY_MONEY				1
#define _TRADE_EDIT_OTHER_NAME				2 // 상대방 이름
#define _TRADE_EDIT_MY_NAME					3 // 내 이름
//----------------------------------------------------------------------
// 개인상점
//----------------------------------------------------------------------
#define _STORE_WIDTH						6
#define _STORE_HEIGHT						2

// 판매
#define _STORE_SELL_BEGIN					10
#define _STORE_SELL_END						21
#define _STORE_PREMIUM_SELL_BEGIN			22	// 프리미엄 확장 인벤 끝
#define _STORE_PREMIUM_SELL_END				33	// 프리미엄 확장 인벤 끝

#define _STORE_SELL_EDIT_MESSAGE			0
#define _STORE_SELL_EDIT_BUYMONEY			1
#define _STORE_SELL_EDIT_MYMONEY			2
#define _STORE_SELL_EDIT_MYPREDATE			3	// 유효기간 표시 (프리미엄)

// 구매
#define _STORE_BUY_BEGIN					10	// 상점목록
#define _STORE_BUY_END						21
#define _STORE_BUY_PREMIUM_END				33	// 프리미엄 확장 인벤 끝

#define _STORE_BUY_MY_BEGIN					34	// 구매 목록
#define _STORE_BUY_MY_END					45
#define _STORE_BUY_MY_PREMIUM_END			57	// 프리미엄 확장 인벤 끝

#define _STORE_BUY_EDIT_BUYMONEY			0
#define _STORE_BUY_EDIT_MYMONEY				1
#define _STORE_BUY_EDIT_SELLER_NAME			2 // 판매자 이름
#define _STORE_BUY_EDIT_BUYER_NAME			3 // 구매자 이름

//----------------------------------------------------------------------
// NPC 다이알로그
//----------------------------------------------------------------------
#define _NPC_EDIT_NPCNAME					0
#define _NPC_EDIT_FRIENDSHIP_TEXT			0
#define _NPC_FRIENDSHIP_TEXT				1
#define _NPC_WORD_TEXT						0

//----------------------------------------------------------------------
// 아이템 제작
//----------------------------------------------------------------------
#define _ITEMMAKE_BTN_PREV					0
#define _ITEMMAKE_BTN_NEXT					1

// 아이템 구입창의 아이템 분류에 따른 각 탭 번호
#define _ITEMMAKE_DEFENCE_ARMOR				0
#define _ITEMMAKE_DEFENCE_HELMET			1
#define _ITEMMAKE_DEFENCE_SHOES				2
#define _ITEMMAKE_DEFENCE_BELT				3
#define _ITEMMAKE_DEFENCE_SHIELD			4
#define _ITEMMAKE_ACCESSORY_USABLE			0
#define _ITEMMAKE_ACCESSORY_REFINE			0
#define _ITEMMAKE_ACCESSORY_BRACELET		1
#define _ITEMMAKE_ACCESSORY_NECKLACE		1
#define _ITEMMAKE_ACCESSORY_EARRING			1
#define _ITEMMAKE_ACCESSORY_RING			1
#define _ITEMMAKE_ACCESSORY_EXPANDINVEN		1

#define _ITEMMAKE_TAP_GROUP					0
//----------------------------------------------------------------------
// 아이템 제련
//----------------------------------------------------------------------
#define _ITEMREFINE_EDIT_RUPIA				0
//#define _ITEMREFINE_EDIT_PRANA			1
//#define _ITEMREFINE_EDIT_ATTRIBUTE		2
#define _ITEMREFINE_ITEM_BEGIN				10

#define _ITEMREFINE_SUBITEM_POS				11
#define _ITEMREFINE_BAR						14

//----------------------------------------------------------------------
// 시스템
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// 루피아언패킹
//----------------------------------------------------------------------
#define _RUPIAUNPACK_EDIT_RUPIA				0
#define _RUPIAUNPACK_FROM_INVEN_X			283
#define _RUPIAUNPACK_FROM_INVEN_Y			295

#define _RUPIAUNPACK_FROM_GOODSKEEP_X			283
#define _RUPIAUNPACK_FROM_GOODSKEEP_Y			295

#define _RUPIAUNPACK_FROM_TRADE_X			283
#define _RUPIAUNPACK_FROM_TRADE_Y			295

//----------------------------------------------------------------------
// 아이템언패킹
//----------------------------------------------------------------------
#define _UNPACKING_ITEM_IMAGE	11

//----------------------------------------------------------------------
// 미니맵
//----------------------------------------------------------------------
//#define _MINIMAP_SUN						11
//#define _MINIMAP_MOON						12


//----------------------------------------------------------------------

//----------------------------------------------------------------------
#define _INVEN_BMP_ORIGINAL					2		// 인벤토리 원래의 투명 색
#define _PASSIBLABAR_RED					23
#define _PASSIBLABAR_BLUE					24
#define _PASSIBLEBAR_GRAY					312		// 인벤토리에서 비활성화 된 부분 그릴 때 사용

#define _INVEN_BMP_ORIGINAL_SCALE			32
#define _INVEN_BMP_DEACTIVATE_SCALE			1		// 인벤토리 비활성화 시 사용
//----------------------------------------------------------------------
// 퀘스트
//----------------------------------------------------------------------
#define _QUEST_PROGRESS_SLIDE			0	// 진행
#define _QUEST_PROGRESS_SLIDE_UP		0
#define _QUEST_PROGRESS_SLIDE_DOWN		2

#define _QUEST_COMPLETE_SLIDE			1	// 완료
#define _QUEST_COMPLETE_SLIDE_UP		1
#define _QUEST_COMPLETE_SLIDE_DOWN		3


#define _QUEST_TAP_GROUP				0	// 탭
#define _QUEST_PROGRESS_GROUP			1	// 진행
#define _QUEST_COMPLETE_GROUP			2	// 완료
#define _QUEST_DESCRIPT_TEXT			3	// 설명

#define _QUEST_TAP_NOVICE				1	// 초보
#define _QUEST_TAP_SCINARIO				2	// 시나리오
#define _QUEST_TAP_REQUEST				3	// 의뢰

#define _QUEST_LINE_NUM					4	// 각 그룹에 쓸 수있는 줄 수

//-----------------------------------------------------------------------------
// 시스템창에서의 슬라이드
//-----------------------------------------------------------------------------
#define _SYSTEM_WINBRIGHT								0
#define _SYSTEM_BGMSOUND								2
#define _SYSTEM_FXSOUND									1

#define _SYSTEM_LEFT_WINBRIGHT							1
#define _SYSTEM_LEFT_FXSOUNDT							2
#define _SYSTEM_LEFT_BGMSOUND							3

#define _SYSTEM_RIGHT_WINBRIGHT							4
#define _SYSTEM_RIGHT_FXSOUNDT							5
#define _SYSTEM_RIGHT_BGMSOUND							6

#define _SYSTEM_BTN_BRIGHT_LEFT							2
#define _SYSTEM_BTN_FXSOUND_LEFT						3
#define _SYSTEM_BTN_BGMSOUND_LEFT						4
#define _SYSTEM_BTN_BRIGHT_RIGHT						5
#define _SYSTEM_BTN_FXSOUND_RIGHT						6
#define _SYSTEM_BTN_BGMSOUND_RIGHT						7

#define _SYSTEM_SLIDE_BRIGHT							0
#define _SYSTEM_SLIDE_FXSOUND							1
#define _SYSTEM_SLIDE_BGMSOUND							2

#define _SYSTEM_CHECHBOX_FXSOUND						0
#define _SYSTEM_CHECHBOX_BGMSOUND						1
#define _SYSTEM_CHECHBOX_PRIVATECHAT					2
#define _SYSTEM_CHECHBOX_INVITE							3
#define _SYSTEM_CHECHBOX_MONSTER						4
#define _SYSTEM_CHECHBOX_GUILD							5
#define _SYSTEM_CHECHBOX_PARTY							6
#define _SYSTEM_CHECHBOX_OTHERCHARAC					7
#define _SYSTEM_CHECHBOX_OTHERFX						8

#define _OPTION_WIN_BASIC								0
#define _OPTION_WIN_VIDEO								1
#define _OPTION_WIN_SOUND								2
#define _OPTION_WIN_GAME								3

#define _OPTION_GAME_CHECKBOX_MYNAME					0
#define _OPTION_GAME_CHECKBOX_NPCNAME					1
#define _OPTION_GAME_CHECKBOX_OHTERNAME					2
#define _OPTION_GAME_CHECKBOX_INITUI					3
#define _OPTION_GAME_CHECKBOX_ROOTINGMODE				4
#define _OPTION_GAME_CHECKBOX_CHATTINGMODE				5

//----------------------------------------------------------------------
// 파티 & 길드
//----------------------------------------------------------------------
//#define _PARTYGUILD_TAB_PARTY							0
//#define _PARTYGUILD_TAB_GUILD							1

#define _GUILD_TAB_GUILDINFO							0
#define _GUILD_TAB_MEMBERINFO							1
#define _GUILD_TAB_BOARD								2
#define _GUILD_TAB_LEVELSET								3

#define _GUILD_ATTACH1									23
#define _GUILD_ATTACH2									24
#define _GUILD_ATTACH3									25


#define _GUILD_MARK_COLOR_START							847
#define _GUILD_MARK_BACK1_START							859
#define _GUILD_MARK_BACK2_START							871
#define _GUILD_MARK_TITLE_START							883
#define _GUILD_MARK_EX_BACK1_BRA_START					1536
#define _GUILD_MARK_EX_BACK1_VIS_START					1556
#define _GUILD_MARK_EX_BACK1_SIV_START					1576
#define _GUILD_MARK_EX_BACK2_BRA_START					1596
#define _GUILD_MARK_EX_BACK2_VIS_START					1616
#define _GUILD_MARK_EX_BACK2_SIV_START					1636
#define _GUILD_MARK_EX_COLOR_BRA_START					1728
#define _GUILD_MARK_EX_COLOR_VIS_START					1748
#define _GUILD_MARK_EX_COLOR_SIV_START					1768
#define _GUILD_MARK_EX_TITLE_START						1656

#define _GUILD_MARK_COLOR_NUM							12
#define _GUILD_MARK_BACK1_NUM							12
#define _GUILD_MARK_BACK2_NUM							12
#define _GUILD_MARK_TITLE_NUM							24

#define _GUILD_MARK_COLOR1								847
#define _GUILD_MARK_COLOR2								848	
#define _GUILD_MARK_COLOR3								849	
#define _GUILD_MARK_COLOR4								850	
#define _GUILD_MARK_COLOR5								851
#define _GUILD_MARK_COLOR6								852	
#define _GUILD_MARK_COLOR7								853	
#define _GUILD_MARK_COLOR8								854
#define _GUILD_MARK_COLOR9								855	
#define _GUILD_MARK_COLOR10								856	
#define _GUILD_MARK_COLOR11								857	
#define _GUILD_MARK_COLOR12								858	

#define _GUILD_MARK_BACK1_1								859
#define _GUILD_MARK_BACK1_2								860
#define _GUILD_MARK_BACK1_3								861
#define _GUILD_MARK_BACK1_4								862
#define _GUILD_MARK_BACK1_5								863
#define _GUILD_MARK_BACK1_6								864
#define _GUILD_MARK_BACK1_7								865
#define _GUILD_MARK_BACK1_8								866
#define _GUILD_MARK_BACK1_9								867
#define _GUILD_MARK_BACK1_10							868
#define _GUILD_MARK_BACK1_11							869
#define _GUILD_MARK_BACK1_12							870

#define _GUILD_MARK_BACK2_1								871
#define _GUILD_MARK_BACK2_2								872
#define _GUILD_MARK_BACK2_3								873
#define _GUILD_MARK_BACK2_4								874
#define _GUILD_MARK_BACK2_5								875
#define _GUILD_MARK_BACK2_6								876
#define _GUILD_MARK_BACK2_7								877
#define _GUILD_MARK_BACK2_8								878
#define _GUILD_MARK_BACK2_9								879
#define _GUILD_MARK_BACK2_10							880
#define _GUILD_MARK_BACK2_11							881
#define _GUILD_MARK_BACK2_12							882

#define _GUILD_MARK_TITLE1								883
#define _GUILD_MARK_TITLE2								884
#define _GUILD_MARK_TITLE3								885
#define _GUILD_MARK_TITLE4								886
#define _GUILD_MARK_TITLE5								887
#define _GUILD_MARK_TITLE6								888
#define _GUILD_MARK_TITLE7								889
#define _GUILD_MARK_TITLE8								890
#define _GUILD_MARK_TITLE9								891
#define _GUILD_MARK_TITLE10								892
#define _GUILD_MARK_TITLE11								893
#define _GUILD_MARK_TITLE12								894
#define _GUILD_MARK_TITLE13								895
#define _GUILD_MARK_TITLE14								896
#define _GUILD_MARK_TITLE15								897
#define _GUILD_MARK_TITLE16								898
#define _GUILD_MARK_TITLE17								899
#define _GUILD_MARK_TITLE18								900
#define _GUILD_MARK_TITLE19								901
#define _GUILD_MARK_TITLE21								902
#define _GUILD_MARK_TITLE22								903
#define _GUILD_MARK_TITLE23								904
#define _GUILD_MARK_TITLE24								905
#define _GUILD_MARK_TITLE25								906
#define _GUILD_MARK_TITLE26								907
#define _GUILD_MARK_TITLE27								908
#define _GUILD_MARK_TITLE28								909
#define _GUILD_MARK_TITLE29								910
#define _GUILD_MARK_TITLE30								911

#define _GUILD_MARK_BACK1								13
#define _GUILD_MARK_BACK2								14
#define _GUILD_MARK_AMBLEM								15

#define _GUILD_BACK										0
#define _GUILD_SHAPE									1
#define _GUILD_COLOR									2

#define _GUILD_TRIBE_START								26

//----------------------------------------------------------------------
// 주소록
//----------------------------------------------------------------------

#define _ADDRESS_GOD_START								44
#define _ADDRESS_CHARACTER_START						50		
#define _ADDRESS_CAST_START								62
#define _ADDRESS_REGISTE_NUM							9

//----------------------------------------------------------------------
// 지역표시
//----------------------------------------------------------------------
#define _AREAINDICATE_AREAEDIT							0

#define _COMMAND_SIT									26
#define _COMMAND_WALK									27
#define _COMMAND_ATTACK									28
#define _COMMAND_TARGET									29
//#define _COMMAND_TRACE									35
//#define _COMMAND_HELP									36
#define _COMMAND_TRADE									30
#define _COMMAND_PICKUP									31

#define _COMMAND_PARTY									32
#define _COMMAND_PARTY_WITHDRAW							33
#define _COMMAND_PRIVATE_SHOP							34

#define _COMMAND_PROVOKE								35
#define _COMMAND_GREET									36
#define _COMMAND_RUSH									37

//#define _COMMAND_HELP									38
#define _COMMAND_BLOG									39
#define _COMMAND_DUEL									41
#define _COMMAND_AWAY									43
#define _COMMAND_ASSIST									45
#define _COMMAND_DIRECTIONS								47
#define _COMMAND_SIEGE									49

#define _COMMAND_SIT_BMP								688
#define _COMMAND_WALK_BMP								689
#define _COMMAND_ATTACK_BMP								690
#define _COMMAND_TARGET_BMP								691
#define _COMMAND_TRACE_BMP								692
#define _COMMAND_TRADE_BMP								694
#define _COMMAND_PICKUP_BMP								695
#define _COMMAND_PARTY_BMP								687
#define _COMMAND_PARTYWITHDRAW_BMP						699
#define _COMMAND_PRIVATESHOP_BMP						698

#define _COMMAND_PROVOKE_BMP							715
#define _COMMAND_GREET_BMP								716
#define _COMMAND_RUSH_BMP								717

#define _COMMAND_HELP_BMP								693
#define _COMMAND_BLOG_BMP								552
#define _COMMAND_DUEL_BMP								1872
#define _COMMAND_AWAY_BMP								1887
#define _COMMAND_ASSIST_BMP								551

// 차투랑가 보드
#define _CTRG_BOARD_BMP_START							11


#endif