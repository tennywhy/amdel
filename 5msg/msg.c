#pragma noregparms
#include <define.h>
#include <struct.h>

MSGSTRSTRUCT code MsgStr[] = {
	"		AMDE		", //Msg_versionNo 0x00
	"					", //Msg_BlankLine 0x01
	"	INITIALIZE?		", //Msg_InitializeYN
	"	\xff\x01\xff\x02\xff\x03\xff\x04	", //Msg_SaveSettingsYN
	"	\xff\x01\xff\x05\xff\x06\xff\x04	", //Msg_LoadSettingsYN
	"		(Y/N?)		", //Msg_ConfigYN
	"SET\xff\x07\xff\x08 ESC\xff\x09\xff\x0a", //Msg_SaveAndExitConfirm
	//Msg_ValueTooLagrge
	"\xff\x0b\xff\x0c\xff\x0d\xff\x0e ESC\xff\x09\xff\x0a",
	//Msg_ValueTooLittle
	"\xff\x0b\xff\x0c\xff\x0d\xff\x0f ESC\xff\x09\xff\x0a",
	//Msg_PasswordError
	"\xff\x10\xff\x11\xff\x12 ESC\xff\x09\xff\x0a",
	" /s ", //Msg_CRUnit
	"q/cm", //Msg_SGUnit
	"	 ", //Msg_PSUnit

	"\xff\x13\xff\x0b\xff\x14:", //Msg_CR
	"\xff\x10	\xff\x15:", //Msg_SG
	"\xff\x16	\xff\x15:", //Msg_PS
	//Msg_SetupUser
	" 1.\xff\x17\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04 "
	//Msg_SetupSystem
	" 2.\xff\x1a\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04 "
	//Msg_SetupTrim
	" 3.\xff\x1b\xff\x1c\xff\x03\xff\x04 "
	//Msg_PasswordUser
	"\xff\x17\xff\x18\xff\x19\xff\x0b\xff\x10\xff\x11",
	//Msg_STD
	"\xff\x1d\xff\x1a\xff\x1f\xff\x20\xff\x10\xff\x15"
	// Msg_S1
	"\xff\x1d\xff\x1e\xff\x1f\xff\x20\xff\x13\xff\x0b\xff\x14",
	// Msg_PasswordSys
	"\xff\x1a\xff\x18\xff\x19\xff\x0b\xff\x10\xff\x11",
	// Msg_SSG
	"\xff\x21\xff\x22\xff\x23\xff\x20\xff\x10\xff\x15",
	// Msg_M
	"\xff\x212\xff\x25\xff\x26\xff\x0b",
	// Msg_LSG
	"\xff\x27\xff\x1b\xff\x1f\xff\x20\xff\x10\xff\x15",
	// Msg_SGLO
	"\xff\x10\xff\x15\xff\x11\xff\x1c\xff\x28\xff\x29",
	// Msg_SGHI
	"\xff\x10\xff\x15\xff\x1b\xff\x1c\xff\x2a\xff\x29",
	// Msg_PSLO
	"\xff\x16\xff\x15\xff\x1b\xff\x1c\xff\x28\xff\x29",
	// Msg_PSHI
	"\xff\x16\xff\x15\xff\x1b\xff\x1c\xff\x2a\xff\x29",
	// Msg_SelectmA	
	"\xff\x21\xff\x2c\xff\x2d\xff\x2e\xff\x1b\xff\x1c",
	// Msg_Baudrate	
	"\xff\x3f\xff\x30\xff\x14",
	// Msg_Parity
	"\xff\x1d\xff\x31\xff\x32\xff\x33",
	// Msg_DeviceNo	
	"\xff\x03\xff\x34\xff\x35",
	// Msg_LoadSettings	
	"\xff\x05\xff\x06\xff\x03\xff\x04",
	// Msg_PasswordTrim	
	"\xff\1d\xff\x36\xff\x10\xff\x11",
	// Msg_NewPassWordTrim
	"\xff\x32\xff\x1d\xff\x36\xff\x10\xff\x11",
	// Msg_TrimZero	
	"\xff\x1b\xff\x38\xff\x39\xff\x30\xff\x0d\xff\x36mA",
	// Msg_TrimRange
	"\xff\x1b\xff\x38\xff\x39\xff\x3c\xff\x1d\xff\x36mA",
	"4mA\xff\x1b\xff\x1c\xff\x1d\xff\x36mA", //Msg_Trim4mA
	"20mA\xff\x1b\xff\x1c\xff\x1d\xff\x36mA", //Msg_Trim20mA
	"\xff\x2d\xff\x2e\xff\x1b\xff\x1c\xff\x3d\xff\x3emA", // Msg TestIout
	"\xff\x01\xff\x02\xff\x03\xff\x04", // Msg_SaveSettings
	"\xff\x10\xff\x15\xff\x2d\xff\x2e", // Msg SelectmA0
	"\xff\x16\xff\x15\xff\x2d\xff\x2e", // Msg SelectmAl
	"1200", //Msg Baudrate0
	"2400", // Msg Baudratel
	"4800", //Msg Baudrate2
	"9600", // Msg Baudrate3
	"\xff\x3f\xff\x1d\xff\x31", // Msg Parity0
	"\xff\x40\xff\x1d\xff\x31", // Msg Parityl
	"\xff\x41\xff\x1d\xff\x31", // Msg Parity2
	"No ", // Msg No
	"Yes", // Msg Yes
};


MainMenuStruct code MainMenu[3] = {
{Msg_SetupUser,	3,	0}, // \xff\x1d\xff\x36\xff\x03\xff\x04 //offset
{Msg_SetupSystem,	13,	3}, // \xff\x42\xff\x43\xff\x03\xff\x04
{Msg_SetupTrim,		8,	16}, //\xff\x26\xff\x44\xff\x03\xff\x04
};

uchar code ParmStr[24] = {
	//\xff\x17\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04\xff\x10\xff\x11
	Msg_PasswordUser	,
	//\xff\xld\xff\xle\xff\x1f\xff\x20\xff\x10\xff\x15
	Msg_STD 	,
	//\xff\x1d\xff\xle\xff\x1f\xff\x20\xff\x13\xff\x0b\xff\x14
	Msg_S1		,
	//\xff\xla\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04\xff\x10\xff\x11
	Msg_PasswordSys		,
	//\xEf\x21\xff\x22\xff\x23\xff\\xff\x20\xff\x10\xff\x15
	Msg_SSG		,
	// \xff\x24\xff\x25\xff\x26\xff\x0b
	Msg_M		,
	//\xff\x27\xff\xlb\xff\xlf\xff\x20\xff\x10\xff\x15
	Msg_LSG		,
	//\xff\x10\xff\x15\xff\x1b\xff\x1c\xff\x28\xff\x29
	Msg_SGLO	,
	//\xff\x10\x��f\x15\xff\xlb\xff\xlc\xff\x2a\xff\x29
	Msg_SGHI	,
	//\xff\x16\xff\x15\xff\xlb\xff\xlc\xff\x28\xff\x29
	Msg_PSLO	,
	//\xff\x16\xff\x15\xff\xlb\xff\x1c\xff\x2a\xff\x29
	Msg_PSHI	,
	//\xff\x2b\xff\x2c\xff\x2d\xff\x2e\xff\x1b\xff\x1c
	Msg_SelectmA	,
	//\xff\x2b\xff\x2c\xff\x2f\xff\x30\xff\x14
	Msg_Baudrate	,
	//\xff\x2b\xff\x2c\xff\x1d\xff\x31\xff\x32\xff\x33
	Msg_Parity		,
	// \xff\x2b\xff\x2c\xff\x03\xff\x34\xff\x35
	Msg_DeviceNo	,
	// \xff\x05\xff\x06\xff\x03\xff\x04
	Msg_LoadSettings	,	
	//\xff\xld\xff\x36\xff\x10\xff\x11
	Msg_PasswordTrim	,
	// \xff\x37\xff\x1d\xff\x36\xff\x10\xff\x11
	Msg_NewPassWordTrim
	//xff\xlb\xff\x38\xff\x39\xff\x3a\xff\x1d\xff\x36mA
	Msg_TrimZero		,
	//\xff\x1b\xff\x38\xff\x3b\xff\x3c\xff\x1d\xff\x36mA
	Msg_TrimRange
	// 4mA\xff\x1b\xff\x1c\xff\x1d\xff\x36mA
	Msg_Trim4mA
	// 20mA\xff\x1b\xff\x1c\xff\x1d\xff\x36mA
	Msg_Trim20mA
	//\xff\x2d\xff\x2e\xff\xlb\xff\xlc\xff\x3d\xff\x3emA
	Msg_TestIout
	// \xff\x01\xff\x02\xff\x03\xff\x04
	Msg_SaveSettings
	};


ParmStruct code DefaultParm = {
	"1000"	, //\xff\x17\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04\xff\x10\xff\x11
	1.0	, //\xff\xld\xff\x1e\xff\x1f\xff\x20\xff\x10\xff\xl5
	1000	, //\xff\xld\xff\xle\xff\x1f\xff\x20\xff\x13\xff\x0b\xff\x14
	"2000"	, //\xff\xla\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04\xff\x10\xff\xl1
	1.4	, // \xff\x21\xff\x22\xff\x23\xff\x20\xff\x10\xff\x15
	1	, //\xff\x24\xff\x25\xff\x26\xff\x0b
	1.0	, // \xff\x27\xff\xlb\xff\x1f\xff\x20\xff\x10\xff\x15
	1.0	, //// \xff\x10\xff\x15\xff\xlb\xff\x1c\xff\x28\xff\x29
	2.0	, // \xff\x10\xff\x15\xff\xlb\xff\x1c\xff\x2a\xff\x29
	0.0	, //\xff\x16\xff\x15\xff\x1b\xff\x1c\xff\x28\xff\x29
	100.0	, // \xff\x16\xff\x15\xff\x1b\xff\x1c\xff\x2a\xff\x29
	//\xff\x2b\xff\x2c\xff\xlb\xff\xlc\xff\x2d\xff\x2e\xff\x45 \xff\x10\xff\x15
	//\xff\x2d\xff\x2e
	0	, 
	3	, //\xff\x2f\xff\x30\xff\x14
	0	, // \xff\xld\xff\x31\xff\x32\xff\x33
	"00"	, //xff\x03\xff\x34\xff\x35
	0	, //\xff\x05\xff\x06\xff\x03\xff\x04
	"3000"	, // \xff\xld\xff\x36\xff\x10\xff\x11
	"0000"	, // \xff\x37\xff\x1d\xff\x36\xff\x10\xff\x11
	4.0	, // \xff\xlb\xff\x38\xff\x39\xff\x3a\xff\x1d\xff\x36mA
	20.0	, // \xff\xlb\xff\x38\xff\x3b\xff\x3c\xff\x1d\xff\x36mA
	0.0	, // 4mA\xff\xlb\xff\xlc\xff\x1d\xff\x36mA
	0.0	, // 20mA\xff\x1b\xff\x1c\xff\x1d\xff\x36mA
	12.0	, // \xff\x2d\xff\x2e\xff\x1b\xff\xlc\xff\x3d\xff\x3emA
	0	, // \xff\x01\xff\x02\xff\x03\xff\x04
};

/*
uchar Mode;
1uchar MaxValue; //for Digit or Select
uchar TotalLen;
uchar DecLen; //for Float
float MaxFloat; //for Float
float MinFloat; //for Float
uint16 Offset;
*/

ParmAttrStruct code ParmAttr[24] = {
	//\xff\x17\xff\x18\xff\x19\xff\x0b\xff\x03\xff\x04\xff\x10\xff\xl1
	{PIN_INPUT, '9', 4, 0, 0.0, 0.0, O}, // һ��������������
	//\xff\xld\xff\xle\xff\xlf\xff\x20\xff\x10\xff\x15 99.0 - 0.0
	{FLOAT_INPUT, 9, 5, 4, 99.0, 1.0, 4}, // У��Һ���ܶ�99.0 - 0.0
	//\xff\x1d\xff\xle\xff\xlf\xff\x20\xff\x13\xff\x0b\xff\x14 99.0 - 0.0
	{FLOAT_INPT, 9,  5, 0, 65535, 0, 8}, //У��Һ�������99.0 - 0.0
	//\xff\xla\xff\xlB\xff\x19\Xff\xOb\xff\X03\Xff\x04\xff\X10\xff\x11
    {PIN_INPUT, '9', 4, 0, 0.0, 0.0, 12} , //����������������
    //0xff\x22\xff\x23\xff\x20\xff\x101xff\x15
    {FLOAT_INPUT, 9, 5, 4, 99999, 1.0, 16}, //���������ܶ�
    //\xff\x24\xff\x25\xff\x26\xff\x0b
    {FLOAT_INPUT, 9, 5, 4, 99.0, 0.0, 20}, // ����ϵ��
    //\xff\x27\xff\x1b\xff\xlf\xff\x20\xff\x10\xff\x15
    {FLOAT_INPUT, 9, 5, 4, 99.0, 0.0, 24}, //����Һ���ܶ�
    //\xff\x10\xff\x15\xff\x1b\xff\x1c\xff\x28\xff\x29
    {FLOAT_INPUT, 9, 5, 4, 99.0, 0.0, 28}, //�ܶ��������
    //0xff\x10\xff\x15\xff\x1b\xff\xlc\xff\x2a\xff\x29
    {fLOAT_INPUT, 9, 5, 4, 99.0, 0.0, 32}, //�ܶ��������
    //\0xff\x16\xff\x15\xff\x1b\xff\x1c\xff\x28\xff\x29
    {FLOAT_INPUT, 9, 5, 4, 99999, 0.0, 36}, //Ũ���������
    //Ix16\xff\x15\xff\x1b\xff\x1c\xff\x2a\xff\x29
    {FLOAT_INPUT, 9, 5, 4, 99999, 0.0, 40}, //Ũ���������
    //\xff\x2b\xff\x2c\xff\x2d\xff\x2e\xff\x1b\xff\xlc
    {SELECT_INPUT, 1, 0, 0.0, 0.0, 44}, //ѡ��������
    //\xff\x2f\xff\x30\xff\x14
    {SELECT_INPUT, 3, 1, 0, 0.0, 0.0, 45}, // ������
    //\xff\x1d\xff\x31\xff\x32\xff\x33
    {SELECT_INPUT, 2, 1, 0, 0.0, 0.0, 46}, //У�鷽ʽ
    //\xff\x03\xff\x34\xff\x35
    {DIGIT_INPUT, '9', 2, 0, 0.0, 0.0, 47}, //�豸��
    //\xff\x05\xff\x06\xff\x03\xff\x04
    {SELECT_INPUT, 1, 0, 0.0, 0.0, 49}, //�ָ�����
    //xff\x1d\xff\x36\xff\x10\xff\x11
    {PIN_INPUT, '9', 4, 0, 0.0, 0.0, 50}, //У׼����
    //\0xff\x37\xff\x1d\xff\x36\xff\x10\xff\x11
    {NEWPIN_INPUT, '9', 4, 0, 0.0, 0.0, 54}, //��У׼����
    //0xff\xlb\xff\x38\xff\x39\xff\x3a\xff\xld\xff\x36mA
    {FLOAT_INPUT, 9, 5, 3, 5.0, 3.0, 58}, //�������У׼mA 5.0 - 3.0
    //\xff\x1b\xff\x38\xff\x3b\xff\x3c\xff\xld\xff\x36mA
    {FLOAT_INPUT, 9, 5, 3, 21.0, 19.0, 62 }, //��������У׼mA 21.0 - 19.0
    //4mA\xff\xlb\xff\x1c\xff\x1d\xff\X36MA 5.0 - 3.0
    {FLOAT_INPUT, 9, 5, 3, 5.0, 3.0, 66}, //4mA ���У׼mA 5.0 - 3.0
    //20MA\xff\xlb\xff\x1c\xff\x1d\xff\x36mA 21.0 - 19.0
    {FLOAT_INPUT, 9, 5, 3, 21.0, 19.0, 70}, //20mA���У׼mA 21.0 - 19.0
    //\xff\x2d\xff\x2e\xff\x1b\xff\x1c\xff\x3d\xff\x3emA
    {FLOAT_INPUT, 9, 4, 1, 20.0, 4.0, 74}, //�����������mA 20.0 - 4.0
    //\xff\x01\xff\x02\xff\x03\xff\x04
    {SELECT_INPUT, 1, 1, 0, 0.0, 0.0, 78 }, // ��������
};

PROMPTSTRUCT code SelectmAStr[2] = {
	//\xff\xlb\xff\xlc\xff\x2d\xff\x2e\xff\x45\xff\x10\xff\x15\xff\x2d\xff\x2e
	Msg_SelectmA0,
	//\xff\x1b\xff\x1c\xff\x2d\xff\x2e\xff\x45\xff\x16\xff\x15\xff\x2d\xff\x2e
	Msg_SelectmA1,
};

PROMPTSTRUCT code BaudrateStr[4] = {
	Msg Baudrate0,
	Msg Baudratel,
	Msg Baudrate2,
	Msg Baudrate3,
};

PROMPTSTRUCT code ParityStr[3] = {
	Msg_Parity0,
	Msg_Parity1,
	Msg_Parity2,
};

PROMPTSTRUCT code YesNoStr[2] = {
	Msg_No ,
	Msg_Yes,
};
