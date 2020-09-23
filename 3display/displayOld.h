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
		sbit rw  = P2^4; // Ĭ�ϵͣ��ӵ�
		sbit lcd_en  = P2^6;
		sbit cs1 = P2^7;

		sbit nBLEN = P3^6;
		sbit rs  = P3^7;  //LCD_DI
	#elif (1)
		/* LCD128*64 ������*/
		sbit nBLEN = P3^6;
		#define LCD12864DataPort P1
		// LCD128*64 I/O�źŹܽ�
		sbit di =P3^7; // ����/ָ��ѡ��
		sbit rw =P2^4; //��д ѡ��
		sbit en =P2^6; //��дʹ��
		sbit cs2 =P2^0; //Ƭѡ1,����Ч(ǰ64��)
		sbit cs1 =P2^7; // Ƭѡ2,����Ч(��64��)
		sbit res= P2^1;	
		//#else
	
	#endif


	/*�������� */
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

	#define S_LINE    0xc0    // ��ʾ��ʼ�� StartLine+0~63
	#define PAGE      0xb8    //  ҳ��ַ���� PAGE+0~8  
	#define COL       0x40    //  �е�ַ����  COL+0~63
	#define DISON     0x3f    // ��ʾ��
	//#define DISOFF    (0x3f-1)  //  ��ʾ��    ram������
	#define DISOFF    0x3e  //  ��ʾ��    ram������

	#define cl();  cs1=0;lcd_cs2=1;   // ��ѡ
	//��ѡ  //��ģ��FM12864A-3�Ľӿڣ�15��CS1��16��lcd_cs2������	
	#define cr();  cs1=1;lcd_cs2=0;   
	#define ca();  cs1=1;lcd_cs2=1;   //ȫѡ15��CS1��16��lcd_cs2   
	#define nca();  cs1=0;lcd_cs2=0;   //ȫ��ѡ	  15��CS1��16��lcd_cs2   

	
	uchar code fm[];
	uchar code zifu[];
	uchar code qzd[];
	//extern uchar key;
	//extern uchar Line;
	
	/*********************************************
		16*16��������д�뺯��ccw_PR
		��������ѡ��:PARA1
		�ڲ����ú���:PR1(), PR2(), PR4(), PR5()
		�����ֿ�: CCTAB
		�����������: CCW_PR()
		�����������: O_XL, O_YL, CODE_1
	*********************************************/
	void CCW_PR(void);

	/**********************************************************
		16*16���׵�������д�뺯�� CCW_PR
		��������ѡ����: PARA1
		�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
		�����ֿ�: CCTAB
		�����������: CCW_PR()
		�����������: O_XL, O_YL, CODE_1
	***********************************************************/
	void CCW_PR1(void);

	/********************************************************
		�����ַ�д�뺯��: CW_PR     		//8*8
		��������ѡ��: PARA1
		�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
		�����ֿ�: ��HTAB
		�����������: CW_PR()
		�����������: O_X,O_Y,CODE_1	
	********************************************************/
	void CW_PR(void);

	/****************8 *16*********************
		�����ַ�д�뺯��:CW_PR1
		��������ѡ��: PARA1
		�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
		�����ֿ�: CHTAB
		�����������: CW_PR()
		�����������: O_X,0_Y,CODE_1
	*********************************************/
	void CW_PR1(void);

	/**********************************************
		��������: CLEAR
		����ʾRAM��(����)����: CLEAR
		�ڲ����ú���: PR1(), PR2(), PR4(),PR5()
		�����������: CLEAR()
	***********************************************/
	void CLEAR(void);

	
#endif

































	
	
	
