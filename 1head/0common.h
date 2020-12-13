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

#define TRUE 1
#define FALSE 0
typedef struct {
	uchar top_menu_disp_flag;
	uchar top_menu_disp_status;
	uchar top_menu_select_row;
	uchar pswd_menu_disp_flag;
	uchar pswd_menu_disp_status;
	uchar pswd_menu_select_col;
	uchar sub_menu_disp_flag;
	uchar sub_menu_disp_status;
	uchar sub_menu_enter_flag;
	uchar sub_menu_select_row;
	uchar sub_menu_select_col;
	uchar pswd_enter_flag;
	uchar pswd_cmp_flag;
	uchar menu_disp_flag;
} menu_disp_t;


void DebugStop (void);


#endif



































	
	
	
