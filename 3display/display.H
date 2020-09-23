/*--------------------------------------------------------------------------
display.H

202009142120
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef LCD_INIT_H
#define LCD_INIT_H

	//sbit rs  = P3^0;

	#if (1) 
		sbit lcd_cs2 = P2^0;
		sbit rst = P2^1; 
		sbit rw  = P2^4; // Ĭ�ϵͣ��ӵ�
		sbit lcd_en  = P2^6;
		sbit cs1 = P2^7;

		sbit nBLEN = P3^6;
		sbit rs  = P3^7;  //LCD_DI
	#endif
	
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
	
	void LCD_TEST(void);

#endif
