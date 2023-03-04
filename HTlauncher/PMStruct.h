#ifndef __PROTOCOL_MESSAGE_STRUCT_H__
#define __PROTOCOL_MESSAGE_STRUCT_H__

#define CSP_REQ_LOGIN                                     0x1001      // �α��� ��û �޽���
#define CSP_REQ_WORLD_LIST                                0x1002      // ���� ���� ����Ʈ ��û
#define CSP_REQ_MOVE_ZONE_SERVER                          0x1003      // ���� ��ǥ �������� ������ ��û
#define CSP_REQ_CHAR_LIST                                 0x1011      // �ش� ������ ĳ���� ����Ʈ ��û
#define CSP_REQ_CHAR_CREATE                               0x1012      // �ɸ��� ������ ��û
#define CSP_REQ_CHAR_REMOVE                               0x1013      // �ɸ��� ������ ��û
#define CSP_REQ_ZONE_CONNECT                              0x1014      // �ɸ��� ������ ������ ���� ��û
#define CSP_REQ_EXIT_ZONE_SERVER                          0x1015      // ĳ���� ����â�� ����������, ���弭�� ����â���� �̵� ��û
#define CSP_REQ_CHAR_LOGOUT                               0x1021      // ĳ������ �α� �ƿ��� ��û
#define CSP_OTHER_CHAR_LOGOUT                             0x1022      // ĳ���� �α׾ƿ�, ����, �����̵��� �ֺ����� ��û
#define CSP_OTHER_CHAR_LOGOUT_NOTIFY                      0x1023      // ĳ������ �α׾ƿ�, ����, �����̵��� ��Ƽ, ���, �ּҷ� ���� �ɸ��Ϳ��� ���ۿ�û
#define CSP_INIT_CHAR                                     0x1101      // ĳ������ �����ʱ����� ��û �޼���
#define CSP_INIT_INVENTORY                                0x1102      // �ɸ����� �κ��丮���� ���� ��û
#define CSP_INIT_NPC_INVENTORY                            0x1103      // NPC�� �κ��丮���� ���� ��û
#define CSP_INIT_SKILL                                    0x1104      // �ɸ����� ��ų���� ���� ��û
#define CSP_INIT_GUILD                                    0x1105      // �ڽ��� ����ʱ������� ������.
#define CSP_INIT_ADDRESS_BOOK                             0x1106      // �ּҷ� ���� ������ ��û
#define CSP_REQ_CHAR_HISTORY                              0x1108      // �ɸ��� �����丮���� ��û
#define CSP_INIT_EQUIPMENT                                0x1109      // �ɸ��� ������� ��û
#define CSP_INIT_MONSTER_NPC                              0x1111      // �ֺ� Monster/NPC ���� ���� ��û
#define CSP_INIT_OTHER_CHAR                               0x1112      // �ֺ� �ٸ� �ɸ��� ���� ���� ��û
#define CSP_INIT_REAL_ADDRESS_BOOK                        0x1113      // �ּҷ� ���� ������ ��û
#define CSP_INIT_REAL_GUILD                               0x1114      // ��� ���� ������ ��û
#define CSP_INIT_REAL_GUILD_MEMBER                        0x1115      // ��� ���� ������ ��û
#define CSP_INIT_ITEM                                     0x1121      // �ֺ� ������ ������ ó�� ��û �޼���
#define CSP_REQ_INIT_REGEN_CHAR                           0x1131      // ĳ���� ���� �ʱ�ȭ ��û
#define CSP_INIT_WORLD_USER_COUNT                         0x1161      // ���庰 �����ڼ��� ó����.
#define CSP_INIT_GUILD_MEMBER                             0x1171      // �ڽ��� ���������� ������.
#define CSP_REQ_CHAR_MOVE                                 0x1201      // ĳ���� �̵� ��û �޽���
#define CSP_OTHER_CHAR_MOVE                               0x1202      // ĳ������ �̵������� �ٸ� ĳ���Ϳ��� �˷���
#define CSP_REQ_ITEM_MOVE                                 0x1203      // ������ �̵� ���
#define CSP_MAP_ITEM_APPEAR                               0x1204      // ���ο� �������� ��Ÿ������ �ֺ�ĳ���Ϳ��� ����
#define CSP_MAP_ITEM_DISAPPEAR                            0x1205      // �������� ��������� �ֺ�ĳ���Ϳ��� ����
#define CSP_MONSTER_MOVE_STEP                             0x1206      // �Ѽ� �̵��� �ֺ��� ����
#define CSP_MONSTER_MOVE_NSTEP                            0x1207      // ������ �̵��� �ֺ��� ����
#define CSP_MONSTER_MOVE_END                              0x1208      // ������ �̵��� ��� ��ǥ�� ����
#define CSP_REQ_ITEM_PACKING                              0x1221      // ������ ��ŷ ��û
#define CSP_REQ_ITEM_UNPACKING                            0x1222      // ������ ����ŷ ��û
#define CSP_REQ_ITEM_USE                                  0x1223      // ������ ��� ��û
#define CSP_ITEM_USE_BROADCAST                            0x1224      // ������ ����� �ֺ� �ٸ� ĳ���͵鿡�� ���� ��û
#define CSP_ITEM_REMOVE                                   0x1225      // �κ��丮���� ������ ������� ��û
#define CSP_REQ_MONEY_MOVE                                0x1226      // ���Ǿ��� �̵��� ��û
#define CSP_REQ_CHAR_MOVE_BROADCAST                       0x1227      // �ɸ����� �̵��� ��û�Ѵ�.
#define CSP_REQ_MOVE_PORTAL                               0x1231      // ��Ż�� ���� �̵���û�� �Ѵ�.
#define CSP_REQ_ATK_CHAR                                  0x1301      // ĳ������ ���� ��û
#define CSP_ATK_CHAR_BROADCAST                            0x1302      // ĳ������ ������ �ֺ� ĳ���͵鿡�� ���� ��û
#define CSP_REQ_ITEM_EQUIPMENT                            0x1401      // ������ ������ ��û
#define CSP_ITEM_EQUIPMENT_BROADCAST                      0x1402      // ������ ������ �ֺ� ĳ���Ϳ��� ����
#define CSP_ITEM_ABRASION                                 0x1411      // ������ ������� �˸�
#define CSP_ITEM_ABRASION_BROADCAST                       0x1412      // ������ ������� �ֺ� �ٸ� ĳ���͵鿡�� ����
#define CSP_ITEM_DURABILITY_DECREASE                      0x1413      // ������ ������ ���Ҹ� �˸�
#define CSP_REQ_NORMAL_CHAT                               0x1501      // �Ϲ� ä�� �޼����� ��û
#define CSP_NORMAL_CHAT                                   0x1502      // �Ϲ� ä�� �޼��� ���� ��û
#define CSP_REQ_WHISPER_CHAT                              0x1503      // �ӼӸ� ������ ��û
#define CSP_WHISPER_CHAT                                  0x1504      // �ӼӸ� ���� ��û
#define CSP_REQ_SHOUT_CHAT                                0x1505      // ��ħ�� ������ ��û
#define CSP_SHOUT_CHAT                                    0x1506      // ��ħ�� ���� ��û
#define CSP_REQ_PARTY_CHAT                                0x1507      // ��Ƽä�� �޼��� ��û
#define CSP_PARTY_CHAT                                    0x1508      // ��Ƽä�� �޼��� ���� ��û
#define CSP_REQ_NOTIFY_MESSAGE                            0x1511      // �������� ���� ��û
#define CSP_NOTIFY_MESSAGE                                0x1512      // �������� �޽��� ����� ���� ��û
#define CSP_REQ_BROADCAST_MESSAGE                         0x1513      // �������� ���� ��û
#define CSP_BROADCAST_MESSAGE                             0x1514      // �������� �޽��� ����� ���� ��û
#define CSP_REQ_CREATE_PARTY                              0x1601      // ��Ƽ ������û �޽���
#define CSP_REQ_DISBAND_PARTY                             0x1602      // ��Ƽ ��ü�� ��û
#define CSP_DISBAND_PARTY_BROADCAST                       0x1603      // ��Ƽ ��ü�� ��Ƽ���鿡�� ����
#define CSP_REQ_JOIN_PARTY                                0x1604      // ��Ƽ ������ ��û
#define CSP_JOIN_PARTY_NOTIFY                             0x1605      // ��Ƽ ������û �޼���
#define CSP_JOIN_PARTY_RESULT                             0x1606      // ��Ƽ ���� ��û ����� ������ ����
#define CSP_JOIN_PARTY_RESULT_NOTIFY                      0x1607      // ��Ƽ ���� ��û�� ���� ���� ����� ��Ƽ�忡�� ���ۿ�û �޼���
#define CSP_NEW_PARTY_MEMBER                              0x1608      // �ű� ��Ƽ���� ������ ��Ƽ���鿡�� ���ۿ�û �޼���
#define CSP_REQ_SECEDE_PARTY                              0x1609      // ��Ƽ Ż��(��Ƽ�� �Ǵ� ��Ƽ���� ���� �����)�� ��û �޼���
#define CSP_SECEDE_PARTY_BROADCAST                        0x160A      // ��Ƽ Ż�� ��Ƽ���鿡�� ���ۿ�û �޼���
#define CSP_REQ_PARTY_LIST                                0x160B      // ��Ƽ���� ����Ʈ�� ��û
#define CSP_REQ_CREATE_GUILD                              0x1611      // ��� ������û �޽���
#define CSP_REQ_DISBAND_GUILD                             0x1612      // ��� ��ü�� ��û
#define CSP_CREATE_GUILD_BROADCAST                        0x1613      // ��� ������ �ֺ��� �˸���.
#define CSP_DISBAND_GUILD_BROADCAST                       0x1614      // ��� ��ü�� �ֺ��� �˸���.
#define CSP_REQ_JOIN_GUILD                                0x1615      // ��� ������ ��û
#define CSP_JOIN_GUILD_NOTIFY                             0x1616      // ��� ������û �޼���
#define CSP_JOIN_GUILD_RESULT                             0x1617      // ��� ���� ��û ����� ������ ����
#define CSP_JOIN_GUILD_RESULT_NOTIFY                      0x1618      // ��� ���� ��û�� ���� ���� ����� ����忡�� ���ۿ�û �޼���
#define CSP_NEW_GUILD_MEMBER                              0x1619      // �ű� ������ ������ �����鿡�� ���ۿ�û �޼���
#define CSP_REQ_SECEDE_GUILD                              0x161A      // ��� Ż��(����� �Ǵ� ������ ���� �����)�� ��û �޼���
#define CSP_SECEDE_GUILD_BROADCAST                        0x161B      // ��� Ż�� �����鿡�� ���ۿ�û �޼���
#define CSP_REQ_EXPEL_GUILD_MEMBER                        0x161D      // ������ ������ ��û
#define CSP_EXPEL_GUILD_MEMBER_BROADCAST                  0x161E      // ������ ������ �˸���.
#define CSP_REQ_QUEST_HISTORY                             0x1701      // ����Ʈ �����丮 ���� ��û
#define CSP_QUEST_DIALOG                                  0x1702      // ��ȭ�� ��� ����
#define CSP_QUEST_NOTIFY_LEVEL                            0x1703      // ����Ʈ �ܰ� �˸�
#define CSP_MONSTER_DISAPPEAR                             0x1801      // Monster ������� �˸�
#define CSP_CHAR_STATUS                                   0x1802      // ĳ������ ���¸� �˸�
#define CSP_CHAR_MONSTER_STATUS_BROADCAST                 0x1803      // ĳ����Monster�� ���¸� �ֺ� �ٸ� ĳ���͵� ���� ������
#define CSP_CHAR_DEATH                                    0x1805      // ĳ������ ������ �˸�
#define CSP_CHAR_MONSTER_DEATH_BROADCAST                  0x1806      // ĳ����/Monster�� ������ �ֺ� �ٸ� ĳ���͵鿡�� ����
#define CSP_CHAR_HP_RECOVERY                              0x1811      // ĳ������ ü�� ȸ���� �˸�
#define CSP_MONSTER_HP_RECOVERY                           0x1812      // Monster�� ü�� ȸ���� �˸�
#define CSP_CHAR_CAST_PROMOTE                             0x1821      // ĳ������ ī��Ʈ ����� �˸�
#define CSP_CHAR_CAST_PROMOTE_BROADCAST                   0x1822      // ĳ������ ī��Ʈ ����� �ֺ� �ٸ� ĳ���͵鿡�� ������
#define CSP_CHAR_PING                                     0x1831      // �ɸ����� �������������� �˸���.
#define CSP_REQ_CHAR_LOCATION                             0x1832      // �ɸ����� �������� ��ġ�� ��û�Ѵ�.
#define CSP_CHAR_PARAMS_CHANGE                            0x1911      // ĳ���� �Ķ���� ��ȭ�� ��û��
#define CSP_REQ_CHAKRA_RISING                             0x1921      // ��ũ�� ����� ��û��
#define CSP_REQ_BRAHMAN_RISING                            0x1922      // ��� ����Ʈ ����� ��û��
#define CSP_REQ_INCREASE_INVENTORY_SLOT                   0x1931      // �κ��丮 ���� ������ ��û
#define CSP_REQ_DECREASE_INVENTORY_SLOT                   0x1932      // Ȯ��� �κ��丮 ���� ������ ��û
#define CSP_REQ_NPC_POINT_UP                              0x1941      // NPC ģ���� ����� ��û��
#define CSP_REQ_CHANGE_CKAKRA_TO_PRANA                    0x1951      // ��ũ�� ���󳪷� �����û�Ѵ�
#define CSP_OTHER_CHAR_PARAM_BROADCAST                    0x1952      // Ÿ�ɸ����� �Ķ���ͺ����� �˸���
#define CSP_REQ_SAVE_POSITION                             0x1961      // �ɸ��� ������ġ�� ������ ��û�Ѵ�.
#define CSP_REQ_PVP_RANKING                               0x1971      // PVP��ŷ����Ʈ�� ��û�Ѵ�.
#define CSP_REQ_SKILL_REGIST                              0x2001      // ��ų ����� ��û�Ѵ�
#define CSP_SKILL_REGIST                                  0x2002      // ī��Ʈ ��¿� ���� ��ų �ڵ� ����� �˷��ش�
#define CSP_REQ_SKILL_SELECT                              0x2003      // ��ϵ� ��ų�� ����/����
#define CSP_REQ_SKILL_SELECT_BROADCAST                    0x2004      // ��ϵ� ��ų�� ����/����
#define CSP_REQ_SKILL_USE2_CHAR                           0x2011      // ĳ������ ��ų ���� �غ����� ��û
#define CSP_SKILL_READY_CHAR_BROADCAST                    0x2012      // ĳ������ ��ų ���� �غ����� �ֺ��� ����
#define CSP_REQ_SKILL_ATK_CHAR                            0x2013      // ĳ������ ��ų ������ ��û
#define CSP_SKILL_ATK_CHAR_BROADCAST                      0x2014      // ĳ������ ��ų ������ �ֺ� ĳ���͵鿡�� ����
#define CSP_REQ_SKILL_LEVEL_UP                            0x2021      // ĳ������ ��ų Level-Up�� ��û
#define CSP_REQ_SHOP_SKILL_LIST                           0x2022      // ���� ������ ��ų List�� ��û
#define CSP_REQ_SHOP_ITEM_LIST                            0x2101      // ���� ������ ������ List�� ��û
#define CSP_REQ_ITEM_MAKING                               0x2102      // ������ ������ ��û
#define CSP_REQ_ITEM_REDEEM                               0x2103      // ������ ������ ã�⸦ ��û
#define CSP_REQ_ITEM_REPAIR                               0x2104      // ������ ������ ��û
#define CSP_REQ_ITEM_DISMANTLE                            0x2105      // ������ ��ü�� ��û
#define CSP_REQ_ITEM_REFINING                             0x2106      // ������ ������ ��û
#define CSP_REQ_PRANA_CONTRIBUTION                        0x2112      // ���� �峳�� ��û
#define CSP_REQ_RESOURCE_BARTER                           0x2113      // ��ȯ�ҿ��� �ڿ� ��ȯ�� ��û
#define CSP_REQ_RESOURCE_BARTER_PRICE                     0x2114      // ��ȯ�ҿ����� �ڿ���ȯ������ ��û�Ѵ�.
#define CSP_REQ_EXCHANGE                                  0x2201      // ������ ��ȯ�� ��û
#define CSP_EXCHANGE_NOTIFY                               0x2202      // ������ ��ȯ ��û
#define CSP_EXCHANGE_RESULT                               0x2203      // ������ ��ȯ ��û�� ���� ����� ������ ������
#define CSP_EXCHANGE_RESULT_NOTIFY                        0x2204      // ������ ��ȯ ��û�� ���� ����� �˸���û
#define CSP_REQ_EXCHANGE_ADD                              0x2205      // ������ ��ȯâ�� ������ �߰� ��û
#define CSP_EXCHANGE_ADD_NOTIFY                           0x2206      // ������ �߰� ��û
#define CSP_REQ_EXCHANGE_ERASE                            0x2207      // ������ ��ȯâ�� ������ ���� ��û
#define CSP_EXCHANGE_ERASE_NOTIFY                         0x2208      // ������ ���� ��û�� �˸���û
#define CSP_EXCHANGE_ACCEPT                               0x2209      // ��ȯ ���� ����
#define CSP_EXCHANGE_ACCEPT_NOTIFY                        0x220A      // ��ȯ ���� ���� �˸���û
#define CSP_EXCHANGE_CANCEL                               0x220B      // ��ȯ ��ҿ�û
#define CSP_REQ_EXCHANGE_MONEY                            0x220C      // ��ȯ�� �� �߰���û
#define CSP_EXCHANGE_MONEY_NOTIFY                         0x220D      // ���� �߰��� �˸���û
#define CSP_REQ_TRADE_ENTRY                               0x2301      // �ŷ� ��� ��û �޼���
#define CSP_REQ_TRADE_CANCEL                              0x2302      // �ŷ� ��� ��� ��û �޼���
#define CSP_REQ_TRADE                                     0x2303      // �ŷ� ��û �޼���
#define CSP_REQ_TRADE_LIST                                0x2304      // �ŷ� ����Ʈ ��û �޼���
#define CSP_REQ_MY_ENTYR_LIST                             0x2305      // �ڽ��� ���,���� ������ ��û
#define CSP_REQ_TRADE_ITEM_SEEK                           0x2306      // ���� ������ ã�� ��û
#define CSP_REQ_TRANSPARENCY_MODE                         0x2501      // �����带 ��û��
#define CSP_TRANSPARENCY_MODE_NOTIFY                      0x2502      // �����带 �ֺ��� ���ۿ�û��
#define CSP_REQ_MOVE_POSITION                             0x2511      // �����̵��� ��û��
#define CSP_REQ_MOVE_NEAR_CHAR                            0x2512      // Ÿ�ɸ���ó�� �����̵��� ��û��
#define CSP_REQ_CHAR_RECALL                               0x2513      // Ÿ�ɸ����� ��ȯ�� ��û��
#define CSP_CHAR_RECALL_NOTIFY                            0x2514      // GM�� ���� ��ȯ���� �˸���û
#define CSP_REQ_CONTROL_CHAT                              0x2521      // ä�û���� ����, ���� ��û��
#define CSP_CONTROL_CHAT_NOTIFY                           0x2522      // ä�û�� ����, ������ �˸���û
#define CSP_REQ_CONTROL_ACTION                            0x2531      // �ɸ����� ���۸���, ������ ��û��
#define CSP_CONTROL_ACTION_NOTIFY                         0x2532      // GM�� ���� �ɸ����� ���۸���, ������ �˸���û.
#define CSP_REQ_TROUBLE_REPORT                            0x2541      // ������ �Ű����� �����Ѵ�.
#define CSP_REQ_TROUBLE_REPORT_LIST                       0x2542      // ������ �Ű����� ����Ʈ�� ��û�Ѵ�.
#define CSP_REQ_TROUBLE_REPORT_SET                        0x2543      // �Ű����� ó����Ȳ�� �޴´�.
#define GCSP_REQ_TROUBLE_REPORT_LIST                      0x2544      // �α��� ��û �޽���
#define GCSP_REQ_TROUBLE_REPORT_SET                       0x2545      // �α��� ��û �޽���
#define GCSP_REQ_TROUBLE_REPORT                           0x2546      // �α��� ��û �޽���
#define GCSP_REQ_CHARACTER_SEARCH                         0x2547      // ĳ������ ���� ��û
#define GCSP_REQ_PARAMETER_CHANGE                         0x2550      // ĳ������ �⺻ �������� ���� ��û
#define GCSP_REQ_ITEM_INSERT                              0x2551      // ������ ���� ��û
#define GCSP_REQ_ITEM_DELETE                              0x2552      // ������ ���� ��û
#define GCSP_REQ_SKILL_INSERT                             0x2553      // ��ų ���� ��û
#define GCSP_REQ_SKILL_DELETE                             0x2554      // ��ų ���� ��û
#define CSP_REQ_CHAR_INFO                                 0x2561      // �ɸ��� ���� ��û �޽���
#define CSP_REQ_CHAR_EQUIPMENT                            0x2562      // �ɸ����� �������� ��û �޽���
#define CSP_REQ_CHAR_SKILL                                0x2563      // �ɸ����� ��ų���� ��û �޽���
#define CSP_REQ_CLOSE_CHAR                                0x2571      // �ɸ����� �������� ��û �޽���
#define CSP_REQ_JOIN_ADDRESS_BOOK                         0x2603      // �ּҷϿ� ĳ���� �߰��� ��û
#define CSP_JOIN_ADDRESS_BOOK_NOTIFY                      0x2604      // �ּҷ� �߰� ��û�� ĳ���Ϳ��� ���ۿ�û �޼���
#define CSP_REQ_JOIN_ADDRESS_BOOK_RESULT                  0x2605      // �ּҷ� �߰� ��û ����� ������ ����
#define CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0x2606      // �ּҷ� �߰� ��û�� ���� ���� ����� ĳ���Ϳ��� ���ۿ�û�޼���
#define CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE                0x2607      // �ּҷϿ� �ִ� ĳ���� ������ ������ ��û
#define CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0x2608      // �ּҷϿ��� ������ �˸���
#define CSP_REQ_ADDRESS_BOOK_GROUP_ADD                    0x2611      // �ּҷϿ� �׷��� �߰��� ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_DELETE                 0x2612      // �ּҷϿ� �׷��� ������ ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_MOVE                   0x2613      // �ּҷϿ� �ɸ����� �׷��̵��� ��û
#define CSP_REQ_ADDRESS_BOOK_GROUP_RENAME                 0x2614      // �ּҷϿ� �׷��� �̸������� ��û
#define CSP_REQ_ADDRESS_BOOK_STATUS                       0x2621      // �ּҷ� ��Ͽ�û�� �źθ� ���ÿ�û
#define CSP_REQ_INIT_MOBILE                               0x3000      // MOBILE �ʱ�ȭ
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
#define CSP_CHAR_ACT_BROADCAST                            0x3310      // Action�� broadcast
#define CSP_REQ_UPDATE_UI                                 0x3500      // Update UI
#define CSP_REQ_UPDATE_STATUS                             0x3501      // Update Status
#define CSP_LEVEL_UP_BROADCAST                            0x3510      // level up
#define CSP_REQ_INCREASE_CHAKRA                           0x3520      // Increase a chakra point
#define SCP_RESP_LOGIN                                    0x9001      // �α��� ���� �޽���
#define SCP_RESP_WORLD_LIST                               0x9002      // ���� ���� ����Ʈ ����
#define SCP_RESP_MOVE_ZONE_SERVER                         0x9003      // ���� ��ǥ �������� ���� ����
#define SCP_RESP_CHAR_LIST                                0x9011      // ĳ���� ����Ʈ ����
#define SCP_RESP_CHAR_CREATE                              0x9012      // �ɸ��� ���� ���� �޽���
#define SCP_RESP_CHAR_REMOVE                              0x9013      // �ɸ��� ���� ���� �޼���
#define SCP_RESP_ZONE_CONNECT                             0x9014      // �ɸ��� ������ ������ ���� ���� �޽���
#define SCP_RESP_EXIT_ZONE_SERVER                         0x9015      // ĳ���� ����â�� ����������, ���弭�� ����â���� �̵� ���� �޼���
#define SCP_RESP_CHAR_LOGOUT                              0x9021      // ĳ������ �α� �ƿ� ���� �޽���
#define SCP_OTHER_CHAR_LOGOUT                             0x9022      // ĳ���� �α׾ƿ�, ����, �����̵��� �ֺ����� ���� �޼���
#define SCP_OTHER_CHAR_LOGOUT_NOTIFY                      0x9023      // ĳ������ �α׾ƿ�, ����, �����̵��� ��Ƽ, ���, �ּҷ� ���� �ɸ��Ϳ��� ���� ���� �޼���
#define SCP_INIT_CHAR                                     0x9101      // ĳ������ �����ʱ����� ���� �޼���
#define SCP_INIT_INVENTORY                                0x9102      // �ɸ����� �κ��丮���� ���� ���� �޼���
#define SCP_INIT_NPC_INVENTORY                            0x9103      // NPC�� �κ��丮���� ���� ���� �޼���
#define SCP_INIT_SKILL                                    0x9104      // �ɸ����� ��ų���� ���� ���� �޼���
#define SCP_INIT_GUILD                                    0x9105      // ����� �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_ADDRESS_BOOK                             0x9106      // �ּҷ� ���� ���� ���� �޼���
#define SCP_RESP_CHAR_HISTORY                             0x9108      // �ɸ��� �����丮���� ���� �޼���
#define SCP_INIT_EQUIPMENT                                0x9109      // �ɸ��� ������� ��û�� ���� ���� �޼���
#define SCP_INIT_MONSTER_NPC                              0x9111      // �ֺ� Monster/NPC ���� ���� ���� �޼���
#define SCP_INIT_OTHER_CHAR                               0x9112      // �ֺ� �ٸ� �ɸ��� ���� ���� �޼���
#define SCP_INIT_REAL_ADDRESS_BOOK                        0x9113      // �ּҷ� ���� ���� ���� �޼���
#define SCP_INIT_REAL_GUILD                               0x9114      // ����� �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_REAL_GUILD_MEMBER                        0x9115      // ������ �ǽð� ���� ���� ���� �޼���
#define SCP_INIT_ITEM                                     0x9121      // �ֺ� ������ ������ ó�� ���� �޼���
#define SCP_RESP_INIT_REGEN_CHAR                          0x9131      // �κ��丮�� ������ ��ġ ���� ���� �޼���
#define SCP_INIT_WORLD_USER_COUNT                         0x9161      // ���庰 �����ڼ��� ó����.
#define SCP_INIT_GUILD_MEMBER                             0x9171      // �ڽ��� ���������� ������.
#define SCP_RESP_CHAR_MOVE                                0x9201      // ĳ���� �̵��� ���� ��� �޽���
#define SCP_OTHER_CHAR_MOVE                               0x9202      // �̵������� �ٸ� ĳ���Ϳ��� �˷���
#define SCP_RESP_ITEM_MOVE                                0x9203      // ������ �̵� ���
#define SCP_MAP_ITEM_APPEAR                               0x9204      // ���ο� �������� ������ ��ġ ������ �ֺ�ĳ���Ϳ��� ����
#define SCP_MAP_ITEM_DISAPPEAR                            0x9205      // �������� ����� ��ġ�� �ֺ�ĳ���Ϳ��� ����
#define SCP_MONSTER_MOVE_STEP                             0x9206      // �Ѽ� �̵��� �ֺ��� ����
#define SCP_MONSTER_MOVE_NSTEP                            0x9207      // ������ �̵��� �ֺ��� ����
#define SCP_MONSTER_MOVE_END                              0x9208      // ������ �̵��� ��� ��ǥ�� ����
#define SCP_RESP_ITEM_PACKING                             0x9221      // ������ ��ŷ ���� �޼���
#define SCP_RESP_ITEM_UNPACKING                           0x9222      // ������ ����ŷ ���� �޼���
#define SCP_RESP_ITEM_USE                                 0x9223      // ������ ��� ���� �޼���
#define SCP_ITEM_USE_BROADCAST                            0x9224      // ������ ����� �ֺ� �ٸ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_ITEM_REMOVE                                   0x9225      // �κ��丮���� ������ ������� �˷���
#define SCP_RESP_MONEY_MOVE                               0x9226      // ���Ǿ��� �̵���û�� ���� ����޼���
#define SCP_RESP_CHAR_MOVE_BROADCAST                      0x9227      // �ɸ����� �̵��� ��û�� ���� ����޼���
#define SCP_RESP_MOVE_PORTAL                              0x9231      // ��Ż�� ���� �̵���û ��� ���� ���� �޼���
#define SCP_RESP_ATK_CHAR                                 0x9301      // ĳ������ ���� ���� �޼���
#define SCP_ATK_CHAR_BROADCAST                            0x9302      // ĳ������ ������ �ֺ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_RESP_ITEM_EQUIPMENT                           0x9401      // ������ ���� ��û�� ���� ���
#define SCP_ITEM_EQUIPMENT_BROADCAST                      0x9402      // ������ ������ �ֺ� ĳ���Ϳ��� ����
#define SCP_ITEM_ABRASION                                 0x9411      // ������ ������� �˸� ���� �޼���
#define SCP_ITEM_ABRASION_BROADCAST                       0x9412      // ������ ������� �ֺ� �ٸ� ĳ���͵鿡�� ���� ���� �޼���
#define SCP_ITEM_DURABILITY_DECREASE                      0x9413      // ������ ������ ���� ���� �޼���
#define SCP_RESP_NORMAL_CHAT                              0x9501      // �Ϲ� ä�ÿ�û�� ���� ��� ���� �޼���
#define SCP_NORMAL_CHAT                                   0x9502      // �Ϲ� ä�� �޼��� ���ۿ� ���� ��� ���� �޼���
#define SCP_RESP_WHISPER_CHAT                             0x9503      // �ӼӸ� ä�� ��û�� ���� ��� ���� �޼���
#define SCP_WHISPER_CHAT                                  0x9504      // �ӼӸ� ���ۿ� ���� ��� ���� �޼���
#define SCP_RESP_SHOUT_CHAT                               0x9505      // ��ħ�� ä�� ��� ���� �޼���
#define SCP_SHOUT_CHAT                                    0x9506      // ��ħ�� ä�� ��� ��û �޼���
#define SCP_RESP_PARTY_CHAT                               0x9507      // ��Ƽ ä�� ��� ���� �޼���
#define SCP_PARTY_CHAT                                    0x9508      // ��Ƽ ä�� ��� ���� �޼���
#define SCP_RESP_NOTIFY_MESSAGE                           0x9511      // �������� ���� ��� ���� �޼���
#define SCP_NOTIFY_MESSAGE                                0x9512      // �������� ä�� ��� ���� �޼���
#define SCP_RESP_BROADCAST_MESSAGE                        0x9513      // �������� ���� ��� ���� �޼���
#define SCP_BROADCAST_MESSAGE                             0x9514      // �������� ä�� ��� ���� �޼���
#define SCP_RESP_CREATE_PARTY                             0x9601      // ��Ƽ ������û ����޼���
#define SCP_RESP_DISBAND_PARTY                            0x9602      // ��Ƽ ��ü��û ����޼���
#define SCP_DISBAND_PARTY_BROADCAST                       0x9603      // ��Ƽ ��ü�� ��Ƽ���鿡�� ����
#define SCP_RESP_JOIN_PARTY                               0x9604      // ��Ƽ ������û ����޼���
#define SCP_JOIN_PARTY_NOTIFY                             0x9605      // ��Ƽ ������û ����޼���
#define SCP_JOIN_PARTY_RESULT                             0x9606      // ��Ƽ ���� ��û ����� ���� ���� ����޼���
#define SCP_JOIN_PARTY_RESULT_NOTIFY                      0x9607      // ��Ƽ ���� ��û�� ���� ���ΰ�� ��Ƽ�忡�� ����
#define SCP_NEW_PARTY_MEMBER                              0x9608      // �ű� ��Ƽ���� ������ ��Ƽ���鿡�� ����
#define SCP_RESP_SECEDE_PARTY                             0x9609      // ��Ƽ Ż���û�� ���� ���� �޼���
#define SCP_SECEDE_PARTY_BROADCAST                        0x960A      // ��Ƽ Ż�� ��Ƽ���鿡�� ����
#define SCP_RESP_PARTY_LIST                               0x960B      // ��Ƽ�� ����Ʈ�� ���� ����޼���
#define SCP_RESP_CREATE_GUILD                             0x9611      // ��� ������û ����޼���
#define SCP_RESP_DISBAND_GUILD                            0x9612      // ��� ��ü��û ����޼���
#define SCP_CREATE_GUILD_BROADCAST                        0x9613      // ��� ������ �ֺ��� �˸���.
#define SCP_DISBAND_GUILD_BROADCAST                       0x9614      // ��� ��ü�� �ֺ��� �˸���.
#define SCP_RESP_JOIN_GUILD                               0x9615      // ��� ������û ����޼���
#define SCP_JOIN_GUILD_NOTIFY                             0x9616      // ��� ������û ����޼���
#define SCP_JOIN_GUILD_RESULT                             0x9617      // ��� ���� ��û ����� ���� ���� ����޼���
#define SCP_JOIN_GUILD_RESULT_NOTIFY                      0x9618      // ��� ���� ��û�� ���� ���ΰ�� ����忡�� ����
#define SCP_NEW_GUILD_MEMBER                              0x9619      // �ű� ������ ������ �����鿡�� ����
#define SCP_RESP_SECEDE_GUILD                             0x961A      // ��� Ż���û�� ���� ���� �޼���
#define SCP_SECEDE_GUILD_BROADCAST                        0x961B      // ��� Ż�� �����鿡�� ����
#define SCP_RESP_EXPEL_GUILD_MEMBER                       0x961D      // ��� Ż���û�� ���� ��� �޼���
#define SCP_EXPEL_GUILD_MEMBER_BROADCAST                  0x961E      // ������ ������ �˸���.
#define SCP_RESP_QUEST_HISTORY                            0x9701      // ����Ʈ �����丮 ���� ����
#define SCP_QUEST_DIALOG                                  0x9702      // ��ȭ�� ���
#define SCP_QUEST_NOTIFY_LEVEL                            0x9703      // ����Ʈ �ܰ� �˸�
#define SCP_MONSTER_DISAPPEAR                             0x9801      // Monster ������� �˸�
#define SCP_CHAR_STATUS                                   0x9802      // ĳ������ ���¸� �˸�
#define SCP_CHAR_MONSTER_STATUS_BROADCAST                 0x9803      // ĳ����Monster�� ���¸� �ֺ� �ٸ� ĳ���͵� ���� ������
#define SCP_CHAR_DEATH                                    0x9805      // ĳ������ ������ �˸�
#define SCP_CHAR_MONSTER_DEATH_BROADCAST                  0x9806      // ĳ����/Monster�� ������ �ֺ� �ٸ� ĳ���͵鿡�� ����
#define SCP_CHAR_HP_RECOVERY                              0x9811      // ĳ������ ü�� ȸ���� �˸�
#define SCP_MONSTER_HP_RECOVERY                           0x9812      // Monster�� ü�� ȸ���� �˸�
#define SCP_CHAR_CAST_PROMOTE                             0x9821      // ĳ������ ī��Ʈ ����� �˸�
#define SCP_CHAR_CAST_PROMOTE_BROADCAST                   0x9822      // ĳ������ ī��Ʈ ����� �ֺ� �ٸ� ĳ���͵鿡�� ������
#define SCP_CHAR_PING                                     0x9831      // �ɸ����� �������������� �˸���.
#define SCP_RESP_CHAR_LOCATION                            0x9832      // �ɸ����� �������� ��ġ�� �˸���.
#define SCP_CHAR_PARAMS_CHANGE                            0x9911      // ĳ���� �Ķ���� ��ȭ�� ������
#define SCP_RESP_CHAKRA_RISING                            0x9921      // ��ũ�� ��� ��û ����� ������
#define SCP_RESP_BRAHMAN_RISING                           0x9922      // ��� ����Ʈ ��� ��û ����� ������
#define SCP_RESP_INCREASE_INVENTORY_SLOT                  0x9931      // �κ��丮 ���� ���� ��û ����� ������
#define SCP_RESP_DECREASE_INVENTORY_SLOT                  0x9932      // Ȯ��� �κ��丮 ���� ������ ��û
#define SCP_RESP_NPC_POINT_UP                             0x9941      // NPC ģ���� ��� ��û ����� ������
#define SCP_RESP_CHANGE_CKAKRA_TO_PRANA                   0x9951      // ��ũ�� ���󳪷� �����û ���
#define SCP_OTHER_CHAR_PARAM_BROADCAST                    0x9952      // Ÿ�ɸ����� �Ķ���ͺ����� �˸���
#define SCP_RESP_SAVE_POSITION                            0x9961      // ������ġ �����û����� �����Ѵ�.
#define SCP_RESP_PVP_RANKING                              0x9971      // PVP��ŷ����Ʈ�� �����Ѵ�.
#define SCP_RESP_SKILL_REGIST                             0xA001      // ��ų ��� ��� ���� �޼���
#define SCP_SKILL_REGIST                                  0xA002      // ī��Ʈ ��¿� ���� ��ų �ڵ� ��� ��� ���� �޼���
#define SCP_RESP_SKILL_SELECT                             0xA003      // ��ϵ� ��ų�� ����/���� ��� ���� �޼���
#define SCP_RESP_SKILL_SELECT_BROADCAST                   0xA004      // ��ϵ� ��ų�� ����/���� ��� ���� �޼���
#define SCP_RESP_SKILL_USE2_CHAR                          0xA011      // ĳ������ ��ų ���� �غ��� ��û ��� �޼���
#define SCP_SKILL_READY_CHAR_BROADCAST                    0xA012      // ĳ������ ��ų ���� �غ����� �ֺ��� ���۰�� �޼���
#define SCP_RESP_SKILL_ATK_CHAR                           0xA013      // ĳ������ ��ų ���� ���� �޼���
#define SCP_SKILL_ATK_CHAR_BROADCAST                      0xA014      // ĳ������ ��ų ������ �ֺ� ĳ���͵鿡�� ���� ��� �޼���
#define SCP_RESP_SKILL_LEVEL_UP                           0xA021      // ĳ������ ��ų Level-Up ��û ��� �޼���
#define SCP_RESP_SHOP_SKILL_LIST                          0xA022      // ���� ������ ��ų List ��û�� ���� ����޼���
#define SCP_RESP_SHOP_ITEM_LIST                           0xA101      // ���� ������ ������ List ��û�� ���� ����޼���
#define SCP_RESP_ITEM_MAKING                              0xA102      // ������ ������ ��û�� ���� ����޼���
#define SCP_RESP_ITEM_REDEEM                              0xA103      // ������ ������ ã���û�� ���� ����޼���
#define SCP_RESP_ITEM_REPAIR                              0xA104      // ������ ������û�� ���� ����޼���
#define SCP_RESP_ITEM_DISMANTLE                           0xA105      // ������ ��ü ��û�� ���� ����޼���
#define SCP_RESP_ITEM_REFINING                            0xA106      // ������ ���� ��û�� ���� ����޼���
#define SCP_RESP_PRANA_CONTRIBUTION                       0xA112      // ���� �峳�� ��û�� ���� ����޼���
#define SCP_RESP_RESOURCE_BARTER                          0xA113      // ��ȯ�ҿ��� �ڿ� ��ȯ��û�� ���� ����޼���
#define SCP_RESP_RESOURCE_BARTER_PRICE                    0xA114      // ��ȯ�ҿ����� �ڿ���ȯ������ ��û�Ѵ�.
#define SCP_RESP_EXCHANGE                                 0xA201      // ������ ��ȯ��û�� ���� ����޼���
#define SCP_EXCHANGE_NOTIFY                               0xA202      // ������ ��ȯ ��û�� �˸��޼���
#define SCP_EXCHANGE_RESULT                               0xA203      // ������ ��ȯ ��û�� ���� ����� ���� ������ ����޼���
#define SCP_EXCHANGE_RESULT_NOTIFY                        0xA204      // ������ ��ȯ ��û�� ���� ����� �˸��޼���
#define SCP_RESP_EXCHANGE_ADD                             0xA205      // ������ ��ȯâ�� ������ �߰� ��û�� ���� ����޼���
#define SCP_EXCHANGE_ADD_NOTIFY                           0xA206      // ������ �߰� ��û�� �˸��޼���
#define SCP_RESP_EXCHANGE_ERASE                           0xA207      // ������ ��ȯâ�� ������ ���� ��û�� ���� ���� �޼���
#define SCP_EXCHANGE_ERASE_NOTIFY                         0xA208      // ������ ���� ��û�� �˸��޼���
#define SCP_EXCHANGE_ACCEPT                               0xA209      // ��ȯ ���� ���ο� ���� ����޼���
#define SCP_EXCHANGE_ACCEPT_NOTIFY                        0xA20A      // ��ȯ ���� ���� �˸��޼���
#define SCP_EXCHANGE_CANCEL                               0xA20B      // ��ȯ ��ҿ�û�� ���� ����޼���
#define SCP_RESP_EXCHANGE_MONEY                           0xA20C      // ������ ��ȯâ�� �� �߰� ��û�� ���� ���� �޼���
#define SCP_EXCHANGE_MONEY_NOTIFY                         0xA20D      // ���� �߰��� �˸�
#define SCP_RESP_TRADE_ENTRY                              0xA301      // �ŷ� ��� ��û ��� �޼���
#define SCP_RESP_TRADE_CANCEL                             0xA302      // �ŷ� ��� ��� ��û ��� �޼���
#define SCP_RESP_TRADE                                    0xA303      // �ŷ� ��û ��� �޼���
#define SCP_RESP_TRADE_LIST                               0xA304      // �ŷ� ����Ʈ ��û ��� �޼���
#define SCP_RESP_MY_ENTYR_LIST                            0xA305      // �ڽ��� ���,���� ������ ��� �޼���
#define SCP_RESP_TRADE_ITEM_SEEK                          0xA306      // ���� ������ ã�� ��� �޼���
#define SCP_RESP_TRADE_SUCCESS                            0xA307      // �ŷ������ ����ڿ��� �˷��ִ� �޼���
#define SCP_RESP_TRANSPARENCY_MODE                        0xA501      // ������ ��û�� ���� ����޼���
#define SCP_TRANSPARENCY_MODE_NOTIFY                      0xA502      // �����带 �ֺ��� ������
#define SCP_RESP_MOVE_POSITION                            0xA511      // �����̵��� ���� ����޼���
#define SCP_RESP_MOVE_NEAR_CHAR                           0xA512      // Ÿ�ɸ���ó���� �����̵� ����޼���
#define SCP_RESP_CHAR_RECALL                              0xA513      // Ÿ�ɸ����� ��ȯ�� ���� ����޼���
#define SCP_CHAR_RECALL_NOTIFY                            0xA514      // GM�� ���� ��ȯ���� �˸�
#define SCP_RESP_CONTROL_CHAT                             0xA521      // ä�û���� ����, ���� ��û�� ���� ����޼���
#define SCP_CONTROL_CHAT_NOTIFY                           0xA522      // ä�û�� ����, ���� �˸�
#define SCP_RESP_CONTROL_ACTION                           0xA531      // �ɸ����� ���۸���, ������ ��û�� ���� ����޼���
#define SCP_CONTROL_ACTION_NOTIFY                         0xA532      // GM�� ���� �ɸ����� ���۸���, ������ �˸�.
#define SCP_RESP_TROUBLE_REPORT                           0xA541      // ������ �Ű����� �����Ѵ�.
#define SCP_RESP_TROUBLE_REPORT_LIST                      0xA542      // ������ �Ű����� ����Ʈ�� ��û�Ѵ�.
#define SCP_RESP_TROUBLE_REPORT_SET                       0xA543      // �Ű����� ó����Ȳ�� �޴´�.
#define GSCP_RESP_TROUBLE_REPORT_LIST                     0xA544      // �α��� ���� �޽���
#define GSCP_RESP_TROUBLE_REPORT_SET                      0xA545      // �α��� ���� �޽���
#define GSCP_RESP_TROUBLE_REPORT                          0xA546      // �α��� ���� �޽���
#define GSCP_INIT_CHAR                                    0xA547      // ĳ���� �⺻����
#define GSCP_INIT_ITEM                                    0xA548      // ĳ���� ������ ����
#define GSCP_INIT_SKILL                                   0xA549      // ĳ���� ��ų ����
#define GSCP_RESP_PARAMETER_CHANGE                        0xA550      // ĳ������ �⺻ �������� ���� ��û�� ���� ���
#define GSCP_RESP_ITEM_INSERT                             0xA551      // ������ ���� ���
#define GSCP_RESP_ITEM_DELETE                             0xA552      // ������ ���� ���
#define GSCP_RESP_SKILL_INSERT                            0xA553      // ��ų ���� ���
#define GSCP_RESP_SKILL_DELETE                            0xA554      // ��ų ���� ���
#define SCP_RESP_CHAR_INFO                                0xA561      // �ɸ��� ���� ���� �޽���
#define SCP_RESP_CHAR_EQUIPMENT                           0xA562      // �ɸ����� �������� ���� �޽���
#define SCP_RESP_CHAR_SKILL                               0xA563      // �ɸ����� ��ų���� ���� �޽���
#define SCP_RESP_CLOSE_CHAR                               0xA571      // �ɸ����� �������� ���� �޽���
#define SCP_RESP_JOIN_ADDRESS_BOOK                        0xA603      // �ּҷϿ� ĳ�����߰� ��û�� ���� ����޼���
#define SCP_JOIN_ADDRESS_BOOK_NOTIFY                      0xA604      // �ּҷ� �߰� ��û�� ĳ���Ϳ��� ���۸޼���
#define SCP_RESP_JOIN_ADDRESS_BOOK_RESULT                 0xA605      // �ּҷ� �߰� ��û ����� ��� �޼���
#define SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY               0xA606      // �ּҷ� �߰� ��û�� ���� ���� ����� ĳ���Ϳ��� ����
#define SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE               0xA607      // �ּҷϿ� �ִ� ĳ���� ������ ������û�� ���� ����޼���
#define SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY             0xA608      // �ּҷϿ��� ������ �˸���
#define SCP_RESP_ADDRESS_BOOK_GROUP_ADD                   0xA611      // �ּҷϿ� �׷��� �߰� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_DELETE                0xA612      // �ּҷϿ� �׷��� ���� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_MOVE                  0xA613      // �ּҷϿ� �ɸ����� �׷��̵� ��û�� ���� ����޼���
#define SCP_RESP_ADDRESS_BOOK_GROUP_RENAME                0xA614      // �ּҷϿ� �׷��� �̸������� ��û���
#define SCP_RESP_ADDRESS_BOOK_STATUS                      0xA621      // �ּҷ� ��Ͽ�û�� �źθ� ���ÿ�û
#define SCP_RESP_INIT_MOBILE                              0xB000      // MOBILE �ʱ�ȭ
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
#define SCP_CHAR_ACT_BROADCAST                            0xB310      // Action�� broadcast
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
	short                                             snDur;        // Item ������
	BYTE                                              nPack;        // Item ��ø����
	WORD                                              wrgMaterial[10];// �߰��Ǵ� �������

} S_TNITEM_DATA, * PS_TNITEM_DATA;


typedef struct _S_TNSKILL_DATA
{
	int                                               iID;          // Skill ID
	BYTE                                              byLevel;      // Skill Level

} S_TNSKILL_DATA, * PS_TNSKILL_DATA;


typedef struct _S_TNCHAKRA
{
	short                                             snMuscle;     // ���� ��ũ��
	short                                             snNerves;     // �Ű� ��ũ��
	short                                             snHeart;      // ���� ��ũ��
	short                                             snMind;       // ���� ��ũ��

} S_TNCHAKRA, * PS_TNCHAKRA;


typedef struct _S_TNRESIST
{
	short                                             snFire;       // fire ����
	short                                             snCold;       // cold ����
	short                                             snLightning;  // lightning ����
	short                                             snPoison;     // poison ����

} S_TNRESIST, * PS_TNRESIST;


typedef struct _S_TNDAMAGE
{
	short                                             snMin;        // �ּ�
	short                                             snMax;        // �ִ�

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
	DWORD                                             dwIndex;      // ��ų�ε���
	BYTE                                              byLevel;      // ���� ��ų����

} S_GUILD_SKILL, * PS_GUILD_SKILL;


typedef struct _S_GUILD_MEMBER_INFO
{
	char                                              szName[26];   // ���� ĳ������ �̸�
	BYTE                                              byTrimuritiClass;// ĳ������ �ֽŰ��
	BYTE                                              bySpecialName;// ĳ������ Ư��Īȣ
	BYTE                                              byGuildAuthority;// ��峻�� ����
	BYTE                                              byTribe;      // ĳ������ ����
	BYTE                                              byCastClass;  // ĳ������ ī��Ʈ ���
	BYTE                                              byCastGrade;  // ĳ������ ī��Ʈ ���
	BYTE                                              byConnect;    // ĳ������ ���ӿ���
	int                                               nContribution;// ĳ������ ��峻 ���嵵

} S_GUILD_MEMBER_INFO, * PS_GUILD_MEMBER_INFO;


typedef struct _S_PARTY_MEMBER_INFO
{
	char                                              szName[26];   // ��Ƽ�� ĳ������ �̸�
	BYTE                                              byMember;     // ��Ƽ���� ����
	BYTE                                              byTrimuriti;  // ĳ������ �ֽ�
	BYTE                                              byTribe;      // ĳ������ ����
	BYTE                                              byCastClass;  // ĳ������ ī��Ʈ ���
	BYTE                                              byCastGrade;  // ĳ������ ī��Ʈ ���
	int                                               nMaxHP;       // ĳ���� �ִ� HP
	int                                               nCurHP;       // ĳ���� ���� HP
	BYTE                                              byRegion;     // ĳ������ ���� Region
	BYTE                                              byZone;       // ĳ������ ���� Zone

} S_PARTY_MEMBER_INFO, * PS_PARTY_MEMBER_INFO;


typedef struct _S_QUEST_HISTORY_INFO
{
	BYTE                                              byIndex;      // �÷��� �ε���
	BYTE                                              byValue;      // �÷��� ��

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
	DWORD                                             dwKeyID;      // ��ȯ�� �������� KeyID
	int                                               nItemIndex;   // ��ȯ�� �������� Index ��ȣ
	short                                             snItemCount;  // ��ȯ�� �������� ��ø ����
	BYTE                                              byX;          // �κ��丮�� X ��ǥ
	BYTE                                              byZ;          // �κ��丮�� Z ��ǥ

} S_ITEM_INVEN, * PS_ITEM_INVEN;


typedef struct _S_USER_REPORT_LIST
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // ó����Ȳ
	char                                              szReport[512];

} S_USER_REPORT_LIST, * PS_USER_REPORT_LIST;


typedef struct _S_REPORT_LIST
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	char                                              szCharName[26];
	BYTE                                              byWorld;      
	DWORD                                             dwTime;       
	BYTE                                              byProceed;    // ó����Ȳ
	char                                              szReport[512];
	char                                              szNote[256];  // ���

} S_REPORT_LIST, * PS_REPORT_LIST;


typedef struct _S_EQUIPITEM
{
	BYTE                                              byPlace;      // �������� ��ġ
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // ��ø����
	BYTE                                              byX;          // ������ X��ǥ
	BYTE                                              byZ;          // ������ Z��ǥ
	S_SUBITEM                                         AddSubItem[10];

} S_EQUIPITEM, * PS_EQUIPITEM;


typedef struct _S_SKILLINFO
{
	BYTE                                              byType;       // Skill�� ����
	DWORD                                             dwIndex;      // Skill Index
	BYTE                                              byLevel;      // Skill Level

} S_SKILLINFO, * PS_SKILLINFO;


typedef struct _S_ADDRESS_MEMBER_INFO
{
	char                                              szGroup[26];  // ĳ������ �Ҽӱ׷��̸�
	char                                              szName[26];   // �ּҷ� ĳ������ �̸�
	BYTE                                              byTrimuriti;  // ĳ������ �ֽ�
	BYTE                                              byTribe;      // ĳ������ ����
	BYTE                                              byCastClass;  // ĳ������ ī��Ʈ ���
	BYTE                                              byCastGrade;  // ĳ������ ī��Ʈ ���
	WORD                                              wServerID;    // �ɸ��Ͱ� ��ġ�� ����ID

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
	S_TNITEM_DATA                                     krgItem[24];  // bag�� ���ԵǴ� ��� ����

} S_SCP_RESP_INIT_BAG, * PS_SCP_RESP_INIT_BAG;


// CSP_REQ_UPDATE_EQUIPMENT : 0x3110
typedef struct _S_CSP_REQ_UPDATE_EQUIPMENT
{

} S_CSP_REQ_UPDATE_EQUIPMENT, * PS_CSP_REQ_UPDATE_EQUIPMENT;


// SCP_RESP_UPDATE_EQUIPMENT : 0xB110
typedef struct _S_SCP_RESP_UPDATE_EQUIPMENT
{
	DWORD                                             dwKeyID;      // PC handle
	short                                             snX;          // PC�� ���� x ��ǥ
	short                                             snZ;          // PC�� ���� y ��ǥ
	S_TNITEM_DATA                                     krgItem[14];  // equipment�� ���ԵǴ� ��� ����

} S_SCP_RESP_UPDATE_EQUIPMENT, * PS_SCP_RESP_UPDATE_EQUIPMENT;


// CSP_REQ_INIT_SKILLBOOK : 0x3200
typedef struct _S_CSP_REQ_INIT_SKILLBOOK
{

} S_CSP_REQ_INIT_SKILLBOOK, * PS_CSP_REQ_INIT_SKILLBOOK;


// SCP_RESP_INIT_SKILLBOOK : 0xB200
typedef struct _S_SCP_RESP_INIT_SKILLBOOK
{
	S_TNSKILL_DATA                                    krgSkill[20]; // skill book�� ���ԵǴ� skill ����

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
	S_TNSKILL_DATA                                    kSkill;       // level up�� skill ����

} S_SCP_RESP_LEARN_SKILL, * PS_SCP_RESP_LEARN_SKILL;


// CSP_REQ_CAST_SKILL : 0x3220
typedef struct _S_CSP_REQ_CAST_SKILL
{
	int                                               iID;          // Skill ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snMapX;       // Target map x ��ǥ
	short                                             snMapZ;       // Target map y ��ǥ

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
	S_TNSKILL_DATA                                    kSkill;       // cast�� skill ����
	int                                               iCastTime;    // Cast Time(Casting delay)
	BYTE                                              byCasterType; // Caster type
	DWORD                                             dwCasterKeyID;// Caster handle
	short                                             snCasterX;    // Caster�� ���� x ��ǥ
	short                                             snCasterZ;    // Caster�� ���� y ��ǥ
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target�� ���� x ��ǥ
	short                                             snTargetZ;    // Target�� ���� y ��ǥ
	short                                             snMapX;       // Target map x ��ǥ
	short                                             snMapZ;       // Target map y ��ǥ

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
	short                                             snCasterX;    // Caster�� ���� x ��ǥ
	short                                             snCasterZ;    // Caster�� ���� y ��ǥ
	BYTE                                              byStrikerType;// Striker type
	DWORD                                             dwStrikerKeyID;// Striker handle
	short                                             snStrikerX;   // Striker�� ���� x ��ǥ
	short                                             snStrikerZ;   // Striker�� ���� y ��ǥ

} S_SCP_FIZZLE_SKILL_BROADCAST, * PS_SCP_FIZZLE_SKILL_BROADCAST;


// CSP_REQ_AFFECT_SKILL : 0x3250
typedef struct _S_CSP_REQ_AFFECT_SKILL
{
	int                                               iID;          // Skill ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snMapX;       // Target map x ��ǥ
	short                                             snMapZ;       // Target map y ��ǥ

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
	BYTE                                              byRes;        // Result(���������� ������ �������� ����, � ������ ���� ���ݵ� �������� ����)
	S_TNSKILL_DATA                                    kSkill;       // cast�� skill ����
	int                                               iCoolDownTime;// Cool-down �ð�
	BYTE                                              byCombatRes;  // Combat Result(Normal, CriticalHit, Dodge, ...)
	int                                               iDamage;      // Damage
	BYTE                                              byCasterType; // Caster type
	DWORD                                             dwCasterKeyID;// Caster handle
	short                                             snCasterX;    // Caster�� ���� x ��ǥ
	short                                             snCasterZ;    // Caster�� ���� y ��ǥ
	int                                               iCasterHP;    // Caster�� �� HP
	int                                               iCasterTP;    // Caster�� �� TP
	BYTE                                              byTargetType; // Target type
	short                                             snMapX;       // Target map x ��ǥ
	short                                             snMapZ;       // Target map y ��ǥ
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target�� ���� x ��ǥ
	short                                             snTargetZ;    // Target�� ���� y ��ǥ
	int                                               iTargetHP;    // Target�� �� HP
	int                                               iTargetTP;    // Target�� �� TP

} S_SCP_AFFECT_SKILL_BROADCAST, * PS_SCP_AFFECT_SKILL_BROADCAST;


// CSP_DEBUFFER_SKILL_BROADCAST : 0x3270
typedef struct _S_CSP_DEBUFFER_SKILL_BROADCAST
{

} S_CSP_DEBUFFER_SKILL_BROADCAST, * PS_CSP_DEBUFFER_SKILL_BROADCAST;


// SCP_DEBUFFER_SKILL_BROADCAST : 0xB270
typedef struct _S_SCP_DEBUFFER_SKILL_BROADCAST
{
	int                                               iEffectID;    // debuffer�� effect ID
	BYTE                                              byTargetType; // Target type
	DWORD                                             dwTargetKeyID;// Target handle
	short                                             snTargetX;    // Target�� ���� x ��ǥ
	short                                             snTargetZ;    // Target�� ���� y ��ǥ
	int                                               iTargetHP;    // Target�� �� HP
	int                                               iTargetTP;    // Target�� �� TP
	int                                               iMoveSpeed;   // Target�� �� MoveSpeed
	int                                               iAttackSpeed; // Target�� �� AttackSpeed

} S_SCP_DEBUFFER_SKILL_BROADCAST, * PS_SCP_DEBUFFER_SKILL_BROADCAST;


// CSP_REQ_CHAR_ACT : 0x3300
typedef struct _S_CSP_REQ_CHAR_ACT
{
	BYTE                                              byAct;        // ���Ϸ��� �ൿ

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
	BYTE                                              byAct;        // ���Ϸ��� �ൿ

} S_SCP_CHAR_ACT_BROADCAST, * PS_SCP_CHAR_ACT_BROADCAST;


// CSP_REQ_UPDATE_UI : 0x3500
typedef struct _S_CSP_REQ_UPDATE_UI
{

} S_CSP_REQ_UPDATE_UI, * PS_CSP_REQ_UPDATE_UI;


// SCP_RESP_UPDATE_UI : 0xB500
typedef struct _S_SCP_RESP_UPDATE_UI
{
	short                                             snX;          // ���� x ��ǥ
	short                                             snZ;          // ���� y ��ǥ
	int                                               iMoveSpeed;   // �� MoveSpeed
	int                                               iAttackSpeed; // �� AttackSpeed
	BYTE                                              byLevel;      // �� Level
	int                                               iBramanPoint; // �� Braman point
	BYTE                                              byCaste;      // Caste ���
	int                                               iTitle;       // Title
	int                                               iMaxPrana;    // �ִ� Prana
	int                                               iPrana;       // �� Prana
	S_TNCHAKRA                                        krgChakra[2]; // 0:base chakra, 1:changed chakra
	short                                             snCPRemaining;// ���� Chakra Point
	short                                             snSPRemaining;// ���� Skill Point
	int                                               iHP;          // �� HP
	int                                               iMaxHP;       // �ִ� HP
	int                                               iHPRecovery;  // HPȸ����/��
	int                                               iTP;          // �� TP
	int                                               iMaxTP;       // �ִ� TP
	int                                               iTPRecovery;  // TPȸ����/��
	short                                             snAC;         // AC
	short                                             snAttackRate; // Attack Rate
	short                                             snDodgeRate;  // Dodge Rate
	S_TNRESIST                                        kResist;      // ����
	S_TNDAMAGE                                        krgDamage[2]; // 0:Physical, 1:Magical

} S_SCP_RESP_UPDATE_UI, * PS_SCP_RESP_UPDATE_UI;


// CSP_REQ_UPDATE_STATUS : 0x3501
typedef struct _S_CSP_REQ_UPDATE_STATUS
{

} S_CSP_REQ_UPDATE_STATUS, * PS_CSP_REQ_UPDATE_STATUS;


// SCP_RESP_UPDATE_STATUS : 0xB501
typedef struct _S_SCP_RESP_UPDATE_STATUS
{
	short                                             snX;          // ���� x ��ǥ
	short                                             snZ;          // ���� y ��ǥ
	int                                               iPrana;       // �� Prana
	int                                               iHP;          // �� HP
	int                                               iHPRecovery;  // HPȸ����/��
	int                                               iTP;          // �� TP
	int                                               iTPRecovery;  // TPȸ����/��

} S_SCP_RESP_UPDATE_STATUS, * PS_SCP_RESP_UPDATE_STATUS;


// CSP_LEVEL_UP_BROADCAST : 0x3510
typedef struct _S_CSP_LEVEL_UP_BROADCAST
{

} S_CSP_LEVEL_UP_BROADCAST, * PS_CSP_LEVEL_UP_BROADCAST;


// SCP_LEVEL_UP_BROADCAST : 0xB510
typedef struct _S_SCP_LEVEL_UP_BROADCAST
{
	DWORD                                             dwKeyID;      // PC handle
	BYTE                                              byLevel;      // �� Level

} S_SCP_LEVEL_UP_BROADCAST, * PS_SCP_LEVEL_UP_BROADCAST;


// CSP_REQ_INCREASE_CHAKRA : 0x3520
typedef struct _S_CSP_REQ_INCREASE_CHAKRA
{
	BYTE                                              byChakra;     // �ø����� chakra(0:muscle, 1:nerves, 2:heart, 3:mind)

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
	BYTE                                              byTrimuriti;  // ���� �Ұ����� �ֽ�
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
	BYTE                                              byConnType;   // ������ġ

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
	BYTE                                              byResult;     // �������� ��Ÿ��

} S_SCP_OTHER_CHAR_LOGOUT, * PS_SCP_OTHER_CHAR_LOGOUT;


// CSP_OTHER_CHAR_LOGOUT_NOTIFY : 0x1023
typedef struct _S_CSP_OTHER_CHAR_LOGOUT_NOTIFY
{

} S_CSP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_CSP_OTHER_CHAR_LOGOUT_NOTIFY;


// SCP_OTHER_CHAR_LOGOUT_NOTIFY : 0x9023
typedef struct _S_SCP_OTHER_CHAR_LOGOUT_NOTIFY
{
	char                                              szCharName[26];
	BYTE                                              byResult;     // �������� ��Ÿ��
	BYTE                                              byRegion;     
	BYTE                                              byZone;       

} S_SCP_OTHER_CHAR_LOGOUT_NOTIFY, * PS_SCP_OTHER_CHAR_LOGOUT_NOTIFY;


// CSP_INIT_CHAR : 0x1101
typedef struct _S_CSP_INIT_CHAR
{
	BYTE                                              byConnType;   // ��������
	BYTE                                              byConnPos;    // ������ġ
	WORD                                              wPortalID;    // ������ŻID
	char                                              szCharName[26];

} S_CSP_INIT_CHAR, * PS_CSP_INIT_CHAR;


// SCP_INIT_CHAR : 0x9101
typedef struct _S_SCP_INIT_CHAR
{
	BYTE                                              byResult;     // �ʱ�ȭ ���
	char                                              szCharName[26];
	DWORD                                             dwKeyID;      
	BYTE                                              byRegion;     // �ɸ����� Region ��ġ
	BYTE                                              byZone;       // �ɸ����� Zone ��ġ
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
	BYTE                                              byMaster;     // ����� ����
	DWORD                                             dwGuildMark;  
	int                                               nBrahmanPoint;
	int                                               nNextCastBrahmanPoint;
	int                                               nSumChakraPoint;
	short                                             snChakraMuscle;
	short                                             snChakraNerve;
	short                                             snChakraHeart;
	short                                             snChakraSoul; 
	short                                             snPureChakraMuscle;// ���� ������ ��ũ��
	short                                             snPureChakraNerve;// ���� �Ű��� ��ũ��
	short                                             snPureChakraHeart;// ���� ������ ��ũ��
	short                                             snPureChakraSoul;// ���� ������ ��ũ��
	short                                             snChakraMusclePrana;
	short                                             snChakraNervePrana;
	short                                             snChakraHeartPrana;
	short                                             snChakraSoulPrana;
	int                                               nPrana;       // �� ������ ��
	short                                             snUsePranaMuscle;
	short                                             snUsePranaNerve;
	short                                             snUsePranaHeart;
	short                                             snUsePranaSoul;
	int                                               nMaxHP;       // �ɸ��� HP�� �ִ밪
	int                                               nCurHP;       // �ɸ��� HP�� ���簪
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
	short                                             snFireResist; // �� ���׷�
	short                                             snColdResist; // ���� ���׷�
	short                                             snPoisonResist;// �� ���׷�
	short                                             snAcidResist; // �� ���׷�
	short                                             snReserved;   // ����
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
	int                                               nStatus;      // �ɸ����� ����
	BYTE                                              byGMStatus;   // GM�� ���� ĳ������ ���û���
	BYTE                                              byUserStatus; // ������ ���� ĳ������ ���û���
	int                                               nPCMoney;     // ĳ���� ���� ���Ǿ�
	int                                               nNPCMoney;    // â�� ���� ���Ǿ�
	int                                               nCloth;       // ĳ������ ���� ���� ī��Ʈ
	DWORD                                             dwBagIndex;   // Ȯ�� �κ��丮 Bag Index

} S_SCP_INIT_CHAR, * PS_SCP_INIT_CHAR;


// CSP_INIT_INVENTORY : 0x1102
typedef struct _S_CSP_INIT_INVENTORY
{

} S_CSP_INIT_INVENTORY, * PS_CSP_INIT_INVENTORY;


// SCP_INIT_INVENTORY : 0x9102
typedef struct _S_SCP_INIT_INVENTORY
{
	BYTE                                              byPlace;      // �������� ��ġ
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // ��ø����
	BYTE                                              byX;          // ������ X��ǥ
	BYTE                                              byZ;          // ������ Z��ǥ
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_INVENTORY, * PS_SCP_INIT_INVENTORY;


// CSP_INIT_NPC_INVENTORY : 0x1103
typedef struct _S_CSP_INIT_NPC_INVENTORY
{

} S_CSP_INIT_NPC_INVENTORY, * PS_CSP_INIT_NPC_INVENTORY;


// SCP_INIT_NPC_INVENTORY : 0x9103
typedef struct _S_SCP_INIT_NPC_INVENTORY
{
	BYTE                                              byPlace;      // �������� ��ġ
	DWORD                                             dwKeyID;      
	DWORD                                             dwIndex;      
	short                                             snCurDurability;
	short                                             snCount;      // ��ø����
	BYTE                                              byX;          // ������ X��ǥ
	BYTE                                              byZ;          // ������ Z��ǥ
	BYTE                                              bySubMaterialCount;

} S_SCP_INIT_NPC_INVENTORY, * PS_SCP_INIT_NPC_INVENTORY;


// CSP_INIT_SKILL : 0x1104
typedef struct _S_CSP_INIT_SKILL
{

} S_CSP_INIT_SKILL, * PS_CSP_INIT_SKILL;


// SCP_INIT_SKILL : 0x9104
typedef struct _S_SCP_INIT_SKILL
{
	BYTE                                              byType;       // Skill�� ����
	DWORD                                             dwIndex;      // Skill Index
	BYTE                                              byLevel;      // Skill Level
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�

} S_SCP_INIT_SKILL, * PS_SCP_INIT_SKILL;


// CSP_INIT_GUILD : 0x1105
typedef struct _S_CSP_INIT_GUILD
{
	char                                              szGuildName[26];// ��� �̸�

} S_CSP_INIT_GUILD, * PS_CSP_INIT_GUILD;


// SCP_INIT_GUILD : 0x9105
typedef struct _S_SCP_INIT_GUILD
{
	char                                              szGuildName[26];// ��� �̸�
	char                                              szGuildBoard[256];// ��� �Խ���
	char                                              szCastleName[26];// ��强 �̸�
	DWORD                                             dwGuildMark;  // ��帶ũ
	short                                             snCastleLevel;// ��� ���׷��̵巹��
	BYTE                                              byTrimuriti;  // �ֽ�
	int                                               nPrana;       // ��庸�� ����
	int                                               nLupia;       // ��庸�� ���Ǿ�
	int                                               nGuildPoint;  // �������Ʈ
	DWORD                                             dwCost;       // ����������
	S_GUILD_SKILL                                     S_Skill[8];   // ��彺ų����

} S_SCP_INIT_GUILD, * PS_SCP_INIT_GUILD;


// CSP_INIT_GUILD_MEMBER : 0x1171
typedef struct _S_CSP_INIT_GUILD_MEMBER
{
	char                                              szGuildName[26];// ��� �̸�

} S_CSP_INIT_GUILD_MEMBER, * PS_CSP_INIT_GUILD_MEMBER;


// SCP_INIT_GUILD_MEMBER : 0x9171
typedef struct _S_SCP_INIT_GUILD_MEMBER
{
	S_GUILD_MEMBER_INFO                               S_Member;     // ���� ����

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
	WORD                                              wServerID;    // �ɸ����� ���� ��ġ

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
	WORD                                              wServerID;    // �ɸ����� ���� ��ġ

} S_SCP_INIT_REAL_ADDRESS_BOOK, * PS_SCP_INIT_REAL_ADDRESS_BOOK;


// CSP_REQ_CHAR_HISTORY : 0x1108
typedef struct _S_CSP_REQ_CHAR_HISTORY
{

} S_CSP_REQ_CHAR_HISTORY, * PS_CSP_REQ_CHAR_HISTORY;


// SCP_RESP_CHAR_HISTORY : 0x9108
typedef struct _S_SCP_RESP_CHAR_HISTORY
{
	DWORD                                             dwStartTime;  // �����丮 �߻� �ð�
	WORD                                              wType;        // �����丮 ����
	char                                              szContent[26];// �����丮 ����

} S_SCP_RESP_CHAR_HISTORY, * PS_SCP_RESP_CHAR_HISTORY;


// CSP_INIT_EQUIPMENT : 0x1109
typedef struct _S_CSP_INIT_EQUIPMENT
{

} S_CSP_INIT_EQUIPMENT, * PS_CSP_INIT_EQUIPMENT;


// SCP_INIT_EQUIPMENT : 0x9109
typedef struct _S_SCP_INIT_EQUIPMENT
{
	BYTE                                              byPlace;      // �������� ���� ��ġ
	DWORD                                             dwKeyID;      // �������� KeyID
	DWORD                                             dwIndex;      // �������� Index
	short                                             snCurDurability;
	short                                             snCount;      // �������� ����(��ø����)
	BYTE                                              byX;          // ������ ���� X ��ǥ(0���� ����)
	BYTE                                              byZ;          // ������ ���� Z ��ǥ(0���� ����)
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�
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
	BYTE                                              bySize;       // ������ ũ��

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
	BYTE                                              byDir;        // �ɸ����� �̵����� �� �̵����� ����. ����, �ɱ���������
	short                                             snTargetX;    // �ɸ����� �̵����� X��ǥ
	short                                             snTargetZ;    // �ɸ����� �̵����� Z��ǥ
	DWORD                                             dwActionSkill;
	BYTE                                              byActionLevel;
	DWORD                                             dwActiveSkill;
	BYTE                                              byActiveLevel;
	BYTE                                              byCount;      // ������ �������� ����

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
	BYTE                                              byRegion;     // �ɸ����� Region ��ġ
	BYTE                                              byZone;       // �ɸ����� Zone ��ġ
	short                                             snX;          
	short                                             snZ;          
	BYTE                                              byY;          
	short                                             snHeight;     
	short                                             snDegree;     
	DWORD                                             dwGameTime;   
	BYTE                                              byWhether;    
	int                                               nPrana;       // �� ������ ��
	int                                               nMaxHP;       // �ɸ��� HP�� �ִ밪
	int                                               nCurHP;       // �ɸ��� HP�� ���簪
	int                                               nMonsterCount;
	int                                               nPKCount;     
	int                                               nCvsCWin;     
	int                                               nCvsCLose;    
	int                                               nPvsPWin;     
	int                                               nPvsPLose;    
	int                                               nGvsGWin;     
	int                                               nGvsGLose;    
	int                                               nStatus;      // �ɸ����� ����

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
	BYTE                                              byDir;        // �̵����� �� �̵����� ����
	short                                             snDegree;     
	DWORD                                             dwTickCount;  
	WORD                                              wSeqNum;      // �̵���Ŷ Sequence Number

} S_CSP_REQ_CHAR_MOVE, * PS_CSP_REQ_CHAR_MOVE;


// SCP_RESP_CHAR_MOVE : 0x9201
typedef struct _S_SCP_RESP_CHAR_MOVE
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // �ɸ����� X��ǥ
	short                                             snZ;          // �ɸ����� Z��ǥ
	BYTE                                              byY;          // �ɸ����� �� ����
	short                                             snHeight;     // �ɸ����� �� ����

} S_SCP_RESP_CHAR_MOVE, * PS_SCP_RESP_CHAR_MOVE;


// CSP_OTHER_CHAR_MOVE : 0x1202
typedef struct _S_CSP_OTHER_CHAR_MOVE
{

} S_CSP_OTHER_CHAR_MOVE, * PS_CSP_OTHER_CHAR_MOVE;


// SCP_OTHER_CHAR_MOVE : 0x9202
typedef struct _S_SCP_OTHER_CHAR_MOVE
{
	DWORD                                             dwKeyID;      // character KeyID
	BYTE                                              byDir;        // ĳ���� �̵�����, ���� ����
	short                                             snDegree;     // �ɸ����� �̵� ���� ����
	short                                             snMovingSpeed;// 100�ʴ� �̵����� Cell ��
	short                                             snX;          // �ɸ����� X��ǥ
	short                                             snZ;          // �ɸ����� Z��ǥ
	BYTE                                              byY;          // �ɸ����� �� ����
	short                                             snHeight;     // �ɸ����� �� ����

} S_SCP_OTHER_CHAR_MOVE, * PS_SCP_OTHER_CHAR_MOVE;


// CSP_REQ_ITEM_MOVE : 0x1203
typedef struct _S_CSP_REQ_ITEM_MOVE
{
	DWORD                                             dwKeyID;      // ������ KeyID
	BYTE                                              byToPlace;    // �������� �̵���ų ���
	short                                             snX;          // �������� �̵� ��ų X��ǥ
	short                                             snZ;          // �������� �̵� ��ų Z��ǥ

} S_CSP_REQ_ITEM_MOVE, * PS_CSP_REQ_ITEM_MOVE;


// SCP_RESP_ITEM_MOVE : 0x9203
typedef struct _S_SCP_RESP_ITEM_MOVE
{
	BYTE                                              byResult;     // �������� �̵��� ���� ���
	DWORD                                             dwKeyID;      // ������ KeyID
	BYTE                                              byToPlace;    // �������� �̵���ų ���
	short                                             snX;          // �������� �̵� ��ų X��ǥ
	short                                             snZ;          // �������� �̵� ��ų Z��ǥ

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
	short                                             snCount;      // Item X��ǥ
	short                                             snX;          // Item X��ǥ
	short                                             snZ;          // Item Z��ǥ
	BYTE                                              byY;          // �������� �� ����
	short                                             snHeight;     // �������� �� ����

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
	short                                             snX;          // ���� x��ǥ
	short                                             snZ;          // ���� z��ǥ

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
	DWORD                                             dwKeyID;      // ����ŷ�� �������� KeyID
	short                                             snCount;      // ������ ����ŷ Count
	BYTE                                              byPlace;      // ����ŷ�� �������� ���� ��ġ
	short                                             snX;          // ����ŷ�� �������� X ��ǥ. Index 0 ���� ����
	short                                             snZ;          // ����ŷ�� �������� Z ��ǥ. Index 0 ���� ����

} S_CSP_REQ_ITEM_UNPACKING, * PS_CSP_REQ_ITEM_UNPACKING;


// SCP_RESP_ITEM_UNPACKING : 0x9222
typedef struct _S_SCP_RESP_ITEM_UNPACKING
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwSourceKeyID;// ����ŷ�� Source �������� KeyID
	short                                             snSourceCount;// ����ŷ�� Source �������� Count
	DWORD                                             dwDestKeyID;  // ����ŷ�� Destinatin �������� KeyID
	short                                             snDestCount;  // ����ŷ�� Destinatin �������� Count

} S_SCP_RESP_ITEM_UNPACKING, * PS_SCP_RESP_ITEM_UNPACKING;


// CSP_REQ_ITEM_USE : 0x1223
typedef struct _S_CSP_REQ_ITEM_USE
{
	BYTE                                              byBagID;      // bag ID(0~2)
	short                                             snX;          // �κ��丮������ �������� X ��ǥ. Index 0 ���� ����
	short                                             snZ;          // �κ��丮������ �������� Z ��ǥ. Index 0 ���� ����

} S_CSP_REQ_ITEM_USE, * PS_CSP_REQ_ITEM_USE;


// SCP_RESP_ITEM_USE : 0x9223
typedef struct _S_SCP_RESP_ITEM_USE
{
	BYTE                                              byResult;     // Result(0: ����, 12:����)
	DWORD                                             dwKeyID;      // ����� �������� KeyID
	BYTE                                              byPackCount;  // ���� ������ ��ø ����

} S_SCP_RESP_ITEM_USE, * PS_SCP_RESP_ITEM_USE;


// CSP_ITEM_USE_BROADCAST : 0x1224
typedef struct _S_CSP_ITEM_USE_BROADCAST
{

} S_CSP_ITEM_USE_BROADCAST, * PS_CSP_ITEM_USE_BROADCAST;


// SCP_ITEM_USE_BROADCAST : 0x9224
typedef struct _S_SCP_ITEM_USE_BROADCAST
{
	DWORD                                             dwKeyID;      // �������� ����ϴ� ĳ������ KeyID
	DWORD                                             dwIndex;      // ����� �������� Index

} S_SCP_ITEM_USE_BROADCAST, * PS_SCP_ITEM_USE_BROADCAST;


// CSP_ITEM_REMOVE : 0x1225
typedef struct _S_CSP_ITEM_REMOVE
{

} S_CSP_ITEM_REMOVE, * PS_CSP_ITEM_REMOVE;


// SCP_ITEM_REMOVE : 0x9225
typedef struct _S_SCP_ITEM_REMOVE
{
	DWORD                                             dwKeyID;      // ����� �������� KeyID
	BYTE                                              byPlace;      // ����� �������� ��ġ
	short                                             snX;          // ����� �������� X ��ǥ
	short                                             snZ;          // ����� �������� Z ��ǥ

} S_SCP_ITEM_REMOVE, * PS_SCP_ITEM_REMOVE;


// CSP_REQ_MONEY_MOVE : 0x1226
typedef struct _S_CSP_REQ_MONEY_MOVE
{
	DWORD                                             dwMoney;      // �̵��� ���Ǿ��� ��
	BYTE                                              byPlace;      // �̵��� ���Ǿ��� ��ġ

} S_CSP_REQ_MONEY_MOVE, * PS_CSP_REQ_MONEY_MOVE;


// SCP_RESP_MONEY_MOVE : 0x9226
typedef struct _S_SCP_RESP_MONEY_MOVE
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byPlace;      // �̵��� ���Ǿ��� ��ġ
	DWORD                                             dwFromMoney;  // ���� ����� ���Ǿƾ�
	DWORD                                             dwToMoney;    // �ű� ����� ���Ǿƾ�

} S_SCP_RESP_MONEY_MOVE, * PS_SCP_RESP_MONEY_MOVE;


// CSP_REQ_CHAR_MOVE_BROADCAST : 0x1227
typedef struct _S_CSP_REQ_CHAR_MOVE_BROADCAST
{
	BYTE                                              byDir;        // �̵�����
	short                                             snToX;        // �̵����� ������ X��ǥ
	short                                             snToZ;        // �̵����� ������ Z��ǥ

} S_CSP_REQ_CHAR_MOVE_BROADCAST, * PS_CSP_REQ_CHAR_MOVE_BROADCAST;


// SCP_RESP_CHAR_MOVE_BROADCAST : 0x9227
typedef struct _S_SCP_RESP_CHAR_MOVE_BROADCAST
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	BYTE                                              byDir;        // �̵�����
	short                                             snFromX;      // �̵����� ������ X��ǥ
	short                                             snFromZ;      // �̵����� ������ Z��ǥ
	short                                             snToX;        // �̵����� ������ X��ǥ
	short                                             snToZ;        // �̵����� ������ Z��ǥ

} S_SCP_RESP_CHAR_MOVE_BROADCAST, * PS_SCP_RESP_CHAR_MOVE_BROADCAST;


// CSP_REQ_MOVE_PORTAL : 0x1231
typedef struct _S_CSP_REQ_MOVE_PORTAL
{
	WORD                                              wPortalID;    // �̵��ϰ��� �ϴ� ��Ż�� ID

} S_CSP_REQ_MOVE_PORTAL, * PS_CSP_REQ_MOVE_PORTAL;


// SCP_RESP_MOVE_PORTAL : 0x9231
typedef struct _S_SCP_RESP_MOVE_PORTAL
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // �̵����� X ��ǥ.
	short                                             snZ;          // �̵����� Z ��ǥ.
	BYTE                                              byY;          // �̵����� Y ��ǥ(��).
	WORD                                              wServerID;    // Server ID
	char                                              szZoneIP[16]; 
	WORD                                              wZonePort;    

} S_SCP_RESP_MOVE_PORTAL, * PS_SCP_RESP_MOVE_PORTAL;


// CSP_REQ_ATK_CHAR : 0x1301
typedef struct _S_CSP_REQ_ATK_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ���� ��� ĳ������ KeyID
	DWORD                                             dwItemKeyID;  // ���ݿ� ����� ������ KeyID
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_ATK_CHAR, * PS_CSP_REQ_ATK_CHAR;


// SCP_RESP_ATK_CHAR : 0x9301
typedef struct _S_SCP_RESP_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCount;      // ��ô������ ���, �ܿ�����
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ����/Monster�� ���� HP

} S_SCP_RESP_ATK_CHAR, * PS_SCP_RESP_ATK_CHAR;


// CSP_ATK_CHAR_BROADCAST : 0x1302
typedef struct _S_CSP_ATK_CHAR_BROADCAST
{

} S_CSP_ATK_CHAR_BROADCAST, * PS_CSP_ATK_CHAR_BROADCAST;


// SCP_ATK_CHAR_BROADCAST : 0x9302
typedef struct _S_SCP_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwKeyID;      // ������ �ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;// ������ ���ϴ� ĳ������ KeyID
	BYTE                                              byEquipPart;  // ���ݽÿ� ����ϴ� �������� ������ ����
	BYTE                                              byResult;     // Result Field
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ������ ���� HP
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCurX;       // �������� ���� X��ǥ
	short                                             snCurz;       // �������� ���� z��ǥ

} S_SCP_ATK_CHAR_BROADCAST, * PS_SCP_ATK_CHAR_BROADCAST;


// CSP_REQ_ITEM_EQUIPMENT : 0x1401
typedef struct _S_CSP_REQ_ITEM_EQUIPMENT
{
	DWORD                                             dwKeyID;      // â���� ������ KeyID
	BYTE                                              byEquipPart;  // ������ ��������
	BYTE                                              byX;          // ���� X ��ǥ
	BYTE                                              byZ;          // ���� Z ��ǥ

} S_CSP_REQ_ITEM_EQUIPMENT, * PS_CSP_REQ_ITEM_EQUIPMENT;


// SCP_RESP_ITEM_EQUIPMENT : 0x9401
typedef struct _S_SCP_RESP_ITEM_EQUIPMENT
{
	BYTE                                              byResult;     // ������ ���� ��û�� ���� ��� ��
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�

} S_SCP_RESP_ITEM_EQUIPMENT, * PS_SCP_RESP_ITEM_EQUIPMENT;


// CSP_ITEM_EQUIPMENT_BROADCAST : 0x1402
typedef struct _S_CSP_ITEM_EQUIPMENT_BROADCAST
{

} S_CSP_ITEM_EQUIPMENT_BROADCAST, * PS_CSP_ITEM_EQUIPMENT_BROADCAST;


// SCP_ITEM_EQUIPMENT_BROADCAST : 0x9402
typedef struct _S_SCP_ITEM_EQUIPMENT_BROADCAST
{
	DWORD                                             dwKeyID;      // ���� ĳ���� KeyID
	DWORD                                             dwIndex;      // ���� ������ �ε���
	BYTE                                              byEquipPart;  // ������ ���� ����
	BYTE                                              bySubMaterialCount;

} S_SCP_ITEM_EQUIPMENT_BROADCAST, * PS_SCP_ITEM_EQUIPMENT_BROADCAST;


// CSP_ITEM_ABRASION : 0x1411
typedef struct _S_CSP_ITEM_ABRASION
{

} S_CSP_ITEM_ABRASION, * PS_CSP_ITEM_ABRASION;


// SCP_ITEM_ABRASION : 0x9411
typedef struct _S_SCP_ITEM_ABRASION
{
	DWORD                                             dwKeyIDWeapon;// ���� �������� KeyID
	DWORD                                             dwKeyIDBody;  // �Ǻ� �������� KeyID
	DWORD                                             dwKeyIDShield;// ���� �������� KeyID
	DWORD                                             dwKeyIDHead;  // ���� �������� KeyID
	DWORD                                             dwKeyIDFoot;  // �Ź� �������� KeyID
	DWORD                                             dwKeyIDBelt;  // �㸮�� �������� KeyID

} S_SCP_ITEM_ABRASION, * PS_SCP_ITEM_ABRASION;


// CSP_ITEM_ABRASION_BROADCAST : 0x1412
typedef struct _S_CSP_ITEM_ABRASION_BROADCAST
{

} S_CSP_ITEM_ABRASION_BROADCAST, * PS_CSP_ITEM_ABRASION_BROADCAST;


// SCP_ITEM_ABRASION_BROADCAST : 0x9412
typedef struct _S_SCP_ITEM_ABRASION_BROADCAST
{
	DWORD                                             dwKeyID;      // �������� ����� ĳ������ KeyID
	DWORD                                             dwIndexWeapon;// ���� �������� Index
	DWORD                                             dwIndexBody;  // �Ǻ� �������� Index
	DWORD                                             dwIndexShield;// ���� �������� Index
	DWORD                                             dwIndexHead;  // ���� �������� Index
	DWORD                                             dwIndexFoot;  // �Ź� �������� Index
	DWORD                                             dwIndexBelt;  // �㸮�� �������� Index

} S_SCP_ITEM_ABRASION_BROADCAST, * PS_SCP_ITEM_ABRASION_BROADCAST;


// CSP_ITEM_DURABILITY_DECREASE : 0x1413
typedef struct _S_CSP_ITEM_DURABILITY_DECREASE
{

} S_CSP_ITEM_DURABILITY_DECREASE, * PS_CSP_ITEM_DURABILITY_DECREASE;


// SCP_ITEM_DURABILITY_DECREASE : 0x9413
typedef struct _S_SCP_ITEM_DURABILITY_DECREASE
{
	DWORD                                             dwKeyIDWeapon;// ���� �������� KeyID
	short                                             snDurWeapon;  // ���� ������
	DWORD                                             dwKeyIDBody;  // �Ǻ� �������� KeyID
	short                                             snDurBody;    // ���� ������
	DWORD                                             dwKeyIDShield;// ���� �������� KeyID
	short                                             snDurShield;  // ���� ������
	DWORD                                             dwKeyIDHead;  // ���� �������� KeyID
	short                                             snDurHead;    // ���� ������
	DWORD                                             dwKeyIDFoot;  // �Ź� �������� KeyID
	short                                             snDurFoot;    // ���� ������
	DWORD                                             dwKeyIDBelt;  // ��Ʈ �������� KeyID
	short                                             snDurBelt;    // ���� ������

} S_SCP_ITEM_DURABILITY_DECREASE, * PS_SCP_ITEM_DURABILITY_DECREASE;


// CSP_REQ_NORMAL_CHAT : 0x1501
typedef struct _S_CSP_REQ_NORMAL_CHAT
{
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_NORMAL_CHAT, * PS_CSP_REQ_NORMAL_CHAT;


// SCP_RESP_NORMAL_CHAT : 0x9501
typedef struct _S_SCP_RESP_NORMAL_CHAT
{
	BYTE                                              byResult;     // ä�� ��� �뺸

} S_SCP_RESP_NORMAL_CHAT, * PS_SCP_RESP_NORMAL_CHAT;


// CSP_NORMAL_CHAT : 0x1502
typedef struct _S_CSP_NORMAL_CHAT
{

} S_CSP_NORMAL_CHAT, * PS_CSP_NORMAL_CHAT;


// SCP_NORMAL_CHAT : 0x9502
typedef struct _S_SCP_NORMAL_CHAT
{
	DWORD                                             dwKeyID;      // ä�� �޼����� ������ ĳ���� KeyID
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���
	char                                              szSender[26]; // �۽����� �̸�

} S_SCP_NORMAL_CHAT, * PS_SCP_NORMAL_CHAT;


// CSP_REQ_WHISPER_CHAT : 0x1503
typedef struct _S_CSP_REQ_WHISPER_CHAT
{
	char                                              szName[26];   // ä�� �޼����� ��û�� ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_WHISPER_CHAT, * PS_CSP_REQ_WHISPER_CHAT;


// SCP_RESP_WHISPER_CHAT : 0x9503
typedef struct _S_SCP_RESP_WHISPER_CHAT
{
	BYTE                                              byResult;     // ä�� ��� �뺸

} S_SCP_RESP_WHISPER_CHAT, * PS_SCP_RESP_WHISPER_CHAT;


// CSP_WHISPER_CHAT : 0x1504
typedef struct _S_CSP_WHISPER_CHAT
{

} S_CSP_WHISPER_CHAT, * PS_CSP_WHISPER_CHAT;


// SCP_WHISPER_CHAT : 0x9504
typedef struct _S_SCP_WHISPER_CHAT
{
	char                                              szName[26];   // ä�� �޼����� ������ ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���
	char                                              szReceiver[26];// �������� �̸�

} S_SCP_WHISPER_CHAT, * PS_SCP_WHISPER_CHAT;


// CSP_REQ_SHOUT_CHAT : 0x1505
typedef struct _S_CSP_REQ_SHOUT_CHAT
{
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_SHOUT_CHAT, * PS_CSP_REQ_SHOUT_CHAT;


// SCP_RESP_SHOUT_CHAT : 0x9505
typedef struct _S_SCP_RESP_SHOUT_CHAT
{
	BYTE                                              byResult;     // ä�� ��� �뺸

} S_SCP_RESP_SHOUT_CHAT, * PS_SCP_RESP_SHOUT_CHAT;


// CSP_SHOUT_CHAT : 0x1506
typedef struct _S_CSP_SHOUT_CHAT
{

} S_CSP_SHOUT_CHAT, * PS_CSP_SHOUT_CHAT;


// SCP_SHOUT_CHAT : 0x9506
typedef struct _S_SCP_SHOUT_CHAT
{
	char                                              szName[26];   // ä�� �޼����� ������ ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_SCP_SHOUT_CHAT, * PS_SCP_SHOUT_CHAT;


// CSP_REQ_PARTY_CHAT : 0x1507
typedef struct _S_CSP_REQ_PARTY_CHAT
{
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_PARTY_CHAT, * PS_CSP_REQ_PARTY_CHAT;


// SCP_RESP_PARTY_CHAT : 0x9507
typedef struct _S_SCP_RESP_PARTY_CHAT
{
	BYTE                                              byResult;     // ä�� ��� �뺸

} S_SCP_RESP_PARTY_CHAT, * PS_SCP_RESP_PARTY_CHAT;


// CSP_PARTY_CHAT : 0x1508
typedef struct _S_CSP_PARTY_CHAT
{

} S_CSP_PARTY_CHAT, * PS_CSP_PARTY_CHAT;


// SCP_PARTY_CHAT : 0x9508
typedef struct _S_SCP_PARTY_CHAT
{
	char                                              szName[26];   // ä�� �޼����� ������ ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_SCP_PARTY_CHAT, * PS_SCP_PARTY_CHAT;


// CSP_REQ_NOTIFY_MESSAGE : 0x1511
typedef struct _S_CSP_REQ_NOTIFY_MESSAGE
{
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_NOTIFY_MESSAGE, * PS_CSP_REQ_NOTIFY_MESSAGE;


// SCP_RESP_NOTIFY_MESSAGE : 0x9511
typedef struct _S_SCP_RESP_NOTIFY_MESSAGE
{
	BYTE                                              byResult;     // ä�� ��� ���� �޼���

} S_SCP_RESP_NOTIFY_MESSAGE, * PS_SCP_RESP_NOTIFY_MESSAGE;


// CSP_NOTIFY_MESSAGE : 0x1512
typedef struct _S_CSP_NOTIFY_MESSAGE
{

} S_CSP_NOTIFY_MESSAGE, * PS_CSP_NOTIFY_MESSAGE;


// SCP_NOTIFY_MESSAGE : 0x9512
typedef struct _S_SCP_NOTIFY_MESSAGE
{
	char                                              szName[26];   // ä�� �޼����� ������ ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_SCP_NOTIFY_MESSAGE, * PS_SCP_NOTIFY_MESSAGE;


// CSP_REQ_BROADCAST_MESSAGE : 0x1513
typedef struct _S_CSP_REQ_BROADCAST_MESSAGE
{
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_CSP_REQ_BROADCAST_MESSAGE, * PS_CSP_REQ_BROADCAST_MESSAGE;


// SCP_RESP_BROADCAST_MESSAGE : 0x9513
typedef struct _S_SCP_RESP_BROADCAST_MESSAGE
{
	BYTE                                              byResult;     // ä�� ��� ���� �޼���

} S_SCP_RESP_BROADCAST_MESSAGE, * PS_SCP_RESP_BROADCAST_MESSAGE;


// CSP_BROADCAST_MESSAGE : 0x1514
typedef struct _S_CSP_BROADCAST_MESSAGE
{

} S_CSP_BROADCAST_MESSAGE, * PS_CSP_BROADCAST_MESSAGE;


// SCP_BROADCAST_MESSAGE : 0x9514
typedef struct _S_SCP_BROADCAST_MESSAGE
{
	char                                              szName[26];   // ä�� �޼����� ������ ĳ���� �̸�
	BYTE                                              byBgColor;    // ä�� �޼��� ����
	BYTE                                              byTextColor;  // ä�� �޼��� ���ڻ�
	char                                              szMsg[221];   // ä�� �޼���

} S_SCP_BROADCAST_MESSAGE, * PS_SCP_BROADCAST_MESSAGE;


// CSP_REQ_CREATE_PARTY : 0x1601
typedef struct _S_CSP_REQ_CREATE_PARTY
{
	char                                              szPartyName[26];// ������ ��Ƽ �̸�

} S_CSP_REQ_CREATE_PARTY, * PS_CSP_REQ_CREATE_PARTY;


// SCP_RESP_CREATE_PARTY : 0x9601
typedef struct _S_SCP_RESP_CREATE_PARTY
{
	BYTE                                              byResult;     // ��Ƽ ������û ���

} S_SCP_RESP_CREATE_PARTY, * PS_SCP_RESP_CREATE_PARTY;


// CSP_REQ_DISBAND_PARTY : 0x1602
typedef struct _S_CSP_REQ_DISBAND_PARTY
{
	char                                              szPartyName[26];// ��ü�� ��Ƽ �̸�

} S_CSP_REQ_DISBAND_PARTY, * PS_CSP_REQ_DISBAND_PARTY;


// SCP_RESP_DISBAND_PARTY : 0x9602
typedef struct _S_SCP_RESP_DISBAND_PARTY
{
	BYTE                                              byResult;     // ��Ƽ ��ü��û ���

} S_SCP_RESP_DISBAND_PARTY, * PS_SCP_RESP_DISBAND_PARTY;


// CSP_DISBAND_PARTY_BROADCAST : 0x1603
typedef struct _S_CSP_DISBAND_PARTY_BROADCAST
{

} S_CSP_DISBAND_PARTY_BROADCAST, * PS_CSP_DISBAND_PARTY_BROADCAST;


// SCP_DISBAND_PARTY_BROADCAST : 0x9603
typedef struct _S_SCP_DISBAND_PARTY_BROADCAST
{
	BYTE                                              byResult;     // ��Ƽ ��ü ���

} S_SCP_DISBAND_PARTY_BROADCAST, * PS_SCP_DISBAND_PARTY_BROADCAST;


// CSP_REQ_JOIN_PARTY : 0x1604
typedef struct _S_CSP_REQ_JOIN_PARTY
{
	DWORD                                             dwKeyID;      // ��Ƽ�� ������ų ĳ������ KeyID

} S_CSP_REQ_JOIN_PARTY, * PS_CSP_REQ_JOIN_PARTY;


// SCP_RESP_JOIN_PARTY : 0x9604
typedef struct _S_SCP_RESP_JOIN_PARTY
{
	BYTE                                              byResult;     // ��Ƽ ������û ���

} S_SCP_RESP_JOIN_PARTY, * PS_SCP_RESP_JOIN_PARTY;


// CSP_JOIN_PARTY_NOTIFY : 0x1605
typedef struct _S_CSP_JOIN_PARTY_NOTIFY
{

} S_CSP_JOIN_PARTY_NOTIFY, * PS_CSP_JOIN_PARTY_NOTIFY;


// SCP_JOIN_PARTY_NOTIFY : 0x9605
typedef struct _S_SCP_JOIN_PARTY_NOTIFY
{
	DWORD                                             dwKeyID;      // ��Ƽ ������ ��û�� ĳ������ KeyID
	char                                              szPartyName[26];// ������ ��û�� ��Ƽ �̸�

} S_SCP_JOIN_PARTY_NOTIFY, * PS_SCP_JOIN_PARTY_NOTIFY;


// CSP_JOIN_PARTY_RESULT : 0x1606
typedef struct _S_CSP_JOIN_PARTY_RESULT
{
	DWORD                                             dwKeyID;      // ��Ƽ ������ ��û�� ĳ������ KeyID
	BYTE                                              byResult;     // ��Ƽ ������û ���

} S_CSP_JOIN_PARTY_RESULT, * PS_CSP_JOIN_PARTY_RESULT;


// SCP_JOIN_PARTY_RESULT : 0x9606
typedef struct _S_SCP_JOIN_PARTY_RESULT
{
	BYTE                                              byResult;     // ��Ƽ ������û ���

} S_SCP_JOIN_PARTY_RESULT, * PS_SCP_JOIN_PARTY_RESULT;


// CSP_JOIN_PARTY_RESULT_NOTIFY : 0x1607
typedef struct _S_CSP_JOIN_PARTY_RESULT_NOTIFY
{

} S_CSP_JOIN_PARTY_RESULT_NOTIFY, * PS_CSP_JOIN_PARTY_RESULT_NOTIFY;


// SCP_JOIN_PARTY_RESULT_NOTIFY : 0x9607
typedef struct _S_SCP_JOIN_PARTY_RESULT_NOTIFY
{
	BYTE                                              byResult;     // ��Ƽ ������û ���
	DWORD                                             dwKeyID;      // ��Ƽ�� ������ ĳ������ KeyID

} S_SCP_JOIN_PARTY_RESULT_NOTIFY, * PS_SCP_JOIN_PARTY_RESULT_NOTIFY;


// CSP_NEW_PARTY_MEMBER : 0x1608
typedef struct _S_CSP_NEW_PARTY_MEMBER
{

} S_CSP_NEW_PARTY_MEMBER, * PS_CSP_NEW_PARTY_MEMBER;


// SCP_NEW_PARTY_MEMBER : 0x9608
typedef struct _S_SCP_NEW_PARTY_MEMBER
{
	S_PARTY_MEMBER_INFO                               MemberInfo;   // ��Ƽ�� ����

} S_SCP_NEW_PARTY_MEMBER, * PS_SCP_NEW_PARTY_MEMBER;


// CSP_REQ_SECEDE_PARTY : 0x1609
typedef struct _S_CSP_REQ_SECEDE_PARTY
{
	char                                              szName[26];   // Ż���� ��Ƽ���� �̸�

} S_CSP_REQ_SECEDE_PARTY, * PS_CSP_REQ_SECEDE_PARTY;


// SCP_RESP_SECEDE_PARTY : 0x9609
typedef struct _S_SCP_RESP_SECEDE_PARTY
{
	BYTE                                              byResult;     // ��Ƽ Ż���û ���

} S_SCP_RESP_SECEDE_PARTY, * PS_SCP_RESP_SECEDE_PARTY;


// CSP_SECEDE_PARTY_BROADCAST : 0x160A
typedef struct _S_CSP_SECEDE_PARTY_BROADCAST
{

} S_CSP_SECEDE_PARTY_BROADCAST, * PS_CSP_SECEDE_PARTY_BROADCAST;


// SCP_SECEDE_PARTY_BROADCAST : 0x960A
typedef struct _S_SCP_SECEDE_PARTY_BROADCAST
{
	char                                              szName[26];   // Ż���� ��Ƽ���� �̸�

} S_SCP_SECEDE_PARTY_BROADCAST, * PS_SCP_SECEDE_PARTY_BROADCAST;


// CSP_REQ_PARTY_LIST : 0x160B
typedef struct _S_CSP_REQ_PARTY_LIST
{
	char                                              szPartyName[26];// ��Ƽ �̸�

} S_CSP_REQ_PARTY_LIST, * PS_CSP_REQ_PARTY_LIST;


// SCP_RESP_PARTY_LIST : 0x960B
typedef struct _S_SCP_RESP_PARTY_LIST
{
	BYTE                                              byCount;      

} S_SCP_RESP_PARTY_LIST, * PS_SCP_RESP_PARTY_LIST;


// CSP_REQ_CREATE_GUILD : 0x1611
typedef struct _S_CSP_REQ_CREATE_GUILD
{
	char                                              szGuildName[26];// ������ ��� �̸�
	DWORD                                             dwGuildMark;  

} S_CSP_REQ_CREATE_GUILD, * PS_CSP_REQ_CREATE_GUILD;


// SCP_RESP_CREATE_GUILD : 0x9611
typedef struct _S_SCP_RESP_CREATE_GUILD
{
	BYTE                                              byResult;     // ��� ������û ���
	S_SCP_INIT_GUILD                                  s_Guild;      // ������ ���

} S_SCP_RESP_CREATE_GUILD, * PS_SCP_RESP_CREATE_GUILD;


// CSP_REQ_DISBAND_GUILD : 0x1612
typedef struct _S_CSP_REQ_DISBAND_GUILD
{
	char                                              szGuildName[26];// ��ü�� ��� �̸�

} S_CSP_REQ_DISBAND_GUILD, * PS_CSP_REQ_DISBAND_GUILD;


// SCP_RESP_DISBAND_GUILD : 0x9612
typedef struct _S_SCP_RESP_DISBAND_GUILD
{
	BYTE                                              byResult;     // ��� ��ü��û ���
	char                                              szGuildName[26];// ��ü�� ��� �̸�

} S_SCP_RESP_DISBAND_GUILD, * PS_SCP_RESP_DISBAND_GUILD;


// CSP_CREATE_GUILD_BROADCAST : 0x1613
typedef struct _S_CSP_CREATE_GUILD_BROADCAST
{

} S_CSP_CREATE_GUILD_BROADCAST, * PS_CSP_CREATE_GUILD_BROADCAST;


// SCP_CREATE_GUILD_BROADCAST : 0x9613
typedef struct _S_SCP_CREATE_GUILD_BROADCAST
{
	char                                              szGuildName[26];// ������ ��� �̸�
	DWORD                                             dwKeyID;      // ������� KeyID

} S_SCP_CREATE_GUILD_BROADCAST, * PS_SCP_CREATE_GUILD_BROADCAST;


// CSP_DISBAND_GUILD_BROADCAST : 0x1614
typedef struct _S_CSP_DISBAND_GUILD_BROADCAST
{
	char                                              szGuildName[26];// ��ü�� ��� �̸�

} S_CSP_DISBAND_GUILD_BROADCAST, * PS_CSP_DISBAND_GUILD_BROADCAST;


// SCP_DISBAND_GUILD_BROADCAST : 0x9614
typedef struct _S_SCP_DISBAND_GUILD_BROADCAST
{
	char                                              szCharName[26];// ��带 ��ü�� ����� �̸�
	char                                              szGuildName[26];// ��ü�� ��� �̸�

} S_SCP_DISBAND_GUILD_BROADCAST, * PS_SCP_DISBAND_GUILD_BROADCAST;


// CSP_REQ_JOIN_GUILD : 0x1615
typedef struct _S_CSP_REQ_JOIN_GUILD
{
	char                                              szCharName[26];// ��忡 ������ų �ɸ����� �̸�

} S_CSP_REQ_JOIN_GUILD, * PS_CSP_REQ_JOIN_GUILD;


// SCP_RESP_JOIN_GUILD : 0x9615
typedef struct _S_SCP_RESP_JOIN_GUILD
{
	BYTE                                              byResult;     // ��� ������û ���
	char                                              szCharName[26];// ��忡 ������ų �ɸ����� �̸�

} S_SCP_RESP_JOIN_GUILD, * PS_SCP_RESP_JOIN_GUILD;


// CSP_JOIN_GUILD_NOTIFY : 0x1616
typedef struct _S_CSP_JOIN_GUILD_NOTIFY
{

} S_CSP_JOIN_GUILD_NOTIFY, * PS_CSP_JOIN_GUILD_NOTIFY;


// SCP_JOIN_GUILD_NOTIFY : 0x9616
typedef struct _S_SCP_JOIN_GUILD_NOTIFY
{
	char                                              szCharName[26];// ��������� ��û�� �ɸ����� �̸�
	char                                              szGuildName[26];// ������ ��û�� ��� �̸�

} S_SCP_JOIN_GUILD_NOTIFY, * PS_SCP_JOIN_GUILD_NOTIFY;


// CSP_JOIN_GUILD_RESULT : 0x1617
typedef struct _S_CSP_JOIN_GUILD_RESULT
{
	char                                              szCharName[26];// ��������� ��û�� �ɸ����� �̸�
	char                                              szGuildName[26];// ������ ��û�� ��� �̸�
	BYTE                                              byResult;     // ��� ������û ���

} S_CSP_JOIN_GUILD_RESULT, * PS_CSP_JOIN_GUILD_RESULT;


// SCP_JOIN_GUILD_RESULT : 0x9617
typedef struct _S_SCP_JOIN_GUILD_RESULT
{
	BYTE                                              byResult;     // ��� ������û ���
	char                                              szGuildName[26];// ������ ��û�� ��� �̸�

} S_SCP_JOIN_GUILD_RESULT, * PS_SCP_JOIN_GUILD_RESULT;


// CSP_JOIN_GUILD_RESULT_NOTIFY : 0x1618
typedef struct _S_CSP_JOIN_GUILD_RESULT_NOTIFY
{

} S_CSP_JOIN_GUILD_RESULT_NOTIFY, * PS_CSP_JOIN_GUILD_RESULT_NOTIFY;


// SCP_JOIN_GUILD_RESULT_NOTIFY : 0x9618
typedef struct _S_SCP_JOIN_GUILD_RESULT_NOTIFY
{
	BYTE                                              byResult;     // ��� ������û ���
	char                                              szCharName[26];// ��尡���� �ɸ����� �̸�

} S_SCP_JOIN_GUILD_RESULT_NOTIFY, * PS_SCP_JOIN_GUILD_RESULT_NOTIFY;


// CSP_NEW_GUILD_MEMBER : 0x1619
typedef struct _S_CSP_NEW_GUILD_MEMBER
{

} S_CSP_NEW_GUILD_MEMBER, * PS_CSP_NEW_GUILD_MEMBER;


// SCP_NEW_GUILD_MEMBER : 0x9619
typedef struct _S_SCP_NEW_GUILD_MEMBER
{
	S_GUILD_MEMBER_INFO                               MemberInfo;   // ���� ����

} S_SCP_NEW_GUILD_MEMBER, * PS_SCP_NEW_GUILD_MEMBER;


// CSP_REQ_SECEDE_GUILD : 0x161A
typedef struct _S_CSP_REQ_SECEDE_GUILD
{

} S_CSP_REQ_SECEDE_GUILD, * PS_CSP_REQ_SECEDE_GUILD;


// SCP_RESP_SECEDE_GUILD : 0x961A
typedef struct _S_SCP_RESP_SECEDE_GUILD
{
	BYTE                                              byResult;     // ��� Ż���û ���
	char                                              szGuildName[26];// Ż���� ����� �̸�

} S_SCP_RESP_SECEDE_GUILD, * PS_SCP_RESP_SECEDE_GUILD;


// CSP_SECEDE_GUILD_BROADCAST : 0x161B
typedef struct _S_CSP_SECEDE_GUILD_BROADCAST
{

} S_CSP_SECEDE_GUILD_BROADCAST, * PS_CSP_SECEDE_GUILD_BROADCAST;


// SCP_SECEDE_GUILD_BROADCAST : 0x961B
typedef struct _S_SCP_SECEDE_GUILD_BROADCAST
{
	char                                              szCharName[26];// Ż���� ������ �̸�
	char                                              szName[26];   // Ż���� ����� �̸�

} S_SCP_SECEDE_GUILD_BROADCAST, * PS_SCP_SECEDE_GUILD_BROADCAST;


// CSP_REQ_EXPEL_GUILD_MEMBER : 0x161D
typedef struct _S_CSP_REQ_EXPEL_GUILD_MEMBER
{
	char                                              szCharName[26];// ������ ������ �̸�

} S_CSP_REQ_EXPEL_GUILD_MEMBER, * PS_CSP_REQ_EXPEL_GUILD_MEMBER;


// SCP_RESP_EXPEL_GUILD_MEMBER : 0x961D
typedef struct _S_SCP_RESP_EXPEL_GUILD_MEMBER
{
	BYTE                                              byResult;     // ��� �����û ���
	char                                              szCharName[26];// ������ ������ �̸�

} S_SCP_RESP_EXPEL_GUILD_MEMBER, * PS_SCP_RESP_EXPEL_GUILD_MEMBER;


// CSP_EXPEL_GUILD_MEMBER_BROADCAST : 0x161E
typedef struct _S_CSP_EXPEL_GUILD_MEMBER_BROADCAST
{

} S_CSP_EXPEL_GUILD_MEMBER_BROADCAST, * PS_CSP_EXPEL_GUILD_MEMBER_BROADCAST;


// SCP_EXPEL_GUILD_MEMBER_BROADCAST : 0x961E
typedef struct _S_SCP_EXPEL_GUILD_MEMBER_BROADCAST
{
	char                                              szSourceName[26];// ������ ������ �̸�
	char                                              szTargetName[26];// ����� ������ �̸�

} S_SCP_EXPEL_GUILD_MEMBER_BROADCAST, * PS_SCP_EXPEL_GUILD_MEMBER_BROADCAST;


// CSP_REQ_QUEST_HISTORY : 0x1701
typedef struct _S_CSP_REQ_QUEST_HISTORY
{

} S_CSP_REQ_QUEST_HISTORY, * PS_CSP_REQ_QUEST_HISTORY;


// SCP_RESP_QUEST_HISTORY : 0x9701
typedef struct _S_SCP_RESP_QUEST_HISTORY
{
	BYTE                                              byCount;      // ����Ʈ �����丮 ī��Ʈ

} S_SCP_RESP_QUEST_HISTORY, * PS_SCP_RESP_QUEST_HISTORY;


// CSP_QUEST_DIALOG : 0x1702
typedef struct _S_CSP_QUEST_DIALOG
{
	DWORD                                             dwDialogIndex;// ��ȭ ��ȣ
	BYTE                                              byResult;     // ��ȭ ���

} S_CSP_QUEST_DIALOG, * PS_CSP_QUEST_DIALOG;


// SCP_QUEST_DIALOG : 0x9702
typedef struct _S_SCP_QUEST_DIALOG
{
	WORD                                              wIndex;       // ��ȭ ��ȣ

} S_SCP_QUEST_DIALOG, * PS_SCP_QUEST_DIALOG;


// CSP_QUEST_NOTIFY_LEVEL : 0x1703
typedef struct _S_CSP_QUEST_NOTIFY_LEVEL
{

} S_CSP_QUEST_NOTIFY_LEVEL, * PS_CSP_QUEST_NOTIFY_LEVEL;


// SCP_QUEST_NOTIFY_LEVEL : 0x9703
typedef struct _S_SCP_QUEST_NOTIFY_LEVEL
{
	DWORD                                             dwNPCIndex;   // NPC �ε��� ��ȣ
	BYTE                                              byIndex;      // ����Ʈ �ε��� ��ȣ
	BYTE                                              byLevel;      // ����Ʈ ���� ����

} S_SCP_QUEST_NOTIFY_LEVEL, * PS_SCP_QUEST_NOTIFY_LEVEL;


// CSP_MONSTER_DISAPPEAR : 0x1801
typedef struct _S_CSP_MONSTER_DISAPPEAR
{

} S_CSP_MONSTER_DISAPPEAR, * PS_CSP_MONSTER_DISAPPEAR;


// SCP_MONSTER_DISAPPEAR : 0x9801
typedef struct _S_SCP_MONSTER_DISAPPEAR
{
	DWORD                                             dwKeyID;      // Monster�� KeyID
	BYTE                                              byType;       // Monster�� ������� ����

} S_SCP_MONSTER_DISAPPEAR, * PS_SCP_MONSTER_DISAPPEAR;


// CSP_CHAR_STATUS : 0x1802
typedef struct _S_CSP_CHAR_STATUS
{

} S_CSP_CHAR_STATUS, * PS_CSP_CHAR_STATUS;


// SCP_CHAR_STATUS : 0x9802
typedef struct _S_SCP_CHAR_STATUS
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	DWORD                                             dwStatus;     // ĳ������ ���� ����

} S_SCP_CHAR_STATUS, * PS_SCP_CHAR_STATUS;


// CSP_CHAR_MONSTER_STATUS_BROADCAST : 0x1803
typedef struct _S_CSP_CHAR_MONSTER_STATUS_BROADCAST
{

} S_CSP_CHAR_MONSTER_STATUS_BROADCAST, * PS_CSP_CHAR_MONSTER_STATUS_BROADCAST;


// SCP_CHAR_MONSTER_STATUS_BROADCAST : 0x9803
typedef struct _S_SCP_CHAR_MONSTER_STATUS_BROADCAST
{
	DWORD                                             dwKeyID;      // ĳ������ KeyID
	BYTE                                              byAct;        // ����
	DWORD                                             dwStatus;     // ����

} S_SCP_CHAR_MONSTER_STATUS_BROADCAST, * PS_SCP_CHAR_MONSTER_STATUS_BROADCAST;


// CSP_CHAR_DEATH : 0x1805
typedef struct _S_CSP_CHAR_DEATH
{

} S_CSP_CHAR_DEATH, * PS_CSP_CHAR_DEATH;


// SCP_CHAR_DEATH : 0x9805
typedef struct _S_SCP_CHAR_DEATH
{
	short                                             snLossPrana;  // �ҽǵ� ������ ��
	BYTE                                              byCount;      // �ҽǵ� �������� ��

} S_SCP_CHAR_DEATH, * PS_SCP_CHAR_DEATH;


// CSP_CHAR_MONSTER_DEATH_BROADCAST : 0x1806
typedef struct _S_CSP_CHAR_MONSTER_DEATH_BROADCAST
{

} S_CSP_CHAR_MONSTER_DEATH_BROADCAST, * PS_CSP_CHAR_MONSTER_DEATH_BROADCAST;


// SCP_CHAR_MONSTER_DEATH_BROADCAST : 0x9806
typedef struct _S_SCP_CHAR_MONSTER_DEATH_BROADCAST
{
	DWORD                                             dwKeyID;      // ���� ĳ���� �Ǵ� Monster�� KeyID

} S_SCP_CHAR_MONSTER_DEATH_BROADCAST, * PS_SCP_CHAR_MONSTER_DEATH_BROADCAST;


// CSP_CHAR_HP_RECOVERY : 0x1811
typedef struct _S_CSP_CHAR_HP_RECOVERY
{

} S_CSP_CHAR_HP_RECOVERY, * PS_CSP_CHAR_HP_RECOVERY;


// SCP_CHAR_HP_RECOVERY : 0x9811
typedef struct _S_SCP_CHAR_HP_RECOVERY
{
	int                                               nCurHP;       // ȸ���� ���� ���� HP
	short                                             snHPRecoveryRate;// ĳ������ HP ȸ����
	int                                               nPrana;       // �� ������ ��

} S_SCP_CHAR_HP_RECOVERY, * PS_SCP_CHAR_HP_RECOVERY;


// CSP_MONSTER_HP_RECOVERY : 0x1812
typedef struct _S_CSP_MONSTER_HP_RECOVERY
{

} S_CSP_MONSTER_HP_RECOVERY, * PS_CSP_MONSTER_HP_RECOVERY;


// SCP_MONSTER_HP_RECOVERY : 0x9812
typedef struct _S_SCP_MONSTER_HP_RECOVERY
{
	int                                               nCurHP;       // ȸ���� ���� ���� HP
	short                                             snStress;     // Monster ��Ʈ����

} S_SCP_MONSTER_HP_RECOVERY, * PS_SCP_MONSTER_HP_RECOVERY;


// CSP_CHAR_CAST_PROMOTE : 0x1821
typedef struct _S_CSP_CHAR_CAST_PROMOTE
{

} S_CSP_CHAR_CAST_PROMOTE, * PS_CSP_CHAR_CAST_PROMOTE;


// SCP_CHAR_CAST_PROMOTE : 0x9821
typedef struct _S_SCP_CHAR_CAST_PROMOTE
{
	BYTE                                              byCastClass;  // ��µ� ���� ī��Ʈ ���
	BYTE                                              byCastGrade;  // ��µ� ���� ī��Ʈ ���

} S_SCP_CHAR_CAST_PROMOTE, * PS_SCP_CHAR_CAST_PROMOTE;


// CSP_CHAR_CAST_PROMOTE_BROADCAST : 0x1822
typedef struct _S_CSP_CHAR_CAST_PROMOTE_BROADCAST
{

} S_CSP_CHAR_CAST_PROMOTE_BROADCAST, * PS_CSP_CHAR_CAST_PROMOTE_BROADCAST;


// SCP_CHAR_CAST_PROMOTE_BROADCAST : 0x9822
typedef struct _S_SCP_CHAR_CAST_PROMOTE_BROADCAST
{
	char                                              szName[26];   // ĳ������ �̸�
	BYTE                                              byCastClass;  // ��µ� ���� ī��Ʈ ���
	BYTE                                              byCastGrade;  // ��µ� ���� ī��Ʈ ���

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
	char                                              szName[26];   // ĳ������ �̸�

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
	int                                               nPrana;       // ���� ����
	short                                             snChakraMuscle;// ������ ��ũ��
	short                                             snChakraNerve;// �Ű��� ��ũ��
	short                                             snChakraHeart;// ������ ��ũ��
	short                                             snChakraSoul; // ������ ��ũ��
	short                                             snPureChakraMuscle;// ���� ������ ��ũ��
	short                                             snPureChakraNerve;// ���� �Ű��� ��ũ��
	short                                             snPureChakraHeart;// ���� ������ ��ũ��
	short                                             snPureChakraSoul;// ���� ������ ��ũ��
	short                                             snPhysicalMinDamage;// ���� �ּ� ������
	short                                             snPhysicalMaxDamage;// ���� �ִ� ������
	short                                             snMagicMinDamage;// ���� �ּ� ������
	short                                             snMagicMaxDamage;// ���� �ִ� ������
	short                                             snFireMinDamage;// �� �ּ� ������
	short                                             snFireMaxDamage;// �� �ִ� ������
	short                                             snColdMinDamage;// ���� �ּ� ������
	short                                             snColdMaxDamage;// ���� �ִ� ������
	short                                             snPoisonMinDamage;// �� �ּ� ������
	short                                             snPoisonMaxDamage;// �� �ִ� ������
	short                                             snAcidMinDamage;// �� �ּ� ������
	short                                             snAcidMaxDamage;// �� �ִ� ������
	short                                             snArmorIntensity;// ������ ����-����
	short                                             snAttackSuccRate;// ���� ������
	short                                             snAvoidanceRate;// ȸ����
	int                                               nMaxHP;       // ĳ������ �ִ� HP
	short                                             snFireResist; // �� ���׷�
	short                                             snColdResist; // ���� ���׷�
	short                                             snPoisonResist;// �� ���׷�
	short                                             snAcidResist; // �� ���׷�

} S_SCP_CHAR_PARAMS_CHANGE, * PS_SCP_CHAR_PARAMS_CHANGE;


// CSP_REQ_CHAKRA_RISING : 0x1921
typedef struct _S_CSP_REQ_CHAKRA_RISING
{
	DWORD                                             dwNpcKeyID;   // NPC KeyID
	BYTE                                              byReqChakraPart;// ��ũ�� ��� ��û ����

} S_CSP_REQ_CHAKRA_RISING, * PS_CSP_REQ_CHAKRA_RISING;


// SCP_RESP_CHAKRA_RISING : 0x9921
typedef struct _S_SCP_RESP_CHAKRA_RISING
{
	BYTE                                              byResult;     // ���
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
	BYTE                                              byResult;     // ���
	int                                               nRisingBrahman;// ��� �� ���� ��� ����Ʈ ��
	BYTE                                              byCastClass;  // ��� ����Ʈ ��� �� ī��Ʈ ���
	BYTE                                              byCastGrade;  // ��� ����Ʈ ��� �� ī��Ʈ ���
	int                                               nPrana;       

} S_SCP_RESP_BRAHMAN_RISING, * PS_SCP_RESP_BRAHMAN_RISING;


// CSP_REQ_INCREASE_INVENTORY_SLOT : 0x1931
typedef struct _S_CSP_REQ_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// �κ��丮 ����

} S_CSP_REQ_INCREASE_INVENTORY_SLOT, * PS_CSP_REQ_INCREASE_INVENTORY_SLOT;


// SCP_RESP_INCREASE_INVENTORY_SLOT : 0x9931
typedef struct _S_SCP_RESP_INCREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // �κ��丮 ���� ���� ��û ���
	BYTE                                              byCount;      // Inventory Expand Info

} S_SCP_RESP_INCREASE_INVENTORY_SLOT, * PS_SCP_RESP_INCREASE_INVENTORY_SLOT;


// CSP_REQ_DECREASE_INVENTORY_SLOT : 0x1932
typedef struct _S_CSP_REQ_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byInventoryType;// �κ��丮 ����
	BYTE                                              byX;          // Bag Item �� ��ǥ X
	BYTE                                              byZ;          // Bag Item �� ��ǥ Z

} S_CSP_REQ_DECREASE_INVENTORY_SLOT, * PS_CSP_REQ_DECREASE_INVENTORY_SLOT;


// SCP_RESP_DECREASE_INVENTORY_SLOT : 0x9932
typedef struct _S_SCP_RESP_DECREASE_INVENTORY_SLOT
{
	BYTE                                              byResult;     // ���

} S_SCP_RESP_DECREASE_INVENTORY_SLOT, * PS_SCP_RESP_DECREASE_INVENTORY_SLOT;


// CSP_REQ_NPC_POINT_UP : 0x1941
typedef struct _S_CSP_REQ_NPC_POINT_UP
{
	DWORD                                             dwNPCKeyID;   // NPC KeyID

} S_CSP_REQ_NPC_POINT_UP, * PS_CSP_REQ_NPC_POINT_UP;


// SCP_RESP_NPC_POINT_UP : 0x9941
typedef struct _S_SCP_RESP_NPC_POINT_UP
{
	BYTE                                              byResult;     // NPC ģ���� ��� ��û ���
	DWORD                                             dwGroup;      // NPC ���� ��ȣ
	DWORD                                             dwPoint;      // ��� �� ����� ����Ʈ ��

} S_SCP_RESP_NPC_POINT_UP, * PS_SCP_RESP_NPC_POINT_UP;


// CSP_REQ_CHANGE_CKAKRA_TO_PRANA : 0x1951
typedef struct _S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA
{

} S_CSP_REQ_CHANGE_CKAKRA_TO_PRANA, * PS_CSP_REQ_CHANGE_CKAKRA_TO_PRANA;


// SCP_RESP_CHANGE_CKAKRA_TO_PRANA : 0x9951
typedef struct _S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA
{
	BYTE                                              byResult;     // NPC ģ���� ��� ��û ���
	int                                               nPrana;       // �������� ��

} S_SCP_RESP_CHANGE_CKAKRA_TO_PRANA, * PS_SCP_RESP_CHANGE_CKAKRA_TO_PRANA;


// CSP_OTHER_CHAR_PARAM_BROADCAST : 0x1952
typedef struct _S_CSP_OTHER_CHAR_PARAM_BROADCAST
{

} S_CSP_OTHER_CHAR_PARAM_BROADCAST, * PS_CSP_OTHER_CHAR_PARAM_BROADCAST;


// SCP_OTHER_CHAR_PARAM_BROADCAST : 0x9952
typedef struct _S_SCP_OTHER_CHAR_PARAM_BROADCAST
{
	DWORD                                             dwKeyID;      // �ɸ����� KeyID
	DWORD                                             dwGuildMark;  // ��帶ũ�ε���

} S_SCP_OTHER_CHAR_PARAM_BROADCAST, * PS_SCP_OTHER_CHAR_PARAM_BROADCAST;


// CSP_REQ_SAVE_POSITION : 0x1961
typedef struct _S_CSP_REQ_SAVE_POSITION
{
	WORD                                              wRegenID;     // ��ġ��������� ID

} S_CSP_REQ_SAVE_POSITION, * PS_CSP_REQ_SAVE_POSITION;


// SCP_RESP_SAVE_POSITION : 0x9961
typedef struct _S_SCP_RESP_SAVE_POSITION
{
	BYTE                                              byResult;     // NPC ģ���� ��� ��û ���

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
	DWORD                                             dwIndex;      // ����� ��ų�� Index
	BYTE                                              byType;       // SKILL�� ����

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
	DWORD                                             dwIndex;      // �ڵ� ��ϵ� ��ų�� Index
	BYTE                                              byType;       // SKILL�� ����

} S_SCP_SKILL_REGIST, * PS_SCP_SKILL_REGIST;


// CSP_REQ_SKILL_SELECT : 0x2003
typedef struct _S_CSP_REQ_SKILL_SELECT
{
	BYTE                                              bySelect;     // SKILL�� ����/����
	BYTE                                              byHand;       // SKILL ������/���� ����
	DWORD                                             dwIndex;      // ����/���� ��ų Index

} S_CSP_REQ_SKILL_SELECT, * PS_CSP_REQ_SKILL_SELECT;


// SCP_RESP_SKILL_SELECT : 0xA003
typedef struct _S_SCP_RESP_SKILL_SELECT
{
	BYTE                                              byResult;     // SKILL ����/���� ���

} S_SCP_RESP_SKILL_SELECT, * PS_SCP_RESP_SKILL_SELECT;


// CSP_REQ_SKILL_SELECT_BROADCAST : 0x2004
typedef struct _S_CSP_REQ_SKILL_SELECT_BROADCAST
{

} S_CSP_REQ_SKILL_SELECT_BROADCAST, * PS_CSP_REQ_SKILL_SELECT_BROADCAST;


// SCP_RESP_SKILL_SELECT_BROADCAST : 0xA004
typedef struct _S_SCP_RESP_SKILL_SELECT_BROADCAST
{
	DWORD                                             dwKeyID;      // �ɸ����� KeyID
	BYTE                                              bySelect;     // SKILL�� ����/����
	BYTE                                              byHand;       // SKILL ������/���� ����
	DWORD                                             dwIndex;      // ����/���� ��ų Index
	BYTE                                              byLevel;      // ��ų ����

} S_SCP_RESP_SKILL_SELECT_BROADCAST, * PS_SCP_RESP_SKILL_SELECT_BROADCAST;


// CSP_REQ_SKILL_USE2_CHAR : 0x2011
typedef struct _S_CSP_REQ_SKILL_USE2_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ������ ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_SKILL_USE2_CHAR, * PS_CSP_REQ_SKILL_USE2_CHAR;


// SCP_RESP_SKILL_USE2_CHAR : 0xA011
typedef struct _S_SCP_RESP_SKILL_USE2_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_SCP_RESP_SKILL_USE2_CHAR, * PS_SCP_RESP_SKILL_USE2_CHAR;


// CSP_SKILL_READY_CHAR_BROADCAST : 0x2012
typedef struct _S_CSP_SKILL_READY_CHAR_BROADCAST
{

} S_CSP_SKILL_READY_CHAR_BROADCAST, * PS_CSP_SKILL_READY_CHAR_BROADCAST;


// SCP_SKILL_READY_CHAR_BROADCAST : 0xA012
typedef struct _S_SCP_SKILL_READY_CHAR_BROADCAST
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwKeyID;      // ��ų�� ����ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;// ��ų ������ ���ϴ� ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ

} S_SCP_SKILL_READY_CHAR_BROADCAST, * PS_SCP_SKILL_READY_CHAR_BROADCAST;


// CSP_REQ_SKILL_ATK_CHAR : 0x2013
typedef struct _S_CSP_REQ_SKILL_ATK_CHAR
{
	BYTE                                              byType;       // ��� Type
	DWORD                                             dwTargetKeyID;// ������ ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	short                                             snDegree;     // �����ڸ� �߽����� �� ������� ����
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��

} S_CSP_REQ_SKILL_ATK_CHAR, * PS_CSP_REQ_SKILL_ATK_CHAR;


// SCP_RESP_SKILL_ATK_CHAR : 0xA013
typedef struct _S_SCP_RESP_SKILL_ATK_CHAR
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCharX;      // ����� X ��ǥ
	short                                             snCharZ;      // ����� Z ��ǥ
	BYTE                                              byClientCount;// Client���� ����� ī��Ʈ ��
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ����/Monster�� ���� HP

} S_SCP_RESP_SKILL_ATK_CHAR, * PS_SCP_RESP_SKILL_ATK_CHAR;


// CSP_SKILL_ATK_CHAR_BROADCAST : 0x2014
typedef struct _S_CSP_SKILL_ATK_CHAR_BROADCAST
{

} S_CSP_SKILL_ATK_CHAR_BROADCAST, * PS_CSP_SKILL_ATK_CHAR_BROADCAST;


// SCP_SKILL_ATK_CHAR_BROADCAST : 0xA014
typedef struct _S_SCP_SKILL_ATK_CHAR_BROADCAST
{
	BYTE                                              byType;       // ��� Type
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // ��ų�� ����ϴ� ĳ������ KeyID
	DWORD                                             dwTargetKeyID;//  ��ų ������ ���ϴ� ĳ������ KeyID
	DWORD                                             dwIndex;      // ���ݿ� ����� ��ų�� Index
	short                                             snX;          // �� X ��ǥ
	short                                             snZ;          // �� Z ��ǥ
	short                                             snCharX;      // ����� X ��ǥ
	short                                             snCharZ;      // ����� Z ��ǥ
	int                                               nReduceHP;    // ��������
	int                                               nCurHP;       // ���� ���ϴ� ĳ������ ���� HP
	BYTE                                              byCritical;   // ũ��Ƽ�� ��Ʈ ���� ����
	short                                             snCurX;       // �������� ���� X ��ǥ
	short                                             snCurZ;       // �������� ���� Z ��ǥ

} S_SCP_SKILL_ATK_CHAR_BROADCAST, * PS_SCP_SKILL_ATK_CHAR_BROADCAST;


// CSP_REQ_SKILL_LEVEL_UP : 0x2021
typedef struct _S_CSP_REQ_SKILL_LEVEL_UP
{
	DWORD                                             dwIndex;      // Level-Up�� ��û�� ��ų�� Index

} S_CSP_REQ_SKILL_LEVEL_UP, * PS_CSP_REQ_SKILL_LEVEL_UP;


// SCP_RESP_SKILL_LEVEL_UP : 0xA021
typedef struct _S_SCP_RESP_SKILL_LEVEL_UP
{
	BYTE                                              byResult;     // Level-Up ���
	BYTE                                              byLevel;      // ��ų�� Level
	int                                               nPrana;       // ���� ������ ��
	short                                             snMovingSpeed;// �������� �̵��ӵ�
	short                                             snAttackSpeed;// �������� ���ݼӵ�
	short                                             snCastingSpeed;// �������� �ɽ��üӵ�
	BYTE                                              byShootRange; // �߻�ü�� �����Ÿ�

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
	BYTE                                              byCount;      // ���� ������ ��ų�� ��

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
	DWORD                                             dwMakingIndex;// �������� ������ Index
	DWORD                                             dwRemainTime; // �������� �������� ���� ���۽ð�
	BYTE                                              byCount;      // ���� ������ �������� ��

} S_SCP_RESP_SHOP_ITEM_LIST, * PS_SCP_RESP_SHOP_ITEM_LIST;


// CSP_REQ_ITEM_MAKING : 0x2102
typedef struct _S_CSP_REQ_ITEM_MAKING
{
	DWORD                                             dwIndex;      // �����Ƿ��� ������ Index
	BYTE                                              byCount;      // �����Ƿ��� ������ ����

} S_CSP_REQ_ITEM_MAKING, * PS_CSP_REQ_ITEM_MAKING;


// SCP_RESP_ITEM_MAKING : 0xA102
typedef struct _S_SCP_RESP_ITEM_MAKING
{
	BYTE                                              byResult;     // Result Field
	BYTE                                              byPlace;      // �������� ��ġ
	int                                               nSteel;       // ���� ���Ǿ�
	int                                               nCloth;       // ���� ����ī��Ʈ(�ǹ̾���)
	DWORD                                             dwNeedTime;   // ������ ���ۿ� �ʿ��� �ð�
	DWORD                                             dwKeyID;      // ���� ������ �������� KeyID
	short                                             snX;          // ���� ������ �������� �κ����� X��ǥ
	short                                             snZ;          // ���� ������ �������� �κ����� Z��ǥ

} S_SCP_RESP_ITEM_MAKING, * PS_SCP_RESP_ITEM_MAKING;


// CSP_REQ_ITEM_REDEEM : 0x2103
typedef struct _S_CSP_REQ_ITEM_REDEEM
{

} S_CSP_REQ_ITEM_REDEEM, * PS_CSP_REQ_ITEM_REDEEM;


// SCP_RESP_ITEM_REDEEM : 0xA103
typedef struct _S_SCP_RESP_ITEM_REDEEM
{
	DWORD                                             dwNeedTime;   // ������ �������� Index
	DWORD                                             dwKeyID;      // ������ �������� KeyID

} S_SCP_RESP_ITEM_REDEEM, * PS_SCP_RESP_ITEM_REDEEM;


// CSP_REQ_ITEM_REPAIR : 0x2104
typedef struct _S_CSP_REQ_ITEM_REPAIR
{
	DWORD                                             dwKeyID;      // ������ �������� KeyID

} S_CSP_REQ_ITEM_REPAIR, * PS_CSP_REQ_ITEM_REPAIR;


// SCP_RESP_ITEM_REPAIR : 0xA104
typedef struct _S_SCP_RESP_ITEM_REPAIR
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // ���� ���Ǿ�
	int                                               nCloth;       // ���� ����ī��Ʈ(�ǹ̾���)

} S_SCP_RESP_ITEM_REPAIR, * PS_SCP_RESP_ITEM_REPAIR;


// CSP_REQ_ITEM_DISMANTLE : 0x2105
typedef struct _S_CSP_REQ_ITEM_DISMANTLE
{
	DWORD                                             dwKeyID;      // ��ü�� �������� KeyID

} S_CSP_REQ_ITEM_DISMANTLE, * PS_CSP_REQ_ITEM_DISMANTLE;


// SCP_RESP_ITEM_DISMANTLE : 0xA105
typedef struct _S_SCP_RESP_ITEM_DISMANTLE
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // ���� ���Ǿ�
	int                                               nCloth;       // ���� ����ī��Ʈ(�ǹ̾���)

} S_SCP_RESP_ITEM_DISMANTLE, * PS_SCP_RESP_ITEM_DISMANTLE;


// CSP_REQ_ITEM_REFINING : 0x2106
typedef struct _S_CSP_REQ_ITEM_REFINING
{
	DWORD                                             dwKeyID;      // ������ �������� KeyID
	DWORD                                             dwSubKeyID;   // ÷���� ��������� KeyID

} S_CSP_REQ_ITEM_REFINING, * PS_CSP_REQ_ITEM_REFINING;


// SCP_RESP_ITEM_REFINING : 0xA106
typedef struct _S_SCP_RESP_ITEM_REFINING
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwKeyID;      // ���õ� �������� KeyID
	DWORD                                             dwSubKeyID;   // ÷���� ������������ KeyID
	int                                               nMoney;       // �ɸ����� ���� ���Ǿ�
	int                                               nPrana;       // �ɸ����� ���� ����
	BYTE                                              byCount;      // ��������� ��

} S_SCP_RESP_ITEM_REFINING, * PS_SCP_RESP_ITEM_REFINING;


// CSP_REQ_PRANA_CONTRIBUTION : 0x2112
typedef struct _S_CSP_REQ_PRANA_CONTRIBUTION
{
	int                                               nPrana;       // �峳�� ������ ��

} S_CSP_REQ_PRANA_CONTRIBUTION, * PS_CSP_REQ_PRANA_CONTRIBUTION;


// SCP_RESP_PRANA_CONTRIBUTION : 0xA112
typedef struct _S_SCP_RESP_PRANA_CONTRIBUTION
{
	BYTE                                              byResult;     // Result Field
	int                                               nBrahmanPoint;// �峳 �� ��� ����Ʈ
	int                                               nMaxHP;       // �� ĳ������ �ִ� HP
	short                                             snUsePrana;   // �� ������ ��ũ�󿡼� �����ð��� �Ҹ�Ǵ� �� ������ ��

} S_SCP_RESP_PRANA_CONTRIBUTION, * PS_SCP_RESP_PRANA_CONTRIBUTION;


// CSP_REQ_RESOURCE_BARTER : 0x2113
typedef struct _S_CSP_REQ_RESOURCE_BARTER
{
	DWORD                                             dwNpcKeyID;   // ��ȯ�� NPC KeyID
	DWORD                                             dwKeyID;      // ��ȯ�� �������� KEYID
	int                                               nItemCount;   // ��ȯ�� �������� ��ø����

} S_CSP_REQ_RESOURCE_BARTER, * PS_CSP_REQ_RESOURCE_BARTER;


// SCP_RESP_RESOURCE_BARTER : 0xA113
typedef struct _S_SCP_RESP_RESOURCE_BARTER
{
	BYTE                                              byResult;     // Result Field
	int                                               nSteel;       // ���� ���Ǿ�
	int                                               nCloth;       // ���� ����ī��Ʈ(�ǹ̾���)

} S_SCP_RESP_RESOURCE_BARTER, * PS_SCP_RESP_RESOURCE_BARTER;


// CSP_REQ_RESOURCE_BARTER_PRICE : 0x2114
typedef struct _S_CSP_REQ_RESOURCE_BARTER_PRICE
{

} S_CSP_REQ_RESOURCE_BARTER_PRICE, * PS_CSP_REQ_RESOURCE_BARTER_PRICE;


// SCP_RESP_RESOURCE_BARTER_PRICE : 0xA114
typedef struct _S_SCP_RESP_RESOURCE_BARTER_PRICE
{
	int                                               nSteelCount;  // ö�� ��ȯ����
	int                                               nClothCount;  // ������ ��ȯ����

} S_SCP_RESP_RESOURCE_BARTER_PRICE, * PS_SCP_RESP_RESOURCE_BARTER_PRICE;


// CSP_REQ_EXCHANGE : 0x2201
typedef struct _S_CSP_REQ_EXCHANGE
{
	DWORD                                             dwKeyID;      // ������ ��ȯ�� �� ĳ������ KeyID

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
	DWORD                                             dwKeyID;      // ������ ��ȯ�� ��û�� ĳ������ KeyID

} S_SCP_EXCHANGE_NOTIFY, * PS_SCP_EXCHANGE_NOTIFY;


// CSP_EXCHANGE_RESULT : 0x2203
typedef struct _S_CSP_EXCHANGE_RESULT
{
	DWORD                                             dwKeyID;      // ������ ��ȯ�� ��û�� ĳ������ KeyID
	BYTE                                              byResult;     // �³� ����

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
	DWORD                                             dwKeyID;      // ��ȯ ��û ����� ������ ĳ������ KeyID
	BYTE                                              byResult;     // �³� ����

} S_SCP_EXCHANGE_RESULT_NOTIFY, * PS_SCP_EXCHANGE_RESULT_NOTIFY;


// CSP_REQ_EXCHANGE_ADD : 0x2205
typedef struct _S_CSP_REQ_EXCHANGE_ADD
{
	DWORD                                             dwKeyID;      // ��ȯâ�� �߰��� �������� KeyID
	short                                             snX;          // ��ȯâ���� ������ X ��ǥ
	short                                             snZ;          // ��ȯâ���� ������ Z ��ǥ

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
	DWORD                                             dwKeyID;      // ��ȯâ�� �߰��� �������� KeyID
	DWORD                                             dwIndex;      // ��ȯâ�� �߰��� �������� Index
	short                                             snCurDurability;
	int                                               nItemCount;   // ��ȯâ�� �߰��� �������� ����
	short                                             snX;          // ��ȯâ���� ������ X ��ǥ
	short                                             snZ;          // ��ȯâ���� ������ Z ��ǥ
	BYTE                                              bySubMaterialCount;

} S_SCP_EXCHANGE_ADD_NOTIFY, * PS_SCP_EXCHANGE_ADD_NOTIFY;


// CSP_REQ_EXCHANGE_ERASE : 0x2207
typedef struct _S_CSP_REQ_EXCHANGE_ERASE
{
	DWORD                                             dwKeyID;      // ��ȯâ���� ������ �������� KeyID

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
	DWORD                                             dwKeyID;      // ��ȯâ���� ������ �������� KeyID

} S_SCP_EXCHANGE_ERASE_NOTIFY, * PS_SCP_EXCHANGE_ERASE_NOTIFY;


// CSP_EXCHANGE_ACCEPT : 0x2209
typedef struct _S_CSP_EXCHANGE_ACCEPT
{
	BYTE                                              byAccept;     // Ȯ�� ��ư ���� ����

} S_CSP_EXCHANGE_ACCEPT, * PS_CSP_EXCHANGE_ACCEPT;


// SCP_EXCHANGE_ACCEPT : 0xA209
typedef struct _S_SCP_EXCHANGE_ACCEPT
{
	BYTE                                              byResult;     // Result Field
	int                                               nMoney;       // ��ȯ�� �ɸ����� ���Ǿƾ�

} S_SCP_EXCHANGE_ACCEPT, * PS_SCP_EXCHANGE_ACCEPT;


// CSP_EXCHANGE_ACCEPT_NOTIFY : 0x220A
typedef struct _S_CSP_EXCHANGE_ACCEPT_NOTIFY
{

} S_CSP_EXCHANGE_ACCEPT_NOTIFY, * PS_CSP_EXCHANGE_ACCEPT_NOTIFY;


// SCP_EXCHANGE_ACCEPT_NOTIFY : 0xA20A
typedef struct _S_SCP_EXCHANGE_ACCEPT_NOTIFY
{
	BYTE                                              byAccept;     // ��ȯâ Ȯ�� ��ư ���� ����
	int                                               nMoney;       // ��ȯ�� �ɸ����� ���Ǿƾ�

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
	int                                               nExMoney;     // ��ȯ�� ��

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
	int                                               nExMoney;     // ��ȯ�� ��

} S_SCP_EXCHANGE_MONEY_NOTIFY, * PS_SCP_EXCHANGE_MONEY_NOTIFY;


// CSP_REQ_TRADE_ENTRY : 0x2301
typedef struct _S_CSP_REQ_TRADE_ENTRY
{
	char                                              szTitle[32];  // �ŷ� ����
	int                                               nGoldCount;   // ���ϴ� �ݾ�
	BYTE                                              byAKindCount; 

} S_CSP_REQ_TRADE_ENTRY, * PS_CSP_REQ_TRADE_ENTRY;


// SCP_RESP_TRADE_ENTRY : 0xA301
typedef struct _S_SCP_RESP_TRADE_ENTRY
{
	BYTE                                              byResult;     // �ŷ� ��� �����

} S_SCP_RESP_TRADE_ENTRY, * PS_SCP_RESP_TRADE_ENTRY;


// CSP_REQ_TRADE_CANCEL : 0x2302
typedef struct _S_CSP_REQ_TRADE_CANCEL
{
	DWORD                                             dwTradeID;    // ����� �ŷ� �׸� ���̵�

} S_CSP_REQ_TRADE_CANCEL, * PS_CSP_REQ_TRADE_CANCEL;


// SCP_RESP_TRADE_CANCEL : 0xA302
typedef struct _S_SCP_RESP_TRADE_CANCEL
{
	BYTE                                              byResult;     // �ŷ� ��� ��� �����

} S_SCP_RESP_TRADE_CANCEL, * PS_SCP_RESP_TRADE_CANCEL;


// CSP_REQ_TRADE : 0x2303
typedef struct _S_CSP_REQ_TRADE
{
	DWORD                                             dwTradeID;    // �ŷ��� �ŷ� �׸� ���̵�

} S_CSP_REQ_TRADE, * PS_CSP_REQ_TRADE;


// SCP_RESP_TRADE : 0xA303
typedef struct _S_SCP_RESP_TRADE
{
	BYTE                                              byResult;     // �ŷ� ��û ��� ��

} S_SCP_RESP_TRADE, * PS_SCP_RESP_TRADE;


// SCP_RESP_TRADE_SUCCESS : 0xA307
typedef struct _S_SCP_RESP_TRADE_SUCCESS
{
	int                                               nGoldCount;   // ����� ���� ���Ǿ�

} S_SCP_RESP_TRADE_SUCCESS, * PS_SCP_RESP_TRADE_SUCCESS;


// CSP_REQ_TRADE_LIST : 0x2304
typedef struct _S_CSP_REQ_TRADE_LIST
{
	BYTE                                              bySearchMethod;// �˻����-�Ϲ�/�ؽ�Ʈ�˻�
	BYTE                                              byCatalogue;  // �˻����-ĳ�����̸�/����
	BYTE                                              byNewSearch;  // ���ο�˻����� ����
	char                                              szSearchChat[32];// �ŷ� ����
	short                                             snTabNumber;  // �˻� �� ��ȣ

} S_CSP_REQ_TRADE_LIST, * PS_CSP_REQ_TRADE_LIST;


// SCP_RESP_TRADE_LIST : 0xA304
typedef struct _S_SCP_RESP_TRADE_LIST
{
	short                                             snTolListCount;// �� �ŷ��׸� ����
	BYTE                                              byListCount;  // ���� �ŷ��׸� ����
	DWORD                                             dwTradeID;    // �ŷ� �׸� ���̵�
	char                                              szCharName[26];// ����� ĳ���� �̸�
	char                                              szTitle[32];  // �ŷ� ����
	int                                               nGoldCount;   // ���ϴ� �ݾ�
	BYTE                                              byAKindCount; 

} S_SCP_RESP_TRADE_LIST, * PS_SCP_RESP_TRADE_LIST;


// CSP_REQ_MY_ENTYR_LIST : 0x2305
typedef struct _S_CSP_REQ_MY_ENTYR_LIST
{

} S_CSP_REQ_MY_ENTYR_LIST, * PS_CSP_REQ_MY_ENTYR_LIST;


// SCP_RESP_MY_ENTYR_LIST : 0xA305
typedef struct _S_SCP_RESP_MY_ENTYR_LIST
{
	BYTE                                              byListCount;  // ���� �ŷ��׸� ����
	BYTE                                              byState;      // 0x00-���/0x01-����
	BYTE                                              byAKindCount; 

} S_SCP_RESP_MY_ENTYR_LIST, * PS_SCP_RESP_MY_ENTYR_LIST;


// CSP_REQ_TRADE_ITEM_SEEK : 0x2306
typedef struct _S_CSP_REQ_TRADE_ITEM_SEEK
{
	BYTE                                              bySeekMethod; // ã����
	BYTE                                              byAKindCount; 

} S_CSP_REQ_TRADE_ITEM_SEEK, * PS_CSP_REQ_TRADE_ITEM_SEEK;


// SCP_RESP_TRADE_ITEM_SEEK : 0xA306
typedef struct _S_SCP_RESP_TRADE_ITEM_SEEK
{
	BYTE                                              byResult;     // �ŷ� ��û ��� ��

} S_SCP_RESP_TRADE_ITEM_SEEK, * PS_SCP_RESP_TRADE_ITEM_SEEK;


// CSP_REQ_TRANSPARENCY_MODE : 0x2501
typedef struct _S_CSP_REQ_TRANSPARENCY_MODE
{
	BYTE                                              byMode;       // ������ �����÷���

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
	BYTE                                              byMode;       // ������ �����÷���
	char                                              szCharName[26];// GM ĳ���� �̸�

} S_SCP_TRANSPARENCY_MODE_NOTIFY, * PS_SCP_TRANSPARENCY_MODE_NOTIFY;


// CSP_REQ_MOVE_POSITION : 0x2511
typedef struct _S_CSP_REQ_MOVE_POSITION
{
	short                                             snX;          // �����̵� X��ǥ
	short                                             snZ;          // �����̵� Z��ǥ
	BYTE                                              byY;          // �����̵��� �� ����

} S_CSP_REQ_MOVE_POSITION, * PS_CSP_REQ_MOVE_POSITION;


// SCP_RESP_MOVE_POSITION : 0xA511
typedef struct _S_SCP_RESP_MOVE_POSITION
{
	BYTE                                              byResult;     // Result Field
	short                                             snX;          // �����̵� X��ǥ
	short                                             snZ;          // �����̵� Z��ǥ
	BYTE                                              byY;          // �����̵��� �� ����

} S_SCP_RESP_MOVE_POSITION, * PS_SCP_RESP_MOVE_POSITION;


// CSP_REQ_MOVE_NEAR_CHAR : 0x2512
typedef struct _S_CSP_REQ_MOVE_NEAR_CHAR
{
	char                                              szCharName[26];// ��� ĳ���� �̸�

} S_CSP_REQ_MOVE_NEAR_CHAR, * PS_CSP_REQ_MOVE_NEAR_CHAR;


// SCP_RESP_MOVE_NEAR_CHAR : 0xA512
typedef struct _S_SCP_RESP_MOVE_NEAR_CHAR
{
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // �̵����� ����

} S_SCP_RESP_MOVE_NEAR_CHAR, * PS_SCP_RESP_MOVE_NEAR_CHAR;


// CSP_REQ_CHAR_RECALL : 0x2513
typedef struct _S_CSP_REQ_CHAR_RECALL
{
	char                                              szCharName[26];// ��� ĳ���� �̸�

} S_CSP_REQ_CHAR_RECALL, * PS_CSP_REQ_CHAR_RECALL;


// SCP_RESP_CHAR_RECALL : 0xA513
typedef struct _S_SCP_RESP_CHAR_RECALL
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// ��� ĳ���� �̸�

} S_SCP_RESP_CHAR_RECALL, * PS_SCP_RESP_CHAR_RECALL;


// CSP_CHAR_RECALL_NOTIFY : 0x2514
typedef struct _S_CSP_CHAR_RECALL_NOTIFY
{

} S_CSP_CHAR_RECALL_NOTIFY, * PS_CSP_CHAR_RECALL_NOTIFY;


// SCP_CHAR_RECALL_NOTIFY : 0xA514
typedef struct _S_SCP_CHAR_RECALL_NOTIFY
{
	char                                              szCharName[26];// ��� ĳ���� �̸�
	S_SCP_RESP_MOVE_PORTAL                            MoveInfo;     // �̵����� ����

} S_SCP_CHAR_RECALL_NOTIFY, * PS_SCP_CHAR_RECALL_NOTIFY;


// CSP_REQ_CONTROL_CHAT : 0x2521
typedef struct _S_CSP_REQ_CONTROL_CHAT
{
	char                                              szCharName[26];// ��� ĳ���� �̸�
	BYTE                                              byMode;       // �������

} S_CSP_REQ_CONTROL_CHAT, * PS_CSP_REQ_CONTROL_CHAT;


// SCP_RESP_CONTROL_CHAT : 0xA521
typedef struct _S_SCP_RESP_CONTROL_CHAT
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// ��� ĳ���� �̸�

} S_SCP_RESP_CONTROL_CHAT, * PS_SCP_RESP_CONTROL_CHAT;


// CSP_CONTROL_CHAT_NOTIFY : 0x2522
typedef struct _S_CSP_CONTROL_CHAT_NOTIFY
{

} S_CSP_CONTROL_CHAT_NOTIFY, * PS_CSP_CONTROL_CHAT_NOTIFY;


// SCP_CONTROL_CHAT_NOTIFY : 0xA522
typedef struct _S_SCP_CONTROL_CHAT_NOTIFY
{
	char                                              szCharName[26];// ��� ĳ���� �̸�
	BYTE                                              byMode;       // �������

} S_SCP_CONTROL_CHAT_NOTIFY, * PS_SCP_CONTROL_CHAT_NOTIFY;


// CSP_REQ_CONTROL_ACTION : 0x2531
typedef struct _S_CSP_REQ_CONTROL_ACTION
{
	char                                              szCharName[26];// ��� ĳ���� �̸�
	BYTE                                              byMode;       // �������

} S_CSP_REQ_CONTROL_ACTION, * PS_CSP_REQ_CONTROL_ACTION;


// SCP_RESP_CONTROL_ACTION : 0xA531
typedef struct _S_SCP_RESP_CONTROL_ACTION
{
	BYTE                                              byResult;     // Result Field
	char                                              szCharName[26];// ��� ĳ���� �̸�

} S_SCP_RESP_CONTROL_ACTION, * PS_SCP_RESP_CONTROL_ACTION;


// CSP_CONTROL_ACTION_NOTIFY : 0x2532
typedef struct _S_CSP_CONTROL_ACTION_NOTIFY
{

} S_CSP_CONTROL_ACTION_NOTIFY, * PS_CSP_CONTROL_ACTION_NOTIFY;


// SCP_CONTROL_ACTION_NOTIFY : 0xA532
typedef struct _S_SCP_CONTROL_ACTION_NOTIFY
{
	char                                              szCharName[26];// ��� ĳ���� �̸�
	BYTE                                              byMode;       // �������

} S_SCP_CONTROL_ACTION_NOTIFY, * PS_SCP_CONTROL_ACTION_NOTIFY;


// CSP_REQ_TROUBLE_REPORT : 0x2541
typedef struct _S_CSP_REQ_TROUBLE_REPORT
{
	char                                              szReport[512];// �Ű��� ����

} S_CSP_REQ_TROUBLE_REPORT, * PS_CSP_REQ_TROUBLE_REPORT;


// SCP_RESP_TROUBLE_REPORT : 0xA541
typedef struct _S_SCP_RESP_TROUBLE_REPORT
{
	BYTE                                              byResult;     // Result Field
	DWORD                                             dwIndex;      // ������ȣ

} S_SCP_RESP_TROUBLE_REPORT, * PS_SCP_RESP_TROUBLE_REPORT;


// CSP_REQ_TROUBLE_REPORT_LIST : 0x2542
typedef struct _S_CSP_REQ_TROUBLE_REPORT_LIST
{

} S_CSP_REQ_TROUBLE_REPORT_LIST, * PS_CSP_REQ_TROUBLE_REPORT_LIST;


// SCP_RESP_TROUBLE_REPORT_LIST : 0xA542
typedef struct _S_SCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // ������ �� �Ű��� ����
	BYTE                                              byCount;      // �������� �Ű��� ����

} S_SCP_RESP_TROUBLE_REPORT_LIST, * PS_SCP_RESP_TROUBLE_REPORT_LIST;


// CSP_REQ_TROUBLE_REPORT_SET : 0x2543
typedef struct _S_CSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ

} S_CSP_REQ_TROUBLE_REPORT_SET, * PS_CSP_REQ_TROUBLE_REPORT_SET;


// SCP_RESP_TROUBLE_REPORT_SET : 0xA543
typedef struct _S_SCP_RESP_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	BYTE                                              byProceed;    // ó����Ȳ

} S_SCP_RESP_TROUBLE_REPORT_SET, * PS_SCP_RESP_TROUBLE_REPORT_SET;


// GCSP_REQ_TROUBLE_REPORT_LIST : 0x2544
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_LIST
{
	int                                               nPage;        // �Ű���Ʈ ������

} S_GCSP_REQ_TROUBLE_REPORT_LIST, * PS_GCSP_REQ_TROUBLE_REPORT_LIST;


// GSCP_RESP_TROUBLE_REPORT_LIST : 0xA544
typedef struct _S_GSCP_RESP_TROUBLE_REPORT_LIST
{
	DWORD                                             dwCount;      // ������ �� �Ű��� ����
	BYTE                                              byCount;      // �������� �Ű��� ����

} S_GSCP_RESP_TROUBLE_REPORT_LIST, * PS_GSCP_RESP_TROUBLE_REPORT_LIST;


// GCSP_REQ_TROUBLE_REPORT_SET : 0x2545
typedef struct _S_GCSP_REQ_TROUBLE_REPORT_SET
{
	DWORD                                             dwIndex;      // ������ �߱޵Ǵ� ������ȣ
	BYTE                                              byProceed;    // ó����Ȳ
	char                                              szNote[256];  // ���

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
	int                                               nMaxHP;       // �ɸ��� HP�� �ִ밪
	int                                               nCurHP;       // �ɸ��� HP�� ���簪
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
	BYTE                                              byCount;      // ������������ ����

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
	char                                              szName[26];   // �ּҷϿ� �߰��� ĳ������ �̸�

} S_CSP_REQ_JOIN_ADDRESS_BOOK, * PS_CSP_REQ_JOIN_ADDRESS_BOOK;


// SCP_RESP_JOIN_ADDRESS_BOOK : 0xA603
typedef struct _S_SCP_RESP_JOIN_ADDRESS_BOOK
{
	BYTE                                              byResult;     // �ּҷϿ� ĳ�����߰� ��û���

} S_SCP_RESP_JOIN_ADDRESS_BOOK, * PS_SCP_RESP_JOIN_ADDRESS_BOOK;


// CSP_JOIN_ADDRESS_BOOK_NOTIFY : 0x2604
typedef struct _S_CSP_JOIN_ADDRESS_BOOK_NOTIFY
{

} S_CSP_JOIN_ADDRESS_BOOK_NOTIFY, * PS_CSP_JOIN_ADDRESS_BOOK_NOTIFY;


// SCP_JOIN_ADDRESS_BOOK_NOTIFY : 0xA604
typedef struct _S_SCP_JOIN_ADDRESS_BOOK_NOTIFY
{
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // �ּҷ� ����� ����

} S_SCP_JOIN_ADDRESS_BOOK_NOTIFY, * PS_SCP_JOIN_ADDRESS_BOOK_NOTIFY;


// CSP_REQ_JOIN_ADDRESS_BOOK_RESULT : 0x2605
typedef struct _S_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT
{
	BYTE                                              byResult;     // �ּҷϿ� ĳ�����߰� ��û���
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // �ּҷ� �߰��� ��û�� ĳ������ �̸�

} S_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT, * PS_CSP_REQ_JOIN_ADDRESS_BOOK_RESULT;


// SCP_RESP_JOIN_ADDRESS_BOOK_RESULT : 0xA605
typedef struct _S_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT
{
	BYTE                                              byResult;     // �ּҷ� �߰� ��û ���

} S_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT, * PS_SCP_RESP_JOIN_ADDRESS_BOOK_RESULT;


// CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY : 0x2606
typedef struct _S_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY
{

} S_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY, * PS_CSP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY;


// SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY : 0xA606
typedef struct _S_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY
{
	BYTE                                              byResult;     // �ּҷ� �߰� ��û�� ���� ���� ���
	S_ADDRESS_MEMBER_INFO                             MemberInfo;   // �ּҷ� �߰��� ��û�� ĳ������ �̸�

} S_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY, * PS_SCP_JOIN_ADDRESS_BOOK_RESULT_NOTIFY;


// CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE : 0x2607
typedef struct _S_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE
{
	char                                              szName[26];   // �ּҷϿ��� ������ ĳ������ �̸�

} S_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE, * PS_CSP_REQ_ADDRESS_BOOK_MEMBER_DELETE;


// SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE : 0xA607
typedef struct _S_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE
{
	BYTE                                              byResult;     // �ּҷϿ� �ִ� ĳ���� ������ ������û ���
	char                                              szName[26];   // �ּҷϿ��� ������ ĳ������ �̸�

} S_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE, * PS_SCP_RESP_ADDRESS_BOOK_MEMBER_DELETE;


// CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY : 0x2608
typedef struct _S_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY
{

} S_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY, * PS_CSP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY;


// SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY : 0xA608
typedef struct _S_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY
{
	char                                              szName[26];   // �ּҷϿ��� ������ ĳ������ �̸�

} S_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY, * PS_SCP_ADDRESS_BOOK_MEMBER_DELETE_NOTIFY;


// CSP_REQ_ADDRESS_BOOK_GROUP_ADD : 0x2611
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_ADD
{
	char                                              szGroup[26];  // �ּҷϿ� �߰��� �׷��� �̸�

} S_CSP_REQ_ADDRESS_BOOK_GROUP_ADD, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_ADD;


// SCP_RESP_ADDRESS_BOOK_GROUP_ADD : 0xA611
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_ADD
{
	BYTE                                              byResult;     // �׷��߰� ��û���
	char                                              szGroup[26];  // �ּҷϿ� �߰��� �׷��� �̸�

} S_SCP_RESP_ADDRESS_BOOK_GROUP_ADD, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_ADD;


// CSP_REQ_ADDRESS_BOOK_GROUP_DELETE : 0x2612
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE
{
	char                                              szGroup[26];  // �ּҷϿ� ������ �׷��� �̸�

} S_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_DELETE;


// SCP_RESP_ADDRESS_BOOK_GROUP_DELETE : 0xA612
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE
{
	BYTE                                              byResult;     // �׷���� ��û���
	char                                              szGroup[26];  // �ּҷϿ� ������ �׷��� �̸�

} S_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_DELETE;


// CSP_REQ_ADDRESS_BOOK_GROUP_MOVE : 0x2613
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE
{
	char                                              szGroup[26];  // �̵��� �׷��� �̸�
	char                                              szName[26];   // �̵��� �ɸ����� �̸�

} S_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_MOVE;


// SCP_RESP_ADDRESS_BOOK_GROUP_MOVE : 0xA613
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE
{
	BYTE                                              byResult;     // �׷��̵��� ���� ó�����
	char                                              szName[26];   // �̵��� �ɸ����� �̸�

} S_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_MOVE;


// CSP_REQ_ADDRESS_BOOK_GROUP_RENAME : 0x2614
typedef struct _S_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME
{
	char                                              szSourceGroup[26];// �̸��� ������ �׷��� �̸� - Source
	char                                              szTargetGroup[26];// �����ϰ��� �ϴ� �׷��� �̸� - Target

} S_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME, * PS_CSP_REQ_ADDRESS_BOOK_GROUP_RENAME;


// SCP_RESP_ADDRESS_BOOK_GROUP_RENAME : 0xA614
typedef struct _S_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME
{
	BYTE                                              byResult;     // �׷��̸����濡 ���� ó�����
	char                                              szGroup[26];  // �̸��� ����� �׷��� �̸� - Source

} S_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME, * PS_SCP_RESP_ADDRESS_BOOK_GROUP_RENAME;


// CSP_REQ_ADDRESS_BOOK_STATUS : 0x2621
typedef struct _S_CSP_REQ_ADDRESS_BOOK_STATUS
{
	BYTE                                              byResult;     // ��ϰźλ��¸� �����Ѵ�.

} S_CSP_REQ_ADDRESS_BOOK_STATUS, * PS_CSP_REQ_ADDRESS_BOOK_STATUS;


// SCP_RESP_ADDRESS_BOOK_STATUS : 0xA621
typedef struct _S_SCP_RESP_ADDRESS_BOOK_STATUS
{
	BYTE                                              byResult;     // �ּҷ� ��Ͽ�û�� ó�����

} S_SCP_RESP_ADDRESS_BOOK_STATUS, * PS_SCP_RESP_ADDRESS_BOOK_STATUS;


// GCSP_REQ_CHARACTER_SEARCH : 0x2547
typedef struct _S_GCSP_REQ_CHARACTER_SEARCH
{
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ������ ĳ���� �̸�
	char                                              szAccountID[18];// ������ ���� ���̵�

} S_GCSP_REQ_CHARACTER_SEARCH, * PS_GCSP_REQ_CHARACTER_SEARCH;


// GSCP_INIT_CHAR : 0xA547
typedef struct _S_GSCP_INIT_CHAR
{
	BYTE                                              byResult;     // �ʱ�ȭ ���
	char                                              szCharName[26];
	char                                              szAccountID[18];
	BYTE                                              byRegion;     // �ɸ����� Region ��ġ
	BYTE                                              byZone;       // �ɸ����� Zone ��ġ
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
	int                                               nPrana;       // �� ������ ��
	int                                               nCurHP;       // �ɸ��� HP�� ���簪
	int                                               nMoney;       // ĳ���Ͱ� ���� ������ �ִ� ��

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
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ������ ĳ���� �̸�
	char                                              szAccountID[18];// ������ ���� ���̵�
	BYTE                                              byType;       // �����ϰ��� �ϴ� �Ķ���� �ʵ�
	int                                               byValues;     // �����ϰ��� �ϴ� ��

} S_GCSP_REQ_PARAMETER_CHANGE, * PS_GCSP_REQ_PARAMETER_CHANGE;


// GSCP_RESP_PARAMETER_CHANGE : 0xA550
typedef struct _S_GSCP_RESP_PARAMETER_CHANGE
{
	BYTE                                              byResult;     // ���� ���� ���

} S_GSCP_RESP_PARAMETER_CHANGE, * PS_GSCP_RESP_PARAMETER_CHANGE;


// GCSP_REQ_ITEM_INSERT : 0x2551
typedef struct _S_GCSP_REQ_ITEM_INSERT
{
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ĳ���� �̸�
	char                                              szAccountID[18];// ���� ���̵�
	DWORD                                             dwIndex;      // �߰��Ϸ��� ������ �ε���
	BYTE                                              byPlace;      // �߰� �Ϸ��� ������ ��ġ
	BYTE                                              bySlot;       // Slot Number
	BYTE                                              byX;          // X ��ǥ
	BYTE                                              byZ;          // Z ��ǥ

} S_GCSP_REQ_ITEM_INSERT, * PS_GCSP_REQ_ITEM_INSERT;


// GSCP_RESP_ITEM_INSERT : 0xA551
typedef struct _S_GSCP_RESP_ITEM_INSERT
{
	BYTE                                              byResult;     // ������ ���� ���

} S_GSCP_RESP_ITEM_INSERT, * PS_GSCP_RESP_ITEM_INSERT;


// GCSP_REQ_ITEM_DELETE : 0x2552
typedef struct _S_GCSP_REQ_ITEM_DELETE
{
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ĳ���� �̸�
	char                                              szAccountID[18];// ���� ���̵�
	DWORD                                             dwIndex;      // �����Ϸ��� ������ �ε���
	BYTE                                              byPlace;      // �����Ϸ��� ������ ��ġ
	BYTE                                              bySlot;       // Slot Number
	BYTE                                              byX;          // X ��ǥ
	BYTE                                              byZ;          // Z ��ǥ

} S_GCSP_REQ_ITEM_DELETE, * PS_GCSP_REQ_ITEM_DELETE;


// GSCP_RESP_ITEM_DELETE : 0xA552
typedef struct _S_GSCP_RESP_ITEM_DELETE
{
	BYTE                                              byResult;     // ������ ���� ���

} S_GSCP_RESP_ITEM_DELETE, * PS_GSCP_RESP_ITEM_DELETE;


// GCSP_REQ_SKILL_INSERT : 0x2553
typedef struct _S_GCSP_REQ_SKILL_INSERT
{
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ĳ���� �̸�
	char                                              szAccountID[18];// ���� ���̵�
	DWORD                                             dwIndex;      // �߰��Ϸ��� ��ų �ε���
	BYTE                                              byLevel;      // �߰��Ϸ��� ��ų �ε���

} S_GCSP_REQ_SKILL_INSERT, * PS_GCSP_REQ_SKILL_INSERT;


// GSCP_RESP_SKILL_INSERT : 0xA553
typedef struct _S_GSCP_RESP_SKILL_INSERT
{
	BYTE                                              byResult;     // ��ų ���� ���

} S_GSCP_RESP_SKILL_INSERT, * PS_GSCP_RESP_SKILL_INSERT;


// GCSP_REQ_SKILL_DELETE : 0x2554
typedef struct _S_GCSP_REQ_SKILL_DELETE
{
	BYTE                                              byWorldNo;    // ĳ���Ͱ� ��ġ�� �����ȣ
	char                                              szCharName[26];// ĳ���� �̸�
	char                                              szAccountID[18];// ���� ���̵�
	DWORD                                             dwIndex;      // �����Ϸ��� ��ų �ε���

} S_GCSP_REQ_SKILL_DELETE, * PS_GCSP_REQ_SKILL_DELETE;


// GSCP_RESP_SKILL_DELETE : 0xA554
typedef struct _S_GSCP_RESP_SKILL_DELETE
{
	BYTE                                              byResult;     // ��ų ���� ���

} S_GSCP_RESP_SKILL_DELETE, * PS_GSCP_RESP_SKILL_DELETE;



#pragma pack(pop)

#endif // __PROTOCOL_MESSAGE_STRUCT_H__
