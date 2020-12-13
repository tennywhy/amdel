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
#define bao 1     //保
#define cun 2     //存
#define she 3     //设
#define zhi 4     //置
#define hui 5     //恢
#define fu 6     //复
#define que 7     //确
#define ren 8     //认
#define qu 9     //取
#define xiao 10    //消
#define shu 11    //数
#define zhii 12    //值
#define guo 13    //过
#define da 14    //大
#define xiaoo 15    //小
#define mi 16    //密
#define ma 17    //码
#define cuo 18    //错
#define ji 19    //计
#define lv 20    //率
#define du 21    //度
#define nong 22    //浓
#define yii 23    //一
#define jii 24    //级
#define can 25    //参
#define er 26    //二
#define shuu 27    //输
#define chu 28    //出
#define jiao 29    //校
#define zhen 30    //正
#define ye 31    //液
#define ti 32    //体
#define xuan 33    //悬
#define fuu 34    //浮
#define gu 35    //固
#define xi 36    //吸
#define shou 37    //收
#define xii 38    //系
#define chuan 39    //传
#define xia 40    //下
#define xian 41    //限
#define shang 42    //上
#define xuann 43    //选
#define zhe 44    //择
#define diann 45    //电
#define liu 46    //流
#define bo 47    //波
#define te 48    //特
#define yan 49    //验
#define fang 50    //方
#define shi 51    //式
#define bei 52    //备
#define hao 53    //号
#define zhun 54    //准
#define xin 55    //新
#define ru 56    //入
#define ling 57    //零
#define dian 58    //点
#define liang 59    //量
#define cheng 60    //程
#define che 61    //测
#define shii 62    //试
#define wu 63    //无
#define qii 64    //奇
#define ou 65    //偶
#define yong 66    //用
#define hu 67    //户
#define tong 68    //统
#define wei 69    //为
#define kun 70    //昆
#define ming 71    //明
#define yee 72    //冶
#define yann 73    //研
#define maoh 62    //:
													
#define chrNum 100  //字符数字偏移;   
#define spcNum 200	//空格数偏移;  
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
	void ParamSetLogic(uchar parmCurLine, float *outVal);
	void PswdSetLogic(uchar * pswd[5]);
	void DispPramOnSecLine(uchar *chr);
	void DispPramOnThirdLine(uchar *chr);
	void NumberToChar(uchar *chr);
	void CharToNumber(uchar *chr[], float *number);
	void ParameterInputDisplay(uchar *userParam, float *outval);
	void NumberToCharTab(uchar Val, uchar* chrp[], uchar* type );
	void SaveCancel(void);
	void LCD_ClearLine(uchar lineNum, uchar clearLength);

	

#endif





