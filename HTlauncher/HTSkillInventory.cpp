

#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTSkillInventory.h"

// 서버 요청 단계
#define SERVER_MSG_NONE						0
#define SERVER_MSG_REQ_SKILL_UP				1

// 메세지창 0:메세지창안뜸,1:작업완료,2:작업재확인
#define SKILL_MESSAGE_NONE				0
#define SKILL_MESSAGE_COMPLETE			1	
#define SKILL_MESSAGE_CONFIRM			2

#define SKILLINVENTORY_ICONCELLTERM		52
#define SKILLINVENTORY_CELLCORRECT		3

//	Skill Inventory SkillIcon Cell No
HTint g_iSkillInventory_SkillIconCellNo[10] = { 52, 53, 54, 55, 56, 57, 58, 59, 60, 61 };
//HTint g_iSkillInventory_SkillIconCellNo[10] = { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 };
//	Skill Inventory SkillIcon Cell No
HTint g_iSkillInventory_SkillLevelCellNo[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	Skill Inventory SkillName Cell No
HTint g_iSkillInventory_SkillNameCellNo[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
//	Skill Inventory Skillexplain Cell No
HTint g_iSkillInventory_SkillexplainCellNo[10] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

//	Skill Inventory SkillPoint Cell No
#define SKILL_SKILLPOINT				0
//	Skill Inventory TrimuritiSkillPoint Cell No
#define SKILL_TRIMURITISKILLPOINT		1

//---------------------------------------------------------------------------------------------------------
//	배열 순서 : Skill 그림번호, 화살표위치, 데이타 인덱스_1 이 순서로 각 텝마다 하나씩 3개
// 23830 아래화살표, 23592 4개짜리 화살표, 23832 3개짜리 화살표, 23831 2개짜리 화살표, 23881 5개짜리 화살표
// <나가/킨나라> 기본 스킬 배열 
HTint _NAGA_1[6][4] = 
{ 
		23483,	23716,	23737,	0,
		23739,	0,		23735,	0,
		23874,	0,		23736,	0,
		23774,	23797,	0,		0,
		23794,	23865,	23491,	0,
		0,		0,		0,		0,
}; 

HTint _NAGAARROW_1[6][4] = 
{
		23830,	0,		0,		0,
		23830,	0,		0,		0,
		23831,	0,		0,		0,
		23832,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_1[6][4] = 
{
		3001,	3008,	3004,	0,			//	발루카,			바루나포스,		프라자스로카,	0,
		3026,	0,		3006,	0,			//	아마다카스,		0,				다라로카,		0,
		3041,	0,		3005,	0,			//	가타나,			0,				토마리로카,		0,
		3007,	3027,	0,		0,			//	발루카만트라,	프리베자,		0,				0,
		3043,	3021,	3061,	0,			//	나우티,			스탐,			부우캄파,		0,
		0,		0,		0,		0,			//	0,				0,				0,				0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _NAGA_2[6][4] = 
{
		0,		23741,	23710,	0,
		0,		23486,	23742,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_2[6][4] = 
{
		0,		23830,	23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_2[6][4] = 
{
		0,		3002,	3042,	0,			//	0,		타누트라,		사비트리포스,		0,
		0,		3003,	3022,	0,			//	0,		바다테,			사마테,				0,
		0,		0,      0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _NAGA_3[6][4] = 
{
		23792,	23723,	23484,	0,
		0,		23790,	23743,	0,
		0,		23785,	23789,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_3[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_3[6][4] = 
{
		3010,	3024,	3023,	0,			//	0,		쿤달리니라이징,		프로스아나,			0,
		0,		3009,	3028,	0,			//	0,		타르카,				프로스아나바티아,	0,
		0,		3030,	3029,	0,			//	0,		마야트,				아자카,				0,
		0,		0,		0,		0,			//	0,		0,					0,					0,
		0,		0,		0,		0,			//	0,		0,					0,					0,
		0,		0,		0,		0,			//	0,		0,					0,					0,
};

// <나가/킨나라> 2차 전직 - [바나르] 스킬 배열
HTint _NAGA_1_1[6][4] = 
{
		23483,	0,		23716,	23737,
		23739,	0,		22655,	23735,	// 3 번째 추가 됨 22655
		23874,	23607,	22638,	23736,	// 3 번째 추가 됨 22638
		23774,	23797,	0,		23477,
		23794,	23865,	23491,	0,
		0,		23524,		0,		0,
};

HTint _NAGAARROW_1_1[6][4] = 
{
		23830,	0,		0,		0,
		23831,	0,		0,		0,
		23831,	0,		0,		0,
		23832,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_1_1[6][4] = 
{
		3001,	0,		3008,	3004,		//	발루카,			0,				바루나포스,		프라자스로카,
		3026,	0,		3059,	3006,		//	아마다카스,		0,				(0)우타,		다라로카,		
		3041,	3011,	3060,	3005,		//	가타나,			비즈사이,		(0)프라티야,	토마리로카,
		3007,	3027,	0,		3097,		//	발루카만트라,	프리베자,		0,				프라하스타로카,
		3043,	3021,	3061,	0,			//	나우티,			스탐,			부우캄파,		0,
		0,		3019,		0,		0,			//	0,				0,				0,				0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _NAGA_1_2[6][4] = 
{
		0,		23741,	23710,	0,
		0,		23486,	23742,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_1_2[6][4] = 
{
		0,		23830,	23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_1_2[6][4] = 
{
		0,		3002,	3042,	0,			//	0,		타누트라,		사비트리포스,		0,
		0,		3003,	3022,	0,			//	0,		바다테,			사마테,				0,
		0,		0,      0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _NAGA_1_3[6][4] = 
{
		23792,	23723,	23484,	0,
		23795,	23790,	23743,	0,
		23822,		23785,	23789,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_1_3[6][4] = 
{
		23830,	23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_1_3[6][4] = 
{
		3010,	3015,	3023,	0,			//	야카트,		쿤달리니라이징,		프로스아나,			0,
		3025,	3009,	3028,	0,			//	아로카킨,	타르카,				프로스아나바티아,	0,
		3014,		3030,	3029,	0,			//	0,			마야트,				아자카,				0,
		0,		0,		0,		0,			//	0,			0,					0,					0,
		0,		0,		0,		0,			//	0,			0,					0,					0,
		0,		0,		0,		0,			//	0,			0,					0,					0,
};

// <나가/킨나라> 2차 전직 - [사트야] 스킬 배열
HTint _NAGA_2_1[6][4] = 
{
		23483,	0,		23716,	23737,
		23739,	0,		22653,	23735,		// 3번째 추가 22653
		23874,	0,		0,		23736,
		23774,	23797,	0,		0,
		23794,	23865,	23491,	23472,
		0,		23520,		0,		0,
};

HTint _NAGAARROW_2_1[6][4] = 
{
		23830,	0,		0,		0,
		23830,	0,		0,		0,
		23831,	0,		0,		0,
		23592,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_2_1[6][4] = 
{
		3001,	0,		3008,	3004,			//	발루카,			0,				바루나포스,		프라자스로카
		3026,	0,		3058,	3006,			//	아마다카스,		0,				(0)카틴,		다라로카,
		3041,	0,		0,		3005,			//	가타나,			0,				0,				토마리로카,
		3007,	3027,	0,		0,				//	발루카만트라,	프리베자,		0,				0,
		3043,	3021,	3017,	3012,			//	나우티,			스탐,			부우캄파,		야마카,
		0,		3033,		0,		0,				//	0,				0,				0,				0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _NAGA_2_2[6][4] = 
{
		0,		23741,	22607,	23823,
		0,		23486,	22606,	0,
		0,		23888,	23886,	0,
		0,		23799,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_2_2[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_2_2[6][4] = 
{
		0,		3002,	3096,	3016,			//	0,		타누트라,		사비트리포스,		0,
		0,		3003,	3098,	0,			//	0,		바다테,			사마테,				0,
		0,		3099,   3031,	0,			//	0,		락스로카,		우마사마테			0,
		0,		3032,	0,		0,			//	0,		카르만,			0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
		0,		0,		0,		0,			//	0,		0,				0,					0,
};
//	나가 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _NAGA_2_3[6][4] = 
{
		23792,	23723,	23484,	0,
		0,		23790,	23743,	0,
		0,		23785,	23789,	22640,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGAARROW_2_3[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23831,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _NAGASKILLINDEX_2_3[6][4] = 
{
		3010,	3024,	3023,	0,			//	0,		쿤달리니라이징,		프로스아나,			0,
		0,		3009,	3028,	0,			//	0,		타르카,				프로스아나바티아,	0,
		0,		3030,	3029,	3013,		//	0,		마야트,				아자카,				(0)그라브,
		0,		0,		0,		0,			//	0,		0,					0,					0,
		0,		0,		0,		0,			//	0,		0,					0,					0,
		0,		0,		0,		0,			//	0,		0,					0,					0,
};

// <아수라/라크샤사> 기본 스킬 배열 
HTint _ASURA_1[6][4] = 
{
		23735,	23713,	23800,	0,
		0,		23728,	0,		0,
		0,		23744,	0,		0,
		0,		23730,	23727,	0,
		0,		0,		23469,	0,
		0,		0,		0,		0,
};

HTint _ASURAARROW_1[6][4] = 
{
		0,		23830,	0,		0,
		0,		23830,	0,		0,
		0,		23831,	0,		0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_1[6][4] = 
{
		3105,	3124,	3106,	0,			//	다라로카,	베가,		나카라로카,		0,
		0,		3142,	0,		0,			//	0,			바이라바,	0,				0,
		0,		3141,	0,		0,			//	0,			캄파테,		0,				0,
		0,		3127,	3126,	0,			//	0,			비사타루,	누다티,			0,
		0,		0,		3161,	0,			//	0,			0,			안타카라,		0,
		0,		0,		0,		0,			//	0,			0,			0,				0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _ASURA_2[6][4] = 
{
		23791,	0,		0,		0,
		23616,	0,		0,		0,
		23732,	23776,	23786,	0,
		23783,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURAARROW_2[6][4] = 
{
		23830,	0,		0,		0,
		23832,	0,		0,		0,
		23830,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_2[6][4] = 
{
		3108,	0,		0,		0,			//	아타니로카,		0,				0,			0,
		3128,	0,		0,		0,			//	사카다라다,		0,				0,			0,
		3143,	3129,	3130,	0,			//	만트라카,		히마라다,		비사라다,	0,
		3162,	0,		0,		0,			//	프라니카,		0,				0,			0,
		0,		0,		0,		0,			//	0,				0,				0,			0,
		0,		0,		0,		0,			//	0,				0,				0,			0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _ASURA_3[6][4] = 
{
		23868,	23712,	23490,	0,
		23896,	23731,	0,		0,
		23897,	23605,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};

HTint _ASURAARROW_3[6][4] = 
{
		23830,	23830,	0,		0,
		23830,	23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_3[6][4] = 
{
		3101,	3121,	3122,	0,			//	스프리카,		타라스,		챠야,		0,
		3102,	3103,	0,		0,			//	파라카,			얀카나,		0,			0,
		3110,	3144,	0,		0,			//	파라카마나,		로카나,		0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
};

// <아수라/라크샤사> 2차 전직 - [카르야] 스킬 배열 
HTint _ASURA_1_1[6][4] = 
{
		23735,	23713,	23800,	0,
		0,		23728,	0,		0,
		0,		23744,	0,		0,
		0,		23730,	23727,	0,
		0,		0,		23469,	0,
		0,		0,		0,		0,
};

HTint _ASURAARROW_1_1[6][4] = 
{
		0,		23830,	0,		0,
		0,		23830,	0,		0,
		0,		23831,	0,		0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_1_1[6][4] = 
{
		3105,	3124,	3106,	0,			//	다라로카,	베가,		나카라로카,		0,
		0,		3142,	0,		0,			//	0,			바이라바,	0,				0,
		0,		3141,	0,		0,			//	0,			캄파테,		0,				0,
		0,		3127,	3126,	0,			//	0,			비사타루,	누다티,			0,
		0,		0,		3161,	0,			//	0,			0,			안타카라,		0,
		0,		0,		0,		0,			//	0,			0,			0,				0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _ASURA_1_2[6][4] = 
{
		23791,	0,		0,		0,
		23616,	23479,	0,		0,
		23732,	23776,	23786,	23471,
		23783,	22650,	0,		0,
		23878,	23824,		0,		0,
		22643,	23825,		0,		0,
};
HTint _ASURAARROW_1_2[6][4] = 
{
		23831,	0,		0,		0,
		23592,	0,		0,		0,
		23831,	0,		0,		0,
		23830,	0,		0,		0,
		23830,	0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_1_2[6][4] = 
{
		3108,	0,		0,		0,			//	아타니로카,		0,				0,			0,
		3128,	3111,	0,		0,			//	사카다라다,		라마스,			0,			0,
		3143,	3129,	3130,	3109,		//	만트라카,		히마라다,		비사라다,	이린티리카,
		3162,	3117,	0,		0,			//	프라니카,		(0)나스,		0,			0,
		3112,	3118,		0,		0,			//	자마티리카,		0,				0,			0,
		3116,	3119,		0,		0,			//	(0)사마요가,	0,				0,			0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _ASURA_1_3[6][4] = 
{
		23868,	23712,	23490,	22601,
		23896,	23731,	0,		0,
		23897,	23605,	0,		0,
		0,		23522,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};

HTint _ASURAARROW_1_3[6][4] = 
{
		23830,	23830,	0,		0,
		23830,	23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_1_3[6][4] = 
{
		3101,	3121,	3122,	3115,		//	스프리카,		타라스,		차야,	늑대소환,
		3102,	3103,	0,		0,			//	파라카,			얀카나,		0,			0,
		3110,	3144,	0,		0,			//	파라카마나,		로카나,		0,			0,
		0,		3146,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
};

// <아수라/라크샤사> 2차 전직 - [드루카] 스킬 배열 
HTint _ASURA_2_1[6][4] = 
{
		23713,	0,		0,		23735,
		23728,	23609,	0,		23800,
		23744,	0,		0,		23889,
		23727,	23730,	0,		0,
		23469,	23470,	23604,	0,
		0,		22651,	0,		0,
};

HTint _ASURAARROW_2_1[6][4] = 
{
		23831,	0,		0,		0,
		23830,	0,		0,		0,
		23831,	0,		0,		0,
		23832,	23830,	0,		0,
		0,		23830,	0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_2_1[6][4] = 
{
		3124,	0,		0,		3105,		//	베가,		0,			0,				다라 로카,
		3142,	3107,	0,		3106,		//	바이라바,	디반다,		0,				나카라 로카,
		3141,	0,		0,		3199,		//	캄파테,		0,			0,				드바이라다 로카,
		3126,	3127,	0,		0,			//	누다티,		비사타루,	0,				0,
		3161,	3113,	3104,	0,			//	안타카라,	아굽타,		암비카비자티	0,
		0,		3160,	0,		0,			//	0,			(0)아킬라,	0,				0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _ASURA_2_2[6][4] = 
{
		23791,	0,		0,		0,
		23616,	0,		0,		0,
		23732,	23776,	23786,	0,
		23783,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURAARROW_2_2[6][4] = 
{
		23830,	0,		0,		0,
		23832,	0,		0,		0,
		23830,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_2_2[6][4] = 
{
		3108,	0,		0,		0,			//	아타니로카,		0,				0,			0,
		3128,	0,		0,		0,			//	사카다라다,		0,				0,			0,
		3143,	3129,	3130,	0,			//	만트라카,		히마라다,		비사라다,	0,
		3162,	0,		0,		0,			//	프라니카,		0,				0,			0,
		0,		0,		0,		0,			//	0,				0,				0,			0,
		0,		0,		0,		0,			//	0,				0,				0,			0,
};
//	아수라 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _ASURA_2_3[6][4] = 
{
		23868,	23712,	0,		23490,
		23896,	23731,	23879,	0,
		23897,	23605,	0,		0,
		22654,	0,		0,		0,
		23525,		0,		0,		0,
		0,		0,		0,		0,
};

HTint _ASURAARROW_2_3[6][4] = 
{
		23830,	23831,	0,		0,
		23830,	23830,	0,		0,
		23830,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _ASURASKILLINDEX_2_3[6][4] = 
{
		3101,	3121,	0,		3122,		//	스프리카,		타라스,		0,			차야,
		3102,	3103,	3114,	0,			//	파라카,			얀카나,		쥬바스,		0,
		3110,	3144,	0,		0,			//	파라카마나,		로카나,		0,			0,
		3159,	0,		0,		0,			//	(0)사누타,		0,			0,			0,
		3145,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
};

// <야크샤/간다르바> 기본 스킬 배열 
HTint _YAKSA_1[6][4] = 
{
		23752,	23716,	23738,	0,
		23719,	23717,	23782,	0,
		23749,	23619,	0,		0,
		0,		23709,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_1[6][4] = 
{
		23830,	23830,	23830,	0,
		23830,	23830,	0,		0,
		0,		23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_1[6][4] = 
{
		3201,	3203,	3205,	0,		//	바즈라무스티,	바루나포스,		가나로카,		0,
		3226,	3222,	3227,	0,		//	바즈라만타라,	비사크로,		타파스아사라,	0,
		3245,	3202,	0,		0,		//	스푸라아사라,	프라파드,		0,				0,
		0,		3224,	0,		0,		//	0,				아사라,			0,				0,
		0,		0,		0,		0,		//	0,				0	,			0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _YAKSA_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_2[6][4] = 
{
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,  0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _YAKSA_3[6][4] = 
{
		23487,	23714,	23726,	0,
		23718,	23772,	0,		0,
		23722,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_3[6][4] = 
{
		0,	23830,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_3[6][4] = 
{
		3208,	3242,	3228,	0,		//	바사티,			만트라쉴드,		로하티,
		3221,	3243,	0,		0,		//	스칸다퓨리,		만트라스킨,		0,
		3229,	0,		0,		0,		//	인드라잘라,			0,			0,
		0,		0,		0,		0,		//	0,					0,			0,
		0,		0,		0,		0,		//	0,					0,			0,
		0,		0,		0,		0,		//	0,					0,			0,
};

// (나카유다)
HTint _YAKSA_1_1[6][4] = 
{
		23752,	23716,	23738,	23880,
		23719,	23717,	23782,	22649,
		23749,	23619,	23777,	0,
		23618,	23709,	0,		0,
		0,		23753,	0,		0,
		0,		23523,		0,		0,
};
HTint _YAKSAARROW_1_1[6][4] = 
{
		23830,	23830,	23830,	23830,
		23830,	23830,	23830,	0,
		23830,	23830,	0,		0,
		0,		23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_1_1[6][4] = 
{
		3201,	3203,	3205,	3209,	//	바즈라무스티,	바루나포스,		가나로카,		사아타,
		3226,	3222,	3227,	3257,	//	바즈라만타라,	비사크로,		타파스아사라,	(0)자무스,
		3245,	3202,	3262,	0,		//	스푸라아사라,	프라파드,		자나티파라,		0,
		3206,	3224,	0,		0,		//	파우바파르야,	아사라,			0,				0,
		0,		3225,	0,		0,		//	0,				티아자티,		0,				0,
		0,		3264,		0,		0,		//	0,				0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _YAKSA_1_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_1_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_1_2[6][4] = 
{
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,  0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_3 
HTint _YAKSA_1_3[6][4] = 
{
		23898,	23714,	23726,	0,
		23881,	23772,	22641,	0,
		23722,	23877,	0,		0,
		23475,	0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_1_3[6][4] = 
{
		0,	23830,		0,		0,
		0,	23830,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_1_3[6][4] = 
{
		3298,	3242,	3228,	0,		//	바사티P,		만트라쉴드,		로하티,
		3299,	3243,	3256,	0,		//	스칸다퓨리P,	만트라스킨,		(0)자하티,
		3229,	3217,	0,		0,		//	인드라잘라,		부카자마,		0,
		3297,	0,		0,		0,		//	외공연마,			0,			0,
		0,		0,		0,		0,		//	0,					0,			0,
		0,		0,		0,		0,		//	0,					0,			0,
};

// (바이드야)
HTint _YAKSA_2_1[6][4] = 
{
		23752,	23716,	23738,	0,
		23719,	23717,	23782,	0,
		23749,	23619,	22642,	0,
		0,		23709,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_2_1[6][4] = 
{
		23830,	23830,	23830,	0,
		23830,	23830,	23830,	0,
		0,		23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_2_1[6][4] = 
{
		3201,	3203,	3205,	0,		//	바즈라무스티,	바루나포스,		가나로카,		0,
		3226,	3222,	3227,	0,		//	바즈라만타라,	비사크로,		타파스아사라,	0,
		3245,	3202,	3259,	0,		//	스푸라아사라,	프라파드,		(0)니크르티,	0,
		0,		3224,	0,		0,		//	0,				아사라,			0,				0,
		0,		0,		0,		0,		//	0,				0	,			0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_2
HTint _YAKSA_2_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSAARROW_2_2[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_2_2[6][4] = 
{
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,  0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
};
//	야크샤 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _YAKSA_2_3[6][4] = 
{
		23487,	23714,	23481,	23779,
		23718,	23772,	23762,	23770,
		23722,	23606,	23826,	23777,
		22644,	23875,	23775,	0,
		0,		0,		23756,		0,
		0,		0,		23827,		0,
};
HTint _YAKSAARROW_2_3[6][4] = 
{
		0,	23830,	23830,	23830,
		0,	23830,		0,		0,
		0,	23830,	    0,		0,
		0,		0,	23830,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _YAKSASKILLINDEX_2_3[6][4] = 
{
		3204,	3218,	3211,	3244,	//	바사티,			만트라쉴드,		로하티,				자사트,
		3214,	3219,	3212,	3230,	//	스칸다퓨리,		만트라스킨,		로하티수사르바,		구나자사트,
		3215,	3241,	3246,	3263,		//	인드라잘라,		카도라이,		사무다바,			0,	
		3258,	3210,	3261,	0,		//	(0)세니야,		칼라티,			비사이야사르바나,	0,
		0,		0,		3213,		0,		//	0,				0,				0,					0,
		0,		0,		3247,		0,		//	0,				0,				0,					0,
};

// <데바/가루다> 기본 스킬 배열
HTint _DEVA_1[6][4] = 
{
		0,		23866,	23733,	0,
		0,		23748,	23787,	0,
		0,		23892,	23754,	0,
		0,		23746,	23758,	0,
		0,		0,		23729,	0,
		0,		0,		23745,	0, //self add fors_debug
};

HTint _DEVAARROW_1[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		23830,	0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_1[6][4] = 
{
		0,		3301,	3315,	0,		//	0,	만트라,			아그니,			0,
		0,		3321,	3316,	0,		//	0,	라하리만트라,	아그니구나,		0,
		0,		3303,	3327,	0,		//	0,	아니라하티,		아그니토마라,	0,
		0,		3326,	3324,	0,		//	0,	마하바타,		아그니수나,		0,
		0,		0,		3306,	0,		//	0,	0,				라라마,			0,
		0,		0,		3341,	0,		//	0,	0,				아그니레스만,	0, fors_debug self_add
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_2
// 업데이트될
HTint _DEVA_2[6][4] = 
{
		0,		23721,	0,		0,
		0,		23759,	23768,	0,
		0,		23755,	23784,	0,
		0,		23798,	23769,	0,
		0,		0,		23489,	0,
		0,		0,		0,		0,
};

HTint _DEVAARROW_2[6][4] = 
{
		0,		23830,	0,		0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_2[6][4] = 
{
		0,		3304,	0,		0,		//	0,	히마,			0,				0,
		0,		3317,	3305,	0,		//	0,	히마구나,		루,				0,
		0,		3322,	3318,	0,		//	0,	히마바티아,		루구나,			0,
		0,		3343,	3323,	0,		//	0,	히마레스만,		라우티,			0,
		0,		0,		3361,	0,		//	0,	0,				라우티바티아,	0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _DEVA_3[6][4] = 
{
		23761,	23720,	23485,	0,
		23605,	23493,	23492,	0,
		0,		0,		23521,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVAARROW_3[6][4] = 
{
		0,		23830,	23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_3[6][4] = 
{
		3310,	3302,	3309,	0,			//	무쿠타로카,		아바리,			스프타,			0,
		3314,	3311,	3329,	0,			//	로카나,			자나티로카,		스프타레스만,	0,
		0,		0,		3313,	0,			//	0,				0,				0,				0,
		0,		0,		0,		0,			//	0,				0,				0,				0,
		0,		0,		0,		0,			//	0,				0,				0,				0,
		0,		0,		0,		0,			//	0,				0,				0,				0,
};

// <데바/가루다> 2차 전직 - [아비카라] 스킬 배열, 원소(공격) 법사
HTint _DEVA_1_1[6][4] = 
{
		0,		23866,	23733,	23529,
		0,		23748,	23787,	0,
		0,		23892,	23754,	0,
		0,		23746,	23758,	0,
		0,		23617,	23729,	22647,
		0,		0,		23745,	23828, //fors_debug oh yeah is 3335 skillid 1100115
};

HTint _DEVAARROW_1_1[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		23830,	0,
		0,		0,		23830,	0,
		0,		0,		23830,	0,
};
HTint _DEVASKILLINDEX_1_1[6][4] = 
{
		0,		3301,	3315,	3397,	//	0,	만트라,			아그니,		아그니 사나다,
		0,		3321,	3316,	0,		//	0,	라하리만트라,	아그니구나,		0,
		0,		3303,	3327,	0,		//	0,	아니라하티,		아그니토마라,	0,
		0,		3326,	3324,	0,		//	0,	마하바타,		아그니수나,		0,
		0,		3307,	3306,	3334,		//	0,	자크티			라라마,			0,
		0,		0,		3341,	3335,	//	0,	0,				아그니레스만,	(0)바르타테,
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_2
// 업데이트될
HTint _DEVA_1_2[6][4] = 
{
		23721,	23530,	0,		0,
		23759,	0,		23768,	23531,
		23755,	0,		23784,	0,
		23798,	23611,	23769,	0,
		0,		0,		23489,	23870,
		0,		0,		22645,	0,
};

HTint _DEVAARROW_1_2[6][4] = 
{
		23830,	0,		0,		0,
		23830,	0,		23830,	0,
		23831,	0,		23830,	0,
		0,		0,		23831,	0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_1_2[6][4] = 
{
		3304,	3398,	0,		0,		//	히마,			히마 사나다,	0,				0,
		3317,	0,		3305,	3399,	//	히마구나,		0,				루,				루 사나다,
		3322,	0,		3318,	0,		//	히마바티아,		0,				루구나,			0,
		3343,	3312,	3323,	0,		//	히마레스만,		히마티리카		라우티,			0,
		0,		0,		3361,	3308,	//	0,				0,				라우티바티아,	시드하루,
		0,		0,		3333,		0,		//	0,				0,				(0)수가마,		0,
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _DEVA_1_3[6][4] = 
{
		23761,	23720,	0,		23485,
		23605,	23493,	0,		23492,
		0,		0,		0,		23521,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVAARROW_1_3[6][4] = 
{
		0,		23830,	0,		23830,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_1_3[6][4] = 
{
		3310,	3302,	0,		3309,		//	무쿠타로카,	아바리,			0,			스프타,
		3314,	3311,	0,		3329,		//	로카나,		자나티로카,		0,			스프타레스만,
		0,		0,		0,		3313,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
		0,		0,		0,		0,			//	0,				0,			0,			0,
};

// <데바/가루다> 2차 전직 - [사마바트] 스킬 배열, 소환법사
HTint _DEVA_2_1[6][4] = 
{
		0,		23866,	23733,	0,
		0,		23748,	23787,	0,
		0,		23892,	23754,	0,
		0,		23746,	23758,	0,
		0,		23608,	23729,	0,
		0,		0,		23745,	0,//fors_debug self add
};

HTint _DEVAARROW_2_1[6][4] = 
{
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_2_1[6][4] = 
{
		0,		3301,	3315,	0,		//	0,	만트라,			아그니,			0,
		0,		3321,	3316,	0,		//	0,	라하리만트라,	아그니구나,		0,
		0,		3303,	3327,	0,		//	0,	아니라하티,		아그니토마라,	0,
		0,		3326,	3324,	0,		//	0,	마하바타,		아그니수나,		0,
		0,		3325,	3306,	0,		//	0,	데스티,			라라마,			0,
		0,		0,		3341,	0,		//	0,	0,				아그니레스만,	0,  fors_debug self_add
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_2
// 업데이트될 
HTint _DEVA_2_2[6][4] = 
{
		0,		23721,	0,		0,
		0,		23759,	23768,	0,
		0,		23755,	23784,	0,
		0,		23798,	23769,	0,
		0,		0,		23489,	0,
		0,		0,		0,		0,
};

HTint _DEVAARROW_2_2[6][4] = 
{
		0,		23830,	0,		0,
		0,		23830,	23830,	0,
		0,		23830,	23830,	0,
		0,		0,		23830,	0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_2_2[6][4] = 
{
		0,		3304,	0,		0,		//	0,	히마,			0,				0,
		0,		3317,	3305,	0,		//	0,	히마구나,		루,				0,
		0,		3322,	3318,	0,		//	0,	히마바티아,		루구나,			0,
		0,		3343,	3323,	0,		//	0,	히마레스만,		라우티,			0,
		0,		0,		3361,	0,		//	0,	0,				라우티바티아,	0,
		0,		0,		0,		0,		//	0,	0,				0,				0,
};
//	데바 Skill 그림번호, 화살표위치, 데이타 인덱스_3
HTint _DEVA_2_3[6][4] = 
{
		23761,	23720,	22604,	23485,
		23605,	23493,	22603,	23492,
		23767,	23882,	22639,	23830,
		22646,	23482,	22656,	0,
		23829,	23526,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVAARROW_2_3[6][4] = 
{
		0,		23830,	23830,	23830,
		0,		23830,	23830,	0,
		23830,	23830,	0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _DEVASKILLINDEX_2_3[6][4] = 
{
		3310,	3302,	3332,	3309,		//	무쿠타로카,		아바리,			은동해태소환,	스프타,		
		3314,	3311,	3331,	3329,		//	로카나,			자나티로카,		금동해태소환,	스프타레스만,
		3330,	3320,	3359,	3336,			//	데힌무타라,		트레타,			(0)다다티,		0,
		3357,	3328,	3360,	0,			//	(0)바르가,		자마,			(0)아비다바,	0,
		3337,	3338,		0,		0,			//	0,				0,				0,				0,
		0,		0,		0,		0,			//	0,				0,				0,				0,
};

//	주신 스킬
HTint _GOD_4[6][4] = 
{
		0,	22623,	23073,	23072,	
		0,	23071,	23070,	23069,	
		0,	23068,	23067,	23066,	
		0,	23076,	23075,	23065,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _GODARROW_4[6][4] = 
{
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
		0,		0,		0,		0,
};
HTint _GODSKILLINDEX_4_1[6][4] = 
{
		0,	3077,	3076,	3075,		//  무즈카티(0),	파라,			체카,			0,
		0,	3074,	3073,	3072,		//	비사탐파,		킬라,			우파 사르가,	0,
		0,	3071,	3070,	3069,		//	신타나,			야인 라트,		타파스 하르사,	0,
		0,	3067,	3066,	3068,		//	파즈,			라가스,			자야스테,		0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};
HTint _GODSKILLINDEX_4_2[6][4] = 
{
		0,	3177,	3176,	3175,		//  무즈카티(0),	파라,			체카,			0,
		0,	3174,	3173,	3172,		//	비사탐파,		킬라,			우파 사르가,	0,
		0,	3171,	3170,	3169,		//	신타나,			야인 라트,		타파스 하르사,	0,
		0,	3167,	3166,	3168,		//	파즈,			라가스,			자야스테,		0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};
HTint _GODSKILLINDEX_4_3[6][4] = 
{
		0,	3277,	3276,	3275,		//  무즈카티(0),	파라,			체카,			0,
		0,	3274,	3273,	3272,		//	비사탐파,		킬라,			우파 사르가,	0,
		0,	3271,	3270,	3269,		//	신타나,			야인 라트,		타파스 하르사,	0,
		0,	3267,	3266,	3268,		//	파즈,			라가스,			자야스테,		0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};
HTint _GODSKILLINDEX_4_4[6][4] = 
{
		0,	3377,	3376,	3375,		//  무즈카티(0),	파라,			체카,			0,
		0,	3374,	3373,	3372,		//	비사탐파,		킬라,			우파 사르가,	0,
		0,	3371,	3370,	3369,		//	신타나,			야인 라트,		타파스 하르사,	0,
		0,	3367,	3366,	3368,		//	파즈,			라가스,			자야스테,		0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
		0,		0,		0,		0,		//	0,				0,				0,				0,
};

//---------------------------------------------------------------------------------------------------------(2)

CHTSkillInventory::CHTSkillInventory()
{
	m_iSkillTab = -1;
	//	인벤토리 현 상태
	m_bSkillInventoryAction = HT_FALSE;
}

CHTSkillInventory::~CHTSkillInventory()
{
}

HTvoid CHTSkillInventory::HT_vSkillInventory_CleanUp()
{
	m_byMessageWin = SKILL_MESSAGE_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;

	m_iSkill_SkillIconStatus = ICON_STATUS_NONE;	// 스킬 이동중인가
}

HTRESULT CHTSkillInventory::HT_hrSkillItemInit()
{
	HTshort stTribe = g_oMainCharacterInfo.snTribe;
	HTint i, j;
	CHTString strRadioName[4], szMessage, szMessage1;

	// 공통 기술 (주신 스킬 삽입 2005. 4. 25)
	for (i=0; i<6; i++)
	{
		for (j=0; j<4; j++)
		{
			m_oSkillIcon.m_iSkillIconNo4[i][j] = _GOD_4[i][j];
			m_oSkillArrow.m_iSkillArrow4[i][j] = _GODARROW_4[i][j];
			// 스킬 인덱스는 주신에 맞게 기록
			switch(stTribe)
			{
				case HT_ID_CHARACTER_NAGA :
				case HT_ID_CHARACTER_KIMNARA :
					m_oSkillIndex.m_iSkillIndex4[i][j] = _GODSKILLINDEX_4_1[i][j];	// 주신 스킬 추가
					break;
				case HT_ID_CHARACTER_ASURA :
				case HT_ID_CHARACTER_RAKSHASA :
					m_oSkillIndex.m_iSkillIndex4[i][j] = _GODSKILLINDEX_4_2[i][j];	// 주신 스킬 추가
					break;
				case HT_ID_CHARACTER_YAKSA :
				case HT_ID_CHARACTER_GANDHARVA :
					m_oSkillIndex.m_iSkillIndex4[i][j] = _GODSKILLINDEX_4_3[i][j];	// 주신 스킬 추가
					break;
				case HT_ID_CHARACTER_DEVA :
				case HT_ID_CHARACTER_GARUDA :
					m_oSkillIndex.m_iSkillIndex4[i][j] = _GODSKILLINDEX_4_4[i][j];	// 주신 스킬 추가
					break;
			}
		}
	}
	HT_vSkillInventory_SetMessage( eMsgCommonSkillGod, &szMessage );	// 주신
	strRadioName[3] = szMessage;


	switch(stTribe)
	{
		case HT_ID_CHARACTER_NAGA :
		case HT_ID_CHARACTER_KIMNARA :
			for (i=0; i<6; i++)
			{
				for (j=0; j<4; j++)
				{
					switch (g_oMainCharacterInfo.byClass1)
					{
					case CLASS_LEVEL0:
					case CLASS_LEVEL1:
						m_oSkillIcon.m_iSkillIconNo1[i][j] = _NAGA_1[i][j];
						m_oSkillIcon.m_iSkillIconNo2[i][j] = _NAGA_2[i][j];
						m_oSkillIcon.m_iSkillIconNo3[i][j] = _NAGA_3[i][j];

						m_oSkillArrow.m_iSkillArrow1[i][j] = _NAGAARROW_1[i][j];
						m_oSkillArrow.m_iSkillArrow2[i][j] = _NAGAARROW_2[i][j];
						m_oSkillArrow.m_iSkillArrow3[i][j] = _NAGAARROW_3[i][j];

						m_oSkillIndex.m_iSkillIndex1[i][j] = _NAGASKILLINDEX_1[i][j];
						m_oSkillIndex.m_iSkillIndex2[i][j] = _NAGASKILLINDEX_2[i][j];
						m_oSkillIndex.m_iSkillIndex3[i][j] = _NAGASKILLINDEX_3[i][j];
						break;

					case CLASS_LEVEL2:	// 2차 전직시에만 새로운 스킬트리 적용

						switch(g_oMainCharacterInfo.byClass2)
						{
						case CLASS_SATVAN2: // 바나르
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _NAGA_1_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _NAGA_1_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _NAGA_1_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _NAGAARROW_1_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _NAGAARROW_1_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _NAGAARROW_1_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _NAGASKILLINDEX_1_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _NAGASKILLINDEX_1_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _NAGASKILLINDEX_1_3[i][j];
							break;

						case CLASS_SATVAN1: // 사트야
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _NAGA_2_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _NAGA_2_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _NAGA_2_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _NAGAARROW_2_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _NAGAARROW_2_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _NAGAARROW_2_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _NAGASKILLINDEX_2_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _NAGASKILLINDEX_2_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _NAGASKILLINDEX_2_3[i][j];
							break;
						}
						break;
					}
				}
			}
			// 공격
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAttack, &szMessage );
			strRadioName[0] = szMessage;
			// 방어
			HT_vSkillInventory_SetMessage( eMsgCommonSkillDefence, &szMessage );
			strRadioName[1] = szMessage;
			// 보조
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAssistance, &szMessage );
			strRadioName[2] = szMessage;
			// 나가/킨나라
			HT_vSkillInventory_SetMessage( eMsgCommonTribeNaga, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonTribeKimnara, &szMessage1 );
			szMessage += _T("/") + szMessage1;
			break;
		case HT_ID_CHARACTER_ASURA :
		case HT_ID_CHARACTER_RAKSHASA :
			for (i=0; i<6; i++)
			{
				for (j=0; j<4; j++)
				{
					switch (g_oMainCharacterInfo.byClass1)
					{
						case CLASS_LEVEL0:
						case CLASS_LEVEL1:

							m_oSkillIcon.m_iSkillIconNo1[i][j] = _ASURA_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _ASURA_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _ASURA_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _ASURAARROW_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _ASURAARROW_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _ASURAARROW_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _ASURASKILLINDEX_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _ASURASKILLINDEX_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _ASURASKILLINDEX_3[i][j];
							break;

						case CLASS_LEVEL2:	// 2차 전직시에만 새로운 스킬트리 적용

							switch(g_oMainCharacterInfo.byClass2)
							{
								case CLASS_DHVANTA1: // 드루타
									
									m_oSkillIcon.m_iSkillIconNo1[i][j] = _ASURA_2_1[i][j];
									m_oSkillIcon.m_iSkillIconNo2[i][j] = _ASURA_2_2[i][j];
									m_oSkillIcon.m_iSkillIconNo3[i][j] = _ASURA_2_3[i][j];

									m_oSkillArrow.m_iSkillArrow1[i][j] = _ASURAARROW_2_1[i][j];
									m_oSkillArrow.m_iSkillArrow2[i][j] = _ASURAARROW_2_2[i][j];
									m_oSkillArrow.m_iSkillArrow3[i][j] = _ASURAARROW_2_3[i][j];

									m_oSkillIndex.m_iSkillIndex1[i][j] = _ASURASKILLINDEX_2_1[i][j];
									m_oSkillIndex.m_iSkillIndex2[i][j] = _ASURASKILLINDEX_2_2[i][j];
									m_oSkillIndex.m_iSkillIndex3[i][j] = _ASURASKILLINDEX_2_3[i][j];
									break;
						
								case CLASS_DHVANTA2: // 카르야

									m_oSkillIcon.m_iSkillIconNo1[i][j] = _ASURA_1_1[i][j];
									m_oSkillIcon.m_iSkillIconNo2[i][j] = _ASURA_1_2[i][j];
									m_oSkillIcon.m_iSkillIconNo3[i][j] = _ASURA_1_3[i][j];

									m_oSkillArrow.m_iSkillArrow1[i][j] = _ASURAARROW_1_1[i][j];
									m_oSkillArrow.m_iSkillArrow2[i][j] = _ASURAARROW_1_2[i][j];
									m_oSkillArrow.m_iSkillArrow3[i][j] = _ASURAARROW_1_3[i][j];

									m_oSkillIndex.m_iSkillIndex1[i][j] = _ASURASKILLINDEX_1_1[i][j];
									m_oSkillIndex.m_iSkillIndex2[i][j] = _ASURASKILLINDEX_1_2[i][j];
									m_oSkillIndex.m_iSkillIndex3[i][j] = _ASURASKILLINDEX_1_3[i][j];
									break;
							}
							break;
					}
				}
			}
			// 암살
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAssassination, &szMessage );
			strRadioName[0] = szMessage;
			// 궁술
			HT_vSkillInventory_SetMessage( eMsgCommonSkillArchery, &szMessage );
			strRadioName[1] = szMessage;
			// 보조
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAssistance, &szMessage );
			strRadioName[2] = szMessage;
			// 아수라/라크샤사
			HT_vSkillInventory_SetMessage( eMsgCommonTribeAsura, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonTribeRakshasa, &szMessage1 );
			szMessage += _T("/") + szMessage1;
			break;
		case HT_ID_CHARACTER_YAKSA :
		case HT_ID_CHARACTER_GANDHARVA :
			for (i=0; i<6; i++)
			{
				for (j=0; j<4; j++)
				{
					switch (g_oMainCharacterInfo.byClass1)
					{
					case CLASS_LEVEL0:
					case CLASS_LEVEL1:
						m_oSkillIcon.m_iSkillIconNo1[i][j] = _YAKSA_1[i][j];
						m_oSkillIcon.m_iSkillIconNo2[i][j] = _YAKSA_2[i][j];
						m_oSkillIcon.m_iSkillIconNo3[i][j] = _YAKSA_3[i][j];

						m_oSkillArrow.m_iSkillArrow1[i][j] = _YAKSAARROW_1[i][j];
						m_oSkillArrow.m_iSkillArrow2[i][j] = _YAKSAARROW_2[i][j];
						m_oSkillArrow.m_iSkillArrow3[i][j] = _YAKSAARROW_3[i][j];

						m_oSkillIndex.m_iSkillIndex1[i][j] = _YAKSASKILLINDEX_1[i][j];
						m_oSkillIndex.m_iSkillIndex2[i][j] = _YAKSASKILLINDEX_2[i][j];
						m_oSkillIndex.m_iSkillIndex3[i][j] = _YAKSASKILLINDEX_3[i][j];
						break;

					case CLASS_LEVEL2:	// 2차 전직시에만 새로운 스킬트리 적용

						switch(g_oMainCharacterInfo.byClass2)
						{
						case CLASS_NIRVANA1: // 나카유다
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _YAKSA_1_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _YAKSA_1_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _YAKSA_1_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _YAKSAARROW_1_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _YAKSAARROW_1_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _YAKSAARROW_1_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _YAKSASKILLINDEX_1_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _YAKSASKILLINDEX_1_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _YAKSASKILLINDEX_1_3[i][j];
							break;

						case CLASS_NIRVANA2: // 바이드야
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _YAKSA_2_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _YAKSA_2_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _YAKSA_2_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _YAKSAARROW_2_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _YAKSAARROW_2_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _YAKSAARROW_2_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _YAKSASKILLINDEX_2_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _YAKSASKILLINDEX_2_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _YAKSASKILLINDEX_2_3[i][j];
							break;
						}
						break;
					}
				}
			}
			// 공격
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAttack, &szMessage );
			strRadioName[0] = szMessage;
			// 방어
			HT_vSkillInventory_SetMessage( eMsgCommonSkillDefence, &szMessage );
			strRadioName[1] = szMessage;
			// 보조
			HT_vSkillInventory_SetMessage( eMsgCommonSkillAssistance, &szMessage );
			strRadioName[2] = szMessage;
			// 야크샤/간다르바
			HT_vSkillInventory_SetMessage( eMsgCommonTribeYaksha, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonTribeGandharva, &szMessage1 );
			szMessage += _T("/") + szMessage1;
			break;
		case HT_ID_CHARACTER_DEVA :
		case HT_ID_CHARACTER_GARUDA :
			for (i=0; i<6; i++)
			{
				for (j=0; j<4; j++)
				{
					switch (g_oMainCharacterInfo.byClass1)
					{
					case CLASS_LEVEL0:
					case CLASS_LEVEL1:
						m_oSkillIcon.m_iSkillIconNo1[i][j] = _DEVA_1[i][j];
						m_oSkillIcon.m_iSkillIconNo2[i][j] = _DEVA_2[i][j];
						m_oSkillIcon.m_iSkillIconNo3[i][j] = _DEVA_3[i][j];

						m_oSkillArrow.m_iSkillArrow1[i][j] = _DEVAARROW_1[i][j];
						m_oSkillArrow.m_iSkillArrow2[i][j] = _DEVAARROW_2[i][j];
						m_oSkillArrow.m_iSkillArrow3[i][j] = _DEVAARROW_3[i][j];

						m_oSkillIndex.m_iSkillIndex1[i][j] = _DEVASKILLINDEX_1[i][j];
						m_oSkillIndex.m_iSkillIndex2[i][j] = _DEVASKILLINDEX_2[i][j];
						m_oSkillIndex.m_iSkillIndex3[i][j] = _DEVASKILLINDEX_3[i][j];

						break;

					case CLASS_LEVEL2:	// 2차 전직시에만 새로운 스킬트리 적용

						switch(g_oMainCharacterInfo.byClass2)
						{
						case CLASS_MANTRIKA1: // 아비카라
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _DEVA_1_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _DEVA_1_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _DEVA_1_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _DEVAARROW_1_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _DEVAARROW_1_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _DEVAARROW_1_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _DEVASKILLINDEX_1_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _DEVASKILLINDEX_1_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _DEVASKILLINDEX_1_3[i][j];
							break;

						case CLASS_MANTRIKA2: // 사마바트
							m_oSkillIcon.m_iSkillIconNo1[i][j] = _DEVA_2_1[i][j];
							m_oSkillIcon.m_iSkillIconNo2[i][j] = _DEVA_2_2[i][j];
							m_oSkillIcon.m_iSkillIconNo3[i][j] = _DEVA_2_3[i][j];

							m_oSkillArrow.m_iSkillArrow1[i][j] = _DEVAARROW_2_1[i][j];
							m_oSkillArrow.m_iSkillArrow2[i][j] = _DEVAARROW_2_2[i][j];
							m_oSkillArrow.m_iSkillArrow3[i][j] = _DEVAARROW_2_3[i][j];

							m_oSkillIndex.m_iSkillIndex1[i][j] = _DEVASKILLINDEX_2_1[i][j];
							m_oSkillIndex.m_iSkillIndex2[i][j] = _DEVASKILLINDEX_2_2[i][j];
							m_oSkillIndex.m_iSkillIndex3[i][j] = _DEVASKILLINDEX_2_3[i][j];
							break;
						}
						break;
					}
				}
			}
			// 물리/화염
			HT_vSkillInventory_SetMessage( eMsgCommonSkillPhysics, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonSkillBlaze, &szMessage1 );
			strRadioName[0] = szMessage + _T("/") + szMessage1;
			// 냉기/전격
			HT_vSkillInventory_SetMessage( eMsgCommonSkillCold, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonSkillLightning, &szMessage1 );
			strRadioName[1] = szMessage + _T("/") + szMessage1;
			// 마법
			HT_vSkillInventory_SetMessage( eMsgCommonSkillMagic, &szMessage );
			strRadioName[2] = szMessage;
			// 데바/가루다
			HT_vSkillInventory_SetMessage( eMsgCommonTribeDeva, &szMessage );
			HT_vSkillInventory_SetMessage( eMsgCommonTribeGaruda, &szMessage1 );
			szMessage += _T("/") + szMessage1;
			break;
	}

	// V3 UI에도 정보 삽입
	for (i=0; i<6; i++)
	{
		for (j=0; j<4; j++)
		{
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex1[i][j] = m_oSkillIndex.m_iSkillIndex1[i][j];
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex2[i][j] = m_oSkillIndex.m_iSkillIndex2[i][j];
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex3[i][j] = m_oSkillIndex.m_iSkillIndex3[i][j];
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex4[i][j] = m_oSkillIndex.m_iSkillIndex4[i][j];
			
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo1[i][j] = m_oSkillIcon.m_iSkillIconNo1[i][j];
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo2[i][j] = m_oSkillIcon.m_iSkillIconNo2[i][j];
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo3[i][j] = m_oSkillIcon.m_iSkillIconNo3[i][j];
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo4[i][j] = m_oSkillIcon.m_iSkillIconNo4[i][j];

			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow1[i][j] = m_oSkillArrow.m_iSkillArrow1[i][j];
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow2[i][j] = m_oSkillArrow.m_iSkillArrow2[i][j];
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow3[i][j] = m_oSkillArrow.m_iSkillArrow3[i][j];
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow4[i][j] = m_oSkillArrow.m_iSkillArrow4[i][j];
		}
	}
	g_cUISkillWindow->HT_vSkillWindow_SetInfo();	// 다시 갱신

	return HT_OK;
}

HTRESULT CHTSkillInventory::HT_hrSkillInventoryInit()
{
	//	Skill Inventory SkillPoint Cell No
	m_snSkillInventory_SkillPoint = 0;
	//	Skill Inventory TrimuritiSkillPoint Cell No
	m_snSkillInventory_TrimutiritiSkillPoint = 0;
	//	슬라이드 바
	m_bSkillInventory_SlideBarBtn = HT_FALSE;	
	//	현재의 슬라이드 Bar Pos
	m_iSkillInventory_SlideBarCurPos = -1;
	//	현재의 라디오 그룹
	m_iSkillInventory_RidioCurGroup = 0;

	m_byMessageWin = SKILL_MESSAGE_NONE;
	m_byResent_ServerMsg = SERVER_MSG_NONE;

	m_iSkill_SkillIconStatus = ICON_STATUS_NONE;	// 스킬 이동중인가

	return HT_OK;
}

HTRESULT CHTSkillInventory::HT_hrSkillInventoryDestory()
{
	return HT_OK;
}

//----------활성화 체크_0x00:인벤토리,0x01:퀴스킬----------//
HTvoid CHTSkillInventory::HT_vSkillInventoryActiveCheck( BYTE byType )
{
	if( g_cUIManager->HT_isShowWindow( _DIALOG_SKILL ) )
	{
		HT_vSkillInventory_SetAntiActive();
	}
	else
	{	
		HT_vSkillInventory_SetActive();
	}
}
 
HTvoid CHTSkillInventory::HT_vSkillInventory_SetActive()
{
	m_bSkillInventoryAction = HT_TRUE;
	g_cUIManager->HT_ShowWindow( _DIALOG_SKILL );
	g_cUISkillWindow->HT_vSkillWindow_WindowPopup();

	if( m_iSkillTab == -1 )
        this->HT_hrSkillItemInit();
}

HTvoid CHTSkillInventory::HT_vSkillInventory_SetAntiActive()
{
	// 현재창 범위에 정보창이 띄워져 있을 경우 정보창을 닫는다
	if( g_cObjectInfo->HT_bObjectInfo_IsActive() == HT_TRUE )
		g_cObjectInfo->HT_vObjectInfo_AntiActive();

	// 스킬 선택 중이었으면
	if( m_iSkill_SkillIconStatus == ICON_STATUS_MOVE )
	{
		m_iSkill_SkillIconStatus = ICON_STATUS_NONE;
	}
	m_bSkillInventoryAction = HT_FALSE;
	g_cUIManager->HT_HideWindow(_DIALOG_SKILL );
}

//	ESC Key 누르면 스킬창 닫기
HTvoid CHTSkillInventory::HT_vSkillInventory_ESC_CloseWindow()
{
	HT_vSkillInventory_SetAntiActive();
}

//----------스킬을 분석하여 그 스킬에 맞는 액션을 해줌----------//
HTvoid CHTSkillInventory::HT_vSkillInventory_SkillAnalysis( DWORD dwSkillID )
{
	//	액션일때는 전투로 넘기고
	//  액티브일때는 여기서 바로 스위츠로 반영구Attack를 호출
    //  패시브는 메인 캐릭터에 값만 셋팅
	//	하지만 여기서 처리해줄 내용은 액티브 스킬에 관련 한 내용 뿐이랑게

	BYTE byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwSkillID );
	if( byLevel == 0 )
		return;

	HT_ATTACKCREATE_FLAG	sAttackFlag;

	//	if( sSkill_Param != HT_NULL && sSkill_Param->byUseType == 0x04 )			//	액티브
	{
		sAttackFlag.Attack_ID = g_cMainCharacter->HT_vMainChar_GetModelID();
		sAttackFlag.Attack_KeyID = g_cMainCharacter->HT_iMainChar_GetKeyID();
		sAttackFlag.Attack_Pos = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		sAttackFlag.Attack_Type = 0x00;
		sAttackFlag.Attack_Skill_Index = dwSkillID;
	}
//	else if( sSkill_Param->byUseType == 0x05 )		//	패시브_서버에서 해야할지 내가 해야할지 판단?
	{
	}
}

//----------셋팅 및 반환값들----------//
HTbool CHTSkillInventory::HT_bSkillInventory_GetActive()
{
	return m_bSkillInventoryAction;
}

HTvoid CHTSkillInventory::HT_vSkillInventory_SetSkillPoint( HTshort snSkillPoint, HTshort snTrimuritiSkillPoint )
{
	//	Skill Inventory SkillPoint Cell No
	m_snSkillInventory_SkillPoint = snSkillPoint;
	//	Skill Inventory TrimuritiSkillPoint Cell No
	m_snSkillInventory_TrimutiritiSkillPoint = snTrimuritiSkillPoint;

	if (g_cUIManager)
	{
		// 남은 스킬포인트를 V3에서도 가지고 옴
		g_cUISkillWindow->m_ExtraSkillPoint = m_snSkillInventory_SkillPoint;
		g_cUISkillWindow->m_ExtraTrimutiritiSkillPoint = m_snSkillInventory_TrimutiritiSkillPoint;

		CHTString str;
		str.HT_szFormat("%d", g_cUISkillWindow->m_ExtraSkillPoint); 
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4000, str);
		str.HT_szFormat("%d", g_cUISkillWindow->m_ExtraTrimutiritiSkillPoint);
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4001, str);
	}
}

//-----네트워크 관련-----//
//-----스킬 레벨업------//	
HTvoid CHTSkillInventory::HT_vNetWork_CSP_Skill_LevekUp()
{
	PS_CSP_REQ_SKILL_LEVEL_UP info = HT_NULL;
	info = new S_CSP_REQ_SKILL_LEVEL_UP;

	info->dwIndex = m_dwSkillIndex_LvlUp;

	g_pNetWorkMgr->RequestSkillLevelUp( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqSkillLevelUp : %d", info->dwIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid CHTSkillInventory::HT_vNetWork_SCP_Skill_LevelUp(PS_SCP_RESP_SKILL_LEVEL_UP info)
{
	CHTString szMessage;
	if(info->byResult == 0)
	{
		g_cSkillSystem->HT_vSkillSystem_SetSkill_Level(m_dwSkillIndex_LvlUp, info->byLevel);

		if( info->nPrana < 0 )
			g_cMainCharacter->HT_vMainChar_SetTotalPrana( 0 );
		else
			g_cMainCharacter->HT_vMainChar_SetTotalPrana( info->nPrana );

		if( info->byLevel > 0 )
		{
			//	일단 여기에 스킬 레밸업시에 게임데이타 셋팅되는부분을 세팅해둔다.
			//	이후 패킷 파라메타를 추가하여 이곳을 수정한다.
			//	공격속도
			g_cSkillSystem->HT_vSkillSystem_SetAttackSpeedVariation( m_dwSkillIndex_LvlUp, info->snAttackSpeed );
			//	캐스팅속도
			g_cSkillSystem->HT_vSkillSystem_SetCastingSpeedVariation( m_dwSkillIndex_LvlUp, info->snCastingSpeed );
			//	사정거리
			g_cSkillSystem->HT_vSkillSystem_SetShootRange( m_dwSkillIndex_LvlUp, info->byShootRange );
			//	이동속도
			g_cSkillSystem->HT_vSkillSystem_SetMovingSpeed( m_dwSkillIndex_LvlUp, info->snMovingSpeed );
		}

		CHTString szName;
		//---------- 시스템창에 출력 ------------//
		if( g_pEngineHandler->HT_hrGetPCSkillName( m_dwSkillIndex_LvlUp, &szName ) == HT_OK )
		{
			// %s(을)를 %d레벨로 올렸습니다.
			m_szMsgSkillName = szName;
			m_byMsgSkillLevel = info->byLevel;
			HT_vSkillInventory_SetMessage( eMsgSkillUpOK, &szMessage );
		}

		//---------- 스킬 레벨업 이펙트 틀어주기 ------------//
		//	생성시의 이펙트
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWSKILL, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	}
	else
	{ 
		if(info->byResult == 0x01)
			// 더이상 레벨을 올릴 수 없습니다.
			HT_vSkillInventory_SetMessage( eMsgSkillUpLimitLevel, &szMessage );
		else if(info->byResult == 0x03)
			// 해당 스킬이 없습니다.
			HT_vSkillInventory_SetMessage( eMsgSkillCannotFindInfo, &szMessage );
		else
			// 스킬 레벨을 올릴 수 없습니다.
			HT_vSkillInventory_SetMessage( eMsgSkillUpFail, &szMessage );
		
		// 완료창 띄움
		m_byMessageWin = SKILL_MESSAGE_COMPLETE;
	}

	//---------- 시스템창에 출력 ------------//
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_SKILL, szMessage );

	m_byResent_ServerMsg = SERVER_MSG_NONE;
}

//-----스킬 배우기------//	
HTvoid CHTSkillInventory::HT_vNetWork_CSP_Skill_LearnSkill( HTint iButton )
{
	HTdword dwIndex = 0;

	// v3버전에서는 다음과 같이 인덱스를 어더온다.
	dwIndex = g_cUISkillWindow->HT_vGetSkillIndex(iButton);

	// 개발자 모드가 아닌 상태에서는 스킬인덱스를 0으로 만들어 작동불가로 만든다.
//	if ( g_bDevelopingMode == HT_FALSE && m_iSkillTab == 3)
//		dwIndex = 0;


	BYTE byCharLevel = g_cStatus->HT_byGetLevel();
	BYTE byMaxLevel = 0, byReqLevel = 0;
	HTint iOut;
	HTbyte byteOut;
	CHTString strReqSkill;
	CHTString strTempSkill;
	CHTString szMessage;

	BYTE byCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwIndex ); // 현재 스킬 레벨
	strReqSkill.HT_hrCleanUp();

	// 다음 레벨의 제한사항
	// 스킬 정보 Lock 설정
	HTbool bNextInfo = HT_FALSE;
	if( byCurLevel == 0 )
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel+1, &byMaxLevel );
	else
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel, &byMaxLevel );

	if( byMaxLevel > 0 && byCurLevel < byMaxLevel && 
		g_pParamMgr->HT_bLockID( dwIndex, byCurLevel+1 ) == true )
	{
		// 요구레벨
		if( g_pParamMgr->HT_bGetPCSkillReqLevel( &byteOut ) == true && byteOut > 0 )
		{
			if( g_cStatus->HT_byGetLevel() < byteOut )
			{
				// %d Level 필요
				HT_vSkillInventory_SetMessage( eMsgSkillInfoNeedLevel, &szMessage );
				strReqSkill.HT_szFormat( szMessage.HT_szGetString(), byteOut );
			}
		}
		// 습득조건 스킬
		if( g_pParamMgr->HT_bGetPCSkillReqSkill1( &iOut ) == true && iOut > 0 && strReqSkill.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrGetPCSkillName( iOut, &strTempSkill);
			g_pParamMgr->HT_bGetPCSkillReqSkill1_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut )
			{
				// %s Lvl %d 필요
				HT_vSkillInventory_SetMessage( eMsgSkillInfoNeedSkillLevel, &szMessage );
				strReqSkill.HT_szFormat( szMessage.HT_szGetString(), strTempSkill.HT_szGetString(), byteOut);
			}
		}
		if( g_pParamMgr->HT_bGetPCSkillReqSkill2( &iOut ) == true && iOut > 0 && strReqSkill.HT_bIsEmpty() )
		{
			g_pEngineHandler->HT_hrGetPCSkillName( iOut, &strTempSkill);
			g_pParamMgr->HT_bGetPCSkillReqSkill2_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut )
			{
				// %s Lvl %d 필요
				HT_vSkillInventory_SetMessage( eMsgSkillInfoNeedSkillLevel, &szMessage );
				strReqSkill.HT_szFormat( szMessage.HT_szGetString(), strTempSkill.HT_szGetString(), byteOut);
			}
		}
		g_pParamMgr->HT_bUnLockID( dwIndex, byCurLevel+1 );
	}


	if( !strReqSkill.HT_bIsEmpty() )
	{
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strReqSkill );
		return;
	}

	PS_CSP_REQ_LEARN_SKILL  info = HT_NULL;
	info = new S_CSP_REQ_LEARN_SKILL;
	info->snID = (short)dwIndex;
	g_pNetWorkMgr->RequestSkillLearn( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqSkillLearn : %d", dwIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
HTvoid CHTSkillInventory::HT_vNetWork_SCP_Skill_LearnSkill( PS_SCP_RESP_LEARN_SKILL info )
{
	if( info->byRes == 0 )
	{
		//	남은 Skill Point스킬 인벤토리에 셋팅
		this->HT_vSkillInventory_SetSkillPoint( m_snSkillInventory_SkillPoint, m_snSkillInventory_TrimutiritiSkillPoint );

		g_cSkillSystem->HT_vSkillSystem_SetLearn( info->kSkill );

		g_cUISkillWindow->HT_vSkillWindow_SetInfo();

		//---------- 스킬 레벨업 이펙트 틀어주기 ------------//
		//	생성시의 이펙트
		HTint idFx;
		g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_NEWSKILL, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
	}
	else if( info->byRes == 107 )
	{
		g_cSkillSystem->HT_vSkillSystem_TotalSkillLevelInit();

		if (g_cUIManager->HT_isShowWindow( _DIALOG_SKILL ) )
			g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );

		g_cSkillInventory->HT_hrSkillItemInit(); // 스킬트리 다시 그리기

		g_cUISkillWindow->HT_vSkillWindow_SetInfo();
	}
	else
	{
		CHTString szMessage;
		HT_vSkillInventory_SetMessage( eMsgSkillUpCannotLearn, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
	}
}

//	Recive Server MSG_SKILL_UP_EFFECT
HTvoid CHTSkillInventory::HT_vNetWork_SCP_Skill_Up_Effect( MSG_SKILL_UP_EFFECT* info )
{
	g_cSkillSystem->HT_vSkillSystem_SetSkillPlusLevel( info->snID, info->byLevel, info->byLevelPlus );
}

HTvoid CHTSkillInventory::HT_vSkillInventory_SetMessage( HTint idMessage, CHTString* pszMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = HT_MSG_PARAM_NONE, sParam2 = HT_MSG_PARAM_NONE, sParam3 = HT_MSG_PARAM_NONE;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();
	
	//------------------------------------------------------------------------------------//
	// 예외 - 스킬 정보 관련의 경우 메세지만 설정하고, 파라미터 값은 외부에서 직접 입력하는 방식으로 한다. 
	//------------------------------------------------------------------------------------//
	// 변수가 3개 일 때
	if( sParam1 != HT_MSG_PARAM_NONE && sParam2 != HT_MSG_PARAM_NONE && sParam3 != HT_MSG_PARAM_NONE )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vSkillInventory_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSkillInventory_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vSkillInventory_SetParamTextForMessage( sParam3, &szOut3 );

		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != HT_MSG_PARAM_NONE && sParam2 != HT_MSG_PARAM_NONE )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vSkillInventory_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vSkillInventory_SetParamTextForMessage( sParam2, &szOut2 );
		
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != HT_MSG_PARAM_NONE  )
	{
		CHTString szOut1;

		// sParam1
		HT_vSkillInventory_SetParamTextForMessage( sParam1, &szOut1 );
		pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pszMessage = szString;
}

HTvoid CHTSkillInventory::HT_vSkillInventory_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// 스킬 이름
		case eMsgParamSkillName :
			*pszParam = m_szMsgSkillName ;
			break;		
		// 스킬 레벨
		case eMsgParamSkillLevel	:	
			pszParam->HT_szFormat( "%d", m_byMsgSkillLevel );
			break;

		default:
			break;
	}
}

