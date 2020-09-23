#ifndef _display_H_
#define _display_H_


	//#include <reg51.h>
	//#include <math.h>
	//#include <absacc.h>
	//#include <string.h>
	//#include <main.h>
	//#include "display.h"
	
	//uchar dat1;
	uchar count1;
	uchar code_1;
	uint CCTAB;
	bool F_Rs485SendStart;
	bool F_Rs485Busy;
	

	//sbit rs  = P3^0;

	#if (0) 
		sbit lcd_cs2 = P2^0;
		sbit rst = P2^1; 
		sbit rw  = P2^4; // 默认低，接地
		sbit lcd_en  = P2^6;
		sbit cs1 = P2^7;

		sbit nBLEN = P3^6;
		sbit rs  = P3^7;  //LCD_DI
	#elif (1)
		/* LCD128*64 数据线*/
		sbit nBLEN = P3^6;
		#define LCD12864DataPort P1
		// LCD128*64 I/O信号管脚
		sbit di =P3^7; // 数据/指令选择
		sbit rw =P2^4; //读写 选择
		sbit en =P2^6; //读写使能
		sbit cs2 =P2^0; //片选1,高有效(前64列)
		sbit cs1 =P2^7; // 片选2,高有效(后64列)
		sbit res= P2^1;	
		//#else
	
	#endif


	/*常量定义 */
	#define display_on 0x3f;
	#define display_off 0x3e;
	#define start_line0 0xc0;
	#define paral 0x40; /*64*/

	
	//sbit key = P3^3;
	sbit LED  = P2^2; 
	//LED =1;

	#define DB  P1
	#define uchar unsigned char
	#define uint  unsigned int

	#define S_LINE    0xc0    // 显示起始行 StartLine+0~63
	#define PAGE      0xb8    //  页地址设置 PAGE+0~8  
	#define COL       0x40    //  列地址设置  COL+0~63
	#define DISON     0x3f    // 显示开
	//#define DISOFF    (0x3f-1)  //  显示关    ram被置零
	#define DISOFF    0x3e  //  显示关    ram被置零

	#define cl();  cs1=0;lcd_cs2=1;   // 左选
	//右选  //因模块FM12864A-3的接口（15脚CS1、16脚lcd_cs2）有误	
	#define cr();  cs1=1;lcd_cs2=0;   
	#define ca();  cs1=1;lcd_cs2=1;   //全选15脚CS1、16脚lcd_cs2   
	#define nca();  cs1=0;lcd_cs2=0;   //全不选	  15脚CS1、16脚lcd_cs2   

	
	uchar code fm[];
	uchar code zifu[];
	uchar code qzd[];
	//extern uchar key;
	//extern uchar Line;
	
	/*********************************************
		16*16点阵中文写入函数ccw_PR
		函数参数选择:PARA1
		内部调用函数:PR1(), PR2(), PR4(), PR5()
		连接字库: CCTAB
		函数调用入口: CCW_PR()
		函数输入变量: O_XL, O_YL, CODE_1
	*********************************************/
	void CCW_PR(void);

	/**********************************************************
		16*16反白点阵中文写入函数 CCW_PR
		函数参数选先择: PARA1
		内部调用函数: PR1(), PR2(), PR4(), PR5()
		连接字库: CCTAB
		函数调用入口: CCW_PR()
		函数输入变量: O_XL, O_YL, CODE_1
	***********************************************************/
	void CCW_PR1(void);

	/********************************************************
		西文字符写入函数: CW_PR     		//8*8
		函数参数选择: PARA1
		内部调用函数: PR1(), PR2(), PR4(), PR5()
		连接字库: СHTAB
		函数调用入口: CW_PR()
		函数输入变量: O_X,O_Y,CODE_1	
	********************************************************/
	void CW_PR(void);

	/****************8 *16*********************
		西文字符写入函数:CW_PR1
		函数参数选择: PARA1
		内部调用函数: PR1(), PR2(), PR4(), PR5()
		连接字库: CHTAB
		函数调用入口: CW_PR()
		函数输入变量: O_X,0_Y,CODE_1
	*********************************************/
	void CW_PR1(void);

	/**********************************************
		清屏函数: CLEAR
		清显示RAM区(清屏)函数: CLEAR
		内部调用函数: PR1(), PR2(), PR4(),PR5()
		函数调用入口: CLEAR()
	***********************************************/
	void CLEAR(void);

	
#endif

































	
	
	
