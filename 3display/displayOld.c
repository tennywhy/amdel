//LCD_display
#include "..\1head\0common.h"
#include "displayOld.h"
#include "struct.h"




/*  O_Y:����ʾ�ַ�ʱ����Ϊ�е�ַ: 0~7
	   �ڻ����ʾʱ����Ϊ�е�ַ(0-63)
	O_X:�е�ַ(0~127)
	com:ָ����Ĵ���
	dat1:���ݼĴ��� */
unsigned int O_X, O_Y, com, dat1;
unsigned char countl, code_i;
unsigned char code picture2[];
unsigned char code zf1[6][18]; /*9*16*/
unsigned char code picture3[]; /*112*64ͼƬ ��벿��58*64*/
unsigned char code picture4[]; /*112*64ͼƬ �Ұ벿��58*64*/
unsigned char code picture5[]; /*112*64ͼƬ ��벿��358*64*/
unsigned char code picture6[]; /*112*64ͼƬ �Ұ벿��58*64*/

/*��������*/
/*״̬���*/
//����
void CheckStatel()
{
	unsigned char dat;
	cs1=1;cs2=0;
	di=0;
	rw=1;
	do{
		LCD12864DataPort = 0xff;
		en=1; dat=LCD12864DataPort; en=0;
		dat=0x90 & dat; /*������4rest, 7busyΪ0ʱ�ſɲ���*/
		}while(!(dat==0x00) );
}
/*��LCD��������*/
/*command : ���� */
void PR1()
{
	CheckStatel();
	rw=0;
	LCD12864DataPort=com;
	en=1; en=0; /*�½��� */
}
/*д��ʾ����+/
/* dat:��ʾ����*/
void PR2()
{
	CheckStatel();
	di=1; rw=0;
	LCD12864DataPort=dat1;
	en=1; en=0;
}

/*����ʾ����*/
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
/*��������*/
/*״̬���*/
void CheckState2()
{
	unsigned char dat;
	cs1=0;cs2=1;
	di=0;
	rw=1;
	do {
	LCD12864DataPort=0xff;
	en=1; dat=LCD12864DataPort; en=0;
	dat=0x90 & dat; /*������4rest, 7busy Ϊ0ʱ�ſɲ���*/
	}while(!(dat==0x00));
}
/*****************************************************/
/*��LCD��������*/
/*command : ����*/
//����������
void PR4()
{
	CheckState2();
	rw=0;
	LCD12864DataPort=com;
	en=1; en=0; /*�½��� */
}
/*д��ʾ����*/
/*dat:��ʾ����*/
//д��������
void PR5()
{
	CheckState2();
	di=1; rw=0;
	LCD12864DataPort=dat1;
	en=1; en=0;
}
/*����ʾ����*/
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
	16*16��������д�뺯��ccw_PR
	��������ѡ��:PARA1
	�ڲ����ú���:PR1(), PR2(), PR4(), PR5()
	�����ֿ�: CCTAB
	�����������: CCW_PR()
	�����������: O_XL, O_YL, CODE_1
*********************************************/

CCW_PR()
{
			unsigned char i,j,k;
			i=0;
			j=paral;
	loop: 	com=O_Y|0xb8; /*ҳ��*/ //ȡҳ������ 
			PR1(); //����������
			PR4(); //����������
				if(O_X<j) /*�ж��İ���*/ //С��64������
					{
						com=O_X|0x40; /*�е�ַ����*/
						PR1(); //����������
						k=1; //��������־
					}
				else
					{
						com=(O_X-j)|0x40; /*�е�ַ����*/
						PR4();
						k=0;
					}
					com=com&0x3f; /*ȡ�е�ַ*/ //ȥ��ָ����
				for(count1=i;count1<i+16;countl++)
					{
						//�Զ�LCD���е�ַ
						dat1=CCTAB[code_1][countl];
							if(k==1) /*��������*/
								{
									PR2(); //д��������
								}
							else
								{
									PR5(); //д��������
								}
									com++; /*�е�ַ��1*/
							if(com==j) /*����*/ //64Ϊ����(0~63)
								{
									if(k==1) //��־����
										{
											com=0; //�е�ַ����
											PR4();
											k=0;
										}
									else
										{
											goto loop2;
										}
								}
					}
	loop2: if(i==0) /*д��һҳ*/
			 {
			 	i=16;
				O_Y++; /*ҳ��ַ+1*/
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
	16*16���׵�������д�뺯�� CCW_PR
	��������ѡ����: PARA1
	�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
	�����ֿ�: CCTAB
	�����������: CCW_PR()
	�����������: O_XL, O_YL, CODE_1
***********************************************************/

CCW_PR1()
{
		unsigned char i,j,k;
		i=0;
		j=paral;
	loop: 	com=O_Y|0xb8; /*ҳ��*/
			PR1();
			PR4();
			if(O_X<j) /*�ж��İ���*/
				{
					com=O_X|0x40; /*�е�ַ����*/
					PR1();
					k=1;
				}
			else
				{
					com=(O_X-j)|0x40; /*�е�ַ����*/
					PR4();
					k=0;
				}
			com=com&0x3f; /*ȡ�е�ַ*/
			for(countl=i;count1<i+16;count1++)
				{
					dat1=(CCTAB[code_1][count1]^0xff);
					if(k==1) /*��������*/
						{
							PR2();
						}
					else
						{
							PR5();
						}
					com++; /*�е�ַ��1*/
					if(com==j) /*����*/
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
	loop2:	if(i==0) /*д��һҳ*/
				{
					i=16;
					O_Y++; /*ҳ��ַ+1*/
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
	�����ַ�д�뺯��: CW_PR     		//8*8
	��������ѡ��: PARA1
	�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
	�����ֿ�: ��HTAB
	�����������: CW_PR()
	�����������: O_X,O_Y,CODE_1
	/******:
	
	
********************************************************/
CW_PR()
{
	unsigned char j;
	j=paral;
	com=O_Y|0xb8; /*ҳ��ַ*/ //ȡҳ����
	PR1(); //������
	PR4(); //������
	if(O_X<j)  //���� �ж����ĸ���
		{
			com=O_X|0x40; /*�е�ַ*/
			PR1();
			O_Y=1;
		}
	else
		{
			com=(O_X-j)|0x40;
			PR4();
			O_Y=0;
		}
	com=com&0x3f; //ȡ��ַȥ��ָ����
	for(count1=0;count1<6;count1++) /*8*6*/
	{
		dat1=CHTAB[code_1][count1];
			if(O_Y==1)
				{
					PR2(); //д����
				}
			else
				{
					PR5(); //д����
				}
		com++; //�е�ַ��1
		if(com==j)  //����
			{
				if(O_Y==1) //��־Ϊ����
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
	�����ַ�д�뺯��:CW_PR1
	��������ѡ��: PARA1
	�ڲ����ú���: PR1(), PR2(), PR4(), PR5()
	�����ֿ�: CHTAB
	�����������: CW_PR()
	�����������: O_X,0_Y,CODE_1
*********************************************/
CW_PR1()
{
	unsigned char i,j,k;
	i=0;
	j=paral;
	loop:	com=O_Y|0xb8; /*ҳ��*/
			PR1();
			PR4();
			if(O_X<j) /*�ж��İ���*/ //������
				{
					com=O_X|0x40; /*�е�ַ����*/
					PR1(); //����������
					k=1; //��������־
				}
			else
				{
					com=(O_X-j)|0x40 /*�е�ַ����*/
					PR4();
					k=0;
				}
			com=com&0x3f; /*ȡ�е�ַ*/
			for(count1=i;count1<i+9;countl++)
				{
					dat1=zfl[code_1][countl];
					if(k==1) /*��������*/
						{
							PR2();
						}
					else
						{
							PR5();
						}
					com++; /*�е�ַ��һ*/
					if(com==j) /*����*/
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
	loop2:	if(i==0) /*д��һҳ*/
				{
					i=9;
					OY++; /*ҳ��ַ+1*/
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
	��������: CLEAR
	����ʾRAM��(����)����: CLEAR
	�ڲ����ú���: PR1(), PR2(), PR4(),PR5()
	�����������: CLEAR()
***********************************************/

CLEAR()
{
	for(count1=0xb8;count1!=0xC0;count1++)
	/*��ҳ��ַ��Ϊѭ����*/
	{
		com=count1; /* ҳ��ַ */
		PR1();
		PR4();		
		com=0x40; /* �е�ַ���� */
		PR1();
		PR4();
		/*�������HD61202���ڲ�RAM��Ԫ*/
		for(com=0;com<64; com++)
			{	
				dat1=0x00;
				PR2();
				PR5();
			}
		}
}

/******************************************
	��㺯��: W_DoT()
	��������ѡ��: PARA1
	�ڲ����ú���:  PR1()~PR6()
	�����������: W_DOT()
	�����������: O_x, O_Y
******************************************/

/*��ʱ*/
Lcd12864delay(unsigned int delayms)
{


}

