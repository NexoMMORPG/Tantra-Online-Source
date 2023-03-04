#ifndef __PROTOCOL_MESSAGE_STRUCT_H__
#define __PROTOCOL_MESSAGE_STRUCT_H__

#define CSP_REQ_LOGIN                                     0x1001      // 로그인 요청 메시지
#define CSP_REQ_WORLD_LIST                                0x1002      // 월드 서버 리스트 요청
#define CSP_REQ_MOVE_ZONE_SERVER                          0x1003      // 월드 대표 존서버에 접속을 요청
#define CSP_REQ_CHAR_LIST                                 0x1011      // 해당 월드의 캐릭터 리스트 요청
#define CSP_REQ_CHAR_CREATE                               0x1012      // 케릭터 생성을 요청
#define CSP_REQ_CHAR_REMOVE                               0x1013      // 케릭터 삭제를 요청
#define CSP_REQ_ZONE_CONNECT                              0x1014      // 케릭터 선택후 존서버 접속 요청
#define CSP_REQ_EXIT_ZONE_SERVER                          0x1015      // 캐릭터 선택창을 빠져나가고, 월드서버 선택창으로 이동 요청
#define CSP_REQ_CHAR_LOGOUT                               0x1021      // 캐릭터의 로그 아웃을 요청
#define CSP_OTHER_CHAR_LOGOUT                             0x1022      // 캐릭터 로그아웃, 워프, 순간이동의 주변전송 요청
#define CSP_OTHER_CHAR_LOGOUT_NOTIFY                      0x1023      // 캐릭터의 로그아웃, 워프, 순간이동을 파티, 길드, 주소록 관련 케릭터에게 전송요청
#define CSP_INIT_CHAR                                     0x1101      // 캐릭터의 접속초기정보 요청 메세지
#define CSP_INIT_INVENTORY                                0x1102      // 케릭터의 인벤토리정보 전송 요청
#define CSP_INIT_NPC_INVENTORY                            0x1103      // NPC의 인벤토리정보 전송 요청
#define CSP_INIT_SKILL                                    0x1104      // 케릭터의 스킬정보 전송 요청
#define CSP_INIT_GUILD                                    0x1105      // 자신의 길드초기정보를 전송함.
#define CSP_INIT_ADDRESS_BOOK                             0x1106      // 주소록 정보 전송을 요청
#define CSP_REQ_CHAR_HISTORY                              0x1108      // 케릭터 히스토리정보 요청
#define CSP_INIT_EQUIPMENT                                0x1109      // 케릭터 착용장비 요청
#define CSP_INIT_MONSTER_NPC                              0x1111      // 주변 Monster/NPC 정보 전송 요청
#define CSP_INIT_OTHER_CHAR                               0x1112      // 주변 다른 케릭터 정보 전송 요청
#define CSP_INIT_REAL_ADDRESS_BOOK                        0x1113      // 주소록 정보 전송을 요청
#define CSP_INIT_REAL_GUILD                               0x1114      // 길드 정보 전송을 요청
#define CSP_INIT_REAL_GUILD_MEMBER                        0x1115      // 길드 정보 전송을 요청
#define CSP_INIT_ITEM                                     0x1121      // 주변 아이템 데이터 처리 요청 메세지
#define CSP_REQ_INIT_REGEN_CHAR                           0x1131      // 캐릭터 리젠 초기화 요청
#define CSP_INIT_WORLD_USER_COUNT                         0x1161      // 월드별 접속자수를 처리함.
#define CSP_INIT_GUILD_MEMBER                             0x1171      // 자신의 길드원정보를 전송함.
#define CSP_REQ_CHAR_MOVE                                 0x1201      // 캐릭터 이동 요청 메시지
#define CSP_OTHER_CHAR_MOVE                               0x1202      // 캐릭터의 이동성공을 다른 캐릭터에게 알려줌
#define CSP_REQ_ITEM_MOVE                                 0x1203      // 아이템 이동 결과
#define CSP_MAP_ITEM_APPEAR                               0x1204      // 새로운 아이템을 나타난것을 주변캐릭터에게 전송
#define CSP_MAP_ITEM_DISAPPEAR                            0x1205      // 아이템이 사라졌음을 주변캐릭터에게 전송
#define CSP_MONSTER_MOVE_STEP                             0x1206      // 한셀 이동을 주변에 전송
#define CSP_MONSTER_MOVE_NSTEP                            0x1207      // 여러셀 이동을 주변에 전송
#define CSP_MONSTER_MOVE_END                              0x1208      // 여러셀 이동의 결과 좌표를 전송
#define CSP_REQ_ITEM_PACKING                              0x1221      // 아이템 패킹 요청
#define CSP_REQ_ITEM_UNPACKING                            0x1222      // 아이템 언패킹 요청
#define CSP_REQ_ITEM_USE                                  0x1223      // 아이템 사용 요청
#define CSP_ITEM_USE_BROADCAST                            0x1224      // 아이템 사용을 주변 다른 캐릭터들에게 전송 요청
#define CSP_ITEM_REMOVE                                   0x1225      // 인벤토리에서 아이템 사라짐을 요청
#define CSP_REQ_MONEY_MOVE                                0x1226      // 루피아의 이동을 요청
#define CSP_REQ_CHAR_MOVE_BROADCAST                       0x1227      // 케릭터의 이동을 요청한다.
#define CSP_REQ_MOVE_PORTAL                               0x1231      // 포탈을 통한 이동요청을 한다.
#define CSP_REQ_ATK_CHAR                                  0x1301      // 캐릭터의 공격 요청
#define CSP_ATK_CHAR_BROADCAST                            0x1302      // 캐릭터의 공격을 주변 캐릭터들에게 전송 요청
#define CSP_REQ_ITEM_EQUIPMENT                            0x1401      // 아이템 장착을 요청
#define CSP_ITEM_EQUIPMENT_BROADCAST                      0x1402      // 아이템 장착을 주변 캐릭터에게 전송
#define CSP_ITEM_ABRASION                                 0x1411      // 아이템 사라짐을 알림
#define CSP_ITEM_ABRASION_BROADCAST                       0x1412      // 아이템 사라짐을 주변 다른 캐릭터들에게 전송
#define CSP_ITEM_DURABILITY_DECREASE                      0x1413      // 아이템 내구도 감소를 알림
#define CSP_REQ_NORMAL_CHAT                               0x1501      // 일반 채팅 메세지을 요청
#define CSP_NORMAL_CHAT                                   0x1502      // 일반 채팅 메세지 전송 요청
#define CSP_REQ_WHISPER_CHAT                              0x1503      // 귓속말 전송을 요청
#define CSP_WHISPER_CHAT                                  0x1504      // 귓속말 전송 요청
#define CSP_REQ_SHOUT_CHAT                                0x1505      // 외침말 전송을 요청
#define CSP_SHOUT_CHAT                                    0x1506      // 외침말 전송 요청
#define CSP_REQ_PARTY_CHAT                                0x1507      // 파티채팅 메세지 요청
#define CSP_PARTY_CHAT                                    0x1508      // 파티채팅 메세지 전송 요청
#define CSP_REQ_NOTIFY_MESSAGE                            0x1511      // 공지사항 전송 요청
#define CSP_NOTIFY_MESSAGE                                0x1512      // 공지사항 메시지 결과를 전송 요청
#define CSP_REQ_BROADCAST_MESSAGE                         0x1513      // 공지사항 전송 요청
#define CSP_BROADCAST_MESSAGE                             0x1514      // 공지사항 메시지 결과를 전송 요청
#define CSP_REQ_CREATE_PARTY                              0x1601      // 파티 생성요청 메시지
#define CSP_REQ_DISBAND_PARTY                             0x1602      // 파티 해체를 요청
#define CSP_DISBAND_PARTY_BROADCAST                       0x1603      // 파티 해체를 파티원들에게 전송
#define CSP_REQ_JOIN_PARTY                                0x1604      // 파티 참여를 요청
#define CSP_JOIN_PARTY_NOTIFY                             0x1605      // 파티 참여요청 메세지
#define CSP_JOIN_PARTY_RESULT                             0x1606      // 파티 참여 요청 결과를 서버에 전송
#define CSP_JOIN_PARTY_RESULT_NOTIFY                      0x1607      // 파티 참여 요청에 대한 승인 결과를 파티장에게 전송요청 메세지
#define CSP_NEW_PARTY_MEMBER                              0x1608      // 신규 파티원의 정보를 파티원들에게 전송요청 메세지
#define CSP_REQ_SECEDE_PARTY                              0x1609      // 파티 탈퇴(파티장 또는 파티원에 의해 수행됨)를 요청 메세지
#define CSP_SECEDE_PARTY_BROADCAST                        0x160A      // 파티 탈퇴를 파티원들에게 전송요청 메세지
#define CSP_REQ_PARTY_LIST                                0x160B      // 파티원의 리스트를 요청
#define CSP_REQ_CREATE_GUILD                              0x1611      // 길드 생성요청 메시지
#define CSP_REQ_DISBAND_GUILD                             0x1612      // 길드 해체를 요청
#define CSP_CREATE_GUILD_BROADCAST                        0x1613      // 길드 생성을 주변에 알린다.
#define CSP_DISBAND_GUILD_BROADCAST                       0x1614      // 길드 해체를 주변에 알린다.
#define CSP_REQ_JOIN_GUILD                                0x1615      // 길드 참여를 요청
#define CSP_JOIN_GUILD_NOTIFY                             0x1616      // 길드 참여요청 메세지
#define CSP_JOIN_GUILD_RESULT                             0x1617      // 길드 참여 요청 결과를 서버에 전송
#define CSP_JOIN_GUILD_RESULT_NOTIFY                      0x1618      // 길드 참여 요청에 대한 승인 결과를 길드장에게 전송요청 메세지
#define CSP_NEW_GUILD_MEMBER                              0x1619      // 신규 길드원의 정보를 길드원들에게 전송요청 메세지
#define CSP_REQ_SECEDE_GUILD                              0x161A      // 길드 탈퇴(길드장 또는 길드원에 의해 수행됨)를 요청 메세지
#define CSP_SECEDE_GUILD_BROADCAST                        0x161B      // 길드 탈퇴를 길드원들에게 전송요청 메세지
#define CSP_REQ_EXPEL_GUILD_MEMBER                        0x161D      // 길드원의 방출을 요청
#define CSP_EXPEL_GUILD_MEMBER_BROADCAST                  0x161E      // 길드원의 방출을 알린다.
#define CSP_REQ_QUEST_HISTORY                             0x1701      // 퀘스트 히스토리 정보 요청
#define CSP_QUEST_DIALOG                                  0x1702      // 대화문 결과 전송
#define CSP_QUEST_NOTIFY_LEVEL                            0x1703      // 퀘스트 단계 알림
#define CSP_MONSTER_DISAPPEAR                             0x1801      // Monster 사라짐을 알림
#define CSP_CHAR_STATUS                                   0x1802      // 캐릭터의 상태를 알림
#define CSP_CHAR_MONSTER_STATUS_BROADCAST                 0x1803      // 캐릭터Monster의 상태를 주변 다른 캐릭터들 에게 전송함
#define CSP_CHAR_DEATH                                    0x1805      // 캐릭터의 죽음을 알림
#define CSP_CHAR_MONSTER_DEATH_BROADCAST                  0x1806      // 캐릭터/Monster의 죽음을 주변 다른 캐릭터들에게 전송
#define CSP_CHAR_HP_RECOVERY                              0x1811      // 캐릭터의 체력 회복을 알림
#define CSP_MONSTER_HP_RECOVERY                           0x1812      // Monster의 체력 회복을 알림
#define CSP_CHAR_CAST_PROMOTE                             0x1821      // 캐릭터의 카스트 상승을 알림
#define CSP_CHAR_CAST_PROMOTE_BROADCAST                   0x1822      // 캐릭터의 카스트 상승을 주변 다른 캐릭터들에게 전송함
#define CSP_CHAR_PING                                     0x1831      // 케릭터의 게임접속중임을 알린다.
#define CSP_REQ_CHAR_LOCATION                             0x1832      // 케릭터의 게임접속 위치를 요청한다.
#define CSP_CHAR_PARAMS_CHANGE                            0x1911      // 캐릭터 파라메터 변화를 요청함
#define CSP_REQ_CHAKRA_RISING                             0x1921      // 차크라 상승을 요청함
#define CSP_REQ_BRAHMAN_RISING                            0x1922      // 브라만 포인트 상승을 요청함
#define CSP_REQ_INCREASE_INVENTORY_SLOT                   0x1931      // 인벤토리 슬롯 증가를 요청
#define CSP_REQ_DECREASE_INVENTORY_SLOT                   0x1932      // 확장된 인벤토리 슬롯 해제를 요청
#define CSP_REQ_NPC_POINT_UP                              0x1941      // NPC 친절도 상승을 요청함
#define CSP_REQ_CHANGE_CKAKRA_TO_PRANA                    0x1951      // 차크라를 프라나로 변경요청한다
#define CSP_OTHER_CHAR_PARAM_BROADCAST                    0x1952      // 타케릭터의 파라메터변경을 알린다
#define CSP_REQ_SAVE_POSITION                             0x1961      // 케릭터 리젠위치의 저장을 요청한다.
#define CSP_REQ_PVP_RANKING                               0x1971      // PVP랭킹리스트를 요청한다.
#define CSP_REQ_SKILL_REGIST                              0x2001      // 스킬 등록을 요청한다
#define CSP_SKILL_REGIST                                  0x2002      // 카스트 상승에 따른 스킬 자동 등록을 알려준다
#define CSP_REQ_SKILL_SELECT                              0x2003      // 등록된 스킬을 선택/해제
#define CSP_REQ_SKILL_SELECT_BROADCAST                    0x2004      // 등록된 스킬을 선택/해제
#define CSP_REQ_SKILL_USE2_CHAR                           0x2011      // 캐릭터의 스킬 공격 준비동작을 요청
#define CSP_SKILL_READY_CHAR_BROADCAST                    0x2012      // 캐릭터의 스킬 공격 준비동작을 주변에 전송
#define CSP_REQ_SKILL_ATK_CHAR                            0x2013      // 캐릭터의 스킬 공격을 요청
#define CSP_SKILL_ATK_CHAR_BROADCAST                      0x2014      // 캐릭터의 스킬 공격을 주변 캐릭터들에게 전송
#define CSP_REQ_SKILL_LEVEL_UP                            0x2021      // 캐릭터의 스킬 Level-Up을 요청
#define CSP_REQ_SHOP_SKILL_LIST                           0x2022      // 습득 가능한 스킬 List를 요청
#define CSP_REQ_SHOP_ITEM_LIST                            0x2101      // 제작 가능한 아이템 List를 요청
#define CSP_REQ_ITEM_MAKING                               0x2102      // 아이템 제작을 요청
#define CSP_REQ_ITEM_REDEEM                               0x2103      // 제작한 아이템 찾기를 요청
#define CSP_REQ_ITEM_REPAIR                               0x2104      // 아이템 수리를 요청
#define CSP_REQ_ITEM_DISMANTLE                            0x2105      // 아이템 해체를 요청
#define CSP_REQ_ITEM_REFINING                             0x2106      // 아이템 제련을 요청
#define CSP_REQ_PRANA_CONTRIBUTION                        0x2112      // 프라나 헌납을 요청
#define CSP_REQ_RESOURCE_BARTER                           0x2113      // 교환소에서 자원 교환을 요청
#define CSP_REQ_RESOURCE_BARTER_PRICE                     0x2114      // 교환소에서의 자원교환비율을 요청한다.
#define CSP_REQ_EXCHANGE                                  0x2201      // 아이템 교환을 요청
#define CSP_EXCHANGE_NOTIFY                               0x2202      // 아이템 교환 요청
#define CSP_EXCHANGE_RESULT                               0x2203      // 아이템 교환 요청에 대한 결과를 서버에 전송함
#define CSP_EXCHANGE_RESULT_NOTIFY                        0x2204      // 아이템 교환 요청에 대한 결과를 알림요청
#define CSP_REQ_EXCHANGE_ADD                              0x2205      // 아이템 교환창에 아이템 추가 요청
#define CSP_EXCHANGE_ADD_NOTIFY                           0x2206      // 아이템 추가 요청
#define CSP_REQ_EXCHANGE_ERASE                            0x2207      // 아이템 교환창에 아이템 제거 요청
#define CSP_EXCHANGE_ERASE_NOTIFY                         0x2208      // 아이템 제거 요청을 알림요청
#define CSP_EXCHANGE_ACCEPT                               0x2209      // 교환 승인 여부
#define CSP_EXCHANGE_ACCEPT_NOTIFY                        0x220A      // 교환 승인 여부 알림요청
#define CSP_EXCHANGE_CANCEL                               0x220B      // 교환 취소요청
#define CSP_REQ_EXCHANGE_MONEY                            0x220C      // 교환할 돈 추가요청
#define CSP_EXCHANGE_MONEY_NOTIFY                         0x220D      // 돈의 추가를 알림요청
#define CSP_REQ_TRADE_ENTRY                               0x2301      // 거래 등록 요청 메세지
#define CSP_REQ_TRADE_CANCEL                              0x2302      // 거래 등록 취소 요청 메세지
#define CSP_REQ_TRADE                                     0x2303      // 거래 요청 메세지
#define CSP_REQ_TRADE_LIST                                0x2304      // 거래 리스트 요청 메세지
#define CSP_REQ_MY_ENTYR_LIST                             0x2305      // 자신이 등록,보관 아이템 요청
#define CSP_REQ_TRADE_ITEM_SEEK                           0x2306      // 보관 아이템 찾기 요청
#define CSP_REQ_TRANSPARENCY_MODE                         0x2501      // 투명모드를 요청함
#define CSP_TRANSPARENCY_MODE_NOTIFY                      0x2502      // 투명모드를 주변에 전송요청함
#define CSP_REQ_MOVE_POSITION                             0x2511      // 워프이동을 요청함
#define CSP_REQ_MOVE_NEAR_CHAR                            0x2512      // 타케릭근처로 워프이동을 요청함
#define CSP_REQ_CHAR_RECALL                               0x2513      // 타케릭터의 소환을 요청함
#define CSP_CHAR_RECALL_NOTIFY                            0x2514      // GM에 의해 소환됨을 알림요청
#define CSP_REQ_CONTROL_CHAT                              0x2521      // 채팅사용을 금지, 해제 요청함
#define CSP_CONTROL_CHAT_NOTIFY                           0x2522      // 채팅사용 금지, 해제를 알림요청
#define CSP_REQ_CONTROL_ACTION                            0x2531      // 케릭터의 동작멈춤, 해제를 요청함
#define CSP_CONTROL_ACTION_NOTIFY                         0x2532      // GM에 의한 케릭터의 동작멈춤, 해제를 알림요청.
#define CSP_REQ_TROUBLE_REPORT                            0x2541      // 서버에 신고내용을 접수한다.
#define CSP_REQ_TROUBLE_REPORT_LIST                       0x2542      // 서버에 신고내용의 리스트를 요청한다.
#define CSP_REQ_TROUBLE_REPORT_SET                        0x2543      // 신고내용의 처리상황을 받는다.
#define GCSP_REQ_TROUBLE_REPORT_LIST                      0x2544      // 로그인 요청 메시지
#define GCSP_REQ_TROUBLE_REPORT_SET                       0x2545      // 로그인 요청 메시지
#define GCSP_REQ_TROUBLE_REPORT                           0x2546      // 로그인 요청 메시지
#define GCSP_REQ_CHARACTER_SEARCH                         0x2547      // 캐릭터의 정보 요청
#define GCSP_REQ_PARAMETER_CHANGE                         0x2550      // 캐릭터의 기본 정보값을 변경 요청
#define GCSP_REQ_ITEM_INSERT                              0x2551      // 아이템 삽입 요청
#define GCSP_REQ_ITEM_DELETE                              0x2552      // 아이템 삭제 요청
#define GCSP_REQ_SKILL_INSERT                             0x2553      // 스킬 삽입 요청
#define GCSP_REQ_SKILL_DELETE                             0x2554      // 스킬 삭제 요청
#define CSP_REQ_CHAR_INFO                                 0x2561      // 케릭터 정보 요청 메시지
#define CSP_REQ_CHAR_EQUIPMENT                            0x2562      // 케릭터의 장착정보 요청 메시지
#define CSP_REQ_CHAR_SKILL                                0x2563      // 케릭터의 스킬정보 요청 메시지
#define CSP_REQ_CLOSE_CHAR                                0x2571      // 케릭터의 접속종료 요청 메시지
#define CSP_REQ_JOIN_ADDRESS_BOOK                         0x2603      // 주소록에 캐릭터 추가를 요청
#define CSP_JOIN_ADDRESS_BOOK_NOTIFY                      0x2604      // 주소록 추가 요청을 캐릭터에게 전송요청 메세지
#define CSP_REQ_JOIN_ADDRESS_BOOK_RESULT                  0x2605      // 주소록 추가 요청 결과를 서버에 전송
#define CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0x2606      // 주소록 추가 요청에 대한 승인 결과를 캐릭터에게 전송요청메세지
#define CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE                0x2607      // 주소록에 있는 캐릭터 정보의 삭제를 요청
#define CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0x2608      // 주소록에서 삭제를 알린다
#define CSP_REQ_ADDRESS_BOOK_GROUP_ADD                    0x2611      // 주소록에 그룹의 추가를 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_DELETE                 0x2612      // 주소록에 그룹의 삭제를 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_MOVE                   0x2613      // 주소록에 케릭터의 그룹이동을 요청
#define CSP_REQ_ADDRESS_BOOK_GROUP_RENAME                 0x2614      // 주소록에 그룹의 이름변경을 요청
#define CSP_REQ_ADDRESS_BOOK_STATUS                       0x2621      // 주소록 등록요청의 거부를 세팅요청
#define CSP_REQ_INIT_MOBILE                               0x3000      // MOBILE 초기화
#define CSP_REQ_INIT_BAG                                  0x3100      // Initialize the content of the bag
#define CSP_REQ_UPDATE_EQUIPMENT                          0x3110      // Update Equipment
#define CSP_REQ_INIT_SKILLBOOK                            0x3200      // Init Skill Book
#define CSP_REQ_LEARN_SKILL                               0x3210      // Learn a skill
#define CSP_REQ_CAST_SKILL                                0x3220      // cast a skill
#define CSP_CAST_SKILL_BROADCAST                          0x3230      // cast a skill
#define CSP_FIZZLE_SKILL_BROADCAST                        0x3240      // fizzle a skill
#define CSP_REQ_AFFECT_SKILL                              0x3250      // Affect a skill to target
#define CSP_AFFECT_SKILL_BROADCAST                        0x3260      // Affect a skill to target
#define CSP_DEBUFFER_SKILL_BROADCAST                      0x3270      // Debuffer a effect to target
#define CSP_REQ_CHAR_ACT                                  0x3300      // Action
#define CSP_CHAR_ACT_BROADCAST                            0x3310      // Action을 broadcast
#define CSP_REQ_UPDATE_UI                                 0x3500      // Update UI
#define CSP_REQ_UPDATE_STATUS                             0x3501      // Update Status
#define CSP_LEVEL_UP_BROADCAST                            0x3510      // level up
#define CSP_REQ_INCREASE_CHAKRA                           0x3520      // Increase a chakra point
#define SCP_RESP_LOGIN                                    0x9001      // 로그인 응답 메시지
#define SCP_RESP_WORLD_LIST                               0x9002      // 월드 서버 리스트 응답
#define SCP_RESP_MOVE_ZONE_SERVER                         0x9003      // 월드 대표 존서버에 접속 응답
#define SCP_RESP_CHAR_LIST                                0x9011      // 캐릭터 리스트 전송
#define SCP_RESP_CHAR_CREATE                              0x9012      // 케릭터 생성 응답 메시지
#define SCP_RESP_CHAR_REMOVE                              0x9013      // 케릭터 삭제 응답 메세지
#define SCP_RESP_ZONE_CONNECT                             0x9014      // 케릭터 선택후 존서버 접속 응답 메시지
#define SCP_RESP_EXIT_ZONE_SERVER                         0x9015      // 캐릭터 선택창을 빠져나가고, 월드서버 선택창으로 이동 응답 메세지
#define SCP_RESP_CHAR_LOGOUT                              0x9021      // 캐릭터의 로그 아웃 응답 메시지
#define SCP_OTHER_CHAR_LOGOUT                             0x9022      // 캐릭터 로그아웃, 워프, 순간이동의 주변전송 응답 메세지
#define SCP_OTHER_CHAR_LOGOUT_NOTIFY                      0x9023      // 캐릭터의 로그아웃, 워프, 순간이동을 파티, 길드, 주소록 관련 케릭터에게 전송 응답 메세지
#define SCP_INIT_CHAR                                     0x9101      // 캐릭터의 접속초기정보 응답 메세지
#define SCP_INIT_INVENTORY                                0x9102      // 케릭터의 인벤토리정보 전송 응답 메세지
#define SCP_INIT_NPC_INVENTORY                            0x9103      // NPC의 인벤토리정보 전송 응답 메세지
#define SCP_INIT_SKILL                                    0x9104      // 케릭터의 스킬정보 전송 응답 메세지
#define SCP_INIT_GUILD                                    0x9105      // 길드의 실시간 정보 전송 응답 메세지
#define SCP_INIT_ADDRESS_BOOK                             0x9106      // 주소록 정보 전송 응답 메세지
#define SCP_RESP_CHAR_HISTORY                             0x9108      // 케릭터 히스토리정보 응답 메세지
#define SCP_INIT_EQUIPMENT                                0x9109      // 케릭터 착용장비 요청에 대한 응답 메세지
#define SCP_INIT_MONSTER_NPC                              0x9111      // 주변 Monster/NPC 정보 전송 응답 메세지
#define SCP_INIT_OTHER_CHAR                               0x9112      // 주변 다른 케릭터 정보 응답 메세지
#define SCP_INIT_REAL_ADDRESS_BOOK                        0x9113      // 주소록 정보 전송 응답 메세지
#define SCP_INIT_REAL_GUILD                               0x9114      // 길드의 실시간 정보 전송 응답 메세지
#define SCP_INIT_REAL_GUILD_MEMBER                        0x9115      // 길드멤의 실시간 정보 전송 응답 메세지
#define SCP_INIT_ITEM                                     0x9121      // 주변 아이템 데이터 처리 응답 메세지
#define SCP_RESP_INIT_REGEN_CHAR                          0x9131      // 인벤토리내 아이템 위치 저장 응답 메세지
#define SCP_INIT_WORLD_USER_COUNT                         0x9161      // 월드별 접속자수를 처리함.
#define SCP_INIT_GUILD_MEMBER                             0x9171      // 자신의 길드원정보를 전송함.
#define SCP_RESP_CHAR_MOVE                                0x9201      // 캐릭터 이동에 대한 결과 메시지
#define SCP_OTHER_CHAR_MOVE                               0x9202      // 이동정보를 다른 캐릭터에게 알려줌
#define SCP_RESP_ITEM_MOVE                                0x9203      // 아이템 이동 결과
#define SCP_MAP_ITEM_APPEAR                               0x9204      // 새로운 아이템의 종류및 위치 정보를 주변캐릭터에게 전송
#define SCP_MAP_ITEM_DISAPPEAR                            0x9205      // 아이템이 사라진 위치를 주변캐릭터에게 전송
#define SCP_MONSTER_MOVE_STEP                             0x9206      // 한셀 이동을 주변에 전송
#define SCP_MONSTER_MOVE_NSTEP                            0x9207      // 여러셀 이동을 주변에 전송
#define SCP_MONSTER_MOVE_END                              0x9208      // 여러셀 이동의 결과 좌표를 전송
#define SCP_RESP_ITEM_PACKING                             0x9221      // 아이템 패킹 응답 메세지
#define SCP_RESP_ITEM_UNPACKING                           0x9222      // 아이템 언패킹 응답 메세지
#define SCP_RESP_ITEM_USE                                 0x9223      // 아이템 사용 응답 메세지
#define SCP_ITEM_USE_BROADCAST                            0x9224      // 아이템 사용을 주변 다른 캐릭터들에게 전송 응답 메세지
#define SCP_ITEM_REMOVE                                   0x9225      // 인벤토리에서 아이템 사라짐을 알려줌
#define SCP_RESP_MONEY_MOVE                               0x9226      // 루피아의 이동요청에 대한 응답메세지
#define SCP_RESP_CHAR_MOVE_BROADCAST                      0x9227      // 케릭터의 이동을 요청에 대한 응답메세지
#define SCP_RESP_MOVE_PORTAL                              0x9231      // 포탈을 통한 이동요청 결과 전송 응답 메세지
#define SCP_RESP_ATK_CHAR                                 0x9301      // 캐릭터의 공격 응답 메세지
#define SCP_ATK_CHAR_BROADCAST                            0x9302      // 캐릭터의 공격을 주변 캐릭터들에게 전송 응답 메세지
#define SCP_RESP_ITEM_EQUIPMENT                           0x9401      // 아이템 장착 요청에 대한 결과
#define SCP_ITEM_EQUIPMENT_BROADCAST                      0x9402      // 아이템 장착을 주변 캐릭터에게 전송
#define SCP_ITEM_ABRASION                                 0x9411      // 아이템 사라짐을 알림 응답 메세지
#define SCP_ITEM_ABRASION_BROADCAST                       0x9412      // 아이템 사라짐을 주변 다른 캐릭터들에게 전송 응답 메세지
#define SCP_ITEM_DURABILITY_DECREASE                      0x9413      // 아이템 내구도 감소 응답 메세지
#define SCP_RESP_NORMAL_CHAT                              0x9501      // 일반 채팅용청에 대한 결과 응답 메세지
#define SCP_NORMAL_CHAT                                   0x9502      // 일반 채팅 메세지 전송에 대한 결과 응답 메세지
#define SCP_RESP_WHISPER_CHAT                             0x9503      // 귓속말 채팅 요청에 대한 결과 응답 메세지
#define SCP_WHISPER_CHAT                                  0x9504      // 귓속말 전송에 대한 결과 응답 메세지
#define SCP_RESP_SHOUT_CHAT                               0x9505      // 외침말 채팅 결과 응답 메세지
#define SCP_SHOUT_CHAT                                    0x9506      // 외침말 채팅 결과 요청 메세지
#define SCP_RESP_PARTY_CHAT                               0x9507      // 파티 채팅 결과 응답 메세지
#define SCP_PARTY_CHAT                                    0x9508      // 파티 채팅 결과 응답 메세지
#define SCP_RESP_NOTIFY_MESSAGE                           0x9511      // 공지사항 전송 결과 응답 메세지
#define SCP_NOTIFY_MESSAGE                                0x9512      // 공지사항 채팅 결과 응답 메세지
#define SCP_RESP_BROADCAST_MESSAGE                        0x9513      // 공지사항 전송 결과 응답 메세지
#define SCP_BROADCAST_MESSAGE                             0x9514      // 공지사항 채팅 결과 응답 메세지
#define SCP_RESP_CREATE_PARTY                             0x9601      // 파티 생성요청 응답메세지
#define SCP_RESP_DISBAND_PARTY                            0x9602      // 파티 해체요청 응답메세지
#define SCP_DISBAND_PARTY_BROADCAST                       0x9603      // 파티 해체를 파티원들에게 전송
#define SCP_RESP_JOIN_PARTY                               0x9604      // 파티 참여요청 응답메세지
#define SCP_JOIN_PARTY_NOTIFY                             0x9605      // 파티 참여요청 응답메세지
#define SCP_JOIN_PARTY_RESULT                             0x9606      // 파티 참여 요청 결과에 대한 서버 응답메세지
#define SCP_JOIN_PARTY_RESULT_NOTIFY                      0x9607      // 파티 참여 요청에 대한 승인결과 파티장에게 전송
#define SCP_NEW_PARTY_MEMBER                              0x9608      // 신규 파티원의 정보를 파티원들에게 전송
#define SCP_RESP_SECEDE_PARTY                             0x9609      // 파티 탈퇴요청에 대한 응답 메세지
#define SCP_SECEDE_PARTY_BROADCAST                        0x960A      // 파티 탈퇴를 파티원들에게 전송
#define SCP_RESP_PARTY_LIST                               0x960B      // 파티원 리스트에 대한 응답메세지
#define SCP_RESP_CREATE_GUILD                             0x9611      // 길드 생성요청 응답메세지
#define SCP_RESP_DISBAND_GUILD                            0x9612      // 길드 해체요청 응답메세지
#define SCP_CREATE_GUILD_BROADCAST                        0x9613      // 길드 생성을 주변에 알린다.
#define SCP_DISBAND_GUILD_BROADCAST                       0x9614      // 길드 해체를 주변에 알린다.
#define SCP_RESP_JOIN_GUILD                               0x9615      // 길드 참여요청 응답메세지
#define SCP_JOIN_GUILD_NOTIFY                             0x9616      // 길드 참여요청 응답메세지
#define SCP_JOIN_GUILD_RESULT                             0x9617      // 길드 참여 요청 결과에 대한 서버 응답메세지
#define SCP_JOIN_GUILD_RESULT_NOTIFY                      0x9618      // 길드 참여 요청에 대한 승인결과 길드장에게 전송
#define SCP_NEW_GUILD_MEMBER                              0x9619      // 신규 길드원의 정보를 길드원들에게 전송
#define SCP_RESP_SECEDE_GUILD                             0x961A      // 길드 탈퇴요청에 대한 응답 메세지
#define SCP_SECEDE_GUILD_BROADCAST                        0x961B      // 길드 탈퇴를 길드원들에게 전송
#define SCP_RESP_EXPEL_GUILD_MEMBER                       0x961D      // 길드 탈퇴요청에 대한 결과 메세지
#define SCP_EXPEL_GUILD_MEMBER_BROADCAST                  0x961E      // 길드원의 방출을 알린다.
#define SCP_RESP_QUEST_HISTORY                            0x9701      // 퀘스트 히스토리 정보 전송
#define SCP_QUEST_DIALOG                                  0x9702      // 대화문 출력
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // 퀘스트 단계 알림
#define SCP_MONSTER_DISAPPEAR                             0x9801      // Monster 사라짐을 알림
#define SCP_CHAR_STATUS                                   0x9802      // 캐릭터의 상태를 알림
#define SCP_CHAR_MONSTER_STATUS_BROADCAST                 0x9803      // 캐릭터Monster의 상태를 주변 다른 캐릭터들 에게 전송함
#define SCP_CHAR_DEATH                                    0x9805      // 캐릭터의 죽음을 알림
#define SCP_CHAR_MONSTER_DEATH_BROADCAST                  0x9806      // 캐릭터/Monster의 죽음을 주변 다른 캐릭터들에게 전송
#define SCP_CHAR_HP_RECOVERY                              0x9811      // 캐릭터의 체력 회복을 알림
#define SCP_MONSTER_HP_RECOVERY                           0x9812      // Monster의 체력 회복을 알림
#define SCP_CHAR_CAST_PROMOTE                             0x9821      // 캐릭터의 카스트 상승을 알림
#define SCP_CHAR_CAST_PROMOTE_BROADCAST                   0x9822      // 캐릭터의 카스트 상승을 주변 다른 캐릭터들에게 전송함
#define SCP_CHAR_PING                                     0x9831      // 케릭터의 게임접속중임을 알린다.
#define SCP_RESP_CHAR_LOCATION                            0x9832      // 케릭터의 게임접속 위치를 알린다.
#define SCP_CHAR_PARAMS_CHANGE                            0x9911      // 캐릭터 파라메터 변화를 전송함
#define SCP_RESP_CHAKRA_RISING                            0x9921      // 차크라 상승 요청 결과를 전송함
#define SCP_RESP_BRAHMAN_RISING                           0x9922      // 브라만 포인트 상승 요청 결과를 전송함
#define SCP_RESP_INCREASE_INVENTORY_SLOT                  0x9931      // 인벤토리 슬롯 증가 요청 결과를 전송함
#define SCP_RESP_DECREASE_INVENTORY_SLOT                  0x9932      // 확장된 인벤토리 슬롯 해제를 요청
#define SCP_RESP_NPC_POINT_UP                             0x9941      // NPC 친절도 상승 요청 결과를 전송함
#define SCP_RESP_CHANGE_CKAKRA_TO_PRANA                   0x9951      // 차크라를 프라나로 변경요청 결과
#define SCP_OTHER_CHAR_PARAM_BROADCAST                    0x9952      // 타케릭터의 파라메터변경을 알린다
#define SCP_RESP_SAVE_POSITION                            0x9961      // 리젠위치 저장요청결과를 전송한다.
#define SCP_RESP_PVP_RANKING                              0x9971      // PVP랭킹리스트를 전송한다.
#define SCP_RESP_SKILL_REGIST                             0xA001      // 스킬 등록 결과 응답 메세지
#define SCP_SKILL_REGIST                                  0xA002      // 카스트 상승에 따른 스킬 자동 등록 결과 응답 메세지
#define SCP_RESP_SKILL_SELECT                             0xA003      // 등록된 스킬을 선택/해제 결과 응답 메세지
#define SCP_RESP_SKILL_SELECT_BROADCAST                   0xA004      // 등록된 스킬을 선택/해제 결과 응답 메세지
#define SCP_RESP_SKILL_USE2_CHAR                          0xA011      // 캐릭터의 스킬 공격 준비동작 요청 결과 메세지
#define SCP_SKILL_READY_CHAR_BROADCAST                    0xA012      // 캐릭터의 스킬 공격 준비동작을 주변에 전송결과 메세지
#define SCP_RESP_SKILL_ATK_CHAR                           0xA013      // 캐릭터의 스킬 공격 응답 메세지
#define SCP_SKILL_ATK_CHAR_BROADCAST                      0xA014      // 캐릭터의 스킬 공격을 주변 캐릭터들에게 전송 결과 메세지
#define SCP_RESP_SKILL_LEVEL_UP                           0xA021      // 캐릭터의 스킬 Level-Up 요청 결과 메세지
#define SCP_RESP_SHOP_SKILL_LIST                          0xA022      // 습득 가능한 스킬 List 요청에 대한 응답메세지
#define SCP_RESP_SHOP_ITEM_LIST                           0xA101      // 제작 가능한 아이템 List 요청에 대한 응답메세지
#define SCP_RESP_ITEM_MAKING                              0xA102      // 아이템 제작을 요청에 대한 응답메세지
#define SCP_RESP_ITEM_REDEEM                              0xA103      // 제작한 아이템 찾기요청에 대한 응답메세지
#define SCP_RESP_ITEM_REPAIR                              0xA104      // 아이템 수리요청에 대한 응답메세지
#define SCP_RESP_ITEM_DISMANTLE                           0xA105      // 아이템 해체 요청에 대한 응답메세지
#define SCP_RESP_ITEM_REFINING                            0xA106      // 아이템 제련 요청에 대한 응답메세지
#define SCP_RESP_PRANA_CONTRIBUTION                       0xA112      // 프라나 헌납을 요청에 대한 응답메세지
#define SCP_RESP_RESOURCE_BARTER                          0xA113      // 교환소에서 자원 교환요청에 대한 응답메세지
#define SCP_RESP_RESOURCE_BARTER_PRICE                    0xA114      // 교환소에서의 자원교환비율을 요청한다.
#define SCP_RESP_EXCHANGE                                 0xA201      // 아이템 교환요청에 대한 응답메세지
#define SCP_EXCHANGE_NOTIFY                               0xA202      // 아이템 교환 요청을 알림메세지
#define SCP_EXCHANGE_RESULT                               0xA203      // 아이템 교환 요청에 대한 결과에 대한 서버의 응답메세지
#define SCP_EXCHANGE_RESULT_NOTIFY                        0xA204      // 아이템 교환 요청에 대한 결과를 알림메세지
#define SCP_RESP_EXCHANGE_ADD                             0xA205      // 아이템 교환창에 아이템 추가 요청에 대한 응답메세지
#define SCP_EXCHANGE_ADD_NOTIFY                           0xA206      // 아이템 추가 요청을 알림메세지
#define SCP_RESP_EXCHANGE_ERASE                           0xA207      // 아이템 교환창에 아이템 제거 요청에 대한 응답 메세지
#define SCP_EXCHANGE_ERASE_NOTIFY                         0xA208      // 아이템 제거 요청을 알림메세지
#define SCP_EXCHANGE_ACCEPT                               0xA209      // 교환 승인 여부에 대한 응답메세지
#define SCP_EXCHANGE_ACCEPT_NOTIFY                        0xA20A      // 교환 승인 여부 알림메세지
#define SCP_EXCHANGE_CANCEL                               0xA20B      // 교환 취소요청에 대한 응답메세지
#define SCP_RESP_EXCHANGE_MONEY                           0xA20C      // 아이템 교환창에 돈 추가 요청에 대한 응답 메세지
#define SCP_EXCHANGE_MONEY_NOTIFY                         0xA20D      // 돈의 추가를 알림
#define SCP_RESP_TRADE_ENTRY                              0xA301      // 거래 등록 요청 결과 메세지
#define SCP_RESP_TRADE_CANCEL                             0xA302      // 거래 등록 취소 요청 결과 메세지
#define SCP_RESP_TRADE                                    0xA303      // 거래 요청 결과 메세지
#define SCP_RESP_TRADE_LIST                               0xA304      // 거래 리스트 요청 결과 메세지
#define SCP_RESP_MY_ENTYR_LIST                            0xA305      // 자신이 등록,보관 아이템 결과 메세지
#define SCP_RESP_TRADE_ITEM_SEEK                          0xA306      // 보관 아이템 찾기 결과 메세지
#define SCP_RESP_TRADE_SUCCESS                            0xA307      // 거래성사시 등록자에게 알려주는 메세지
#define SCP_RESP_TRANSPARENCY_MODE                        0xA501      // 투명모드 요청에 대한 응답메세지
#define SCP_TRANSPARENCY_MODE_NOTIFY                      0xA502      // 투명모드를 주변에 전송함
#define SCP_RESP_MOVE_POSITION                            0xA511      // 워프이동에 대한 응답메세지
#define SCP_RESP_MOVE_NEAR_CHAR                           0xA512      // 타케릭근처로의 워프이동 결과메세지
#define SCP_RESP_CHAR_RECALL                              0xA513      // 타케릭터의 소환에 대한 결과메세지
#define SCP_CHAR_RECALL_NOTIFY                            0xA514      // GM에 의해 소환됨을 알림
#define SCP_RESP_CONTROL_CHAT                             0xA521      // 채팅사용의 금지, 해제 요청에 대한 응답메세지
#define SCP_CONTROL_CHAT_NOTIFY                           0xA522      // 채팅사용 금지, 해제 알림
#define SCP_RESP_CONTROL_ACTION                           0xA531      // 케릭터의 동작멈춤, 해제를 요청에 대한 응답메세지
#define SCP_CONTROL_ACTION_NOTIFY                         0xA532      // GM에 의한 케릭터의 동작멈춤, 해제를 알림.
#define SCP_RESP_TROUBLE_REPORT                           0xA541      // 서버에 신고내용을 접수한다.
#define SCP_RESP_TROUBLE_REPORT_LIST                      0xA542      // 서버에 신고내용의 리스트를 요청한다.
#define SCP_RESP_TROUBLE_REPORT_SET                       0xA543      // 신고내용의 처리상황을 받는다.
#define GSCP_RESP_TROUBLE_REPORT_LIST                     0xA544      // 로그인 응답 메시지
#define GSCP_RESP_TROUBLE_REPORT_SET                      0xA545      // 로그인 응답 메시지
#define GSCP_RESP_TROUBLE_REPORT                          0xA546      // 로그인 응답 메시지
#define GSCP_INIT_CHAR                                    0xA547      // 캐릭터 기본정보
#define GSCP_INIT_ITEM                                    0xA548      // 캐릭터 아이템 정보
#define GSCP_INIT_SKILL                                   0xA549      // 캐릭터 스킬 정보
#define GSCP_RESP_PARAMETER_CHANGE                        0xA550      // 캐릭터의 기본 정보값을 변경 요청에 대한 결과
#define GSCP_RESP_ITEM_INSERT                             0xA551      // 아이템 삽입 결과
#define GSCP_RESP_ITEM_DELETE                             0xA552      // 아이템 삭제 결과
#define GSCP_RESP_SKILL_INSERT                            0xA553      // 스킬 삽입 결과
#define GSCP_RESP_SKILL_DELETE                            0xA554      // 스킬 삭제 결과
#define SCP_RESP_CHAR_INFO                                0xA561      // 케릭터 정보 응답 메시지
#define SCP_RESP_CHAR_EQUIPMENT                           0xA562      // 케릭터의 장착정보 응답 메시지
#define SCP_RESP_CHAR_SKILL                               0xA563      // 케릭터의 스킬정보 응답 메시지
#define SCP_RESP_CLOSE_CHAR                               0xA571      // 케릭터의 접속종료 응답 메시지
#define SCP_RESP_JOIN_ADDRESS_BOOK                        0xA603      // 주소록에 캐릭터추가 요청에 대한 응답메세지
#define SCP_JOIN_ADDRESS_BOOK_NOTIFY                      0xA604      // 주소록 추가 요청을 캐릭터에게 전송메세지
#define SCP_RESP_JOIN_ADDRESS_BOOK_RESULT                 0xA605      // 주소록 추가 요청 결과에 결과 메세지
#define SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0xA606      // 주소록 추가 요청에 대한 승인 결과를 캐릭터에게 전송
#define SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE               0xA607      // 주소록에 있는 캐릭터 정보의 삭제요청에 대한 응답메세지
#define SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0xA608      // 주소록에서 삭제를 알린다
#define SCP_RESP_ADDRESS_BOOK_GROUP_ADD                   0xA611      // 주소록에 그룹의 추가 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_DELETE                0xA612      // 주소록에 그룹의 삭제 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_MOVE                  0xA613      // 주소록에 케릭터의 그룹이동 요청에 대한 응답메세지
#define SCP_RESP_ADDRESS_BOOK_GROUP_RENAME                0xA614      // 주소록에 그룹의 이름변경을 요청결과
#define SCP_RESP_ADDRESS_BOOK_STATUS                      0xA621      // 주소록 등록요청의 거부를 세팅요청
#define SCP_RESP_INIT_MOBILE                              0xB000      // MOBILE 초기화
#define SCP_RESP_INIT_BAG                                 0xB100      // Initialize the content of the bag
#define SCP_RESP_UPDATE_EQUIPMENT                         0xB110      // Update Equipment
#define SCP_RESP_INIT_SKILLBOOK                           0xB200      // Init Skill Book
#define SCP_RESP_LEARN_SKILL                              0xB210      // Learn a skill
#define SCP_RESP_CAST_SKILL                               0xB220      // cast a skill
#define SCP_CAST_SKILL_BROADCAST                          0xB230      // cast a skill
#define SCP_FIZZLE_SKILL_BROADCAST                        0xB240      // fizzle a skill
#define SCP_RESP_AFFECT_SKILL                             0xB250      // Affect a skill to target
#define SCP_AFFECT_SKILL_BROADCAST                        0xB260      // Affect a skill to target
#define SCP_DEBUFFER_SKILL_BROADCAST                      0xB270      // Debuffer a effect to target
#define SCP_RESP_CHAR_ACT                                 0xB300      // Action
#define SCP_CHAR_ACT_BROADCAST                            0xB310      // Action을 broadcast
#define SCP_RESP_UPDATE_UI                                0xB500      // Update UI
#define SCP_RESP_UPDATE_STATUS                            0xB501      // Update Status
#define SCP_LEVEL_UP_BROADCAST                            0xB510      // level up
#define SCP_RESP_INCREASE_CHAKRA                          0xB520      // Increase a chakra point

#pragma pack(push, 1)

// Protocol Message Header
typedef struct _S_HEADER
{
	WORD                                              wType;        // Message ID Field
	WORD                                              wSeq;         // Packet Seq Number Field
	WORD                                              wPDULength;   // PDU Length Field
	DWORD                                             dwClientTick; // Client's Sended Tick

} S_HEADER, * PS_HEADER;


inline void Header_NTOH(PS_HEADER __pHeader) {
	__pHeader->wType = ntohs(__pHeader->wType);
	__pHeader->wSeq = ntohs(__pHeader->wSeq);
	__pHeader->wPDULength = ntohs(__pHeader->wPDULength);
	__pHeader->dwClientTick = ntohl(__pHeader->dwClientTick);
}

inline void Header_HTON(PS_HEADER __pHeader) {
	__pHeader->wType = htons(__pHeader->wType);
	__pHeader->wSeq = htons(__pHeader->wSeq);
	__pHeader->wPDULength = htons(__pHeader->wPDULength);
	__pHeader->dwClientTick = htonl(__pHeader->dwClientTick);
}

typedef struct _S_TNITEM_DATA
{
	DWORD                                             dwKeyID;      // Item handle
	int                                               iID;          // Item ID
	short                                             snDur;        // Item 내구성
	BYTE                                              nPack;        // Item 중첩개수
	WORD                                              wrgMaterial[10];// 추가되는 보조재료

} S_TNITEM_DATA, * PS_TNITEM_DATA;


typedef struct _S_TNSKILL_DATA
{
	int                                               iID;          // Skill ID
	BYTE                                              byLevel;      // Skill Level

} S_TNSKILL_DATA, * PS_TNSKILL_DATA;


typedef struct _S_TNCHAKRA
{
	short                                             snMuscle;     // 근육 차크라
	short                                             snNerves;     // 신경 차크라
	short                                             snHeart;      // 심장 차크라
	short                                             snMind;       // 정신 차크라

} S_TNCHAKRA, * PS_TNCHAKRA;


typedef struct _S_TNRESIST
{
	short                                             snFire;       // fire 저항
	short                                             snCold;       // cold 저항
	short                                             snLightning;  // lightning 저항
	short                                             snPoison;     // poison 저항

} S_TNRESIST, * PS_TNRESIST;


typedef struct _S_TNDAMAGE
{
	short                                             snMin;        // 최소
	short                                             snMax;        // 최대

} S_TNDAMAGE, * PS_TNDAMAGE;


typedef struct _S_SERVER_LIST
{
	BYTE                                              byServerStatus;
	char                                              szServerName[26];
	char                                              szServerIP[16];
	WORD                                              wServerPort;  

} S_SERVER_LIST, * PS_SERVER_LIST;


typedef struct _S_ITEM_INFO
{
	BYTE                                              byEquipPart;  
	DWORD                                             dwItemIndex;  

} S_ITEM_INFO, * PS_ITEM_INFO;


typedef struct _S_EQUIPITEM_INFO
{
	BYTE                                              byEquipPart;  
	DWORD                                             dwItemIndex;  
	BYTE                                              byCount;      

} S_EQUIPITEM_INFO, * PS_EQUIPITEM_INFO;


typedef struct _S_CHARACTER_LIST
{
	char                                              szCharName[26];
	BYTE                                              byFaceType;   
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byTrimuritiClass;
	int                                               nBrahmanPoint;
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	int                                               nChakraPoint; 
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	int                                               nPrana;       
	BYTE                                              byCount;      

} S_CHARACTER_LIST, * PS_CHARACTER_LIST;


typedef struct _S_SUBITEM
{
	DWORD                                             dwUseIndex;   
	short                                             snUseCount;   

} S_SUBITEM, * PS_SUBITEM;


typedef struct _S_TRADEITEM
{
	DWORD                                             dwUseIndex;   
	DWORD                                             dwItemKeyID;  
	short                                             snUseCount;   

} S_TRADEITEM, * PS_TRADEITEM;


typedef struct _S_TRADEITEMLIST
{
	DWORD                                             dwUseIndex;   
	short                                             snUseCount;   
	short                                             snCurDurability;
	S_SUBITEM                                         AddSubItem[10];

} S_TRADEITEMLIST, * PS_TRADEITEMLIST;


typedef struct _S_TRADEITEMMYLIST
{
	DWORD                                             dwUseIndex;   
	DWORD                                             dwItemKeyID;  
	short                                             snUseCount;   
	short                                             snCurDurability;
	S_SUBITEM                                         AddSubItem[10];

} S_TRADEITEMMYLIST, * PS_TRADEITEMMYLIST;


typedef struct _S_GUILD_SKILL
{
	DWORD                                             dwIndex;      // 스킬인덱스
	BYTE                                              byLevel;      // 현재 스킬레벨

} S_GUILD_SKILL, * PS_GUILD_SKILL;


typedef struct _S_GUILD_MEMBER_INFO
{
	char                                              szName[26];   // 길드원 캐릭터의 이름
	BYTE                                              byTrimuritiClass;// 캐릭터의 주신계급
	BYTE                                              bySpecialName;// 캐릭터의 특수칭호
	BYTE                                              byGuildAuthority;// 길드내의 지위
	BYTE                                              byTribe;      // 캐릭터의 종족
	BYTE                                              byCastClass;  // 캐릭터의 카스트 계급
	BYTE                                              byCastGrade;  // 캐릭터의 카스트 등급
	BYTE                                              byConnect;    // 캐릭터의 접속여부
	int                                               nContribution;// 캐릭터의 길드내 공헌도

} S_GUILD_MEMBER_INFO, * PS_GUILD_MEMBER_INFO;


typedef struct _S_PARTY_MEMBER_INFO
{
	char                                              szName[26];   // 파티원 캐릭터의 이름
	BYTE                                              byMember;     // 파티내의 직위
	BYTE                                              byTrimuriti;  // 캐릭터의 주신
	BYTE                                              byTribe;      // 캐릭터의 종족
	BYTE                                              byCastClass;  // 캐릭터의 카스트 등급
	BYTE                                              byCastGrade;  // 캐릭터의 카스트 계급
	int                                               nMaxHP;       // 캐릭터 최대 HP
	int                                               nCurHP;       // 캐릭터 현재 HP
	BYTE                                              byRegion;     // 캐릭터의 접속 Region
	BYTE                                              byZone;       // 캐릭터의 접속 Zone

} S_PARTY_MEMBER_INFO, * PS_PARTY_MEMBER_INFO;


typedef struct _S_QUEST_HISTORY_INFO
{
	BYTE                                              byIndex;      // 플래그 인덱스
	BYTE                                              byValue;      // 플래스 값

} S_QUEST_HISTORY_INFO, * PS_QUEST_HISTORY_INFO;


typedef struct _S_KEY_ID
{
	DWORD                                             dwKeyID;      

} S_KEY_ID, * PS_KEY_ID;


typedef struct _S_INVENTORY_EXPAND_INFO
{
	BYTE                                              byIndex;      
	BYTE                                              bySizeX;      
	BYTE                                              bySizeZ;      

} S_INVENTORY_EXPAND_INFO, * PS_INVENTORY_EXPAND_INFO;


typedef struct _S_PVP_INFO
{
	char                                              szCharName[26];
	DWORD                                             dwWin;        
	DWORD                                             dwLose;       
	DWORD                                             dwPVPPoint;   

} S_PVP_INFO, * PS_PVP_INFO;


typedef struct _S_SKILL_INDEX
{
	DWORD                                             dwIndex;      

} S_SKILL_INDEX, * PS_SKILL_INDEX;


typedef struct _S_ITEM_INDEX
{
	BYTE                                              byFriendly;   
	DWORD                                             dwIndex;      

} S_ITEM_INDEX, * PS_ITEM_INDEX;


typedef struct _S_SUBITEMKEY
{
	DWORD                                             dwKeyID;      

} S_SUBITEMKEY, * PS_SUBITEMKEY;


typedef struct _S_ITEM_INVEN
{
	DWORD                                             dwKeyID;      // 교환된 아이템의 KeyID
	int                                               nItemIndex;   // 교환된 아이템의 Index 번호
	short                                             snItemCount;  // 교환된 아이템의 중첩 개수
	BYTE                                              byX;          // 인벤토리내 X 좌표
	BYTE                                              byZ;          // 인벤토리내 Z 좌표

} S_ITEM_INVEN, * PS_ITEM_INVEN;


typedef struct _S_USER_REPORT_LIST
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // 처리상황
	char                                              szReport[512];

} S_USER_REPORT_LIST, * PS_USER_REPORT_LIST;


typedef struct _S_REPORT_LIST
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	char                                              szCharName[26];
	BYTE                                              byWorld;      
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // 처리상황
	char                                              szReport[512];
	char                                              szNote[256];  // 비고

} S_REPORT_LIST, * PS_REPORT_LIST;


typedef struct _S_EQUIPITEM
{
	BYTE                                              byPlace;      // 아이템의 위치
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // 중첩갯수
	BYTE                                              byX;          // 아이템 X좌표
	BYTE                                              byZ;          // 아이템 Z좌표
	S_SUBITEM                                         AddSubItem[10];

} S_EQUIPITEM, * PS_EQUIPITEM;


typedef struct _S_SKILLINFO
{
	BYTE                                              byType;       // Skill의 종류
	DWORD                                             dwIndex;      // Skill Index
	BYTE                                              byLevel;      // Skill Level

} S_SKILLINFO, * PS_SKILLINFO;


typedef struct _S_ADDRESS_MEMBER_INFO
{
	char                                              szGroup[26];  // 캐릭터의 소속그룹이름
	char                                              szName[26];   // 주소록 캐릭터의 이름
	BYTE                                              byTrimuriti;  // 캐릭터의 주신
	BYTE                                              byTribe;      // 캐릭터의 종족
	BYTE                                              byCastClass;  // 캐릭터의 카스트 등급
	BYTE                                              byCastGrade;  // 캐릭터의 카스트 계급
	WORD                                              wServerID;    // 케릭터가 위치한 서버ID

} S_ADDRESS_MEMBER_INFO, * PS_ADDRESS_MEMBER_INFO;


// CSP_REQ_INIT_MOBILE : 0x3000
typedef struct _S_CSP_REQ_INIT_MOBILE
{
	char                                              szAccountID[18];// Char ID Field
	char                                              szPassword[18];// Password Field

} S_CSP_REQ_INIT_MOBILE, * PS_CSP_REQ_INIT_MOBILE;


// SCP_RESP_INIT_MOBILE : 0xB000
typedef struct _S_SCP_RESP_INIT_MOBILE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_INIT_MOBILE, * PS_SCP_RESP_INIT_MOBILE;


// CSP_REQ_INIT_BAG : 0x3100
typedef struct _S_CSP_REQ_INIT_BAG
{

} S_CSP_REQ_INIT_BAG, * PS_CSP_REQ_INIT_BAG;


// SCP_RESP_INIT_BAG : 0xB100
typedef struct _S_SCP_RESP_INIT_BAG
{
	BYTE                                              nBagID;       // bag ID(0~2)
	S_TNITEM_DATA                                     krgItem[24];  // bag에 포함되는 장비 정보

} S_SCP_RESP_INIT_BAG, * PS_SCP_RESP_INIT_BAG;


// CSP_REQ_UPDATE_EQUIPMENT : 0x3110
typedef struct _S_CSP_REQ_UPDATE_EQUIPMENT
{

} S_CSP_REQ_UPDATE_EQUIPMENT, * PS_CSP_REQ_UPDATE_EQUIPMENT;


// SCP_RESP_UPDATE_EQUIPMENT : 0xB110
typedef struct _S_SCP_RESP_UPDATE_EQUIPMENT
{
	DWORD                                             dwKeyID;      // PC handle
	short                                             snX;          // PC의 현재 x 좌표
	short                                             snZ;          // PC의 현재 y 좌표
	S_TNITEM_DATA                                     krgItem[14];  // equipment에 포함되는 장비 정보

} S_SCP_RESP_UPDATE_EQUIPMENT, * PS_SCP_RESP_UPDATE_EQUIPMENT;


// CSP_REQ_INIT_SKILLBOOK : 0x3200
typedef struct _S_CSP_REQ_INIT_SKILLBOOK
{

} S_CSP_REQ_INIT_SKILLBOOK, * PS_CSP_REQ_INIT_SKILLBOOK;


// SCP_RESP_INIT_SKILLBOOK : 0xB200
typedef struct _S_SCP_RESP_INIT_SKILLBOOK
{
	S_TNSKILL_DATA                                    krgSkill[20]; // skill book에 포함되는 skill 정보

} S_SCP_RESP_INIT_SKILLBOOK, * PS_SCP_RESP_INIT_SKILLBOOK;


// CSP_REQ_LEARN_SKILL : 0x3210
typedef struct _S_CSP_REQ_LEARN_SKILL
{
	int                                               iID;          // Skill ID

} S_CSP_REQ_LEARN_SKILL, * PS_CSP_REQ_LEARN_SKILL;


// SCP_RESP_LEARN_SKILL : 0xB210
typedef struct _S_SCP_RESP_LEARN_SKILL
{
	BYTE                                              byRes;        // Result
	S_TNSKILL_DATA                                    kSkill;       // level up될 skill 정보

} S_SCP_RESP_LEARN_SKILL, * PS_SCP_RESP_LEARN_SKILL;


// CSP_REQ_CAST_SKILL : 0x3220
typedef struct _S_CSP_REQ_CAST_SKILL
{
	int                                               iID;          // Skill ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snMapX;       // Target map x 좌표
	short                                             snMapZ;       // Target map y 좌표

} S_CSP_REQ_CAST_SKILL, * PS_CSP_REQ_CAST_SKILL;


// SCP_RESP_CAST_SKILL : 0xB220
typedef struct _S_SCP_RESP_CAST_SKILL
{

} S_SCP_RESP_CAST_SKILL, * PS_SCP_RESP_CAST_SKILL;


// CSP_CAST_SKILL_BROADCAST : 0x3230
typedef struct _S_CSP_CAST_SKILL_BROADCAST
{

} S_CSP_CAST_SKILL_BROADCAST, * PS_CSP_CAST_SKILL_BROADCAST;


// SCP_CAST_SKILL_BROADCAST : 0xB230
typedef struct _S_SCP_CAST_SKILL_BROADCAST
{
	BYTE                                              byRes;        // Result
	S_TNSKILL_DATA                                    kSkill;       // cast한 skill 정보
	int                                               iCastTime;    // Cast Time(Casting delay)
	BYTE                                              byCasterType; // Caster type
	DWORD                                             dwCasterKeyID;// Caster handle
	short                                             snCasterX;    // Caster의 현재 x 좌표
	short                                             snCasterZ;    // Caster의 현재 y 좌표
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target의 현재 x 좌표
	short                                             snTargetZ;    // Target의 현재 y 좌표
	short                                             snMapX;       // Target map x 좌표
	short                                             snMapZ;       // Target map y 좌표

} S_SCP_CAST_SKILL_BROADCAST, * PS_SCP_CAST_SKILL_BROADCAST;


// CSP_FIZZLE_SKILL_BROADCAST : 0x3240
typedef struct _S_CSP_FIZZLE_SKILL_BROADCAST
{

} S_CSP_FIZZLE_SKILL_BROADCAST, * PS_CSP_FIZZLE_SKILL_BROADCAST;


// SCP_FIZZLE_SKILL_BROADCAST : 0xB240
typedef struct _S_SCP_FIZZLE_SKILL_BROADCAST
{
	BYTE                                              byCasterType; // Caster type
	DWORD                                             dwCasterKeyID;// Caster handle
	short                                             snCasterX;    // Caster의 현재 x 좌표
	short                                             snCasterZ;    // Caster의 현재 y 좌표
	BYTE                                              byStrikerType;// Striker type
	DWORD                                             dwStrikerKeyID;// Striker handle
	short                                             snStrikerX;   // Striker의 현재 x 좌표
	short                                             snStrikerZ;   // Striker의 현재 y 좌표

} S_SCP_FIZZLE_SKILL_BROADCAST, * PS_SCP_FIZZLE_SKILL_BROADCAST;


// CSP_REQ_AFFECT_SKILL : 0x3250
typedef struct _S_CSP_REQ_AFFECT_SKILL
{
	int                                               iID;          // Skill ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snMapX;       // Target map x 좌표
	short                                             snMapZ;       // Target map y 좌표

} S_CSP_REQ_AFFECT_SKILL, * PS_CSP_REQ_AFFECT_SKILL;


// SCP_RESP_AFFECT_SKILL : 0xB250
typedef struct _S_SCP_RESP_AFFECT_SKILL
{

} S_SCP_RESP_AFFECT_SKILL, * PS_SCP_RESP_AFFECT_SKILL;


// CSP_AFFECT_SKILL_BROADCAST : 0x3260
typedef struct _S_CSP_AFFECT_SKILL_BROADCAST
{

} S_CSP_AFFECT_SKILL_BROADCAST, * PS_CSP_AFFECT_SKILL_BROADCAST;


// SCP_AFFECT_SKILL_BROADCAST : 0xB260
typedef struct _S_SCP_AFFECT_SKILL_BROADCAST
{
	BYTE                                              byRes;        // Result(정상적으로 공격을 가했으면 성공, 어떤 이유에 의해 가격도 못했으면 실패)
	S_TNSKILL_DATA                                    kSkill;       // cast한 skill 정보
	int                                               iCoolDownTime;// Cool-down 시간
	BYTE                                              byCombatRes;  // Combat Result(Normal, CriticalHit, Dodge, ...)
	int                                               iDamage;      // Damage
	BYTE                                              byCasterType; // Caster type
	DWORD                                             dwCasterKeyID;// Caster handle
	short                                             snCasterX;    // Caster의 현재 x 좌표
	short                                             snCasterZ;    // Caster의 현재 y 좌표
	int                                               iCasterHP;    // Caster의 현 HP
	int                                               iCasterTP;    // Caster의 현 TP
	BYTE                                              byTargetType; // Target type
	short                                             snMapX;       // Target map x 좌표
	short                                             snMapZ;       // Target map y 좌표
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target의 현재 x 좌표
	short                                             snTargetZ;    // Target의 현재 y 좌표
	int                                               iTargetHP;    // Target의 현 HP
	int                                               iTargetTP;    // Target의 현 TP

} S_SCP_AFFECT_SKILL_BROADCAST, * PS_SCP_AFFECT_SKILL_BROADCAST;


// CSP_DEBUFFER_SKILL_BROADCAST : 0x3270
typedef struct _S_CSP_DEBUFFER_SKILL_BROADCAST
{

} S_CSP_DEBUFFER_SKILL_BROADCAST, * PS_CSP_DEBUFFER_SKILL_BROADCAST;


// SCP_DEBUFFER_SKILL_BROADCAST : 0xB270
typedef struct _S_SCP_DEBUFFER_SKILL_BROADCAST
{
	int                                               iEffectID;    // debuffer될 effect ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target의 현재 x 좌표
	short                                             snTargetZ;    // Target의 현재 y 좌표
	int                                               iTargetHP;    // Target의 현 HP
	int                                               iTargetTP;    // Target의 현 TP
	int                                               iMoveSpeed;   // Target의 현 MoveSpeed
	int                                               iAttackSpeed; // Target의 현 AttackSpeed

} S_SCP_DEBUFFER_SKILL_BROADCAST, * PS_SCP_DEBUFFER_SKILL_BROADCAST;


// CSP_REQ_CHAR_ACT : 0x3300
typedef struct _S_CSP_REQ_CHAR_ACT
{
	BYTE                                              byAct;        // 취하려는 행동

} S_CSP_REQ_CHAR_ACT, * PS_CSP_REQ_CHAR_ACT;


// SCP_RESP_CHAR_ACT : 0xB300
typedef struct _S_SCP_RESP_CHAR_ACT
{

} S_SCP_RESP_CHAR_ACT, * PS_SCP_RESP_CHAR_ACT;


// CSP_CHAR_ACT_BROADCAST : 0x3310
typedef struct _S_CSP_CHAR_ACT_BROADCAST
{

} S_CSP_CHAR_ACT_BROADCAST, * PS_CSP_CHAR_ACT_BROADCAST;


// SCP_CHAR_ACT_BROADCAST : 0xB310
typedef struct _S_SCP_CHAR_ACT_BROADCAST
{
	DWORD                                             dwKeyID;      // PC handle
	BYTE                                              byAct;        // 취하려는 행동

} S_SCP_CHAR_ACT_BROADCAST, * PS_SCP_CHAR_ACT_BROADCAST;


// CSP_REQ_UPDATE_UI : 0x3500
typedef struct _S_CSP_REQ_UPDATE_UI
{

} S_CSP_REQ_UPDATE_UI, * PS_CSP_REQ_UPDATE_UI;


// SCP_RESP_UPDATE_UI : 0xB500
typedef struct _S_SCP_RESP_UPDATE_UI
{
	short                                             snX;          // 현재 x 좌표
	short                                             snZ;          // 현재 y 좌표
	int                                               iMoveSpeed;   // 현 MoveSpeed
	int                                               iAttackSpeed; // 현 AttackSpeed
	BYTE                                              byLevel;      // 현 Level
	int                                               iBramanPoint; // 현 Braman point
	BYTE                                              byCaste;      // Caste 계급
	int                                               iTitle;       // Title
	int                                               iMaxPrana;    // 최대 Prana
	int                                               iPrana;       // 현 Prana
	S_TNCHAKRA                                        krgChakra[2]; // 0:base chakra, 1:changed chakra
	short                                             snCPRemaining;// 남은 Chakra Point
	short                                             snSPRemaining;// 남은 Skill Point
	int                                               iHP;          // 현 HP
	int                                               iMaxHP;       // 최대 HP
	int                                               iHPRecovery;  // HP회복량/초
	int                                               iTP;          // 현 TP
	int                                               iMaxTP;       // 최대 TP
	int                                               iTPRecovery;  // TP회복량/초
	short                                             snAC;         // AC
	short                                             snAttackRate; // Attack Rate
	short                                             snDodgeRate;  // Dodge Rate
	S_TNRESIST                                        kResist;      // 저항
	S_TNDAMAGE                                        krgDamage[2]; // 0:Physical, 1:Magical

} S_SCP_RESP_UPDATE_UI, * PS_SCP_RESP_UPDATE_UI;


// CSP_REQ_UPDATE_STATUS : 0x3501
typedef struct _S_CSP_REQ_UPDATE_STATUS
{

} S_CSP_REQ_UPDATE_STATUS, * PS_CSP_REQ_UPDATE_STATUS;


// SCP_RESP_UPDATE_STATUS : 0xB501
typedef struct _S_SCP_RESP_UPDATE_STATUS
{
	short                                             snX;          // 현재 x 좌표
	short                                             snZ;          // 현재 y 좌표
	int                                               iPrana;       // 현 Prana
	int                                               iHP;          // 현 HP
	int                                               iHPRecovery;  // HP회복량/초
	int                                               iTP;          // 현 TP
	int                                               iTPRecovery;  // TP회복량/초

} S_SCP_RESP_UPDATE_STATUS, * PS_SCP_RESP_UPDATE_STATUS;


// CSP_LEVEL_UP_BROADCAST : 0x3510
typedef struct _S_CSP_LEVEL_UP_BROADCAST
{

} S_CSP_LEVEL_UP_BROADCAST, * PS_CSP_LEVEL_UP_BROADCAST;


// SCP_LEVEL_UP_BROADCAST : 0xB510
typedef struct _S_SCP_LEVEL_UP_BROADCAST
{
	DWORD                                             dwKeyID;      // PC handle
	BYTE                                              byLevel;      // 현 Level

} S_SCP_LEVEL_UP_BROADCAST, * PS_SCP_LEVEL_UP_BROADCAST;


// CSP_REQ_INCREASE_CHAKRA : 0x3520
typedef struct _S_CSP_REQ_INCREASE_CHAKRA
{
	BYTE                                              byChakra;     // 올리려는 chakra(0:muscle, 1:nerves, 2:heart, 3:mind)

} S_CSP_REQ_INCREASE_CHAKRA, * PS_CSP_REQ_INCREASE_CHAKRA;


// SCP_RESP_INCREASE_CHAKRA : 0xB520
typedef struct _S_SCP_RESP_INCREASE_CHAKRA
{

} S_SCP_RESP_INCREASE_CHAKRA, * PS_SCP_RESP_INCREASE_CHAKRA;


// CSP_REQ_LOGIN : 0x1001
typedef struct _S_CSP_REQ_LOGIN
{
	char                                              szAccountID[18];// Char ID Field
	char                                              szPassword[18];// Password Field

} S_CSP_REQ_LOGIN, * PS_CSP_REQ_LOGIN;


// SCP_RESP_LOGIN : 0x9001
typedef struct _S_SCP_RESP_LOGIN
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_LOGIN, * PS_SCP_RESP_LOGIN;


// CSP_REQ_WORLD_LIST : 0x1002
typedef struct _S_CSP_REQ_WORLD_LIST
{

} S_CSP_REQ_WORLD_LIST, * PS_CSP_REQ_WORLD_LIST;


// SCP_RESP_WORLD_LIST : 0x9002
typedef struct _S_SCP_RESP_WORLD_LIST
{
	BYTE                                              byWorldCount; // World Server Count Field

} S_SCP_RESP_WORLD_LIST, * PS_SCP_RESP_WORLD_LIST;


// CSP_REQ_MOVE_ZONE_SERVER : 0x1003
typedef struct _S_CSP_REQ_MOVE_ZONE_SERVER
{
	char                                              szAccountID[18];// Char ID Field
	char                                              szPassword[18];// Password Field
	char                                              szCharName[26];// Character Name

} S_CSP_REQ_MOVE_ZONE_SERVER, * PS_CSP_REQ_MOVE_ZONE_SERVER;


// SCP_RESP_MOVE_ZONE_SERVER : 0x9003
typedef struct _S_SCP_RESP_MOVE_ZONE_SERVER
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_MOVE_ZONE_SERVER, * PS_SCP_RESP_MOVE_ZONE_SERVER;


// CSP_REQ_CHAR_LIST : 0x1011
typedef struct _S_CSP_REQ_CHAR_LIST
{

} S_CSP_REQ_CHAR_LIST, * PS_CSP_REQ_CHAR_LIST;


// SCP_RESP_CHAR_LIST : 0x9011
typedef struct _S_SCP_RESP_CHAR_LIST
{
	BYTE                                              byTrimuriti;  // 생성 불가능한 주신
	BYTE                                              byCount;      

} S_SCP_RESP_CHAR_LIST, * PS_SCP_RESP_CHAR_LIST;


// CSP_REQ_CHAR_CREATE : 0x1012
typedef struct _S_CSP_REQ_CHAR_CREATE
{
	char                                              szCharName[26];
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byFaceType;   

} S_CSP_REQ_CHAR_CREATE, * PS_CSP_REQ_CHAR_CREATE;


// SCP_RESP_CHAR_CREATE : 0x9012
typedef struct _S_SCP_RESP_CHAR_CREATE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CHAR_CREATE, * PS_SCP_RESP_CHAR_CREATE;


// CSP_REQ_CHAR_REMOVE : 0x1013
typedef struct _S_CSP_REQ_CHAR_REMOVE
{
	char                                              szCharName[26];
	char                                              szJumin[16];  

} S_CSP_REQ_CHAR_REMOVE, * PS_CSP_REQ_CHAR_REMOVE;


// SCP_RESP_CHAR_REMOVE : 0x9013
typedef struct _S_SCP_RESP_CHAR_REMOVE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CHAR_REMOVE, * PS_SCP_RESP_CHAR_REMOVE;


// CSP_REQ_ZONE_CONNECT : 0x1014
typedef struct _S_CSP_REQ_ZONE_CONNECT
{
	char                                              szCharName[26];
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	BYTE                                              byConnType;   // 접속위치

} S_CSP_REQ_ZONE_CONNECT, * PS_CSP_REQ_ZONE_CONNECT;


// SCP_RESP_ZONE_CONNECT : 0x9014
typedef struct _S_SCP_RESP_ZONE_CONNECT
{
	BYTE                                              byResult;     // Result Field
	WORD                                              wServerID;    // Server ID
	char                                              szZoneIP[16]; 
	WORD                                              wZonePort;    

} S_SCP_RESP_ZONE_CONNECT, * PS_SCP_RESP_ZONE_CONNECT;


// CSP_REQ_EXIT_ZONE_SERVER : 0x1015
typedef struct _S_CSP_REQ_EXIT_ZONE_SERVER
{

} S_CSP_REQ_EXIT_ZONE_SERVER, * PS_CSP_REQ_EXIT_ZONE_SERVER;


// SCP_RESP_EXIT_ZONE_SERVER : 0x9015
typedef struct _S_SCP_RESP_EXIT_ZONE_SERVER
{
	BYTE                                              byWorldCount; // World Server Count Field

} S_SCP_RESP_EXIT_ZONE_SERVER, * PS_SCP_RESP_EXIT_ZONE_SERVER;


// CSP_REQ_CHAR_LOGOUT : 0x1021
typedef struct _S_CSP_REQ_CHAR_LOGOUT
{

} S_CSP_REQ_CHAR_LOGOUT, * PS_CSP_REQ_CHAR_LOGOUT;


// SCP_RESP_CHAR_LOGOUT : 0x9021
typedef struct _S_SCP_RESP_CHAR_LOGOUT
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CHAR_LOGOUT, * PS_SCP_RESP_CHAR_LOGOUT;


// CSP_OTHER_CHAR_LOGOUT : 0x1022
typedef struct _S_CSP_OTHER_CHAR_LOGOUT
{

} S_CSP_OTHER_CHAR_LOGOUT, * PS_CSP_OTHER_CHAR_LOGOUT;


// SCP_OTHER_CHAR_LOGOUT : 0x9022
typedef struct _S_SCP_OTHER_CHAR_LOGOUT
{
	DWORD                                             dwKeyID;      
	BYTE                                              byResult;     // 접속종료 스타일

} S_SCP_OTHER_CHAR_LOGOUT, * PS_SCP_OTHER_CHAR_LOGOUT;


// CSP_OTHER_CHAR_LOGOUT_NOTIFY : 0x1023
typedef struct _S_CSP_OTHER_CHAR_LOGOUT_NOTIFY
{

} S_CSP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_CSP_OTHER_CHAR_LOGOUT_NOTIFY;


// SCP_OTHER_CHAR_LOGOUT_NOTIFY : 0x9023
typedef struct _S_SCP_OTHER_CHAR_LOGOUT_NOTIFY
{
	char                                              szCharName[26];
	BYTE                                              byResult;     // 접속종료 스타일
	BYTE                                              byRegion;     
	BYTE                                              byZone;       

} S_SCP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_SCP_OTHER_CHAR_LOGOUT_NOTIFY;


// CSP_INIT_CHAR : 0x1101
typedef struct _S_CSP_INIT_CHAR
{
	BYTE                                              byConnType;   // 접속유형
	BYTE                                              byConnPos;    // 접속위치
	WORD                                              wPortalID;    // 접속포탈ID
	char                                              szCharName[26];

} S_CSP_INIT_CHAR, * PS_CSP_INIT_CHAR;


// SCP_INIT_CHAR : 0x9101
typedef struct _S_SCP_INIT_CHAR
{
	BYTE                                              byResult;     // 초기화 결과
	char                                              szCharName[26];
	DWORD                                             dwKeyID;      
	BYTE                                              byRegion;     // 케릭터의 Region 위치
	BYTE                                              byZone;       // 케릭터의 Zone 위치
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	short                                             snDegree;     
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byFaceType;   
	DWORD                                             dwCharBirth;  
	DWORD                                             dwGameTime;   
	BYTE                                              byWhether;    
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	BYTE                                              byTrimuritiClass;
	BYTE                                              bySpecialName;
	DWORD                                             dwSpecialNameGetTime;
	char                                              szGuildName[26];
	BYTE                                              byMaster;     // 길드멤버 구분
	DWORD                                             dwGuildMark;  
	int                                               nBrahmanPoint;
	int                                               nNextCastBrahmanPoint;
	int                                               nSumChakraPoint;
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	short                                             snPureChakraMuscle;// 순수 근육의 차크라
	short                                             snPureChakraNerve;// 순수 신경의 차크라
	short                                             snPureChakraHeart;// 순수 심장의 차크라
	short                                             snPureChakraSoul;// 순수 정신의 차크라
	short                                             snChakraMusclePrana;
	short                                             snChakraNervePrana;
	short                                             snChakraHeartPrana;
	short                                             snChakraSoulPrana;
	int                                               nPrana;       // 총 프라나의 양
	short                                             snUsePranaMuscle;
	short                                             snUsePranaNerve;
	short                                             snUsePranaHeart;
	short                                             snUsePranaSoul;
	int                                               nMaxHP;       // 케릭터 HP의 최대값
	int                                               nCurHP;       // 케릭터 HP의 현재값
	DWORD                                             dwRightSkill; 
	DWORD                                             dwLeftSkill;  
	short                                             snMinPhysicalDamage;
	short                                             snMaxPhysicalDamage;
	short                                             snMinMagicDamage;
	short                                             snMaxMagicDamage;
	short                                             snMinFireDamage;
	short                                             snMaxFireDamage;
	short                                             snMinColdDamage;
	short                                             snMaxColdDamage;
	short                                             snMinPoisonDamage;
	short                                             snMaxPoisonDamage;
	short                                             snMinAcidDamage;
	short                                             snMaxAcidDamage;
	BYTE                                              byCriticalHitRate;
	short                                             snAttackSuccRate;
	short                                             snAvoidanceRate;
	short                                             snBlockRate;  
	short                                             snArmorIntensity;
	short                                             snPranaCreateRate;
	short                                             snMovingSpeed;
	short                                             snAttackSpeed;
	short                                             snCastingSpeed;
	short                                             snFireResist; // 불 저항력
	short                                             snColdResist; // 추위 저항력
	short                                             snPoisonResist;// 독 저항력
	short                                             snAcidResist; // 산 저항력
	short                                             snReserved;   // 예비
	int                                               nNPCFriedly1; 
	int                                               nNPCFriedly2; 
	int                                               nNPCFriedly3; 
	int                                               nNPCFriedly4; 
	int                                               nNPCFriedly5; 
	int                                               nMonsterCount;
	int                                               nPKCount;     
	int                                               nCvsCWin;     
	int                                               nCvsCLose;    
	int                                               nPvsPWin;     
	int                                               nPvsPLose;    
	int                                               nGvsGWin;     
	int                                               nGvsGLose;    
	int                                               nStatus;      // 케릭터의 상태
	BYTE                                              byGMStatus;   // GM에 의한 캐릭터의 세팅상태
	BYTE                                              byUserStatus; // 유저에 의한 캐릭터의 세팅상태
	int                                               nPCMoney;     // 캐릭터 보유 루피아
	int                                               nNPCMoney;    // 창고 보유 루피아
	int                                               nCloth;       // 캐릭터의 보유 직물 카운트
	DWORD                                             dwBagIndex;   // 확장 인벤토리 Bag Index

} S_SCP_INIT_CHAR, * PS_SCP_INIT_CHAR;


// CSP_INIT_INVENTORY : 0x1102
typedef struct _S_CSP_INIT_INVENTORY
{

} S_CSP_INIT_INVENTORY, * PS_CSP_INIT_INVENTORY;


// SCP_INIT_INVENTORY : 0x9102
typedef struct _S_SCP_INIT_INVENTORY
{
	BYTE                                              byPlace;      // 아이템의 위치
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // 중첩갯수
	BYTE                                              byX;          // 아이템 X좌표
	BYTE                                              byZ;          // 아이템 Z좌표
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_INVENTORY, * PS_SCP_INIT_INVENTORY;


// CSP_INIT_NPC_INVENTORY : 0x1103
typedef struct _S_CSP_INIT_NPC_INVENTORY
{

} S_CSP_INIT_NPC_INVENTORY, * PS_CSP_INIT_NPC_INVENTORY;


// SCP_INIT_NPC_INVENTORY : 0x9103
typedef struct _S_SCP_INIT_NPC_INVENTORY
{
	BYTE                                              byPlace;      // 아이템의 위치
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // 중첩갯수
	BYTE                                              byX;          // 아이템 X좌표
	BYTE                                              byZ;          // 아이템 Z좌표
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_NPC_INVENTORY, * PS_SCP_INIT_NPC_INVENTORY;


// CSP_INIT_SKILL : 0x1104
typedef struct _S_CSP_INIT_SKILL
{

} S_CSP_INIT_SKILL, * PS_CSP_INIT_SKILL;


// SCP_INIT_SKILL : 0x9104
typedef struct _S_SCP_INIT_SKILL
{
	BYTE                                              byType;       // Skill의 종류
	DWORD                                             dwIndex;      // Skill Index
	BYTE                                              byLevel;      // Skill Level
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리

} S_SCP_INIT_SKILL, * PS_SCP_INIT_SKILL;


// CSP_INIT_GUILD : 0x1105
typedef struct _S_CSP_INIT_GUILD
{
	char                                              szGuildName[26];// 길드 이름

} S_CSP_INIT_GUILD, * PS_CSP_INIT_GUILD;


// SCP_INIT_GUILD : 0x9105
typedef struct _S_SCP_INIT_GUILD
{
	char                                              szGuildName[26];// 길드 이름
	char                                              szGuildBoard[256];// 길드 게시판
	char                                              szCastleName[26];// 길드성 이름
	DWORD                                             dwGuildMark;  // 길드마크
	short                                             snCastleLevel;// 요새 업그레이드레벨
	BYTE                                              byTrimuriti;  // 주신
	int                                               nPrana;       // 길드보유 프라나
	int                                               nLupia;       // 길드보유 루피아
	int                                               nGuildPoint;  // 길드포인트
	DWORD                                             dwCost;       // 길드유지비용
	S_GUILD_SKILL                                     S_Skill[8];   // 길드스킬정보

} S_SCP_INIT_GUILD, * PS_SCP_INIT_GUILD;


// CSP_INIT_GUILD_MEMBER : 0x1171
typedef struct _S_CSP_INIT_GUILD_MEMBER
{
	char                                              szGuildName[26];// 길드 이름

} S_CSP_INIT_GUILD_MEMBER, * PS_CSP_INIT_GUILD_MEMBER;


// SCP_INIT_GUILD_MEMBER : 0x9171
typedef struct _S_SCP_INIT_GUILD_MEMBER
{
	S_GUILD_MEMBER_INFO                               S_Member;     // 길드원 정보

} S_SCP_INIT_GUILD_MEMBER, * PS_SCP_INIT_GUILD_MEMBER;


// CSP_INIT_REAL_GUILD : 0x1114
typedef struct _S_CSP_INIT_REAL_GUILD
{

} S_CSP_INIT_REAL_GUILD, * PS_CSP_INIT_REAL_GUILD;


// SCP_INIT_REAL_GUILD : 0x9114
typedef struct _S_SCP_INIT_REAL_GUILD
{
	char                                              szGuildName[26];
	short                                             snPranaRatio; 
	short                                             snLupiaRatio; 
	short                                             snMaxMember;  

} S_SCP_INIT_REAL_GUILD, * PS_SCP_INIT_REAL_GUILD;


// CSP_INIT_REAL_GUILD_MEMBER : 0x1115
typedef struct _S_CSP_INIT_REAL_GUILD_MEMBER
{

} S_CSP_INIT_REAL_GUILD_MEMBER, * PS_CSP_INIT_REAL_GUILD_MEMBER;


// SCP_INIT_REAL_GUILD_MEMBER : 0x9115
typedef struct _S_SCP_INIT_REAL_GUILD_MEMBER
{
	char                                              szCharName[26];
	BYTE                                              byTrimuritiClass;
	BYTE                                              bySpecialName;
	BYTE                                              byGuildAuthority;
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	BYTE                                              byConnect;    
	int                                               nMaxHP;       
	int                                               nCurHP;       
	int                                               nContribution;

} S_SCP_INIT_REAL_GUILD_MEMBER, * PS_SCP_INIT_REAL_GUILD_MEMBER;


// CSP_INIT_ADDRESS_BOOK : 0x1106
typedef struct _S_CSP_INIT_ADDRESS_BOOK
{

} S_CSP_INIT_ADDRESS_BOOK, * PS_CSP_INIT_ADDRESS_BOOK;


// SCP_INIT_ADDRESS_BOOK : 0x9106
typedef struct _S_SCP_INIT_ADDRESS_BOOK
{
	char                                              szGroupName[26];
	char                                              szCharName[26];
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	WORD                                              wServerID;    // 케릭터의 현재 위치

} S_SCP_INIT_ADDRESS_BOOK, * PS_SCP_INIT_ADDRESS_BOOK;


// CSP_INIT_REAL_ADDRESS_BOOK : 0x1113
typedef struct _S_CSP_INIT_REAL_ADDRESS_BOOK
{

} S_CSP_INIT_REAL_ADDRESS_BOOK, * PS_CSP_INIT_REAL_ADDRESS_BOOK;


// SCP_INIT_REAL_ADDRESS_BOOK : 0x9113
typedef struct _S_SCP_INIT_REAL_ADDRESS_BOOK
{
	char                                              szCharName[26];
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	WORD                                              wServerID;    // 케릭터의 현재 위치

} S_SCP_INIT_REAL_ADDRESS_BOOK, * PS_SCP_INIT_REAL_ADDRESS_BOOK;


// CSP_REQ_CHAR_HISTORY : 0x1108
typedef struct _S_CSP_REQ_CHAR_HISTORY
{

} S_CSP_REQ_CHAR_HISTORY, * PS_CSP_REQ_CHAR_HISTORY;


// SCP_RESP_CHAR_HISTORY : 0x9108
typedef struct _S_SCP_RESP_CHAR_HISTORY
{
	DWORD                                             dwStartTime;  // 히스토리 발생 시간
	WORD                                              wType;        // 히스토리 종류
	char                                              szContent[26];// 히스토리 내용

} S_SCP_RESP_CHAR_HISTORY, * PS_SCP_RESP_CHAR_HISTORY;


// CSP_INIT_EQUIPMENT : 0x1109
typedef struct _S_CSP_INIT_EQUIPMENT
{

} S_CSP_INIT_EQUIPMENT, * PS_CSP_INIT_EQUIPMENT;


// SCP_INIT_EQUIPMENT : 0x9109
typedef struct _S_SCP_INIT_EQUIPMENT
{
	BYTE                                              byPlace;      // 아이템의 장착 위치
	DWORD                                             dwKeyID;      // 아이템의 KeyID
	DWORD                                             dwIndex;      // 아이템의 Index
	short                                             snCurDurability;
	short                                             snCount;      // 아이템의 수량(중첩갯수)
	BYTE                                              byX;          // 아이템 장착 X 좌표(0부터 시작)
	BYTE                                              byZ;          // 아이템 장착 Z 좌표(0부터 시작)
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_EQUIPMENT, * PS_SCP_INIT_EQUIPMENT;


// CSP_INIT_MONSTER_NPC : 0x1111
typedef struct _S_CSP_INIT_MONSTER_NPC
{
	DWORD                                             dwKeyID;      

} S_CSP_INIT_MONSTER_NPC, * PS_CSP_INIT_MONSTER_NPC;


// SCP_INIT_MONSTER_NPC : 0x9111
typedef struct _S_SCP_INIT_MONSTER_NPC
{
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	BYTE                                              byType;       
	BYTE                                              byTrimuriti;  
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	DWORD                                             dwStatus;     
	int                                               nMaxHP;       
	int                                               nCurHP;       
	int                                               nSpeed;       
	short                                             snDestX;      
	short                                             snDestZ;      
	BYTE                                              bySize;       // 몬스터의 크기

} S_SCP_INIT_MONSTER_NPC, * PS_SCP_INIT_MONSTER_NPC;


// CSP_INIT_OTHER_CHAR : 0x1112
typedef struct _S_CSP_INIT_OTHER_CHAR
{
	DWORD                                             dwKeyID;      

} S_CSP_INIT_OTHER_CHAR, * PS_CSP_INIT_OTHER_CHAR;


// SCP_INIT_OTHER_CHAR : 0x9112
typedef struct _S_SCP_INIT_OTHER_CHAR
{
	DWORD                                             dwKeyID;      
	char                                              szName[26];   
	char                                              szGuild[26];  
	DWORD                                             dwGuildMark;  
	BYTE                                              byMember;     
	BYTE                                              byFace;       
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	BYTE                                              bySpecialName;
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	DWORD                                             dwStatus;     
	BYTE                                              byGMStatus;   
	int                                               nMaxHP;       
	int                                               nCurHP;       
	BYTE                                              byType;       
	BYTE                                              byDir;        // 케릭터의 이동상태 및 이동방향 정보. 서기, 앉기정보포함
	short                                             snTargetX;    // 케릭터의 이동시의 X좌표
	short                                             snTargetZ;    // 케릭터의 이동시의 Z좌표
	DWORD                                             dwActionSkill;
	BYTE                                              byActionLevel;
	DWORD                                             dwActiveSkill;
	BYTE                                              byActiveLevel;
	BYTE                                              byCount;      // 장착한 아이템의 개수

} S_SCP_INIT_OTHER_CHAR, * PS_SCP_INIT_OTHER_CHAR;


// CSP_INIT_ITEM : 0x1121
typedef struct _S_CSP_INIT_ITEM
{
	DWORD                                             dwKeyID;      

} S_CSP_INIT_ITEM, * PS_CSP_INIT_ITEM;


// SCP_INIT_ITEM : 0x9121
typedef struct _S_SCP_INIT_ITEM
{
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	BYTE                                              byPlace;      
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_ITEM, * PS_SCP_INIT_ITEM;


// CSP_REQ_INIT_REGEN_CHAR : 0x1131
typedef struct _S_CSP_REQ_INIT_REGEN_CHAR
{
	BYTE                                              byConnType;   

} S_CSP_REQ_INIT_REGEN_CHAR, * PS_CSP_REQ_INIT_REGEN_CHAR;


// SCP_RESP_INIT_REGEN_CHAR : 0x9131
typedef struct _S_SCP_RESP_INIT_REGEN_CHAR
{
	BYTE                                              byRegion;     // 케릭터의 Region 위치
	BYTE                                              byZone;       // 케릭터의 Zone 위치
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	short                                             snDegree;     
	DWORD                                             dwGameTime;   
	BYTE                                              byWhether;    
	int                                               nPrana;       // 총 프라나의 양
	int                                               nMaxHP;       // 케릭터 HP의 최대값
	int                                               nCurHP;       // 케릭터 HP의 현재값
	int                                               nMonsterCount;
	int                                               nPKCount;     
	int                                               nCvsCWin;     
	int                                               nCvsCLose;    
	int                                               nPvsPWin;     
	int                                               nPvsPLose;    
	int                                               nGvsGWin;     
	int                                               nGvsGLose;    
	int                                               nStatus;      // 케릭터의 상태

} S_SCP_RESP_INIT_REGEN_CHAR, * PS_SCP_RESP_INIT_REGEN_CHAR;


// CSP_INIT_WORLD_USER_COUNT : 0x1161
typedef struct _S_CSP_INIT_WORLD_USER_COUNT
{

} S_CSP_INIT_WORLD_USER_COUNT, * PS_CSP_INIT_WORLD_USER_COUNT;


// SCP_INIT_WORLD_USER_COUNT : 0x9161
typedef struct _S_SCP_INIT_WORLD_USER_COUNT
{
	short                                             snUser[20];   

} S_SCP_INIT_WORLD_USER_COUNT, * PS_SCP_INIT_WORLD_USER_COUNT;


// CSP_REQ_CHAR_MOVE : 0x1201
typedef struct _S_CSP_REQ_CHAR_MOVE
{
	BYTE                                              byDir;        // 이동상태 및 이동방향 정보
	short                                             snDegree;     
	DWORD                                             dwTickCount;  
	WORD                                              wSeqNum;      // 이동패킷 Sequence Number

} S_CSP_REQ_CHAR_MOVE, * PS_CSP_REQ_CHAR_MOVE;


// SCP_RESP_CHAR_MOVE : 0x9201
typedef struct _S_SCP_RESP_CHAR_MOVE
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // 케릭터의 X좌표
	short                                             snZ;          // 케릭터의 Z좌표
	BYTE                                              byY;          // 케릭터의 층 높이
	short                                             snHeight;     // 케릭터의 단 높이

} S_SCP_RESP_CHAR_MOVE, * PS_SCP_RESP_CHAR_MOVE;


// CSP_OTHER_CHAR_MOVE : 0x1202
typedef struct _S_CSP_OTHER_CHAR_MOVE
{

} S_CSP_OTHER_CHAR_MOVE, * PS_CSP_OTHER_CHAR_MOVE;


// SCP_OTHER_CHAR_MOVE : 0x9202
typedef struct _S_SCP_OTHER_CHAR_MOVE
{
	DWORD                                             dwKeyID;      // character KeyID
	BYTE                                              byDir;        // 캐릭터 이동상태, 방향 정보
	short                                             snDegree;     // 케릭터의 이동 각도 정보
	short                                             snMovingSpeed;// 100초당 이동가능 Cell 수
	short                                             snX;          // 케릭터의 X좌표
	short                                             snZ;          // 케릭터의 Z좌표
	BYTE                                              byY;          // 케릭터의 층 높이
	short                                             snHeight;     // 케릭터의 단 높이

} S_SCP_OTHER_CHAR_MOVE, * PS_SCP_OTHER_CHAR_MOVE;


// CSP_REQ_ITEM_MOVE : 0x1203
typedef struct _S_CSP_REQ_ITEM_MOVE
{
	DWORD                                             dwKeyID;      // 아이템 KeyID
	BYTE                                              byToPlace;    // 아이템을 이동시킬 대상
	short                                             snX;          // 아이템을 이동 시킬 X좌표
	short                                             snZ;          // 아이템을 이동 시킬 Z좌표

} S_CSP_REQ_ITEM_MOVE, * PS_CSP_REQ_ITEM_MOVE;


// SCP_RESP_ITEM_MOVE : 0x9203
typedef struct _S_SCP_RESP_ITEM_MOVE
{
	BYTE                                              byResult;     // 아이템을 이동에 대한 결과
	DWORD                                             dwKeyID;      // 아이템 KeyID
	BYTE                                              byToPlace;    // 아이템을 이동시킬 대상
	short                                             snX;          // 아이템을 이동 시킬 X좌표
	short                                             snZ;          // 아이템을 이동 시킬 Z좌표

} S_SCP_RESP_ITEM_MOVE, * PS_SCP_RESP_ITEM_MOVE;


// CSP_MAP_ITEM_APPEAR : 0x1204
typedef struct _S_CSP_MAP_ITEM_APPEAR
{

} S_CSP_MAP_ITEM_APPEAR, * PS_CSP_MAP_ITEM_APPEAR;


// SCP_MAP_ITEM_APPEAR : 0x9204
typedef struct _S_SCP_MAP_ITEM_APPEAR
{
	DWORD                                             dwKeyID;      // Item KeyID
	DWORD                                             dwIndex;      // Item Index
	short                                             snCurDurability;
	short                                             snCount;      // Item X좌표
	short                                             snX;          // Item X좌표
	short                                             snZ;          // Item Z좌표
	BYTE                                              byY;          // 아이템의 층 높이
	short                                             snHeight;     // 아이템의 단 높이

} S_SCP_MAP_ITEM_APPEAR, * PS_SCP_MAP_ITEM_APPEAR;


// CSP_MAP_ITEM_DISAPPEAR : 0x1205
typedef struct _S_CSP_MAP_ITEM_DISAPPEAR
{

} S_CSP_MAP_ITEM_DISAPPEAR, * PS_CSP_MAP_ITEM_DISAPPEAR;


// SCP_MAP_ITEM_DISAPPEAR : 0x9205
typedef struct _S_SCP_MAP_ITEM_DISAPPEAR
{
	DWORD                                             dwKeyID;      // Item KeyID

} S_SCP_MAP_ITEM_DISAPPEAR, * PS_SCP_MAP_ITEM_DISAPPEAR;


// CSP_MONSTER_MOVE_STEP : 0x1206
typedef struct _S_CSP_MONSTER_MOVE_STEP
{

} S_CSP_MONSTER_MOVE_STEP, * PS_CSP_MONSTER_MOVE_STEP;


// SCP_MONSTER_MOVE_STEP : 0x9206
typedef struct _S_SCP_MONSTER_MOVE_STEP
{
	DWORD                                             dwKeyID;      
	BYTE                                              byDir;        
	int                                               nMoveTime;    

} S_SCP_MONSTER_MOVE_STEP, * PS_SCP_MONSTER_MOVE_STEP;


// CSP_MONSTER_MOVE_NSTEP : 0x1207
typedef struct _S_CSP_MONSTER_MOVE_NSTEP
{

} S_CSP_MONSTER_MOVE_NSTEP, * PS_CSP_MONSTER_MOVE_NSTEP;


// SCP_MONSTER_MOVE_NSTEP : 0x9207
typedef struct _S_SCP_MONSTER_MOVE_NSTEP
{
	DWORD                                             dwKeyID;      
	int                                               nMovingSpeed; 
	short                                             snX;          // 최종 x좌표
	short                                             snZ;          // 최종 z좌표

} S_SCP_MONSTER_MOVE_NSTEP, * PS_SCP_MONSTER_MOVE_NSTEP;


// CSP_MONSTER_MOVE_END : 0x1208
typedef struct _S_CSP_MONSTER_MOVE_END
{

} S_CSP_MONSTER_MOVE_END, * PS_CSP_MONSTER_MOVE_END;


// SCP_MONSTER_MOVE_END : 0x9208
typedef struct _S_SCP_MONSTER_MOVE_END
{
	DWORD                                             dwKeyID;      
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byDir;        

} S_SCP_MONSTER_MOVE_END, * PS_SCP_MONSTER_MOVE_END;


// CSP_REQ_ITEM_PACKING : 0x1221
typedef struct _S_CSP_REQ_ITEM_PACKING
{
	DWORD                                             dwSourceKeyID;// Source Item KeyID
	DWORD                                             dwDestKeyID;  // Destinatin Item KeyID

} S_CSP_REQ_ITEM_PACKING, * PS_CSP_REQ_ITEM_PACKING;


// SCP_RESP_ITEM_PACKING : 0x9221
typedef struct _S_SCP_RESP_ITEM_PACKING
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwSourceKeyID;// Source Item KeyID
	short                                             snSourceCount;// Source Item Count
	DWORD                                             dwDestKeyID;  // Destinatin Item KeyID
	short                                             snDestCount;  // Destinatin Item Count

} S_SCP_RESP_ITEM_PACKING, * PS_SCP_RESP_ITEM_PACKING;


// CSP_REQ_ITEM_UNPACKING : 0x1222
typedef struct _S_CSP_REQ_ITEM_UNPACKING
{
	DWORD                                             dwKeyID;      // 언패킹할 아이템의 KeyID
	short                                             snCount;      // 아이템 언패킹 Count
	BYTE                                              byPlace;      // 언패킹된 아이템을 놓는 위치
	short                                             snX;          // 언패킹된 아이템의 X 좌표. Index 0 으로 시작
	short                                             snZ;          // 언패킹된 아이템의 Z 좌표. Index 0 으로 시작

} S_CSP_REQ_ITEM_UNPACKING, * PS_CSP_REQ_ITEM_UNPACKING;


// SCP_RESP_ITEM_UNPACKING : 0x9222
typedef struct _S_SCP_RESP_ITEM_UNPACKING
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwSourceKeyID;// 언패킹할 Source 아이템의 KeyID
	short                                             snSourceCount;// 언패킹할 Source 아이템의 Count
	DWORD                                             dwDestKeyID;  // 언패킹할 Destinatin 아이템의 KeyID
	short                                             snDestCount;  // 언패킹할 Destinatin 아이템의 Count

} S_SCP_RESP_ITEM_UNPACKING, * PS_SCP_RESP_ITEM_UNPACKING;


// CSP_REQ_ITEM_USE : 0x1223
typedef struct _S_CSP_REQ_ITEM_USE
{
	BYTE                                              byBagID;      // bag ID(0~2)
	short                                             snX;          // 인벤토리에서의 아이템의 X 좌표. Index 0 으로 시작
	short                                             snZ;          // 인벤토리에서의 아이템의 Z 좌표. Index 0 으로 시작

} S_CSP_REQ_ITEM_USE, * PS_CSP_REQ_ITEM_USE;


// SCP_RESP_ITEM_USE : 0x9223
typedef struct _S_SCP_RESP_ITEM_USE
{
	BYTE                                              byResult;     // Result(0: 성공, 12:오류)
	DWORD                                             dwKeyID;      // 사용한 아이템의 KeyID
	BYTE                                              byPackCount;  // 남은 아이템 중첩 수량

} S_SCP_RESP_ITEM_USE, * PS_SCP_RESP_ITEM_USE;


// CSP_ITEM_USE_BROADCAST : 0x1224
typedef struct _S_CSP_ITEM_USE_BROADCAST
{

} S_CSP_ITEM_USE_BROADCAST, * PS_CSP_ITEM_USE_BROADCAST;


// SCP_ITEM_USE_BROADCAST : 0x9224
typedef struct _S_SCP_ITEM_USE_BROADCAST
{
	DWORD                                             dwKeyID;      // 아이템을 사용하는 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 사용한 아이템의 Index

} S_SCP_ITEM_USE_BROADCAST, * PS_SCP_ITEM_USE_BROADCAST;


// CSP_ITEM_REMOVE : 0x1225
typedef struct _S_CSP_ITEM_REMOVE
{

} S_CSP_ITEM_REMOVE, * PS_CSP_ITEM_REMOVE;


// SCP_ITEM_REMOVE : 0x9225
typedef struct _S_SCP_ITEM_REMOVE
{
	DWORD                                             dwKeyID;      // 사라진 아이템의 KeyID
	BYTE                                              byPlace;      // 사라진 아이템의 위치
	short                                             snX;          // 사라진 아이템의 X 좌표
	short                                             snZ;          // 사라진 아이템의 Z 좌표

} S_SCP_ITEM_REMOVE, * PS_SCP_ITEM_REMOVE;


// CSP_REQ_MONEY_MOVE : 0x1226
typedef struct _S_CSP_REQ_MONEY_MOVE
{
	DWORD                                             dwMoney;      // 이동할 루피아의 양
	BYTE                                              byPlace;      // 이동할 루피아의 위치

} S_CSP_REQ_MONEY_MOVE, * PS_CSP_REQ_MONEY_MOVE;


// SCP_RESP_MONEY_MOVE : 0x9226
typedef struct _S_SCP_RESP_MONEY_MOVE
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byPlace;      // 이동할 루피아의 위치
	DWORD                                             dwFromMoney;  // 이전 장소의 루피아양
	DWORD                                             dwToMoney;    // 옮긴 장소의 루피아양

} S_SCP_RESP_MONEY_MOVE, * PS_SCP_RESP_MONEY_MOVE;


// CSP_REQ_CHAR_MOVE_BROADCAST : 0x1227
typedef struct _S_CSP_REQ_CHAR_MOVE_BROADCAST
{
	BYTE                                              byDir;        // 이동상태
	short                                             snToX;        // 이동시의 종착점 X좌표
	short                                             snToZ;        // 이동시의 종착점 Z좌표

} S_CSP_REQ_CHAR_MOVE_BROADCAST, * PS_CSP_REQ_CHAR_MOVE_BROADCAST;


// SCP_RESP_CHAR_MOVE_BROADCAST : 0x9227
typedef struct _S_SCP_RESP_CHAR_MOVE_BROADCAST
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	BYTE                                              byDir;        // 이동상태
	short                                             snFromX;      // 이동시의 시작점 X좌표
	short                                             snFromZ;      // 이동시의 시작점 Z좌표
	short                                             snToX;        // 이동시의 종착점 X좌표
	short                                             snToZ;        // 이동시의 종착점 Z좌표

} S_SCP_RESP_CHAR_MOVE_BROADCAST, * PS_SCP_RESP_CHAR_MOVE_BROADCAST;


// CSP_REQ_MOVE_PORTAL : 0x1231
typedef struct _S_CSP_REQ_MOVE_PORTAL
{
	WORD                                              wPortalID;    // 이동하고자 하는 포탈의 ID

} S_CSP_REQ_MOVE_PORTAL, * PS_CSP_REQ_MOVE_PORTAL;


// SCP_RESP_MOVE_PORTAL : 0x9231
typedef struct _S_SCP_RESP_MOVE_PORTAL
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // 이동시의 X 좌표.
	short                                             snZ;          // 이동시의 Z 좌표.
	BYTE                                              byY;          // 이동시의 Y 좌표(층).
	WORD                                              wServerID;    // Server ID
	char                                              szZoneIP[16]; 
	WORD                                              wZonePort;    

} S_SCP_RESP_MOVE_PORTAL, * PS_SCP_RESP_MOVE_PORTAL;


// CSP_REQ_ATK_CHAR : 0x1301
typedef struct _S_CSP_REQ_ATK_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격 대상 캐릭터의 KeyID
	DWORD                                             dwItemKeyID;  // 공격에 사용할 아이템 KeyID
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_ATK_CHAR, * PS_CSP_REQ_ATK_CHAR;


// SCP_RESP_ATK_CHAR : 0x9301
typedef struct _S_SCP_RESP_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCount;      // 투척무기일 경우, 잔여수량
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터/Monster의 현재 HP

} S_SCP_RESP_ATK_CHAR, * PS_SCP_RESP_ATK_CHAR;


// CSP_ATK_CHAR_BROADCAST : 0x1302
typedef struct _S_CSP_ATK_CHAR_BROADCAST
{

} S_CSP_ATK_CHAR_BROADCAST, * PS_CSP_ATK_CHAR_BROADCAST;


// SCP_ATK_CHAR_BROADCAST : 0x9302
typedef struct _S_SCP_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwKeyID;      // 공격을 하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;// 공격을 당하는 캐릭터의 KeyID
	BYTE                                              byEquipPart;  // 공격시에 사용하는 아이템을 장착한 부위
	BYTE                                              byResult;     // Result Field
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터의 현재 HP
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCurX;       // 공격자의 현재 X좌표
	short                                             snCurz;       // 공격자의 현재 z좌표

} S_SCP_ATK_CHAR_BROADCAST, * PS_SCP_ATK_CHAR_BROADCAST;


// CSP_REQ_ITEM_EQUIPMENT : 0x1401
typedef struct _S_CSP_REQ_ITEM_EQUIPMENT
{
	DWORD                                             dwKeyID;      // 창착할 아이템 KeyID
	BYTE                                              byEquipPart;  // 아이템 장착부위
	BYTE                                              byX;          // 장착 X 좌표
	BYTE                                              byZ;          // 장착 Z 좌표

} S_CSP_REQ_ITEM_EQUIPMENT, * PS_CSP_REQ_ITEM_EQUIPMENT;


// SCP_RESP_ITEM_EQUIPMENT : 0x9401
typedef struct _S_SCP_RESP_ITEM_EQUIPMENT
{
	BYTE                                              byResult;     // 아이템 장착 요청에 대한 결과 값
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리

} S_SCP_RESP_ITEM_EQUIPMENT, * PS_SCP_RESP_ITEM_EQUIPMENT;


// CSP_ITEM_EQUIPMENT_BROADCAST : 0x1402
typedef struct _S_CSP_ITEM_EQUIPMENT_BROADCAST
{

} S_CSP_ITEM_EQUIPMENT_BROADCAST, * PS_CSP_ITEM_EQUIPMENT_BROADCAST;


// SCP_ITEM_EQUIPMENT_BROADCAST : 0x9402
typedef struct _S_SCP_ITEM_EQUIPMENT_BROADCAST
{
	DWORD                                             dwKeyID;      // 장착 캐릭터 KeyID
	DWORD                                             dwIndex;      // 장착 아이템 인덱스
	BYTE                                              byEquipPart;  // 아이템 장착 부위
	BYTE                                              bySubMaterialCount;

} S_SCP_ITEM_EQUIPMENT_BROADCAST, * PS_SCP_ITEM_EQUIPMENT_BROADCAST;


// CSP_ITEM_ABRASION : 0x1411
typedef struct _S_CSP_ITEM_ABRASION
{

} S_CSP_ITEM_ABRASION, * PS_CSP_ITEM_ABRASION;


// SCP_ITEM_ABRASION : 0x9411
typedef struct _S_SCP_ITEM_ABRASION
{
	DWORD                                             dwKeyIDWeapon;// 무기 아이템의 KeyID
	DWORD                                             dwKeyIDBody;  // 의복 아이템의 KeyID
	DWORD                                             dwKeyIDShield;// 방패 아이템의 KeyID
	DWORD                                             dwKeyIDHead;  // 모자 아이템의 KeyID
	DWORD                                             dwKeyIDFoot;  // 신발 아이템의 KeyID
	DWORD                                             dwKeyIDBelt;  // 허리띠 아이템의 KeyID

} S_SCP_ITEM_ABRASION, * PS_SCP_ITEM_ABRASION;


// CSP_ITEM_ABRASION_BROADCAST : 0x1412
typedef struct _S_CSP_ITEM_ABRASION_BROADCAST
{

} S_CSP_ITEM_ABRASION_BROADCAST, * PS_CSP_ITEM_ABRASION_BROADCAST;


// SCP_ITEM_ABRASION_BROADCAST : 0x9412
typedef struct _S_SCP_ITEM_ABRASION_BROADCAST
{
	DWORD                                             dwKeyID;      // 아이템이 사라진 캐릭터의 KeyID
	DWORD                                             dwIndexWeapon;// 무기 아이템의 Index
	DWORD                                             dwIndexBody;  // 의복 아이템의 Index
	DWORD                                             dwIndexShield;// 방패 아이템의 Index
	DWORD                                             dwIndexHead;  // 모자 아이템의 Index
	DWORD                                             dwIndexFoot;  // 신발 아이템의 Index
	DWORD                                             dwIndexBelt;  // 허리띠 아이템의 Index

} S_SCP_ITEM_ABRASION_BROADCAST, * PS_SCP_ITEM_ABRASION_BROADCAST;


// CSP_ITEM_DURABILITY_DECREASE : 0x1413
typedef struct _S_CSP_ITEM_DURABILITY_DECREASE
{

} S_CSP_ITEM_DURABILITY_DECREASE, * PS_CSP_ITEM_DURABILITY_DECREASE;


// SCP_ITEM_DURABILITY_DECREASE : 0x9413
typedef struct _S_SCP_ITEM_DURABILITY_DECREASE
{
	DWORD                                             dwKeyIDWeapon;// 무기 아이템의 KeyID
	short                                             snDurWeapon;  // 현재 내구도
	DWORD                                             dwKeyIDBody;  // 의복 아이템의 KeyID
	short                                             snDurBody;    // 현재 내구도
	DWORD                                             dwKeyIDShield;// 방패 아이템의 KeyID
	short                                             snDurShield;  // 현재 내구도
	DWORD                                             dwKeyIDHead;  // 모자 아이템의 KeyID
	short                                             snDurHead;    // 현재 내구도
	DWORD                                             dwKeyIDFoot;  // 신발 아이템의 KeyID
	short                                             snDurFoot;    // 현재 내구도
	DWORD                                             dwKeyIDBelt;  // 벨트 아이템의 KeyID
	short                                             snDurBelt;    // 현재 내구도

} S_SCP_ITEM_DURABILITY_DECREASE, * PS_SCP_ITEM_DURABILITY_DECREASE;


// CSP_REQ_NORMAL_CHAT : 0x1501
typedef struct _S_CSP_REQ_NORMAL_CHAT
{
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_NORMAL_CHAT, * PS_CSP_REQ_NORMAL_CHAT;


// SCP_RESP_NORMAL_CHAT : 0x9501
typedef struct _S_SCP_RESP_NORMAL_CHAT
{
	BYTE                                              byResult;     // 채팅 결과 통보

} S_SCP_RESP_NORMAL_CHAT, * PS_SCP_RESP_NORMAL_CHAT;


// CSP_NORMAL_CHAT : 0x1502
typedef struct _S_CSP_NORMAL_CHAT
{

} S_CSP_NORMAL_CHAT, * PS_CSP_NORMAL_CHAT;


// SCP_NORMAL_CHAT : 0x9502
typedef struct _S_SCP_NORMAL_CHAT
{
	DWORD                                             dwKeyID;      // 채팅 메세지를 전송한 캐릭터 KeyID
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지
	char                                              szSender[26]; // 송신자의 이름

} S_SCP_NORMAL_CHAT, * PS_SCP_NORMAL_CHAT;


// CSP_REQ_WHISPER_CHAT : 0x1503
typedef struct _S_CSP_REQ_WHISPER_CHAT
{
	char                                              szName[26];   // 채팅 메세지를 요청한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_WHISPER_CHAT, * PS_CSP_REQ_WHISPER_CHAT;


// SCP_RESP_WHISPER_CHAT : 0x9503
typedef struct _S_SCP_RESP_WHISPER_CHAT
{
	BYTE                                              byResult;     // 채팅 결과 통보

} S_SCP_RESP_WHISPER_CHAT, * PS_SCP_RESP_WHISPER_CHAT;


// CSP_WHISPER_CHAT : 0x1504
typedef struct _S_CSP_WHISPER_CHAT
{

} S_CSP_WHISPER_CHAT, * PS_CSP_WHISPER_CHAT;


// SCP_WHISPER_CHAT : 0x9504
typedef struct _S_SCP_WHISPER_CHAT
{
	char                                              szName[26];   // 채팅 메세지를 전송한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지
	char                                              szReceiver[26];// 수신자의 이름

} S_SCP_WHISPER_CHAT, * PS_SCP_WHISPER_CHAT;


// CSP_REQ_SHOUT_CHAT : 0x1505
typedef struct _S_CSP_REQ_SHOUT_CHAT
{
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_SHOUT_CHAT, * PS_CSP_REQ_SHOUT_CHAT;


// SCP_RESP_SHOUT_CHAT : 0x9505
typedef struct _S_SCP_RESP_SHOUT_CHAT
{
	BYTE                                              byResult;     // 채팅 결과 통보

} S_SCP_RESP_SHOUT_CHAT, * PS_SCP_RESP_SHOUT_CHAT;


// CSP_SHOUT_CHAT : 0x1506
typedef struct _S_CSP_SHOUT_CHAT
{

} S_CSP_SHOUT_CHAT, * PS_CSP_SHOUT_CHAT;


// SCP_SHOUT_CHAT : 0x9506
typedef struct _S_SCP_SHOUT_CHAT
{
	char                                              szName[26];   // 채팅 메세지를 전송한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_SCP_SHOUT_CHAT, * PS_SCP_SHOUT_CHAT;


// CSP_REQ_PARTY_CHAT : 0x1507
typedef struct _S_CSP_REQ_PARTY_CHAT
{
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_PARTY_CHAT, * PS_CSP_REQ_PARTY_CHAT;


// SCP_RESP_PARTY_CHAT : 0x9507
typedef struct _S_SCP_RESP_PARTY_CHAT
{
	BYTE                                              byResult;     // 채팅 결과 통보

} S_SCP_RESP_PARTY_CHAT, * PS_SCP_RESP_PARTY_CHAT;


// CSP_PARTY_CHAT : 0x1508
typedef struct _S_CSP_PARTY_CHAT
{

} S_CSP_PARTY_CHAT, * PS_CSP_PARTY_CHAT;


// SCP_PARTY_CHAT : 0x9508
typedef struct _S_SCP_PARTY_CHAT
{
	char                                              szName[26];   // 채팅 메세지를 전송한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_SCP_PARTY_CHAT, * PS_SCP_PARTY_CHAT;


// CSP_REQ_NOTIFY_MESSAGE : 0x1511
typedef struct _S_CSP_REQ_NOTIFY_MESSAGE
{
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_NOTIFY_MESSAGE, * PS_CSP_REQ_NOTIFY_MESSAGE;


// SCP_RESP_NOTIFY_MESSAGE : 0x9511
typedef struct _S_SCP_RESP_NOTIFY_MESSAGE
{
	BYTE                                              byResult;     // 채팅 결과 응답 메세지

} S_SCP_RESP_NOTIFY_MESSAGE, * PS_SCP_RESP_NOTIFY_MESSAGE;


// CSP_NOTIFY_MESSAGE : 0x1512
typedef struct _S_CSP_NOTIFY_MESSAGE
{

} S_CSP_NOTIFY_MESSAGE, * PS_CSP_NOTIFY_MESSAGE;


// SCP_NOTIFY_MESSAGE : 0x9512
typedef struct _S_SCP_NOTIFY_MESSAGE
{
	char                                              szName[26];   // 채팅 메세지를 전송한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_SCP_NOTIFY_MESSAGE, * PS_SCP_NOTIFY_MESSAGE;


// CSP_REQ_BROADCAST_MESSAGE : 0x1513
typedef struct _S_CSP_REQ_BROADCAST_MESSAGE
{
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_CSP_REQ_BROADCAST_MESSAGE, * PS_CSP_REQ_BROADCAST_MESSAGE;


// SCP_RESP_BROADCAST_MESSAGE : 0x9513
typedef struct _S_SCP_RESP_BROADCAST_MESSAGE
{
	BYTE                                              byResult;     // 채팅 결과 응답 메세지

} S_SCP_RESP_BROADCAST_MESSAGE, * PS_SCP_RESP_BROADCAST_MESSAGE;


// CSP_BROADCAST_MESSAGE : 0x1514
typedef struct _S_CSP_BROADCAST_MESSAGE
{

} S_CSP_BROADCAST_MESSAGE, * PS_CSP_BROADCAST_MESSAGE;


// SCP_BROADCAST_MESSAGE : 0x9514
typedef struct _S_SCP_BROADCAST_MESSAGE
{
	char                                              szName[26];   // 채팅 메세지를 전송한 캐릭터 이름
	BYTE                                              byBgColor;    // 채팅 메세지 배경색
	BYTE                                              byTextColor;  // 채팅 메세지 글자색
	char                                              szMsg[221];   // 채팅 메세지

} S_SCP_BROADCAST_MESSAGE, * PS_SCP_BROADCAST_MESSAGE;


// CSP_REQ_CREATE_PARTY : 0x1601
typedef struct _S_CSP_REQ_CREATE_PARTY
{
	char                                              szPartyName[26];// 생성할 파티 이름

} S_CSP_REQ_CREATE_PARTY, * PS_CSP_REQ_CREATE_PARTY;


// SCP_RESP_CREATE_PARTY : 0x9601
typedef struct _S_SCP_RESP_CREATE_PARTY
{
	BYTE                                              byResult;     // 파티 생성요청 결과

} S_SCP_RESP_CREATE_PARTY, * PS_SCP_RESP_CREATE_PARTY;


// CSP_REQ_DISBAND_PARTY : 0x1602
typedef struct _S_CSP_REQ_DISBAND_PARTY
{
	char                                              szPartyName[26];// 해체할 파티 이름

} S_CSP_REQ_DISBAND_PARTY, * PS_CSP_REQ_DISBAND_PARTY;


// SCP_RESP_DISBAND_PARTY : 0x9602
typedef struct _S_SCP_RESP_DISBAND_PARTY
{
	BYTE                                              byResult;     // 파티 해체요청 결과

} S_SCP_RESP_DISBAND_PARTY, * PS_SCP_RESP_DISBAND_PARTY;


// CSP_DISBAND_PARTY_BROADCAST : 0x1603
typedef struct _S_CSP_DISBAND_PARTY_BROADCAST
{

} S_CSP_DISBAND_PARTY_BROADCAST, * PS_CSP_DISBAND_PARTY_BROADCAST;


// SCP_DISBAND_PARTY_BROADCAST : 0x9603
typedef struct _S_SCP_DISBAND_PARTY_BROADCAST
{
	BYTE                                              byResult;     // 파티 해체 결과

} S_SCP_DISBAND_PARTY_BROADCAST, * PS_SCP_DISBAND_PARTY_BROADCAST;


// CSP_REQ_JOIN_PARTY : 0x1604
typedef struct _S_CSP_REQ_JOIN_PARTY
{
	DWORD                                             dwKeyID;      // 파티에 참여시킬 캐릭터의 KeyID

} S_CSP_REQ_JOIN_PARTY, * PS_CSP_REQ_JOIN_PARTY;


// SCP_RESP_JOIN_PARTY : 0x9604
typedef struct _S_SCP_RESP_JOIN_PARTY
{
	BYTE                                              byResult;     // 파티 참여요청 결과

} S_SCP_RESP_JOIN_PARTY, * PS_SCP_RESP_JOIN_PARTY;


// CSP_JOIN_PARTY_NOTIFY : 0x1605
typedef struct _S_CSP_JOIN_PARTY_NOTIFY
{

} S_CSP_JOIN_PARTY_NOTIFY, * PS_CSP_JOIN_PARTY_NOTIFY;


// SCP_JOIN_PARTY_NOTIFY : 0x9605
typedef struct _S_SCP_JOIN_PARTY_NOTIFY
{
	DWORD                                             dwKeyID;      // 파티 참여를 요청한 캐릭터의 KeyID
	char                                              szPartyName[26];// 참여를 요청한 파티 이름

} S_SCP_JOIN_PARTY_NOTIFY, * PS_SCP_JOIN_PARTY_NOTIFY;


// CSP_JOIN_PARTY_RESULT : 0x1606
typedef struct _S_CSP_JOIN_PARTY_RESULT
{
	DWORD                                             dwKeyID;      // 파티 참여를 요청한 캐릭터의 KeyID
	BYTE                                              byResult;     // 파티 참여요청 결과

} S_CSP_JOIN_PARTY_RESULT, * PS_CSP_JOIN_PARTY_RESULT;


// SCP_JOIN_PARTY_RESULT : 0x9606
typedef struct _S_SCP_JOIN_PARTY_RESULT
{
	BYTE                                              byResult;     // 파티 참여요청 결과

} S_SCP_JOIN_PARTY_RESULT, * PS_SCP_JOIN_PARTY_RESULT;


// CSP_JOIN_PARTY_RESULT_NOTIFY : 0x1607
typedef struct _S_CSP_JOIN_PARTY_RESULT_NOTIFY
{

} S_CSP_JOIN_PARTY_RESULT_NOTIFY, * PS_CSP_JOIN_PARTY_RESULT_NOTIFY;


// SCP_JOIN_PARTY_RESULT_NOTIFY : 0x9607
typedef struct _S_SCP_JOIN_PARTY_RESULT_NOTIFY
{
	BYTE                                              byResult;     // 파티 참여요청 결과
	DWORD                                             dwKeyID;      // 파티에 가입한 캐릭터의 KeyID

} S_SCP_JOIN_PARTY_RESULT_NOTIFY, * PS_SCP_JOIN_PARTY_RESULT_NOTIFY;


// CSP_NEW_PARTY_MEMBER : 0x1608
typedef struct _S_CSP_NEW_PARTY_MEMBER
{

} S_CSP_NEW_PARTY_MEMBER, * PS_CSP_NEW_PARTY_MEMBER;


// SCP_NEW_PARTY_MEMBER : 0x9608
typedef struct _S_SCP_NEW_PARTY_MEMBER
{
	S_PARTY_MEMBER_INFO                               MemberInfo;   // 파티원 정보

} S_SCP_NEW_PARTY_MEMBER, * PS_SCP_NEW_PARTY_MEMBER;


// CSP_REQ_SECEDE_PARTY : 0x1609
typedef struct _S_CSP_REQ_SECEDE_PARTY
{
	char                                              szName[26];   // 탈퇴할 파티원의 이름

} S_CSP_REQ_SECEDE_PARTY, * PS_CSP_REQ_SECEDE_PARTY;


// SCP_RESP_SECEDE_PARTY : 0x9609
typedef struct _S_SCP_RESP_SECEDE_PARTY
{
	BYTE                                              byResult;     // 파티 탈퇴요청 결과

} S_SCP_RESP_SECEDE_PARTY, * PS_SCP_RESP_SECEDE_PARTY;


// CSP_SECEDE_PARTY_BROADCAST : 0x160A
typedef struct _S_CSP_SECEDE_PARTY_BROADCAST
{

} S_CSP_SECEDE_PARTY_BROADCAST, * PS_CSP_SECEDE_PARTY_BROADCAST;


// SCP_SECEDE_PARTY_BROADCAST : 0x960A
typedef struct _S_SCP_SECEDE_PARTY_BROADCAST
{
	char                                              szName[26];   // 탈퇴할 파티원의 이름

} S_SCP_SECEDE_PARTY_BROADCAST, * PS_SCP_SECEDE_PARTY_BROADCAST;


// CSP_REQ_PARTY_LIST : 0x160B
typedef struct _S_CSP_REQ_PARTY_LIST
{
	char                                              szPartyName[26];// 파티 이름

} S_CSP_REQ_PARTY_LIST, * PS_CSP_REQ_PARTY_LIST;


// SCP_RESP_PARTY_LIST : 0x960B
typedef struct _S_SCP_RESP_PARTY_LIST
{
	BYTE                                              byCount;      

} S_SCP_RESP_PARTY_LIST, * PS_SCP_RESP_PARTY_LIST;


// CSP_REQ_CREATE_GUILD : 0x1611
typedef struct _S_CSP_REQ_CREATE_GUILD
{
	char                                              szGuildName[26];// 생성할 길드 이름
	DWORD                                             dwGuildMark;  

} S_CSP_REQ_CREATE_GUILD, * PS_CSP_REQ_CREATE_GUILD;


// SCP_RESP_CREATE_GUILD : 0x9611
typedef struct _S_SCP_RESP_CREATE_GUILD
{
	BYTE                                              byResult;     // 길드 생성요청 결과
	S_SCP_INIT_GUILD                                  s_Guild;      // 생성할 길드

} S_SCP_RESP_CREATE_GUILD, * PS_SCP_RESP_CREATE_GUILD;


// CSP_REQ_DISBAND_GUILD : 0x1612
typedef struct _S_CSP_REQ_DISBAND_GUILD
{
	char                                              szGuildName[26];// 해체할 길드 이름

} S_CSP_REQ_DISBAND_GUILD, * PS_CSP_REQ_DISBAND_GUILD;


// SCP_RESP_DISBAND_GUILD : 0x9612
typedef struct _S_SCP_RESP_DISBAND_GUILD
{
	BYTE                                              byResult;     // 길드 해체요청 결과
	char                                              szGuildName[26];// 해체할 길드 이름

} S_SCP_RESP_DISBAND_GUILD, * PS_SCP_RESP_DISBAND_GUILD;


// CSP_CREATE_GUILD_BROADCAST : 0x1613
typedef struct _S_CSP_CREATE_GUILD_BROADCAST
{

} S_CSP_CREATE_GUILD_BROADCAST, * PS_CSP_CREATE_GUILD_BROADCAST;


// SCP_CREATE_GUILD_BROADCAST : 0x9613
typedef struct _S_SCP_CREATE_GUILD_BROADCAST
{
	char                                              szGuildName[26];// 생성한 길드 이름
	DWORD                                             dwKeyID;      // 길드장의 KeyID

} S_SCP_CREATE_GUILD_BROADCAST, * PS_SCP_CREATE_GUILD_BROADCAST;


// CSP_DISBAND_GUILD_BROADCAST : 0x1614
typedef struct _S_CSP_DISBAND_GUILD_BROADCAST
{
	char                                              szGuildName[26];// 해체한 길드 이름

} S_CSP_DISBAND_GUILD_BROADCAST, * PS_CSP_DISBAND_GUILD_BROADCAST;


// SCP_DISBAND_GUILD_BROADCAST : 0x9614
typedef struct _S_SCP_DISBAND_GUILD_BROADCAST
{
	char                                              szCharName[26];// 길드를 해체한 사람의 이름
	char                                              szGuildName[26];// 해체한 길드 이름

} S_SCP_DISBAND_GUILD_BROADCAST, * PS_SCP_DISBAND_GUILD_BROADCAST;


// CSP_REQ_JOIN_GUILD : 0x1615
typedef struct _S_CSP_REQ_JOIN_GUILD
{
	char                                              szCharName[26];// 길드에 참여시킬 케릭터의 이름

} S_CSP_REQ_JOIN_GUILD, * PS_CSP_REQ_JOIN_GUILD;


// SCP_RESP_JOIN_GUILD : 0x9615
typedef struct _S_SCP_RESP_JOIN_GUILD
{
	BYTE                                              byResult;     // 길드 참여요청 결과
	char                                              szCharName[26];// 길드에 참여시킬 케릭터의 이름

} S_SCP_RESP_JOIN_GUILD, * PS_SCP_RESP_JOIN_GUILD;


// CSP_JOIN_GUILD_NOTIFY : 0x1616
typedef struct _S_CSP_JOIN_GUILD_NOTIFY
{

} S_CSP_JOIN_GUILD_NOTIFY, * PS_CSP_JOIN_GUILD_NOTIFY;


// SCP_JOIN_GUILD_NOTIFY : 0x9616
typedef struct _S_SCP_JOIN_GUILD_NOTIFY
{
	char                                              szCharName[26];// 길드참여를 요청한 케릭터의 이름
	char                                              szGuildName[26];// 참여를 요청한 길드 이름

} S_SCP_JOIN_GUILD_NOTIFY, * PS_SCP_JOIN_GUILD_NOTIFY;


// CSP_JOIN_GUILD_RESULT : 0x1617
typedef struct _S_CSP_JOIN_GUILD_RESULT
{
	char                                              szCharName[26];// 길드참여를 요청한 케릭터의 이름
	char                                              szGuildName[26];// 참여를 요청한 길드 이름
	BYTE                                              byResult;     // 길드 참여요청 결과

} S_CSP_JOIN_GUILD_RESULT, * PS_CSP_JOIN_GUILD_RESULT;


// SCP_JOIN_GUILD_RESULT : 0x9617
typedef struct _S_SCP_JOIN_GUILD_RESULT
{
	BYTE                                              byResult;     // 길드 참여요청 결과
	char                                              szGuildName[26];// 참여를 요청한 길드 이름

} S_SCP_JOIN_GUILD_RESULT, * PS_SCP_JOIN_GUILD_RESULT;


// CSP_JOIN_GUILD_RESULT_NOTIFY : 0x1618
typedef struct _S_CSP_JOIN_GUILD_RESULT_NOTIFY
{

} S_CSP_JOIN_GUILD_RESULT_NOTIFY, * PS_CSP_JOIN_GUILD_RESULT_NOTIFY;


// SCP_JOIN_GUILD_RESULT_NOTIFY : 0x9618
typedef struct _S_SCP_JOIN_GUILD_RESULT_NOTIFY
{
	BYTE                                              byResult;     // 길드 참여요청 결과
	char                                              szCharName[26];// 길드가입한 케릭터의 이름

} S_SCP_JOIN_GUILD_RESULT_NOTIFY, * PS_SCP_JOIN_GUILD_RESULT_NOTIFY;


// CSP_NEW_GUILD_MEMBER : 0x1619
typedef struct _S_CSP_NEW_GUILD_MEMBER
{

} S_CSP_NEW_GUILD_MEMBER, * PS_CSP_NEW_GUILD_MEMBER;


// SCP_NEW_GUILD_MEMBER : 0x9619
typedef struct _S_SCP_NEW_GUILD_MEMBER
{
	S_GUILD_MEMBER_INFO                               MemberInfo;   // 길드원 정보

} S_SCP_NEW_GUILD_MEMBER, * PS_SCP_NEW_GUILD_MEMBER;


// CSP_REQ_SECEDE_GUILD : 0x161A
typedef struct _S_CSP_REQ_SECEDE_GUILD
{

} S_CSP_REQ_SECEDE_GUILD, * PS_CSP_REQ_SECEDE_GUILD;


// SCP_RESP_SECEDE_GUILD : 0x961A
typedef struct _S_SCP_RESP_SECEDE_GUILD
{
	BYTE                                              byResult;     // 길드 탈퇴요청 결과
	char                                              szGuildName[26];// 탈퇴한 길드의 이름

} S_SCP_RESP_SECEDE_GUILD, * PS_SCP_RESP_SECEDE_GUILD;


// CSP_SECEDE_GUILD_BROADCAST : 0x161B
typedef struct _S_CSP_SECEDE_GUILD_BROADCAST
{

} S_CSP_SECEDE_GUILD_BROADCAST, * PS_CSP_SECEDE_GUILD_BROADCAST;


// SCP_SECEDE_GUILD_BROADCAST : 0x961B
typedef struct _S_SCP_SECEDE_GUILD_BROADCAST
{
	char                                              szCharName[26];// 탈퇴할 길드원의 이름
	char                                              szName[26];   // 탈퇴한 길드의 이름

} S_SCP_SECEDE_GUILD_BROADCAST, * PS_SCP_SECEDE_GUILD_BROADCAST;


// CSP_REQ_EXPEL_GUILD_MEMBER : 0x161D
typedef struct _S_CSP_REQ_EXPEL_GUILD_MEMBER
{
	char                                              szCharName[26];// 방출할 길드원의 이름

} S_CSP_REQ_EXPEL_GUILD_MEMBER, * PS_CSP_REQ_EXPEL_GUILD_MEMBER;


// SCP_RESP_EXPEL_GUILD_MEMBER : 0x961D
typedef struct _S_SCP_RESP_EXPEL_GUILD_MEMBER
{
	BYTE                                              byResult;     // 길드 방출요청 결과
	char                                              szCharName[26];// 방출할 길드원의 이름

} S_SCP_RESP_EXPEL_GUILD_MEMBER, * PS_SCP_RESP_EXPEL_GUILD_MEMBER;


// CSP_EXPEL_GUILD_MEMBER_BROADCAST : 0x161E
typedef struct _S_CSP_EXPEL_GUILD_MEMBER_BROADCAST
{

} S_CSP_EXPEL_GUILD_MEMBER_BROADCAST, * PS_CSP_EXPEL_GUILD_MEMBER_BROADCAST;


// SCP_EXPEL_GUILD_MEMBER_BROADCAST : 0x961E
typedef struct _S_SCP_EXPEL_GUILD_MEMBER_BROADCAST
{
	char                                              szSourceName[26];// 방출한 길드원의 이름
	char                                              szTargetName[26];// 방출된 길드원의 이름

} S_SCP_EXPEL_GUILD_MEMBER_BROADCAST, * PS_SCP_EXPEL_GUILD_MEMBER_BROADCAST;


// CSP_REQ_QUEST_HISTORY : 0x1701
typedef struct _S_CSP_REQ_QUEST_HISTORY
{

} S_CSP_REQ_QUEST_HISTORY, * PS_CSP_REQ_QUEST_HISTORY;


// SCP_RESP_QUEST_HISTORY : 0x9701
typedef struct _S_SCP_RESP_QUEST_HISTORY
{
	BYTE                                              byCount;      // 퀘스트 히스토리 카운트

} S_SCP_RESP_QUEST_HISTORY, * PS_SCP_RESP_QUEST_HISTORY;


// CSP_QUEST_DIALOG : 0x1702
typedef struct _S_CSP_QUEST_DIALOG
{
	DWORD                                             dwDialogIndex;// 대화 번호
	BYTE                                              byResult;     // 대화 결과

} S_CSP_QUEST_DIALOG, * PS_CSP_QUEST_DIALOG;


// SCP_QUEST_DIALOG : 0x9702
typedef struct _S_SCP_QUEST_DIALOG
{
	WORD                                              wIndex;       // 대화 번호

} S_SCP_QUEST_DIALOG, * PS_SCP_QUEST_DIALOG;


// CSP_QUEST_NOTIFY_LEVEL : 0x1703
typedef struct _S_CSP_QUEST_NOTIFY_LEVEL
{

} S_CSP_QUEST_NOTIFY_LEVEL, * PS_CSP_QUEST_NOTIFY_LEVEL;


// SCP_QUEST_NOTIFY_LEVEL : 0x9703
typedef struct _S_SCP_QUEST_NOTIFY_LEVEL
{
	DWORD                                             dwNPCIndex;   // NPC 인덱스 번호
	BYTE                                              byIndex;      // 퀘스트 인덱스 번호
	BYTE                                              byLevel;      // 퀘스트 진행 상태

} S_SCP_QUEST_NOTIFY_LEVEL, * PS_SCP_QUEST_NOTIFY_LEVEL;


// CSP_MONSTER_DISAPPEAR : 0x1801
typedef struct _S_CSP_MONSTER_DISAPPEAR
{

} S_CSP_MONSTER_DISAPPEAR, * PS_CSP_MONSTER_DISAPPEAR;


// SCP_MONSTER_DISAPPEAR : 0x9801
typedef struct _S_SCP_MONSTER_DISAPPEAR
{
	DWORD                                             dwKeyID;      // Monster의 KeyID
	BYTE                                              byType;       // Monster가 사라지는 유형

} S_SCP_MONSTER_DISAPPEAR, * PS_SCP_MONSTER_DISAPPEAR;


// CSP_CHAR_STATUS : 0x1802
typedef struct _S_CSP_CHAR_STATUS
{

} S_CSP_CHAR_STATUS, * PS_CSP_CHAR_STATUS;


// SCP_CHAR_STATUS : 0x9802
typedef struct _S_SCP_CHAR_STATUS
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	DWORD                                             dwStatus;     // 캐릭터의 상태 정보

} S_SCP_CHAR_STATUS, * PS_SCP_CHAR_STATUS;


// CSP_CHAR_MONSTER_STATUS_BROADCAST : 0x1803
typedef struct _S_CSP_CHAR_MONSTER_STATUS_BROADCAST
{

} S_CSP_CHAR_MONSTER_STATUS_BROADCAST, * PS_CSP_CHAR_MONSTER_STATUS_BROADCAST;


// SCP_CHAR_MONSTER_STATUS_BROADCAST : 0x9803
typedef struct _S_SCP_CHAR_MONSTER_STATUS_BROADCAST
{
	DWORD                                             dwKeyID;      // 캐릭터의 KeyID
	BYTE                                              byAct;        // 상태
	DWORD                                             dwStatus;     // 상태

} S_SCP_CHAR_MONSTER_STATUS_BROADCAST, * PS_SCP_CHAR_MONSTER_STATUS_BROADCAST;


// CSP_CHAR_DEATH : 0x1805
typedef struct _S_CSP_CHAR_DEATH
{

} S_CSP_CHAR_DEATH, * PS_CSP_CHAR_DEATH;


// SCP_CHAR_DEATH : 0x9805
typedef struct _S_SCP_CHAR_DEATH
{
	short                                             snLossPrana;  // 소실된 프라나의 양
	BYTE                                              byCount;      // 소실된 아이템의 수

} S_SCP_CHAR_DEATH, * PS_SCP_CHAR_DEATH;


// CSP_CHAR_MONSTER_DEATH_BROADCAST : 0x1806
typedef struct _S_CSP_CHAR_MONSTER_DEATH_BROADCAST
{

} S_CSP_CHAR_MONSTER_DEATH_BROADCAST, * PS_CSP_CHAR_MONSTER_DEATH_BROADCAST;


// SCP_CHAR_MONSTER_DEATH_BROADCAST : 0x9806
typedef struct _S_SCP_CHAR_MONSTER_DEATH_BROADCAST
{
	DWORD                                             dwKeyID;      // 죽은 캐릭터 또는 Monster의 KeyID

} S_SCP_CHAR_MONSTER_DEATH_BROADCAST, * PS_SCP_CHAR_MONSTER_DEATH_BROADCAST;


// CSP_CHAR_HP_RECOVERY : 0x1811
typedef struct _S_CSP_CHAR_HP_RECOVERY
{

} S_CSP_CHAR_HP_RECOVERY, * PS_CSP_CHAR_HP_RECOVERY;


// SCP_CHAR_HP_RECOVERY : 0x9811
typedef struct _S_SCP_CHAR_HP_RECOVERY
{
	int                                               nCurHP;       // 회복된 후의 현재 HP
	short                                             snHPRecoveryRate;// 캐릭터의 HP 회복율
	int                                               nPrana;       // 총 프라나의 양

} S_SCP_CHAR_HP_RECOVERY, * PS_SCP_CHAR_HP_RECOVERY;


// CSP_MONSTER_HP_RECOVERY : 0x1812
typedef struct _S_CSP_MONSTER_HP_RECOVERY
{

} S_CSP_MONSTER_HP_RECOVERY, * PS_CSP_MONSTER_HP_RECOVERY;


// SCP_MONSTER_HP_RECOVERY : 0x9812
typedef struct _S_SCP_MONSTER_HP_RECOVERY
{
	int                                               nCurHP;       // 회복된 후의 현재 HP
	short                                             snStress;     // Monster 스트레스

} S_SCP_MONSTER_HP_RECOVERY, * PS_SCP_MONSTER_HP_RECOVERY;


// CSP_CHAR_CAST_PROMOTE : 0x1821
typedef struct _S_CSP_CHAR_CAST_PROMOTE
{

} S_CSP_CHAR_CAST_PROMOTE, * PS_CSP_CHAR_CAST_PROMOTE;


// SCP_CHAR_CAST_PROMOTE : 0x9821
typedef struct _S_SCP_CHAR_CAST_PROMOTE
{
	BYTE                                              byCastClass;  // 상승된 후의 카스트 등급
	BYTE                                              byCastGrade;  // 상승된 후의 카스트 계급

} S_SCP_CHAR_CAST_PROMOTE, * PS_SCP_CHAR_CAST_PROMOTE;


// CSP_CHAR_CAST_PROMOTE_BROADCAST : 0x1822
typedef struct _S_CSP_CHAR_CAST_PROMOTE_BROADCAST
{

} S_CSP_CHAR_CAST_PROMOTE_BROADCAST, * PS_CSP_CHAR_CAST_PROMOTE_BROADCAST;


// SCP_CHAR_CAST_PROMOTE_BROADCAST : 0x9822
typedef struct _S_SCP_CHAR_CAST_PROMOTE_BROADCAST
{
	char                                              szName[26];   // 캐릭터의 이름
	BYTE                                              byCastClass;  // 상승된 후의 카스트 등급
	BYTE                                              byCastGrade;  // 상승된 후의 카스트 계급

} S_SCP_CHAR_CAST_PROMOTE_BROADCAST, * PS_SCP_CHAR_CAST_PROMOTE_BROADCAST;


// CSP_CHAR_PING : 0x1831
typedef struct _S_CSP_CHAR_PING
{

} S_CSP_CHAR_PING, * PS_CSP_CHAR_PING;


// SCP_CHAR_PING : 0x9831
typedef struct _S_SCP_CHAR_PING
{

} S_SCP_CHAR_PING, * PS_SCP_CHAR_PING;


// CSP_REQ_CHAR_LOCATION : 0x1832
typedef struct _S_CSP_REQ_CHAR_LOCATION
{
	char                                              szName[26];   // 캐릭터의 이름

} S_CSP_REQ_CHAR_LOCATION, * PS_CSP_REQ_CHAR_LOCATION;


// SCP_RESP_CHAR_LOCATION : 0x9832
typedef struct _S_SCP_RESP_CHAR_LOCATION
{
	BYTE                                              byResult;     // Result Field
	WORD                                              wServerID;    // Server ID

} S_SCP_RESP_CHAR_LOCATION, * PS_SCP_RESP_CHAR_LOCATION;


// CSP_CHAR_PARAMS_CHANGE : 0x1911
typedef struct _S_CSP_CHAR_PARAMS_CHANGE
{

} S_CSP_CHAR_PARAMS_CHANGE, * PS_CSP_CHAR_PARAMS_CHANGE;


// SCP_CHAR_PARAMS_CHANGE : 0x9911
typedef struct _S_SCP_CHAR_PARAMS_CHANGE
{
	int                                               nPrana;       // 현재 프라나
	short                                             snChakraMuscle;// 근육의 차크라
	short                                             snChakraNerve;// 신경의 차크라
	short                                             snChakraHeart;// 심장의 차크라
	short                                             snChakraSoul; // 정신의 차크라
	short                                             snPureChakraMuscle;// 순수 근육의 차크라
	short                                             snPureChakraNerve;// 순수 신경의 차크라
	short                                             snPureChakraHeart;// 순수 심장의 차크라
	short                                             snPureChakraSoul;// 순수 정신의 차크라
	short                                             snPhysicalMinDamage;// 물리 최소 데미지
	short                                             snPhysicalMaxDamage;// 물리 최대 데미지
	short                                             snMagicMinDamage;// 마법 최소 데미지
	short                                             snMagicMaxDamage;// 마법 최대 데미지
	short                                             snFireMinDamage;// 불 최소 데미지
	short                                             snFireMaxDamage;// 불 최대 데미지
	short                                             snColdMinDamage;// 추위 최소 데미지
	short                                             snColdMaxDamage;// 추위 최대 데미지
	short                                             snPoisonMinDamage;// 독 최소 데미지
	short                                             snPoisonMaxDamage;// 독 최대 데미지
	short                                             snAcidMinDamage;// 산 최소 데미지
	short                                             snAcidMaxDamage;// 산 최대 데미지
	short                                             snArmorIntensity;// 갑옷의 강도-방어력
	short                                             snAttackSuccRate;// 공격 성공률
	short                                             snAvoidanceRate;// 회피율
	int                                               nMaxHP;       // 캐릭터의 최대 HP
	short                                             snFireResist; // 불 저항력
	short                                             snColdResist; // 추위 저항력
	short                                             snPoisonResist;// 독 저항력
	short                                             snAcidResist; // 산 저항력

} S_SCP_CHAR_PARAMS_CHANGE, * PS_SCP_CHAR_PARAMS_CHANGE;


// CSP_REQ_CHAKRA_RISING : 0x1921
typedef struct _S_CSP_REQ_CHAKRA_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID
	BYTE                                              byReqChakraPart;// 차크라 상승 요청 부위

} S_CSP_REQ_CHAKRA_RISING, * PS_CSP_REQ_CHAKRA_RISING;


// SCP_RESP_CHAKRA_RISING : 0x9921
typedef struct _S_SCP_RESP_CHAKRA_RISING
{
	BYTE                                              byResult;     // 결과
	int                                               nChakraPoint; 
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	int                                               nPrana;       

} S_SCP_RESP_CHAKRA_RISING, * PS_SCP_RESP_CHAKRA_RISING;


// CSP_REQ_BRAHMAN_RISING : 0x1922
typedef struct _S_CSP_REQ_BRAHMAN_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID

} S_CSP_REQ_BRAHMAN_RISING, * PS_CSP_REQ_BRAHMAN_RISING;


// SCP_RESP_BRAHMAN_RISING : 0x9922
typedef struct _S_SCP_RESP_BRAHMAN_RISING
{
	BYTE                                              byResult;     // 결과
	int                                               nRisingBrahman;// 상승 후 현재 브라만 포인트 값
	BYTE                                              byCastClass;  // 브라만 포인트 상승 후 카스트 등급
	BYTE                                              byCastGrade;  // 브라만 포인트 상승 후 카스트 계급
	int                                               nPrana;       

} S_SCP_RESP_BRAHMAN_RISING, * PS_SCP_RESP_BRAHMAN_RISING;


// CSP_REQ_INCREASE_INVENTORY_SLOT : 0x1931
typedef struct _S_CSP_REQ_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// 인벤토리 종류

} S_CSP_REQ_INCREASE_INVENTORY_SLOT, * PS_CSP_REQ_INCREASE_INVENTORY_SLOT;


// SCP_RESP_INCREASE_INVENTORY_SLOT : 0x9931
typedef struct _S_SCP_RESP_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // 인벤토리 슬롯 증가 요청 결과
	BYTE                                              byCount;      // Inventory Expand Info

} S_SCP_RESP_INCREASE_INVENTORY_SLOT, * PS_SCP_RESP_INCREASE_INVENTORY_SLOT;


// CSP_REQ_DECREASE_INVENTORY_SLOT : 0x1932
typedef struct _S_CSP_REQ_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// 인벤토리 종류
	BYTE                                              byX;          // Bag Item 들어갈 좌표 X
	BYTE                                              byZ;          // Bag Item 들어갈 좌표 Z

} S_CSP_REQ_DECREASE_INVENTORY_SLOT, * PS_CSP_REQ_DECREASE_INVENTORY_SLOT;


// SCP_RESP_DECREASE_INVENTORY_SLOT : 0x9932
typedef struct _S_SCP_RESP_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // 결과

} S_SCP_RESP_DECREASE_INVENTORY_SLOT, * PS_SCP_RESP_DECREASE_INVENTORY_SLOT;


// CSP_REQ_NPC_POINT_UP : 0x1941
typedef struct _S_CSP_REQ_NPC_POINT_UP
{
	DWORD                                             dwNPCKeyID;   // NPC KeyID

} S_CSP_REQ_NPC_POINT_UP, * PS_CSP_REQ_NPC_POINT_UP;


// SCP_RESP_NPC_POINT_UP : 0x9941
typedef struct _S_SCP_RESP_NPC_POINT_UP
{
	BYTE                                              byResult;     // NPC 친절도 상승 요청 결과
	DWORD                                             dwGroup;      // NPC 계통 번호
	DWORD                                             dwPoint;      // 상승 후 변경된 포인트 값

} S_SCP_RESP_NPC_POINT_UP, * PS_SCP_RESP_NPC_POINT_UP;


// CSP_REQ_CHANGE_CKAKRA_TO_PRANA : 0x1951
typedef struct _S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA
{

} S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA, * PS_CSP_REQ_CHANGE_CKAKRA_TO_PRANA;


// SCP_RESP_CHANGE_CKAKRA_TO_PRANA : 0x9951
typedef struct _S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA
{
	BYTE                                              byResult;     // NPC 친절도 상승 요청 결과
	int                                               nPrana;       // 총프라나의 양

} S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA, * PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA;


// CSP_OTHER_CHAR_PARAM_BROADCAST : 0x1952
typedef struct _S_CSP_OTHER_CHAR_PARAM_BROADCAST
{

} S_CSP_OTHER_CHAR_PARAM_BROADCAST, * PS_CSP_OTHER_CHAR_PARAM_BROADCAST;


// SCP_OTHER_CHAR_PARAM_BROADCAST : 0x9952
typedef struct _S_SCP_OTHER_CHAR_PARAM_BROADCAST
{
	DWORD                                             dwKeyID;      // 케릭터의 KeyID
	DWORD                                             dwGuildMark;  // 길드마크인덱스

} S_SCP_OTHER_CHAR_PARAM_BROADCAST, * PS_SCP_OTHER_CHAR_PARAM_BROADCAST;


// CSP_REQ_SAVE_POSITION : 0x1961
typedef struct _S_CSP_REQ_SAVE_POSITION
{
	WORD                                              wRegenID;     // 위치저장장소의 ID

} S_CSP_REQ_SAVE_POSITION, * PS_CSP_REQ_SAVE_POSITION;


// SCP_RESP_SAVE_POSITION : 0x9961
typedef struct _S_SCP_RESP_SAVE_POSITION
{
	BYTE                                              byResult;     // NPC 친절도 상승 요청 결과

} S_SCP_RESP_SAVE_POSITION, * PS_SCP_RESP_SAVE_POSITION;


// CSP_REQ_PVP_RANKING : 0x1971
typedef struct _S_CSP_REQ_PVP_RANKING
{

} S_CSP_REQ_PVP_RANKING, * PS_CSP_REQ_PVP_RANKING;


// SCP_RESP_PVP_RANKING : 0x9971
typedef struct _S_SCP_RESP_PVP_RANKING
{
	S_PVP_INFO                                        PvpInfo[50];  

} S_SCP_RESP_PVP_RANKING, * PS_SCP_RESP_PVP_RANKING;


// CSP_REQ_SKILL_REGIST : 0x2001
typedef struct _S_CSP_REQ_SKILL_REGIST
{
	DWORD                                             dwIndex;      // 등록할 스킬의 Index
	BYTE                                              byType;       // SKILL의 종류

} S_CSP_REQ_SKILL_REGIST, * PS_CSP_REQ_SKILL_REGIST;


// SCP_RESP_SKILL_REGIST : 0xA001
typedef struct _S_SCP_RESP_SKILL_REGIST
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_SKILL_REGIST, * PS_SCP_RESP_SKILL_REGIST;


// CSP_SKILL_REGIST : 0x2002
typedef struct _S_CSP_SKILL_REGIST
{

} S_CSP_SKILL_REGIST, * PS_CSP_SKILL_REGIST;


// SCP_SKILL_REGIST : 0xA002
typedef struct _S_SCP_SKILL_REGIST
{
	DWORD                                             dwIndex;      // 자동 등록된 스킬의 Index
	BYTE                                              byType;       // SKILL의 종류

} S_SCP_SKILL_REGIST, * PS_SCP_SKILL_REGIST;


// CSP_REQ_SKILL_SELECT : 0x2003
typedef struct _S_CSP_REQ_SKILL_SELECT
{
	BYTE                                              bySelect;     // SKILL의 선택/해제
	BYTE                                              byHand;       // SKILL 오른쪽/왼쪽 구분
	DWORD                                             dwIndex;      // 선택/해제 스킬 Index

} S_CSP_REQ_SKILL_SELECT, * PS_CSP_REQ_SKILL_SELECT;


// SCP_RESP_SKILL_SELECT : 0xA003
typedef struct _S_SCP_RESP_SKILL_SELECT
{
	BYTE                                              byResult;     // SKILL 선택/해제 결과

} S_SCP_RESP_SKILL_SELECT, * PS_SCP_RESP_SKILL_SELECT;


// CSP_REQ_SKILL_SELECT_BROADCAST : 0x2004
typedef struct _S_CSP_REQ_SKILL_SELECT_BROADCAST
{

} S_CSP_REQ_SKILL_SELECT_BROADCAST, * PS_CSP_REQ_SKILL_SELECT_BROADCAST;


// SCP_RESP_SKILL_SELECT_BROADCAST : 0xA004
typedef struct _S_SCP_RESP_SKILL_SELECT_BROADCAST
{
	DWORD                                             dwKeyID;      // 케릭터의 KeyID
	BYTE                                              bySelect;     // SKILL의 선택/해제
	BYTE                                              byHand;       // SKILL 오른쪽/왼쪽 구분
	DWORD                                             dwIndex;      // 선택/해제 스킬 Index
	BYTE                                              byLevel;      // 스킬 레벨

} S_SCP_RESP_SKILL_SELECT_BROADCAST, * PS_SCP_RESP_SKILL_SELECT_BROADCAST;


// CSP_REQ_SKILL_USE2_CHAR : 0x2011
typedef struct _S_CSP_REQ_SKILL_USE2_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격할 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_SKILL_USE2_CHAR, * PS_CSP_REQ_SKILL_USE2_CHAR;


// SCP_RESP_SKILL_USE2_CHAR : 0xA011
typedef struct _S_SCP_RESP_SKILL_USE2_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_SCP_RESP_SKILL_USE2_CHAR, * PS_SCP_RESP_SKILL_USE2_CHAR;


// CSP_SKILL_READY_CHAR_BROADCAST : 0x2012
typedef struct _S_CSP_SKILL_READY_CHAR_BROADCAST
{

} S_CSP_SKILL_READY_CHAR_BROADCAST, * PS_CSP_SKILL_READY_CHAR_BROADCAST;


// SCP_SKILL_READY_CHAR_BROADCAST : 0xA012
typedef struct _S_SCP_SKILL_READY_CHAR_BROADCAST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwKeyID;      // 스킬을 사용하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;// 스킬 공격을 당하는 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표

} S_SCP_SKILL_READY_CHAR_BROADCAST, * PS_SCP_SKILL_READY_CHAR_BROADCAST;


// CSP_REQ_SKILL_ATK_CHAR : 0x2013
typedef struct _S_CSP_REQ_SKILL_ATK_CHAR
{
	BYTE                                              byType;       // 대상 Type
	DWORD                                             dwTargetKeyID;// 공격할 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	short                                             snDegree;     // 공격자를 중심으로 한 방어자의 각도
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값

} S_CSP_REQ_SKILL_ATK_CHAR, * PS_CSP_REQ_SKILL_ATK_CHAR;


// SCP_RESP_SKILL_ATK_CHAR : 0xA013
typedef struct _S_SCP_RESP_SKILL_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCharX;      // 방어자 X 좌표
	short                                             snCharZ;      // 방어자 Z 좌표
	BYTE                                              byClientCount;// Client에서 사용할 카운트 값
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터/Monster의 현재 HP

} S_SCP_RESP_SKILL_ATK_CHAR, * PS_SCP_RESP_SKILL_ATK_CHAR;


// CSP_SKILL_ATK_CHAR_BROADCAST : 0x2014
typedef struct _S_CSP_SKILL_ATK_CHAR_BROADCAST
{

} S_CSP_SKILL_ATK_CHAR_BROADCAST, * PS_CSP_SKILL_ATK_CHAR_BROADCAST;


// SCP_SKILL_ATK_CHAR_BROADCAST : 0xA014
typedef struct _S_SCP_SKILL_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // 대상 Type
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // 스킬을 사용하는 캐릭터의 KeyID
	DWORD                                             dwTargetKeyID;//  스킬 공격을 당하는 캐릭터의 KeyID
	DWORD                                             dwIndex;      // 공격에 사용할 스킬의 Index
	short                                             snX;          // 맵 X 좌표
	short                                             snZ;          // 맵 Z 좌표
	short                                             snCharX;      // 방어자 X 좌표
	short                                             snCharZ;      // 방어자 Z 좌표
	int                                               nReduceHP;    // 데미지값
	int                                               nCurHP;       // 공격 당하는 캐릭터의 현재 HP
	BYTE                                              byCritical;   // 크리티컬 히트 판정 여부
	short                                             snCurX;       // 공격자의 현재 X 좌표
	short                                             snCurZ;       // 공격자의 현재 Z 좌표

} S_SCP_SKILL_ATK_CHAR_BROADCAST, * PS_SCP_SKILL_ATK_CHAR_BROADCAST;


// CSP_REQ_SKILL_LEVEL_UP : 0x2021
typedef struct _S_CSP_REQ_SKILL_LEVEL_UP
{
	DWORD                                             dwIndex;      // Level-Up을 요청할 스킬의 Index

} S_CSP_REQ_SKILL_LEVEL_UP, * PS_CSP_REQ_SKILL_LEVEL_UP;


// SCP_RESP_SKILL_LEVEL_UP : 0xA021
typedef struct _S_SCP_RESP_SKILL_LEVEL_UP
{
	BYTE                                              byResult;     // Level-Up 결과
	BYTE                                              byLevel;      // 스킬의 Level
	int                                               nPrana;       // 현재 프라나의 양
	short                                             snMovingSpeed;// 아이템의 이동속도
	short                                             snAttackSpeed;// 아이템의 공격속도
	short                                             snCastingSpeed;// 아이템의 케스팅속도
	BYTE                                              byShootRange; // 발사체의 사정거리

} S_SCP_RESP_SKILL_LEVEL_UP, * PS_SCP_RESP_SKILL_LEVEL_UP;


// CSP_REQ_SHOP_SKILL_LIST : 0x2022
typedef struct _S_CSP_REQ_SHOP_SKILL_LIST
{
	DWORD                                             dwIndex;      
	DWORD                                             dwNpcKeyID;   

} S_CSP_REQ_SHOP_SKILL_LIST, * PS_CSP_REQ_SHOP_SKILL_LIST;


// SCP_RESP_SHOP_SKILL_LIST : 0xA022
typedef struct _S_SCP_RESP_SHOP_SKILL_LIST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCount;      // 습득 가능한 스킬의 수

} S_SCP_RESP_SHOP_SKILL_LIST, * PS_SCP_RESP_SHOP_SKILL_LIST;


// CSP_REQ_SHOP_ITEM_LIST : 0x2101
typedef struct _S_CSP_REQ_SHOP_ITEM_LIST
{
	DWORD                                             dwIndex;      
	DWORD                                             dwNpcKeyID;   

} S_CSP_REQ_SHOP_ITEM_LIST, * PS_CSP_REQ_SHOP_ITEM_LIST;


// SCP_RESP_SHOP_ITEM_LIST : 0xA101
typedef struct _S_SCP_RESP_SHOP_ITEM_LIST
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwMakingIndex;// 제작중인 아이템 Index
	DWORD                                             dwRemainTime; // 제작중인 아이템의 남은 제작시간
	BYTE                                              byCount;      // 제작 가능한 아이템의 수

} S_SCP_RESP_SHOP_ITEM_LIST, * PS_SCP_RESP_SHOP_ITEM_LIST;


// CSP_REQ_ITEM_MAKING : 0x2102
typedef struct _S_CSP_REQ_ITEM_MAKING
{
	DWORD                                             dwIndex;      // 제작의뢰할 아이템 Index
	BYTE                                              byCount;      // 제작의뢰할 아이템 개수

} S_CSP_REQ_ITEM_MAKING, * PS_CSP_REQ_ITEM_MAKING;


// SCP_RESP_ITEM_MAKING : 0xA102
typedef struct _S_SCP_RESP_ITEM_MAKING
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byPlace;      // 아이템의 위치
	int                                               nSteel;       // 현재 루피아
	int                                               nCloth;       // 현재 보조카운트(의미없음)
	DWORD                                             dwNeedTime;   // 아이템 제작에 필요한 시간
	DWORD                                             dwKeyID;      // 새로 생성된 아이템의 KeyID
	short                                             snX;          // 새로 생성된 아이템의 인벤내의 X좌표
	short                                             snZ;          // 새로 생성된 아이템의 인벤내의 Z좌표

} S_SCP_RESP_ITEM_MAKING, * PS_SCP_RESP_ITEM_MAKING;


// CSP_REQ_ITEM_REDEEM : 0x2103
typedef struct _S_CSP_REQ_ITEM_REDEEM
{

} S_CSP_REQ_ITEM_REDEEM, * PS_CSP_REQ_ITEM_REDEEM;


// SCP_RESP_ITEM_REDEEM : 0xA103
typedef struct _S_SCP_RESP_ITEM_REDEEM
{
	DWORD                                             dwNeedTime;   // 생성된 아이템의 Index
	DWORD                                             dwKeyID;      // 생성된 아이템의 KeyID

} S_SCP_RESP_ITEM_REDEEM, * PS_SCP_RESP_ITEM_REDEEM;


// CSP_REQ_ITEM_REPAIR : 0x2104
typedef struct _S_CSP_REQ_ITEM_REPAIR
{
	DWORD                                             dwKeyID;      // 수리할 아이템의 KeyID

} S_CSP_REQ_ITEM_REPAIR, * PS_CSP_REQ_ITEM_REPAIR;


// SCP_RESP_ITEM_REPAIR : 0xA104
typedef struct _S_SCP_RESP_ITEM_REPAIR
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // 현재 루피아
	int                                               nCloth;       // 현재 보조카운트(의미없음)

} S_SCP_RESP_ITEM_REPAIR, * PS_SCP_RESP_ITEM_REPAIR;


// CSP_REQ_ITEM_DISMANTLE : 0x2105
typedef struct _S_CSP_REQ_ITEM_DISMANTLE
{
	DWORD                                             dwKeyID;      // 해체할 아이템의 KeyID

} S_CSP_REQ_ITEM_DISMANTLE, * PS_CSP_REQ_ITEM_DISMANTLE;


// SCP_RESP_ITEM_DISMANTLE : 0xA105
typedef struct _S_SCP_RESP_ITEM_DISMANTLE
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // 현재 루피아
	int                                               nCloth;       // 현재 보조카운트(의미없음)

} S_SCP_RESP_ITEM_DISMANTLE, * PS_SCP_RESP_ITEM_DISMANTLE;


// CSP_REQ_ITEM_REFINING : 0x2106
typedef struct _S_CSP_REQ_ITEM_REFINING
{
	DWORD                                             dwKeyID;      // 제련할 아이템의 KeyID
	DWORD                                             dwSubKeyID;   // 첨가할 보조재료의 KeyID

} S_CSP_REQ_ITEM_REFINING, * PS_CSP_REQ_ITEM_REFINING;


// SCP_RESP_ITEM_REFINING : 0xA106
typedef struct _S_SCP_RESP_ITEM_REFINING
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // 제련된 아이템의 KeyID
	DWORD                                             dwSubKeyID;   // 첨가된 보조아이템의 KeyID
	int                                               nMoney;       // 케릭터의 현재 루피아
	int                                               nPrana;       // 케릭터의 현재 프라나
	BYTE                                              byCount;      // 보조재료의 수

} S_SCP_RESP_ITEM_REFINING, * PS_SCP_RESP_ITEM_REFINING;


// CSP_REQ_PRANA_CONTRIBUTION : 0x2112
typedef struct _S_CSP_REQ_PRANA_CONTRIBUTION
{
	int                                               nPrana;       // 헌납할 프라나의 양

} S_CSP_REQ_PRANA_CONTRIBUTION, * PS_CSP_REQ_PRANA_CONTRIBUTION;


// SCP_RESP_PRANA_CONTRIBUTION : 0xA112
typedef struct _S_SCP_RESP_PRANA_CONTRIBUTION
{
	BYTE                                              byResult;     // Result Field
	int                                               nBrahmanPoint;// 헌납 후 브라만 포인트
	int                                               nMaxHP;       // 후 캐릭터의 최대 HP
	short                                             snUsePrana;   // 각 부위별 차크라에서 단위시간당 소모되는 총 프라나의 양

} S_SCP_RESP_PRANA_CONTRIBUTION, * PS_SCP_RESP_PRANA_CONTRIBUTION;


// CSP_REQ_RESOURCE_BARTER : 0x2113
typedef struct _S_CSP_REQ_RESOURCE_BARTER
{
	DWORD                                             dwNpcKeyID;   // 교환소 NPC KeyID
	DWORD                                             dwKeyID;      // 교환할 아이템의 KEYID
	int                                               nItemCount;   // 교환할 아이템의 중첩개수

} S_CSP_REQ_RESOURCE_BARTER, * PS_CSP_REQ_RESOURCE_BARTER;


// SCP_RESP_RESOURCE_BARTER : 0xA113
typedef struct _S_SCP_RESP_RESOURCE_BARTER
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // 현재 루피아
	int                                               nCloth;       // 현재 보조카운트(의미없음)

} S_SCP_RESP_RESOURCE_BARTER, * PS_SCP_RESP_RESOURCE_BARTER;


// CSP_REQ_RESOURCE_BARTER_PRICE : 0x2114
typedef struct _S_CSP_REQ_RESOURCE_BARTER_PRICE
{

} S_CSP_REQ_RESOURCE_BARTER_PRICE, * PS_CSP_REQ_RESOURCE_BARTER_PRICE;


// SCP_RESP_RESOURCE_BARTER_PRICE : 0xA114
typedef struct _S_SCP_RESP_RESOURCE_BARTER_PRICE
{
	int                                               nSteelCount;  // 철의 교환비율
	int                                               nClothCount;  // 직물의 교환비율

} S_SCP_RESP_RESOURCE_BARTER_PRICE, * PS_SCP_RESP_RESOURCE_BARTER_PRICE;


// CSP_REQ_EXCHANGE : 0x2201
typedef struct _S_CSP_REQ_EXCHANGE
{
	DWORD                                             dwKeyID;      // 아이템 교환을 할 캐릭터의 KeyID

} S_CSP_REQ_EXCHANGE, * PS_CSP_REQ_EXCHANGE;


// SCP_RESP_EXCHANGE : 0xA201
typedef struct _S_SCP_RESP_EXCHANGE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_EXCHANGE, * PS_SCP_RESP_EXCHANGE;


// CSP_EXCHANGE_NOTIFY : 0x2202
typedef struct _S_CSP_EXCHANGE_NOTIFY
{

} S_CSP_EXCHANGE_NOTIFY, * PS_CSP_EXCHANGE_NOTIFY;


// SCP_EXCHANGE_NOTIFY : 0xA202
typedef struct _S_SCP_EXCHANGE_NOTIFY
{
	DWORD                                             dwKeyID;      // 아이템 교환을 요청한 캐릭터의 KeyID

} S_SCP_EXCHANGE_NOTIFY, * PS_SCP_EXCHANGE_NOTIFY;


// CSP_EXCHANGE_RESULT : 0x2203
typedef struct _S_CSP_EXCHANGE_RESULT
{
	DWORD                                             dwKeyID;      // 아이템 교환을 요청한 캐릭터의 KeyID
	BYTE                                              byResult;     // 승낙 여부

} S_CSP_EXCHANGE_RESULT, * PS_CSP_EXCHANGE_RESULT;


// SCP_EXCHANGE_RESULT : 0xA203
typedef struct _S_SCP_EXCHANGE_RESULT
{

} S_SCP_EXCHANGE_RESULT, * PS_SCP_EXCHANGE_RESULT;


// CSP_EXCHANGE_RESULT_NOTIFY : 0x2204
typedef struct _S_CSP_EXCHANGE_RESULT_NOTIFY
{

} S_CSP_EXCHANGE_RESULT_NOTIFY, * PS_CSP_EXCHANGE_RESULT_NOTIFY;


// SCP_EXCHANGE_RESULT_NOTIFY : 0xA204
typedef struct _S_SCP_EXCHANGE_RESULT_NOTIFY
{
	DWORD                                             dwKeyID;      // 교환 요청 결과를 보내온 캐릭터의 KeyID
	BYTE                                              byResult;     // 승낙 여부

} S_SCP_EXCHANGE_RESULT_NOTIFY, * PS_SCP_EXCHANGE_RESULT_NOTIFY;


// CSP_REQ_EXCHANGE_ADD : 0x2205
typedef struct _S_CSP_REQ_EXCHANGE_ADD
{
	DWORD                                             dwKeyID;      // 교환창에 추가할 아이템의 KeyID
	short                                             snX;          // 교환창내의 아이템 X 좌표
	short                                             snZ;          // 교환창내의 아이템 Z 좌표

} S_CSP_REQ_EXCHANGE_ADD, * PS_CSP_REQ_EXCHANGE_ADD;


// SCP_RESP_EXCHANGE_ADD : 0xA205
typedef struct _S_SCP_RESP_EXCHANGE_ADD
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_EXCHANGE_ADD, * PS_SCP_RESP_EXCHANGE_ADD;


// CSP_EXCHANGE_ADD_NOTIFY : 0x2206
typedef struct _S_CSP_EXCHANGE_ADD_NOTIFY
{

} S_CSP_EXCHANGE_ADD_NOTIFY, * PS_CSP_EXCHANGE_ADD_NOTIFY;


// SCP_EXCHANGE_ADD_NOTIFY : 0xA206
typedef struct _S_SCP_EXCHANGE_ADD_NOTIFY
{
	DWORD                                             dwKeyID;      // 교환창에 추가한 아이템의 KeyID
	DWORD                                             dwIndex;      // 교환창에 추가한 아이템의 Index
	short                                             snCurDurability;
	int                                               nItemCount;   // 교환창에 추가한 아이템의 수량
	short                                             snX;          // 교환창내의 아이템 X 좌표
	short                                             snZ;          // 교환창내의 아이템 Z 좌표
	BYTE                                              bySubMaterialCount;

} S_SCP_EXCHANGE_ADD_NOTIFY, * PS_SCP_EXCHANGE_ADD_NOTIFY;


// CSP_REQ_EXCHANGE_ERASE : 0x2207
typedef struct _S_CSP_REQ_EXCHANGE_ERASE
{
	DWORD                                             dwKeyID;      // 교환창에서 제거할 아이템의 KeyID

} S_CSP_REQ_EXCHANGE_ERASE, * PS_CSP_REQ_EXCHANGE_ERASE;


// SCP_RESP_EXCHANGE_ERASE : 0xA207
typedef struct _S_SCP_RESP_EXCHANGE_ERASE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_EXCHANGE_ERASE, * PS_SCP_RESP_EXCHANGE_ERASE;


// CSP_EXCHANGE_ERASE_NOTIFY : 0x2208
typedef struct _S_CSP_EXCHANGE_ERASE_NOTIFY
{

} S_CSP_EXCHANGE_ERASE_NOTIFY, * PS_CSP_EXCHANGE_ERASE_NOTIFY;


// SCP_EXCHANGE_ERASE_NOTIFY : 0xA208
typedef struct _S_SCP_EXCHANGE_ERASE_NOTIFY
{
	DWORD                                             dwKeyID;      // 교환창에서 제거한 아이템의 KeyID

} S_SCP_EXCHANGE_ERASE_NOTIFY, * PS_SCP_EXCHANGE_ERASE_NOTIFY;


// CSP_EXCHANGE_ACCEPT : 0x2209
typedef struct _S_CSP_EXCHANGE_ACCEPT
{
	BYTE                                              byAccept;     // 확인 버튼 세팅 여부

} S_CSP_EXCHANGE_ACCEPT, * PS_CSP_EXCHANGE_ACCEPT;


// SCP_EXCHANGE_ACCEPT : 0xA209
typedef struct _S_SCP_EXCHANGE_ACCEPT
{
	BYTE                                              byResult;     // Result Field
	int                                               nMoney;       // 교환시 케릭터의 루피아양

} S_SCP_EXCHANGE_ACCEPT, * PS_SCP_EXCHANGE_ACCEPT;


// CSP_EXCHANGE_ACCEPT_NOTIFY : 0x220A
typedef struct _S_CSP_EXCHANGE_ACCEPT_NOTIFY
{

} S_CSP_EXCHANGE_ACCEPT_NOTIFY, * PS_CSP_EXCHANGE_ACCEPT_NOTIFY;


// SCP_EXCHANGE_ACCEPT_NOTIFY : 0xA20A
typedef struct _S_SCP_EXCHANGE_ACCEPT_NOTIFY
{
	BYTE                                              byAccept;     // 교환창 확인 버튼 세팅 여부
	int                                               nMoney;       // 교환시 케릭터의 루피아양

} S_SCP_EXCHANGE_ACCEPT_NOTIFY, * PS_SCP_EXCHANGE_ACCEPT_NOTIFY;


// CSP_EXCHANGE_CANCEL : 0x220B
typedef struct _S_CSP_EXCHANGE_CANCEL
{

} S_CSP_EXCHANGE_CANCEL, * PS_CSP_EXCHANGE_CANCEL;


// SCP_EXCHANGE_CANCEL : 0xA20B
typedef struct _S_SCP_EXCHANGE_CANCEL
{

} S_SCP_EXCHANGE_CANCEL, * PS_SCP_EXCHANGE_CANCEL;


// CSP_REQ_EXCHANGE_MONEY : 0x220C
typedef struct _S_CSP_REQ_EXCHANGE_MONEY
{
	int                                               nExMoney;     // 교환할 돈

} S_CSP_REQ_EXCHANGE_MONEY, * PS_CSP_REQ_EXCHANGE_MONEY;


// SCP_RESP_EXCHANGE_MONEY : 0xA20C
typedef struct _S_SCP_RESP_EXCHANGE_MONEY
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_EXCHANGE_MONEY, * PS_SCP_RESP_EXCHANGE_MONEY;


// CSP_EXCHANGE_MONEY_NOTIFY : 0x220D
typedef struct _S_CSP_EXCHANGE_MONEY_NOTIFY
{

} S_CSP_EXCHANGE_MONEY_NOTIFY, * PS_CSP_EXCHANGE_MONEY_NOTIFY;


// SCP_EXCHANGE_MONEY_NOTIFY : 0xA20D
typedef struct _S_SCP_EXCHANGE_MONEY_NOTIFY
{
	int                                               nExMoney;     // 교환할 돈

} S_SCP_EXCHANGE_MONEY_NOTIFY, * PS_SCP_EXCHANGE_MONEY_NOTIFY;


// CSP_REQ_TRADE_ENTRY : 0x2301
typedef struct _S_CSP_REQ_TRADE_ENTRY
{
	char                                              szTitle[32];  // 거래 제목
	int                                               nGoldCount;   // 원하는 금액
	BYTE                                              byAKindCount; 

} S_CSP_REQ_TRADE_ENTRY, * PS_CSP_REQ_TRADE_ENTRY;


// SCP_RESP_TRADE_ENTRY : 0xA301
typedef struct _S_SCP_RESP_TRADE_ENTRY
{
	BYTE                                              byResult;     // 거래 등록 결과값

} S_SCP_RESP_TRADE_ENTRY, * PS_SCP_RESP_TRADE_ENTRY;


// CSP_REQ_TRADE_CANCEL : 0x2302
typedef struct _S_CSP_REQ_TRADE_CANCEL
{
	DWORD                                             dwTradeID;    // 취소할 거래 항목 아이디

} S_CSP_REQ_TRADE_CANCEL, * PS_CSP_REQ_TRADE_CANCEL;


// SCP_RESP_TRADE_CANCEL : 0xA302
typedef struct _S_SCP_RESP_TRADE_CANCEL
{
	BYTE                                              byResult;     // 거래 등록 취소 결과값

} S_SCP_RESP_TRADE_CANCEL, * PS_SCP_RESP_TRADE_CANCEL;


// CSP_REQ_TRADE : 0x2303
typedef struct _S_CSP_REQ_TRADE
{
	DWORD                                             dwTradeID;    // 거래할 거래 항목 아이디

} S_CSP_REQ_TRADE, * PS_CSP_REQ_TRADE;


// SCP_RESP_TRADE : 0xA303
typedef struct _S_SCP_RESP_TRADE
{
	BYTE                                              byResult;     // 거래 요청 결과 값

} S_SCP_RESP_TRADE, * PS_SCP_RESP_TRADE;


// SCP_RESP_TRADE_SUCCESS : 0xA307
typedef struct _S_SCP_RESP_TRADE_SUCCESS
{
	int                                               nGoldCount;   // 재계산된 현재 루피아

} S_SCP_RESP_TRADE_SUCCESS, * PS_SCP_RESP_TRADE_SUCCESS;


// CSP_REQ_TRADE_LIST : 0x2304
typedef struct _S_CSP_REQ_TRADE_LIST
{
	BYTE                                              bySearchMethod;// 검색방법-일반/텍스트검색
	BYTE                                              byCatalogue;  // 검색목록-캐릭터이름/제목
	BYTE                                              byNewSearch;  // 새로운검색인지 구분
	char                                              szSearchChat[32];// 거래 제목
	short                                             snTabNumber;  // 검색 탭 번호

} S_CSP_REQ_TRADE_LIST, * PS_CSP_REQ_TRADE_LIST;


// SCP_RESP_TRADE_LIST : 0xA304
typedef struct _S_SCP_RESP_TRADE_LIST
{
	short                                             snTolListCount;// 총 거래항목 개수
	BYTE                                              byListCount;  // 보낸 거래항목 개수
	DWORD                                             dwTradeID;    // 거래 항목 아이디
	char                                              szCharName[26];// 등록자 캐릭터 이름
	char                                              szTitle[32];  // 거래 제목
	int                                               nGoldCount;   // 원하는 금액
	BYTE                                              byAKindCount; 

} S_SCP_RESP_TRADE_LIST, * PS_SCP_RESP_TRADE_LIST;


// CSP_REQ_MY_ENTYR_LIST : 0x2305
typedef struct _S_CSP_REQ_MY_ENTYR_LIST
{

} S_CSP_REQ_MY_ENTYR_LIST, * PS_CSP_REQ_MY_ENTYR_LIST;


// SCP_RESP_MY_ENTYR_LIST : 0xA305
typedef struct _S_SCP_RESP_MY_ENTYR_LIST
{
	BYTE                                              byListCount;  // 보낸 거래항목 개수
	BYTE                                              byState;      // 0x00-등록/0x01-보관
	BYTE                                              byAKindCount; 

} S_SCP_RESP_MY_ENTYR_LIST, * PS_SCP_RESP_MY_ENTYR_LIST;


// CSP_REQ_TRADE_ITEM_SEEK : 0x2306
typedef struct _S_CSP_REQ_TRADE_ITEM_SEEK
{
	BYTE                                              bySeekMethod; // 찾기방법
	BYTE                                              byAKindCount; 

} S_CSP_REQ_TRADE_ITEM_SEEK, * PS_CSP_REQ_TRADE_ITEM_SEEK;


// SCP_RESP_TRADE_ITEM_SEEK : 0xA306
typedef struct _S_SCP_RESP_TRADE_ITEM_SEEK
{
	BYTE                                              byResult;     // 거래 요청 결과 값

} S_SCP_RESP_TRADE_ITEM_SEEK, * PS_SCP_RESP_TRADE_ITEM_SEEK;


// CSP_REQ_TRANSPARENCY_MODE : 0x2501
typedef struct _S_CSP_REQ_TRANSPARENCY_MODE
{
	BYTE                                              byMode;       // 투명모드 설정플레그

} S_CSP_REQ_TRANSPARENCY_MODE, * PS_CSP_REQ_TRANSPARENCY_MODE;


// SCP_RESP_TRANSPARENCY_MODE : 0xA501
typedef struct _S_SCP_RESP_TRANSPARENCY_MODE
{
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_TRANSPARENCY_MODE, * PS_SCP_RESP_TRANSPARENCY_MODE;


// CSP_TRANSPARENCY_MODE_NOTIFY : 0x2502
typedef struct _S_CSP_TRANSPARENCY_MODE_NOTIFY
{

} S_CSP_TRANSPARENCY_MODE_NOTIFY, * PS_CSP_TRANSPARENCY_MODE_NOTIFY;


// SCP_TRANSPARENCY_MODE_NOTIFY : 0xA502
typedef struct _S_SCP_TRANSPARENCY_MODE_NOTIFY
{
	BYTE                                              byMode;       // 투명모드 설정플레그
	char                                              szCharName[26];// GM 캐릭터 이름

} S_SCP_TRANSPARENCY_MODE_NOTIFY, * PS_SCP_TRANSPARENCY_MODE_NOTIFY;


// CSP_REQ_MOVE_POSITION : 0x2511
typedef struct _S_CSP_REQ_MOVE_POSITION
{
	short                                             snX;          // 워프이동 X좌표
	short                                             snZ;          // 워프이동 Z좌표
	BYTE                                              byY;          // 워프이동의 층 높이

} S_CSP_REQ_MOVE_POSITION, * PS_CSP_REQ_MOVE_POSITION;


// SCP_RESP_MOVE_POSITION : 0xA511
typedef struct _S_SCP_RESP_MOVE_POSITION
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // 워프이동 X좌표
	short                                             snZ;          // 워프이동 Z좌표
	BYTE                                              byY;          // 워프이동의 층 높이

} S_SCP_RESP_MOVE_POSITION, * PS_SCP_RESP_MOVE_POSITION;


// CSP_REQ_MOVE_NEAR_CHAR : 0x2512
typedef struct _S_CSP_REQ_MOVE_NEAR_CHAR
{
	char                                              szCharName[26];// 대상 캐릭터 이름

} S_CSP_REQ_MOVE_NEAR_CHAR, * PS_CSP_REQ_MOVE_NEAR_CHAR;


// SCP_RESP_MOVE_NEAR_CHAR : 0xA512
typedef struct _S_SCP_RESP_MOVE_NEAR_CHAR
{
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // 이동지역 정보

} S_SCP_RESP_MOVE_NEAR_CHAR, * PS_SCP_RESP_MOVE_NEAR_CHAR;


// CSP_REQ_CHAR_RECALL : 0x2513
typedef struct _S_CSP_REQ_CHAR_RECALL
{
	char                                              szCharName[26];// 대상 캐릭터 이름

} S_CSP_REQ_CHAR_RECALL, * PS_CSP_REQ_CHAR_RECALL;


// SCP_RESP_CHAR_RECALL : 0xA513
typedef struct _S_SCP_RESP_CHAR_RECALL
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// 대상 캐릭터 이름

} S_SCP_RESP_CHAR_RECALL, * PS_SCP_RESP_CHAR_RECALL;


// CSP_CHAR_RECALL_NOTIFY : 0x2514
typedef struct _S_CSP_CHAR_RECALL_NOTIFY
{

} S_CSP_CHAR_RECALL_NOTIFY, * PS_CSP_CHAR_RECALL_NOTIFY;


// SCP_CHAR_RECALL_NOTIFY : 0xA514
typedef struct _S_SCP_CHAR_RECALL_NOTIFY
{
	char                                              szCharName[26];// 대상 캐릭터 이름
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // 이동지역 정보

} S_SCP_CHAR_RECALL_NOTIFY, * PS_SCP_CHAR_RECALL_NOTIFY;


// CSP_REQ_CONTROL_CHAT : 0x2521
typedef struct _S_CSP_REQ_CONTROL_CHAT
{
	char                                              szCharName[26];// 대상 캐릭터 이름
	BYTE                                              byMode;       // 금지모드

} S_CSP_REQ_CONTROL_CHAT, * PS_CSP_REQ_CONTROL_CHAT;


// SCP_RESP_CONTROL_CHAT : 0xA521
typedef struct _S_SCP_RESP_CONTROL_CHAT
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// 대상 캐릭터 이름

} S_SCP_RESP_CONTROL_CHAT, * PS_SCP_RESP_CONTROL_CHAT;


// CSP_CONTROL_CHAT_NOTIFY : 0x2522
typedef struct _S_CSP_CONTROL_CHAT_NOTIFY
{

} S_CSP_CONTROL_CHAT_NOTIFY, * PS_CSP_CONTROL_CHAT_NOTIFY;


// SCP_CONTROL_CHAT_NOTIFY : 0xA522
typedef struct _S_SCP_CONTROL_CHAT_NOTIFY
{
	char                                              szCharName[26];// 대상 캐릭터 이름
	BYTE                                              byMode;       // 금지모드

} S_SCP_CONTROL_CHAT_NOTIFY, * PS_SCP_CONTROL_CHAT_NOTIFY;


// CSP_REQ_CONTROL_ACTION : 0x2531
typedef struct _S_CSP_REQ_CONTROL_ACTION
{
	char                                              szCharName[26];// 대상 캐릭터 이름
	BYTE                                              byMode;       // 금지모드

} S_CSP_REQ_CONTROL_ACTION, * PS_CSP_REQ_CONTROL_ACTION;


// SCP_RESP_CONTROL_ACTION : 0xA531
typedef struct _S_SCP_RESP_CONTROL_ACTION
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// 대상 캐릭터 이름

} S_SCP_RESP_CONTROL_ACTION, * PS_SCP_RESP_CONTROL_ACTION;


// CSP_CONTROL_ACTION_NOTIFY : 0x2532
typedef struct _S_CSP_CONTROL_ACTION_NOTIFY
{

} S_CSP_CONTROL_ACTION_NOTIFY, * PS_CSP_CONTROL_ACTION_NOTIFY;


// SCP_CONTROL_ACTION_NOTIFY : 0xA532
typedef struct _S_SCP_CONTROL_ACTION_NOTIFY
{
	char                                              szCharName[26];// 대상 캐릭터 이름
	BYTE                                              byMode;       // 금지모드

} S_SCP_CONTROL_ACTION_NOTIFY, * PS_SCP_CONTROL_ACTION_NOTIFY;


// CSP_REQ_TROUBLE_REPORT : 0x2541
typedef struct _S_CSP_REQ_TROUBLE_REPORT
{
	char                                              szReport[512];// 신고할 내용

} S_CSP_REQ_TROUBLE_REPORT, * PS_CSP_REQ_TROUBLE_REPORT;


// SCP_RESP_TROUBLE_REPORT : 0xA541
typedef struct _S_SCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwIndex;      // 접수번호

} S_SCP_RESP_TROUBLE_REPORT, * PS_SCP_RESP_TROUBLE_REPORT;


// CSP_REQ_TROUBLE_REPORT_LIST : 0x2542
typedef struct _S_CSP_REQ_TROUBLE_REPORT_LIST
{

} S_CSP_REQ_TROUBLE_REPORT_LIST, * PS_CSP_REQ_TROUBLE_REPORT_LIST;


// SCP_RESP_TROUBLE_REPORT_LIST : 0xA542
typedef struct _S_SCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // 접수된 총 신고의 갯수
	BYTE                                              byCount;      // 페이지내 신고의 갯수

} S_SCP_RESP_TROUBLE_REPORT_LIST, * PS_SCP_RESP_TROUBLE_REPORT_LIST;


// CSP_REQ_TROUBLE_REPORT_SET : 0x2543
typedef struct _S_CSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호

} S_CSP_REQ_TROUBLE_REPORT_SET, * PS_CSP_REQ_TROUBLE_REPORT_SET;


// SCP_RESP_TROUBLE_REPORT_SET : 0xA543
typedef struct _S_SCP_RESP_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	BYTE                                              byProceed;    // 처리상황

} S_SCP_RESP_TROUBLE_REPORT_SET, * PS_SCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT_LIST : 0x2544
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_LIST
{
	int                                               nPage;        // 신고리스트 페이지

} S_GCSP_REQ_TROUBLE_REPORT_LIST, * PS_GCSP_REQ_TROUBLE_REPORT_LIST;


// GSCP_RESP_TROUBLE_REPORT_LIST : 0xA544
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // 접수된 총 신고의 갯수
	BYTE                                              byCount;      // 페이지내 신고의 갯수

} S_GSCP_RESP_TROUBLE_REPORT_LIST, * PS_GSCP_RESP_TROUBLE_REPORT_LIST;


// GCSP_REQ_TROUBLE_REPORT_SET : 0x2545
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // 접수시 발급되는 접수번호
	BYTE                                              byProceed;    // 처리상황
	char                                              szNote[256];  // 비고

} S_GCSP_REQ_TROUBLE_REPORT_SET, * PS_GCSP_REQ_TROUBLE_REPORT_SET;


// GSCP_RESP_TROUBLE_REPORT_SET : 0xA545
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_SET
{
	BYTE                                              byResult;     // Result Field

} S_GSCP_RESP_TROUBLE_REPORT_SET, * PS_GSCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT : 0x2546
typedef struct _S_GCSP_REQ_TROUBLE_REPORT
{

} S_GCSP_REQ_TROUBLE_REPORT, * PS_GCSP_REQ_TROUBLE_REPORT;


// GSCP_RESP_TROUBLE_REPORT : 0xA546
typedef struct _S_GSCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field

} S_GSCP_RESP_TROUBLE_REPORT, * PS_GSCP_RESP_TROUBLE_REPORT;


// CSP_REQ_CHAR_INFO : 0x2561
typedef struct _S_CSP_REQ_CHAR_INFO
{
	char                                              szCharName[26];

} S_CSP_REQ_CHAR_INFO, * PS_CSP_REQ_CHAR_INFO;


// SCP_RESP_CHAR_INFO : 0xA561
typedef struct _S_SCP_RESP_CHAR_INFO
{
	char                                              szCharName[26];
	int                                               nMaxHP;       // 케릭터 HP의 최대값
	int                                               nCurHP;       // 케릭터 HP의 현재값
	short                                             snMinPhysicalDamage;
	short                                             snMaxPhysicalDamage;
	short                                             snMinMagicDamage;
	short                                             snMaxMagicDamage;
	short                                             snMinFireDamage;
	short                                             snMaxFireDamage;
	short                                             snMinColdDamage;
	short                                             snMaxColdDamage;
	short                                             snMinPoisonDamage;
	short                                             snMaxPoisonDamage;
	short                                             snMinAcidDamage;
	short                                             snMaxAcidDamage;
	short                                             snArmorIntensity;
	short                                             snBlockRate;  
	int                                               nSumChakraPoint;
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	short                                             snAttackSuccRate;
	short                                             snAvoidanceRate;
	short                                             snMovingSpeed;
	short                                             snAttackSpeed;

} S_SCP_RESP_CHAR_INFO, * PS_SCP_RESP_CHAR_INFO;


// CSP_REQ_CHAR_EQUIPMENT : 0x2562
typedef struct _S_CSP_REQ_CHAR_EQUIPMENT
{
	char                                              szCharName[26];

} S_CSP_REQ_CHAR_EQUIPMENT, * PS_CSP_REQ_CHAR_EQUIPMENT;


// SCP_RESP_CHAR_EQUIPMENT : 0xA562
typedef struct _S_SCP_RESP_CHAR_EQUIPMENT
{
	char                                              szCharName[26];
	BYTE                                              byCount;      // 장착아이템의 갯수

} S_SCP_RESP_CHAR_EQUIPMENT, * PS_SCP_RESP_CHAR_EQUIPMENT;


// CSP_REQ_CHAR_SKILL : 0x2563
typedef struct _S_CSP_REQ_CHAR_SKILL
{
	char                                              szCharName[26];

} S_CSP_REQ_CHAR_SKILL, * PS_CSP_REQ_CHAR_SKILL;


// SCP_RESP_CHAR_SKILL : 0xA563
typedef struct _S_SCP_RESP_CHAR_SKILL
{
	char                                              szCharName[26];
	S_SKILLINFO                                       SkillInfo[30];

} S_SCP_RESP_CHAR_SKILL, * PS_SCP_RESP_CHAR_SKILL;


// CSP_REQ_CLOSE_CHAR : 0x2571
typedef struct _S_CSP_REQ_CLOSE_CHAR
{
	char                                              szCharName[26];

} S_CSP_REQ_CLOSE_CHAR, * PS_CSP_REQ_CLOSE_CHAR;


// SCP_RESP_CLOSE_CHAR : 0xA571
typedef struct _S_SCP_RESP_CLOSE_CHAR
{
	char                                              szCharName[26];
	BYTE                                              byResult;     // Result Field

} S_SCP_RESP_CLOSE_CHAR, * PS_SCP_RESP_CLOSE_CHAR;


// CSP_REQ_JOIN_ADDRESS_BOOK : 0x2603
typedef struct _S_CSP_REQ_JOIN_ADDRESS_BOOK
{
	char                                              szName[26];   // 주소록에 추가할 캐릭터의 이름

} S_CSP_REQ_JOIN_ADDRESS_BOOK, * PS_CSP_REQ_JOIN_ADDRESS_BOOK;


// SCP_RESP_JOIN_ADDRESS_BOOK : 0xA603
typedef struct _S_SCP_RESP_JOIN_ADDRESS_BOOK
{
	BYTE                                              byResult;     // 주소록에 캐릭터추가 요청결과

} S_SCP_RESP_JOIN_ADDRESS_BOOK, * PS_SCP_RESP_JOIN_ADDRESS_BOOK;


// CSP_JOIN_ADDRESS_BOOK_NOTIFY : 0x2604
typedef struct _S_CSP_JOIN_ADDRESS_BOOK_NOTIFY
{

} S_CSP_JOIN_ADDRESS_BOOK_NOTIFY, * PS_CSP_JOIN_ADDRESS_BOOK_NOTIFY;


// SCP_JOIN_ADDRESS_BOOK_NOTIFY : 0xA604
typedef struct _S_SCP_JOIN_ADDRESS_BOOK_NOTIFY
{
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // 주소록 등록자 정보

} S_SCP_JOIN_ADDRESS_BOOK_NOTIFY, * PS_SCP_JOIN_ADDRESS_BOOK_NOTIFY;


// CSP_REQ_JOIN_ADDRESS_BOOK_RESULT : 0x2605
typedef struct _S_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT
{
	BYTE                                              byResult;     // 주소록에 캐릭터추가 요청결과
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // 주소록 추가를 요청한 캐릭터의 이름

} S_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT, * PS_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT;


// SCP_RESP_JOIN_ADDRESS_BOOK_RESULT : 0xA605
typedef struct _S_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT
{
	BYTE                                              byResult;     // 주소록 추가 요청 결과

} S_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT, * PS_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT;


// CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY : 0x2606
typedef struct _S_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY
{

} S_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY, * PS_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY;


// SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY : 0xA606
typedef struct _S_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY
{
	BYTE                                              byResult;     // 주소록 추가 요청에 대한 승인 결과
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // 주소록 추가를 요청한 캐릭터의 이름

} S_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY, * PS_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY;


// CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE : 0x2607
typedef struct _S_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE
{
	char                                              szName[26];   // 주소록에서 삭제할 캐릭터의 이름

} S_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE, * PS_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE;


// SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE : 0xA607
typedef struct _S_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE
{
	BYTE                                              byResult;     // 주소록에 있는 캐릭터 정보의 삭제요청 결과
	char                                              szName[26];   // 주소록에서 삭제할 캐릭터의 이름

} S_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE, * PS_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE;


// CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY : 0x2608
typedef struct _S_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY
{

} S_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY, * PS_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY;


// SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY : 0xA608
typedef struct _S_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY
{
	char                                              szName[26];   // 주소록에서 삭제할 캐릭터의 이름

} S_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY, * PS_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY;


// CSP_REQ_ADDRESS_BOOK_GROUP_ADD : 0x2611
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_ADD
{
	char                                              szGroup[26];  // 주소록에 추가할 그룹의 이름

} S_CSP_REQ_ADDRESS_BOOK_GROUP_ADD, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_ADD;


// SCP_RESP_ADDRESS_BOOK_GROUP_ADD : 0xA611
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_ADD
{
	BYTE                                              byResult;     // 그룹추가 요청결과
	char                                              szGroup[26];  // 주소록에 추가할 그룹의 이름

} S_SCP_RESP_ADDRESS_BOOK_GROUP_ADD, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_ADD;


// CSP_REQ_ADDRESS_BOOK_GROUP_DELETE : 0x2612
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE
{
	char                                              szGroup[26];  // 주소록에 삭제할 그룹의 이름

} S_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE;


// SCP_RESP_ADDRESS_BOOK_GROUP_DELETE : 0xA612
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE
{
	BYTE                                              byResult;     // 그룹삭제 요청결과
	char                                              szGroup[26];  // 주소록에 삭제할 그룹의 이름

} S_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE;


// CSP_REQ_ADDRESS_BOOK_GROUP_MOVE : 0x2613
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE
{
	char                                              szGroup[26];  // 이동할 그룹의 이름
	char                                              szName[26];   // 이동할 케릭터의 이름

} S_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE;


// SCP_RESP_ADDRESS_BOOK_GROUP_MOVE : 0xA613
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE
{
	BYTE                                              byResult;     // 그룹이동에 대한 처리결과
	char                                              szName[26];   // 이동할 케릭터의 이름

} S_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE;


// CSP_REQ_ADDRESS_BOOK_GROUP_RENAME : 0x2614
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME
{
	char                                              szSourceGroup[26];// 이름을 변경할 그룹의 이름 - Source
	char                                              szTargetGroup[26];// 변동하고자 하는 그룹의 이름 - Target

} S_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME;


// SCP_RESP_ADDRESS_BOOK_GROUP_RENAME : 0xA614
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME
{
	BYTE                                              byResult;     // 그룹이름변경에 대한 처리결과
	char                                              szGroup[26];  // 이름이 변경된 그룹의 이름 - Source

} S_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME;


// CSP_REQ_ADDRESS_BOOK_STATUS : 0x2621
typedef struct _S_CSP_REQ_ADDRESS_BOOK_STATUS
{
	BYTE                                              byResult;     // 등록거부상태를 세팅한다.

} S_CSP_REQ_ADDRESS_BOOK_STATUS, * PS_CSP_REQ_ADDRESS_BOOK_STATUS;


// SCP_RESP_ADDRESS_BOOK_STATUS : 0xA621
typedef struct _S_SCP_RESP_ADDRESS_BOOK_STATUS
{
	BYTE                                              byResult;     // 주소록 등록요청의 처리결과

} S_SCP_RESP_ADDRESS_BOOK_STATUS, * PS_SCP_RESP_ADDRESS_BOOK_STATUS;


// GCSP_REQ_CHARACTER_SEARCH : 0x2547
typedef struct _S_GCSP_REQ_CHARACTER_SEARCH
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 변경할 캐릭터 이름
	char                                              szAccountID[18];// 변경할 계정 아이디

} S_GCSP_REQ_CHARACTER_SEARCH, * PS_GCSP_REQ_CHARACTER_SEARCH;


// GSCP_INIT_CHAR : 0xA547
typedef struct _S_GSCP_INIT_CHAR
{
	BYTE                                              byResult;     // 초기화 결과
	char                                              szCharName[26];
	char                                              szAccountID[18];
	BYTE                                              byRegion;     // 케릭터의 Region 위치
	BYTE                                              byZone;       // 케릭터의 Zone 위치
	BYTE                                              byTrimuriti;  
	BYTE                                              byTribe;      
	BYTE                                              byFaceType;   
	DWORD                                             dwCharBirth;  
	BYTE                                              byCastClass;  
	BYTE                                              byCastGrade;  
	BYTE                                              byTrimuritiClass;
	BYTE                                              bySpecialName;
	DWORD                                             dwSpecialNameGetTime;
	int                                               nBrahmanPoint;
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	int                                               nPrana;       // 총 프라나의 양
	int                                               nCurHP;       // 케릭터 HP의 현재값
	int                                               nMoney;       // 캐릭터가 현재 가지고 있는 돈

} S_GSCP_INIT_CHAR, * PS_GSCP_INIT_CHAR;


// GSCP_INIT_ITEM : 0xA548
typedef struct _S_GSCP_INIT_ITEM
{

} S_GSCP_INIT_ITEM, * PS_GSCP_INIT_ITEM;


// GSCP_INIT_SKILL : 0xA549
typedef struct _S_GSCP_INIT_SKILL
{

} S_GSCP_INIT_SKILL, * PS_GSCP_INIT_SKILL;


// GCSP_REQ_PARAMETER_CHANGE : 0x2550
typedef struct _S_GCSP_REQ_PARAMETER_CHANGE
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 변경할 캐릭터 이름
	char                                              szAccountID[18];// 변경할 계정 아이디
	BYTE                                              byType;       // 변경하고자 하는 파라미터 필드
	int                                               byValues;     // 변경하고자 하는 값

} S_GCSP_REQ_PARAMETER_CHANGE, * PS_GCSP_REQ_PARAMETER_CHANGE;


// GSCP_RESP_PARAMETER_CHANGE : 0xA550
typedef struct _S_GSCP_RESP_PARAMETER_CHANGE
{
	BYTE                                              byResult;     // 정보 변경 결과

} S_GSCP_RESP_PARAMETER_CHANGE, * PS_GSCP_RESP_PARAMETER_CHANGE;


// GCSP_REQ_ITEM_INSERT : 0x2551
typedef struct _S_GCSP_REQ_ITEM_INSERT
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 캐릭터 이름
	char                                              szAccountID[18];// 계정 아이디
	DWORD                                             dwIndex;      // 추가하려는 아이템 인덱스
	BYTE                                              byPlace;      // 추가 하려는 아이템 위치
	BYTE                                              bySlot;       // Slot Number
	BYTE                                              byX;          // X 좌표
	BYTE                                              byZ;          // Z 좌표

} S_GCSP_REQ_ITEM_INSERT, * PS_GCSP_REQ_ITEM_INSERT;


// GSCP_RESP_ITEM_INSERT : 0xA551
typedef struct _S_GSCP_RESP_ITEM_INSERT
{
	BYTE                                              byResult;     // 아이템 삽입 결과

} S_GSCP_RESP_ITEM_INSERT, * PS_GSCP_RESP_ITEM_INSERT;


// GCSP_REQ_ITEM_DELETE : 0x2552
typedef struct _S_GCSP_REQ_ITEM_DELETE
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 캐릭터 이름
	char                                              szAccountID[18];// 계정 아이디
	DWORD                                             dwIndex;      // 삭제하려는 아이템 인덱스
	BYTE                                              byPlace;      // 삭제하려는 아이템 위치
	BYTE                                              bySlot;       // Slot Number
	BYTE                                              byX;          // X 좌표
	BYTE                                              byZ;          // Z 좌표

} S_GCSP_REQ_ITEM_DELETE, * PS_GCSP_REQ_ITEM_DELETE;


// GSCP_RESP_ITEM_DELETE : 0xA552
typedef struct _S_GSCP_RESP_ITEM_DELETE
{
	BYTE                                              byResult;     // 아이템 삭제 결과

} S_GSCP_RESP_ITEM_DELETE, * PS_GSCP_RESP_ITEM_DELETE;


// GCSP_REQ_SKILL_INSERT : 0x2553
typedef struct _S_GCSP_REQ_SKILL_INSERT
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 캐릭터 이름
	char                                              szAccountID[18];// 계정 아이디
	DWORD                                             dwIndex;      // 추가하려는 스킬 인덱스
	BYTE                                              byLevel;      // 추가하려는 스킬 인덱스

} S_GCSP_REQ_SKILL_INSERT, * PS_GCSP_REQ_SKILL_INSERT;


// GSCP_RESP_SKILL_INSERT : 0xA553
typedef struct _S_GSCP_RESP_SKILL_INSERT
{
	BYTE                                              byResult;     // 스킬 삽입 결과

} S_GSCP_RESP_SKILL_INSERT, * PS_GSCP_RESP_SKILL_INSERT;


// GCSP_REQ_SKILL_DELETE : 0x2554
typedef struct _S_GCSP_REQ_SKILL_DELETE
{
	BYTE                                              byWorldNo;    // 캐릭터가 위치한 월드번호
	char                                              szCharName[26];// 캐릭터 이름
	char                                              szAccountID[18];// 계정 아이디
	DWORD                                             dwIndex;      // 삭제하려는 스킬 인덱스

} S_GCSP_REQ_SKILL_DELETE, * PS_GCSP_REQ_SKILL_DELETE;


// GSCP_RESP_SKILL_DELETE : 0xA554
typedef struct _S_GSCP_RESP_SKILL_DELETE
{
	BYTE                                              byResult;     // 스킬 삭제 결과

} S_GSCP_RESP_SKILL_DELETE, * PS_GSCP_RESP_SKILL_DELETE;



#pragma pack(pop)

#endif // __PROTOCOL_MESSAGE_STRUCT_H__
