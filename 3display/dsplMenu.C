
#include "..\1head\0common.h"
#include "dsplMenu.h"
//#include "defineSTC.h"
#include "display.H"
#include "..\5msgCalc\msgCalc.h"

	void sub_menu_disp(menu_disp_t *disp);


	#define Grd1Pwd 1
	#define Grd2Pwd 2
	#define Grd3Pwd 3

	#define startStatus 0
	#define menuEntry 1
	#define pwdInput 2
	#define grd1Menu 3
	#define grd2Menu 4
	#define grd3Menu 5

	extern char currentStatus, passwrdRead;
	extern struct{unsigned char edot[32];} code CCTAB[];
	extern struct{unsigned char edot[16];} code ECTAB[];
	//extern uchar userParamInput[PARAMlENGTH];
	uchar userParamInput[PARAMlENGTH] = {0};
	//uchar userParamInput[PARAMlENGTH];

//	extern uchar CCTAB[32];
//	extern uchar ECTAB[16];
	extern uchar GchrLocation;
	extern uchar parameterChanged=0xff;

	uchar paramNumSplit[PARAMlENGTH]; //参数拆分后保存的位置
	//bit paswrdRight TRUE;
	uchar passwrdsave[5]={0}; //{0}; ???
	uchar passwrdSet[3][5] = {{1,0,0,0,0}, {2,0,0,0,0}, {3,0,0,0,0}};
	float code parameterSet[25][4] = {
	// 预设值 当前值，最小值，最大值，
	//一级参数
		//{63, 63, 1, 99},	//一级参数密码
		{2, 2, 1, 99},	//校正液体密度
		{1000, 1000, 0, 60000},  //校正液体计数率
	//二级参数
		//{63, 63, 1, 99},	//二级参数密码
		{1.4, 1.4, 1, 99999},  //悬浮固体密度
		{1, 1, 0, 99},	//吸收系数
		{1, 1, 0, 99},	//传输液体密度
		{1, 1, 0, 99},	//密度输出下限
		{2, 2, 0, 99},	//密度输出上限
		{0, 0, 0, 99},	//浓度输出下限
		{100, 100, 0, 99999},  //浓度输出上限
		{0, 1, 0, 1},  //选择电流输出
		{9600, 9600, 4800, 115200},  //波特率
		{0, 0, 0, 1},  //校验方式
		{0, 0, 0, 0},  //设备号
		{0, 0, 0, 1},  //恢复设置 2-14
	//三级参数
		//{63, 63, 1, 99},	//三级参数密码
		{2, 0, 0, 0},	//校准密码
		{3, 0, 0, 0},	//新校准密码
		{4, 4, 3, 5},  //输入零点校准mA
		{20, 20, 19, 21},  //输入量程校准mA
		{0, 4, 3, 5},  //4mA输出校准mA
		{0, 20, 19, 21},  //20mA输出校准mA
		{12, 12, 4, 20},  //电流输出测试mA
		{0, 0, 0, 1},  //保存设置 15-22
		};


	//此数组专门保存当前所有的参数值，应保存在铁电存储中
	float parameterCurrent[25] = {0.0f};


unsigned char code allStringSet[112][16] = {
		//main status display
	{ji,shu,lv,chnmh,chn0,spn(4),chn1,chnxg,chns,0xff},
	{mi,spn(2),du,chnmh,chnN,chna,chnN,spn(2),chng,chnxg,chnc,chnm,0xff},
	{nong,spn(2),du,chnmh,chnP,chnS,spn(3),chnE,chnr,chnbfh,0xff},
	{spn(2),kun,spn(1),ming,spn(1),yee,spn(1),yann,0xff},

	//param select entry
	{spn(1),chn1,chndh,yii,jii,can,shu,she,zhi,0xff},
	{spn(1),chn2,chndh,er,jii,can,shu,she,zhi,0xff},
	{spn(1),chn3,chndh,shuu,chu,she,zhi,0xff},
	{0xff},
	//一级参数密码
	//fisrt param set //8
	{yii,jii,can,shu,mi,ma,0xff},
	{0xff},
	{spn(11),chn0,chn0,chn0,chn0,chn0,0xff},
	{0xff},

	{jiao,zhen,ye,ti,mi,du,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn1,chnjh,chn9,chn9,0xff},
	{0xff},
	{0xff},

	//5 X4
	{jiao,zhen,ye,ti,ji,shu,lv,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn0,chnjh,chn6,chn0,chn0,chn0,chn0,0xff},
	{0xff},
	{0xff},
	//二级参数密码
	//second param set  //20
	{er,jii,can,shu,mi,ma,0xff},
	{0xff},
	{spn(11),chnyh,chnyh,chnyh,chnyh,chnyh,0xff},
	{0xff},

	{xuan,fuu,gu,ti,mi,du,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn1,chnjh,chn9,chn9,chn9,chn9,chn9,0xff},
	{0xff},
	{0xff},


	{xi,shou,xii,shu,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn0,chnjh,chn9,chn9,0xff},
	{0xff},
	{0xff},

	{chuan,shuu,ye,ti,mi,du,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn0,chnjh,chn9,chn9,0xff},
	{0xff},
	{0xff},
	//10 X4
	{mi,du,shuu,chu,xia,xian,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn0,chnjh,chn9,chn9,0xff},
	{0xff},
	{0xff},

	{mi,du,shuu,chu,shang,xian,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn0,chnjh,chn9,chn9,0xff},
	{0xff},
	{0xff},

	{nong,du,shuu,chu,xia,xian,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn1,chnjh,chn9,chn9,chn9,chn9,chn9,0xff},
	{0xff},
	{0xff},

	{nong,du,shuu,chu,shang,xian,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn1,chnjh,chn9,chn9,chn9,chn9,chn9,0xff},
	{0xff},
	{0xff},


	{xuann,zhe,diann,liu,shuu,chu,0xff},
	//{spn(7),mi,du,diann,liu,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(7),mi,du,diann,liu,0xff},
	//15 X4
	{bo,te,lv,0xff},
	//{spn(11),chn9,chn6,chn0,chn0,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(11),chn9,chn6,chn0,chn0,0xff},

	{jiao,yan,fang,shi,0xff},
	//{spn(9),wu,jiao,yan,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(9),wu,jiao,yan,0xff},


	{she,bei,hao,0xff},
	//{spn(13),chn0,chn0,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(13),chn0,chn0,0xff},

	{hui,fu,she,zhi,0xff},
	//{spn(12),chnN,chno,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(12),chnN,chno,0xff},
	//三级参数密码 校准密码
	//third param set //18x4
	{jiao,zhun,mi,ma,0xff},
	{0xff},
	{spn(11),chnyh,chnyh,chnyh,chnyh,chnyh,0xff},
	{0xff},
	//{spn(11),chn0,chn0,chn0,chn0,0xff},
	//20 X4
	{xin,jiao,zhun,mi,ma,0xff},
	{0xff},
	{0xff},
	{0xff},
	//{spn(11),chn0,chn0,chn0,chn0,0xff},

	{shuu,ru,ling,dian,jiao,zhun,chnm,chnA,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn3,chnjh,chn5,0xff},
	//{spn(10),chn4,chndh,chn0,chn0,chn0,0xff},
	{0xff},
	{0xff},
	//{spn(10),chn4,chndh,chn0,chn0,chn0,0xff},

	{shuu,ru,liang,cheng,jiao,zhun,chnm,chnA,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn1,chn9,chnjh,chn2,chn1,0xff},
	//{spn(10),chn2,chn0,chndh,chn0,chn0,0xff},
	{0xff},
	{0xff},
	//{spn(10),chn2,chn0,chndh,chn0,chn0,0xff},

	{chn4,chnm,chnA,shuu,chu,jiao,zhun,chnm,chnA,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn3,chnjh,chn5,0xff},
	//{spn(10),chn0,chndh,chn0,chn0,chn0,0xff},
	{0xff},
	{0xff},
	//{spn(10),chn4,chndh,chn0,chn0,chn0,0xff},

	{chn2,chn0,chnm,chnA,shuu,chu,jiao,zhun,chnm,chnA,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn3,chnjh,chn5,0xff},
	//{spn(10),chn0,chndh,chn0,chn0,chn0,0xff},
	{0xff},
	{0xff},
	//{spn(10),chn2,chn0,chndh,chn0,chn0,0xff},
	//25 X4
	{diann,liu,shuu,chu,che,shii,chnm,chnA,0xff},
	{chnR,chna,chnn,chng,chne,chnmh,chn4,chnjh,chn2,chn0,0xff},
	//{spn(10),chn1,chn2,chndh,chn0,0xff},
	{0xff},
	{0xff},
	//{spn(10),chn1,chn2,chndh,chn0,0xff},

	{bao,cun,she,zhi,0xff},
	//{spn(12),chnN,chno,0xff},
	{0xff},
	{0xff},
	{0xff},
	//108 lINE
	{mi,ma,cuo,spn(2),chnE,chnS,chnC,qu,xiao,0xff},
	{shu,zhii,cuo,spn(2),chnE,chnS,chnC,qu,xiao,0xff},
	{chnS,chnE,chnT,que,ren,spn(2),chnE,chnS,chnC,qu,xiao,0xff},
	{0xff},

	//{spn(12),chnN,chno,0xff},
};

/*
*  获取密度公式SG = STG + (1/ML) * ((ln(S4) - ln(CR)))
*/
float cr_calc(float density, float liquid_cr, float input_cr)
{
	float ML = 1.0f;

	return density + ((1 / ML) * (log(liquid_cr) - log(input_cr)));
}

/*
* 获取浓度公式计算
*/
float concentration_calc(float SG, float SSG, float LSG)
{
	return (((SG - LSG) * SSG) * 100) / ((SSG - LSG) * SG);
}

float input_cr_get(void)
{
	/* TODO:从IO口中获取 */
	return 1000.0f;
}

uchar pswd_cmp(uchar *src, uchar *dest, uchar len)
{
	uchar i = 0;

	for (i = 0; i < len; i++) {
		if (src[i] != dest[i])
			return 0;
	}

	return 1;
}

void paswd_disp(menu_disp_t *disp)
{
	uchar *default_pswd = passwrdSet[disp->top_menu_disp_status];
	uchar i;

	if (disp->pswd_cmp_flag == TRUE) {
		disp->pswd_enter_flag = TRUE;
		if (pswd_cmp(default_pswd, passwrdsave, 5))	{
			disp->sub_menu_disp_flag = TRUE;
			disp->pswd_enter_flag = FALSE;
			disp->pswd_menu_disp_flag = FALSE;
			disp->sub_menu_param_enter = FALSE;
			dwnKeyValLast = dwnKeyVal = 0;
			userParamClear();
			sub_menu_disp(disp);
		} else {
			//密码错误显示信息
			//同时将进入密码输入flag
			SaveCancel();
			disp->sub_menu_disp_flag = FALSE;
		}
		for (i = 0; i < 5; i++)
			passwrdsave[i] = 0;
		disp->pswd_cmp_flag = FALSE;
		return;
	}

	LCD_Clear();
	//显示输入密码界面，并回读输入密码，
	//如果正确则进入行相应的菜单循环
	switch (disp->top_menu_disp_status)
	{
		case 0:
			StaticDisp(8,4,3);
			PswdSetLogic(passwrdsave);
			printf("\n paswd %d \n" , (short) disp->top_menu_disp_status);
		//ReadPwd();
			break;
		case 1:
			StaticDisp(20,4,3);
			PswdSetLogic(passwrdsave);
			printf("\n paswd %d \n" , (short) disp->top_menu_disp_status);
		//ReadPwd();
			break;
		case 2:
			StaticDisp(72,4,3);
			PswdSetLogic(passwrdsave);
			printf("\n paswd %d \n" , (short) disp->top_menu_disp_status);
		//ReadPwd();
			break;
		default:
			break;
	}

	//passwrdRead = ReadPwd();

	return;
}

void sub_menu_disp(menu_disp_t *disp)
{
	uchar cur_status = disp->sub_menu_disp_status;
	uchar colpos = 0xff;

	switch (disp->top_menu_disp_status) {
	case 0:  // 进入子菜单1
			//passwrd=1;
		LCD_Clear();
		StaticDisp(3*4+(cur_status)%2*4,4,3);
		colpos = cur_status % 2;
		ParamSetLogic(colpos, &parameterCurrent[colpos]);
		disp->sub_menu_param_status = colpos;
		break;
	case 1:  // 进入子菜单2
		//passwrd=2;
		LCD_Clear();
		StaticDisp(7*4+(cur_status-3)%12*4,4,3);
		colpos = 2 + (cur_status-3) % 12;
		ParamSetLogic(colpos, &parameterCurrent[colpos]);
		disp->sub_menu_param_status = colpos;
		break;
	case 2:  // 进入子菜单3
			//passwrd=3;
		LCD_Clear();
		StaticDisp(18*4+(cur_status-3)%8*4,4,3);
		colpos = 14+(cur_status-3)%8;
		ParamSetLogic(colpos, &parameterCurrent[colpos]);
		disp->sub_menu_param_status = colpos;
		break;
	default:
		break;
	}

	printf("set param parameterCurrent[colpos] %f %f\n", parameterCurrent[colpos], fabs(parameterCurrent[colpos] - parameterSet[colpos][0]));

	/* 没获得参数时，保持缺省参数 */
	if (colpos != 0xff && (fabs(parameterCurrent[colpos] - parameterSet[colpos][0]) >= 0.0001f)) {
		parameterCurrent[colpos] = parameterSet[colpos][0];
		disp->sub_menu_param_enter = TRUE;
	}

	printf("get current %d %f cur_status %d sub status %d\n", (short)colpos, parameterCurrent[colpos], (short)disp->top_menu_disp_status, (short)cur_status);
}

void DisplayLogic(menu_disp_t *disp)
{
	uchar LoopMenuNum = 0;
	uchar top_disp_status = disp->top_menu_disp_status;
	printf ("start menu%d\n", disp->menu_disp_flag);

	//0xff 无高亮显示行
	//取消键显示初始界面,并清零所有按键数，清除密码
	if (disp->menu_disp_flag) {
		uchar i;
		for (i = 0; i < 5; i++)
			passwrdsave[i] = 0;
		LCD_Clear();
		StaticDisp(0,4,0xff);
		return;
	}

#if 1
	if (disp->sub_menu_disp_flag) {
		disp->pswd_enter_flag = FALSE;
		sub_menu_disp(disp);
		return;
	}

	if (disp->pswd_menu_disp_flag) {
		disp->top_menu_disp_flag = FALSE;
		paswd_disp(disp);
		return;
	}

	if (disp->top_menu_disp_flag) {
		LCD_Clear();
		StaticDisp(4, 4, top_disp_status);
		return;
	}
#else
	switch (top_disp_status)
	{
		//显示菜单入口界面
		case 1:
			//dwnKeyVal = dwnKeyVal%3;
			LCD_Clear();
			StaticDisp(4,4,dwnKeyVal%3);
			printf("dk %d %d\n", (short) dwnKeyVal%3, (short) dwnKeyVal);
			rgtKeyVal=0;
			//escKeyVal=0;
//			if ( setKpressed )
//				{
//					currentStatus ++ ;
//				}

			break;
		//显示输入密码界面
		case 2:
			paswd_disp(NULL);
			break;

		case 4:  // 进入子菜单1
				//passwrd=1;
				LCD_Clear();
				StaticDisp(3*4+(setKeyVal-3)%2*4,4,3);
				ParamSetLogic((setKeyVal-3)%2);	break;
				break;
		case 5:  // 进入子菜单2
				//passwrd=2;
				LCD_Clear();
				StaticDisp(7*4+(setKeyVal-3)%12*4,4,3);
				ParamSetLogic(2+(setKeyVal-3)%12);	break;
				break;
		case 6:  // 进入子菜单3
				//passwrd=3;
				LCD_Clear();
				StaticDisp(18*4+(setKeyVal-3)%8*4,4,3);
				ParamSetLogic(14+(setKeyVal-3)%8);	break;
				break;

		default:  // setkey number >=3
				printf ( "error mode %d\n", (short) currentStatus);
				break;
	}
#endif
}




//完成的功能：把参数数字拆分成字符，显示在第三行
//把输入的字符数字化，存储在变量中
void ParamSetLogic(uchar parmCurLine, float *outVal)
{
	uint remainder=0;
	//uchar paramNumSplit[5];
	uchar i=0, *chr, j=0;
	uint quitioent=0;
	float paramNum;
	printf("parmCurLine %d\n", (short)parmCurLine);
	if (fabs(parameterCurrent[parmCurLine] - parameterSet[parmCurLine][0]) < EPS
		|| fabs(parameterCurrent[parmCurLine] - parameterSet[parmCurLine][2]) < EPS)
		paramNum = parameterSet[parmCurLine][0];
	else
		paramNum = parameterSet[parmCurLine][0];

	printf("paramNum %f\n", paramNum);

	floatToChar(&paramNum, paramNumSplit);
	DispPramOnSecLine(paramNumSplit);
	ParameterInputDisplay(paramNumSplit, outVal);
}

//密码显示和处理
void PswdSetLogic(uchar *pswd)
{
	//uint remainder=0;
	//uchar paramNumSplit[5];
//	uchar *chr;
	//uint quitioent=0;
	//float paramNum, paramNumInt;
	//paramNum=parameterSet[parmCurLine][0];
	//NumberToChar(&paramNum);
//	chr = &pswd;
	//DispPramOnSecLine(chr);
	passwordDisplayGet(pswd);
	//ParameterInputDisplay(chr);
}

//将指针指向的一个数组以字符显示出来
void DispPramOnSecLine(uchar *chr)
{
	uchar *chrp,i=0;
	//uchar j;
	for (i = 0; i < 5; i++)	{
		chrp = &ECTAB[chr[i]];
		PutChnChar(chrp, 4, 0 + i, 0, 1, 1);
	}
}

//将一个总位数为5位的数字按位拆分到一个
//长度为5的数组里面
//如302.953 转成 paramNumSplit=[3][0][2][.][9]
void floatToChar(float *num, char *str)
{
	float paramNum = *num;
	float paramNumFrc;
	float numVal;
	uint paramNumInt;
	uint quotient, remainder;
	uint temp[PARAMlENGTH];
	uchar i=0, j=0, k = 0;
	uchar extra = 0;
	uchar Frc;
	if  (paramNum > 99999.0f)
		paramNum = 99999.0f;
	else if (paramNum < 0.001)
		paramNum = 0.0f;
	//paramNum = 20.05;
	paramNumFrc = modf(paramNum, &numVal);
	quotient = paramNumInt = (uint)numVal;
	printf("paramNumFrc %f numVal %f paramNumInt %d\n", paramNumFrc, numVal, paramNumInt);
	for (i = 0; i < PARAMlENGTH; i++) {
		remainder = quotient % 10;
		quotient = quotient / 10;

//		if (remainder == 0 && quotient <= 9) {
//			remainder = quotient;
//		}

		temp[i] = remainder;
//		printf("temp[i]  %d %d\n", temp[i], quotient);

		if (quotient == 0)
			break;
	}

	for (j = 0; j < i; j++)
		str[j] = temp[i - j];

//	printf("i %d\n", (short)i);

	Frc = i + 1;
	str[Frc] = 64;
	if (Frc < PARAMlENGTH -  1) {
		for (k = 0; k < PARAMlENGTH - 1 - Frc; k++) {
			paramNumFrc = paramNumFrc * 10;
			temp[k] = (uint)paramNumFrc;
			paramNumFrc -= temp[k];
		printf("temp[i]  %d %d\n", temp[k], (short) k);
		}

//		str[Frc] = 64;
		for (j = 1; j < (PARAMlENGTH - Frc); j++) {
			str[Frc + j] = temp[j - 1];
			printf("str[Frc + j] %d \n", (uint) str[Frc + j]);
		}
	}
	for (j = 0; j < 5; j++) {
		printf("parm i %d \n", (uint) str[j]);
	}

#if 0
	//将paramNum拆分成整数部分paramNumInt和小数部分paramNumFrc
	//类型转换为uint才能取模
	quitioent=paramNumInt;
	//printf("parm i %d \n", (uint) quitioent);
	//i从1开始，与后面转录匹配
	for(i=1;i<6;i++)
		{

			remainder=quitioent%10; //余数
			quitioent=quitioent/10; //商
			temp[i-1]=remainder;
			//商为0时转换结束
			if(quitioent==0)
				{
					break;
				}
		}
	//将上面temp的内容按顺序写到paramNumSplit中
	for(j=0;i>0;i--)
		{
			paramNumSplit[j]=temp[i-1];
			//printf("parm j %d %d\n", (uint) paramNumSplit[j], (short) j);
			j++;
			//printf("parm j %d %d\n", (uint) paramNumSplit[j], (short) j);
		}
	//数组未满加小数点 点号为64
	if(j<5)
		{
			paramNumSplit[j]=64;
			j++;
		}

	//把小数部分跟在小数点后，如果总位数超过5位就退出
	for(;j<5;j++)
		{
			//类型转换，才能取模运算
			//小数部分依次乘10取模，填充数组
			quitioent=paramNumFrc*10;
			remainder=quitioent%10;
			paramNumSplit[j]=remainder;
			///printf("parm i %d \n", (uint) paramNumSplit[j]);
		}
	for (j = 0; j < 5; j++) {
		printf("parm i %d \n", (uint) paramNumSplit[j]);
	}
#endif
}

#define IS_NUM_CHAR(num) (num >= 0 && num <= 9)
 //将数组paramNumSplit[5]的字符转成数字
void CharToNumber(uchar *chr, float *number, uchar len)
{
	uchar i;
	float paramNum = 0.0f;
	double dec = 1;
	uchar dotpos = ~0;

	/*
	 * 获取浮点数的实数部分，并将虚数部分转换成实数
	 * 转换完成后，将虚数部分除以10^n，完成参数的转换
	 * 例如: char input[5]    float     float
	 *            1.083   --> 1083 --> 1083 / 10^3 = 1.083
	 */
	for (i = 0; i < len; i++) {
		if (!IS_NUM_CHAR(chr[i])) {
			dotpos = i;
		} else {
			paramNum = (paramNum * 10) + chr[i];
		}
	}

	if (dotpos == ~0) {
		dec = 1.0f;
	} else {
		uchar power = i - dotpos - 1;
		power > 0 ? (dec = pow(10, power)) : (dec = 1.0f);
	}

	paramNum = paramNum / dec;
	*number = paramNum;
	printf("paramNumEnd %f %f \n", paramNum, *number);
	//printf("paramNum %d \n", paramNum);
	//printf("param setted %f %d \n", paramNum, dec);
}

void passwordDisplayGet(uchar *passwd)
{
	uchar i = 0;
	uchar *chrp;
	uchar hiLight;

	i = rgtKeyVal % PARAMlENGTH;
	if (userParamInput[i] > 10)
		userParamInput[i] = 10;

	userParamInput[i] = (userParamInput[i] + dwnKpressed) % 11;
	for (i = 0; i < PARAMlENGTH; i++)
		passwd[i] = userParamInput[i];

	for (i = 0; i < PARAMlENGTH; i++) {
		uchar charIndex = userParamInput[i];
		if(userParamInput[i] >= 10)
			charIndex = 64;

		chrp = &ECTAB[charIndex];
		if ((rgtKeyVal %  PARAMlENGTH) == i)
			hiLight = 1;

		PutChnChar(chrp, 4, 11 + i, 0, 1, hiLight);
		hiLight =  0;
	}
}

void userParamClear(void)
{
	uchar i;
	for (i = 0; i < 5; i++)
		userParamInput[i] = 0;
}

//在第4行显示5个小点占位符，高亮最左位
//等待用户输入
//右键循环移动，下移循环选中0-9,.号11个字符
//set 确定， esc 取消
void ParameterInputDisplay(uchar *userParam, float *outval)
{
	//uchar userParamInput[PARAMlENGTH];
	//uchar userParamInput[PARAMlENGTH];
	uchar numberInput=0,hiLight=0,rgtKeyValLast;
	uchar i=0, *chrp;
	float number=0, numberDft=0,nbVal;
	for (i = 0; i < PARAMlENGTH; i++) {
		userParamInput[i] = userParam[i];
		if (userParamInput[i] > 10) {
			userParamInput[i] = 10;
		}

		printf("userParam[%d] %d\n", (short)i, (short)userParam[i]);
	}

	i = rgtKeyVal % PARAMlENGTH;

	userParamInput[i] = (userParamInput[i] + dwnKpressed) % 11;

	//显示当前值
	for (i = 0; i < PARAMlENGTH; i++) {
		uchar charIndex = userParamInput[i];
		if(userParamInput[i] >= 10)
			charIndex = 64;

		chrp = &ECTAB[charIndex];
		if ((rgtKeyVal %  PARAMlENGTH) == i)
			hiLight = 1;

		PutChnChar(chrp, 4, 11 + i, 0, 1, hiLight);
		hiLight =  0;
	}

	CharToNumber(userParamInput, &number, sizeof(userParamInput));

	if (outval) {
		if (number < 0.00001)
			number = 10000000.0f;
		*outval = number;
	}
}


//保存或取消， 反回0取消，非0，保存。
//按下set 键时在第2行显示 保存或取消，等待确认。
void SaveCancel(void)
{


	//LCD_ClearLine(6,0);
	//StaticDisp(106,1,0);
	PutChnLine(106,3,0);
}


// 显示一行字符 （内容，显示位置，是否高亮）
// 如果数组值小于70 中文字符，70－200 英文字符，200以上空格字符数
void PutChnLine(uchar DBrowLine, uchar PageLine, uchar hiLightOn)
{
	uchar *chr, chrType=0;
	uchar pageNum;
	uchar ichar=0, charSqu=0;
	//uchar dispLine=0, charLoca=0, chrLen=0;
	//清行
	LCD_ClearLine(6,0);
	//Len =16;
	pageNum=DBrowLine;
	//GchrLocation=0;
			GchrLocation=0;
			//printf("line %d\n", (short) pageNum);
			for(ichar=0; ichar<16; ichar++)
				{
					chr = &allStringSet[pageNum][ichar];
					charSqu = *chr;
					//如果是结束符0xff 结束当前行显示
					if(charSqu==0xff)
						{
							break;
						}
					else
						{
							if(charSqu>200)
								{
									GchrLocation += (charSqu-200);
								}
							else
								{
									if(charSqu<100)
										{
											chrType=2;
											chr = &CCTAB[charSqu];
										}
									else if( charSqu>=100 )
										{
											chrType=1;
											charSqu -=100;
											chr = &ECTAB[charSqu];
											//i=charSqu;
											//printf("putchar %d \n", (short) i);
										}
									else {	printf("error error\n");	}
									PutChnChar(chr, 2*PageLine, GchrLocation,0,chrType,hiLightOn);
									//GchrLocation +=chrType*8;
									GchrLocation +=chrType;
									//hiLightOn=0;
								}
						}
		}
}


//显示多行字符（显示内容，显示行数量，高亮哪一行（0123））
void StaticDisp(uchar DBrowLine, uchar RowNub, uchar hightLightRow)
{

	uchar dispLine = 0, hiLightOn = 0;
	uchar Len = 0;
	for (dispLine = 0; dispLine < RowNub; dispLine++)
		{
			if (dispLine == hightLightRow)
			{
				hiLightOn = 1;
			}
			PutChnLine(DBrowLine+dispLine, dispLine, hiLightOn);
			hiLightOn=0;
		}
}



//把要显示的字符转换到码表 allStringSet数组的字符
//要转换才能输出,一次只显示一个字符
//接收一个uchar数，输出一个码表地址指针
void NumberToCharTab(uchar Val, uchar* chrp[], uchar* type )
{
	uchar charSqu=0, chrType;
					charSqu = Val;
					//如果是结束符0xff 结束当前行显示
					if(charSqu==0xff)
						{
							type = &charSqu;
						}
					else
						{
							if(charSqu>200)
								{
									GchrLocation += (charSqu-200)*8;

								}
							else
								{
									if(charSqu<100)
										{
											chrType=2;
											chrp = &CCTAB[charSqu];
										}
									else if( charSqu>=100 )
										{
											chrType=1;
											charSqu -=100;
											chrp = &ECTAB[charSqu];
											//i=charSqu;
											//printf("putchar %d \n", (short) i);
										}
									else {	printf("error error\n");}
								}

						}
}

// 接收两个参数，清除行数，从第几列开始清，清多少位
//clearLength 高字节表示从第几个字符（8位）开始，
//低字节表示清除的位数长度,如果clearLength=0,清除整行
void LCD_ClearLine(uchar lineNum, uchar clearLength)
{
		uchar colStart=0, colLeng=0;
		uchar i,j;
		colLeng=0x0F&clearLength;
		colStart=0xf0&clearLength;
		colStart=colStart/16;
		colStart=colStart*8;
		cl();
		if(colStart >= 64) //大于64清右屏
			colStart=colStart-64;
			{cr();}
		if(clearLength==0)
			{
				lcd_fullEnable();
				colLeng=64;
			}
				SendCommand(COL+colStart);
		for(j=0;j<2;j++)
			{
				SendCommand(PAGE+lineNum+j);
				CheckBusy();
				for(i=0;i<colLeng;i++)
					{
						if((colStart + i) >=64)
							{
								cr();
								SendCommand(COL+0); //跨屏就从右屏0列开始
							}
						SendData(0x00);  //dat1
					}
			}
		lcd_fullDisable();
}

