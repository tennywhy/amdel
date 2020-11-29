//LCD_display
#include "..\1head\0common.h"
#include "displayOld.h"
#include "struct.h"




/*  O_Y:在显示字符时定义为行地址: 0~7
	   在绘点显示时定义为行地址(0-63)
	O_X:列地址(0~127)
	com:指令码寄存器
	dat1:数据寄存器 */
unsigned int O_X, O_Y, com, dat1;
unsigned char countl, code_i;
unsigned char code picture2[];
unsigned char code zf1[6][18]; /*9*16*/
unsigned char code picture3[]; /*112*64图片 左半部分58*64*/
unsigned char code picture4[]; /*112*64图片 右半部分58*64*/
unsigned char code picture5[]; /*112*64图片 左半部分358*64*/
unsigned char code picture6[]; /*112*64图片 右半部分58*64*/

/*左屏操作*/
/*状态检查*/
//左屏
void CheckStatel()
{
	unsigned char dat;
	cs1=1;cs2=0;
	di=0;
	rw=1;
	do{
		LCD12864DataPort = 0xff;
		en=1; dat=LCD12864DataPort; en=0;
		dat=0x90 & dat; /*仅当第4rest, 7busy为0时才可操作*/
		}while(!(dat==0x00) );
}
/*向LCD发送命令*/
/*command : 命令 */
void PR1()
{
	CheckStatel();
	rw=0;
	LCD12864DataPort=com;
	en=1; en=0; /*下降沿 */
}
/*写显示数据+/
/* dat:显示数据*/
void PR2()
{
	CheckStatel();
	di=1; rw=0;
	LCD12864DataPort=dat1;
	en=1; en=0;
}

/*读显示数据*/
unsigned char PR3()
{
	unsigned char dat;
	CheckStatel();
	di=1; rw=1;
	LCD12864DataPort=0xff;
	en=1; dat=LCD12864DataPort;
	;en=0;
	return(dat);
}
/*右屏操作*/
/*状态检查*/
void CheckState2()
{
	unsigned char dat;
	cs1=0;cs2=1;
	di=0;
	rw=1;
	do {
	LCD12864DataPort=0xff;
	en=1; dat=LCD12864DataPort; en=0;
	dat=0x90 & dat; /*仅当第4rest, 7busy 为0时才可操作*/
	}while(!(dat==0x00));
}
/*****************************************************/
/*向LCD发送命令*/
/*command : 命令*/
//右屏发命令
void PR4()
{
	CheckState2();
	rw=0;
	LCD12864DataPort=com;
	en=1; en=0; /*下降沿 */
}
/*写显示数据*/
/*dat:显示数据*/
//写右屏数据
void PR5()
{
	CheckState2();
	di=1; rw=0;
	LCD12864DataPort=dat1;
	en=1; en=0;
}
/*读显示数据*/
unsigned char PR6()
{
	unsigned char dat;
	CheckState2();
	di=1; rw=1;
	LCD12864DataPort=0xff;
	en=1; dat=LCD12864DataPort; en=0;
	return(dat);
}

/*********************************************
	16*16点阵中文写入函数ccw_PR
	函数参数选择:PARA1
	内部调用函数:PR1(), PR2(), PR4(), PR5()
	连接字库: CCTAB
	函数调用入口: CCW_PR()
	函数输入变量: O_XL, O_YL, CODE_1
*********************************************/

CCW_PR()
{
			unsigned char i,j,k;
			i=0;
			j=paral;
	loop: 	com=O_Y|0xb8; /*页号*/ //取页号命令 
			PR1(); //发左屏命令
			PR4(); //发右屏命令
				if(O_X<j) /*判断哪半屏*/ //小于64是左屏
					{
						com=O_X|0x40; /*列地址设置*/
						PR1(); //发左屏命令
						k=1; //置左屏标志
					}
				else
					{
						com=(O_X-j)|0x40; /*列地址设置*/
						PR4();
						k=0;
					}
					com=com&0x3f; /*取列地址*/ //去掉指令码
				for(count1=i;count1<i+16;countl++)
					{
						//自动LCD加列地址
						dat1=CCTAB[code_1][countl];
							if(k==1) /*左屏内容*/
								{
									PR2(); //写左屏数据
								}
							else
								{
									PR5(); //写右屏数据
								}
									com++; /*列地址加1*/
							if(com==j) /*右屏*/ //64为右屏(0~63)
								{
									if(k==1) //标志左屏
										{
											com=0; //列地址清零
											PR4();
											k=0;
										}
									else
										{
											goto loop2;
										}
								}
					}
	loop2: if(i==0) /*写下一页*/
			 {
			 	i=16;
				O_Y++; /*页地址+1*/
				if(O_Y==8)
					{
						return;
					}
				else
					{
						goto loop;
					}
			 }
}
		
/**********************************************************
	16*16反白点阵中文写入函数 CCW_PR
	函数参数选先择: PARA1
	内部调用函数: PR1(), PR2(), PR4(), PR5()
	连接字库: CCTAB
	函数调用入口: CCW_PR()
	函数输入变量: O_XL, O_YL, CODE_1
***********************************************************/

CCW_PR1()
{
		unsigned char i,j,k;
		i=0;
		j=paral;
	loop: 	com=O_Y|0xb8; /*页号*/
			PR1();
			PR4();
			if(O_X<j) /*判断哪半屏*/
				{
					com=O_X|0x40; /*列地址设置*/
					PR1();
					k=1;
				}
			else
				{
					com=(O_X-j)|0x40; /*列地址设置*/
					PR4();
					k=0;
				}
			com=com&0x3f; /*取列地址*/
			for(countl=i;count1<i+16;count1++)
				{
					dat1=(CCTAB[code_1][count1]^0xff);
					if(k==1) /*左屏内容*/
						{
							PR2();
						}
					else
						{
							PR5();
						}
					com++; /*列地址加1*/
					if(com==j) /*右屏*/
						{
							if(k==1)
								{
									com=0;
									PR4();
									k=0;
								}
							else
								{
									goto loop2;
								}
						}
				}
	loop2:	if(i==0) /*写下一页*/
				{
					i=16;
					O_Y++; /*页地址+1*/
					if(O_Y==8)
						{
							return;
						}
					else
						{
							goto loop;
						}
		}
}

/********************************************************
	西文字符写入函数: CW_PR     		//8*8
	函数参数选择: PARA1
	内部调用函数: PR1(), PR2(), PR4(), PR5()
	连接字库: СHTAB
	函数调用入口: CW_PR()
	函数输入变量: O_X,O_Y,CODE_1
	/******:
	
	
********************************************************/
CW_PR()
{
	unsigned char j;
	j=paral;
	com=O_Y|0xb8; /*页地址*/ //取页命令
	PR1(); //发左屏
	PR4(); //发右屏
	if(O_X<j)  //左屏 判断是哪个屏
		{
			com=O_X|0x40; /*列地址*/
			PR1();
			O_Y=1;
		}
	else
		{
			com=(O_X-j)|0x40;
			PR4();
			O_Y=0;
		}
	com=com&0x3f; //取地址去掉指令码
	for(count1=0;count1<6;count1++) /*8*6*/
	{
		dat1=CHTAB[code_1][count1];
			if(O_Y==1)
				{
					PR2(); //写左屏
				}
			else
				{
					PR5(); //写右屏
				}
		com++; //列地址加1
		if(com==j)  //右屏
			{
				if(O_Y==1) //标志为左屏
					{
						com=0x40;
						PR4();
						O_Y=0;
					}
				else
					{
						return;
					}
			}
		}
}

/****************8 *16*********************
	西文字符写入函数:CW_PR1
	函数参数选择: PARA1
	内部调用函数: PR1(), PR2(), PR4(), PR5()
	连接字库: CHTAB
	函数调用入口: CW_PR()
	函数输入变量: O_X,0_Y,CODE_1
*********************************************/
CW_PR1()
{
	unsigned char i,j,k;
	i=0;
	j=paral;
	loop:	com=O_Y|0xb8; /*页号*/
			PR1();
			PR4();
			if(O_X<j) /*判断哪半屏*/ //屏左屏
				{
					com=O_X|0x40; /*列地址设置*/
					PR1(); //发左屏命令
					k=1; //置左屏标志
				}
			else
				{
					com=(O_X-j)|0x40 /*列地址设置*/
					PR4();
					k=0;
				}
			com=com&0x3f; /*取列地址*/
			for(count1=i;count1<i+9;countl++)
				{
					dat1=zfl[code_1][countl];
					if(k==1) /*左屏内容*/
						{
							PR2();
						}
					else
						{
							PR5();
						}
					com++; /*列地址加一*/
					if(com==j) /*右屏*/
						{
							if(k==1)
								{
									com=0;
									PR4();
									k=0;
								}
							else
								{
									goto loop2;
								}
						}
				}
	loop2:	if(i==0) /*写下一页*/
				{
					i=9;
					OY++; /*页地址+1*/
					if(O_Y==8)
						{
							return;
						}
					else
						{
							goto loop;
						}
		}
}

/**********************************************
	清屏函数: CLEAR
	清显示RAM区(清屏)函数: CLEAR
	内部调用函数: PR1(), PR2(), PR4(),PR5()
	函数调用入口: CLEAR()
***********************************************/

CLEAR()
{
	for(count1=0xb8;count1!=0xC0;count1++)
	/*以页地址作为循环量*/
	{
		com=count1; /* 页地址 */
		PR1();
		PR4();		
		com=0x40; /* 列地址设置 */
		PR1();
		PR4();
		/*清除所有HD61202的内部RAM单元*/
		for(com=0;com<64; com++)
			{	
				dat1=0x00;
				PR2();
				PR5();
			}
		}
}

/******************************************
	绘点函数: W_DoT()
	函数参数选择: PARA1
	内部调用函数:  PR1()~PR6()
	函数调用入口: W_DOT()
	函数输入变量: O_x, O_Y
******************************************/

/*延时*/
Lcd12864delay(unsigned int delayms)
{


}

