/*--------------------------------------------------------------------------
display.H

202009142120
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef _dsplMenu_H_
#define _dsplMenu_H_
//#include "struct.h"
#define PWD1 1
#define PWD2 2
#define PWD3 3
#define PARAMlENGTH 5	



#define kong 0     //NULL  
#define bao 1     //��
#define cun 2     //��
#define she 3     //��
#define zhi 4     //��
#define hui 5     //��
#define fu 6     //��
#define que 7     //ȷ
#define ren 8     //��
#define qu 9     //ȡ
#define xiao 10    //��
#define shu 11    //��
#define zhii 12    //ֵ
#define guo 13    //��
#define da 14    //��
#define xiaoo 15    //С
#define mi 16    //��
#define ma 17    //��
#define cuo 18    //��
#define ji 19    //��
#define lv 20    //��
#define du 21    //��
#define nong 22    //Ũ
#define yii 23    //һ
#define jii 24    //��
#define can 25    //��
#define er 26    //��
#define shuu 27    //��
#define chu 28    //��
#define jiao 29    //У
#define zhen 30    //��
#define ye 31    //Һ
#define ti 32    //��
#define xuan 33    //��
#define fuu 34    //��
#define gu 35    //��
#define xi 36    //��
#define shou 37    //��
#define xii 38    //ϵ
#define chuan 39    //��
#define xia 40    //��
#define xian 41    //��
#define shang 42    //��
#define xuann 43    //ѡ
#define zhe 44    //��
#define diann 45    //��
#define liu 46    //��
#define bo 47    //��
#define te 48    //��
#define yan 49    //��
#define fang 50    //��
#define shi 51    //ʽ
#define bei 52    //��
#define hao 53    //��
#define zhun 54    //׼
#define xin 55    //��
#define ru 56    //��
#define ling 57    //��
#define dian 58    //��
#define liang 59    //��
#define cheng 60    //��
#define che 61    //��
#define shii 62    //��
#define wu 63    //��
#define qii 64    //��
#define ou 65    //ż
#define yong 66    //��
#define hu 67    //��
#define tong 68    //ͳ
#define wei 69    //Ϊ
#define kun 70    //��
#define ming 71    //��
#define yee 72    //ұ
#define yann 73    //��
#define maoh 62    //:
													
#define chrNum 100  //�ַ�����ƫ��;   
#define spcNum 200	//�ո���ƫ��;  
#define chn(charNum) (charNum+100)
#define spn(spaceN) (spaceN+200)
													
#define  chn0  100
#define  chn1  101
#define  chn2  102
#define  chn3  103
#define  chn4  104
#define  chn5  105
#define  chn6  106
#define  chn7  107
#define  chn8  108
#define  chn9  109
#define  chnA  110
#define  chnB  111
#define  chnC  112
#define  chnD  113
#define  chnE  114
#define  chnF  115
#define  chnG  116
#define  chnH  117
#define  chnI  118
#define  chnJ  119
#define  chnK  120
#define  chnL  121
#define  chnM  122
#define  chnN  123
#define  chnO  124
#define  chnP  125
#define  chnQ  126
#define  chnR  127
#define  chnS  128
#define  chnT  129
#define  chnU  130
#define  chnV  131
#define  chnW  132
#define  chnX  133
#define  chnY  134
#define  chnZ  135
#define  chna  136
#define  chnb  137
#define  chnc  138
#define  chnd  139
#define  chne  140
#define  chnf  141
#define  chng  142
#define  chnh  143
#define  chni  144
#define  chnj  145
#define  chnk  146
#define  chnl  147
#define  chnm  148
#define  chnn  149
#define  chno  150
#define  chnp  151
#define  chnq  152
#define  chnr  153
#define  chns  154
#define  chnt  155
#define  chnu  156
#define  chnv  157
#define  chnw  158
#define  chnx  159
#define  chny  160
#define  chnz  161
#define  chnmh  162
#define  chnyh  163
#define  chndh  164
#define  chnjh  165
#define  chnxg  166
#define  chnbfh  167

	extern uchar setKeyVal, rgtKeyVal, dwnKeyVal, escKeyVal ;
	extern uchar setKeyValLast, rgtKeyValLast, dwnKeyValLast, escKeyValLast;


	void StartMenu(void);
	void ParamMenue(void);
	void StaticDisp(uchar DBrowLine, uchar RowNub, uchar hightLightRow);
	void PutChnLine(uchar DBrowLine, uchar PageLine, uchar hiLightOn);
	void DisplayLogic(menu_disp_t *disp);
	void ParamSetLogic(uchar parmCurLine);
	void DispPramOnSecLine(uchar *chr);
	void DispPramOnThirdLine(uchar *chr);
	void NumberToChar(uchar *chr);
	void CharToNumber(uchar *chr[], float *number);
	void ParameterInputDisplay( uchar * userParam[]);
	void NumberToCharTab(uchar Val, uchar* chrp[], uchar* type );
	void SaveCancel(void);
	void LCD_ClearLine(uchar lineNum, uchar clearLength);

	

#endif




