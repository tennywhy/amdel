
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
	extern char currentStatus, passwrdRead;
	extern struct{unsigned char edot[32];} code CCTAB[];
	extern struct{unsigned char edot[16];} code ECTAB[];
	//extern uchar userParamInput[PARAMlENGTH];
	uchar userParamInput[PARAMlENGTH];
	//uchar userParamInput[PARAMlENGTH];

//	extern uchar CCTAB[32];
//	extern uchar ECTAB[16];
	extern uchar GchrLocation;
	extern uchar parameterChanged=0xff;
	
	uchar paramNumSplit[PARAMlENGTH]; //������ֺ󱣴��λ��
	
	uchar passwrd=0;
	uint code parameterSet[25][4] = {
	// Ԥ��ֵ ��ǰֵ����Сֵ�����ֵ��
	//һ������
		//{63, 63, 1, 99},	//һ����������
		{2, 2, 1, 99},	//У��Һ���ܶ�
		{1000, 1000, 0, 60000},  //У��Һ�������
	//��������		
		//{63, 63, 1, 99},	//������������
		{1.4, 1.4, 1, 99999},  //���������ܶ�
		{1, 1, 0, 99},	//����ϵ��
		{1, 1, 0, 99},	//����Һ���ܶ�
		{1, 1, 0, 99},	//�ܶ��������
		{2, 2, 0, 99},	//�ܶ��������
		{0, 0, 0, 99},	//Ũ���������
		{100, 100, 0, 99999},  //Ũ���������
		{0, 1, 0, 1},  //ѡ��������
		{9600, 9600, 4800, 115200},  //������
		{0, 0, 0, 1},  //У�鷽ʽ
		{0, 0, 0, 0},  //�豸��
		{0, 0, 0, 1},  //�ָ����� 2-14
	//��������
		//{63, 63, 1, 99},	//������������
		{2, 0, 0, 0},	//У׼����
		{3, 0, 0, 0},	//��У׼����
		{4, 4, 3, 5},  //�������У׼mA
		{20, 20, 19, 21},  //��������У׼mA
		{0, 4, 3, 5},  //4mA���У׼mA
		{0, 20, 19, 21},  //20mA���У׼mA
		{12, 12, 4, 20},  //�����������mA
		{0, 0, 0, 1},  //�������� 15-22
		};


	//������ר�ű��浱ǰ���еĲ���ֵ��Ӧ����������洢��
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
	//һ����������
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
	//������������
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
	//������������ У׼����
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

void paswd_disp(menu_disp_t *disp)
{

	LCD_Clear();
	//��ʾ����������棬���ض��������룬
	//�����ȷ���������Ӧ�Ĳ˵�ѭ��
	switch (disp->top_menu_disp_status)
	{   
		case 0: 
			StaticDisp(8,4,3); 
			passwrd = Grd1Pwd;
		//ReadPwd();
			break;	
		case 1: 
			StaticDisp(20,4,3);
			passwrd = Grd2Pwd;
		//ReadPwd();
			break;								
		case 2: 
			StaticDisp(72,4,3); 
			passwrd = Grd3Pwd;
		//ReadPwd();
			break;
		default:
			break;
	}
	
	//passwrdRead = ReadPwd();
	passwrdRead = 0;
	disp->sub_menu_disp_flag = TRUE;
	if (passwrdRead == passwrd)	{
		disp->sub_menu_disp_flag = TRUE;
		disp->pswd_enter_flag = FALSE;
	} else {
		//���������ʾ��Ϣ
		//ͬʱ��������������flag
		disp->pswd_enter_flag = TRUE;
		disp->sub_menu_disp_flag = FALSE;
	}
	
	return;
}

void sub_menu_disp(menu_disp_t *disp)
{
	uchar cur_status = disp->sub_menu_disp_status;
	
	switch (disp->top_menu_disp_status) {
	case 0:  // �����Ӳ˵�1
			//passwrd=1;
		LCD_Clear();
		StaticDisp(3*4+(cur_status)%2*4,4,3); 
		ParamSetLogic((cur_status)%2);
		break;
	case 1:  // �����Ӳ˵�2
		//passwrd=2;
		LCD_Clear();
		StaticDisp(7*4+(cur_status-3)%12*4,4,3); 
		ParamSetLogic(2+(cur_status-3)%12);
		break;
	case 2:  // �����Ӳ˵�3
			//passwrd=3;
		LCD_Clear();
		StaticDisp(18*4+(cur_status-3)%8*4,4,3);
		ParamSetLogic(14+(cur_status-3)%8);
		break;
	default:
		break;
	}
	//������ȷ��Ҫ��disp->sub_menu_enter_flag = FALSE;
	//������������Ҫ��disp->sub_menu_enter_flag = TRUE;
}

void DisplayLogic(menu_disp_t *disp)
{
	uchar LoopMenuNum = 0;
	uchar top_disp_status = disp->top_menu_disp_status;
	//uchar currentStatus = 0;  //״̬����ʶ
	//0xff �޸�����ʾ��
	//ȡ������ʾ��ʼ����,���������а��������������

	// status disp
	if (disp->menu_disp_flag) {
		LCD_Clear();
		StaticDisp(0,4,0xff);
		return;
	}
	
#if 1
	if (disp->sub_menu_disp_flag) {
		sub_menu_disp(disp);
		return;
	}
	
	if (disp->pswd_menu_disp_flag) {
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
		//��ʾ�˵���ڽ���
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
		//��ʾ�����������
		case 2: 
			paswd_disp(NULL);
			break;

		case 4:  // �����Ӳ˵�1
				//passwrd=1;
				LCD_Clear();
				StaticDisp(3*4+(setKeyVal-3)%2*4,4,3); 
				ParamSetLogic((setKeyVal-3)%2);	break;  
				break;
		case 5:  // �����Ӳ˵�2
				//passwrd=2;
				LCD_Clear();
				StaticDisp(7*4+(setKeyVal-3)%12*4,4,3); 
				ParamSetLogic(2+(setKeyVal-3)%12);	break; 
				break;
		case 6:  // �����Ӳ˵�3
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




//��ɵĹ��ܣ��Ѳ������ֲ�ֳ��ַ�����ʾ�ڵ�����
//��������ַ����ֻ����洢�ڱ�����
void ParamSetLogic(uchar parmCurLine)
{
	uint remainder=0;
	//uchar paramNumSplit[5];
	uchar i=0, *chr, j=0;
	uint quitioent=0;
	float paramNum, paramNumInt;
	//paramNum=parameterSet[i][j];
	
	//���еĲ������ܳ��ޣ����޽�ֹ
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

//��ָ��ָ���һ���������ַ���ʾ����
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

//��һ����λ��Ϊ5λ�����ְ�λ��ֵ�һ��
//����Ϊ5����������
//��302.953 ת�� paramNumSplit=[3][0][2][.][9]
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
		
		//��paramNum��ֳ���������paramNumInt��С������paramNumFrc 
		paramNumFrc=modf(paramNum, &paramNumInt);
		//����ת��Ϊuint����ȡģ
		quitioent=paramNumInt;
		//printf("parm i %d \n", (uint) quitioent);
		//i��1��ʼ�������ת¼ƥ��
		for(i=1;i<6;i++)
			{
				
				remainder=quitioent%10; //����
				quitioent=quitioent/10; //��
				temp[i-1]=remainder;
				//��Ϊ0ʱת������
				if(quitioent==0)
					{
						break;
					}
			}
		//������temp�����ݰ�˳��д��paramNumSplit��
		for(j=0;i>0;i--)
			{
				paramNumSplit[j]=temp[i-1];
				//printf("parm j %d %d\n", (uint) paramNumSplit[j], (short) j);
				j++;
				//printf("parm j %d %d\n", (uint) paramNumSplit[j], (short) j);
			}
		//����δ����С���� ���Ϊ64
		if(j<5)
			{
				paramNumSplit[j]=64;
				j++;
			}

		//��С�����ָ���С����������λ������5λ���˳�
		for(;j<5;j++)
			{
				//����ת��������ȡģ����
				//С���������γ�10ȡģ���������
				quitioent=paramNumFrc*10;
				remainder=quitioent%10;
				paramNumSplit[j]=remainder;
				///printf("parm i %d \n", (uint) paramNumSplit[j]);
			}	
	}

//������paramNumSplit[5]���ַ�ת������
void CharToNumber(uchar *chr, float *number)
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


//�ڵ�4����ʾ5��С��ռλ������������λ
//�ȴ��û�����
//�Ҽ�ѭ���ƶ�������ѭ��ѡ��0-9,.��11���ַ�
//set ȷ���� esc ȡ��
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
		
		//�ѵ�ǰ����λ������д��������
		//numberInput = dwnKeyVal%11;
//		if(numberInput == 10)
//			{  
//				numberInput=64; //���
//			}
		//printf("rightkey %d %d\n", (short) rgtKeyVal, (short) rgtKeyValLast, (short) dwnKeyVal);
		//ת��һ�Σ�����ǵ�ţ�64�����������ϱ�ʾΪ10���Ա������ʾ
		//����������ڴ洢Ϊ64����ʾʱ��10
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
		
		//��ʾ��ǰֵ
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
		
		//��ֵ����ʾ
		//if()	
}


//�����ȡ���� ����0ȡ������0�����档
//����set ��ʱ�ڵ�2����ʾ �����ȡ�����ȴ�ȷ�ϡ�
void SaveCancel(void)
{
	
	//LCD_ClearLine(6,0);
	//StaticDisp(106,1,0);
	PutChnLine(106,3,0);
}


// ��ʾһ���ַ� �����ݣ���ʾλ�ã��Ƿ������
// �������ֵС��70 �����ַ���70��200 Ӣ���ַ���200���Ͽո��ַ���
void PutChnLine(uchar DBrowLine, uchar PageLine, uchar hiLightOn)
{
	uchar *chr, chrType=0;
	uchar pageNum;
	uchar ichar=0, charSqu=0;
	//uchar dispLine=0, charLoca=0, chrLen=0;
	//����
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
					//����ǽ�����0xff ������ǰ����ʾ
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


//��ʾ�����ַ�����ʾ���ݣ���ʾ��������������һ�У�0123����
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



//��Ҫ��ʾ���ַ�ת������� allStringSet������ַ�
//Ҫת���������,һ��ֻ��ʾһ���ַ�
//����һ��uchar�������һ�������ַָ��
void NumberToCharTab(uchar Val, uchar* chrp[], uchar* type )
{
	uchar charSqu=0, chrType;
					charSqu = Val;
					//����ǽ�����0xff ������ǰ����ʾ
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

// ������������������������ӵڼ��п�ʼ�壬�����λ
//clearLength ���ֽڱ�ʾ�ӵڼ����ַ���8λ����ʼ��
//���ֽڱ�ʾ�����λ������,���clearLength=0,�������
void LCD_ClearLine(uchar lineNum, uchar clearLength)
{
		uchar colStart=0, colLeng=0;
		uchar i,j;	
		colLeng=0x0F&clearLength;
		colStart=0xf0&clearLength;
		colStart=colStart/16;
		colStart=colStart*8;
		cl();
		if(colStart >= 64) //����64������
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
								SendCommand(COL+0); //�����ʹ�����0�п�ʼ
							}
						SendData(0x00);  //dat1
					}
			}
		lcd_fullDisable();
}
