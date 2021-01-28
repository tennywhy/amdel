#ifndef _common_H_
#define _common_H_
	// define shot keywords

#include "..\1head\C8051F000.h"   // SFR declarations
#include "..\1head\stdio.h"
#include "..\1head\intrins.h"
#include "..\1head\math.h"

//#include "..\3display\display.H"
//#include "..\1head\STARTUP.A51"

	// define shot keywords
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

#define EPS 1e-7


#define TRUE 1
#define FALSE 0
typedef struct {
	uint top_menu_disp_flag : 1;
	uint top_menu_disp_status : 1;
	uint top_menu_select_row : 1;
	uint pswd_menu_disp_flag : 1;
	uint pswd_menu_disp_status : 1;
	uint pswd_menu_select_col : 1;
	uint sub_menu_disp_flag : 1;
	uint sub_menu_disp_status : 1;
	uint sub_menu_param_status : 6;
	uint sub_menu_param_enter : 1;
	uint sub_menu_select_row : 1;
	uint sub_menu_select_col : 1;
	uint pswd_enter_flag : 1;
	uint pswd_cmp_flag : 1;
	uint menu_disp_flag : 1;
} menu_disp_t;


void DebugStop (void);


#endif






































