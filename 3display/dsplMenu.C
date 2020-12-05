
#include "..\1head\0common.h"
#include "dsplMenu.h"
//#include "defineSTC.h"
#include "display.H"
#include "..\5msgCalc\msgCalc.h"

	#define Grd1Pwd 1
	#define Grd2Pwd 2
	#define Grd3Pwd 3

	#define startStatus 0
	#define menuEntry 1
	#define pwdInput 2
	#define grd1Menu 3
	#define grd2Menu 4
	#define grd3Menu 5
	
	extern bit setKpressed, rgtKpressed, dwnKpressed, escKpressed; 
	extern char currentStatus;
	extern struct{unsigned char edot[32];} code CCTAB[];
	extern struct{unsigned char edot[16];} code ECTAB[];
	//extern uchar userParamInput[PARAMlENGTH];
	uchar userParamInput[PARAMlENGTH];
	//uchar userParamInput[PARAMlENGTH];

//	extern uchar CCTAB[32];
//	extern uchar ECTAB[16];
	extern uchar GchrLocation;
	extern uchar parameterChanged=0xff;
	
	uchar paramNumSplit[PARAMlENGTH]; //参数拆分后保存的位置
	
	uchar passwrd=0;
	uint code parameterSet[25][4] = {
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
	float parameterCurrent[30] = {0,0,0,0,0,0,0,0,0,0, 
								 0,0,0,0,0,0,0,0,0,0,
								 0,0,0,0,0,0,0,0,0,0};
	

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
	
	//second param set  //20
	{er,jii,can,shu,mi,ma,0xff},
	{0xff},
	{spn(11),chn0,chn0,chn0,chn0,chn0,0xff},
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
	
	//third param set //18x4
	{jiao,zhun,mi,ma,0xff},
	{0xff},
	{spn(11),chn0,chn0,chn0,chn0,chn0,0xff},
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

void DisplayLogic(void)
{
	
	uchar LoopMenuNum=0;
	//uchar currentStatus = 0;  //状态机标识
	//0xff 无高亮显示行
	//取消键显示初始界面,并清零所有按键数，清除密码
	if(escKpressed) 
		{
			setKeyVal=0; 
			rgtKeyVal=0;
			dwnKeyVal=0;
			passwrd =0;
			escKeyVal=0;
			currentStatus = 0; //显示开始/状态界面
			setKpressed = 0;
			rgtKpressed = 0;
			dwnKpressed = 0;
			escKpressed = 0;
		}

	switch (currentStatus)
		{	
		//显示状态界面
		case 0: 
			LCD_Clear();
			StaticDisp(0,4,0xff); 
			//rgtKeyVal=0;
			//dwnKeyVal=0;
			//escKeyVal=0;
			if ( setKpressed )
				{
					currentStatus ++ ;
				}	

			break;
		//显示菜单入口界面
		case 1: 
			//dwnKeyVal = dwnKeyVal%3;
			LCD_Clear();
			StaticDisp(4,4,dwnKeyVal%3); 
			printf("dk %d %d\n", (short) dwnKeyVal%3, (short) dwnKeyVal);
			rgtKeyVal=0;
			//escKeyVal=0;
			if ( setKpressed )
				{
					currentStatus ++ ;
				}	

			break;
		//显示输入密码界面
		case 2: 
				//rgtKpressed = 0;
				//dwnKeyVal=0;
				dwnKeyVal = 0;
				///???dwnKeyVal += rgtKpressed;
				if ( dwnKpressed )
					{
						currentStatus ++ ;
					}	

				LCD_Clear();
				if(dwnKeyVal%3 == 0) 
				{
					StaticDisp(8,4,3); 
				}
				
				//if(dwnKeyVal%3 == 0) {StaticDisp(20,4,3);}
				if(dwnKeyVal%3 == 1) {StaticDisp(20,4,3);}
				if(dwnKeyVal%3 == 2) {StaticDisp(72,4,3);}
				passwrd=0;
				switch (passwrd)
					{
						case 0: 
							StaticDisp(8,4,3); 
						//ReadPwd();
							break;  
						case 1: 
							StaticDisp(20,4,3);
							break; 								
						case 2: 
							StaticDisp(72,4,3); 
							break; 
					}
				break;

		case 3: 
				rgtKeyVal=0;
				//dwnKeyVal=0;
				LCD_Clear();
				passwrd=3;
				switch (dwnKeyVal%3)
					{
						case 0: StaticDisp(8,4,3); 
						//ReadPwd();
						break;  
						case 1: StaticDisp(20,4,3); break; 								
						case 2: StaticDisp(72,4,3); break; 
					}
				break;
		default:  // setkey number >=3
				//passwrd=3;
				LCD_Clear();
				//ReadPwd();
				switch (passwrd)
					{
						//在3个字菜单中循环
						case Grd1Pwd: StaticDisp(3*4+(setKeyVal-3)%2*4,4,3); 
								ParamSetLogic((setKeyVal-3)%2);	break;  //2 sub menue
						case Grd2Pwd: StaticDisp(7*4+(setKeyVal-3)%12*4,4,3); 
								ParamSetLogic(2+(setKeyVal-3)%12);	break; //12
						case Grd3Pwd: StaticDisp(18*4+(setKeyVal-3)%8*4,4,3);
								ParamSetLogic(14+(setKeyVal-3)%8);	break; //8
					}
				break;
		}
	//printf("menue dispalyed done\n");
}




//完成的功能：把参数数字拆分成字符，显示在第三行
//把输入的字符数字化，存储在变量中
void ParamSetLogic(uchar parmCurLine)
{
	uint remainder=0;
	//uchar paramNumSplit[5];
	uchar i=0, *chr, j=0;
	uint quitioent=0;
	float paramNum, paramNumInt;
	//paramNum=parameterSet[i][j];
	
	//所有的参数不能超限，超限截止
	//paramNum=32.59;
	paramNum=parameterSet[parmCurLine][0];
	//paramNum=parameterCurrent[parmCurLine];
	//paramNum=56;
	//paramNum =4;
	NumberToChar(&paramNum);
//	for(i=0;i<5;i++)
//		{ printf("parm i %d %d\n", (uint) paramNumSplit[i], (short) i); }
	chr = &paramNumSplit[0];
	DispPramOnSecLine(chr);
	
//	CharToNumber(chr, &paramNum);
	//chr = &paramNumSplit;
//	chr = &paramNumSplit[0];
	//DispPramOnThirdLine(chr);
	ParameterInputDisplay(chr);

	    //parameterSet[i][j]=paramNum;

}

//将指针指向的一个数组以字符显示出来
void DispPramOnSecLine(uchar *chr)
{
	uchar *chrp,i=0;
	//uchar j;
	for(i=0;i<5;i++)
		{
//			j=chr[i];
//			printf("%d \n", (short) j);
			chrp = &ECTAB[chr[i]];
			PutChnChar(chrp, 4, 0+i,0,1,1);
		}
}

//将一个总位数为5位的数字按位拆分到一个
//长度为5的数组里面
//如302.953 转成 paramNumSplit=[3][0][2][.][9]
void NumberToChar(float *chr) 
	{
		float paramNum, paramNumFrc, paramNumInt;
		uint quitioent, remainder;
		uint temp[PARAMlENGTH];
		uchar i=0, j=0;
		paramNum=*chr;
		if(paramNum>99999) 
			{
				paramNum=99999;
			}
		else if(paramNum<0.001) 
			{
				paramNum=0;
			}
		
		//将paramNum拆分成整数部分paramNumInt和小数部分paramNumFrc 
		paramNumFrc=modf(paramNum, &paramNumInt);
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
	}

//将数组paramNumSplit[5]的字符转成数字
void CharToNumber(uchar *chr[5], float *number)
{
	uchar *chrp;
	uchar i,j;
	float paramNum;
	uint dec=1;
//	userParamInput[0]=2; 
//	userParamInput[1]=0;
//	userParamInput[2]=1;
//	userParamInput[3]=0;
//	userParamInput[4]=10;

	//chrp=&paramNumSplit[0];
	chrp=chr;
	chrp=userParamInput;
	if( userParamInput[0]>=0 && userParamInput[0] <=9)
		{paramNum = userParamInput[0];}
	else {paramNum=0; dec=10000;}
	//paramNum=0;
	//paramNum=*chrp;
	for(i=1;i<5;i++)
		{
			if(*(chrp+i)>9 && dec==1)
				{
					dec=1*pow(10,(5-i));
					//printf("paramNumi %d \n", (short) dec);
					//printf("paramNumi %f \n", dec);
					printf("goes11");
					*(chrp+i)=0;
				}
			else if(*(chrp+i)>9 && dec!=1) 
					{
						*(chrp+i)=0;
						printf("goies22");
					}
			else{
			printf("goies33");
			//paramNum = paramNum*10 + *(chrp+i);
			}
			paramNum = paramNum*10 + *(chrp+i);
			printf("paramNum %f %d %d \n \n", paramNum, dec, (short) i);

		}
		
		paramNum = paramNum/dec;
		*number = paramNum;
		printf("paramNumEnd %f %f \n", paramNum, *number );
		//printf("paramNum %d \n", paramNum);
		//printf("param setted %f %d \n", paramNum, dec);		
}


//在第4行显示5个小点占位符，高亮最左位
//等待用户输入
//右键循环移动，下移循环选中0-9,.号11个字符
//set 确定， esc 取消
void ParameterInputDisplay( uchar * userParam) 
{
	//uchar userParamInput[PARAMlENGTH];
	//uchar userParamInput[PARAMlENGTH];
	uchar numberInput=0,hiLight=0,rgtKeyValLast;
	uchar i=0, *chrp;
	float number=0, numberDft=0,nbVal;
	//uchar save, cancel;
	if(setKeyValLast!= setKeyVal) {
			userParamInput[0]=userParam[0];	
			userParamInput[1]=userParam[1];
			userParamInput[2]=userParam[2];
			userParamInput[3]=userParam[3];
			userParamInput[4]=userParam[4];
			rgtKeyVal=0;
			rgtKeyValLast=0;
			dwnKeyVal=0;
			//rgtKeyValLast=0
			//dwnKeyVal=0; 
		}

		if(rgtKeyVal!= rgtKeyValLast)
			{dwnKeyVal=0; dwnKeyValLast=0;}
			//printf("dwnkeyk %d\n", (short) dwnKeyVal); 
		
		//把当前高亮位的输入写入数组内
		//numberInput = dwnKeyVal%11;
//		if(numberInput == 10)
//			{  
//				numberInput=64; //点号
//			}
		//printf("rightkey %d %d\n", (short) rgtKeyVal, (short) rgtKeyValLast, (short) dwnKeyVal);
		//转换一次，如果是点号（64）则在数字上表示为10，以便进行显示
		//点号在数组内存储为64，显示时是10
		i = rgtKeyVal%PARAMlENGTH;
		if(userParamInput[i]>10)
			{userParamInput[i]=10;}
	
		//for(i=0;i<PARAMlENGTH;i++) {printf("UP %d\n", (short) userParamInput[i] ); }
		//i = rgtKeyVal%PARAMlENGTH;
		//delaym(1);
		//printf("UPp %d %d %d \n", (short) userParamInput[i], (short) dwnKeyVal, (short) userParam[i]);
		userParamInput[i] = (userParamInput[i]+dwnKeyVal-dwnKeyValLast)%11;
		//printf("UPp %d %d %d \n", (short) userParamInput[i], (short) dwnKeyVal, (short) userParam[i]);
		rgtKeyValLast=rgtKeyVal;
		//for(i=0;i<PARAMlENGTH;i++) {printf("UPX %d\n", (short) userParamInput[i] ); }
		
		//显示当前值
		//chrp = &userParamInput;
		for(i=0;i<PARAMlENGTH;i++)
			{
				//printf("paramNum %d - %d \n", (short) userParamInput[i], (short) chrp);
				if(userParamInput[i]>=10) {userParamInput[i]=64; }
				chrp = &ECTAB[userParamInput[i]];
				
				//chrp = &ECTAB[userParamInput[i]];
				//printf("paramNum %d - %d \n", (short) userParamInput[i], (short) chrp);
				if((rgtKeyVal%PARAMlENGTH) == i)
					{hiLight=1; }
				//PutChnChar(chrp, 4, (11+i)*8,0,1,hiLight);
				PutChnChar(chrp, 4, 11+i,0,1,hiLight);
				hiLight=0;	
			}
		
		CharToNumber(userParamInput , &number);
		CharToNumber(userParamInput , &numberDft);
		if(numberDft!=number ) {printf("param changed\n");}
		
		printf("paramVal DFT %f %f",  number, numberDft);
		SaveCancel();
		
		//读值并显示
		//if()	
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

